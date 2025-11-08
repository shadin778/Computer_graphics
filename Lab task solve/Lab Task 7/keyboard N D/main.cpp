//scene 1 : #include <GL/glut.h>
#include <cmath>

// Globals
float trainX = 0;
bool trainMoving = true;
float minuteAngle = 0.0f;
float hourAngle = 0.0f;
bool isDay = false;
bool sunRising = false;
float sunY = 300.0f;
float carX = 0;
float carY = 145;
float Car2X = -400;

float cloudX1 = -150.0f;  // Starting offscreen left
float cloudX2 = -400.0f;
float cloudX3 = -700.0f;

float windmill_angle = 0.0f;

// Utility Functions
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; ++i) {
        float theta = 2.0f * 3.1416f * i / 100;
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}


void drawMountains_A() {
    glBegin(GL_TRIANGLES);

    // Mountain 1
    glColor3f(0.3f, 0.2f, 0.1f);
    glVertex2f(-100, 300);
    glVertex2f(50, 430);
    glVertex2f(200, 300);

    // Mountain 2 (tallest)
    glColor3f(0.4f, 0.26f, 0.13f);
    glVertex2f(100, 300);
    glVertex2f(250, 450);
    glVertex2f(400, 300);

    // Mountain 3
    glColor3f(0.35f, 0.25f, 0.15f);
    glVertex2f(350, 300);
    glVertex2f(500, 420);
    glVertex2f(650, 300);

    // Mountain 4
    glColor3f(0.38f, 0.28f, 0.14f);
    glVertex2f(600, 300);
    glVertex2f(750, 460);
    glVertex2f(900, 300);

    // Mountain 5
    glColor3f(0.42f, 0.30f, 0.16f);
    glVertex2f(850, 300);
    glVertex2f(1000, 430);
    glVertex2f(1150, 300);

    glEnd();
}


void drawplatform_A() {
    glColor3f(1.0f, 1.0f, 0.0f); // grass green
    glBegin(GL_POLYGON);
    glVertex2f(0, 270);    // left bottom (railway track base)
    glVertex2f(1000, 270); // right bottom
    glVertex2f(1000, 300); // right top (bottom of mountains)
    glVertex2f(0, 300);    // left top
    glEnd();
}



// Railway Track
void drawRailwayTrack_A() {
    //Track base
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(0, 270);
    glVertex2f(1000, 270);
    glVertex2f(1000, 250);
    glVertex2f(0, 250);
    glEnd();

    //sleepers
    glColor3f(0.3, 0.2, 0.1);
    for (int i = 0; i < 1000; i += 20) {
        glBegin(GL_LINES);
        glVertex2f(i, 250);
        glVertex2f(i, 270);
        glEnd();
    }

    //rails
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_LINES);
    glVertex2f(0, 268); glVertex2f(1000, 268);
    glVertex2f(0, 252); glVertex2f(1000, 252);
    glEnd();
}


// Train
void drawTrain_A() {
    float baseY = 270;
    for (int i = 0; i < 5; ++i) {
        float cx = trainX + i * 80;

        // Coach body
        glColor3f(0.2, 0.2, 0.8);
        glBegin(GL_POLYGON);
        glVertex2f(cx, baseY);
        glVertex2f(cx + 70, baseY);
        glVertex2f(cx + 70, baseY + 40);
        glVertex2f(cx, baseY + 40);
        glEnd();

        // Roof
        glColor3f(0.1, 0.1, 0.5);
        glBegin(GL_POLYGON);
        glVertex2f(cx, baseY + 40);
        glVertex2f(cx + 70, baseY + 40);
        glVertex2f(cx + 70, baseY + 45);
        glVertex2f(cx, baseY + 45);
        glEnd();

        // Windows
        glColor3f(0.9, 0.9, 1.0);
        for (int j = 0; j < 3; ++j) {
            float wx = cx + 10 + j * 20;
            glBegin(GL_POLYGON);
            glVertex2f(wx, baseY + 20);
            glVertex2f(wx + 10, baseY + 20);
            glVertex2f(wx + 10, baseY + 35);
            glVertex2f(wx, baseY + 35);
            glEnd();
        }

        // Wheels
        glColor3f(0, 0, 0);
        drawCircle(cx + 15, baseY, 5);
        drawCircle(cx + 55, baseY, 5);
    }

    // Engine
    float x = trainX + 5 * 80;

    glColor3f(0.7, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(x, baseY);
    glVertex2f(x + 70, baseY);
    glVertex2f(x + 70, baseY + 50);
    glVertex2f(x, baseY + 50);
    glEnd();

    // chimney
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(x + 50, baseY + 50);
    glVertex2f(x + 60, baseY + 50);
    glVertex2f(x + 60, baseY + 70);
    glVertex2f(x + 50, baseY + 70);
    glEnd();

    // Slanted nose at the front (right side)
    glColor3f(0.5, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 70, baseY);
    glVertex2f(x + 90, baseY);
    glVertex2f(x + 70, baseY + 30);
    glEnd();

    // Engine windows
    glColor3f(0.9, 0.9, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x + 5, baseY + 30);
    glVertex2f(x + 25, baseY + 30);
    glVertex2f(x + 25, baseY + 45);
    glVertex2f(x + 5, baseY + 45);
    glEnd();

    // Engine wheels
    glColor3f(0, 0, 0);
    drawCircle(x + 15, baseY, 6);
    drawCircle(x + 55, baseY, 6);
}





// Station
void drawStation_A() {
    // Platform base
    glColor3f(0.5f, 0.5f, 0.5f); // Concrete grey
    glBegin(GL_POLYGON);
    glVertex2f(220, 275);
    glVertex2f(580, 275);
    glVertex2f(580, 285);
    glVertex2f(220, 285);
    glEnd();

    // Main building block
    glColor3f(0.15f, 0.15f, 0.15f); // Modern dark grey
    glBegin(GL_POLYGON);
    glVertex2f(240, 285);
    glVertex2f(560, 285);
    glVertex2f(560, 385);
    glVertex2f(240, 385);
    glEnd();

    // Bigger window 1 (lower position)
    glColor3f(0.86f, 0.86f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(260, 355);  // Left
    glVertex2f(320, 355);  // Right
    glVertex2f(320, 315);  // Bottom right
    glVertex2f(260, 315);  // Bottom left
    glEnd();

    // Bigger window 2 (lower position)
    glBegin(GL_POLYGON);
    glVertex2f(480, 355);
    glVertex2f(540, 355);
    glVertex2f(540, 315);
    glVertex2f(480, 315);
    glEnd();

    // Entrance door
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(360, 285);
    glVertex2f(440, 285);
    glVertex2f(440, 365);
    glVertex2f(360, 365);
    glEnd();

    // Door mid-line
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
    glVertex2f(400, 285);
    glVertex2f(400, 365);
    glEnd();

    // Roof top slab
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(235, 385);
    glVertex2f(565, 385);
    glVertex2f(565, 395);
    glVertex2f(235, 395);
    glEnd();

    // Station name boar
    glColor3f(0.0f, 0.2f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(300, 405);
    glVertex2f(500, 405);
    glVertex2f(500, 425);
    glVertex2f(300, 425);
    glEnd();

    // Station name text
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(315, 407);
    const char* stationName = "HILLSIDE STATION";
    for (int i = 0; stationName[i] != '\0'; ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stationName[i]);
}


void drawHouse_A(float x, float y) {
    // Base
    glColor3f(0.1f, 0.1f, 0.4f); // Blue base
    glBegin(GL_POLYGON);
    glVertex2f(x - 5, y - 10);
    glVertex2f(x + 105, y - 10);
    glVertex2f(x + 100, y);
    glVertex2f(x, y);
    glEnd();

    // Main Body
    glColor3f(0.7f, 0.7f, 0.75f); // Light gray
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 100, y);
    glVertex2f(x + 100, y + 60);
    glVertex2f(x, y + 60);
    glEnd();

    // Roof
    glColor3f(0.95f, 0.85f, 0.4f); // Darker gray
    glBegin(GL_POLYGON);
    glVertex2f(x - 10, y + 60);
    glVertex2f(x + 110, y + 60);
    glVertex2f(x + 100, y + 80);
    glVertex2f(x, y + 80);
    glEnd();

    // Door
    glColor3f(0.5f, 0.3f, 0.1f); // Brown door
    glBegin(GL_POLYGON);
    glVertex2f(x + 40, y);
    glVertex2f(x + 60, y);
    glVertex2f(x + 60, y + 35);
    glVertex2f(x + 40, y + 35);
    glEnd();

    // Windows
    glColor3f(0.6f, 0.85f, 1.0f); // Blue-tinted windows
    glBegin(GL_POLYGON);
    glVertex2f(x + 10, y + 35);
    glVertex2f(x + 30, y + 35);
    glVertex2f(x + 30, y + 55);
    glVertex2f(x + 10, y + 55);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x + 70, y + 35);
    glVertex2f(x + 90, y + 35);
    glVertex2f(x + 90, y + 55);
    glVertex2f(x + 70, y + 55);
    glEnd();
}


void drawFence_A(float startX, float endX, float baseY) {
    float postWidth = 5.0f;
    float postHeight = 30.0f;
    float spacing = 15.0f;

    glColor3f(0.6f, 0.4f, 0.2f); // Wooden brown

    // Draw vertical posts
    for (float x = startX; x <= endX; x += spacing) {
        glBegin(GL_POLYGON);
        glVertex2f(x, baseY);
        glVertex2f(x + postWidth, baseY);
        glVertex2f(x + postWidth, baseY + postHeight);
        glVertex2f(x, baseY + postHeight);
        glEnd();
    }

    // Draw two horizontal rails
    glBegin(GL_QUADS);
    glVertex2f(startX, baseY + 10);
    glVertex2f(endX, baseY + 10);
    glVertex2f(endX, baseY + 13);
    glVertex2f(startX, baseY + 13);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(startX, baseY + 22);
    glVertex2f(endX, baseY + 22);
    glVertex2f(endX, baseY + 25);
    glVertex2f(startX, baseY + 25);
    glEnd();
}


void drawGrass_A() {
    if (isDay)
        glColor3f(0.15f, 0.5f, 0.15f);  // Daytime bright green
    else
        glColor3f(0.05f, 0.2f, 0.05f);  // Nighttime dark green

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(1000, 0);
    glVertex2f(1000, 300);
    glVertex2f(0, 300);
    glEnd();
}


void drawBench_A(float x, float y, float scale = 1.0f) {
    // Bench seat (main plank)
    glColor3f(0.55f, 0.27f, 0.07f); // Brown wood color
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 40 * scale, y);
    glVertex2f(x + 40 * scale, y + 5 * scale);
    glVertex2f(x, y + 5 * scale);
    glEnd();

    // Bench back
    glBegin(GL_POLYGON);
    glVertex2f(x, y + 5 * scale);
    glVertex2f(x + 40 * scale, y + 5 * scale);
    glVertex2f(x + 40 * scale, y + 15 * scale);
    glVertex2f(x, y + 15 * scale);
    glEnd();

    // Bench legs (left)
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 5 * scale, y);
    glVertex2f(x + 5 * scale, y - 10 * scale);
    glVertex2f(x, y - 10 * scale);
    glEnd();

    // Bench legs (right)
    glBegin(GL_POLYGON);
    glVertex2f(x + 35 * scale, y);
    glVertex2f(x + 40 * scale, y);
    glVertex2f(x + 40 * scale, y - 10 * scale);
    glVertex2f(x + 35 * scale, y - 10 * scale);
    glEnd();
}


void drawTree_A() {
    // Tree base (brown rectangle)
    glColor3f(0.55f, 0.27f, 0.07f); // Brown
    glBegin(GL_QUADS);
    glVertex2f(855.5f, 228.5f);    // C
    glVertex2f(868.5f, 228.5f);    // D
    glVertex2f(868.5f, 263.5f);    // E
    glVertex2f(855.5f, 263.5f);    // F
    glEnd();

    // Lower triangle leaves (dark green)
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(827.0f, 263.5f);    // G
    glVertex2f(894.0f, 263.5f);    // H
    glVertex2f(862.0f, 311.5f);    // I
    glEnd();

    // Middle triangle leaves (green)
    glBegin(GL_TRIANGLES);
    glVertex2f(834.0f, 287.5f);    // J
    glVertex2f(890.0f, 287.5f);    // K
    glVertex2f(862.0f, 335.5f);    // L
    glEnd();

    // Top triangle leaves (light green)
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(841.0f, 311.5f);    // M
    glVertex2f(883.0f, 311.5f);    // N
    glVertex2f(862.0f, 359.5f);    // O
    glEnd();
}


void drawRoad_A() {
    // Road base
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 80);
    glVertex2f(1000, 80);
    glVertex2f(1000, 170);
    glVertex2f(0, 170);
    glEnd();

    // Lane markings (white dashed lines)
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3);
    for (int i = 0; i < 1000; i += 80) {
        glBegin(GL_LINES);
        glVertex2f(i, 125);      // start of dash (middle of road)
        glVertex2f(i + 40, 125); // end of dash
        glEnd();
    }
}

void drawStars_A() {
    if (isDay) return;

    glColor3f(1.0f, 1.0f, 1.0f);  // White stars
    glPointSize(2.0f);
    glBegin(GL_POINTS);

    int starPositions[][2] = {
        {100, 550}, {150, 530}, {200, 580}, {250, 520}, {300, 560},
        {350, 545}, {400, 575}, {450, 510}, {500, 590}, {550, 525},
        {600, 570}, {650, 535}, {700, 580}, {750, 520}, {800, 550},
        {850, 530}, {900, 580}, {950, 540}, {990, 560}
    };

    for (auto& star : starPositions) {
        glVertex2i(star[0], star[1]);
    }

    glEnd();
}

void drawMoon_A() {
    if (isDay) return;

    glColor3f(0.95f, 0.95f, 0.85f);
    drawCircle(300, 500, 25);  // Position and radius
}

//  street lights along the road
void drawStreetLights_A() {
    for (int i = 100; i < 900; i += 150) {
        // Pole
        glColor3f(0.3f, 0.3f, 0.3f); // Dark gray
        glBegin(GL_POLYGON);
        glVertex2f(i, 170);
        glVertex2f(i + 5, 170);
        glVertex2f(i + 5, 220);
        glVertex2f(i, 220);
        glEnd();

        // Lamp head
        glColor3f(0.7f, 0.7f, 0.7f); // Light gray
        glBegin(GL_POLYGON);
        glVertex2f(i - 5, 220);
        glVertex2f(i + 10, 220);
        glVertex2f(i + 10, 230);
        glVertex2f(i - 5, 230);
        glEnd();

        // Light (only visible at night)
        if (!isDay) {
            glColor3f(1.0f, 1.0f, 0.8f); // Yellowish white
            glBegin(GL_TRIANGLES);
            glVertex2f(i - 5, 220);
            glVertex2f(i + 10, 220);
            glVertex2f(i + 2.5, 190);
            glEnd();
        }
    }
}


// Clock & Building
void drawClock_A(float cx, float cy, float radius) {
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(cx, cy, radius);

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 100; ++i) {
        float theta = 2.0f * 3.1416f * i / 100;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();

    // Hour hand
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + 0.5 * radius * cos(hourAngle), cy + 0.5 * radius * sin(hourAngle));
    glEnd();

    // Minute hand
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + 0.75 * radius * cos(minuteAngle), cy + 0.75 * radius * sin(minuteAngle));
    glEnd();

    glLineWidth(1);
}

void drawClockTower_A() {
    // Tower base
    glColor3f(0.25f, 0.28f, 0.32f);
    glBegin(GL_POLYGON);
    glVertex2f(580, 275);
    glVertex2f(610, 275);
    glVertex2f(610, 405);
    glVertex2f(580, 405);
    glEnd();

    // Clock housing
    glColor3f(0.6f, 0.65f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(570, 405);
    glVertex2f(620, 405);
    glVertex2f(620, 445);
    glVertex2f(570, 445);
    glEnd();

    // Roof
    glColor3f(0.1f, 0.1f, 0.3f);
    glBegin(GL_TRIANGLES);
    glVertex2f(560, 445);
    glVertex2f(630, 445);
    glVertex2f(595, 475);
    glEnd();

    // Clock face
    drawClock_A(595, 425, 15);
}



void drawCar_A() {
     float x = carX;
    float y = carY;
    // Car body
    glColor3f(0.8f, 0.1f, 0.1f);  // Red
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 80, y);
    glVertex2f(x + 80, y + 30);
    glVertex2f(x, y + 30);
    glEnd();

    // Roof
    glColor3f(0.8f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(x + 15, y + 30);
    glVertex2f(x + 65, y + 30);
    glVertex2f(x + 55, y + 50);
    glVertex2f(x + 25, y + 50);
    glEnd();

    // Windows
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x + 20, y + 35);
    glVertex2f(x + 40, y + 35);
    glVertex2f(x + 40, y + 45);
    glVertex2f(x + 20, y + 45);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x + 45, y + 35);
    glVertex2f(x + 60, y + 35);
    glVertex2f(x + 60, y + 45);
    glVertex2f(x + 45, y + 45);
    glEnd();

    // Wheels
    glColor3f(0, 0, 0);
    drawCircle(x + 20, y, 10);
    drawCircle(x + 60, y, 10);
}

void drawCar2_A() {
    float x = Car2X;
    float y = carY;

    // Car body - blue
    glColor3f(0.1f, 0.1f, 0.8f);  // Blue
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 80, y);
    glVertex2f(x + 80, y + 30);
    glVertex2f(x, y + 30);
    glEnd();

    // Roof - blue
    glColor3f(0.1f, 0.1f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(x + 15, y + 30);
    glVertex2f(x + 65, y + 30);
    glVertex2f(x + 55, y + 50);
    glVertex2f(x + 25, y + 50);
    glEnd();

    // Windows - light blue
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x + 20, y + 35);
    glVertex2f(x + 40, y + 35);
    glVertex2f(x + 40, y + 45);
    glVertex2f(x + 20, y + 45);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(x + 45, y + 35);
    glVertex2f(x + 60, y + 35);
    glVertex2f(x + 60, y + 45);
    glVertex2f(x + 45, y + 45);
    glEnd();

    // Wheels
    glColor3f(0, 0, 0);
    drawCircle(x + 20, y, 10);
    drawCircle(x + 60, y, 10);
}

void drawWindmill_A() {
    float x = 175.0f;  // Position
    float y = 300.0f;  // Base of windmill at ground level

    // Tower (simple rectangle)
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 10, y);
    glVertex2f(x + 10, y);
    glVertex2f(x + 10, y + 100);
    glVertex2f(x - 10, y + 100);
    glEnd();

    // Hub (center of blades)
    glColor3f(0.4f, 0.4f, 0.4f);
    drawCircle(x, y + 100, 5);

    // Rotating Blades (4 blades)
    glPushMatrix();
    glTranslatef(x, y + 100, 0);
    glRotatef(windmill_angle, 0, 0, 1);

    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 4; i++) {
        glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(40, 5);
        glVertex2f(60, 0);
        glVertex2f(40, -5);
        glEnd();
        glRotatef(90, 0, 0, 1); // Rotate 90 degrees for next blade
    }
    glPopMatrix();
}

void drawCloud_A(float cx, float cy) {
    glColor3f(1.0f, 1.0f, 1.0f);  // White cloud

    //multiple overlapping circles to form a cloud shape
    drawCircle(cx, cy, 20);
    drawCircle(cx + 25, cy + 10, 20);
    drawCircle(cx + 50, cy, 20);
    drawCircle(cx + 25, cy - 10, 20);
}


void drawSun_A() {
    if (!isDay) return;
    glColor3f(1.0f, 0.9f, 0.0f);
    drawCircle(800, sunY, 30);
}

// Main Display
void display() {
    if (isDay)
        glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
    else
        glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    if (isDay)
    {
    drawCloud_A(cloudX1, 520);
    drawCloud_A(cloudX2, 560);
    drawCloud_A(cloudX3, 530);
    }

    drawSun_A();
    drawMountains_A();

    drawGrass_A();
    drawplatform_A();
    drawRoad_A();



    // Grass below station/train
    drawRailwayTrack_A();

    drawBench_A(50, 285, 0.8f);
    drawBench_A(100, 285, 0.8f);
    drawBench_A(150, 285, 0.8f);

    // benches above the road
    drawBench_A(160, 180, 0.7f);
    drawBench_A(310, 180, 0.7f);
    drawBench_A(460, 180, 0.7f);
    drawBench_A(610, 180, 0.7f);
    drawBench_A(760, 180, 0.7f);
    drawStars_A();
    drawMoon_A();
    drawStation_A();
    drawStreetLights_A();      // street lights along road
    drawClockTower_A();
    drawWindmill_A();
    glPushMatrix();
    glTranslatef(-120.0f, 0.0f, 0.0f);  // Adjust position as needed
    drawWindmill_A();
    glPopMatrix();
    drawTrain_A();
    drawTree_A();
    drawStreetLights_A();

    // Draw second tree using translation
    glPushMatrix();
    glTranslatef(50.0f, 0.0f, 0.0f);

    drawTree_A();
    glPopMatrix();

    // Draw third tree using translation
    glPushMatrix();
    glTranslatef(100.0f, 0.0f, 0.0f);
    drawTree_A();
    glPopMatrix();
    drawCar_A();
    drawCar2_A();
    drawFence_A(0, 1000, 50);
    drawHouse_A(50, 20); // 1st house
    drawHouse_A(200, 20); // 2nd house

    glutSwapBuffers();
}

// Animation Update
void update(int value) {
     if (trainMoving) {
        trainX += 1;
        if (trainX > 1000) trainX = -550;
    }

    cloudX1 += 0.5f;
    cloudX2 += 0.7f;
    cloudX3 += 0.6f;

    // Reset when  width 1000)
    if (cloudX1 > 1100) cloudX1 = -150;

    if (cloudX2 > 1100) cloudX2 = -150;
    if (cloudX3 > 1100) cloudX3 = -150;


    carX += 2;  // Move car faster than train
    if (carX > 1000) carX = -100;  // Reset once off screen

    Car2X += 2;
    if (Car2X > 1400) Car2X = -700;



    //clockhand
    minuteAngle -= 0.01f;
    hourAngle -= 0.0015f;

    //sun rise
    if (sunRising && sunY < 500.0f) {
        sunY += 0.5f;
        if (sunY >= 500.0f) sunRising = false;
    }

    windmill_angle += 2.0f;
    if (windmill_angle >= 360.0f)
    windmill_angle -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Reshape
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 600);
    glMatrixMode(GL_MODELVIEW);
}

void handleKeypress(unsigned char key, int x, int y) {
    if (key == 'D' || key == 'd') {
        if (!isDay) {
            isDay = true;
            sunRising = true;
        }
    }
    if (key == 'N' || key == 'n') {
        isDay = false;
        sunRising = false;
        sunY = 300.0f;
    }
}


void handleMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            trainMoving = false; // Stop train
        }
        if (button == GLUT_RIGHT_BUTTON) {
            trainMoving = true; // Start train
        }
    }
}

// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 500);
    glutCreateWindow("Train Overlapping Station Scene");

    glClearColor(0.53, 0.81, 0.98, 1.0); // Sky blue

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouse);

    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
//Scene 02: #include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// Global variables
bool isRaining = false;
bool isBoatMoving = true;
float trainX = 0;
float boatPos1 = 0.0f;
const float boatY1 = 40.0f; // Y position for Boat 1
float boatPos2 = 500.0f;
const float boatY2 = 70.0f; // Y position for Boat 2
float cloudOffset = 0.0f;
float rainDrops[200][2]; // Increased number of raindrops
// Sound and train control variables
bool isTrainMoving = true;
bool isTrainSoundPlaying = false;
// Airplane variables
float airplaneX = 1100.0f;  // Start from right edge
float airplaneY = 450.0f;

// Windmill variables
float windmillBladeAngle1 = 0.0f;
float windmillBladeAngle2 = 0.0f;
bool windmillsMoving = true;

// Stars for night mode
float stars[200][2]; // Increased number of stars

// Day/Night cycle variables (manual)
float currentHour = 12.0f; // Start at noon
bool lamppostsOn = false;
bool isNightTime = false;

// Car and road related variables
float carPositions[5] = {100.0f, 300.0f, 500.0f, 700.0f, 900.0f};
float carSpeeds[5] = {0.5f, 0.7f, 0.6f, 0.8f, 0.55f};
int carDirections[5] = {1, -1, 1, -1, 1}; // 1 for right, -1 for left
float busPosition = 600.0f;
float busSpeed = 0.4f;
int busDirection = -1;

// Constants for Y-coordinates
const float GROUND_LEVEL_Y = 250.0f;
const float RIVERSIDE_TOP_Y = 150.0f; // Top of the river bank
const float RIVER_BOTTOM_Y = 0.0f;    // Bottom of the river

const float BRIDGE_DECK_BASE_Y = GROUND_LEVEL_Y + 10.0f;
const float BRIDGE_DECK_TOP_Y = GROUND_LEVEL_Y + 20.0f;

const float ROAD_WIDTH = 25.0f;
const float ROAD_TOP_Y = BRIDGE_DECK_TOP_Y + 30.0f;
const float ROAD_BOTTOM_Y = ROAD_TOP_Y - ROAD_WIDTH;

// Train Bridge Constants
const float TRAIN_BRIDGE_DECK_Y = ROAD_TOP_Y + 50.0f; // Above the road
const float TRAIN_BRIDGE_HEIGHT = 20.0f;

const float RAILWAY_BASE_Y = TRAIN_BRIDGE_DECK_Y + TRAIN_BRIDGE_HEIGHT; // Railway on top of the train bridge deck


// Initialization functions
void initRain() {
    for (int i = 0; i < 200; i++) {
        rainDrops[i][0] = rand() % 1000;
        rainDrops[i][1] = rand() % 600;
    }
}

void initStars() {
    for (int i = 0; i < 200; i++) {
        stars[i][0] = rand() % 1000;
        stars[i][1] = GROUND_LEVEL_Y + rand() % (600 - (int)GROUND_LEVEL_Y);
    }
}

// Helper functions
void drawCircle(float cx, float cy, float r, int segments, float rCol, float gCol, float bCol) {
    glColor3f(rCol, gCol, bCol);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * float(i) / float(segments);
        glVertex2f(cx + r * cosf(angle), cy + r * sinf(angle));
    }
    glEnd();
}

void mixColors(float *result, const float *c1, const float *c2, float alpha) {
    result[0] = c1[0] * (1.0f - alpha) + c2[0] * alpha;
    result[1] = c1[1] * (1.0f - alpha) + c2[1] * alpha;
    result[2] = c1[2] * (1.0f - alpha) + c2[2] * alpha;
}

void getSkyColor(float hour, float *color) {
    float dawn[3] = {0.8f, 0.6f, 0.5f};
    float day[3] = {0.4f, 0.8f, 1.0f};
    float dusk[3] = {0.6f, 0.3f, 0.4f};
    // Black ash color: #383B39 -> R=56, G=59, B=57
    float night[3] = {56.0f/255.0f, 59.0f/255.0f, 57.0f/255.0f};

    if (hour >= 5.0f && hour < 10.0f) {
        float alpha = (hour - 5.0f) / 5.0f;
        mixColors(color, dawn, day, alpha);
    } else if (hour >= 10.0f && hour < 19.0f) {
        color[0] = day[0]; color[1] = day[1]; color[2] = day[2];
    } else if (hour >= 19.0f && hour < 22.0f) {
        float alpha = (hour - 19.0f) / 3.0f;
        mixColors(color, day, dusk, alpha);
    } else if (hour >= 22.0f && hour < 24.0f) {
        float alpha = (hour - 22.0f) / 2.0f;
        mixColors(color, dusk, night, alpha);
    } else if (hour >= 0.0f && hour < 5.0f) {
        float alpha = hour / 5.0f;
        mixColors(color, night, dawn, alpha);
    } else {
        color[0] = day[0]; color[1] = day[1]; color[2] = day[2];
    }
}

// Drawing scene elements
void drawSun() {
    float sunY;
    if (currentHour >= 5.0f && currentHour <= 19.0f) {
        sunY = 500 + 100 * sinf(currentHour / 24.0f * 2 * M_PI - M_PI / 2);
    } else {
        sunY = -100;
    }

    float sunBrightness = 1.0f;
    if (currentHour < 5.0f || currentHour > 20.0f) sunBrightness = 0.0f;
    else if (currentHour < 6.0f) sunBrightness = (currentHour - 5.0f);
    else if (currentHour > 19.0f) sunBrightness = (20.0f - currentHour);
    if (isRaining) sunBrightness = 0.0f;

    if (sunBrightness > 0.01f)
        drawCircle(850, sunY, 40, 50, sunBrightness, 0.8f * sunBrightness, 0.2f * sunBrightness);
}

void drawMoon() {
    float moonY;
    if (currentHour >= 20.0f || currentHour < 6.0f) {
        moonY = 500 + 100 * sinf(currentHour / 24.0f * 2 * M_PI + M_PI / 2);
    } else {
        moonY = -100;
    }

    float moonBrightness = 0.0f;
    if (currentHour >= 20.0f || currentHour < 6.0f) {
        moonBrightness = 0.8f;
    } else if (currentHour < 6.0f) {
        moonBrightness = (6.0f - currentHour) * 0.8f;
    } else if (currentHour > 19.0f) {
        moonBrightness = (currentHour - 19.0f) * 0.8f;
    }

    if (moonBrightness > 0.01f) {
        drawCircle(850, moonY, 35, 50, 0.9f * moonBrightness, 0.9f * moonBrightness, 0.8f * moonBrightness);
        drawCircle(860, moonY + 10, 8, 20, 0.7f * moonBrightness, 0.7f * moonBrightness, 0.7f * moonBrightness);
        drawCircle(840, moonY - 10, 6, 20, 0.7f * moonBrightness, 0.7f * moonBrightness, 0.7f * moonBrightness);
        drawCircle(850, moonY - 20, 5, 20, 0.7f * moonBrightness, 0.7f * moonBrightness, 0.7f * moonBrightness);
    }
}

void drawStars() {
    if (!isNightTime) return;
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 200; i++) {
        float brightness = 0.7f + 0.3f * sinf(glutGet(GLUT_ELAPSED_TIME) * 0.001f + i);
        glColor3f(brightness, brightness, brightness);
        glVertex2f(stars[i][0], stars[i][1]);
        if (i % 10 == 0) {
            glVertex2f(stars[i][0] + 1, stars[i][1]);
            glVertex2f(stars[i][0], stars[i][1] + 1);
            glVertex2f(stars[i][0] - 1, stars[i][1]);
            glVertex2f(stars[i][0], stars[i][1] - 1);
        }
    }
    glEnd();
}

void drawClouds() {
    float cloudBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f)
        cloudBrightnessFactor = 0.3f;
    if (isRaining) cloudBrightnessFactor *= 0.6f;

    float cloudColor[3] = {cloudBrightnessFactor, cloudBrightnessFactor, cloudBrightnessFactor};
    for (int i = 0; i < 3; i++) {
        float x = fmod(cloudOffset + i * 300, 1100) - 100;
        drawCircle(x, 500, 25, 20, cloudColor[0], cloudColor[1], cloudColor[2]);
        drawCircle(x + 30, 510, 30, 20, cloudColor[0], cloudColor[1], cloudColor[2]);
        drawCircle(x + 60, 500, 25, 20, cloudColor[0], cloudColor[1], cloudColor[2]);
    }
    if (isRaining) {
        for (int i = 0; i < 2; i++) {
            float x = fmod(cloudOffset + 150 + i * 400, 1100) - 100;
            drawCircle(x, 480, 30, 20, cloudColor[0], cloudColor[1], cloudColor[2]);
            drawCircle(x + 40, 490, 35, 20, cloudColor[0], cloudColor[1], cloudColor[2]);
            drawCircle(x + 80, 480, 30, 20, cloudColor[0], cloudColor[1], cloudColor[2]);
        }
    }
}

void drawMountains() {
    float mountainBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) {
        mountainBrightnessFactor = 0.4f;
    }
    if (isRaining) mountainBrightnessFactor *= 0.7f;

    glBegin(GL_TRIANGLES);
    glColor3f(0.3f * mountainBrightnessFactor, 0.5f * mountainBrightnessFactor, 0.2f * mountainBrightnessFactor);
    for (int i = 0; i < 8; i++) {
        int base = i * 150;
        glVertex2f(base, GROUND_LEVEL_Y);
        glVertex2f(base + 75, 350 + (GROUND_LEVEL_Y - 150));
        glVertex2f(base + 150, GROUND_LEVEL_Y);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.5f * mountainBrightnessFactor, 0.8f * mountainBrightnessFactor, 0.3f * mountainBrightnessFactor);
    for (int i = 0; i < 5; i++) {
        int base = i * 250;
        glVertex2f(base, GROUND_LEVEL_Y);
        glVertex2f(base + 125, 400 + (GROUND_LEVEL_Y - 150));
        glVertex2f(base + 250, GROUND_LEVEL_Y);
    }
    glEnd();
}

void drawTrees() {
    float treeBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) {
        treeBrightnessFactor = 0.5f;
    }
    if (isRaining) treeBrightnessFactor *= 0.7f;

    // Existing trees on the higher ground
    for (int i = 50; i < 950; i += 100) {
        // Draw trunk
        glColor3f(0.4f * treeBrightnessFactor, 0.2f * treeBrightnessFactor, 0.1f * treeBrightnessFactor);
        glBegin(GL_QUADS);
        glVertex2f(i, GROUND_LEVEL_Y); glVertex2f(i + 10, GROUND_LEVEL_Y);
        glVertex2f(i + 10, GROUND_LEVEL_Y + 30); glVertex2f(i, GROUND_LEVEL_Y + 30);
        glEnd();

        // Draw leaves
        drawCircle(i + 5, GROUND_LEVEL_Y + 50, 25, 10, 0.1f * treeBrightnessFactor, 0.5f * treeBrightnessFactor, 0.1f * treeBrightnessFactor);
        drawCircle(i - 5, GROUND_LEVEL_Y + 40, 20, 10, 0.1f * treeBrightnessFactor, 0.5f * treeBrightnessFactor, 0.1f * treeBrightnessFactor);
        drawCircle(i + 15, GROUND_LEVEL_Y + 40, 20, 10, 0.1f * treeBrightnessFactor, 0.5f * treeBrightnessFactor, 0.1f * treeBrightnessFactor);
    }

    // New trees between the road and river
    for (int i = 150; i < 850; i += 80) { // Adjust spacing as needed
        // Draw trunk
        glColor3f(0.4f * treeBrightnessFactor, 0.2f * treeBrightnessFactor, 0.1f * treeBrightnessFactor);
        glBegin(GL_QUADS);
        glVertex2f(i, RIVERSIDE_TOP_Y + 10);
        glVertex2f(i + 8, RIVERSIDE_TOP_Y + 10);
        glVertex2f(i + 8, RIVERSIDE_TOP_Y + 40);
        glVertex2f(i, RIVERSIDE_TOP_Y + 40);
        glEnd();

        // Draw leaves
        drawCircle(i + 4, RIVERSIDE_TOP_Y + 60, 20, 10, 0.1f * treeBrightnessFactor, 0.5f * treeBrightnessFactor, 0.1f * treeBrightnessFactor);
        drawCircle(i - 4, RIVERSIDE_TOP_Y + 50, 16, 10, 0.1f * treeBrightnessFactor, 0.5f * treeBrightnessFactor, 0.1f * treeBrightnessFactor);
        drawCircle(i + 12, RIVERSIDE_TOP_Y + 50, 16, 10, 0.1f * treeBrightnessFactor, 0.5f * treeBrightnessFactor, 0.1f * treeBrightnessFactor);
    }
}

void drawGround() {
    float groundBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) {
        groundBrightnessFactor = 0.4f;
    }
    if (isRaining) groundBrightnessFactor *= 0.7f;

    glColor3f(0.2f * groundBrightnessFactor, 0.8f * groundBrightnessFactor, 0.2f * groundBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(0, RIVERSIDE_TOP_Y);
    glVertex2f(1000, RIVERSIDE_TOP_Y);
    glVertex2f(1000, GROUND_LEVEL_Y);
    glVertex2f(0, GROUND_LEVEL_Y);
    glEnd();
}

void drawRiverside() {
    float groundBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) {
        groundBrightnessFactor = 0.4f;
    }
    if (isRaining) groundBrightnessFactor *= 0.7f;

    float darkGreenR = 0.2f * groundBrightnessFactor;
    float darkGreenG = 0.6f * groundBrightnessFactor;
    float darkGreenB = 0.2f * groundBrightnessFactor;

    glBegin(GL_TRIANGLES);
    glColor3f(darkGreenR, darkGreenG, darkGreenB);
    glVertex2f(0, GROUND_LEVEL_Y);
    glVertex2f(0, RIVERSIDE_TOP_Y);
    glVertex2f(400, RIVERSIDE_TOP_Y);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(darkGreenR * 0.8f, darkGreenG * 0.8f, darkGreenB * 0.8f);
    glVertex2f(0, RIVERSIDE_TOP_Y);
    glVertex2f(0, RIVER_BOTTOM_Y);
    glVertex2f(400, RIVER_BOTTOM_Y);
    glVertex2f(400, RIVERSIDE_TOP_Y);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(darkGreenR, darkGreenG, darkGreenB);
    glVertex2f(1000, GROUND_LEVEL_Y);
    glVertex2f(1000, RIVERSIDE_TOP_Y);
    glVertex2f(600, RIVERSIDE_TOP_Y);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(darkGreenR * 0.8f, darkGreenG * 0.8f, darkGreenB * 0.8f);
    glVertex2f(600, RIVERSIDE_TOP_Y);
    glVertex2f(600, RIVER_BOTTOM_Y);
    glVertex2f(1000, RIVER_BOTTOM_Y);
    glVertex2f(1000, RIVERSIDE_TOP_Y);
    glEnd();

    glColor3f(0.3f * groundBrightnessFactor, 0.5f * groundBrightnessFactor, 0.2f * groundBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(0, RIVERSIDE_TOP_Y);
    glVertex2f(1000, RIVERSIDE_TOP_Y);
    glVertex2f(1000, RIVERSIDE_TOP_Y + 5);
    glVertex2f(0, RIVERSIDE_TOP_Y + 5);
    glEnd();
}

void drawRiver() {
    float riverBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) {
        riverBrightnessFactor = 0.5f;
    }
    if (isRaining) riverBrightnessFactor *= 0.7f;

    glBegin(GL_QUADS);
    glColor3f(0.2f * riverBrightnessFactor, 0.6f * riverBrightnessFactor, 0.9f * riverBrightnessFactor);
    glVertex2f(0, RIVER_BOTTOM_Y); glVertex2f(1000, RIVER_BOTTOM_Y);
    glVertex2f(1000, RIVERSIDE_TOP_Y); glVertex2f(0, RIVERSIDE_TOP_Y);
    glEnd();
}

void drawBridge() {
    float bridgeBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) {
        bridgeBrightnessFactor = 0.6f;
    }
    if (isRaining) bridgeBrightnessFactor *= 0.7f;

    float bridgeColorR = 0.4f * bridgeBrightnessFactor;
    float bridgeColorG = 0.2f * bridgeBrightnessFactor;
    float bridgeColorB = 0.1f * bridgeBrightnessFactor;

    glBegin(GL_QUADS);
    glColor3f(bridgeColorR, bridgeColorG, bridgeColorB);
    glVertex2f(0, BRIDGE_DECK_TOP_Y); glVertex2f(1000, BRIDGE_DECK_TOP_Y);
    glVertex2f(1000, BRIDGE_DECK_BASE_Y); glVertex2f(0, BRIDGE_DECK_BASE_Y);
    glEnd();

    glColor3f(0.3f * bridgeBrightnessFactor, 0.3f * bridgeBrightnessFactor, 0.3f * bridgeBrightnessFactor);
    for (int i = 100; i < 900; i += 200) {
        glBegin(GL_QUADS);
        glVertex2f(i - 10, GROUND_LEVEL_Y); glVertex2f(i + 10, GROUND_LEVEL_Y);
        glVertex2f(i + 10, BRIDGE_DECK_BASE_Y); glVertex2f(i - 10, BRIDGE_DECK_BASE_Y);
        glEnd();

        glBegin(GL_LINE_STRIP);
        for (int j = 0; j <= 50; j++) {
            float angle = M_PI * float(j) / 50.0f;
            float archRadius = 50.0f;
            float x = i + archRadius * cosf(angle);
            float y = BRIDGE_DECK_BASE_Y + archRadius * sinf(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }

    glColor3f(0.5f * bridgeBrightnessFactor, 0.5f * bridgeBrightnessFactor, 0.5f * bridgeBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(0, BRIDGE_DECK_TOP_Y); glVertex2f(1000, BRIDGE_DECK_TOP_Y);
    glVertex2f(1000, BRIDGE_DECK_TOP_Y + 3); glVertex2f(0, BRIDGE_DECK_TOP_Y + 3);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0, BRIDGE_DECK_BASE_Y); glVertex2f(1000, BRIDGE_DECK_BASE_Y);
    glVertex2f(1000, BRIDGE_DECK_BASE_Y + 3); glVertex2f(0, BRIDGE_DECK_BASE_Y + 3);
    glEnd();

    for (int i = 10; i < 990; i += 20) {
        glBegin(GL_QUADS);
        glVertex2f(i, BRIDGE_DECK_BASE_Y + 3); glVertex2f(i + 2, BRIDGE_DECK_BASE_Y + 3);
        glVertex2f(i + 2, BRIDGE_DECK_TOP_Y); glVertex2f(i, BRIDGE_DECK_TOP_Y);
        glEnd();
    }
}

void drawRoad() {
    float roadBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) {
        roadBrightnessFactor = 0.5f;
    }
    if (isRaining) roadBrightnessFactor *= 0.8f;

    // Darker asphalt color
    glColor3f(0.2f * roadBrightnessFactor, 0.2f * roadBrightnessFactor, 0.2f * roadBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(0, ROAD_BOTTOM_Y);
    glVertex2f(1000, ROAD_BOTTOM_Y);
    glVertex2f(1000, ROAD_TOP_Y);
    glVertex2f(0, ROAD_TOP_Y);
    glEnd();

    // Road markings (white dashed line)
    glColor3f(0.9f * roadBrightnessFactor, 0.9f * roadBrightnessFactor, 0.9f * roadBrightnessFactor);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (float i = 0.0f; i < 1000.0f; i += 40.0f) { // Dash length + gap = 40
        glVertex2f(i, ROAD_BOTTOM_Y + ROAD_WIDTH / 2.0f);
        glVertex2f(i + 20.0f, ROAD_BOTTOM_Y + ROAD_WIDTH / 2.0f);
    }
    glEnd();
    glLineWidth(1.0f); // Reset line width
}

void drawTrainBridge() {
    float bridgeBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) {
        bridgeBrightnessFactor = 0.5f;
    }
    if (isRaining) bridgeBrightnessFactor *= 0.7f;

    // Bridge Deck
    glColor3f(0.45f * bridgeBrightnessFactor, 0.35f * bridgeBrightnessFactor, 0.25f * bridgeBrightnessFactor); // Darker brown
    glBegin(GL_QUADS);
    glVertex2f(0, TRAIN_BRIDGE_DECK_Y);
    glVertex2f(1000, TRAIN_BRIDGE_DECK_Y);
    glVertex2f(1000, TRAIN_BRIDGE_DECK_Y + TRAIN_BRIDGE_HEIGHT);
    glVertex2f(0, TRAIN_BRIDGE_DECK_Y + TRAIN_BRIDGE_HEIGHT);
    glEnd();

    // Bridge supports/pillars extending to the ground
    glColor3f(0.3f * bridgeBrightnessFactor, 0.3f * bridgeBrightnessFactor, 0.3f * bridgeBrightnessFactor); // Gray/concrete
    for (int i = 100; i < 900; i += 250) { // Pillars
        glBegin(GL_QUADS);
        glVertex2f(i - 15, GROUND_LEVEL_Y); // Start pillars from GROUND_LEVEL_Y
        glVertex2f(i + 15, GROUND_LEVEL_Y);
        glVertex2f(i + 15, TRAIN_BRIDGE_DECK_Y);
        glVertex2f(i - 15, TRAIN_BRIDGE_DECK_Y);
        glEnd();
    }

    // Additional side supports/beams on the deck for more detail
    glColor3f(0.5f * bridgeBrightnessFactor, 0.5f * bridgeBrightnessFactor, 0.5f * bridgeBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(0, TRAIN_BRIDGE_DECK_Y + TRAIN_BRIDGE_HEIGHT);
    glVertex2f(1000, TRAIN_BRIDGE_DECK_Y + TRAIN_BRIDGE_HEIGHT);
    glVertex2f(1000, TRAIN_BRIDGE_DECK_Y + TRAIN_BRIDGE_HEIGHT + 5);
    glVertex2f(0, TRAIN_BRIDGE_DECK_Y + TRAIN_BRIDGE_HEIGHT + 5);
    glEnd();
}

void drawRailway() {
    float railBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) {
        railBrightnessFactor = 0.6f;
    }
    if (isRaining) railBrightnessFactor *= 0.7f;

    // Ballast
    glBegin(GL_QUADS);
    glColor3f(0.3f * railBrightnessFactor, 0.3f * railBrightnessFactor, 0.3f * railBrightnessFactor);
    glVertex2f(0, RAILWAY_BASE_Y); glVertex2f(1000, RAILWAY_BASE_Y);
    glVertex2f(1000, RAILWAY_BASE_Y + 5); glVertex2f(0, RAILWAY_BASE_Y + 5); // Thinner ballast
    glEnd();

    // Rails
    glBegin(GL_LINES);
    glColor3f(0.8f * railBrightnessFactor, 0.8f * railBrightnessFactor, 0.8f * railBrightnessFactor);
    glVertex2f(0, RAILWAY_BASE_Y + 5); glVertex2f(1000, RAILWAY_BASE_Y + 5);
    glVertex2f(0, RAILWAY_BASE_Y + 10); glVertex2f(1000, RAILWAY_BASE_Y + 10);
    glEnd();

    // Sleepers (ties)
    glColor3f(0.5f * railBrightnessFactor, 0.3f * railBrightnessFactor, 0.1f * railBrightnessFactor);
    for (int i = 0; i < 1000; i += 30) {
        glBegin(GL_QUADS);
        glVertex2f(i, RAILWAY_BASE_Y + 3);
        glVertex2f(i + 15, RAILWAY_BASE_Y + 3);
        glVertex2f(i + 15, RAILWAY_BASE_Y + 12);
        glVertex2f(i, RAILWAY_BASE_Y + 12);
        glEnd();
    }
}

void playTrainSound() {
    if (!isTrainSoundPlaying) {
        PlaySound(TEXT("train.wav"), NULL, SND_ASYNC | SND_LOOP);
        isTrainSoundPlaying = true;
    }
}

void stopTrainSound() {
    PlaySound(NULL, NULL, 0);
    isTrainSoundPlaying = false;
}

void playTrainWhistle() {
    PlaySound(TEXT("train_whistle.wav"), NULL, SND_ASYNC);
}
void drawTrain() {
    float baseY = RAILWAY_BASE_Y + 10; // Position above the railway
    float trainBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) trainBrightnessFactor = 0.7f;
    if (isRaining) trainBrightnessFactor *= 0.8f;

    for (int i = 0; i < 5; ++i) {
        float cx = trainX + i * 80;

        // Coach body
        glColor3f(0.2f * trainBrightnessFactor, 0.2f * trainBrightnessFactor, 0.8f * trainBrightnessFactor);
        glBegin(GL_POLYGON);
        glVertex2f(cx, baseY);
        glVertex2f(cx + 70, baseY);
        glVertex2f(cx + 70, baseY + 30);
        glVertex2f(cx, baseY + 30);
        glEnd();

        // Roof
        glColor3f(0.1f * trainBrightnessFactor, 0.1f * trainBrightnessFactor, 0.5f * trainBrightnessFactor);
        glBegin(GL_POLYGON);
        glVertex2f(cx, baseY + 30);
        glVertex2f(cx + 70, baseY + 30);
        glVertex2f(cx + 70, baseY + 35);
        glVertex2f(cx, baseY + 35);
        glEnd();

        // Windows
        glColor3f(0.9f * trainBrightnessFactor, 0.9f * trainBrightnessFactor, 1.0f * trainBrightnessFactor);
        for (int j = 0; j < 3; ++j) {
            float wx = cx + 10 + j * 20;
            glBegin(GL_POLYGON);
            glVertex2f(wx, baseY + 15);
            glVertex2f(wx + 10, baseY + 15);
            glVertex2f(wx + 10, baseY + 25);
            glVertex2f(wx, baseY + 25);
            glEnd();
        }

        // Wheels
        glColor3f(0, 0, 0);
        drawCircle(cx + 15, baseY, 5, 20, 0.0f, 0.0f, 0.0f);
        drawCircle(cx + 55, baseY, 5, 20, 0.0f, 0.0f, 0.0f);
    }

    // Engine
    float x = trainX + 5 * 80;
    glColor3f(0.7f * trainBrightnessFactor, 0.0f * trainBrightnessFactor, 0.0f * trainBrightnessFactor);
    glBegin(GL_POLYGON);
    glVertex2f(x, baseY);
    glVertex2f(x + 70, baseY);
    glVertex2f(x + 70, baseY + 40);
    glVertex2f(x, baseY + 40);
    glEnd();

    // Chimney (slightly stylized for realism)
    glColor3f(0.2f * trainBrightnessFactor, 0.2f * trainBrightnessFactor, 0.2f * trainBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(x + 50, baseY + 40);
    glVertex2f(x + 60, baseY + 40);
    glVertex2f(x + 58, baseY + 55);
    glVertex2f(x + 52, baseY + 55);
    glEnd();

    // Nose (smoother)
    glColor3f(0.5f * trainBrightnessFactor, 0.0f * trainBrightnessFactor, 0.0f * trainBrightnessFactor);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 70, baseY);
    glVertex2f(x + 90, baseY + 15); // Adjusted for a smoother curve
    glVertex2f(x + 70, baseY + 30);
    glEnd();

    // Engine Window
    glColor3f(0.9f * trainBrightnessFactor, 0.9f * trainBrightnessFactor, 1.0f * trainBrightnessFactor);
    glBegin(GL_POLYGON);
    glVertex2f(x + 5, baseY + 20);
    glVertex2f(x + 25, baseY + 20);
    glVertex2f(x + 25, baseY + 35);
    glVertex2f(x + 5, baseY + 35);
    glEnd();

    // Wheels
    glColor3f(0, 0, 0);
    drawCircle(x + 15, baseY, 6, 20, 0.0f, 0.0f, 0.0f);
    drawCircle(x + 55, baseY, 6, 20, 0.0f, 0.0f, 0.0f);

    // Headlight (on the front of the engine)
    if (lamppostsOn || isNightTime) {
        glColor3f(1.0f, 1.0f, 0.5f); // Bright yellow light
        glBegin(GL_TRIANGLES);
        glVertex2f(x + 90, baseY + 15); // Front tip of the nose
        glVertex2f(x + 90 + 20, baseY + 15 + 10); // Light spread upwards
        glVertex2f(x + 90 + 20, baseY + 15 - 10); // Light spread downwards
        glEnd();
    }
}

// Draw boat with offset and different designs based on type
void drawBoat(float boatX, float boatOffsetY, int type) {
    float boatBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) {
        boatBrightnessFactor = 0.8f;
    }
    if (isRaining) boatBrightnessFactor *= 0.7f;

    glPushMatrix();
    glTranslatef(boatX, RIVER_BOTTOM_Y + boatOffsetY, 0);
    glScalef(0.6f, 0.6f, 1.0f);

    if (type == 1) { // Modern style boat (like a speedboat or yacht)
        // Hull
        glColor3f(0.1f * boatBrightnessFactor, 0.1f * boatBrightnessFactor, 0.6f * boatBrightnessFactor); // Dark blue
        glBegin(GL_POLYGON);
        glVertex2f(350, 60);
        glVertex2f(550, 60);
        glVertex2f(540, 75);
        glVertex2f(360, 75);
        glEnd();

        // Deck
        glColor3f(0.7f * boatBrightnessFactor, 0.7f * boatBrightnessFactor, 0.7f * boatBrightnessFactor); // Gray deck
        glBegin(GL_QUADS);
        glVertex2f(360, 75);
        glVertex2f(540, 75);
        glVertex2f(530, 85);
        glVertex2f(370, 85);
        glEnd();

        // Cabin/Windshield
        glColor3f(0.2f * boatBrightnessFactor, 0.2f * boatBrightnessFactor, 0.3f * boatBrightnessFactor);
        glBegin(GL_QUADS);
        glVertex2f(400, 85);
        glVertex2f(500, 85);
        glVertex2f(490, 100);
        glVertex2f(410, 100);
        glEnd();

        // Cabin window (tinted blue)
        glColor3f(0.3f, 0.5f, 0.7f);
        glBegin(GL_QUADS);
        glVertex2f(415, 88);
        glVertex2f(485, 88);
        glVertex2f(475, 96);
        glVertex2f(425, 96);
        glEnd();

    } else { // Traditional wooden boat (like a small ferry or fishing boat)
        // Hull
        glColor3f(0.5f * boatBrightnessFactor, 0.3f * boatBrightnessFactor, 0.1f * boatBrightnessFactor); // Brown wood
        glBegin(GL_POLYGON);
        glVertex2f(350, 60);
        glVertex2f(370, 50);
        glVertex2f(530, 50);
        glVertex2f(550, 60);
        glVertex2f(540, 75);
        glVertex2f(360, 75);
        glEnd();

        // Deck
        glColor3f(0.6f * boatBrightnessFactor, 0.4f * boatBrightnessFactor, 0.2f * boatBrightnessFactor); // Lighter brown deck
        glBegin(GL_QUADS);
        glVertex2f(380, 75);
        glVertex2f(520, 75);
        glVertex2f(510, 100);
        glVertex2f(390, 100);
        glEnd();

        // Cabin
        glColor3f(0.35f * boatBrightnessFactor, 0.25f * boatBrightnessFactor, 0.15f * boatBrightnessFactor); // Darker cabin
        glBegin(GL_POLYGON);
        glVertex2f(385, 100);
        glVertex2f(515, 100);
        glVertex2f(505, 115);
        glVertex2f(395, 115);
        glEnd();

        // Windows
        float windowLightFactor = (lamppostsOn && isNightTime) ? 1.0f : 0.5f;
        glColor3f(0.7f * windowLightFactor, 0.9f * windowLightFactor, 1.0f * windowLightFactor);
        glBegin(GL_QUADS);
        glVertex2f(400, 80);
        glVertex2f(430, 80);
        glVertex2f(430, 95);
        glVertex2f(400, 95);
        glVertex2f(470, 80);
        glVertex2f(500, 80);
        glVertex2f(500, 95);
        glVertex2f(470, 95);
        glEnd();
    }
    glPopMatrix();
}

// Draw lamppost (y is the base of the pole on the ground)
void drawLamppost(float x, float y) {
    float lamppostBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) lamppostBrightnessFactor = 0.8f;
    if (isRaining) lamppostBrightnessFactor *= 0.7f;

    // Pole height and lamp arm position
    float poleHeight = 100.0f; // Total height of the pole from its base
    float armHeight = poleHeight - 10.0f; // Arm starts 10 units below pole top

    // Pole
    glColor3f(0.3f * lamppostBrightnessFactor, 0.3f * lamppostBrightnessFactor, 0.3f * lamppostBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 5, y);
    glVertex2f(x + 5, y + poleHeight);
    glVertex2f(x, y + poleHeight);
    glEnd();

    // Arm
    glColor3f(0.4f * lamppostBrightnessFactor, 0.4f * lamppostBrightnessFactor, 0.4f * lamppostBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(x - 5, y + armHeight);
    glVertex2f(x + 10, y + armHeight);
    glVertex2f(x + 10, y + armHeight + 5);
    glVertex2f(x - 5, y + armHeight + 5);
    glEnd();

    // Light source
    if (lamppostsOn) {
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow light
        glBegin(GL_POLYGON);
        glVertex2f(x - 5, y + armHeight + 5);
        glVertex2f(x + 10, y + armHeight + 5);
        glVertex2f(x + 15, y + armHeight + 15);
        glVertex2f(x - 10, y + armHeight + 15);
        glEnd();
    } else {
        glColor3f(0.2f * lamppostBrightnessFactor, 0.2f * lamppostBrightnessFactor, 0.2f * lamppostBrightnessFactor); // Off light
        glBegin(GL_POLYGON);
        glVertex2f(x - 5, y + armHeight + 5);
        glVertex2f(x + 10, y + armHeight + 5);
        glVertex2f(x + 15, y + armHeight + 15);
        glVertex2f(x - 10, y + armHeight + 15);
        glEnd();
    }
}

void drawWindmill(float x, float y, float scale, float angle) {
    float wmBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) wmBrightnessFactor = 0.6f;
    if (isRaining) wmBrightnessFactor *= 0.6f;

    float newScale = scale * 3.0f; // Overall scaling
    glPushMatrix();
    glTranslatef(x, y, 0); // Use the passed y directly
    glScalef(newScale, newScale, 1.0f);

    // Thinner Tower
    glColor3f(0.6f * wmBrightnessFactor, 0.4f * wmBrightnessFactor, 0.2f * wmBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(-5, 0); // Thinner base
    glVertex2f(5, 0);  // Thinner base
    glVertex2f(2.5, 80); // Thinner top
    glVertex2f(-2.5, 80); // Thinner top
    glEnd();

    // Hub
    drawCircle(0, 80, 8, 20, 0.3f * wmBrightnessFactor, 0.3f * wmBrightnessFactor, 0.3f * wmBrightnessFactor);

    glPushMatrix();
    glTranslatef(0, 80, 0);
    glRotatef(angle, 0, 0, 1);
    glColor3f(0.8f * wmBrightnessFactor, 0.8f * wmBrightnessFactor, 0.8f * wmBrightnessFactor);

    // Blades
    glBegin(GL_QUADS);
    glVertex2f(-5, -5); glVertex2f(5, -5); glVertex2f(20, 50); glVertex2f(-20, 50);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-5, -5); glVertex2f(5, -5); glVertex2f(-50, 20); glVertex2f(-50, -20);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-5, -5); glVertex2f(5, -5); glVertex2f(-20, -50); glVertex2f(20, -50);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-5, -5); glVertex2f(5, -5); glVertex2f(50, -20); glVertex2f(50, 20);
    glEnd();

    glPopMatrix();
    glPopMatrix();
}

void drawRain() {
    if (!isRaining) return;
    glColor3f(0.7f, 0.7f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 200; i++) {
        glVertex2f(rainDrops[i][0], rainDrops[i][1]);
        glVertex2f(rainDrops[i][0], rainDrops[i][1] - 10);
        rainDrops[i][1] -= 5;
        if (rainDrops[i][1] < 0) rainDrops[i][1] = 600;
    }
    glEnd();
}

void drawAirplane() {
    float airplaneBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) airplaneBrightnessFactor = 0.6f;
    if (isRaining) airplaneBrightnessFactor *= 0.7f;

    glPushMatrix();
    glTranslatef(airplaneX, airplaneY, 0.0f);
    glScalef(0.7f, 0.7f, 1.0f);

    // Fuselage
    glColor3f(0.8f * airplaneBrightnessFactor, 0.8f * airplaneBrightnessFactor, 0.85f * airplaneBrightnessFactor);
    glBegin(GL_POLYGON);
    glVertex2f(0, 50);
    glVertex2f(10, 60);
    glVertex2f(120, 60);
    glVertex2f(150, 50);
    glVertex2f(140, 40);
    glVertex2f(10, 40);
    glVertex2f(0, 50);
    glEnd();

    // Windows
    float windowColorR = 0.3f;
    float windowColorG = 0.5f;
    float windowColorB = 0.7f;
    if (lamppostsOn || isNightTime) {
        windowColorR = 1.0f;
        windowColorG = 1.0f;
        windowColorB = 0.8f; // Yellowish light for windows at night
    }
    glColor3f(windowColorR, windowColorG, windowColorB);
    glBegin(GL_QUADS);
    glVertex2f(30, 52); glVertex2f(35, 52); glVertex2f(35, 57); glVertex2f(30, 57);
    glVertex2f(40, 52); glVertex2f(45, 52); glVertex2f(45, 57); glVertex2f(40, 57);
    glVertex2f(50, 52); glVertex2f(55, 52); glVertex2f(55, 57); glVertex2f(50, 57);
    glVertex2f(60, 52); glVertex2f(65, 52); glVertex2f(65, 57); glVertex2f(60, 57);
    glVertex2f(70, 52); glVertex2f(75, 52); glVertex2f(75, 57); glVertex2f(70, 57);
    glEnd();

    // Cockpit window
    glColor3f(0.2f, 0.2f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(8, 52);
    glVertex2f(25, 52);
    glVertex2f(23, 57);
    glVertex2f(10, 57);
    glEnd();

    // Wings
    glColor3f(0.6f * airplaneBrightnessFactor, 0.6f * airplaneBrightnessFactor, 0.65f * airplaneBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(60, 55);
    glVertex2f(70, 55);
    glVertex2f(100, 30);
    glVertex2f(90, 30);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(60, 45);
    glVertex2f(70, 45);
    glVertex2f(100, 70);
    glVertex2f(90, 70);
    glEnd();

    // Tail fin
    glColor3f(0.7f * airplaneBrightnessFactor, 0.7f * airplaneBrightnessFactor, 0.75f * airplaneBrightnessFactor);
    glBegin(GL_TRIANGLES);
    glVertex2f(140, 60);
    glVertex2f(150, 60);
    glVertex2f(145, 80);
    glEnd();

    // Tail stabilizers
    glColor3f(0.6f * airplaneBrightnessFactor, 0.6f * airplaneBrightnessFactor, 0.65f * airplaneBrightnessFactor);
    glBegin(GL_TRIANGLES);
    glVertex2f(145, 50);
    glVertex2f(160, 55);
    glVertex2f(160, 45);
    glEnd();

    glPopMatrix();
}

// Realistic Car Drawing Function
void drawRealisticCar(float x, float y, float r, float g, float b, int direction) {
    float carBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) carBrightnessFactor = 0.7f;
    if (isRaining) carBrightnessFactor *= 0.8f;

    // Body
    glColor3f(r * carBrightnessFactor, g * carBrightnessFactor, b * carBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(x, y + 5); // Bottom front
    glVertex2f(x + 40, y + 5); // Bottom back
    glVertex2f(x + 40, y + 20); // Top back
    glVertex2f(x, y + 20); // Top front
    glEnd();

    // Roof and Cabin
    glColor3f(r * 0.8f * carBrightnessFactor, g * 0.8f * carBrightnessFactor, b * 0.8f * carBrightnessFactor);
    glBegin(GL_POLYGON);
    glVertex2f(x + 8, y + 20); // Base front
    glVertex2f(x + 32, y + 20); // Base back
    glVertex2f(x + 30, y + 28); // Top back
    glVertex2f(x + 10, y + 28); // Top front
    glEnd();

    // Windows (slightly darker blue)
    glColor3f(0.3f, 0.5f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(x + 10, y + 21); // Front window
    glVertex2f(x + 18, y + 21);
    glVertex2f(x + 18, y + 26);
    glVertex2f(x + 10, y + 26);

    glVertex2f(x + 22, y + 21); // Rear window
    glVertex2f(x + 30, y + 21);
    glVertex2f(x + 30, y + 26);
    glVertex2f(x + 22, y + 26);
    glEnd();


    // Wheels
    glColor3f(0.1f, 0.1f, 0.1f); // Darker for wheels
    drawCircle(x + 10, y + 5, 5, 20, 0.1f, 0.1f, 0.1f);
    drawCircle(x + 30, y + 5, 5, 20, 0.1f, 0.1f, 0.1f);

    // Headlights (only if lampposts are on or it's night)
    if (lamppostsOn || isNightTime) {
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow light
        glBegin(GL_TRIANGLES);
        if (direction == 1) { // Moving right (headlights on the right side of the car)
            glVertex2f(x + 40, y + 10);
            glVertex2f(x + 45, y + 8);
            glVertex2f(x + 45, y + 12);
        } else { // Moving left (headlights on the left side of the car)
            glVertex2f(x, y + 10);
            glVertex2f(x - 5, y + 8);
            glVertex2f(x - 5, y + 12);
        }
        glEnd();
    }
}

// Realistic Bus Drawing Function
void drawRealisticBus(float x, float y, int direction) {
    float busBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) busBrightnessFactor = 0.7f;
    if (isRaining) busBrightnessFactor *= 0.8f;

    // Body (Red color)
    glColor3f(0.8f * busBrightnessFactor, 0.2f * busBrightnessFactor, 0.2f * busBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(x, y + 5);
    glVertex2f(x + 70, y + 5);
    glVertex2f(x + 70, y + 30);
    glVertex2f(x, y + 30);
    glEnd();

    // Windows (blue tint)
    glColor3f(0.3f, 0.5f, 0.7f);
    for (int i = 0; i < 3; ++i) {
        glBegin(GL_QUADS);
        glVertex2f(x + 10 + i * 20, y + 15);
        glVertex2f(x + 25 + i * 20, y + 15);
        glVertex2f(x + 25 + i * 20, y + 25);
        glVertex2f(x + 10 + i * 20, y + 25);
        glEnd();
    }

    // Wheels
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle(x + 15, y + 5, 6, 20, 0.1f, 0.1f, 0.1f);
    drawCircle(x + 55, y + 5, 6, 20, 0.1f, 0.1f, 0.1f);

    // Headlights (only if lampposts are on or it's night)
    if (lamppostsOn || isNightTime) {
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow light
        glBegin(GL_TRIANGLES);
        if (direction == 1) { // Moving right (headlights on the right side of the bus)
            glVertex2f(x + 70, y + 10);
            glVertex2f(x + 75, y + 8);
            glVertex2f(x + 75, y + 12);
        } else { // Moving left (headlights on the left side of the bus)
            glVertex2f(x, y + 10);
            glVertex2f(x - 5, y + 8);
            glVertex2f(x - 5, y + 12);
        }
        glEnd();
    }
}

void drawSignpost(float x, float y) {
    float signBrightnessFactor = 1.0f;
    if (currentHour > 18.0f || currentHour < 6.0f) signBrightnessFactor = 0.6f;
    if (isRaining) signBrightnessFactor *= 0.7f;

    // Pole
    glColor3f(0.4f * signBrightnessFactor, 0.2f * signBrightnessFactor, 0.1f * signBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 3, y);
    glVertex2f(x + 3, y + 25);
    glVertex2f(x, y + 25);
    glEnd();

    // Signboard
    glColor3f(0.8f * signBrightnessFactor, 0.8f * signBrightnessFactor, 0.8f * signBrightnessFactor);
    glBegin(GL_QUADS);
    glVertex2f(x - 15, y + 25);
    glVertex2f(x + 18, y + 25);
    glVertex2f(x + 18, y + 35);
    glVertex2f(x - 15, y + 35);
    glEnd();

    // Example text/symbol on sign
    glColor3f(0.1f, 0.1f, 0.1f); // Dark color for symbol
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 5, y + 28);
    glVertex2f(x + 5, y + 28);
    glVertex2f(x, y + 33);
    glEnd();
}




// Main display function
void display() {
    float skyColor[3];
    getSkyColor(currentHour, skyColor);
    if (isRaining) {
        skyColor[0] *= 0.8f; skyColor[1] *= 0.8f; skyColor[2] *= 0.8f;
    }
    glClearColor(skyColor[0], skyColor[1], skyColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    isNightTime = (currentHour >= 20.0f || currentHour < 6.0f);
    if (isNightTime) {
        lamppostsOn = true; // Ensure lampposts are on during night
    } else {
        // Only turn off if not explicitly set by user.
        lamppostsOn = false;
    }


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    drawStars();
    drawMoon();
    drawSun();
    drawClouds();
    drawMountains();
    drawGround();
    drawRiverside();
    drawRiver();

    drawTrees();

    // Windmills adjusted to be smaller, thinner, and connected to the ground
    drawWindmill(200, GROUND_LEVEL_Y + 30, 0.3f, windmillBladeAngle1);
    drawWindmill(700, GROUND_LEVEL_Y + 30, 0.3f, windmillBladeAngle2);

    drawBridge(); // This is the road bridge over the river

    drawRoad();
    // Cars and bus are now positioned relative to the new ROAD_BOTTOM_Y
    drawRealisticCar(carPositions[0], ROAD_BOTTOM_Y + 5, 0.0f, 0.0f, 1.0f, carDirections[0]); // Blue car
    drawRealisticCar(carPositions[1], ROAD_BOTTOM_Y + 5, 0.7f, 0.7f, 0.0f, carDirections[1]); // Yellow car
    drawRealisticCar(carPositions[2], ROAD_BOTTOM_Y + 5, 0.8f, 0.2f, 0.6f, carDirections[2]); // Purple car
    drawRealisticCar(carPositions[3], ROAD_BOTTOM_Y + 5, 0.1f, 0.5f, 0.1f, carDirections[3]); // Green car
    drawRealisticBus(busPosition, ROAD_BOTTOM_Y + 5, busDirection);

    drawSignpost(150, ROAD_TOP_Y);
    drawSignpost(850, ROAD_TOP_Y);

    // Draw the train bridge before the railway itself
    drawTrainBridge();
    drawRailway();
    drawTrain(); // Train is now on the new train bridge

    // Draw two different boats
    drawBoat(boatPos1, boatY1, 1); // Type 1: Modern boat
    drawBoat(boatPos2, boatY2, 2); // Type 2: Traditional boat
    drawRain();
    drawAirplane();

    // Lampposts placed along the TRAIN LINE
    // These are on the bridge, so their "ground" is RAILWAY_BASE_Y
    drawLamppost(100, RAILWAY_BASE_Y + 10); // +10 to sit just above the rail ties
    drawLamppost(350, RAILWAY_BASE_Y + 10);
    drawLamppost(600, RAILWAY_BASE_Y + 10);
    drawLamppost(850, RAILWAY_BASE_Y + 10);

    // Lampposts placed along the ROADSIDE
    // Their base is now at GROUND_LEVEL_Y to connect to the ground
    drawLamppost(50, GROUND_LEVEL_Y);
    drawLamppost(250, GROUND_LEVEL_Y);
    drawLamppost(450, GROUND_LEVEL_Y);
    drawLamppost(700, GROUND_LEVEL_Y);
    drawLamppost(950, GROUND_LEVEL_Y);

    glDisable(GL_BLEND);
    glutSwapBuffers();
}



// Update logic
void update(int value) {
     // Train movement
    if (isTrainMoving) {
        trainX += 1;
        if (!isTrainSoundPlaying) {
            playTrainSound();
        }
        // Play whistle occasionally
        if (rand() % 500 == 0) {
            playTrainWhistle();
        }
    } else {
        if (isTrainSoundPlaying) {
            stopTrainSound();
        }
    }

    if (trainX > 1000) trainX = -480; // Reset train position (considering its length)

    // Boat movement
    if (isBoatMoving) {
        boatPos1 += 1.0f;
        if (boatPos1 > 1000.0f) boatPos1 = -600.0f;
        boatPos2 += 0.8f;
        if (boatPos2 > 1000.0f) boatPos2 = -600.0f;
    }

    // Car movement
    for (int i = 0; i < 5; ++i) {
        carPositions[i] += carSpeeds[i] * carDirections[i];
        if (carDirections[i] == 1 && carPositions[i] > 1050) {
            carPositions[i] = -50;
        } else if (carDirections[i] == -1 && carPositions[i] < -50) {
            carPositions[i] = 1050;
        }
    }

    // Bus movement
    busPosition += busSpeed * busDirection;
    if (busDirection == 1 && busPosition > 1070) {
        busPosition = -70;
    } else if (busDirection == -1 && busPosition < -70) {
        busPosition = 1070;
    }

    cloudOffset += 0.3f;
    if (cloudOffset > 1100.0f) cloudOffset = 0.0f;

    if (windmillsMoving) {
        windmillBladeAngle1 += 2.0f;
        if (windmillBladeAngle1 > 360.0f) windmillBladeAngle1 -= 360.0f;
        windmillBladeAngle2 += 1.5f;
        if (windmillBladeAngle2 > 360.0f) windmillBladeAngle2 -= 360.0f;
    }

    // Airplane now moves from right to left
    airplaneX -= 1.5f;
    if (airplaneX < -200) {
        airplaneX = 1100;
        airplaneY = 400 + (rand() % 100);
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Approximately 60 FPS
}



void keyboard(unsigned char key, int x, int y) {
    if (key == 's' || key == 'S') windmillsMoving = !windmillsMoving;
    else if (key == 'b' || key == 'B') isBoatMoving = !isBoatMoving;
    else if (key == 'r' || key == 'R') isRaining = !isRaining;
    else if (key == 'n' || key == 'N') { // Night (Midnight)
        currentHour = 2.0f;
        lamppostsOn = true;
    }
    else if (key == 'm' || key == 'M') { // Morning
        currentHour = 8.0f;
        lamppostsOn = false;
    }
    else if (key == 'd' || key == 'D') { // Day (Noon)
        currentHour = 12.0f;
        lamppostsOn = false;
    }
    else if (key == 'e' || key == 'E') { // Evening
        currentHour = 19.0f;
        lamppostsOn = true;
    }
    else if (key == 't' || key == 'T') { // Toggle train movement
        isTrainMoving = !isTrainMoving;
        if (isTrainMoving) {
            playTrainSound();
        } else {
            playTrainWhistle(); // Play whistle when stopping
        }
    }
    glutPostRedisplay();
}
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Toggle train movement with left click
        isTrainMoving = !isTrainMoving;
        if (isTrainMoving) {
            playTrainSound();
        } else {
            playTrainWhistle(); // Play whistle when stopping
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Keep original right click functionality for rain
        isRaining = !isRaining;
    }
    glutPostRedisplay();
}

// Reshape window
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 600);
    glMatrixMode(GL_MODELVIEW);
}



// Main
int main(int argc, char** argv) {
    srand(time(0));
    initRain();
    initStars();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Realistic Train & River Scene");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(0, update, 0);
    // Play initial train sound if moving
if (isTrainMoving) {
    playTrainSound();
}

    glutMainLoop();
    return 0;
}
//scene 03:
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <vector>

// Global variables for animation states and positions
float sunY = 500;
float angle = 0;
float trainX = 0;
float trainSpeed = 2.0f;
float carPosX = 0.0f;
float ambulancePosX = -200.0f;
float busPosX = -400.0f;
float carPosX2 = 1000.0f;
float cloudX1 = 0, cloudX2 = 300, cloudX3 = 600;
float cloudSpeed = 0.5f;
bool isRaining = false;
int currentMode = 0;
bool sirenOn = false;
float sirenTimer = 0;
bool busStopped = false;
bool thunderActive = false;
int thunderTimer = 0;
float airplaneX = -200.0f;
float airplaneSpeed = 3.0f;
int thunderBlinks = 0;       // Count of thunder blinks
bool thunderBlinking = false; // Whether thunder is currently blinking
int thunderBlinkTimer = 0;   // Timer for blink intervals
// Structure for raindrops
struct Raindrop {
    float x;
    float y;
    float speed;
    float length;
};
std::vector<Raindrop> raindrops;
const float BUS_COLOR_R = 1.0f;
const float BUS_COLOR_G = 0.0f;
const float BUS_COLOR_B = 1.0f;

// Function to draw a circle
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; ++i) {
        float theta = 2.0f * 3.1416f * i / 100;
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Function to draw a rectangle
void drawRectangle(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Function to draw a triangle
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

// Function to draw the sun
void drawSun() {
    if (currentMode == 0 || currentMode == 2) { // Day or Evening
        glColor3f(1.0, 0.7, 0.2);
        drawCircle(800, sunY, 40);
        glColor3f(1.0, 0.8, 0.4);
        for (int i = 0; i < 360; i += 30) {
            float rad = i * 3.1416 / 180.0;
            float x1 = 800 + cos(rad) * 50;
            float y1 = sunY + sin(rad) * 50;
            float x2 = 800 + cos(rad) * 70;
            float y2 = sunY + sin(rad) * 70;
            glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glEnd();
        }
    }
}

// Function to draw the moon
void drawMoon() {
    if (currentMode == 1) { // Night
        glColor3f(0.9, 0.9, 0.8);
        drawCircle(800, 500, 30);
        glColor3f(0.7, 0.7, 0.6); // Craters
        drawCircle(790, 510, 5);
        drawCircle(810, 490, 4);
        drawCircle(800, 480, 3);
    }
}

// Function to draw very distant mountains (behind everything)
void drawDistantMountains() {
    // Darker, less detailed mountains in the far background
    glColor3f(0.15, 0.25, 0.15);
    glBegin(GL_POLYGON);
    glVertex2f(0, 300);
    glVertex2f(100, 450);
    glVertex2f(250, 400);
    glVertex2f(400, 500);
    glVertex2f(550, 420);
    glVertex2f(700, 480);
    glVertex2f(850, 430);
    glVertex2f(1000, 500);
    glVertex2f(1000, 300);
    glEnd();
}


// Function to draw simple background buildings (less detailed)
void drawBackgroundBuilding(float x, float y, float width, float height, float r, float g, float b) {
    // Main building body
    drawRectangle(x, y, width, height, r, g, b);

    // Simple windows (fewer and less detailed)
    glColor3f(currentMode == 1 ? 1.0 : r+0.3, currentMode == 1 ? 1.0 : g+0.3, currentMode == 1 ? 0.0 : b+0.3);
    for (float i = x + 5; i < x + width - 5; i += width/4) {
        for (float j = y + 5; j < y + height - 15; j += height/5) {
            drawRectangle(i, j, 8, 10,
                         currentMode == 1 ? 1.0 : r+0.3,
                         currentMode == 1 ? 1.0 : g+0.3,
                         currentMode == 1 ? 0.0 : b+0.3);
        }
    }

    // Simple roof
    drawRectangle(x-3, y+height, width+6, 5, r*0.7, g*0.7, b*0.7);
}

// Function to draw mountains
void drawMountains() {

    glColor3f(0.4, 0.35, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(150, 380);
    glVertex2f(147, 440);
    glVertex2f(195, 483.32);
    glVertex2f(266, 436);
    glVertex2f(266, 384);
    glEnd();

    glColor3f(0.4, 0.35, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(400, 400);
    glVertex2f(397, 438);
    glVertex2f(445, 499);
    glVertex2f(500, 434);
    glVertex2f(482, 403);
    glEnd();

    glColor3f(0.4, 0.35, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(727, 391);
    glVertex2f(724, 430);
    glVertex2f(760, 461);
    glVertex2f(803, 427);
    glVertex2f(805, 387);
    glEnd();
    // Base mountain color - dark green/brown
    glColor3f(0.25, 0.3, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(0, 297.378);
    glVertex2f(0, 431.207);
    glVertex2f(82.160, 521.206);
    glVertex2f(256.457, 374.875);
    glVertex2f(255.807, 292.279);
    glEnd();

    // Middle mountain - lighter earth tone
    glColor3f(0.3, 0.35, 0.25);
    glBegin(GL_POLYGON);
    glVertex2f(210.807, 294.785);
    glVertex2f(213.473, 415.165);
    glVertex2f(350.058, 531.855);
    glVertex2f(490.536, 374.468);
    glVertex2f(492.278, 292.285);
    glEnd();

    // Right mountain - rocky gray-brown
    glColor3f(0.35, 0.4, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(439.654, 295.068);
    glVertex2f(440.666, 427.009);
    glVertex2f(630.899, 538.027);
    glVertex2f(767.548, 416.775);
    glVertex2f(766.928, 291.998);
    glEnd();

    // Far right mountain - lighter with some vegetation
    glColor3f(0.35, 0.4, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(757.512, 291.550);
    glVertex2f(763.690, 414.240);
    glVertex2f(892.637, 527.107);
    glVertex2f(1000, 405.440);
    glVertex2f(1000, 290.000);
    glEnd();

    // Mountain base/foothills - earthy brown
    glColor3ub(139, 115, 85);
    glBegin(GL_QUADS);
    glVertex2f(0, 300);
    glVertex2f(0, 100);
    glVertex2f(1000, 120);
    glVertex2f(1000, 300);
    glEnd();

    glColor3f(0.2, 0.25, 0.15);
    glBegin(GL_LINES);
    // Middle mountain ridges
    glVertex2f(300, 350); glVertex2f(350, 500);
    glVertex2f(400, 400); glVertex2f(450, 480);
    glVertex2f(600, 400); glVertex2f(650, 500);
    glEnd();
}

// Function to draw a residential building
void drawResidentialBuilding(float x, float y, float width, float height) {
    drawRectangle(x, y, width, height, 0.9, 0.8, 0.7); // Building body
    glColor3f(currentMode == 1 ? 1.0 : 0.4, currentMode == 1 ? 1.0 : 0.6, currentMode == 1 ? 0.0 : 0.8); // Window color changes with mode
    for (float i = x + 10; i < x + width - 10; i += 25) {
        for (float j = y + 10; j < y + height - 20; j += 30) {
            drawRectangle(i, j, 15, 20,
                            currentMode == 1 ? 1.0 : 0.4,
                            currentMode == 1 ? 1.0 : 0.6,
                            currentMode == 1 ? 0.0 : 0.8);
            glColor3f(0.2, 0.2, 0.2); // Window panes
            glBegin(GL_LINES);
            glVertex2f(i, j + 10);
            glVertex2f(i + 15, j + 10);
            glVertex2f(i + 7.5, j);
            glVertex2f(i + 7.5, j + 20);
            glEnd();
        }
    }
    glColor3f(0.6, 0.4, 0.2); // Roof trim
    drawRectangle(x - 5, y + height - 20, width + 10, 10, 0.6, 0.4, 0.2);
    glColor3f(0.7, 0.7, 0.7); // Chimney
    drawRectangle(x + width / 2 - 10, y + height, 20, 15, 0.7, 0.7, 0.7);
}

// Function to draw a Bangladeshi commercial building
void drawBangladeshiCommercial(float x, float y, float width, float height) {
    drawRectangle(x, y, width, height, 0.5, 0.5, 0.6); // Building body
    glColor3f(0.6, 0.2, 0.2); // Top decorative band
    drawRectangle(x, y, width, 40, 0.6, 0.2, 0.2);
    glColor3f(0.9, 0.9, 0.9); // Small rectangles on band
    for (float i = x + 5; i < x + width - 5; i += width / 3) {
        drawRectangle(i, y + 30, width / 3 - 5, 10, 0.9, 0.9, 0.9);
    }
    glColor3f(currentMode == 1 ? 1.0 : 0.5, currentMode == 1 ? 1.0 : 0.7, currentMode == 1 ? 0.0 : 0.9); // Windows
    for (float i = x + 10; i < x + width - 10; i += 30) {
        for (float j = y + 50; j < y + height - 10; j += 35) {
            drawRectangle(i, j, 20, 25,
                            currentMode == 1 ? 1.0 : 0.5,
                            currentMode == 1 ? 1.0 : 0.7,
                            currentMode == 1 ? 0.0 : 0.9);
        }
    }
    glColor3f(0.9, 0.5, 0.1); // Sign/awning area
    drawRectangle(x + width / 2 - 30, y + height, 60, 10, 0.9, 0.5, 0.1);
}

// Function to draw a school building
void drawSchoolBuilding(float x, float y, float width, float height) {
    drawRectangle(x, y, width, height, 1.0, 0.8, 0.2); // Main building body (yellow)

    glColor3f(0.7, 0.1, 0.1); // Roof (red triangular part)
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 10, y + height);
    glVertex2f(x + width + 10, y + height);
    glVertex2f(x + width / 2, y + height + 40); // Apex of the roof
    glEnd();

    drawRectangle(x + width / 2 - 20, y, 40, height * 0.6, 0.8, 0.8, 0.8); // Entrance area (light grey)

    glColor3f(0.1, 0.3, 0.7); // Double doors (blue)
    drawRectangle(x + width / 2 - 18, y, 17, height * 0.5, 0.1, 0.3, 0.7);
    drawRectangle(x + width / 2 + 1, y, 17, height * 0.5, 0.1, 0.3, 0.7);

    // Windows (blueish, light up at night)
    float windowColorR = currentMode == 1 ? 1.0 : 0.3;
    float windowColorG = currentMode == 1 ? 1.0 : 0.5;
    float windowColorB = currentMode == 1 ? 0.0 : 0.8;

    for (int i = 0; i < 2; ++i) { // Two rows
        for (int j = 0; j < 2; ++j) { // Two columns
            drawRectangle(x + 10 + j * 30, y + 10 + i * 40, 20, 30, windowColorR, windowColorG, windowColorB);
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            drawRectangle(x + width - 50 + j * 30, y + 10 + i * 40, 20, 30, windowColorR, windowColorG, windowColorB);
        }
    }

    glColor3f(0.8, 0.1, 0.1); // "SCHOOL" sign background
    drawRectangle(x + width / 2 - 25, y + height * 0.9, 50, 15, 0.8, 0.1, 0.1);
    glColor3f(1.0, 1.0, 1.0); // White text
    glRasterPos2f(x + width / 2 - 20, y + height * 0.9 + 4);
    const char* schoolText = "SCHOOL";
    for (int i = 0; schoolText[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, schoolText[i]);
    }

    glColor3f(0.1, 0.1, 0.1); // Clock outline
    drawCircle(x + width / 2, y + height + 20, 10);
    glColor3f(1.0, 1.0, 1.0); // Clock face
    drawCircle(x + width / 2, y + height + 20, 8);
    glColor3f(0.0, 0.0, 0.0); // Clock hands
    glBegin(GL_LINES);
    glVertex2f(x + width / 2, y + height + 20);
    glVertex2f(x + width / 2, y + height + 20 + 5); // Hour hand
    glVertex2f(x + width / 2, y + height + 20);
    glVertex2f(x + width / 2 + 4, y + height + 20 - 4); // Minute hand
    glEnd();

    glColor3f(0.4, 0.4, 0.4); // Flagpole
    drawRectangle(x + width / 2 + 30, y + height + 20, 3, 30, 0.4, 0.4, 0.4);

    glColor3f(0.8, 0.0, 0.0); // Flag (red part)
    glBegin(GL_QUADS);
    glVertex2f(x + width / 2 + 31, y + height + 65);
    glVertex2f(x + width / 2 + 31, y + height + 50);
    glVertex2f(x + width / 2 + 31 + 15, y + height + 50);
    glVertex2f(x + width / 2 + 31 + 15, y + height + 65);
    glEnd();
}

// Function to draw a Bangladeshi high-rise building
void drawBangladeshiHighRise(float x, float y, float width, float height) {
    drawRectangle(x, y, width, height, 0.4, 0.5, 0.6); // Building body
    glColor3f(currentMode == 1 ? 1.0 : 0.3, currentMode == 1 ? 1.0 : 0.4, currentMode == 1 ? 0.0 : 0.7); // Windows
    for (float j = y + 10; j < y + height - 10; j += 25) {
        for (float i = x + 5; i < x + width - 5; i += 20) {
            drawRectangle(i, j, 15, 15,
                            currentMode == 1 ? 1.0 : 0.3,
                            currentMode == 1 ? 1.0 : 0.4,
                            currentMode == 1 ? 0.0 : 0.7);
        }
    }
    glColor3f(0.2, 0.3, 0.4); // Roof ledge
    drawRectangle(x - 5, y + height, width + 10, 20, 0.2, 0.3, 0.4);
    glColor3f(0.7, 0.7, 0.7); // Antenna
    glBegin(GL_LINES);
    glVertex2f(x + width / 2, y + height + 20);
    glVertex2f(x + width / 2, y + height + 40);
    glEnd();
}

// Function to draw a Bangladeshi store building
void drawBangladeshiStoreBuilding(float x, float y, float width, float height) {
    // Main building body: light reddish-brown/orange hue (238, 139, 95 in RGB).
    drawRectangle(x, y, width, height, 0.93333f, 0.54510f, 0.37255f);

    // Roof (Bright Orange)
    glColor3f(1.0f, 0.471f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 5, y + height);
    glVertex2f(x + width + 3, y + height);
    glVertex2f(x + width, y + height + 15);
    glVertex2f(x, y + height + 15);
    glEnd();

    // Door (Earthy Green)
    glColor3f(0.314f, 0.588f, 0.235f);
    drawRectangle(x + width / 2 - 7, y, 10, 25, 0.314f, 0.588f, 0.235f);

    // Original Window (conditional color based on currentMode)
    if (currentMode == 1) {
        // Pinkish-purple for mode 1
        glColor3f(1.0f, 0.0f, 0.588f);
        drawRectangle(x + width / 4, y + 20, 10, 10, 1.0f, 0.0f, 0.588f);
    } else {
        // Light blue for other modes
        glColor3f(0.588f, 0.784f, 1.0f);
        drawRectangle(x + width / 4, y + 20, 10, 10, 0.588f, 0.784f, 1.0f);
    }

    // Additional Windows (Soft Blue with a slightly darker shade)
    drawRectangle(x + width / 8, y + height / 3, 10, 10, 0.4f, 0.6f, 0.8f); // Window 1
    drawRectangle(x + 5 * width / 8, y + height / 3, 10, 10, 0.4f, 0.6f, 0.8f); // Window 2
}

// Function to draw a tree
void drawTree(float x, float y) {
    drawRectangle(x + 12, y, 10, 40, 0.5, 0.3, 0.1); // Trunk
    glColor3f(0.1, 0.7, 0.2); // Leaves
    drawCircle(x + 17, y + 55, 20);
    drawCircle(x + 7, y + 50, 18);
    drawCircle(x + 27, y + 50, 18);
}

// Function to draw the train track on the bridge
void drawBridgeTrack() {
    glColor3f(0.6, 0.6, 0.6); // Main track body
    glBegin(GL_POLYGON);
    glVertex2f(0, 270);
    glVertex2f(1000, 270);
    glVertex2f(1000, 250);
    glVertex2f(0, 250);
    glEnd();
    glColor3f(0.4, 0.3, 0.2); // Railway sleepers
    for (int i = 0; i < 1000; i += 20) {
        glBegin(GL_LINES);
        glVertex2f(i, 250);
        glVertex2f(i, 270);
        glEnd();
    }
    glColor3f(0.8, 0.8, 0.8); // Rails
    glBegin(GL_LINES);
    glVertex2f(0, 268);
    glVertex2f(1000, 268);
    glVertex2f(0, 252);
    glVertex2f(1000, 252);
    glEnd();
}

// Function to draw the bridge structure (pillars and road surface)
void drawBridgeStructure() {
    glColor3f(0.4, 0.35, 0.3); // Bridge pillars
    for (int x = 0; x <= 1000; x += 120) {
        glBegin(GL_POLYGON);
        glVertex2f(x, 250);
        glVertex2f(x + 20, 250);
        glVertex2f(x + 20, 100);
        glVertex2f(x, 100);
        glEnd();
    }
    glColor3f(0.5, 0.45, 0.4); // Bridge road/surface
    glBegin(GL_QUADS);
    glVertex2f(0, 250);
    glVertex2f(1000, 250);
    glVertex2f(1000, 245);
    glVertex2f(0, 245);
    glEnd();
}

// Function to draw the bridge guard rails
void drawBridgeGuard() {
    glColor3f(0.3, 0.3, 0.3); // Vertical bars
    for (int x = 0; x <= 1000; x += 10) {
        glBegin(GL_LINES);
        glVertex2f(x, 270);
        glVertex2f(x, 285);
        glEnd();
    }
    glBegin(GL_LINES); // Horizontal bars
    glVertex2f(0, 285);
    glVertex2f(1000, 285);
    glVertex2f(0, 275);
    glVertex2f(1000, 275);
    glEnd();
}

void drawAirplane() {
    float y = 450.0f;

    // Main body
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(airplaneX, y);
    glVertex2f(airplaneX + 150, y);
    glVertex2f(airplaneX + 140, y + 20);
    glVertex2f(airplaneX + 10, y + 20);
    glEnd();

    // Tail
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(airplaneX + 10, y + 20);
    glVertex2f(airplaneX + 40, y + 20);
    glVertex2f(airplaneX + 30, y + 50);
    glVertex2f(airplaneX + 20, y + 50);
    glEnd();

    // Tail wings
    glBegin(GL_POLYGON);
    glVertex2f(airplaneX + 20, y + 10);
    glVertex2f(airplaneX + 50, y + 10);
    glVertex2f(airplaneX + 45, y + 15);
    glVertex2f(airplaneX + 25, y + 15);
    glEnd();

    // Windows
    glColor3f(0.4f, 0.6f, 0.8f);
    for (int i = 0; i < 6; i++) {
        drawRectangle(airplaneX + 30 + i * 15, y + 5, 10, 5, 0.4f, 0.6f, 0.8f);
    }

    // Engine
    glColor3f(0.5f, 0.5f, 0.5f);
    drawRectangle(airplaneX + 110, y + 5, 20, 10, 0.5f, 0.5f, 0.5f);

    // Nose
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_TRIANGLES);
    glVertex2f(airplaneX + 140, y + 20);
    glVertex2f(airplaneX + 150, y);
    glVertex2f(airplaneX + 140, y);
    glEnd();
}

// Function to draw the train
void drawTrain() {
    float baseY = 270;
    // Train coaches
    for (int i = 0; i < 5; ++i) {
        float cx = trainX + i * 80;
        glColor3f(0.2, 0.2, 0.8); // Coach body
        glBegin(GL_POLYGON);
        glVertex2f(cx, baseY);
        glVertex2f(cx + 70, baseY);
        glVertex2f(cx + 70, baseY + 40);
        glVertex2f(cx, baseY + 40);
        glEnd();
        glColor3f(0.1, 0.1, 0.5); // Coach top
        glBegin(GL_POLYGON);
        glVertex2f(cx, baseY + 40);
        glVertex2f(cx + 70, baseY + 40);
        glVertex2f(cx + 70, baseY + 45);
        glVertex2f(cx, baseY + 45);
        glEnd();
        glColor3f(0.9, 0.9, 1.0); // Windows
        for (int j = 0; j < 3; ++j) {
            float wx = cx + 10 + j * 20;
            glBegin(GL_POLYGON);
            glVertex2f(wx, baseY + 20);
            glVertex2f(wx + 10, baseY + 20);
            glVertex2f(wx + 10, baseY + 35);
            glVertex2f(wx, baseY + 35);
            glEnd();
        }
        glColor3f(0, 0, 0); // Wheels
        drawCircle(cx + 15, baseY, 5);
        drawCircle(cx + 55, baseY, 5);
    }
    // Train engine
    float x = trainX + 5 * 80;
    glColor3f(0.7, 0.0, 0.0); // Engine body
    glBegin(GL_POLYGON);
    glVertex2f(x, baseY);
    glVertex2f(x + 70, baseY);
    glVertex2f(x + 70, baseY + 50);
    glVertex2f(x, baseY + 50);
    glEnd();
    glColor3f(0.2, 0.2, 0.2); // Chimney/exhaust
    glBegin(GL_POLYGON);
    glVertex2f(x + 50, baseY + 50);
    glVertex2f(x + 60, baseY + 50);
    glVertex2f(x + 60, baseY + 70);
    glVertex2f(x + 50, baseY + 70);
    glEnd();
    glColor3f(0.5, 0, 0); // Front triangular part
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 70, baseY);
    glVertex2f(x + 90, baseY);
    glVertex2f(x + 70, baseY + 30);
    glEnd();
    glColor3f(0.9, 0.9, 1.0); // Front window
    glBegin(GL_POLYGON);
    glVertex2f(x + 5, baseY + 30);
    glVertex2f(x + 25, baseY + 30);
    glVertex2f(x + 25, baseY + 45);
    glVertex2f(x + 5, baseY + 45);
    glEnd();
    glColor3f(0, 0, 0); // Engine wheels
    drawCircle(x + 15, baseY, 6);
    drawCircle(x + 55, baseY, 6);
}

// Function to draw the river
void drawRiver() {
    glBegin(GL_POLYGON); // River body
    glColor3f(0.0, 0.3, 0.6); // Darker blue at bottom
    glVertex2f(0, 0);
    glVertex2f(1000, 0);
    glColor3f(0.0, 0.5, 0.8); // Lighter blue at top
    glVertex2f(1000, 120);
    glVertex2f(0, 120);
    glEnd();

    // River banks (wavy brown)
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.4, 0.2);
    glVertex2f(0, 120);
    glVertex2f(50, 125);
    glVertex2f(100, 130);
    glVertex2f(150, 122);
    glVertex2f(200, 135);
    glVertex2f(250, 120);
    glVertex2f(300, 125);
    glVertex2f(350, 120);
    glVertex2f(400, 128);
    glVertex2f(450, 122);
    glVertex2f(500, 130);
    glVertex2f(550, 120);
    glVertex2f(600, 125);
    glVertex2f(650, 120);
    glVertex2f(700, 130);
    glVertex2f(750, 125);
    glVertex2f(800, 120);
    glVertex2f(850, 130);
    glVertex2f(900, 125);
    glVertex2f(950, 120);
    glVertex2f(1000, 122);
    glVertex2f(1000, 120);
    glVertex2f(0, 120);
    glEnd();

    // River vegetation/reeds
    for (int x = 30; x < 1000; x += 80) {
        glColor3f(0.1, 0.6, 0.3);
        glBegin(GL_TRIANGLES);
        glVertex2f(x, 120);
        glVertex2f(x + 5, 130);
        glVertex2f(x + 10, 120);
        glEnd();
    }

    // Water ripples/highlights
    glColor3f(0.7, 0.8, 0.9);
    for (float x = 0; x <= 1000; x += 60) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 30; ++i) {
            float xi = x + i * 2;
            float yi = 100 + 5 * sin(xi * 0.02);
            glVertex2f(xi, yi);
        }
        glEnd();
    }
}

// Function to draw a cloud
void drawCloud(float x, float y) {
    glColor3f(0.95, 0.95, 0.95);
    drawCircle(x, y, 15);
    drawCircle(x + 20, y, 15);
    drawCircle(x + 10, y + 10, 15);
}

// Function to draw the road
void drawRoad() {
    drawRectangle(0, 0, 1000, 70, 0.15, 0.15, 0.15); // Main road surface
    glColor3f(1, 1, 0.8); // Lane markers
    for (int i = 0; i < 1000; i += 40) {
        glBegin(GL_LINES);
        glVertex2f(i, 35);
        glVertex2f(i + 10, 35);
        glEnd();
    }
    glColor3ub(193,155,107); // Sidewalk/shoulder
    glBegin(GL_QUADS);
    glVertex2f(0, 150);
    glVertex2f(1000, 150);
    glVertex2f(1000, 140);
    glVertex2f(0, 140);
    glEnd();
}

// Function to draw a car
void drawCar(float x, float y, float r, float g, float b) {
    glColor3f(r, g, b); // Car body
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 80, y);
    glVertex2f(x + 80, y + 30);
    glVertex2f(x, y + 30);
    glEnd();

    glColor3f(r * 0.7f, g * 0.7f, b * 0.7f); // Car cabin
    glBegin(GL_POLYGON);
    glVertex2f(x + 15, y + 30);
    glVertex2f(x + 65, y + 30);
    glVertex2f(x + 55, y + 50);
    glVertex2f(x + 25, y + 50);
    glEnd();

    // Wheels
    glColor3f(0.05f, 0.05f, 0.05f);
    float radius = 10.0f;
    int triangleAmount = 20;
    GLfloat twicePi = 2.0f * 3.1416f;

    // First wheel
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + 20, y);
    for (int i = 0; i <= triangleAmount; ++i)
        glVertex2f(
            x + 20 + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount)));
    glEnd();

    // Second wheel
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + 60, y);
    for (int i = 0; i <= triangleAmount; ++i)
        glVertex2f(
            x + 60 + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount)));
    glEnd();
}

// Function to draw an ambulance
void drawAmbulance(float x, float y) {
    glColor3f(0.9, 0.1, 0.1); // Ambulance body (red)
    drawRectangle(x, y, 100, 35, 0.9, 0.1, 0.1);

    glColor3f(0.8, 0.05, 0.05); // Front cabin/hood
    glBegin(GL_POLYGON);
    glVertex2f(x + 70, y);
    glVertex2f(x + 100, y);
    glVertex2f(x + 100, y + 25);
    glVertex2f(x + 80, y + 35);
    glEnd();

    glColor3f(0.6, 0.8, 1.0); // Windows
    drawRectangle(x + 5, y + 15, 25, 15, 0.6, 0.8, 1.0);
    drawRectangle(x + 75, y + 10, 20, 15, 0.6, 0.8, 1.0);

    glColor3f(1.0, 1.0, 1.0); // White stripe
    drawRectangle(x + 5, y + 30, 90, 5, 1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 1.0); // Red cross background
    drawRectangle(x + 40, y + 32, 20, 10, 1.0, 1.0, 1.0);
    glColor3f(0.9, 0.1, 0.1); // Red cross
    glBegin(GL_LINES);
    glVertex2f(x + 40, y + 37);
    glVertex2f(x + 60, y + 37);
    glVertex2f(x + 50, y + 32);
    glVertex2f(x + 50, y + 42);
    glEnd();

    glColor3f(0.05, 0.05, 0.05); // Wheels (outer)
    drawCircle(x + 20, y, 10);
    drawCircle(x + 80, y, 10);
    glColor3f(0.2, 0.2, 0.2); // Wheels (inner)
    drawCircle(x + 20, y, 6);
    drawCircle(x + 80, y, 6);

    // Siren logic (flashing light)
    sirenTimer += 0.1;
    if (sirenTimer > 0.5) {
        sirenOn = !sirenOn;
        sirenTimer = 0;
    }
    if (sirenOn) {
        glColor3f(1.0, 0.7, 0.0); // Orange/yellow siren light
        drawRectangle(x + 45, y + 35, 10, 10, 1.0, 0.7, 0.0);
    }
    glColor3f(1.0, 1.0, 0.7); // Headlight/taillight
    drawRectangle(x + 95, y + 5, 5, 5, 1.0, 1.0, 0.7);
}

// Function to draw a bus
void drawBus(float x, float y) {
    // Main body
    glColor3f(BUS_COLOR_R, BUS_COLOR_G, BUS_COLOR_B);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 150, y);
    glVertex2f(x + 150, y + 60);
    glVertex2f(x + 140, y + 70);
    glVertex2f(x + 10, y + 70);
    glVertex2f(x, y + 60);
    glEnd();

    // Windows
    glColor3f(0.7f, 0.9f, 1.0f);
    for (int i = 0; i < 5; ++i) {
        drawRectangle(x + 15 + i * 25, y + 40, 20, 20, 0.7f, 0.9f, 1.0f);
    }

    // Front window
    glBegin(GL_POLYGON);
    glVertex2f(x + 140, y + 70);
    glVertex2f(x + 150, y + 60);
    glVertex2f(x + 150, y + 50);
    glVertex2f(x + 140, y + 50);
    glEnd();

    // Side stripe
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y + 60);
    glVertex2f(x + 150, y + 60);
    glVertex2f(x + 150, y + 55);
    glVertex2f(x, y + 55);
    glEnd();

    // Wheels
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle(x + 30, y, 15);
    drawCircle(x + 120, y, 15);

    // Wheel hubs
    glColor3f(0.5f, 0.5f, 0.5f);
    drawCircle(x + 30, y, 8);
    drawCircle(x + 120, y, 8);

    // Headlights
    glColor3f(1.0f, 1.0f, 0.8f);
    drawRectangle(x + 145, y + 10, 5, 10, 1.0f, 1.0f, 0.8f);
}

// Function to initialize raindrops
void initRain() {
    raindrops.clear();
    for (int i = 0; i < 1000; ++i) {
        Raindrop drop;
        drop.x = rand() % 1000;
        drop.y = rand() % 600 + 150; // Start drops above visible area
        drop.speed = 5 + rand() % 10;
        drop.length = 5 + rand() % 10;
        raindrops.push_back(drop);
    }
}

// Function to draw raindrops
void drawRain() {
    if (!isRaining) return;
    glColor3f(0.5, 0.5, 1.0); // Blueish raindrops
    glBegin(GL_LINES);
    for (auto& drop : raindrops) {
        glVertex2f(drop.x, drop.y);
        glVertex2f(drop.x - 2, drop.y - drop.length); // Slanted drops
    }
    glEnd();
}

// Function to update raindrop positions
void updateRain() {
    if (!isRaining) return;
    for (auto& drop : raindrops) {
        drop.x += 2.0; // Simulate wind
        drop.y -= drop.speed;
        if (drop.y < 0) { // Reset if off screen
            drop.x = rand() % 1000;
            drop.y = rand() % 600 + 150;
            drop.speed = 5 + rand() % 10;
            drop.length = 5 + rand() % 10;
        }
    }
}

// Function to draw a hospital building
void drawHospital(float x, float y, float width, float height) {
    drawRectangle(x, y, width, height, 0.95, 0.95, 0.95); // Hospital body
    glColor3f(currentMode == 1 ? 1.0 : 0.5, currentMode == 1 ? 1.0 : 0.7, currentMode == 1 ? 0.0 : 0.9); // Windows
    for (float i = x + 10; i < x + width - 10; i += 20) {
        for (float j = y + 10; j < y + height - 10; j += 20) {
            drawRectangle(i, j, 10, 10,
                            currentMode == 1 ? 1.0 : 0.5,
                            currentMode == 1 ? 1.0 : 0.7,
                            currentMode == 1 ? 0.0 : 0.9);
        }
    }
    glColor3f(0.8, 0.0, 0.0); // Red cross symbol
    float crossX = x + width / 2 - 5;
    float crossY = y + height - 40;
    drawRectangle(crossX, crossY, 10, 30, 0.8, 0.0, 0.0);
    drawRectangle(crossX - 10, crossY + 10, 30, 10, 0.8, 0.0, 0.0);
}

// Function to draw a roadlight
void drawRoadlight(float x, float y) {
    glColor3f(0.25, 0.25, 0.25); // Pole
    drawRectangle(x, y, 5, 80, 0.25, 0.25, 0.25);
    drawRectangle(x, y + 75, 30, 5, 0.25, 0.25, 0.25); // Arm
    if (currentMode == 1 || currentMode == 2) { // Lights on at night/evening
        glColor3f(1.0, 0.9, 0.0);
        drawCircle(x + 30, y + 77.5, 5);
    } else { // Lights off during day
        glColor3f(0.6, 0.6, 0.6);
        drawCircle(x + 30, y + 77.5, 5);
    }
}

// Function to draw a park bench
void drawParkBench(float x, float y) {
    glColor3f(0.4f, 0.25f, 0.1f); // Legs
    drawRectangle(x, y, 5, 20, 0.4f, 0.25f, 0.1f);
    drawRectangle(x + 40, y, 5, 20, 0.4f, 0.25f, 0.1f);
    glColor3f(0.7f, 0.5f, 0.3f); // Seat
    drawRectangle(x - 5, y + 15, 55, 10, 0.3, 0.3, 0.3); // Back support
    drawRectangle(x - 5, y + 25, 55, 10, 0.7f, 0.5f, 0.3f);
    glColor3f(0.4f, 0.25f, 0.1f); // Additional back legs
    drawRectangle(x, y + 20, 5, 15, 0.4f, 0.25f, 0.1f);
    drawRectangle(x + 40, y + 20, 5, 15, 0.4f, 0.25f, 0.1f);
    glColor3f(0.7f, 0.5f, 0.3f); // Top backrest
    drawRectangle(x - 5, y + 35, 55, 5, 0.7f, 0.5f, 0.3f);
}

// Function to draw a bus stop
void drawBusStop(float x, float y) {
    float baseY = y;
    glColor3f(0.5f, 0.5f, 0.5f); // Poles
    drawRectangle(x, baseY, 5, 50, 0.5f, 0.5f, 0.5f);
    drawRectangle(x + 60, baseY, 5, 50, 0.5f, 0.5f, 0.5f);
    glColor3f(0.7f, 0.7f, 0.7f); // Roof
    drawRectangle(x - 10, baseY + 50, 85, 10, 0.7f, 0.7f, 0.7f);
    drawParkBench(x + 10, baseY + 5); // Bench at bus stop
    glColor3f(0.1f, 0.1f, 0.1f); // Text color
    glRasterPos2f(x + 10, baseY + 53);
    const char* text = "  BusStop";
    for (int i = 0; text[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

// Function to draw thunder flash
void drawThunder() {
    if (thunderActive || thunderBlinking) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.7f); // White flash with transparency
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(1000, 0);
        glVertex2f(1000, 600);
        glVertex2f(0, 600);
        glEnd();
    }
}

// Main display function
void display() {
    // Background color based on current mode
    if (currentMode == 0) // Day
        glClearColor(0.6, 0.9, 1.0, 1.0);
    else if (currentMode == 1) // Night
        glClearColor(0.0, 0.0, 0.15, 1.0);
    else if (currentMode == 2) // Evening (sunset/sunrise)
        glClearColor(0.9, 0.6, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawSun();
    drawMoon();

    drawCloud(cloudX1, 500);
    drawCloud(cloudX2, 520);
    drawCloud(cloudX3, 550);
    drawThunder(); // Draw thunder flash if active
    drawMountains();
    //Background buildings (behind main buildings but in front of distant mountains)
    drawBackgroundBuilding(3, 200, 60, 180, 0.6, 0.5, 0.4);
    drawBackgroundBuilding(230, 230, 110, 190, 0.6, 0.6, 0.5);
    drawBackgroundBuilding(370, 200, 55, 190, 0.6, 0.5, 0.5);
    drawBackgroundBuilding(450, 220, 60, 170, 0.5, 0.6, 0.6);
    drawBackgroundBuilding(540, 210, 70, 180, 0.6, 0.6, 0.5);
    drawBackgroundBuilding(665, 150, 50, 185, 0.5, 0.6, 0.6);
    drawBackgroundBuilding(720, 150, 65, 200, 0.7, 0.5, 0.5);
    drawBackgroundBuilding(900, 210, 80, 180, 0.5, 0.5, 0.6);

    drawRiver();
    drawRoad();
    drawBusStop(510, 60);
    drawAirplane();
    drawResidentialBuilding(30, 150, 80, 290);
    drawSchoolBuilding(235, 150, 100, 200);
    drawBangladeshiCommercial(120, 150, 100, 260);
    drawBangladeshiHighRise(350, 150, 90, 290);
    drawResidentialBuilding(460, 150, 80, 210);
    drawBangladeshiCommercial(560, 150, 100, 260);
    drawHospital(790, 150, 100, 270);
    drawBangladeshiStoreBuilding(900, 150, 120, 160);

    // Trees
    drawTree(23, 150);
    drawTree(134, 150);
    drawTree(253, 150);
    drawTree(348, 150);
    drawTree(453, 150);
    drawTree(548, 150);
    drawTree(663, 150);
    drawTree(775, 150);
    drawTree(908, 150);

    drawTrain();
    drawBridgeTrack();
    drawBridgeStructure();
    drawBridgeGuard();

    drawRain(); // Draw raindrops if it's raining

    // Roadlights
    for (int i = 50; i < 1000; i += 150) {
        drawRoadlight(i, 70);
    }

    // Vehicles
    drawBus(busPosX, 50);
    drawCar(carPosX, 50, 0.8f, 0.2f, 0.2f);
    drawAmbulance(ambulancePosX, 50);
    drawCar(carPosX2, 10, 0.1f, 0.4f, 0.7f);

    drawParkBench(900, 140); // Another park bench example

    glutSwapBuffers();
}

// Animation update function
void update(int value) {
    angle += 0.05f; // For general animation/rotation (if used)

    // Vehicle movement
    trainX += trainSpeed;
    if (trainX > 1000)
        trainX = -600;

    carPosX += 5.0f;
    if (carPosX > 1000)
        carPosX = -100;

    ambulancePosX += 3.0f;
    if (ambulancePosX > 1000)
        ambulancePosX = -150;

    if (!busStopped) {
        busPosX += 2.0f;
        if (busPosX > 1000)
            busPosX = -200;
    }

    carPosX2 -= 4.0f;
    if (carPosX2 < -100)
        carPosX2 = 1000;
    airplaneX += airplaneSpeed;
    if (airplaneX > 1200) // Reset when off screen to the right
        airplaneX = -200;


    // Cloud movement
    cloudX1 -= cloudSpeed;
    cloudX2 -= cloudSpeed;
    cloudX3 -= cloudSpeed;
    if (cloudX1 < -400)
        cloudX1 = 1000;
    if (cloudX2 < -400)
        cloudX2 = 1000;
    if (cloudX3 < -400)
        cloudX3 = 1000;

    updateRain(); // Update raindrop positions

// Thunder logic
if (thunderActive) {
    if (!thunderBlinking) {
        thunderBlinking = true;
        thunderBlinks = 0;
        thunderBlinkTimer = 5; // Short duration for each blink
    }

    if (thunderBlinking) {
        thunderBlinkTimer--;
        if (thunderBlinkTimer <= 0) {
            thunderBlinks++;
            if (thunderBlinks >= 6) { // 3 blinks (on-off counts as 2)
                thunderActive = false;
                thunderBlinking = false;
            } else {
                // Toggle visibility for blinking effect
                thunderBlinkTimer = (thunderBlinks % 2 == 0) ? 10 : 5;
            }
        }
    }
}
    glutPostRedisplay(); // Request redraw
    glutTimerFunc(16, update, 0); // ~60 frames per second
}

// Keyboard input handler
void handleKeys(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        isRaining = !isRaining;
        if (isRaining)
            initRain(); // Initialize raindrops when rain starts
    } else if (key == 'd' || key == 'D')
        currentMode = 0; // Day mode
    else if (key == 'n' || key == 'N')
        currentMode = 1; // Night mode
    else if (key == 'e' || key == 'E')
        currentMode = 2; // Evening mode
    else if (key == 's' || key == 'S') {
        busStopped = !busStopped; // Toggle bus stop
    }
    else if (key == 'a' || key == 'A') {
        // Speed up airplane
        airplaneSpeed += 0.5f;
        if (airplaneSpeed > 10.0f)
            airplaneSpeed = 10.0f;
    } else if (key == 'z' || key == 'Z') {
        // Slow down airplane
        airplaneSpeed -= 0.5f;
        if (airplaneSpeed < 0.5f)
            airplaneSpeed = 0.5f;
    }

    glutPostRedisplay();
}

// Mouse input handler
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        trainSpeed -= 0.5f;
        if (trainSpeed < 0.0f)
            trainSpeed = 0.0f;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        trainSpeed += 0.5f;
        if (trainSpeed > 100.0f)
            trainSpeed = 100.0f;
    } else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        thunderActive = true;
        thunderBlinks = 0; // Reset blink counter
    }
    glutPostRedisplay();
}

// Initialization function
void init() {
    glClearColor(0.6, 0.9, 1.0, 1.0); // Default clear color (Day sky)
    gluOrtho2D(0, 1000, 0, 600); // Set up 2D orthographic projection
    srand(time(0)); // Seed random number generator for raindrops
    initRain(); // Initialize raindrops
    glEnable(GL_BLEND); // Enable blending for transparent thunder flash
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("A journey by Train"); // Window title
    init();
    glutDisplayFunc(display); // Register display callback
    glutTimerFunc(0, update, 0); // Register timer for animation
    glutKeyboardFunc(handleKeys); // Register keyboard callback
    glutMouseFunc(mouse); // Register mouse callback
    glutMainLoop(); // Enter GLUT event processing loop
    return 0;
}
scene 04: #include <GL/glut.h>
#include <cmath>
#include <cstdlib> // for rand()
#include <algorithm> // for std::fmin, std::fmax

// Global variables
bool isDaytime = true;
bool isMorning = false;

float trainX = -320.0f; // Adjusted initial position to be fully off-screen for a smooth start
float trainSpeed = 2.0f;
float cloudPos = 0.0f;
float sunMoonPos = 0.0f; // 0.0 means sun/moon is at its starting side, 1.0 means it's at the ending side
float boatPos = -150.0f;
float boatSpeed = 1.0f;
bool isRaining = false;
float windmillAngle = 0.0f;

bool showRainbow = false;
int rainbowTimer = 0;



// Airplane position and speed
float airplanePos = 200.0f;
float airplaneSpeed = 3.0f;
float angle = 0.0f;
float airplaneX = 100.0f;  // Adjust to your desired starting position
float airplaneY = 100.0f;


// Additional boats
float boat2Pos = 1100.0f;    // Starting from the right
float boat2Speed = 0.8f;     // Slightly slower than main boat
float boat3Pos = -300.0f;    // Another boat starting from left
float fasterBoatSpeed = 1.2f;     // Use a separate variable for the third boat's speed

//Car
float car1X = -200;  // Starts from the left, moves right
float car2X = 1000;  // Starts from the right, moves left


// New global variables for lightning
bool isLightning = false;
int lightningTimer = 0; // Timer to control flash duration
const int LIGHTNING_DURATION = 100; // Flash duration in milliseconds (e.g., 100ms)

struct Color {
    float r, g, b;
};


// ----------- Day Colors -----------

Color skyDay = {0.4f, 0.7f, 1.0f};          // Bright blue sky
Color groundDay = {0.2f, 0.45f, 0.1f};      // Deep lush green
Color riverColorDay = {0.05f, 0.3f, 0.6f};  // Deep river blue

Color buildingColorDay = {0.27f, 0.51f, 0.71f};   // Steel Blue
Color windowColorDay = {0.6f, 0.75f, 0.95f};      // Cool light blue

// ----------- Night Colors -----------
Color skyNight = {0.02f, 0.03f, 0.15f};        // Dark blue
Color groundNight = {0.04f, 0.07f, 0.05f};     // Very dark green
Color riverColorNight = {0.02f, 0.05f, 0.15f}; // Midnight blue

Color buildingColorNight = {0.27f, 0.51f, 0.71f};  // Steel Blue
Color windowColorNight = {0.95f, 0.85f, 0.3f};     // Warm yellow lights

// ----------- Morning Colors -----------
Color skyMorning = {0.0f, 0.0f, 0.0f};            // Placeholder
Color groundMorning = {0.25f, 0.3f, 0.2f};         // Dewy dark green
Color riverColorMorning = {0.15f, 0.25f, 0.45f};   // Bluish-violet

Color buildingColorMorning = {0.27f, 0.51f, 0.71f}; // Steel Blue
Color windowColorMorning = {0.7f, 0.6f, 0.8f};      // Soft lavender-blue


struct Raindrop {
    float x, y;
    float speed;
};

#define MAX_RAINDROPS 200
Raindrop raindrops[MAX_RAINDROPS];

struct Star {
    float x, y;
    float size;
};

#define MAX_STARS 100
Star stars[MAX_STARS];

// Function to draw a filled circle
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; ++i) {
        float theta = 2.0f * 3.1416f * i / 100;
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Function to draw a filled circle with specified color and segments
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

// New helper function to draw a 5-pointed star
void drawFivePointedStar(float cx, float cy, float outerRadius, float innerRadius, Color c) {
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_TRIANGLE_FAN);

    // Center point for the star (optional, makes it easier to fill)
    glVertex2f(cx, cy);

    // Draw 10 vertices for a 5-pointed star (5 outer points, 5 inner points)
    // Adjust angle to make the star upright
    for (int i = 0; i <= 10; ++i) {
        float angle = M_PI / 5.0f * i; // Angle for each segment (2 segments per point)
        float r = (i % 2 == 0) ? outerRadius : innerRadius; // Alternate between outer and inner radius
        glVertex2f(cx + r * cos(angle - M_PI / 2.0f), cy + r * sin(angle - M_PI / 2.0f)); // Rotate to start upright
    }
    glEnd();
}

void initRain() {
    for (int i = 0; i < MAX_RAINDROPS; ++i) {
        raindrops[i].x = rand() % 1000;
        raindrops[i].y = rand() % 600;
        raindrops[i].speed = 4.0f + (rand() % 5);
    }
}

void initStars() {
    for (int i = 0; i < MAX_STARS; ++i) {
        stars[i].x = rand() % 1000;
        stars[i].y = 200 + rand() % 400; // Stars primarily in the upper sky
        stars[i].size = (rand() % 3) + 1.0f;
    }
}

void drawRain() {
    if (!isRaining) return;
    glColor3f(0.8f, 0.8f, 1.0f); // Brighter blue for raindrops
    glLineWidth(2);
    glBegin(GL_LINES);
    for (int i = 0; i < MAX_RAINDROPS; ++i) {
        float x = raindrops[i].x;
        float y = raindrops[i].y;
        glVertex2f(x, y);
        glVertex2f(x, y - 15); // Draw a slightly longer line for each drop
    }
    glEnd();
    glLineWidth(1); // Reset line width
}

void drawStars() {
    // Only draw stars if it's night and not morning
    if (isDaytime || isMorning) return;
    glColor3f(1.0f, 1.0f, 1.0f); // White stars
    glBegin(GL_POINTS);
    for (int i = 0; i < MAX_STARS; ++i) {
        glPointSize(stars[i].size);
        glVertex2f(stars[i].x, stars[i].y);
    }
    glEnd();
    glPointSize(1); // Reset point size
}

void updateRain() {
    if (!isRaining) return;
    for (int i = 0; i < MAX_RAINDROPS; ++i) {
        raindrops[i].y -= raindrops[i].speed;
        if (raindrops[i].y < 0) { // If raindrop goes off screen, reset it to the top
            raindrops[i].x = rand() % 1000;
            raindrops[i].y = 600;
            raindrops[i].speed = 4.0f + (rand() % 5);
        }
    }
}

void drawSunMoon() {
    if (isMorning) {
        // Reddish/Orange sun for morning rise
        // sunMoonPos goes from 0 (off-screen left) to 0.5 (mid-morning)
        drawCircle(sunMoonPos * 1000, 500, 40, 32, {1.0f, 0.6f, 0.2f}); // Orange/Red
    } else if (isDaytime) {
        // Yellow Sun for daytime, moves from right to left
        // sunMoonPos goes from 0 (right) to 1 (left)
        drawCircle(900 - sunMoonPos * 800, 500, 40, 32, {1.0f, 0.95f, 0.3f}); // Bright Yellow Sun
    } else { // Night
        // Moon, moves from left to right
        // sunMoonPos goes from 0 (left) to 1 (right)
        drawCircle(100 + sunMoonPos * 800, 500, 35, 32, {0.95f, 0.95f, 0.9f}); // Bright Moon
        // Craters on moon
        drawCircle(110 + sunMoonPos * 800, 510, 8, 16, {0.8f, 0.8f, 0.8f});
        drawCircle(90 + sunMoonPos * 800, 490, 5, 16, {0.8f, 0.8f, 0.8f});
    }
}

void drawClouds() {
    for (int i = 0; i < 4; i++) {
        float x = fmod(cloudPos + i * 250, 1100) - 100; // Loop clouds horizontally
        // Clouds can be slightly darker/more subtle in morning
        Color cloudColor;
        if (isMorning) {
            cloudColor = {0.85f, 0.85f, 0.9f};
        } else if (isDaytime) {
            cloudColor = {0.95f, 0.95f, 1.0f};
        } else {
            cloudColor = {0.7f, 0.7f, 0.8f};
        }

        drawCircle(x, 450, 20, 16, cloudColor);
        drawCircle(x + 15, 460, 25, 16, cloudColor);
        drawCircle(x + 40, 450, 20, 16, cloudColor);
        drawCircle(x + 25, 435, 25, 16, cloudColor);
    }
}

void drawMountains() {
    glBegin(GL_TRIANGLES);
    // Adjust mountain color for morning
    if (isMorning) {
        glColor3f(0.15f, 0.25f, 0.15f); // Darker, silhouetted mountains for morning
    } else if (isDaytime) {
        glColor3f(0.25f, 0.4f, 0.2f); // Green mountains during day
    } else {
        glColor3f(0.1f, 0.15f, 0.1f); // Dark mountains at night
    }

    // Adjusted mountain base to be lower (y=100) to appear behind the city/river
    // Peaks adjusted relative to this new base
    float base_y = 100.0f; // New base Y-coordinate for mountains
    float peak_height_offset = 200.0f; // Height from base to peak

    for (int i = 0; i < 5; i++) {
        float x = i * 250 - 50; // Offset and spacing for mountains
        glVertex2f(x, base_y);
        glVertex2f(x + 125, base_y + peak_height_offset); // Peak
        glVertex2f(x + 250, base_y);
    }
    glEnd();
}

void drawRainbow() {
    if (!showRainbow) return;

    float cx =460, cy=450; // Rainbow center
    float radius = 100;

    float colors[7][3] = {
        {1.0, 0.0, 0.0},  // Red
        {1.0, 0.5, 0.0},  // Orange
        {1.0, 1.0, 0.0},  // Yellow
        {0.0, 1.0, 0.0},  // Green
        {0.0, 0.0, 1.0},  // Blue
        {0.29, 0.0, 0.51},// Indigo
        {0.56, 0.0, 1.0}  // Violet
    };

    for (int j = 0; j < 7; j++) {
        glColor3f(colors[j][0], colors[j][1], colors[j][2]);
        glBegin(GL_LINE_STRIP);
        for (float i = 0; i <= 180; i += 1) {
            float angle = i * 3.14159 / 180;
            float x = cx + cos(angle) * (radius + j * 5);
            float y = cy + sin(angle) * (radius + j * 5);
            glVertex2f(x, y);
        }
        glEnd();
    }
}


 void rainbowOff(int value) {
    showRainbow = false;
    glutPostRedisplay();


    }


// Enhanced function to draw big visible hills
void drawHills() {
    glBegin(GL_TRIANGLES);

    // Hill colors based on time
    if (isMorning) {
        glColor3f(0.2f, 0.3f, 0.2f); // Morning - dark green
    } else if (isDaytime) {
        glColor3f(0.3f, 0.5f, 0.25f); // Day - brighter green
    } else {
        glColor3f(0.15f, 0.2f, 0.15f); // Night - darker green
    }

    float hill_base = 200.0f;       // Slightly above ground level to make visible
    float hill_height = 180.0f;     // Much taller hills

    // Hill 1
    glVertex2f(-200, hill_base);
    glVertex2f(250, hill_base + hill_height);
    glVertex2f(700, hill_base);

    // Hill 2 (overlapping slightly)
    glVertex2f(400, hill_base);
    glVertex2f(800, hill_base + hill_height * 0.9f);
    glVertex2f(1200, hill_base);

    // Hill 3
    glVertex2f(900, hill_base);
    glVertex2f(1350, hill_base + hill_height * 0.8f);
    glVertex2f(1800, hill_base);

    glEnd();
}

// Function to draw a simple tree
void drawTree(float x, float y) {
    // Tree Trunk (Brown)
    glColor3f(0.5f, 0.35f, 0.05f); // Brown color
    glBegin(GL_QUADS);
    glVertex2f(x - 10, y);
    glVertex2f(x + 10, y);
    glVertex2f(x + 10, y + 50);
    glVertex2f(x - 10, y + 50);
    glEnd();

    // Tree Leaves (Green - a simple circle or multiple circles for a bushier look)
    glColor3f(0.2f, 0.5f, 0.1f); // Darker green for leaves
    drawCircle(x, y + 70, 30); // Top part of the tree
    drawCircle(x - 15, y + 50, 25); // Left part
    drawCircle(x + 15, y + 50, 25); // Right part
}


void drawWindmill() {
    float x = 950;  // ✅ Near the right edge, but within view
    float y = 185;

    // Windmill tower
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.4f, 0.4f); // Grey tower
    glVertex2f(x - 10, y);
    glVertex2f(x + 10, y);
    glVertex2f(x + 5, y + 200);
    glVertex2f(x - 5, y + 200);
    glEnd();

    glPushMatrix();
    glTranslatef(x, y + 200, 0); // Translate to pivot point for blades
    glRotatef(windmillAngle, 0, 0, 1); // Rotate blades

    // Blades
    for (int i = 0; i < 4; i++) {
        glRotatef(90, 0, 0, 1); // Rotate for each blade
        glColor3f(0.7f, 0.7f, 0.7f); // Light grey blades
        glBegin(GL_TRIANGLES);
        glVertex2f(0, 0);
        glVertex2f(50, 10);
        glVertex2f(100, 0);
        glEnd();
    }

    drawCircle(0, 0, 10, 16, {0.4f, 0.4f, 0.4f}); // Center hub
    glPopMatrix();
}
// Function to draw seating zones with green colors
void drawSeatingZones() {
    // Seating zone 1 (left side) - Green grassy area
    if (isMorning) {
        glColor3f(0.3f, 0.5f, 0.2f); // Morning green
    } else if (isDaytime) {
        glColor3f(0.4f, 0.7f, 0.3f); // Day bright green
    } else {
        glColor3f(0.2f, 0.4f, 0.1f); // Night dark green
    }
    glBegin(GL_QUADS);
    glVertex2f(50, 170);
    glVertex2f(150, 170);
    glVertex2f(150, 190);
    glVertex2f(50, 190);
    glEnd();

    // Draw 3 benches in left seating area with more detail
    for (int i = 0; i < 3; i++) {
        float benchX = 60 + i*30;

        // Bench seat (main part)
        glColor3f(0.5f, 0.35f, 0.2f); // Wood color
        glBegin(GL_QUADS);
        glVertex2f(benchX, 175);
        glVertex2f(benchX + 20, 175);
        glVertex2f(benchX + 20, 180);
        glVertex2f(benchX, 180);
        glEnd();

        // Bench back
        glBegin(GL_QUADS);
        glVertex2f(benchX, 180);
        glVertex2f(benchX + 20, 180);
        glVertex2f(benchX + 18, 185);
        glVertex2f(benchX + 2, 185);
        glEnd();

        // Bench legs
        glColor3f(0.4f, 0.3f, 0.15f); // Darker wood
        glBegin(GL_LINES);
        // Front legs
        glVertex2f(benchX + 3, 170); glVertex2f(benchX + 3, 175);
        glVertex2f(benchX + 17, 170); glVertex2f(benchX + 17, 175);
        // Back legs
        glVertex2f(benchX + 2, 180); glVertex2f(benchX + 2, 185);
        glVertex2f(benchX + 18, 180); glVertex2f(benchX + 18, 185);
        glEnd();
    }

    // Seating zone 2 (right side) - Green grassy area
    if (isMorning) {
        glColor3f(0.3f, 0.5f, 0.2f); // Morning green
    } else if (isDaytime) {
        glColor3f(0.4f, 0.7f, 0.3f); // Day bright green
    } else {
        glColor3f(0.2f, 0.4f, 0.1f); // Night dark green
    }
    glBegin(GL_QUADS);
    glVertex2f(800, 170);
    glVertex2f(900, 170);
    glVertex2f(900, 190);
    glVertex2f(800, 190);
    glEnd();

    // Draw 3 benches in right seating area with more detail
    for (int i = 0; i < 3; i++) {
        float benchX = 810 + i*30;

        // Bench seat (main part)
        glColor3f(0.5f, 0.35f, 0.2f); // Wood color
        glBegin(GL_QUADS);
        glVertex2f(benchX, 175);
        glVertex2f(benchX + 20, 175);
        glVertex2f(benchX + 20, 180);
        glVertex2f(benchX, 180);
        glEnd();

        // Bench back
        glBegin(GL_QUADS);
        glVertex2f(benchX, 180);
        glVertex2f(benchX + 20, 180);
        glVertex2f(benchX + 18, 185);
        glVertex2f(benchX + 2, 185);
        glEnd();

        // Bench legs
        glColor3f(0.4f, 0.3f, 0.15f); // Darker wood
        glBegin(GL_LINES);
        // Front legs
        glVertex2f(benchX + 3, 170); glVertex2f(benchX + 3, 175);
        glVertex2f(benchX + 17, 170); glVertex2f(benchX + 17, 175);
        // Back legs
        glVertex2f(benchX + 2, 180); glVertex2f(benchX + 2, 185);
        glVertex2f(benchX + 18, 180); glVertex2f(benchX + 18, 185);
        glEnd();
    }

    // Draw some small green trees in seating areas
    drawTree(70, 190); // Left seating area
    drawTree(130, 190);
    drawTree(820, 190); // Right seating area
    drawTree(880, 190);
}

// Updated road with green borders
void drawRoad() {
    // Main road surface (gray)
    glColor3f(0.2f, 0.2f, 0.2f); // Dark gray
    glBegin(GL_QUADS);
    glVertex2f(0, 150);
    glVertex2f(1000, 150);
    glVertex2f(1000, 185);
    glVertex2f(0, 185);
    glEnd();

    // Green borders/verges - changes with time of day
    if (isMorning) {
        glColor3f(0.25f, 0.45f, 0.15f); // Morning green
    } else if (isDaytime) {
        glColor3f(0.35f, 0.65f, 0.25f); // Day bright green
    } else {
        glColor3f(0.15f, 0.35f, 0.1f); // Night dark green
    }

    // Left green verge
    glBegin(GL_QUADS);
    glVertex2f(0, 185);
    glVertex2f(1000, 185);
    glVertex2f(1000, 200);
    glVertex2f(0, 200);
    glEnd();

    // Right green verge
    glBegin(GL_QUADS);
    glVertex2f(0, 140);
    glVertex2f(1000, 140);
    glVertex2f(1000, 150);
    glVertex2f(0, 150);
    glEnd();

    // Lane markings (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 1000; i += 80) {
        glBegin(GL_QUADS);
        glVertex2f(i + 20, 165);
        glVertex2f(i + 50, 165);
        glVertex2f(i + 50, 170);
        glVertex2f(i + 20, 170);
        glEnd();
    }

    // Road edges (white lines)
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(0, 150);
    glVertex2f(1000, 150);
    glVertex2f(0, 185);
    glVertex2f(1000, 185);
    glEnd();
    glLineWidth(1.0f);
}

void drawLight(float x1, float y1, float x2, float y2) {
    glColor3f(1.0f, 1.0f, 0.7f); // Soft yellow light
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawBuilding(float x, float y, float width, float height) {
    // Building structure
    Color buildingColor;
    Color windowColor;

    if (isMorning) {
        buildingColor = buildingColorMorning;
        windowColor = windowColorMorning;
    } else if (isDaytime) {
        buildingColor = buildingColorDay;
        windowColor = windowColorDay;
    } else {
        buildingColor = buildingColorNight;
        windowColor = windowColorNight;
    }

    glColor3f(buildingColor.r, buildingColor.g, buildingColor.b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Window grid calculation based on building size
    int rows = (int)(height / 40);
    int cols = (int)(width / 50);

    float winWidth = 20.0f;
    float winHeight = 20.0f;
    float xOffset = 15.0f;
    float yOffset = 15.0f;

    // Draw windows
    glColor3f(windowColor.r, windowColor.g, windowColor.b);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            float wx1 = x + xOffset + c * 40;
            float wy1 = y + yOffset + r * 30;
            float wx2 = wx1 + winWidth;
            float wy2 = wy1 + winHeight;

            glBegin(GL_QUADS);
            glVertex2f(wx1, wy1);
            glVertex2f(wx2, wy1);
            glVertex2f(wx2, wy2);
            glVertex2f(wx1, wy2);
            glEnd();

            // Lights are off during day and morning
            if (!isDaytime && !isMorning) {
                drawLight(wx1, wy1, wx2, wy2);
            }
        }
    }
}

// Draw multiple buildings with different sizes and positions
void drawBuildings() {
    drawBuilding(50, 185, 140, 320);    // Big building
    drawBuilding(220, 185, 120, 280);   // Medium building
    drawBuilding(370, 185, 100, 250);   // Smaller building
    drawBuilding(500, 185, 160, 350);   // Very big building
    drawBuilding(700, 185, 130, 300);   // Medium building
}

void drawHospital() {
    float x = 650;

    // Hospital structure
    Color hospitalColor;
if (isMorning) {
    hospitalColor = {0.6f, 0.2f, 0.3f};  // Light Meherun for morning
} else if (isDaytime) {
    hospitalColor = {0.5f, 0.0f, 0.1f};  // Deep Meherun for day
} else {
    hospitalColor = {0.3f, 0.0f, 0.05f}; // Dark Meherun for night
}

    glColor3f(hospitalColor.r, hospitalColor.g, hospitalColor.b);
    glBegin(GL_QUADS);
    glVertex2f(x, 185); glVertex2f(x + 120, 185);
    glVertex2f(x + 120, 360); glVertex2f(x, 360);
    glEnd();

    // Red cross
    glColor3f(0.9f, 0.1f, 0.1f); // Bright red cross
    glBegin(GL_QUADS);
    glVertex2f(x + 50, 300); glVertex2f(x + 70, 300);
    glVertex2f(x + 70, 340); glVertex2f(x + 50, 340);
    glVertex2f(x + 40, 315); glVertex2f(x + 80, 315);
    glVertex2f(x + 80, 325); glVertex2f(x + 40, 325);
    glEnd();

    // Windows
    Color hospitalWindowColor;
    if (isMorning) {
        hospitalWindowColor = {0.5f, 0.7f, 0.9f};
    } else if (isDaytime) {
        hospitalWindowColor = {0.7f, 0.8f, 1.0f};
    } else {
        hospitalWindowColor = {0.9f, 0.9f, 0.2f};
    }

    glColor3f(hospitalWindowColor.r, hospitalWindowColor.g, hospitalWindowColor.b);
    for (int i = 0; i < 3; ++i) {
        float y = 200 + i * 40;
        glBegin(GL_QUADS);
        glVertex2f(x + 20, y); glVertex2f(x + 45, y);
        glVertex2f(x + 45, y + 25); glVertex2f(x + 20, y + 25);
        glVertex2f(x + 75, y); glVertex2f(x + 100, y);
        glVertex2f(x + 100, y + 25); glVertex2f(x + 75, y + 25);
        glEnd();

        if (!isDaytime && !isMorning) { // Lights off during day and morning
            drawLight(x + 20, y, x + 45, y + 25);
            drawLight(x + 75, y, x + 100, y + 25);
        }
    }
}

void drawMosque() {
    float x = 800;

    // Main building
    Color mosqueColor;
    if (isMorning) {
        mosqueColor = {0.85f, 0.85f, 0.75f};
    } else if (isDaytime) {
        mosqueColor = {0.95f, 0.95f, 0.85f};
    } else {
        mosqueColor = {0.5f, 0.5f, 0.45f};
    }

    glColor3f(mosqueColor.r, mosqueColor.g, mosqueColor.b);
    glBegin(GL_QUADS);
    glVertex2f(x, 185); glVertex2f(x + 100, 185);
    glVertex2f(x + 100, 350); glVertex2f(x, 350);
    glEnd();

    // Dome
    Color domeColor;
    if (isMorning) {
        domeColor = {0.7f, 0.8f, 0.6f};
    } else if (isDaytime) {
        domeColor = {0.8f, 0.9f, 0.7f};
    } else {
        domeColor = {0.4f, 0.5f, 0.4f};
    }
    drawCircle(x + 50, 370, 30, 32, domeColor);

    // Minaret
    Color minaretColor;
    if (isMorning) {
        minaretColor = {0.8f, 0.8f, 0.7f};
    } else if (isDaytime) {
        minaretColor = {0.9f, 0.9f, 0.8f};
    } else {
        minaretColor = {0.5f, 0.5f, 0.45f};
    }

    glColor3f(minaretColor.r, minaretColor.g, minaretColor.b);
    glBegin(GL_QUADS);
    glVertex2f(x + 80, 185); glVertex2f(x + 90, 185);
    glVertex2f(x + 90, 420); glVertex2f(x + 80, 420);
    glEnd();

    // Minaret top (sphere/dome-like structure)
    drawCircle(x + 85, 425, 10, 16, domeColor);

    // Star on Minaret
    Color starColor;
    if (isMorning) {
        starColor = {0.9f, 0.8f, 0.1f}; // Gold for morning
    } else if (isDaytime) {
        starColor = {0.8f, 0.7f, 0.15f}; // Gold for day
    } else { // Night
        starColor = {1.0f, 0.95f, 0.1f}; // Bright gold for night
    }
    drawFivePointedStar(x + 85, 445, 12, 5, starColor);

    // Windows
    Color mosqueWindowColor;
    if (isMorning) {
        mosqueWindowColor = {0.5f, 0.7f, 0.9f};
    } else if (isDaytime) {
        mosqueWindowColor = {0.7f, 0.8f, 1.0f};
    } else {
        mosqueWindowColor = {0.9f, 0.9f, 0.2f};
    }

    glColor3f(mosqueWindowColor.r, mosqueWindowColor.g, mosqueWindowColor.b);
    for (int i = 0; i < 3; ++i) {
        float y_win = 200 + i * 40;
        glBegin(GL_QUADS);
        glVertex2f(x + 20, y_win); glVertex2f(x + 40, y_win);
        glVertex2f(x + 40, y_win + 25); glVertex2f(x + 20, y_win + 25);
        glVertex2f(x + 60, y_win); glVertex2f(x + 80, y_win);
        glVertex2f(x + 80, y_win + 25); glVertex2f(x + 60, y_win + 25);
        glEnd();

        if (!isDaytime && !isMorning) { // Lights off during day and morning
            drawLight(x + 20, y_win, x + 40, y_win + 25);
            drawLight(x + 60, y_win, x + 80, y_win + 25);
        }
    }
}

void drawBridgeStructure() {
    glColor3f(0.35f, 0.25f, 0.15f); // Darker brown pillars
    for (int x = 0; x <= 260; x += 40) {
        glBegin(GL_POLYGON);
        glVertex2f(x, 250);
        glVertex2f(x + 15, 250);
        glVertex2f(x + 15, 180);
        glVertex2f(x, 180);
        glEnd();
    }
    glColor3f(0.6f, 0.5f, 0.4f); // Lighter brown deck under rails
    glBegin(GL_QUADS);
    glVertex2f(0, 250);
    glVertex2f(300, 250);
    glVertex2f(300, 245);
    glVertex2f(0, 245);
    glEnd();
}

void drawRailGuard() {
    glColor3f(0.25f, 0.25f, 0.25f); // Dark grey for guard rails
    for (int x = 0; x <= 300; x += 10) {
        glBegin(GL_LINES);
        glVertex2f(x, 270);
        glVertex2f(x, 285);
        glEnd();
    }
    glBegin(GL_LINES);
    glVertex2f(0, 285);
    glVertex2f(300, 285);
    glVertex2f(0, 275);
    glVertex2f(300, 275);
    glEnd();
}

void drawRailwayLine() {
    glColor3f(0.55f, 0.55f, 0.55f);    // Track base
    glBegin(GL_POLYGON);
    glVertex2f(0, 270);
    glVertex2f(1000, 270);
    glVertex2f(1000, 250);
    glVertex2f(0, 250);
    glEnd();

    glColor3f(0.35f, 0.25f, 0.15f);    // Sleepers
    for (int i = 0; i < 1000; i += 20) {
        glBegin(GL_LINES);
        glVertex2f(i, 250);
        glVertex2f(i, 270);
        glEnd();
    }

    glColor3f(0.85f, 0.85f, 0.85f);    // Rails
    glBegin(GL_LINES);
    glVertex2f(0, 230);
    glVertex2f(1000, 230);
    glVertex2f(0, 210);
    glVertex2f(1000, 210);
    glEnd();
}

void drawTrain() {
    float baseY = 230;

    // Draw 5 coaches
    for (int i = 0; i < 5; ++i) {
        float cx = trainX + i * 80;

        // Coach body
        glColor3f(0.15f, 0.15f, 0.7f); // Darker blue coaches
        glBegin(GL_POLYGON);
        glVertex2f(cx, baseY);
        glVertex2f(cx + 70, baseY);
        glVertex2f(cx + 70, baseY + 40);
        glVertex2f(cx, baseY + 40);
        glEnd();

        // Roof
        glColor3f(0.1f, 0.1f, 0.5f); // Darker blue roof
        glBegin(GL_POLYGON);
        glVertex2f(cx, baseY + 40);
        glVertex2f(cx + 70, baseY + 40);
        glVertex2f(cx + 70, baseY + 45);
        glVertex2f(cx, baseY + 45);
        glEnd();

        // Windows
        glColor3f(0.95f, 0.95f, 1.0f); // Light blue windows
        for (int j = 0; j < 3; ++j) {
            float wx = cx + 10 + j * 20;
            glBegin(GL_POLYGON);
            glVertex2f(wx, baseY + 20);
            glVertex2f(wx + 10, baseY + 20);
            glVertex2f(wx + 10, baseY + 35);
            glVertex2f(wx, baseY + 35);
            glEnd();
        }

        // Wheels
        glColor3f(0, 0, 0); // Black wheels
        drawCircle(cx + 15, baseY, 5);
        drawCircle(cx + 55, baseY, 5);
    }

    // Engine
    float x = trainX + 5 * 80; // Position of the engine after coaches
    glColor3f(0.8f, 0.1f, 0.1f); // Bright red engine body
    glBegin(GL_POLYGON);
    glVertex2f(x, baseY);
    glVertex2f(x + 70, baseY);
    glVertex2f(x + 70, baseY + 50);
    glVertex2f(x, baseY + 50);
    glEnd();

    // Chimney
    glColor3f(0.3f, 0.3f, 0.3f); // Dark grey chimney
    glBegin(GL_POLYGON);
    glVertex2f(x + 50, baseY + 50);
    glVertex2f(x + 60, baseY + 50);
    glVertex2f(x + 60, baseY + 70);
    glVertex2f(x + 50, baseY + 70);
    glEnd();

    // Slanted nose at the front (right side)
    glColor3f(0.6f, 0.1f, 0.1f); // Darker red nose
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 70, baseY);
    glVertex2f(x + 90, baseY);
    glVertex2f(x + 70, baseY + 30);
    glEnd();

    // Engine windows
    glColor3f(0.95f, 0.95f, 1.0f); // Light blue windows
    glBegin(GL_POLYGON);
    glVertex2f(x + 5, baseY + 30);
    glVertex2f(x + 25, baseY + 30);
    glVertex2f(x + 25, baseY + 45);
    glVertex2f(x + 5, baseY + 45);
    glEnd();

    // Engine wheels
    glColor3f(0, 0, 0); // Black wheels
    drawCircle(x + 15, baseY, 6);
    drawCircle(x + 55, baseY, 6);
}

void drawBoat(float xPos, float yPos, float scale, bool reverseDirection = false) {
    glPushMatrix();
    glTranslatef(xPos, yPos, 0.0f);
    glScalef(scale, scale, 1.0f);

    if (reverseDirection) {
        glScalef(-1.0f, 1.0f, 1.0f); // Flip horizontally for opposite direction
    }

    // Hull
    glColor3f(0.15f, 0.15f, 0.4f); // Darker blue hull
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.1f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.4f, -0.1f);
    glEnd();

    // Cabin
    glColor3f(0.9f, 0.8f, 0.55f); // Cream/tan cabin
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(-0.2f, 0.2f);
    glEnd();

    // Oar (represented as a single stick for simplicity)
    glColor3f(0.35f, 0.15f, 0.0f); // Darker brown oar
    glPushMatrix();
    glTranslatef(0.1f, 0.15f, 0.0f);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // Rotate oar
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, -0.15f);
        glVertex2f(0.01f, -0.15f);
        glVertex2f(0.01f, 0.15f);
        glVertex2f(-0.01f, 0.15f);
    glEnd();
    glPopMatrix();

    // Person (simple rectangle)
    glColor3f(0.15f, 0.15f, 0.15f); // Darker grey/black person
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.0f);
        glVertex2f(0.05f, 0.0f);
        glVertex2f(0.05f, 0.15f);
        glVertex2f(-0.05f, 0.15f);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

void drawLamppost(float x, float y_base) {
    // Pole
    glColor3f(0.35f, 0.35f, 0.35f); // Dark grey pole
    glBegin(GL_QUADS);
    glVertex2f(x - 3, y_base);
    glVertex2f(x + 3, y_base);
    glVertex2f(x + 3, y_base + 100); // Taller lamppost
    glVertex2f(x - 3, y_base + 100);
    glEnd();

    // Lamp head arm
    glBegin(GL_QUADS);
    glVertex2f(x, y_base + 100);
    glVertex2f(x + 25, y_base + 100);
    glVertex2f(x + 25, y_base + 95);
    glVertex2f(x, y_base + 95);
    glEnd();

    // Lamp head
    glColor3f(0.5f, 0.5f, 0.5f); // Grey lamp head
    glBegin(GL_QUADS);
    glVertex2f(x + 20, y_base + 95);
    glVertex2f(x + 35, y_base + 95);
    glVertex2f(x + 35, y_base + 80);
    glVertex2f(x + 20, y_base + 80);
    glEnd();

    // Light glow (only at night)
    if (!isDaytime && !isMorning) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 0.8f, 0.5f); // Yellowish light with transparency

        // Light cone
        glBegin(GL_TRIANGLES);
        glVertex2f(x + 27, y_base + 80); // Top of light source
        glVertex2f(x + 10, y_base);      // Bottom left
        glVertex2f(x + 45, y_base);      // Bottom right
        glEnd();

        // Light bulb
        glColor4f(1.0f, 1.0f, 0.5f, 1.0f); // Bright yellow bulb
        glBegin(GL_QUADS);
        glVertex2f(x + 25, y_base + 85);
        glVertex2f(x + 30, y_base + 85);
        glVertex2f(x + 30, y_base + 80);
        glVertex2f(x + 25, y_base + 80);
        glEnd();

        glDisable(GL_BLEND);
    }
}

void drawBridge() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.35f); // Darker grey for bridge
    glVertex2f(0, 170);
    glVertex2f(1000, 170);
    glVertex2f(1000, 190);
glVertex2f(0, 190);
    glEnd();
}

void drawTracks() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f); // Dark grey for track base
    glVertex2f(0, 185); glVertex2f(1000, 185); glVertex2f(1000, 230); glVertex2f(0, 230);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.8f); // Silver for rails
    glVertex2f(0, 220); glVertex2f(1000, 220);
    glVertex2f(0, 195); glVertex2f(1000, 195);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.35f, 0.2f); // Brown for sleepers
    for (int i = 0; i < 1000; i += 40) {
        glVertex2f(i, 190); glVertex2f(i + 30, 190);
        glVertex2f(i + 30, 225); glVertex2f(i, 225);
    }
    glEnd();
}

void drawRiver() {
    glBegin(GL_QUADS);
    // Use morning river color if isMorning is true
    if (isMorning) {
        glColor3fv(&riverColorMorning.r);
    } else {
        glColor3fv(isDaytime ? &riverColorDay.r : &riverColorNight.r);
    }
    glVertex2f(0, 0);
    glVertex2f(1000, 0);
    glVertex2f(1000, 170);
    glVertex2f(0, 170);
    glEnd();

    // Adjust water ripples color for morning
    if (isMorning) {
        glColor3f(riverColorMorning.r * 1.1f, riverColorMorning.g * 1.1f, riverColorMorning.b * 1.1f);
    } else {
        glColor3f(isDaytime ? 0.2f * 1.1f : 0.1f * 1.1f,
                  isDaytime ? 0.6f * 1.1f : 0.2f * 1.1f,
                  isDaytime ? 0.8f * 1.1f : 0.3f * 1.1f);
    }
    glLineWidth(1.5);
    glBegin(GL_LINES);
    for (int i = 0; i < 1000; i += 20) {
        glVertex2f(i, 50 + 10 * sinf(i * 0.05f + cloudPos * 0.1f));
        glVertex2f(i + 15, 50 + 10 * sinf((i + 15) * 0.05f + cloudPos * 0.1f));
        glVertex2f(i + 5, 100 + 8 * sinf((i + 5) * 0.06f + 1 + cloudPos * 0.1f));
        glVertex2f(i + 20, 100 + 8 * sinf((i + 20) * 0.06f + 1 + cloudPos * 0.1f));
    }
    glEnd();
    glLineWidth(1);
}

// Helper function to draw a triangle
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawRealisticAirplane(float x, float y) {
    // Fuselage - main body
    glColor3f(0.7f, 0.7f, 0.7f); // Light gray
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 100, y);
    glVertex2f(x + 100, y + 20);
    glVertex2f(x, y + 20);
    glEnd();

    // Fuselage - nose (front)
    drawTriangle(x, y, x, y + 20, x - 20, y + 10);

    // Fuselage - tail (back)
    drawTriangle(x + 100, y, x + 100, y + 20, x + 120, y + 10);

    // Main Wing - left
    glColor3f(0.5f, 0.5f, 0.5f); // Darker gray
    glBegin(GL_QUADS);
    glVertex2f(x + 20, y);
    glVertex2f(x + 50, y);
    glVertex2f(x + 80, y - 50);
    glVertex2f(x + 30, y - 50);
    glEnd();

    // Main Wing - right (symmetric to left)
    glBegin(GL_QUADS);
    glVertex2f(x + 20, y + 20);
    glVertex2f(x + 50, y + 20);
    glVertex2f(x + 80, y + 70);
    glVertex2f(x + 30, y + 70);
    glEnd();

    // Vertical Tail Fin
    glBegin(GL_QUADS);
    glVertex2f(x + 90, y + 20);
    glVertex2f(x + 100, y + 20);
    glVertex2f(x + 100, y + 45);
    glVertex2f(x + 90, y + 35);
    glEnd();

    // Horizontal Tail Fins
    glBegin(GL_QUADS);
    glVertex2f(x + 100, y + 10);
    glVertex2f(x + 110, y + 10);
    glVertex2f(x + 110, y + 15);
    glVertex2f(x + 100, y + 15);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(x + 100, y + 5);
    glVertex2f(x + 110, y + 5);
    glVertex2f(x + 110, y + 0);
    glVertex2f(x + 100, y + 0);
    glEnd();

    // Windows (simple rectangles)
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glBegin(GL_QUADS);
    glVertex2f(x + 10, y + 12);
    glVertex2f(x + 15, y + 12);
    glVertex2f(x + 15, y + 16);
    glVertex2f(x + 10, y + 16);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(x + 20, y + 12);
    glVertex2f(x + 25, y + 12);
    glVertex2f(x + 25, y + 16);
    glVertex2f(x + 20, y + 16);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(x + 30, y + 12);
    glVertex2f(x + 35, y + 12);
    glVertex2f(x + 35, y + 16);
    glVertex2f(x + 30, y + 16);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Sky gradient
    glBegin(GL_QUADS);
    // Determine sky color based on morning, day, or night
    if (isMorning) {
        glColor3fv(&skyMorning.r); // Top color (darker morning sky)
    } else {
        glColor3fv(isDaytime ? &skyDay.r : &skyNight.r); // Top color
    }
    glVertex2f(0, 600); glVertex2f(1000, 600);

    // Adjust bottom sky color for morning (slightly lighter than top)
    if (isMorning) {
        glColor3f(skyMorning.r * 1.2f, skyMorning.g * 1.2f, skyMorning.b * 1.2f);
    } else {
        glColor3f(isDaytime ? skyDay.r * 0.8f : skyNight.r * 1.2f,
                  isDaytime ? skyDay.g * 0.8f : skyNight.g * 1.2f,
                  isDaytime ? skyDay.b * 0.8f : skyNight.b * 1.2f);
    }
    glVertex2f(1000, 185); glVertex2f(0, 185);
    glEnd();

    // --- Lightning Flash Drawing ---
    if (isLightning) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // White-blue flash that covers the whole sky
        // Alpha fades out from 1.0 to 0.0 as lightningTimer decreases
        float alpha = (float)lightningTimer / LIGHTNING_DURATION;
        glColor4f(0.9f, 0.9f, 1.0f, alpha); // Mostly white, slightly blue, with fading alpha
        glBegin(GL_QUADS);
        glVertex2f(0, 185); // Start from just above the ground/city level
        glVertex2f(1000, 185);
        glVertex2f(1000, 600); // Up to the top of the screen
        glVertex2f(0, 600);
        glEnd();
        glDisable(GL_BLEND);
    }
    // --- End Lightning Flash Drawing ---

    drawSunMoon();
    drawHills();
    drawRainbow();


    drawStars();

    drawClouds();
    drawMountains(); // Mountains drawn before buildings to appear behind them

    // Ground for the city/structures (Draw this *before* things on top of it)
    glBegin(GL_QUADS);
    // Use morning ground color if isMorning is true
    if (isMorning) {
        glColor3fv(&groundMorning.r);
    } else {
        glColor3fv(isDaytime ? &groundDay.r : &groundNight.r);
    }
    glVertex2f(0, 170); glVertex2f(1000, 170); glVertex2f(1000, 185); glVertex2f(0, 185);
    glEnd();

    drawRiver(); // Draw river before the bridge, as bridge is on top
    drawBridge(); // Draw bridge over the river
    drawRoad(); // Draw road on top of the ground/bridge



    // Draw all three boats
    drawBoat(boatPos, 85.0f, 100.0f); // Main boat moving right
    drawBoat(boat2Pos, 120.0f, 80.0f, true); // Second boat moving left (opposite direction)
    drawBoat(boat3Pos, 60.0f, 120.0f); // Third boat moving right (larger and faster)


      // Draw trees near buildings (should be on top of ground)
    drawTree(70, 185);    // Near the first building
    drawTree(180, 185);   // Between first and second building
    drawTree(350, 185);   // Near the third building
    drawTree(500, 185);   // Near the very big building

    // Draw a tree next to the windmill (should be on top of ground)
    drawTree(920, 185); // Adjust X coordinate as needed to position relative to your windmill
    drawRain();



    // Draw buildings and structures (should be on top of ground)
    drawBuildings();
    drawHospital();
    drawMosque(); // Draw mosque


    // Draw windmill (should be on top of ground)
    drawWindmill();

    drawTracks(); // Tracks on top of road/ground

    drawTrain(); // Train on tracks

    // Draw lampposts (should be on top of road/ground)
    drawLamppost(150, 170);
    drawLamppost(300, 170);
    drawLamppost(450, 170);
    drawLamppost(600, 170);
    drawLamppost(750, 170);
    drawLamppost(900, 170);


    // DRAW SEATING ZONES LAST, so benches are on top of everything else in that area.
    drawSeatingZones(); //


    //drawRealisticAirplane(airplanePos, 450); // Use airplanePos for horizontal movement

    glTranslatef(airplaneX + 50.0f, airplaneY + 10.0f, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-(airplaneX + 50.0f), -(airplaneY + 10.0f), 0.0f);

    glutSwapBuffers();
}

void update(int value) {
    // Calculate the total width of the train
    float trainLength = 5 * 80.0f + 90.0f; // 5 coaches + engine length (approx)

    trainX += trainSpeed;
    if (trainX > 1000 + trainLength) {
        trainX = -trainLength; // Reset to start just off the left side
    }

    cloudPos += 0.3f;
    if (cloudPos > 1100.0f) cloudPos = 0.0f;

    // Adjust sun/moon position logic to account for morning
    if (isMorning) {

        if (sunMoonPos < 0.5f) sunMoonPos += 0.0005f;
        else if (sunMoonPos > 0.5f) sunMoonPos = 0.5f;
    } else if (isDaytime) {

        if (sunMoonPos < 1.0f) sunMoonPos += 0.0005f; // Slower movement
        else if (sunMoonPos > 1.0f) sunMoonPos = 1.0f; // Cap at a certain point for "day"
    } else { // Night transition (moon rising/setting)

        if (sunMoonPos < 1.0f) sunMoonPos += 0.0005f; // Slower movement
        else if (sunMoonPos > 1.0f) sunMoonPos = 1.0f;
    }


    // Update boat positions
    boatPos += boatSpeed;
    if (boatPos > 1000.0f + 50.0f) boatPos = -150.0f;

    boat2Pos -= boat2Speed; // Boat moving left (opposite direction)
    if (boat2Pos < -150.0f) boat2Pos = 1100.0f;

    boat3Pos += fasterBoatSpeed; // Third boat moving right
    if (boat3Pos > 1000.0f + 75.0f) boat3Pos = -300.0f;

    updateRain();
    airplanePos += airplaneSpeed;
    if (airplanePos > 1000.0f + 120.0f) airplanePos = -200.0f;

    windmillAngle += 1.0f;
    if (windmillAngle >= 360.0f) windmillAngle -= 360.0f;

    // --- Lightning Flash Timer ---
    if (isLightning) {
        lightningTimer--;
        if (lightningTimer <= 0) {
            isLightning = false; // Turn off flash when timer expires
        }
    }
    // --- End Lightning Flash Timer ---

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS

}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'd': case 'D':
            isDaytime = true;
            isMorning = false; // Ensure morning is off
            // Reset colors to default day colors explicitly when 'D' is pressed
            skyDay = {0.53f, 0.81f, 0.92f}; // Re-assign values
            groundDay = {0.4f, 0.7f, 0.2f};
            riverColorDay = {0.2f, 0.6f, 0.8f};
            sunMoonPos = 0.0f; // Reset sun position to start of day (right side for setting)
            break;
        case 'n': case 'N':
            isDaytime = false;
            isMorning = false; // Ensure morning is off
            sunMoonPos = 0.0f; // Reset moon position to start of night (left side for rising)
            break;
        case 'm': case 'M': // New key for morning view
            isMorning = true;
            isDaytime = false; // Ensure it's not also daytime

            // **Darker Morning Sky Colors**
            skyMorning.r = 0.1f;
            skyMorning.g = 0.1f;
            skyMorning.b = 0.2f;

            // Complementary darker ground and river colors for the darker morning sky
            groundMorning.r = 0.25f;
            groundMorning.g = 0.35f;
            groundMorning.b = 0.15f;

            riverColorMorning.r = 0.1f;
            riverColorMorning.g = 0.2f;
            riverColorMorning.b = 0.3f;

            sunMoonPos = 0.0f; // Reset sun position to start of morning rise (left side)
        case '+': // Increase speed
    if (trainSpeed < 10.0f) trainSpeed += 0.2f;
    if (boatSpeed < 5.0f) boatSpeed += 0.1f;
    if (boat2Speed < 4.0f) boat2Speed += 0.1f;
    if (fasterBoatSpeed < 6.0f) fasterBoatSpeed += 0.1f;
    if (airplaneSpeed < 10.0f) airplaneSpeed += 0.2f;
    break;

case '-': // Decrease speed
    if (trainSpeed > 0.2f) trainSpeed -= 0.2f;
    if (boatSpeed > 0.1f) boatSpeed -= 0.1f;
    if (boat2Speed > 0.1f) boat2Speed -= 0.1f;
    if (fasterBoatSpeed > 0.1f) fasterBoatSpeed -= 0.1f;
    if (airplaneSpeed > 0.5f) airplaneSpeed -= 0.2f;
    break;

        case ' ': // Toggle pause/resume
            if (trainSpeed > 0.01f || boatSpeed > 0.01f || airplaneSpeed > 0.01f) {
                trainSpeed = 0.0f;
                boatSpeed = 0.0f;
                boat2Speed = 0.0f;
                fasterBoatSpeed = 0.0f;
                airplaneSpeed = 0.0f;
            } else { // Resume to default speeds
                trainSpeed = 2.0f;
                boatSpeed = 1.0f;
                boat2Speed = 0.8f;
                fasterBoatSpeed = 1.2f;
                airplaneSpeed = 3.0f;
            }
            break;
        case 'l': case 'L': // New: Lightning flash
            // Only allow lightning if it's night or raining
            if (!isDaytime && !isMorning || isRaining) {
                isLightning = true;
                lightningTimer = LIGHTNING_DURATION;
            }
            break;

           // ... other cases ...
        case 'r': case 'R': // Show rainbow
            showRainbow = true;
            glutTimerFunc(3000, rainbowOff, 0); // Hide rainbow after 3 seconds
            break;
        // ... other


    }
    glutPostRedisplay(); // Request a redraw after keyboard input
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_RIGHT_BUTTON) {
            isRaining = true;
        } else if (button == GLUT_LEFT_BUTTON) {
            isRaining = false;
        }
    }
}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 600); // Set up 2D orthographic projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Double buffering and RGB color
    glutInitWindowSize(1000, 600); // Initial window size
    glutCreateWindow("Animated Scene: Railway, River, City Elements"); // Window title

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(0, update, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    initRain();  // Initialize raindrop positions
    initStars(); // Initialize star positions

    glutMainLoop(); // Enter the GLUT event processing loop
    return 0;
}
now  merge those scene 1,2,3,4 part together with keyboard interaction 1 for scene 1 ,2 for scene 2,3 for scene 3 and 4 for scene 4 . everything will same just merge them. if it need to change any function name then just add "_A" in the beginning at every function for scene 1, add "_E" in the beginning at every function for scene 2,add "_N" in the beginning at every function for scene 3,add "_S" in the beginning at every function for scene 4 .
