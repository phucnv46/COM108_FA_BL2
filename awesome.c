#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define WIDTH 80
#define HEIGHT 24
#define LOGO "DVD"

// Clear screen function
void clearScreen() {
    system("cls");
}

// Set cursor position
void setCursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Set text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Hide cursor
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int main() {
    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    int dx = 1;
    int dy = 1;
    int color = 9; // Blue
    int cornerHits = 0;
    int totalBounces = 0;
    
    hideCursor();
    clearScreen();
    
    printf("=== BOUNCING DVD LOGO ===\n");
    printf("Watch the magic happen! Press Ctrl+C to exit.\n");
    printf("Corner hits: 0 | Total bounces: 0\n\n");
    Sleep(2000);
    
    while (1) {
        // Clear previous position
        setCursor(x, y);
        printf("   ");
        
        // Update position
        x += dx;
        y += dy;
        
        // Check boundaries and change direction
        int bounced = 0;
        
        // Check corners first
        if ((x <= 0 || x >= WIDTH - 3) && (y <= 3 || y >= HEIGHT - 1)) {
            cornerHits++;
            color = 13; // Bright magenta for corner hit!
            bounced = 1;
        }
        
        if (x <= 0 || x >= WIDTH - 3) {
            dx = -dx;
            if (!bounced) {
                color = (color % 15) + 1; // Cycle through colors
            }
            totalBounces++;
            bounced = 1;
        }
        
        if (y <= 3 || y >= HEIGHT - 1) {
            dy = -dy;
            if (!bounced) {
                color = (color % 15) + 1;
            }
            totalBounces++;
        }
        
        // Draw logo at new position
        setColor(color);
        setCursor(x, y);
        printf(LOGO);
        
        // Update stats
        setCursor(0, 2);
        setColor(15);
        printf("Corner hits: %d | Total bounces: %d", cornerHits, totalBounces);
        
        // Add some sparkle effect on corner hits
        if (bounced && cornerHits > 0 && color == 13) {
            setCursor(WIDTH - 20, HEIGHT - 1);
            printf("*** CORNER HIT! ***");
            Sleep(500);
            setCursor(WIDTH - 20, HEIGHT - 1);
            printf("                   ");
        }
        
        Sleep(50); // Animation speed
    }
    
    return 0;
}
