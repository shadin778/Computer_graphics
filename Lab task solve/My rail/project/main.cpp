#include <GL/glut.h>
#include <cmath>
#include <cstdlib> // for rand()

// Global variables
bool isDaytime = true;
float trainPos = -300.0f;
float trainSpeed = 2.0f;
float cloudPos = 0.0f;
float sunMoonPos = 0.0f;
float boatPos = 0.0f;
float boatSpeed = 1.0f;
bool isRaining = false;
float windmillAngle = 0.0f; // For rotating windmill blades

// Airplane position and speed
float airplanePos = -200.0f;
float airplaneSpeed = 3.0f;

void drawAirplane() {
    glPushMatrix();
    glTranslatef(airplanePos, 520.0f, 0.0f); // High in the sky

    // Body of the airplane
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.1f, 0.1f); // Red color
    glVertex2f(0, 0);
    glVertex2f(100, 0);
    glVertex2f(100, 20);
    glVertex2f(0, 20);
    glEnd();

    // Nose (triangle)
    glBegin(GL_TRIANGLES);
    glColor3f(0.9f, 0.3f, 0.3f);
    glVertex2f(100, 0);
    glVertex2f(120, 10);
    glVertex2f(100, 20);
    glEnd();

    // Upper wing
    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 0.1f, 0.1f);
    glVertex2f(40, 20);
    glVertex2f(70, 50);
    glVertex2f(100, 20);
    glEnd();

    // Lower wing
    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 0.1f, 0.1f);
    glVertex2f(40, 0);
    glVertex2f(70, -30);
    glVertex2f(100, 0);
    glEnd();

    glPopMatrix();
}

// Structure for raindrops
struct Raindrop {
    float x, y;
    float speed;
};

#define MAX_RAINDROPS 200
Raindrop raindrops[MAX_RAINDROPS];

// Structure for stars
struct Star {
    float x, y;
    float size;
};

#define MAX_STARS 100
Star stars[MAX_STARS];

// Initialize raindrops positions
void initRain() {
    for (int i = 0; i < MAX_RAINDROPS; ++i) {
        raindrops[i].x = rand() % 1000;
        raindrops[i].y = rand() % 600;
        raindrops[i].speed = 4.0f + (rand() % 5);  // random speed between 4-8
    }
}

// Initialize stars positions
void initStars() {
    for (int i = 0; i < MAX_STARS; ++i) {
        stars[i].x = rand() % 1000;
        stars[i].y = 200 + rand() % 400; // Stars in the upper part of the sky
        stars[i].size = (rand() % 3) + 1.0f; // Varying sizes
    }
}

// Draw raindrops as simple lines
void drawRain() {
    if (!isRaining) return; // Don't draw if not raining
    glColor3f(0.6f, 0.6f, 1.0f); // Light blue rain color
    glLineWidth(2);
    glBegin(GL_LINES);
    for (int i = 0; i < MAX_RAINDROPS; ++i) {
        float x = raindrops[i].x;
        float y = raindrops[i].y;
        glVertex2f(x, y);
        glVertex2f(x, y - 10); // rain drop line length
    }
    glEnd();
    glLineWidth(1);
}

// Draw stars as small points
void drawStars() {
    if (isDaytime) return; // Only draw at night
    glColor3f(1.0f, 1.0f, 1.0f); // White stars
    glBegin(GL_POINTS);
    for (int i = 0; i < MAX_STARS; ++i) {
        glPointSize(stars[i].size);
        glVertex2f(stars[i].x, stars[i].y);
    }
    glEnd();
    glPointSize(1); // Reset point size
}

// Update raindrops position (fall down)
void updateRain() {
    if (!isRaining) return;
    for (int i = 0; i < MAX_RAINDROPS; ++i) {
        raindrops[i].y -= raindrops[i].speed;
        if (raindrops[i].y < 0) {
            raindrops[i].x = rand() % 1000;
            raindrops[i].y = 600;
            raindrops[i].speed = 4.0f + (rand() % 5);
        }
    }
}

// Mouse callback to start/stop rain
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_RIGHT_BUTTON) {
            isRaining = true;
        } else if (button == GLUT_LEFT_BUTTON) {
            isRaining = false;
        }
    }
}

struct Color {
    float r, g, b;
};

Color skyDay = {0.53f, 0.81f, 0.92f};
Color skyNight = {0.0f, 0.05f, 0.2f};
Color groundDay = {0.4f, 0.7f, 0.2f};
Color groundNight = {0.1f, 0.15f, 0.1f};
Color riverColorDay = {0.2f, 0.6f, 0.8f};
Color riverColorNight = {0.1f, 0.2f, 0.3f};

void drawCircle(float cx, float cy, float r, int segments, Color c) {
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        glVertex2f(cx + r * cosf(angle), cy + r * sinf(angle));
    }
    glEnd();
}

void drawSunMoon() {
    if (isDaytime) {
        drawCircle(900 - sunMoonPos * 800, 500, 40, 32, {1.0f, 0.9f, 0.1f});
    } else {
        drawCircle(100 + sunMoonPos * 800, 500, 35, 32, {0.9f, 0.9f, 0.8f});
        drawCircle(110 + sunMoonPos * 800, 510, 8, 16, {0.7f, 0.7f, 0.7f});
        drawCircle(90 + sunMoonPos * 800, 490, 5, 16, {0.7f, 0.7f, 0.7f});
    }
}

void drawClouds() {
    for (int i = 0; i < 4; i++) {
        float x = fmod(cloudPos + i * 250, 1100) - 100;
        drawCircle(x, 450, 20, 16, {1.0f, 1.0f, 1.0f});
        drawCircle(x + 15, 460, 25, 16, {1.0f, 1.0f, 1.0f});
        drawCircle(x + 40, 450, 20, 16, {1.0f, 1.0f, 1.0f});
        drawCircle(x + 25, 435, 25, 16, {1.0f, 1.0f, 1.0f});
    }
}

void drawMountains() {
    glBegin(GL_TRIANGLES);
    glColor3f(isDaytime ? 0.3f : 0.1f, isDaytime ? 0.5f : 0.15f, isDaytime ? 0.3f : 0.1f);

    // Original 5 mountains
    for (int i = 0; i < 5; i++) {
        float x = i * 250 - 50;
        glVertex2f(x, 185);
        glVertex2f(x + 125, 300);
        glVertex2f(x + 250, 185);
    }

    glEnd();
}

void drawWindmill() {
    float x = 400; // Position behind the buildings
    float y = 185; // Ground level

    // Windmill tower
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f); // Gray color
    glVertex2f(x - 10, y);
    glVertex2f(x + 10, y);
    glVertex2f(x + 5, y + 200);
    glVertex2f(x - 5, y + 200);
    glEnd();

    // Windmill head (rotating part)
    glPushMatrix();
    glTranslatef(x, y + 200, 0);
    glRotatef(windmillAngle, 0, 0, 1);

    // Blades
    for (int i = 0; i < 4; i++) {
        glRotatef(90, 0, 0, 1);
        glBegin(GL_TRIANGLES);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex2f(0, 0);
        glVertex2f(50, 10);
        glVertex2f(100, 0);
        glEnd();
    }

    // Center of rotation
    drawCircle(0, 0, 10, 16, {0.3f, 0.3f, 0.3f});

    glPopMatrix();
}

void drawBuildings() {
    // Generic buildings
    for (int i = 0; i < 3; i++) {
        float x = 100 + i * 180;
        glBegin(GL_QUADS);
        glColor3f(0.6f, 0.6f, 0.7f); // Changed building color
        glVertex2f(x, 185); glVertex2f(x + 100, 185);
        glVertex2f(x + 100, 350); glVertex2f(x, 350);
        glEnd();

        // Windows on the buildings
        glColor3f(0.8f, 0.9f, 1.0f); // Window color
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 2; ++k) {
                glBegin(GL_QUADS);
                glVertex2f(x + 15 + k * 40, 200 + j * 30);
                glVertex2f(x + 35 + k * 40, 200 + j * 30);
                glVertex2f(x + 35 + k * 40, 220 + j * 30);
                glVertex2f(x + 15 + k * 40, 220 + j * 30);
                glEnd();
            }
        }
    }
}

void drawHospital() {
    float x = 650;
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.8f, 0.9f);  // light blueish hospital
    glVertex2f(x, 185); glVertex2f(x + 120, 185);
    glVertex2f(x + 120, 360); glVertex2f(x, 360);
    glEnd();

    // Red cross
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x + 50, 300); glVertex2f(x + 70, 300);
    glVertex2f(x + 70, 340); glVertex2f(x + 50, 340);
    glVertex2f(x + 40, 315); glVertex2f(x + 80, 315);
    glVertex2f(x + 80, 325); glVertex2f(x + 40, 325);
    glEnd();

    // Windows
    glColor3f(0.6f, 0.8f, 1.0f);
    for (int i = 0; i < 3; ++i) {
        float y = 200 + i * 40;
        glBegin(GL_QUADS);
        glVertex2f(x + 20, y); glVertex2f(x + 45, y);
        glVertex2f(x + 45, y + 25); glVertex2f(x + 20, y + 25);
        glVertex2f(x + 75, y); glVertex2f(x + 100, y);
        glVertex2f(x + 100, y + 25); glVertex2f(x + 75, y + 25);
        glEnd();
    }
}

void drawMosque() {
    float x = 800; // Position to the right of the hospital
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.9f, 0.8f); // Light beige mosque
    glVertex2f(x, 185); glVertex2f(x + 100, 185);
    glVertex2f(x + 100, 350); glVertex2f(x, 350);
    glEnd();

    // Dome
    drawCircle(x + 50, 370, 30, 32, {0.7f, 0.8f, 0.6f});

    // Minaret
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.8f, 0.7f);
    glVertex2f(x + 80, 185); glVertex2f(x + 90, 185);
    glVertex2f(x + 90, 420); glVertex2f(x + 80, 420);
    glEnd();

    // Minaret top
    drawCircle(x + 85, 425, 10, 16, {0.6f, 0.7f, 0.5f});
}

void drawTrain() {
    glPushMatrix();
    glTranslatef(trainPos, 190.0f, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.3f);
    glVertex2f(0, 0); glVertex2f(150, 0); glVertex2f(150, 70); glVertex2f(0, 70);
    glColor3f(0.3f, 0.3f, 0.35f);
    glVertex2f(150, 0); glVertex2f(200, 0); glVertex2f(200, 90); glVertex2f(150, 90);
    glEnd();

    Color windowColor = isDaytime ? Color{0.7f, 0.8f, 1.0f} : Color{0.9f, 0.9f, 0.5f};
    drawCircle(40, 50, 12, 16, windowColor);
    drawCircle(90, 50, 12, 16, windowColor);
    drawCircle(175, 60, 10, 16, windowColor);

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(220 + i * 120, 0, 0);
        glBegin(GL_QUADS);
        glColor3f(0.2f, 0.2f, 0.25f);
        glVertex2f(0, 0); glVertex2f(100, 0); glVertex2f(100, 60); glVertex2f(0, 60);
        glEnd();
        drawCircle(25, -10, 15, 16, {0.1f, 0.1f, 0.1f});
        drawCircle(75, -10, 15, 16, {0.1f, 0.1f, 0.1f});
        drawCircle(25, 40, 10, 16, windowColor);
        drawCircle(75, 40, 10, 16, windowColor);
        glPopMatrix();
    }

    glPopMatrix();
}

void drawBoat() {
    glPushMatrix();
    glTranslatef(boatPos, 0, 0);

    // Boat hull
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.35f, 0.2f); // Brown wooden color
    glVertex2f(0, 50);
    glVertex2f(120, 50);
    glVertex2f(100, 80);
    glVertex2f(20, 80);
    glEnd();

    // Cabin
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.5f, 0.3f);
    glVertex2f(30, 80);
    glVertex2f(80, 80);
    glVertex2f(80, 110);
    glVertex2f(30, 110);
    glEnd();

    // Window
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex2f(40, 90);
    glVertex2f(70, 90);
    glVertex2f(70, 100);
    glVertex2f(40, 100);
    glEnd();

    // Mast
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.3f, 0.2f);
    glVertex2f(60, 110);
    glVertex2f(62, 110);
    glVertex2f(62, 160);
    glVertex2f(60, 160);
    glEnd();

    // Sail
    glBegin(GL_TRIANGLES);
    glColor3f(0.95f, 0.95f, 0.95f);
    glVertex2f(62, 120);
    glVertex2f(62, 160);
    glVertex2f(100, 140);
    glEnd();

    glPopMatrix();
}

void drawBridge() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.35f);
    glVertex2f(0, 170); glVertex2f(1000, 170); glVertex2f(1000, 190); glVertex2f(0, 190);
    glEnd();
}

void drawTracks() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(0, 185); glVertex2f(1000, 185); glVertex2f(1000, 230); glVertex2f(0, 230);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(0, 220); glVertex2f(1000, 220);
    glVertex2f(0, 195); glVertex2f(1000, 195);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.35f, 0.2f);
    for (int i = 0; i < 1000; i += 40) {
        glVertex2f(i, 190); glVertex2f(i + 30, 190);
        glVertex2f(i + 30, 225); glVertex2f(i, 225);
    }
    glEnd();
}

void drawRiver() {
    glBegin(GL_QUADS);
    glColor3fv(isDaytime ? &riverColorDay.r : &riverColorNight.r);
    glVertex2f(0, 0);
    glVertex2f(1000, 0);
    glVertex2f(1000, 170);
    glVertex2f(0, 170);
    glEnd();

    // Add some subtle wavy lines for the water effect
    glColor3f(isDaytime ? 0.2f * 1.1f : 0.1f * 1.1f,
              isDaytime ? 0.6f * 1.1f : 0.2f * 1.1f,
              isDaytime ? 0.8f * 1.1f : 0.3f * 1.1f);
    glLineWidth(1.5);
    glBegin(GL_LINES);
    for (int i = 0; i < 1000; i += 20) {
        glVertex2f(i, 50 + 10 * sinf(i * 0.05));
        glVertex2f(i + 15, 50 + 10 * sinf((i + 15) * 0.05));
        glVertex2f(i + 5, 100 + 8 * sinf((i + 5) * 0.06 + 1));
        glVertex2f(i + 20, 100 + 8 * sinf((i + 20) * 0.06 + 1));
    }
    glEnd();
    glLineWidth(1); // Reset line width
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Sky gradient
    glBegin(GL_QUADS);
    glColor3fv(isDaytime ? &skyDay.r : &skyNight.r);
    glVertex2f(0, 600); glVertex2f(1000, 600);
    glColor3f(isDaytime ? skyDay.r * 0.8 : skyNight.r * 1.2,
              isDaytime ? skyDay.g * 0.8 : skyNight.g * 1.2,
              isDaytime ? skyDay.b * 0.8 : skyNight.b * 1.2);
    glVertex2f(1000, 185); glVertex2f(0, 185);
    glEnd();

    drawSunMoon();
    drawClouds();
    drawMountains();
    drawBuildings();
    drawWindmill(); // Draw the windmill behind the buildings
    drawHospital();
    drawMosque();

    drawRiver(); // Draw the river before the ground and tracks

    // Draw the boat on the river
    drawBoat();

    glBegin(GL_QUADS);
    glColor3fv(isDaytime ? &groundDay.r : &groundNight.r);
    glVertex2f(0, 170); glVertex2f(1000, 170); glVertex2f(1000, 185); glVertex2f(0, 185);
    glEnd();

    drawBridge();
    drawTracks();
    drawTrain();
    drawRain(); // Draw rain
    drawStars();
    drawAirplane(); // Draw the airplane
    glutSwapBuffers();
}

void update(int value) {
    trainPos += trainSpeed;
    if (trainPos > 1200.0f) trainPos = -500.0f;

    cloudPos += 0.3f;
    if (cloudPos > 1100) cloudPos = 0;

    if (isDaytime && sunMoonPos > 0) sunMoonPos -= 0.01f;
    if (!isDaytime && sunMoonPos < 1) sunMoonPos += 0.01f;

    boatPos += boatSpeed;
    if (boatPos > 1200.0f) boatPos = -200.0f;

    updateRain(); // Update rain

    // Update airplane position
    airplanePos += airplaneSpeed;
    if (airplanePos > 1000.0f) airplanePos = -200.0f; // Reset airplane position

    // Update windmill rotation
    windmillAngle += 1.0f;
    if (windmillAngle > 360.0f) windmillAngle -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'd': case 'D':
            isDaytime = true;     // Set to day view explicitly
            break;
        case 'n': case 'N':
            isDaytime = false;    // Set to night view explicitly
            break;
        case '+':
            trainSpeed = fmin(5.0f, trainSpeed + 0.2f);
            boatSpeed = fmin(3.0f, boatSpeed + 0.1f);
            break;
        case '-':
            trainSpeed = fmax(0.5f, trainSpeed - 0.2f);
            boatSpeed = fmax(0.3f, boatSpeed - 0.1f);
            break;
        case ' ':
            trainSpeed = (trainSpeed == 0) ? 2.0f : 0.0f;
            boatSpeed = (boatSpeed == 0) ? 1.0f : 0.0f;
            break;
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 600);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Railway with Hospital and Mosque");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse); // Set the mouse callback function
    glutTimerFunc(0, update, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    initRain(); // Initialize rain data
    initStars();
    glutMainLoop();
    return 0;
}
