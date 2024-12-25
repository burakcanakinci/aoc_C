#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define INPUT_FILE "input.txt"
#define MAX_COLUMN 141
#define MAX_ROW 140
#define WORD "XMAS"
#define WORD_LENGTH 4

int dx[] = {1, -1, 0, 0, 1, -1, 1, -1};
int dy[] = {0, 0, 1, -1, 1, 1, -1, -1};

int searchWord(char array[MAX_ROW][MAX_COLUMN], int startX, int startY) {
    int total_found = 0;

    for (int direction = 0; direction < 8; direction++) { // Iterate through directions
        int match = 1;

        for (int i = 0; i < WORD_LENGTH; i++) {
            int nx = startX + dx[direction] * i;
            int ny = startY + dy[direction] * i;

            if (nx < 0 || nx >= MAX_ROW || ny < 0 || ny >= MAX_COLUMN || array[nx][ny] != WORD[i]) {
                match = 0;
                break;
            }       
        }
        if (match) {
            total_found++;
        }
    }

    return total_found; // Return the count of matches for all directions
}
int main() { 

    char array[MAX_ROW][MAX_COLUMN] = {{'\0'}};
    int total_xmas = 0;

    FILE *file = fopen(INPUT_FILE, "r");

    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COLUMN; j++) {
            int ch = fgetc(file);

            if (ch == EOF) break;
            if (ch == '\n') break;
            array[i][j] = (char)ch;
        }
    }

    fclose(file);
    
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COLUMN; j++) {
            if  (array[i][j] == WORD[0]) {
                total_xmas += searchWord(array, i, j); // Add all found instances}
            }
        }
    }

    printf("Total: %d", total_xmas);

    return 0;
}
