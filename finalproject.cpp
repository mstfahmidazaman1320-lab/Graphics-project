#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <ctime>

const int WIN_W = 1200;
const int WIN_H = 686;


#define NUM_BIRDS 5


float boatPosX = 0.0f;
float cloudPosX1 = 0.0f;

float boatStartX = 300.0f;
float boatWidth  = 200.0f;

float cloudStartX = 225.0f;
float cloudWidth  = 150.0f;


float cloudPosX2 = -400.0f;
float cloudPosX3 = -800.0f;


float headAngle = 0.0f;   // current rotation angle of head
float headSpeed = 0.5f;   // speed of head rotation


float fishY = 0.0f;    // fish vertical offset


float fishAnim = 20;      // distance from beak
float fishSpeed = 0.15;   // approach speed
float fishBounce = 0.0;   // vertical bounce
float fishBounceSpeed = 0.1; // bounce speed
float fishBounceDir = 1;  // up/down direction

float cowMove = 0.0f;
int cowDir = 1;

float cowHeadAngle = 0.0f;
int cowHeadDir = 1;


void drawCircle(float cx, float cy, float r, int num_segments) {

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(cx, cy);

    for (int i = 0; i <= num_segments; i++) {

        float theta = 2.0f * 3.1415926f * i / num_segments;

        float x = r * cosf(theta);

        float y = r * sinf(theta);

        glVertex2f(cx + x, cy + y);

    }

    glEnd();

}

struct Bird {
    float x, y;
    float speed;
    float wave;
    float waveSpeed;
};
 Bird birds[NUM_BIRDS];

void drawBirds()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3);

    for(int i = 0; i < NUM_BIRDS; i++)
    {
        glBegin(GL_LINES);
       // left wing
        glVertex2f(birds[i].x - 16, birds[i].y);
        glVertex2f(birds[i].x,      birds[i].y + 12);

        // right wing
        glVertex2f(birds[i].x,      birds[i].y + 12);
        glVertex2f(birds[i].x + 16, birds[i].y);

        glEnd();
    }
}

void drawEllipse(float cx, float cy, float rx, float ry)
{
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i++)
    {
        float rad = i * 3.1416f / 180;
        glVertex2f(cx + cos(rad)*rx, cy + sin(rad)*ry);
    }
    glEnd();
}


void drawCow(float x, float y)
{
    //  BODY (CURVED BACK)
glColor3f(0.97f, 0.96f, 0.90f);

// Upper back (slight curve)

drawEllipse(x + 150, y + 110, 108, 20);

// Neck hump (small & local)
drawEllipse(x + 185, y + 125, 35, 15);

// Middle body

drawEllipse(x + 150, y + 88, 120, 32);


// Back slope towards hip

drawEllipse(x + 125, y + 90, 82, 38);


// Hip (slimmer & lower)
drawEllipse(x + 83, y + 78, 48, 35);

// Belly (deep curve)
drawEllipse(x + 145, y + 60, 95, 40);
drawEllipse(x + 145, y + 50, 65, 28);

// Front chest
drawEllipse(x + 235, y + 90, 45, 35);



    // BLACK PATCHES
    glColor3f(0.1f, 0.1f, 0.1f);
    drawEllipse(x + 130, y + 105, 28, 18);
    drawEllipse(x + 175, y + 80, 25, 18);
    drawEllipse(x + 50,  y + 100, 20, 15);

    // LEGS
    glColor3f(0.97f, 0.96f, 0.90f);

    // Front legs
    glBegin(GL_POLYGON);
        glVertex2f(x+180, y+40);
        glVertex2f(x+195, y+40);
        glVertex2f(x+195, y-15);
        glVertex2f(x+180, y-15);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(x+155, y+40);
        glVertex2f(x+170, y+40);
        glVertex2f(x+170, y-15);
        glVertex2f(x+155, y-15);
    glEnd();

    // Back legs
    glBegin(GL_POLYGON);
        glVertex2f(x+100, y+40);
        glVertex2f(x+115, y+40);
        glVertex2f(x+115, y-15);
        glVertex2f(x+100, y-15);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(x+75, y+40);
        glVertex2f(x+90, y+40);
        glVertex2f(x+90, y-15);
        glVertex2f(x+75, y-15);
    glEnd();

    // Hooves (black)
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(x+180, y-15); glVertex2f(x+195, y-15);
        glVertex2f(x+195, y-25); glVertex2f(x+180, y-25);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(x+155, y-15); glVertex2f(x+170, y-15);
        glVertex2f(x+170, y-25); glVertex2f(x+155, y-25);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(x+100, y-15); glVertex2f(x+115, y-15);
        glVertex2f(x+115, y-25); glVertex2f(x+100, y-25);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(x+75, y-15); glVertex2f(x+90, y-15);
        glVertex2f(x+90, y-25); glVertex2f(x+75, y-25);
    glEnd();

    // UDDER
    glColor3f(1.0f, 0.7f, 0.7f);
    drawEllipse(x + 120, y + 18, 8, 6);

    //  NECK (angled, slim)
    glColor3f(0.97f, 0.96f, 0.90f);
    glBegin(GL_POLYGON);
        glVertex2f(x+230, y+105);   // upper back attach
        glVertex2f(x+260, y+90);    // upper head attach
        glVertex2f(x+250, y+65);    // lower head attach
        glVertex2f(x+225, y+80);    // lower back attach
    glEnd();

    // HEAD
    glBegin(GL_POLYGON);
        glVertex2f(x+265, y+90);   // top back
        glVertex2f(x+305, y+80);   // forehead
        glVertex2f(x+315, y+50);   // nose down
        glVertex2f(x+285, y+45);   // jaw
        glVertex2f(x+250, y+65);   // neck join
    glEnd();

    // Pink mouth
    glColor3f(1.0f, 0.7f, 0.7f);
    drawEllipse(x+305, y+48, 7, 5);

    // Eye
    glColor3f(0,0,0);
    drawEllipse(x+280, y+75, 3, 3);

    //  EARS
    glColor3f(0.97f, 0.85f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x+260, y+95);
        glVertex2f(x+235, y+115);
        glVertex2f(x+270, y+110);
    glEnd();



//  HORNS (FIXED TO HEAD)
glColor3f(0.1f, 0.1f, 0.1f);

// Left horn
glBegin(GL_TRIANGLES);
    glVertex2f(x+265, y+92);   // head top (attach point)
    glVertex2f(x+255, y+110);  // horn tip
    glVertex2f(x+275, y+96);   // horn base
glEnd();

// Right horn
glBegin(GL_TRIANGLES);
    glVertex2f(x+285, y+90);   // head top (attach point)
    glVertex2f(x+300, y+108);  // horn tip
    glVertex2f(x+275, y+96);   // horn base
glEnd();



// TAIL (MORE DOWN + MORE BACK)
glColor3f(0,0,0);
glLineWidth(4);

glBegin(GL_LINE_STRIP);
    glVertex2f(x+32, y+100);
    glVertex2f(x+30, y+70);
    glVertex2f(x+33, y+40);
    glVertex2f(x+52, y+20);
glEnd();

//  TAIL HAIR
glColor3f(0,0,0);
glLineWidth(3);

glBegin(GL_LINES);
    glVertex2f(x+52, y+20); glVertex2f(x+38, y-5);
    glVertex2f(x+52, y+20); glVertex2f(x+57, y-5);
    glVertex2f(x+52, y+20); glVertex2f(x+50, y-8);
glEnd();

}



void drawKhuti(float x, float y)
{
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 5, y);
    glVertex2f(x + 5, y);
    glVertex2f(x + 5, y + 60);
    glVertex2f(x - 5, y + 60);
    glEnd();
}


void drawBasket(float x, float y)
{
    //  BASKET BODY
    glColor3f(0.55f, 0.28f, 0.12f);   // basket brown

    glBegin(GL_POLYGON);
        glVertex2f(x + 5,  y);          // bottom left
        glVertex2f(x + 75, y);          // bottom right
        glVertex2f(x + 65, y + 45);     // top right (slanted)
        glVertex2f(x + 15, y + 45);     // top left
    glEnd();


    // BASKET RIM
    glColor3f(0.45f, 0.22f, 0.08f);
    glBegin(GL_POLYGON);
        glVertex2f(x + 12, y + 42);
        glVertex2f(x + 68, y + 42);
        glVertex2f(x + 66, y + 48);
        glVertex2f(x + 14, y + 48);
    glEnd();


    // GRASS (GOLDEN + GREEN)
    glLineWidth(2.0f);

    for(int i = 0; i < 12; i++)
    {
        float gx = x + 18 + i * 4;

        // green grass
        glColor3f(0.2f, 0.7f, 0.2f);
        glBegin(GL_LINES);
            glVertex2f(gx, y + 45);
            glVertex2f(gx - 3, y + 60);
        glEnd();

        // golden dry grass
        glColor3f(0.8f, 0.7f, 0.2f);
        glBegin(GL_LINES);
            glVertex2f(gx + 2, y + 45);
            glVertex2f(gx + 4, y + 58);
        glEnd();
    }


    // LITTLE STRAW TOP
    glColor3f(0.9f, 0.8f, 0.3f);
    drawEllipse(x + 40, y + 55, 25, 6);
}


void drawFish(float x, float y)
{
    glColor3f(0, 1, 0); // green fish
    glBegin(GL_POLYGON);
    glVertex2f(x, y);       // nose
    glVertex2f(x - 15, y + 5);
    glVertex2f(x - 20, y);
    glVertex2f(x - 15, y - 5);
    glEnd();

    // fish tail
    glColor3f(0.1f, 0.5f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 20, y);
    glVertex2f(x - 25, y + 5);
    glVertex2f(x - 25, y - 5);
    glEnd();
}


void drawBokPakhi(float x, float y)
{

    // BODY
    glColor3f(0.9f, 0.9f, 0.9f);
    drawCircle(x, y + 60, 18, 50);

    // NECK
    glLineWidth(6);
    glColor3f(0.85f, 0.85f, 0.85f);
    glBegin(GL_LINES);
    glVertex2f(x, y + 60);
    glVertex2f(x, y + 110);
    glEnd();

    // LEGS
    glLineWidth(4);
    glColor3f(0.8f, 0.6f, 0.2f);
    // LEG 1 (in water)
    glBegin(GL_LINES);
    glVertex2f(x - 5, y + 45);
    glVertex2f(x - 5, y + 0);
    glEnd();
    // LEG 2 (up)
    glBegin(GL_LINES);
    glVertex2f(x + 5, y + 45);
    glVertex2f(x + 5, y + 20);
    glEnd();


    // HEAD + EYE + BEAK + FISH

    float headTopY = y + 110;  // neck top
    float fishSpeedFactor = 0.2f; // slow movement

    // HEAD
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, headTopY, 12, 40);

    // EYE
    glColor3f(0, 0, 0);
    drawCircle(x + 5, headTopY + 5, 3, 20);

    // BEAK
    glColor3f(1.0f, 0.7f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 12, headTopY);      // tip
    glVertex2f(x + 40, headTopY - 3);  // bottom
    glVertex2f(x + 12, headTopY - 5);  // bottom
    glEnd();

    // FISH (attached inside beak)
    glColor3f(0.6f, 0.6f, 0.9f); // fish color
    drawCircle(x + 26, headTopY - 3 + fishY * fishSpeedFactor, 5, 20);
}

void drawFlyingBird(float x, float y) {
    glColor3f(0.0f, 0.0f, 0.0f); // black bird
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x + 10, y + 5);
    glVertex2f(x, y);
    glVertex2f(x + 10, y - 5);
    glEnd();
}


void seen_one(){
    // SKY

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.8f, 1.0f);  // Light blue at top
    glVertex2f(0, 440);
    glVertex2f(1200, 440);
    glColor3f(0.2f, 0.4f, 0.8f);  // Dark blue at bottom
    glVertex2f(1200, 750);
    glVertex2f(0, 750);
    glEnd();


// SUN
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(1050, 650, 45, 80);

    drawBirds();

    // CLOUDS (Moving)
glColor3f(1.0f, 1.0f, 1.0f);

// Cloud 1
glPushMatrix();
glTranslatef(cloudPosX1, 0.0f, 0.0f);
drawCircle(225, 625, 42, 70);
drawCircle(270, 625, 56, 70);
drawCircle(330, 625, 42, 70);
glPopMatrix();

// Cloud 2
glPushMatrix();
glTranslatef(cloudPosX2, 0.0f, 0.0f);
drawCircle(750, 700, 35, 70);
drawCircle(790, 700, 45, 70);
drawCircle(840, 700, 35, 70);
glPopMatrix();

// Cloud 3
glPushMatrix();
glTranslatef(cloudPosX3, 0.0f, 0.0f);
drawCircle(900, 650, 35, 70);
drawCircle(945, 650, 50, 70);
drawCircle(1005, 650, 35, 70);
glPopMatrix();


    // FIELD

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.8f, 0.5f);
    glVertex2f(0, 187);//187
    glVertex2f(1200, 187);
    glColor3f(0.3f, 0.6f, 0.3f);  // Medium green
    glVertex2f(1200, 440);//375
    glVertex2f(0, 440);
    glEnd();


    // BUSHES (behind van)
    glColor3f(0.0f, 0.5f, 0.0f);  // dark green
    drawCircle(920, 460, 35, 50);
    drawCircle(960, 470, 60, 50);
    drawCircle(1000, 480, 55, 50);
    drawCircle(1040, 470, 60, 50);
    drawCircle(1080, 465, 55, 50);
    drawCircle(1120, 470, 60, 50);
    drawCircle(1160, 480, 55, 50);

    glColor3f(0.2f, 0.4f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(1200,400);
    glVertex2f(1200,440);
    glVertex2f(900,440);
    glVertex2f(900,400);
    glEnd();

    // FENCE (right side)

    glColor3f(0.6f, 0.3f, 0.0f); // brown color
    glLineWidth(6.0f);           // thick fence rails
    glBegin(GL_LINES);
    // Horizontal rails
    glVertex2f(900, 400);
    glVertex2f(1200, 400);
    glVertex2f(900, 440);
    glVertex2f(1200, 440);
    glVertex2f(900, 460);
    glVertex2f(1200, 460);
    // Vertical posts
    for (int x = 900; x <= 1200; x += 50)
    {
        glVertex2f(x, 400);
        glVertex2f(x, 460);
    }
    glEnd();



    // paddy inside the van

    glColor3f(0.93f, 0.79f, 0.25f); // golden yellow paddy color
    glBegin(GL_POLYGON);
    glVertex2f(885, 420); // left top near van
    glVertex2f(910, 450);
    glVertex2f(940, 460);
    glVertex2f(970, 455);
    glVertex2f(1000, 470);
    glVertex2f(1040, 460);
    glVertex2f(1080, 465);
    glVertex2f(1110, 450);
    glVertex2f(1145, 420); // right end of van
    glVertex2f(880, 420);  // close back to start
    glEnd();


//hay square
    glColor3f(0.8f, 0.6f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(1145, 350); // left top near cart
    glVertex2f(1145, 420);
    glVertex2f(885, 420);
    glVertex2f(885,350);

    glEnd();


    // BULLOCK CART (wooden style, slim wheel, line body)


    // Cart horizontal bars (long wide lines)
    glLineWidth(12.0f);
    glColor3f(0.36f, 0.25f, 0.20f); // dark brown
    glBegin(GL_LINES);
    glVertex2f(880, 420);//
    glVertex2f(1180, 420); // top bar
    glVertex2f(880, 385);
    glVertex2f(1150, 385); // middle bar
    glVertex2f(880, 350);
    glVertex2f(1150, 350); // bottom bar
    glEnd();

    // Vertical posts of the cart
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    for (int x = 900; x <= 1120; x += 50)
    {
        glVertex2f(x, 350);
        glVertex2f(x, 420);
    }
    glEnd();

    // Slim wooden wheel (outer rim only)
    glLineWidth(10.0f);
    glColor3f(0.36f, 0.25f, 0.20f); // dark brown
    glBegin(GL_LINE_LOOP);
    for (int angle = 0; angle < 360; angle++)
    {
        float x = 950 + 35 * cos(angle * M_PI / 180.0);
        float y = 340 + 35 * sin(angle * M_PI / 180.0);
        glVertex2f(x, y);
    }
    glEnd();

    // Wheel spokes
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    for (int angle = 0; angle < 360; angle += 30)
    {
        float x = 950 + 35 * cos(angle * M_PI / 180.0);
        float y = 340 + 35 * sin(angle * M_PI / 180.0);
        glVertex2f(950, 340);
        glVertex2f(x, y);
    }
    glEnd();

    // Cart handles (front sticks to tie bulls)
    glLineWidth(10.0f);
    glBegin(GL_LINES);
    glVertex2f(1110, 305);
    glVertex2f(1120, 350);

    glVertex2f(1140, 305);
    glVertex2f(1120, 350);
    glEnd();



    // RIVER gradient: deep blue (bottom) to lighter blue (top)
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.3f, 0.7f);  // Darker blue at bottom
    glVertex2f(0, 0);
    glVertex2f(1200, 0);
    glColor3f(0.3f, 0.6f, 1.0f);  // Lighter blue at top
    glVertex2f(1200, 300);
    glVertex2f(0, 300);
    glEnd();

    // BOK PAKHI (standing beside river)
    drawBokPakhi(200, 100);




    // TREE 1
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(30,425);
    glVertex2f(30,562.5);
    glVertex2f(60,562.5);
    glVertex2f(60,425);
    glEnd();
    //glColor3f(0.0f, 0.6f, 0.0f);
    glColor3f(0.0f, 0.27f, 0.13f);
    drawCircle(30,587.5, 56, 70);
    drawCircle(120,587.5, 50, 70);
    drawCircle(75,650, 70, 70);
    drawCircle(15,675,60, 70);



// HOUSE 2


// top front part
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.1f, 0.1f);
    glVertex2f(660,515);
    glColor3f(0.9f, 0.3f, 0.3f);
    glVertex2f(600,575);
    glVertex2f(375,575);
    glVertex2f(375,515);
    glEnd();

// upper house
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.5f, 0.5f);
    glVertex2f(495,575);
    glColor3f(1.0f, 0.7f, 0.6f);
    glVertex2f(495,625);
    glVertex2f(330,625);
    glVertex2f(375,575);
    glEnd();

    // Side lines for upper house
    glColor3f(0.1f, 0.1f, 0.1f);  // Dark color
    glLineWidth(5.0f);             // Slightly wide

    glBegin(GL_LINES);
// Vertical line (right side of upper house)
    glVertex2f(495+80, 575);
    glVertex2f(495+80, 610);

// Horizontal line (top side of upper house)
    glVertex2f(495+80, 610);
    glVertex2f(330+165, 610);

// vertical line (left side of upper house)
    glVertex2f(330+165, 575);
    glVertex2f(330+165, 610);

    glVertex2f(330+175, 575);
    glVertex2f(330+175, 610);

    glVertex2f(330+185, 575);
    glVertex2f(330+185, 610);

    glVertex2f(330+195, 575);
    glVertex2f(330+195, 610);


    glVertex2f(330+205, 575);
    glVertex2f(330+205, 610);

    glVertex2f(330+215, 575);
    glVertex2f(330+215, 610);

    glVertex2f(330+225, 575);
    glVertex2f(330+225, 610);

    glVertex2f(330+235, 575);
    glVertex2f(330+235, 610);

    glVertex2f(330+245, 575);
    glVertex2f(330+245, 610);


    glEnd();




// roof
   glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.0f, 0.0f);
    glVertex2f(510,625);
    glColor3f(0.9f, 0.2f, 0.2f);
    glVertex2f(480,662.5);
    glVertex2f(315,662.5);
    glVertex2f(300,640);
    glVertex2f(315,640);
    glVertex2f(330,625);
    glEnd();

// house body
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.6f, 0.4f);
    glVertex2f(640,450);
    glVertex2f(640,515);
    glColor3f(1.0f, 0.85f, 0.65f);
    glVertex2f(375,515);
    glVertex2f(375,450);
    glEnd();

// house entry
    glBegin(GL_POLYGON);
    glColor3f(0.4f, 0.2f, 0.1f);
    glVertex2f(660,437.5);
    glVertex2f(660,450);
    glVertex2f(375,450);
    glVertex2f(375,437.5);
    glEnd();

// door
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.15f, 0.05f);
    glVertex2f(555,450);
    glVertex2f(555,500);
    glVertex2f(465,500);
    glVertex2f(465,450);
    glEnd();
// door split
    glColor3f(0.0f,0.0f,0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(510,450);
    glVertex2f(510,500);
    glEnd();
// handles
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(500,475);
    glVertex2f(520,475);
    glEnd();

// window 1
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(615,462.5);
    glVertex2f(615,487.5);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(585,487.5);
    glVertex2f(585,462.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(615,462.5);
    glVertex2f(615,487.5);
    glVertex2f(585,487.5);
    glVertex2f(585,462.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(600,462.5);
    glVertex2f(600,487.5);
    glEnd();

// window 2
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(435,462.5);
    glVertex2f(435,487.5);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(405,487.5);
    glVertex2f(405,462.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(435,462.5);
    glVertex2f(435,487.5);
    glVertex2f(405,487.5);
    glVertex2f(405,462.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(420,462.5);
    glVertex2f(420,487.5);
    glEnd();

// upper window 1
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(465,587.5);
    glVertex2f(465,612.5);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(435,612.5);
    glVertex2f(435,587.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(465,587.5);
    glVertex2f(465,612.5);
    glVertex2f(435,612.5);
    glVertex2f(435,587.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(450,587.5);
    glVertex2f(450,612.5);
    glEnd();

// upper window 2
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(390,587.5);
    glVertex2f(390,612.5);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(360,612.5);
    glVertex2f(360,587.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(390,587.5);
    glVertex2f(390,612.5);
    glVertex2f(360,612.5);
    glVertex2f(360,587.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(375,587.5);
    glVertex2f(375,612.5);
    glEnd();



// HOUSE 1

    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.5f, 0.3f);
    glVertex2f(375, 437.5);
    glVertex2f(375,575);
    glColor3f(0.7f, 0.3f, 0.2f);
    glVertex2f(315,637.5);
    glVertex2f(195,637.5);
    glVertex2f(150,575);
    glVertex2f(75,575);
    glVertex2f(75,437.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.6f);
    glVertex2f(375, 437.5);
    glVertex2f(375,562.5);
    glVertex2f(315,625);
    glColor3f(0.85f, 0.55f, 0.3f);
    glVertex2f(195,625);
    glVertex2f(150,562.5);
    glVertex2f(90,562.5);
    glVertex2f(90,437.5);
    glEnd();



// Door
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.15f, 0.05f);
    glVertex2f(315, 437.5);
    glVertex2f(315,512.5);
    glVertex2f(270,512.5);
    glVertex2f(270,437.5);
    glEnd();
// door split
    glColor3f(0.0f,0.0f,0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(292.5,437.5);
    glVertex2f(292.5,512.5);
    glEnd();
// handles
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(285,475);
    glVertex2f(300,475);
    glEnd();

// Window 1
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(165, 462.5);
    glVertex2f(165,515);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(120,515);
    glVertex2f(120,462.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(165,462.5);
    glVertex2f(165,515);
    glVertex2f(120,515);
    glVertex2f(120,462.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(142.5,462.5);
    glVertex2f(142.5,515);
    glEnd();

// Window 2
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(240, 462.5);
    glVertex2f(240,515);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(195,515);
    glVertex2f(195,462.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(240,462.5);
    glVertex2f(240,515);
    glVertex2f(195,515);
    glVertex2f(195,462.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(217.5,462.5);
    glVertex2f(217.5,515);
    glEnd();

// Window 3
    glBegin(GL_POLYGON);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex2f(300, 562.5);
    glVertex2f(300,607.5);
    glColor3f(0.65f,0.32f,0.10f);
    glVertex2f(225,607.5);
    glVertex2f(225,562.5);
    glEnd();
// frame
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(300,562.5);
    glVertex2f(300,607.5);
    glVertex2f(225,607.5);
    glVertex2f(225,562.5);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(262.5,562.5);
    glVertex2f(262.5,607.5);
    glEnd();
    // Side lines for upper house
    glColor3f(0.1f, 0.1f, 0.1f);  // Dark color
    glLineWidth(3.0f);

    glBegin(GL_LINES);
    glVertex2f(375, 437.5);
    glVertex2f(375,565);
    glEnd();



// TREE 2

    glColor3f(0.0f, 0.27f, 0.13f);
    drawCircle(785,590.5, 50, 70);//1
    drawCircle(75+645,640, 60, 70);//2

    drawCircle(725,585,60, 70);//3
    drawCircle(585,590.5, 50, 70);//1.1
    drawCircle(640,570.5, 50, 70);//1.2

    drawCircle(800,650.5,60, 70);//4
    drawCircle(630,650.5, 70, 70);//5
    drawCircle(750,680, 70, 70);//6

    drawCircle(670,695,60, 70);//7

    drawCircle(580,660.5,60, 70);//8

    drawCircle(590,680.5,50, 70);//8



    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(675,425);
    glVertex2f(675,562.5);
    glVertex2f(705,562.5);
    glVertex2f(705,425);
    glEnd();



// grass
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.35f, 0.0f);   // dark green (bottom)
    glVertex2f(645,392.5);//h

    glColor3f(0.0f, 0.55f, 0.0f);   // softer green (top)
    glVertex2f(625,430);//i

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(655,392.5);//k

    glColor3f(0.0f, 0.55f, 0.0f);   // soft
    glVertex2f(650,440);//j

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(665,392.5);//l

    glColor3f(0.0f, 0.55f, 0.0f);   // soft
    glVertex2f(690,430);//m

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(675,392.5);//n
    glEnd();

    //tree branch
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(730,470+50);//d
    glVertex2f(730,455+50);//c
    glVertex2f(705,430+50);//a
    glVertex2f(705,460+50);//b
    glEnd();


// grass2
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.35f, 0.0f);   // dark green (bottom)
    glVertex2f(645+70,392.5+10);//h

    glColor3f(0.0f, 0.55f, 0.0f);   // softer green (top)
    glVertex2f(625+70,430+10);//i

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(655+70,392.5+10);//k

    glColor3f(0.0f, 0.55f, 0.0f);   // soft
    glVertex2f(650+70,440+10);//j

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(665+70,392.5+10);//l

    glColor3f(0.0f, 0.55f, 0.0f);   // soft
    glVertex2f(690+70,430+10);//m

    glColor3f(0.0f, 0.35f, 0.0f);   // dark
    glVertex2f(675+70,392.5+10);//n
    glEnd();


//tree branch 2
    glColor3f(0.36f, 0.16f, 0.09f);
    drawCircle(730,513.5,8, 70);
    glColor3f(0.91f, 0.76f, 0.65f);
    drawCircle(730,513.5,4, 70);


//tree branch
    glColor3f(0.55f, 0.27f, 0.07f);

    glBegin(GL_POLYGON);
    glVertex2f(705,562.5);//d
    glVertex2f(730,592.5);//c
    glVertex2f(715,592.5);//a
    glVertex2f(690,575);//b
    glVertex2f(700,625);//d
    glVertex2f(690,635);//c
    glVertex2f(675,560);//a
    glVertex2f(615,620);//b
    glVertex2f(605,630);//a
    glVertex2f(675,562.5);//b
    glEnd();


//paddy hill
    // paddy HILL (in front of first tree)
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.9f, 0.3f);   // bright yellow (top of hill)
    glVertex2f(0, 420);            // left bottom
    glColor3f(0.95f, 0.75f, 0.1f); // golden (bottom side)
    glVertex2f(160, 420);          // right bottom
    glColor3f(1.0f, 0.85f, 0.2f);  // yellow-gold (top curve)
    glVertex2f(150, 480);          // right top
    glVertex2f(140, 500);          // right top
    glVertex2f(120, 520);           // left top
    glVertex2f(100, 540);           // left top
    glVertex2f(80, 560);           // left top
    glVertex2f(60, 540);           // left top
    glVertex2f(40, 520);           // left top
    glVertex2f(20, 500);
    glVertex2f(10, 480);
    //glEnd();

    // Add some hay texture lines (to make it look real)
    glColor3f(0.85f, 0.65f, 0.05f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(30, 440);
    glVertex2f(50, 470);
    glVertex2f(70, 430);
    glVertex2f(90, 465);
    glVertex2f(110, 435);
    glVertex2f(130, 468);
    glEnd();


// narrow river 1 beside the house


    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.3f, 0.7f);  // bottom
    glVertex2f(809,282);//n
    glVertex2f(807,327);//m
    glColor3f(0.3f, 0.6f, 1.0f);  // top
    glVertex2f(462,305);//f
    glVertex2f(465,274);//g
    glEnd();

    glColor3f(0.0f, 0.4f, 0.9f);
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.3f, 0.7f);  // bottom
    glVertex2f(807,327);//m
    glVertex2f(900,440);//k
    glColor3f(0.3f, 0.6f, 1.0f);  // top
    glVertex2f(490,274);//j
    glVertex2f(685,337);//h
    glEnd();

    //soil
    glColor3f(0.823f, 0.705f, 0.549f);
    glBegin(GL_POLYGON);
    glVertex2f(400,265);//g
    glVertex2f(400,300);//f
    glVertex2f(0,300);//d
    glVertex2f(0,265);//e
    glEnd();

    glColor3f(0.823f, 0.705f, 0.549f);
    glBegin(GL_POLYGON);
    glVertex2f(625,300);//i
    glVertex2f(625,330);//h
    glVertex2f(400,300);//f
    glVertex2f(400,265);//g
    glEnd();

    glColor3f(0.823f, 0.705f, 0.549f);
    glBegin(GL_POLYGON);
    glVertex2f(625,300);//i
    glVertex2f(890,430);//g
    glVertex2f(900,440);//k
    glVertex2f(625,330);//h

    glEnd();
    glColor3f(0.823f, 0.705f, 0.549f);
    glBegin(GL_POLYGON);
    glVertex2f(1200,265);//p
    glVertex2f(1200,300);//o
    glVertex2f(840,300);//s
    glVertex2f(807,305);//m
    glVertex2f(807,265);//n
    glEnd();



    // COW on green grass (front of house)
     float cowX = 200 + cowMove;
        float cowY = 400;

    //drawGrassPatch(cowX - 20, cowY - 10);
       drawCow(cowX, cowY);


// Khuti + rope
drawKhuti(150, cowY);
//drawCurvedRope(cowX + 120, cowY + 35, 150, cowY + 50);


drawBasket(165, cowY - 10);   // khuti , fixed position

    // BOAT

    glPushMatrix();                  // Save current coordinate system
    glTranslatef(boatPosX, 0.0f, 0); // Move boat along x-axis



    //pall (Right side )
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(630, 125);   // Bottom-left
    glVertex2f(630, 560);   // Much taller mast height
    glVertex2f(880, 300);   // Wider outward point
    glVertex2f(800, 125);   // Bottom-right
    glEnd();

    //pall (Left side)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_TRIANGLES);
    glVertex2f(630, 125);   // Bottom-right
    glVertex2f(630, 560);   // Same tall height as mainsail
    glVertex2f(400, 125);   // Much farther left for width
    glEnd();

    // Stick
    glColor3f(0.3f, 0.15f, 0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(625, 125);
    glVertex2f(635, 125);
    glVertex2f(635, 580);   // Taller mast
    glVertex2f(625, 580);
    glEnd();

    //back body
    glColor3f(0.0f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(855, 100);
    glVertex2f(910, 125);
    glVertex2f(345, 125);
    glVertex2f(390, 100);//365
    glEnd();


    //Human
    // Head (circle)
    glColor3f(0.9f, 0.8f, 0.6f);
    drawCircle(400, 270, 30, 100);

    //hair
    // Hair (polygon on top of head)
    glColor3f(0.1f, 0.1f, 0.1f); // Dark black hair
    glBegin(GL_POLYGON);
    glVertex2f(370, 280);  // left side of head
    glVertex2f(430, 280);  // right side of head
    glVertex2f(440, 300);  // top right
    glVertex2f(400, 320);  // top middle
    glVertex2f(360, 300);  // top left
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f); // Dark black hair
    glBegin(GL_POLYGON);
    glVertex2f(400, 250);  //1
    glVertex2f(400, 280);  // 2
    glVertex2f(370, 280);  //3
    glVertex2f(370, 250);  // 4

    glEnd();


    // Eyes (small black circles)
    glColor3f(0.0f, 0.0f, 0.0f); // Black
    drawCircle(390, 265, 3, 50); // Left eye
    drawCircle(410, 265, 3, 50); // Right eye

    // Eyebrows (thin black rectangles/lines above eyes)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON); // Left eyebrow
    glVertex2f(383, 273);
    glVertex2f(397, 273);
    glVertex2f(397, 276);
    glVertex2f(383, 276);
    glEnd();

    glBegin(GL_POLYGON); // Right eyebrow
    glVertex2f(403, 273);
    glVertex2f(417, 273);
    glVertex2f(417, 276);
    glVertex2f(403, 276);
    glEnd();

    // Lips (smile shape)


    // Lips (just one line)
    glColor3f(0.8f, 0.2f, 0.2f); // Red lips
    glBegin(GL_LINES);
    glVertex2f(420, 250); // left corner
    glVertex2f(410, 250); // right corner
    glEnd();



// Body (rectangle)
    glColor3f(0.2f, 0.2f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(430, 165);
    glVertex2f(430, 240);
    glVertex2f(370, 240);
    glVertex2f(370, 165);
    glEnd();

    // Arm
    glColor3f(0.9f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(445, 220-40);
    glVertex2f(445, 200-30);
    glVertex2f(380, 200);
    glVertex2f(380, 215);
    glEnd();

    // Leg
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(490, 100);//1
    glVertex2f(470, 150);//2
    glVertex2f(470-30, 170);//3
    glVertex2f(430-30, 170);//4
    glVertex2f(400-30, 165);//5
    glVertex2f(430-70, 130);
    glVertex2f(410-50, 100);//6
    glEnd();

    // boat boitha Oar (long brown rectangle)
    glColor3f(0.5f, 0.25f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(455, 200);
    glVertex2f(470, 200);
    glVertex2f(350, 70);
    glVertex2f(365, 70);
    glEnd();

// Oar Blade (flat part touching water)
    glColor3f(0.3f, 0.15f, 0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(330, 60);
    glVertex2f(380, 60);
    glVertex2f(380, 90);
    glVertex2f(330, 90);
    glEnd();


//boat part
    glColor3f(0.5f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(870, 62.5);
    glVertex2f(945, 150);
    glVertex2f(840, 110);
    glVertex2f(340, 110);//365
    glVertex2f(390, 62.5);//960

    glEnd();

    glColor3f(0.5f, 0.2f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(430,95);
    glVertex2f(300, 150);
    glVertex2f(350, 100);
    glEnd();

    glPopMatrix();


    //flower
/*
// flower 2
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.9f); // soft pink
    glVertex2f(75+40,100-40);
    glVertex2f(150+40,155-40);
    glColor3f(1.0f, 1.0f, 1.0f); // white
    glVertex2f(150+40,200-40);
    glVertex2f(75+40,165-40);
    glEnd();*/

// flower 1
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.9f);
    glVertex2f(75-15,63);
    glVertex2f(50,120);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0,125);
    glVertex2f(30,75);
    glEnd();

// flower 2
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.9f);
    glVertex2f(75-15,38);
    glVertex2f(50,63);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0,40);
    glVertex2f(30,50);
    glEnd();

// flower 3
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.9f);
    glVertex2f(75,100);
    glVertex2f(150,188-35);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(150,250-50);
    glVertex2f(75,200-35);
    glEnd();

// flower 4 (near 255,38)
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.8f, 0.9f);
    glVertex2f(255,38);
    glVertex2f(225,63);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(165,75);
    glVertex2f(195,40);
    glEnd();

// grass 1 (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(90,0);
    glVertex2f(150,125);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(150,115);
    glVertex2f(120,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(150,125);
    glVertex2f(210,50);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(150,95);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(0.5f);
    glBegin(GL_LINES);
    glVertex2f(120,0);
    glVertex2f(150,125);
    glEnd();

// grass 2 (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(90+15,0);
    glVertex2f(150+15,125);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(150+15+15,115);
    glVertex2f(120+15,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(150+15,125);
    glVertex2f(210+15,50);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(150+15,95);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(0.5f);
    glBegin(GL_LINES);
    glVertex2f(90+25,0);
    glVertex2f(150+15,125);
    glEnd();

// grass 3 (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(90,0+35);
    glVertex2f(150,125+35);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(150,115+35);
    glVertex2f(120,0+35);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(150,125+35);
    glVertex2f(210,50+35);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(150,95+35);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(100,0+35);
    glVertex2f(150,115+35);
    glEnd();

// grass 4 (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(90,0);
    glVertex2f(150-60,125);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(120,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(100,0);
    glVertex2f(150-60,125);
    glEnd();

// grass 5 (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(90,0);
    glVertex2f(150-90,125);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(140,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(100,0);
    glVertex2f(150-90,125);
    glEnd();

// grass 6 left (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(70,0);
    glVertex2f(0,115);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(50,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(10,85);
    glVertex2f(0,125);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(0,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(78,0);
    glVertex2f(0,115);
    glEnd();

// grass 7 (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(90+15,0);
    glVertex2f(0+15,125);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(50+15,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(90+20,0);
    glVertex2f(0+15,120);
    glEnd();

// grass 7 small (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(45,0);
    glVertex2f(10,25);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(30,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(35,0);
    glVertex2f(10,25);
    glEnd();

// grass 8 (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(55,0);
    glVertex2f(0,55);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(40,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(50,0);
    glVertex2f(0,55);
    glEnd();

// grass 9 left (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(70,0);
    glVertex2f(0,115-35);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(50,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(10,85-20);
    glVertex2f(0,125-40);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(0,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(10,85-20);
    glVertex2f(0,125-40);
    glEnd();

// grass 10 left (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(120,0);
    glVertex2f(50,170);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(85,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(55,150);
    glVertex2f(0,130);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(50,170);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(55,150);
    glVertex2f(0,130);
    glEnd();

// grass 11 left (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(120-15,0);
    glVertex2f(50-15,170);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(85-15,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(55-15,150-15);
    glVertex2f(0,130-15);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(50-15,170-15);
    glEnd();

// grass 12 left (Type A)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.6f, 0.0f);
    glVertex2f(150,0);
    glVertex2f(220,130);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(150-20,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(150,0);
    glVertex2f(220,130);
    glEnd();

// grass 13 left (Type B)
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(180,0);
    glVertex2f(230,80);
    glColor3f(0.1f, 0.7f, 0.1f);
    glVertex2f(180-20,0);
    glEnd();

// line
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(180,0);
    glVertex2f(230,80);
    glEnd();

}

void seen_two(){
    //sky

glBegin(GL_POLYGON);


// Top-left vertex: sky blue

    glColor3f(0.53f, 0.81f, 0.92f);

    glVertex2f(0, 686);



    // Bottom-left vertex: white

    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(0, 460);



    // Bottom-right vertex: white

    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(1200, 452);



    // Top-right vertex: sky blue

    glColor3f(0.53f, 0.81f, 0.92f);

    glVertex2f(1200, 686);



glEnd();

}

void seen_three(){
    // Reset modelview

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    seen_one( );

    glFlush();
}

// boat moving

void update(int value)


{
    boatPosX += 2.0f;   // slow speed


    if (boatStartX + boatPosX > 1200)
    {
        boatPosX = -(boatStartX + boatWidth);
    }

    // Cloud movement
    cloudPosX1 += 0.3f;
    cloudPosX2 += 0.2f;
    cloudPosX3 += 0.4f;


    if (cloudPosX1 > 1200)
    cloudPosX1 = -(cloudStartX + cloudWidth);


// head rotation
    headAngle += headSpeed;
    if(headAngle > 10 || headAngle < -10) headSpeed = -headSpeed;


    // Fish bounce
    fishY += fishSpeed;
    if(fishY > 5 || fishY < 0) fishSpeed = -fishSpeed; // limits


    // fish slowly moves to mouth
    if(fishAnim > 0) fishAnim -= fishSpeed;

    // fish gentle bounce
    fishBounce += fishBounceSpeed * fishBounceDir;
    if(fishBounce > 2 || fishBounce < -2) fishBounceDir = -fishBounceDir;



for(int i = 0; i < NUM_BIRDS; i++)
    {
        birds[i].x += birds[i].speed;
        birds[i].wave += birds[i].waveSpeed;

        // wave motion
        birds[i].y += sin(birds[i].wave) * 0.5f;

        // screen cross
        if(birds[i].x > 1250)
        {
            birds[i].x = -50;
            birds[i].y = 520 + rand() % 180;
        }
    }

    // Cow move (slow)
       cowMove += 0.2f * cowDir;
         if(cowMove > 20 || cowMove < -20)
             cowDir = -cowDir;

         // Cow head eating motion
          cowHeadAngle += 0.3f * cowHeadDir;
               if(cowHeadAngle > 15 || cowHeadAngle < -15)
                  cowHeadDir = -cowHeadDir;



    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}


void initGL()
{
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1200, 0, 750);
}


void initBirds()
{
    for(int i = 0; i < NUM_BIRDS; i++)
    {
        birds[i].x = rand() % 1200;          // screen width
        birds[i].y = 520 + rand() % 180;     // sky area
        birds[i].speed = 0.6f + (rand() % 4) * 0.3f;

        birds[i].wave = rand() % 360;
        birds[i].waveSpeed = 0.03f + (rand() % 5) * 0.01f;
    }
}




int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 750);
    glutCreateWindow("Beautiful Scenic View - 1200x750 Frame");
    glClearColor(0.5f,0.8f,1.0f,1.0f);
    initBirds();
    glutDisplayFunc(display);
    glutTimerFunc(15, update, 0);


    initGL();
    glutMainLoop();
    return 0;
}


