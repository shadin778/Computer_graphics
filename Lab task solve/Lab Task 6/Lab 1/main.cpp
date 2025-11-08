#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

#define MAX_DROPS 800

float dropX[MAX_DROPS];
float dropY[MAX_DROPS];
int totalDrops = 0;

float lakeLevel = -0.6f;
float roadFloodLevel = -0.3f;
bool isFlooding = false;

void addDrop() {
    if (totalDrops < MAX_DROPS) {
        dropX[totalDrops] = -1.0f + static_cast<float>(rand()) / (RAND_MAX / 2.0f);
        dropY[totalDrops] = 1.0f;
        totalDrops++;
    }
}

void update(int value) {
    for (int i = 0; i < totalDrops; i++) {
        dropY[i] -= 0.03f;

        if (dropY[i] <= lakeLevel + 0.05f) {
            if (lakeLevel < 0.0f) {
                lakeLevel += 0.0007f; // Fill lake
            } else {
                isFlooding = true; // Lake overflowed
            }

            // Remove the drop
            for (int j = i; j < totalDrops - 1; j++) {
                dropX[j] = dropX[j + 1];
                dropY[j] = dropY[j + 1];
            }
            totalDrops--;
            i--;
        }
    }

    // Add new drops
    for (int i = 0; i < 5; i++) {
        addDrop();
    }

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

void drawRaindrops() {
    glColor3f(0.2f, 0.4f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < totalDrops; i++) {
        glVertex2f(dropX[i], dropY[i]);
        glVertex2f(dropX[i], dropY[i] - 0.05f);
    }
    glEnd();
}

void drawLakeAndFlood() {
    // Lake (filling)
    glColor3f(0.2f, 0.4f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, lakeLevel);
        glVertex2f(-1.0f, lakeLevel);
    glEnd();

    // Road
    glColor3f(0.3f, 0.3f, 0.3f);  // asphalt color
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, lakeLevel);
        glVertex2f(1.0f, lakeLevel);
        glVertex2f(1.0f, roadFloodLevel);
        glVertex2f(-1.0f, roadFloodLevel);
    glEnd();

    // Flood water on road
    if (isFlooding) {
        glColor4f(0.4f, 0.6f, 0.9f, 0.7f);  // semi-transparent blue
        glBegin(GL_QUADS);
            glVertex2f(-1.0f, roadFloodLevel);
            glVertex2f(1.0f, roadFloodLevel);
            glVertex2f(1.0f, lakeLevel + 0.05f);
            glVertex2f(-1.0f, lakeLevel + 0.05f);
        glEnd();
    }
}

void drawBuildings() {
    glColor3f(0.7f, 0.7f, 0.7f); // grey buildings
    glBegin(GL_QUADS);
        glVertex2f(-0.8f, -0.3f);
        glVertex2f(-0.6f, -0.3f);
        glVertex2f(-0.6f, 0.4f);
        glVertex2f(-0.8f, 0.4f);

        glVertex2f(-0.4f, -0.3f);
        glVertex2f(-0.2f, -0.3f);
        glVertex2f(-0.2f, 0.3f);
        glVertex2f(-0.4f, 0.3f);

        glVertex2f(0.2f, -0.3f);
        glVertex2f(0.4f, -0.3f);
        glVertex2f(0.4f, 0.5f);
        glVertex2f(0.2f, 0.5f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLakeAndFlood();
    drawBuildings();
    drawRaindrops();
    glFlush();
}

void init() {
    glClearColor(0.8f, 0.9f, 1.0f, 1.0f); // sky
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("City Lake Flood Simulation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
