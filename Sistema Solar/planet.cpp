#include "planet.h"
#include "math.h"
#include "getbmp.h"
#include <iostream>
using namespace std;
#define PI 3.1415926
GLUquadric *sun;
//texture
GLuint id; // Currently displayed texture id.

//Constructor
Planet::Planet(float radius, float distance, float revolutionSpeed,float selfSpeed, Planet* parent){
    //this->color = {0,0,0,1.0};
    this->radius = radius;
    this->distance = distance;
    if(revolutionSpeed > 0){
        this->revolutionSpeed = 360.0 / revolutionSpeed;
    }
    this->selfSpeed = selfSpeed;
    this->parentPlanet = parent;
    
}
void Planet::drawPlanet(){
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glPushMatrix();
    
    { sun = gluNewQuadric();
    
    //revolution route.
    if(parentPlanet != 0 && parentPlanet->distance >0){
        glRotatef(parentPlanet->alpha, 0.0, 0.0, 1.0);
        glTranslatef(parentPlanet->distance, 0.0, 0.0);
        
        glBegin(GL_LINES);
        // glColor3f(0.0,0.0,0.0); // route
        for(int i =0; i<1440;i++){
            glVertex2f(distance * cos(2.0 * PI * i/1440.0), distance * sin(2.0 * PI * i/1440.0));
            
        }
        glEnd();
        
    }else{
        glBegin(GL_LINES);
        //cout<<"route"<<endl;
       // glColor3f(0.0,0.0,0.0); // route
        for(int i =0; i<1440;i++){
            glVertex2f(distance * cos(2.0 * PI * i/1440.0), distance * sin(2.0 * PI * i/1440.0));
        }
        glEnd();
        
    }
    glRotatef(alpha, 0.0, 0.0, 1.0);
    glTranslatef(distance, 0.0, 0.0);
    
    //self rotation
    glRotatef(selfAlpha, 0.0, 0.0, 1.0);
    
    glBindTexture(GL_TEXTURE_2D, textId);
    // printf("fff"+textId);
    // cout<<"textId"<<textId;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluQuadricTexture(sun,1);
       // glColor3f(0.5,0.5,0.5);
    gluSphere(sun,radius,20,20);
}
    //draw mesh
    //glColor3f(0.0, 0.0, 0.0);
    
    //  glGenTextures(2,textureID);
    //loadExternalTextures();
    // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //if(mesh){
    //glutWireSphere(radius, 20, 20);
    //    }else{
    //    glutSolidSphere(radius, 20, 20);
    //    }
    glPopMatrix();
    
}
void Planet::update(float time){
    //time ---- day by dat
    alpha += time * revolutionSpeed;
    selfAlpha += selfSpeed;
}
