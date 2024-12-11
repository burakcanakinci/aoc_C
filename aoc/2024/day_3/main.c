#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int main(void) {
    FILE *file = fopen(INPUT_FILE, "r");

    regex_t regex;
    const char *pattern = "mul\\([0-9]+,[0-9]+\\)";

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    int ret = regcomp(&regex, pattern, REG_EXTENDED);

    char *search_position = buffer;
    regmatch_t match[1];
    int match_count = 0;

    while (1) {
        ret = regexec(&regex, search_position, 1, match, 0);
        if (ret == REG_NOMATCH) {
            break; // no more matches
        }

        int start = match[0].rm_so;
        int end = match[0].rm_eo;

        printf("%d: ",++match_count);
        for (int i = start; i < end; i++) {
            putchar(search_position[i]);
        }
        printf("\n");

        size_t new_start = match[0].rm_eo;
        memmove(buffer, buffer + new_start, strlen(buffer + new_start) + 1);

        search_position += match[0].rm_eo;
    } 

    printf("total matches: %d", match_count);

    /* printf("%s", buffer); */

    regfree(&regex);
    free(buffer);
    return 0;
}
