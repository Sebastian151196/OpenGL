#include <stdio.h>
#include <math.h>
#include "planet.h"
#include "getbmp.h"


#define countTime 1
#define ARRAY_SIZE 13

//define radius of planet
#define mercuryRadius (0.3829*earthRadius)
#define venusRadius (0.9499*earthRadius)
#define earthRadius 2
#define moonRadius (0.83*earthRadius)
#define marsRadius (0.532*earthRadius)
#define jupiterRadius (3.209*earthRadius) //11.209
#define saturnRadius (3.4492*earthRadius) //9.4492
#define uranusRadius (4.007*earthRadius)
#define neptuneRadius (3.883*earthRadius)
#define sunRaius (5*earthRadius) //109



//camera (+z -y)

// lookAt
GLdouble eyeX = 0, eyeY = -150, eyeZ= 150;
GLdouble centerX= 0, centerY= 0, centerZ= 0;
GLdouble upX= 0, upY= 0, upZ= 1;
//bool meshOnly = false;

GLuint texture[15]; // Array of texture ids.


enum PLANETS {Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune, one, two, three};
Planet * Planets[ARRAY_SIZE];

void loadExternalTextures()
{
    // Local storage for bmp image data.
    BitMapFile *image[11];
    
    // Load the image.
    image[0] = getBmp("Textures/sunmap.bmp");
    image[1] = getBmp("Textures/Uranus.bmp");
    image[3] = getBmp("Textures/Earth.bmp");
    image[4] = getBmp("Textures/Moon.bmp");
    image[2] = getBmp("Textures/Pluto.bmp");
    image[5] = getBmp("Textures/Mars.bmp");
    image[6] = getBmp("Textures/Venus.bmp");
    image[7] = getBmp("Textures/Mercury.bmp");
    image[8] = getBmp("Textures/Neptune.bmp");
    image[9] = getBmp("Textures/Uranus.bmp");
    image[10] = getBmp("Textures/Saturn.bmp");
    
    for (int i =0;i<11;i++){
        // Create texture object texture[0].
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        
        // Specify image data for currently active texture object.
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[i]->sizeX, image[i]->sizeY, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, image[i]->data);
        
        // Set texture parameters for wrapping.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        // Set texture parameters for filtering.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
}


void setup(){
    //texture.
    glGenTextures(15, texture);
    loadExternalTextures();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_2D);
}

void init() {
    //    for (int i =0; i<ARRAY_SIZE;i++){
    //        Planets[i]->texture();
    //    }
    
    //textureInit();
    //GLuint temp;
    Planets[Sun] = new Planet(sunRaius,0,0,5,0);
    // Planets[Sun]->textureInit();
    // glGenTextures(1, &temp);
    
    //cout<<"texture[0]"<<texture[0];
    Planets[Mercury] = new Planet(mercuryRadius,15,87,6,Planets[Sun]);
    
    //cout<<"texture[0]"<<texture[1];
    Planets[Venus] = new Planet(venusRadius,25,225,6,Planets[Sun]);
    
    Planets[Earth] = new Planet(earthRadius,35,365,6,Planets[Sun]);
    
    Planets[Moon] = new Planet(moonRadius,10,30,5,Planets[Earth]);
    Planets[Mars] = new Planet(marsRadius,55,687,6,Planets[Sun]);
    Planets[Jupiter] = new Planet(jupiterRadius,68,4331,5,Planets[Sun]);
    Planets[Saturn] = new Planet(saturnRadius,95,10832,4,Planets[Sun]);
    Planets[Uranus] = new Planet(uranusRadius,110,30799,5,Planets[Sun]);
    Planets[Neptune] = new Planet(neptuneRadius,140,60327,2,Planets[Sun]);
    Planets[one] = new Planet(3,10,90,4,Planets[Neptune]);
    Planets[two] = new Planet(2,15,67,3,Planets[Neptune]);
    Planets[three] = new Planet(2,10,67,3,Planets[Jupiter]);
    
    Planets[Sun]->textId = texture[0];
    Planets[Mercury]->textId = texture[1];
    Planets[Venus]->textId = texture[2];
    Planets[Earth]->textId = texture[3];
    Planets[Moon]->textId = texture[4];
    Planets[Mars]->textId = texture[5];
    Planets[Jupiter]->textId = texture[6];
    Planets[Saturn]->textId = texture[7];
    Planets[Uranus]->textId = texture[8];
    Planets[Neptune]->textId = texture[9];
    
    
    //    // Light property vectors.
}
void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT  |  GL_DEPTH_BUFFER_BIT);
    glClearColor(0.8, 0.8, 0.8, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Material property vectors.
    gluPerspective(75.0f, 1.0f, 1.0f, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY,eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    
    for (int i=0; i<ARRAY_SIZE; i++){
        Planets[i]->drawPlanet();
    }
    glutSwapBuffers();
}

void idle(void) {
    for (int i=0; i<ARRAY_SIZE; i++){
        Planets[i]->update(countTime);
    }
    drawScene();
    
}

void keyInput (unsigned char key, int x, int y) {
    switch (key){
        case 'z':
            eyeZ+=5;
            break;
        case 'Z':
            eyeZ-=5;
            break;
        case 'r':
            eyeX = 0; eyeY = -150; eyeZ= 150;
            centerX= 0; centerY= 0; centerZ= 0;
            upX= 0; upY= 0; upZ= 1;
            break;
        case 'q':exit(1); break;
        default: break;
    }
    glutPostRedisplay();
}
void keyArrowInput(int key, int x, int y){
    if(key == GLUT_KEY_LEFT){
        eyeX+=5;
    }
    if(key == GLUT_KEY_RIGHT){
        eyeX-=5;
    }
    if(key == GLUT_KEY_UP){
        eyeY+=5;
    }
    if(key == GLUT_KEY_DOWN){
        eyeY-=5;
    }
    glutPostRedisplay();
}


int main(int argc, char*  argv[]) {
      
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA |  GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Solar System");
    setup();
    init();
    glutDisplayFunc(drawScene);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(keyArrowInput);
    
    
    glutMainLoop();
    
    return 0;
}
