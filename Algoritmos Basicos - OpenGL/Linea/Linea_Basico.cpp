/*
 * Nombre: Algoritmo básico de la línea
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

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		float m = ((float)y2 - (float)y1) / ((float)x2 - (float)x1);
		float y;
		for(int x = x1; x <= x2; x++){
			y = m * (x - (float)x1) + (float)y1;
			glVertex2i(x, ceil(y));
		}
	glEnd();
	glFlush();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Algoritmo basico de la linea");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 640, 0, 480);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
