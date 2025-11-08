#include <windows.h>
#include <GL/glut.h>

// Visibility flags for each object
bool show[4] = {false, false, false, false};

// Draw a rectangle at a position with color
void drawRectangle(float x, float y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.1f, y - 0.05f);
        glVertex2f(x + 0.1f, y - 0.05f);
        glVertex2f(x + 0.1f, y + 0.05f);
        glVertex2f(x - 0.1f, y + 0.05f);
    glEnd();
}

// Display function to render all visible objects
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (show[0]) drawRectangle(-0.7f,  0.6f, 1.0f, 0.0f, 0.0f); // Red
    if (show[1]) drawRectangle( 0.7f,  0.6f, 0.0f, 1.0f, 0.0f); // Green
    if (show[2]) drawRectangle(-0.7f, -0.6f, 0.0f, 0.0f, 1.0f); // Blue
    if (show[3]) drawRectangle( 0.7f, -0.6f, 1.0f, 1.0f, 0.0f); // Yellow

    glFlush();
}

// Timer callback to enable object i and set next one
void revealObject(int i) {
    if (i < 4) {
        show[i] = true;
        glutPostRedisplay();
        glutTimerFunc(20, revealObject, i + 1);
    }
}

void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sequential Rectangle Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(20, revealObject, 0); // Start revealing rectangles
    glutMainLoop();
    return 0;
}
