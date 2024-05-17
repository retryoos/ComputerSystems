/*
 * PA2 - Boston College Computer Systems
 * Visualizing Floating-Point Representations Binary
 * Date: Mar 1st, 2024
 */ 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fp_analyzer.h"

int main(int argc, char *argv[]) {
    FP_TYPE special_values[] = {1.0/0.0, -1.0/0.0, NAN, -NAN};}
    int len = sizeof(special_values) / sizeof(special_values[0]);
    if (argc > 1) {
        if (strcmp(argv[1], "Special")) {
            for (int i = 0; i < len; i++) {
                union Converter value;
                value.n = special_values[i];
                printf(PRINT_TYPE"\n", value.n);
                print_components(value);
                puts("");
            }
            return 0;
    } else {
        union Converter num;
        puts("Please enter a floating-point number or q to quit.");
        while(scanf(PRINT_TYPE, &num.n)){
            printf("> ");
            printf(PRINT_TYPE"\n", num.n);
            print_reconstitution(num);
        }
    }
    return 0;
}