#include <stdio.h>
#include <string.h>

#define MAX_PAGES 50       // Maximum number of pages that can be referenced
#define MAX_FRAMES 10      // Maximum number of frames that can be used

void fcfs(int pages[], int n, int frame_size) {
    int frames[MAX_FRAMES];      // Array to store current frames
    memset(frames, -1, sizeof(frames));  // Initialize frames to -1 (empty)
    int page_faults = 0;         // Counter for page faults

    // Iterate through each page reference
    for (int i = 0; i < n; i++) {
        int page = pages[i];     // Current page being referenced
        int found = 0;           // Flag to check if page is in frames

        // Check if the current page is already in one of the frames
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == page) { // If page is found in frames
                found = 1;           // Set found flag
                break;               // Exit the loop early
            }
        }

        // If the page was not found, it's a page fault
        if (!found) {
            // Replace the oldest page in frames using the page_faults counter (FIFO logic)
            frames[page_faults % frame_size] = page;
            page_faults++;          // Increment the page fault counter
        }

        // Print current reference and state of frames
        printf("Reference: %d | Frames: ", page);
        for (int k = 0; k < frame_size; k++) {
            if (frames[k] != -1) {   // Only print frames that are occupied
                printf("%d ", frames[k]);
            }
        }
        printf("\n");                 // New line for better readability
    }

    // Print total number of page faults after processing all references
    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES], n, frame_size;

    // Prompt user for number of frames and validate input
    printf("Enter number of frames (minimum 3, maximum %d): ", MAX_FRAMES);
    scanf("%d", &frame_size);

    if (frame_size < 3 || frame_size > MAX_FRAMES) {
        printf("Frame size must be between 3 and %d.\n", MAX_FRAMES);
        return 1; // Exit if invalid
    }

    // Prompt user for number of pages
    printf("Enter number of pages (maximum %d): ", MAX_PAGES);
    scanf("%d", &n);
    
    if (n > MAX_PAGES) {
        printf("Number of pages cannot exceed %d.\n", MAX_PAGES);
        return 1; // Exit if invalid
    }

    // Prompt user for the page reference string
    printf("Enter the page reference string (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);     // Read each page reference
    }

    // Call the FCFS function to process the page references
    fcfs(pages, n, frame_size);
    return 0; // Exit program successfully
}
