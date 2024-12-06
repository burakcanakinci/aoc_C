#include <stdio.h>
#include <stdlib.h>
#include <pcre.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int main(void) {
    FILE* file = fopen(INPUT_FILE, "r");

    const char *pattern = "mux\\([0-9]+,[0-9]+\\)";
    const char *error;
    int error_offset;
    pcre *re;
    int rc;
    int output_vector[30];

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    re = pcre_compile(pattern, 0, &error, &error_offset, NULL);



    pcre_free(re);
    free(buffer);
    return 0;
}