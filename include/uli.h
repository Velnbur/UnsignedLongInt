#ifndef ULI_H_SENTRY
#define ULI_H_SENTRY

#include "bitarr.h"

class ULI {
public:
    ULI(unsigned int base);
    ULI(const ULI &a);
    ULI(unsigned int num, unsigned int base);
    ULI(const char *str, size_t len, unsigned int base);
    ~ULI();

    char *ToString(char *str = nullptr, size_t len = 0) const;
    bool IsEven() const;
    ULI operator+(const ULI &b) const;
    ULI operator-(const ULI &b) const;
    ULI operator-(unsigned int num) const;
    ULI operator*(const ULI &b) const;
    ULI operator*(unsigned int num) const;
    ULI operator/(const ULI &b) const;
    ULI operator%(const ULI &b) const;
    ULI operator>>(unsigned int bits) const;
    ULI operator<<(unsigned int bits) const;
    ULI &operator=(const ULI &b);
    bool operator>(const ULI &b) const;
    bool operator<(const ULI &b) const;
    bool operator>(unsigned int num) const;
    bool operator>=(const ULI &b) const;
    bool operator==(const ULI &b) const;
    bool operator!=(unsigned int b) const;
    bool operator==(unsigned int num) const;
    bool IsPrimary(unsigned int method = 1) const;

    static ULI power_mod(const ULI &a, const ULI &power, const ULI &mod);
    static ULI rand(unsigned base);

private:
    bitarr *arr;
    int base;
    
    ULI();
    void ParseString(const char *string, size_t len);
    void DivAndMod(const ULI &b, ULI &div, ULI &mod) const;
    void SliceByHalfs(ULI &a_l, ULI &a_r, unsigned n) const;
    ULI Karatsuba(const ULI &b) const;
    bool Lemena() const;
    
    static char *strrev(char *str);
    static int
    len_from_digits(unsigned int digits, unsigned int base);
};

typedef ULI uli;

#endif // ULI_H_SENTRY
