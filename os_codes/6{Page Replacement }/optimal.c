#include <stdio.h>
#include <limits.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

// Function to find the optimal page to replace
int findOptimal(int frames[], int n, int pages[], int current, int frame_size) {
    int index = -1;
    int farthest = current;

    for (int i = 0; i < frame_size; i++) {
        int j;
        // Check how far into the future each frame's page is used
        for (j = current; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {  // Page is found in future references, update if it's farther
                    farthest = j;
                    index = i;
                }
                break;  // Stop searching for this frame if page is found
            }
        }
        // If frame's page is never referenced again
        if (j == n) {
            return i;  // This frame's page is optimal to replace
        }
    }

    // Return the index with the farthest future use, or the first frame if none found
    return (index == -1) ? 0 : index;
}

// Function to simulate Optimal Page Replacement
void optimal(int pages[], int n, int frame_size) {
    int frames[MAX_FRAMES];
    int page_faults = 0;

    // Initialize all frames to -1 (indicating empty)
    for (int i = 0; i < frame_size; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in frames
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If page is not found in frames, it's a page fault
        if (!found) {
            int index = findOptimal(frames, n, pages, i + 1, frame_size);
            frames[index] = page;  // Replace the page in the selected frame
            page_faults++;         // Increment the page fault counter
        }

        // Print the current state of frames after each reference
        printf("Reference: %d | Frames: ", page);
        for (int k = 0; k < frame_size; k++) {
            if (frames[k] != -1) {
                printf("%d ", frames[k]);
            }
        }
        printf("\n");
    }

    // Print the total page faults
    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES], n, frame_size;

    printf("Enter number of frames (minimum 3): ");
    scanf("%d", &frame_size);
    if (frame_size < 3) {
        printf("Frame size must be at least 3.\n");
        return 1;
    }

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Run the optimal page replacement algorithm
    optimal(pages, n, frame_size);
    return 0;
}
