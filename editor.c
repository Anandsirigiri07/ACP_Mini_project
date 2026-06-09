#include <stdio.h>
#include <stdlib.h>

#define WIDTH 50
#define HEIGHT 20

char canvas[HEIGHT][WIDTH];

// --- 1. STATE MANAGEMENT ---
typedef enum { RECTANGLE, LINE, CIRCLE, TRIANGLE } ShapeType;

typedef struct {
    int id;
    ShapeType type;
    int x, y;          
    int width, height; // For Rectangle
    int x2, y2;        // For Line & Triangle
    int x3, y3;        // For Triangle
    int radius;        // For Circle
} Shape;

Shape memory[100];
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

void drawRectangle(int startX, int startY, int width, int height) {
    for (int i = startY; i < startY + height; i++) {
        for (int j = startX; j < startX + width; j++) {
            if (i == startY || i == startY + height - 1 || j == startX || j == startX + width - 1) {
                if (i >= 0 && i < HEIGHT && j >= 0 && j < WIDTH) canvas[i][j] = '*';
            }
        }
    }
}

void drawLine(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        if (y0 >= 0 && y0 < HEIGHT && x0 >= 0 && x0 < WIDTH) canvas[y0][x0] = '*';
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void drawCircle(int xc, int yc, int r) {
    for (int y = -r; y <= r; y++) {
        for (int x = -r; x <= r; x++) {
            int distSq = x*x + y*y;
            if (distSq >= r*r - r && distSq <= r*r + r) {
                if (xc+x >= 0 && xc+x < WIDTH && yc+y >= 0 && yc+y < HEIGHT) {
                    canvas[yc+y][xc+x] = '*';
                }
            }
        }
    }
}

// A triangle is just three connected lines!
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

void renderAll() {
    clearCanvas(); 
    for(int i = 0; i < shapeCount; i++) {
        if (memory[i].type == RECTANGLE) drawRectangle(memory[i].x, memory[i].y, memory[i].width, memory[i].height);
        else if (memory[i].type == LINE) drawLine(memory[i].x, memory[i].y, memory[i].x2, memory[i].y2);
        else if (memory[i].type == CIRCLE) drawCircle(memory[i].x, memory[i].y, memory[i].radius);
        else if (memory[i].type == TRIANGLE) drawTriangle(memory[i].x, memory[i].y, memory[i].x2, memory[i].y2, memory[i].x3, memory[i].y3);
    }
    displayCanvas(); 
}

// --- 3. MAIN MENU ---

int main() {
    int choice;

    while(1) {
        renderAll();

        printf("\n=== 2D Graphics Editor ===\n");
        printf("1. Add Rectangle\n2. Add Line\n3. Add Circle\n4. Add Triangle\n");
        printf("5. Modify a Shape\n6. Delete a Shape\n7. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int x, y, w, h;
            printf("Enter X Y Width Height: ");
            scanf("%d %d %d %d", &x, &y, &w, &h);
            memory[shapeCount].id = nextId++; memory[shapeCount].type = RECTANGLE;
            memory[shapeCount].x = x; memory[shapeCount].y = y; memory[shapeCount].width = w; memory[shapeCount].height = h;
            shapeCount++;
        } 
        else if (choice == 2) {
            int x1, y1, x2, y2;
            printf("Enter X1 Y1 X2 Y2: ");
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            memory[shapeCount].id = nextId++; memory[shapeCount].type = LINE;
            memory[shapeCount].x = x1; memory[shapeCount].y = y1; memory[shapeCount].x2 = x2; memory[shapeCount].y2 = y2;
            shapeCount++;
        }
        else if (choice == 3) {
            int x, y, r;
            printf("Enter CenterX CenterY Radius: ");
            scanf("%d %d %d", &x, &y, &r);
            memory[shapeCount].id = nextId++; memory[shapeCount].type = CIRCLE;
            memory[shapeCount].x = x; memory[shapeCount].y = y; memory[shapeCount].radius = r;
            shapeCount++;
        }
        else if (choice == 4) {
            int x1, y1, x2, y2, x3, y3;
            printf("Enter X1 Y1 X2 Y2 X3 Y3 (e.g., 10 2 5 10 15 10): ");
            scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
            memory[shapeCount].id = nextId++; memory[shapeCount].type = TRIANGLE;
            memory[shapeCount].x = x1; memory[shapeCount].y = y1; 
            memory[shapeCount].x2 = x2; memory[shapeCount].y2 = y2;
            memory[shapeCount].x3 = x3; memory[shapeCount].y3 = y3;
            shapeCount++;
        }
        else if (choice == 5) {
            int modId, found = 0;
            printf("Enter the ID of the shape to modify: ");
            scanf("%d", &modId);
            
            for (int i = 0; i < shapeCount; i++) {
                if (memory[i].id == modId) {
                    found = 1;
                    if (memory[i].type == CIRCLE) {
                        printf("Current Circle is at %d,%d with radius %d.\n", memory[i].x, memory[i].y, memory[i].radius);
                        printf("Enter NEW CenterX CenterY Radius: ");
                        scanf("%d %d %d", &memory[i].x, &memory[i].y, &memory[i].radius);
                    } else if (memory[i].type == RECTANGLE) {
                        printf("Enter NEW X Y Width Height: ");
                        scanf("%d %d %d %d", &memory[i].x, &memory[i].y, &memory[i].width, &memory[i].height);
                    }
                    // You can add modification prompts for Line and Triangle here if desired
                    break;
                }
            }
            if (!found) printf("--> ID not found.\n");
        }
        else if (choice == 6) {
            int deleteId, found = 0;
            printf("Enter the ID of the shape to delete: ");
            scanf("%d", &deleteId);
            for (int i = 0; i < shapeCount; i++) {
                if (memory[i].id == deleteId) {
                    found = 1;
                    for (int j = i; j < shapeCount - 1; j++) memory[j] = memory[j + 1];
                    shapeCount--;
                    break;
                }
            }
            if (!found) printf("--> ID not found.\n");
        }
        else if (choice == 7) break;
    }
    return 0;
}