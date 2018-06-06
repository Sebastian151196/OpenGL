/*
 * Nombre: Funcion polar
 *
 * Autor: Sebastián de Jesus
 *
 * 
 */

#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace std; 

void renderScene(void){

	double r;
	int a = 10;
	double t = 0;

	double x;
	double y;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		while (t <= 2 * M_PI){
			r = (double)a * cos(3 * t);
			x =  r * cos(t);
			y = r * sin(t);
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
	glutInitWindowSize(500, 500);
	glutCreateWindow("Funcion polar");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-11, 11, -11, 11);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
