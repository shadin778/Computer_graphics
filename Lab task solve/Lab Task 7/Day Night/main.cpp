#include <GL/glut.h>
#include <cmath>
using namespace std;

bool isDay = true; // Start with day

void drawCircle(float x, float y, float radius) {
    int triangleAmount = 50;
    float twicePi = 2.0f * 3.1416f;

    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i <= triangleAmount; ++i) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set background color
    if (isDay) {
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Day: sky blue
    } else {
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Night: dark blue
    }
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw sun or moon
    if (isDay) {
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow sun
    } else {
        glColor3f(1.0f, 1.0f, 1.0f); // White moon
    }

    drawCircle(0.7f, 0.7f, 0.1f); // Static position in top-right

    glutSwapBuffers();
}

void timer(int value) {
    isDay = !isDay; // Toggle day/night
    glutPostRedisplay(); // Redraw screen
    glutTimerFunc(3000, timer, 0); // Call again after 3 seconds
}

void init() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1); // 2D coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Static Day and Night Scene");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}
