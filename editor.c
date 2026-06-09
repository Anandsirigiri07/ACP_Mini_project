#include <stdio.h>
#include <stdlib.h>

#define WIDTH 50
#define HEIGHT 20

char canvas[HEIGHT][WIDTH];

// --- 1. STATE MANAGEMENT (Storing the shapes) ---
typedef enum { RECTANGLE } ShapeType;

typedef struct {
    int id;
    ShapeType type;
    int x, y;
    int width, height;
} Shape;

Shape memory[100]; // We can store up to 100 shapes
int shapeCount = 0;
int nextId = 1;

// --- 2. DRAWING FUNCTIONS ---

void clearCanvas() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

// Function to calculate where the '*' go for a rectangle
void drawRectangle(int startX, int startY, int width, int height) {
    for (int i = startY; i < startY + height; i++) {
        for (int j = startX; j < startX + width; j++) {
            // Only draw the outer border
            if (i == startY || i == startY + height - 1 || 
                j == startX || j == startX + width - 1) {
                
                // Make sure it doesn't draw outside our 50x20 grid
                if (i >= 0 && i < HEIGHT && j >= 0 && j < WIDTH) {
                    canvas[i][j] = '*';
                }
            }
        }
    }
}

// Wipes the screen, reads memory, and redraws everything
void renderAll() {
    clearCanvas(); 
    
    for(int i = 0; i < shapeCount; i++) {
        if (memory[i].type == RECTANGLE) {
            drawRectangle(memory[i].x, memory[i].y, memory[i].width, memory[i].height);
        }
    }
    
    displayCanvas(); 
}

// --- 3. MAIN MENU ---

int main() {
    int choice;

    while(1) {
        // Redraw the screen every time the loop restarts
        renderAll();

        printf("\n=== 2D Graphics Editor ===\n");
        printf("1. Add a Rectangle\n");
        printf("2. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int x, y, w, h;
            printf("Enter X and Y coordinates (e.g., 5 5): ");
            scanf("%d %d", &x, &y);
            printf("Enter Width and Height (e.g., 10 4): ");
            scanf("%d %d", &w, &h);

            // Save the new shape to our memory array
            memory[shapeCount].id = nextId++;
            memory[shapeCount].type = RECTANGLE;
            memory[shapeCount].x = x;
            memory[shapeCount].y = y;
            memory[shapeCount].width = w;
            memory[shapeCount].height = h;
            
            shapeCount++; // Increase the total number of shapes
        } 
        else if (choice == 2) {
            printf("Exiting program...\n");
            break;
        }
    }

    return 0;
}