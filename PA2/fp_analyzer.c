#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fp_analyzer.h"

FP_TYPE power_of_2(int num) {
    FP_TYPE result = 1.0;
    if (num > 0) {
        for (int i = 0; i < num; i++) {
            result *= 2;
        }
    } else {
        for (int i = 0; i < abs(num); i++) {
            result *= 2;
        }
    }
    return result;
}
void print_bits(unsigned INT_TYPE num, unsigned INT_TYPE size) { // Try: long instead of INT_TYPE
    unsigned INT_TYPE mask = 1;
    for (int i = size; i < BITS_FP_TYPE; i++) {
        printf("%d", (!!(num & (mask << ((BITS_FP_TYPE - 1) - i)))));
    }
    puts("");
}
void print_components(union Converter num){
    printf("All bits: ");
    print_bits(num.u, 0);
    printf("Sign: ");
    print_bits(num.comps.sign, EXPONENT_SIZE + MANTISSA_SIZE);
    printf("Exponent: ");
    print_bits(num.comps.exponent, MANTISSA_SIZE + SIGN_SIZE);
    printf("Mantissa: ");
    print_bits(num.comps.mantissa, EXPONENT_SIZE + SIGN_SIZE);
}
void print_normalized(union Converter num) {
    print_components(num);
    if (num.comps.sign == 0) {
        puts("Original value:");
        printf("(-1)^{%d} x (1 + "PRINT_TYPE") x 2^{%d - %d}\n", num.comps.sign, num.comps.mantissa / power_of_2(MANTISSA_SIZE), num.comps.exponent, EXPONENT_BIAS);
        printf("  = 1 x "PRINT_TYPE" x 2^{%d}\n", 1 + num.comps.mantissa / power_of_2(MANTISSA_SIZE), ((int)num.comps.exponent) - EXPONENT_BIAS);
        if ((((int)num.comps.exponent) - EXPONENT_BIAS) >= 0) {
            printf("  = "PRINT_TYPE" x %.0f\n", 1 + num.comps.mantissa / power_of_2(MANTISSA_SIZE), power_of_2(((int)num.comps.exponent) - EXPONENT_BIAS));
            printf("  = %.45f\n", num.n);
        } else {
            printf("  = "PRINT_TYPE" x 1/%.0f\n", 1 + num.comps.mantissa / power_of_2(MANTISSA_SIZE), power_of_2(((int)num.comps.exponent) - EXPONENT_BIAS));
            printf("  = %.45f\n", num.n);
        }
    } else {
        printf("  = 1 x "PRINT_TYPE" x 2^{%d}\n", 1 + num.comps.mantissa / power_of_2(MANTISSA_SIZE), ((int)num.comps.exponent) - EXPONENT_BIAS);
        if ((((int)num.comps.exponent) - EXPONENT_BIAS) >= 0) {
            printf("  = "PRINT_TYPE" x %.0f\n", 1 + num.comps.mantissa / power_of_2(MANTISSA_SIZE), power_of_2(((int)num.comps.exponent) - EXPONENT_BIAS));
            printf("  = %.45f\n", num.n);
        } else {
            printf("  = "PRINT_TYPE" x 1/%.0f\n", 1 + num.comps.mantissa / power_of_2(MANTISSA_SIZE), power_of_2(((int)num.comps.exponent) - EXPONENT_BIAS));
            printf("  = %.45f\n", num.n);
        }
    }
}
void print_denormalized(union Converter num) {
    if (num.u == 0.0 || (num.comps.sign == 1 && num.comps.exponent == 0 && num.comps.mantissa == 0)) {
        print_components(num);
        printf("Original value: %0.1lf\n", num.n);
    } else {
        if (num.comps.sign == 0) {
            print_components(num);
            puts("Original value:");
            printf("(-1)^{%d} x %0.45f x 2^{1 - %d}\n", num.comps.sign, num.comps.mantissa / power_of_2(MANTISSA_SIZE), EXPONENT_BIAS);
            printf("  = 1 x "PRINT_TYPE" x 2^{%d}\n", num.comps.mantissa / power_of_2(MANTISSA_SIZE), 1 - EXPONENT_BIAS);
            printf("  = %0.45f x 1/%.0f\n", num.comps.mantissa / power_of_2(MANTISSA_SIZE), power_of_2(1 - EXPONENT_BIAS));
            printf("  = %0.45f\n",num.n);
        } else {
            print_components(num);
            puts("Original value:");
            printf("(-1)^{%d} x %0.45f x 2^{1 - %d}\n", num.comps.sign, num.comps.mantissa / power_of_2(MANTISSA_SIZE), EXPONENT_BIAS);
            printf("  = -1 x "PRINT_TYPE" x 2^{%d}\n", num.comps.mantissa / power_of_2(MANTISSA_SIZE), 1 - EXPONENT_BIAS);
            printf("  = -1 x %0.45f x 1/%45.0f\n", num.comps.mantissa / power_of_2(MANTISSA_SIZE), power_of_2(1 - EXPONENT_BIAS));
            printf("  = %0.45f\n", num.n);
        }
    }
}
void print_reconstitution(union Converter num) {
    if (num.comps.exponent == 0.0 || num.comps.exponent == -0.0) {
        print_denormalized(num);
    } else {
        print_normalized(num);
    }
}