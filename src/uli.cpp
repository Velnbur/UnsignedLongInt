#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <time.h>

#include "uli.h"

#define DEFAULT_ARR_SIZE 64

ULI::ULI()
    :base(2)
{
    arr = new BitArr(DEFAULT_ARR_SIZE);
}

ULI::~ULI()
{
    if (arr)
        delete arr;
}

ULI::ULI(unsigned int _base)
    : base(_base)
{
    arr = new BitArr(DEFAULT_ARR_SIZE);
}

ULI::ULI(unsigned int num, unsigned int base)
    : base(base)
{
    arr = new BitArr(DEFAULT_ARR_SIZE);
    do {
        arr->PushBack(num % 2);
        num >>= 1;
    } while (num);
}

ULI::ULI(const ULI &a)
{
    arr = new BitArr(DEFAULT_ARR_SIZE);
    *arr = *(a.arr);
    base = a.base;
}

ULI::ULI(const char *str, size_t _len, unsigned int _base)
    : base(_base)
{
    arr = new BitArr(DEFAULT_ARR_SIZE);

    for (; *(str) == '0'; ++str)
        --_len;

    this->ParseString(str, _len);
}

int ULI::len_from_digits(unsigned int digits, unsigned int base)
{
    int count = 0;
    do {
        ++count;
        base >>= 1;
    } while (base);
    return digits / count + 1;
}

char *ULI::strrev(char *str)
{
    if (!str || !*str)
        return str;

    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}

char *ULI::ToString(char *str, size_t _len) const
{
    int len = arr->Len();
    int tmp_len = len_from_digits(len, base) + 1;
    char *result = new char[tmp_len];
    for (int i = 0; i < tmp_len; ++i)
        result[i] = 0;
    int used = 1;

    for (int i = len - 1; i >= 0; --i) {
        for (int j = used - 1; j >= 0; --j) {
            result[j] *= 2;
            if (result[j] >= base) {
                if (used <= j + 1)
                    ++used;
                result[j + 1] += result[j] / base;
                result[j] %= base;
            }
        }
        result[0] += arr->Get(i);
    }

    for (int j = 0; j < used; ++j) {
        if (result[j] < 10)
            result[j] += '0';
        else
            result[j] += 'A' - 10;
    }

    result[used] = '\0';
    ULI::strrev(result);
    return result;
}

bool ULI::IsEven() const
{
    return !(arr->Get(0));
}

void ULI::ParseString(const char *str, size_t _len)
{
    int *nums = new int[_len];

    if (base <= 10)
        for (unsigned i = 0; i < _len; ++i) {
            if (str[i] <= ('0' + base - 1) && str[i] >= '0')
                nums[i] = str[i] - '0';
            else
                throw "Invalid string";
        }
    else
        for (unsigned i = 0; i < _len; ++i) {
            if (str[i] <= '9' && str[i] >= '0')
                nums[i] = str[i] - '0';
            else if (str[i] <= ('A' + base - 11) && str[i] >= 'A')
                nums[i] = str[i] - 'A' + 10;
            else if (str[i] <= ('a' + base - 11) && str[i] >= 'a')
                nums[i] = str[i] - 'A' + 10;
            else
                throw "Invalid string";
        }
    arr->FromLongNum(nums, _len, base);
    delete[] nums;
}

ULI ULI::operator+(const ULI &b) const
{
    int cf = 0;
    int max = arr->Len() > b.arr->Len() ? arr->Len() : b.arr->Len();
    ULI result(base);

    for (int i = 0; i < max || cf != 0; ++i) {
        int tmp = arr->Get(i) + b.arr->Get(i) + cf;
        if (2 <= tmp) {
            result.arr->PushBack(tmp - 2);
            cf = 1;
        } else {
            result.arr->PushBack(tmp);
            cf = 0;
        }
    }
    result.arr->RecountDigits();
    return result;
}

ULI ULI::operator+(unsigned int num) const
{
    return (*this) + ULI(num, base);
}

ULI ULI::operator-(const ULI &b) const
{
    if (b >= *this)
        return ULI(0, base);

    int cf = 0;
    int max = arr->Len();
    ULI result(base);

    for (int i = 0; i < max || cf != 0; ++i) {
        int tmp = b.arr->Get(i) + cf;
        if (arr->Get(i) < tmp) {
            result.arr->PushBack(2 + arr->Get(i) - tmp);
            cf = 1;
        } else {
            result.arr->PushBack(arr->Get(i) - tmp);
            cf = 0;
        }
    }
    result.arr->RecountDigits();
    return result;
}

ULI ULI::operator-(unsigned int num) const
{
    return (*this) - ULI(num, base);
}

ULI ULI::operator*(const ULI &another) const
{
    if(another.arr->Len() > 10 &&
        arr->Len() > 10)
    {
        return Karatsuba(another);
    }

    ULI result(base);
    const ULI *tmp1, *tmp2;

    if (*this > another) {
        tmp1 = this;
        tmp2 = &another;
    } else {
        tmp1 = &another;
        tmp2 = this;
    }
    ULI a = *tmp1, b = *tmp2;

    while (b > 0) {
        if (b.IsEven()) {
            a = a << 1;
            b = b >> 1;
        } else {;
            b = b - 1;
            result = result + a;
        }
    }
    return result;
}

ULI ULI::operator*(unsigned int num) const
{
    return (*this) * ULI(num, base);
}

ULI ULI::operator/(const ULI &b) const
{
    // div = a / b
    ULI div(base);
    ULI mod(base);
    DivAndMod(b, div, mod);
    return div;
}

ULI ULI::operator%(const ULI &b) const
{
    // mod = a % b
    ULI div(base);
    ULI mod(base);
    DivAndMod(b, div, mod);
    return mod;
}

ULI ULI::operator>>(unsigned int bits) const
{
    if (bits > arr->Len())
        return ULI(0, base);

    ULI result(base);
    int len = arr->Len();

    for (int i = bits; i < len; ++i)
        result.arr->PushBack(arr->Get(i));

    return result;
}

ULI ULI::operator<<(unsigned int bits) const
{
    ULI result(base);

    unsigned len = arr->Len();

    for (unsigned i = 0; i < len + bits; ++i)
        result.arr->PushBack(i < bits ? 0 : arr->Get(i - bits));

    return result;
}

ULI &ULI::operator=(const ULI &b)
{
    if(this == &b)
        return (*this);
    *arr = *(b.arr);
    base = b.base;
    return *this;
}

bool ULI::operator>(const ULI &b) const
{
    if (arr->Len() != b.arr->Len())
        return arr->Len() > b.arr->Len();

    for (int i = arr->Len() - 1; i >= 0; --i)
    {
        if (arr->Get(i) > b.arr->Get(i))
            return true;
        else if (arr->Get(i) < b.arr->Get(i))
            return false;
    }
    return false;
}

bool ULI::operator<(const ULI &b) const
{
    return !(*this >= b);
}

bool ULI::operator<(unsigned num) const
{
    return !(*this >= ULI(num, base));
}

bool ULI::operator>(unsigned num) const
{
    return *this > ULI(num, 10);
}

bool ULI::operator>=(const ULI &b) const
{
    if (arr->Len() != b.arr->Len())
        return arr->Len() > b.arr->Len();

    for (int i = arr->Len() - 1; i >= 0; --i)
    {
        if (arr->Get(i) > b.arr->Get(i))
            return true;
        else if (arr->Get(i) < b.arr->Get(i))
            return false;
    }
    return true;
} 

bool ULI::operator<=(const ULI &b) const
{
    if (arr->Len() != b.arr->Len())
        return arr->Len() < b.arr->Len();

    for (int i = arr->Len() - 1; i >= 0; --i)
    {
        if (arr->Get(i) < b.arr->Get(i))
            return true;
        else if (arr->Get(i) > b.arr->Get(i))
            return false;
    }
    return true;
} 

bool ULI::operator<=(unsigned int num) const
{
    return (*this) <= ULI(num, base);
}

bool ULI::operator==(const ULI &b) const
{
    if (arr->Len() != b.arr->Len())
        return false;

    for (int i = arr->Len() - 1; i >= 0; --i)
    {
        if (arr->Get(i) != b.arr->Get(i))
            return false;
    }
    return true;
}

bool ULI::operator==(unsigned num) const
{
    return *this == ULI(num, base);
}

bool ULI::operator!=(unsigned num) const
{
    return !(*this == ULI(num, base));
}

bool ULI::operator!=(const ULI &b) const
{
    return !(*this == b);
}

void ULI::DivAndMod(const ULI &b, ULI &div, ULI &mod) const
{
    // div = a / b
    // mod = a % b
    mod = *this;
    int sh = arr->Len() - b.arr->Len();

    while (mod >= b)
    {
        ULI tmp = mod >> sh;

        while (b > tmp)
        {
            --sh;
            tmp = mod >> sh;
            div.arr->PushBack(0);
        }
        mod = mod - (b << sh);
        div.arr->PushBack(1);

        if (sh > 0 && b > mod)
            for (; sh > 0; --sh)
                div.arr->PushBack(0);
        --sh;
    }
    div.arr->RevertBits();
}

ULI ULI::Karatsuba(const ULI &b) const
{
    // c = a.Karatsuba(b);
    size_t max = arr->Len() > b.arr->Len()
                     ? arr->Len()
                     : b.arr->Len();

    if (max <= 4)
        return (*this) * b;
    if (max & 1)
        ++max;

    ULI a_l(base), a_r(base);
    SliceByHalfs(a_l, a_r, max);
    ULI b_l(base), b_r(base);
    b.SliceByHalfs(b_l, b_r, max);
    ULI tmp1 = a_l.Karatsuba(b_l);
    ULI tmp2 = a_r.Karatsuba(b_r);
    ULI tmp3 = (a_r + a_l).Karatsuba(b_l + b_r);

    return (tmp1 << max) + ((tmp3 - tmp2 - tmp1) << (max / 2)) + tmp2;
}

void ULI::SliceByHalfs(ULI &a_l, ULI &a_r, unsigned n) const
{
    unsigned len = arr->Len();
    for (unsigned i = 0; i < n; ++i)
    {
        int value = i >= len ? 0 : arr->Get(i);
        if (i < n / 2)
            a_r.arr->PushBack(value);
        else
            a_l.arr->PushBack(value);
    }
    a_l.arr->RecountDigits();
    a_r.arr->RecountDigits();
}

ULI ULI::power_mod(const ULI &a, const ULI &power, const ULI &mod)
{
    ULI result(1, a.base);
    size_t len = power.arr->Len()+1;
    ULI *array = new ULI[len];

    array[0] = a;
    for(unsigned i = 1; i < len; ++i)
        array[i] = (array[i-1] * array[i-1]) % mod;

    for(unsigned i = 0; i < len; ++i)
        if(power.arr->Get(i))
            result = result * array[i];

    delete [] array;
    return result % mod;
}

// ULI ULI::rand(unsigned base)
// {
//     ULI result(time(0), base);
//     const int a = 17;
//     const int c = 19;
//     result = result * a + c;
//     return result;
//}

enum PRIMARY_METHODS {
    LEMENA = 1,
    MILLERA_RABINA = 2,
};

bool ULI::IsPrimary(unsigned int method) const
{
    if(method > 4 || !method)
        throw "There is no such method";
    
    switch((PRIMARY_METHODS)method) {
        case LEMENA:
            return Lemena();
        case MILLERA_RABINA:
            return RabinMiller();
    }
    return false;
}

bool ULI::Lemena() const
{
    const unsigned T = 10;

    if((*this) != 2 && IsEven())
        return false;

    srand((unsigned)time(NULL));

    for(unsigned i = 0; i < T; ++i) {
        ULI a = ULI(rand(), base) % ((*this)-1) + 2;
        ULI power = ((*this)-1) >> 1;

        ULI tmp = ULI::power_mod(a, power, (*this));

        if(tmp != 1 && tmp != (*this)-1)
            return false;
        else if(tmp == 1 || tmp == ((*this)-1)%(*this))
            return true;
    }

    return true;
}

bool ULI::RabinMiller() const
{
    if(*this < 3)
        return true;
    if(IsEven())
        return false;

    ULI r = *this;
    ULI count(0, base);
    srand((unsigned)time(NULL)); // TODO

    for(;;) {
        r = r >> 1;
        if(!r.IsEven())
            break;
        count = count + 1;
    }

    const unsigned t = 8;
    for(unsigned i = 0; i <= t; ++i) {
        ULI a = ULI(rand(), base) % ((*this)-1) + 2; // TODO
        ULI y = power_mod(a, r, (*this));

        if(y != 1 && y != (*this)-1) {
            for(unsigned j = 0; j <= count-1; ++j) {
                y = power_mod(y, ULI(2, base), (*this));
                if(y == 1)
                    return false;
            }
            if(y != (*this)-1)
                return false;
        }
    }
    return true;
}

bool operator<=(unsigned num, const ULI &b)
{
    return !(b > num);
}