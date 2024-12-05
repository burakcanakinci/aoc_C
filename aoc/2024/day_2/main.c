#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_FILE "input.txt"
#define MAX_LINE_LENGTH 1024

int check_safe(char *lines) {
    int numbers[8];
    int i = 0;
    char *token = strtok(lines, " ");

    while (token != NULL) {
        numbers[i++] = atoi(token);
        token = strtok(NULL, " ");
    }

    // for (int j = 0; j < i; j++) {
    //     printf("%d ", numbers[j]);
    // }
    // printf("\n");

    int is_increasing = 1;
    int is_decreasing = 1;

    for (int j = 0; j < i - 1; j++) {
        int diff = numbers[j+1] - numbers[j];

        if (diff > 3 || diff < -3 || diff == 0) {
            return 1;
        }

        if (diff > 0) {
            is_decreasing = 0;
        } else {
            is_increasing = 0;
        }
    }

    free(token);

    return !(is_decreasing || is_increasing);
}

int main(void) {
    FILE* file = fopen(TEST_FILE, "r");

    char line[MAX_LINE_LENGTH];
    int safe = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (check_safe(line) == 0) {
            safe++;
        }
    }

    printf("\n%d\n", safe);

    fclose(file);

    return 0;
}