#include <GL/glut.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstdio>

// Maze dimensions
int mazeWidth = 11;
int mazeHeight = 11;
std::vector<std::vector<int>> maze;

// Player position
float playerX = 1.0f, playerY = 1.0f;

// Exit position
int exitX = mazeWidth - 2;
int exitY = mazeHeight - 2;

// Window dimensions
const int windowWidth = 800;
const int windowHeight = 800;
float cellSize;

// Timer variables
int timeRemaining = 30;
bool gameRunning = false;
bool won = false;
int level = 1;
int highScore = 0;
int currentScore = 0;

// Game states
enum GameState { MENU, PLAYING, GAME_OVER, WIN, PAUSE };
GameState gameState = MENU;

// Maze generation using Depth-First Search (DFS)
void generateMaze(int x, int y) {
    maze[y][x] = 0;
    std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    std::random_shuffle(directions.begin(), directions.end());

    for (auto& dir : directions) {
        int nx = x + dir.first * 2;
        int ny = y + dir.second * 2;
        if (nx >= 0 && ny >= 0 && nx < mazeWidth && ny < mazeHeight && maze[ny][nx] == 1) {
            maze[ny - dir.second][nx - dir.first] = 0;
            generateMaze(nx, ny);
        }
    }
}

// Rendering the maze with improved design
void renderMaze() {
    for (int y = 0; y < mazeHeight; y++) {
        for (int x = 0; x < mazeWidth; x++) {
            if (maze[y][x] == 1) {
                glColor3f(0.3f, 0.3f, 0.3f); // Darker wall color
            }
            else {
                glColor3f(0.9f, 0.9f, 0.9f); // Lighter path color
            }
            glBegin(GL_QUADS);
            glVertex2f(x * cellSize, y * cellSize);
            glVertex2f((x + 1) * cellSize, y * cellSize);
            glVertex2f((x + 1) * cellSize, (y + 1) * cellSize);
            glVertex2f(x * cellSize, (y + 1) * cellSize);
            glEnd();
        }
    }
    glColor3f(0.0f, 0.7f, 0.2f); // Green exit color
    glBegin(GL_QUADS);
    glVertex2f(exitX * cellSize, exitY * cellSize);
    glVertex2f((exitX + 1) * cellSize, exitY * cellSize);
    glVertex2f((exitX + 1) * cellSize, (exitY + 1) * cellSize);
    glVertex2f(exitX * cellSize, (exitY + 1) * cellSize);
    glEnd();
}

// Rendering the player with improved design
void renderPlayer() {
    glColor3f(0.8f, 0.2f, 0.2f); // Red player color
    glBegin(GL_QUADS);
    glVertex2f(playerX * cellSize + 0.1 * cellSize, playerY * cellSize + 0.1 * cellSize);
    glVertex2f((playerX + 1) * cellSize - 0.1 * cellSize, playerY * cellSize + 0.1 * cellSize);
    glVertex2f((playerX + 1) * cellSize - 0.1 * cellSize, (playerY + 1) * cellSize - 0.1 * cellSize);
    glVertex2f(playerX * cellSize + 0.1 * cellSize, (playerY + 1) * cellSize - 0.1 * cellSize);
    glEnd();
}

// Render text on the screen with improved design
void renderText(float x, float y, const char* text, void* font = GLUT_BITMAP_HELVETICA_18) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// Check for win condition
void checkWin() {
    if (int(playerX) == exitX && int(playerY) == exitY) {
        won = true;
        gameRunning = false;
        currentScore += level;
        highScore = std::max(highScore, currentScore);
        level++;
        if (level > 5) {
            gameState = WIN;
        }
        else {
            mazeWidth += 2;
            mazeHeight += 2;
            maze.assign(mazeHeight, std::vector<int>(mazeWidth, 1));
            exitX = mazeWidth - 2;
            exitY = mazeHeight - 2;
            cellSize = windowWidth / static_cast<float>(mazeWidth);
            timeRemaining = 60 - (level * 2);
            generateMaze(1, 1);
            playerX = 1.0f;
            playerY = 1.0f;
            gameRunning = true;
            won = false;
        }
        glutPostRedisplay();
    }
}

// Timer function
void timer(int value) {
    if (gameRunning) {
        timeRemaining--;
        if (timeRemaining <= 0) {
            gameRunning = false;
            gameState = GAME_OVER;
        }
        glutPostRedisplay();
    }
    int interval = std::max(500, 1000 - level * 100);
    glutTimerFunc(interval, timer, 0);
}

// Display function for rendering the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameState == MENU) {
        renderText(windowWidth / 2 - 150, windowHeight / 2 - 80, "Welcome to Maze Escape", GLUT_BITMAP_TIMES_ROMAN_24);
        renderText(windowWidth / 2 - 100, windowHeight / 2, "Press 'Enter' to Start New Game");
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "Highest Score: %d", highScore);
        renderText(windowWidth / 2 - 100, windowHeight / 2 + 50, buffer);
    }
    else if (gameState == PLAYING) {
        renderMaze();
        renderPlayer();

        if (won) {
            renderText(windowWidth / 2 - 50, windowHeight / 2, "You Win!");
        }
        else if (!gameRunning) {
            renderText(windowWidth / 2 - 50, windowHeight / 2, "You Lose!");
        }

        char buffer[20];
        snprintf(buffer, sizeof(buffer), "Time: %d", timeRemaining);
        renderText(windowWidth - 120, 20, buffer);

        snprintf(buffer, sizeof(buffer), "Level: %d", level);
        renderText(10, 20, buffer);
    }
    else if (gameState == GAME_OVER) {
        renderText(windowWidth / 2 - 100, windowHeight / 2, "Game Over! Press 'Enter' to Retry.");
    }
    else if (gameState == WIN) {
        renderText(windowWidth / 2 - 150, windowHeight / 2 - 50, "Congratulations! You completed all levels!");
        renderText(windowWidth / 2 - 100, windowHeight / 2, "Press 'R' to Retry");
        renderText(windowWidth / 2 - 100, windowHeight / 2 + 50, "Press 'M' to Return to Menu");
    }

    else if (gameState == PAUSE) {
        renderText(windowWidth / 2 - 100, windowHeight / 2 - 50, "Game Paused");
        renderText(windowWidth / 2 - 100, windowHeight / 2, "Press 'R' to Retry");
        renderText(windowWidth / 2 - 100, windowHeight / 2 + 50, "Press 'C' to Continue");
        renderText(windowWidth / 2 - 100, windowHeight / 2 + 100, "Press 'M' to Menu");
    }

    renderText(10, windowHeight - 20, "Press 'Esc' for Options");

    glutSwapBuffers();
}

// Modify the keyboard function to handle the Enter key as a normal key
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        if (gameState == PLAYING) {
            gameState = PAUSE;
            gameRunning = false;
            glutPostRedisplay();
        }
        return;
    }

    if (gameState == PAUSE) {
        if (key == 'r') {
            gameState = PLAYING;
            level = 1;
            currentScore = 0;
            mazeWidth = 11;
            mazeHeight = 11;
            maze.assign(mazeHeight, std::vector<int>(mazeWidth, 1));
            exitX = mazeWidth - 2;
            exitY = mazeHeight - 2;
            cellSize = windowWidth / static_cast<float>(mazeWidth);
            timeRemaining = 30;
            generateMaze(1, 1);
            playerX = 1.0f;
            playerY = 1.0f;
            gameRunning = true;
            won = false;
            glutPostRedisplay();
        }
        else if (key == 'c') {
            gameState = PLAYING;
            gameRunning = true;
            glutPostRedisplay();
        }
        else if (key == 'm') {
            gameState = MENU;
            glutPostRedisplay();
        }
        return;
    }

    if (!gameRunning) {
        if (key == 13) {
            if (gameState == MENU || gameState == GAME_OVER || gameState == WIN) {
                gameState = PLAYING;
                level = 1;
                currentScore = 0;
                mazeWidth = 11;
                mazeHeight = 11;
                maze.assign(mazeHeight, std::vector<int>(mazeWidth, 1));
                exitX = mazeWidth - 2;
                exitY = mazeHeight - 2;
                cellSize = windowWidth / static_cast<float>(mazeWidth);
                timeRemaining = 30;
                generateMaze(1, 1);
                playerX = 1.0f;
                playerY = 1.0f;
                gameRunning = true;
                won = false;
                glutPostRedisplay();
            }
        }
        // Handle 'R' and 'M' for retry or menu in WIN state
        if (gameState == WIN) {
            if (key == 'r') {
                // Restart the game
                gameState = PLAYING;
                level = 1;
                currentScore = 0;
                mazeWidth = 11;
                mazeHeight = 11;
                maze.assign(mazeHeight, std::vector<int>(mazeWidth, 1));
                exitX = mazeWidth - 2;
                exitY = mazeHeight - 2;
                cellSize = windowWidth / static_cast<float>(mazeWidth);
                timeRemaining = 30;
                generateMaze(1, 1);
                playerX = 1.0f;
                playerY = 1.0f;
                gameRunning = true;
                won = false;
                glutPostRedisplay();
            }
            else if (key == 'm') {
                // Return to the menu
                gameState = MENU;
                glutPostRedisplay();
            }
        }
        return;
    }


    float newX = playerX, newY = playerY;
    switch (key) {
    case 'w': newY -= 1; break;
    case 's': newY += 1; break;
    case 'a': newX -= 1; break;
    case 'd': newX += 1; break;
    }
    if (newX >= 0 && newX < mazeWidth && newY >= 0 && newY < mazeHeight && maze[int(newY)][int(newX)] == 0) {
        playerX = newX;
        playerY = newY;
        checkWin();
    }
    glutPostRedisplay();
}

// OpenGL initialization
void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, windowHeight, 0.0);
}

// Main function
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    maze.assign(mazeHeight, std::vector<int>(mazeWidth, 1));
    generateMaze(1, 1);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Maze Game");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, timer, 0);

    glutMainLoop();

    return 0;
}
