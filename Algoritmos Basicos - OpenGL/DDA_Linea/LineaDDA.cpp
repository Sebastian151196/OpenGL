/*
 * Nombre: Algoritmo DDA (Digital differential analyzer)
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

	//Punto 1: (7, 10)
	int x1 = 7;
	int y1 = 10;
	//Punto 2: (600, 300)
	int x2 = 600;
	int y2 = 300;

	int steps;

	int dx = x2 - x1;
	int dy = y2 - y1;

	float x = x1;
	float y = y1;

	if (fabs(dx) > fabs(dy)){
		steps = fabs(dx);
	}else{
		steps = fabs(dy);
	}

	float xi = (float)dx / (float)steps;
	float yi = (float)dy / (float)steps;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		glVertex2i(ceil(x), ceil(y));
		for (int k = 0; k < steps; k++){
			x += xi;
			y += yi;
			glVertex2i(ceil(x), ceil(y));
		}
	glEnd();
	glFlush();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Algoritmo DDA (Digital differential analyzer)");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 640, 0, 480);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
