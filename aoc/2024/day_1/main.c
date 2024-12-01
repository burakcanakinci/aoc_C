#include <stdio.h>
#include <stdlib.h>

#define TEST_FILE "input.txt"

int *left_side = NULL;
int *right_side = NULL;
int numbers = 0;

void create_arrays(FILE *file) {
    int num1, num2;
    numbers = 0;
    while (fscanf(file, "%d %d", &num1, &num2) == 2) {
        numbers++;
    }
    left_side = malloc(numbers * sizeof(int));
    right_side = malloc(numbers * sizeof(int));

    if (left_side == NULL || right_side == NULL) {
        perror("memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }
}

void add_numbers(FILE *file) {
    int num1, num2;
    int index = 0;
    while (fscanf(file, "%d %d", &num1, &num2) == 2) {
        left_side[index] = num1;
        right_side[index] = num2;
        index++;
    }
}

int compare_ints(const void *a, const void *b) { // ascending order
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main(void) {
    FILE *file = fopen(TEST_FILE, "r");
    int total_distance = 0;

    create_arrays(file);
    rewind(file);
    add_numbers(file);
    fclose(file);

    qsort(left_side, numbers, sizeof(int), compare_ints);
    qsort(right_side, numbers, sizeof(int), compare_ints);

    for (int i = 0; i < numbers; i++) {
        int distance = abs(left_side[i] - right_side[i]);
        total_distance += distance;
    }

    for (int i = 0; i < numbers; i++) {
        printf("Read numbers: %d and %d\n", left_side[i], right_side[i]);
    }

    printf("%d\n", total_distance);

    free(left_side);
    free(right_side);
    return 0;
}