#include <GL/glut.h>

void drawSquare(float x, float y, float size, bool isBlack) {
    if (isBlack) glColor3f(0.0f, 0.0f, 0.0f); // Black square
    else glColor3f(1.0f, 1.0f, 1.0f); // White square

    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + size);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float size = 0.5f; // Size of each square
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            bool isBlack = (i + j) % 2 == 0;
            drawSquare(-1.0f + j * size, 1.0f - (i + 1) * size, size, isBlack);
        }
    }
    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(270, 270);
    glutCreateWindow("4x4 Chess Board");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
