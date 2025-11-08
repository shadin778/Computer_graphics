#include <GL/glut.h>
#include <cmath>

void drawBoat() {
    // Hull
    glColor3f(0.2f, 0.2f, 0.5f); // Navy blue
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.1f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.4f, -0.1f);
    glEnd();

    // Cabin
    glColor3f(0.95f, 0.85f, 0.6f); // Soft beige
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(-0.2f, 0.2f);
    glEnd();

    // Oar
    glColor3f(0.3f, 0.1f, 0.0f); // Dark brown
    glPushMatrix();
    glTranslatef(0.1f, 0.15f, 0.0f);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, -0.15f);
        glVertex2f(0.01f, -0.15f);
        glVertex2f(0.01f, 0.15f);
        glVertex2f(-0.01f, 0.15f);
    glEnd();
    glPopMatrix();

    // Person
    glColor3f(0.1f, 0.1f, 0.1f); // Dark gray
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.0f);
        glVertex2f(0.05f, 0.0f);
        glVertex2f(0.05f, 0.15f);
        glVertex2f(-0.05f, 0.15f);
    glEnd();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0.2f, 0.4f, 0.6f); // Water
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();

    glTranslatef(0.0f, -0.3f, 0.0f);
    drawBoat();

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("GLUT Boat");

    glClearColor(0.7f, 0.8f, 1.0f, 1.0f); // Sky blue

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
