#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#define PI 3.14159265358979323846
/// Cloud offset for animation
float cloudOffsetX = 0.0f;
float cloudOffsetY = 0.0f;
float carOffsetX = 0.0f;
float planeOffsetX =0.0f;
bool planeMoving = false;
bool isNight = false;
///Cloud part
void drawSmallCircle(float x, float y, float radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360 ; i++) {
        float theta = i * (3.14159 / 180.0);
        float circleX = x + radius * cos(theta);
        float circleY = y + radius * sin(theta);
        glVertex2f(circleX, circleY);
    }
    glEnd();
}

void drawMovingCloud(float x, float y) {
    glColor3ub(255, 255, 255);

    // Drawing multiple circles to form the cloud shape
    drawSmallCircle(x, y, 0.2);  // Smaller circle at the center
    drawSmallCircle(x + 0.75, y , 0.4);  // Right side circle
    drawSmallCircle(x -0.25, y + 0.25, 0.1);  // Left side circle
    drawSmallCircle(x + 1.0, y, 0.5);  // Upper right side circle
    drawSmallCircle(x , y, 0.5);  // Upper left side circle
    drawSmallCircle(x, y - 0.25, 0.5);  // Bottom center circlele
}

void drawMovingClouds() {

    drawMovingCloud(cloudOffsetX - 5.0f, cloudOffsetY + 1); // Cloud 1
    drawMovingCloud(cloudOffsetX + 3.0f, cloudOffsetY + 1.5); // Cloud 2
    drawMovingCloud(cloudOffsetX + 8.0f, cloudOffsetY + 1); // Cloud 3
}

void updateCloudPosition() {
    cloudOffsetX += 0.0001f;
    if (cloudOffsetX > 15.0f) {
        cloudOffsetX = -10.0f;
    }
}

///car update function

void updateCarPosition() {
    carOffsetX += 0.001f;
    if (carOffsetX > 10.0f) {
    }
}

///plane update function
void updatePlanePosition() {
    if (planeMoving) {
        planeOffsetX -= 0.01f;
        if (planeOffsetX < -20.0f) {
            planeOffsetX = 10.0f;
        }
    }
}

/// Circle function
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.1416 /90.0f; // Convert degrees to radians
        float x = r * cos(angle);       // Calculate x-coordinate
        float y = r * sin(angle);       // Calculate y-coordinate
        glVertex2f(cx + x, cy + y);     // Add vertex
    }
    glEnd();
}

/// Function to draw a sun and the ray
void drawSun(float cx, float cy, float r) {
    glColor3f(1.0, 1.0, 0.0); /// Yellow color

    ///sun's body (circle)
    drawCircle(cx, cy, r);

    /// Draw the sun's rays
    glBegin(GL_LINES);
    for (int i = 0; i < 12; i++) { /// 12 rays
        float angle = 2.0f * M_PI * i / 12;
        float x1 = cx + cos(angle) * r;       /// Start of ray (edge of sun)
        float y1 = cy + sin(angle) * r;
        float x2 = cx + cos(angle) * (r+0.3); /// End of ray (outside sun)
        float y2 = cy + sin(angle) * (r+0.3);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();
}
///moon
void drawMoon(float cx, float cy, float r) {
    glColor3ub(235, 235, 224);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.1416 / 180.0f;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}
void drawcar(float cx, float cy, float r) {
    glColor3f(0,0,0); /// Yellow color

    ///sun's body (circle)
    drawCircle(cx, cy, r);

    glEnd();
}


void initGL()
{
   if (isNight) {
        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    } else {
        glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    }
}

void car(){

    glBegin(GL_POLYGON);
    glColor3ub(255, 230, 204);
    glVertex2f(carOffsetX-3.5,7.5);
    glVertex2f(carOffsetX-3.25,7.5);
    glVertex2f(carOffsetX-3.25,7.75);
    glVertex2f(carOffsetX-3.5,7.75);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(242, 242, 242);
    glVertex2f(carOffsetX-3.25,7.5);
    glVertex2f(carOffsetX-3,7.25);
    glVertex2f(carOffsetX-1.75,7.25);
    glVertex2f(carOffsetX-1.5,7.5);
    glVertex2f(carOffsetX-1.5,7.75);
    glVertex2f(carOffsetX-3.25,7.75);
    glEnd();

     glBegin(GL_POLYGON);
    glColor3ub(255, 230, 204);
    glVertex2f(carOffsetX-1.5,7.5);
    glVertex2f(carOffsetX-1.25,7.5);
    glVertex2f(carOffsetX-1.25,7.75);
    glVertex2f(carOffsetX-1.5,7.75);
    glEnd();

    drawcar(carOffsetX-1.75,7.75,0.2);
    drawcar(carOffsetX-3,7.75,0.2);

    ///plan

     glBegin(GL_POLYGON);
    glColor3ub(255, 230, 204);
    glVertex2f(planeOffsetX+8.25,0.25);
    glVertex2f(planeOffsetX+9.5,0.25);
    glVertex2f(planeOffsetX+9.25,0.5);
    glVertex2f(planeOffsetX+8,0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 230, 204);
    glVertex2f(planeOffsetX+9.25,0.25);
    glVertex2f(planeOffsetX+9.5,0);
    glVertex2f(planeOffsetX+9.5,0.25);
    glEnd();

    glFlush();

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     if (isNight) {
        glColor3ub(0, 0, 50);  // Dark blue color for night
    } else {
        glColor3ub(128, 229, 255);  // Light blue color for day
    }

    glBegin(GL_POLYGON);

    glVertex2f(-5,0);
    glVertex2f(10,0);
    glVertex2f(10,10);
    glVertex2f(-5,10);
    glEnd();

    ///cloud
    drawMovingClouds();

    ///sun and moon
        if (isNight) {
        drawMoon(-3.75, 1, 0.35f);  // Draw the moon
        }
        else{drawSun(-3.75,1, 0.35);}
    ///Building
    glBegin(GL_POLYGON); //1
    glColor3ub(230, 230, 230);
    glVertex2f(-5,2);
    glVertex2f(-3.75,2);
    glVertex2f(-3.75,3.25);
    glVertex2f(-5,3.25);
    glEnd();

    glBegin(GL_POLYGON); //2
    glColor3ub(230, 230, 230);
    glVertex2f(-5,3.25);
    glVertex2f(-3.75,3.25);
    glVertex2f(-3.75,4.5);
    glVertex2f(-5,4.5);
    glEnd();

    glBegin(GL_POLYGON); //3
    glColor3ub(230, 230, 230);
    glVertex2f(-5,4.5);
    glVertex2f(-3.75,4.5);
    glVertex2f(-3.75,5.75);
    glVertex2f(-5,5.75);
    glEnd();

    glBegin(GL_POLYGON); //4
    glColor3ub(230, 230, 230);
    glVertex2f(-5,5.75);
    glVertex2f(-3.75,5.75);
    glVertex2f(-3.75,7);
    glVertex2f(-5,7);
    glEnd();


    glBegin(GL_POLYGON); //5
    glColor3ub(230, 230, 230);
    glVertex2f(8.75,2);
    glVertex2f(10,2);
    glVertex2f(10,3.25);
    glVertex2f(8.75,3.25);
    glEnd();

    glBegin(GL_POLYGON); //6
    glColor3ub(230, 230, 230);
    glVertex2f(8.75,3.25);
    glVertex2f(10,3.25);
    glVertex2f(10,4.5);
    glVertex2f(8.75,4.5);
    glEnd();

    glBegin(GL_POLYGON); //7
    glColor3ub(230, 230, 230);
    glVertex2f(8.75,3.25);
    glVertex2f(10,3.25);
    glVertex2f(10,5.75);
    glVertex2f(8.75,5.75);
    glEnd();

    glBegin(GL_POLYGON); //8
    glColor3ub(230, 230, 230);
    glVertex2f(8.75,5.75);
    glVertex2f(10,5.75);
    glVertex2f(10,7);
    glVertex2f(8.75,7);
    glEnd();

    glBegin(GL_POLYGON); //9
    glColor3ub(230, 230, 230);
    glVertex2f(-3.75,2);
    glVertex2f(0.75,2);
    glVertex2f(0.75,3.75);
    glVertex2f(-3.75,3.75);
    glEnd();

    glBegin(GL_POLYGON); //10
    glColor3ub(166, 166, 166);
    glVertex2f(0.75,2);
    glVertex2f(1,2);
    glVertex2f(1,3.25);
    glVertex2f(0.75,3.25);
    glEnd();

    glBegin(GL_POLYGON); //12
    glColor3ub(166, 166, 166);
    glVertex2f(-3.75,3.25);
    glVertex2f(-3,3.75);
    glVertex2f(-3,5);
    glVertex2f(-3.75,4.5);
    glEnd();

     glBegin(GL_POLYGON); //13
    glColor3ub(166, 166, 166);
    glVertex2f(-3.75,3.25);
    glVertex2f(8.75,3.25);
    glVertex2f(7.75,3.75);
    glVertex2f(-3,3.75);
    glEnd();

    glBegin(GL_POLYGON); //14
    glColor3ub(166, 166, 166);
    glVertex2f(-3.75,4.5);
    glVertex2f(-3,5);
    glVertex2f(-3,6.25);
    glVertex2f(-3.75,5.75);
    glEnd();

     glBegin(GL_POLYGON); //15
    glColor3ub(166, 166, 166);
    glVertex2f(-3.75,5.75);
    glVertex2f(-3,6.25);
    glVertex2f(-3,7);
    glVertex2f(-3.75,7);
    glEnd();

    glBegin(GL_POLYGON); //16
    glColor3ub(242, 242, 242);
    glVertex2f(-3,5.5);
    glVertex2f(1,5.5);
    glVertex2f(1,6);
    glVertex2f(-3,6);
    glEnd();

    glBegin(GL_POLYGON); //17
    glColor3ub(166, 166, 166);
    glVertex2f(-3,6);
    glVertex2f(1,6);
    glVertex2f(1,6.75);
    glVertex2f(-3,6.75);
    glEnd();

    glBegin(GL_POLYGON); //18
    glColor3ub(242, 242, 242);
    glVertex2f(-3,6.75);
    glVertex2f(0.75,6.75);
    glVertex2f(0.75,7);
    glVertex2f(-3,7);
    glEnd();
    glBegin(GL_POLYGON); //18
    glColor3ub(166, 166, 166);
    glVertex2f(0.75,6.75);
    glVertex2f(4.75,6.75);
    glVertex2f(4.75,7);
    glVertex2f(0.75,7);
    glEnd();

    glBegin(GL_POLYGON); //18
    glColor3ub(166, 166, 166);
    glVertex2f(8.75,3.25);
    glVertex2f(8,3.75);
    glVertex2f(8,4.75);
    glVertex2f(8.75,4.5);
    glEnd();
    glBegin(GL_POLYGON); //18
    glColor3ub(166, 166, 166);
    glVertex2f(8,4.75);
    glVertex2f(8.75,4.5);
    glVertex2f(8.75,5.75);
    glVertex2f(8,6);
    glEnd();
    glBegin(GL_POLYGON); //18
    glColor3ub(166, 166, 166);
    glVertex2f(8,6);
    glVertex2f(8.75,5.75);
    glVertex2f(8.75,7);
    glVertex2f(8,7);
    glEnd();

    glBegin(GL_POLYGON); //18
    glColor3ub(242, 242, 242);
    glVertex2f(4.75,6.75);
    glVertex2f(8,6.75);
    glVertex2f(8,7);
    glVertex2f(4.75,7);
    glEnd();


    glBegin(GL_POLYGON); //18
    glColor3ub(166, 166, 166);
    glVertex2f(4.5,6);
    glVertex2f(8,6);
    glVertex2f(8,6.75);
    glVertex2f(4.5,6.75);
    glEnd();

    glBegin(GL_POLYGON); //18
    glColor3ub(242, 242, 242);
    glVertex2f(4.5,5.5);
    glVertex2f(8,5.5);
    glVertex2f(8,6);
    glVertex2f(4.5,6);
    glEnd();
    glBegin(GL_POLYGON); //18
    glColor3ub(166, 166, 166);
    glVertex2f(4.5,3.25);
    glVertex2f(8.75,3.25);
    glVertex2f(8,3.75);
    glVertex2f(4.5,3.75);
    glEnd();

    glBegin(GL_POLYGON); //18
    glColor3ub(166, 166, 166);
    glVertex2f(4.5,2);
    glVertex2f(4.75,2);
    glVertex2f(4.75,3.25);
    glVertex2f(4.5,3.25);
    glEnd();
    glBegin(GL_POLYGON); //18
    glColor3ub(242, 242, 242);
    glVertex2f(4.75,2);
    glVertex2f(8.75,2);
    glVertex2f(8.75,3.25);
    glVertex2f(4.75,3.25);
    glEnd();

    ///lines of the building
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-3.75,2);
    glVertex2f(-3.75,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-5,3.25);
    glVertex2f(0.75,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-2.5,2);
    glVertex2f(-2.5,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-1.25,2);
    glVertex2f(-1.25,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(0,2);
    glVertex2f(0,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(0.75,2);
    glVertex2f(0.75,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-3.75,3.25);
    glVertex2f(-3.75,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-5,4.5);
    glVertex2f(-3.75,4.5);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-3.75,3.25);
    glVertex2f(-3,3.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-3,3.25);
    glVertex2f(-2.25,3.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-2.25,3.25);
    glVertex2f(-1.5,3.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-1.5,3.25);
    glVertex2f(-0.75,3.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.75,3.25);
    glVertex2f(0,3.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(0,3.25);
    glVertex2f(0.75,3.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-3,3.75);
    glVertex2f(1,3.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-3,3.75);
    glVertex2f(-3,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-5,5.75);
    glVertex2f(-3.75,5.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-3.75,5.75);
    glVertex2f(-3,6.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-3.75,4.5);
    glVertex2f(-3,5);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-5,2);
    glVertex2f(1,2);
    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-2.75,5.25);
    glVertex2f(-2.75,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-2.5,5.25);
    glVertex2f(-2.5,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-2.25,5.25);
    glVertex2f(-2.25,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-2,5.25);
    glVertex2f(-2,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-1.75,5.25);
    glVertex2f(-1.75,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-1.5,5.25);
    glVertex2f(-1.5,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-1.25,5.25);
    glVertex2f(-1.25,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-1,5.25);
    glVertex2f(-1,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.75,5.25);
    glVertex2f(-0.75,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.5,5.25);
    glVertex2f(-0.5,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.25,5.25);
    glVertex2f(-0.25,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(0,5.25);
    glVertex2f(0,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(0.25,5.25);
    glVertex2f(0.25,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(0.5,5.25);
    glVertex2f(0.5,7);
    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(0.75,5.25);
    glVertex2f(0.75,7);
    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-2.75,6.25);
    glVertex2f(0.75,6.25);
    glEnd();

    ///right side line
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(4,2);
    glVertex2f(10,2);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(10,3.25);
    glVertex2f(4.75,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(4.75,3.25);
    glVertex2f(4.75,2);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(5.75,2);
    glVertex2f(5.75,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(7,3.25);
    glVertex2f(7,2);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(8,2);
    glVertex2f(8,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(8.75,2);
    glVertex2f(8.75,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(8.75,3.25);
    glVertex2f(8,3.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(8,3.75);
    glVertex2f(4.5,3.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(4.5,3.75);
    glVertex2f(5,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(5.75,3.25);
    glVertex2f(5,3.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(5.75,3.75);
    glVertex2f(6.5,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(7.25,3.25);
    glVertex2f(6.5,3.75);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(7.25,3.75);
    glVertex2f(8,3.25);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(8,3.75);
    glVertex2f(8,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(8,4.75);
    glVertex2f(8.75,4.5);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(8,6);
    glVertex2f(8.75,5.75);
    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(7.75,5.25);
    glVertex2f(7.75,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(7.5,5.25);
    glVertex2f(7.5,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(7.25,5.25);
    glVertex2f(7.25,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(7,5.25);
    glVertex2f(7,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(6.75,5.25);
    glVertex2f(6.75,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(6.5,5.25);
    glVertex2f(6.5,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(6.25,5.25);
    glVertex2f(6.25,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(6,5.25);
    glVertex2f(6,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(5.75,5.25);
    glVertex2f(5.75,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(5.5,5.25);
    glVertex2f(5.5,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(5.25,5.25);
    glVertex2f(5.25,7);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(5,5.25);
    glVertex2f(5,7);
    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(4.75,5.25);
    glVertex2f(4.75,7);
    glEnd();

    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(4.75,6.25);
    glVertex2f(7.75,6.25);
    glEnd();

    /// left piller

    glBegin(GL_POLYGON); //19
    glColor3ub(242, 242, 242);
    glVertex2f(1,0.75);
    glVertex2f(1.5,0.75);
    glVertex2f(1.5,6.75);
    glVertex2f(1,6.75);
    glEnd();

    ///lower piller

    glBegin(GL_POLYGON); //20
    glColor3ub(166, 166, 166);
    glVertex2f(1.5,1);
    glVertex2f(1.75,1);
    glVertex2f(1.75,6.75);
    glVertex2f(1.5,6.75);
    glEnd();
    ///piller
    glBegin(GL_POLYGON); //21
    glColor3ub(242, 242, 242);
    glVertex2f(1.75,0.75);
    glVertex2f(2.25,0.75);
    glVertex2f(2.25,6.75);
    glVertex2f(1.75,6.75);
    glEnd();
    ///lower piller
    glBegin(GL_POLYGON); //22
    glColor3ub(166, 166, 166);
    glVertex2f(2.25,1);
    glVertex2f(2.5,1);
    glVertex2f(2.5,6.75);
    glVertex2f(2.25,6.75);
    glEnd();
    ///piller
    glBegin(GL_POLYGON); //24
    glColor3ub(242, 242, 242);
    glVertex2f(2.5,0.75);
    glVertex2f(3,0.75);
    glVertex2f(3,6.75);
    glVertex2f(2.5,6.75);
    glEnd();
    ///lower piller
    glBegin(GL_POLYGON); //25
    glColor3ub(166, 166, 166);
    glVertex2f(3,1);
    glVertex2f(3.25,1);
    glVertex2f(3.25,6.75);
    glVertex2f(3,6.75);
    glEnd();
    ///piller
    glBegin(GL_POLYGON); //26
    glColor3ub(242, 242, 242);
    glVertex2f(3.25,0.75);
    glVertex2f(3.75,0.75);
    glVertex2f(3.75,6.75);
    glVertex2f(3.25,6.75);
    glEnd();

    ///lower piller
    glBegin(GL_POLYGON); //27
    glColor3ub(166, 166, 166);
    glVertex2f(3.75,1);
    glVertex2f(4,1);
    glVertex2f(4,6.75);
    glVertex2f(3.75,6.75);
    glEnd();

    ///piller
    glBegin(GL_POLYGON); //28
    glColor3ub(242, 242, 242);
    glVertex2f(4,0.75);
    glVertex2f(4.5,0.75);
    glVertex2f(4.5,6.75);
    glVertex2f(4,6.75);
    glEnd();

    ///road
    glBegin(GL_POLYGON); //28
    glColor3ub(51, 51, 0);
    glVertex2f(-5,7);
    glVertex2f(10,7);
    glVertex2f(10,10);
    glVertex2f(-5,10);
    glEnd();

    ///road lines
    glBegin(GL_POLYGON); //28
    glColor3ub(255, 255, 230);
    glVertex2f(-3.75,8.25);
    glVertex2f(-1.5,8.25);
    glVertex2f(-1.5,8.5);
    glVertex2f(-3.75,8.5);
    glEnd();

    glBegin(GL_POLYGON); //28
    glColor3ub(255, 255, 230);
    glVertex2f(1.25,8.25);
    glVertex2f(3.75,8.25);
    glVertex2f(3.75,8.5);
    glVertex2f(1.25,8.5);
    glEnd();

    glBegin(GL_POLYGON); //28
    glColor3ub(255, 255, 230);
    glVertex2f(6.75,8.25);
    glVertex2f(8.75,8.25);
    glVertex2f(8.75,8.5);
    glVertex2f(6.75,8.5);
    glEnd();

    ///car
    car();


updateCloudPosition();
updateCarPosition();
updatePlanePosition();
    glFlush();
glutPostRedisplay();
}

void handleKeyPress(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        planeMoving = true; ///start the plan
    }
    if (key == 's' || key == 'S') {
        planeMoving = false;///stop the plan
    }
    if (key == 'm' || key == 'M') {
        isNight = true; ///for night
    }
    if (key == 'u' || key == 'U') {
        isNight = false; ///again come back to the sun
    }
}
/// Main Function
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(1080,1080);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("late");
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyPress);
    initGL();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-5,10, 10, 0);
    glutMainLoop();

    return 0;
}
