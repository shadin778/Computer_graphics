#include <GL/glut.h>
#include <math.h>

void circle(float centerX, float centerY) {
    glLineWidth(2);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++) {
        glColor3ub(0, 0, 0);
        float pi = 3.1416f;
        float A = (i * 2 * pi) / 200;
        float r = 0.35f;
        float x = centerX + r * cos(A);
        float y = centerY + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
}

void innercircle(float centerX, float centerY) {
    glLineWidth(2);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++) {
        glColor3ub(255, 255, 255);
        float pi = 3.1416f;
        float A = (i * 2 * pi) / 200;
        float r = 0.345f;
        float x = centerX + r * cos(A);
        float y = centerY + r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
}

void box() {
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2d(0.906, .83);
    glVertex2d(1.34, .84);
    glVertex2d(1.62, 0.51);
    glVertex2d(.58, .50);
    glEnd();
}

void tree() {
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2d(.3, .2); glVertex2d(1.8, .2);
    glVertex2d(.4, .2); glVertex2d(.4, .4);
    glVertex2d(.35, .25); glVertex2d(.4, .3);
    glVertex2d(.4, .35); glVertex2d(.45, .3);
    glVertex2d(.4, .3); glVertex2d(.45, .25);
    glVertex2d(.35, .3); glVertex2d(.4, .35);
    glVertex2d(.35, .35); glVertex2d(.4, .4);
    glVertex2d(.4, .4); glVertex2d(.45, .35);
    glVertex2d(1.7, .2); glVertex2d(1.7, .4);
    glVertex2d(1.65, .25); glVertex2d(1.7, .3);
    glVertex2d(1.7, .3); glVertex2d(1.75, .25);
    glVertex2d(1.7, .35); glVertex2d(1.75, .3);
    glVertex2d(1.65, .3); glVertex2d(1.7, .35);
    glVertex2d(1.7, .4); glVertex2d(1.65, .35);
    glVertex2d(1.7, .4); glVertex2d(1.75, .35);
    glVertex2d(0.64, .83); glVertex2d(0.82, 0.83);
    glVertex2d(.62, 1.14); glVertex2d(.99, 1.14);
    glVertex2d(1.29, 1.10); glVertex2d(1.59, 1.10);
    glVertex2d(1.40, .85); glVertex2d(1.56, .85);
    glEnd();
}

void mountain() {
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2d(.4, .2); glVertex2d(.5, .3);
    glVertex2d(.5, .3); glVertex2d(.56, .32);
    glVertex2d(.56, .32); glVertex2d(.6, .4);
    glVertex2d(.6, .4); glVertex2d(.7, .5);
    glVertex2d(.7, .5); glVertex2d(.9, .7);
    glVertex2d(.9, .7); glVertex2d(.95, .76);
    glVertex2d(.95, .76); glVertex2d(1, .75);
    glVertex2d(1, .75); glVertex2d(1.03, .75);
    glVertex2d(1.03, .75); glVertex2d(1.1, 0.85);
    glVertex2d(1.1, 0.85); glVertex2d(1.195, .77);
    glVertex2d(1.195, .77); glVertex2d(1.25, 0.7);
    glVertex2d(1.25, .7); glVertex2d(1.4, .5);
    glVertex2d(1.4, .5); glVertex2d(1.5, .4);
    glVertex2d(1.5, .4); glVertex2d(1.6, .3);
    glVertex2d(1.6, .3); glVertex2d(1.7, .2);
    glVertex2d(.96, .2); glVertex2d(.97, .25);
    glVertex2d(.97, .25); glVertex2d(1, 0.3);
    glVertex2d(1, .3); glVertex2d(1.02, 0.34);
    glVertex2d(1.02, .34); glVertex2d(1.05, 0.4);
    glVertex2d(1.05, .4); glVertex2d(1.06, 0.5);
    glVertex2d(1.06, .5); glVertex2d(1.1, 0.6);
    glVertex2d(1.1, .6); glVertex2d(1.02, 0.7);
    glVertex2d(1.02, 0.7); glVertex2d(1.03, 0.75);
    glVertex2d(.92, .7); glVertex2d(1, .7);
    glVertex2d(0.86, 0.62); glVertex2d(1.04, .62);
    glVertex2d(.8, .56); glVertex2d(1.06, .56);
    glVertex2d(.75, .5); glVertex2d(1.05, 0.5);
    glVertex2d(.8, .56); glVertex2d(1.06, .56);
    glVertex2d(.75, 0.5); glVertex2d(1.05, 0.5);
    glVertex2d(0.7, 0.45); glVertex2d(1.04, .44);
    glVertex2d(0.6, 0.35); glVertex2d(1, 0.35);
    glVertex2d(0.55, 0.3); glVertex2d(.98, .3);
    glEnd();
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(5);
    circle(1.1, 0.85);
    innercircle(1.1, 0.85);
    box();
    tree();
    mountain();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL Setup Test");
    glutDisplayFunc(display);
    gluOrtho2D(.25, 1.85, .15, 1.35);
    glutMainLoop();
    return 0;
}
