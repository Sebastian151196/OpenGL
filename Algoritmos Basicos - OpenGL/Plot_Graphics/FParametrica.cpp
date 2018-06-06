/*
 * Nombre: Funcion parametrica
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

	int K = 5;
	double t = 0;

	double x;
	double y;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		while (t <= 1){
			x = 1 - (1 - sin(t * M_PI / 2));
			y = (cos((2 * K - 1) * t * M_PI) + 2 * t + 4 * K * (1 - t) - 1) / (4 * K);
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
	glutCreateWindow("Funcion parametrica");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1, 0, 1);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
