//#include <GLUT/glut.h>
#include <GL/glut.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "imageloader.h" //HELPER CLASS TO LAOD BMP DATA



void MouseWheel();

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

double zoom = 0.3;

// XZ position of the camera
float x=0.0f, z=5.0f;


// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// define glu objects

GLUquadricObj *sphereObj;
GLUquadricObj *Cylinder;
GLUquadricObj *Disk;

GLuint texture; // this variable stores the texture

struct tm *newtime;
time_t ltime;

GLfloat rx, ry, rz, angle;

// lighting
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition[]= { 5.0f, 25.0f, 15.0f, 1.0f };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

static int light_state = 1; // light on = 1, light off = 0
static int view_state = 1; // Ortho view = 1, Perspective = 0

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)

bool movingUp = false; // Whether or not we are moving up or down
float yLocation = 0.0f; // Keep track of our position on the y axis.

float yRotationAngle = 0.0f; // The angle of rotation for our object

void keyOperations (void) {
    if (keyStates[GLUT_KEY_UP]) { // If the left arrow key has been pressed
    // Perform left arrow key operations
    }
}

GLuint loadTexture(Image* image) {

  GLuint textureId;

  glGenTextures(1, &textureId); //Make room for our texture

  glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit

  //Map the image to the texture
/*
  glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
         0,                            //0 for now
         GL_RGB,                       //Format OpenGL uses for image
         image->width, image->height,  //Width and height
         0,                            //The border of the image
         GL_RGB, //GL_RGB, because pixels are stored in RGB format
         GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                           //as unsigned numbers
         image->pixels);               //The actual pixel data
*/
 gluBuild2DMipmaps( GL_TEXTURE_2D, 3, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->pixels );
  return textureId; //Returns the id of the texture

}

void img(int id){
    
    if(id == 1){
        Image *image = loadBMP("DATA/neptune.bmp");
        texture = loadTexture(image);
        
        delete image;
    }
    
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}



void Sprint( int x, int y, char *st)
{
    int l,i;

    l=strlen( st );
    glRasterPos3i( x, y, -1);
    for( i=0; i < l; i++)
        {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
    }

}

static void TimeEvent(int te)
{
    int timent;
    int i;
    int M_TWOPI=0;
    rx = 30 * cos( angle );
    ry = 30 * sin( angle );
    rz = 30 * cos( angle );
    angle += 0.01;
    if (angle > M_TWOPI) angle = 0;

    glutPostRedisplay();
    glutTimerFunc( 100, TimeEvent, 1);
}

void init(void)
{


   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   // Lighting is added to scene
   glLightfv(GL_LIGHT1 ,GL_AMBIENT, LightAmbient);
   glLightfv(GL_LIGHT1 ,GL_DIFFUSE, LightDiffuse);
   glLightfv(GL_LIGHT1 ,GL_POSITION, LightPosition);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT1);


   Cylinder = gluNewQuadric();
   gluQuadricDrawStyle( Cylinder, GLU_FILL);
   gluQuadricNormals( Cylinder, GLU_SMOOTH);
   gluQuadricOrientation( Cylinder, GLU_OUTSIDE);
   gluQuadricTexture( Cylinder, GL_TRUE);

   Disk = gluNewQuadric();
   gluQuadricDrawStyle( Disk, GLU_FILL);
   gluQuadricNormals( Disk, GLU_SMOOTH);
   gluQuadricOrientation( Disk, GLU_OUTSIDE);
   gluQuadricTexture( Disk, GL_TRUE);


}

void Draw_gear( void )
{

    int i;
    glPushMatrix();
    gluCylinder(Cylinder, 2.5, 2.5, 1, 16, 16);
    gluDisk(Disk, 0, 2.5, 32, 16);
    glTranslatef(0,0,1);
    gluDisk(Disk, 0, 2.5, 32, 16);
    glPopMatrix();
    for( i = 0; i < 8; i++)
        {
        glPushMatrix();
        glTranslatef( 0.0, 0.0, 0.50);
        glRotatef( (360/8) * i, 0.0, 0.0, 1.0);
        glTranslatef( 3.0, 0.0, 0.0);
        //glutSolidCube( 1.0 );
        glPopMatrix();
        }


}


void Draw_clock( GLfloat cx, GLfloat cy, GLfloat cz )
{

  keyOperations();
    
  //GLfloat angulo = 0.0f;
  sphereObj = gluNewQuadric();

  img(1);
  
  gluQuadricDrawStyle(sphereObj, GLU_FILL);
  gluQuadricTexture(sphereObj, GL_TRUE);
  gluQuadricNormals(sphereObj, GLU_SMOOTH);  
  
  
  int hour_ticks , sec_ticks;
  glPushMatrix();

  glTranslatef(cx,cy,cz);
  glRotatef( 180, 1.0, 0.0, 0.0);

  glPushMatrix(); // Draw large wire cube
  //glColor3f(0.5, 1.5, 1.0);
  glTranslatef( 0.0, 0.0, 6.0);
  //glutWireCube(14.0);
  glPopMatrix();

  glPushMatrix(); // Draw clock face
  glColor3f(1.0, 1.5, 0.5);
  glTranslatef( 0.0, 0.0, 0.0);
  //gluSphere(sphereObj, 6.5, 32, 16);  

  //glRotatef(290.0f, 0.0f, 0.0f, 1.0f);
  glRotatef(yRotationAngle, 0.0f, 12.0f, 0.0f); // Rotate our object around the y axis
  
  //glScalef(zoom, zoom, 1.0f);
  
  //glScalef(zoom, zoom, 1.0f);
  
  glutWireSphere(6.5, 32, 16);
  
  
  
  glLoadIdentity();
  
  //gluDisk(Disk, 0, 6.75, 32, 16);

  glPopMatrix();
  
  //glDeleteTextures(1, &texture);
  
      
    if (movingUp) // If we are moving up
        yLocation -= 0.005f; // Move up along our yLocation
    else  // Otherwise
        yLocation += 0.005f; // Move down along our yLocation

    if (yLocation < -3.0f) // If we have gone up too far
        movingUp = false; // Reverse our direction so we are moving down
    else if (yLocation > 3.0f) // Else if we have gone down too far
        movingUp = true; // Reverse our direction so we are moving up

    yRotationAngle += 0.005f; // Increment our rotation value

    if (yRotationAngle > 360.0f) // If we have rotated beyond 360 degrees (a full rotation)
        yRotationAngle -= 360.0f; // Subtract 360 degrees off of our rotation
        
  glFlush();
    

  glPushMatrix();// Draw hour hand
  glColor3f(2.5, 0.5, 0.5);
  glTranslatef( 0, 0, 0.0);
  glRotatef( (360/12) * newtime->tm_hour  + (360/60) * (60 / (newtime->tm_min+1)), 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 2.0);
  Draw_gear();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.75, 0, 4, 16, 16);
  glPopMatrix();

  glPushMatrix();// Draw minute hand
  glColor3f(2.5, 1.5, 1.5);
  glTranslatef( 0, 0, 0.0);
  glRotatef( (360/60) * newtime->tm_min, 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 3.0);
  glScalef(0.5, 0.5, 1.0);
  Draw_gear();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.5, 0, 6, 16, 16);
  glPopMatrix();

  glPushMatrix();// Draw second hand
  glColor3f(1.5, 0.0, 0.5);
  glTranslatef( 0, 0, -0.0);
  glRotatef( (360/60) * newtime->tm_sec, 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 4.0);
  glScalef(0.25, 0.25, 1.0);
  Draw_gear();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.25, 0, 6, 16, 16);
  glPopMatrix();

  //Hours
  for(hour_ticks = 0; hour_ticks < 12; hour_ticks++)
      {
      glPushMatrix();// Draw next arm axis.
      glColor3f(1.0, 1.0, 1.0); // give it a color
      glTranslatef(0.0, 0.0, 0.0);
      glRotatef(angle, 1.0, 0.0, 1.0);
      glRotatef( (360/12) * hour_ticks, 0.0, 0.0, 1.0);
      glTranslatef( 6.0, 0.0, 0.0);
      //glutSolidCube(1.0);
      glScalef(zoom, zoom, 1.0f);
      glutSolidSphere(0.5, 20, 16);
      

      glPopMatrix();
  }
  //Minutes
  for(sec_ticks = 0; sec_ticks < 60; sec_ticks++)
     {
       glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
    glTranslatef(6.0, 0.0, 0.0);
    //glutSolidCube(0.25);
    glColor3f(1.0, 1.0, 2.0);
    glutSolidCone(0.15, 2, 4, 4);
    glPopMatrix();
    }


  glPopMatrix();

}


void display(void)
{
    
  time(&ltime); // Get time
  newtime = localtime(&ltime); // Convert to local time
  
  if (deltaMove)
		computePos(deltaMove);

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // easy way to put text on the screen.
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-8.0, 8.0, -8.0, 8.0, 1.0, 60.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);

  // Put view state on screen
  glColor3f( 1.0, 1.0, 1.0);
  if (view_state == 0)
      {
      //Sprint(-3, -4, "Vista en perspectiva");
      //}else Sprint(-2, -4, "Vista Ortogonal");
      }

      Sprint(-4,-8, asctime(newtime));
  // Set the camera
	gluLookAt(	x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);
  // Turn Perspective mode on/off
  if (view_state == 0)
     {
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity();

     gluPerspective(70.0, 1, 1.0, 70.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
  
     gluLookAt( rx, 0.0, rz, 0.0, 0.0, -14.0, 0, 1, 0);
     }

    if (light_state == 1)
      {
       glEnable(GL_LIGHTING);
       glEnable(GL_COLOR_MATERIAL);  // Enable for lighing
      }else
      {
      glDisable(GL_LIGHTING);
      glDisable(GL_COLOR_MATERIAL);  // Disable for no lighing
  }

Draw_clock( 0.0, 0.0, -10.0);
//-14.0


glutSwapBuffers();
}

void MouseWheel(int wheel, int direction, int x, int y){
    
    wheel = 0;
    if(direction == -1){
        zoom -= 0.3; 
    }
    else if(direction == +1){
        zoom += 0.3;
    }
    
    glutPostRedisplay();
}


void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
}

void keyboard (unsigned char key, int x, int y)
{
   
   float fraction = 0.1f;
   keyStates[key] = true; // Set the state of the current key to pressed
   switch (key)
   {
         case 'L':
         light_state = abs(light_state - 1);
         break;
         case 'V':
         view_state = abs(view_state - 1);
         break;
         
      case 27:
         exit(0); // exit program when [ESC] key presseed
         break;
      default:
         break;
   }


}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 'W':
			x += lx * fraction;
			z += lz * fraction;
			break;
		case 'S':
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
}



void releaseKey(int key, int x, int y) { 	
        keyStates[key] = false; // Set the state of the current key to not pressed
        switch (key) {
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
        }
} 


void mouseMove(int x, int y) { 	

         // this will only be true when the left button is down
         if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
        lx = -sin(angle + deltaAngle);

	}
}



void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (900, 900);
   glutInitWindowPosition (10, 10);
   glutCreateWindow (argv[0]);
   glutSetWindowTitle("OpenGL Clock");
   init ();
   /*
   glutDisplayFunc(display);
   //glutReshapeFunc(reshape);
   glutReshapeFunc(changeSize);
   glutKeyboardFunc(keyboard);
   	glutSpecialUpFunc(releaseKey);
   // here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
    
    */
    // register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutIdleFunc(display);

	//glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyboard);
    glutSpecialFunc(processSpecialKeys);
	//glutSpecialFunc(keyboard);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	//glutMouseFunc(mouseButton);
	//glutMotionFunc(mouseMove);
    glutMouseFunc(MouseWheel);
    
    //glutMouseWheelFunc(MouseWheel);
    
    
   glutTimerFunc( 10, TimeEvent, 1);
   
   	// OpenGL init
	glEnable(GL_DEPTH_TEST);
   
   glutMainLoop();
   return 0;
}
