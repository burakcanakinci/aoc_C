#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"

int mul(int a, int b) {
    return a*b;
}

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
    int total = 0;

    while (1) {
        ret = regexec(&regex, search_position, 1, match, 0);
        char matched_str[20];

        if (ret == REG_NOMATCH) {
            break; // no more matches
        }

        int start = match[0].rm_so;
        int end = match[0].rm_eo;
        snprintf(matched_str, end - start + 1, "%s", search_position + start);
        /* printf("%s\n", matched_str); */

        int a, b;
        if (sscanf(matched_str, "mul(%d,%d)", &a, &b) == 2) {
            total += mul(a,b);
        }

        search_position += match[0].rm_eo;
    } 

    printf("total: %d", total);

    regfree(&regex);
    free(buffer);
    return 0;
}
