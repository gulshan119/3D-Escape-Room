#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include<bits/stdc++.h>
#include <cmath>
using namespace std;

GLboolean zoomed=false, zoomed_t = false, zoomed_d=false, switchOne = false, switchTwo=false, switchLamp=false, amb1=true, diff1=true, spec1=true, amb2=true, diff2=true, spec2=true, amb3=true, diff3=true, spec3=true,zoomed_b=false,zoomed_drawer=false;
double windowHeight=800, windowWidth=600;
double eyeX=7.0, eyeY=2.0, eyeZ=15.0, refX = 0, refY=0,refZ=0;
double l_x=1.6, l_z=10 ,locker_x=0.01, locker_y=1, locker_z=0.4;
double knob_x=1.6,knob_y=0.5,knob_z=10.05;

bool lockerDoorOpen = false;


// Global variables to store the scale factor
GLfloat torusScale = 10.0; // Initial scale factor
GLfloat orig_torus_x=1.4, orig_torus_y=0.97,orig_torus_z=10.2;
GLfloat torus_x=orig_torus_x,torus_y=orig_torus_y,torus_z=orig_torus_z;



// Global variables to store the scale factor
GLfloat ballScale = 1.0; // Initial scale factor
GLfloat orig_ball_x=1.4, orig_ball_y=0.68,orig_ball_z=10;
GLfloat ball_x=orig_ball_x, ball_y=orig_ball_y, ball_z=orig_ball_z;



// Global variables to store the scale factor
GLfloat dS_x = 0.038,dS_y=0.025,dS_yn=-0.025, dS_z=0.05; // Initial scale factor
GLfloat diamondScale=1;
GLfloat orig_diamond_x=1.4, orig_diamond_y=1.3,orig_diamond_z=10;
GLfloat diamond_x=orig_diamond_x, diamond_y=orig_diamond_y, diamond_z=orig_diamond_z;




// Global variables to store the scale factor
GLfloat bS_x = 0.03,bS_y=0.15, bS_z=0.1; // Initial scale factor
GLfloat r=15;
GLfloat bookScale=1;
GLfloat orig_book_x=1.28, orig_book_y=1.97,orig_book_z=1.2;
GLfloat book_x=orig_book_x, book_y=orig_book_y, book_z=orig_book_z;

// Global variables
GLfloat drawerScale=1;
GLfloat drawer_x=-0.72,drawer_y=-0.09,orig_drawerbase_z=1.16,orig_drawer_z=1.6;
GLfloat drawerbase_z=orig_drawerbase_z, drawer_z=orig_drawer_z;


static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};



static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    
    glutSolidSphere (3.0, 20, 16);
}


void drawCube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    glBegin(GL_QUADS);
    
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}



static GLfloat v_trapezoid[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.5, 3.0, 0.5}, //4
    {0.5, 3.0, 2.5}, //5
    {2.5, 3.0, 2.5}, //6
    {2.5, 3.0, 0.5}  //7
};

static GLubyte TquadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};

void drawTrapezoid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_emission[] = {difX, difY, difZ, 0.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    
    if(switchLamp==true){
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    } else {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_trapezoid[TquadIndices[i][0]][0], v_trapezoid[TquadIndices[i][0]][1], v_trapezoid[TquadIndices[i][0]][2],
        v_trapezoid[TquadIndices[i][1]][0], v_trapezoid[TquadIndices[i][1]][1], v_trapezoid[TquadIndices[i][1]][2],
        v_trapezoid[TquadIndices[i][2]][0], v_trapezoid[TquadIndices[i][2]][1], v_trapezoid[TquadIndices[i][2]][2]);
        
        glVertex3fv(&v_trapezoid[TquadIndices[i][0]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][1]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][2]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][3]][0]);
    }
    glEnd();
}


//Drawing pyramid *
static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte PquadIndices[1][4] =
{
    {0, 3, 2, 1}
};


void drawpyramid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        getNormal3p(v_pyramid[PquadIndices[i][0]][0], v_pyramid[PquadIndices[i][0]][1], v_pyramid[PquadIndices[i][0]][2],
                    v_pyramid[PquadIndices[i][1]][0], v_pyramid[PquadIndices[i][1]][1], v_pyramid[PquadIndices[i][1]][2],
                    v_pyramid[PquadIndices[i][2]][0], v_pyramid[PquadIndices[i][2]][1], v_pyramid[PquadIndices[i][2]][2]);
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}

void lamp() {
    // Lamp base
    glPushMatrix();
    glTranslatef(0.6, 0.5, 4.95);
    glScalef(0.07, 0.02, 0.07);
    drawCube1(0, 0, 1, 0, 0, 0.5);
    glPopMatrix();


    // Lamp Desk
    glPushMatrix();
    glTranslatef(0.6, 0.35, 4.9);
    glScalef(0.1, 0.1, 0.1);
    drawCube1(0.545, 0.271, 0.075, 0.5, 0.0, 0.0);
    glPopMatrix();

    // Lamp stand
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(0.7, 0.35, 5.05);
    glScalef(0.01, 0.2, 0.01);
    drawCube1(1, 0, 0, 0.5, 0.0, 0.0);
    glPopMatrix();

    // Lamp shade
    glColor3f(0.000, 0.000, 0.545);
    glPushMatrix();
    glTranslatef(0.6, 0.9, 4.95);
    glScalef(0.08, 0.09, 0.08);
    drawTrapezoid(0.000, 0.000, 0.545, 0, 0, 0.2725);
    glPopMatrix();
}


void lampLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT2);

    glPushMatrix();
    GLfloat no_light[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_ambient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    
    // Adjust light position to be near the lamp
    GLfloat light_position[] = {0.6, 0.9, 4.9, 1.0}; // Adjust the position as needed

    if (amb3 == true) { glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient); }
    else { glLightfv(GL_LIGHT2, GL_AMBIENT, no_light); }

    if (diff3 == true) { glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse); }
    else { glLightfv(GL_LIGHT2, GL_DIFFUSE, no_light); }

    if (spec3 == true) { glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular); }
    else { glLightfv(GL_LIGHT2, GL_SPECULAR, no_light); }

    glLightfv(GL_LIGHT2, GL_POSITION, light_position);
    
    // Set attenuation to simulate the light spreading evenly in all directions
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.1);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.01);
    
    glPopMatrix();
}




void window()
{
    //Window **
    //window white open
    glPushMatrix();
    glTranslatef(3,1,1); //0.5,1,9.6
    glScalef(0.6, 0.6, 0.001);
   drawCube1(0.0, 0.0, 0.3, 0.1, 0.1, 0.2);//0.0, 0.0, 0.3, 0.1, 0.1, 0.2
    glPopMatrix();
        
    //window right side corner
    glPushMatrix();
    glTranslatef(4.8,1,1);
    glScalef(0.04, 0.6, 0.001);
    drawCube1(0.545, 0.271, 0.075, 0.05, 0.05, 0.05); 
    glPopMatrix();
    
    //window left side corner
    glPushMatrix();
    glTranslatef(2.9,1,1);
    glScalef(0.04, 0.6, 0.001);
    drawCube1(0.545, 0.271, 0.075, 0.05, 0.05, 0.05); 
    glPopMatrix();
        
    //window upper side corner
    glPushMatrix();
    glTranslatef(3,1,1);
    glScalef(0.6, 0.05, 0.01);
    drawCube1(0.7,0.6,0.5,  0.35,0.3,0.25);
    glPopMatrix();
        
        
    //window lower side corner
    glPushMatrix();
    glTranslatef(3,2.8,1);
    glScalef(0.6, 0.05, 0.01);
    drawCube1(0.7,0.6,0.5,  0.35,0.3,0.25);
    glPopMatrix();
        
        
        //window vertical bar 1
        glPushMatrix();
        glTranslatef(3.4,1,1.3);
        glScalef(0.02, 0.6, 0.002);
        drawCube1(0.0,0.0,0.0, 0.0,0.0,0.0, 5);
        glPopMatrix();
        
        //window vertical bar 2
        glPushMatrix();
        glTranslatef(4.2,1,1.3);
        glScalef(0.02, 0.6, 0.002);
        drawCube1(0.0,0.0,0.0, 0.0,0.0,0.0, 5);
        glPopMatrix();
        
        //window horizontal bar
        glPushMatrix();
        glTranslatef(3,1.5,1.3);
        glScalef(0.6, 0.02, 0.01);
        drawCube1(0.0,0.0,0.0, 0.0,0.0,0.0, 5);
        glPopMatrix();
      

        //window horizontal bar
        glPushMatrix();
        glTranslatef(3,2.1,1.3);
        glScalef(0.6, 0.02, 0.01);
        drawCube1(0.0,0.0,0.0, 0.0,0.0,0.0, 5);
        glPopMatrix();
        
        
    // Draw mountains
    glPushMatrix();
    glTranslatef(3.3, 1.1, 1.2);
    glScalef(0.38, 0.31, 0.001); // Position the second mountain at the bottom
    //glRotatef(30, 0, 0, 1); // Rotate the mountain to give a different perspective
    drawpyramid(0.0, 0.5, 0.0, 0.0, 0.3, 0.0, 90.0); // Adjust colors and shine as needed
    glPopMatrix();
    
    //right mountain
    glPushMatrix();
    glTranslatef(3.8, 1.1, 1.2);
    glScalef(0.4, 0.25, 0.001); // Position the mountain at the bottom
    drawpyramid(0.0, 0.5, 0.0, 0.0, 0.3, 0.0, 90.0);// Adjust colors and shine as needed
    glPopMatrix();

    // Draw sun
    glPushMatrix();
    glTranslatef(4.5, 2.5, 1.2);
    glScalef(0.08, 0.08, 0.001);  // Position the sun at the top
    drawSphere(1.0, 0.8, 0.0, 1.0, 0.8, 0.0); // Yellow sun
    glPopMatrix();
    
    //draw cloud
    
     glTranslatef(3.2, 2.35, 1.2);
    glScalef(0.05, 0.05, 0.001);  
    drawSphere(0.1, 0.3, 0.8, 0.3, 0.5, 0.9); 
    glPopMatrix();    
    
    glPushMatrix();
    glTranslatef(3.3, 2.5, 1.2);
    glScalef(0.05, 0.05, 0.001);  
    drawSphere(0.1, 0.3, 0.8, 0.3, 0.5, 0.9); 
    glPopMatrix();
    
    glPushMatrix();
     glTranslatef(3.3, 2.26, 1.2);
    glScalef(0.05, 0.05, 0.001);  
    drawSphere(0.1, 0.3, 0.8, 0.3, 0.5, 0.9); 
    glPopMatrix();
    
    glPushMatrix();
     glTranslatef(3.5, 2.5, 1.2);
    glScalef(0.05, 0.05, 0.001); 
    drawSphere(0.1, 0.3, 0.8, 0.3, 0.5, 0.9); 
    glPopMatrix();
    
    glPushMatrix();    
     glTranslatef(3.5, 2.26, 1.2);
    glScalef(0.05, 0.05, 0.001);  
    drawSphere(00.1, 0.3, 0.8, 0.3, 0.5, 0.9); 
    glPopMatrix();
    
     glPushMatrix();    
     glTranslatef(3.6, 2.35, 1.2);
    glScalef(0.05, 0.05, 0.001);  
    drawSphere(0.1, 0.3, 0.8, 0.3, 0.5, 0.7); 
    glPopMatrix();    
        
        
        
        
        
}



void room()
{
    // carpet
    glPushMatrix();
    glTranslatef(3,-0.2,7);
    glScalef(1.3, 0.01, 1.7);
    drawCube1(0.2, 0.2, 0.2, 0.3, 0.3, 0.3);
    glPopMatrix();
    
    // right wall
    glPushMatrix();
    glTranslatef(-1.5,-1,.5);
    glScalef(5, 2, 0.1);
    drawCube1(0.4, 0.25, 0.15, 0.35, 0.2, 0.1); // Dark Wood
    glPopMatrix();
    
    // left wall
    glPushMatrix();
    glTranslatef(-4.5,-1,0);
    glScalef(1, 2, 5);
    drawCube1(0.4, 0.25, 0.15, 0.35, 0.2, 0.1); // Dark Wood
    glPopMatrix();
    
    // wall besides the right wall
    glPushMatrix();
    glTranslatef(8,-1,0);
    glScalef(0.2, 2, 5);
    drawCube1(0.4, 0.25, 0.15, 0.35, 0.2, 0.1); // Dark Wood
    glPopMatrix();
    
    //ceiling
    glPushMatrix();
    glTranslatef(-2,5.1,0);
    glScalef(5, 0.1, 7);
    drawCube1(1.0, 1.0, 0.0,  0.5,0.45,0.4); // Yellow
    glPopMatrix();
    
    // floor
    glPushMatrix();
    glScalef(5, 0.1, 7);
    glTranslatef(-1,-5,0);
    drawCube1(0.3, 0.1, 0.2, 0.2, 0.1, 0.15); // Dark Burgundy
    glPopMatrix();
}

void Drawer()
{
    //drawer *****
      
      //drawer body
      glPushMatrix();
      glTranslatef(-0.8,-0.1,1); //0.5,-0.1,9
      glScalef(0.23, 0.15, 0.2);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();
      
      //drawer's front
      glPushMatrix();
      glTranslatef(-0.72,-0.09,drawer_z);
      glScalef(0.18, 0.1, 0.0011);
      drawCube1(0.3,0.2,0.2, 0.15,0.1,0.1);
      glPopMatrix();


      //drawer's base
      glPushMatrix();
      glTranslatef(-0.72,-0.09,drawerbase_z);
      glScalef(0.18, 0.002, 0.15);
      drawCube1(0.3,0.2,0.2, 0.15,0.1,0.1);
      glPopMatrix();
      
      //drawer's knob
      glPushMatrix();
      glTranslatef(-0.48,0.1,(drawer_z)+0.1);
      glScalef(0.02, 0.02, 0.02);
      drawSphere(0.3, 0.1, 0.0,  0.15,0.05,0.0);
      glPopMatrix();
}

void bed()
{
    //bed headboard
    glPushMatrix();
    glScalef(0.1, 0.5, 0.9);
    glTranslatef(-2,-0.5,6.2);
    drawCube1(0.0, 0.6, 0.6, 0.0, 0.5, 0.5, 50); // Soft Blue
    glPopMatrix();
   
    
    //bed body
    glPushMatrix();
    glScalef(1, 0.2, 0.9);
    glTranslatef(0,-0.5,6.2);
    drawCube1(0.99, 0.85, 0.73, 0.4, 0.45, 0.43, 50); // Gray
    glPopMatrix();
    
    //pillow right far
    glPushMatrix();
    glTranslatef(0.5,0.5,6);
    glRotatef(20, 0,0,1);
    glScalef(0.1, 0.15, 0.28);
    drawCube1(1.0, 0.937, 0.835, 0.5, 0.4685, 0.4175, 50); // Muted Blue
    glPopMatrix();
    
    //pillow left near
    glPushMatrix();
    glTranslatef(0.5,0.5,7.2);
    glRotatef(22, 0,0,1);
    glScalef(0.1, 0.15, 0.28);
    drawCube1(1.0, 0.937, 0.835, 0.5, 0.4685, 0.4175, 50); // Muted Blue
    glPopMatrix();
    
    //blanket
    glPushMatrix();
    glTranslatef(1.4,0.45,5.5);
    glScalef(0.5, 0.05, 0.95);
    drawCube1(0.498, 1.0, 0.831, 0.249, 0.5, 0.4155, 50);
    glPopMatrix();
    
    //blanket side left part
    glPushMatrix();
    glTranslatef(1.4,-0.3,8.16);
    glScalef(0.5, 0.25, 0.05);
    drawCube1(0.498, 1.0, 0.831, 0.249, 0.5, 0.4155, 50);
    glPopMatrix();
}





void bookstack() {
    // Book 1 (Bottom book)
    glColor3f(0.2, 0.5, 0.8); // Blue
    glPushMatrix();
    glTranslatef(7, 1.05, 10); // Position of the bottom book on the table
    glScalef(0.1, 0.04, 0.06); // Dimensions of the book
    drawCube1(0.2, 0.5, 0.8, 0.1, 0.05, 0.05); // Drawing the book
    glPopMatrix();

    // Book 2 (Top book)
    glColor3f(0.2, 0.5, 0.8); // Blue
    glPushMatrix();
    glTranslatef(7, 1.15, 10); // Position of the top book on the table (stacked on top of the bottom book)
    glRotatef(45, 0, 1, 0); // Rotate the top book slightly
    glScalef(0.1, 0.04, 0.06); // Dimensions of the book
    drawCube1(0.2, 0.5, 0.8, 0.1, 0.05, 0.05); // Drawing the book
    glPopMatrix();
}


void lightBulb1()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_ambient_color[] = { 0.6, 0.7, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1.000, 1,1, 0.0};
    
    glPushMatrix();
    glTranslatef (4, 5.15, 8);
    glScalef(0.4, 0.1, 0.4);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
    if(switchOne == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    
   glutSolidCube(3.0);
    glPopMatrix();
}

void lightBulb2()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.2, 0.2, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1,1,1, 1.0};
    
    glPushMatrix();
    glTranslatef (0,5,8);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if(switchTwo == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void lightOne()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 5.0, 5.0, 8.0, 1.0 }; //5 5 10
    
    //glEnable( GL_LIGHT0);
    
    if(amb1 == true){glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);}
    
    if(diff1 == true){glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);}
    
    if(spec1 == true){glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);}
   
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void lightTwo()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 0.5};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 0.9, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 5.0, 8.0, 1.0 };
    
    //glEnable( GL_LIGHT1);
    
    if(amb2 == true){glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);}
    
    if(diff2 == true){glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);}
    
    if(spec2 == true){glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);}
    
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case 'f': // Open/close the locker door
            if(!lockerDoorOpen){
            	locker_x=0.5;
                locker_y=1;
                locker_z=0.01;
                l_x+=0.5;
                l_z-=0.42;
                knob_x=2.3;
                knob_y=0.5;
                knob_z=9.5;
            }
            if(lockerDoorOpen){
            	locker_x=0.01;
                locker_y=1;
                locker_z=0.4;
                l_x-=0.5;
                l_z+=0.42;
                knob_x=1.6;
                knob_y=0.5;
                knob_z=10.05;
            }
            lockerDoorOpen = !lockerDoorOpen; // Toggle lockerDoorOpen variable
            glutPostRedisplay(); // Request redisplay to reflect the change
            break;
        case 'w': // move eye point upwards along Y axis
            eyeY+=1.0;
            break;
        case 's': // move eye point downwards along Y axis
            eyeY-=1.0;
            break;
        case 'a': // move eye point left along X axis
            eyeX-=1.0;
            break;
        case 'd': // move eye point right along X axis
            eyeX+=1.0;
            break;
        case 'o':  //zoom out
            eyeZ+=1;
            break;
        case 'i': //zoom in
            eyeZ-=1;
            break;
        case 'q': //back to default eye point and ref point
                eyeX=7.0; eyeY=2.0; eyeZ=15.0;
                refX=0.0; refY=0.0; refZ=0.0;
            break;
        case 'j': // move ref point upwards along Y axis
            refY+=1.0;
            break;
        case 'n': // move ref point downwards along Y axis
            refY-=1.0;
            break;
        case 'b': // move ref point left along X axis
            refX-=1.0;
            break;
        case 'm': // move eye point right along X axis
            refX+=1.0;
            break;
        case 'k':  //move ref point away from screen/ along z axis
            refZ+=1;
            break;
        case 'l': //move ref point towards screen/ along z axis
            refZ-=1;
            break;
        case '1': //to turn on and off light one
            if(switchOne == false)
            {
                switchOne = true; amb1=true; diff1=true; spec1=true;
                glEnable( GL_LIGHT0); break;
            }
            else if(switchOne == true)
            {
                switchOne = false; amb1=false; diff1=false; spec1=false; glDisable( GL_LIGHT0); break;
            }
        case '2': //to turn on and off light two
            if(switchTwo == false)
            {
                switchTwo = true; amb2=true; diff2=true; spec2=true;
                glEnable( GL_LIGHT1); break;
            }
            else if(switchTwo == true)
            {
                switchTwo = false; amb2=false; diff2=false; spec2=false;
                glDisable( GL_LIGHT1); break;
            }
        case '3': //to turn on and off lamp light
            if(switchLamp == false)
            {
                switchLamp = true; amb3=true; diff3=true; spec3=true;
                glEnable( GL_LIGHT2); break;
            }
            else if(switchLamp == true)
            {
                switchLamp = false; amb3=false; diff3=false; spec3=false;
                glDisable( GL_LIGHT2); break;
            }
        case'4': //turn on/off ambient light 1
            if(amb1 == false) {amb1=true; break;}
            else{amb1=false; break;}
        case'5':
            if(diff1 == false) {diff1=true; break;}
            else{diff1=false; break;}
        case'6':
            if(spec1 == false) {spec1=true; break;}
            else{spec1=false; break;}
        case'7': //turn on/off ambient light 2
            if(amb2 == false) {amb2=true; break;}
            else{amb2=false; break;}
        case'8':
            if(diff2 == false) {diff2=true; break;}
            else{diff2=false; break;}
        case'9':
            if(spec2 == false) {spec2=true; break;}
            else{spec2=false; break;}
        case'e': //turn on/off ambient lamp light
            if(amb3 == false) {amb3=true; break;}
            else{amb3=false; break;}
        case'r':
            if(diff3 == false) {diff3=true; break;}
            else{diff3=false; break;}
        case't':
            if(spec3 == false) {spec3=true; break;}
            else{spec3=false; break;}
        case 27:    // Escape key
            exit(1);
    }
    
    glutPostRedisplay();
}



void fullScreen(int w, int h)
{
    //Prevent a divide by zero, when window is too short;you cant make a window of zero width.
    if (h == 0)
        h = 1;
    float ratio = (GLfloat)w / (GLfloat)h;         //Calculate aspect ratio of the window

    //Set the perspective coordinate system
    glMatrixMode(GL_PROJECTION);                   //Use the Projection Matrix
    glLoadIdentity();                              //Reset Matrix

    glViewport(0, 0, w, h);                        //Set the viewport to be the entire window
    gluPerspective(60, ratio, 1, 500);             //Set the correct perspective.
    //glFrustum(-2.5,2.5,-2.5,2.5, ratio, 200);
    glMatrixMode(GL_MODELVIEW);                    //Get Back to the Modelview
}


void simplecube(float a1,float a2,float a3,float d1,float d2,float d3,float s)
{
	GLfloat ambient[] = {a1,a2,a3}; // Ambient color (RGB)
	GLfloat diffuse[] = {d1,d2,d3}; // Diffuse color (RGB)

	GLfloat shininess = s; // Shininess (0-128)
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glutSolidCube(2); // Drawing the table top
}




void table() {
    // Table Top
    glPushMatrix();
    glTranslatef(7, 1, 10);
    glScalef(0.5, 0.02, 0.5); // Dimensions of the table top
    simplecube(0.524, 0.506, 0.549, 0.512, 0.553, 0.5745, 100); // Drawing the table top
    glPopMatrix();

    // Legs
    glPushMatrix();
    glTranslatef(6.75, 0.5, 9.75); // Position of the first leg
    glScalef(0.02, 0.52, 0.02); // Dimensions of the leg
    simplecube(0.524, 0.506, 0.549, 0.512, 0.553, 0.5745, 100); // Drawing the leg
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.25, 0.5, 9.75); // Position of the second leg
    glScalef(0.02, 0.52, 0.02); // Dimensions of the leg
    simplecube(0.524, 0.506, 0.549, 0.512, 0.553, 0.5745, 100); // Drawing the leg
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.75, 0.5, 10.25); // Position of the third leg
    glScalef(0.02, 0.52, 0.02); // Dimensions of the leg
    simplecube(0.524, 0.506, 0.549, 0.512, 0.553, 0.5745, 100); // Drawing the leg
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.25, 0.5, 10.25); // Position of the fourth leg
    glScalef(0.02, 0.52, 0.02); // Dimensions of the leg
    simplecube(0.524, 0.506, 0.549, 0.512, 0.553, 0.5745, 100); // Drawing the leg
    glPopMatrix();
}


void Teapot() {
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(6.8, 1.1, 10.3);
    glScalef(0.1,0.15,0.1);
    glutSolidTeapot(1.0); // Teapot
    glPopMatrix();
}


void chair() {
    // Chair Seat
    glPushMatrix();
    glTranslatef(6.35, 0.7, 10); // Position of the seat relative to the table
    glScalef(0.25, 0.02, 0.3); // Dimensions of the seat
    simplecube(0.5, 0.3, 0.1, 0.6, 0.4, 0.2, 100); // Drawing the seat
    glPopMatrix();

    // Chair Back
    glPushMatrix();
    glTranslatef(6.1, 1.1, 9.9); // Position of the back relative to the table
    glScalef(0.02, 0.4, 0.3); // Dimensions of the back
    simplecube(0.5, 0.3, 0.1, 0.6, 0.4, 0.2, 100); // Drawing the back
    glPopMatrix();

    // Chair Legs
    glPushMatrix();
    glTranslatef(6.1, 0.35, 9.75); // Position of the first leg relative to the table
    glScalef(0.02, 0.38, 0.02); // Dimensions of the leg
    simplecube(0.5, 0.3, 0.1, 0.6, 0.4, 0.2, 100); // Drawing the leg
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.6, 0.35, 9.75); // Position of the second leg relative to the table
    glScalef(0.02, 0.38, 0.02); // Dimensions of the leg
    simplecube(0.5, 0.3, 0.1, 0.6, 0.4, 0.2, 100); // Drawing the leg
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.1, 0.35, 10.25); // Position of the third leg relative to the table
    glScalef(0.02, 0.38, 0.02); // Dimensions of the leg
    simplecube(0.5, 0.3, 0.1, 0.6, 0.4, 0.2, 100); // Drawing the leg
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.6, 0.35, 10.25); // Position of the fourth leg relative to the table
    glScalef(0.02, 0.38, 0.02); // Dimensions of the leg
    simplecube(0.5, 0.3, 0.1, 0.6, 0.4, 0.2, 100); // Drawing the leg
    glPopMatrix();
}



void door(){
    glPushMatrix();
    glTranslatef(7, 1.5, 1);
    glScalef(0.6, 2, 0.02);    
    simplecube(0.1, 0.1, 0.2, 0.05, 0.05, 0.1, 100); // Dark Blue
    glPopMatrix();
    // door Knob
    glPushMatrix();
    glTranslatef(6.7,1.5,1); 
    glScalef(0.03, 0.03, 0.04); // Dimensions of the knob
    drawSphere(0.1,0.1,0.1,0.5,0.5,0.5,1); // Black sphere
    glPopMatrix();
}




void locker() {
    // Locker Sides
    // Front
    glPushMatrix();
    glTranslatef(l_x, 0.5, l_z); // Position of the locker relative to the bed
    glScalef(locker_x,locker_y,locker_z); // Dimensions of the locker front
    simplecube(0.5, 0.5, 0.5, 0.6, 0.6, 0.6, 100); // Drawing the locker front
    glPopMatrix();

    

    // Back
    glPushMatrix();
    glTranslatef(0.4, 0.5, 10); // Position of the locker relative to the bed
    glScalef(0.01, 1, 0.4); // Dimensions of the locker back
    simplecube(0.5, 0.5, 0.5, 0.6, 0.6, 0.6, 100); // Drawing the locker back
    glPopMatrix();

    // Top
    glPushMatrix();
    glTranslatef(1, 1.5, 10); // Position of the locker relative to the bed
    glScalef(0.6, 0.02, 0.4); // Dimensions of the locker top
    simplecube(0.5, 0.5, 0.5, 0.6, 0.6, 0.6, 100); // Drawing the locker top
    glPopMatrix();

    // Bottom
    glPushMatrix();
    glTranslatef(1, -0.01, 10); // Position of the locker relative to the bed
    glScalef(0.6, 0.02, 0.4); // Dimensions of the locker bottom
    simplecube(0.5, 0.5, 0.5, 0.6, 0.6, 0.6, 100); // Drawing the locker bottom
    glPopMatrix();

    // Left
    glPushMatrix();
    glTranslatef(1, 0.5, 9.6); // Position of the locker relative to the bed
    glScalef(0.6, 1, 0.01); // Dimensions of the locker left side    
    simplecube(0.5, 0.5, 0.5, 0.6, 0.6, 0.6, 100); // Drawing the locker left side
    glPopMatrix();

    // Right
    glPushMatrix();
    glTranslatef(1, 0.5, 10.4); // Position of the locker relative to the bed
    glScalef(0.6, 1, 0.01); // Dimensions of the locker right side
    simplecube(0.5, 0.5, 0.5, 0.6, 0.6, 0.6, 100); // Drawing the locker right side
    glPopMatrix();

    // Locker Knob
    glPushMatrix();
    glTranslatef(knob_x,knob_y,knob_z); // Position of the knob relative to the locker
    glScalef(0.02, 0.02, 0.02); // Dimensions of the knob
    drawSphere(1, 1, 1, 0, 0, 0); // Black sphere
    glPopMatrix();


    // rack1
    glPushMatrix();
    glTranslatef(1, 1.2, 10); // Position of the locker relative to the bed
    glScalef(0.6, 0.02, 0.4); // Dimensions of the locker top
    simplecube(0.1, 0.1, 0.1, 0.2, 0.2, 0.2, 100); // Drawing the locker top
    glPopMatrix();

    // rack2
    glPushMatrix();
    glTranslatef(1, 0.9, 10); // Position of the locker relative to the bed
    glScalef(0.6, 0.02, 0.4); // Dimensions of the locker bottom
    simplecube(0.1, 0.1, 0.1, 0.2, 0.2, 0.2, 100); // Drawing the locker bottom
    glPopMatrix();

    // rack3
    glPushMatrix();
    glTranslatef(1, 0.6, 10); // Position of the locker relative to the bed
    glScalef(0.6, 0.02, 0.4); // Dimensions of the locker bottom
    simplecube(0.1, 0.1, 0.1, 0.2, 0.2, 0.2, 100); // Drawing the locker bottom
    glPopMatrix();
    
    // rack4
    glPushMatrix();
    glTranslatef(1, 0.3, 10); // Position of the locker relative to the bed
    glScalef(0.6, 0.02, 0.4); // Dimensions of the locker bottom
    simplecube(0.1, 0.1, 0.1, 0.2, 0.2, 0.2, 100); // Drawing the locker bottom
    glPopMatrix();

}

void myMouseFunc(int button, int state, int x, int y) {


    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        GLint viewport[4];
        GLdouble modelview[16];
        GLdouble projection[16];
        GLfloat winX, winY, winZ;
        GLdouble posX, posY, posZ;

        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glGetIntegerv(GL_VIEWPORT, viewport);

        winX = (float)x;
        winY = (float)viewport[3] - (float)y;
        glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

        // Calculate distance between mouse click and ball center
        double ball_distance = sqrt((posX - ball_x) * (posX - ball_x) +
                                    (posY - ball_y) * (posY - ball_y) +
                                    (posZ - ball_z) * (posZ - ball_z));

        // Calculate distance between mouse click and torus center
        double torus_distance = sqrt((posX - torus_x) * (posX - torus_x) +
                                     (posY - torus_y) * (posY - torus_y) +
                                     (posZ - torus_z) * (posZ - torus_z));

        // Calculate distance between mouse click and diamond center
        double diamond_distance = sqrt((posX - diamond_x) * (posX - diamond_x) +
                                     (posY - diamond_y) * (posY - diamond_y) +
                                     (posZ - diamond_z) * (posZ - diamond_z));

        // Calculate distance between mouse click and book center
        double book_distance = sqrt((posX - book_x) * (posX - book_x) +
                                     (posY - book_y) * (posY - book_y) +
                                     (posZ - book_z) * (posZ - book_z));

// Calculate distance between mouse click and drawer center
        double drawer_distance = sqrt((posX - drawer_x) * (posX - drawer_x) +
                                     (posY - drawer_y) * (posY - drawer_y) +
                                     (posZ - drawer_z) * (posZ - drawer_z));
                                     
        // Check if mouse click is within the boundaries of the ball
        if (ball_distance <= 0.1 * ballScale) {
            // Clicked on the ball, zoom in or out
            if (!zoomed) {
                // Zoom in
                ballScale += 3;
                ball_x += 4;
                ball_y += 1;
                ball_z += 1.2;
                zoomed = true;
            } else {
                // Zoom out
                ballScale = 1.0;
                ball_x = orig_ball_x;
                ball_y = orig_ball_y;
                ball_z = orig_ball_z;
                zoomed = false;
            }
        } else if (torus_distance <= 0.02 * torusScale) {
            // Clicked on the torus, zoom in or out
            // Implement zooming for torus as required
            if (!zoomed_t) {
                // Zoom in for torus
                torusScale += 10;
                // Adjust torus position accordingly
                torus_x += 4;
                torus_y += 1;
                torus_z += 1.2;
                zoomed_t = true;
            } else {
                // Zoom out for torus
                torusScale = 10.0;
                // Reset torus position to original
                torus_x = orig_torus_x;
                torus_y = orig_torus_y;
                torus_z = orig_torus_z;
                zoomed_t = false;
            }
        }else if (diamond_distance <= 0.1*diamondScale) {
            // Clicked on the diamond, zoom in or out
            // Implement zooming for diamond as required
            if (!zoomed_d) {
                // Zoom in for diamond
                diamondScale =3.0;
                // Adjust diamond position accordingly
                diamond_x += 4;
                diamond_y += 1;
                diamond_z += 1.2;
                zoomed_d = true;
            } else {
                // Zoom out for diamond
                diamondScale = 1.0;
                // Reset diamond position to original
                diamond_x = orig_diamond_x;
                diamond_y = orig_diamond_y;
                diamond_z = orig_diamond_z;
                zoomed_d = false;
            }
        }
        else if (book_distance <= 0.5*bookScale) {
            // Clicked on the diamond, zoom in or out
            // Implement zooming for diamond as required
            if (!zoomed_b) {
                 r=0;
                 bS_x=0.1;
                 bS_y=0.15;
                 bS_z=0.03;
                 bookScale=3.0;
                // Adjust book position accordingly
                book_x += 2;
                book_y += 1;
                book_z += 6;
                zoomed_b = true;
            } else {
                r=15;
                bS_x=0.03;
                bS_y=0.15;
                bS_z=0.1;
                bookScale=1.0;
                // Reset book position to original
                book_x = orig_book_x;
                book_y = orig_book_y;
                book_z = orig_book_z;
                zoomed_b = false;
            }
        }
        else if (drawer_distance <= 0.5*drawerScale) {
            // Clicked on the diamond, zoom in or out
            // Implement zooming for diamond as required
            if (!zoomed_drawer) {
                drawer_z += 0.25;
                drawerbase_z+=0.25;
                zoomed_drawer = true;
            } else {
                r=15;
                drawer_z = orig_drawer_z;
                drawerbase_z=orig_drawerbase_z;
                zoomed_drawer = false;
            }
        }
    }

    glutPostRedisplay(); // Request a redraw
}





// Modify the CricketBall function to include the ballScale
void CricketBall() {
    glPushMatrix();
    glTranslatef(ball_x, ball_y, ball_z);
    glScalef(0.02 * ballScale, 0.02 * ballScale, 0.02 * ballScale); // Apply scale factor
    drawSphere(1.0, 0.0, 0.0, 0.5, 0.0, 0.0, 100);
    glPopMatrix();
}



void Torus() {
    GLfloat brownAmbient[] = {0.4, 0.2, 0.0, 1.0}; // Brown ambient color
    GLfloat brownDiffuse[] = {0.6, 0.3, 0.0, 1.0}; // Brown diffuse color

    glPushMatrix();
    glTranslatef(torus_x, torus_y, torus_z);
    glScalef(0.01*torusScale, 0.01*torusScale, 0.01*torusScale);
    glRotatef(90, 1, 0, 0);

    // Set material properties for brown color
    glMaterialfv(GL_FRONT, GL_AMBIENT, brownAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, brownDiffuse);

    glutSolidTorus(0.5, 1, 30, 30); // Draw torus
    glPopMatrix();
}



void diamond(){
    // Material properties for a shiny, reflective surface
    GLfloat diamond_specular[] = {1.0, 1.0, 1.0, 1.0}; // Specular color
    GLfloat diamond_shininess[] = {100.0}; // Shininess factor
    
    // Set material properties
    glMaterialfv(GL_FRONT, GL_SPECULAR, diamond_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, diamond_shininess);
    
    // Color of the diamond with a slight blue tint
    GLfloat diamond_color[] = {0.7, 0.8, 1.0}; // Slightly blue tint
    
    // First diamond
    glPushMatrix();
    glTranslatef(diamond_x,diamond_y,diamond_z);
    glScalef(diamondScale*dS_x,diamondScale*dS_y,diamondScale*dS_z);
    glColor3fv(diamond_color); // Set the color
    drawpyramid(diamond_color[0], diamond_color[1], diamond_color[2], diamond_color[0], diamond_color[1], diamond_color[2], 50); // Using diamond color
    glPopMatrix();
    
    // Second inverted diamond
    glPushMatrix();
    glTranslatef(diamond_x,diamond_y,diamond_z);
    glScalef(diamondScale*dS_x,diamondScale*dS_yn,diamondScale*dS_z);
    glColor3fv(diamond_color); // Set the color
    drawpyramid(diamond_color[0], diamond_color[1], diamond_color[2], diamond_color[0], diamond_color[1], diamond_color[2], 50); // Using diamond color
    glPopMatrix();
}


void building_name(std::string s, float x, float y, float z)
{
    // Set text color to red
    glColor3f(1.0f, 0.0f, 0.0f);

    // Adjust scale factor and spacing between characters
    float scale_factor = 0.001f;
    float spacing = 0.04f;

    // Push matrix to apply transformations
    glPushMatrix();
    // Translate to position
    glTranslatef(x, y, z);
    // Rotate text to be vertical
    glRotatef(90, 0, 1, 0);
    
    // Loop through characters of the string
    for (int i = 0; i < s.size(); i++)
    {
        // Push matrix for each character
        glPushMatrix();
        // Translate to adjust spacing between characters
        glTranslatef(0, 0, spacing * i);
        // Scale text
        glScalef(scale_factor, scale_factor, scale_factor);
        // Render character
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, s[i]);
        // Pop matrix for each character
        glPopMatrix();
    }

    // Pop matrix to revert transformations
    glPopMatrix();
}

void building_name2(std::string s, float x, float y, float z)
{


    // Adjust scale factor and spacing between characters
    float scale_factor = 0.0012f;
    float spacing = 0.09f;


    // Push matrix to apply transformations
    glPushMatrix();
    // Translate to position
    glTranslatef(x, y, z);
    // Rotate text to be vertical along the Y-axis
    glRotatef(-90, 0, 1, 0); // Rotate in the opposite direction to face the left wall
    glRotatef(-90,0,1,0);
    // Loop through characters of the string
    for (int i = 0; i < s.size(); i++)
    {
        // Push matrix for each character
        glPushMatrix();
        // Translate to adjust spacing between characters
        glTranslatef(0, 0, spacing * i); // Adjust the translation along the Z-axis
        // Scale text
        glRotatef(180,0,1,0);
        glScalef(scale_factor, scale_factor, scale_factor);
        // Render character
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, s[i]);
        // Pop matrix for each character
        glPopMatrix();
    }

    // Pop matrix to revert transformations
    glPopMatrix();
}

void Poster()
{       
       //poster black
       glPushMatrix();
       glTranslatef(-1,1.4,4.6);
       glScalef(0.0001, .65, .8);
       drawCube1(0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 10);
       glPopMatrix();
       
       glColor3f(1.0,1.0,1.0);
       glPushMatrix();
       glTranslatef(-0.9,1.8,6);
       glRotatef(-60, 1,0,0);
       glScalef(0.0001, .02, .25);
       drawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10);
       glPopMatrix();

       glColor3f(1.0,1.0,1.0);
       glPushMatrix();
       glTranslatef(-0.9,1.8,6);
       glRotatef(240, 1,0,0);
       glScalef(0.0001, .02, .27);
       drawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10);
       glPopMatrix();


       glPushMatrix();
       glTranslatef(-0.9,2.6,6.2);
       glRotatef(60, 1,0,0);
       glScalef(0.0001, .02, 0.08);
       drawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10);
       glPopMatrix();
       


       glColor3f(1.0,1.0,1.0);
       glPushMatrix();
       glTranslatef(-0.9,2.62,5.67);
       glScalef(0.0001, .02, .19);
       drawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10);
       glPopMatrix();


       glColor3f(1.0,1.0,1.0);
       glPushMatrix();
       glTranslatef(-0.9,2.50,5.55);
       glRotatef(36, 1,0,0);
       glScalef(0.0001, 0.08, .029);
       drawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10);
       glPopMatrix();





       glColor3f(1.0,1.0,1.0);
       glPushMatrix();
       glTranslatef(-0.9,1.8,6);
       glRotatef(-75, 1,0,0);
       glScalef(0.0001, .02, .3);
       drawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10);
       glPopMatrix();

       glColor3f(1.0,1.0,1.0);
       glPushMatrix();
       glTranslatef(-0.9,1.8,6);
       glRotatef(255, 1,0,0);
       glScalef(0.0001, .02, .3);
       drawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10);
       glPopMatrix();
       

       glColor3f(1.0,1.0,1.0);
       glPushMatrix();
       glTranslatef(-0.9,2.42,5.62);
       glScalef(0.0001, .02, .24);
       drawCube1(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10);
       glPopMatrix();


      glColor3f(0.0,0.0,0.8);
      glPushMatrix();   
      building_name2("YOU CAN'T ESCAPE",-1,3,6.6);
      building_name2("FROM HERE :>",-1,2.8,6.5);
      glPopMatrix();
       
}
void Clock()
{
    // Clock body
    glPushMatrix();
    glTranslatef(-0.9,2.3,7.885);
    glScalef(0.08, 0.25, 0.15);
    drawSphere(0.545, 0.271, 0.075, 0.545, 0.271, 0.075, 90); // Replace drawCube1 with drawSphere
    glPopMatrix();
    
    // Clock body white
    glPushMatrix();
    glTranslatef(-0.83,2.3,7.885);
    glScalef(0.06, 0.21, 0.14);
    drawSphere(1.000, 0.894, 0.710, 1.000, 0.894, 0.710, 90); 
    glPopMatrix();
    
    // Clock hour handle
    glPushMatrix();
    glTranslatef(-0.65,2.3,8.0);
    glRotatef(45, 1,0,0);
    glScalef(0.0001, 0.01, 0.04);
    drawSphere(0, 0, 0, 0, 0, 0, 90); // Replace drawCube1 with drawSphere
    glPopMatrix();
    
    // Clock minute handle
    glPushMatrix();
    glTranslatef(-0.65,2.3,8.0);
    glRotatef(90, 1,0,0);
    glScalef(0.0001, 0.012, 0.08);
    drawSphere(0, 0, 0, 0, 0, 0, 90); // Replace drawCube1 with drawSphere
    glPopMatrix();
    
// Draw numbers on the clock face
    glPushMatrix();
    float radius = 0.35; // Radius of the circle
    float centerY = 2.3; // Y coordinate of the center of the circle
    float centerZ = 8.025; // Z coordinate of the center of the circle
    float startAngle = 0; // Start angle (aligned with 12 o'clock)
    float angleIncrement = -2 * M_PI / 12.0; // Angle between each number, adjusted for clockwise arrangement

    for (int i = 0; i < 12; ++i)
    {
        float angle = startAngle + i * angleIncrement;
        float y = centerY + radius * cos(angle); // Calculate y coordinate
        float z = centerZ + radius * sin(angle); // Calculate z coordinate
        building_name(std::to_string(i + 1), -0.65, y, z); // X coordinate can be adjusted as needed
    }

 
    
}





void simplecylinder(float a1, float a2, float a3, float d1, float d2, float d3, float s, float baseRadius, float topRadius, float height, int slices, int stacks) {
    GLfloat ambient[] = {a1, a2, a3}; // Ambient color (RGB)
    GLfloat diffuse[] = {d1, d2, d3}; // Diffuse color (RGB)

    GLfloat shininess = s; // Shininess (0-128)
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    
    gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);
    
    gluDeleteQuadric(quadric);
}

void bottle() {
	   // Bottom of the bottle (light purple)
	glPushMatrix();
	glTranslatef(7.0, 0.0, 11.0); 
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(0.5,0.5,0.5);
	simplecylinder(0.6f, 0.4f, 0.8f, 0.8f, 0.6f, 1.0f, 5.0f, 
		       0.2f, 0.2f, 0.5f, 20, 20);
	glPopMatrix();

	// Top of the bottle (light purple)
	glPushMatrix();
	glTranslatef(7.0, 0.25, 11.0); 
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(0.5,0.5,0.5);
	simplecylinder(0.6f, 0.4f, 0.8f, 0.8f, 0.6f, 1.0f, 5.0f, 
		       0.2f, 0.07f, 0.2f, 20, 20);
	glPopMatrix();

		// Cap of the bottle (light purple)
	glPushMatrix();
	glTranslatef(7.0, 0.35, 11.0); 
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(0.5,0.5,0.5);
	simplecylinder(0.4f, 0.2f, 0.6f, 0.6f, 0.3f, 0.8f, 5.0f, 
		       0.1f, 0.1f, 0.1f, 20, 20);
	glPopMatrix();


}
void wallshelf()
{
    //Wall Shelf **
      
      //wall shelf left
      glPushMatrix();
      glTranslatef(0.4,0.8,1);
      glScalef(0.02, 1.1, 0.2);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();
      
      //wall shelf left
      glPushMatrix();
      glTranslatef(1.1,0.8,1);
      glScalef(0.02, 1.1, 0.2);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();
      
      //wall shelf left
      glPushMatrix();
      glTranslatef(1.82,0.8,1);
      glScalef(0.02, 0.74, 0.2);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();
         
      //wall shelf left
      glPushMatrix();
      glTranslatef(2.56,0.8,1);
      glScalef(0.02, 0.37, 0.2);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix(); 
       
      //wall shelf top
      glPushMatrix();
      glTranslatef(0.4,4.05,1);
      glScalef(0.25, 0.03, 0.2);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();   
      
      //wall shelf bottom
      glPushMatrix();
      glTranslatef(0.4,2.97,1);
      glScalef(0.5, 0.03, 0.2);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();  
      
      //wall shelf bottom
      glPushMatrix();
      glTranslatef(0.4,1.883,1);
      glScalef(0.75, 0.03, 0.2);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();   
      
      //wall shelf bottom
      glPushMatrix();
      glTranslatef(0.4,0.8,1);
      glScalef(0.75, 0.03, 0.2);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();

          

}

void showpiece(){
      
      //showpiece on 3th shelf
      glPushMatrix();
      glTranslatef(1.4,0.9,1.2);
      glScalef(0.2, 0.1, 0.2);
      drawpyramid(0.282,0.239,0.545,  0.141,0.1195,0.2725, 50);
      glPopMatrix();
      
      //showpiece on 3th shelf
      glPushMatrix();
      glTranslatef(2,0.9,1.2);
      glScalef(0.15, 0.1, 0.2);
      drawpyramid(1.0, 0.752, 0.796, 0.5, 0.376, 0.398, 50);
      glPopMatrix();
      
      //showpiece on 3th shelf
      glPushMatrix();
      glTranslatef(0.6,0.9,1.2);
      glScalef(0.15, 0.1, 0.2);
      drawpyramid(0.545, 0.271, 0.369, 0.2725, 0.1355, 0.1845, 50);
      glPopMatrix();
      
     //showpiece on 1th shelf
    glPushMatrix();
    glTranslatef(0.6, 3.06, 1.2); // Position of the top book on the table (stacked on top of the bottom book)
    glScalef(0.1, 0.05, 0.15); // Dimensions of the book
    drawCube1(0.2, 0.5, 0.8, 0.1, 0.05, 0.05); // Drawing the book
    glPopMatrix();
    
     //showpiece on 2th shelf
    glPushMatrix();
    glTranslatef(0.6, 1.97, 1.12); // Position of the top book on the table
    glScalef(0.08, 0.1, 0.1); // Dimensions of the book
    drawCube1(0.0, 0.0, 0.545, 0.1, 0.05, 0.05);
    glPopMatrix();
     
     //showpiece on 2th shelf
    glPushMatrix();
    glTranslatef(0.57,2.21,1.15);
    glScalef(0.15, 0.12, 0.18);
    drawpyramid(0.545, 0.271, 0.075, 0.545, 0.271, 0.075, 50);
    glPopMatrix();
   
    //showpiece on 2th shelf
    
    glPushMatrix();
    glTranslatef(1.18, 1.97, 1.2); // Position of the top book on the table
    glScalef(0.03, 0.15, 0.1); // Dimensions of the book	
    glColor3f(0.4, 0.7, 0.2); // Change the color (e.g., to green)
    drawCube1(0.545, 0.271, 0.075, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(book_x,book_y,book_z); // Position of the top book on the table
    glScalef(bookScale*bS_x,bookScale*bS_y,bookScale*bS_z); // Dimensions of the book
    glRotatef(r,0,1,0);
    drawCube1(0.6, 0.11, 0.11, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.45, 1.98, 1.2); // Position of the top book on the table
    glScalef(0.1, 0.03, 0.1); // Dimensions of the book
    //glRotatef(-20,0,0,0);
    glColor3f(0.4, 0.7, 0.2); // Change the color (e.g., to green)
    drawCube1(0.545, 0.271, 0.075, 0.1, 0.05, 0.05);
    glPopMatrix();


}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	if (zoomed_b) {
        // Display text when not zoomed out
        building_name("YOUR NEXT CLUE", (book_x)+0.7, (book_y)+0.4, (book_z + 1.5));
        building_name("IS IN LOCKER", (book_x)+0.7, book_y, (book_z + 1.5));

    }
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(60,1,1,100);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  0,1,0); //7,2,15, 0,0,0, 0,1,0
    
    glEnable(GL_LIGHTING);
    lightOne();
    lightTwo();
    lampLight();
    diamond();
    bottle();
    room();
    Poster();
    bed();
    table();
    chair();
    locker();
    bookstack();
    door();
    CricketBall();
    Teapot();
    Torus();
    lamp();
    wallshelf();
    showpiece();
    Clock();
    window();
    Drawer();
    lightBulb1();
    lightBulb2();
    glDisable(GL_LIGHTING);
    glFlush();
    glutSwapBuffers();
    
}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    
    std::cout<<"To move Eye point:"<< std::endl;
    std::cout<<"w: up"<<std::endl;
    std::cout<<"s: down"<<std::endl;
    std::cout<<"a: left"<<std::endl;
    std::cout<<"d: right"<<std::endl;
    std::cout<<"i: zoom in"<<std::endl;
    std::cout<<"o: zoom out"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"To move Camera point:"<< std::endl;
    std::cout<<"j: up"<<std::endl;
    std::cout<<"n: down"<<std::endl;
    std::cout<<"b: left"<<std::endl;
    std::cout<<"m: right"<<std::endl;
    std::cout<<"l: move nearer"<<std::endl;
    std::cout<<"k: move far"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"Press q to move to default position"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"For lighting:      "<<std::endl;
    std::cout<<"Light source 1 [the light on the right on the screen      "<<std::endl;
    std::cout<<"1: to turn on/off light one     "<<std::endl;
    std::cout<<"4: to turn on/off ambient light one     "<<std::endl;
    std::cout<<"5: to turn on/off diffusion light one     "<<std::endl;
    std::cout<<"6: to turn on/off specular light one      "<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"Light source 2 [the light on the left on the screen "<<std::endl;
    std::cout<<"2: to turn on/off light two     "<<std::endl;
    std::cout<<"7: to turn on/off ambient light two     "<<std::endl;
    std::cout<<"8: to turn on/off diffusion light two     "<<std::endl;
    std::cout<<"9: to turn on/off specular light two      "<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"Lamp light (spot light)" <<std::endl;
    std::cout<<"3: to turn on/off lamp     "<<std::endl;
    std::cout<<"e: to turn on/off ambient lamp light    "<<std::endl;
    std::cout<<"r: to turn on/off diffusion lamp light      "<<std::endl;
    std::cout<<"t: to turn on/off specular lamp light      "<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"      "<<std::endl;
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("3D Escape Room");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glutReshapeFunc(fullScreen);
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);
    //glutMouseFunc(myMouseFuncForTorus);
    glutMouseFunc(myMouseFunc);
    glutMainLoop();

    return 0;
}
