#include <GL/glut.h>


float flagWidth = 0.6f;
float flagHeight = 0.4f;


void drawRectangle(float x, float y, float width, float height, float color[3]) {
    glColor3fv(color);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    float blue[] = {0.0f, 0.0f, 1.0f};
    float white[] = {1.0f, 1.0f, 1.0f};
    float red[] = {1.0f, 0.0f, 0.0f};

    float stripeWidth = flagWidth / 3;
    drawRectangle(0.0f, 0.0f, stripeWidth, flagHeight, blue);
    drawRectangle(stripeWidth, 0.0f, stripeWidth, flagHeight, white);
    drawRectangle(2 * stripeWidth, 0.0f, stripeWidth, flagHeight, red);

    glFlush();
}


void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 0.6, 0.0, 0.4);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 250);
    glutCreateWindow("French Flag");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
