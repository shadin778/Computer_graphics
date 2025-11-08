#include <GL/glut.h>
#include <cmath>

void drawCircle(GLfloat cx, GLfloat cy, GLfloat r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 500);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Tree trunk
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(180, 100);
    glVertex2f(220, 100);
    glVertex2f(220, 250);
    glVertex2f(180, 250);
    glEnd();

    // Tree leaves using circles
    glColor3ub(0, 153, 0);
    drawCircle(200, 250, 60, 50);
    drawCircle(160, 220, 50, 50);
    drawCircle(240, 220, 50, 50);
    drawCircle(180, 280, 50, 50);
    drawCircle(220, 280, 50, 50);

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Tree");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
