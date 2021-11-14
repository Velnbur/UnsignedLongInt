#ifndef BITARR_H_SENTRY
#define BITARR_H_SENTRY

class BitArr {
public:
    explicit BitArr(size_t len);
    BitArr(const BitArr &a);

    BitArr &operator=(const BitArr &a);

    void Set(unsigned i, char value);
    char Get(unsigned i);
    void PushBack(int value);
    size_t Len() const;
    void FromLongNum(unsigned *long_num, size_t _len, unsigned base);
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
    static bool is_empty(const unsigned *a, size_t len);
};

typedef BitArr bitarr;
#endif // BITARR_H_SENTRY
