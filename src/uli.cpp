#include <cstdio>
#include <cstdlib>
#include <strings.h>
#include <cstring>
#include <ctime>

#include "uli.h"

ULI::ULI() : base(2) {}

ULI::ULI(unsigned _base)
    : base(_base) {}

ULI::ULI(unsigned int num, unsigned base)
    : base(base)
{
    do
    {
        arr.PushBack(num % 2);
        num >>= 1;
    } while (num);
}

ULI::ULI(const ULI &a)
{
    arr = a.arr;
    base = a.base;
}

ULI::ULI(const char *str, unsigned _base, size_t _len)
    : base(_base)
{
    if(_len == 0) 
        _len = strlen(str);

    for (; *(str) == '0'; ++str)
        --_len;

    ParseString(str, _len);
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

void ULI::Print() const
{
    size_t len = arr.Len();
/*     for(unsigned i = len; i > 0; --i) {
        putchar(arr.Get(i-1) + '0');
    }
    putchar('\n'); */
    unsigned tmp_len = len;
    unsigned result[tmp_len];
    for (unsigned i = 0; i < tmp_len; ++i)
        result[i] = 0;
    size_t used = 1;

    for (size_t i = len; i > 0; --i)
    {
        // multiply every digit by 2
        for (size_t j = used; j > 0; --j)
        {
            result[j-1] *= 2;
        }
        result[0] += arr.Get(i - 1);
        // if digit > base, mod it by base
        // and raise next digit
        for (size_t j = 0; j < used; ++j)
        {
            if (result[j] >= base)
            {
                if (used <= j+1 && used < tmp_len)
                    ++used;
                result[j + 1] += result[j] / base;
                result[j] %= base;
            }
        }
    }

    // make array of digits to array of chars
    for (size_t j = used; j > 0; --j)
        putchar(result[j-1]+'0');

}

bool ULI::IsEven() const
{
    return !(arr.Get(0));
}

void ULI::ParseString(const char *str, size_t _len)
{
    unsigned nums[_len];

    if (base <= 10)
        for (unsigned i = 0; i < _len; ++i)
        {
            if ((unsigned)str[i] <= ('0' + base - 1) && str[i] >= '0')
                nums[i] = str[i] - '0';
            else
                throw "Invalid string";
        }
    else
        for (unsigned i = 0; i < _len; ++i)
        {
            if (str[i] <= '9' && str[i] >= '0')
                nums[i] = str[i] - '0';
            else if ((unsigned)str[i] <= ('A' + base - 11) && str[i] >= 'A')
                nums[i] = str[i] - 'A' + 10;
            else if ((unsigned)str[i] <= ('a' + base - 11) && str[i] >= 'a')
                nums[i] = str[i] - 'a' + 10;
            else
                throw "Invalid string";
        }

    arr.FromLongNum(nums, _len, base);
}

ULI ULI::operator+(const ULI &b) const
{
    int cf = 0;
    size_t max = arr.Len() > b.arr.Len() ? arr.Len() : b.arr.Len();
    ULI result(base);

    for (size_t i = 0; i < max || cf != 0; ++i)
    {
        int tmp = arr.Get(i) + b.arr.Get(i) + cf;
        if (2 <= tmp)
        {
            result.arr.PushBack(tmp - 2);
            cf = 1;
        }
        else
        {
            result.arr.PushBack(tmp);
            cf = 0;
        }
    }
    result.arr.RecountDigits();
    return result;
}

ULI ULI::operator+(unsigned int num) const
{
    return (*this) + ULI(num, base);
}

ULI ULI::operator-(const ULI &b) const
{
    if (b >= (*this))
        return ULI(0u, base);

    int cf = 0;
    size_t max = arr.Len();
    ULI result(base);

    for (size_t i = 0; i < max || cf != 0; ++i)
    {
        int tmp = b.arr.Get(i) + cf;
        if (arr.Get(i) < tmp)
        {
            result.arr.PushBack(2 + arr.Get(i) - tmp);
            cf = 1;
        }
        else
        {
            result.arr.PushBack(arr.Get(i) - tmp);
            cf = 0;
        }
    }
    result.arr.RecountDigits();
    return result;
}

ULI ULI::operator-(unsigned int num) const
{
    return (*this) - ULI(num, base);
}

ULI ULI::operator*(const ULI &_b) const
{
    if (_b.arr.Len() >= 40 &&
        arr.Len() >= 40)
    {
        return Karatsuba(_b);
    }

    ULI result(base);
    ULI a = *this;
    ULI b = _b;

    while (b > 0)
    {
        if (b.IsEven())
        {
            a = a << 1;
            b = b >> 1;
        }
        else
        {
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
    if (b > (*this))
        return ULI(0u, base);
    if (b == (*this))
        return ULI(1u, base);
    ULI div(base);
    ULI mod = *this;
    DivAndMod(b, div, mod);
    return div;
}

ULI ULI::operator%(const ULI &b) const
{
    // mod = a % b
    if (b > (*this))
        return (*this);
    if (b == (*this))
        return ULI(0u, base);
    ULI div(base);
    ULI mod = *this;
    DivAndMod(b, div, mod);
    return mod;
}

ULI ULI::operator>>(unsigned int bits) const
{
    if (bits == 0)
        return (*this);
    if (bits >= arr.Len())
        return ULI(0u, base);

    ULI result(base);
    size_t len = arr.Len();

    for (unsigned i = bits; i < len; ++i)
        result.arr.PushBack(arr.Get(i));

    return result;
}

ULI ULI::operator<<(unsigned int bits) const
{
    if (bits == 0)
        return (*this);
    ULI result(base);

    unsigned len = arr.Len();

    for (unsigned i = 0; i < len + bits; ++i)
        result.arr.PushBack(i < bits ? 0 : arr.Get(i - bits));

    return result;
}

ULI &ULI::operator=(const ULI &b)
{
    if (this == &b)
        return (*this);
    arr = b.arr;
    base = b.base;
    return *this;
}

bool ULI::operator>(const ULI &b) const
{
    if (arr.Len() != b.arr.Len())
        return arr.Len() > b.arr.Len();

    for (int i = arr.Len() - 1; i >= 0; --i)
    {
        if (arr.Get(i) > b.arr.Get(i))
            return true;
        else if (arr.Get(i) < b.arr.Get(i))
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
    if (arr.Len() != b.arr.Len())
        return arr.Len() > b.arr.Len();

    for (int i = arr.Len() - 1; i >= 0; --i)
    {
        if (arr.Get(i) > b.arr.Get(i))
            return true;
        else if (arr.Get(i) < b.arr.Get(i))
            return false;
    }
    return true;
}

bool ULI::operator<=(const ULI &b) const
{
    if (arr.Len() != b.arr.Len())
        return arr.Len() < b.arr.Len();

    for (int i = arr.Len() - 1; i >= 0; --i)
    {
        if (arr.Get(i) < b.arr.Get(i))
            return true;
        else if (arr.Get(i) > b.arr.Get(i))
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
    if (arr.Len() != b.arr.Len())
        return false;

    for (int i = arr.Len() - 1; i >= 0; --i)
    {
        if (arr.Get(i) != b.arr.Get(i))
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
    size_t sh = arr.Len() - b.arr.Len();
    while (mod >= b)
    {
        ULI tmp = mod >> sh;

        while (b > tmp)
        {
            if(sh == 0)
                throw "Shift between error";
            --sh;
            tmp = mod >> sh;
            div.arr.PushBack(0);
        }

        mod = mod - (b << sh);
        div.arr.PushBack(1);

        if (sh > 0 && b > mod)
            for (long long int i = sh; i > 0; --i)
                div.arr.PushBack(0);

        --sh;
    }
    div.arr.RevertBits();
}

ULI ULI::Karatsuba(const ULI &b) const
{
    // c = a.Karatsuba(b);
    size_t max = arr.Len() > b.arr.Len()
                     ? arr.Len()
                     : b.arr.Len();

    if (max <= 16)
        return (*this) * b;
    if (max & 1) // if is odd
        ++max;

    ULI a_l(base), a_r(base);
    SliceByHalfs(a_l, a_r, max);
    ULI b_l(base), b_r(base);
    b.SliceByHalfs(b_l, b_r, max);
    ULI tmp1 = a_l.Karatsuba(b_l);
    ULI tmp2 = a_r.Karatsuba(b_r);
    ULI tmp3 = (a_r + a_l).Karatsuba(b_l + b_r);
/*     puts(a_l.ToString());
    puts(a_r.ToString());
    fflush(stdout); */
    return (tmp1 << max) + ((tmp3 - tmp2 - tmp1) << (max / 2)) + tmp2;
}

void ULI::SliceByHalfs(ULI &a_l, ULI &a_r, unsigned n) const
{
    unsigned len = arr.Len();
    for (unsigned i = 0; i < n; ++i)
    {
        int value = i >= len ? 0 : arr.Get(i);
        if (i < n / 2)
            a_r.arr.PushBack(value);
        else
            a_l.arr.PushBack(value);
    }
    a_l.arr.RecountDigits();
    a_r.arr.RecountDigits();
}

// ULI ULI::ToomCook(const ULI &b) const
// {
//     ULI result(0, base);
//     int len = b.arr->Len();
//     if (arr->Len() > b.arr->Len()){
//         len = arr->Len();
//     }
//     if (len == 1){
//         return u * v;
//     }
//     ++len;
//     len = static_cast<int>pow(3, len); // повертає 3^k, size <= 3^k

//     ULI v1, v2, v3, u1, u2, u3;
//     v1 = b.mod(len/3);
//     u1 = mod(len/3);
//     v2 = (v >> len/3).mod(len/3);
//     u2 = (u >> len/3).mod(len/3);
//     v3 = (v >> 2 * (len/3));
//     u3 = (u >> 2 * (len/3));

//     ULI arrayU[5] = {};
//     ULI arrayV[5] = {};
//     ULI arrayW[5] = {};

//     for (int i = 0; i < 5; i++){
//         arrayU[i] = u3 * i * i + u2 * i + u1;
//         arrayV[i] = v3 * i * i + v2 * i + v1;
//         arrayW[i] = ToomCook(arrayU[i], arrayV[i]);
//     }

//     ULI temp[5] = {};
//     temp[0] = arrayW[0];

//     for (int i = 1; i < 5; i++){
//         for (int j = 0; j < 5 - i; j++){
//             arrayW[j] = (arrayW[j + 1] - arrayW[j]) / i;
//         }
//         temp[i] = arrayW[0];
//     }

//     ULI W[5] = {};
//     // реалізувати схему 18
//     result = result + W[0] + W[1] << len/3 + W[2] << 2 * len/3 + W[3] << 3 * len/3 + W[4] << 4 * len/3;
//     return result;
// }

ULI ULI::power_mod(const ULI &a, const ULI &power, const ULI &mod)
{
    ULI result(1, a.base);
    size_t len = power.arr.Len();
    ULI array[len];

    array[0] = a;
    for (unsigned i = 1; i < len; ++i) {
        array[i] = (array[i - 1] * array[i - 1]) % mod;
    }

    for (unsigned i = 0; i < len; ++i) {
        if (power.arr.Get(i))
            result = (result * array[i]) % mod;
    }
    return result;
}

ULI ULI::random(const ULI &from, const ULI &to, const ULI &seed)
{
    ULI sum(0u, 2u);
    ULI x = seed - 1;
    const unsigned a = 1234567;
    const unsigned c = 6789045;

    for (unsigned i = 0; i < 12; ++i)
    {
        sum = sum + x;
        x = (x * a + c) % to;
    }

    return from + (sum - 6) % (to - from);
}

enum PRIMARY_METHODS
{
    MILLERA_RABINA = 1,
    SOLOVEY_SHTRASSEN = 2,
};

bool ULI::IsPrimary(unsigned int method) const
{
    if (method > 4 || !method)
        throw "There is no such method";

    switch ((PRIMARY_METHODS)method)
    {
    case MILLERA_RABINA:
        return RabinMiller();
    case SOLOVEY_SHTRASSEN:
        return SoloveyShtrassen();
    }
    return false;
}

bool ULI::lemera_test(unsigned num)
{
    ULI s(4, 2);
    ULI M = (ULI(1, 2) << num) - 1;
    for (unsigned i = 0; i < num - 2; ++i)
        s = ((s * s) - 2) % M;

    if (s == 0)
        return true;
    else
        return false;
}

ULI ULI::gcd(const ULI &_a, const ULI &_b)
{
    if (_a == 0)
        return _b;

    ULI a = _a;
    ULI b = _b;
    while (b != 0)
    {
        ULI r;
        if (a > b)
            r = a % b;
        else
            r = b % a;
        a = b;
        b = r;
    }
    return a;
}

bool ULI::RabinMiller() const
{
    if (*this <= 3)
        return true;
    if (IsEven())
        return false;

    ULI m = (*this - 1) >> 1;
    unsigned long long int t = 1;

    while (m.IsEven())
    {
        m = m >> 1;
        ++t;
    }

    const unsigned k = 8;
    ULI a(time(NULL), base);
    for (unsigned i = 0; i <= k; ++i)
    {
        a = ULI::random(ULI(2, base), (*this)-2, a);
        ULI u = ULI::power_mod(a, m, (*this));

        if (u != (*this)-1 && u != 1)
        {
            for (unsigned j = 1; j < t && u != (*this)-1; ++j)
            {
                u = (u * u) % (*this);
                if (u == 1)
                    return false;
            }
            if(u != (*this)-1)
                return false;
        }
    }
    return true;
}

bool ULI::SoloveyShtrassen() const
{
    if ((*this) < 3)
        return true;
    if (IsEven())
        return false;

    unsigned k = 8;
    ULI a(time(NULL), base);
    for (unsigned i = 0; i <= k; ++i)
    {
        a = ULI::random(ULI(2, base), (*this), a);
        if (ULI::gcd(a, (*this)) > 1)
            return false;

        ULI tmp = ULI::power_mod(a, ((*this) - 1) >> 1, (*this));
        int j = ULI::jac_sym(a, (*this));
        //printf("%s, %s, %d\n", a.ToString(), this->ToString(), j);

        if (j == -1)
        {
            if (tmp != (*this) - 1)
                return false;
        }
        else
        {
            if (tmp != j)
                return false;
        }
    }
    return true;
}

int ULI::jac_sym(const ULI &a, const ULI &n)
{
    if (a == 0)
        return 0;
    if (a == 1)
        return 1;

    ULI a1 = a;
    unsigned e = 0;
    while (a1.IsEven())
    {
        a1 = a1 >> 1;
        ++e;
    }
    ULI tmp(a.base);
    int s = 1;
    if (e % 2 == 0)
        s = 1;
    else
    {
        tmp = n % ULI(8, n.base);
        if (tmp == 1 || tmp == 7)
            s = 1;
        else if (tmp == 3 || tmp == 5)
            s = -1;
    }
    if (n % ULI(4, a.base) == 3 && a1 % ULI(4, a.base) == 3)
        s = -s;

    ULI n1 = n % a1;
    //printf("%s, %s, %d\n", n1.ToString(), a1.ToString(), s);
    if (a1 == 1)
        return s;
    else
        return s * ULI::jac_sym(n1, a1);
}

bool operator<=(unsigned num, const ULI &b)
{
    return ULI(num, b.base) <= b;
}

enum MULTIPLY
{
    KARATSUBA = 0,
};

ULI ULI::FastMul(const ULI &b, int method) const
{
    switch ((MULTIPLY)method)
    {
    case KARATSUBA:
        return Karatsuba(b);
    }
    throw "There is no such fast mul method";
}
