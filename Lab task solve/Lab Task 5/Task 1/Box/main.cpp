#include <GL/glut.h>

struct Box {
    float x, y;     // Center position
    float width, height;
    float speed;
    int direction;
    float color[3];
    const char* label;
};

// Initialize boxes with same speed but opposite directions
Box box1 = {-3.0f, 1.0f, 2.0f, 1.5f, 0.03f, 1, {0.8f, 0.2f, 0.0f}, "A"}; // Orange box moving right
Box box2 = {3.0f, -1.0f, 2.0f, 1.5f, 0.03f, -1, {0.0f, 0.6f, 0.8f}, "B"};  // Teal box moving left

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *text++);
    }
}

void drawBox(const Box& box) {
    glColor3fv(box.color);
    glBegin(GL_QUADS);
        glVertex2f(box.x - box.width/2, box.y - box.height/2);
        glVertex2f(box.x + box.width/2, box.y - box.height/2);
        glVertex2f(box.x + box.width/2, box.y + box.height/2);
        glVertex2f(box.x - box.width/2, box.y + box.height/2);
    glEnd();

    // Draw label at box center
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(box.x - 0.1f, box.y, box.label);
}

void update(int value) {
    // Move both boxes at same speed in opposite directions
    box1.x += box1.speed * box1.direction;
    box2.x += box2.speed * box2.direction;

    // Boundary checking - bounce when edges hit boundaries
    if (box1.x + box1.width/2 > 7.0f || box1.x - box1.width/2 < -7.0f) {
        box1.direction *= -1;
    }
    if (box2.x + box2.width/2 > 7.0f || box2.x - box2.width/2 < -7.0f) {
        box2.direction *= -1;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 FPS
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw title and info
    //glColor3f(1.0f, 1.0f, 1.0f);
    //drawText(-1.5f, 2.5f, "Synchronized Box Movement");
    //drawText(-3.0f, -2.8f, "Both boxes moving at speed: 0.03");

    drawBox(box1);
    drawBox(box2);

    glutSwapBuffers();
}

void init() {
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f); // Dark background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-8.0, 8.0, -3.5, 3.5);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Synchronized Box Animation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}
