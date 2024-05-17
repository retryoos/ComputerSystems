/*
 * PA3 - Boston College Computer Systems
 * Visualizing the Central Limit Theorem
 * Date: Mar 17th, 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAMPLES 10000
#define RUNS 50000
#define BINS 64
#define HISTOGRAM_SPAN 0.05
#define SCALE 32

double get_mean_of_uniform_random_samples() {
    double sum = 0.0;
    for (int i = 0; i < SAMPLES; ++i) {
        double rand_num = (double)rand() / RAND_MAX;
        rand_num = rand_num * 2.0 - 1.0;
        sum += rand_num;
    }
    return sum / SAMPLES;
}
double populate_values_and_get_mean(double *values) {
    double sum = 0.0;
    for (int i = 0; i < RUNS; ++i) {
        values[i] = get_mean_of_uniform_random_samples();
        sum += values[i];
    }
    return sum / RUNS;
}
double get_mean_squared_error(double *values, double mean) {
    double sum = 0.0;
    for (int i = 0; i < RUNS; ++i) {
        double error = values[i] - mean;
        sum += error * error;
    }
    return sum / RUNS;
}
void create_histogram(double *values, int *counts) {
    double bin_size = HISTOGRAM_SPAN / BINS;
    for (int i = 0; i < RUNS; ++i) {
        int j = 0;
        double bin_start = -(HISTOGRAM_SPAN / 2.0);
        while (values[i] > bin_start + bin_size * (j + 1)) {
            ++j;
        }
        counts[j]++;
    }
}
void print_histogram(int *counts) {
    double bin_size = HISTOGRAM_SPAN / BINS;
    for (int i = 0; i< BINS; ++i) {
        double bin_start = -(HISTOGRAM_SPAN / 2.0) + i * bin_size;
        double bin_mid = bin_start + bin_size / 2.0;
        printf("%.4f: ", bin_mid);
        for (int j = 0; j < counts[i] / SCALE; ++j) {
            printf("X");
        }
        printf("\n");
    }
}
int main() {
    srand(time(NULL));

    double *values = malloc(RUNS * sizeof(double));
    if (values == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    int *counts = calloc(BINS, sizeof(int));
    if (counts == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(values);
        return 1;
    }
    double mean = populate_values_and_get_mean(values);
    double mean_squared_error = get_mean_squared_error(values, mean);
    create_histogram(values, counts);
    print_histogram(counts);
    printf("Sample mean: %.6f    Sample variance: %.6f\n", mean, mean_squared_error);
    free(values);
    free(counts);

    return 0;
}