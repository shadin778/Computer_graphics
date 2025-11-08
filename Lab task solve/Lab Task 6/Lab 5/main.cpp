#include <windows.h>
#include <GL/glut.h>

// Define color states (R, G, B)
float bgColors[][3] = {
    {0.2f, 0.3f, 0.8f},  // Blueish
    {0.9f, 0.6f, 0.1f},  // Orange
    {0.2f, 0.6f, 0.2f},  // Greenish
    {0.6f, 0.2f, 0.5f}   // Purple
};

int colorIndex = 0;
int totalColors = sizeof(bgColors) / sizeof(bgColors[0]);

void display() {
    // Clear screen with current background color
    glClear(GL_COLOR_BUFFER_BIT);

    // Optional: draw something to make it obvious
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(-0.2f, 0.2f);
    glEnd();

    glFlush();
}

void changeBackgroundColor(int value) {
    // Update background color
    float* color = bgColors[colorIndex];
    glClearColor(color[0], color[1], color[2], 1.0f);

    // Move to next color
    colorIndex = (colorIndex + 1) % totalColors;

    glutPostRedisplay();
    glutTimerFunc(20, changeBackgroundColor, 0);
}

void init() {
    glClearColor(bgColors[0][0], bgColors[0][1], bgColors[0][2], 1.0f); // Initial color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Needed for proper rendering
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Background Color Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(20, changeBackgroundColor, 0);
    glutMainLoop();
    return 0;
}
