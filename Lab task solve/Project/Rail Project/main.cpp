#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include<cstdio>
#include <GL/gl.h>
#include<math.h>
#include <windows.h>
#include <mmsystem.h>
using namespace std;



bool Ridwandisplay= true;
bool Sourovdisplay = false;
bool Fahaddisplay = false;
bool PrantoDisplay = false;


float sCloudX1 = 50.0f; // Black cloud
float sCloudSpeed1 = 0.50f;

float sCloudX2 = 50.0f; // White cloud
float sCloudSpeed2 = 0.80f;

float sBirdx = 10.0f; // Bird transformation
float sBirdspeed = 1.0f;

float sBoatx = -400.0f; // Boat transformation
float sBoatspeed = 1.0f;

float sBoat2x = 1080.0f; // Boat transformation
float sBoat2speed = 1.0f;

float sTrainX=-900.0f;
float sTrainSpeed=2.0f;

float s_angle1 = 0.0f;
float sspeed = 0.2f;

bool sisRaining = false;

float sSunX = 100.0f;
float sSunY = 140.0f; // Start sun below the screen
float SunSpeed = 0.5f;

float sMoonX = 250.0f;
float sMoonY = 140.0f; // Start moon below the screen
float sMoonSpeed = 0.5f;

bool sisDaytime = true;
bool sisSunRising = false; // Sun rising animation
bool sisSunSetting = false; // Sun setting animation
bool sisMoonRising = false; // Moon rising animation
bool sisMoonSetting = false;

bool sisTrainrunning=false;

// Function to draw water
void sWater() {
    if (sisDaytime) {
        glColor3ub(65, 105, 225); // Daytime water color
    } else {
        glColor3ub(0, 0, 100); // Nighttime water color
    }
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1000, 0);
    glVertex2f(1000, 300);
    glVertex2f(0, 300);
    glEnd();
}

// Function to draw left soil
void sleftsoil() {
    glBegin(GL_QUADS);
    if (sisDaytime) {
        glColor3ub(139, 69, 19);
    } else {
        glColor3ub(100, 42, 12);
    }
    glVertex2i(0, 190);
    glVertex2i(250, 190);
    glVertex2i(400, 300);
    glVertex2i(0, 300);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(100, 42, 12);

    glVertex2i(250, 190);
    glVertex2i(255, 180);
    glVertex2i(400, 295);
    glVertex2i(400, 300);
    glEnd();

    //farmer land
    glBegin(GL_POLYGON);
    if (sisDaytime) {
           glColor3f(0.0f, 0.80f, 0.0f); // Bright Green for Daytime
       } else {
           glColor3f(0.0f, 0.5f, 0.0f); // Darker Green for Nighttime
       }
    glVertex2i(0, 250);
    glVertex2i(100,250);
    glVertex2i(140, 290);
    glVertex2i(0, 290);
    glEnd();


}

// Function to draw right soil
void sRightsoil() {
    glBegin(GL_QUADS);
    if (sisDaytime) {
        glColor3ub(139, 69, 19); // Ground - Brown (Day)
    } else {
        glColor3ub(100, 42, 12); // Ground - Dark Brown (Night)
    }
    glVertex2i(800, 190);
    glVertex2i(1000, 190);
    glVertex2i(1000, 300);
    glVertex2i(600, 300);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3ub(100, 42, 12);

    glVertex2i(800, 190);
    glVertex2i(600, 300);
    glVertex2i(600, 295);
    glVertex2i(795, 190);

glEnd();



}

// Function to draw a hill
void sHill(float x, float y, float width, float height) {
    glBegin(GL_POLYGON);

    if (sisDaytime) {
        glColor3ub(34, 139, 34); // Green hills for daytime
    } else {
        glColor3ub(19, 64, 19); // Darker green for nighttime
    } // Green color for the hill

    for (float angle = 0.0f; angle <= 3.14f; angle += 0.1f) {
        float vx = x + (width / 2.0f) + (cos(angle) * (width / 2.0f));
        float vy = y + (sin(angle) * height);
        glVertex2f(vx, vy);
    }

    glVertex2f(x, y);    // Bottom left
    glVertex2f(x + width, y);    // Bottom right
    glEnd();
}

// Function to draw multiple hills
void sDrawHills() {
    float startX = 0.0f; // Starting x-coordinate for hills
    float hillWidth = 60.0f; // Width of each hill
    float hillHeight = 60.0f; // Height of each hill

    while (startX < 1000.0f) { // Loop until the end of the window width
        sHill(startX, 300.0f, hillWidth, hillHeight); // Draw each hill
        startX += hillWidth - 5.0f; // Slight overlap for a continuous effect
    }
}

// Function to draw a circle
void sCircle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy) {
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

// Function to draw the sun
void sSun(float x, float y) {
    if (sisDaytime || sisSunRising || sisSunSetting) {
        glPushMatrix();
        glTranslatef(sSunX, sSunY, 1.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 36; ++i) {
            float angle = i * 10.0f * 3.1415926f / 180.0f;
            float dx = 40.0f * cos(angle);
            float dy = 40.0f * sin(angle);
            glVertex2f(x + dx, y + dy);
        }
        glEnd();
        glPopMatrix();
    }
}

// Function to draw the moon
void sMoon(float x, float y) {
    if (!sisDaytime || sisMoonRising) {
        glPushMatrix();
        glTranslatef(sMoonX + 500, sMoonY, 1.0f);
        glColor3f(.80f, .80f, 0.80f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 36; ++i) {
            float angle = i * 10.0f * 3.1415926f / 180.0f;
            float dx = 40.0f * cos(angle);
            float dy = 40.0f * sin(angle);
            glVertex2f(x + dx, y + dy);
        }
        glEnd();
        glPopMatrix();
    }
}

// Function to draw black clouds
void sClouds1() {
    glPushMatrix();
    glTranslatef(sCloudX1, 10, 0); // Move the clouds from left to right

    // First cloud
    glColor3f(0.1f, 0.1f, 0.1f);

    // Left cloud
    sCircle(30, 30, 100, 500);
    sCircle(30, 30, 140, 500);
    sCircle(30, 30, 140, 520); // Upper circle
    sCircle(30, 30, 180, 500);

    glPopMatrix();

    sCloudX1 += sCloudSpeed1;  // Move the cloud to the right
    if (sCloudX1 > 1000) {
        sCloudX1 = -500;
    }

    glutPostRedisplay();
}

// Function to draw white clouds
void sClouds2() {
    glPushMatrix();
    glTranslatef(sCloudX2, 0, 0); // Move the clouds from left to right

    // First cloud
    if (sisDaytime) {
        glColor3ub(255, 255, 255); // Clouds - White (Day)
    } else {
        glColor3ub(105, 105, 105); // Clouds - Dark Gray (Night)
    }

    // Right cloud
    sCircle(30, 30, 300, 500);
    sCircle(30, 30, 340, 500);
    sCircle(30, 30, 340, 520); // Upper circle
    sCircle(30, 30, 340, 490); // Lower circle
    sCircle(30, 30, 380, 500);

    glPopMatrix();

    sCloudX2 += sCloudSpeed2;  // Move the cloud to the right
    if (sCloudX2 > 1000) {
        sCloudX2 = -500;
    }

    glutPostRedisplay();
}

// Function to draw rain
void SRain() {
    if (sisDaytime) {
        glColor3f(1.0f, 1.0f, 1.0f); // Pure white for daytime
    } else {
        glColor3f(0.5f, 0.5f, 0.5f); // Dark gray for nighttime
    }
    int numDrops = 500;
    int rainLength = 10;

    for (int i = 0; i < numDrops; i++) {
        float x = rand() % 1000;
        float y = rand() % 600;           // Random y-coordinate across the entire screen height
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y - rainLength);    // Create the raindrop by extending downwards
        glEnd();
    }
}

// Function to draw a house//right
void sHouse() {
    if (sisDaytime) {
        glColor3f(0.9f, 0.85f, 0.55f); // Light yellowish color (Day)
    } else {
        glColor3f(0.6f, 0.55f, 0.3f); // Darker yellowish color (Night)
    }
    glBegin(GL_QUADS);
    glVertex2f(760, 250);
    glVertex2f(960, 250);
    glVertex2f(960, 350);
    glVertex2f(760, 350);
    glEnd();

    // Side Roof - Deep Maroon
    glColor3f(0.2f, 0.1f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(960, 250);
    glVertex2f(990, 280);
    glVertex2f(990, 350);
    glVertex2f(980, 380);
    glVertex2f(960, 350);
    glEnd();

    // Main Roof - Brick Red
    glColor3f(0.55f, 0.15f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(760, 350);
    glVertex2f(960, 350);
    glVertex2f(980, 380);
    glVertex2f(780, 380);
    glEnd();

    // Door - Dark Wooden Brown
    glColor3f(0.38f, 0.20f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(790, 250);
    glVertex2f(830, 250);
    glVertex2f(830, 300);
    glVertex2f(790, 300);
    glEnd();

    // Windows - Sky Blue Glass

    if (sisDaytime) {
        glColor3f(0.52f, 0.73f, 0.94f);
    } else {
        glColor3f(1.0f, 0.9f, 0.55f); // Warm yellowish light for windows (Night)
    }

    // Window 1
    glBegin(GL_QUADS);
    glVertex2f(850, 270);
    glVertex2f(880, 270);
    glVertex2f(880, 300);
    glVertex2f(850, 300);
    glEnd();

    // Window 2
    glBegin(GL_QUADS);
    glVertex2f(910, 270);
    glVertex2f(940, 270);
    glVertex2f(940, 300);
    glVertex2f(910, 300);
    glEnd();

    glColor3f(0.25f, 0.26f, 0.2f);//brown
    glBegin(GL_QUADS);
    glVertex2f(50,250);
    glVertex2f(250,250);
    glVertex2f(250,350);
    glVertex2f(50,350);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);//black
    glBegin(GL_POLYGON);
    glVertex2f(250,250);
    glVertex2f(280,280);
    glVertex2f(280,350);
    glVertex2f(270,380);
    glVertex2f(250,350);
    glEnd();


    ///house left
    glColor3f(1.0f,0.5f, 0.0f);//yellow
    glBegin(GL_QUADS);
    glVertex2f(50,350);
    glVertex2f(250,350);
    glVertex2f(270,380);
    glVertex2f(70,380);
    glEnd();

    //door
    if (!sisDaytime) {
        glColor3f(1.0f, 1.0f, 0.f);
    } else {
        glColor3f(0.0f, 0.0f, 0.0f);
    }
    //door
    glBegin(GL_QUADS);
    glColor3f(0.2f,0.4f,0.4f);
    glVertex2f(80,250);
    glVertex2f(120,250);
    glVertex2f(120,300);
    glVertex2f(80,300);
    glEnd();

    //window
    if (!sisDaytime) {
        glColor3f(1.0f, 1.0f, 0.f);
    } else {
        glColor3f(0.0f, 0.0f, 0.0f);
    }
    glBegin(GL_QUADS);
    glVertex2f(140,270);
    glVertex2f(170,270);
    glVertex2f(170,300);
    glVertex2f(140,300);
    glEnd();

    //window
    if (!sisDaytime) {
        glColor3f(1.0f, 1.0f, 0.f);
    } else {
        glColor3f(0.0f, 0.0f, 0.0f);
    }
    glBegin(GL_QUADS);
    glVertex2f(200,270);
    glVertex2f(230,270);
    glVertex2f(230,300);
    glVertex2f(200,300);
    glEnd();
}
// Function to draw a bridge
void sbridge() {
    // Bridge left
    glBegin(GL_POLYGON);
    if (sisDaytime) {
        glColor3f(0.2, 0.2, 0.2); // Steel gray for bridge (Day)
    } else {
        glColor3f(0.1f, 0.1f, 0.1f); // Dark gray for bridge (Night)
    }

    glVertex2f(0, 90);       // Point 1
    glVertex2f(190, 90);     // Point 2
    glVertex2f(240, 145);
    glVertex2f(240, 190);
    glVertex2f(0, 190);
    glEnd();

    //shade
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);
    glVertex2f(190, 90);
    glVertex2f(220, 110);
    glVertex2f(240, 145);
    glEnd();


    // Bridge middle
    glBegin(GL_QUADS);
    if (sisDaytime) {
        glColor3f(0.2, 0.2, 0.2); // Steel gray for bridge (Day)
    } else {
        glColor3f(0.1f, 0.1f, 0.1f); // Dark gray for bridge (Night)
    }

    glVertex2f(240, 145);
    glVertex2f(780, 145);
    glVertex2f(780, 190);
    glVertex2f(240, 190);
    glEnd();

    // Bridge right
    glBegin(GL_POLYGON);
    if (sisDaytime) {
        glColor3f(0.2, 0.2, 0.2); // Steel gray for bridge (Day)
    } else {
        glColor3f(0.1f, 0.1f, 0.1f); // Dark gray for bridge (Night)
    }
    glVertex2f(780, 145);       // Point 1
    glVertex2f(820, 90);      // Point 2
    glVertex2f(1000, 90);     // Point 3
    glVertex2f(1000, 190);    // Point 4
    glVertex2f(780, 190);
    glEnd();



}


// Function to draw rail lines
void srailline() {
    // Line background
    glColor3f(0.803, 0.690, 0.675);
    glBegin(GL_QUADS);
    glVertex2f(0, 185);
    glVertex2f(1000, 185);
    glVertex2f(1000, 230);
    glVertex2f(0, 230);
    glEnd();

    // Down black railline
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(0, 190);
    glVertex2f(1000, 190);
    glVertex2f(1000, 195);
    glVertex2f(0, 195);
    glEnd();

    // Upper black railline
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(0, 220);
    glVertex2f(1000, 220);
    glVertex2f(1000, 225);
    glVertex2f(0, 225);
    glEnd();

    // Rail line supports
    glColor3f(0.3, 0.3, 0.3); // Dark gray color for rail line
    glBegin(GL_QUADS);
    for (int i = 0; i <= 1000; i = i + 30) {
        glVertex2f(i, 190);        // Bottom left corner of the rail
        glVertex2f(i + 5, 190);    // Bottom right corner of the rail
        glVertex2f(i + 20, 225);   // Top right corner of the rail
        glVertex2f(i + 25, 225);   // Top left corner of the rail
    }


    glEnd();
}

void sRaling()
{
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    for (int i = 5; i <= 1000; i = i + 60) {
        glVertex2f(i+5,190);           // Left bottom
        glVertex2f(i+15,190);      // Left top
        glVertex2f(i+15,260);     // Right top
        glVertex2f(i+5,260);          // Right bottom
    }

    glBegin(GL_QUADS);
        glVertex2f(0,245);           // Left bottom
        glVertex2f(1000,245);      // Left top
        glVertex2f(1000,250);     // Right top
        glVertex2f(0,250);

    glEnd();
}

void slamppost()
{
    for (int i = -100, j = 40; i <= 1000; i += 200) {
        glBegin(GL_QUADS);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex2f(i+240, 190+j);
        glVertex2f(i+260, 190+j);
        glVertex2f(i+260, 290+j);
        glVertex2f(i+240, 290+j);
        glEnd();

        glBegin(GL_QUADS);
        if (sisDaytime) {
            glColor3f(1.0f, 1.0f, 1.0f); // Pure White (Day)
        }
        else {
            glColor3f(1.0f, 0.9f, 0.4f);
        }
        glVertex2f(i+250, 290+j);
        glVertex2f(i+270, 300+j);
        glVertex2f(i+250, 320+j);
        glVertex2f(i+230, 300+j);
        glEnd();
    }



}


// Function to draw a tree
void sTree1() {


        // Tree Trunk - Moved & Scaled
        glBegin(GL_QUADS);
        if (sisDaytime) {
            glColor3f(0.4f, 0.10f, 0.1f); // Brown (Day)
        } else {
            glColor3f(0.25f, 0.07f, 0.07f); // Dark Brown (Night)
        }
        glVertex2f(747, 274);  // Moved Left (-100) and Up (+60)
        glVertex2f(777, 274);
        glVertex2f(777, 430);
        glVertex2f(747, 430);
        glEnd();

        // Leaves - Moved & Scaled
        if (sisDaytime) {
            glColor3f(0.0f, 0.3f, 0.0f); // Green (Day)
        } else {
            glColor3f(0.1f, 0.2f, 0.1f); // Dark Greenish Gray (Night)
        }

        sCircle(39, 39, 715, 430); // Moved left (-100), up (+60)
        sCircle(39, 39, 760, 455);
        sCircle(39, 39, 805, 430);

        sCircle(39, 39, 735, 475);
        sCircle(39, 39, 770, 490);
        sCircle(39, 39, 800, 470);
    }


// Function to draw a bird
void sBird() {
    glPushMatrix();
    glTranslatef(sBirdx, 300.0f, 0.0f); // Translate the bird's position
    glScalef(0.5f, 0.5f, 1.0f);  // Scale the bird (50% smaller)

    // Bird Body (Triangle)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f); // Black bird
    glVertex2f(25, 450);  // Vertex 1
    glVertex2f(10, 455);  // Vertex 2
    glVertex2f(10, 445);  // Vertex 3
    glEnd();

    // Bird Wings (Polygon)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f); // Black bird
    glVertex2f(25, 450);  // Vertex 1
    glVertex2f(50, 455);  // Vertex 2
    glVertex2f(55, 430);  // Vertex 3
    glVertex2f(60, 455);  // Vertex 4
    glVertex2f(70, 450);  // Vertex 5
    glVertex2f(60, 470);  // Vertex 6
    glVertex2f(55, 460);  // Vertex 7
    glVertex2f(50, 475);  // Vertex 8
    glEnd();

    glPopMatrix();
    sBirdx += sBirdspeed;
    if (sBirdx > 1000.0f) sBirdx = -200.0f; // Reset position for looping
}

// Function to draw a boat
void sBoat() {
    glPushMatrix(); // Save the current transformation matrix
    glTranslatef(sBoatx, -180.0f, 0.0f); // Translate the boat's position
    glColor3ub(0, 0, 0);

    glBegin(GL_POLYGON);
    glVertex2d(325 , 220);
    glVertex2d(400, 220);
    glVertex2d(425, 250);
    glVertex2d(300, 250);
    glEnd();

    glColor3ub(205, 133, 63);
    glBegin(GL_POLYGON);
    glVertex2d(325, 250);
    glVertex2d(400, 250);
    glVertex2d(390, 280);
    glVertex2d(335, 280);
    glEnd();

    glPopMatrix(); // Restore the transformation matrix

    // Update the boat's position for movement
    sBoatx += sBoatspeed;
    if (sBoatx>1000.0f) sBoatx = -400.0f; // Reset position for looping
}

void sBoat2()
{
    glPushMatrix(); // Save the current transformation matrix
    glTranslatef(sBoat2x, -170.0f, 0.0f); // Translate the boat's position
        glColor3ub(0, 0, 0);

        glBegin(GL_POLYGON);
        glVertex2d(325 , 220);
        glVertex2d(400, 220);
        glVertex2d(425, 250);
        glVertex2d(300, 250);
        glEnd();

        glColor3ub(205, 133, 63);
        glBegin(GL_POLYGON);
        glVertex2d(325, 250);
        glVertex2d(400, 250);
        glVertex2d(390, 280);
        glVertex2d(335, 280);
        glEnd();




    glPopMatrix(); // Restore the transformation matrix

    // Update the boat's position for movement
    sBoat2x -= sBoat2speed;
    if (sBoat2x < -400.0f) sBoat2x = 1000.0f; // Reset position for looping

}
void strain(){

    //left first
    glPushMatrix(); // Save the current transformation matrix
    glTranslatef(sTrainX, 0, 0.0f);
    glColor3f(0.0, 0.2,0.7);
    glBegin(GL_QUADS);
    glVertex2f(0,200);
    glVertex2f(200,200);
    glVertex2f(200,300);
    glVertex2f(0,300);
    glEnd();
    //design
    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(0,210);
    glVertex2f(200,210);
    glVertex2f(200,220);
    glVertex2f(0,220);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(0,300);
    glVertex2f(200,300);
    glVertex2f(220,320);
    glVertex2f(30,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(200,300);
    glVertex2f(220,320);
    glVertex2f(220,230);
    glVertex2f(200,200);
    glEnd();

    //1st window
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(10,250);
    glVertex2f(40,250);
    glVertex2f(40,280);
    glVertex2f(10,280);
    glEnd();
    //2nd
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(50,250);
    glVertex2f(80,250);
    glVertex2f(80,280);
    glVertex2f(50,280);
    glEnd();
    //3rd
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(90,250);
    glVertex2f(120,250);
    glVertex2f(120,280);
    glVertex2f(90,280);
    glEnd();

    //1st door
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(130,220);
    glVertex2f(165,220);
    glVertex2f(165,280);
    glVertex2f(130,280);
    glEnd();



      //left second
    glColor3f(0.0, 0.2, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(220,200);
    glVertex2f(420,200);
    glVertex2f(420,300);
    glVertex2f(220,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(220,210);
    glVertex2f(420,210);
    glVertex2f(420,220);
    glVertex2f(220,220);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(220,300);
    glVertex2f(420,300);
    glVertex2f(440,320);
    glVertex2f(250,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(420,300);
    glVertex2f(440,320);
    glVertex2f(440,230);
    glVertex2f(420,200);
    glEnd();


     //1st window
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(230,250);
    glVertex2f(260,250);
    glVertex2f(260,280);
    glVertex2f(230,280);
    glEnd();
    //2nd
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(270,250);
    glVertex2f(300,250);
    glVertex2f(300,280);
    glVertex2f(270,280);
    glEnd();
    //3rd
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(310,250);
    glVertex2f(340,250);
    glVertex2f(340,280);
    glVertex2f(310,280);
    glEnd();

    // door
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(355,220);
    glVertex2f(390,220);
    glVertex2f(390,280);
    glVertex2f(355,280);
    glEnd();


      //left 3rd
    glColor3f(0.0, 0.2, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(440,200);
    glVertex2f(640,200);
    glVertex2f(640,300);
    glVertex2f(440,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(440,210);
    glVertex2f(640,210);
    glVertex2f(640,220);
    glVertex2f(440,220);
    glEnd();


    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(440,300);
    glVertex2f(640,300);
    glVertex2f(660,320);
    glVertex2f(470,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(640,300);
    glVertex2f(660,320);
    glVertex2f(660,230);
    glVertex2f(640,200);
    glEnd();


    //1st window
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(450,250);
    glVertex2f(480,250);
    glVertex2f(480,280);
    glVertex2f(450,280);
    glEnd();
    //2nd
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(490,250);
    glVertex2f(520,250);
    glVertex2f(520,280);
    glVertex2f(490,280);
    glEnd();
    //3rd
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(530,250);
    glVertex2f(560,250);
    glVertex2f(560,280);
    glVertex2f(530,280);
    glEnd();

    // door
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(580,220);
    glVertex2f(615,220);
    glVertex2f(615,280);
    glVertex2f(580,280);
    glEnd();


      //head eng
      glColor3f(0.0,0.2,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(660,200);
    glVertex2f(860,200);
    glVertex2f(860,250);
    glVertex2f(760,300);
    glVertex2f(660,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(660,210);
    glVertex2f(860,210);
    glVertex2f(860,220);
    glVertex2f(660,220);
    glEnd();


    glColor3f(0.0,0.0,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(660,300);
    glVertex2f(760,300);
    glVertex2f(790,320);
    glVertex2f(690,320);
    glEnd();

    glColor3f(0.0,0.6,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(760,300);
    glVertex2f(790,320);
    glVertex2f(880,270);
    glVertex2f(860,250);
    glEnd();

    glColor3f(0.7,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(860,200);
    glVertex2f(860,250);
    glVertex2f(880,270);
    glVertex2f(880,225);
    glEnd();

     // door
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(680,220);
    glVertex2f(720,220);
    glVertex2f(720,280);
    glVertex2f(680,280);
    glEnd();

      //window
    if (sisDaytime) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(730,250);
    glVertex2f(760,250);
    glVertex2f(760,280);
    glVertex2f(730,280);
    glEnd();

    //chaka
    glColor3f(0.0, 0.0, 0.0);
      sCircle(10, 10, 10, 200);
      sCircle(10, 10, 60, 200);
      sCircle(10, 10, 110, 200);
      sCircle(10, 10, 170, 200);

      sCircle(10, 10, 250, 200);
      sCircle(10, 10, 300, 200);
      sCircle(10, 10, 350, 200);
       sCircle(10, 10,400, 200);


      sCircle(10, 10, 460, 200);
      sCircle(10, 10, 510, 200);
      sCircle(10, 10, 560, 200);
       sCircle(10, 10,620, 200);

       sCircle(10, 10, 680, 200);
      sCircle(10, 10, 730, 200);
      sCircle(10, 10, 780, 200);
       sCircle(10, 10,830, 200);

    glPopMatrix(); // Restore the transformation matrix


        // Update the boat's position for movement
        sTrainX += sTrainSpeed;
        if (sTrainX > 1200.0f) sTrainX = -1080.0f;



}






// Mouse click handler
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x > sCloudX1 && x < sCloudX1 + 200 && y > 100 && y < 200) // Check if clicked near CloudX1
        {
            sisRaining = !sisRaining; // Toggle rain
        }
    }
    glutPostRedisplay();
}

// Keyboard handler
void skeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'd': // Day mode

            sisDaytime = true;
            sisMoonSetting = true;
            sisSunRising = true;
            sisSunSetting = false;
            sSunY = 140.0f;
            sSunX = 100.0f;

            // Start sun below the screen
            break;
        case 'n': // Night mode
            sisDaytime = false;
            sisSunSetting = true;
            sisMoonRising = true;
            sisMoonSetting = false;
            sMoonY = 140.0f; // Start moon below the screen
            sMoonX=300;
            //SunY=140;
            break;

        case 't':
            sisTrainrunning = !sisTrainrunning; // Toggle train state
               if (sisTrainrunning) {
                   sTrainSpeed = 1.0f; // Start train
               } else {
                   sTrainSpeed = 0.0f; // Stop train
               }
               break;

            break;

    }
    glutPostRedisplay();
}

// Display function
void sdisplay() {


    if (sisDaytime) {
        glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // Sky blue background for day
    } else {
        glClearColor(0.0f, 0.0f, 0.1f, 1.0f); // Dark blue background for night
    }
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 600);

    // Draw elements
    sWater();
    sSun(50.0f, sSunY);

    sMoon(50.0f, sMoonY);
    sDrawHills();
    sleftsoil();
    sRightsoil();
    sbridge();


    srailline();
    slamppost();

    if (sisTrainrunning) {
              strain();
          }
    else
    {
        strain();
        sTrainSpeed=0;
    }




    sRaling();

    sBoat();
    sBoat2();

    // Draw rain if raining


    // Sun rising animation
    if (sisSunRising && sSunY < 270.0f) {
        sSunY += SunSpeed;
        sSunX += SunSpeed;

    } else {
        sisSunRising = false;
    }

    if(sisMoonSetting && sMoonY>140.0f){
        // Moon setting animation (Moon should move down)
        if (sMoonY > 140.0f) {
            sMoonY -= sMoonSpeed;
            sMoonX=1300;
        } else {
            sisMoonSetting = false;
        }
    }
    // Sun setting animation
    if (sisSunSetting && sSunY > 140.0f) {
        sSunY -= SunSpeed;
        sSunX = -185;
        glutPostRedisplay();


    } else {
        sisSunSetting = false;

    }

    // Moon rising animation
    if (sisMoonRising && sMoonY < 270.0f) {
        sMoonY += sMoonSpeed;
        sMoonX -= sMoonSpeed;
    } else {
        sisMoonRising = false;
    }

    sClouds1(); // Black clouds
    sClouds2(); // White clouds
    sBird();
    sTree1();
    sHouse();
    srailline();
    slamppost();

    if (sisTrainrunning) {
              strain();
          }
    else
    {
        strain();
        sTrainSpeed=0;
    }




    sRaling();

    sBoat();
    //sBoat2();

    if (sisRaining) {
        if (sCloudX1 <= 900 && sCloudX1 >= -50) {
            SRain();
        }
    }

    glFlush();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:  // Move train left
            sTrainSpeed -=0.2;  // Increase speed for visibility
            break;
        case GLUT_KEY_RIGHT: // Move train right
            sTrainSpeed +=0.2;
            break;

        case GLUT_KEY_UP:
            sBoatspeed+=1;
            sBoat2speed+=1.5;
            break;

        case GLUT_KEY_DOWN:
            sBoatspeed-=1;
            sBoat2speed-=1;
            break;
    }
    glutPostRedisplay();  // Redraw the scene
}


// Timer function for animation
void stimer(int value) {
    glutPostRedisplay();
    glutTimerFunc(10, stimer, 0);
}


//////////////////////////Fahad Start//////////////////////////


bool FisDay=true;

void Fcircle(int centerX, int centerY, int radius)
{
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i++)
    {
        float pi = 3.1416;
        float A  = (i*2*pi)/180 ;
        float r  = radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x + centerX, y + centerY );
    }
    glEnd();
}
void FRiver() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.6f, 1.0f);
    glVertex2f(0, 0);
    glVertex2d(1000, 0);             //river
    glVertex2d(1000, 300);
    glVertex2d(0, 300);
    glEnd();

}

void FRiverNight() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.4f);
    glVertex2f(0, 0);
    glVertex2d(1000, 0);             //riverNight
    glVertex2d(1000, 300);
    glVertex2d(0, 300);
    glEnd();

}

void FRiverBank() {
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.6f, 0.7f);
    glVertex2f(0, 290);
    glVertex2d(1000, 290);             //riverBank
    glVertex2d(1010, 310);
    glVertex2d(0, 310);
    glEnd();

}

void FRoad() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0, 310);
    glVertex2f(1000, 310);      //road
    glVertex2f(1000, 400);
    glVertex2f(0, 400);
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int x = 10; x < 1000; x += 90) {      //divider
        glVertex2f(x, 350);
        glVertex2f(x + 50, 350);
    }
    glEnd();

}

void FSidewalk() {
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.4f, 0.0f);
    glVertex2f(0, 400);
    glVertex2f(1000, 400);
    glVertex2f(1000, 420);
    glVertex2f(0, 420);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.6f, 0.7f);
    glVertex2f(0, 400);
    glVertex2f(1000, 400);
    glVertex2f(1000, 405);
    glVertex2f(0, 405);
    glEnd();


}

void FSky() {
    glBegin(GL_QUADS);
    glColor3f(.63f, 0.85f, 1.0f);
    glVertex2f(0, 420);
    glVertex2d(1000, 420);                 //sky
    glVertex2d(1000, 600);
    glVertex2d(0, 600);
    glEnd();


}

void FSkyNight() {
    glBegin(GL_QUADS);
    glColor3f(.0f, 0.2f, 0.4f);
    glVertex2f(0, 420);
    glVertex2d(1000, 420);               //night sky
    glVertex2d(1000, 600);
    glVertex2d(0, 600);
    glEnd();


}

void FBuilding3() {
    glBegin(GL_QUADS);
    glColor3f(.7f, .8f, .9f);
    glVertex2f(200, 420);
    glVertex2d(295, 420);
    glVertex2d(295, 520);
    glVertex2d(200, 520);
    glEnd();

    for (int i = 0; i < 4; i++) {
        glBegin(GL_QUADS);
        glColor3f(0.75f, 0.75f, 0.75f);
        glVertex2f(210 + i * 20, 430);
        glVertex2d(220 + i * 20, 430);
        glVertex2d(220 + i * 20, 510);
        glVertex2d(210 + i * 20, 510);
        glEnd();
    }

}

void FBuilding3Night() {
    glBegin(GL_QUADS);
    glColor3f(.7f, .8f, .9f);
    glVertex2f(200, 420);
    glVertex2d(295, 420);
    glVertex2d(295, 520);
    glVertex2d(200, 520);
    glEnd();

    for (int i = 0; i < 4; i++) {
        glBegin(GL_QUADS);
        glColor3f(1.f, 1.0f, 0.0f);
        glVertex2f(210 + i * 20, 430);
        glVertex2d(220 + i * 20, 430);
        glVertex2d(220 + i * 20, 510);
        glVertex2d(210 + i * 20, 510);
        glEnd();
    }

}

void FBuilding1() {
    glBegin(GL_POLYGON);
    glColor3f(0.4f, 0.5f, 0.2f);
    glVertex2f(0, 420);
    glVertex2f(100, 420);
    glVertex2f(100, 500);
    glVertex2f(50, 550);
    glVertex2f(0, 500);
    glEnd();

    // Windows
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(10 + i * 20, 430 + j * 30);
            glVertex2f(18 + i * 20, 430 + j * 30);
            glVertex2f(18 + i * 20, 440 + j * 30);
            glVertex2f(10 + i * 20, 440 + j * 30);
            glEnd();
        }
    }

}


void FBuilding1Night() {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.2f, 0.1f);
    glVertex2f(0, 420);
    glVertex2f(100, 420);
    glVertex2f(100, 500);
    glVertex2f(50, 550);
    glVertex2f(0, 500);
    glEnd();

    // Windows
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(10 + i * 20, 430 + j * 30);
            glVertex2f(18 + i * 20, 430 + j * 30);
            glVertex2f(18 + i * 20, 440 + j * 30);
            glVertex2f(10 + i * 20, 440 + j * 30);
            glEnd();
        }
    }

}


void FBuilding2() {
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.6f, 0.6f);
    glVertex2f(100, 420);
    glVertex2f(200, 420);
    glVertex2f(200, 570);
    glVertex2f(100, 570);
    glEnd();

    // Windows
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(115 + i * 20, 430 + j * 25);
            glVertex2f(125 + i * 20, 430 + j * 25);
            glVertex2f(125 + i * 20, 440 + j * 25);
            glVertex2f(115 + i * 20, 440 + j * 25);
            glEnd();
        }
    }

}

void FBuilding2Night() {
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.24f, 0.4f);
    glVertex2f(100, 420);
    glVertex2f(200, 420);
    glVertex2f(200, 570);
    glVertex2f(100, 570);
    glEnd();

    // Windows
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(115 + i * 20, 430 + j * 25);
            glVertex2f(125 + i * 20, 430 + j * 25);
            glVertex2f(125 + i * 20, 440 + j * 25);
            glVertex2f(115 + i * 20, 440 + j * 25);
            glEnd();
        }
    }

}

void FBuilding4() {
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.5f, 0.2f);
    glVertex2f(300, 420);
    glVertex2f(400, 420);
    glVertex2f(400, 470);
    glVertex2f(300, 470);
    glEnd();

    // Windows
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(305 + i * 18, 430 + j * 20);
            glVertex2f(315 + i * 18, 430 + j * 20);
            glVertex2f(315 + i * 18, 440 + j * 20);
            glVertex2f(305 + i * 18, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuilding4Night() {
    glBegin(GL_POLYGON);
    glColor3f(0.58f, 0.3f, 0.2f);
    glVertex2f(300, 420);
    glVertex2f(400, 420);
    glVertex2f(400, 470);
    glVertex2f(300, 470);
    glEnd();


    // Windows
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(305 + i * 18, 430 + j * 20);
            glVertex2f(315 + i * 18, 430 + j * 20);
            glVertex2f(315 + i * 18, 440 + j * 20);
            glVertex2f(305 + i * 18, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuilding5()
{
   glBegin(GL_POLYGON);
    glColor3f(1.f, 1.f, 1.f);
    glVertex2d(400,   420);
    glVertex2d(450,   420);
    glVertex2d(450,   550);
    glVertex2d(400,   550);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.f,0.5f,0.5f);
    glVertex2f(450,   420);
    glVertex2d(480,   420);
    glVertex2d(480,   550);
    glVertex2d(450,   550);
    glEnd();


    // Windows
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(405 + i * 15, 430 + j * 20);
            glVertex2f(415 + i * 15, 430 + j * 20);
            glVertex2f(415 + i * 15, 440 + j * 20);
            glVertex2f(405 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}



void FBuilding5Night()
{
   glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2d(400,   420);
    glVertex2d(450,   420);
    glVertex2d(450,   550);
    glVertex2d(400,   550);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(.45f,0.f,0.f);
    glVertex2f(450,   420);
    glVertex2d(480,   420);
    glVertex2d(480,   550);
    glVertex2d(450,   550);
    glEnd();


    // Windows
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(405 + i * 15, 430 + j * 20);
            glVertex2f(415 + i * 15, 430 + j * 20);
            glVertex2f(415 + i * 15, 440 + j * 20);
            glVertex2f(405 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuilding6() {
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.5f, 0.8f);
    glVertex2f(480, 420);
    glVertex2f(550, 420);
    glVertex2f(550, 520);
    glVertex2f(480, 520);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(490, 520);
    glVertex2f(540, 520);
    glVertex2f(540, 530);
    glVertex2f(490, 530);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.6f, 0.4f);
    glVertex2f(500, 530);
    glVertex2f(530, 530);
    glVertex2f(530, 540);
    glVertex2f(500, 540);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.5f, 0.8f);
    glVertex2f(514, 540);
    glVertex2f(516, 540);
    glVertex2f(516, 570);
    glVertex2f(514, 570);
    glEnd();

    // Windows
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(485 + i * 15, 430 + j * 20);
            glVertex2f(495 + i * 15, 430 + j * 20);
            glVertex2f(495 + i * 15, 440 + j * 20);
            glVertex2f(485 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuilding6Night() {
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.5f);
    glVertex2f(480, 420);
    glVertex2f(550, 420);
    glVertex2f(550, 520);
    glVertex2f(480, 520);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(490, 520);
    glVertex2f(540, 520);
    glVertex2f(540, 530);
    glVertex2f(490, 530);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.6f, 0.4f);
    glVertex2f(500, 530);
    glVertex2f(530, 530);
    glVertex2f(530, 540);
    glVertex2f(500, 540);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.5f, 0.8f);
    glVertex2f(514, 540);
    glVertex2f(516, 540);
    glVertex2f(516, 570);
    glVertex2f(514, 570);
    glEnd();

    // Windows
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(485 + i * 15, 430 + j * 20);
            glVertex2f(495 + i * 15, 430 + j * 20);
            glVertex2f(495 + i * 15, 440 + j * 20);
            glVertex2f(485 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuilding7() {
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.4f, 0.3f);
    glVertex2f(550, 420);
    glVertex2f(650, 420);
    glVertex2f(650, 500);
    glVertex2f(550, 500);
    glEnd();


    // Windows
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(555 + i * 15, 430 + j * 20);
            glVertex2f(565 + i * 15, 430 + j * 20);
            glVertex2f(565 + i * 15, 440 + j * 20);
            glVertex2f(555 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}



void FBuilding7Night() {
    glBegin(GL_POLYGON);
    glColor3f(0.4f, 0.2f, 0.f);
    glVertex2f(550, 420);
    glVertex2f(650, 420);
    glVertex2f(650, 500);
    glVertex2f(550, 500);
    glEnd();

    // Windows
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(555 + i * 15, 430 + j * 20);
            glVertex2f(565 + i * 15, 430 + j * 20);
            glVertex2f(565 + i * 15, 440 + j * 20);
            glVertex2f(555 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuilding8() {
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.5f, 0.2f);
    glVertex2f(650, 420);
    glVertex2f(750, 420);
    glVertex2f(750, 470);
    glVertex2f(650, 470);
    glEnd();

    // Windows
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(655 + i * 18, 430 + j * 20);
            glVertex2f(665 + i * 18, 430 + j * 20);
            glVertex2f(665 + i * 18, 440 + j * 20);
            glVertex2f(655 + i * 18, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuilding8Night() {
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.3f, 0.f);
    glVertex2f(650, 420);
    glVertex2f(750, 420);
    glVertex2f(750, 470);
    glVertex2f(650, 470);
    glEnd();

    // Windows
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(655 + i * 18, 430 + j * 20);
            glVertex2f(665 + i * 18, 430 + j * 20);
            glVertex2f(665 + i * 18, 440 + j * 20);
            glVertex2f(655 + i * 18, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuilding9() {
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.7f, 0.2f);
    glVertex2f(800, 420);
    glVertex2f(900, 420);
    glVertex2f(900, 500);
    glVertex2f(850, 550);
    glVertex2f(800, 500);
    glEnd();


    // Windows
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(810 + i * 20, 430 + j * 30);
            glVertex2f(820 + i * 20, 430 + j * 30);
            glVertex2f(820 + i * 20, 440 + j * 30);
            glVertex2f(810 + i * 20, 440 + j * 30);
            glEnd();
        }
    }

}

void FBuilding9Night() {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.4f, 0.2f);
    glVertex2f(800, 420);
    glVertex2f(900, 420);
    glVertex2f(900, 500);
    glVertex2f(850, 550);
    glVertex2f(800, 500);
    glEnd();


    // Windows
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(810 + i * 20, 430 + j * 30);
            glVertex2f(820 + i * 20, 430 + j * 30);
            glVertex2f(820 + i * 20, 440 + j * 30);
            glVertex2f(810 + i * 20, 440 + j * 30);
            glEnd();
        }
    }

}

void FBuilding10() {
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.2f, 0.3f);
    glVertex2f(900, 420);
    glVertex2f(1000, 420);
    glVertex2f(1000, 480);
    glVertex2f(900, 480);
    glEnd();


    // Windows
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(905 + i * 15, 430 + j * 20);
            glVertex2f(915 + i * 15, 430 + j * 20);
            glVertex2f(915 + i * 15, 440 + j * 20);
            glVertex2f(905 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuilding10Night() {
    glBegin(GL_POLYGON);
    glColor3f(0.4f, 0.f, 0.f);
    glVertex2f(900, 420);
    glVertex2f(1000, 420);
    glVertex2f(1000, 480);
    glVertex2f(900, 480);
    glEnd();

    // Windows
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(905 + i * 15, 430 + j * 20);
            glVertex2f(915 + i * 15, 430 + j * 20);
            glVertex2f(915 + i * 15, 440 + j * 20);
            glVertex2f(905 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuildingB1() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.7f, 0.7f);
    glVertex2f(250, 420);
    glVertex2f(350, 420);
    glVertex2f(350, 555);
    glVertex2f(250, 555);
    glEnd();

    // Windows
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(255 + i * 18, 430 + j * 20);
            glVertex2f(265 + i * 18, 430 + j * 20);
            glVertex2f(265 + i * 18, 440 + j * 20);
            glVertex2f(255 + i * 18, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuildingB2() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.7f, 0.7f);
    glVertex2f(580, 420);
    glVertex2f(680, 420);
    glVertex2f(680, 555);
    glVertex2f(580, 555);
    glEnd();

    // Windows
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(585 + i * 15, 430 + j * 20);
            glVertex2f(595 + i * 15, 430 + j * 20);
            glVertex2f(595 + i * 15, 440 + j * 20);
            glVertex2f(585 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}


void FBuildingB3() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.7f, 0.7f);
    glVertex2f(720, 420);
    glVertex2f(820, 420);
    glVertex2f(820, 530);
    glVertex2f(720, 530);
    glEnd();

    // Windows
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(725 + i * 15, 430 + j * 20);
            glVertex2f(735 + i * 15, 430 + j * 20);
            glVertex2f(735 + i * 15, 440 + j * 20);
            glVertex2f(725 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuildingB4() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.7f, 0.7f);
    glVertex2f(950, 420);
    glVertex2f(1000, 420);
    glVertex2f(1000, 570);
    glVertex2f(950, 570);
    glEnd();


    // Windows
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            glBegin(GL_QUADS);
            glColor3f(0.75f, 0.75f, 0.75f);
            glVertex2f(955 + i * 15, 430 + j * 20);
            glVertex2f(965 + i * 15, 430 + j * 20);
            glVertex2f(965 + i * 15, 440 + j * 20);
            glVertex2f(955 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuildingB1Night() {
    glBegin(GL_QUADS);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(250, 420);
    glVertex2f(350, 420);
    glVertex2f(350, 555);
    glVertex2f(250, 555);
    glEnd();


    // Windows
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(255 + i * 18, 430 + j * 20);
            glVertex2f(265 + i * 18, 430 + j * 20);
            glVertex2f(265 + i * 18, 440 + j * 20);
            glVertex2f(255 + i * 18, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuildingB2Night() {
    glBegin(GL_QUADS);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(580, 420);
    glVertex2f(680, 420);
    glVertex2f(680, 555);
    glVertex2f(580, 555);
    glEnd();

    // Windows
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(585 + i * 15, 430 + j * 20);
            glVertex2f(595 + i * 15, 430 + j * 20);
            glVertex2f(595 + i * 15, 440 + j * 20);
            glVertex2f(585 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuildingB3Night() {
    glBegin(GL_QUADS);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(720, 420);
    glVertex2f(820, 420);
    glVertex2f(820, 530);
    glVertex2f(720, 530);
    glEnd();

    // Windows
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(725 + i * 15, 430 + j * 20);
            glVertex2f(735 + i * 15, 430 + j * 20);
            glVertex2f(735 + i * 15, 440 + j * 20);
            glVertex2f(725 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}

void FBuildingB4Night() {
    glBegin(GL_QUADS);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(950, 420);
    glVertex2f(1000, 420);
    glVertex2f(1000, 570);
    glVertex2f(950, 570);
    glEnd();

    // Windows
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex2f(955 + i * 15, 430 + j * 20);
            glVertex2f(965 + i * 15, 430 + j * 20);
            glVertex2f(965 + i * 15, 440 + j * 20);
            glVertex2f(955 + i * 15, 440 + j * 20);
            glEnd();
        }
    }

}

void FBridge() {
    int shift = 200;
    for (int i = 0; i < 5; i++) {
        // Bridge supports (pillars)
        glBegin(GL_QUADS);
        glColor3f(0.61f, 0.35f, 0.18f); // Brown  supports
        glVertex2f(0   + shift * i, 100);
        glVertex2f(10  + shift * i, 100);
        glVertex2f(10  + shift * i, 200);
        glVertex2f(0   + shift * i, 200);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.61f, 0.35f, 0.18f); // Brown  supports
        glVertex2f(190   + shift * i, 100);
        glVertex2f(200  + shift * i, 100);
        glVertex2f(200  + shift * i, 200);
        glVertex2f(190   + shift * i, 200);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.61f, 0.35f, 0.18f); // Brown supports
        glVertex2f(10   + shift * i, 175);
        glVertex2f(190  + shift * i, 175);
        glVertex2f(190  + shift * i, 185);
        glVertex2f(10   + shift * i, 185);
        glEnd();

        // Bridge planks
        glBegin(GL_QUADS);
        glColor3f(0.7f, 0.7f, 0.7f); // Gray  planks
        glVertex2f(0 + shift * i, 200);
        glVertex2f(200 + shift * i, 200);
        glVertex2f(200 + shift * i, 220);
        glVertex2f(0 + shift * i, 220);
        glEnd();
    }


}

void Frailline()
{
    glColor3f(0.803, 0.690, 0.675);
    glBegin(GL_QUADS);
    glVertex2f(0, 185);
    glVertex2f(1000,185);
    glVertex2f(1000,230);
    glVertex2f(0, 230);

    glEnd();
    glBegin(GL_QUADS);//down black railline
    glColor3f(0, 0, 0);
    glVertex2f(0, 190);
    glVertex2f(1000, 190);
    glVertex2f(1000, 195);
    glVertex2f(0, 195);
    glEnd();

    glBegin(GL_QUADS);//upper black railline
    glColor3f(0, 0, 0);
    glVertex2f(0, 220);
    glVertex2f(1000, 220);
    glVertex2f(1000, 225);
    glVertex2f(0, 225);
    glEnd();

       glColor3f(0.3, 0.3, 0.3); // Dark gray  rail line
       glBegin(GL_QUADS);
       for (int i =0 ; i <= 1000; i = i + 30) {
           glVertex2f(i, 190);        // Bottom left corner of the rail
           glVertex2f(i + 5, 190);    // Bottom right corner of the rail
           glVertex2f(i + 20, 225);   // Top right corner of the rail
           glVertex2f(i + 25, 225);   // Top left corner of the rail
       }
       glEnd();

}

void Ftree() {
    int shift = 200;
    for (int i = 0; i < 5; i++) {
        // Tree trunk
        glBegin(GL_QUADS);
        glColor3f(0.61, 0.35, 0.18);
        glVertex2f(100  + shift * i, 300);
        glVertex2f(110  + shift * i, 300);
        glVertex2f(110  + shift * i, 370);
        glVertex2f(100  + shift * i, 370);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.04, 0.36, 0.12);
        glVertex2f(70  + shift * i, 370);
        glVertex2f(140  + shift * i, 370);
        glVertex2f(105  + shift * i, 420);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.09, 0.8, 0.2);
        glVertex2f(75  + shift * i, 390);
        glVertex2f(135  + shift * i, 390);
        glVertex2f(105  + shift * i, 430);
        glEnd();
    }

}

void FtreeNight() {
    int shift = 200;
    for (int i = 0; i < 5; i++) {
        // Tree trunk
        glBegin(GL_QUADS);
        glColor3f(0.61, 0.35, 0.18);
        glVertex2f(100  + shift * i, 300);
        glVertex2f(110  + shift * i, 300);
        glVertex2f(110  + shift * i, 370);
        glVertex2f(100  + shift * i, 370);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.0, 0.2, 0.0);
        glVertex2f(70  + shift * i, 370);
        glVertex2f(140  + shift * i, 370);
        glVertex2f(105  + shift * i, 420);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.2, 0.4, 0.0);
        glVertex2f(75  + shift * i, 390);
        glVertex2f(135  + shift * i, 390);
        glVertex2f(105  + shift * i, 430);
        glEnd();
    }

}

void FtreeUp() {
    int shift = 200;
    for (int i = 0; i < 5; i++) {
        // Tree trunk
        glBegin(GL_QUADS);
        glColor3f(0.61, 0.35, 0.18);
        glVertex2f(50  + shift * i, 400);
        glVertex2f(55  + shift * i, 400);
        glVertex2f(55  + shift * i, 440);
        glVertex2f(50  + shift * i, 440);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.04, 0.36, 0.12);
        glVertex2f(35   + shift * i, 440);
        glVertex2f(70  + shift * i, 440);
        glVertex2f(52.5  + shift * i, 480);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.09, 0.8, 0.2);
        glVertex2f(38   + shift * i, 455);
        glVertex2f(68  + shift * i, 455);
        glVertex2f(52.5  + shift * i, 485);
        glEnd();
    }

}

void FtreeUpNight() {
    int shift = 200;
    for (int i = 0; i < 5; i++) {
        // Tree trunk
        glBegin(GL_QUADS);
        glColor3f(0.61, 0.35, 0.18);
        glVertex2f(50  + shift * i, 400);
        glVertex2f(55  + shift * i, 400);
        glVertex2f(55  + shift * i, 440);
        glVertex2f(50  + shift * i, 440);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.0, 0.2, 0.0);
        glVertex2f(35   + shift * i, 440);
        glVertex2f(70  + shift * i, 440);
        glVertex2f(52.5  + shift * i, 480);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.2, 0.4, 0.0);
        glVertex2f(38   + shift * i, 455);
        glVertex2f(68  + shift * i, 455);
        glVertex2f(52.5  + shift * i, 485);
        glEnd();
    }

}

int Birdx =10.0f;
void FupdateBird(int value) {
    Birdx += 2;
    if (Birdx > 1000) {
        Birdx = -300;
    }
    glutPostRedisplay();
    glutTimerFunc(10, FupdateBird, 0);
}

void FBird() {

    glPushMatrix();
    glTranslatef(Birdx, 0.0f, 0.0f);

    int shift = 40;
    for (int i = 0; i < 5; i++) {
        // Left wing
        glBegin(GL_TRIANGLES);
        glColor3f(0, 0, 0);
        glVertex2f(80 + shift * i, 570);
        glVertex2f(95 + shift * i, 555);
        glVertex2f(100 + shift * i, 555);
        glEnd();

        // Right wing
        glBegin(GL_TRIANGLES);
        glColor3f(0, 0, 0);
        glVertex2f(110 + shift * i, 570);
        glVertex2f(95 + shift * i, 555);
        glVertex2f(100 + shift * i, 555);
        glEnd();
    }
      glPopMatrix();

}

float busX = 0.0f;
float car1X = 0.0f;
float car2X = 0.0f;
float car3X = 0.0f;
float truckX = 0.0f;
float truck2X = 0.0f;
float boatX = 0.0f;
float boatY = 0.0f;
float cloudX = 0.0f;
float vehicleSpeed = 5.0f;
float FTrainX=-900.0f;
float FTrainSpeed=2.0f;


void FupdateCloud(int value) {
    cloudX += 0.5f;
    if (cloudX > 1300) cloudX = -850;
    glutPostRedisplay();
    glutTimerFunc(16, FupdateCloud, 0);
}

void FCloud(int centerX, int centerY, int radius) {
    glPushMatrix();
    glTranslatef(cloudX, 0.0f, 0.0f);

    glColor3f(.75f, .75f, .75f);
    Fcircle(centerX, centerY, radius); // center circle
    Fcircle(centerX + radius, centerY, radius); // Right circle
    Fcircle(centerX - radius, centerY, radius); // Left circle
    Fcircle(centerX, centerY + radius, radius); // Top circle

    glPopMatrix();
}

void FCloudNight(int centerX, int centerY, int radius) {
    glPushMatrix();
    glTranslatef(cloudX, 0.0f, 0.0f);

    glColor3f(.85f, .85f, .85f);
    Fcircle(centerX, centerY, radius); // center circle
    Fcircle(centerX + radius, centerY, radius); // Right circle
    Fcircle(centerX - radius, centerY, radius); // Left circle
    Fcircle(centerX, centerY + radius, radius); // Top circle

    glPopMatrix();
}

void FupdateVehicles(int value) {
    // Move right
    busX += vehicleSpeed;
    if (busX > 1050) busX = -180;

    car1X += vehicleSpeed;
    if (car1X > 900) car1X = -340;

    car2X += vehicleSpeed;
    if (car2X > 680) car2X = -540;

    // Move left
    car3X -= vehicleSpeed;
    if (car3X < -180) car3X = 1000;

    truckX += vehicleSpeed;
    if (truckX > 300) truckX = -900;

    truck2X -= vehicleSpeed;
    if (truck2X < -620) truck2X = 550;

    glutPostRedisplay();
    glutTimerFunc(16, FupdateVehicles, 0);
}

void FBus() {
     glPushMatrix();
    glTranslatef(busX, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.5f, 0.1f);
    glVertex2f(80, 380);
    glVertex2f(180, 380);
    glVertex2f(180, 400);
    glVertex2f(160, 420);
    glVertex2f(80, 420);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(90, 400);
    glVertex2f(160, 400);
    glVertex2f(160, 410);
    glVertex2f(90, 410);
    glEnd();

    glColor3f(0.25f, 0.25f, 0.25f);
    Fcircle(105, 380, 7);
    Fcircle(155, 380, 7);

    glPopMatrix();
}

void FBusnight() {
    glPushMatrix();
    glTranslatef(busX, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.5f, 0.1f);
    glVertex2f(80, 380);
    glVertex2f(180, 380);
    glVertex2f(180, 400);
    glVertex2f(160, 420);
    glVertex2f(80, 420);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(90, 400);
    glVertex2f(160, 400);
    glVertex2f(160, 410);
    glVertex2f(90, 410);
    glEnd();

    glColor3f(0.25f, 0.25f, 0.25f);
    Fcircle(105, 380, 7);
    Fcircle(155, 380, 7);

    glPopMatrix();
}

void FCar1() {
    glPushMatrix();
    glTranslatef(car1X, 0.0f, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(300, 380);
    glVertex2f(360, 380);
    glVertex2f(360, 395);
    glVertex2f(300, 395);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(310, 395);
    glVertex2f(350, 395);
    glVertex2f(340, 405);
    glVertex2f(315, 405);
    glEnd();

    glColor3f(0.5f, 0.0f, 0.0f);
    Fcircle(314, 380, 5);
    Fcircle(345, 380, 5);

    glPopMatrix();
}

void FCarNight() {
    glPushMatrix();
    glTranslatef(car1X, 0.0f, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.4f, 0.0f);
    glVertex2f(300, 380);
    glVertex2f(360, 380);
    glVertex2f(360, 395);
    glVertex2f(300, 395);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(310, 395);
    glVertex2f(350, 395);
    glVertex2f(340, 405);
    glVertex2f(315, 405);
    glEnd();

    glColor3f(0.5f, 0.0f, 0.0f);
    Fcircle(314, 380, 5);
    Fcircle(345, 380, 5);

    glPopMatrix();
}

void FCar2() {
    glPushMatrix();
    glTranslatef(car2X, 0.0f, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(500, 380);
    glVertex2f(560, 380);
    glVertex2f(560, 395);
    glVertex2f(500, 395);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.25f, .25f, .25f);
    glVertex2f(510, 395);
    glVertex2f(550, 395);
    glVertex2f(540, 405);
    glVertex2f(515, 405);
    glEnd();

    glColor3f(0.5f, 0.0f, 0.0f);
    Fcircle(514, 380, 5);
    Fcircle(545, 380, 5);

    glPopMatrix();
}

void FCar3() {
    glPushMatrix();
    glTranslatef(car3X, 0.0f, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(.0f, 0.0f, 1.0f);
    glVertex2f(100, 330);
    glVertex2f(180, 330);
    glVertex2f(180, 355);
    glVertex2f(100, 355);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 4.0f, 6.0f);
    glVertex2f(110, 355);
    glVertex2f(170, 355);
    glVertex2f(165, 372);
    glVertex2f(120, 372);
    glEnd();

    glColor3f(0.5f, 0.0f, 0.0f);
    Fcircle(120, 330, 6);
    Fcircle(160, 330, 6);

    glPopMatrix();
}

void FTruck() {
    glPushMatrix();
    glTranslatef(truckX, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.5f, 0.1f);
    glVertex2f(802, 380);
    glVertex2f(830, 380);
    glVertex2f(830, 400);
    glVertex2f(820, 420);
    glVertex2f(802, 420);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.2f, 0.3f);
    glVertex2f(700, 380);
    glVertex2f(800, 380);
    glVertex2f(800, 420);
    glVertex2f(700, 420);
    glEnd();

    glColor3f(0.25f, 0.25f, 0.25f);
    Fcircle(815, 380, 7);
    Fcircle(720, 380, 7);
    Fcircle(775, 380, 7);

    glPopMatrix();
}

void FTruckNight() {
    glPushMatrix();
    glTranslatef(truck2X, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.5f, 0.1f);
    glVertex2f(498, 330);
    glVertex2f(460, 330);
    glVertex2f(460, 370);
    glVertex2f(475, 390);
    glVertex2f(498, 390);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.3f, 0.5f);
    glVertex2f(500, 330);
    glVertex2f(620, 330);
    glVertex2f(620, 390);
    glVertex2f(500, 390);
    glEnd();

    glColor3f(0.25f, 0.25f, 0.25f);
    Fcircle(480, 330, 7);
    Fcircle(530, 330, 7);
    Fcircle(590, 330, 7);

    glPopMatrix();
}

void FTruck2() {
    glPushMatrix();
    glTranslatef(truck2X, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.5f, 0.1f);
    glVertex2f(498, 330);
    glVertex2f(460, 330);
    glVertex2f(460, 370);
    glVertex2f(475, 390);
    glVertex2f(498, 390);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.2f, 0.3f);
    glVertex2f(500, 330);
    glVertex2f(620, 330);
    glVertex2f(620, 390);
    glVertex2f(500, 390);
    glEnd();

    glColor3f(0.25f, 0.25f, 0.25f);
    Fcircle(480, 330, 7);
    Fcircle(530, 330, 7);
    Fcircle(590, 330, 7);

    glPopMatrix();
}

void FupdateBoat(int value) {
    boatX += 1.0f;
    if (boatX > 1250) boatX = -650;
    glutPostRedisplay();
    glutTimerFunc(20, FupdateBoat, 0);
}
float moveUp=0.0f;

void FBoat() {
    glPushMatrix();
    glTranslatef(boatX, moveUp, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.2f, 0.0f);
    glVertex2f(400, 50);
    glVertex2f(600, 50);
    glVertex2f(550, 100);
    glVertex2f(450, 100);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(250, 50);
    glVertex2f(650, 50);
    glVertex2f(600, 20);
    glVertex2f(300, 20);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(470, 100);
    glVertex2f(530, 100);
    glVertex2f(530, 125);
    glVertex2f(470, 125);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex2f(470, 125);
    glVertex2f(530, 125);
    glVertex2f(500, 155);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(490, 125);
    glVertex2f(500, 125);
    glVertex2f(500, 160);
    glVertex2f(490, 160);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(480, 110);
    glVertex2f(490, 110);
    glVertex2f(490, 120);
    glVertex2f(480, 120);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(510, 110);
    glVertex2f(520, 110);
    glVertex2f(520, 120);
    glVertex2f(510, 120);
    glEnd();

    glPopMatrix();
}

void FupdateBoatNight(int value) {
    boatY -= 1.0f;
    if (boatY < -650) boatY = 1200;

    glutPostRedisplay();
    glutTimerFunc(20, FupdateBoatNight, 0);
}

void FBoatNight() {
    glPushMatrix();
    glTranslatef(boatY, moveUp, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.2f, 0.0f);
    glVertex2f(400, 250);
    glVertex2f(600, 250);
    glVertex2f(550, 300);
    glVertex2f(450, 300);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(250, 250);
    glVertex2f(650, 250);
    glVertex2f(600, 220);
    glVertex2f(300, 220);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(470, 300);
    glVertex2f(530, 300);
    glVertex2f(530, 325);
    glVertex2f(470, 325);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex2f(470, 325);
    glVertex2f(530, 325);
    glVertex2f(500, 355);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(490, 325);
    glVertex2f(500, 325);
    glVertex2f(500, 360);
    glVertex2f(490, 360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.f, 1.f, 0.0f);
    glVertex2f(480, 310);
    glVertex2f(490, 310);
    glVertex2f(490, 320);
    glVertex2f(480, 320);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.f, 1.f, 0.0f);
    glVertex2f(510, 310);
    glVertex2f(520, 310);
    glVertex2f(520, 320);
    glVertex2f(510, 320);
    glEnd();

    glPopMatrix();
}

void FSun() {
    int centerX = 228;
    int centerY = 550;
    int radius = 20;

    glColor3f(1.0f, 0.5f, 0.0f); // Orange sun
    Fcircle(centerX, centerY, radius);
}

void FMoon() {
    int centerX = 730;
    int centerY = 570;
    int radius = 20;

    glColor3f(1.0f, 1.0f, 1.0f); // white moon
    Fcircle(centerX, centerY, radius);
}



void Ftrain(){

    //left first
    glPushMatrix(); // Save the current transformation matrix
    glTranslatef(FTrainX, 0, 0.0f);
    glColor3f(0.0, 0.2,0.7);
    glBegin(GL_QUADS);
    glVertex2f(0,200);
    glVertex2f(200,200);
    glVertex2f(200,300);
    glVertex2f(0,300);
    glEnd();
    //design
    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(0,210);
    glVertex2f(200,210);
    glVertex2f(200,220);
    glVertex2f(0,220);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(0,300);
    glVertex2f(200,300);
    glVertex2f(220,320);
    glVertex2f(30,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(200,300);
    glVertex2f(220,320);
    glVertex2f(220,230);
    glVertex2f(200,200);
    glEnd();


           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           //glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(10,250);
    glVertex2f(40,250);
    glVertex2f(40,280);
    glVertex2f(10,280);
    glEnd();
    //2nd
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           //glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(50,250);
    glVertex2f(80,250);
    glVertex2f(80,280);
    glVertex2f(50,280);
    glEnd();
    //3rd
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           //glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(90,250);
    glVertex2f(120,250);
    glVertex2f(120,280);
    glVertex2f(90,280);
    glEnd();

    //1st door
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

          // glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(130,220);
    glVertex2f(165,220);
    glVertex2f(165,280);
    glVertex2f(130,280);
    glEnd();



      //left second
    glColor3f(0.0, 0.2, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(220,200);
    glVertex2f(420,200);
    glVertex2f(420,300);
    glVertex2f(220,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(220,210);
    glVertex2f(420,210);
    glVertex2f(420,220);
    glVertex2f(220,220);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(220,300);
    glVertex2f(420,300);
    glVertex2f(440,320);
    glVertex2f(250,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(420,300);
    glVertex2f(440,320);
    glVertex2f(440,230);
    glVertex2f(420,200);
    glEnd();


     //1st window
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

          // glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(230,250);
    glVertex2f(260,250);
    glVertex2f(260,280);
    glVertex2f(230,280);
    glEnd();
    //2nd
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

          // glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(270,250);
    glVertex2f(300,250);
    glVertex2f(300,280);
    glVertex2f(270,280);
    glEnd();
    //3rd
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           //glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(310,250);
    glVertex2f(340,250);
    glVertex2f(340,280);
    glVertex2f(310,280);
    glEnd();

    // door
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           //glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(355,220);
    glVertex2f(390,220);
    glVertex2f(390,280);
    glVertex2f(355,280);
    glEnd();


      //left 3rd
    glColor3f(0.0, 0.2, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(440,200);
    glVertex2f(640,200);
    glVertex2f(640,300);
    glVertex2f(440,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(440,210);
    glVertex2f(640,210);
    glVertex2f(640,220);
    glVertex2f(440,220);
    glEnd();


    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(440,300);
    glVertex2f(640,300);
    glVertex2f(660,320);
    glVertex2f(470,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(640,300);
    glVertex2f(660,320);
    glVertex2f(660,230);
    glVertex2f(640,200);
    glEnd();


    //1st window
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           //glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(450,250);
    glVertex2f(480,250);
    glVertex2f(480,280);
    glVertex2f(450,280);
    glEnd();
    //2nd
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

          // glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(490,250);
    glVertex2f(520,250);
    glVertex2f(520,280);
    glVertex2f(490,280);
    glEnd();
    //3rd
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           //glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(530,250);
    glVertex2f(560,250);
    glVertex2f(560,280);
    glVertex2f(530,280);
    glEnd();

    // door
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           //glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(580,220);
    glVertex2f(615,220);
    glVertex2f(615,280);
    glVertex2f(580,280);
    glEnd();


      //head eng
      glColor3f(0.0,0.2,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(660,200);
    glVertex2f(860,200);
    glVertex2f(860,250);
    glVertex2f(760,300);
    glVertex2f(660,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(660,210);
    glVertex2f(860,210);
    glVertex2f(860,220);
    glVertex2f(660,220);
    glEnd();


    glColor3f(0.0,0.0,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(660,300);
    glVertex2f(760,300);
    glVertex2f(790,320);
    glVertex2f(690,320);
    glEnd();

    glColor3f(0.0,0.6,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(760,300);
    glVertex2f(790,320);
    glVertex2f(880,270);
    glVertex2f(860,250);
    glEnd();

    glColor3f(0.7,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(860,200);
    glVertex2f(860,250);
    glVertex2f(880,270);
    glVertex2f(880,225);
    glEnd();

     // door
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           //glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(680,220);
    glVertex2f(720,220);
    glVertex2f(720,280);
    glVertex2f(680,280);
    glEnd();

      //window
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           //glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(730,250);
    glVertex2f(760,250);
    glVertex2f(760,280);
    glVertex2f(730,280);
    glEnd();

    //chaka
    glColor3f(0.0, 0.0, 0.0);
      Fcircle(10, 200, 10);
      Fcircle(60, 200, 10);
      Fcircle(110, 200,10);
      Fcircle( 170, 200,10);

      Fcircle( 250, 200,10);
      Fcircle( 300, 200,10);
      Fcircle( 350, 200,10);
      Fcircle(400, 200,10);


      Fcircle( 460, 200,10);
      Fcircle( 510, 200,10);
      Fcircle( 560, 200,10);
       Fcircle(620, 200,10);

       Fcircle( 680, 200,10);
      Fcircle( 730, 200,10);
      Fcircle(780, 200,10);
       Fcircle(830, 200,10);

    glPopMatrix(); // Restore the transformation matrix


        // Update the boat's position for movement
        FTrainX += sTrainSpeed;
        if (FTrainX > 1200.0f) FTrainX = -1080.0f;



}





void FtrainNight(){

    //left first
    glPushMatrix(); // Save the current transformation matrix
    glTranslatef(FTrainX, 0, 0.0f);
    glColor3f(0.0, 0.2,0.7);
    glBegin(GL_QUADS);
    glVertex2f(0,200);
    glVertex2f(200,200);
    glVertex2f(200,300);
    glVertex2f(0,300);
    glEnd();
    //design
    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(0,210);
    glVertex2f(200,210);
    glVertex2f(200,220);
    glVertex2f(0,220);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(0,300);
    glVertex2f(200,300);
    glVertex2f(220,320);
    glVertex2f(30,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(200,300);
    glVertex2f(220,320);
    glVertex2f(220,230);
    glVertex2f(200,200);
    glEnd();


           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(10,250);
    glVertex2f(40,250);
    glVertex2f(40,280);
    glVertex2f(10,280);
    glEnd();
    //2nd
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(50,250);
    glVertex2f(80,250);
    glVertex2f(80,280);
    glVertex2f(50,280);
    glEnd();
    //3rd
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(90,250);
    glVertex2f(120,250);
    glVertex2f(120,280);
    glVertex2f(90,280);
    glEnd();

    //1st door
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

          glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(130,220);
    glVertex2f(165,220);
    glVertex2f(165,280);
    glVertex2f(130,280);
    glEnd();



      //left second
    glColor3f(0.0, 0.2, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(220,200);
    glVertex2f(420,200);
    glVertex2f(420,300);
    glVertex2f(220,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(220,210);
    glVertex2f(420,210);
    glVertex2f(420,220);
    glVertex2f(220,220);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(220,300);
    glVertex2f(420,300);
    glVertex2f(440,320);
    glVertex2f(250,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(420,300);
    glVertex2f(440,320);
    glVertex2f(440,230);
    glVertex2f(420,200);
    glEnd();


     //1st window
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(230,250);
    glVertex2f(260,250);
    glVertex2f(260,280);
    glVertex2f(230,280);
    glEnd();
    //2nd
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(270,250);
    glVertex2f(300,250);
    glVertex2f(300,280);
    glVertex2f(270,280);
    glEnd();
    //3rd
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(310,250);
    glVertex2f(340,250);
    glVertex2f(340,280);
    glVertex2f(310,280);
    glEnd();

    // door
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(355,220);
    glVertex2f(390,220);
    glVertex2f(390,280);
    glVertex2f(355,280);
    glEnd();


      //left 3rd
    glColor3f(0.0, 0.2, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(440,200);
    glVertex2f(640,200);
    glVertex2f(640,300);
    glVertex2f(440,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(440,210);
    glVertex2f(640,210);
    glVertex2f(640,220);
    glVertex2f(440,220);
    glEnd();


    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(440,300);
    glVertex2f(640,300);
    glVertex2f(660,320);
    glVertex2f(470,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(640,300);
    glVertex2f(660,320);
    glVertex2f(660,230);
    glVertex2f(640,200);
    glEnd();


    //1st window
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(450,250);
    glVertex2f(480,250);
    glVertex2f(480,280);
    glVertex2f(450,280);
    glEnd();
    //2nd
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(490,250);
    glVertex2f(520,250);
    glVertex2f(520,280);
    glVertex2f(490,280);
    glEnd();
    //3rd
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(530,250);
    glVertex2f(560,250);
    glVertex2f(560,280);
    glVertex2f(530,280);
    glEnd();

    // door
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(580,220);
    glVertex2f(615,220);
    glVertex2f(615,280);
    glVertex2f(580,280);
    glEnd();


      //head eng
      glColor3f(0.0,0.2,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(660,200);
    glVertex2f(860,200);
    glVertex2f(860,250);
    glVertex2f(760,300);
    glVertex2f(660,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(660,210);
    glVertex2f(860,210);
    glVertex2f(860,220);
    glVertex2f(660,220);
    glEnd();


    glColor3f(0.0,0.0,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(660,300);
    glVertex2f(760,300);
    glVertex2f(790,320);
    glVertex2f(690,320);
    glEnd();

    glColor3f(0.0,0.6,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(760,300);
    glVertex2f(790,320);
    glVertex2f(880,270);
    glVertex2f(860,250);
    glEnd();

    glColor3f(0.7,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(860,200);
    glVertex2f(860,250);
    glVertex2f(880,270);
    glVertex2f(880,225);
    glEnd();

     // door
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(680,220);
    glVertex2f(720,220);
    glVertex2f(720,280);
    glVertex2f(680,280);
    glEnd();

      //window
           //glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)

           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)

    glBegin(GL_QUADS);
    glVertex2f(730,250);
    glVertex2f(760,250);
    glVertex2f(760,280);
    glVertex2f(730,280);
    glEnd();

    //chaka
    glColor3f(0.0, 0.0, 0.0);
      Fcircle(10, 200, 10);
      Fcircle(60, 200, 10);
      Fcircle(110, 200,10);
      Fcircle( 170, 200,10);

      Fcircle( 250, 200,10);
      Fcircle( 300, 200,10);
      Fcircle( 350, 200,10);
      Fcircle(400, 200,10);


      Fcircle( 460, 200,10);
      Fcircle( 510, 200,10);
      Fcircle( 560, 200,10);
       Fcircle(620, 200,10);

       Fcircle( 680, 200,10);
      Fcircle( 730, 200,10);
      Fcircle(780, 200,10);
       Fcircle(830, 200,10);

    glPopMatrix(); // Restore the transformation matrix


        // Update the boat's position for movement
        FTrainX += sTrainSpeed;
        if (FTrainX > 1200.0f) FTrainX = -1080.0f;



}




// ...  ...


void FDay()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 600);

    FRiver();
    FRiverBank();
    FRoad();
    FSidewalk();
    FSky();
    FSun();

    // clouds
    FCloud(200, 560, 8);
    FCloud(800, 530, 17);
    FCloud(400, 540, 13);
    FCloud(600, 540, 11);

    FBird();

    //background buildings
    FBuildingB1();
    FBuildingB2();
    FBuildingB3();
    FBuildingB4();

    //front buildings
    FBuilding1();
    FBuilding2();
    FBuilding3();
    FBuilding4();
    FBuilding5();
    FBuilding6();
    FBuilding7();
    FBuilding8();
    FBuilding9();
    FBuilding10();
    FtreeUp();
    FBus();
    FCar1();
    FCar2();
    FCar3();
    FTruck();
    FTruck2();
    Ftree();
    FBridge();
    Frailline();
    FBoat();
    Ftrain();

}

void FNight()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 600);

    FRiverNight();
    FRiverBank();
    FRoad();
    FSidewalk();
    FSkyNight();
    FMoon();

    // clouds
    FCloudNight(100, 560, 8);
    FCloudNight(800, 530, 17);
    FCloudNight(400, 540, 13);
   // Bird();

    //background buildings
    FBuildingB1Night();
    FBuildingB2Night();
    FBuildingB3Night();
    FBuildingB4Night();

    //front buildings
    FBuilding1Night();
    FBuilding2Night();
    FBuilding3Night();
    FBuilding4Night();
    FBuilding5Night();
    FBuilding6Night();
    FBuilding7Night();
    FBuilding8Night();
    FBuilding9Night();
    FBuilding10Night();
    FtreeUpNight();
    FCarNight();
    FBusnight();
    FTruckNight();
    FtreeNight();
    FBoatNight();
    FBridge();
    Frailline();
    FtrainNight();

}

void Fdisplay() {
            glClear(GL_COLOR_BUFFER_BIT);

            if (FisDay) {
                FDay();  // Call the day setup
            } else {
                FNight();  // Call the night setup
            }
    glFlush();

            //glutSwapBuffers();  // Swap buffers to update the display
        }


void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:     // ESC key
         exit(0);
         break;
      case 'n':
      case 'N':
          FisDay=false;
          break;
          case 'd':
          case 'D':
          FisDay=true;
          break;

   }

}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            vehicleSpeed += 0.5f;
            if (vehicleSpeed > 10.0f)
                vehicleSpeed = 1.0f;
        } else if (button == GLUT_RIGHT_BUTTON) {
            vehicleSpeed -= 0.5f;
            if (vehicleSpeed < 0.0f) vehicleSpeed = 0.0f;
        }
    }
}
void Fkeyboard(unsigned char key, int x, int y) {
    if (key == '1') {
        Ridwandisplay = true;
        Fahaddisplay = false;
        Sourovdisplay = false;
        PrantoDisplay = false;
    } if (key == '2') {
        Ridwandisplay = false;
        Fahaddisplay = true;
        Sourovdisplay = false;
        PrantoDisplay = false;
    } if (key == '3') {
        Ridwandisplay = false;
        Fahaddisplay = false;
        Sourovdisplay = true;
        PrantoDisplay = false;
    } if (key == '4') {
        Ridwandisplay = false;
        Fahaddisplay = false;
        Sourovdisplay = false;
        PrantoDisplay = true;
    } if (key == 27) { // ESC key
        exit(0);
    } if (key == 'n' || key == 'N') {
        FisDay = false;
    } if (key == 'd' || key == 'D') {
        FisDay = true;
    } if (key == 'w') {
        moveUp += 5.0f;
        if (moveUp > 50.0f) {
            moveUp = 0.0f;
        }
    } if (key == 's') {
        moveUp -= 5.0f;
        if (moveUp < -70.0f) {
            moveUp = 0.0f;
        }
    }
}


void specialKeyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: // Up arrow key
            moveUp += 5.0f; // Move the boat up
            if (moveUp>50.0f)
                moveUp=0.0f;
            break;
        case GLUT_KEY_DOWN: // Down arrow key
            moveUp -= 5.0f; // Move the boat down
            if (moveUp<-70.0f)
                moveUp=0.0f;
            break;
    }
}

void Ftimer(int value) {
    glutPostRedisplay();
    glutTimerFunc(10, stimer, 0);
}

//////////////////Fahad END//////////////////////

////////////////// Tansu Start/////////////////////
using namespace std;
float prancloud_x = 0.0f;
float prancloud_speed = 1.25f;
float SunY = 430.0f;
    float SunY_speed = .25f;
float prancar_x = 0.0f;
float prancar_y=1080.f;
float prancar_speed = 2.50f;
float pranplaneY=800.0f;
float pranplane_speed=2.0f;
float pranTrainX=-1000.0f;
float pranTrainSpeed=1.0f;
bool pranisNight = false;
bool pranisRaining = false;
bool pranTrainrunning=false;
float Boatx =0.0f;
    float Boatspeed = 1.0f;



void prandrawSun(float x, float y) {
    //glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 36; ++i) {
        float angle = i * 10.0f * 3.1415926f / 180.0f;
        float dx = 40.0f * cos(angle);
        float dy = 40.0f * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}
void pranCircle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}
void pranrectangle(int x, int y, int x1, int y1)
{
    glBegin(GL_QUADS);
        glVertex2d(x,y);
        glVertex2d(x,y1);
        glVertex2d(x1,y1);
        glVertex2d(x1,y);
    glEnd();
}



 void prancloud(){
     glPushMatrix();
     glTranslatef(prancloud_x, 0.0f, 0.0f);
     if (pranisNight) {
      glColor3f(0.2, 0.2, 0.2);



    } else {
         glColor3f(1.0, 1.0, 1.0);
    }
      pranCircle(30, 30, 100, 500);
        pranCircle(30, 30, 140, 500);
        pranCircle(30, 30, 140, 520); // Upper circle
        pranCircle(30, 30, 180, 500);

         glPopMatrix();
          prancloud_x += prancloud_speed;
        if (prancloud_x > 1080.0f) prancloud_x = -500.0f;
}
void prancloud1(){
    glPushMatrix();
     glTranslatef(prancloud_x, 0.0f, 0.0f);

        if (pranisNight) {
      glColor3f(0.2, 0.2, 0.2);



    } else {
         glColor3f(1.0, 1.0, 1.0);
    }


        pranCircle(30, 30, 250, 500);
        pranCircle(30, 30, 290, 500);
        pranCircle(30, 30, 290, 520); // Upper circle
        pranCircle(30, 30, 320, 500);
         glPopMatrix();
          prancloud_x += prancloud_speed;
        if (prancloud_x > 1080.0f) prancloud_x = -500.0f;
}


void mountain(){





 if (pranisNight) {
           glColor3f(0.0f, 0.0f, 0.f);
       } else {
            glColor3f(0.0f,0.2f,0.0f);
       }


    glBegin(GL_POLYGON);
    glVertex2f(0,350);
    glVertex2f(0,450);
    glVertex2f(50,450);
    glVertex2f(100,350);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(100,350);
    glVertex2f(160,470);
    glVertex2f(220,470);
    glVertex2f(280,350);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(280,350);
    glVertex2f(350,490);
    glVertex2f(400,490);
    glVertex2f(450,350);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(450,350);
    glVertex2f(500,450);
    glVertex2f(550,450);
    glVertex2f(590,350);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(590,350);
    glVertex2f(640,470);
    glVertex2f(700,470);
    glVertex2f(750,350);
    glEnd();

     glBegin(GL_POLYGON);
    glVertex2f(750,350);
    glVertex2f(800,450);
    glVertex2f(860,450);
    glVertex2f(910,350);
    glEnd();

     glBegin(GL_POLYGON);
    glVertex2f(910,350);
    glVertex2f(950,450);
    glVertex2f(1000,450);
    glVertex2f(1000,350);
    glEnd();

}
void pCircle(GLfloat rx,GLfloat ry,GLfloat cx,GLfloat cy){

    glBegin(GL_POLYGON);
    glVertex2f(cx,cy);
for(int i=0;i<360;i++){

    float angle=i*3.1416/180;
    float x=rx*cos(angle);
    float y=ry*sin(angle);
    glVertex2f((x+cx),(y+cy));

}
    glEnd();
}
void tree(){

glColor3f(0.4f, 0.10f, 0.1f);//brown
    glBegin(GL_QUADS);
    glVertex2f(310,250);
    glVertex2f(330,250);
    glVertex2f(330,350);
    glVertex2f(310,350);
    glEnd();


    glColor3f(0.0,0.3,0.0);
    pCircle(30,30,300,360);
    pCircle(30,30,340,360);
    pCircle(30,30,320,380);



    glColor3f(0.4f, 0.10f, 0.1f);//brown
    glBegin(GL_QUADS);
    glVertex2f(610,250);
    glVertex2f(630,250);
    glVertex2f(630,350);
    glVertex2f(610,350);
    glEnd();


    glColor3f(0.0,0.3,0.0);
    pCircle(30,30,600,360);
    pCircle(30,30,640,360);
    pCircle(30,30,620,380);

}
void house(){
//house
    glColor3f(0.65f, 0.16f, 0.16f);//brown
    glBegin(GL_QUADS);
    glVertex2f(50,250);
    glVertex2f(250,250);
    glVertex2f(250,350);
    glVertex2f(50,350);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);//black
    glBegin(GL_POLYGON);
    glVertex2f(250,250);
    glVertex2f(280,280);
    glVertex2f(280,350);
    glVertex2f(270,380);
    glVertex2f(250,350);
    glEnd();

    glColor3f(1.0f,0.5f, 0.0f);//yellow
    glBegin(GL_QUADS);
    glVertex2f(50,350);
    glVertex2f(250,350);
    glVertex2f(270,380);
    glVertex2f(70,380);
    glEnd();

//door
 if (pranisNight) {
           glColor3f(1.0f, 1.0f, 0.f);
       } else {
          glColor3f(0.0f, 0.0f, 0.0f);
       }
    glBegin(GL_QUADS);
    glVertex2f(80,250);
    glVertex2f(120,250);
    glVertex2f(120,300);
    glVertex2f(80,300);
    glEnd();

//window
 if (pranisNight) {
           glColor3f(1.0f, 1.0f, 0.f);
       } else {
          glColor3f(0.0f, 0.0f, 0.0f);
       }
    glBegin(GL_QUADS);
    glVertex2f(140,270);
    glVertex2f(170,270);
    glVertex2f(170,300);
    glVertex2f(140,300);
    glEnd();

//window
 if (pranisNight) {
           glColor3f(1.0f, 1.0f, 0.f);
       } else {
          glColor3f(0.0f, 0.0f, 0.0f);
       }
    glBegin(GL_QUADS);
    glVertex2f(200,270);
    glVertex2f(230,270);
    glVertex2f(230,300);
    glVertex2f(200,300);
    glEnd();

//house2
    glColor3f(0.65f, 0.16f, 0.16f);//brown
    glBegin(GL_QUADS);
    glVertex2f(400,250);
    glVertex2f(550,250);
    glVertex2f(550,350);
    glVertex2f(400,350);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);//black
    glBegin(GL_POLYGON);
    glVertex2f(550,250);
    glVertex2f(570,280);
    glVertex2f(570,350);
    glVertex2f(560,380);
    glVertex2f(550,350);
    glEnd();

    glColor3f(1.0f,0.5f, 0.0f);//yellow
    glBegin(GL_QUADS);
    glVertex2f(400,350);
    glVertex2f(550,350);
    glVertex2f(560,380);
    glVertex2f(420,380);
    glEnd();

//door
  if (pranisNight) {
           glColor3f(1.0f, 1.0f, 0.f);
       } else {
          glColor3f(0.0f, 0.0f, 0.0f);
       }

    glBegin(GL_QUADS);
    glVertex2f(430,250);
    glVertex2f(470,250);
    glVertex2f(470,300);
    glVertex2f(430,300);
    glEnd();

//window
 if (pranisNight) {
           glColor3f(1.0f, 1.0f, 0.f);
       } else {
          glColor3f(0.0f, 0.0f, 0.0f);
       }
    glBegin(GL_QUADS);
    glVertex2f(490,270);
    glVertex2f(520,270);
    glVertex2f(520,300);
    glVertex2f(490,300);
    glEnd();

//window
 if (pranisNight) {
           glColor3f(1.0f, 1.0f, 0.f);
       } else {
          glColor3f(0.0f, 0.0f, 0.0f);
       }
    glBegin(GL_QUADS);
    glVertex2f(200,270);
    glVertex2f(230,270);
    glVertex2f(230,300);
    glVertex2f(200,300);
    glEnd();




    //house
    glColor3f(0.65f, 0.16f, 0.16f);//brown
    glBegin(GL_QUADS);
    glVertex2f(700,250);
    glVertex2f(900,250);
    glVertex2f(900,350);
    glVertex2f(700,350);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);//black
    glBegin(GL_POLYGON);
    glVertex2f(900,250);
    glVertex2f(930,280);
    glVertex2f(930,350);
    glVertex2f(920,380);
    glVertex2f(900,350);
    glEnd();

    glColor3f(1.0f,0.5f, 0.0f);//yellow
    glBegin(GL_QUADS);
    glVertex2f(700,350);
    glVertex2f(900,350);
    glVertex2f(920,380);
    glVertex2f(720,380);
    glEnd();

//door
 if (pranisNight) {
           glColor3f(1.0f, 1.0f, 0.f);
       } else {
          glColor3f(0.0f, 0.0f, 0.0f);
       }
    glBegin(GL_QUADS);
    glVertex2f(720,250);
    glVertex2f(760,250);
    glVertex2f(760,300);
    glVertex2f(720,300);
    glEnd();

//window
 if (pranisNight) {
           glColor3f(1.0f, 1.0f, 0.f);
       } else {
          glColor3f(0.0f, 0.0f, 0.0f);
       }
    glBegin(GL_QUADS);
    glVertex2f(780,270);
    glVertex2f(810,270);
    glVertex2f(810,300);
    glVertex2f(780,300);
    glEnd();

//window
 if (pranisNight) {
           glColor3f(1.0f, 1.0f, 0.f);
       } else {
          glColor3f(0.0f, 0.0f, 0.0f);
       }
    glBegin(GL_QUADS);
    glVertex2f(830,270);
    glVertex2f(860,270);
    glVertex2f(860,300);
    glVertex2f(830,300);
    glEnd();

}
void pond(){

 if (pranisNight) {
           glColor3f(0.0f, 0.0f, 0.5f);
       } else {
          glColor3f(0.0f, 0.4f, 1.0f);
       }



    glBegin(GL_POLYGON);
    glVertex2f(1000,0);
    glVertex2f(1000,140);
    glVertex2f(750,100);
    glVertex2f(0,50);
    glVertex2f(0,0);
    glEnd();

    glLineWidth(15);
    glBegin(GL_LINES);
    glColor3f(0.6f, 0.298f, 0.0f);
    glVertex2i(0, 50);
    glVertex2i(750, 100);
    glEnd();

    glLineWidth(15);
    glBegin(GL_LINES);
    glColor3f(0.6f, 0.298f, 0.0f);
    glVertex2i(750, 100);
    glVertex2i(1000, 140);
    glEnd();

}
void mati(){

 if (pranisNight) {
           glColor3f(0.0f, 0.2f, 0.f);
       } else {
          glColor3f(0.0f, 0.5f, 0.0f);
       }
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(1000,0);
    glVertex2f(1000,350);
    glVertex2f(0,350);
    glEnd();
}

void pranrailline()
{
    //line background
    glColor3f(0.663, 0.663, 0.663);
    glBegin(GL_QUADS);
    glVertex2f(0, 185);
    glVertex2f(1000,185);
    glVertex2f(1000,230);
    glVertex2f(0, 230);


    glEnd();
    glBegin(GL_QUADS);//down black railline
    glColor3f(0, 0, 0);
    glVertex2f(0, 190);
    glVertex2f(1000, 190);
    glVertex2f(1000, 195);
    glVertex2f(0, 195);
    glEnd();

    glBegin(GL_QUADS);//upper black railline
    glColor3f(0, 0, 0);
    glVertex2f(0, 220);
    glVertex2f(1000, 220);
    glVertex2f(1000, 225);
    glVertex2f(0, 225);
    glEnd();




       glColor3f(0.3, 0.3, 0.3); // Dark gray color for rail line
       glBegin(GL_QUADS);
       for (int i =0 ; i <= 1000; i = i + 30) {
           glVertex2f(i, 190);
           glVertex2f(i + 5, 190);
           glVertex2f(i + 20, 225);
           glVertex2f(i + 25, 225);
       }
       glEnd();



}


void prantrain(){

    //left first
    glPushMatrix(); // Save the current transformation matrix
    glTranslatef(pranTrainX, 0, 0.0f);
    glColor3f(0.0, 0.2,0.7);
    glBegin(GL_QUADS);
    glVertex2f(0,200);
    glVertex2f(200,200);
    glVertex2f(200,300);
    glVertex2f(0,300);
    glEnd();
    //design
    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(0,210);
    glVertex2f(200,210);
    glVertex2f(200,220);
    glVertex2f(0,220);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(0,300);
    glVertex2f(200,300);
    glVertex2f(220,320);
    glVertex2f(30,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(200,300);
    glVertex2f(220,320);
    glVertex2f(220,230);
    glVertex2f(200,200);
    glEnd();

    //1st window
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(10,250);
    glVertex2f(40,250);
    glVertex2f(40,280);
    glVertex2f(10,280);
    glEnd();
    //2nd
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(50,250);
    glVertex2f(80,250);
    glVertex2f(80,280);
    glVertex2f(50,280);
    glEnd();
    //3rd
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(90,250);
    glVertex2f(120,250);
    glVertex2f(120,280);
    glVertex2f(90,280);
    glEnd();

    //1st door
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(130,220);
    glVertex2f(165,220);
    glVertex2f(165,280);
    glVertex2f(130,280);
    glEnd();



      //left second
    glColor3f(0.0, 0.2, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(220,200);
    glVertex2f(420,200);
    glVertex2f(420,300);
    glVertex2f(220,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(220,210);
    glVertex2f(420,210);
    glVertex2f(420,220);
    glVertex2f(220,220);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(220,300);
    glVertex2f(420,300);
    glVertex2f(440,320);
    glVertex2f(250,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(420,300);
    glVertex2f(440,320);
    glVertex2f(440,230);
    glVertex2f(420,200);
    glEnd();


     //1st window
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(230,250);
    glVertex2f(260,250);
    glVertex2f(260,280);
    glVertex2f(230,280);
    glEnd();
    //2nd
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(270,250);
    glVertex2f(300,250);
    glVertex2f(300,280);
    glVertex2f(270,280);
    glEnd();
    //3rd
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(310,250);
    glVertex2f(340,250);
    glVertex2f(340,280);
    glVertex2f(310,280);
    glEnd();

    // door
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(355,220);
    glVertex2f(390,220);
    glVertex2f(390,280);
    glVertex2f(355,280);
    glEnd();


      //left 3rd
    glColor3f(0.0, 0.2, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(440,200);
    glVertex2f(640,200);
    glVertex2f(640,300);
    glVertex2f(440,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(440,210);
    glVertex2f(640,210);
    glVertex2f(640,220);
    glVertex2f(440,220);
    glEnd();


    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(440,300);
    glVertex2f(640,300);
    glVertex2f(660,320);
    glVertex2f(470,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(640,300);
    glVertex2f(660,320);
    glVertex2f(660,230);
    glVertex2f(640,200);
    glEnd();


    //1st window
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(450,250);
    glVertex2f(480,250);
    glVertex2f(480,280);
    glVertex2f(450,280);
    glEnd();
    //2nd
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(490,250);
    glVertex2f(520,250);
    glVertex2f(520,280);
    glVertex2f(490,280);
    glEnd();
    //3rd
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(530,250);
    glVertex2f(560,250);
    glVertex2f(560,280);
    glVertex2f(530,280);
    glEnd();

    // door
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(580,220);
    glVertex2f(615,220);
    glVertex2f(615,280);
    glVertex2f(580,280);
    glEnd();


      //head eng
      glColor3f(0.0,0.2,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(660,200);
    glVertex2f(860,200);
    glVertex2f(860,250);
    glVertex2f(760,300);
    glVertex2f(660,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(660,210);
    glVertex2f(860,210);
    glVertex2f(860,220);
    glVertex2f(660,220);
    glEnd();


    glColor3f(0.0,0.0,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(660,300);
    glVertex2f(760,300);
    glVertex2f(790,320);
    glVertex2f(690,320);
    glEnd();

    glColor3f(0.0,0.6,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(760,300);
    glVertex2f(790,320);
    glVertex2f(880,270);
    glVertex2f(860,250);
    glEnd();

    glColor3f(0.7,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(860,200);
    glVertex2f(860,250);
    glVertex2f(880,270);
    glVertex2f(880,225);
    glEnd();

     // door
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(680,220);
    glVertex2f(720,220);
    glVertex2f(720,280);
    glVertex2f(680,280);
    glEnd();

      //window
    if (pranisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(730,250);
    glVertex2f(760,250);
    glVertex2f(760,280);
    glVertex2f(730,280);
    glEnd();

    //chaka
    glColor3f(0.0, 0.0, 0.0);
      pranCircle(10, 10, 10, 200);
      pranCircle(10, 10, 60, 200);
      pranCircle(10, 10, 110, 200);
      pranCircle(10, 10, 170, 200);

      pranCircle(10, 10, 250, 200);
      pranCircle(10, 10, 300, 200);
      pranCircle(10, 10, 350, 200);
       pranCircle(10, 10,400, 200);


      pranCircle(10, 10, 460, 200);
      pranCircle(10, 10, 510, 200);
      pranCircle(10, 10, 560, 200);
       pranCircle(10, 10,620, 200);

       pranCircle(10, 10, 680, 200);
      pranCircle(10, 10, 730, 200);
      pranCircle(10, 10, 780, 200);
       pranCircle(10, 10,830, 200);

    glPopMatrix(); // Restore the transformation matrix


        // Update the boat's position for movement
        pranTrainX += pranTrainSpeed;
        if (pranTrainX > 1200.0f) pranTrainX = -1080.0f;




}
void boat(){
    //lower
    glPushMatrix();
    glTranslatef(Boatx, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(50, 30);
    glVertex2f(150, 30);
    glVertex2f(200, 70);
    glVertex2f(0, 70);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glVertex2f(40,70);
    glVertex2f(160,70);
    glVertex2f(130,100);
     glVertex2f(70,100);

    glEnd();
    glPopMatrix();
    if (SunY< 520.0f){
        SunY += SunY_speed;
    } //SunY = -270.0f;

    Boatx += Boatspeed;
    if (Boatx > 990.0f) Boatx = -270.0f;
}

void PranDisplay()

{

     glClear(GL_COLOR_BUFFER_BIT);

    if (pranisNight) {
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f);


    } else {
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    }

     if (pranisNight) {
        glColor3f(1.0f, 1.0f, 1.0f);
        prandrawSun(150.0f, SunY);

    } else {
        glColor3f(1.0f, 1.0f, 0.0f);
          prandrawSun(150.0f, SunY);
    }


    prancloud1();

     prancloud();
     mountain();
     mati();;


house();tree();
    pranrailline();


    prantrain();
    pond();

 boat();

glFlush();




 }


void praninit()
{
    glClearColor(0.3, .65, 1, 1.0);  //light blue
    gluOrtho2D(0,1000,0,600);
}
void prantimer(int value) {
    glutPostRedisplay();
    glutTimerFunc(10, prantimer, 0);
}



void pranhandleMouse(int button, int state, int x, int y) {

if (button == GLUT_LEFT_BUTTON)
    {
       Boatspeed += 0.85f;
    }


else if (button == GLUT_RIGHT_BUTTON)
    {
        Boatspeed -= 0.85f;
    }
glutPostRedisplay();
}



void prankeyboard(unsigned char key, int x, int y) {

    if (key == '1') {
           Ridwandisplay = true;
           Fahaddisplay = false;
           Sourovdisplay = false;
           PrantoDisplay = false;
       } if (key == '2') {
           Ridwandisplay = false;
           Fahaddisplay = true;
           Sourovdisplay = false;
           PrantoDisplay = false;
       } if (key == '3') {
           Ridwandisplay = false;
           Fahaddisplay = false;
           Sourovdisplay = true;
           PrantoDisplay = false;
       } if (key == '4') {
           Ridwandisplay = false;
           Fahaddisplay = false;
           Sourovdisplay = false;
           PrantoDisplay = true;
       }
    if (key == 'n' || key == 'N') {
        pranisNight = true;


    } else if (key == 'd' || key == 'D') {
        pranisNight = false;

    }
    else if(key=='r'||key == 'R'){
         pranisRaining=true;
    }
     else if(key=='e'||key == 'E'){
         pranisRaining=false;
    }
     else if(key=='T'||key == 't'){
         pranisRaining=false;

    pranTrainrunning = !pranTrainrunning; // Toggle train state
               if (pranTrainrunning) {
                   pranTrainSpeed = 1.0f; // Start train
               } else {
                   pranTrainSpeed = 0.0f; // Stop train
               }
     }
    glutPostRedisplay();
}

//////////////// Tansu End//////////////////////

/////////////// Rid Start////////////////////

bool RidTrainrunning=false;
float Ridcloud_x = 0.0f;
float Ridcloud_speed = 1.25f;
float RidSunY = 400.0f;
float Ridsun_speed = .25f;
float Ridcar_x = 0.0f;
float Ridcar_y=1080.f;
float Ridcar_speed = 2.50f;
float RidplaneY=800.0f;
float Ridplane_speed=2.0f;
float RidTrainX=-500.0f;
float RidTrainSpeed=1.0f;
bool RidisNight = false;
bool RidisRaining = false;


void RidRain() {
    glColor3f(1.0f, 1.0f, 1.0f);
    int numDrops = 500;
    int rainLength = 10;

    for (int i = 0; i < numDrops; i++) {
        float x = (rand() % 2000) - 1000;
        float y = rand() % 600;
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y - rainLength);
        glEnd();
    }
}
void RiddrawSun(float x, float y) {
    //glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 36; ++i) {
        float angle = i * 10.0f * 3.1415926f / 180.0f;
        float dx = 40.0f * cos(angle);
        float dy = 40.0f * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}
void RidCircle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}
void Ridrectangle(int x, int y, int x1, int y1)
{
    glBegin(GL_QUADS);
        glVertex2d(x,y);
        glVertex2d(x,y1);
        glVertex2d(x1,y1);
        glVertex2d(x1,y);
    glEnd();
}



 void Ridcloud(){
     glPushMatrix();
     glTranslatef(Ridcloud_x, 0.0f, 0.0f);
     if (RidisNight) {
      glColor3f(0.2, 0.2, 0.2);



    } else {
         glColor3f(1.0, 1.0, 1.0);
    }
      RidCircle(30, 30, 100, 500);
        RidCircle(30, 30, 140, 500);
        RidCircle(30, 30, 140, 520); // Upper circle
        RidCircle(30, 30, 180, 500);

         glPopMatrix();
          Ridcloud_x += Ridcloud_speed;
        if (Ridcloud_x > 1080.0f) Ridcloud_x = -500.0f;
}
void Ridcloud1(){
    glPushMatrix();
     glTranslatef(Ridcloud_x, 0.0f, 0.0f);

        if (RidisNight) {
      glColor3f(0.2, 0.2, 0.2);



    } else {
         glColor3f(1.0, 1.0, 1.0);
    }


        RidCircle(30, 30, 250, 500);
        RidCircle(30, 30, 290, 500);
        RidCircle(30, 30, 290, 520); // Upper circle
        RidCircle(30, 30, 320, 500);
         glPopMatrix();
          Ridcloud_x += Ridcloud_speed;
        if (Ridcloud_x > 1080.0f) Ridcloud_x = -500.0f;
}

void Ridroad()

{
  //  drawSun(150.0f, SunY);


        //Road Area
        glColor3f(0.3, 0.3, 0.3);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(1000, 0);
        glVertex2f(1000, 200);
        glVertex2f(0, 200);
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(1000, 0);
        glVertex2f(1000, 5);
        glVertex2f(0, 5);
        glEnd();
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex2f(0, 200);
        glVertex2f(1000, 200);
        glVertex2f(1000, 205);
        glVertex2f(0, 205);
        glEnd();
        //divider 1st
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glVertex2f(50, 100);
        glVertex2f(250, 100);
        glVertex2f(250, 90);
        glVertex2f(50, 90);
        glEnd();
        //divider 2nd
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glVertex2f(300, 100);
        glVertex2f(500, 100);
        glVertex2f(500, 90);
        glVertex2f(300, 90);
        glEnd();
        //divider  3rd
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glVertex2f(550, 100);
        glVertex2f(750, 100);
        glVertex2f(750, 90);
        glVertex2f(550, 90);
        glEnd();
        //divider  4th

        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glVertex2f(800, 100);
        glVertex2f(1000, 100);
        glVertex2f(1000, 90);
        glVertex2f(800, 90);
        glEnd();

        if (RidSunY < 530.0f) //SunY = 500.0f;
        {RidSunY += Ridsun_speed;}


        Ridcar_x += Ridcar_speed;
        if (Ridcar_x > 1080.0f) Ridcar_x = -80.0f;
         Ridcar_y -= Ridcar_speed;
        if (Ridcar_y < -80.0f) Ridcar_y = 1080.0f;


}
void Ridmati(){
 glColor3f(0.58, 0.52, 0.05);
 glBegin(GL_QUADS);
    glVertex2f(0, 230);
    glVertex2f(1000,230);
    glVertex2f(1000,260);
    glVertex2f(0, 260);
  glEnd();
}
void Ridstation(){

glColor3f(0.663, 0.663, 0.663);
 glBegin(GL_QUADS);
    glVertex2f(15, 240);
    glVertex2f(300,240);
    glVertex2f(300,340);
    glVertex2f(15, 340);
  glEnd();

  glColor3f(1.0,1.0, 0.0);
 glBegin(GL_QUADS);
    glVertex2f(5,340);
    glVertex2f(310,340);
    glVertex2f(310,380);
    glVertex2f(5, 380);
  glEnd();

 glColor3f(1.0,0.5, 0.0);
 glBegin(GL_QUADS);
    glVertex2f(10,380);
    glVertex2f(300,380);
    glVertex2f(300,390);
    glVertex2f(10, 390);
  glEnd();



}


 void Ridhouse(){

glColor3f(1.0, 0.6, 0.2);
 glBegin(GL_QUADS);
    glVertex2f(340, 240);
    glVertex2f(420,240);
    glVertex2f(420,370);
    glVertex2f(340, 370);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
 glBegin(GL_QUADS);
    glVertex2f(420, 240);
    glVertex2f(440,260);
    glVertex2f(440,370);
    glVertex2f(420, 370);
  glEnd();




//house2

glColor3f(1.0, 0.6, 0.2);
 glBegin(GL_QUADS);
    glVertex2f(560, 240);
    glVertex2f(650,240);
    glVertex2f(650,400);
    glVertex2f(560, 400);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
 glBegin(GL_QUADS);
    glVertex2f(650, 240);
    glVertex2f(680,260);
    glVertex2f(680,400);
    glVertex2f(650, 400);
  glEnd();


  //house3

glColor3f(1.0, 0.6, 0.2);
 glBegin(GL_QUADS);
    glVertex2f(700, 240);
    glVertex2f(760,240);
    glVertex2f(760,450);
    glVertex2f(700, 450);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
 glBegin(GL_QUADS);
    glVertex2f(760, 240);
    glVertex2f(770,260);
    glVertex2f(770,450);
    glVertex2f(760, 450);
  glEnd();



  //house3

glColor3f(0.0, 0.0, 1.0);
 glBegin(GL_QUADS);
    glVertex2f(780, 240);
    glVertex2f(840,240);
    glVertex2f(840,450);
    glVertex2f(780, 450);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
 glBegin(GL_QUADS);
    glVertex2f(840, 240);
    glVertex2f(850,260);
    glVertex2f(850,450);
    glVertex2f(840, 450);
  glEnd();


    //house4

glColor3f(1.0, 0.3, 0.0);
 glBegin(GL_QUADS);
    glVertex2f(860, 240);
    glVertex2f(960,240);
    glVertex2f(960,430);
    glVertex2f(860, 430);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
 glBegin(GL_QUADS);
    glVertex2f(960, 240);
    glVertex2f(980,260);
    glVertex2f(980,430);
    glVertex2f(960, 430);
  glEnd();

 // Door last
 if (RidisNight) {
       glColor3f(1.0f, 1.0, 1.0f);
    } else {
        glColor3f(1.0f, 0.9f, 0.55f);
    }

 glBegin(GL_QUADS);
    glVertex2f(870, 240);
    glVertex2f(950,240);
    glVertex2f(950,270);
    glVertex2f(870, 270);
  glEnd();

 glBegin(GL_QUADS);
    glVertex2f(790, 240);
    glVertex2f(830,240);
    glVertex2f(830,310);
    glVertex2f(790, 310);
  glEnd();

 glBegin(GL_QUADS);
    glVertex2f(710, 240);
    glVertex2f(750,240);
    glVertex2f(750,310);
    glVertex2f(710, 310);
  glEnd();

 glBegin(GL_QUADS);
    glVertex2f(570, 245);
    glVertex2f(640,245);
    glVertex2f(640,300);
    glVertex2f(570, 300);
  glEnd();
   glBegin(GL_QUADS);
    glVertex2f(350, 240);
    glVertex2f(410,240);
    glVertex2f(410,300);
    glVertex2f(350, 300);
  glEnd();


   if (RidisNight) {
        glColor3f(1.0f, 1.0, 1.0f);
    } else {
         glColor3f(1.0f, 0.9f, 0.55f);
    }

  glBegin(GL_QUADS);
    glVertex2f(350, 340);
    glVertex2f(375,340);
    glVertex2f(375,360);
    glVertex2f(350,360);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(385, 340);
    glVertex2f(410,340);
    glVertex2f(410,360);
    glVertex2f(385,360);
  glEnd();

   glBegin(GL_QUADS);
    glVertex2f(350, 310);
    glVertex2f(375,310);
    glVertex2f(375,330);
    glVertex2f(350,330);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(385, 310);
    glVertex2f(410,310);
    glVertex2f(410,330);
    glVertex2f(385,330);
  glEnd();
  //door 2nd house


 glBegin(GL_QUADS);
    glVertex2f(570, 310);
    glVertex2f(600,310);
    glVertex2f(600,340);
    glVertex2f(570, 340);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(610, 310);
    glVertex2f(640,310);
    glVertex2f(640,340);
    glVertex2f(610, 340);
  glEnd();
   glBegin(GL_QUADS);
    glVertex2f(570, 310);
    glVertex2f(600,310);
    glVertex2f(600,340);
    glVertex2f(570, 340);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(610, 350);
    glVertex2f(640,350);
    glVertex2f(640,380);
    glVertex2f(610, 380);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(570, 350);
    glVertex2f(600,350);
    glVertex2f(600,380);
    glVertex2f(570, 380);
  glEnd();
  //house 3 windows

      glBegin(GL_QUADS);
    glVertex2f(710, 410);
    glVertex2f(750,410);
    glVertex2f(750,440);
    glVertex2f(710, 440);
  glEnd();
   glBegin(GL_QUADS);
    glVertex2f(710, 370);
    glVertex2f(750,370);
    glVertex2f(750,400);
    glVertex2f(710, 400);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(710, 330);
    glVertex2f(750,330);
    glVertex2f(750,360);
    glVertex2f(710, 360);
  glEnd();
  //house 4 windows

 glBegin(GL_QUADS);
    glVertex2f(790, 410);
    glVertex2f(830,410);
    glVertex2f(830,440);
    glVertex2f(790, 440);
  glEnd();
   glBegin(GL_QUADS);
    glVertex2f(790, 370);
    glVertex2f(830,370);
    glVertex2f(830,400);
    glVertex2f(790, 400);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(790, 330);
    glVertex2f(830,330);
    glVertex2f(830,360);
    glVertex2f(790, 360);
  glEnd();
  //house 5 windows

  glBegin(GL_QUADS);
    glVertex2f(870, 275);
    glVertex2f(905,275);
    glVertex2f(905,305);
    glVertex2f(870, 305);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(910, 275);
    glVertex2f(950,275);
    glVertex2f(950,305);
    glVertex2f(910, 305);
  glEnd();
 glBegin(GL_QUADS);
    glVertex2f(870, 310);
    glVertex2f(905,310);
    glVertex2f(905,340);
    glVertex2f(870, 340);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(910, 310);
    glVertex2f(950,310);
    glVertex2f(950,340);
    glVertex2f(910, 340);
  glEnd();
   glBegin(GL_QUADS);
    glVertex2f(870, 310);
    glVertex2f(905,310);
    glVertex2f(870,340);
    glVertex2f(905, 340);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(910, 345);
    glVertex2f(950,345);
    glVertex2f(950,380);
    glVertex2f(910, 380);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(870, 345);
    glVertex2f(905,345);
    glVertex2f(905,380);
    glVertex2f(870, 380);
  glEnd();
   glBegin(GL_QUADS);
    glVertex2f(910, 385);
    glVertex2f(950,385);
    glVertex2f(950,420);
    glVertex2f(910, 420);
  glEnd();
  glBegin(GL_QUADS);
    glVertex2f(870, 385);
    glVertex2f(905,385);
    glVertex2f(905,420);
    glVertex2f(870, 420);
  glEnd();



}

void ppCircle(GLfloat rx,GLfloat ry,GLfloat cx,GLfloat cy){

glBegin(GL_POLYGON);
glVertex2f(cx,cy);
for(int i=0;i<360;i++){

    float angle=i*3.1416/180;
    float x=rx*cos(angle);
    float y=ry*sin(angle);
    glVertex2f((x+cx),(y+cy));

}
glEnd();
}
void Ridtree(){

glColor3f(0.4f, 0.10f, 0.1f);//brown
    glBegin(GL_QUADS);
    glVertex2f(490,250);
    glVertex2f(505,250);
    glVertex2f(505,350);
    glVertex2f(490,350);
    glEnd();


glColor3f(0.0,0.3,0.0);
ppCircle(30,30,515,360);
ppCircle(30,30,480,360);
ppCircle(30,30,500,380);


}
void Ridplan(){
         glPushMatrix();
     glTranslatef( RidplaneY, 0.0f, 0.0f);



        glColor3f(0.3, 1.3, 0.3);
        glBegin(GL_QUADS);
        glVertex2f(450, 520);
        glVertex2f(640, 520);
        glVertex2f(670, 470);
        glVertex2f(450, 470);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2f(640, 520);
        glVertex2f(710, 560);
        glVertex2f(670, 470);

        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2f(520, 520);
        glVertex2f(610, 570);
        glVertex2f(590, 520);
        glEnd();
        RidCircle(30,25,450,495);


        //plan door
         glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex2f(460, 515);
        glVertex2f(480, 515);
        glVertex2f(480, 475);
        glVertex2f(460, 475);
        glEnd();
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex2f(500, 507);
        glVertex2f(530, 507);
        glVertex2f(530, 485);
        glVertex2f(500, 485);
        glEnd();
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex2f(550, 507);
        glVertex2f(580, 507);
        glVertex2f(580, 485);
        glVertex2f(550, 485);
        glEnd();
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex2f(600, 507);
        glVertex2f(630, 507);
        glVertex2f(630, 485);
        glVertex2f(600, 485);
        glEnd();
        glPopMatrix();
           RidplaneY -= Ridplane_speed;
        if ( RidplaneY < -700.0f)  RidplaneY = 700.0f;


}

void Ridrailline()
{
    //line background
    glColor3f(0.663, 0.663, 0.663);
    glBegin(GL_QUADS);
    glVertex2f(0, 185);
    glVertex2f(1000,185);
    glVertex2f(1000,230);
    glVertex2f(0, 230);


    glEnd();
    glBegin(GL_QUADS);//down black railline
    glColor3f(0, 0, 0);
    glVertex2f(0, 190);
    glVertex2f(1000, 190);
    glVertex2f(1000, 195);
    glVertex2f(0, 195);
    glEnd();

    glBegin(GL_QUADS);//upper black railline
    glColor3f(0, 0, 0);
    glVertex2f(0, 220);
    glVertex2f(1000, 220);
    glVertex2f(1000, 225);
    glVertex2f(0, 225);
    glEnd();




       glColor3f(0.3, 0.3, 0.3); // Dark gray color for rail line
       glBegin(GL_QUADS);
       for (int i =0 ; i <= 1000; i = i + 30) {
           glVertex2f(i, 190);
           glVertex2f(i + 5, 190);
           glVertex2f(i + 20, 225);
           glVertex2f(i + 25, 225);
       }
       glEnd();



}
void RiddrawCar() {
    glPushMatrix();
    glTranslatef(Ridcar_x, 130.0f, 0.0f); // Position the car

    // Car body (bottom part)
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for body
    glBegin(GL_QUADS);
    glVertex2f(-50.0f, 0.0f);
    glVertex2f(50.0f, 0.0f);
    glVertex2f(50.0f, 25.0f);
    glVertex2f(-50.0f, 25.0f);
    glEnd();

    // Car roof
    glColor3f(0.2f, 0.2f, 0.2f); // Gray roof
    glBegin(GL_QUADS);
    glVertex2f(-35.0f, 25.0f);
    glVertex2f(35.0f, 25.0f);
    glVertex2f(25.0f, 50.0f);
    glVertex2f(-25.0f, 50.0f);
    glEnd();

    // Windows
    glColor3f(0.0f, 0.7f, 1.0f); // Light blue windows
    // Front window
    glBegin(GL_QUADS);
    glVertex2f(-25.0f, 25.0f);
    glVertex2f(25.0f, 25.0f);
    glVertex2f(20.0f, 45.0f);
    glVertex2f(-20.0f, 45.0f);
    glEnd();
    // Left window
    glBegin(GL_QUADS);
    glVertex2f(-30.0f, 25.0f);
    glVertex2f(-20.0f, 25.0f);
    glVertex2f(-15.0f, 45.0f);
    glVertex2f(-25.0f, 45.0f);
    glEnd();
    // Right window
    glBegin(GL_QUADS);
    glVertex2f(20.0f, 25.0f);
    glVertex2f(30.0f, 25.0f);
    glVertex2f(25.0f, 45.0f);
    glVertex2f(15.0f, 45.0f);
    glEnd();

    // Wheels
    glColor3f(0.0f, 0.0f, 0.0f); // Black for tires
   float offsets[] = {-30.0f, 30.0f};
for (int i = 0; i < 2; ++i) {
    float offsetX = offsets[i];
    glBegin(GL_POLYGON);
    for (int j = 0; j < 360; ++j) {
        float theta = j * 3.14159f / 180.0f;
        glVertex2f(offsetX + 10.0f * cos(theta), -10.0f + 10.0f * sin(theta));
    }
    glEnd();
}


    // Headlights
    glColor3f(1.0f, 1.0f, 0.5f); // Yellow for headlights
    glBegin(GL_QUADS);
    glVertex2f(50.0f, 10.0f);
    glVertex2f(55.0f, 10.0f);
    glVertex2f(55.0f, 20.0f);
    glVertex2f(50.0f, 20.0f);
    glEnd();

    // Taillights
    glColor3f(1.0f, 0.0f, 0.0f); // Red for taillights
    glBegin(GL_QUADS);
    glVertex2f(-55.0f, 10.0f);
    glVertex2f(-50.0f, 10.0f);
    glVertex2f(-50.0f, 20.0f);
    glVertex2f(-55.0f, 20.0f);
    glEnd();

    glPopMatrix();
}


void RiddrawCar2() {


    // Car body
     glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for car body
    glTranslatef(Ridcar_y, 30.0f, 0.0f); // Blue color for body
    glBegin(GL_QUADS);
    glVertex2f(-50.0f, 0.0f);
    glVertex2f(50.0f, 0.0f);
    glVertex2f(50.0f, 25.0f);
    glVertex2f(-50.0f, 25.0f);
    glEnd();

    // Car roof
    glColor3f(0.2f, 0.2f, 0.2f); // Gray roof
    glBegin(GL_QUADS);
    glVertex2f(-35.0f, 25.0f);
    glVertex2f(35.0f, 25.0f);
    glVertex2f(25.0f, 50.0f);
    glVertex2f(-25.0f, 50.0f);
    glEnd();

    // Windows
    glColor3f(0.0f, 0.7f, 1.0f); // Light blue windows
    // Front window
    glBegin(GL_QUADS);
    glVertex2f(-25.0f, 25.0f);
    glVertex2f(25.0f, 25.0f);
    glVertex2f(20.0f, 45.0f);
    glVertex2f(-20.0f, 45.0f);
    glEnd();
    // Left window
    glBegin(GL_QUADS);
    glVertex2f(-30.0f, 25.0f);
    glVertex2f(-20.0f, 25.0f);
    glVertex2f(-15.0f, 45.0f);
    glVertex2f(-25.0f, 45.0f);
    glEnd();
    // Right window
    glBegin(GL_QUADS);
    glVertex2f(20.0f, 25.0f);
    glVertex2f(30.0f, 25.0f);
    glVertex2f(25.0f, 45.0f);
    glVertex2f(15.0f, 45.0f);
    glEnd();

    // Wheels
    glColor3f(0.0f, 0.0f, 0.0f); // Black for tires
   float offsets[] = {-30.0f, 30.0f};
for (int i = 0; i < 2; ++i) {
    float offsetX = offsets[i];
    glBegin(GL_POLYGON);
    for (int j = 0; j < 360; ++j) {
        float theta = j * 3.14159f / 180.0f;
        glVertex2f(offsetX + 10.0f * cos(theta), -10.0f + 10.0f * sin(theta));
    }
    glEnd();
}


    // Headlights
    glColor3f(1.0f, 1.0f, 0.5f); // Yellow for headlights
    glBegin(GL_QUADS);
    glVertex2f(50.0f, 10.0f);
    glVertex2f(55.0f, 10.0f);
    glVertex2f(55.0f, 20.0f);
    glVertex2f(50.0f, 20.0f);
    glEnd();

    // Taillights
    glColor3f(1.0f, 0.0f, 0.0f); // Red for taillights
    glBegin(GL_QUADS);
    glVertex2f(-55.0f, 10.0f);
    glVertex2f(-50.0f, 10.0f);
    glVertex2f(-50.0f, 20.0f);
    glVertex2f(-55.0f, 20.0f);
    glEnd();

    glPopMatrix();
}
void Ridtrain(){

    //left first
    glPushMatrix(); // Save the current transformation matrix
    glTranslatef(RidTrainX, 0, 0.0f);
    glColor3f(0.0, 0.2,0.7);
    glBegin(GL_QUADS);
    glVertex2f(0,200);
    glVertex2f(200,200);
    glVertex2f(200,300);
    glVertex2f(0,300);
    glEnd();
    //design
    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(0,210);
    glVertex2f(200,210);
    glVertex2f(200,220);
    glVertex2f(0,220);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(0,300);
    glVertex2f(200,300);
    glVertex2f(220,320);
    glVertex2f(30,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(200,300);
    glVertex2f(220,320);
    glVertex2f(220,230);
    glVertex2f(200,200);
    glEnd();

    //1st window
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(10,250);
    glVertex2f(40,250);
    glVertex2f(40,280);
    glVertex2f(10,280);
    glEnd();
    //2nd
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(50,250);
    glVertex2f(80,250);
    glVertex2f(80,280);
    glVertex2f(50,280);
    glEnd();
    //3rd
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(90,250);
    glVertex2f(120,250);
    glVertex2f(120,280);
    glVertex2f(90,280);
    glEnd();

    //1st door
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(130,220);
    glVertex2f(165,220);
    glVertex2f(165,280);
    glVertex2f(130,280);
    glEnd();



      //left second
    glColor3f(0.0, 0.2, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(220,200);
    glVertex2f(420,200);
    glVertex2f(420,300);
    glVertex2f(220,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(220,210);
    glVertex2f(420,210);
    glVertex2f(420,220);
    glVertex2f(220,220);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(220,300);
    glVertex2f(420,300);
    glVertex2f(440,320);
    glVertex2f(250,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(420,300);
    glVertex2f(440,320);
    glVertex2f(440,230);
    glVertex2f(420,200);
    glEnd();


     //1st window
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(230,250);
    glVertex2f(260,250);
    glVertex2f(260,280);
    glVertex2f(230,280);
    glEnd();
    //2nd
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(270,250);
    glVertex2f(300,250);
    glVertex2f(300,280);
    glVertex2f(270,280);
    glEnd();
    //3rd
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(310,250);
    glVertex2f(340,250);
    glVertex2f(340,280);
    glVertex2f(310,280);
    glEnd();

    // door
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(355,220);
    glVertex2f(390,220);
    glVertex2f(390,280);
    glVertex2f(355,280);
    glEnd();


      //left 3rd
    glColor3f(0.0, 0.2, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(440,200);
    glVertex2f(640,200);
    glVertex2f(640,300);
    glVertex2f(440,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(440,210);
    glVertex2f(640,210);
    glVertex2f(640,220);
    glVertex2f(440,220);
    glEnd();


    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(440,300);
    glVertex2f(640,300);
    glVertex2f(660,320);
    glVertex2f(470,320);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(640,300);
    glVertex2f(660,320);
    glVertex2f(660,230);
    glVertex2f(640,200);
    glEnd();


    //1st window
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(450,250);
    glVertex2f(480,250);
    glVertex2f(480,280);
    glVertex2f(450,280);
    glEnd();
    //2nd
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(490,250);
    glVertex2f(520,250);
    glVertex2f(520,280);
    glVertex2f(490,280);
    glEnd();
    //3rd
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(530,250);
    glVertex2f(560,250);
    glVertex2f(560,280);
    glVertex2f(530,280);
    glEnd();

    // door
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(580,220);
    glVertex2f(615,220);
    glVertex2f(615,280);
    glVertex2f(580,280);
    glEnd();


      //head eng
      glColor3f(0.0,0.2,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(660,200);
    glVertex2f(860,200);
    glVertex2f(860,250);
    glVertex2f(760,300);
    glVertex2f(660,300);
    glEnd();

    glColor3f(1.0, 0.6, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(660,210);
    glVertex2f(860,210);
    glVertex2f(860,220);
    glVertex2f(660,220);
    glEnd();


    glColor3f(0.0,0.0,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(660,300);
    glVertex2f(760,300);
    glVertex2f(790,320);
    glVertex2f(690,320);
    glEnd();

    glColor3f(0.0,0.6,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(760,300);
    glVertex2f(790,320);
    glVertex2f(880,270);
    glVertex2f(860,250);
    glEnd();

    glColor3f(0.7,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(860,200);
    glVertex2f(860,250);
    glVertex2f(880,270);
    glVertex2f(880,225);
    glEnd();

     // door
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(680,220);
    glVertex2f(720,220);
    glVertex2f(720,280);
    glVertex2f(680,280);
    glEnd();

      //window
    if (RidisNight) {
           glColor3f(1.0f, 1.0f, 1.0f);  // Sky blue (Day)
       } else {
           glColor3f(1.0f, 0.9f, 0.55f);   // Warm yellow glow (Night)
       }
    glBegin(GL_QUADS);
    glVertex2f(730,250);
    glVertex2f(760,250);
    glVertex2f(760,280);
    glVertex2f(730,280);
    glEnd();

    //chaka
    glColor3f(0.0, 0.0, 0.0);
      RidCircle(10, 10, 10, 200);
      RidCircle(10, 10, 60, 200);
      RidCircle(10, 10, 110, 200);
      RidCircle(10, 10, 170, 200);

      RidCircle(10, 10, 250, 200);
      RidCircle(10, 10, 300, 200);
      RidCircle(10, 10, 350, 200);
       RidCircle(10, 10,400, 200);


      RidCircle(10, 10, 460, 200);
      RidCircle(10, 10, 510, 200);
      RidCircle(10, 10, 560, 200);
       RidCircle(10, 10,620, 200);

       RidCircle(10, 10, 680, 200);
      RidCircle(10, 10, 730, 200);
      RidCircle(10, 10, 780, 200);
       RidCircle(10, 10,830, 200);

    glPopMatrix(); // Restore the transformation matrix


        // Update the boat's position for movement
        RidTrainX += RidTrainSpeed;
        if (RidTrainX > 1200.0f) RidTrainX = -1080.0f;



}

void Riddisplay()

{

    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 600);

    if (RidisNight) {
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f);


    } else {
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    }

     if (RidisNight) {
        glColor3f(1.0f, 1.0f, 1.0f);
        RiddrawSun(150.0f, RidSunY);

    } else {
        glColor3f(1.0f, 1.0f, 0.0f);
          RiddrawSun(150.0f, RidSunY);
    }

    Ridroad();
    Ridcloud1();
     Ridplan();
     Ridcloud();
     Ridmati();

    Ridrailline();

    RiddrawCar();
    RiddrawCar2();
    Ridstation();
    Ridhouse();
    Ridtree();
    Ridtrain();

 if (RidisRaining) {
        RidRain();
 }
glFlush();


    //

 }


void Ridinit()
{
    glClearColor(0.3, .65, 1, 1.0);  //light blue
    gluOrtho2D(0,1000,0,600);
}
void Ridtimer(int value) {
    glutPostRedisplay();
    glutTimerFunc(10, Ridtimer, 0);
}
void Ridkeyboard(unsigned char key, int x, int y) {

    if(key=='1')
    {
        Ridwandisplay= true;
        Fahaddisplay= false;
        Sourovdisplay=false;
        PrantoDisplay= false;
    }
    if(key=='2')
    {
        Ridwandisplay= false;
        Fahaddisplay= true;
        Sourovdisplay=false;
        PrantoDisplay= false;

    }
    if(key=='3')
    {
        Ridwandisplay= false;
        Fahaddisplay= false;
        Sourovdisplay=true;
        PrantoDisplay= false;

    }
    if(key=='4')
    {
        Ridwandisplay= false;
        Fahaddisplay= false;
        Sourovdisplay=false;
        PrantoDisplay= true;

    }

    if (key == 'n' || key == 'N') {
          RidisNight = true;


      } else if (key == 'd' || key == 'D') {
          RidisNight = false;

      }
      else if(key=='r'||key == 'R'){
           RidisRaining=true;
      }
       else if(key=='e'||key == 'E'){
           RidisRaining=false;
      }
       else if(key=='T'||key == 't'){
           RidisRaining=false;

      RidTrainrunning = !RidTrainrunning; // Toggle train state
                 if (RidTrainrunning) {
                     RidTrainSpeed = 1.0f; // Start train
                 } else {
                     RidTrainSpeed = 0.0f; // Stop train
                 }
       }
      glutPostRedisplay();
}


void RidhandleMouse(int button, int state, int x, int y) {

if (button == GLUT_LEFT_BUTTON)
    {
        Ridcar_speed += 0.85f;
    }


else if (button == GLUT_RIGHT_BUTTON)
    {
        Ridcar_speed -= 0.85f;
    }
glutPostRedisplay();
}

/////////////////////////////Rid End//////////////////


void selectKeyboard (unsigned char key, int x, int y)
{
    if(key=='1')
    {
        Ridwandisplay= true;
        Fahaddisplay= false;
        Sourovdisplay=false;
        PrantoDisplay= false;
    }
    if(key=='2')
    {
        Ridwandisplay= false;
        Fahaddisplay= true;
        Sourovdisplay=false;
        PrantoDisplay= false;

    }
    if(key=='3')
    {
        Ridwandisplay= false;
        Fahaddisplay= false;
        Sourovdisplay=true;
        PrantoDisplay= false;

    }
    if(key=='4')
    {
        Ridwandisplay= false;
        Fahaddisplay= false;
        Sourovdisplay=false;
        PrantoDisplay= true;

    }

    if (Ridwandisplay)
    {
       Ridkeyboard(key,x,y);
    }
    if (Fahaddisplay)
    {

        Fkeyboard(key, x, y);
    }
    if (Sourovdisplay)
    {
        skeyboard(key, x, y);
        specialKeys(key, x, y);
    }

    if (PrantoDisplay)
    {

       prankeyboard(key,x,y);
    }
}
    void mergedmouseClick(int button, int state, int x, int y)
    {
        // Call mouse handling functions based on the active display
          if (Ridwandisplay) {
              RidhandleMouse(button, state, x, y);
          }
          if (Fahaddisplay) {
              mouse(button, state, x, y);
          }
          if (Sourovdisplay) {
              mouseClick(button, state, x, y);

          }
          if (PrantoDisplay) {
              pranhandleMouse(button, state, x, y);
          }
        glutPostRedisplay();
    }


        void Mergedisplay() {
            if(Sourovdisplay)
            {

                sdisplay();

            }
            if(Fahaddisplay)
            {
                Fdisplay();

            }
            if(PrantoDisplay)
            {
                PranDisplay();

            }
            if(Ridwandisplay)
            {
                Riddisplay();

            }

            glFlush();
        }
    int main(int argc, char **argv) {
        //cout<<"Press 1,2,3,4 for calling different Display"<<endl;
        //cout<< "Press 't' for train start and off\n"<<endl;
        //cout << "Press 'd' for Day Mode\n";
        //cout << "Press 'n' for Night Mode\n";


        //cout<<"Click on Black cloud for start/End Rain"<<endl;
       //cout<< "Press UP key for increase Boat Speed \n"<<endl;
       // cout << "Press DOWN key for decrease Boat Speed \n"<<endl;

       // cout<< "Press RIGHT key for increase Train Speed \n"<<endl;
       // cout << "Press LEFT key for decrease Speed \n"<<endl;


        glutInit(&argc, argv);
        glutInitWindowSize(1000, 600);
        glutInitWindowPosition(150, 100);

        glutCreateWindow("City to Village The Train Ride");

        glutDisplayFunc(Mergedisplay);
         glutMouseFunc(mergedmouseClick);
         glutKeyboardFunc(selectKeyboard);
         glutSpecialFunc(specialKeys);
         glutTimerFunc(20,FupdateBird,0);
         glutTimerFunc(20, FupdateVehicles, 0);
         glutTimerFunc(20, FupdateBoat, 0);
         glutTimerFunc(20, FupdateBoatNight, 0);
         glutTimerFunc(20, FupdateCloud, 0);
        glutTimerFunc(20, stimer, 0);
       //
              //PlaySound(TEXT("2.wav"), NULL, SND_SYNC);
        glutMainLoop();

        return 0;
    }
