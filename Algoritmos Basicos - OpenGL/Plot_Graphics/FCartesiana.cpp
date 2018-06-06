/*
 * Nombre: Funcion cartesiana
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

	float x = 0;
	float y;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		while (x <= 1){
			y = 1 - pow(x, 3);
			glVertex2f(x, y);
			x += 0.0001;
		}
	glEnd();
	glFlush();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Funcion cartesiana");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1, 0, 1);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
