#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to extract a number from a string starting at a given index
int extract_number(const char *str, int *index) {
    int num = 0;
    while (isdigit(str[*index])) {
        num = num * 10 + (str[*index] - '0');
        (*index)++;
    }
    return num;
}

int process_text(const char *text_buffer) {
    int sum = 0;
    int mul_enabled = 1;
    int i = 0;
    int len = strlen(text_buffer);
    
    while (i < len) {
        if (strncmp(&text_buffer[i], "do()", 4) == 0) {
            mul_enabled = 1;
            i += 4;
        } else if (strncmp(&text_buffer[i], "don't()", 7) == 0) {
            mul_enabled = 0;
            i += 7;
        } else if (strncmp(&text_buffer[i], "mul(", 4) == 0) {
            i += 4; // Move past "mul("
            if (mul_enabled) {
                int num1 = extract_number(text_buffer, &i);
                if (text_buffer[i] == ',') {
                    i++; // Move past ","
                    int num2 = extract_number(text_buffer, &i);
                    if (text_buffer[i] == ')') {
                        sum += num1 * num2; // Add the result of multiplication
                        i++; // Move past ")"
                    }
                }
            } else {
                // Skip to the end of this invalid "mul" instruction
                while (i < len && text_buffer[i] != ')') {
                    i++;
                }
                if (text_buffer[i] == ')') {
                    i++; // Move past ")"
                }
            }
        } else {
            i++; // Skip invalid characters
        }
    }

    return sum;}

int main() {
    FILE *file = fopen("input.txt", "r");

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    fclose(file);

    int result = process_text(buffer);
    printf("Result: %d", result);

    free(buffer);
    return 0;
}

