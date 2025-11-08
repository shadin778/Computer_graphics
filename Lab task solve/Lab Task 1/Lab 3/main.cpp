#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
}

/* Handler for window-repaint event */
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    // ===== XY Axis =====
    glLineWidth(2.0); // Set line width for better visibility
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f); // White color for axes

    // X-Axis
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);

    // Y-Axis
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    // ===== 1st Shape: Square =====
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex2f(-0.8f, -0.8f);
    glVertex2f(-0.5f, -0.8f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.8f, -0.5f);
    glEnd();

    // ===== 2nd Shape: Triangle =====
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(-0.9f, 0.3f);
    glVertex2f(-0.5f, 0.3f);
    glVertex2f(-0.7f, 0.6f);
    glEnd();

    // ===== 3rd Shape: Triangle =====
    glBegin(GL_TRIANGLES);
    glColor3ub(232, 133, 20); // Orange
    glVertex2f(0.5f, -0.8f);
    glVertex2f(0.7f, -0.8f);
    glVertex2f(0.6f, -0.4f);
    glEnd();

    glFlush();  // Render now
}

/* Main function */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Vertex, Primitive & Color");
    glutInitWindowSize(320, 320);
    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}

