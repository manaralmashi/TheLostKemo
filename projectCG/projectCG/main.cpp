//
//  main.cpp
//  CGProject
//
//

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>      // handle the window-managing operations
#else
#include <GL/glew.h>
#include <GL/freeglut.h>    // handle the window-managing operations
#endif
#include <chrono>
#include <iostream>

//-----------------------------------------------------------
float boxX = 0.07f;
float boxY = 0.05f;
float boxY2 = -0.19f;
float boxSizey = 0.18f;
float boxSizex = 0.42f;
//-----------------------------------------------------------
GLint windowWidth = 500;
GLint windowHeight = 500;

GLdouble PI = 3.14159265359;
//-----------------------------[0]---------------------------
#define TIMER_INTERVAL 9000

// Timer variables
std::chrono::steady_clock::time_point timer1;
int currentShape = 0;
//-----------------------------[1]---------------------------
GLfloat jumpY = 0.0;                 //Stores the Y position value when characters jump
GLfloat angle = 0.0;                 // Angle of jump
GLfloat radius = 0.2;                //Amount of jump radius
GLfloat stepSize = -0.02f;        // Step size of the leg movement of Kimo's mother and father
bool isLeftFootForward = true;       //Checks the condition of the foot

//The foot position of Kima's mother and father
// Y position :
GLfloat LY = -0.40f;
GLfloat RY = -0.39f;
// Position of clouds on the x - axis :
GLfloat cloudX1 = 0.0;
GLfloat cloudX2 = 0.14;
// Position of Kimo on the x - axis :
GLfloat KimoX = 0.0;
GLfloat KimoX2 = 0.0;
// Position of Kimo on the y - axis :
GLfloat KimoY = 0.0;

//-----------------------------[2]---------------------------
GLfloat jumpY2 = 0.0;      //Stores the Y position value when Kimo jump
GLfloat angle2 = 0.0;      // Angle of jump
GLfloat radius2 = 0.2;     //Amount of jump radius
GLfloat cornY = 0.0;       //Stores the Y position value for corn
GLfloat  sunY = 0.0;       //Stores the Y position value for sun
GLfloat KimoY2 = 0.0;       // Position of Kimo on the y - axis

//-----------------------------[3]---------------------------
GLfloat txc = 0.0, // use it to move the clouds along x axis
tys = 0.0, // use it to move the su along y axis
transpS = 0.0, // to control the degree of sunset
tyk = -0.8, // use it to move the character along y axis
tsk = 0.5, // to control how much the character is reduced
trl = 0.0, // to move the leaves
tyl = 0.0; // to move the leaves

//-----------------------------[4]---------------------------
float xpos_s4 = -1;
float xpos_cloud_reverse = 0.9;
float ypos_s4 = 0.0;
float angle_s4 = 180.0f;
int refreshmill = 1;

//-----------------------------[5-6-7-8-9-12]---------------------------
float Typos =0.4;
float Txpos = 0.0;
float Mxpos = 0.0;
float Kxpos = 0.0;
float Kxpos2 = 0.0;
float Opos = 0.0;
float Fpos = 0.0;
float sposx = 1.2;//sun movment on x axis
float sposy = -0.54;//sun movment on y axis
float cavepos = 1.4;//cave momvment
float cpos = 0.77;//carrot momvment
float dposx = 0.8;//rabbet`s dad momvment on x axis
float dposy = 0.1;//rabbet`s dad momvment on y axis
float kpos = -0.23;//kemp movment
float gpos = -0.6;//girl rabbet movment
float nfpos = 1.0;//normal face expression movment
float sfpos = 0.0;//shock face expression movment


//-----------------------------[10-11]---------------------------
GLfloat transp = 0.0,
transp2 = 0.0,
transp3 = 0.0,
transp4 = 0.0,
transp5 = 0.0,
transp6 = 0.0,
txo = -0.99,
txs = 0.0,
txsf = -0.65,
txt = 0.0,
txt2 = 1.0,
txt3 = -0.5,
txt4 = -0.9,
txt5 = 0.0,
transp7 = 0.0;

//-----------------------------[13]---------------------------
float xpos_cloud_s13 = -0.5;
float angleValue_s13 = 0.0;

GLuint woodTexture;
char imagePath[] = "/Users/manaralmashi/Desktop/6th level/Computer Graphics/Free_Woodgrain_Vector-04.bmp";

//-----------------------------[14]---------------------------
float xpos_cloud_s14 = -0.5;
float orthoValue_s14 = 1;
float alphaValue_s14 = -1;


//-------------------------------------------------------------------------------
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat twicePi) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle



    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi * PI / triangleAmount)),
            y + (radius * sin(i * twicePi * PI / triangleAmount))
        );
    }
    glEnd();
}
//-------------------------------------------------------------------------------

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat twicePi) {
    int i;
    int lineAmount = 100; //# of triangles used to draw circle



    glBegin(GL_LINE_LOOP);
    for (i = 0; i <= lineAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi * PI / lineAmount)),
            y + (radius * sin(i * twicePi * PI / lineAmount))
        );
    }
    glEnd();
}
//-------------------------------------------------------------------------------
//To draw eyelashes :
void drawHollowCircle3(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 0.5f * PI;

    glBegin(GL_LINE_STRIP);
    for (i = 0; i <= lineAmount; i++) {
        glVertex2f(
            x + (-radius * sin(i * twicePi / lineAmount)),
            y + (-radius * cos(i * twicePi / lineAmount))
        );
    }
    glEnd();
}
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//                   THE BEGINNING OF SCENE DRAWINGS        :
//----------------------------------------------------------------------------------
//

void Kemo_Mother()
{

    //  FACE:
    //The purple part of the face
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.5, .09, 2.0);
    drawFilledCircle(-0.1, 0.09, .07, 2.0);
    drawFilledCircle(0.22, 0.09, .07, 2.0);

    glBegin(GL_POLYGON);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(-0.1f, 0.02f);
    glVertex2f(0.23f, 0.02f);
    glVertex2f(0.06f, 0.3f);
    glVertex2f(0.2915f, 0.09f);
    glVertex2f(0.148f, 0.5208f);
    glVertex2f(-0.028f, 0.5208f);
    glVertex2f(-0.17f, 0.1f);
    glEnd();


    //The white part of the face
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.01, 0.45, .019, 2.0f);
    drawFilledCircle(0.13, 0.45, .019, 2.0f);
    drawFilledCircle(-0.12, 0.1, .02, 2.0f);
    drawFilledCircle(0.24, 0.1, .02, 2.0f);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.12f, 0.08f);
    glVertex2f(0.24f, 0.08f);
    glVertex2f(0.24f, 0.1f);
    glVertex2f(-0.12f, 0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.030f, 0.45f);
    glVertex2f(-0.138f, 0.1f);
    glVertex2f(0.258f, 0.1f);
    glVertex2f(0.149f, 0.45f);
    glEnd();
    //-------------------------------------------
    // HAIR :

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.01, 0.45, .019, 2.0);
    drawFilledCircle(0.13, 0.45, .019, 2.0);
    drawFilledCircle(-0.04f, 0.35f, .018, 2.0);
    drawFilledCircle(-0.03f, 0.35f, .02, 2.0);
    drawFilledCircle(0.0f, 0.35f, .02, 2.0);
    drawFilledCircle(0.03f, 0.35f, .02, 2.0);
    drawFilledCircle(0.06f, 0.35f, .02, 2.0);
    drawFilledCircle(0.09f, 0.35f, .02, 2.0);
    drawFilledCircle(0.12f, 0.35f, .02, 2.0);
    drawFilledCircle(0.15f, 0.35f, .02, 2.0);
    drawFilledCircle(0.16f, 0.35f, .018, 2.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.18f, 0.35f);
    glVertex2f(0.149f, 0.453f);
    glVertex2f(0.06f, 0.36f);
    glVertex2f(-0.061f, 0.35f);
    glVertex2f(-0.031f, 0.453f);
    glVertex2f(0.06f, 0.36f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-0.01, 0.45);
    glVertex2f(0.13, 0.45f);
    glVertex2f(0.13f, 0.35f);
    glVertex2f(-0.01f, 0.35f);
    glEnd();
    //-------------------------------------------
    //The purple circle at the top of the face
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.46, .05, 2.0);
    //Arrange the ends of the hair
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.001, 0.44, .02, 2.0);
    drawFilledCircle(0.0, 0.45, .02, 2.0);
    drawFilledCircle(0.12, 0.44, .02, 2.0);
    drawFilledCircle(0.121, 0.45, .02, 2.0);

    //--------------------------------------------
    //The hat

    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.42, .041, 2.0);
    drawFilledCircle(0.15, 0.56, .02, 2.0);
    glBegin(GL_TRIANGLES);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.078f, 0.59f);
    glVertex2f(0.15f, 0.58f);
    glVertex2f(0.18f, 0.51f);
    glVertex2f(0.17f, 0.57f);
    glVertex2f(0.18f, 0.51f);
    glVertex2f(0.15f, 0.56f);
    glEnd();
    //--------------------------------------------
    glColor3f(0.0f, 0.0f, 0.0f);
    //The mouth
    drawHollowCircle(0.061f, 0.19f, 0.03f, -1.0);
    //The eyes
    drawHollowCircle(0.026f, 0.26f, 0.04, 2.0);
    drawHollowCircle(0.105f, 0.26f, 0.04, 2.0);
    drawFilledCircle(0.04, 0.26, .016, 2.0);
    drawFilledCircle(0.09, 0.26, .016, 2.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.04, 0.26, .005, 2.0);
    drawFilledCircle(0.09, 0.26, .005, 2.0);
    drawFilledCircle(0.032, 0.264, .003, 2.0);
    drawFilledCircle(0.032, 0.255, .003, 2.0);
    drawFilledCircle(0.098, 0.264, .003, 2.0);
    drawFilledCircle(0.098, 0.255, .003, 2.0);

    //Eyelashes
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.142, 0.30, 0.02, -0.5);
    drawHollowCircle(0.12, 0.312, 0.02, -0.5);
    drawHollowCircle(0.13, 0.31, 0.02, -0.5);
    drawHollowCircle3(-0.01, 0.30, 0.02);
    drawHollowCircle3(0.0, 0.312, 0.02);
    drawHollowCircle3(0.014, 0.315, 0.02);

    //--------------------------------------------
    //Hand :
    //Left hand
    glBegin(GL_QUADS);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(-0.04f, 0.02f);
    glVertex2f(-0.08f, 0.02f);
    glVertex2f(-0.13f, -0.16f);
    glVertex2f(-0.09f, -0.16f);
    //Right hand
    glBegin(GL_QUADS);
    glVertex2f(0.185f, 0.02f);
    glVertex2f(0.223f, 0.02f);
    glVertex2f(0.275f, -0.16f);
    glVertex2f(0.233f, -0.16f);
    glEnd();

    //Left hand palm
    drawFilledCircle(-0.13f, -0.15f, .04, 2.0);
    //Right hand palm
    drawFilledCircle(0.275f, -0.15f, .04, 2.0);

}
void MotherFootL() {
    glBegin(GL_QUADS);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.015f, 0.02f);
    glVertex2f(0.06f, 0.02f);
    glVertex2f(0.06f, -0.3f);
    glVertex2f(0.015f, -0.3f);
    glEnd();
    drawFilledCircle(0.012f, -0.3f, .05, 2.0);
}
void MotherFootR() {
    glBegin(GL_QUADS);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.09f, 0.02f);
    glVertex2f(0.135f, 0.02f);
    glVertex2f(0.135f, -0.3f);
    glVertex2f(0.09f, -0.3f);
    glEnd();
    drawFilledCircle(0.138f, -0.3f, .05, 2.0);


    //Skirt
    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.7f, 0.8f);
    glVertex2f(0.015f, 0.02f);
    glVertex2f(0.015f, -0.15f);
    glVertex2f(-0.04f, -0.15f);

    glVertex2f(0.135f, 0.02f);
    glVertex2f(0.135f, -0.15f);
    glVertex2f(0.185f, -0.15f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.7f, 0.8f);
    glVertex2f(0.015f, 0.02f);
    glVertex2f(0.135f, 0.02f);
    glVertex2f(0.135f, -0.15f);
    glVertex2f(0.015f, -0.15f);
    glEnd();

}
void  Kemo_Father()
{
    //  FACE:
    //The purple part of the face
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.5, .09, 2.0);
    drawFilledCircle(-0.1, 0.09, .07, 2.0);
    drawFilledCircle(0.22, 0.09, .07, 2.0);

    glBegin(GL_POLYGON);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(-0.1f, 0.02f);
    glVertex2f(0.23f, 0.02f);
    glVertex2f(0.06f, 0.3f);
    glVertex2f(0.2915f, 0.09f);
    glVertex2f(0.148f, 0.5208f);
    glVertex2f(-0.028f, 0.5208f);
    glVertex2f(-0.17f, 0.1f);
    glEnd();


    //The white part of the face
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.01, 0.45, .019, 2.0f);
    drawFilledCircle(0.13, 0.45, .019, 2.0f);
    drawFilledCircle(-0.12, 0.1, .02, 2.0f);
    drawFilledCircle(0.24, 0.1, .02, 2.0f);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.12f, 0.08f);
    glVertex2f(0.24f, 0.08f);
    glVertex2f(0.24f, 0.1f);
    glVertex2f(-0.12f, 0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.030f, 0.45f);
    glVertex2f(-0.138f, 0.1f);
    glVertex2f(0.258f, 0.1f);
    glVertex2f(0.149f, 0.45f);
    glEnd();
    //-------------------------------------------
    // HAIR :

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.02f, 0.41f);
    glVertex2f(0.01f, 0.35f);
    glVertex2f(0.1f, 0.38f);
    glVertex2f(0.1f, 0.41f);
    glVertex2f(0.11f, 0.35f);
    glVertex2f(0.02f, 0.38f);
    glVertex2f(0.02f, 0.37f);
    glVertex2f(0.06f, 0.30f);
    glVertex2f(0.1f, 0.37f);
    glEnd();
    //-------------------------------------------

   //The purple circle at the top of the face
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.46, .05, 2.0f);
    //Arrange the ends of the hair
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.001, 0.44, .02, 2.0f);
    drawFilledCircle(0.0, 0.45, .02, 2.0f);
    drawFilledCircle(0.12, 0.44, .02, 2.0f);
    drawFilledCircle(0.121, 0.45, .02, 2.0f);

    //--------------------------------------------
    //The hat

    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.42, .041, 2.0);
    drawFilledCircle(0.15, 0.56, .02, 2.0);
    glBegin(GL_TRIANGLES);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.078f, 0.59f);
    glVertex2f(0.15f, 0.58f);
    glVertex2f(0.18f, 0.51f);
    glVertex2f(0.17f, 0.57f);
    glVertex2f(0.18f, 0.51f);
    glVertex2f(0.15f, 0.56f);
    glEnd();
    //--------------------------------------------

    glColor3f(0.73f, 0.61f, 0.76f);
    //The mouth
    drawHollowCircle(0.061f, 0.19f, 0.03f, -1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.08, 0.20, .02, 2.0f);
    drawFilledCircle(0.045, 0.20, .02, 2.0f);
    drawFilledCircle(0.1f, 0.213f, 0.024f, -1.0f);
    drawFilledCircle(0.1f, 0.206f, 0.02f, -1.0f);
    drawFilledCircle(0.02f, 0.213f, 0.024f, -1.0f);
    drawFilledCircle(0.02f, 0.206f, 0.02f, -1.0f);
    //The eyes
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.022f, 0.26f, 0.02, 2.0f);
    drawHollowCircle(0.101f, 0.26f, 0.02, 2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.022, 0.26, .012, 2.0f);
    drawFilledCircle(0.101, 0.26, .012, 2.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.02, 0.26, .005, 2.0f);
    drawFilledCircle(0.1, 0.26, .005, 2.0f);

    //--------------------------------------------
    //Hand :
    //Left hand
    glBegin(GL_QUADS);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(-0.04f, 0.02f);
    glVertex2f(-0.08f, 0.02f);
    glVertex2f(-0.13f, -0.16f);
    glVertex2f(-0.09f, -0.16f);
    //Right hand
    glBegin(GL_QUADS);
    glVertex2f(0.185f, 0.02f);
    glVertex2f(0.223f, 0.02f);
    glVertex2f(0.275f, -0.16f);
    glVertex2f(0.233f, -0.16f);
    glEnd();

    //Left hand palm
    drawFilledCircle(-0.13f, -0.15f, .04, 2.0);
    //Right hand palm
    drawFilledCircle(0.275f, -0.15f, .04, 2.0);


}
void FatherFootL() {
    glBegin(GL_QUADS);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.015f, 0.02f);
    glVertex2f(0.06f, 0.02f);
    glVertex2f(0.06f, -0.3f);
    glVertex2f(0.015f, -0.3f);
    glEnd();
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.012f, -0.3f, .05, 2.0f);
    //Pants-left side
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.1f, 0.0f);
    glVertex2f(0.015f, 0.02f);
    glVertex2f(0.06f, 0.02f);
    glVertex2f(0.06f, -0.2f);
    glVertex2f(0.015f, -0.2f);

    glVertex2f(0.09f, 0.02f);
    glVertex2f(0.06f, 0.02f);
    glVertex2f(0.06f, -0.05f);
    glVertex2f(0.09f, -0.05f);

    glColor3f(0.5f, 0.0f, .1f);
    glVertex2f(0.015f, -0.17f);
    glVertex2f(0.06f, -0.17f);
    glVertex2f(0.06f, -0.2f);
    glVertex2f(0.015f, -0.2f);
    glEnd();
}
void FatherFootR() {
    glBegin(GL_QUADS);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.09f, 0.02f);
    glVertex2f(0.135f, 0.02f);
    glVertex2f(0.135f, -0.3f);
    glVertex2f(0.09f, -0.3f);
    glEnd();

    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.138f, -0.3f, .05, 2.0f);
    //Pants-right side
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.1f, 0.0f);
    glVertex2f(0.09f, 0.02f);
    glVertex2f(0.135f, 0.02f);
    glVertex2f(0.135f, -0.2f);
    glVertex2f(0.09f, -0.2f);


    glColor3f(0.5f, 0.0f, .1f);
    glVertex2f(0.09f, -0.17f);
    glVertex2f(0.135f, -0.17f);
    glVertex2f(0.135f, -0.2f);
    glVertex2f(0.09f, -0.2f);

    //Belt
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.135f, 0.02f);
    glVertex2f(0.015f, 0.02f);
    glVertex2f(0.015f, 0.0f);
    glVertex2f(0.135f, 0.0f);
    glEnd();
    glColor3f(0.8f, 0.6f, 0.3f);
    drawFilledCircle(0.072f, 0.011f, .01, 2.0f);
    glColor3f(0.6f, 0.1f, 0.0f);
    drawHollowCircle(0.072f, 0.011f, .01, 2.0f);


}
void  Kemo_Brother()
{

    //  FACE:
    //The purple part of the face
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.5, .09, 2.0);
    drawFilledCircle(-0.1, 0.09, .07, 2.0);
    drawFilledCircle(0.22, 0.09, .07, 2.0);

    glBegin(GL_POLYGON);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(-0.1f, 0.02f);
    glVertex2f(0.23f, 0.02f);
    glVertex2f(0.06f, 0.3f);
    glVertex2f(0.2915f, 0.09f);
    glVertex2f(0.148f, 0.5208f);
    glVertex2f(-0.028f, 0.5208f);
    glVertex2f(-0.17f, 0.1f);
    glEnd();


    //The black part of the face
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.01, 0.45, .019, 2.0f);
    drawFilledCircle(0.13, 0.45, .019, 2.0f);
    drawFilledCircle(-0.12, 0.1, .02, 2.0f);
    drawFilledCircle(0.24, 0.1, .02, 2.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.12f, 0.08f);
    glVertex2f(0.24f, 0.08f);
    glVertex2f(0.24f, 0.1f);
    glVertex2f(-0.12f, 0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.030f, 0.45f);
    glVertex2f(-0.138f, 0.1f);
    glVertex2f(0.258f, 0.1f);
    glVertex2f(0.149f, 0.45f);
    glEnd();


    //----------------------------------------------
    // HAIR :

    glColor3f(0.9f, 0.7f, 0.0f);
    drawFilledCircle(-0.01, 0.45, .019, 2.0f);
    drawFilledCircle(0.13, 0.45, .019, 2.0f);
    drawFilledCircle(0.105f, 0.38f, .05, -1.0f);
    drawFilledCircle(0.015f, 0.38f, .05, -1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(0.9f, 0.7f, 0.0f);
    glVertex2f(0.18f, 0.35f);
    glVertex2f(0.149f, 0.453f);
    glVertex2f(0.06f, 0.36f);
    glVertex2f(-0.061f, 0.35f);
    glVertex2f(-0.031f, 0.453f);
    glVertex2f(0.06f, 0.36f);
    glVertex2f(0.02f, 0.37f);
    glVertex2f(0.06f, 0.30f);
    glVertex2f(0.1f, 0.37f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-0.01, 0.45);
    glVertex2f(0.13, 0.45f);
    glVertex2f(0.13f, 0.35f);
    glVertex2f(-0.01f, 0.35f);
    glEnd();

    //--------------------------------------------

   //The purple circle at the top of the face
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.46, .05, 2.0f);
    //Arrange the ends of the hair
    glColor3f(0.9f, 0.7f, 0.0f);
    drawFilledCircle(0.001, 0.44, .02, 2.0f);
    drawFilledCircle(0.0, 0.45, .02, 2.0f);
    drawFilledCircle(0.12, 0.44, .02, 2.0f);
    drawFilledCircle(0.121, 0.45, .02, 2.0f);

    //----------------------------------------

      //The hat

    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.42, .041, 2.0);
    drawFilledCircle(0.15, 0.56, .02, 2.0);
    glBegin(GL_TRIANGLES);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.078f, 0.59f);
    glVertex2f(0.15f, 0.58f);
    glVertex2f(0.18f, 0.51f);
    glVertex2f(0.17f, 0.57f);
    glVertex2f(0.18f, 0.51f);
    glVertex2f(0.15f, 0.56f);
    glEnd();
    //--------------------------------------------

    glColor3f(0.73f, 0.61f, 0.76f);
    //The mouth
    drawFilledCircle(0.061f, 0.19f, 0.03f, -1.0f);
    //The eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.022f, 0.26f, 0.02, 2.0f);
    drawFilledCircle(0.101f, 0.26f, 0.02, 2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.022, 0.26, .012, 2.0f);
    drawFilledCircle(0.101, 0.26, .012, 2.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.02, 0.26, .005, 2.0f);
    drawFilledCircle(0.1, 0.26, .005, 2.0f);

    //--------------------------------------------

    //Foot
    glBegin(GL_QUADS);
    //left Foot
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.015f, 0.02f);
    glVertex2f(0.06f, 0.02f);
    glVertex2f(0.06f, -0.3f);
    glVertex2f(0.015f, -0.3f);
    //Right foot
    glVertex2f(0.09f, 0.02f);
    glVertex2f(0.135f, 0.02f);
    glVertex2f(0.135f, -0.3f);
    glVertex2f(0.09f, -0.3f);
    glEnd();
    glColor3f(0.3f, 0.2f, 0.0f);
    drawFilledCircle(0.138f, -0.3f, .05, 2.0f);
    drawFilledCircle(0.012f, -0.3f, .05, 2.0f);
    //Hand
    glBegin(GL_QUADS);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(-0.04f, 0.02f);
    glVertex2f(-0.08f, 0.02f);
    glVertex2f(-0.13f, -0.16f);
    glVertex2f(-0.09f, -0.16f);

    glVertex2f(0.185f, 0.02f);
    glVertex2f(0.223f, 0.02f);
    glVertex2f(0.275f, -0.16f);
    glVertex2f(0.233f, -0.16f);
    glEnd();

    drawFilledCircle(-0.13f, -0.15f, .04, 2.0f);
    drawFilledCircle(0.275f, -0.15f, .04, 2.0f);

    //Pants
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.6f, 0.7f);
    glVertex2f(0.015f, 0.02f);
    glVertex2f(0.06f, 0.02f);
    glVertex2f(0.06f, -0.2f);
    glVertex2f(0.015f, -0.2f);

    glVertex2f(0.09f, 0.02f);
    glVertex2f(0.135f, 0.02f);
    glVertex2f(0.135f, -0.2f);
    glVertex2f(0.09f, -0.2f);

    glVertex2f(0.09f, 0.02f);
    glVertex2f(0.06f, 0.02f);
    glVertex2f(0.06f, -0.05f);
    glVertex2f(0.09f, -0.05f);

    glColor3f(0.3f, 0.4f, .5f);
    glVertex2f(0.015f, -0.17f);
    glVertex2f(0.06f, -0.17f);
    glVertex2f(0.06f, -0.2f);
    glVertex2f(0.015f, -0.2f);

    glVertex2f(0.09f, -0.17f);
    glVertex2f(0.135f, -0.17f);
    glVertex2f(0.135f, -0.2f);
    glVertex2f(0.09f, -0.2f);

    //Shoes
    glColor3f(0.3f, 0.2f, 0.0f);
    glVertex2f(0.015f, -0.3f);
    glVertex2f(0.06f, -0.3f);
    glVertex2f(0.06f, -0.23f);
    glVertex2f(0.015f, -0.23f);

    glVertex2f(0.09f, -0.3f);
    glVertex2f(0.135f, -0.3f);
    glVertex2f(0.135f, -0.23f);
    glVertex2f(0.09f, -0.23f);

    //Belt
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.135f, 0.02f);
    glVertex2f(0.015f, 0.02f);
    glVertex2f(0.015f, 0.0f);
    glVertex2f(0.135f, 0.0f);
    glEnd();
    glColor3f(0.8f, 0.6f, 0.3f);
    drawFilledCircle(0.072f, 0.011f, .01, 2.0f);
    glColor3f(0.6f, 0.1f, 0.0f);
    drawHollowCircle(0.072f, 0.011f, .01, 2.0f);




}
void  Kemo_sister1()
{

    //  FACE:
    //The purple part of the face
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.5, .09, 2.0);
    drawFilledCircle(-0.1, 0.09, .07, 2.0);
    drawFilledCircle(0.22, 0.09, .07, 2.0);

    glBegin(GL_POLYGON);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(-0.1f, 0.02f);
    glVertex2f(0.23f, 0.02f);
    glVertex2f(0.06f, 0.3f);
    glVertex2f(0.2915f, 0.09f);
    glVertex2f(0.148f, 0.5208f);
    glVertex2f(-0.028f, 0.5208f);
    glVertex2f(-0.17f, 0.1f);
    glEnd();


    //The Black part of the face
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.01, 0.45, .019, 2.0f);
    drawFilledCircle(0.13, 0.45, .019, 2.0f);
    drawFilledCircle(-0.12, 0.1, .02, 2.0f);
    drawFilledCircle(0.24, 0.1, .02, 2.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.12f, 0.08f);
    glVertex2f(0.24f, 0.08f);
    glVertex2f(0.24f, 0.1f);
    glVertex2f(-0.12f, 0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.030f, 0.45f);
    glVertex2f(-0.138f, 0.1f);
    glVertex2f(0.258f, 0.1f);
    glVertex2f(0.149f, 0.45f);
    glEnd();


    //----------------------------------------------
    // HAIR :
    glColor3f(0.6f, 0.4f, 0.2f);
    drawFilledCircle(-0.01, 0.45, .019, 2.0f);
    drawFilledCircle(0.13, 0.45, .019, 2.0f);
    drawFilledCircle(0.105f, 0.37f, .07, -1.0f);
    drawFilledCircle(0.015f, 0.37f, .07, -1.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(0.18f, 0.35f);
    glVertex2f(0.149f, 0.453f);
    glVertex2f(0.06f, 0.36f);
    glVertex2f(-0.061f, 0.35f);
    glVertex2f(-0.031f, 0.453f);
    glVertex2f(0.06f, 0.36f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.4f, 0.2f);
    glVertex2f(-0.01, 0.45);
    glVertex2f(0.13, 0.45f);
    glVertex2f(0.13f, 0.35f);
    glVertex2f(-0.01f, 0.35f);
    glEnd();
    //----------------------------------------------
    //The purple circle at the top of the face
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.46, .05, 2.0f);
    //Arrange the ends of the hair
    glColor3f(0.6f, 0.4f, 0.2f);
    drawFilledCircle(0.001, 0.44, .02, 2.0f);
    drawFilledCircle(0.0, 0.45, .02, 2.0f);
    drawFilledCircle(0.12, 0.44, .02, 2.0f);
    drawFilledCircle(0.121, 0.45, .02, 2.0f);

    //----------------------------------------

     //The hat
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.42, .041, 2.0);
    drawFilledCircle(0.15, 0.56, .02, 2.0);
    glBegin(GL_TRIANGLES);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.078f, 0.59f);
    glVertex2f(0.15f, 0.58f);
    glVertex2f(0.18f, 0.51f);
    glVertex2f(0.17f, 0.57f);
    glVertex2f(0.18f, 0.51f);
    glVertex2f(0.15f, 0.56f);
    glEnd();
    //--------------------------------------------

    glColor3f(0.73f, 0.61f, 0.76f);
    //The mouth
    drawHollowCircle(0.061f, 0.19f, 0.03f, -1.0f);
    //the eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.022f, 0.26f, 0.02, 2.0f);
    drawFilledCircle(0.101f, 0.26f, 0.02, 2.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.022, 0.26, .012, 2.0f);
    drawFilledCircle(0.101, 0.26, .012, 2.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.02, 0.26, .005, 2.0f);
    drawFilledCircle(0.1, 0.26, .005, 2.0f);
    //--------------------------------------------
    //Al - Fionka

    glBegin(GL_TRIANGLES);

    glColor3f(0.9f, 0.6f, 0.7);
    glVertex2f(0.06f, 0.36f);
    glVertex2f(0.11f, 0.38f);
    glVertex2f(0.11f, 0.34f);

    glVertex2f(0.06f, 0.36f);
    glVertex2f(0.01f, 0.38f);
    glVertex2f(0.01f, 0.34f);
    glEnd();

    glColor3f(0.9f, 0.8f, 0.5f);
    drawFilledCircle(0.06f, 0.36f, .015f, 2.0f);
    drawHollowCircle(0.06f, 0.36f, .015f, 2.0f);
    //--------------------------------------------
    //--------------------------------------------

    //Foot
    glBegin(GL_QUADS);
    //left Foot
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.015f, 0.02f);
    glVertex2f(0.06f, 0.02f);
    glVertex2f(0.06f, -0.3f);
    glVertex2f(0.015f, -0.3f);
    //Right foot
    glVertex2f(0.09f, 0.02f);
    glVertex2f(0.135f, 0.02f);
    glVertex2f(0.135f, -0.3f);
    glVertex2f(0.09f, -0.3f);
    glEnd();
    glColor3f(0.3f, 0.2f, 0.0f);
    drawFilledCircle(0.138f, -0.3f, .05, 2.0f);
    drawFilledCircle(0.012f, -0.3f, .05, 2.0f);
    //Hand
    glBegin(GL_QUADS);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(-0.04f, 0.02f);
    glVertex2f(-0.08f, 0.02f);
    glVertex2f(-0.13f, -0.16f);
    glVertex2f(-0.09f, -0.16f);

    glVertex2f(0.185f, 0.02f);
    glVertex2f(0.223f, 0.02f);
    glVertex2f(0.275f, -0.16f);
    glVertex2f(0.233f, -0.16f);
    glEnd();

    drawFilledCircle(-0.13f, -0.15f, .04, 2.0f);
    drawFilledCircle(0.275f, -0.15f, .04, 2.0f);

    // Skirt
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.6f, 0.7);
    glVertex2f(0.18f, 0.02f);
    glVertex2f(-0.04f, 0.02f);
    glVertex2f(-0.04f, -0.15f);
    glVertex2f(0.18f, -0.15f);
    glEnd();
    drawFilledCircle(0.07f, -0.06f, 0.111, -1.0f);
    drawFilledCircle(0.15f, -0.12f, 0.043, 2.0f);
    drawFilledCircle(-0.01f, -0.12f, 0.043, 2.0f);

    glColor3f(.9f, 0.8f, 0.5f);
    drawFilledCircle(0.13f, -0.09f, .03, -1.0f);
    drawFilledCircle(0.07f, -0.09f, .03, -1.0f);
    drawFilledCircle(0.01f, -0.09f, .03, -1.0f);

    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.8f, 0.5f);
    glVertex2f(0.16f, -0.09f);
    glVertex2f(0.1f, -0.09f);
    glVertex2f(0.1f, 0.02f);
    glVertex2f(0.16f, 0.02f);

    glVertex2f(0.1f, -0.09f);
    glVertex2f(0.04f, -0.09f);
    glVertex2f(0.04f, 0.02f);
    glVertex2f(0.1f, 0.02f);

    glVertex2f(-0.02f, -0.09f);
    glVertex2f(0.04f, -0.09f);
    glVertex2f(0.04f, 0.02f);
    glVertex2f(-0.02f, 0.02f);
    glEnd();


}
void  Kemo_sister2()
{

    //  FACE:
    //The purple part of the face
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.5, .09, 2.0);
    drawFilledCircle(-0.1, 0.09, .07, 2.0);
    drawFilledCircle(0.22, 0.09, .07, 2.0);

    glBegin(GL_POLYGON);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(-0.1f, 0.02f);
    glVertex2f(0.23f, 0.02f);
    glVertex2f(0.06f, 0.3f);
    glVertex2f(0.2915f, 0.09f);
    glVertex2f(0.148f, 0.5208f);
    glVertex2f(-0.028f, 0.5208f);
    glVertex2f(-0.17f, 0.1f);
    glEnd();


    //The white part of the face
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.01, 0.45, .019, 2.0f);
    drawFilledCircle(0.13, 0.45, .019, 2.0f);
    drawFilledCircle(-0.12, 0.1, .02, 2.0f);
    drawFilledCircle(0.24, 0.1, .02, 2.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.12f, 0.08f);
    glVertex2f(0.24f, 0.08f);
    glVertex2f(0.24f, 0.1f);
    glVertex2f(-0.12f, 0.1f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.030f, 0.45f);
    glVertex2f(-0.138f, 0.1f);
    glVertex2f(0.258f, 0.1f);
    glVertex2f(0.149f, 0.45f);
    glEnd();


    //----------------------------------------------
    // HAIR :
    glColor3f(0.3f, 0.2f, 0.0f);
    drawFilledCircle(-0.01, 0.45, .019, 2);
    drawFilledCircle(0.13, 0.45, .019, 2);
    drawFilledCircle(0.0f, 0.35f, .02, 2);
    drawFilledCircle(0.03f, 0.35f, .02, 2);
    drawFilledCircle(0.06f, 0.35f, .02, 2);
    drawFilledCircle(0.09f, 0.35f, .02, 2);
    drawFilledCircle(0.12f, 0.35f, .02, 2);
    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.2f, 0.0f);
    glVertex2f(0.18f, 0.35f);
    glVertex2f(0.149f, 0.453f);
    glVertex2f(0.06f, 0.36f);
    glVertex2f(-0.061f, 0.35f);
    glVertex2f(-0.031f, 0.453f);
    glVertex2f(0.06f, 0.36f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.2f, 0.0f);
    glVertex2f(-0.01, 0.45);
    glVertex2f(0.13, 0.45f);
    glVertex2f(0.13f, 0.35f);
    glVertex2f(-0.01f, 0.35f);
    glEnd();




    //---------------------------------

     //The purple circle at the top of the face
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.46, .05, 2.0f);
    //Arrange the ends of the hair
    glColor3f(0.3f, 0.2f, 0.0f);
    drawFilledCircle(0.001, 0.44, .02, 2.0f);
    drawFilledCircle(0.0, 0.45, .02, 2.0f);
    drawFilledCircle(0.12, 0.44, .02, 2.0f);
    drawFilledCircle(0.121, 0.45, .02, 2.0f);

    //----------------------------------------

     //The hat
    glColor3f(0.52f, 0.39f, 0.72f);
    drawFilledCircle(0.06, 0.42, .041, 2.0);
    drawFilledCircle(0.15, 0.56, .02, 2.0);
    glBegin(GL_TRIANGLES);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.078f, 0.59f);
    glVertex2f(0.15f, 0.58f);
    glVertex2f(0.18f, 0.51f);
    glVertex2f(0.17f, 0.57f);
    glVertex2f(0.18f, 0.51f);
    glVertex2f(0.15f, 0.56f);
    glEnd();
    //--------------------------------------------

    glColor3f(0.73f, 0.61f, 0.76f);
    //The mouth
    drawHollowCircle(0.061f, 0.19f, 0.03f, -1.0f);
    //the eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.022f, 0.26f, 0.02, 2.0f);
    drawFilledCircle(0.101f, 0.26f, 0.02, 2.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.022, 0.26, .012, 2.0f);
    drawFilledCircle(0.101, 0.26, .012, 2.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.02, 0.26, .005, 2.0f);
    drawFilledCircle(0.1, 0.26, .005, 2.0f);
    //--------------------------------------------

    //Foot
    glBegin(GL_QUADS);
    //left Foot
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(0.015f, 0.02f);
    glVertex2f(0.06f, 0.02f);
    glVertex2f(0.06f, -0.3f);
    glVertex2f(0.015f, -0.3f);
    //Right foot
    glVertex2f(0.09f, 0.02f);
    glVertex2f(0.135f, 0.02f);
    glVertex2f(0.135f, -0.3f);
    glVertex2f(0.09f, -0.3f);
    glEnd();
    glColor3f(0.3f, 0.2f, 0.0f);
    drawFilledCircle(0.138f, -0.3f, .05, 2.0f);
    drawFilledCircle(0.012f, -0.3f, .05, 2.0f);
    //Hand
    glBegin(GL_QUADS);
    glColor3f(0.52f, 0.39f, 0.72f);
    glVertex2f(-0.04f, 0.02f);
    glVertex2f(-0.08f, 0.02f);
    glVertex2f(-0.13f, -0.16f);
    glVertex2f(-0.09f, -0.16f);

    glVertex2f(0.185f, 0.02f);
    glVertex2f(0.223f, 0.02f);
    glVertex2f(0.275f, -0.16f);
    glVertex2f(0.233f, -0.16f);
    glEnd();

    drawFilledCircle(-0.13f, -0.15f, .04, 2.0f);
    drawFilledCircle(0.275f, -0.15f, .04, 2.0f);

    // Skirt

    glBegin(GL_QUADS);

    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.9f, 0.6);
    glVertex2f(0.18f, 0.02f);
    glVertex2f(-0.04f, 0.02f);
    glVertex2f(-0.04f, -0.05f);
    glVertex2f(0.18f, -0.05f);

    glColor4f(0.7f, 0.5f, 0.5, 0.8);
    glVertex2f(0.17f, 0.02f);
    glVertex2f(-0.03f, 0.02f);
    glVertex2f(-0.03f, -0.05f);
    glVertex2f(0.17f, -0.05f);


    glColor4f(0.3f, 0.3f, 0.3f, 0.9f);
    glVertex2f(0.015f, -0.3f);
    glVertex2f(0.06f, -0.3f);
    glVertex2f(0.06f, -0.13f);
    glVertex2f(0.015f, -0.13f);

    glVertex2f(0.09f, -0.3f);
    glVertex2f(0.135f, -0.3f);
    glVertex2f(0.135f, -0.13f);
    glVertex2f(0.09f, -0.13f);


    glEnd();


    glColor3f(0.7f, 0.9f, 0.6);
    drawFilledCircle(0.07f, -0.05f, 0.111, -1);
    glColor4f(0.7f, 0.5f, 0.5, 0.5);
    drawFilledCircle(0.07f, -0.05f, 0.1, -1);
}
void corn() {
    //           DRAWING CORN kERNELS        :
    // 1] RIGHT SIDE
    glColor4f(0.9607f, 0.8235f, 0.01568f, 1);
    drawFilledCircle(0.29, 0.53, .05, 2.0f);
    glColor4f(0.8705f, 0.6, 0.13725f, 1);
    drawHollowCircle(0.29, 0.53, .052, 2.0f);
    glColor4f(0.9607f, 0.8235f, 0.01568f, 1);
    drawFilledCircle(0.32, 0.49, .05, 2.0f);
    glColor4f(0.8705f, 0.6, 0.13725f, 1);
    drawHollowCircle(0.32, 0.49, .052, 2.0f);
    glColor4f(0.9607f, 0.8235f, 0.01568f, 1);
    drawFilledCircle(0.33, 0.43, .05, 2.0f);
    glColor4f(0.8705f, 0.6, 0.13725f, 1);
    drawHollowCircle(0.33, 0.43, .052, 2.0f);
    glColor4f(0.9607f, 0.8235f, 0.01568f, 1);
    drawFilledCircle(0.33, 0.38, .05, 2.0f);
    glColor4f(0.8705f, 0.6, 0.13725f, 1);
    drawHollowCircle(0.33, 0.38, .052, 2.0f);
    glColor4f(0.9607f, 0.8235f, 0.01568f, 1);
    drawFilledCircle(0.30, 0.32, .053, 2.0f);
    glColor4f(0.8705f, 0.6, 0.13725f, 1);
    drawHollowCircle(0.30, 0.32, .054, 2.0f);


    // 2] LEFT SIDE
    glColor4f(0.9607f, 0.8235f, 0.01568f, 1);
    drawFilledCircle(0.26, 0.49, .05, 2.0f);
    glColor4f(0.8705f, 0.6, 0.13725f, 1);
    drawHollowCircle(0.26, 0.49, .052, 2.0f);
    glColor4f(0.9607f, 0.8235f, 0.01568f, 1);
    drawFilledCircle(0.25, 0.43, .05, 2.0f);
    glColor4f(0.8705f, 0.6, 0.13725f, 1);
    drawHollowCircle(0.25, 0.43, .052, 2.0f);
    glColor4f(0.9607f, 0.8235f, 0.01568f, 1);
    drawFilledCircle(0.24, 0.38, .05, 2.0f);
    glColor4f(0.8705f, 0.6, 0.13725f, 1);
    drawHollowCircle(0.24, 0.38, .052, 2.0f);
    drawHollowCircle(0.25, 0.32, .054, 2.0f);



    // 3] CENTRAL SIDE
    glColor4f(0.9607f, 0.8235f, 0.01568f, 1);
    drawFilledCircle(0.29, 0.45, .05, 2.0f);
    glColor4f(0.8705f, 0.6, 0.13725f, 1);
    drawHollowCircle(0.29, 0.45, .052, 2.0f);
    glColor4f(0.9607f, 0.8235f, 0.01568f, 1);
    drawFilledCircle(0.28, 0.38, .05, 2.0f);
    glColor4f(0.8705f, 0.6, 0.13725f, 1);
    drawHollowCircle(0.28, 0.38, .052, 2.0f);
    glColor4f(0.9607f, 0.8235f, 0.01568f, 1);
    drawFilledCircle(0.28, 0.32, .053, 2.0f);
    glColor4f(0.8705f, 0.6, 0.13725f, 1);
    drawHollowCircle(0.28, 0.32, .054, 2.0f);


    //             DRAW THE UPPER LEAVES     :

    // 1] RIGHT SIDE
    glBegin(GL_POLYGON);
    glColor4f(0.3215f, 0.5411f, 0.2431f, 1);
    glVertex2f(0.3f, 0.263f);
    glVertex2f(0.3f, 0.25f);
    glVertex2f(0.3f, 0.22f);
    glVertex2f(0.3f, 0.2f);

    glVertex2f(0.31f, 0.29f);
    glVertex2f(0.32f, 0.309f);


    glVertex2f(0.32f, 0.32f);
    glVertex2f(0.35f, 0.33f);
    glVertex2f(0.36f, 0.35f);
    glVertex2f(0.4f, 0.35f);

    glVertex2f(0.41f, 0.34f);
    glVertex2f(0.42f, 0.33f);
    glVertex2f(0.42f, 0.3f);
    glVertex2f(0.42f, 0.39f);



    glVertex2f(0.41f, 0.28f);
    glVertex2f(0.4f, 0.27f);
    glVertex2f(0.39f, 0.26f);
    glVertex2f(0.37f, 0.25f);


    glVertex2f(0.35f, 0.24f);
    glVertex2f(0.34f, 0.23f);
    glVertex2f(0.33f, 0.22f);
    glVertex2f(0.32f, 0.21f);

    glVertex2f(0.31f, 0.2f);

    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(0.3215f, 0.5411f, 0.2431f, 1);

    glVertex2f(0.27f, 0.263f);
    glVertex2f(0.27f, 0.25f);
    glVertex2f(0.27f, 0.22f);
    glVertex2f(0.27f, 0.2f);

    glVertex2f(0.28f, 0.29f);
    glVertex2f(0.29f, 0.309f);


    glVertex2f(0.29f, 0.32f);
    glVertex2f(0.32f, 0.33f);
    glVertex2f(0.33f, 0.35f);
    glVertex2f(0.37f, 0.35f);

    glVertex2f(0.38f, 0.34f);
    glVertex2f(0.39f, 0.33f);
    glVertex2f(0.39f, 0.3f);
    glVertex2f(0.39f, 0.39f);



    glVertex2f(0.38f, 0.28f);
    glVertex2f(0.37f, 0.27f);
    glVertex2f(0.36f, 0.26f);
    glVertex2f(0.34f, 0.25f);


    glVertex2f(0.32f, 0.24f);
    glVertex2f(0.31f, 0.23f);
    glVertex2f(0.30f, 0.22f);
    glVertex2f(0.29f, 0.21f);

    glVertex2f(0.28f, 0.2f);

    glEnd();

    // 2] LEFT SIDE

    glBegin(GL_POLYGON);

    glColor4f(0.3215f, 0.5411f, 0.2431f, 1);

    glVertex2f(0.27f, 0.263f);
    glVertex2f(0.27f, 0.25f);
    glVertex2f(0.27f, 0.22f);
    glVertex2f(0.27f, 0.2f);

    glVertex2f(0.26f, 0.29f);
    glVertex2f(0.25f, 0.309f);


    glVertex2f(0.25f, 0.32f);
    glVertex2f(0.22f, 0.33f);
    glVertex2f(0.21f, 0.35f);
    glVertex2f(0.17f, 0.35f);

    glVertex2f(0.16f, 0.34f);
    glVertex2f(0.15f, 0.33f);
    glVertex2f(0.15f, 0.3f);
    glVertex2f(0.15f, 0.39f);



    glVertex2f(0.16f, 0.28f);
    glVertex2f(0.17f, 0.27f);
    glVertex2f(0.18f, 0.26f);
    glVertex2f(0.20f, 0.25f);


    glVertex2f(0.22f, 0.24f);
    glVertex2f(0.23f, 0.23f);
    glVertex2f(0.24f, 0.22f);
    glVertex2f(0.25f, 0.21f);

    glVertex2f(0.26f, 0.2f);

    glEnd();


    glBegin(GL_POLYGON);

    glColor4f(0.3215f, 0.5411f, 0.2431f, 1);

    glVertex2f(0.31f, 0.263f);
    glVertex2f(0.31f, 0.25f);
    glVertex2f(0.31f, 0.22f);
    glVertex2f(0.31f, 0.2f);

    glVertex2f(0.3f, 0.29f);
    glVertex2f(0.29f, 0.309f);


    glVertex2f(0.29f, 0.32f);
    glVertex2f(0.26f, 0.33f);
    glVertex2f(0.25f, 0.35f);
    glVertex2f(0.21f, 0.35f);

    glVertex2f(0.2f, 0.34f);
    glVertex2f(0.19f, 0.33f);
    glVertex2f(0.19f, 0.3f);
    glVertex2f(0.19f, 0.39f);

    glVertex2f(0.2f, 0.28f);
    glVertex2f(0.21f, 0.27f);
    glVertex2f(0.22f, 0.26f);
    glVertex2f(0.24f, 0.25f);

    glVertex2f(0.26f, 0.24f);
    glVertex2f(0.29f, 0.23f);
    glVertex2f(0.28f, 0.22f);
    glVertex2f(0.29f, 0.21f);

    glVertex2f(0.3f, 0.2f);

    glEnd();



    // BOTTOM COVER OF LEAVES :
    glColor4f(0.3215f, 0.5411f, 0.2431f, 1);

    // DRAWING A CORN STALK   :
    glEnable(GL_LINES);
    glLineWidth(3.0f);

    glBegin(GL_LINES);
    glColor4f(0.3215f, 0.5411f, 0.2431f, 1);

    glVertex2f(0.28f, .23f);
    glVertex2f(0.28f, -0.23f);

    glEnd();
    glLineWidth(1.0f);


    //             DRAW THE LOWER LEAVES     :

  // 1] RIGHT SIDE
    glBegin(GL_POLYGON);
    glColor4f(0.3215f, 0.5411f, 0.2431f, 1);

    glVertex2f(0.28f, 0.063f);
    glVertex2f(0.28f, 0.05f);
    glVertex2f(0.28f, 0.02f);
    glVertex2f(0.28f, 0.0f);

    glVertex2f(0.29f, 0.09f);
    glVertex2f(0.3f, 0.109f);

    glVertex2f(0.3f, 0.12f);
    glVertex2f(0.33f, 0.13f);
    glVertex2f(0.34f, 0.15f);
    glVertex2f(0.38f, 0.15f);

    glVertex2f(0.39f, 0.14f);
    glVertex2f(0.4f, 0.13f);
    glVertex2f(0.4f, 0.1f);
    glVertex2f(0.4f, 0.19f);

    glVertex2f(0.39f, 0.18f);
    glVertex2f(0.38f, 0.07f);
    glVertex2f(0.37f, 0.06f);
    glVertex2f(0.35f, 0.05f);

    glVertex2f(0.33f, 0.04f);
    glVertex2f(0.31f, 0.03f);
    glVertex2f(0.30f, 0.02f);
    glVertex2f(0.29f, 0.01f);

    glVertex2f(0.28f, 0.0f);

    glEnd();


    // 2] LEFT SIDE
    glBegin(GL_POLYGON);

    glColor4f(0.3215f, 0.5411f, 0.2431f, 1);

    glVertex2f(0.3f, 0.063f);
    glVertex2f(0.3f, 0.05f);
    glVertex2f(0.3f, 0.02f);
    glVertex2f(0.3f, 0.0f);

    glVertex2f(0.29f, 0.09f);
    glVertex2f(0.28f, 0.109f);

    glVertex2f(0.28f, 0.12f);
    glVertex2f(0.25f, 0.13f);
    glVertex2f(0.24f, 0.15f);
    glVertex2f(0.20f, 0.15f);

    glVertex2f(0.19f, 0.14f);
    glVertex2f(0.18f, 0.13f);
    glVertex2f(0.18f, 0.1f);
    glVertex2f(0.18f, 0.19f);

    glVertex2f(0.19f, 0.08f);
    glVertex2f(0.2f, 0.07f);
    glVertex2f(0.21f, 0.06f);
    glVertex2f(0.23f, 0.05f);

    glVertex2f(0.25f, 0.04f);
    glVertex2f(0.28f, 0.03f);



    glEnd();

}
void Burrow() {


    //The top layer of the burrow
    glBegin(GL_QUADS);
    glColor3f(0.2549f, 0.1764f, 0.1686f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
    //The second layer of the burrow
    glBegin(GL_POLYGON);
    glColor4f(0.5254f, 0.4196f, 0.3137f, 1.0);
    glVertex2f(-0.65f, -1.0f);
    glVertex2f(-0.7f, -.85f);
    glVertex2f(-0.75f, -.8f);
    glVertex2f(-0.8f, -.8f);
    glVertex2f(-0.85f, -.7f);
    glVertex2f(-.9f, -0.5f);
    glVertex2f(-.9f, -0.4f);
    glVertex2f(-.95f, 0.2f);
    glVertex2f(-0.855f, 0.41f);
    glVertex2f(-0.85f, 0.6f);
    glVertex2f(-0.75f, 0.8f);
    glVertex2f(-0.34f, 0.79f);
    glVertex2f(-0.25f, 0.72f);
    glVertex2f(-0.152f, 0.78f);
    glVertex2f(-0.05f, 0.7f);

    glVertex2f(0.05f, 0.7f);
    glVertex2f(0.152f, 0.78f);
    glVertex2f(0.25f, 0.72f);
    glVertex2f(0.34f, 0.79f);
    glVertex2f(0.75f, 0.8f);
    glVertex2f(0.85f, 0.6f);
    glVertex2f(.95f, 0.2f);
    glVertex2f(.9f, -0.4f);
    glVertex2f(.9f, -0.5f);
    glVertex2f(0.85f, -.7f);
    glVertex2f(0.8f, -.8f);
    glVertex2f(0.75f, -.8f);
    glVertex2f(0.7f, -.85f);
    glVertex2f(0.65f, -1.f);
    glEnd();

    //Boundaries of the second layer of the burrow
    glEnable(GL_LINE_STRIP);
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);
    glColor4f(0.7333f, 0.5921f, 0.4549f, 1);
    glVertex2f(-0.65f, -1.0f);
    glVertex2f(-0.7f, -.85f);
    glVertex2f(-0.75f, -.8f);
    glVertex2f(-0.8f, -.8f);
    glVertex2f(-0.85f, -.7f);
    glVertex2f(-.9f, -0.5f);
    glVertex2f(-.9f, -0.4f);
    glVertex2f(-.95f, 0.2f);
    glVertex2f(-0.855f, 0.41f);
    glVertex2f(-0.85f, 0.6f);
    glVertex2f(-0.75f, 0.8f);
    glVertex2f(-0.34f, 0.79f);
    glVertex2f(-0.25f, 0.72f);
    glVertex2f(-0.152f, 0.78f);
    glVertex2f(-0.05f, 0.7f);

    glVertex2f(0.05f, 0.7f);
    glVertex2f(0.152f, 0.78f);
    glVertex2f(0.25f, 0.72f);
    glVertex2f(0.34f, 0.79f);
    glVertex2f(0.75f, 0.8f);
    glVertex2f(0.85f, 0.6f);
    glVertex2f(0.855f, 0.41f);
    glVertex2f(.95f, 0.2f);
    glVertex2f(.9f, -0.4f);
    glVertex2f(.9f, -0.5f);
    glVertex2f(0.85f, -.7f);
    glVertex2f(0.8f, -.8f);
    glVertex2f(0.75f, -.8f);
    glVertex2f(0.7f, -.85f);
    glVertex2f(0.65f, -1.f);

    glEnd();


    //----------------------------------

   // The third layer of the burrow
    glBegin(GL_POLYGON);
    glColor3f(0.4862, 0.3607, 0.2549);
    glVertex2f(-0.7, -0.6);
    glVertex2f(-0.85, -0.6);
    glVertex2f(-0.8, -0.5);
    glVertex2f(-0.78, -0.42);
    glVertex2f(-0.72, -0.34);
    glVertex2f(-0.67, -0.22);
    glVertex2f(-0.62, -0.14);

    glVertex2f(-0.6, 0.1);
    glVertex2f(-0.46, 0.22);
    glVertex2f(-0.3, 0.35);
    glVertex2f(-0.32, 0.48);
    glVertex2f(-0.1, 0.43);
    glVertex2f(-0.17, 0.44);
    glVertex2f(0.15, 0.43);
    glVertex2f(0.4, 0.35);
    glVertex2f(0.42, 0.23);
    glVertex2f(0.44, 0.18);

    glVertex2f(0.7, -0.13);
    glVertex2f(0.8, -0.4);
    glVertex2f(0.85, -0.6);
    glVertex2f(0.70, -0.6);
    glEnd();
    // Boundaries of the third layer of the burrow
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glColor4f(0.7333f, 0.5921f, 0.4549f, 1);
    glVertex2f(-0.7, -0.6);
    glVertex2f(-0.85, -0.6);
    glVertex2f(-0.8, -0.5);
    glVertex2f(-0.78, -0.42);
    glVertex2f(-0.72, -0.34);
    glVertex2f(-0.67, -0.22);
    glVertex2f(-0.62, -0.14);

    glVertex2f(-0.6, 0.1);
    glVertex2f(-0.46, 0.22);
    glVertex2f(-0.3, 0.35);
    glVertex2f(-0.32, 0.48);
    glVertex2f(-0.1, 0.43);
    glVertex2f(-0.17, 0.44);
    glVertex2f(0.15, 0.43);
    glVertex2f(0.4, 0.35);
    glVertex2f(0.42, 0.23);
    glVertex2f(0.44, 0.18);

    glVertex2f(0.7, -0.13);
    glVertex2f(0.8, -0.4);
    glVertex2f(0.85, -0.6);
    glVertex2f(0.70, -0.6);
    glEnd();




    //-------------------------------------

    // The inner layer of the burrow
    glBegin(GL_POLYGON);
    glColor4f(0.6745f, 0.5490f, 0.4235f, 0.9);
    glVertex2f(-0.35f, -0.3f);
    glVertex2f(-0.65f, -0.9f);
    glColor4f(0.2549f, 0.1764f, 0.1686f, 0.4);
    glVertex2f(-0.65f, -0.4f);
    glVertex2f(-0.653f, -0.21f);
    glVertex2f(-0.6f, -0.2f);
    glVertex2f(-0.559f, -0.19f);
    glVertex2f(-0.557f, -0.1f);
    glVertex2f(-0.553f, 0.0f);
    glVertex2f(-0.458f, 0.02f);
    glVertex2f(-0.4f, 0.11f);
    glVertex2f(-0.3f, 0.32f);
    glVertex2f(-0.15f, 0.4f);
    glVertex2f(-0.1f, 0.4f);
    glVertex2f(0.05f, 0.41f);


    glVertex2f(0.05f, 0.41f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.15f, 0.4f);
    glVertex2f(0.3f, 0.32f);
    glVertex2f(0.4f, 0.11f);
    glVertex2f(0.458f, 0.02f);
    glVertex2f(0.553f, 0.0f);
    glVertex2f(0.557f, -0.1f);
    glVertex2f(0.559f, -0.19f);
    glVertex2f(0.6f, -0.2f);
    glVertex2f(0.653f, -0.21f);
    glVertex2f(0.65f, -0.4f);
    glVertex2f(0.65f, -0.9f);

    glVertex2f(0.35f, -0.3f);
    glVertex2f(-0.35f, -0.3f);
    glEnd();
    //--------------------------------------------
    //Door Boundaries
    glEnable(GL_LINES);
    glLineStipple(3, 0xAAAA);
    glLineWidth(20.0f);

    glColor3f(0.2549f, 0.1764f, 0.1686f);
    drawHollowCircle(0.0f, -0.12f, .36, 1.0f);

    // Detailed lines
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);

    glVertex2f(-0.88, -0.42);
    glVertex2f(-0.82, -0.34);
    glVertex2f(-0.77, -0.22);
    glVertex2f(-0.72, -0.14);

    glVertex2f(-0.7, 0.1);
    glVertex2f(-0.56, 0.22);
    glVertex2f(-0.4, 0.35);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(0.54, 0.18);
    glVertex2f(0.8, -0.13);
    glVertex2f(0.87, -0.4);

    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.1, 0.53);
    glVertex2f(-0.17, 0.54);
    glVertex2f(0.15, 0.53);
    glVertex2f(0.4, 0.45);
    glVertex2f(0.42, 0.43);
    glVertex2f(0.44, 0.38);
    glEnd();
    //-----------------------------------------------
    //The sky
    glColor3f(0.6588f, 0.8392f, 0.9058f);
    drawFilledCircle(0.0f, -0.16f, .37, 1.0f);
    //The clouds
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.0f, 0.02f, .02, 1.0f);
    drawFilledCircle(0.02f, 0.02f, .01, 1.0f);
    drawFilledCircle(-0.02f, 0.02f, .01, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.14f, 0.09f, .02, 1.0f);
    drawFilledCircle(0.12f, 0.09f, .01, 1.0f);
    drawFilledCircle(0.16f, 0.09f, .01, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.16f, -0.02f, .02, 1.0f);
    drawFilledCircle(0.14f, -0.02f, .01, 1.0f);
    drawFilledCircle(0.18f, -0.02f, .01, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.14f, 0.08f, .02, 1.0f);
    drawFilledCircle(-0.12f, 0.08f, .01, 1.0f);
    drawFilledCircle(-0.16f, 0.08f, .01, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.16f, -0.03f, .02, 1.0f);
    drawFilledCircle(-0.14f, -0.03f, .01, 1.0f);
    drawFilledCircle(-0.18f, -0.03f, .01, 1.0f);

    //Mountains
    glBegin(GL_POLYGON);
    glColor4f(0.7803f, 0.8039f, 0.7607f, 1);
    glVertex2f(-0.37f, -0.18f);
    glVertex2f(-0.34f, -0.1f);
    glVertex2f(-0.3f, -0.18f);
    glVertex2f(-0.22f, -0.1f);
    glVertex2f(-0.18f, -0.18f);
    glVertex2f(-0.1f, -0.1f);
    glVertex2f(-0.04f, -0.18f);
    glVertex2f(0.02f, -0.1f);
    glVertex2f(0.1f, -0.18f);
    glVertex2f(0.16f, -0.1f);
    glVertex2f(0.22f, -0.18f);
    glVertex2f(0.26f, -0.1f);
    glVertex2f(0.3f, -0.18f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(0.6627f, 0.6980f, 0.6666f, 1);
    glVertex2f(-0.37f, -0.18f);
    glVertex2f(-0.34f, -0.14f);
    glVertex2f(-0.3f, -0.18f);
    glVertex2f(-0.22f, -0.14f);
    glVertex2f(-0.18f, -0.18f);
    glVertex2f(-0.1f, -0.14f);
    glVertex2f(-0.04f, -0.18f);
    glVertex2f(0.02f, -0.14f);
    glVertex2f(0.1f, -0.18f);
    glVertex2f(0.16f, -0.14f);
    glVertex2f(0.22f, -0.18f);
    glVertex2f(0.26f, -0.14f);
    glVertex2f(0.3f, -0.18f);

    glEnd();
    //The lawn
    glBegin(GL_QUADS);
    glColor4f(0.7019f, 0.8196f, 0.4039f, 1);
    glVertex2f(-0.37f, -0.16f);
    glVertex2f(0.37f, -0.16f);
    glVertex2f(0.35f, -0.3f);
    glVertex2f(-0.35f, -0.3f);
    glEnd();
    //The Road
    glBegin(GL_QUADS);
    glColor3f(0.2549f, 0.1764f, 0.1686f);
    glVertex2f(-0.35f, -0.3f);
    glVertex2f(0.35f, -0.3f);
    glColor3f(0.58f, 0.506f, 0.388f);
    glVertex2f(0.78f, -1.2f);
    glVertex2f(-0.8f, -1.2f);
    glEnd();


    //Trees

    glBegin(GL_POLYGON);
    glColor4f(0.2313f, 0.4901f, 0.1490f, 1);
    glVertex2f(-0.35f, -0.3f);
    glVertex2f(-0.36f, -0.22f);
    glVertex2f(-0.24f, -0.26f);
    glVertex2f(-0.28f, -0.22f);
    glVertex2f(-0.24f, -0.3f);

    glVertex2f(-0.28f, -0.26f);
    glVertex2f(-0.25f, -0.22f);
    glVertex2f(-0.22f, -0.26f);
    glVertex2f(-0.22f, -0.24f);
    glVertex2f(-0.18f, -0.26f);
    glVertex2f(-0.18f, -0.22f);
    glVertex2f(-0.14f, -0.26f);
    glVertex2f(-0.12f, -0.22f);
    glVertex2f(-0.06f, -0.3f);

    glEnd();


    // Details of the sides of the burrow

    glBegin(GL_POLYGON);
    glColor4f(0.4352f, 0.3450f, 0.2509f, 0.7);

    glVertex2f(-0.35f, 0.51f);
    glVertex2f(-0.45f, 0.51f);
    glVertex2f(-0.55f, 0.35f);
    glVertex2f(-0.565f, 0.35f);
    glVertex2f(-0.75f, 0.1f);

    glColor4f(0.2549f, 0.1764f, 0.1686f, 0.2);
    glVertex2f(-.95f, 0.2f);
    glVertex2f(-0.855f, 0.41f);
    glVertex2f(-0.85f, 0.6f);
    glVertex2f(-0.75f, 0.8f);
    glVertex2f(-0.34f, 0.79f);
    glVertex2f(-0.25f, 0.72f);
    glVertex2f(-0.152f, 0.78f);
    glVertex2f(-0.05f, 0.7f);
    glEnd();



    glBegin(GL_POLYGON);
    glColor4f(0.4352f, 0.3450f, 0.2509f, 0.7);
    glVertex2f(0.35f, 0.51f);
    glVertex2f(0.45f, 0.51f);
    glVertex2f(0.55f, 0.35f);
    glVertex2f(0.565f, 0.35f);
    glVertex2f(0.75f, 0.1f);

    glColor4f(0.2549f, 0.1764f, 0.1686f, 0.2);
    glVertex2f(.95f, 0.2f);
    glVertex2f(0.855f, 0.41f);
    glVertex2f(0.85f, 0.6f);
    glVertex2f(0.75f, 0.8f);
    glVertex2f(0.34f, 0.79f);
    glVertex2f(0.25f, 0.72f);
    glVertex2f(0.152f, 0.78f);
    glVertex2f(0.05f, 0.7f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor4f(0.4352f, 0.3450f, 0.2509f, 0.7);
    glVertex2f(-0.96f, 0.3f);
    glVertex2f(-0.965f, 0.51f);
    glVertex2f(-0.96f, 0.7f);
    glVertex2f(-0.76f, .9f);
    glVertex2f(-0.35f, 0.89f);
    glVertex2f(-0.26f, 0.82f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor4f(0.4352f, 0.3450f, 0.2509f, 0.7);
    glVertex2f(0.96f, 0.3f);
    glVertex2f(0.965f, 0.51f);
    glVertex2f(0.96f, 0.7f);
    glVertex2f(0.76f, .9f);
    glVertex2f(0.35f, 0.89f);
    glVertex2f(0.26f, 0.82f);

    glEnd();

    ///------------------------------------------------


    //rock
    glBegin(GL_POLYGON);
    glColor4f(0.7333f, 0.5921f, 0.4549f, 0.2);
    glVertex2f(-0.2, -0.43);
    glVertex2f(-0.15, -0.32);
    glVertex2f(-0.0, -0.31);
    glVertex2f(0.06, -0.34);
    glVertex2f(0.1, -0.45);
    glVertex2f(-0.12, -0.44);
    glEnd();


    glBegin(GL_POLYGON);
    glColor4f(0.7333f, 0.5921f, 0.4549f, 0.2);
    glVertex2f(-0.2, -0.61);
    glVertex2f(-0.15, -0.49);
    glVertex2f(-0.0, -0.48);
    glVertex2f(0.06, -0.51);
    glVertex2f(0.1, -0.62);
    glVertex2f(-0.12, -0.61);
    glEnd();


    glBegin(GL_POLYGON);
    glColor4f(0.7333f, 0.5921f, 0.4549f, 0.2);
    glVertex2f(-0.2, -0.81);
    glVertex2f(-0.15, -0.69);
    glVertex2f(-0.0, -0.68);
    glVertex2f(0.06, -0.71);
    glVertex2f(0.1, -0.82);
    glVertex2f(-0.12, -0.81);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(0.7333f, 0.5921f, 0.4549f, 0.2);
    glVertex2f(-0.2, -1.0);
    glVertex2f(-0.15, -0.89);
    glVertex2f(-0.0, -0.88);
    glVertex2f(0.06, -0.91);
    glVertex2f(0.1, -1.02);
    glVertex2f(-0.12, -1.01);
    glEnd();



    glEnable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    //---------------------------------------

    //corn
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(0.7, -1.25, 0.0);
    corn();
    glPopMatrix();


    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(1.0, -1.25, 0.0);
    corn();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(1.3, -1.25, 0.0);
    corn();
    glPopMatrix();



}
void cloudO() {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.0f, 0.02f, .02, 1.0f);
    drawFilledCircle(0.02f, 0.02f, .01, 1.0f);
    drawFilledCircle(-0.02f, 0.02f, .01, 1.0f);


}
void cloudO2() {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.16f, -0.03f, .02, 1.0f);
    drawFilledCircle(-0.14f, -0.03f, .01, 1.0f);
    drawFilledCircle(-0.18f, -0.03f, .01, 1.0f);
}

void RoadO() {
    //The path separating the corn seedlings
    glBegin(GL_QUADS);
    glColor3f(0.8823f, 0.7882f, 0.4705f);
    glVertex2f(-0.1f, -1.0f);
    glColor3f(0.7372f, 0.5764f, 0.1921f);
    glVertex2f(0.1f, -1.0f);
    glColor3f(0.7372f, 0.5764f, 0.1921f);
    glVertex2f(0.3f, 0.38f);
    glColor3f(0.8823f, 0.7882f, 0.4705f);
    glVertex2f(-0.3f, 0.38f);
    glEnd();
    //Grass Boundaries
    glLineWidth(13.0f);
    glColor4f(0.6745f, 0.7411f, 0.1098f, 1);
    drawHollowCircle(0.0, -1.0, 1.4, 1.0);
    glLineWidth(1.0f);
}
void SunO() {

    glColor4f(0.9843f, 0.7882f, 0.3490f, 1);
    drawFilledCircle(0.0, 0.5, 0.2, 2.0);
    glColor4f(0.9882f, 0.8314f, 0.4549f, 0.8);
    drawFilledCircle(0.0, 0.5, 0.18, 2.0);
    glColor4f(0.9882f, 0.8509f, 0.5333, 0.9);
    drawFilledCircle(0.0, 0.5, 0.13, 2.0);

}
void couldO() {


    glColor3f(1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.16f, 0.7f, .08, 2.0f);
    drawFilledCircle(0.1f, 0.7f, .06, 2.0f);
    drawFilledCircle(0.22f, 0.7f, .06, 2.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.14f, 0.8f, .08, 2.0f);
    drawFilledCircle(-0.08f, 0.8f, .06, 2.0f);
    drawFilledCircle(-0.2f, 0.8f, .06, 2.0f);

}
void Kimo_from_behind()
{

    glBegin(GL_QUADS); //(B-FEET & PUR-ARMS))

    glColor4f(0.13f, 0.05f, 0.19f, 1);
    //RIGHT-FEET
    glVertex2f(0.04, -0.4);   //right-up
    glVertex2f(0.005, -0.4);  //left-up
    glVertex2f(0.005, -0.7); //left-down
    glVertex2f(0.04, -0.7);  //right-down
    //LEFT-FEET
    glVertex2f(-0.005, -0.4);   //right-up
    glVertex2f(-0.04, -0.4);  //left-up
    glVertex2f(-0.04, -0.7); //left-down
    glVertex2f(-0.005, -0.7);  //right-down
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    //RIGHT-ARM
    glVertex2f(0.03, -0.22);   //right-up
    glVertex2f(0.0, -0.25);  //left-up
    glVertex2f(0.20, -0.60); //left-down
    glVertex2f(0.23, -0.57);  //right-down
    //LEFT-ARM
    glVertex2f(-0.03, -0.22);   //right-up
    glVertex2f(0.0, -0.25);  //left-up
    glVertex2f(-0.20, -0.60); //left-down
    glVertex2f(-0.23, -0.57);  //right-down
    glEnd();

    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0, 0, 0.15, 2);        //up
    drawFilledCircle(-0.20, -0.3, 0.10, 2); //left
    drawFilledCircle(0.20, -0.3, 0.10, 2);  //right
    // ------------------------------------------------------------------
    glBegin(GL_TRIANGLES); //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f); //BIG
    //big-right
    glVertex2f(0.14f, 0.05f);
    glVertex2f(0.0f, -0.25f); //center
    glVertex2f(0.286f, -0.25f);
    //big-left
    glVertex2f(-0.14f, 0.05f);
    glVertex2f(0.0f, -0.25f); //center
    glVertex2f(-0.286f, -0.25f);
    //big-down
    glVertex2f(-0.20f, -0.40f);
    glVertex2f(0.0f, 0.0f); //center
    glVertex2f(0.20f, -0.40f);
    //right-up-tail
    glVertex2f(0.20, 0.07);
    glVertex2f(0.14, 0.03);
    glVertex2f(0.22, 0.0); //tail
    //left-up-head
    glVertex2f(0.16, 0.11);
    glVertex2f(0.02, 0.148); //head
    glVertex2f(0.14, 0.03);
    glEnd();
    // ------------------------------------------------------------------
    glBegin(GL_TRIANGLES); //(PUR-CLOTHES)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    glVertex2f(0.1f, -0.58f); //right
    glVertex2f(-0.1f, -0.58f); //left

    glColor4f(0.12f, 0.0f, 0.32f, 1.0f);
    glVertex2f(0.0f, -0.25f); //center

    glEnd();
    // ------------------------------------------------------------------
    // drawing half filled circle (B-SHOES)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.04, -0.7, 0.035, 1.0);
    drawFilledCircle(-0.04, -0.7, 0.035, 1.0);
    // ------------------------------------------------------------------
    // drawing half filled circle (B-HANDS)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.215, -0.585, 0.035, 2); //midpoint formula = (x1 + x2)/2, (y1 + y2)/2.
    drawFilledCircle(-0.215, -0.585, 0.035, 2);
    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0.0, 0.02, 0.07, 2);
    drawFilledCircle(0.16, 0.07, 0.04, 2);
    //-----------------------------------------------------------------------
}
void Kemo_PUR_CLOTHES() {
    glBegin(GL_TRIANGLES); //(PUR-CLOTHES)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    glVertex2f(0.1f, -0.58f); //right
    glVertex2f(-0.1f, -0.58f); //left

    glColor4f(0.12f, 0.0f, 0.32f, 1.0f);
    glVertex2f(0.0f, -0.25f); //center
    glEnd();
}
void KemoHands_RIGHT_ARM() {
    //RIGHT-ARM
    glBegin(GL_QUADS);
    glColor4f(0.12f, 0.0f, 0.32f, 1.0f);
    glVertex2f(0.03, -0.27);   //right-up
    glVertex2f(0.0, -0.30);  //left-up
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    glVertex2f(0.20, -0.60); //left-down
    glVertex2f(0.23, -0.57);  //right-down
    glEnd();
}
void KemoHands_LEFT_ARM() {
    //LEFT-ARM
    glBegin(GL_QUADS);
    glColor4f(0.12f, 0.0f, 0.32f, 1.0f);
    glVertex2f(-0.03, -0.27);   //right-up
    glVertex2f(0.0, -0.30);  //left-up
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    glVertex2f(-0.20, -0.60); //left-down
    glVertex2f(-0.23, -0.57);  //right-down
    glEnd();
}
void KemoHands_RIGHT_HAND() {
    // drawing half filled circle (B-HANDS)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.215, -0.585, 0.035, 2); //right
}
void KemoHands_LEFT_HAND() {
    // drawing half filled circle (B-HANDS)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(-0.215, -0.585, 0.035, 2);//left
}
void Kimo_from_behind2()
{
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(B-FEET & PUR-ARMS))
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    //RIGHT-FEET
    glVertex2f(0.04, -0.4);   //right-up
    glVertex2f(0.005, -0.4);  //left-up
    glVertex2f(0.005, -0.7); //left-down
    glVertex2f(0.04, -0.7);  //right-down
    //LEFT-FEET
    glVertex2f(-0.005, -0.4);   //right-up
    glVertex2f(-0.04, -0.4);  //left-up
    glVertex2f(-0.04, -0.7); //left-down
    glVertex2f(-0.005, -0.7);  //right-down
    glEnd();
    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0, 0, 0.15, 2);        //up
    drawFilledCircle(-0.20, -0.3, 0.10, 2); //left
    drawFilledCircle(0.20, -0.3, 0.10, 2);  //right
    // ------------------------------------------------------------------
    glBegin(GL_TRIANGLES); //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f); //BIG
    //big-right
    glVertex2f(0.14f, 0.05f);
    glVertex2f(0.0f, -0.25f); //center
    glVertex2f(0.286f, -0.25f);
    //big-left
    glVertex2f(-0.14f, 0.05f);
    glVertex2f(0.0f, -0.25f); //center
    glVertex2f(-0.286f, -0.25f);
    //big-down
    glVertex2f(-0.20f, -0.40f);
    glVertex2f(0.0f, 0.0f); //center
    glVertex2f(0.20f, -0.40f);
    //right-up-tail
    glVertex2f(-0.20, 0.07);
    glVertex2f(-0.14, 0.03);
    glColor4f(0.33f, 0.25f, 0.39f, 1);
    glVertex2f(-0.22, 0.0); //tail
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    //left-up-head
    glVertex2f(-0.16, 0.11);
    glVertex2f(-0.02, 0.148); //head
    glVertex2f(-0.14, 0.03);
    glEnd();
    // ------------------------------------------------------------------
    // drawing half filled circle (B-SHOES)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.04, -0.7, 0.035, 1);
    drawFilledCircle(-0.04, -0.7, 0.035, 1);
    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0.0, 0.02, 0.15, 2);
    drawFilledCircle(-0.16, 0.07, 0.04, 2);

    Kemo_PUR_CLOTHES();
}
void Kemo()
{
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(B-FEET & PUR-ARMS))
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    //RIGHT-FEET
    glVertex2f(0.04, -0.4);   //right-up
    glVertex2f(0.005, -0.4);  //left-up
    glVertex2f(0.005, -0.7); //left-down
    glVertex2f(0.04, -0.7);  //right-down
    //LEFT-FEET
    glVertex2f(-0.005, -0.4);   //right-up
    glVertex2f(-0.04, -0.4);  //left-up
    glVertex2f(-0.04, -0.7); //left-down
    glVertex2f(-0.005, -0.7);  //right-down
    glEnd();
    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0, 0, 0.15, 2);        //up
    drawFilledCircle(-0.20, -0.3, 0.10, 2); //left
    drawFilledCircle(0.20, -0.3, 0.10, 2);  //right
    // ------------------------------------------------------------------
    glBegin(GL_TRIANGLES); //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f); //BIG
    //big-right
    glVertex2f(0.14f, 0.05f);
    glVertex2f(0.0f, -0.25f); //center
    glVertex2f(0.286f, -0.25f);
    //big-left
    glVertex2f(-0.14f, 0.05f);
    glVertex2f(0.0f, -0.25f); //center
    glVertex2f(-0.286f, -0.25f);
    //big-down
    glVertex2f(-0.20f, -0.40f);
    glVertex2f(0.0f, 0.0f); //center
    glVertex2f(0.20f, -0.40f);
    //right-up-tail
    glVertex2f(-0.20, 0.07);
    glVertex2f(-0.14, 0.03);
    glColor4f(0.33f, 0.25f, 0.39f, 1);
    glVertex2f(-0.22, 0.0); //tail
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    //left-up-head
    glVertex2f(-0.16, 0.11);
    glVertex2f(-0.02, 0.148); //head
    glVertex2f(-0.14, 0.03);
    glEnd();
    // ------------------------------------------------------------------
    // drawing half filled circle (B-SHOES)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.04, -0.7, 0.035, 1);
    drawFilledCircle(-0.04, -0.7, 0.035, 1);
    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0.0, 0.02, 0.15, 2);
    drawFilledCircle(-0.16, 0.07, 0.04, 2);

    Kemo_PUR_CLOTHES();
}
void KemoFromTheSide()
{
    // ------------------------------------------------------------------
    glBegin(GL_TRIANGLES); //(PUR-CLOTHES)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    glVertex2f(-0.05f, -0.58f); //right
    glVertex2f(-0.2f, -0.58f); //left

    glColor4f(0.12f, 0.0f, 0.32f, 1.0f);
    glVertex2f(0.0f, -0.25f); //center

    glEnd();
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(B-FEET & PUR-ARMS))

    glColor4f(0.13f, 0.05f, 0.19f, 1);

    //RIGHT-FEET
    glVertex2f(0.015, -0.4);   //right-up
    glVertex2f(-0.02, -0.4);  //left-up
    glVertex2f(0.044, -0.567);  //left-up
    glVertex2f(0.085, -0.56);   //right-up

    glVertex2f(0.044, -0.567);  //left-up
    glVertex2f(0.085, -0.56);   //right-up
    glVertex2f(0.055, -0.68);  //right-down
    glVertex2f(0.019, -0.68); //left-down

    //LEFT-FEET
    glVertex2f(-0.005, -0.4);   //right-up
    glVertex2f(-0.05, -0.4);  //left-up
    glVertex2f(-0.026, -0.567);  //left-up
    glVertex2f(0.01, -0.56);   //right-up

    glVertex2f(-0.026, -0.567);  //left-up
    glVertex2f(0.01, -0.56);   //right-up
    glVertex2f(-0.0248, -0.7);  //right-down
    glVertex2f(-0.065, -0.7); //left-down



    //RIGHT-ARM
    glColor4f(0.12f, 0.0f, 0.32f, 1.0f);
    glVertex2f(-0.1, -0.40);   //right-up
    glVertex2f(-0.1, -0.35);  //left-up
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    glVertex2f(0.25, -0.15); //left-down
    glVertex2f(0.25, -0.20);  //right-down

    //LEFT-ARM
    glColor4f(0.12f, 0.0f, 0.32f, 1.0f);
    glVertex2f(-0.1, -0.40);   //right-up
    glVertex2f(-0.1, -0.35);  //left-up
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    glVertex2f(0.3, -0.30); //left-down
    glVertex2f(0.3, -0.35);  //right-down
    glEnd();
    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(-0.056, 0.04, 0.08, 2); //up
    drawFilledCircle(-0.25, -0.3, 0.10, 2); //left
    //    drawFilledCircle(0.20, -0.3, 0.10);  //right
        // ------------------------------------------------------------------
    glBegin(GL_TRIANGLES); //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f); //BIG
    //big-left
    glVertex2f(-0.14f, 0.05f);
    glVertex2f(0.0f, -0.25f); //center
    glVertex2f(-0.336f, -0.25f);
    //big-down
    glVertex2f(-0.25f, -0.40f);
    glVertex2f(0.0f, 0.0f); //center
    glVertex2f(0.02f, -0.40f);
    //    right-up-tail
    glVertex2f(-0.20, 0.07);
    glVertex2f(-0.14, 0.03);
    glColor4f(0.33f, 0.25f, 0.39f, 1);
    glVertex2f(-0.23, 0.0); //tail
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    //left-up-head
    glVertex2f(-0.16, 0.11);
    glVertex2f(-0.02, 0.12); //head
    glVertex2f(-0.14, 0.03);
    glEnd();

    // ------------------------------------------------------------------
    // drawing half filled circle (B-SHOES)
    glColor4f(0.26f, 0.18f, 0.32f, 1);
    drawFilledCircle(-0.0248, -0.7, 0.039, 1);
    drawFilledCircle(0.065, -0.68, 0.039, 1);
    // ------------------------------------------------------------------
    // drawing half filled circle (B-HANDS)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.3, -0.325, 0.035, 2);
    drawFilledCircle(0.25, -0.175, 0.035, 2);
    // ------------------------------------------------------------------
    // drawing the filled circle //(B-FACE)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(-0.09, -0.02, 0.03, 2); //left-up
    drawFilledCircle(-0.25, -0.3, 0.05, 2);  //left-down
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(B-FACE)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.0, -0.02);  //right-up
    glVertex2f(-0.09, -0.02); //left-up
    glVertex2f(-0.25, -0.35);  //left-down
    glVertex2f(0.01, -0.35);   //right-down

    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.0, -0.02);  //right-up
    glVertex2f(-0.12, -0.02); //left-up
    glVertex2f(-0.3, -0.3);  //left-down
    glVertex2f(0.01, -0.3);   //right-down
    glEnd();
    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(-0.05, 0.02, 0.05, 2);
    drawFilledCircle(-0.16, 0.07, 0.04, 2);
    // ------------------------------------------------------------------
    // drawing the filled circle (MOUTH)
    glColor4f(0.73f, 0.61f, 0.76f, 1);
    drawFilledCircle(-0.025, -0.25, 0.04, 2);
    glBegin(GL_QUADS);
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(-0.001, -0.2);  //right-up
    glVertex2f(-0.09, -0.2); //left-up
    glVertex2f(-0.09, -0.25);  //left-down
    glVertex2f(-0.001, -0.25);   //right-down
    glEnd();
    // ------------------------------------------------------------------
    // drawing the filled circle (EYES)
    glColor4f(1.0f, 1.0f, 1.0f, 1); //white eyes
    drawFilledCircle(-0.05, -0.16, 0.06, 2);

    glColor4f(0.26f, 0.18f, 0.32f, 1); //black eyes
    drawFilledCircle(-0.04, -0.15, 0.033, 2);

    glColor4f(1.0f, 1.0f, 1.0f, 1); //white shine eyes
    drawFilledCircle(-0.05, -0.15, 0.005, 2);
    drawFilledCircle(-0.03, -0.16, 0.01, 2);
    // ------------------------------------------------------------------
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    glVertex2f(0.005, 0.01);
    glVertex2f(0.005, -0.35);
    glEnd();
}
void cloudM() {
    //cloud
    glLineWidth(1.0);
    glColor3f(1.0, 1.0, 1.0);
    drawFilledCircle(-0.6498515626162, 0.6668802394198, 0.2, 2);
    drawFilledCircle(-0.4576896959081, 0.6446299180115, 0.18, 2);
    drawFilledCircle(-0.3828477057165, 0.4706728597283, 0.16, 2);
    drawFilledCircle(-0.530508929608, 0.3796488176035, 0.13, 2);
    drawFilledCircle(-0.6822156664829, 0.3958308695368, 0.11, 2);
    drawFilledCircle(-0.7732397086078, 0.4949459376283, 0.12, 2);
    //RIGHT EYE
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.5030961485909, 0.5610530759826);
    glVertex2f(-0.492931656624, 0.5523833622462);
    glVertex2f(-0.4824682090111, 0.548197983201);
    glVertex2f(-0.471406850106, 0.5478990275549);
    glVertex2f(-0.4591496686165, 0.5505896283697);
    glVertex2f(-0.4506844826352, 0.555472085257);
    glVertex2f(-0.4436039750201, 0.5616509872748);
    glVertex2f(-0.436130083868, 0.5700217453652);
    glEnd();
    //RIGHT EYELASHES
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-0.492931656624, 0.5523833622462);
    glVertex2f(-0.5014359038422, 0.543482672191);
    glVertex2f(-0.4824682090111, 0.548197983201);
    glVertex2f(-0.4859524624713, 0.5336916725006);
    glVertex2f(-0.471406850106, 0.5478990275549);
    glVertex2f(-0.4713798117693, 0.5355132538384);
    glVertex2f(-0.4591496686165, 0.5505896283697);
    glVertex2f(-0.4563517657329, 0.5391564165139);
    glVertex2f(-0.4506844826352, 0.555472085257);
    glVertex2f(-0.4422345103653, 0.5471258348665);
    glVertex2f(-0.4436039750201, 0.5616509872748);
    glVertex2f(-0.433581999011, 0.5587384158947);
    glEnd();
    //cloud left eye
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.6194992390173, 0.5645203004541);
    glVertex2f(-0.6294950510313, 0.555660376169);
    glVertex2f(-0.6394908630453, 0.5513440027993);
    glVertex2f(-0.6508497403339, 0.550662470162);
    glVertex2f(-0.6633445053514, 0.5538429558028);
    glVertex2f(-0.6719772520908, 0.5592952169013);
    glVertex2f(-0.6776566907351, 0.5638387678168);
    glVertex2f(-0.6826545967421, 0.5697453840069);
    glVertex2f(-0.6848112684173, 0.5724585938753);
    glEnd();
    //LEFT EYELASHES
    glBegin(GL_LINES);
    glVertex2f(-0.6294950510313, 0.555660376169);
    glVertex2f(-0.6213793395091, 0.5461904066827);
    glVertex2f(-0.6394908630453, 0.5513440027993);
    glVertex2f(-0.6362324846516, 0.5375798877595);
    glVertex2f(-0.6508497403339, 0.550662470162);
    glVertex2f(-0.6504398408748, 0.5341356801902);
    glVertex2f(-0.6633445053514, 0.5538429558028);
    glVertex2f(-0.6665845638557, 0.5375798877595);
    glVertex2f(-0.6719772520908, 0.5592952169013);
    glVertex2f(-0.6827292868366, 0.5472667215481);
    glVertex2f(-0.6776566907351, 0.5638387678168);
    glVertex2f(-0.6906940168406, 0.5591061850674);
    glEnd();

    //MOUTH
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.602324521769, 0.4974603193862);
    glVertex2f(-0.5951428046164, 0.4864750597975);
    glVertex2f(-0.584964273662, 0.4784269190429);
    glVertex2f(-0.5733654825744, 0.4734560085768);
    glVertex2f(-0.5622401115312, 0.4717990384214);
    glVertex2f(-0.5468539600885, 0.4741661386434);
    glVertex2f(-0.5347817489565, 0.481030729287);
    glVertex2f(-0.5274437382684, 0.4883687399751);
    glVertex2f(-0.5222361177801, 0.4968903007741);
    glEnd();
    //CHEEKS
    glColor3f(0.992, 0.776, 0.784);
    drawFilledCircle(-0.4196958216639, 0.4968473167704, 0.02, 2);
    drawFilledCircle(-0.7043258734122, 0.4977789544584, 0.02, 2);
}
void cloudM1() {
    // drawing the filled circle (white cloud)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.39, 0.6, 0.07, 2);
    drawFilledCircle(-0.8, 0.6, 0.12, 2);
    drawFilledCircle(-0.65, 0.65, 0.15, 2); //the biggest circle
    drawFilledCircle(-0.5, 0.6, 0.12, 2);
    drawFilledCircle(-0.91, 0.6, 0.07, 2);
}
void cloudM2() {
    // drawing the filled circle (white cloud)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.24, 0.84, 0.03, 2);
    drawFilledCircle(0.135, 0.84, 0.08, 2);
    drawFilledCircle(-0.01, 0.88, 0.12, 2); //the biggest circle
    drawFilledCircle(-0.155, 0.84, 0.08, 2);
    drawFilledCircle(0.22, 0.84, 0.03, 2);
}
void TreeWood() {
    glColor3f(0.7f, 0.4f, 0.3f);

    glBegin(GL_POLYGON);
    glVertex2f(0.35, -1.0); // c
    glVertex2f(0.4, -0.97); // D
    glVertex2f(0.45, -0.95); // E
    glVertex2f(0.5, -0.90); // a
    glVertex2f(0.55, -0.85); // F
    glVertex2f(0.6, -0.8);  // G

    glVertex2f(0.69, -0.935);
    glVertex2f(0.65, -0.940);
    glVertex2f(0.63, -0.950); //
    glVertex2f(0.6, -0.952);
    glVertex2f(0.55, -0.955);
    glVertex2f(0.54, -0.958);
    glVertex2f(0.52, -0.9585);
    glVertex2f(0.5, -0.959);
    glVertex2f(0.48, -0.9595);
    glVertex2f(0.48, -0.975);
    glVertex2f(0.44, -0.99);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.6, -0.8);  // G
    glVertex2f(0.65, -0.65); // H
    glVertex2f(0.85, -0.92);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.6, -0.8);  // G
    glVertex2f(0.55, -0.85); // F
    glVertex2f(0.84, -0.925); // I3
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.66, -0.45); // K
    glVertex2f(0.55, -0.44); // L
    glVertex2f(0.5, -0.4); // M
    glVertex2f(0.4, -0.4); // N
    glVertex2f(0.48, -0.38); // O
    glVertex2f(0.55, -0.39); // b
    glVertex2f(0.66, -0.39); // P
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.654, -0.36); // R

    glVertex2f(0.58, -0.28); // S
    glVertex2f(0.5, -0.25); // T
    glVertex2f(0.44, -0.248); // U
    glVertex2f(0.38, -0.16); // V
    glVertex2f(0.46, -0.16); // W
    glVertex2f(0.5, -0.2); // Z
    glVertex2f(0.55, -0.2); // A1
    glVertex2f(0.6, -0.215); // B2
    glVertex2f(0.65, -0.22); // B2
    glVertex2f(0.7, -0.225); // B2
    glEnd();
    glBegin(GL_POLYGON);

    glVertex2f(0.66, -0.154); // I1
    glVertex2f(0.63, -0.05); // J1
    glVertex2f(0.6, -0.0);    // K1
    glVertex2f(0.658, 0.05); // L1
    glVertex2f(0.74, -0.155);// M1
    glVertex2f(0.78, -0.02); // N1
    glVertex2f(0.805, 0.02); // O1
    glVertex2f(0.81, 0.075); // Q1
    glVertex2f(0.88, 0.052);   // R1
    glVertex2f(0.86, -0.048); // S1
    glVertex2f(0.85, -0.048); // T1
    glVertex2f(0.85, -0.152); // U1
    glVertex2f(0.86, -0.158); // V1
    glVertex2f(0.86, -0.1615); // W1
    glVertex2f(0.84, -0.3);  // Z1
    glVertex2f(0.85, -0.405);
    glVertex2f(0.86, -0.658); // R2
    glVertex2f(0.87, -0.8); // S1
    glVertex2f(0.88, -0.81); // T2
    glVertex2f(0.89, -0.82); // U2
    glVertex2f(0.9, -0.83); // V2
    glVertex2f(0.92, -0.84); // W2
    glVertex2f(0.92, -0.85);// A3
    glVertex2f(0.93, -0.88); // B3
    glVertex2f(1.0, -0.98); // C3
    glVertex2f(0.92, -0.94); // D3
    glVertex2f(0.91, -0.92); // E3
    glVertex2f(0.88, -0.918); // F3
    glVertex2f(0.87, -0.91); // G3
    glVertex2f(0.86, -0.91); // H3
    glVertex2f(0.85, -0.92); // J3
    glVertex2f(0.84, -0.925); // I3
    glVertex2f(0.83, -0.93); // K3
    glVertex2f(0.82, -1.0);  //
    glVertex2f(0.75, -1.0); // L3
    glVertex2f(0.73, -0.95);//
    glVertex2f(0.71, -0.93);
    glVertex2f(0.69, -0.935);
    glVertex2f(0.65, -0.940);
    glEnd();
}
void leaves() {
    glColor3f(0.0f, 0.5f, 0.3f);
    drawFilledCircle(0.445, -0.41, .05, 2);
    drawFilledCircle(0.445, -0.38, .05, 2);
    drawFilledCircle(0.4, -0.41, .05, 2);
    drawFilledCircle(0.4, -0.38, .05, 2);
    drawFilledCircle(0.35, -0.40, .05, 2);
    glColor3f(0.0f, 0.2f, 0.2f);
    drawFilledCircle(0.945, 0.052, .1, 2);
    drawFilledCircle(0.84, 0.054, .09, 2);
    drawFilledCircle(0.75, 0.054, .06, 2);
    drawFilledCircle(0.72, 0.25, .06, 2);
    drawFilledCircle(0.8, 0.26, .08, 2);
    drawFilledCircle(0.62, 0.09, .1, 2);
    drawFilledCircle(0.75, 0.1, .1, 2);
    drawFilledCircle(0.65, 0.14, .1, 2);
    drawFilledCircle(0.84, 0.18, .1, 2);
    drawFilledCircle(0.75, 0.18, .1, 2);
    drawFilledCircle(0.9, 0.179, .1, 2);
    glColor3f(0.0f, 0.5f, 0.3f);
    drawFilledCircle(0.42, -0.02, .18, 2);
    drawFilledCircle(0.5, 0.1, .18, 2);
    drawFilledCircle(0.38, 0.1, .18, 2);
    drawFilledCircle(0.25, -0.05, .18, 2);
    drawFilledCircle(0.56, 0.19, .18, 2);


    glColor3f(0.0f, 0.6f, 0.3f);
    drawFilledCircle(0.2, -0.09, .08, 2);
    drawFilledCircle(0.32, 0.01, .16, 2);
    drawFilledCircle(0.35, 0.15, .1, 2);
    drawFilledCircle(0.32, 0.05, .1, 2);
    drawFilledCircle(0.44, 0.05, .08, 2);
    drawFilledCircle(0.48, 0.15, .08, 2);
    drawFilledCircle(0.5, 0.2, .1, 2);
    drawFilledCircle(0.2, 0.01, .08, 2);
    glColor4f(0.0f, 0.7f, 0.4f, 1.0f);
    drawFilledCircle(0.35, 0.15, .02, 2);
    drawFilledCircle(0.3, 0.2, .025, 2);
    drawFilledCircle(0.2, 0.01, .025, 2);
    drawFilledCircle(0.25, 0.05, .025, 2);
    glColor4f(0.0f, 0.7f, 0.4f, 1.0f);
    drawFilledCircle(0.29, 0.12, .035, 2);
    drawFilledCircle(0.16, 0.01, .035, 2);
    drawFilledCircle(0.2, 0.05, .03, 2);
    drawFilledCircle(0.28, 0.05, .03, 2);
    drawFilledCircle(0.38, 0.09, .04, 2);
    drawFilledCircle(0.4, 0.2, .04, 2);
    drawFilledCircle(0.45, 0.14, .06, 2);
    drawFilledCircle(0.4, 0.14, .04, 2);
    drawFilledCircle(0.24, 0.12, .025, 2);
    drawFilledCircle(0.26, 0.17, .015, 2);
    drawFilledCircle(0.45, 0.24, .015, 2);
    drawFilledCircle(0.5, 0.24, .035, 2);
    drawFilledCircle(0.45, 0.2, .035, 2);
    drawFilledCircle(0.54, 0.18, .015, 2);
    drawFilledCircle(0.36, 0.15, .06, 2);
    drawFilledCircle(0.3, 0.09, .05, 2);
    drawFilledCircle(0.28, -0.02, .03, 2);
    drawFilledCircle(0.18, -0.06, .025, 2);

    glColor3f(0.0f, 0.6f, 0.3f);
    drawFilledCircle(0.38, -0.38, .03, 2);
    drawFilledCircle(0.42, -0.38, .04, 2);
    drawFilledCircle(0.37, -0.4, .025, 2);
    drawFilledCircle(0.35, -0.4, .025, 2);

    glColor4f(0.0f, 0.7f, 0.4f, 1.0f);
    drawFilledCircle(0.35, -0.38, .02, 2);
    drawFilledCircle(0.41, -0.36, .015, 2);
    drawFilledCircle(0.39, -0.38, .03, 2);
    drawFilledCircle(0.32, -0.39, .015, 2);
    glColor4f(0.0f, 0.8f, 0.5f, 1.0f);
    drawFilledCircle(0.35, 0.15, .03, 2);
    drawFilledCircle(0.32, 0.1, .025, 2);
    drawFilledCircle(0.3, 0.14, .02, 2);
    drawFilledCircle(0.25, 0.12, .015, 2);
    drawFilledCircle(0.25, 0.08, .02, 2);
    drawFilledCircle(0.22, 0.04, .025, 2);
    drawFilledCircle(0.4, 0.15, .025, 2);
    drawFilledCircle(0.4, 0.21, .025, 2);
    glColor4f(0.0f, 0.8f, 0.5f, 1.0f);
    drawFilledCircle(0.4, -0.36, .02, 2);
    drawFilledCircle(0.365, -0.38, .015, 2);
}
void leaves2() {

    glColor3f(0.0f, 0.2f, 0.2f);
    drawFilledCircle(0.945, 0.052, .1, 2);
    drawFilledCircle(0.84, 0.054, .09, 2);
    drawFilledCircle(0.75, 0.054, .06, 2);
    drawFilledCircle(0.72, 0.25, .06, 2);
    drawFilledCircle(0.8, 0.26, .08, 2);
    drawFilledCircle(0.62, 0.09, .1, 2);
    drawFilledCircle(0.75, 0.1, .1, 2);
    drawFilledCircle(0.65, 0.14, .1, 2);
    drawFilledCircle(0.84, 0.18, .1, 2);
    drawFilledCircle(0.75, 0.18, .1, 2);
    drawFilledCircle(0.9, 0.179, .1, 2);
    glColor3f(0.0f, 0.5f, 0.3f);
    drawFilledCircle(0.42, -0.02, .18, 2);
    drawFilledCircle(0.5, 0.1, .18, 2);
    drawFilledCircle(0.38, 0.1, .18, 2);
    drawFilledCircle(0.25, -0.05, .18, 2);
    drawFilledCircle(0.56, 0.19, .18, 2);


    glColor3f(0.0f, 0.6f, 0.3f);
    drawFilledCircle(0.2, -0.09, .08, 2);
    drawFilledCircle(0.32, 0.01, .16, 2);
    drawFilledCircle(0.35, 0.15, .1, 2);
    drawFilledCircle(0.32, 0.05, .1, 2);
    drawFilledCircle(0.44, 0.05, .08, 2);
    drawFilledCircle(0.48, 0.15, .08, 2);
    drawFilledCircle(0.5, 0.2, .1, 2);
    drawFilledCircle(0.2, 0.01, .08, 2);
    glColor4f(0.0f, 0.7f, 0.4f, 1.0f);
    drawFilledCircle(0.35, 0.15, .02, 2);
    drawFilledCircle(0.3, 0.2, .025, 2);
    drawFilledCircle(0.2, 0.01, .025, 2);
    drawFilledCircle(0.25, 0.05, .025, 2);
    glColor4f(0.0f, 0.7f, 0.4f, 1.0f);
    drawFilledCircle(0.29, 0.12, .035, 2);
    drawFilledCircle(0.16, 0.01, .035, 2);
    drawFilledCircle(0.2, 0.05, .03, 2);
    drawFilledCircle(0.28, 0.05, .03, 2);
    drawFilledCircle(0.38, 0.09, .04, 2);
    drawFilledCircle(0.4, 0.2, .04, 2);
    drawFilledCircle(0.45, 0.14, .06, 2);
    drawFilledCircle(0.4, 0.14, .04, 2);
    drawFilledCircle(0.24, 0.12, .025, 2);
    drawFilledCircle(0.26, 0.17, .015, 2);
    drawFilledCircle(0.45, 0.24, .015, 2);
    drawFilledCircle(0.5, 0.24, .035, 2);
    drawFilledCircle(0.45, 0.2, .035, 2);
    drawFilledCircle(0.54, 0.18, .015, 2);
    drawFilledCircle(0.36, 0.15, .06, 2);
    drawFilledCircle(0.3, 0.09, .05, 2);
    drawFilledCircle(0.28, -0.02, .03, 2);
    drawFilledCircle(0.18, -0.06, .025, 2);

    //glColor3f(0.0f, 0.6f, 0.3f);
    //drawFilledCircle(0.38, -0.38, .03, 2);
    //drawFilledCircle(0.42, -0.38, .04, 2);
    //drawFilledCircle(0.37, -0.4, .025, 2);
    //drawFilledCircle(0.35, -0.4, .025, 2);

    //glColor4f(0.0f, 0.7f, 0.4f, 1.0f);
    //drawFilledCircle(0.35, -0.38, .02, 2);
    //drawFilledCircle(0.41, -0.36, .015, 2);
    //drawFilledCircle(0.39, -0.38, .03, 2);
    //drawFilledCircle(0.32, -0.39, .015, 2);
    glColor4f(0.0f, 0.8f, 0.5f, 1.0f);
    drawFilledCircle(0.35, 0.15, .03, 2);
    drawFilledCircle(0.32, 0.1, .025, 2);
    drawFilledCircle(0.3, 0.14, .02, 2);
    drawFilledCircle(0.25, 0.12, .015, 2);
    drawFilledCircle(0.25, 0.08, .02, 2);
    drawFilledCircle(0.22, 0.04, .025, 2);
    drawFilledCircle(0.4, 0.15, .025, 2);
    drawFilledCircle(0.4, 0.21, .025, 2);

}
void walnut() {
    glColor3f(0.82, 0.58, 0.34);//(1)
    drawFilledCircle(0.4, -0.25, 0.30, 2);
    drawFilledCircle(0.4, -0.53, 0.05, 2);
    drawFilledCircle(0.4, 0.03, 0.05, 2);

    glColor3f(0.91, 0.69, 0.44);//(2)
    drawFilledCircle(0.38, -0.23, 0.26, 2);
    drawFilledCircle(0.4, 0.028, 0.04, 2);

    glColor3f(0.953, 0.792, 0.573);//-1-
    drawFilledCircle(0.54, -0.13, 0.04, 2);
    drawFilledCircle(0.57, -0.23, 0.04, 2);
    drawFilledCircle(0.5, -0.35, 0.03, 2);
    drawFilledCircle(0.43, -0.4, 0.04, 2);
    drawFilledCircle(0.35, -0.4, 0.03, 2);
    //    drawFilledCircle(0.51, -0.35, 0.035);
    //    drawFilledCircle(0.35, -0.48, 0.04);
    //    drawFilledCircle(0.5, -0.45, 0.03);

    glColor3f(0.953, 0.792, 0.573);//(3)
    drawFilledCircle(0.35, -0.20, 0.20, 2);
    //    drawFilledCircle(0.37, 0.015, 0.03);

    glColor3f(0.91, 0.69, 0.44);//-2-
    drawFilledCircle(0.44, -0.05, 0.03, 2);
    drawFilledCircle(0.43, -0.14, 0.04, 2);
    drawFilledCircle(0.5, -0.22, 0.03, 2);
    drawFilledCircle(0.45, -0.35, 0.035, 2);
    drawFilledCircle(0.3, -0.35, 0.02, 2);

    glColor3f(0.969, 0.902, 0.824);//(4)
    drawFilledCircle(0.23, -0.14, 0.055, 2);
    drawFilledCircle(0.3, -0.1, 0.05, 2);
    drawFilledCircle(0.33, -0.17, 0.04, 2);
    drawFilledCircle(0.28, -0.24, 0.03, 2);
    drawFilledCircle(0.34, -0.24, 0.02, 2);
    drawFilledCircle(0.38, -0.11, 0.02, 2);

    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.72, 0.48, 0.24);
    glVertex2f(0.400, 0.024);
    glVertex2f(0.52, -0.033);
    glVertex2f(0.53, -0.106);
    glVertex2f(0.61, -0.13);
    glVertex2f(0.597, -0.235);
    glVertex2f(0.631, -0.31);
    glVertex2f(0.58, -0.372);
    glVertex2f(0.56, -0.456);
    glVertex2f(0.468, -0.466);
    glVertex2f(0.3998769386105, -0.5337382637096);
    glVertex2f(0.332, -0.466);
    glVertex2f(0.2345246029215, -0.4493668895866);
    glVertex2f(0.2074738224281, -0.3682145481063);
    glVertex2f(0.1596147492474, -0.3057896700446);
    glVertex2f(0.2116354809655, -0.2287989871019);
    glVertex2f(0.1991505053532, -0.1434849870842);
    glVertex2f(0.2761411882959, -0.099787572441);
    glVertex2f(0.2865453346396, -0.0311202065731);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.72, 0.48, 0.24);
    glVertex2f(0.3998769386105, 0.0242181893147);
    glVertex2f(0.4497250351341, -0.0481522880632);
    glVertex2f(0.4901990757195, -0.1189818590876);
    glVertex2f(0.4965231445609, -0.1758984786608);
    glVertex2f(0.5496453228293, -0.2049891953316);
    glVertex2f(0.483875006878, -0.3023798554902);
    glVertex2f(0.5167601648536, -0.3453835236122);
    glVertex2f(0.4231639459999, -0.426331604783);
    glVertex2f(0.3998769386105, -0.5337382637096);
    glVertex2f(0.367512140195, -0.4238019772464);
    glVertex2f(0.272651107573, -0.3529724062219);
    glVertex2f(0.3131251481584, -0.2998502279536);
    glVertex2f(0.2562085285852, -0.2037243815633);
    glVertex2f(0.3105955206218, -0.1758984786608);
    glVertex2f(0.3093307068535, -0.1139226040145);
    glVertex2f(0.3599232575852, -0.0747133771974);
    glVertex2f(0.3485399336706, -0.0279152677705);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.72, 0.48, 0.24);
    glVertex2f(0.4041917394755, -0.0683893083559);
    glVertex2f(0.4269427549452, -0.1302836904809);
    glVertex2f(0.3826899054145, -0.1885466163438);
    glVertex2f(0.4256935735365, -0.2606410011365);
    glVertex2f(0.3800071459843, -0.3311396407659);
    glVertex2f(0.4, -0.4);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.72, 0.48, 0.24);
    glVertex2f(0.25716357119, -0.0199631724005);
    glVertex2f(0.2, -0.05);
    glVertex2f(0.1936476944429, -0.0901150362704);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.72, 0.48, 0.24);
    glVertex2f(0.1661557477913, -0.1204509774033);
    glVertex2f(0.1310798158563, -0.1896548431127);
    glVertex2f(0.1557277680268, -0.2351587548121);
    glVertex2f(0.1206518360919, -0.2759226757094);
    glEnd();

}
void Tree() {

    // Tree Wood
    glColor3f(0.7f, 0.4f, 0.3f);

    glBegin(GL_POLYGON);
    glVertex2f(0.35, -1.0); // c
    glVertex2f(0.4, -0.97); // D
    glVertex2f(0.45, -0.95); // E
    glVertex2f(0.5, -0.90); // a
    glVertex2f(0.55, -0.85); // F
    glVertex2f(0.6, -0.8);  // G

    glVertex2f(0.69, -0.935);
    glVertex2f(0.65, -0.940);
    glVertex2f(0.63, -0.950); //
    glVertex2f(0.6, -0.952);
    glVertex2f(0.55, -0.955);
    glVertex2f(0.54, -0.958);
    glVertex2f(0.52, -0.9585);
    glVertex2f(0.5, -0.959);
    glVertex2f(0.48, -0.9595);
    glVertex2f(0.48, -0.975);
    glVertex2f(0.44, -0.99);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.6, -0.8);  // G
    glVertex2f(0.65, -0.65); // H
    glVertex2f(0.85, -0.92);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.6, -0.8);  // G
    glVertex2f(0.55, -0.85); // F
    glVertex2f(0.84, -0.925); // I3
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.66, -0.45); // K
    glVertex2f(0.55, -0.44); // L
    glVertex2f(0.5, -0.4); // M
    glVertex2f(0.4, -0.4); // N
    glVertex2f(0.48, -0.38); // O
    glVertex2f(0.55, -0.39); // b
    glVertex2f(0.66, -0.39); // P
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.654, -0.36); // R

    glVertex2f(0.58, -0.28); // S
    glVertex2f(0.5, -0.25); // T
    glVertex2f(0.44, -0.248); // U
    glVertex2f(0.38, -0.16); // V
    glVertex2f(0.46, -0.16); // W
    glVertex2f(0.5, -0.2); // Z
    glVertex2f(0.55, -0.2); // A1
    glVertex2f(0.6, -0.215); // B2
    glVertex2f(0.65, -0.22); // B2
    glVertex2f(0.7, -0.225); // B2
    glEnd();
    glBegin(GL_POLYGON);

    glVertex2f(0.66, -0.154); // I1
    glVertex2f(0.63, -0.05); // J1
    glVertex2f(0.6, -0.0);    // K1
    glVertex2f(0.658, 0.05); // L1
    glVertex2f(0.74, -0.155);// M1
    glVertex2f(0.78, -0.02); // N1
    glVertex2f(0.805, 0.02); // O1
    glVertex2f(0.81, 0.075); // Q1
    glVertex2f(0.88, 0.052);   // R1
    glVertex2f(0.86, -0.048); // S1
    glVertex2f(0.85, -0.048); // T1
    glVertex2f(0.85, -0.152); // U1
    glVertex2f(0.86, -0.158); // V1
    glVertex2f(0.86, -0.1615); // W1
    glVertex2f(0.84, -0.3);  // Z1
    glVertex2f(0.85, -0.405);
    glVertex2f(0.86, -0.658); // R2
    glVertex2f(0.87, -0.8); // S1
    glVertex2f(0.88, -0.81); // T2
    glVertex2f(0.89, -0.82); // U2
    glVertex2f(0.9, -0.83); // V2
    glVertex2f(0.92, -0.84); // W2
    glVertex2f(0.92, -0.85);// A3
    glVertex2f(0.93, -0.88); // B3
    glVertex2f(1.0, -0.98); // C3
    glVertex2f(0.92, -0.94); // D3
    glVertex2f(0.91, -0.92); // E3
    glVertex2f(0.88, -0.918); // F3
    glVertex2f(0.87, -0.91); // G3
    glVertex2f(0.86, -0.91); // H3
    glVertex2f(0.85, -0.92); // J3
    glVertex2f(0.84, -0.925); // I3
    glVertex2f(0.83, -0.93); // K3
    glVertex2f(0.82, -1.0);  //
    glVertex2f(0.75, -1.0); // L3
    glVertex2f(0.73, -0.95);//
    glVertex2f(0.71, -0.93);
    glVertex2f(0.69, -0.935);
    glVertex2f(0.65, -0.940);
    glEnd();

    // leaves that i don't want to move
    glColor3f(0.0f, 0.5f, 0.3f);
    drawFilledCircle(0.445, -0.41, .05, 2);
    drawFilledCircle(0.445, -0.38, .05, 2);
    drawFilledCircle(0.4, -0.41, .05, 2);
    drawFilledCircle(0.4, -0.38, .05, 2);
    drawFilledCircle(0.35, -0.40, .05, 2);
    glColor3f(0.0f, 0.6f, 0.3f);
    drawFilledCircle(0.38, -0.38, .03, 2);
    drawFilledCircle(0.42, -0.38, .04, 2);
    drawFilledCircle(0.37, -0.4, .025, 2);
    drawFilledCircle(0.35, -0.4, .025, 2);


    drawFilledCircle(0.35, -0.38, .02, 2);
    drawFilledCircle(0.41, -0.36, .015, 2);
    drawFilledCircle(0.39, -0.38, .03, 2);
    drawFilledCircle(0.32, -0.39, .015, 2);
    glColor4f(0.0f, 0.8f, 0.5f, 1.0f);
    drawFilledCircle(0.4, -0.36, .02, 2);
    drawFilledCircle(0.365, -0.38, .015, 2);
    glColor4f(0.0f, 0.7f, 0.4f, 1.0f);
}
void treeFarest() {
    glColor3f(0.3f, 0.1f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.35, -1.0); // c
    glVertex2f(0.4, -0.97); // D
    glVertex2f(0.45, -0.95); // E
    glVertex2f(0.5, -0.90); // a
    glVertex2f(0.55, -0.85); // F
    glVertex2f(0.6, -0.8);  // G

    glVertex2f(0.69, -0.935);
    glVertex2f(0.65, -0.940);
    glVertex2f(0.63, -0.950);
    glVertex2f(0.6, -0.952);
    glVertex2f(0.55, -0.955);
    glVertex2f(0.54, -0.958);
    glVertex2f(0.52, -0.9585);
    glVertex2f(0.5, -0.959);
    glVertex2f(0.48, -0.9595);
    glVertex2f(0.48, -0.975);
    glVertex2f(0.44, -0.99);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.6, -0.8);  // G
    glVertex2f(0.65, -0.65); // H
    glVertex2f(0.85, -0.92);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.6, -0.8);  // G
    glVertex2f(0.55, -0.85); // F
    glVertex2f(0.84, -0.925); // I3
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.66, -0.45); // K
    glVertex2f(0.55, -0.44); // L
    glVertex2f(0.5, -0.4); // M
    glVertex2f(0.4, -0.4); // N
    glVertex2f(0.48, -0.38); // O
    glVertex2f(0.55, -0.39); // b
    glVertex2f(0.66, -0.39); // P
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.654, -0.36); // R

    glVertex2f(0.58, -0.28); // S
    glVertex2f(0.5, -0.25); // T
    glVertex2f(0.44, -0.248); // U
    glVertex2f(0.38, -0.16); // V
    glVertex2f(0.46, -0.16); // W
    glVertex2f(0.5, -0.2); // Z
    glVertex2f(0.55, -0.2); // A1
    glVertex2f(0.6, -0.215); // B2
    glVertex2f(0.65, -0.22); // B2
    glVertex2f(0.7, -0.225); // B2
    glEnd();
    glBegin(GL_POLYGON);

    glVertex2f(0.66, -0.154); // I1
    glVertex2f(0.63, -0.05); // J1
    glVertex2f(0.6, -0.0);    // K1
    glVertex2f(0.658, 0.05); // L1
    glVertex2f(0.74, -0.155);// M1
    glVertex2f(0.78, -0.02); // N1
    glVertex2f(0.805, 0.02); // O1
    glVertex2f(0.81, 0.075); // Q1
    glVertex2f(0.88, 0.052);   // R1
    glVertex2f(0.86, -0.048); // S1
    glVertex2f(0.85, -0.048); // T1
    glVertex2f(0.85, -0.152); // U1
    glVertex2f(0.86, -0.158); // V1
    glVertex2f(0.86, -0.1615); // W1
    glVertex2f(0.84, -0.3);  // Z1
    glVertex2f(0.85, -0.405);
    glVertex2f(0.86, -0.658); // R2
    glVertex2f(0.87, -0.8); // S1
    glVertex2f(0.88, -0.81); // T2
    glVertex2f(0.89, -0.82); // U2
    glVertex2f(0.9, -0.83); // V2
    glVertex2f(0.92, -0.84); // W2
    glVertex2f(0.92, -0.85);// A3
    glVertex2f(0.93, -0.88); // B3
    glVertex2f(1.0, -0.98); // C3
    glVertex2f(0.92, -0.94); // D3
    glVertex2f(0.91, -0.92); // E3
    glVertex2f(0.88, -0.918); // F3
    glVertex2f(0.87, -0.91); // G3
    glVertex2f(0.86, -0.91); // H3
    glVertex2f(0.85, -0.92); // J3
    glVertex2f(0.84, -0.925); // I3
    glVertex2f(0.83, -0.93); // K3
    glVertex2f(0.82, -1.0);  //
    glVertex2f(0.75, -1.0); // L3
    glVertex2f(0.73, -0.95);//
    glVertex2f(0.71, -0.93);
    glVertex2f(0.69, -0.935);
    glVertex2f(0.65, -0.940);
    glEnd();
    // leaf
    glColor3f(0.1f, 0.1f, 0.0f);
    drawFilledCircle(0.445, -0.41, .05, 2);
    drawFilledCircle(0.445, -0.38, .05, 2);
    drawFilledCircle(0.4, -0.41, .05, 2);
    drawFilledCircle(0.4, -0.38, .05, 2);
    drawFilledCircle(0.35, -0.40, .05, 2);
    glColor3f(0.1f, 0.1f, 0.0f);
    drawFilledCircle(0.945, 0.052, .1, 2);
    drawFilledCircle(0.84, 0.054, .09, 2);
    drawFilledCircle(0.75, 0.054, .06, 2);
    drawFilledCircle(0.72, 0.25, .06, 2);
    drawFilledCircle(0.8, 0.26, .08, 2);
    drawFilledCircle(0.62, 0.09, .1, 2);
    drawFilledCircle(0.75, 0.1, .1, 2);
    drawFilledCircle(0.65, 0.14, .1, 2);
    drawFilledCircle(0.84, 0.18, .1, 2);
    drawFilledCircle(0.75, 0.18, .1, 2);
    drawFilledCircle(0.9, 0.179, .1, 2);

    glColor3f(0.1f, 0.2f, 0.0f);
    drawFilledCircle(0.42, -0.02, .18, 2);
    drawFilledCircle(0.5, 0.1, .18, 2);
    drawFilledCircle(0.38, 0.1, .18, 2);
    drawFilledCircle(0.25, -0.05, .18, 2);
    drawFilledCircle(0.56, 0.19, .18, 2);

    glColor3f(0.1f, 0.3f, 0.0f);
    drawFilledCircle(0.2, -0.09, .08, 2);
    drawFilledCircle(0.32, 0.01, .16, 2);
    drawFilledCircle(0.35, 0.15, .1, 2);
    drawFilledCircle(0.32, 0.05, .1, 2);
    drawFilledCircle(0.44, 0.05, .08, 2);
    drawFilledCircle(0.48, 0.15, .08, 2);
    drawFilledCircle(0.5, 0.2, .1, 2);
    drawFilledCircle(0.2, 0.01, .08, 2);

    glColor3f(0.1f, 0.3f, 0.0f);
    drawFilledCircle(0.38, -0.38, .03, 2);
    drawFilledCircle(0.42, -0.38, .04, 2);
    drawFilledCircle(0.37, -0.4, .025, 2);
    drawFilledCircle(0.35, -0.4, .025, 2);
}
void treeFar() {
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.35, -1.0); // c
    glVertex2f(0.4, -0.97); // D
    glVertex2f(0.45, -0.95); // E
    glVertex2f(0.5, -0.90); // a
    glVertex2f(0.55, -0.85); // F
    glVertex2f(0.6, -0.8);  // G

    glVertex2f(0.69, -0.935);
    glVertex2f(0.65, -0.940);
    glVertex2f(0.63, -0.950); //
    glVertex2f(0.6, -0.952);
    glVertex2f(0.55, -0.955);
    glVertex2f(0.54, -0.958);
    glVertex2f(0.52, -0.9585);
    glVertex2f(0.5, -0.959);
    glVertex2f(0.48, -0.9595);
    glVertex2f(0.48, -0.975);
    glVertex2f(0.44, -0.99);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.6, -0.8);  // G
    glVertex2f(0.65, -0.65); // H
    glVertex2f(0.85, -0.92);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.6, -0.8);  // G
    glVertex2f(0.55, -0.85); // F
    glVertex2f(0.84, -0.925); // I3
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.66, -0.45); // K
    glVertex2f(0.55, -0.44); // L
    glVertex2f(0.5, -0.4); // M
    glVertex2f(0.4, -0.4); // N
    glVertex2f(0.48, -0.38); // O
    glVertex2f(0.55, -0.39); // b
    glVertex2f(0.66, -0.39); // P
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.654, -0.36); // R

    glVertex2f(0.58, -0.28); // S
    glVertex2f(0.5, -0.25); // T
    glVertex2f(0.44, -0.248); // U
    glVertex2f(0.38, -0.16); // V
    glVertex2f(0.46, -0.16); // W
    glVertex2f(0.5, -0.2); // Z
    glVertex2f(0.55, -0.2); // A1
    glVertex2f(0.6, -0.215); // B2
    glVertex2f(0.65, -0.22); // B2
    glVertex2f(0.7, -0.225); // B2
    glEnd();
    glBegin(GL_POLYGON);

    glVertex2f(0.66, -0.154); // I1
    glVertex2f(0.63, -0.05); // J1
    glVertex2f(0.6, -0.0);    // K1
    glVertex2f(0.658, 0.05); // L1
    glVertex2f(0.74, -0.155);// M1
    glVertex2f(0.78, -0.02); // N1
    glVertex2f(0.805, 0.02); // O1
    glVertex2f(0.81, 0.075); // Q1
    glVertex2f(0.88, 0.052);   // R1
    glVertex2f(0.86, -0.048); // S1
    glVertex2f(0.85, -0.048); // T1
    glVertex2f(0.85, -0.152); // U1
    glVertex2f(0.86, -0.158); // V1
    glVertex2f(0.86, -0.1615); // W1
    glVertex2f(0.84, -0.3);  // Z1
    glVertex2f(0.85, -0.405);
    glVertex2f(0.86, -0.658); // R2
    glVertex2f(0.87, -0.8); // S1
    glVertex2f(0.88, -0.81); // T2
    glVertex2f(0.89, -0.82); // U2
    glVertex2f(0.9, -0.83); // V2
    glVertex2f(0.92, -0.84); // W2
    glVertex2f(0.92, -0.85);// A3
    glVertex2f(0.93, -0.88); // B3
    glVertex2f(1.0, -0.98); // C3
    glVertex2f(0.92, -0.94); // D3
    glVertex2f(0.91, -0.92); // E3
    glVertex2f(0.88, -0.918); // F3
    glVertex2f(0.87, -0.91); // G3
    glVertex2f(0.86, -0.91); // H3
    glVertex2f(0.85, -0.92); // J3
    glVertex2f(0.84, -0.925); // I3
    glVertex2f(0.83, -0.93); // K3
    glVertex2f(0.82, -1.0);  //
    glVertex2f(0.75, -1.0); // L3
    glVertex2f(0.73, -0.95);//
    glVertex2f(0.71, -0.93);
    glVertex2f(0.69, -0.935);
    glVertex2f(0.65, -0.940);
    glEnd();
    // leaf
    glColor3f(0.1f, 0.4f, 0.2f);
    drawFilledCircle(0.445, -0.41, .05, 2);
    drawFilledCircle(0.445, -0.38, .05, 2);
    drawFilledCircle(0.4, -0.41, .05, 2);
    drawFilledCircle(0.4, -0.38, .05, 2);
    drawFilledCircle(0.35, -0.40, .05, 2);
    glColor3f(0.1f, 0.2f, 0.1f);
    drawFilledCircle(0.945, 0.052, .1, 2);
    drawFilledCircle(0.84, 0.054, .09, 2);
    drawFilledCircle(0.75, 0.054, .06, 2);
    drawFilledCircle(0.72, 0.25, .06, 2);
    drawFilledCircle(0.8, 0.26, .08, 2);
    drawFilledCircle(0.62, 0.09, .1, 2);
    drawFilledCircle(0.75, 0.1, .1, 2);
    drawFilledCircle(0.65, 0.14, .1, 2);
    drawFilledCircle(0.84, 0.18, .1, 2);
    drawFilledCircle(0.75, 0.18, .1, 2);
    drawFilledCircle(0.9, 0.179, .1, 2);

    glColor3f(0.1f, 0.4f, 0.2f);
    drawFilledCircle(0.42, -0.02, .18, 2);
    drawFilledCircle(0.5, 0.1, .18, 2);
    drawFilledCircle(0.38, 0.1, .18, 2);
    drawFilledCircle(0.25, -0.05, .18, 2);
    drawFilledCircle(0.56, 0.19, .18, 2);

    glColor3f(0.1f, 0.5f, 0.3f);
    drawFilledCircle(0.2, -0.09, .08, 2);
    drawFilledCircle(0.32, 0.01, .16, 2);
    drawFilledCircle(0.35, 0.15, .1, 2);
    drawFilledCircle(0.32, 0.05, .1, 2);
    drawFilledCircle(0.44, 0.05, .08, 2);
    drawFilledCircle(0.48, 0.15, .08, 2);
    drawFilledCircle(0.5, 0.2, .1, 2);
    drawFilledCircle(0.2, 0.01, .08, 2);

    drawFilledCircle(0.38, -0.38, .03, 2);
    drawFilledCircle(0.42, -0.38, .04, 2);
    drawFilledCircle(0.37, -0.4, .025, 2);
    drawFilledCircle(0.35, -0.4, .025, 2);
}
void sapling() {
    glColor3f(0.0f, 0.5f, 0.3f);
    drawFilledCircle(0.42, -0.02, .18, 2);
    drawFilledCircle(0.5, 0.1, .18, 2);
    drawFilledCircle(0.38, 0.1, .18, 2);
    drawFilledCircle(0.25, -0.05, .18, 2);
    drawFilledCircle(0.56, 0.19, .18, 2);
    glColor3f(0.0f, 0.6f, 0.3f);
    drawFilledCircle(0.2, -0.09, .08, 2);
    drawFilledCircle(0.32, 0.01, .16, 2);
    drawFilledCircle(0.35, 0.15, .1, 2);
    drawFilledCircle(0.32, 0.05, .1, 2);
    drawFilledCircle(0.44, 0.05, .08, 2);
    drawFilledCircle(0.48, 0.15, .08, 2);
    drawFilledCircle(0.5, 0.2, .1, 2);
    drawFilledCircle(0.2, 0.01, .08, 2);


}
void floor() {

    glColor3f(0.0f, 0.3f, 0.0f);
    drawFilledCircle(0.6, -0.8, .5, 2);
    glLineWidth(10.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.1, -0.8);
    glVertex2f(0.3, -0.4);
    glEnd();

    drawFilledCircle(-0.8, -0.8, .35, 2);


    glBegin(GL_QUADS);
    glVertex2f(1.0, -0.58);
    glVertex2f(-1.0, -0.58);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(1.0, -0.58);
    glVertex2f(0.125, -0.55);
    glColor3f(0.0f, 0.7f, 0.3f);
    glVertex2f(0.0, -1.0);
    glVertex2f(1.0, -1.0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(-1.0, -0.58);
    glVertex2f(-0.125, -0.55);
    glColor3f(0.0f, 0.7f, 0.3f);
    glVertex2f(-0.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();


}
void floor1() {

    glColor3f(0.0f, 0.3f, 0.0f);
    drawFilledCircle(0.6, -0.8, .5, 2);
    glLineWidth(18.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.1, -0.8);
    glVertex2f(0.35, -0.4);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(1.0, -0.58);
    glVertex2f(-1.0, -0.58);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.2f, 0.0f);
    glVertex2f(1.0, -0.58);
    glVertex2f(-1.0, -0.58);
    glColor3f(0.0f, 0.7f, 0.3f);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glEnd();


}
void sunL() {
    glColor3f(1.0f, 0.8f, 0.4f);
    drawFilledCircle(0.0, -0.5, .18, 2);
    glColor4f(1.0f, 0.8f, 0.4f, 0.2f);

}
void sun1() {
    glColor3f(1.0f, 0.8f, 0.4f);
    drawFilledCircle(-0.6, 0.5, .18, 2);
    glColor4f(1.0f, 0.8f, 0.4f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6, 0.5);
    glVertex2f(1.0, -0.3);
    glVertex2f(1.0, -0.99);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6, 0.5);
    glVertex2f(-1.0, -0.1);
    glVertex2f(-1.0, -0.6);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6, 0.5);
    glVertex2f(0.0, -1.0);
    glVertex2f(-0.4, -1.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6, 0.5);
    glVertex2f(0.0, 1.0);
    glVertex2f(-0.4, 1.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6, 0.5);
    glVertex2f(1.0, 0.8);
    glVertex2f(1.0, 0.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6, 0.5);
    glVertex2f(-1.0, 0.6);
    glVertex2f(-1.0, 0.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6, 0.5);
    glVertex2f(-0.8, 1.0);
    glVertex2f(-1.0, 0.8);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.0, 1.0);
    glVertex2f(-0.8, 1.0);
    glVertex2f(-1.0, 0.8);
    glEnd();


}
void sun2() {
    if (transp7 <= 0.19) {
        transp7 += 0.0025;//0.00001
    }
    else if (transp7 == 0.19) {
        transp7 = 0.09;
    }
    glColor3f(1.0f, 0.8f, 0.4f);
    drawFilledCircle(-0.6, 0.5, .18, 2);
    glColor4f(1.0f, 0.9f, 0.1f, transp7);
    drawFilledCircle(-0.6, 0.5, .25, 2);
    drawFilledCircle(-0.6, 0.5, .23, 2);
    drawFilledCircle(-0.6, 0.5, .2, 2);

}
void roadL() {
    glColor3f(1.0f, 0.9f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(-0.45, -1.0);
    glColor3f(0.6f, 0.3f, 0.1f);
    glVertex2f(-0.125, -0.55);
    glVertex2f(0.125, -0.55);
    glColor3f(1.0f, 0.9f, 0.7f);
    glVertex2f(0.45, -1.0);
    glEnd();
}
void cloudL() {
    glColor4f(0.99f, 0.99f, 0.99f, 0.9);
    drawFilledCircle(0.4, 0.1, .1, 2);
    drawFilledCircle(0.6, 0.105, .15, 2);
    drawFilledCircle(0.8, 0.1, .1, 2);
    drawFilledCircle(0.6, 0.14, .15, 2);
    glColor4f(1.0f, 1.0f, 1.0f, 0.9);
    drawFilledCircle(-0.4, 0.2, .1, 2);
    drawFilledCircle(-0.2, 0.2, .1, 2);
    drawFilledCircle(0.0, 0.21, .15, 2);
    drawFilledCircle(0.2, 0.2, .1, 2);
    drawFilledCircle(-0.2, 0.28, .15, 2);
}
void sunset() {
    glColor4f(0.8f, 0.5f, 0.1f, transpS);
    glBegin(GL_QUADS);
    glVertex2f(1.0, 1.0);
    glVertex2f(-1.0, 1.0);
    glVertex2f(-1.0, -0.6);
    glVertex2f(1.0, -0.6);
    glEnd();


}
void owl() {
    // body
    glColor4f(1.0f, 0.9f, 0.6f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.15, 0.2);
    glVertex2f(-0.15, 0.2);
    glVertex2f(-0.15, -0.075);
    glVertex2f(0.15, -0.075);
    glEnd();

    // it does not have sharp corners
    glColor3f(1.0f, 0.9f, 0.6f);
    drawFilledCircle(0.13, -0.0595, .023, 2);
    drawFilledCircle(-0.13, -0.0595, .023, 2);
    glColor3f(1.0f, 0.9f, 0.6f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.13, -0.0775);
    glVertex2f(-0.13, -0.0775);
    glEnd();

    glColor3f(1.0f, 0.9f, 0.6f);
    drawFilledCircle(0.0, 0.075, .145, 2);
    glLineWidth(4.8);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.1, 0.2);
    glVertex2f(-0.1, 0.2);
    glEnd();
    // eir
    glColor3f(1.0f, 0.9f, 0.6f);
    drawFilledCircle(0.125, 0.185, .041, 2);
    drawFilledCircle(-0.125, 0.185, .04, 2);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.2, 0.25);
    glVertex2f(0.125, 0.225);
    glVertex2f(0.15, 0.15);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2, 0.25);
    glVertex2f(-0.125, 0.225);
    glVertex2f(-0.15, 0.15);
    glEnd();

    glColor3f(0.8f, 0.5f, 0.3f);
    drawFilledCircle(0.135, 0.19, .0225, 2);
    drawFilledCircle(-0.135, 0.19, .0225, 2);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.1825, 0.23);
    glVertex2f(0.115, 0.2);
    glVertex2f(0.14, 0.1625);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.1825, 0.23);
    glVertex2f(-0.115, 0.2);
    glVertex2f(-0.14, 0.1625);
    glEnd();
    // eye
    drawFilledCircle(0.05, 0.09, .075, 2);
    drawFilledCircle(-0.05, 0.09, .075, 2);
    glColor3f(1.0f, 0.9f, 0.7f);
    drawFilledCircle(0.05, 0.09, .06, 2);
    drawFilledCircle(-0.05, 0.09, .06, 2);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.04, 0.09, .02, 2);
    drawFilledCircle(-0.04, 0.09, .02, 2);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.045, 0.1, .005, 2);
    drawFilledCircle(-0.035, 0.1, .005, 2);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.04, 0.08, .006, 2);
    drawFilledCircle(-0.041, 0.08, .006, 2);
    // noice
    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0225, 0.055);
    glVertex2f(0.0, 0.0);
    glVertex2f(-0.0225, 0.055);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0225, 0.055);
    glVertex2f(0.0, 0.0);
    glVertex2f(-0.0255, 0.055);
    glEnd();
    // Legs
    glColor3f(1.0f, 0.9f, 0.6f);
    glLineWidth(11.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.025, -0.05);
    glVertex2f(0.025, -0.2);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.025, -0.05);
    glVertex2f(-0.025, -0.2);
    glEnd();
    glColor3f(1.0f, 0.9f, 0.6f);
    drawFilledCircle(0.035, -0.195, .0275, 2);
    drawFilledCircle(-0.035, -0.195, .0275, 2);
    //
    // body
    glColor3f(0.8f, 0.5f, 0.3f);
    drawFilledCircle(0.02, -0.055, .02, 2);
    drawFilledCircle(-0.0095, -0.055, .02, 2);
    glColor3f(1.0f, 0.9f, 0.6f);
    drawFilledCircle(0.02, -0.05, .02, 2);
    drawFilledCircle(-0.0095, -0.05, .02, 2);

    glColor3f(0.8f, 0.5f, 0.3f);
    drawFilledCircle(-0.025, -0.02, .02, 2);
    drawFilledCircle(0.0, -0.02, .02, 2);
    drawFilledCircle(0.025, -0.02, .02, 2);
    glColor3f(1.0f, 0.9f, 0.6f);
    drawFilledCircle(-0.025, -0.015, .02, 2);
    drawFilledCircle(0.0, -0.015, .02, 2);
    drawFilledCircle(0.025, -0.015, .02, 2);

    // wings
    glColor3f(1.0f, 0.9f, 0.6f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.225, 0.0);
    glVertex2f(0.15, 0.1);
    glVertex2f(0.15, 0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.255, 0.0);
    glVertex2f(0.255, 0.045);
    glVertex2f(0.1, 0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.2545, 0.03);
    glVertex2f(0.225, 0.0);
    glVertex2f(0.15, 0.08);
    glEnd();
    drawFilledCircle(0.2, 0.01, .03, 2);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.255, 0.0);
    glVertex2f(0.21, -0.0125);
    glEnd();
    glLineWidth(2.5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.15, 0.0);
    glVertex2f(0.21, -0.016);
    glEnd();

    // left wing
    glColor3f(1.0f, 0.9f, 0.6f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.225, 0.0);
    glVertex2f(-0.15, 0.1);
    glVertex2f(-0.15, 0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.255, 0.0);
    glVertex2f(-0.255, 0.045);
    glVertex2f(-0.1, 0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2545, 0.03);
    glVertex2f(-0.225, 0.0);
    glVertex2f(-0.15, 0.08);
    glEnd();
    drawFilledCircle(-0.2, 0.01, .03, 2);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.255, 0.0);
    glVertex2f(-0.21, -0.0125);
    glEnd();
    glLineWidth(2.5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.15, 0.0);
    glVertex2f(-0.21, -0.016);
    glEnd();
}
void sunface() {
    //eyelashes right eye
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.0845399363691, 0.080123824998);
    glVertex2f(0.0783664041974, 0.0744710196187);
    glVertex2f(0.0906709040623, 0.07737546017);
    glVertex2f(0.0892420962643, 0.0686706505163);
    glVertex2f(0.0995502365835, 0.0769526348119);
    glVertex2f(0.0993927421933, 0.0686706505163);
    glVertex2f(0.1073725057093, 0.0790667616026);
    glVertex2f(0.1099059111913, 0.0708457889297);
    glVertex2f(0.1135034734024, 0.0824493644678);
    glVertex2f(0.1189689879137, 0.0759211118942);
    glVertex2f(0.1175203143049, 0.0866776180493);
    glVertex2f(0.1247693570161, 0.08389661941);
    glEnd();



    //left eye
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.0015278720011, 0.0884617418834);
    glVertex2f(-0.0082470594866, 0.0814065950236);
    glVertex2f(-0.0156381657207, 0.0790548794036);
    glVertex2f(-0.0230292719548, 0.0783829606551);
    glVertex2f(-0.031764215686, 0.0803987169007);
    glVertex2f(-0.037811484423, 0.0840942700178);
    glVertex2f(-0.04150703754, 0.0881257825091);
    glVertex2f(-0.0458713422101, 0.0924136490281);
    glEnd();

    //eyelashes left eye
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-0.0082470594866, 0.0814065950236);
    glVertex2f(-0.0031366752155, 0.075952888408);
    glVertex2f(-0.0156381657207, 0.0790548794036);
    glVertex2f(-0.0132663740587, 0.0693052735422);
    glVertex2f(-0.0230292719548, 0.0783829606551);
    glVertex2f(-0.0227629667241, 0.0674059550091);
    glVertex2f(-0.031764215686, 0.0803987169007);
    glVertex2f(-0.033525771745, 0.0702549328088);
    glVertex2f(-0.037811484423, 0.0840942700178);
    glVertex2f(-0.0449216829435, 0.0765859945857);
    glVertex2f(-0.04150703754, 0.0881257825091);
    glVertex2f(-0.0493534261874, 0.0844998218069);
    glEnd();

    //cheeks
    glColor3f(0.98, 0.745, 0.51);
    drawFilledCircle(-0.0495365713462, 0.0235385177666, 0.02, 2);
    drawFilledCircle(0.125424239421, 0.0251290705918, 0.02, 2);

    //mouth
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.009808308886, 0.0426596470177);
    glVertex2f(0.0149348435866, 0.0351706053598);
    glVertex2f(0.0250276944198, 0.0283074667933);
    glVertex2f(0.0355242592863, 0.0250777545267);
    glVertex2f(0.0492505364194, 0.0270963246933);
    glVertex2f(0.0589396732193, 0.0335557492265);
    glVertex2f(0.065109947811, 0.0431074335677);
    glEnd();

}
void Rabbit()
{
    // ------------------------------------------------------------------
    // drawing the filled circle //(WH-FACE)
    glColor4f(1.0f, 1.0f, 1.0f, 1.0);
    drawFilledCircle(0.13, -0.25, 0.10, 2);  //right
    drawFilledCircle(-0.13, -0.25, 0.10, 2); //left
    drawFilledCircle(0.0, -0.40, 0.10, 2);   //down
    // ------------------------------------------------------------------
    glBegin(GL_TRIANGLES); //(WH-FACE)
    glColor4f(1.0f, 1.0f, 1.0f, 1);

    glVertex2f(0.13, -0.15); //right
    glVertex2f(-0.13, -0.15); //left
    glVertex2f(0.0, -0.40); //center
    glEnd();
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(WH-FACE)

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    glVertex2f(0.219, -0.3);   //right-up
    glVertex2f(-0.219, -0.3);  //left-up
    glVertex2f(-0.085, -0.45); //left-down
    glVertex2f(0.085, -0.45);  //right-down
    glEnd();
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(FEET & HANDS)

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    ////RIGHT-FEET
    glVertex2f(0.04, -0.4);   //right-up
    glVertex2f(0.005, -0.4);  //left-up
    glVertex2f(0.005, -0.7); //left-down
    glVertex2f(0.04, -0.7);  //right-down
    //LEFT-FEET
    glVertex2f(-0.005, -0.4);   //right-up
    glVertex2f(-0.04, -0.4);  //left-up
    glVertex2f(-0.04, -0.7); //left-down
    glVertex2f(-0.005, -0.7);  //right-down
    //RIGHT-HAND
    glVertex2f(0.03, -0.22);   //right-up
    glVertex2f(0.0, -0.25);  //left-up
    glVertex2f(0.20, -0.60); //left-down
    glVertex2f(0.23, -0.57);  //right-down
    //LEFT-HAND
    glVertex2f(-0.03, -0.22);   //right-up
    glVertex2f(0.0, -0.25);  //left-up
    glVertex2f(-0.20, -0.60); //left-down
    glVertex2f(-0.23, -0.57);  //right-down
    glEnd();
    // ------------------------------------------------------------------
    // drawing half filled circle (P-SHOES)
    glColor4f(0.85f, 0.65f, 0.9f, 1);
    drawFilledCircle(0.04, -0.7, 0.035, 1);
    drawFilledCircle(-0.04, -0.7, 0.035, 1);
    // ------------------------------------------------------------------
    // drawing half filled circle (P-HANDS)
    glColor4f(0.85f, 0.65f, 0.9f, 1);
    drawFilledCircle(0.215, -0.585, 0.035, 2); //midpoint formula = (x1 + x2)/2, (y1 + y2)/2.
    drawFilledCircle(-0.215, -0.585, 0.035, 2);
    // ------------------------------------------------------------------
    // drawing the filled circle (EARS)
    //(WHITE)
    glColor4f(1.0f, 1.0f, 1.0f, 1);
    drawFilledCircle(0.08, 0.09, 0.06, 2);//right
    drawFilledCircle(-0.08, 0.09, 0.06, 2);//left
    //(PINK)
    glColor4f(0.85f, 0.65f, 0.9f, 1);
    drawFilledCircle(0.08, 0.09, 0.03, 2);//right
    drawFilledCircle(-0.08, 0.09, 0.03, 2);//left
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(EARS)

    glColor4f(1.0f, 1.0f, 1.0f, 1); //(WHITE)
    //right-ear
    glVertex2f(0.14, 0.09); //right-up
    glVertex2f(0.02, 0.09); //left-up
    glVertex2f(0.0, -0.15); //left-down
    glVertex2f(0.03, -0.15); //right-down
    //left-ear
    glVertex2f(-0.02, 0.09); //right-up
    glVertex2f(-0.14, 0.09); //left-up
    glVertex2f(-0.03, -0.15); //left-down
    glVertex2f(-0.0, -0.15); //right-down

    glColor4f(0.85f, 0.65f, 0.9f, 1); //(PINK)
    //right-ear
    glVertex2f(0.11, 0.09); //right-up
    glVertex2f(0.05, 0.09); //left-up
    glColor4f(0.65f, 0.45f, 0.7f, 1);
    glVertex2f(0.01, -0.15); //left-down
    glVertex2f(0.02, -0.15); //right-down
    glColor4f(0.85f, 0.65f, 0.9f, 1);
    //left-ear
    glVertex2f(-0.05, 0.09); //right-up
    glVertex2f(-0.11, 0.09); //left-up
    glColor4f(0.55f, 0.35f, 0.6f, 1);
    glVertex2f(-0.02, -0.15); //left-down
    glVertex2f(-0.01, -0.15); //right-down

    glEnd();

}
void faceExep() {
    // ------------------------------------------------------------------
// drawing the filled circle (MOUTH & CKEEKS)
//MOUTH
    glColor3f(0.4f, 0.4f, 0.4f);//black
    drawFilledCircle(0.017, -0.33, 0.022, 2);
    drawFilledCircle(-0.017, -0.33, 0.022, 2);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0);//white
    drawFilledCircle(0.0175, -0.324, 0.020, 2);
    drawFilledCircle(-0.0175, -0.324, 0.020, 2);

    //CKEEKS
    glColor4f(0.85f, 0.65f, 0.9f, 1);
    drawFilledCircle(0.08f, -0.31f, 0.025, 2);
    drawFilledCircle(-0.08f, -0.31f, 0.025, 2);
    // ------------------------------------------------------------------
    glLineWidth(6.0f); // (EYES)
    glBegin(GL_LINES);

    glColor3f(0.4f, 0.4f, 0.4f);
    //RIGHT-EYES
    glVertex2f(0.08f, -0.30f);//right
    glVertex2f(0.05f, -0.26f);//head

    glVertex2f(0.05f, -0.26f);//head
    glVertex2f(0.02f, -0.30f);//left
    //LEFT-EYES
    glVertex2f(-0.02f, -0.30f);//right
    glVertex2f(-0.05f, -0.26f);//head

    glVertex2f(-0.05f, -0.26f);//head
    glVertex2f(-0.08f, -0.30f);//left
    glEnd();

}
void faceExepSleep() {
    // ------------------------------------------------------------------
// drawing the filled circle (MOUTH & CKEEKS)
//MOUTH
    glColor3f(0.4f, 0.4f, 0.4f);//black
    drawFilledCircle(0.017, -0.33, 0.022, 2);
    drawFilledCircle(-0.017, -0.33, 0.022, 2);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0);//white
    drawFilledCircle(0.0175, -0.324, 0.020, 2);
    drawFilledCircle(-0.0175, -0.324, 0.020, 2);

    //CKEEKS
    glColor4f(0.85f, 0.65f, 0.9f, 1);
    drawFilledCircle(0.08f, -0.31f, 0.025, 2);
    drawFilledCircle(-0.08f, -0.31f, 0.025, 2);
    // ------------------------------------------------------------------
    glLineWidth(4.0f); // (EYES)
    glBegin(GL_LINES);

    glColor3f(0.4f, 0.4f, 0.4f);
    //RIGHT-EYES
    glVertex2f(0.08f, -0.30f);//right
    glVertex2f(0.02f, -0.30f);//left
    //LEFT-EYES
    glVertex2f(-0.02f, -0.30f);//right
    glVertex2f(-0.08f, -0.30f);//left
    glEnd();

}
void faceExepShock() {
    // ------------------------------------------------------------------
// drawing the filled circle (MOUTH & CKEEKS)
//MOUTH
    glColor3f(0.4f, 0.4f, 0.4f);//black
    drawFilledCircle(0.0, -0.35, 0.022, 2);
    drawFilledCircle(0.0, -0.36, 0.022, 2);
    drawFilledCircle(0.0, -0.37, 0.022, 2);

    //CKEEKS
    glColor4f(0.85f, 0.65f, 0.9f, 1);
    drawFilledCircle(0.08f, -0.31f, 0.025, 2);
    drawFilledCircle(-0.08f, -0.31f, 0.025, 2);
    // ------------------------------------------------------------------

    //RIGHT-EYEBROWS
    glColor3f(0.4f, 0.4f, 0.4f);//black
    drawFilledCircle(0.04, -0.25, 0.02, 2);
    glColor3f(1.0f, 1.0f, 1.0f);//white
    drawFilledCircle(0.04, -0.26, 0.02, 2);
    //LEFT-EYEBROWS
    glColor3f(0.4f, 0.4f, 0.4f);//black
    drawFilledCircle(-0.04, -0.25, 0.02, 2);
    glColor3f(1.0f, 1.0f, 1.0f);//white
    drawFilledCircle(-0.04, -0.26, 0.02, 2);

    //RIGHT-EYE
    glColor3f(0.4f, 0.4f, 0.4f);//black
    drawFilledCircle(0.04, -0.28, 0.015, 2);
    drawFilledCircle(0.04, -0.29, 0.015, 2);
    drawFilledCircle(0.04, -0.3, 0.015, 2);
    //LEFT-EYE
    glColor3f(0.4f, 0.4f, 0.4f);//black
    drawFilledCircle(-0.04, -0.28, 0.015, 2);
    drawFilledCircle(-0.04, -0.29, 0.015, 2);
    drawFilledCircle(-0.04, -0.3, 0.015, 2);


}
void accessories_girl() {


    glColor4f(0.75f, 0.35f, 0.9f, 1);
    drawFilledCircle(0.1, -0.10, 0.05, 2);
    drawFilledCircle(-0.1, -0.10, 0.05, 2);

    glBegin(GL_TRIANGLES);
    glColor4f(0.75f, 0.35f, 0.9f, 1);
    //right
    glVertex2f(0.08, -0.052);
    glVertex2f(0.1, -0.15);
    glColor4f(0.50f, 0.05f, 0.60f, 1);
    glVertex2f(0.0, -0.15);
    //left
    glVertex2f(0.0, -0.15);
    glColor4f(0.75f, 0.35f, 0.9f, 1);
    glVertex2f(-0.08, -0.052);
    glVertex2f(-0.1, -0.15);

    glEnd();

    drawFilledCircle(0.0, -0.15, 0.03, 1);
}
void accessories_boy() {

    glColor4f(0.2f, 0.4f, 0.5f, 1);
    drawFilledCircle(0.0, -0.15, 0.10, 1);

    glColor4f(0.20f, 0.30f, 0.40f, 1);
    drawFilledCircle(0.1, -0.12, 0.03, 2);

    glBegin(GL_TRIANGLES);
    glColor4f(0.20f, 0.30f, 0.40f, 1);

    glVertex2f(0.08, -0.10);
    glVertex2f(0.1, -0.15);
    glColor4f(0.0f, 0.10f, 0.20f, 1);
    glVertex2f(-0.035, -0.15);
    glEnd();

    drawFilledCircle(0.0, -0.05, 0.013, 2);

}
void accessories_baby() {


    glColor4f(1.0f, 0.9f, 0.3f, 1);
    drawFilledCircle(0.0175, -0.34, 0.025, 2);
    drawFilledCircle(-0.0175, -0.34, 0.025, 2);

    glColor4f(1.0f, 0.7f, 0.0f, 1);
    drawFilledCircle(0.0, -0.36, 0.025, 2);

    glColor4f(1.0f, 0.9f, 0.3f, 1);
    drawFilledCircle(0.0, -0.355, 0.02, 2);

    glColor4f(1.0f, 0.6f, 0.1f, 1);
    drawFilledCircle(0.0, -0.34, 0.01, 2);

}
void accessories_father() {

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawHollowCircle(0.05, -0.28, 0.045, 2);///right
    drawHollowCircle(-0.05, -0.28, 0.045, 2);///left
    ///right
    glBegin(GL_LINES);
    glVertex2f(0.095, -0.28);
    glVertex2f(0.22, -0.2);
    glEnd();
    //left
    glBegin(GL_LINES);
    glVertex2f(-0.095, -0.28);
    glVertex2f(-0.22, -0.2);
    glEnd();

    //MOUTH
    glColor3f(0.4f, 0.4f, 0.4f);//black
    drawFilledCircle(0.017, -0.375, 0.022, 2);
    drawFilledCircle(-0.017, -0.375, 0.022, 2);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0);//white
    drawFilledCircle(0.0175, -0.37, 0.020, 2);
    drawFilledCircle(-0.0175, -0.37, 0.020, 2);

    ///mostash

    ////
    glColor3f(0.0f, 0.0f, 0.0f);//black
    drawFilledCircle(0.017, -0.35, 0.022, 2);//right
    drawFilledCircle(-0.017, -0.35, 0.022, 2);//left
    //right
    glBegin(GL_TRIANGLES);
    glVertex2f(0.03, -0.328);
    glVertex2f(0.03, -0.372);
    glVertex2f(0.085, -0.35);
    glEnd();
    //left
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03, -0.328);
    glVertex2f(-0.03, -0.372);
    glVertex2f(-0.085, -0.35);
    glEnd();

}
void accessories_mother() {

    glColor4f(1.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.1, -0.10, 0.05, 2);
    drawFilledCircle(-0.1, -0.10, 0.05, 2);

    glBegin(GL_TRIANGLES);
    glColor4f(1.0f, 0.0f, 0.0f, 1);
    //right
    glVertex2f(0.08, -0.052);
    glVertex2f(0.1, -0.15);
    glColor4f(0.6f, 0.0f, 0.0f, 1);
    glVertex2f(0.0, -0.15);
    //left
    glVertex2f(0.0, -0.15);
    glColor4f(1.0f, 0.0f, 0.0f, 1);
    glVertex2f(-0.08, -0.052);
    glVertex2f(-0.1, -0.15);

    glEnd();

    drawFilledCircle(0.0, -0.15, 0.03, 1);
}
void carrot() {

    //drawFilledCircle(-0.215, -0.585, 0.035);

    //CARROT1
    glColor3f(1.0f, 0.545f, 0.0f);//
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.235, -0.6);
    glVertex2f(-0.195, -0.6);
    glVertex2f(-0.215, -0.7);
    glEnd();

    glColor3f(0.89f, 0.518f, 0.0f);//ORANGE
    drawFilledCircle(-0.215, -0.588, 0.02, 2);

    glColor3f(1.0f, 0.545f, 0.0f);//ORANGE
    drawFilledCircle(-0.215, -0.585, 0.02, 2);

    //leaf base
    glColor3f(0.078f, 0.431f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.2, -0.58);
    glVertex2f(-0.23, -0.58);
    glVertex2f(-0.23, -0.57);
    glVertex2f(-0.2, -0.57);
    glEnd();

    ////left leaf
    glColor3f(0.078f, 0.431f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.23, -0.57);
    glVertex2f(-0.23, -0.56);
    glVertex2f(-0.21, -0.58);
    glEnd();

    //center leaf
    glColor3f(0.078f, 0.431f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.224, -0.58);
    glVertex2f(-0.216, -0.55);
    glVertex2f(-0.208, -0.58);
    glEnd();

    //right leaf
    glColor3f(0.078f, 0.431f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.215, -0.57);
    glVertex2f(-0.2, -0.56);
    glVertex2f(-0.2, -0.58);
    glEnd();


    //CARROT2
    glColor3f(1.0f, 0.545f, 0.0f);//ORANGE
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.270, -0.6);
    glVertex2f(-0.230, -0.6);
    glVertex2f(-0.25, -0.7);
    glEnd();

    glColor3f(0.89f, 0.518f, 0.0f);//ORANGE
    drawFilledCircle(-0.25, -0.605, 0.02, 2);

    glColor3f(1.0f, 0.545f, 0.0f);//ORANGE
    drawFilledCircle(-0.25, -0.6, 0.02, 2);

    //CARROT3
    glColor3f(1.0f, 0.545f, 0.0f);//ORANGE
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.158, -0.6);
    glVertex2f(-0.199, -0.6);
    glVertex2f(-0.18, -0.7);
    glEnd();

    glColor3f(0.89f, 0.518f, 0.0f);//ORANGE
    drawFilledCircle(-0.179, -0.605, 0.02, 2);

    glColor3f(1.0f, 0.545f, 0.0f);//ORANGE
    drawFilledCircle(-0.179, -0.6, 0.02, 2);

}

void thinkingCloud()
{
    //thinking cloud
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.328525163992, -0.4459591727961, 0.02, 2);
    drawFilledCircle(0.4244997717381, -0.3876454870769, 0.04, 2);
    drawFilledCircle(0.5047030329057, -0.2647367076464, 0.09, 2);
    drawFilledCircle(0.6280889823958, -0.2506354562761, 0.12, 2);
    drawFilledCircle(0.7285603984091, -0.1660279480543, 0.08, 2);
    drawFilledCircle(0.6668674236641, -0.0955216912029, 0.08, 2);
    drawFilledCircle(0.5787346025998, -0.0849457526752, 0.08, 2);
    drawFilledCircle(0.4676872480587, -0.0955216912029, 0.11, 2);
    drawFilledCircle(0.420095524684, -0.2012810764801, 0.1, 2);
    //numbers
    //number 1
    glLineWidth(2);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.4376280262, -0.1583566762168);
    glVertex2f(0.4438492345718, -0.1524888970144);
    glVertex2f(0.4498813447537, -0.1522016536724);
    glVertex2f(0.4475833980177, -0.1995968051012);

    glEnd();
    //number 2
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.4823398423988, -0.1631169006681);
    glVertex2f(0.4854995191607, -0.1544996004083);
    glVertex2f(0.4946913061045, -0.1522016536724);
    glVertex2f(0.5035958497063, -0.1567975471443);
    glVertex2f(0.5044575797323, -0.166851064114);
    glVertex2f(0.48, -0.2);
    glVertex2f(0.5070427698102, -0.1995968051012);
    glEnd();
    //number 3
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.5372033207194, -0.1625424139841);
    glVertex2f(0.5423737008753, -0.1539251137244);
    glVertex2f(0.5501292711091, -0.1527761403564);
    glVertex2f(0.5564486246329, -0.1556485737763);
    glVertex2f(0.56, -0.16);
    glVertex2f(0.5596083013948, -0.1654148474041);
    glVertex2f(0.5575975980009, -0.1711597142439);
    glVertex2f(0.553001704529, -0.1754683643738);
    glVertex2f(0.5478313243731, -0.1760428510578);
    glVertex2f(0.5570231113169, -0.1797770145037);
    glVertex2f(0.5596083013948, -0.1843729079756);
    glVertex2f(0.5598955447368, -0.1895432881314);
    glVertex2f(0.5587465713689, -0.1952881549713);
    glVertex2f(0.555012407923, -0.1981605883912);
    glVertex2f(0.5501292711091, -0.2001712917852);
    glVertex2f(0.5455333776372, -0.1998840484432);
    glVertex2f(0.5409760173582, -0.1983217255595);
    glVertex2f(0.5363170662938, -0.190720279086);
    glEnd();

    //number 4
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.6100950557377, -0.1539837737823);
    glVertex2f(0.5930415358552, -0.1924317095175);
    glVertex2f(0.6218774876566, -0.1927417735154);
    glVertex2f(0.616296335695, -0.1750681256371);
    glVertex2f(0.6156762076993, -0.2011135014577);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.616296335695, -0.1750681256371);
    glVertex2f(0.6156762076993, -0.2011135014577);
    glEnd();
    //?
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.649010019223, -0.1646934174102);
    glVertex2f(0.651348943626, -0.1580664649352);
    glVertex2f(0.6591453583026, -0.1549478990645);
    glVertex2f(0.6663570418784, -0.1567020923668);
    glVertex2f(0.6692806973821, -0.1619646722734);
    glVertex2f(0.67, -0.17);
    glVertex2f(0.6669417729791, -0.1736592942883);
    glVertex2f(0.6618741034394, -0.1806760674972);
    glVertex2f(0.660314820504, -0.1841844541017);
    glVertex2f(0.66, -0.19);
    glEnd();

    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2f(0.6587187634573, -0.2005569249225);
    glEnd();

    //!
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.6857566085377, -0.1545363738868);
    glVertex2f(0.6848527023129, -0.1908432739152);
    glEnd();


    glBegin(GL_POINTS);
    glVertex2f(0.6848527023129, -0.2004849403128);
    glEnd();

}

void drawCave2() {
    glPushMatrix();
    //outer line
    glBegin(GL_POLYGON);
    // glColor3f(0.71, 0.569, 0.506);//b59181
     //glColor3f(0.773, 0.71, 0.612);
    glColor4f(0.6745f, 0.5490f, 0.4235f, 0.9);// light
    //    glColor4f(0.7333f, 0.5921f, 0.4549f, 1); //bit darker
    glColor3f(0.2549f, 0.1764f, 0.1686f);//dark
    // glColor4f(0.5254f, 0.4196f, 0.3137f, 1.0);//bit bit darker
    glVertex2f(-0.3774609664515, -0.455358888729);
    glVertex2f(-0.7916804531199, -0.4534050232259);
    glVertex2f(-0.7697686078601, -0.3293554325366);
    glVertex2f(-0.6935179304471, -0.2228357872808);
    glVertex2f(-0.7, -0.2);
    glVertex2f(-0.66167637155, -0.1220041841068);
    glVertex2f(-0.5829776937063, 0.0636064155758);
    glVertex2f(-0.4776184132713, 0.2403381117893);
    glVertex2f(-0.4466723718922, 0.2435661568713);
    glVertex2f(-0.4099654496936, 0.3292156420013);
    glVertex2f(-0.3610228867622, 0.3769346408595);
    glVertex2f(-0.2937268627314, 0.4760433307957);
    glVertex2f(-0.1, 0.6);
    glVertex2f(0.05, 0.65);
    glVertex2f(0.1573472959914, 0.6346832738073);
    glVertex2f(0.25, 0.65);
    glVertex2f(0.318742908845, 0.642577624436);
    glVertex2f(0.4389124684153, 0.5724056188475);
    glVertex2f(0.4862785721876, 0.5443368166121);

    glVertex2f(0.5310132257502, 0.5636341181489);
    glVertex2f(0.6546913856, 0.526793815215);
    glVertex2f(0.6924088386038, 0.4873220620714);
    glVertex2f(0.7345120419569, 0.4241672570418);
    glVertex2f(0.7574916883096, 0.3544901487461);
    glVertex2f(0.7895530385637, 0.3056803319413);
    glVertex2f(0.8173076402762, 0.2611772636782);
    glVertex2f(0.857025432382, 0.223852109651);
    glVertex2f(0.8780806474742, 0.1630791024529);
    glVertex2f(0.8924364759462, 0.1085269542594);
    glVertex2f(0.9, 0.04);
    glVertex2f(0.9, -0.1);
    glVertex2f(0.9101364001263, -0.2384798178791);
    glVertex2f(0.9209004280314, -0.461757224504);
    glVertex2f(0.4529318723885, -0.4944361987921);
    glVertex2f(0.2594991875764, -0.5002977953015);
    glVertex2f(0.1, -0.5);
    glEnd();
    ////////////////////////////////////////////////////////////
    //inside cave shade
    glBegin(GL_POLYGON);
    //glColor3f(0.459, 0.424, 0.31);
    //glColor4f(0.5254f, 0.4196f, 0.3137f, 1.0);//bit bit darker
    glColor3f(0.42, 0.294, 0.286);
    glVertex2f(0.1934180545841, -0.3468150094993);
    glVertex2f(0.2457967854723, -0.3046210318394);
    glVertex2f(0.2748960804102, -0.2420575477229);
    glVertex2f(0.3039953753481, -0.1809490283534);
    glVertex2f(0.2661662919288, -0.1271153327183);
    glVertex2f(0.3113069668642, -0.1748006137485);
    glVertex2f(0.2661662919288, -0.1271153327183);
    glVertex2f(0.2748960804102, -0.0776465313238);
    glVertex2f(0.2210623847751, 0.0038314945023);
    glVertex2f(0.1701386186338, 0.1245935684945);
    glVertex2f(0.1, 0.2);
    glVertex2f(0.0435566856539, 0.2875496201467);
    glVertex2f(-0.039376304919, 0.3501131042632);
    glVertex2f(-0.1121245422638, 0.3370184215411);
    glVertex2f(-0.1994224270774, 0.2511755014743);
    glVertex2f(-0.2561660522063, 0.1696974756482);
    glVertex2f(-0.3318242190449, 0.104224062038);
    glVertex2f(-0.3754731614517, 0.0576651901374);
    glVertex2f(-0.3551036549952, -0.0325426241701);
    glVertex2f(-0.3551036549952, -0.1271153327183);
    glVertex2f(-0.3740181967048, -0.2304178297478);
    glVertex2f(-0.3914777736675, -0.3220806088021);
    glVertex2f(-0.2227018630278, -0.4035586346282);
    glEnd();

    ///////////////////////////////////////////////////////
    //overline for the outter line
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.3774609664515, -0.455358888729);
    glVertex2f(-0.7916804531199, -0.4534050232259);
    glVertex2f(-0.7697686078601, -0.3293554325366);
    glVertex2f(-0.6935179304471, -0.2228357872808);
    glVertex2f(-0.7, -0.2);
    glVertex2f(-0.66167637155, -0.1220041841068);
    glVertex2f(-0.5829776937063, 0.0636064155758);
    glVertex2f(-0.4776184132713, 0.2403381117893);
    glVertex2f(-0.4466723718922, 0.2435661568713);
    glVertex2f(-0.4099654496936, 0.3292156420013);
    glVertex2f(-0.3610228867622, 0.3769346408595);
    glVertex2f(-0.2937268627314, 0.4760433307957);
    glVertex2f(-0.1, 0.6);
    glVertex2f(0.05, 0.65);
    glVertex2f(0.1573472959914, 0.6346832738073);
    glVertex2f(0.25, 0.65);
    glVertex2f(0.318742908845, 0.642577624436);
    glVertex2f(0.4389124684153, 0.5724056188475);
    glVertex2f(0.4862785721876, 0.5443368166121);
    glVertex2f(0.5310132257502, 0.5636341181489);
    glVertex2f(0.6546913856, 0.526793815215);
    glVertex2f(0.6924088386038, 0.4873220620714);
    glVertex2f(0.7345120419569, 0.4241672570418);
    glVertex2f(0.7574916883096, 0.3544901487461);
    glVertex2f(0.7895530385637, 0.3056803319413);
    glVertex2f(0.8173076402762, 0.2611772636782);
    glVertex2f(0.857025432382, 0.223852109651);
    glVertex2f(0.8780806474742, 0.1630791024529);
    glVertex2f(0.8924364759462, 0.1085269542594);
    glVertex2f(0.9, 0.04);
    glVertex2f(0.9, -0.1);
    glVertex2f(0.9101364001263, -0.2384798178791);
    glVertex2f(0.9209004280314, -0.461757224504);
    glVertex2f(0.4529318723885, -0.4944361987921);
    glVertex2f(0.2594991875764, -0.5002977953015);
    glVertex2f(0.1, -0.5);
    glVertex2f(0.152679041671, -0.4108334583627);
    glVertex2f(0.1934180545841, -0.3468150094993);
    glVertex2f(0.2457967854723, -0.3046210318394);
    glVertex2f(0.2748960804102, -0.2420575477229);
    glVertex2f(0.3039953753481, -0.1809490283534);
    glVertex2f(0.2661662919288, -0.1271153327183);
    glVertex2f(0.3113069668642, -0.1748006137485);
    glVertex2f(0.2661662919288, -0.1271153327183);
    glVertex2f(0.2748960804102, -0.0776465313238);
    glVertex2f(0.2210623847751, 0.0038314945023);
    glVertex2f(0.1701386186338, 0.1245935684945);
    glVertex2f(0.1, 0.2);
    glVertex2f(0.0435566856539, 0.2875496201467);
    glVertex2f(-0.039376304919, 0.3501131042632);
    glVertex2f(-0.1121245422638, 0.3370184215411);
    glVertex2f(-0.1994224270774, 0.2511755014743);
    glVertex2f(-0.2561660522063, 0.1696974756482);
    glVertex2f(-0.3318242190449, 0.104224062038);
    glVertex2f(-0.3754731614517, 0.0576651901374);
    glVertex2f(-0.3551036549952, -0.0325426241701);
    glVertex2f(-0.3551036549952, -0.1271153327183);
    glVertex2f(-0.3740181967048, -0.2304178297478);
    glVertex2f(-0.3914777736675, -0.3220806088021);
    glEnd();


    //////////////////////////////////////////////////////
    //   top shade

    glBegin(GL_POLYGON);
    // glColor3f(0.655, 0.627, 0.525);


    glColor3f(0.349, 0.267, 0.259);


    glVertex2f(0.2996304811074, 0.587272358007);
    glVertex2f(0.2181524552813, 0.6192815824387);
    glVertex2f(0.1573472959914, 0.6346832738073);
    glVertex2f(0.1573472959914, 0.6346832738073);
    glVertex2f(0.25, 0.65);
    glVertex2f(0.318742908845, 0.642577624436);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.4389124684153, 0.5724056188475);
    glVertex2f(0.4862785721876, 0.5443368166121);
    glVertex2f(0.5363705229793, 0.5088641523404);
    glVertex2f(0.5149652636478, 0.4810599314837);
    glVertex2f(0.4756812154816, 0.4665102840147);
    glVertex2f(0.5527943470671, 0.325378703566);
    glVertex2f(0.6, 0.2);
    glVertex2f(0.6, 0.1);
    glVertex2f(0.5469744880795, 0.2569953604619);
    glVertex2f(0.4640414975065, 0.4039467998983);
    glVertex2f(0.3942031896555, 0.4563255307865);
    glVertex2f(0.3534641767425, 0.5203439796498);
    glEnd();

    ////////////////////////////////////////////////////////
    //overline the shade
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.1573472959914, 0.6346832738073);
    glVertex2f(0.25, 0.65);
    glVertex2f(0.318742908845, 0.642577624436);
    glVertex2f(0.4389124684153, 0.5724056188475);
    glVertex2f(0.4862785721876, 0.5443368166121);

    glVertex2f(0.5363705229793, 0.5088641523404);
    glVertex2f(0.5149652636478, 0.4810599314837);
    glVertex2f(0.4756812154816, 0.4665102840147);
    glVertex2f(0.5527943470671, 0.325378703566);
    glVertex2f(0.6, 0.2);

    glVertex2f(0.6, 0.1);
    glVertex2f(0.5469744880795, 0.2569953604619);
    glVertex2f(0.4640414975065, 0.4039467998983);
    glVertex2f(0.3942031896555, 0.4563255307865);
    glVertex2f(0.3534641767425, 0.5203439796498);

    glVertex2f(0.2996304811074, 0.587272358007);
    glVertex2f(0.2181524552813, 0.6192815824387);
    glVertex2f(0.1573472959914, 0.6346832738073);
    glEnd();

    ////////////////////////////////////////////////////////////////
    //right crack
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.5863879969057, -0.1562584902985);
    glVertex2f(0.4582216385189, -0.0019883644853);
    glVertex2f(0.3534641767425, 0.0736698023532);
    glVertex2f(0.1934180545841, 0.3719375754666);
    glVertex2f(0.3112701990826, 0.0562102253905);
    glVertex2f(0.3112701990826, 0.0562102253905);
    glVertex2f(0.471316321241, -0.102380932021);
    glVertex2f(0.4305773083279, -0.1183855442369);
    glVertex2f(0.4785911449754, -0.1984086053161);
    glVertex2f(0.4407620615562, -0.3046210318394);
    glEnd();

    //////////////////////////////////////////////////////
    //top crack
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.1192148524925, 0.4679652487616);
    glVertex2f(0.056651368376, 0.4956095789526);
    glVertex2f(-0.0277365869439, 0.5014294379402);
    glVertex2f(-0.1106695775169, 0.4810599314837);
    glVertex2f(-0.1906926385961, 0.4403209185706);
    glVertex2f(-0.2838103823973, 0.3733925402135);
    glVertex2f(-0.3623784787296, 0.3020992676156);
    glVertex2f(-0.434561607005, 0.2388831049282);
    glEnd();

    /////////////////////////////////////////////////////////
    //left carck
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.4715008347467, 0.0562102253905);
    glVertex2f(-0.5195146713943, 0.0140162477305);
    glVertex2f(-0.5878980144983, -0.0849213550583);
    glVertex2f(-0.6300919921582, -0.1605795218968);
    glVertex2f(-0.6935179304471, -0.2228357872808);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.3754731614517, 0.0576651901374);
    glVertex2f(-0.4074823858834, 0.0823995908346);
    glVertex2f(-0.3943877031613, -0.0179929767012);
    glVertex2f(-0.4744107642405, -0.1663993808844);
    glVertex2f(-0.4569511872778, -0.2376926534822);
    glEnd();

    //small crack on the left
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.4626427355998, -0.3227394669676);
    glVertex2f(-0.5020550944315, -0.3817341634248);
    glVertex2f(-0.5468861213841, -0.4591335201423);
    glVertex2f(-0.5468861213841, -0.4591335201423);
    glEnd();

    //////////////////////////////////////////////////////////
    //dots
    glPushMatrix();
    glTranslatef(0.3316520446529, 0.3552192091067, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.01, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2514202486678, 0.4575147489877, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.02, 25, 25);
    glPopMatrix();

    ///////////////////////////////////////////////////////////
    //rock1
    glBegin(GL_POLYGON);
    glColor3f(0.361, 0.353, 0.361);
    glVertex2f(-0.520810787689, -0.493232033436);
    glVertex2f(-0.4847064794957, -0.4410813660457);
    glVertex2f(-0.4365674019046, -0.4150060323505);
    glVertex2f(-0.4185152478079, -0.4410813660457);
    glVertex2f(-0.4686601202986, -0.4972436232352);
    glVertex2f(-0.4104920682094, -0.4832030589378);
    glVertex2f(-0.3583414008191, -0.4671566997408);
    glVertex2f(-0.3904341192131, -0.4290465966479);
    glVertex2f(-0.4365674019046, -0.4150060323505);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.4847064794957, -0.4410813660457);
    glVertex2f(-0.520810787689, -0.493232033436);
    glVertex2f(-0.4686601202986, -0.4972436232352);
    glVertex2f(-0.4104920682094, -0.4832030589378);
    glVertex2f(-0.3583414008191, -0.4671566997408);
    glVertex2f(-0.3904341192131, -0.4290465966479);
    glVertex2f(-0.4365674019046, -0.4150060323505);
    glEnd();

    //////////////////////////////////////////////////////////
    //drak grass on the right
    glPushMatrix();
    glTranslatef(0.04, -0.12, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.392, 0.204);
    glVertex2f(0.8905365927871, 0.0249196068538);
    glVertex2f(0.8591820282587, 0.0053230040236);
    glVertex2f(0.8278274637304, 0.0014036834576);
    glVertex2f(0.7768762963719, -0.0260315605047);
    glVertex2f(0.8239081431644, -0.0652247661652);
    glVertex2f(0.8056179805228, 0.0549677311935);

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.7611990141077, -0.0717569671086);
    glVertex2f(0.6762804018434, -0.1135630531463);
    glVertex2f(0.7363766505228, -0.1997881055993);
    glVertex2f(0.5678458661829, -0.3722382105051);
    glVertex2f(0.6932641242963, -0.3265128039013);
    glVertex2f(0.7037156458057, -0.4179636171089);
    glVertex2f(0.8134566216549, -0.4114314161655);
    glVertex2f(0.8408918656172, -0.3330450048447);
    glVertex2f(0.9258104778814, -0.3748510908825);
    glVertex2f(0.8853108320323, -0.2938517991843);
    glVertex2f(0.9650036835419, -0.2873195982409);
    glVertex2f(0.8761657507116, -0.2063203065427);
    glVertex2f(0.9610843629758, -0.1736593018256);
    glVertex2f(0.8892301525984, -0.1240145746558);
    glVertex2f(0.9689230041079, -0.0560796848444);
    glVertex2f(0.8931494731644, -0.0377895222029);
    glVertex2f(0.9506328414664, 0.0066294442123);
    glVertex2f(0.9, 0);
    glVertex2f(0.9245040376928, 0.0432097694953);
    glVertex2f(0.8905365927871, 0.0249196068538);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.8056179805228, 0.0549677311935);
    glVertex2f(0.8223539297956, -0.0166226075071);
    glVertex2f(0.7768762963719, -0.0260315605047);
    glVertex2f(0.8043115403341, -0.0482410437123);
    glVertex2f(0.6783560300089, -0.117807709514);
    glVertex2f(0.7123855264945, -0.1551221054655);
    glVertex2f(0.5678458661829, -0.3722382105051);
    glVertex2f(0.6932641242963, -0.3265128039013);
    glVertex2f(0.7037156458057, -0.4179636171089);
    glVertex2f(0.7690376552398, -0.3500287272975);
    glVertex2f(0.8134566216549, -0.4114314161655);
    glVertex2f(0.8408918656172, -0.3330450048447);
    glVertex2f(0.9258104778814, -0.3748510908825);
    glVertex2f(0.8853108320323, -0.2938517991843);
    glVertex2f(0.9650036835419, -0.2873195982409);
    glVertex2f(0.8761657507116, -0.2063203065427);
    glVertex2f(0.9610843629758, -0.1736593018256);
    glVertex2f(0.8892301525984, -0.1240145746558);
    glVertex2f(0.9689230041079, -0.0560796848444);
    glVertex2f(0.8931494731644, -0.0377895222029);
    glVertex2f(0.9506328414664, 0.0066294442123);
    glVertex2f(0.9, 0);
    glVertex2f(0.9245040376928, 0.0432097694953);
    glVertex2f(0.8905365927871, 0.0249196068538);
    glEnd();
    glPopMatrix();
    /////////////////////////////////////////////////////////////////////////////
    //leftside right grass

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.608, 0.208);
    glVertex2f(-0.7, -0.5);
    glVertex2f(-0.7186194102455, -0.5295914658544);
    glVertex2f(-0.6695885565977, -0.5147531811979);
    glVertex2f(-0.6605565572415, -0.5366880367772);
    glVertex2f(-0.6366862732287, -0.5057211818417);
    glVertex2f(-0.604429132671, -0.5315268942879);
    glVertex2f(-0.6153965604606, -0.4883023259405);
    glVertex2f(-0.55, -0.5);
    glVertex2f(-0.5678965934078, -0.464114605227);
    glVertex2f(-0.6031713052311, -0.4379851890616);
    glVertex2f(-0.5457211368558, -0.4302394729365);
    glVertex2f(-0.5915262764479, -0.3954017611341);
    glVertex2f(-0.633460559173, -0.3921760470783);
    glVertex2f(-0.5908811336367, -0.3547577640313);
    glVertex2f(-0.6405571300957, -0.3560480496536);
    glVertex2f(-0.6831365556319, -0.3728217627437);
    glVertex2f(-0.7256963569331, -0.4032128290892);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.7, -0.5);
    glVertex2f(-0.7186194102455, -0.5295914658544);
    glVertex2f(-0.6695885565977, -0.5147531811979);
    glVertex2f(-0.6605565572415, -0.5366880367772);
    glVertex2f(-0.6366862732287, -0.5057211818417);
    glVertex2f(-0.604429132671, -0.5315268942879);
    glVertex2f(-0.6153965604606, -0.4883023259405);
    glVertex2f(-0.55, -0.5);
    glVertex2f(-0.5678965934078, -0.464114605227);
    glVertex2f(-0.6031713052311, -0.4379851890616);
    glVertex2f(-0.5457211368558, -0.4302394729365);
    glVertex2f(-0.5915262764479, -0.3954017611341);
    glVertex2f(-0.633460559173, -0.3921760470783);
    glVertex2f(-0.5908811336367, -0.3547577640313);
    glVertex2f(-0.6405571300957, -0.3560480496536);
    glVertex2f(-0.6831365556319, -0.3728217627437);
    glVertex2f(-0.7256963569331, -0.4032128290892);
    glEnd();
    ///////////////////////////////////////////////////////
    //leftside left grass
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.392, 0.204);
    glVertex2f(-0.6913033541574, -0.196374388291);
    glVertex2f(-0.7895873042391, -0.1341947464026);
    glVertex2f(-0.7615061756443, -0.1843396188933);
    glVertex2f(-0.8597901257261, -0.1723048494955);
    glVertex2f(-0.9380161268116, -0.2124207474881);
    glVertex2f(-0.8377263818302, -0.2465192607817);
    glVertex2f(-0.9099349982168, -0.2926525434732);
    glVertex2f(-0.936010331912, -0.3347742363654);
    glVertex2f(-0.8691402136454, -0.3491999924806);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.9059234084176, -0.3809075190568);
    glVertex2f(-0.9420111975525, -0.4310576861175);
    glVertex2f(-0.9540325715707, -0.4911645562089);
    glVertex2f(-0.8711549825541, -0.4505714513844);
    glVertex2f(-0.8796118793925, -0.5249921435626);
    glVertex2f(-0.806882566582, -0.4759421418997);
    glVertex2f(-0.7595239442868, -0.5622024896517);
    glVertex2f(-0.7406928190711, -0.4845235859079);
    glVertex2f(-0.6766463552702, -0.5030042117827);
    glVertex2f(-0.7256963569331, -0.4032128290892);
    glVertex2f(-0.6512756647549, -0.3913731735154);
    glVertex2f(-0.7003256664178, -0.3389404131171);
    glVertex2f(-0.7520588611807, -0.315085284177);
    glVertex2f(-0.6913033541574, -0.196374388291);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.6913033541574, -0.196374388291);
    glVertex2f(-0.7895873042391, -0.1341947464026);
    glVertex2f(-0.7615061756443, -0.1843396188933);
    glVertex2f(-0.8597901257261, -0.1723048494955);
    glVertex2f(-0.9380161268116, -0.2124207474881);
    glVertex2f(-0.8377263818302, -0.2465192607817);
    glVertex2f(-0.9099349982168, -0.2926525434732);
    glVertex2f(-0.936010331912, -0.3347742363654);
    glVertex2f(-0.8691402136454, -0.3491999924806);
    glVertex2f(-0.9059234084176, -0.3809075190568);
    glVertex2f(-0.9420111975525, -0.4310576861175);
    glVertex2f(-0.9540325715707, -0.4911645562089);
    glVertex2f(-0.8841700823239, -0.4567389711014);
    glVertex2f(-0.8796118793925, -0.5249921435626);
    glVertex2f(-0.806882566582, -0.4759421418997);
    glVertex2f(-0.7595239442868, -0.5622024896517);
    glVertex2f(-0.7406928190711, -0.4845235859079);
    glVertex2f(-0.6766463552702, -0.5030042117827);
    glVertex2f(-0.7256963569331, -0.4032128290892);
    glVertex2f(-0.6512756647549, -0.3913731735154);
    glVertex2f(-0.7003256664178, -0.3389404131171);
    glVertex2f(-0.7520588611807, -0.315085284177);
    glVertex2f(-0.6913033541574, -0.196374388291);
    glEnd();
    //////////////////////////////////////////
    //rightside bottom grass

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.608, 0.208);
    glVertex2f(0.3565440176884, -0.376926952972);
    glVertex2f(0.2815690915668, -0.4035309590151);
    glVertex2f(0.2247332604746, -0.4458555140838);
    glVertex2f(0.3166380086237, -0.4410184220759);
    glVertex2f(0.2731041805531, -0.4990635261701);
    glVertex2f(0.2791505455629, -0.5353417162289);
    glVertex2f(0.3771016587217, -0.4918078881583);
    glVertex2f(0.3783109317237, -0.5583179032662);
    glVertex2f(0.4121705757786, -0.5413880812387);
    glVertex2f(0.4351467628159, -0.5776662712975);
    glVertex2f(0.4653785878649, -0.5438066272426);
    glVertex2f(0.5052845969296, -0.5716199062877);
    glVertex2f(0.5379349679826, -0.5389695352348);
    glVertex2f(0.587515161063, -0.5788755442995);
    glVertex2f(0.620165532116, -0.5401788082367);
    glVertex2f(0.6564437221748, -0.5716199062877);
    glVertex2f(0.6987682772434, -0.5305046242211);
    glVertex2f(0.7338371943003, -0.5522715382564);
    glVertex2f(0.7616504733454, -0.5196211672034);
    glVertex2f(0.8305790344572, -0.5534808112583);
    glVertex2f(0.8, -0.5);
    glVertex2f(0.9140188715925, -0.5026913451759);
    glVertex2f(0.8329975804611, -0.4591575171053);
    glVertex2f(0.9128095985906, -0.4325535110622);
    glVertex2f(0.8596015865043, -0.4180422350387);
    glVertex2f(0.7568133813376, -0.4337627840642);
    glVertex2f(0.8656479515141, -0.3720898609641);
    glVertex2f(0.7943008443984, -0.3599971309445);
    glVertex2f(0.7326279212983, -0.3745084069681);
    glVertex2f(0.5584926090159, -0.3720898609641);
    glVertex2f(0.3565440176884, -0.376926952972);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.3565440176884, -0.376926952972);
    glVertex2f(0.2815690915668, -0.4035309590151);
    glVertex2f(0.2247332604746, -0.4458555140838);
    glVertex2f(0.3166380086237, -0.4410184220759);
    glVertex2f(0.2731041805531, -0.4990635261701);
    glVertex2f(0.2791505455629, -0.5353417162289);
    glVertex2f(0.3771016587217, -0.4918078881583);
    glVertex2f(0.3783109317237, -0.5583179032662);
    glVertex2f(0.4121705757786, -0.5413880812387);
    glVertex2f(0.4351467628159, -0.5776662712975);
    glVertex2f(0.4653785878649, -0.5438066272426);
    glVertex2f(0.5052845969296, -0.5716199062877);
    glVertex2f(0.5379349679826, -0.5389695352348);
    glVertex2f(0.587515161063, -0.5788755442995);
    glVertex2f(0.620165532116, -0.5401788082367);
    glVertex2f(0.6564437221748, -0.5716199062877);
    glVertex2f(0.6987682772434, -0.5305046242211);
    glVertex2f(0.7338371943003, -0.5522715382564);
    glVertex2f(0.7616504733454, -0.5196211672034);
    glVertex2f(0.8305790344572, -0.5534808112583);
    glVertex2f(0.8, -0.5);
    glVertex2f(0.9140188715925, -0.5026913451759);
    glVertex2f(0.8329975804611, -0.4591575171053);
    glVertex2f(0.9128095985906, -0.4325535110622);
    glVertex2f(0.8596015865043, -0.4180422350387);
    glVertex2f(0.7568133813376, -0.4337627840642);
    glVertex2f(0.8656479515141, -0.3720898609641);
    glVertex2f(0.7943008443984, -0.3599971309445);
    glVertex2f(0.7326279212983, -0.3745084069681);
    glVertex2f(0.5584926090159, -0.3720898609641);
    glVertex2f(0.3565440176884, -0.376926952972);
    glEnd();
    //////////////////////////////////////////////////////
    //rightside left grass

    glBegin(GL_POLYGON);
    glColor3f(0.204, 0.8, 0.404);
    glVertex2f(0.4740659642378, -0.327590424447);
    glVertex2f(0.3952407537512, -0.3466951279229);
    glVertex2f(0.3553347446864, -0.3914382289955);
    glVertex2f(0.4532858578453, -0.3986938670073);
    glVertex2f(0.3945074987218, -0.4650882072411);
    glVertex2f(0.4382570880537, -0.4535589316772);
    glVertex2f(0.4307494064451, -0.5307807996517);
    glVertex2f(0.4972460149787, -0.4460512500686);
    glVertex2f(0.51333390414, -0.5329258515398);
    glVertex2f(0.5508723121832, -0.4675017689504);
    glVertex2f(0.5787579867295, -0.5168379623785);
    glVertex2f(0.6023535574995, -0.4803720802794);
    glVertex2f(0.6366743877104, -0.5039676510494);
    glVertex2f(0.6473996471513, -0.4439061981804);
    glVertex2f(0.6903006849148, -0.4814446062235);
    glVertex2f(0.6988808924676, -0.439616094404);
    glVertex2f(0.751434663728, -0.4535589316772);
    glVertex2f(0.7310566707903, -0.4074403160813);
    glVertex2f(0.7610873972248, -0.4042227382491);
    glVertex2f(0.5873381942822, -0.2519240541883);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.7610873972248, -0.4042227382491);
    glVertex2f(0.5873381942822, -0.2519240541883);
    glVertex2f(0.5026086446991, -0.2143856461452);
    glVertex2f(0.5390745267982, -0.2658668914615);
    glVertex2f(0.4961734890346, -0.2637218395733);
    glVertex2f(0.5039789688598, -0.2915468971306);
    glVertex2f(0.4500548734387, -0.3055503513928);
    glEnd();


    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.4936879479039, -0.3213113468146);
    glVertex2f(0.3952407537512, -0.3466951279229);
    glVertex2f(0.3553347446864, -0.3914382289955);
    glVertex2f(0.4532858578453, -0.3986938670073);
    glVertex2f(0.3945074987218, -0.4650882072411);
    glVertex2f(0.4382570880537, -0.4535589316772);
    glVertex2f(0.4307494064451, -0.5307807996517);
    glVertex2f(0.4972460149787, -0.4460512500686);
    glVertex2f(0.51333390414, -0.5329258515398);
    glVertex2f(0.5508723121832, -0.4675017689504);
    glVertex2f(0.5787579867295, -0.5168379623785);
    glVertex2f(0.6023535574995, -0.4803720802794);
    glVertex2f(0.6366743877104, -0.5039676510494);
    glVertex2f(0.6473996471513, -0.4439061981804);
    glVertex2f(0.6903006849148, -0.4814446062235);
    glVertex2f(0.6988808924676, -0.439616094404);
    glVertex2f(0.751434663728, -0.4535589316772);
    glVertex2f(0.7310566707903, -0.4074403160813);
    glVertex2f(0.7610873972248, -0.4042227382491);
    glVertex2f(0.5873381942822, -0.2519240541883);
    glVertex2f(0.5026086446991, -0.2143856461452);
    glVertex2f(0.5390745267982, -0.2658668914615);
    glVertex2f(0.4961734890346, -0.2637218395733);
    glVertex2f(0.5039789688598, -0.2915468971306);
    glVertex2f(0.4500548734387, -0.3055503513928);
    glEnd();
    ///////////////////////////////////////////////////////////////
    //rightside top grass
    glBegin(GL_POLYGON);
    glColor3f(0.204, 0.8, 0.404);
    glVertex2f(0.8905365927871, 0.0249196068538);
    glVertex2f(0.8591820282587, 0.0053230040236);
    glVertex2f(0.8278274637304, 0.0014036834576);
    glVertex2f(0.7768762963719, -0.0260315605047);
    glVertex2f(0.8239081431644, -0.0652247661652);
    glVertex2f(0.8056179805228, 0.0549677311935);

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.7611990141077, -0.0717569671086);
    glVertex2f(0.6762804018434, -0.1135630531463);
    glVertex2f(0.7363766505228, -0.1997881055993);
    glVertex2f(0.5678458661829, -0.3722382105051);
    glVertex2f(0.6932641242963, -0.3265128039013);
    glVertex2f(0.7037156458057, -0.4179636171089);
    glVertex2f(0.8134566216549, -0.4114314161655);
    glVertex2f(0.8408918656172, -0.3330450048447);
    glVertex2f(0.9258104778814, -0.3748510908825);
    glVertex2f(0.8853108320323, -0.2938517991843);
    glVertex2f(0.9650036835419, -0.2873195982409);
    glVertex2f(0.8761657507116, -0.2063203065427);
    glVertex2f(0.9610843629758, -0.1736593018256);
    glVertex2f(0.8892301525984, -0.1240145746558);
    glVertex2f(0.9689230041079, -0.0560796848444);
    glVertex2f(0.8931494731644, -0.0377895222029);
    glVertex2f(0.9506328414664, 0.0066294442123);
    glVertex2f(0.9, 0);
    glVertex2f(0.9245040376928, 0.0432097694953);
    glVertex2f(0.8905365927871, 0.0249196068538);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.8056179805228, 0.0549677311935);
    glVertex2f(0.8223539297956, -0.0166226075071);
    glVertex2f(0.7768762963719, -0.0260315605047);
    glVertex2f(0.8043115403341, -0.0482410437123);
    glVertex2f(0.6783560300089, -0.117807709514);
    glVertex2f(0.7123855264945, -0.1551221054655);
    glVertex2f(0.5678458661829, -0.3722382105051);
    glVertex2f(0.6932641242963, -0.3265128039013);
    glVertex2f(0.7037156458057, -0.4179636171089);
    glVertex2f(0.7690376552398, -0.3500287272975);
    glVertex2f(0.8134566216549, -0.4114314161655);
    glVertex2f(0.8408918656172, -0.3330450048447);
    glVertex2f(0.9258104778814, -0.3748510908825);
    glVertex2f(0.8853108320323, -0.2938517991843);
    glVertex2f(0.9650036835419, -0.2873195982409);
    glVertex2f(0.8761657507116, -0.2063203065427);
    glVertex2f(0.9610843629758, -0.1736593018256);
    glVertex2f(0.8892301525984, -0.1240145746558);
    glVertex2f(0.9689230041079, -0.0560796848444);
    glVertex2f(0.8931494731644, -0.0377895222029);
    glVertex2f(0.9506328414664, 0.0066294442123);
    glVertex2f(0.9, 0);
    glVertex2f(0.9245040376928, 0.0432097694953);
    glVertex2f(0.8905365927871, 0.0249196068538);
    glEnd();

    glPopMatrix();


}
void KemoFace() {
    // ------------------------------------------------------------------
// drawing the filled circle (EYES)
    glColor4f(1.0f, 1.0f, 1.0f, 1); //white eyes
    drawFilledCircle(0.05, -0.17, 0.06, 2);
    drawFilledCircle(-0.05, -0.17, 0.06, 2);

    glColor4f(0.26f, 0.18f, 0.32f, 1); //black eyes
    drawFilledCircle(0.04, -0.17, 0.03, 2);
    drawFilledCircle(-0.04, -0.17, 0.03, 2);

    glColor4f(1.0f, 1.0f, 1.0f, 1); //white shine eyes
    drawFilledCircle(0.03, -0.16, 0.005, 2);
    drawFilledCircle(-0.05, -0.16, 0.005, 2);
    drawFilledCircle(0.05, -0.17, 0.01, 2);
    drawFilledCircle(-0.03, -0.17, 0.01, 2);

    //mouth
    glPushMatrix();
    glRotatef(180, 0.0, 0.0, 1.0);
    glColor4f(0.73f, 0.61f, 0.76f, 1);
    drawFilledCircle(0.0, 0.25, 0.03, 1);
    glPopMatrix();
}
void sadKemo() {
    // ------------------------------------------------------------------
// drawing the filled circle (EYES)
    glColor4f(1.0f, 1.0f, 1.0f, 1); //white eyes
    drawFilledCircle(0.05, -0.17, 0.06, 2);
    drawFilledCircle(-0.05, -0.17, 0.06, 2);

    glColor4f(0.26f, 0.18f, 0.32f, 1); //black eyes
    drawFilledCircle(0.04, -0.17, 0.03, 2);
    drawFilledCircle(-0.04, -0.17, 0.03, 2);

    glColor4f(1.0f, 1.0f, 1.0f, 1); //white shine eyes
    drawFilledCircle(0.03, -0.16, 0.005, 2);
    drawFilledCircle(-0.05, -0.16, 0.005, 2);
    drawFilledCircle(0.05, -0.17, 0.01, 2);
    drawFilledCircle(-0.03, -0.17, 0.01, 2);
    //mouth
    glPushMatrix();
    glTranslatef(0.0, -0.54, 0.0);
    glColor4f(0.73f, 0.61f, 0.76f, 1);
    drawFilledCircle(0.0, 0.25, 0.03, 1);
    glPopMatrix();
}
void KemoSleepEyes() {

    // drawing the filled circle (EYES)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0.05, -0.19, 0.06, 2);
    drawFilledCircle(-0.05, -0.19, 0.06, 2);

    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    drawFilledCircle(0.05, -0.18, 0.06, 2);
    drawFilledCircle(-0.05, -0.18, 0.06, 2);

    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0.05, -0.17, 0.06, 2);
    drawFilledCircle(-0.05, -0.17, 0.06, 2);

    //mouth
    glLineWidth(1.5);
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex2f(-0.02, -0.28);
    glVertex2f(0.02, -0.28);
    glEnd();

    //Z
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.25, -0.01);
    glVertex2f(0.3, -0.01);
    glEnd();

    glBegin(GL_LINES);
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.3, -0.01);
    glVertex2f(0.25, -0.1);
    glEnd();

    glBegin(GL_LINES);
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.25, -0.1);
    glVertex2f(0.3, -0.1);
    glEnd();

    //z
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.32, -0.03);
    glVertex2f(0.36, -0.03);
    glEnd();

    glBegin(GL_LINES);
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.36, -0.03);
    glVertex2f(0.32, -0.08);
    glEnd();

    glBegin(GL_LINES);
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.32, -0.08);
    glVertex2f(0.36, -0.08);
    glEnd();
}
void rock() {
    //rook2
    glBegin(GL_POLYGON);
    glColor3f(0.361, 0.353, 0.361);
    glVertex2f(0.6, -0.01);
    glVertex2f(0.55, 0.11);
    glVertex2f(0.4, 0.12);
    glVertex2f(0.34, 0.09);
    glVertex2f(0.3, -0.02);
    glVertex2f(0.42, -0.01);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.6, -0.02);
    glVertex2f(0.55, 0.11);
    glVertex2f(0.4, 0.12);
    glVertex2f(0.34, 0.09);
    glVertex2f(0.3, -0.02);
    glVertex2f(0.42, -0.02);
    glEnd();

    //rook3
    glBegin(GL_POLYGON);
    glColor3f(0.361, 0.353, 0.361);
    glVertex2f(0.8, -0.01);
    glVertex2f(0.75, 0.11);
    glVertex2f(0.6, 0.12);
    glVertex2f(0.54, 0.09);
    glVertex2f(0.5, -0.02);
    glVertex2f(0.62, -0.01);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.8, -0.01);
    glVertex2f(0.75, 0.11);
    glVertex2f(0.6, 0.12);
    glVertex2f(0.54, 0.09);
    glVertex2f(0.5, -0.02);
    glVertex2f(0.62, -0.01);
    glEnd();

}
void Kemo_Without_Face()
{
    // ------------------------------------------------------------------
    glBegin(GL_TRIANGLES); //(PUR-CLOTHES)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    glVertex2f(0.1f, -0.58f); //right
    glVertex2f(-0.1f, -0.58f); //left

    glColor4f(0.12f, 0.0f, 0.32f, 1.0f);
    glVertex2f(0.0f, -0.25f); //center

    glEnd();
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(B-FEET & PUR-ARMS))

    glColor4f(0.13f, 0.05f, 0.19f, 1);
    //RIGHT-FEET
    glVertex2f(0.04, -0.4);   //right-up
    glVertex2f(0.005, -0.4);  //left-up
    glVertex2f(0.005, -0.7); //left-down
    glVertex2f(0.04, -0.7);  //right-down
    //LEFT-FEET
    glVertex2f(-0.005, -0.4);   //right-up
    glVertex2f(-0.04, -0.4);  //left-up
    glVertex2f(-0.04, -0.7); //left-down
    glVertex2f(-0.005, -0.7);  //right-down
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    //RIGHT-ARM
    glVertex2f(0.03, -0.22);   //right-up
    glVertex2f(0.0, -0.25);  //left-up
    glVertex2f(0.20, -0.60); //left-down
    glVertex2f(0.23, -0.57);  //right-down
    //LEFT-ARM
    glVertex2f(-0.03, -0.22);   //right-up
    glVertex2f(0.0, -0.25);  //left-up
    glVertex2f(-0.20, -0.60); //left-down
    glVertex2f(-0.23, -0.57);  //right-down
    glEnd();
    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0, 0, 0.15, 2);        //up
    drawFilledCircle(-0.20, -0.3, 0.10, 2); //left
    drawFilledCircle(0.20, -0.3, 0.10, 2);  //right
    // ------------------------------------------------------------------
    glBegin(GL_TRIANGLES); //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f); //BIG
    //big-right
    glVertex2f(0.14f, 0.05f);
    glVertex2f(0.0f, -0.25f); //center
    glVertex2f(0.286f, -0.25f);
    //big-left
    glVertex2f(-0.14f, 0.05f);
    glVertex2f(0.0f, -0.25f); //center
    glVertex2f(-0.286f, -0.25f);
    //big-down
    glVertex2f(-0.20f, -0.40f);
    glVertex2f(0.0f, 0.0f); //center
    glVertex2f(0.20f, -0.40f);
    //right-up-tail
    glVertex2f(0.20, 0.07);
    glVertex2f(0.14, 0.03);
    glColor4f(0.33f, 0.25f, 0.39f, 1);
    glVertex2f(0.22, 0.0); //tail
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    //left-up-head
    glVertex2f(0.16, 0.11);
    glVertex2f(0.02, 0.148); //head
    glVertex2f(0.14, 0.03);
    glEnd();

    // ------------------------------------------------------------------
    // drawing half filled circle (B-SHOES)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.04, -0.7, 0.035, 1);
    drawFilledCircle(-0.04, -0.7, 0.035, 1);
    // ------------------------------------------------------------------
    // drawing half filled circle (B-HANDS)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.215, -0.585, 0.035, 2); //midpoint formula = (x1 + x2)/2, (y1 + y2)/2.
    drawFilledCircle(-0.215, -0.585, 0.035, 2);
    // ------------------------------------------------------------------
    // drawing the filled circle //(B-FACE)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.09, -0.02, 0.03, 2);  //right-up
    drawFilledCircle(-0.09, -0.02, 0.03, 2); //left-up
    drawFilledCircle(-0.20, -0.3, 0.05, 2);  //left-down
    drawFilledCircle(0.20, -0.3, 0.05, 2);   //right-down
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(B-FACE)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.09, -0.02);  //right-up
    glVertex2f(-0.09, -0.02); //left-up
    glVertex2f(-0.20, -0.35);  //left-down
    glVertex2f(0.20, -0.35);   //right-down

    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.12, -0.02);  //right-up
    glVertex2f(-0.12, -0.02); //left-up
    glVertex2f(-0.25, -0.3);  //left-down
    glVertex2f(0.25, -0.3);   //right-down
    glEnd();
    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0.0, 0.02, 0.07, 2);
    drawFilledCircle(0.16, 0.07, 0.04, 2);

}
void sunR() {
    //sun shine

    glColor4f(0.973, 0.988, 0.271, 0.5);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.0562279068563, 0.4030634938519);
    glVertex2f(0.0181498319724, 0.3117817234712);
    glVertex2f(0.0384346698348, 0.3320665613336);
    glVertex2f(0.0463371141647, 0.310993376454);
    glVertex2f(0.1218493599833, 0.3856275729026);
    glVertex2f(0.1069225206935, 0.2995787346442);
    glVertex2f(0.1288737549431, 0.310993376454);
    glVertex2f(0.136776199273, 0.2899201915744);
    glVertex2f(0.2570689629607, 0.3408470550334);
    glVertex2f(0.1964835564319, 0.256554315515);
    glVertex2f(0.2228250375314, 0.253042118035);
    glVertex2f(0.2166786919415, 0.2249445381956);
    glVertex2f(0.3580446405089, 0.2442616243352);
    glVertex2f(0.2674796837725, 0.1634833286317);
    glVertex2f(0.3142123276809, 0.1509656561563);
    glVertex2f(0.2875079597332, 0.1259303112054);
    glVertex2f(0.3850706205838, 0.1056575505092);
    glVertex2f(0.2746918559402, 0.0531934939915);
    glVertex2f(0.3145794355598, 0.033713513247);
    glVertex2f(0.2821128009857, 0.0262925682015);
    glVertex2f(0.3637431964863, -0.0349302284239);
    glVertex2f(0.266343292764, -0.0256540471171);
    glVertex2f(0.2886061279006, -0.0590482998218);
    glVertex2f(0.2552118751958, -0.0590482998218);
    glVertex2f(0.3127241992985, -0.1416063134531);
    glVertex2f(0.221817622491, -0.1026463519642);
    glVertex2f(0.2348042763206, -0.1545929672827);
    glVertex2f(0.2014100236159, -0.1351129865383);
    glVertex2f(0.2088309686614, -0.2130329095161);
    glVertex2f(0.1123586830698, -0.1480996403679);
    glVertex2f(0.1067929742856, -0.1740729480272);
    glVertex2f(0.0891682298026, -0.1610862941976);
    glVertex2f(0.0919510841946, -0.2501376347436);
    glVertex2f(0.0306539475608, -0.1537912187776);
    glVertex2f(0.0119913430571, -0.1758470241002);
    glVertex2f(0.0052049414193, -0.1470048171398);
    glVertex2f(-0.074535277824, -0.218262034336);
    glVertex2f(-0.0643556753674, -0.131735413455);
    glVertex2f(-0.0847148802806, -0.143611616321);
    glVertex2f(-0.0813216794618, -0.1062864073135);
    glVertex2f(-0.1695449007523, -0.20638583147);
    glVertex2f(-0.1288264909259, -0.0757475999437);
    glVertex2f(-0.1457924950202, -0.0825340015814);
    glVertex2f(-0.1491856958391, -0.0672645978965);
    glVertex2f(-0.2068701097598, -0.1266456122267);
    glVertex2f(-0.1780279027995, -0.0384223909361);
    glVertex2f(-0.2, -0.04);
    glVertex2f(-0.1885786568249, -0.0213719477538);
    glVertex2f(-0.3039286975381, -0.0346815678361);
    glVertex2f(-0.2072121249401, 0.0305355705672);
    glVertex2f(-0.2254019390526, 0.0327538405809);
    glVertex2f(-0.2067684709374, 0.0544928867153);
    glVertex2f(-0.3, 0.06);
    glVertex2f(-0.2068709237076, 0.0934725476379);
    glVertex2f(-0.2225536575603, 0.1025520251316);
    glVertex2f(-0.200680370871, 0.1174093519394);
    glVertex2f(-0.2905506395818, 0.1327872689182);
    glVertex2f(-0.1962295343668, 0.1582389957222);
    glVertex2f(-0.222429841371, 0.1717134393243);
    glVertex2f(-0.1797607699642, 0.1851878829265);
    glVertex2f(-0.25, 0.25);
    glVertex2f(-0.1445775005586, 0.2241140533326);
    glVertex2f(-0.15, 0.25);
    glVertex2f(-0.1251144153556, 0.2510629405369);
    glVertex2f(-0.1740034521697, 0.346333181785);
    glVertex2f(-0.0786334545533, 0.2935250012867);
    glVertex2f(-0.0746925455609, 0.3171704552411);
    glVertex2f(-0.05, 0.3);
    glVertex2f(-0.0562279068563, 0.4030634938519);
    glEnd();



    //the sun
    glColor3f(0.973, 0.988, 0.271);
    drawFilledCircle(0.0382991199671, 0.0694215466285, 0.2, 2);
    //sun right eyes

    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.0773519052805, 0.0871004434075);
    glVertex2f(0.0845399363691, 0.080123824998);
    glVertex2f(0.0906709040623, 0.07737546017);
    glVertex2f(0.0995502365835, 0.0769526348119);
    glVertex2f(0.1073725057093, 0.0790667616026);
    glVertex2f(0.1135034734024, 0.0824493644678);
    glVertex2f(0.1175203143049, 0.0866776180493);
    glVertex2f(0.1225942186027, 0.0925971730635);
    glEnd();

    //eyelashes right eye
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.0845399363691, 0.080123824998);
    glVertex2f(0.0783664041974, 0.0744710196187);
    glVertex2f(0.0906709040623, 0.07737546017);
    glVertex2f(0.0892420962643, 0.0686706505163);
    glVertex2f(0.0995502365835, 0.0769526348119);
    glVertex2f(0.0993927421933, 0.0686706505163);
    glVertex2f(0.1073725057093, 0.0790667616026);
    glVertex2f(0.1099059111913, 0.0708457889297);
    glVertex2f(0.1135034734024, 0.0824493644678);
    glVertex2f(0.1189689879137, 0.0759211118942);
    glVertex2f(0.1175203143049, 0.0866776180493);
    glVertex2f(0.1247693570161, 0.08389661941);
    glEnd();



    //left eye
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.0015278720011, 0.0884617418834);
    glVertex2f(-0.0082470594866, 0.0814065950236);
    glVertex2f(-0.0156381657207, 0.0790548794036);
    glVertex2f(-0.0230292719548, 0.0783829606551);
    glVertex2f(-0.031764215686, 0.0803987169007);
    glVertex2f(-0.037811484423, 0.0840942700178);
    glVertex2f(-0.04150703754, 0.0881257825091);
    glVertex2f(-0.0458713422101, 0.0924136490281);
    glEnd();

    //eyelashes left eye
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-0.0082470594866, 0.0814065950236);
    glVertex2f(-0.0031366752155, 0.075952888408);
    glVertex2f(-0.0156381657207, 0.0790548794036);
    glVertex2f(-0.0132663740587, 0.0693052735422);
    glVertex2f(-0.0230292719548, 0.0783829606551);
    glVertex2f(-0.0227629667241, 0.0674059550091);
    glVertex2f(-0.031764215686, 0.0803987169007);
    glVertex2f(-0.033525771745, 0.0702549328088);
    glVertex2f(-0.037811484423, 0.0840942700178);
    glVertex2f(-0.0449216829435, 0.0765859945857);
    glVertex2f(-0.04150703754, 0.0881257825091);
    glVertex2f(-0.0493534261874, 0.0844998218069);
    glEnd();

    //cheeks
    glColor3f(0.98, 0.745, 0.51);
    drawFilledCircle(-0.0495365713462, 0.0235385177666, 0.02, 2);
    drawFilledCircle(0.125424239421, 0.0251290705918, 0.02, 2);

    //mouth
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.009808308886, 0.0426596470177);
    glVertex2f(0.0149348435866, 0.0351706053598);
    glVertex2f(0.0250276944198, 0.0283074667933);
    glVertex2f(0.0355242592863, 0.0250777545267);
    glVertex2f(0.0492505364194, 0.0270963246933);
    glVertex2f(0.0589396732193, 0.0335557492265);
    glVertex2f(0.065109947811, 0.0431074335677);
    glEnd();

}
void carrot3() {
    //the carrots
    glColor3f(0.945, 0.482, 0.129);
    glBegin(GL_POLYGON);
    glVertex2f(0.4354142143516, -0.855);
    glVertex2f(0.432268825498, -0.821923051953);
    glVertex2f(0.4306961310712, -0.8065892812917);
    glVertex2f(0.4310893046779, -0.7928282050572);
    glVertex2f(0.4396378194985, -0.7847305270457);
    glVertex2f(0.4463211637057, -0.7809432986616);
    glVertex2f(0.4567917362971, -0.7791610735397);
    glVertex2f(0.4694900902908, -0.7802749642409);
    glVertex2f(0.4761734344981, -0.7836166363445);
    glVertex2f(0.4817428880041, -0.789631646131);
    glVertex2f(0.4868667852296, -0.7963149903383);
    glVertex2f(0.4877578977906, -0.8052261159479);
    glVertex2f(0.4884262322113, -0.82);
    glVertex2f(0.4875351196504, -0.85);
    glEnd();
    //the carrot lines
    glColor3f(0.91, 0.416, 0.075);
    glBegin(GL_LINES);
    glVertex2f(0.4505539483703, -0.7945327652164);
    glVertex2f(0.4625839679434, -0.7947555433566);
    glVertex2f(0.4425339353216, -0.8110183475942);
    glVertex2f(0.453004507913, -0.8105727913137);
    glVertex2f(0.4429794916021, -0.8145827978381);
    glVertex2f(0.4532272860532, -0.8139144634173);
    glVertex2f(0.4799606628822, -0.8110183475942);
    glVertex2f(0.4884262322113, -0.810795569454);
    glVertex2f(0.4534500641935, -0.8183700262222);
    glVertex2f(0.4636978586446, -0.8185928043624);
    glVertex2f(0.44, -0.84);
    glVertex2f(0.4516678390715, -0.8402022839658);
    glVertex2f(0.4741684312359, -0.8390883932646);
    glVertex2f(0.4870895633699, -0.8390883932646);
    glEnd();

    //CARROT LEAVES
    glColor3f(0.471, 0.667, 0.294);
    glBegin(GL_POLYGON);
    glVertex2f(0.4461662952859, -0.7807636470371);
    glVertex2f(0.4339580609028, -0.7493387474214);
    glVertex2f(0.4461662952859, -0.77036403997);
    glVertex2f(0.4484270794309, -0.7289916901163);
    glVertex2f(0.4515921772339, -0.7425563949863);
    glVertex2f(0.4561137455239, -0.7443650223024);
    glVertex2f(0.4581484512545, -0.7529560020534);
    glVertex2f(0.4626700195445, -0.7260526707278);
    glVertex2f(0.468321979907, -0.7525038452244);
    glVertex2f(0.470582764052, -0.7335132584063);
    glVertex2f(0.4735217834405, -0.764033844364);
    glVertex2f(0.4805302142901, -0.7432346302298);
    glVertex2f(0.4721653129535, -0.7800854117936);
    glVertex2f(0.46, -0.78);
    glEnd();
}
void carrots() {
    //the soil
    glColor3f(0.408, 0.169, 0.086);
    glBegin(GL_POLYGON);
    glVertex2f(0.3847944141133, -0.921794887247);
    glVertex2f(0.3844224247674, -0.9043113879902);
    glVertex2f(0.4249692634695, -0.8514889008738);
    glVertex2f(0.5062280423446, -0.8485868016282);
    glVertex2f(0.5323469355545, -0.8664830803091);
    glVertex2f(0.5507647197126, -0.8548484987588);
    glVertex2f(0.5883629065164, -0.8491885566593);
    glVertex2f(0.6231311222703, -0.8516142461305);
    glVertex2f(0.6494094248751, -0.8738497329499);
    glVertex2f(0.6756877274798, -0.8520185277091);
    glVertex2f(0.7569483247653, -0.8504014013949);
    glVertex2f(0.7936418483929, -0.8919940871943);
    glVertex2f(0.7954192416001, -0.9204323785088);
    glVertex2f(0.6010909176174, -0.9210248429112);
    glEnd();
    glColor3f(0.192, 0.122, 0.082);
    drawFilledCircle(0.430661846944, -0.9002451832808, 0.01, 2);
    drawFilledCircle(0.4893520138241, -0.8935377356374, 0.01, 2);
    drawFilledCircle(0.5534940858823, -0.8810339667279, 0.01, 2);
    drawFilledCircle(0.6042853358637, -0.9003529654406, 0.01, 2);
    drawFilledCircle(0.6853582290271, -0.9018771897608, 0.01, 2);
    drawFilledCircle(0.7195258116265, -0.8728187783913, 0.01, 2);
    drawFilledCircle(0.7635130402978, -0.9004539432781, 0.01, 2);
    //carrots
    glPushMatrix();
    carrot3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.13, 0.0, 0.0);
    carrot3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25, 0.0, 0.0);
    carrot3();
    glPopMatrix();
}
void Stars() {

    glPushMatrix();

    glColor3f(0.969, 0.749, 0.188);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2262632945446, 0.0945489388426);
    glVertex2f(-0.2278649905283, 0.4020126840107);
    glVertex2f(-0.2080886075285, 0.3892201075518);
    glVertex2f(-0.1720458854953, 0.3240301108028);
    glVertex2f(-0.160553716812, 0.284628389603);
    glVertex2f(-0.1203311264205, 0.2862701279863);
    glVertex2f(-0.0718998441124, 0.2829866512196);
    glVertex2f(-0.0185433466543, 0.2567188370864);
    glVertex2f(-0.0587659370458, 0.2082875547783);
    glVertex2f(-0.0916007047123, 0.1853032174117);
    glVertex2f(-0.1326441642955, 0.1664232260035);
    glVertex2f(-0.1185128374572, 0.133135251178);
    glVertex2f(-0.1039519648778, 0.0887245898108);
    glVertex2f(-0.1097763139095, 0.0392176230409);
    glVertex2f(-0.1629234988243, 0.0464980593306);
    glVertex2f(-0.2015098111597, 0.0727076299735);
    glVertex2f(-0.2278649905283, 0.4020126840107);
    glEnd();


    //half
    glBegin(GL_POLYGON);
    glVertex2f(-0.2262632945446, 0.0945489388426);
    glVertex2f(-0.2561006670844, 0.0679815545092);
    glVertex2f(-0.2878649768039, 0.0499531625062);
    glVertex2f(-0.3429535923832, 0.0375687082211);
    glVertex2f(-0.3482390127129, 0.0932743358759);
    glVertex2f(-0.3341305725704, 0.1351409273271);
    glVertex2f(-0.3216745445994, 0.1662809972545);
    glVertex2f(-0.355812768312, 0.1832088469799);
    glVertex2f(-0.3951575188263, 0.2083955081615);
    glVertex2f(-0.4312620300581, 0.2553313727628);
    glVertex2f(-0.3761205947223, 0.2786351936488);
    glVertex2f(-0.3264742209723, 0.284439417872);
    glVertex2f(-0.2886093107114, 0.284628389603);
    glVertex2f(-0.2787588804114, 0.3248509799944);
    glVertex2f(-0.2639832349615, 0.357685747661);
    glVertex2f(-0.2278649905283, 0.4020126840107);
    glEnd();

    glLineWidth(2);
    //smile
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.2476069776193, 0.1830780943549);
    glVertex2f(-0.2430194760241, 0.1754514598414);
    glVertex2f(-0.2373219574915, 0.1708077876621);
    glVertex2f(-0.2295844139844, 0.168228606493);
    glVertex2f(-0.2209257343454, 0.1678601520403);
    glVertex2f(-0.2130039636119, 0.1706235604357);
    glVertex2f(-0.206386596946, 0.1756060289514);
    glVertex2f(-0.2012858163148, 0.1825616389029);
    glEnd();

    //left lash
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.2957275425459, 0.2258409897126);
    glVertex2f(-0.291863314795, 0.2207402090814);

    glVertex2f(-0.2875353797141, 0.2174942577707);
    glVertex2f(-0.2822800299729, 0.2147120137901);

    glVertex2f(-0.2753244200213, 0.2128571844697);
    glVertex2f(-0.2686779482899, 0.2131663226898);

    glVertex2f(-0.2628043221085, 0.2156394284503);
    glVertex2f(-0.2577035414774, 0.2207402090814);
    glEnd();


    //left eyelash
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    glVertex2f(-0.291863314795, 0.2207402090814);
    glVertex2f(-0.3014710610083, 0.2162631933467);

    glVertex2f(-0.2875353797141, 0.2174942577707);
    glVertex2f(-0.2960401321426, 0.2103977901717);

    glVertex2f(-0.2822800299729, 0.2147120137901);
    glVertex2f(-0.2856127487204, 0.2051840984606);

    glVertex2f(-0.2753244200213, 0.2128571844697);
    glVertex2f(-0.2758370767622, 0.2030117269143);

    glVertex2f(-0.2686779482899, 0.2131663226898);
    glVertex2f(-0.2669303534224, 0.2040979126875);

    glVertex2f(-0.2628043221085, 0.2156394284503);
    glVertex2f(-0.2554167842271, 0.2088771300893);
    glEnd();

    //right lash
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);

    glVertex2f(-0.1901568403924, 0.2182671033209);
    glVertex2f(-0.1853651979813, 0.2139391682399);

    glVertex2f(-0.1787320686433, 0.2114839759448);
    glVertex2f(-0.1722268236284, 0.2113114933693);

    glVertex2f(-0.1649620754568, 0.2131663226898);
    glVertex2f(-0.1600158639357, 0.2161031357804);

    glVertex2f(-0.1563062052948, 0.2195036562012);
    glVertex2f(-0.1521328393239, 0.2247590059423);
    glEnd();



    //right eyelash
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    glVertex2f(-0.1853651979813, 0.2139391682399);
    glVertex2f(-0.1924180093849, 0.2071392328523);

    glVertex2f(-0.1787320686433, 0.2114839759448);
    glVertex2f(-0.1815561516535, 0.2025772526051);

    glVertex2f(-0.1722268236284, 0.2113114933693);
    glVertex2f(-0.1724321911591, 0.2023600154505);

    glVertex2f(-0.1649620754568, 0.2131663226898);
    glVertex2f(-0.1628737563554, 0.2040979126875);

    glVertex2f(-0.1600158639357, 0.2161031357804);
    glVertex2f(-0.1544015073249, 0.2097460787078);

    glVertex2f(-0.1563062052948, 0.2195036562012);
    glVertex2f(-0.1474499183768, 0.2164804305013);
    glEnd();


    glPushMatrix();
    glColor3f(0.929, 0.635, 0.694);
    glTranslatef(-0.1636306129723, 0.1752434845717, 0.0);
    glutSolidSphere(0.02, 25, 25);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.929, 0.635, 0.694);
    glTranslatef(-0.2863997934139, 0.1747653481132, 0.0);
    glutSolidSphere(0.02, 25, 25);
    glPopMatrix();


    glPopMatrix();




}
void moon() {

    //    //moon
    glPushMatrix();


    glColor3f(0.961, 0.753, 0.231);
    glBegin(GL_POLYGON);
    glVertex2f(0.2101541240633, 0.2472047239071);
    glVertex2f(0.2070447691781, 0.2683483371262);
    glVertex2f(0.2005748041169, 0.2862256948055);
    glVertex2f(0.1936152574705, 0.3063852327819);
    glVertex2f(0.1859078955758, 0.3243032458255);
    glVertex2f(0.1782925952221, 0.3369920755528);
    glVertex2f(0.17, 0.35);
    glVertex2f(0.1598635984177, 0.3641419369164);
    glVertex2f(0.1502252267675, 0.3771633486781);
    glVertex2f(0.1411645236053, 0.3862240518402);
    glVertex2f(0.1299072863432, 0.3961084552899);
    glVertex2f(0.117526663397, 0.40922038517);
    glVertex2f(0.1079500981891, 0.4265759866083);
    glVertex2f(0.1079500981891, 0.4265759866083);
    glVertex2f(0.1408645944544, 0.4321784540577);
    glVertex2f(0.166776006408, 0.429377220333);
    glVertex2f(0.1968892689486, 0.4223741360212);
    glVertex2f(0.2228006809021, 0.4160713601406);
    glVertex2f(0.2494124012869, 0.4062670421042);
    glVertex2f(0.2739231963781, 0.3943617987741);
    glVertex2f(0.3040364589187, 0.3775543964259);
    glVertex2f(0.3278469455787, 0.3572454519217);
    glVertex2f(0.3481558900829, 0.3355358905552);
    glVertex2f(0.3663639092935, 0.3075235533082);
    glVertex2f(0.3782691526235, 0.2746090570428);
    glVertex2f(0.3838716200729, 0.2465967197957);
    glVertex2f(0.3859725453664, 0.2178840741175);
    glVertex2f(0.3831713116417, 0.1863701947145);
    glVertex2f(0.3747676104676, 0.1534556984492);
    glVertex2f(0.2132634789484, 0.2198424009176);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.3747676104676, 0.1534556984492);
    glVertex2f(0.3628623671376, 0.1268439780644);
    glVertex2f(0.3508785352541, 0.1058671221186);
    glVertex2f(0.3371792299879, 0.0897456945658);
    glVertex2f(0.320396093678, 0.0744434232244);
    glVertex2f(0.3028239839982, 0.0597330804038);
    glVertex2f(0.2809063611841, 0.0482814754472);
    glVertex2f(0.2650996904124, 0.0390688176753);
    glVertex2f(0.2485202238046, 0.0313797896833);
    glVertex2f(0.2288102533743, 0.0239530431519);
    glVertex2f(0.2039354142929, 0.0158687204505);
    glVertex2f(0.1796824461886, 0.0115156236113);
    glVertex2f(0.1535638651532, 0.006540655795);
    glVertex2f(0.1268474962016, 0.0039287987413);
    glVertex2f(0.0973307862372, 0.0093401955681);
    glVertex2f(0.1108592783042, 0.0329535635396);
    glVertex2f(0.1268474962016, 0.0501716443522);
    glVertex2f(0.149832639291, 0.0737027213146);
    glVertex2f(0.1703543815331, 0.099199431373);
    glVertex2f(0.1902542527982, 0.1271836253396);
    glVertex2f(0.2033135433159, 0.1570334322372);
    glVertex2f(0.2126416079714, 0.191236335974);
    glVertex2f(0.2132634789484, 0.2198424009176);
    glEnd();

    //outer line
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.1079500981891, 0.4265759866083);

    glVertex2f(0.1408645944544, 0.4321784540577);
    glVertex2f(0.166776006408, 0.429377220333);

    glVertex2f(0.1968892689486, 0.4223741360212);
    glVertex2f(0.2228006809021, 0.4160713601406);

    glVertex2f(0.2494124012869, 0.4062670421042);
    glVertex2f(0.2739231963781, 0.3943617987741);

    glVertex2f(0.3040364589187, 0.3775543964259);
    glVertex2f(0.3278469455787, 0.3572454519217);

    glVertex2f(0.3481558900829, 0.3355358905552);
    glVertex2f(0.3663639092935, 0.3075235533082);

    glVertex2f(0.3782691526235, 0.2746090570428);
    glVertex2f(0.3838716200729, 0.2465967197957);

    glVertex2f(0.3859725453664, 0.2178840741175);
    glVertex2f(0.3831713116417, 0.1863701947145);

    glVertex2f(0.3747676104676, 0.1534556984492);
    glVertex2f(0.3628623671376, 0.1268439780644);

    glVertex2f(0.3508785352541, 0.1058671221186);
    glVertex2f(0.3371792299879, 0.0897456945658);

    glVertex2f(0.320396093678, 0.0744434232244);
    glVertex2f(0.3028239839982, 0.0597330804038);

    glVertex2f(0.2809063611841, 0.0482814754472);
    glVertex2f(0.2650996904124, 0.0390688176753);

    glVertex2f(0.2485202238046, 0.0313797896833);
    glVertex2f(0.2288102533743, 0.0239530431519);
    glVertex2f(0.2039354142929, 0.0158687204505);
    glVertex2f(0.1796824461886, 0.0115156236113);

    glVertex2f(0.1535638651532, 0.006540655795);
    glVertex2f(0.1268474962016, 0.0039287987413);

    glVertex2f(0.0973307862372, 0.0093401955681);
    glVertex2f(0.1108592783042, 0.0329535635396);

    glVertex2f(0.1268474962016, 0.0501716443522);
    glVertex2f(0.149832639291, 0.0737027213146);

    glVertex2f(0.1703543815331, 0.099199431373);
    glVertex2f(0.1902542527982, 0.1271836253396);

    glVertex2f(0.2033135433159, 0.1570334322372);
    glVertex2f(0.2126416079714, 0.191236335974);
    glVertex2f(0.2132634789484, 0.2198424009176);
    glVertex2f(0.2101541240633, 0.2472047239071);

    glVertex2f(0.2070447691781, 0.2683483371262);
    glVertex2f(0.2005748041169, 0.2862256948055);

    glVertex2f(0.1936152574705, 0.3063852327819);
    glVertex2f(0.1859078955758, 0.3243032458255);

    glVertex2f(0.1782925952221, 0.3369920755528);
    glVertex2f(0.17, 0.35);

    glVertex2f(0.1598635984177, 0.3641419369164);
    glVertex2f(0.1502252267675, 0.3771633486781);

    glVertex2f(0.1411645236053, 0.3862240518402);
    glVertex2f(0.1299072863432, 0.3961084552899);
    glVertex2f(0.117526663397, 0.40922038517);
    glEnd();

    //smile
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.2226353503687, 0.1925378519707);
    glVertex2f(0.2259186751044, 0.1878864752618);
    glVertex2f(0.2297492206295, 0.1840559297368);
    glVertex2f(0.2341269869438, 0.1804989946064);
    glVertex2f(0.238892138156, 0.1787263536631);
    glVertex2f(0.2437734757662, 0.178072129487);
    glVertex2f(0.248326113209, 0.178072129487);
    glVertex2f(0.2536560302154, 0.1789604489881);
    glVertex2f(0.2582086676582, 0.1810702078031);
    glVertex2f(0.262206105413, 0.1837351663062);
    glVertex2f(0.2667587428559, 0.1880657238739);
    glVertex2f(0.2690621410006, 0.1927531394764);
    glEnd();

    //eyes
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.2590255328564, 0.2661390481301);
    glVertex2f(0.2628560783814, 0.2606668402372);
    glVertex2f(0.2669602343011, 0.2568362947122);
    glVertex2f(0.2717700846358, 0.2542030766716);
    glVertex2f(0.2784238502884, 0.252816875494);
    glVertex2f(0.2850185203476, 0.2530057491871);
    glVertex2f(0.2907643386351, 0.2551946323443);
    glVertex2f(0.2967837673173, 0.2609404506318);
    glEnd();


    //eyes lash
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    glVertex2f(0.2628560783814, 0.2606668402372);
    glVertex2f(0.2538418827387, 0.2576223729097);

    glVertex2f(0.2669602343011, 0.2568362947122);
    glVertex2f(0.2581853130952, 0.2501368865506);

    glVertex2f(0.2717700846358, 0.2542030766716);
    glVertex2f(0.2691825091043, 0.2432982940744);

    glVertex2f(0.2784238502884, 0.252816875494);
    glVertex2f(0.2791631575831, 0.2413576124257);

    glVertex2f(0.2850185203476, 0.2530057491871);
    glVertex2f(0.2880348451198, 0.2428362270152);

    glVertex2f(0.2907643386351, 0.2551946323443);
    glVertex2f(0.298385147246, 0.2482886183138);

    glEnd();

    glPushMatrix();
    glColor3f(0.929, 0.635, 0.694);
    glTranslatef(0.3028031959995, 0.2021142157833, 0.0);
    glutSolidSphere(0.02, 25, 25);
    glPopMatrix();

    glPopMatrix();
    //




}
void tears() {


    glBegin(GL_TRIANGLES);
    glColor3f(0.365, 0.69, 0.878);
    glVertex2f(0.0, -0.6);
    glColor3f(0.184, 0.702, 1.0);
    glVertex2f(-0.05, -0.7);
    glVertex2f(0.05, -0.7);
    glEnd();


    glPushMatrix();
    glColor3f(0.184, 0.702, 1.0);
    glTranslatef(0.0, -0.7, 0.0);
    glutSolidSphere(0.05, 25, 25); // to use texture for the moon
    glPopMatrix();
}
void drawStars() {

    // glColor3f(1.0, 1.0, 1.0);
    glColor3f(0.969, 0.749, 0.188);
    srand((unsigned)time(NULL));
    for (int i = 1; i < 20; i++) {
        float x = (float)rand() / RAND_MAX;
        float y = (float)rand() / RAND_MAX;
        drawFilledCircle(x, y, 0.002, 2);
        drawFilledCircle(-x, y, 0.002, 2);
        drawFilledCircle(x, -y, 0.002, 2);
        drawFilledCircle(-x, -y, 0.002, 2);
    }


}
void drawCave() {
    //outer line
    glBegin(GL_POLYGON);
    // glColor3f(0.71, 0.569, 0.506);
    glColor3f(0.2549f, 0.1764f, 0.1686f);//dark
    glVertex2f(-0.6, 0);
    glVertex2f(-0.7, 0);
    glVertex2f(-0.7, 0.1);
    glVertex2f(-0.68, 0.18);
    glVertex2f(-0.62, 0.26);
    glVertex2f(-0.57, 0.38);
    glVertex2f(-0.52, 0.46);
    glVertex2f(-0.5, 0.6);
    glVertex2f(-0.36, 0.72);
    glVertex2f(-0.2, 0.81);
    glVertex2f(-0.22, 0.88);
    glVertex2f(0.0, 0.93);
    glVertex2f(0.13, 0.94);
    glVertex2f(0.25, 0.93);
    glVertex2f(0.5, 0.83);
    glVertex2f(0.52, 0.73);
    glVertex2f(0.54, 0.68);
    glVertex2f(0.7, 0.47);
    glVertex2f(0.8, 0.2);
    glVertex2f(0.85, 0.0);
    glVertex2f(0.75, 0.0);
    glEnd();


    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.6, 0);
    glVertex2f(-0.7, 0);
    glVertex2f(-0.7, 0.1);
    glVertex2f(-0.68, 0.18);
    glVertex2f(-0.62, 0.26);
    glVertex2f(-0.57, 0.38);
    glVertex2f(-0.52, 0.46);
    glVertex2f(-0.5, 0.6);
    glVertex2f(-0.36, 0.72);
    glVertex2f(-0.2, 0.81);
    glVertex2f(-0.22, 0.88);
    glVertex2f(0.0, 0.93);
    glVertex2f(0.13, 0.94);
    glVertex2f(0.25, 0.93);
    glVertex2f(0.5, 0.83);
    glVertex2f(0.52, 0.73);
    glVertex2f(0.54, 0.68);
    glVertex2f(0.7, 0.47);
    glVertex2f(0.8, 0.2);
    glVertex2f(0.85, 0.0);
    glVertex2f(0.75, 0.0);
    glEnd();


    //inner line
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.4, 0.1);
    glVertex2f(-0.32, 0.32);
    glVertex2f(-0.2, 0.55);
    glVertex2f(-0.12, 0.62);
    glVertex2f(-0.1, 0.71);
    glVertex2f(0.05, 0.76);
    glVertex2f(0.24, 0.74);
    glVertex2f(0.38, 0.61);
    glVertex2f(0.45, 0.57);
    glVertex2f(0.48, 0.45);
    glVertex2f(0.61, 0.12);
    glVertex2f(0.65, 0.0);
    glEnd();

    //inner inner line :)
    glBegin(GL_POLYGON);
    glColor3f(0.192, 0.114, 0.086);
    glVertex2f(-0.26, 0.0);
    glVertex2f(-0.11, 0.35);
    glVertex2f(0.01, 0.47);
    glVertex2f(0.0, 0.6);
    glVertex2f(0.11, 0.61);
    glVertex2f(0.33, 0.47);
    glVertex2f(0.31, 0.39);
    glVertex2f(0.4, 0.3);
    glVertex2f(0.48, 0.0);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.26, 0.0);
    glVertex2f(-0.11, 0.35);
    glVertex2f(0.01, 0.47);
    glVertex2f(0.0, 0.6);
    glVertex2f(0.11, 0.61);
    glVertex2f(0.33, 0.47);
    glVertex2f(0.31, 0.39);
    glVertex2f(0.4, 0.3);
    glVertex2f(0.48, 0.0);
    glEnd();


    //crack1
    glLineWidth(3);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.51, 0.15);
    glVertex2f(-0.6, 0.15);
    glVertex2f(-0.55, 0.22);
    glEnd();

    //crack2
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.48, 0.21);
    glVertex2f(-0.44, 0.3);
    glVertex2f(-0.5, 0.37);
    glEnd();


    //rock1
    glBegin(GL_POLYGON);
    glColor3f(0.361, 0.353, 0.361);
    glVertex2f(-0.6, -0.01);
    glVertex2f(-0.55, 0.11);
    glVertex2f(-0.4, 0.12);
    glVertex2f(-0.34, 0.09);
    glVertex2f(-0.3, -0.02);
    glVertex2f(-0.42, -0.01);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-0.6, -0.02);
    glVertex2f(-0.55, 0.11);
    glVertex2f(-0.4, 0.12);
    glVertex2f(-0.34, 0.09);
    glVertex2f(-0.3, -0.02);
    glVertex2f(-0.42, -0.02);
    glEnd();


    //rook2
    glBegin(GL_POLYGON);
    glColor3f(0.361, 0.353, 0.361);
    glVertex2f(0.6, -0.01);
    glVertex2f(0.55, 0.11);
    glVertex2f(0.4, 0.12);
    glVertex2f(0.34, 0.09);
    glVertex2f(0.3, -0.02);
    glVertex2f(0.42, -0.01);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.6, -0.02);
    glVertex2f(0.55, 0.11);
    glVertex2f(0.4, 0.12);
    glVertex2f(0.34, 0.09);
    glVertex2f(0.3, -0.02);
    glVertex2f(0.42, -0.02);
    glEnd();

    //rook3
    glBegin(GL_POLYGON);
    glColor3f(0.361, 0.353, 0.361);
    glVertex2f(0.8, -0.01);
    glVertex2f(0.75, 0.11);
    glVertex2f(0.6, 0.12);
    glVertex2f(0.54, 0.09);
    glVertex2f(0.5, -0.02);
    glVertex2f(0.62, -0.01);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(0.8, -0.01);
    glVertex2f(0.75, 0.11);
    glVertex2f(0.6, 0.12);
    glVertex2f(0.54, 0.09);
    glVertex2f(0.5, -0.02);
    glVertex2f(0.62, -0.01);
    glEnd();




}
void drawBackground() {

    glPushMatrix();
    //sky
    glBegin(GL_QUADS);
    glColor3f(0.051, 0.067, 0.173);
    //glColor3f(0.051, 0.067, Bc);
    glVertex2f(1, 1);
    glColor3f(0.075, 0.141, 0.361);
    glVertex2f(-1, 1);
    glColor3f(0.141, 0.278, 0.529);
    glVertex2f(-1, -1);
    glColor3f(0.075, 0.141, 0.361);
    glVertex2f(1, -1);
    glEnd();

    //    stars
    glPushMatrix();
    glScalef(0.3, 0.3, 1.0);
    Stars();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.3, 0.3, 1.0);
    glTranslatef(-2.0, 2.5, 0.0);
    Stars();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.3, 0.3, 1.0);
    glTranslatef(-1.0, 1.3, 0.0);
    Stars();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.3, 0.3, 1.0);
    glTranslatef(-2.6, .8, 0.0);
    Stars();
    glPopMatrix();


    glPushMatrix();
    glScalef(0.3, 0.3, 1.0);
    glTranslatef(0.2, 2.8, 0.0);
    Stars();
    glPopMatrix();


    glPushMatrix();
    glScalef(0.3, 0.3, 1.0);
    glTranslatef(3.2, 2.4, 0.0);
    Stars();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.3, 0.3, 1.0);
    glTranslatef(0.9, 2.0, 0.0);
    Stars();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.3, 0.3, 1.0);
    glTranslatef(2.5, 0.5, 0.0);
    Stars();
    glPopMatrix();

    drawStars();

    //moon
    glPushMatrix();
    glTranslatef(0.4, 0.5, 0.0);
    moon();
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.149, 0.31, 0.086);
    //darker
    glColor3f(0.106, 0.22, 0.063);
    drawFilledCircle(-0.8, -0.2, 0.3, 1);
    //midlle
    glColor3f(0.243, 0.4, 0.18);
    drawFilledCircle(-0.6, -0.41, 0.3, 1);
    //lighter
    glColor3f(0.18, 0.329, 0.122);
    drawFilledCircle(-0.3, -0.3, 0.3, 1);

    glPopMatrix();

    glPushMatrix();
    //glColor3f(0.149, 0.31, 0.086);
    glColor3f(0.106, 0.22, 0.063);
    drawFilledCircle(0.8, -0.3, 0.3, 1);
    glColor3f(0.18, 0.329, 0.122);
    drawFilledCircle(1.0, -0.4, 0.3, 1);
    glPopMatrix();


    //grass
    glBegin(GL_QUADS);
    glColor3f(0.149, 0.31, 0.086);
    glVertex2f(-1, -0.2);
    glVertex2f(1, -0.2);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();

    glPopMatrix();
}
void multipleCorn_scene13() {
    //----------------(continue)------------------
    glPushMatrix();
    glTranslatef(-0.7725259024378, 0.4906513083048, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.6247454893674, 0.499518133089, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.4828762928199, 0.4906513083048, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.338051488011, 0.4936069165662, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.1873154666793, 0.4965625248276, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.6749908298113, 0.3960718439398, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.5538108910937, 0.3931162356784, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.4267197358532, 0.3990274522012, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.2700724979986, 0.3990274522012, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.1341145179739, 0.404938668724, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0, 0.4, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.7754815106992, 0.2926255547906, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.6247454893674, 0.295581163052, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.4946987258655, 0.2926255547906, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.3498739210566, 0.2985367713134, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.2080047245091, 0.295581163052, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.0750023527458, 0.3014923795748, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.0727780603245, 0.3044479878362, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.3498739210566, 0.1921348739028, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.0786892768473, 0.2039573069484, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.8676525774611, 0.4930622146674, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.9358156726552, 0.37538258611, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.7832572182779, 0.3383381943714, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.6019800453558, 0.1315760511161, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.4461771120562, 0.1351993751463, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.0584814408223, 0.5011551021988, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------( 7 )------------
    glPushMatrix();
    glTranslatef(0.7, 0.2, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.87, 0.2, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------( 6 )------------
    glPushMatrix();
    glTranslatef(0.5, 0.0, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.59, 0.1, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.7, 0.0, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.77, 0.1, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.93, 0.1, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------(left)
    glPushMatrix();
    glTranslatef(-0.07, 0.1, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.04, 0.0, 0.0);
    glScalef(-0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.25, 0.1, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.75, 0.1, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------( 5 )------------
    glPushMatrix();
    glTranslatef(0.37, -0.07, 0.0);
    glScalef(0.25, 0.25, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.49, -0.17, 0.0);
    glScalef(0.25, 0.25, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.61, -0.07, 0.0);
    glScalef(0.25, 0.25, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.73, -0.17, 0.0);
    glScalef(0.25, 0.25, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.85, -0.07, 0.0);
    glScalef(0.25, 0.25, 1.0);
    corn();
    glPopMatrix();
    //------------(left)
    glPushMatrix();
    glTranslatef(-0.25, -0.07, 0.0);
    glScalef(0.25, 0.25, 1.0);
    corn();
    glPopMatrix();
    //------------( 4 )------------
    glPushMatrix();
    glTranslatef(0.30, -0.25, 0.0);
    glScalef(0.3, 0.3, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.44, -0.35, 0.0);
    glScalef(0.3, 0.3, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.58, -0.25, 0.0);
    glScalef(0.3, 0.3, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.72, -0.35, 0.0);
    glScalef(0.3, 0.3, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.86, -0.25, 0.0);
    glScalef(0.3, 0.3, 1.0);
    corn();
    glPopMatrix();
    //------------( 3 )------------
    glPushMatrix();
    glTranslatef(0.20, -0.5, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.35, -0.65, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.50, -0.5, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.65, -0.65, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.80, -0.5, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------( 2 )------------
    glPushMatrix();
    glTranslatef(0.85, -0.8, 0.0);
    glScalef(0.5, 0.5, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.50, -0.8, 0.0);
    glScalef(0.5, 0.5, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.10, -0.8, 0.0);
    glScalef(0.5, 0.5, 1.0);
    corn();
    glPopMatrix();
    //------------( 1 )------------
    glPushMatrix();
    glTranslatef(0.22, -1.1, 0.0);
    glScalef(0.7, 0.7, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.62, -1.1, 0.0);
    glScalef(0.7, 0.7, 1.0);
    corn();
    glPopMatrix();
}
void multipleCorn_scene14() {
    //----------------(continue)------------------
    glPushMatrix();
    glTranslatef(-0.9723401522904, -0.0506178492519, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.8350102160413, -0.047348088865, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.6813314778579, -0.0506178492519, 0.0);
    glScalef(0.22, 0.22, 1.0);
    corn();
    glPopMatrix();
    //-------------------------
    glPushMatrix();
    glTranslatef(-0.9167542257134, -0.214105868596, 0.0);
    glScalef(0.3, 0.3, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.7369174044349, -0.2173756289829, 0.0);
    glScalef(0.3, 0.3, 1.0);
    corn();
    glPopMatrix();
    //----------------------------
    glPushMatrix();
    glTranslatef(-1, -0.4, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.8317404556545, -0.3939426898745, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //----------------------------
    glPushMatrix();
    glTranslatef(-1.0965910469919, -0.5803190319268, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.9167542257134, -0.573779511153, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.7499964459824, -0.5770492715399, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.7540933319831, -0.5901283130874, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.9600882363567, -0.5966678338612, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //----------------------------
    glPushMatrix();
    glTranslatef(-1.0213865580936, -0.7241884889496, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(-0.8513590179757, -0.7274582493364, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.8292978208814, -0.7372675304971, 0.0);
    glScalef(0.4, 0.4, 1.0);
    corn();
    glPopMatrix();
    //----------------------------
    glPushMatrix();
    glTranslatef(-1.0867817658312, -0.9138345913887, 0.0);
    glScalef(0.5, 0.5, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.2, -1, 0.0);
    glScalef(0.5, 0.5, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.3617220855573, -1.05, 0.0);
    glScalef(0.5, 0.5, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.5350193860621, -1, 0.0);
    glScalef(0.5, 0.5, 1.0);
    corn();
    glPopMatrix();
    //------------
    glPushMatrix();
    glTranslatef(0.7639026131438, -1, 0.0);
    glScalef(0.5, 0.5, 1.0);
    corn();
    glPopMatrix();
    //--------------------

}
void Kimo() {


    // ------------------------------------------------------------------

    glBegin(GL_TRIANGLES); //(PUR-CLOTHES)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    glVertex2f(0.1f, -0.58f); //right
    glVertex2f(-0.1f, -0.58f); //left

    glColor4f(0.12f, 0.0f, 0.32f, 1.0f);
    glVertex2f(0.0f, -0.25f); //center

    glEnd();
    glBegin(GL_QUADS); //(B-FEET & PUR-ARMS))
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    //RIGHT-FEET
    glVertex2f(0.04, -0.4);   //right-up
    glVertex2f(0.005, -0.4);  //left-up
    glVertex2f(0.005, -0.7); //left-down
    glVertex2f(0.04, -0.7);  //right-down
    //LEFT-FEET
    glVertex2f(-0.005, -0.4);   //right-up
    glVertex2f(-0.04, -0.4);  //left-up
    glVertex2f(-0.04, -0.7); //left-down
    glVertex2f(-0.005, -0.7);  //right-down
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    //RIGHT-ARM
    glVertex2f(0.03, -0.22);   //right-up
    glVertex2f(0.0, -0.25);  //left-up
    glVertex2f(0.20, -0.60); //left-down
    glVertex2f(0.23, -0.57);  //right-down
    //LEFT-ARM
    glVertex2f(-0.03, -0.22);   //right-up
    glVertex2f(0.0, -0.25);  //left-up
    glVertex2f(-0.20, -0.60); //left-down
    glVertex2f(-0.23, -0.57);  //right-down
    glEnd();

    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0, 0, 0.15, 2);        //up
    drawFilledCircle(-0.20, -0.3, 0.10, 2); //left
    drawFilledCircle(0.20, -0.3, 0.10, 2);  //right
    // ------------------------------------------------------------------
    glBegin(GL_TRIANGLES); //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f); //BIG
    //big-right
    glVertex2f(0.14f, 0.05f);
    glVertex2f(0.0f, -0.25f); //center
    glVertex2f(0.286f, -0.25f);
    //big-left
    glVertex2f(-0.14f, 0.05f);
    glVertex2f(0.0f, -0.25f); //center
    glVertex2f(-0.286f, -0.25f);
    //big-down
    glVertex2f(-0.20f, -0.40f);
    glVertex2f(0.0f, 0.0f); //center
    glVertex2f(0.20f, -0.40f);
    //right-up-tail
    glVertex2f(0.20, 0.07);
    glVertex2f(0.14, 0.03);
    //glColor4f(0.33f, 0.25f, 0.39f, 1);
    glVertex2f(0.22, 0.0); //tail
    //glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    //left-up-head
    glVertex2f(0.16, 0.11);
    glVertex2f(0.02, 0.148); //head
    glVertex2f(0.14, 0.03);
    glEnd();

    // ------------------------------------------------------------------
    // drawing half filled circle (B-SHOES)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.04, -0.7, 0.035, 1.0);
    drawFilledCircle(-0.04, -0.7, 0.035, 1.0);
    // ------------------------------------------------------------------
    // drawing half filled circle (B-HANDS)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.215, -0.585, 0.035, 2); //midpoint formula = (x1 + x2)/2, (y1 + y2)/2.
    drawFilledCircle(-0.215, -0.585, 0.035, 2);
    // ------------------------------------------------------------------
    // drawing the filled circle //(B-FACE)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    drawFilledCircle(0.09, -0.02, 0.03, 2);  //right-up
    drawFilledCircle(-0.09, -0.02, 0.03, 2); //left-up
    drawFilledCircle(-0.20, -0.3, 0.05, 2);  //left-down
    drawFilledCircle(0.20, -0.3, 0.05, 2);   //right-down
    //// ------------------------------------------------------------------
    glBegin(GL_QUADS); //(B-FACE)
    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.09, -0.02);  //right-up
    glVertex2f(-0.09, -0.02); //left-up
    glVertex2f(-0.20, -0.35);  //left-down
    glVertex2f(0.20, -0.35);   //right-down

    glColor4f(0.13f, 0.05f, 0.19f, 1);
    glVertex2f(0.12, -0.02);  //right-up
    glVertex2f(-0.12, -0.02); //left-up
    glVertex2f(-0.25, -0.3);  //left-down
    glVertex2f(0.25, -0.3);   //right-down
    glEnd();
    // ------------------------------------------------------------------

    // ------------------------------------------------------------------
    // drawing the filled circle //(PUR-FACE)
    glColor4f(0.52f, 0.39f, 0.72f, 1.0f);
    drawFilledCircle(0.0, 0.02, 0.07, 2);
    drawFilledCircle(0.16, 0.07, 0.04, 2);
    // ------------------------------------------------------------------
    // drawing the filled circle (EYES)
    glColor4f(1.0f, 1.0f, 1.0f, 1); //white eyes
    drawFilledCircle(0.05, -0.17, 0.06, 2);
    drawFilledCircle(-0.05, -0.17, 0.06, 2);

    glColor4f(0.26f, 0.18f, 0.32f, 1); //black eyes
    drawFilledCircle(0.04, -0.17, 0.03, 2);
    drawFilledCircle(-0.04, -0.17, 0.03, 2);

    glColor4f(1.0f, 1.0f, 1.0f, 1); //white shine eyes
    drawFilledCircle(0.03, -0.16, 0.005, 2);
    drawFilledCircle(-0.05, -0.16, 0.005, 2);
    drawFilledCircle(0.05, -0.17, 0.01, 2);
    drawFilledCircle(-0.03, -0.17, 0.01, 2);

    // -----------------------------------------------------------------------


//    glColor4f(0.73f, 0.61f, 0.76f, 1);
//    drawFilledCircle(0.0, -0.27, 0.03, -1.0);


}
void CornField() {
    float x = 0;
    float y = 0;

    glEnable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glPushMatrix();
    glTranslatef(0.0, sunY, 0);
    SunO();
    glPopMatrix();

    RoadO();
    couldO();

    jumpY2 = radius2 * sin(angle2);



    glPushMatrix();
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(0.0, 1.8, 0);
    glTranslatef(0, KimoY2, 0);
    glTranslatef(0, jumpY2, 0);
    Kimo();
    KemoFace();
    glPopMatrix();

    for (int i = 0; x < 3.4; i++) {
        if (cornY >= 0.02) {
            cornY = 0.01;
        }

        else {
            cornY += 0.00002;//0.00002


        }

        if (sunY >= 0.2) {
            sunY = 0.2;
        }
        else {
            sunY += 0.00020;//0.00020

        }

        if (KimoY2 <= -6) {
            KimoY2 = -6;


        }
        else {
            KimoY2 -= 0.00050;//0.00199

        }

        //-------------------------------------right
        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.65 + x, 1.0 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();



        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.60 + x, 0.7 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.57 + x, 0.3 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.52 + x, 0.0 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.46 + x, -0.3 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.40 + x, -0.6 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();



        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.34 + x, -0.9 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.29 + x, -1.2 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.26 + x, -1.5 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.23 + x, -1.8 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.20 + x, -2.1 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.17 + x, -2.4 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.14 + x, -2.7 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(0.11 + x, -3.0 + y, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        x += 0.4;//0.4
        y -= 0.2;//0.2

    }

    //-------------------------------------left
    float x2 = 0;
    float y2 = 0;
    for (int i = 0; x2 > -2.8; i++) {



        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-1.2 + x2, 1.0 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-1.15 + x2, 0.7 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-1.1 + x2, 0.3 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-1.05 + x2, 0.0 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-1.0 + x2, -0.3 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-0.95 + x2, -0.6 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();



        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-0.9 + x2, -0.9 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-0.85 + x2, -1.2 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-0.82 + x2, -1.5 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-0.77 + x2, -1.8 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-0.72 + x2, -2.1 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-0.67 + x2, -2.4 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-0.62 + x2, -2.7 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(-0.63 + x2, -3.0 + y2, 0.0);
        glTranslatef(cornY, 0.0, 0);
        corn();
        glPopMatrix();

        x2 -= 0.35;//0.35
        y2 -= 0.2;//0.2

    }

}
void jump() {


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    jumpY = radius * sin(angle);
    //Jumping characters, sister, brother and Kimo
    if (RY <= -0.8) {

        jumpY = radius * sin(0);
        glPushMatrix();
        glScalef(0.35, 0.35, 0.35);
        glTranslatef(-0.7, -2.0, 0.0);
        glTranslatef(-0.2, jumpY, 0.0);
        Kemo_Brother();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.35, 0.35, 0.35);
        glTranslatef(-1.4, -2.0, 0.0);
        glTranslatef(-0.2, jumpY, 0.0);
        Kemo_sister1();
        glPopMatrix();



        glPushMatrix();

        glScalef(0.35, 0.35, 0.35);
        glTranslatef(-0.5, -2.0, 0.0);
        glRotatef(-5.0, 0.0, 0.0, 1.0);

        /*  When the father and mother reach the middle of the burrow,
           the characters stop jumping and Kimo moves towards his mother*/

        if (KimoX >= 0.3) {
            KimoX = 0.3;

            if (KimoY >= 0.65) {

                if (KimoY >= 0.65 & KimoY <= 0.7) {

                    KimoY += 0.0005;//0.0010

                }
                if (KimoY > 0.7 & KimoY < 2.3) {
                    glScalef(0.84, 0.84, 0.84);
                    KimoY += 0.0020;//0.0200

                }
                if (KimoY >= 2.3) {
                    glScalef(0.8, 0.8, 0.8);
                    KimoY = 2.3;
                }
                glTranslatef(KimoX, KimoY, 0);

            }

            else {
                KimoY += 0.0020;//0.0200
                glTranslatef(KimoX, KimoY, 0);
            }

        }

        else {

            KimoX += 0.0020;//0.0200
            glTranslatef(KimoX, KimoY, 0);

        }

        Kimo_from_behind();
        glPopMatrix();

    }
    else {
        jumpY = radius * sin(angle);
        glPushMatrix();
        glScalef(0.35, 0.35, 0.35);
        glTranslatef(-0.2, -2.0, 0.0);
        glTranslatef(-0.2, jumpY, 0.0);
        Kemo_Brother();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.35, 0.35, 0.35);
        glTranslatef(-0.9, -2.0, 0.0);
        glTranslatef(-0.2, jumpY, 0.0);
        Kemo_sister1();
        glPopMatrix();



        glPushMatrix();
        glScalef(0.35, 0.35, 0.35);
        glTranslatef(-0.4, -2.0, 0.0);
        glTranslatef(-0.4, jumpY, 0.0);
        Kimo_from_behind();
        glPopMatrix();


    }



}
void move()
{
    //--------------------------------
    if (cloudX1 <= -0.27) {
        cloudX1 = -0.270;
    }
    else {
        cloudX1 -= 0.001;//0.002
    }
    glPushMatrix();
    glTranslatef(cloudX1, 0.02, 0);
    cloudO();
    glPopMatrix();
    //--------------------------------
    if (cloudX2 >= 0.36) {
        cloudX2 = 0.370;
    }
    else {
        cloudX2 += 0.001;
    }
    glPushMatrix();
    glTranslatef(cloudX2, -0.03, 0);
    cloudO2();
    glPopMatrix();
    //--------------------------------
    //Verify that the character's feet move forward and backward while walking
    // Move Kimo's Mother
    glPushMatrix();
    glScalef(0.38, 0.38, 0.38);
    glTranslatef(0.1, -0.4, 0.0);
    if (LY <= -0.8) {
        LY = -0.8;

    }
    else {
        if (isLeftFootForward) {
            LY -= stepSize;
            RY += stepSize;
        }
        else {
            LY += stepSize;
            RY -= stepSize;
        }
        if (LY <= -0.1f || LY >= -0.05f) {
            isLeftFootForward = !isLeftFootForward;
        }
        LY -= 0.003;

    }
    glTranslatef(0.1, LY, 0);
    MotherFootL();
    Kemo_Mother();
    glPopMatrix();

    //--------------------------------

    glPushMatrix();
    glScalef(0.38, 0.38, 0.38);
    glTranslatef(0.1, -0.4, 0.0);


    if (RY <= -0.8) {
        RY = -0.8;

    }
    else {
        if (isLeftFootForward) {
            LY -= stepSize;
            RY += stepSize;
        }
        else {
            LY += stepSize;
            RY -= stepSize;
        }
        if (RY <= -0.1f || RY >= -0.05f) {
            isLeftFootForward = !isLeftFootForward;
        }
        RY -= 0.003;

    }
    glTranslatef(0.1, RY, 0);
    MotherFootR();
    glPopMatrix();




    //--------------------------------------------------------------------
    // Move Kimo's Father
    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);

    glTranslatef(0.6, -0.4, 0.0);

    if (LY <= -0.8) {
        LY = -0.8;

    }
    else {
        if (isLeftFootForward) {
            LY -= stepSize;
            RY += stepSize;
        }
        else {
            LY += stepSize;
            RY -= stepSize;
        }
        if (LY <= -0.1f || LY >= -0.05f) {
            isLeftFootForward = !isLeftFootForward;
        }
        LY -= 0.003;

    }
    glTranslatef(0.1, LY, 0);
    FatherFootL();
    Kemo_Father();
    glPopMatrix();

    //--------------------------------

    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);
    glTranslatef(0.6, -0.4, 0.0);


    if (RY <= -0.8) {
        RY = -0.8;

    }
    else {
        if (isLeftFootForward) {
            LY -= stepSize;
            RY += stepSize;
        }
        else {
            LY += stepSize;
            RY -= stepSize;
        }
        if (RY <= -0.1f || RY >= -0.05f) {
            isLeftFootForward = !isLeftFootForward;
        }
        RY -= 0.003;

    }
    glTranslatef(0.1, RY, 0);
    FatherFootR();
    glPopMatrix();

    ///---------------------------------------------------



}
void chat() {
    if (transp <= 1.0) {
        transp += 0.02;//0.0005
    }
    else if (transp2 <= 1.0) {
        transp2 += 0.02;//0.0005
    }
    else if (transp3 <= 1.0) {
        transp3 += 0.02;//0.0005
    }
    else if (transp4 <= 1.0) {
        transp4 += 0.04;//0.0007
    }
    else if (transp5 <= 1.0) {
        transp5 += 0.04;//0.0007
    }
    else if (transp6 <= 1.0) {
        transp6 += 0.04;//0.0007
    }
    glColor4f(1.0f, 1.0f, 1.0f, transp);
    drawFilledCircle(-0.35, -0.55, 0.02, 2);
    glColor4f(1.0f, 1.0f, 1.0f, transp2);
    drawFilledCircle(-0.32, -0.5, 0.025, 2);

    glColor4f(1.0f, 1.0f, 1.0f, transp3);
    drawFilledCircle(-0.2, -0.45, 0.06, 2);
    drawFilledCircle(-0.12, -0.38, 0.07, 2);
    drawFilledCircle(-0.22, -0.38, 0.05, 2);
    drawFilledCircle(-0.1, -0.45, 0.08, 2);
    drawFilledCircle(-0.05, -0.38, 0.05, 2);

    glColor4f(0.0f, 0.0f, 0.0f, transp4);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(-0.19, -0.42);
    glColor4f(0.0f, 0.0f, 0.0f, transp5);
    glVertex2f(-0.14, -0.42);
    glColor4f(0.0f, 0.0f, 0.0f, transp6);
    glVertex2f(-0.09, -0.42);
    glEnd();

}
void Rabbit_f()
{

    // ------------------------------------------------------------------
    // drawing the filled circle //(WH-FACE)
    glColor4f(1.0f, 1.0f, 1.0f, 1.0);
    drawFilledCircle(0.13, -0.25, 0.10, 2);  //right
    drawFilledCircle(-0.13, -0.25, 0.10, 2); //left
    drawFilledCircle(0.0, -0.40, 0.10, 2);   //down
    // ------------------------------------------------------------------
    glBegin(GL_TRIANGLES); //(WH-FACE)
    glColor4f(1.0f, 1.0f, 1.0f, 1);

    glVertex2f(0.13, -0.15); //right
    glVertex2f(-0.13, -0.15); //left
    glVertex2f(0.0, -0.40); //center
    glEnd();
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(WH-FACE)

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    glVertex2f(0.219, -0.3);   //right-up
    glVertex2f(-0.219, -0.3);  //left-up
    glVertex2f(-0.085, -0.45); //left-down
    glVertex2f(0.085, -0.45);  //right-down
    glEnd();
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(FEET & HANDS)

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    //////RIGHT-FEET
    //glVertex2f(0.04, -0.4);   //right-up
    //glVertex2f(0.005, -0.4);  //left-up
    //glVertex2f(0.005, -0.7); //left-down
    //glVertex2f(0.04, -0.7);  //right-down
    ////LEFT-FEET
    //glVertex2f(-0.005, -0.4);   //right-up
    //glVertex2f(-0.04, -0.4);  //left-up
    //glVertex2f(-0.04, -0.7); //left-down
    //glVertex2f(-0.005, -0.7);  //right-down
    //RIGHT-HAND
    glVertex2f(0.03, -0.22);   //right-up
    glVertex2f(0.0, -0.25);  //left-up
    glVertex2f(0.20, -0.60); //left-down
    glVertex2f(0.23, -0.57);  //right-down
    //LEFT-HAND
    glVertex2f(-0.03, -0.22);   //right-up
    glVertex2f(0.0, -0.25);  //left-up
    glVertex2f(-0.20, -0.60); //left-down
    glVertex2f(-0.23, -0.57);  //right-down
    glEnd();
    // ------------------------------------------------------------------
    //// drawing half filled circle (P-SHOES)
    //glColor4f(0.85f, 0.65f, 0.9f, 1);
    //drawFilledCircle(0.04, -0.7, 0.035, 2);
    //drawFilledCircle(-0.04, -0.7, 0.035, 2);
    // ------------------------------------------------------------------
    // drawing half filled circle (P-HANDS)
    glColor4f(0.85f, 0.65f, 0.9f, 1);
    drawFilledCircle(0.215, -0.585, 0.035, 2); //midpoint formula = (x1 + x2)/2, (y1 + y2)/2.
    drawFilledCircle(-0.215, -0.585, 0.035, 2);
    // ------------------------------------------------------------------
    // drawing the filled circle (EARS)
    //(WHITE)
    glColor4f(1.0f, 1.0f, 1.0f, 1);
    drawFilledCircle(0.08, 0.09, 0.06, 2);//right
    drawFilledCircle(-0.08, 0.09, 0.06, 2);//left
    //(PINK)
    glColor4f(0.85f, 0.65f, 0.9f, 1);
    drawFilledCircle(0.08, 0.09, 0.03, 2);//right
    drawFilledCircle(-0.08, 0.09, 0.03, 2);//left
    // ------------------------------------------------------------------
    glBegin(GL_QUADS); //(EARS)

    glColor4f(1.0f, 1.0f, 1.0f, 1); //(WHITE)
    //right-ear
    glVertex2f(0.14, 0.09); //right-up
    glVertex2f(0.02, 0.09); //left-up
    glVertex2f(0.0, -0.15); //left-down
    glVertex2f(0.03, -0.15); //right-down
    //left-ear
    glVertex2f(-0.02, 0.09); //right-up
    glVertex2f(-0.14, 0.09); //left-up
    glVertex2f(-0.03, -0.15); //left-down
    glVertex2f(-0.0, -0.15); //right-down

    glColor4f(0.85f, 0.65f, 0.9f, 1); //(PINK)
    //right-ear
    glVertex2f(0.11, 0.09); //right-up
    glVertex2f(0.05, 0.09); //left-up
    glColor4f(0.65f, 0.45f, 0.7f, 1);
    glVertex2f(0.01, -0.15); //left-down
    glVertex2f(0.02, -0.15); //right-down
    glColor4f(0.85f, 0.65f, 0.9f, 1);
    //left-ear
    glVertex2f(-0.05, 0.09); //right-up
    glVertex2f(-0.11, 0.09); //left-up
    glColor4f(0.55f, 0.35f, 0.6f, 1);
    glVertex2f(-0.02, -0.15); //left-down
    glVertex2f(-0.01, -0.15); //right-down

    glEnd();

}





//--------------------------------------------------
void button() {
    glBegin(GL_QUADS);
    //glColor3f(0.0f, 0.0f, 0.0f);  // Red color
    glVertex2f(-0.1f, 0.34f);
    glVertex2f(0.2f, 0.34f);
    glVertex2f(0.2f, 0.16f);
    glVertex2f(-0.1f, 0.16f);

    glVertex2f(-0.1f, 0.3f);
    glVertex2f(-0.1f, 0.2f);
    glVertex2f(-0.14f, 0.2f);
    glVertex2f(-0.14f, 0.3f);


    glVertex2f(0.2f, 0.3f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.24f, 0.2f);
    glVertex2f(0.24f, 0.3f);
    glEnd();

    drawFilledCircle(-0.1, 0.3, 0.04, 2);
    drawFilledCircle(0.2, 0.3, 0.04, 2);
    drawFilledCircle(0.2, 0.2, 0.04, 2);
    drawFilledCircle(-0.1, 0.2, 0.04, 2);



}

void Homepage() {
    glBegin(GL_QUADS);
    glColor3f(0.85098f, 0.85098f, 1.0f);  // Red color
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    glColor3f(0.88235f, 0.50196f, 0.54901f);
    drawFilledCircle(-1.0, 1.0, 0.3, 2);
    drawFilledCircle(-0.55, 1.14, 0.3, 2);
    drawFilledCircle(-0.4, 1.2, 0.3, 2);
    drawFilledCircle(-1.0, 0.7, 0.2, 2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glScalef(1.2, 1.2, 1.2);
    glTranslatef(-0.5, 0.1, 0.0);
    Kimo();
    KemoFace();
    glPopMatrix();


    glPushMatrix();
    glScalef(0.6, 0.5, 0.5);
    glTranslatef(1.18, 0.26, 0.0);
    Kemo_Mother();
    glPopMatrix();


    glPushMatrix();
    glScalef(0.7, 0.5, 0.5);
    glTranslatef(1.0, -0.4, 0.0);
    Kemo_Father();
    glPopMatrix();



    glPushMatrix();
    glScalef(.7, 0.7, 0.7);
    glTranslatef(1.1, 1.2, 0.0);
    Rabbit_f();
    faceExep();
    accessories_father();
    glLineWidth(1.0f);
    glPopMatrix();



    glPushMatrix();
    glScalef(.7, 0.7, 0.7);
    glTranslatef(1.05, -0.56, 0.0);
    Rabbit();
    faceExep();
    accessories_mother();
    glLineWidth(1.0f);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(-1.2, 0.8, 0.0);
    owl();
    glPopMatrix();



    glPushMatrix();
    glColor3f(0.8666f, 0.2823f, 0.3333f);
    glScalef(1.2, 1.0, 1.2);
    glTranslatef(0.0, -0.2, 0.0);
    button();
    glPopMatrix();


    glPushMatrix();
    glColor3f(0.88235f, 0.50196f, 0.54901f);
    glScalef(1.0, 0.8, 1.0);
    glTranslatef(0.01, -0.185, 0.0);
    button();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8666f, 0.2823f, 0.3333f);
    glScalef(1.2, 1., 1.2);
    glTranslatef(0.0, -0.44, 0.0);
    button();
    glPopMatrix();



    glPushMatrix();
    glColor3f(0.88235f, 0.50196f, 0.54901f);
    glColor3f(0.88235f, 0.50196f, 0.54901f);
    glScalef(1.0, 0.8, 1.0);
    glTranslatef(0.01, -0.48, 0.0);
    button();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(-0.4f, 0.5f);
    const char* text = "THE LOST KEMO!";
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
        text++;
    }

    glRasterPos2f(-0.09f, 0.0f);
    const char* text2 = "START";
    while (*text2) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text2);
        text2++;
    }

    glRasterPos2f(-0.07f, -0.23f);
    const char* text3 = "READ";
    while (*text3) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text3);
        text3++;
    }

}
//-------------------------------------------------------------------------
GLuint LoadTexture( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;
    
    //The following code will read in our RAW file
    file = fopen( filename, "rb" );
    
    if ( file == NULL )
    {
        exit(0);
        return 0;
    }
    
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    
    fclose( file );
    
    
    // reorder the image colors to RGB not BGR
    for(int i = 0; i < width * height ; ++i)
    {
        int index = i*3;
        unsigned char B,R;
        B = data[index];
        R = data[index+2];
        
        data[index] = R;
        data[index+2] = B;
        
    }
    
    
    /////////////////////////////////////////
    // texture image
    //////
    glGenTextures( 1, &texture );            //generate the texture with the loaded data
    glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it's array
    
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //set texture environment parameters
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    /////////////////////////////////////////
    
    free( data ); //free the texture array
    
    if (glGetError()!=GL_NO_ERROR)
        printf("GLError in genTexture()\n");
    
    return texture; //return whether it was successfull
}
//-------------------------------------------------------------------------
// Function to handle timer event for Scene animation
void timerEvent1(int value) {
    glutPostRedisplay();
    auto currentTime = std::chrono::steady_clock::now();
    timer1 = currentTime + std::chrono::milliseconds(TIMER_INTERVAL);
    glutTimerFunc(TIMER_INTERVAL, timerEvent1, 0);
    currentShape++;
}
void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(refreshmill, timer, 0);
}
// Function to update the rotation angle
void updateAngle(int value) {
    angle += 0.1; // Change the rotation speed here
    angle2 += 0.1;
    //Limit the angle within 0 to 360 degrees
    if (angle > 90.0) {
        angle -= 90;
    }
    if (angle2 > 90.0) {
        angle2 -= 90;
    }

    glutPostRedisplay();
    glutTimerFunc(40, updateAngle, 0); // Change the rotation interval here
}

//--------------------------------------------------
void Scene1() {
    Burrow();
    jump();
    move();
}
//--------------------------------------------------
void Scene2() {

    //the sky
    glBegin(GL_QUADS);
    glColor3f(0.8784f, 0.9490f, 0.9803f);
    glVertex2f(-1.0f, -0.2f);
    glVertex2f(1.0f, -0.2f);

    glColor3f(0.6588f, 0.8392f, 0.9058f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
    //Green grass
    glColor4f(0.6745f, 0.7411f, 0.1098f, 1);
    drawFilledCircle(0.0, -1.0, 1.4, 1.0);
    glColor4f(0.3686f, 0.5490f, 0.04705f, 0.3);
    drawFilledCircle(-1.0, -1.0, 1.0, 1.0);
    glColor4f(0.3686f, 0.5490f, 0.04705f, 0.3);
    drawFilledCircle(1.0, -1.0, 1.0, 1.0);


    //--------------------------------

    CornField();

}
//--------------------------------------------------
void scene3()
{
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
    glEnable(GL_BLEND);
    if (txc <= 1.0) {
        txc -= 0.0005;//0.00005
    }
    if (tys >= -1.0 & transpS <= 0.8) {
        tys -= 0.0001;//0.00001
    }
    if (transpS <= 0.8) {
        transpS += 0.0016;//0.00009
    }
    if (tyk <= -0.5) {
        tyk += 0.0008;//0.00003
    }
    if (tsk >= 0.09) {
        tsk -= 0.0008;//0.00003
    }
    if (trl <= 14.0 & tyl >= -0.14) { //------------------------------HEENAAA
        trl += 0.03;//0.005
        tyl -= 0.000300;//0.00005
    }
    else if (trl > 5) {//------------------------------HEENAAA
        trl -= 0.015;//0.015
        tyl += 0.001000;//0.0001
    }

    sunset();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0, tys, 0.0);
    sunL();
    glPopMatrix();

    floor();
    roadL();

    glPushMatrix();
    glTranslatef(txc, 0.0, 0.0);
    cloudL();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1, -0.4, 0.0);
    glScalef(0.25, 0.25, 1.0);
    treeFarest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, -0.4, 0.0);
    glScalef(-0.35, 0.35, 1.0);
    treeFarest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4, -0.4, 0.0);
    glScalef(-0.2, 0.2, 1.0);
    treeFarest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4, -0.4, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glPushMatrix();
    glTranslatef(-0.3, -0.55, 0.0);
    glScalef(0.3, 0.3, 1.0);
    treeFarest();
    glPopMatrix();
    glTranslatef(-3.0, -0.55, 0.0);
    glScalef(-0.3, 0.3, 1.0);
    treeFarest();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.28, -0.5, 0.0);
    glScalef(-0.2, 0.2, 1.0);
    treeFarest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8, -0.2, 0.0);
    treeFarest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7, -0.4, 0.0);
    glScalef(0.28, 0.28, 1.0);
    treeFarest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3, -0.4, 0.0);
    glScalef(0.35, 0.35, 1.0);
    treeFarest();
    glPopMatrix();
    treeFarest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1, -0.2, 0.0);
    glScalef(0.6, 0.6, 1.0);
    treeFar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2, -0.28, 0.0);
    glScalef(-0.65, 0.65, 1.0);
    treeFar();
    glPopMatrix();

    Tree();

    glPushMatrix();

    glTranslatef(0.0, tyl, 0.0);
    glRotatef(trl, 0.0, 0.0, 1.0);
    leaves2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3, 0.05, 0.0);
    glScalef(-1.0, 1.0, 1.0);
    Tree();
    glTranslatef(0.0, tyl, 0.0);
    glRotatef(trl, 0.0, 0.0, 1.0);
    
    leaves2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2, -1.2, 0.0);
    glRotatef(145.0, 0.0, 0.0, 1.0);
    sapling();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, tyk, 0.0);
    glScalef(tsk, tsk, 1.0);
    Kimo_from_behind();
    glPopMatrix();

    glutPostRedisplay();
    glutSwapBuffers();
}
//--------------------------------------------------
void scene4(){
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
    glEnable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if (xpos_s4 <= 2) {
        xpos_s4 += 0.005;
        std::cout << "xpos_s4..." << xpos_s4;
    }
    
    if (xpos_cloud_reverse >= -2) {
        xpos_cloud_reverse -= 0.002;
        std::cout << "xpos_cloud_reverse..." << xpos_cloud_reverse;
    } else {
        xpos_cloud_reverse = 0.9;
    }
    
    if (ypos_s4 <= 0.5) {
        ypos_s4 += 0.001;
        std::cout << "ypos_s4..." << ypos_s4;
    }
    
    //-----------------
    glBegin(GL_QUADS);
    //floor-green
    glColor3f(0.3f, 0.6f, 0.2f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f,-0.4f);
    glColor3f(0.5f, 0.8f, 0.4f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    
    //sky-orange
    glColor4f(0.9f, 0.6f, 0.2f, 0.8f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f,-0.4f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glEnd();
    //-----------------
    //---clouds
    //( 1 )
    glPushMatrix();
        glTranslatef(xpos_cloud_reverse, 0, 0);
        glScalef(0.8, 0.8, 1);
    cloudM();
    glPopMatrix();
    //( 2 )
    glPushMatrix();
        glTranslatef(xpos_cloud_reverse-0.7, 0.3, 0);
        glScalef(0.8, 0.8, 1);
    cloudM();
    glPopMatrix();
    //---tree-up-right
    glPushMatrix();
        glTranslatef(0.1, 0.5, 0);
    TreeWood();
    leaves();
    glPopMatrix();
    //---tree-up-left
    glPushMatrix();
        glTranslatef(-0.45, 0.3, 0);
        glScalef(-1, 1, 1);
    TreeWood();
    leaves();
    glPopMatrix();
    //---walnut
    glPushMatrix();
        glTranslatef(xpos_s4, ypos_s4, 0);
        glTranslated(0.4, -0.25, 0);
        glRotatef(angle_s4, 0.0, 0.0, -1);
        glTranslated(-0.4, 0.25, 0);
    walnut();
    glPopMatrix();
    //---Kemo
    glPushMatrix();
        glTranslatef(xpos_s4, ypos_s4, 0);
    KemoFromTheSide();
    glPopMatrix();
    //---tree-down-right
    glPushMatrix();
        glTranslatef(0.2, -0.5, 0);
    TreeWood();
    leaves();
    glPopMatrix();
    //---tree-down-left
    glPushMatrix();
        glTranslatef(-0.5, -0.5, 0);
        glScalef(-0.8, 0.8, 1);
    TreeWood();
    leaves();
    glPopMatrix();
    //---tree-down-mid-right
    glPushMatrix();
        glTranslatef(-0.1, -0.8, 0);
        glScalef(0.8, 0.8, 1);
    TreeWood();
    leaves();
    glPopMatrix();
    //---tree-down-mid-left
    glPushMatrix();
        glTranslatef(-0.9, -0.8, 0);
        glScalef(1, 1, 1);
    TreeWood();
    leaves();
    glPopMatrix();
    //------------
    
//    forMe();
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
    angle_s4 += 0.5;
    
    
}
//--------------------------------------------------
void scene5() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPushMatrix();

    drawBackground();



    glPushMatrix();
    glTranslatef(-0.7, -0.5, 0.0);
    glScalef(-0.3, 0.3, 1.0);
    TreeWood();
    leaves();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.39, -0.2, 0.0);
    glScalef(0.3, 0.3, 1.0);
    TreeWood();
    leaves();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.39, 0.0, 0.0);
    glScalef(-0.3, 0.3, 1.0);
    TreeWood();
    leaves();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.04, 0.0, 0.0);
    glScalef(0.2, 0.2, 1.0);
    TreeWood();
    leaves();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.05, -0.5, 0.0);
    glScalef(0.3, 0.3, 1.0);
    drawCave2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8, -0.2, 0.0);
    glScalef(-0.25, 0.25, 1.0);
    drawCave2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9, -0.99, 0.0);
    glScalef(-0.3, 0.3, 1.0);
    drawCave();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.4, -0.2, 0.0);
    glScalef(-0.2, 0.2, 1.0);
    drawCave();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.4, -0.2, 0.0);
    glScalef(0.2, 0.2, 1.0);
    TreeWood();
    leaves();
    glPopMatrix();

    if (Kxpos >= 2.25) {
        Kxpos = 2.25;
    }
    else {
        Kxpos += 0.008;//0.0009
    }

    glPushMatrix();
    glTranslatef(1.1, -0.6, 0.0);
    glScalef(0.5, 0.5, 1.0);
    glTranslatef(-Kxpos, 0.0, 0.0);
    Kimo();
    sadKemo();
    glPopMatrix();






    glutSwapBuffers();
    glutPostRedisplay();

}
//--------------------------------------------------
void scene6() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    drawBackground();
    glPushMatrix();
    //reflection over y
    glScalef(-1.5, 1.5, 1.0);
    glTranslatef(0.1, -0.1, 0.0);
    drawCave2();
    glPopMatrix();
    if (Kxpos == 2.25) {
        Kxpos = 0;
    }
    if (Kxpos >= 2.26) {
        Kxpos = 2.26;
    }
    else {
        Kxpos += 0.0065;//0.00065
    }

    glPushMatrix();
    glTranslatef(1.3, -0.6, 0.0);
    glScalef(0.5, 0.5, 1.0);
    glTranslatef(-Kxpos, 0.0, 0.0);
    Kimo();
    sadKemo();
    glPopMatrix();

    //kemo crying

//    if (Typos <= 0.4) {
//        Typos += 0.0003;
//
//    }
//    else {
//        Typos = Typos - 0.2;
//    }
//
//    if (Txpos <= 3.69) {
//        Txpos += 0.0010586;
//
//    }
        if(Typos<= 0.4){
            Typos+= 0.00915;//0.0003+0.00585
    
        }
        else{
            Typos = Typos-0.2;
        }
    
        if(Txpos<= 3.69){
            Txpos+= 0.0105;//0.0010586+0.00585
    
        }
    float Kxpos = 0.0;

        if(Kxpos <= 2.25){
            Kxpos += 0.0019;
        }

    glPushMatrix();
    glTranslatef(1.31, -0.45, 0.0);
    glScalef(0.3, 0.3, 1.0);
    glTranslatef(-Txpos, -Typos, 0.0);
    tears();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.25, -0.45, 0.0);
    glScalef(0.3, 0.3, 1.0);
    glTranslatef(-Txpos, -Typos, 0.0);
    tears();
    glPopMatrix();

    glutPostRedisplay();
    glutSwapBuffers();




}
//--------------------------------------------------
void Scene7() {
    glEnable(GL_BLEND);
    ///The sky
    glColor4f(0.6, 0.9, 1.0, 1.0);
    glRectd(-1.0, -0.4, 1.0, 1.0);
    if (sposx >= 0.1) {
        sposx -= 0.003;//0.00015
    }
    if (sposy <= 0.55) {
        sposy += 0.003;//0.00015
    }
    //sun
    glPushMatrix();
    glTranslatef(sposx, sposy, 0.0);
    sunR();
    glPopMatrix();

    ///cloud
    glPushMatrix();
    glTranslatef(-0.2, 0.2, 0.0);
    glScalef(0.7, 0.7, 0.0);
    cloudM();
    glPopMatrix();
    //cloud2
    glPushMatrix();
    glTranslatef(1.0, 0.53, 0.0);
    glScalef(0.5, 0.5, 0.0);
    cloudM();
    glPopMatrix();
    /// THE Grass
    glColor3f(0.0f, 0.5f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, -0.4);
    glVertex2f(-1.0, -0.4);
    glEnd();

    ///the cave
    glPushMatrix();
    glTranslatef(-0.5, -0.4, 0.0);
    glScalef(-0.6, 0.6, 0.0);
    drawCave2();
    glPopMatrix();

    ///the tree
    glPushMatrix();
    glTranslatef(0.3, 0.3, 0.0);
    glScalef(0.9, 0.9, 0.0);
    TreeWood();
    leaves();
    glPopMatrix();

    //carrot

    glPushMatrix();
    glTranslatef(0.0, 0.18, 0.0);
    carrots();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.08, 0.0);
    carrots();
    glPopMatrix();

    glPushMatrix();
    carrots();
    glPopMatrix();

    glutPostRedisplay();
    glutSwapBuffers();
}
//--------------------------------------------------
void Scene8() {
    glEnable(GL_BLEND);
    /// the Sky
    glColor4f(0.6, 0.9, 1.0, 1.0);
    glRectd(-1.0, -0.3, 1.0, 1.0);

    /// THE GRASS
    glBegin(GL_QUADS);
    glColor4f(0.0, 0.7, 0.3, 1.0);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, -0.3);
    glVertex2f(-1.0, -0.3);
    glEnd();
    if (cavepos <= 1.6) {
        cavepos += 0.0015;//0.0001

    }

    if (nfpos >= 0.0) {
        nfpos -= 0.005;//0.00025
    }
    if (sfpos <= 1.0) {
        sfpos += 0.005;//0.0002
    }
    //CAVE
    glPushMatrix();
    glTranslatef(0.0, -0.3, 0.0);
    glScalef(cavepos, 1.6, 0.0);
    drawCave2();
    glPopMatrix();

    //rock
    glPushMatrix();
    glTranslatef(-0.45, -1.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    glScalef(0.5, 0.5, 0.0);
    rock();
    glPopMatrix();

    //kemo
    glPushMatrix();
    glTranslatef(-0.4, -0.7, 0.0);
    glScalef(0.4, 0.4, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    Kimo();
    KemoSleepEyes();
    glPopMatrix();

    //baby
    glPushMatrix();
    glTranslatef(-0.25, 0.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    glScalef(0.3, 0.3, 0.0);
    Rabbit();
    faceExepSleep();
    accessories_baby();
    glPopMatrix();

    //girl
    glPushMatrix();
    glTranslatef(-0.32, -0.17, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    glScalef(0.4, 0.4, 0.0);
    Rabbit();
    faceExepSleep();
    accessories_girl();
    glPopMatrix();

    //boy
    glPushMatrix();
    glTranslatef(-0.4, -0.4, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    glScalef(0.46, 0.46, 0.0);
    Rabbit();
    faceExepSleep();
    accessories_boy();
    glPopMatrix();

    // mother
    glPushMatrix();
    glTranslatef(0.1, -0.3, 0.0);
    glScalef(0.7, 0.7, 0.0);
    Rabbit();
    glColor4f(0.4f, 0.4f, 0.4f, nfpos);//black
    drawFilledCircle(0.017, -0.33, 0.022, 2);
    drawFilledCircle(-0.017, -0.33, 0.022, 2);

    glColor4f(1.0f, 1.0f, 1.0f, nfpos);//white
    drawFilledCircle(0.0175, -0.324, 0.020, 2);
    drawFilledCircle(-0.0175, -0.324, 0.020, 2);

    //CKEEKS
    glColor4f(0.85f, 0.65f, 0.9f, 1);
    drawFilledCircle(0.08f, -0.31f, 0.025, 2);
    drawFilledCircle(-0.08f, -0.31f, 0.025, 2);
    // ------------------------------------------------------------------
    glLineWidth(6.0f); // (EYES)
    glBegin(GL_LINES);

    glColor4f(0.4f, 0.4f, 0.4f, nfpos);
    //RIGHT-EYES
    glVertex2f(0.08f, -0.30f);//right
    glVertex2f(0.05f, -0.26f);//head

    glVertex2f(0.05f, -0.26f);//head
    glVertex2f(0.02f, -0.30f);//left
    //LEFT-EYES
    glVertex2f(-0.02f, -0.30f);//right
    glVertex2f(-0.05f, -0.26f);//head

    glVertex2f(-0.05f, -0.26f);//head
    glVertex2f(-0.08f, -0.30f);//left
    glEnd();
    /////////
    // ------------------------------------------------------------------
    //drawing the filled circle (MOUTH & CKEEKS)
    //MOUTH
    glColor4f(0.4f, 0.4f, 0.4f, sfpos);//black
    drawFilledCircle(0.0, -0.35, 0.022, 2);
    drawFilledCircle(0.0, -0.36, 0.022, 2);
    drawFilledCircle(0.0, -0.37, 0.022, 2);

    //RIGHT-EYEBROWS
    glColor4f(0.4f, 0.4f, 0.4f, sfpos);//black
    drawFilledCircle(0.04, -0.25, 0.02, 2);
    glColor4f(1.0f, 1.0f, 1.0f, sfpos);//white
    drawFilledCircle(0.04, -0.26, 0.02, 2);
    //LEFT-EYEBROWS
    glColor4f(0.4f, 0.4f, 0.4f, sfpos);//black
    drawFilledCircle(-0.04, -0.25, 0.02, 2);
    glColor4f(1.0f, 1.0f, 1.0f, sfpos);//white
    drawFilledCircle(-0.04, -0.26, 0.02, 2);

    //RIGHT-EYE
    glColor4f(0.4f, 0.4f, 0.4f, sfpos);//black
    drawFilledCircle(0.04, -0.28, 0.015, 2);
    drawFilledCircle(0.04, -0.29, 0.015, 2);
    drawFilledCircle(0.04, -0.3, 0.015, 2);
    //LEFT-EYE
    glColor4f(0.4f, 0.4f, 0.4f, sfpos);//black
    drawFilledCircle(-0.04, -0.28, 0.015, 2);
    drawFilledCircle(-0.04, -0.29, 0.015, 2);
    drawFilledCircle(-0.04, -0.3, 0.015, 2);

    accessories_mother();
    glTranslatef(0.0, 0.2, 0.0);
    thinkingCloud();
    glPopMatrix();
    glutPostRedisplay();
    glutSwapBuffers();
}
//--------------------------------------------------
void Scene9() {

    glEnable(GL_BLEND);
    //the grass
    glColor3f(0.0f, 0.5f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-1, -1);
    glVertex2f(-0.9990300696302, -0.2679402809972);
    glVertex2f(-0.7981409893297, -0.3237947626629);
    glVertex2f(-0.5849247916638, -0.3431780533598);
    glVertex2f(-0.3571711259753, -0.3625613440567);
    glVertex2f(-0.1536465736579, -0.3625613440567);
    glVertex2f(-0.003426070757, -0.3237947626629);
    glVertex2f(0.1758693681893, -0.3334864080113);
    glVertex2f(0.3163982257418, -0.3334864080113);
    glVertex2f(0.45208126062, -0.3286405853371);
    glVertex2f(0.6265308768921, -0.3189489399886);
    glVertex2f(0.7719055571188, -0.2898740039433);
    glVertex2f(0.9997404752048, -0.2328707755275);
    glVertex2f(1, -1);
    glEnd();


    //the revier
    glColor3f(0.31, 0.718, 0.855);
    glBegin(GL_POLYGON);
    glVertex2f(-0.9990300696302, -0.2679402809972);
    glVertex2f(-0.7981409893297, -0.3237947626629);
    glVertex2f(-0.5849247916638, -0.3431780533598);
    glVertex2f(-0.3571711259753, -0.3625613440567);
    glVertex2f(-0.1536465736579, -0.3625613440567);
    glVertex2f(-0.003426070757, -0.3237947626629);
    glVertex2f(0.1758693681893, -0.3334864080113);
    glVertex2f(0.3163982257418, -0.3334864080113);
    glVertex2f(0.45208126062, -0.3286405853371);
    glVertex2f(0.6265308768921, -0.3189489399886);
    glVertex2f(0.7719055571188, -0.2898740039433);
    glVertex2f(0.9997404752048, -0.2328707755275);
    glVertex2f(1.0010926629269, -0.1091295207928);
    glVertex2f(0.8033159676732, -0.0877534985346);
    glVertex2f(0.6340372823932, -0.0944481358055);
    glVertex2f(0.4460878913812, -0.0949188017361);
    glVertex2f(0.2426767180097, -0.1014106476948);
    glVertex2f(0.0327736986795, -0.1100664423063);
    glVertex2f(-0.1767199741906, -0.1151470601685);
    glVertex2f(-0.3632701863927, -0.1242116548109);
    glVertex2f(-0.5259693009785, -0.1355733626243);
    glVertex2f(-0.6961501281219, -0.1355733626243);
    glVertex2f(-0.8558259659355, -0.1481793498202);
    glVertex2f(-0.9940839032239, -0.1658362188797);
    glVertex2f(-0.9990300696302, -0.2679402809972);
    glEnd();

    //the sky
    glColor4f(0.6, 0.9, 1.0, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(1.0010926629269, -0.1091295207928);
    glVertex2f(0.8033159676732, -0.0877534985346);
    glVertex2f(0.6340372823932, -0.0944481358055);
    glVertex2f(0.4460878913812, -0.0949188017361);
    glVertex2f(0.2426767180097, -0.1014106476948);
    glVertex2f(0.0327736986795, -0.1100664423063);
    glVertex2f(-0.1767199741906, -0.1151470601685);
    glVertex2f(-0.3632701863927, -0.1242116548109);
    glVertex2f(-0.5259693009785, -0.1355733626243);
    glVertex2f(-0.6961501281219, -0.1355733626243);
    glVertex2f(-0.8558259659355, -0.1481793498202);
    glVertex2f(-0.9998985224174, -0.1658362188797);
    glColor4f(0.6, 0.9, 1.0, 1.0);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glEnd();



    //the land
    glColor3f(0.886, 0.718, 0.357);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, -1.0);
    glVertex2f(-1.0001611675542, -0.2835394954788);
    glVertex2f(-0.878585723896, -0.3396512387057);
    glVertex2f(-0.9463874136285, -0.3957629819325);
    glVertex2f(-0.9019656169072, -0.3887490140292);
    glVertex2f(-0.9627533387363, -0.4284948321482);
    glVertex2f(-0.9043036062083, -0.4378467893527);
    glVertex2f(-0.976781274543, -0.4612266823639);
    glVertex2f(-0.9113175741117, -0.4962965218807);
    glVertex2f(-0.9627533387363, -0.5360423399997);
    glVertex2f(-0.9294694274127, -0.5375377421187);
    glVertex2f(-0.9505782686808, -0.5635178544487);
    glVertex2f(-0.7638462113089, -0.5732603965725);
    glVertex2f(-0.7849550525771, -0.5959929948613);
    glVertex2f(-0.6518069768858, -0.631715649315);
    glVertex2f(-0.5868566960608, -0.6512007335625);
    glVertex2f(-0.4926787888645, -0.6593195186656);
    glVertex2f(-0.3205605446783, -0.7453786407588);
    glVertex2f(-0.3, -0.8);
    glVertex2f(-0.1444679684512, -0.833543359687);
    glVertex2f(-0.0810292892513, -0.8526352486703);
    glVertex2f(0.0232824304087, -0.8588628140232);
    glVertex2f(0.0419651264673, -0.9040126628313);
    glVertex2f(0.1540613028184, -0.9008988801548);
    glVertex2f(0.2863970665663, -0.8931144234638);
    glVertex2f(0.277055718537, -0.932036706919);
    glVertex2f(0.3751398728443, -0.9382642722719);
    glVertex2f(0.5380603691378, -0.995424502811);
    glEnd();
    if (Kxpos == 2.26) {
        Kxpos = 0;
    }
    if (cpos >= 0.55) {
        cpos -= 0.005;//0.0005
    }

    if (dposx >= -0.68) {
        dposx -= 0.0035;//0.0002
    }

    if (dposy >= -0.25) {
        dposy -= 0.0040;//0.00025
    }

    if (gpos <= -0.4) {
        gpos += 0.001;//0.00005
    }

    if (kpos >= -0.55) {
        kpos -= 0.001;//0.00005
    }
    ///the trees
    glPushMatrix();
    glTranslatef(-0.12, 0.7, 0.0);
    glScalef(-1.2, 1.3, 0.0);
    TreeWood();
    leaves();
    glPopMatrix();
    //sun
    glPushMatrix();
    glTranslatef(0.2, 0.4, 0.0);
    glScalef(1.2, 1.2, 0.0);
    sunR();
    glPopMatrix();
    //cave
    glPushMatrix();
    glTranslatef(0.9, -0.1, 0.0);
    glScalef(0.7, 0.7, 0.0);
    drawCave2();
    glPopMatrix();

    //girl
    glPushMatrix();
    glTranslatef(gpos, -0.2, 0.0);
    glScalef(0.4, 0.4, 0.0);
    Rabbit();
    faceExep();
    accessories_girl();
    glPopMatrix();

    //boy
    glPushMatrix();
    glTranslatef(-0.15, -0.2, 0.0);
    glScalef(0.5, 0.5, 0.0);
    Rabbit();
    faceExep();
    accessories_boy();
    glPopMatrix();

    //baby
    glPushMatrix();
    glTranslatef(0.46, -0.3, 0.0);
    glScalef(0.3, 0.3, 0.0);
    Rabbit();
    faceExep();
    accessories_baby();
    glPopMatrix();


    // mother
    glPushMatrix();
    glTranslatef(0.2, -0.04, 0.0);
    glScalef(0.7, 0.7, 1.0);
    Rabbit();
    faceExep();
    accessories_mother();
    glPopMatrix();


    //Kemo
    glPushMatrix();
    glTranslatef(-0.4, kpos, 0.0);
    glScalef(0.4, 0.4, 0.0);
    Kimo();
    KemoFace();
    glPopMatrix();

    //carrot
    glPushMatrix();
    glTranslatef(cpos, 0.15, 0.0);
    carrot();
    glPopMatrix();

    // father
    glPushMatrix();
    glTranslatef(dposx, dposy, 0.0);
    glScalef(0.9, 0.9, 1.0);
    Rabbit();
    faceExep();
    accessories_father();
    glPopMatrix();

    glutPostRedisplay();
    glutSwapBuffers();
}
//--------------------------------------------------
void scene10() {
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
    glEnable(GL_BLEND);

    sun1();
    glPushMatrix();
    glTranslatef(-0.635, 0.4, 0.0);
    sunface();
    glPopMatrix();

    floor1();

    glPushMatrix();
    glTranslatef(0.1, -0.4, 0.0);
    glScalef(0.25, 0.25, 1.0);
    treeFarest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, -0.5, 0.0);
    glScalef(-0.2, 0.2, 1.0);
    treeFarest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, -0.4, 0.0);
    glScalef(-0.35, 0.35, 1.0);
    treeFarest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4, -0.4, 0.0);
    glScalef(0.2, 0.2, 1.0);
    glPushMatrix();
    glTranslatef(-0.3, -0.65, 0.0);
    glScalef(0.3, 0.3, 1.0);
    treeFarest();
    glPopMatrix();

    glTranslatef(-3.0, -0.65, 0.0);
    glScalef(-0.3, 0.3, 1.0);
    treeFarest();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.28, -0.5, 0.0);
    glScalef(-0.2, 0.2, 1.0);
    treeFarest();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.7, -0.4, 0.0);
    glScalef(0.28, 0.28, 1.0);
    treeFarest();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.1, -0.2, 0.0);
    glScalef(0.6, 0.6, 1.0);
    treeFar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, -0.25, 0.0);
    glScalef(-0.6, 0.6, 1.0);
    treeFar();
    glPopMatrix();


    Tree();
    leaves2();

    glPushMatrix();
    glTranslatef(1.2, -1.2, 0.0);
    glRotatef(145.0, 0.0, 0.0, 1.0);
    sapling();
    glPopMatrix();

    chat();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.2, -0.4, 0.0);
    glRotatef(45.0, 0.0, 0.0, 1.0);
    glScalef(0.5, 0.5, 1.0);
    owl();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, -0.65, 0.0);
    glScalef(0.5, 0.5, 1.0);
    Rabbit();
    faceExep();
    accessories_father();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75, -0.75, 0.0);
    glScalef(0.3, 0.3, 1.0);
    Kimo();
    KemoFace();
    glPopMatrix();

    glutPostRedisplay();
    // glFlush();
    glutSwapBuffers();
}
//--------------------------------------------------
void scene11() {
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
    glEnable(GL_BLEND);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (txt <= 1.0 & txt3 > -0.9) {
        txt -= 0.0013;//0.000025
    }
    glPushMatrix();
    glTranslatef(txt, -0.999, 0.0);
    leaves();
    glPopMatrix();
    if (txs <= 1.0 & txt3 > -0.9) {
        txs -= 0.0013;//0.000025
        txsf -= 0.0013;//0.000025
    }
    glPushMatrix();
    glTranslatef(txs, 0.0, 0.0);
    sun2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(txsf, 0.4, 0.0);
    sunface();
    glPopMatrix();

    if (txt2 <= 1.0 & txt3 > -0.9) {
        txt2 -= 0.0013;//0.000025
    }
    glPushMatrix();
    glTranslatef(txt2, -0.999, 0.0);
    leaves();
    glPopMatrix();
    if (txt3 <= 1.0 & txt3 > -0.9) {
        txt3 -= 0.0013;//0.000025
    }
    glPushMatrix();
    glTranslatef(txt3, -0.999, 0.0);
    leaves();
    glPopMatrix();
    if (txt4 <= 1.0 & txt3 > -0.9) {
        txt4 -= 0.0013;//0.000025
    }
    glPushMatrix();
    glTranslatef(txt4, -0.999, 0.0);
    leaves();
    glPopMatrix();
    if (txt5 <= 1.0 & txt3 > -0.9) {
        txt5 -= 0.0013;//0.000025
    }
    glPushMatrix();
    glTranslatef(txt5, 0.0, 0.0);
    cloudL();
    glPopMatrix();
    if (txo <= 1.4) {
        txo += 0.006;//0.00015
    }
    glPushMatrix();
    glTranslatef(txo, -0.5, 0.0);
    glRotatef(-45, 0.0, 0.0, 1.0);
    glScalef(0.6, 0.6, 1.0);
    owl();
    glPopMatrix();
    glutPostRedisplay();

    glFlush();
    glutSwapBuffers();
}
//--------------------------------------------------
void scene12() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //The sky
    glColor4f(0.6, 0.9, 1.0, 1.0);
    glRectd(-1.0, -0.4, 1.0, 1.0);

    //THE Grass
    glColor3f(0.0f, 0.5f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, -0.4);
    glVertex2f(-1.0, -0.4);
    glEnd();

    //sun
    glPushMatrix();
    glTranslatef(0.6, 0.58, 0.0);
    sunR();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.53, 0.0, 0.0);
    glScalef(0.7, 0.7, 1.0);
    cloudM();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.6, 0.0);
    glScalef(-1.2, 1.2, 1.0);
    TreeWood();
    leaves();
    glPopMatrix();


    if (Mxpos <= 2.5) {
        Mxpos += 0.0080;//0.0007

    }
    else {
        Mxpos = Mxpos - 2.5;
    }


    if (Fpos <= 1.0) {
        Fpos += 0.0029;//0.00019
    }


    if (Opos <= 0.6) {
        Opos += 0.0029;//0.00019
    }

    glPushMatrix();
    glTranslatef(-1.1, 0.25, 0.0);
    glTranslatef(Opos, 0.0, 0.0);
    glRotatef(-40.0, 0.0, 0.0, 1.0);
    glScalef(0.5, 0.5, 1.0);
    owl();
    glPopMatrix();

    glPushMatrix();
    glLineWidth(1.0);
    glTranslatef(0.7, -0.6, 0.0);
    glScalef(0.5, 0.5, 1.0);
    glTranslatef(-Fpos, 0.0, 0.0);
    Kemo_Father();
    FatherFootL();
    FatherFootR();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -0.8, 0.0);
    glScalef(0.5, 0.5, 1.0);
    glTranslatef(Fpos, 0.0, 0.0);
    Kemo_Mother();
    MotherFootL();
    MotherFootR();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 1.0);
    glTranslatef(0.0, -0.5, 0.0);
    Kemo_Brother();
    glPopMatrix();


    glPushMatrix();
    glScalef(0.5, 0.5, 1.0);
    glTranslatef(-0.4, -0.5, 0.0);
    Kemo_sister2();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 1.0);
    glTranslatef(-0.8, -0.5, 0.0);
    Kemo_sister1();
    glPopMatrix();

    //   glFlush();
    glutPostRedisplay();
    glutSwapBuffers();


}
//--------------------------------------------------
void scene13(){
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
    glEnable(GL_BLEND);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    

    if (xpos_cloud_s13 <= 2) {
        xpos_cloud_s13 += 0.002;
        std::cout << "xpos_cloud_s13..." << xpos_cloud_s13;
    } else {
        xpos_cloud_s13 = -1;
    }
    //------------
    if (angleValue_s13 <= 90) {
        angleValue_s13 += 0.7;
        std::cout << "angleValue_s13..." << angleValue_s13;
    } else {
        angleValue_s13 = 0;
    }
    //------------------------
    //the sky
    glBegin(GL_QUADS);
    glColor3f(0.8784f, 0.9490f, 0.9803f);
    glVertex2f(-1.0f, .2f);
    glVertex2f(1.0f, 0.2f);

    glColor3f(0.6588f, 0.8392f, 0.9058f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
    
    glBegin(GL_QUADS);
        //green-floor
    glColor3f(0.3f, 0.6f, 0.2f);
        glVertex2f(1.0f, 0.5f);
        glVertex2f(-1.0f, 0.5f);
    glColor3f(0.5f, 0.8f, 0.4f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        
        //yellow-floor
    glColor3f(0.7f, 0.6f, 0.3f);
        glVertex2f(0.6f, 0.5f);
        glVertex2f(0.5f, 0.5f);
    glColor3f(1.0f, 0.9f, 0.5f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(0.1f, -1.0f);
    glEnd();
    //------------------------
    glPushMatrix();
        glTranslatef(0.8, 0.8, 0);
        glScalef(0.55, 0.55, 1);
    sunR();
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(xpos_cloud_s13, 0.60, 0);
        glScalef(0.25, 0.25, 1);
    cloudM();
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(xpos_cloud_s13+0.5, 0.75, 0);
        glScalef(0.25, 0.25, 1);
    cloudM();
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(xpos_cloud_s13+1, 0.55, 0);
        glScalef(0.25, 0.25, 1);
    cloudM();
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(xpos_cloud_s13+1.5, 0.65, 0);
        glScalef(0.25, 0.25, 1);
    cloudM();
    glPopMatrix();
    //------------------------
    glColor3f(0.6745f, 0.5490f, 0.4235f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, woodTexture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBegin(GL_QUADS);
            glTexCoord2f(0.5, 0.5);
            glVertex2f(-0.75f, 1.0f);
            glTexCoord2f(0.0, 0.5);
            glVertex2f(-1.0f, 1.0f);
            glTexCoord2f(0.0, 0.0);
            glVertex2f(-2.0f, -2.0f);
            glTexCoord2f(0.5, 0.0);
            glVertex2f(-0.75f, -2.0f);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    //------------------------
    glPushMatrix();
        glTranslatef(0.5, 0.6, 0.0);
        glScalef(0.4, 0.4, 1.0);
    drawCave2();
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(0.63, 0.4, 0.0);
        glScalef(0.35, 0.25, 1.0);
    Kemo_Brother();
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(0.43, 0.4, 0.0);
        glScalef(0.35, 0.25, 1.0);
    Kemo_sister1();
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(0.23, 0.4, 0.0);
        glScalef(0.35, 0.25, 1.0);
    Kemo_sister2();
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(0.53, 0.25, 0.0);
        glScalef(0.35, 0.25, 1.0);
    FatherFootL();
    FatherFootR();
    Kemo_Father();
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(0.33, 0.25, 0.0);
        glScalef(0.35, 0.25, 1.0);
    MotherFootL();
    MotherFootR();
    Kemo_Mother();
    glPopMatrix();
    //------------------------
    multipleCorn_scene13();
    //------------------------
    //[ test rotation ]
    //glColor3f(0.5, 0, 1.0);
    //drawFilledCircle(0.25, -0.25, 0.035);
    //------------------------
    glPushMatrix();
        glTranslatef(0.215-0.5, -0.585, 0.0);
        glRotatef(angleValue_s13, 0.0, 0.0, 1.0);
        glTranslatef(-0.215+0.5, 0.585, 0.0);
        glTranslatef(-0.5, 0.0, 0.0);
        glScalef(1.5, 1.5, 1.0);
    
    KemoHands_RIGHT_ARM();//(0.215, -0.585);
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(0.215-0.5, -0.585, 0.0);
        glRotatef(angleValue_s13, 0.0, 0.0, 1.0);
        glTranslatef(-0.215+0.5, 0.585, 0.0);
        glTranslatef(-0.5, 0.0, 0.0);
        glScalef(1.5, 1.5, 1.0);
    
    KemoHands_RIGHT_HAND();//(0.215, -0.585);
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(-0.215-0.5, -0.585, 0.0);
        glRotatef(angleValue_s13, 0.0, 0.0, -1.0);
        glTranslatef(0.215+0.5, 0.585, 0.0);
        glTranslatef(-0.5, 0.0, 0.0);
        glScalef(1.5, 1.5, 1.0);
    
    KemoHands_LEFT_ARM();//(-0.215, -0.585);
    glPopMatrix();
    //------------------------
    glPushMatrix();
        glTranslatef(-0.215-0.5, -0.585, 0.0);
        glRotatef(angleValue_s13, 0.0, 0.0, -1.0);
        glTranslatef(0.215+0.5, 0.585, 0.0);
        glTranslatef(-0.5, 0.0, 0.0);
        glScalef(1.5, 1.5, 1.0);

    KemoHands_LEFT_HAND();//(-0.215, -0.585);
    glPopMatrix();
    //------------
    glPushMatrix();
        glTranslatef(-0.5, 0.0, 0.0);
        glScalef(1.5, 1.5, 1.0);
    Kimo_from_behind2();
    glPopMatrix();
    //------------
//    glPushMatrix();
//    for (int i = 0; i<10; i++) {
//        glRotatef(i, 0.0, 0.0, 1.0);
//        glColor3f(1, 0, 0);
//        drawFilledCircle(0.25, -0.25, 0.035);
//    }
//    glPopMatrix();
    
//    pointForMe();
//    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}
//--------------------------------------------------
void scene14(){
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
    glEnable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //ZOOM_IN
    gluOrtho2D(-orthoValue_s14, orthoValue_s14, 
               -orthoValue_s14, orthoValue_s14);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if (xpos_cloud_s14 == 2) {
        xpos_cloud_s14 = -0.5;
    }
    if (xpos_cloud_s14 <= 2) {
        xpos_cloud_s14 += 0.001;
        std::cout << "xpos_cloud_s14..." << xpos_cloud_s14;
    } else {
        xpos_cloud_s14 = -1;
    }
    //------------
    if (orthoValue_s14 >= 0.1) {
        orthoValue_s14 -= 0.001;
        std::cout << "orthoValue..." << orthoValue_s14;
    }
    //------------
    if (alphaValue_s14 <= 1.0) {
        alphaValue_s14 += 0.01;
        std::cout << "alphaValue_s14..." << alphaValue_s14;
    } else {
        alphaValue_s14 = 1;
    }
    //-----------------------------------------------------------------------------
    //the sky
//    glBegin(GL_QUADS);
//    glColor3f(0.8784f, 0.9490f, 0.9803f);
//    glVertex2f(-1.0f, 0.2f);
//    glVertex2f(1.0f, 0.2f);
//
//    glColor3f(0.6588f, 0.8392f, 0.9058f);
//    glVertex2f(1.0f, 1.0f);
//    glVertex2f(-1.0f, 1.0f);
//    glEnd();
    
    glBegin(GL_QUADS);
    
    //floor-green
    glColor3f(0.3f, 0.6f, 0.2f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glColor3f(0.5f, 0.8f, 0.4f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    
    //floor-yellow
    glColor3f(0.6f, 0.5f, 0.4f);
    glVertex2f(0.35f, -0.3f);
    glVertex2f(-0.2f, -0.3f);
    glColor3f(1.0f, 0.9f, 0.5f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(0.2f, -1.0f);
    
    glEnd();
    //-----------------------------------------------------------------------------
    glPushMatrix();
        glTranslatef(0.7, 0.7, 0);
        glScalef(1, 1, 1);
    sunR();
    glPopMatrix();
    //-------------
    glPushMatrix();
        glTranslatef(xpos_cloud_s14, 0.2, 0);
        glScalef(0.5, 0.5, 1);
    cloudM();
    glPopMatrix();
    //-------------
    glPushMatrix();
        glTranslatef(xpos_cloud_s14+0.5, 0.35, 0);
        glScalef(0.5, 0.5, 1);
    cloudM();
    glPopMatrix();
    //-------------
    glPushMatrix();
        glTranslatef(0.2, 0.1, 0.0);
    drawCave2();
    glPopMatrix();
    //-------------
    multipleCorn_scene14();
    //-------------
    glPushMatrix();
        glTranslatef(0.25, -0.3, 0);
        glScalef(0.6, 0.6, 1);
    Kemo_Brother();
    glPopMatrix();
    //-------------
    glPushMatrix();
        glTranslatef(-0.3, -0.3, 0);
        glScalef(0.6, 0.6, 1);
    Kemo_sister1();
    glPopMatrix();
    //-------------
    glPushMatrix();
        glTranslatef(-0.55, -0.38, 0);
    MotherFootL();
    MotherFootR();
    Kemo_Mother();
    glPopMatrix();
    //-------------
    glPushMatrix();
        glTranslatef(0.45, -0.38, 0);
    FatherFootL();
    FatherFootR();
    Kemo_Father();
    glPopMatrix();
    //-------------
    glPushMatrix();
        glTranslatef(0.0, -0.1, 0);
    Kimo();
    KemoFace();
    glPopMatrix();
    //-------------
    //black background
    glBegin(GL_QUADS);
    glColor4f(0.0, 0.0, 0.0, alphaValue_s14);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glEnd();
    //-------------
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}
//----------------------------------------------------------------------------
void display2() {
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(boxX - boxSizex / 2, boxY - boxSizey / 2, boxX + boxSizex / 2, boxY + boxSizey / 2);
    glRectf(boxX - boxSizex / 2, boxY2 - boxSizey / 2, boxX + boxSizex / 2, boxY2 + boxSizey / 2);
    Homepage();
    glutSwapBuffers();
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);


    switch (currentShape) {
    case 0:
        Scene1();
        break;
    case 1:
        Scene2();
        break;
    case 2:
        scene3();
        break;
    case 3:
        scene4();
        break;
    case 4:
        scene5();
        break;
    case 5:
        scene6();
        break;
    case 6:
        Scene7();
        break;
    case 7:
        Scene8();
        break;
    case 8:
        Scene9();
        break;
    case 9:
        scene10();
        break;
    case 10:
        scene11();
        break;
    case 11:
        scene12();
        break;
    case 12:
        scene13();
        break;
    case 13:
        scene14();
        break;

    }
    glutSwapBuffers();
}

void reshapeFun(GLint newWidth, GLint newHight)
{
    glViewport(0, 0, newWidth, newHight);
    windowWidth = newWidth;
    windowHeight = newHight;
}

void init()
{
    glClearColor(0.6f, 0.9f, 1.0f, 1.0f); // Set background color to White and opaque
    glMatrixMode(GL_PROJECTION);          // set the projection parameters
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    //------- Texture ---------
    woodTexture = LoadTexture(imagePath, 120, 138);
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Convert screen coordinates to OpenGL coordinates
        float glX = (2.0f * x) / windowWidth - 1.0f;
        float glY = 1.0f - (2.0f * y) / windowHeight;


        // Check if the cursor is within the box's boundaries
        if (glX >= boxX - boxSizex / 2 && glX <= boxX + boxSizex / 2 &&
            glY >= boxY - boxSizey / 2 && glY <= boxY + boxSizey / 2)
        {
            // Task to execute when the box is clicked
            glutDisplayFunc(display);
            auto currentTime = std::chrono::steady_clock::now();
            timer1 = currentTime + std::chrono::milliseconds(TIMER_INTERVAL);
            glutTimerFunc(TIMER_INTERVAL, timerEvent1, 0);
            // Start  animation timer

        }
        if (glX >= boxX - boxSizex / 2 && glX <= boxX + boxSizex / 2 &&
            glY >= boxY2 - boxSizey / 2 && glY <= boxY2 + boxSizey / 2)
        {
            // Task to execute when the box is clicked
           // std::cout << "at (" << glX << ", " << glY << ")" << std::endl;
            fprintf(stderr, "\n------------------"
                "\n|STORY CHARACTERS|\n"
                "------------------\n"
                "KEMO'S FAMILY:\n"
                "KEMO'S MOM\n"
                "KEMO'S FATHER\n"
                "KEMO'S SISTERS\n"
                "KEMO'S BROTHER\n"
                "\nTHE RABBETS FAMILY:\n"
                "RABBIT'S MOM\n"
                "RABBIT'S FATHER\n"
                "BABY RABBIT\n"
                "GIRL RABBET\n"
                "BOY RABBIT\n"
                "\nTHE OWL\n"
                "------------------\n"
                "\t\t\t---------------\t\t\t"
                "\n\t\t\t|THE LOST KEMO|\t\t\t\n"
                "\t\t\t---------------\n\n"
                "IN THE MIDDLE OF ONE OF THE  CORNFIELDS, KEMO LIVES WITH HIS"
                "\nPARENTS AND SIBLINGS IN A BIG HOLE THAT EXTENDS UNDERGROUND."
                "\nKEMO LOVES TO PLAY A LOT IN THE CORNFIELDS AND THE FOREST.\n"
                "\nONE DAY HE ASKED HIS MOM TO GO OUTSIDE TO PLAY IN THE CORNFIELDS."
                "\nHIS MOM AGREES ON THE CONDITION THAT HE RETURNED BEFORE THE SUN SET."
                "\nSO HE WENT OUT HAPPILY, THEN HE TALKED TO HIMSELF AND"
                "\nSAID : I AM GOING TO WALK A LITTLE BIT IN THE FOREST AND THEN GO BACK"
                "\nHOME BEFORE DARK COMES.\n"
                "\nHE ENTERED THE FOREST AND STARTED MOVING AROUND THE TREES, THEN HE FOUND"
                "\nON THE GROUND A BIG WALNUT.HE WAS PLAYING WITH IT WITH HIS FEET UNTIL"
                "\nHE ENTERED THE HEART OF THE FOREST.\n"
                "\nKEMO STOPPED SUDDENLY IN HIS PLACE AND RECOGNIZED THAT THE SUN HAD GONE DOWN"
                "\nAND THE DARK STARTED.HE REMEMBERED HIS MOM'S"
                "\nWORDS THAT HE SHOULD NOT BE LATE AND RETURNED HOME."
                "\nAT THAT TIME, HE TURNED AND STARTED RUNNING IN THE FOREST.\n"
                "\nHE RAN FOR TOO LONG BUT HE DIDN’T REACH TO THE CORNFIELDS"
                "\nWHERE HE LIVES, SO HE STAYED IN THE FOREST BETWEEN THE TREES."
                "\nHE TURNED TO THE RIGHT SIDE AND STARTED RUNNING AND RUNNING"
                "\nUNTIL THE DARKNESS OF THE NIGHT INCREASED AND HE GOT EXHAUSTED.\n"
                "\nKEMO STARTED CRYING. HE WAS SCARED OF GETTING EATEN BY ONE OF"
                "\nTHE FOXES, SO HE DECIDED TO HIDE IN THE NEAREST HOLE HE REACHED,"
                "\nSO HE WALKED A FEW STEPS AND HE FOUND A SMALL HOLE AND ENTERED"
                "\nIT AND SLEPT BESIDE A SMALL ANIMAL.\n"
                "\nTHE SUN ROSE AND ALL THE ANIMALS GOT UP."
                "\nINCLUDING THE RABBIT'S FAMILY THAT LIVES IN THE HOLE  WHERE KEMO ENTERED.\n"
                "\nTHE RABBIT'S MOM WAS SURPRISED. SHE HAS 3 CHILDREN. WHO IS THAT ANIMAL"
                "\nSLEEPING BESIDE THEM? THE RABBITS WERE SURPRISED."
                "\nTHEIR FUR IS WHITE BUT HIS IS PURPLE, THE RABBITS' EARS ARE BIG BUT HIS IS SMALL.\n"
                "\nTHE RABBIT'S FATHER CAME WITH SOME CARROTS AND SAW THE SMALL PURPLE ANIMAL BETWEEN"
                "\nHIS CHILDREN, SO HE SAID: LOOKS LIKE HE HAD LOST HIS WAY HOME IN THE DARK,"
                "\nSO HE ENTERED OUR HOME AND SLEPT WITH US.\n"
                "\nTHE RABBIT'S FATHER AND KEMO WENT TO A BIG TREE WHERE THE OWL LIVES."
                "\nTHE RABBIT'S FATHER SAID TO THE OWL : GOOD MORNING OWL, I HAVE A PROBLEM."
                "\nCOULD YOU PLEASE HELP ME SOLVE IT?\n"
                "\nTHE OWL SAID:GO AHEAD RABBIT."
                "\nTHE RABBIT : LAST NIGHT THIS SMALL ANIMAL CAME TO US AND WE DIDN’T KNOW"
                "\nWHERE HIS HOME WAS, SO WE COULD RETURN HIM TO IT."
                "\nTHE OWL : DON’T WORRY RABBIT.I WILL LOOK FOR HIS HOME"
                "\nAND FAMILY.WAIT FOR ME HERE.I WILL COME BACK SOON.\n"
                "\nTHE OWL FLEW ABOVE THE FIELDS THAT ARE NEAR THE FOREST"
                "\nAND HE EXAMINED IT WITH A KEEN EYE, BUT HE GOT CONFUSED BECAUSE OF"
                "\nTHE NUMBER OF HOLES IN THE FOREST. THEN HE RECOGNIZED FROM FARAWAY"
                "\nA GROUP OF PURPLE ANIMALS THAT HAD GATHERED IN ONE PLACE."
                "\nHE WENT TO THEM AND ASKED THEM ABOUT THE CAUSE OF THE GATHERING."
                "\nTHEY TOLD HIM THAT ONE OF THE FAMILY MEMBERS GOT LOST IN THE FOREST."
                "\nTHE OWL KNEW THAT THEY WERE KEMO’S FAMILY AND HE BROUGHT KEMO BACK"
                "\nTO HIS FAMILY . FINALLY, KEMO CAME BACK HOME.\n"
                "\nWHEN HIS MOTHER SAW HIM, SHE RAN AND HUGGED HIM AND"
                "\nSAID : WE WERE WORRIED ABOUT YOU."
                "\nDIDN’T I TELL  NOT TO BE LATE, AND COME BEFORE THE SUN SET ?\n"
                "\nKEMO APOLOGIZED TO HIS MOM AND FAMILY AND PROMISED THEM"
                "\nNOT TO GO TO THE FOREST BY HIMSELF AND  COME BACK HOME LATE EVER.\n");

        }

    }

}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("");
    init();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutTimerFunc(40, updateAngle, 0);
    glutReshapeFunc(reshapeFun);
    
    glutMouseFunc(mouse);
    glutDisplayFunc(display2);
    
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
