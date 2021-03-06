#ifndef ULI_H_SENTRY
#define ULI_H_SENTRY

#include "bitarr.h"

class ULI {
  public:
    ULI(unsigned int base);
    ULI(const ULI &a);
    explicit ULI(unsigned int num, unsigned int base);
    ULI(const char *str, unsigned int base, size_t len = 0);

    void Print() const;
    bool IsEven() const;
    ULI operator+(const ULI &b) const;
    ULI operator+(unsigned int num) const;
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
    bool operator>(unsigned int num) const;
    bool operator<(const ULI &b) const;
    bool operator<(unsigned int num) const;
    bool operator<=(const ULI &b) const;
    bool operator<=(unsigned int num) const;
    bool operator>=(const ULI &b) const;
    bool operator==(const ULI &b) const;
    bool operator==(unsigned int num) const;
    bool operator!=(const ULI &b) const;
    bool operator!=(unsigned int b) const;
    bool IsPrimary(unsigned method = 1, unsigned k = 8) const;

    ULI FastMul(const ULI &b, int method = 0) const;

    static ULI power_mod(const ULI &a, const ULI &power, const ULI &mod);
    static ULI random(const ULI &from, const ULI &to, const ULI &seed);
    static ULI gcd(const ULI &a, const ULI &b);

    // JACOBI SYMBOL
    static int jac_sym(const ULI &a, const ULI &n);
    // TEST LEMERA FOR MERSEN's NUMBERS
    static bool lemera_test(unsigned num);

    friend bool operator<=(unsigned num, const ULI &b);

  private:
    bitarr arr;
    unsigned int base;

    ULI();
    void ParseString(const char *string, size_t len);
    void DivAndMod(const ULI &b, ULI &div, ULI &mod) const;
    void SliceByHalfs(ULI &a_l, ULI &a_r, unsigned n) const;

    // MULTIPLICATION METHODS
    ULI Karatsuba(const ULI &b) const;

    // PRIMALITY TESTS
    bool RabinMiller(unsigned k) const;
    bool SoloveyShtrassen(unsigned k) const;
    bool Frobenius(unsigned k) const;

    static char *strrev(char *str);
};

typedef ULI uli;

#endif // ULI_H_SENTRY
