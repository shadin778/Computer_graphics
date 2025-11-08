#include <windows.h>
#include <GL/glut.h>

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 10, 0, 6); // Viewport adjusted for flag proportions
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float colors[6][3] = {
        {1.0f, 0.0f, 0.0f}, // Red
        {1.0f, 0.5f, 0.0f}, // Orange
        {1.0f, 1.0f, 0.0f}, // Yellow
        {0.0f, 1.0f, 0.0f}, // Green
        {0.0f, 0.0f, 1.0f}, // Blue
        {0.5f, 0.0f, 0.5f}  // Purple
    };

    for (int i = 0; i < 6; i++) {
        glColor3fv(colors[i]); // Set color
        glBegin(GL_QUADS);
        glVertex2f(1.0f, i);
        glVertex2f(9.0f, i);
        glVertex2f(9.0f, i + 1);
        glVertex2f(1.0f, i + 1);
        glEnd();
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Rainbow Flag");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
