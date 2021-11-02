#ifndef BITARR_H_SENTRY
#define BITARR_H_SENTRY

class BitArr {
public:
    BitArr(size_t len);
    BitArr(const BitArr &a);

    BitArr &operator=(const BitArr &a);

    void Set(unsigned i, char value);
    char Get(unsigned i);
    void PushBack(int value);
    size_t Len();
    void FromLongNum(int *long_num, size_t len, unsigned base);
    void RecountDigits();
    void RevertBits();
 
    ~BitArr();

private:
    char *arr;
    size_t arr_size;
    size_t len;
    unsigned last_used;

    void Erase();
    void Resize(size_t size);
    static char *strrev(char *str);
};

typedef BitArr bitarr;
#endif // BITARR_H_SENTRY
