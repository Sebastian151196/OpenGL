#ifndef __PLANET
#define __PLANET

#include <stdio.h>
#include <GL/glut.h>

class Planet {
public:
    //float color[4];
    float radius;
    float revolutionSpeed;
    float selfSpeed;
    Planet * parentPlanet; //parent planet.
    float distance; //between child and parent.
    float alpha; // angle
    float selfAlpha;
    GLuint textId;
    //constructor
    Planet(float radius, float distance, float revolutionSpeed,float selfSpeed, Planet* parent);
    
    void drawPlanet();
   // void loadExternalImage();
    //void textureInit();
    void update(float time);
    
};
#endif /* defined(__motionViewer__planet__) */
