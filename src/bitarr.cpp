#include <cstring>
#include <cstdio>

#include "bitarr.h"


#define DEFAULT_ARR_SIZE 64

const unsigned char BIT_0 = 1;
const unsigned char BIT_1 = 2;
const unsigned char BIT_2 = 4;
const unsigned char BIT_3 = 8;
const unsigned char BIT_4 = 16;
const unsigned char BIT_5 = 32;
const unsigned char BIT_6 = 64;
const unsigned char BIT_7 = 128;

BitArr::BitArr(size_t _len)
    : len(_len), last_used(0)
{
    if (_len % 8)
        arr_size = len / 8 + 1;
    else
        arr_size = len / 8;
    arr = new char[arr_size];
    Erase();
}

BitArr::BitArr()
    : len(DEFAULT_ARR_SIZE), last_used(0)
{
    if (len % 8)
        arr_size = len / 8 + 1;
    else
        arr_size = len / 8;
    arr = new char[arr_size];
    Erase();
}

BitArr::~BitArr()
{
    if(arr)
        delete [] arr;
}

BitArr::BitArr(const BitArr &a)
{
    arr_size = a.arr_size;
    len = a.len;
    last_used = a.last_used;

    arr = new char[arr_size];
    for (unsigned i = 0; i < arr_size; ++i)
        arr[i] = a.arr[i];
}

BitArr &BitArr::operator=(const BitArr &a)
{
    if(this == &a)
        return *this;
    if(arr)
        delete [] arr;
    arr_size = a.arr_size;
    len = a.len;
    last_used = a.last_used;

    arr = new char[arr_size];
    for (size_t i = 0; i < arr_size; ++i)
        arr[i] = a.arr[i];

    return *this;
}

char BitArr::Get(unsigned i) const
{
    if(i >= Len())
        return 0;
    unsigned bit = i % 8;
    char tmp = arr[i / 8];
    int result = 0;
    switch (bit) {
        case 0:
            result = tmp & BIT_0;
            break;
        case 1:
            result = tmp & BIT_1;
            break;
        case 2:
            result = tmp & BIT_2;
            break;
        case 3:
            result = tmp & BIT_3;
            break;
        case 4:
            result = tmp & BIT_4;
            break;
        case 5:
            result = tmp & BIT_5;
            break;
        case 6:
            result = tmp & BIT_6;
            break;
        case 7:
            result = tmp & BIT_7;
        default:
            break;
    }
    if (result)
        return 1;
    else
        return 0;
}

void BitArr::Set(unsigned i, char value)
{
    unsigned bit = i % 8;
    if (i >= len)
        Resize(i / 8 + 1);

    if(i >= last_used)
        last_used = i+1;

    if (value)
        value = 255;
    else
        value = 0;
    switch (bit) {
        case 0:
            arr[i / 8] |= BIT_0 & value;
            break;
        case 1:
            arr[i / 8] |= BIT_1 & value;
            break;
        case 2:
            arr[i / 8] |= BIT_2 & value;
            break;
        case 3:
            arr[i / 8] |= BIT_3 & value;
            break;
        case 4:
            arr[i / 8] |= BIT_4 & value;
            break;
        case 5:
            arr[i / 8] |= BIT_5 & value;
            break;
        case 6:
            arr[i / 8] |= BIT_6 & value;
            break;
        case 7:
            arr[i / 8] |= BIT_7 & value;
            break;
        default:
            break;
    }
}

void BitArr::Resize(size_t _size)
{
    size_t new_size = arr_size;
    while (_size >= new_size)
        new_size *= 2;
    char *tmp = new char[new_size];

    for (size_t i = 0; i < new_size; ++i)
        tmp[i] = i < arr_size ? arr[i] : 0;

    delete [] arr;
    arr = tmp;
    arr_size = new_size;
    len = arr_size * 8;
}

size_t BitArr::Len() const
{
    return last_used;
}

void BitArr::PushBack(int value)
{
    Set(last_used, value);
}

bool BitArr::is_empty(const unsigned *a, size_t len)
{
    for (size_t i = 0; i < len; ++i)
        if (a[i] != 0)
            return false;
    return true;
}

void BitArr::FromLongNum(unsigned *long_num, size_t _len, unsigned base)
{
    Erase();

    size_t i = 0, cf = 0, t;
    while (!BitArr::is_empty(long_num, _len)) {
        while (i < _len) {
            t = long_num[i] + cf * base;
            long_num[i] = t / 2;
            cf = t % 2;
            i += 1;
        }
        i = 0;
        PushBack(cf);
        cf = 0;
    }
}

void BitArr::Erase()
{
    for (size_t i = 0; i < arr_size; ++i)
        arr[i] = 0; 
    last_used = 0;
}

void BitArr::RecountDigits()
{
    while(last_used && !Get(last_used-1))
        --last_used;
}

void BitArr::RevertBits()
{
    size_t _len = Len();
    char *tmp = new char[_len];
    for(size_t i = 0; i < _len; ++i)
        tmp[i] = Get(i);
    Erase();
    for(size_t i = _len; i > 0; --i)
        PushBack(tmp[i-1]);

    delete[] tmp;
}