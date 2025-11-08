#include <windows.h>
#include <GL/glut.h>

void window(float x1, float y1, float x2, float y2)
{
    glBegin(GL_POLYGON);
    glColor3ub(173, 216, 230);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();

    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glColor3ub(255, 255, 255);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    glBegin(GL_POLYGON);
    glColor3ub(46, 128, 202);
    glVertex2f(-1.5f, -1.0f);
    glVertex2f(1.5f, -1.0f);
    glVertex2f(1.5f, 7.7f);
    glVertex2f(-1.5f, 7.7f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(-0.5f, -1.0f);
    glVertex2f(0.5f, -1.0f);
    glVertex2f(0.5f, 2.0f);
    glVertex2f(-0.5f, 2.0f);
    glEnd();


    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.5f, -1.0f);
    glVertex2f(0.5f, -1.0f);
    glVertex2f(0.5f, 2.0f);
    glVertex2f(-0.5f, 2.0f);
    glEnd();

    for (float y = 2.5f; y <= 6.5f; y += 1.0f) {
        window(-1.3f, y, -0.5f, y + 0.6f);
    }


    for (float y = 2.5f; y <= 6.5f; y += 1.0f) {
        window(0.5f, y, 1.3f, y + 0.6f);
    }


    window(-0.3f, 6.4f, 0.3f, 7.2f);
    window(-0.3f, 4.4f, 0.3f, 5.2f);
    window(-0.3f, 2.4f, 0.3f, 3.2f);

    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 800);
    glutCreateWindow("OpenGL Building");

    gluOrtho2D(-2.5, 2.5, -2, 8); // Adjusted view
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
