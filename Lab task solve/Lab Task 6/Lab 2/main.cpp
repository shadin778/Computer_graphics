#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float starX = -0.6f, starY = 0.6f;
float diamondX = 0.6f, diamondY = 0.6f;
float pentagonX = -0.6f, pentagonY = -0.6f;
float crossX = 0.6f, crossY = -0.6f;

float moveSpeed = 0.025f;

void drawStar(float x, float y) {
    glColor3f(0.6f, 0.1f, 0.7f);  // Purple
    float radius = 0.05f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 10; i++) {
        float angle = i * 3.14159f / 5.0f;
        float r = (i % 2 == 0) ? radius : radius / 2;
        glVertex2f(x + cos(angle) * r, y + sin(angle) * r);
    }
    glEnd();
}

void drawDiamond(float x, float y) {
    glColor3f(1.0f, 0.5f, 0.0f);  // Orange
    glBegin(GL_QUADS);
        glVertex2f(x, y + 0.06f);
        glVertex2f(x + 0.06f, y);
        glVertex2f(x, y - 0.06f);
        glVertex2f(x - 0.06f, y);
    glEnd();
}

void drawPentagon(float x, float y) {
    glColor3f(0.2f, 0.8f, 0.2f);  // Green
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; i++) {
        float angle = i * 2.0f * 3.14159f / 5.0f;
        glVertex2f(x + cos(angle) * 0.05f, y + sin(angle) * 0.05f);
    }
    glEnd();
}

void drawCross(float x, float y) {
    glColor3f(0.9f, 0.1f, 0.1f);  // Red
    float size = 0.02f;
    glBegin(GL_QUADS);
        glVertex2f(x - size, y + 3 * size);
        glVertex2f(x + size, y + 3 * size);
        glVertex2f(x + size, y - 3 * size);
        glVertex2f(x - size, y - 3 * size);

        glVertex2f(x - 3 * size, y + size);
        glVertex2f(x + 3 * size, y + size);
        glVertex2f(x + 3 * size, y - size);
        glVertex2f(x - 3 * size, y - size);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawStar(starX, starY);
    drawDiamond(diamondX, diamondY);
    drawPentagon(pentagonX, pentagonY);
    drawCross(crossX, crossY);
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Star (WASD)
        case 'w': starY += moveSpeed; break;
        case 's': starY -= moveSpeed; break;
        case 'a': starX -= moveSpeed; break;
        case 'd': starX += moveSpeed; break;

        // Diamond (IJKL)
        case 'i': diamondY += moveSpeed; break;
        case 'k': diamondY -= moveSpeed; break;
        case 'j': diamondX -= moveSpeed; break;
        case 'l': diamondX += moveSpeed; break;

        // Pentagon (TFGH)
        case 't': pentagonY += moveSpeed; break;
        case 'g': pentagonY -= moveSpeed; break;
        case 'f': pentagonX -= moveSpeed; break;
        case 'h': pentagonX += moveSpeed; break;

        // Cross (UYMO)
        case 'u': crossY += moveSpeed; break;
        case 'm': crossY -= moveSpeed; break;
        case 'y': crossX -= moveSpeed; break;
        case 'o': crossX += moveSpeed; break;
    }

    glutPostRedisplay();
}

void init() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Dark background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Move 4 Unique Objects");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
