#include <windows.h>
#include <GL/glut.h>


void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(5.0);

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 0.0f);


    glVertex2f(-0.8f, 0.8f);
    glVertex2f(0.8f, 0.8f);
    glVertex2f(0.8f, 0.0f);
    glVertex2f(-0.8f, 0.0f);
    glEnd();

    glFlush(); // Render now
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL Setup Test");
    glutInitWindowSize(320, 320);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
