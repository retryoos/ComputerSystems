/*
 * PA1 - Boston College Computer Systems
 * Converts input between metric and US units and prints the convertion
 * Date: Feb 9th, 2024
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN_TO_CM 2.54
#define MAX_BUFFER_LENGTH 256

typedef enum {
    MM,
    CM,
    M,
    KM,
    IN,
    FT,
    YD,
    MI,
    UNSUPPORTED
} Unit;

const char * const unit_strings[] = {"mm", "cm", "m", "km", "in", "ft", "yd", "mi"};
const double factors[] = {0.1, 1.0, 100.0, 100000.0, 1.0, 12.0, 36.0, 63360.0};
const int num_unit_strings = sizeof(unit_strings) / sizeof(unit_strings[0]);

Unit unit_string_to_unit(const char * const unit_string) {
    for (int i = 0; i < num_unit_strings; ++i) {
        if (!strcmp(unit_strings[i], unit_string)) {
            return (Unit)i;
        }   
    }
    return UNSUPPORTED;
} 

int is_metric(const Unit unit) {
    return (unit >= MM && unit <= KM);
} 

char * scan_substring(char * input, const char * input_end, char * output) {
    while (input < input_end && isspace(*input)) {
        input++;
    }
    while (input < input_end && !isspace(*input)) {
        *output++ = *input++;
    }
    *output = '\0';
    return input;
}

int scan_input(char * input, double * value, char * input_string, char * output_string, int max_length) {
    int num_scanned = 0;
    char * rest = input;
    char * end_len = input + max_length;
    
    *value = strtod(input, &rest);
    
    if (rest == input) {
        return num_scanned;
    }
    ++num_scanned;

    rest = scan_substring(rest, end_len, input_string);
    if (rest == input) {
        return num_scanned;
    }
    ++num_scanned;

    rest = scan_substring(rest, end_len, output_string);
    if (rest == input) {
        return num_scanned;
    }
    
    return ++num_scanned; 
}

int capture_and_scan_input(double * value, char * input_string, char * output_string, int max_length) {
    char buffer[MAX_BUFFER_LENGTH];
  
    char * result = fgets(buffer, MAX_BUFFER_LENGTH, stdin);
    if (!result) {
        return 0;
    }    
    return scan_input(buffer, value, input_string, output_string, max_length);   
}

double convert(double value, const char * const input_unit_string, const char * const output_unit_string) {
    Unit input_unit = unit_string_to_unit(input_unit_string);
    Unit output_unit = unit_string_to_unit(output_unit_string);

    if (input_unit == UNSUPPORTED || output_unit == UNSUPPORTED) {
        return NAN;
    }
    double reference_value;

    if (is_metric(input_unit) && !is_metric(output_unit)) {        
        if (input_unit == CM) {
            reference_value = value;
        } else if (input_unit == MM) {
            reference_value = value / 10; 
        } else if (input_unit == M) {
            reference_value = value * 100;
        } else if (input_unit == KM) {
            reference_value = value * 100000;
        }
        reference_value /= IN_TO_CM;   
        return reference_value / factors[output_unit];
    } else if (!is_metric(input_unit) && is_metric(output_unit)) {
        if (input_unit == IN) {
            reference_value = value;
        } else if (input_unit == FT) {
            reference_value = value * 12;
        } else if (input_unit == YD) {
            reference_value = value * 36;
        } else if (input_unit == MI) {
            reference_value = value * 63360;
        }
        reference_value *= IN_TO_CM;
        return reference_value / factors[output_unit];
    } else {
        reference_value = value * factors[input_unit];
        return reference_value / factors[output_unit];
    }                      
}

void print_allowable_units() {
    printf("Allowable units:");    
    for (int i = 0; i < num_unit_strings; i++) {
        printf(" %s", unit_strings[i]);
    }
    printf(".\n");
}

int main() {
    puts("Please enter a length to convert, in the form <number> <input-unit> <output-unit>.");
    puts("Enter any letter to quit.");

    while (1) {
        char input_string[MAX_BUFFER_LENGTH];
        char output_string[MAX_BUFFER_LENGTH];
        double value;
        
        printf("> ");

        int length = capture_and_scan_input(&value, input_string, output_string, MAX_BUFFER_LENGTH);
        
        if (length < 3) {
            break;
        }   
        
        double converted_val = convert(value, input_string, output_string);
        
        if (isnan(converted_val)) {
            print_allowable_units();
        } else {
            printf("%f %s = %f %s\n", value, input_string, converted_val, output_string);
        }
    }
    return 0;
}
