#include <windows.h>
#include <GL/glut.h>

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(246, 82, 80); // Set polygon color

    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.2);
    glVertex2f(0.4, 0.2);
    glVertex2f(0.2, 0.6);
    glVertex2f(-0.2, 0.6);
    glEnd();

    glutSwapBuffers(); // Use double buffering for smooth rendering
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(320, 320);
    glutCreateWindow("OpenGL Polygon");

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
