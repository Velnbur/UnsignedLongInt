#include <stdio.h>
#include <time.h>
#include <string.h>

#include "uli.h"

// #define GREEN   "\033[32m"
// #define RED     "\033[31m"
// #define RESET   "\033[0m"

void test_base_conv()
{
    puts("\nTEST BASE CONV");
    ULI uli("124", 7);
    ULI uli2("123", 7);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("uli2 = ");
    uli2.Print();
    putchar('\n');
}

void test_greater()
{
    puts("\nTEST GREATER");
    ULI uli(123, 10);
    ULI uli2("6", 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("uli2 = ");
    uli2.Print();
    putchar('\n');

    printf("uli > uli2 = %d\n", uli > uli2);
}

void test_greater_num()
{
    puts("\nTEST GREATER BETWEEN NUM AND ULI");
    ULI uli(123, 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("uli > 13 = %d\n", uli > 13);
}

void test_gr_or_eq()
{
    puts("\nTEST GREATER OR EQUAL");
    ULI uli(123, 10);
    ULI uli2("123", 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("uli2 = ");
    uli2.Print();
    putchar('\n');

    printf("uli >= uli2 = %d\n", uli >= uli2);
}

void test_add()
{
    puts("\nTEST ADD");
    ULI uli(123123, 10);
    ULI uli2("12123", 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("uli2 = ");
    uli2.Print();
    putchar('\n');

    printf("uli + uli2 = ");
    (uli + uli2).Print();
    putchar('\n');

    puts("\nTEST ADD NUM");
    ULI uli0(123, 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("uli + 2 = ");
    (uli + 2).Print();
    putchar('\n');
}

void test_sub()
{
    puts("\nTEST SUB");
    ULI uli1("505069340036661361787556680197619398372", 10);
    ULI uli2("2153236456547547567587979799", 10);

    printf("uli1 = ");
    uli1.Print();
    putchar('\n');

    printf("uli2 = ");
    uli2.Print();
    putchar('\n');

    uli1 = uli1 - (uli2 << 37);
    printf("uli1 - uli2 = ");
    uli1.Print();
    putchar('\n');
}

void test_bits_right()
{
    puts("\nTEST RIGHT SHIFT");
    ULI uli(0u, 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("uli >> 1 = ");
    (uli >> 1).Print();
    putchar('\n');
}

void test_bits_left()
{
    puts("\nTEST LEFT SHIFT");
    ULI uli(7, 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("uli1 << 1 = ");
    (uli << 1).Print();
    putchar('\n');
}

void test_mul()
{
    puts("\nTEST MUL");
    ULI uli("666", 10);
    ULI uli2("3456", 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("uli2 = ");
    uli2.Print();
    putchar('\n');

    printf("uli  * uli2 = ");
    (uli * uli2).Print();
    putchar('\n');
}

void test_mod()
{
    puts("\nTEST MOD");
    ULI uli1("505069340036661361787556680197619398372", 10);
    ULI uli2("215323645654754756758797979", 10);
    
    uli1 = (uli1 * uli1);
    printf("uli1 = ");
    uli1.Print();
    putchar('\n');

    printf("uli2 = ");
    uli2.Print();
    putchar('\n');

    printf("uli1 %% uli2 = ");
    (uli1 % uli2).Print();
    putchar('\n');
}

void test_div()
{
    puts("\nTEST DIVISION");
    ULI uli(12, 10);
    ULI uli2(4, 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("uli2 = ");
    uli2.Print();
    putchar('\n');

    printf("uli / uli2 = ");
    (uli / uli2).Print();
    putchar('\n');
}

void test_karatsuba()
{
    puts("\nTEST KARATSUBA");
    ULI uli("1150417", 10);
    ULI uli1("517535188689292811822475", 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("uli1 = ");
    uli1.Print();
    putchar('\n');

    printf("uli.Karatsube(uli1) = ");
    uli.FastMul(uli1).Print();
    putchar('\n');
}

void test_power_mod()
{
    puts("\nTEST POWER MOD");

    ULI uli("289376487", 10); 
    ULI power("123456", 10);
    ULI mod("123456", 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');

    printf("power = ");
    power.Print();
    putchar('\n');

    printf("mod = ");
    mod.Print();
    putchar('\n');

    printf("uli^power mod mod = ");
    ULI::power_mod(uli, power, mod).Print();
    putchar('\n');
}

 void test_rand()
{
    puts("\nTEST RANDOM");
    ULI from(2, 10);
    ULI to(10101, 10);
    ULI x(time(NULL), 10);

    for(int i = 0; i < 12; ++i) {
        x = ULI::random(from, to, x);
        x.Print();
        putchar('\n');
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
    ULI uli("27634585789999", 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');
    printf("uli is prime = %d\n", uli.IsPrimary(1));
}

void test_jac_sym()
{
    puts("\nTEST JAC SYM");

    ULI uli1("51618", 10);
    ULI uli2("100019", 10);

    printf("uli1 = ");
    uli1.Print();
    putchar('\n');

    printf("uli2 = ");
    uli2.Print();
    putchar('\n');

    printf("jacobi symbol = %d\n", ULI::jac_sym(uli1, uli2));
}

void test_soloveya_shtrassena()
{
    puts("\nTEST SOLOVEYA SHTRASSENA");

    ULI uli("27634585789999", 10);

    printf("uli = ");
    uli.Print();
    putchar('\n');
    printf("uli is prime = %d\n", uli.IsPrimary(2));
} 

int main()
{
    try {
        test_base_conv();
        test_greater();
        test_greater_num();
        test_add();
        test_sub();
        test_gr_or_eq();
        test_bits_right();
        test_bits_left();
        test_mul();
        test_mod();
        test_div();
        test_karatsuba();
        test_power_mod();
        test_rand();
        test_lemera();
        // 21359761114
        test_miller_rabina();
        test_jac_sym();
        test_soloveya_shtrassena(); 
    } catch (const char *mess) {
        printf("%s\n", mess);
        return 1;
    }

    return 0;   
}
