#include <GL/glut.h>

float trunkAngle = 0.0f;
bool trunkDirection = true;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    // Body
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_QUADS);
    glVertex2f(-0.2f, -0.1f);
    glVertex2f(0.2f, -0.1f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glEnd();

    // Head
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, 0.2f);
    glVertex2f(0.15f, 0.2f);
    glVertex2f(0.15f, 0.35f);
    glVertex2f(-0.15f, 0.35f);
    glEnd();

    // Trunk (Moves)
    glPushMatrix();
    glTranslatef(0.1f, 0.3f, 0);
    glRotatef(trunkAngle, 0, 0, 1);
    glTranslatef(-0.1f, -0.3f, 0);

    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_QUADS);
    glVertex2f(0.1f, 0.3f);
    glVertex2f(0.15f, 0.3f);
    glVertex2f(0.15f, 0.15f);
    glVertex2f(0.1f, 0.15f);
    glEnd();

    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void update(int value) {
    if (trunkDirection) {
        trunkAngle += 5.0f;
        if (trunkAngle >= 20.0f) trunkDirection = false;
    } else {
        trunkAngle -= 5.0f;
        if (trunkAngle <= -20.0f) trunkDirection = true;
    }

    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Elephant Dance");

    glutDisplayFunc(display);
    glutTimerFunc(100, update, 0);

    glClearColor(0.0f, 0.7f, 1.0f, 1.0f);
    glutMainLoop();

    return 0;
}
