#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>
#else
  #include <unistd.h>
  #include <termios.h>
  #include <fcntl.h>
#endif

// Simple ASCII Tank Shooter (single player)
// Controls: A/D move, W/S aim, +/- power, Space fire, Q quit

#define WIDTH 80
#define HEIGHT 25

static const double PI = 3.14159265358979323846;

#ifdef _WIN32
static void sleep_ms(int ms) { Sleep(ms); }
static void clear_screen(void) { system("cls"); }
#else
static void sleep_ms(int ms) { usleep(ms * 1000); }
static void clear_screen(void) { system("clear"); }

// Minimal kbhit/getch replacement for POSIX
static int kbhit(void) {
    static const int STDIN_FD = 0;
    static int initialized = 0;
    static struct termios oldt, newt;
    if (!initialized) {
        tcgetattr(STDIN_FD, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FD, TCSANOW, &newt);
        setvbuf(stdin, NULL, _IONBF, 0);
        initialized = 1;
    }
    int bytes waiting;
    ioctl(STDIN_FD, FIONREAD, &bytes waiting);
    return bytes waiting > 0;
}
static int getch(void) { return getchar(); }
#endif

static void draw_frame(int tank_x, int tank_y, int enemy_x, int enemy_y,
                       int shot_active, int bx, int by,
                       int score, int angle_deg, int power, int ground_y) {
    char scr[HEIGHT][WIDTH + 1];

    for (int r = 0; r < HEIGHT; ++r) {
        for (int c = 0; c < WIDTH; ++c) scr[r][c] = ' ';
        scr[r][WIDTH] = '\0';
    }

    // Ground line
    for (int c = 0; c < WIDTH; ++c) scr[ground_y][c] = '-';

    // Tank
    if (tank_x >= 0 && tank_x < WIDTH && tank_y >= 0 && tank_y < HEIGHT)
        scr[tank_y][tank_x] = 'T';

    // Enemy
    if (enemy_x >= 0 && enemy_x < WIDTH && enemy_y >= 0 && enemy_y < HEIGHT)
        scr[enemy_y][enemy_x] = 'E';

    // Bullet
    if (shot_active) {
        if (bx >= 0 && bx < WIDTH && by >= 0 && by < HEIGHT)
            scr[by][bx] = '*';
    }

    // HUD (last line)
    char hud[WIDTH + 1];
    snprintf(hud, sizeof(hud), "Score:%d  Angle:%d  Power:%d   [A/D] move  [W/S] aim  [+/-] power  [Space] fire  [Q] quit",
             score, angle_deg, power);

    // Place HUD on bottom row
    int hud_row = HEIGHT - 1;
    for (int c = 0; c < WIDTH && hud[c] != '\0'; ++c) scr[hud_row][c] = hud[c];

    // Print buffer
    for (int r = 0; r < HEIGHT; ++r) puts(scr[r]);
}

static int rng_range(int lo, int hi) { // inclusive lo..hi
    if (hi < lo) { int t = lo; lo = hi; hi = t; }
    int span = hi - lo + 1;
    return lo + rand() % (span > 0 ? span : 1);
}

int main(void) {
    srand((unsigned)time(NULL));

    const int ground_y = HEIGHT - 3; // keep last row for HUD, one row buffer
    int tank_x = 5;
    int tank_y = ground_y - 1;

    int enemy_x = rng_range(WIDTH / 2, WIDTH - 4);
    int enemy_y = ground_y - 1;
    if (enemy_x == tank_x) enemy_x = (enemy_x + 10) % (WIDTH - 2);

    int angle_deg = 45; // 5..85
    int power = 24;     // 8..50

    // Shot state
    int shot_active = 0;
    double sx = 0, sy = 0;   // shot position (float)
    double vx = 0, vy = 0;   // velocity

    const double dt = 0.05;  // physics timestep ~50 ms
    const double g = 9.8;    // gravity (down)

    int score = 0;

    for (;;) {
        // Input
#ifdef _WIN32
        if (_kbhit()) {
            int ch = _getch();
            if (ch >= 'a' && ch <= 'z') ch -= 32; // to upper
            if (ch == 'Q') break;
            if (ch == 'A') { tank_x -= 1; if (tank_x < 1) tank_x = 1; }
            else if (ch == 'D') { tank_x += 1; if (tank_x > WIDTH - 2) tank_x = WIDTH - 2; }
            else if (ch == 'W') { angle_deg += 1; if (angle_deg > 85) angle_deg = 85; }
            else if (ch == 'S') { angle_deg -= 1; if (angle_deg < 5) angle_deg = 5; }
            else if (ch == '+' || ch == '=') { power += 1; if (power > 50) power = 50; }
            else if (ch == '-') { power -= 1; if (power < 8) power = 8; }
            else if (ch == ' ') {
                if (!shot_active) {
                    double rad = angle_deg * (PI / 180.0);
                    sx = (double)tank_x; sy = (double)tank_y;
                    vx = power * cos(rad);
                    vy = -power * sin(rad); // up is negative
                    shot_active = 1;
                }
            }
        }
#else
        // POSIX minimal (optional)
        // Left as an exercise or use WASD + +/- + space + q reading via getchar() non-blocking
#endif

        // Physics update
        if (shot_active) {
            sx += vx * dt;
            sy += vy * dt;
            vy += g * dt; // gravity pulls down (positive y)

            int bx = (int)lrint(sx);
            int by = (int)lrint(sy);

            // Out of bounds horizontally
            if (bx < 0 || bx >= WIDTH) {
                shot_active = 0;
            }
            // Hit ground
            else if (by >= ground_y) {
                // Check hit near enemy x on landing
                if (abs(bx - enemy_x) <= 1) {
                    score += 1;
                    // respawn enemy somewhere on right half, away from tank
                    int nx;
                    do { nx = rng_range(WIDTH / 2, WIDTH - 4); } while (abs(nx - tank_x) < 8);
                    enemy_x = nx;
                }
                shot_active = 0;
            }
        }

        // Render
        clear_screen();
        int bx = (int)lrint(sx), by = (int)lrint(sy);
        draw_frame(tank_x, tank_y, enemy_x, enemy_y, shot_active, bx, by,
                   score, angle_deg, power, ground_y);

        sleep_ms(30);
    }

    clear_screen();
    printf("Thanks for playing! Final score: %d\n", score);
    return 0;
}
