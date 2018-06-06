/*
 * Nombre: Spline Bezier
 *
 * Autor: Sebastian Marroquin
 */

#include <iostream>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std; 

class Punto{
	int x;
	int y;
public:
	void setPunto(int xx, int yy);
	int getX();
	int getY();
};

void Punto::setPunto(int xx, int yy){
	x = xx;
	y = yy;
}

int Punto::getX(){
	return x;
}

int Punto::getY(){
	return y;
}

void renderScene(void){
	Punto A, B, C, D;

	A.setPunto(106, 135); //Punto A
	B.setPunto(221, 193); //Punto B
	C.setPunto(423, 106); //Punto C
	D.setPunto(526, 109); //Punto D

	float t = 0;
	float x;
	float y;
	float dk;
	float dk1;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		while (t <= 1){
			dk = 3 * (B.getX() - A.getX());
			dk1 = 3 * (D.getX() - C.getX());
			x = A.getX() * ((2 * pow(t, 3)) - (3 * pow(t, 2)) + 1) + 
					D.getX() * ((-2 * pow(t, 3)) + (3 * pow(t, 2))) +
					dk * (pow(t, 3) - (2 * pow(t, 2)) + t) +
					dk1 * (pow(t, 3) - pow(t, 2));
			dk = 3 * (B.getY() - A.getY());
			dk1 = 3 * (D.getY() - C.getY());
			y = A.getY() * ((2 * pow(t, 3)) - (3 * pow(t, 2)) + 1) + 
					D.getY() * ((-2 * pow(t, 3)) + (3 * pow(t, 2))) +
					dk * (pow(t, 3) - (2 * pow(t, 2)) + t) +
					dk1 * (pow(t, 3) - pow(t, 2));
			glVertex2f(x, y);
			t += 0.001;
		}
	glEnd();
	glFlush();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Spline Bezier");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 640, 0, 480);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}