#include <stdio.h>
#include <time.h>

#include "uli.h"

// #define GREEN   "\033[32m"
// #define RED     "\033[31m"
// #define RESET   "\033[0m"

void test_base_conv()
{
    puts("\nTEST BASE CONV");
    ULI uli("124", 3, 7);
    ULI uli2("123", 3, 7);
    const char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete[] str;

    str = uli2.ToString();
    printf("uli2 = %s\n", str);
    delete[] str;
}

void test_greater()
{
    puts("\nTEST GREATER");
    ULI uli(123, 10);
    ULI uli2("6", 1, 10);
    const char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete[] str;

    str = uli2.ToString();
    printf("uli2 = %s\n", str);
    delete[] str;

    printf("uli > uli2 = %d\n", uli > uli2);
}

void test_greater_num()
{
    puts("\nTEST GREATER BETWEEN NUM AND ULI");
    ULI uli(123, 10);
    const char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete[] str;

    printf("uli > 13 = %d\n", uli > 13);
}

void test_gr_or_eq()
{
    puts("\nTEST GREATER OR EQUAL");
    ULI uli(123, 10);
    ULI uli2("123", 3, 10);
    const char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete[] str;

    str = uli2.ToString();
    printf("uli2 = %s\n", str);
    delete[] str;

    printf("uli >= uli2 = %d\n", uli >= uli2);
}

void test_add()
{
    puts("\nTEST ADD");
    ULI uli(123123, 10);
    ULI uli2("12123", 5, 10);
    const char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete[] str;

    str = uli2.ToString();
    printf("uli2 = %s\n", str);
    delete[] str;

    printf("uli + uli2 = %s\n", (uli + uli2).ToString());

    puts("\nTEST ADD NUM");
    ULI uli0(123, 10);

    str = uli0.ToString();
    printf("uli = %s\n", str);
    delete[] str;

    printf("uli + 2 = %s\n", (uli0 + 2).ToString());
}

void test_minus()
{
    puts("\nTEST SUB");
    ULI uli(123123, 10);
    ULI uli2("12123", 5, 10);
    const char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete[] str;

    str = uli2.ToString();
    printf("uli2 = %s\n", str);
    delete[] str;


    printf("uli - uli2 = %s\n", (uli - uli2).ToString());
}

void test_bits_right()
{
    puts("\nTEST LEFT SHIFT");
    ULI uli(7, 10);
    const char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete[] str;

    printf("uli >> 1 = %s\n", (uli >> 1).ToString());
}

void test_bits_left()
{
    puts("\nTEST MUL");
    ULI uli("666", 3, 7);
    ULI uli2("3456", 4, 7);
    const char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete[] str;

    str = uli2.ToString();
    printf("uli2 = %s\n", str);
    delete[] str;

    printf("uli * uli2 = %s\n", (uli * uli2).ToString());
}

void test_mod()
{
    puts("\nTEST MOD");
    ULI uli(324, 10);
    ULI uli2("32", 2, 10);
    const char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete[] str;

    str = uli2.ToString();
    printf("uli2 = %s\n", str);
    delete[] str;

    printf("uli %% uli2 = %s\n", (uli % uli2).ToString());
}

void test_div()
{
    puts("\nTEST DIVISION");
    ULI uli(12, 10);
    ULI uli2(4, 10);
    const char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete[] str;

    str = uli2.ToString();
    printf("uli2 = %s\n", str);
    delete[] str;

    printf("uli / uli2 = %s\n", (uli / uli2).ToString());
}

void test_karatsuba()
{
    puts("\nTEST KARATSUBA");
    ULI uli("6334234245435245", 16, 10);
    ULI uli1("122435454545454", 15, 10);
    char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete [] str;

    str = uli1.ToString();
    printf("uli1 = %s\n", str);
    delete [] str;

    str = (uli.FastMul(uli1)).ToString();
    printf("uli.Karatsuba(uli1) = %s\n", str);
}

void test_power_mod()
{
    puts("\nTEST POWER MOD");

    ULI uli("3", 1, 10); 
    ULI power("90", 2, 10);
    ULI mod("5", 1, 10);
    char *str;

    str = uli.ToString();
    printf("uli = %s\n", str);
    delete [] str;

    str = power.ToString();
    printf("power = %s\n", str);
    delete [] str;

    str = mod.ToString();
    printf("mod = %s\n", str);
    delete [] str;

    str = ULI::power_mod(uli, power, mod).ToString();
    printf("uli^power %% mod = %s\n", str);
}

void test_rand()
{
    puts("\nTEST RANDOM");
    ULI from(2, 10);
    ULI to(10101, 10);
    ULI x(time(NULL), 10);
    char *str;

    for(int i = 0; i < 12; ++i) {
        x = ULI::random(from, to, x);
        str = x.ToString();
        printf("%s\n", str);
        delete [] str;
    }
}

void test_lemera()
{
    puts("\nTEST LEMERA");

    unsigned num = 13;

    printf("num = %u\n", num);
    printf("num is primary = %d\n", ULI::lemera_test(num));
}

void test_miller_rabina()
{
    puts("\nTEST MILLERA RABINA");

    ULI uli("31", 2, 10);
    char *string;

    string = uli.ToString();
    printf("uli = %s\n", string);
    delete [] string;
    printf("uli is primary = %d\n", uli.IsPrimary(1));
}

void test_jac_sym()
{
    puts("\nTEST JAC SYM");

    ULI uli1("51618", 5, 10);
    ULI uli2("100019", 6, 10);
    char *str;

    str = uli1.ToString();
    printf("uli1 = %s\n", str);
    delete [] str;

    str = uli2.ToString();
    printf("uli2 = %s\n", str);
    delete [] str;

    printf("jacobi symbol = %d\n", ULI::jac_sym(uli1, uli2));
}

void test_soloveya_shtrassena()
{
    puts("\nTEST SOLOVEYA SHTRASSENA");

    ULI uli("100003", 6, 10);
    char *string;

    string = uli.ToString();
    printf("uli = %s\n", string);
    delete [] string;
    printf("uli is primary = %d\n", uli.IsPrimary(2));
}

int main()
{
    try {
        test_base_conv();
        test_greater();
        test_greater_num();
        test_add();
        test_minus();
        test_gr_or_eq();
        test_bits_right();
        test_bits_left();
        //test_mul();
        test_mod();
        test_div();
        test_karatsuba();
        test_power_mod();
        test_rand();
        test_lemera();
        test_miller_rabina();
        test_jac_sym();
        test_soloveya_shtrassena();
    } catch (const char *mess) {
        printf("%s\n", mess);
        return 1;
    }

    return 0;   
}
