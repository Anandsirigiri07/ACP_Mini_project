#include <stdio.h>
#include <stdlib.h>

// Define the size of your drawing area
#define WIDTH 50
#define HEIGHT 20

// This 2D array is your actual picture
char canvas[HEIGHT][WIDTH];

// Function to wipe the canvas clean with underscores
void clearCanvas() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            canvas[i][j] = '_';
        }
    }
}

// Function to print the canvas to the terminal
void displayCanvas() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Test that the canvas works
    clearCanvas();
    printf("--- Initializing ACP Mini Project Canvas ---\n");
    displayCanvas();
    
    return 0;
}