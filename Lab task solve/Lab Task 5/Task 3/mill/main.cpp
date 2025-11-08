#include <GL/glut.h>
#include <cmath>

// Windmill parameters
float bladeAngle = 0.0f;
float rotationSpeed = 2.0f; // Faster rotation
const int NUM_BLADES = 4;   // 4 blades (pakha)

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void drawWindmill() {
    // Draw tower (brown rectangle)
    glColor3f(0.55f, 0.27f, 0.07f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(-0.03f, -1.0f);
        glVertex2f(0.03f, -1.0f);
        glVertex2f(0.03f, 0.0f);
        glVertex2f(-0.03f, 0.0f);
    glEnd();

    // Draw hub (center circle)
    glColor3f(0.3f, 0.3f, 0.3f); // Dark gray
    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++) {
            float degInRad = i * M_PI/180.0f;
            glVertex2f(cos(degInRad)*0.08, sin(degInRad)*0.08 + 0.1f);
        }
    glEnd();

    // Draw 4 rotating blades (pakha)
    glColor3f(0.5f, 0.5f, 0.8f); // Light blue blades
    for(int i = 0; i < NUM_BLADES; i++) {
        float angle = bladeAngle + i * (360.0f/NUM_BLADES);
        float rad = angle * M_PI / 180.0f;

        // Each blade is a quadrilateral
        glBegin(GL_QUADS);
            // Base near hub
            glVertex2f(cos(rad)*0.08, sin(rad)*0.08 + 0.1f);
            glVertex2f(cos(rad + 7)*0.08, sin(rad + 7)*0.08 + 0.1f);
            // Tip of blade
            glVertex2f(cos(rad + 7)*0.7, sin(rad + 7)*0.7 + 0.1f);
            glVertex2f(cos(rad)*0.7, sin(rad)*0.7 + 0.1f);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawWindmill();

    glutSwapBuffers();
}

void update(int value) {
    bladeAngle += rotationSpeed;
    if(bladeAngle > 360) bladeAngle -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("4-Blade Windmill (Pakha)");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
