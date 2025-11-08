#include <windows.h>
#include <GL/glut.h>

void floodlight() {
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);

    glVertex2d(-7, 0);    glVertex2d(-3, 0);
    glVertex2d(-3, 0);    glVertex2d(-2.4, 0.35);
    glVertex2d(-2.4, 0.35); glVertex2d(-1.83, 0.65);
    glVertex2d(-1.83, 0.65); glVertex2d(-0.87, 0.87);
    glVertex2d(-0.87, 0.87); glVertex2d(-0.176, 0.89);
    glVertex2d(-0.176, 0.89); glVertex2d(0.52, 0.90);
    glVertex2d(0.52, 0.90); glVertex2d(1.7, 0.75);
    glVertex2d(1.7, 0.75); glVertex2d(2.24, 0.41);
    glVertex2d(2.24, 0.41); glVertex2d(3, 0);
    glVertex2d(3, 0);     glVertex2d(7, 0);

    glVertex2d(-0.87, 0.87); glVertex2d(-0.5, 4.5);
    glVertex2d(-0.5, 4.5);  glVertex2d(0.23, 4.5);
    glVertex2d(0.23, 4.5);  glVertex2d(0.52, 0.90);

    glVertex2d(-0.5, 4.5);  glVertex2d(-0.6, 4.6);
    glVertex2d(-0.6, 4.6);  glVertex2d(-0.66, 4.86);
    glVertex2d(-0.66, 4.86); glVertex2d(-0.66, 5.08);
    glVertex2d(-0.66, 5.08); glVertex2d(0.41, 5.08);
    glVertex2d(0.41, 5.08); glVertex2d(0.39, 4.85);
    glVertex2d(0.39, 4.85); glVertex2d(-0.65, 4.86);

    glVertex2d(0.39, 4.85); glVertex2d(0.32, 4.69);
    glVertex2d(0.32, 4.69); glVertex2d(-0.6, 4.69);
    glVertex2d(0.32, 4.69); glVertex2d(0.238, 4.50);

    glVertex2d(-3.19, 6.77); glVertex2d(-1.18, 6.32);
    glVertex2d(-3.57, 6.00); glVertex2d(-1.27, 6.01);
    glVertex2d(-3.45, 5.33); glVertex2d(-1.22, 5.68);

    glVertex2d(0.91, 6.33);  glVertex2d(2.98, 6.63);
    glVertex2d(1, 6);        glVertex2d(3.5, 6);
    glVertex2d(0.91, 5.61);   glVertex2d(3.03, 5.37);
    glVertex2d(-0.74, 5.80);  glVertex2d(-0.40, 6.11);
    glVertex2d(-0.40, 6.11);  glVertex2d(-0.29, 6.36);
    glVertex2d(-0.29, 6.36);  glVertex2d(-0.15, 6.73);
    glVertex2d(-0.15, 6.73);  glVertex2d(0, 6.36);
    glVertex2d(0, 6.36);     glVertex2d(0.14, 6.13);
    glVertex2d(0.14, 6.13);  glVertex2d(0.41, 5.86);

    glVertex2d(-0.531, 5.08); glVertex2d(-0.53, 5.88);
    glVertex2d(-0.53, 5.88);  glVertex2d(0.27, 5.89);
    glVertex2d(0.27, 5.89);   glVertex2d(0.26, 5.08);
    glVertex2d(-0.35, 5.08);  glVertex2d(-0.35, 5.88);
    glVertex2d(-0.36, 5.73);  glVertex2d(0.12, 5.74);
    glVertex2d(0.12, 5.88);   glVertex2d(0.11, 5.09);

    glVertex2d(-0.26, 4.30);  glVertex2d(-0.04, 4.30);
    glVertex2d(-0.04, 4.30);  glVertex2d(-0.05, 4.08);
    glVertex2d(-0.05, 4.08);  glVertex2d(-0.25, 4.07);
    glVertex2d(-0.25, 4.07);  glVertex2d(-0.26, 4.30);

    glVertex2d(-0.28, 2.73);  glVertex2d(0.04, 2.74);
    glVertex2d(0.05, 2.32);   glVertex2d(0.04, 2.74);
    glVertex2d(0.05, 2.32);   glVertex2d(-0.30, 2.31);
    glVertex2d(-0.30, 2.32);  glVertex2d(-0.28, 2.73);
    glEnd();
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(4.0);
    floodlight();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL Setup Test");
    glutDisplayFunc(display);
    gluOrtho2D(-8, 8, -1, 8);
    glutMainLoop();
    return 0;
}
