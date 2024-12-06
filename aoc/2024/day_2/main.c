#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_FILE "input.txt"
#define MAX_LINE_LENGTH 1024

int check_safe(int *numbers, int index) {
    int is_increasing = 1;
    int is_decreasing = 1;

    for (int i = 0; i < index - 1; i++) {
        int diff = numbers[i+1] - numbers[i];

        if (diff > 3 || diff < -3 || diff == 0) {

            return 1;
        }

        if (diff > 0) {
            is_decreasing = 0;
        } else {
            is_increasing = 0;
        }
    }

    return !(is_decreasing || is_increasing);
}

int check_removed_safe(char *lines) {
    int numbers[8];
    int index = 0;
    char *token = strtok(lines, " ");

    while (token != NULL) {
        numbers[index++] = atoi(token);
        token = strtok(NULL, " ");
    }

    if (check_safe(numbers, index) == 0) {
        return 0;
    }

    for (int i = 0; i < index; i++) {
        int temp[8];
        int temp_index = 0;

        for (int j = 0; j < index; j++) {
            if (j != i) {
                temp[temp_index++] = numbers[j];
            }
        }

        if (check_safe(temp, temp_index) == 0) {
            return 0;
        }
    }

    free(token);

    return 1;
}

int main(void) {
    FILE* file = fopen(TEST_FILE, "r");

    char line[MAX_LINE_LENGTH];
    int safe = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (check_removed_safe(line) == 0) {
            safe++;
        }
    }

    // printf("\nSafe: %d\n", safe);
    printf("\nSafe with removed: %d\n", safe);

    fclose(file);

    return 0;
}