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

    for (int j = 0; j < i; j++) {
        printf("%d ", numbers[j]);
    }

    // printf("%s", lines);
    printf("\n");
    free(token);

    return 0;
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