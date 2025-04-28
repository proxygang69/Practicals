#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define OUTPUT_FILE "output.txt"

void count_lines_words_chars(char *input, int *lines, int *words, int *chars) {
    *lines = *words = *chars = 0;

    char *token;
    int in_word = 0;

    token = strtok(input, "\n");
    while (token != NULL) {
        (*lines)++;
        *chars += strlen(token) + 1; // +1 for newline
        char *word = strtok(token, " ");
        while (word != NULL) {
            if (!in_word) {
                (*words)++;
                in_word = 1;
            }
            word = strtok(NULL, " ");
        }
        in_word = 0;
        token = strtok(NULL, "\n");
    }
}

int main() {
    char input[256];
    char output[256];
    int fd1, fd2;

    // Open FIFOs
    fd1 = open(FIFO1, O_RDONLY);
    fd2 = open(FIFO2, O_WRONLY);

    // Open the output file
    FILE *file = fopen(OUTPUT_FILE, "w");
    if (file == NULL) {
        perror("Failed to open output file");
        return 1;
    }

    while (1) {
        // Read from FIFO1
        read(fd1, input, sizeof(input));
        if (strlen(input) == 0) {
            continue;
        }

        // Process the input
        int lines, words, chars;
        count_lines_words_chars(input, &lines, &words, &chars);

        // Prepare output
        snprintf(output, sizeof(output), "Lines: %d\nWords: %d\nCharacters: %d\n", lines, words, chars);
        
        // Write output to the text file
        fprintf(file, "%s", output);
        fflush(file);  // Flush the file stream to ensure data is written
        printf("Records added in a file from reader.c in output.txt");

        // Write output back to FIFO2
        write(fd2, output, strlen(output));
    }

    // Close the file and FIFOs
    fclose(file);
    close(fd1);
    close(fd2);
    return 0;
}
