#include <stdio.h>
#include <stdlib.h>
#include <string.h>   // Include this for strcpy and strcat
#include <stdbool.h>

int allocated[5][3] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
int maxNeed[5][3] = {{7,5,3},{3,2,2},{9,0,2},{4,2,2},{5,3,3}};
int remaining[5][3];
int available[3];
char path[5][3];   // Array to store path as strings "P1", "P2", etc.
bool isDone[5] = {false, false, false, false, false}; // Initialize with false

int count = 0;
int n = 5; //process
int m = 3; //resources
int total[3] = {10,5,7};

void calRemaining() {
    for (int i = 0; i < n; i++) {
        for(int j = 0;j<m;j++){
            remaining[i][j] = maxNeed[i][j] - allocated[i][j];
        }
        // remaining[i][0] = maxNeed[i][0] - allocated[i][0];
        // remaining[i][1] = maxNeed[i][1] - allocated[i][1];
        // remaining[i][2] = maxNeed[i][2] - allocated[i][2];
    }
}

void calAvailable() {
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < n; i++) {
        a += allocated[i][0];
        b += allocated[i][1];
        c += allocated[i][2];
    }
    available[0] = total[0] - a;
    available[1] = total[1] - b;
    available[2] = total[2] - c;
}

void findPath() {
    int pointer = 0;
    while (count < n) {
        if (remaining[pointer][0] <= available[0] &&
            remaining[pointer][1] <= available[1] &&
            remaining[pointer][2] <= available[2] && 
            !isDone[pointer]) {
            
            available[0] += allocated[pointer][0];
            available[1] += allocated[pointer][1];
            available[2] += allocated[pointer][2];
            isDone[pointer] = true;
            sprintf(path[count],"P%d", pointer + 1); // Store "P1", "P2", etc. in path
            count++;
        }
        pointer = (pointer + 1) % n; // Move to the next process
    }
}

int main() {
    calRemaining();
    calAvailable();
    findPath();

    printf("Remaining matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", remaining[i][j]);
        }
        printf("\n");
    }

    printf("\nAvailable resources: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("The Path Sequence is: ");
    for (int i = 0; i < n - 1; i++) {
        printf("%s -> ", path[i]);
    }
    printf("%s\n", path[n - 1]);

    return 0;
}
