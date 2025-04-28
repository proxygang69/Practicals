#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

int main() {
    char input[256];
    int fd1, fd2;

    // Create FIFOs if they don't exist
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    // Open FIFO1 for writing
    fd1 = open(FIFO1, O_WRONLY);
    // Open FIFO2 for reading
    fd2 = open(FIFO2, O_RDONLY);

    while (1) {
        printf("Enter a sentence (type 'exit' to quit): ");
        fgets(input, sizeof(input), stdin);
        // Exit condition
        if (strcmp(input, "exit\n") == 0) {
            break;
        }

        // Write input to FIFO1
        write(fd1, input, strlen(input));

        // Read from FIFO2
        char output[256];
        read(fd2, output, sizeof(output));
        printf("Processed Output:\n%s", output);
    }

    // Close FIFOs
    close(fd1);
    close(fd2);
    return 0;
}