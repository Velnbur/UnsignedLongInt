#include <stdio.h>

#include "uli.h"

// #define GREEN   "\033[32m"
// #define RED     "\033[31m"
// #define RESET   "\033[0m"

void test_greater() {
  puts("\nTEST GREATER");
  ULI uli(123, 10);
  ULI uli2("6", 1, 10);
  const char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete[] string;

  string = uli2.ToString();
  printf("uli2 = %s\n", string);
  delete[] string;

  printf("uli > uli2 = %d\n", uli > uli2);
}

void test_greater_num() {
  puts("\nTEST GREATER BETWEEN NUM AND ULI");
  ULI uli(123, 10);
  const char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete[] string;

  printf("uli > 13 = %d\n", uli > 13);
}

void test_gr_or_eq() {
  puts("\nTEST GREATER OR EQUAL");
  ULI uli(123, 10);
  ULI uli2("123", 3, 10);
  const char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete[] string;

  string = uli2.ToString();
  printf("uli2 = %s\n", string);
  delete[] string;

  printf("uli >= uli2 = %d\n", uli >= uli2);
}

void test_add() {
  puts("\nTEST ADD");
  ULI uli(123123, 10);
  ULI uli2("12123", 5, 10);
  const char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete[] string;

  string = uli2.ToString();
  printf("uli2 = %s\n", string);
  delete[] string;

  printf("uli + uli2 = %s\n", (uli + uli2).ToString());
}

void test_minus() {
  puts("\nTEST SUB");
  ULI uli(123123, 10);
  ULI uli2("12123", 5, 10);
  const char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete[] string;

  string = uli2.ToString();
  printf("uli2 = %s\n", string);
  delete[] string;

  printf("uli - uli2 = %s\n", (uli - uli2).ToString());
}

void test_bits_right() {
  puts("\nTEST LEFT SHIFT");
  ULI uli(7, 10);
  const char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete[] string;

  printf("uli >> 1 = %s\n", (uli >> 1).ToString());
}

void test_bits_left() {
  puts("\nTEST LEFT SHIFT");
  ULI uli(123123, 10);
  const char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete[] string;

  printf("uli << 2 = %s\n", (uli << 2).ToString());
}

void test_mul() {
  puts("\nTEST MUL");
  ULI uli("429", 3, 10);
  ULI uli2("2194", 4, 10);
  const char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete[] string;

  string = uli2.ToString();
  printf("uli2 = %s\n", string);
  delete[] string;

  printf("uli * uli2 = %s\n", (uli * uli2).ToString());
}

void test_mod() {
  puts("\nTEST MOD");
  ULI uli(324, 10);
  ULI uli2("12", 2, 10);
  const char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete[] string;

  string = uli2.ToString();
  printf("uli2 = %s\n", string);
  delete[] string;

  printf("uli %% uli2 = %s\n", (uli % uli2).ToString());
}

void test_div() {
  puts("\nTEST DIVISION");
  ULI uli(324, 10);
  ULI uli2("32", 2, 10);
  const char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete[] string;

  string = uli2.ToString();
  printf("uli2 = %s\n", string);
  delete[] string;

  printf("uli / uli2 = %s\n", (uli / uli2).ToString());
}

void test_karatsuba() {
  puts("\nTEST KARATSUBA");
  ULI uli("429428585122", 12, 10);
  ULI uli1("21942995959349358394935", 23, 10);
  char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete [] string;

  string = uli1.ToString();
  printf("uli1 = %s\n", string);
  delete [] string;

  string = (uli * uli1).ToString();
  printf("uli.Karatsuba(uli1) = %s\n", string);
}

void test_power_mod() {
  puts("\nTEST POWER MOD");

  ULI uli("3", 1, 10); 
  ULI power("90", 2, 10);
  ULI mod("5", 1, 10);
  char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete [] string;

  string = power.ToString();
  printf("power = %s\n", string);
  delete [] string;

  string = mod.ToString();
  printf("mod = %s\n", string);
  delete [] string;

  string = ULI::power_mod(uli, power, mod).ToString();
  printf("uli^power %% mod = %s\n", string);
}

void test_rand() {
  puts("\nTEST RAND");
  char *string;

  string = ULI::rand(10).ToString();
  printf("rand() = %s\n", string);
}

void test_Lemena() {
  puts("\nTEST LEMERA");

  ULI uli("100003", 6, 10); 
  char *string;

  string = uli.ToString();
  printf("uli = %s\n", string);
  delete [] string;
  printf("uli is primary = %d\n", uli.IsPrimary());  
}

int main() {
  try {
    test_greater();
    test_greater_num();
    test_add();
    test_minus();
    test_gr_or_eq();
    test_bits_right();
    test_bits_left();
    test_mul();
    test_mod();
    test_div();
    test_karatsuba();
    test_power_mod();
    test_rand();
    test_Lemena();
  } catch (const char *mess) {
    printf("%s\n", mess);
    return 1;
  }

  return 0;
}
