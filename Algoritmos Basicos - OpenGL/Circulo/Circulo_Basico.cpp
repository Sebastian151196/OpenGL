/*
 * Nombre: Algoritmo básico de circunferencias
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
	
	glClear(GL_COLOR_BUFFER_BIT);
	//Radio
	int r = 200;
	int x = 0;
	float y = (float)r;
	int z = r;
	glBegin(GL_POINTS);
		while (x <= z){
			glVertex2i(x, z);
			glVertex2i(x, -z);
			glVertex2i(-x, z);
			glVertex2i(-x, -z);
			glVertex2i(z, x);
			glVertex2i(z, -x);
			glVertex2i(-z, x);
			glVertex2i(-z, -x);
			x++;
			y = sqrt((float)pow(r,2) - (float)pow(x,2));
			z = (int)ceil(y);
		}
	glEnd();
	glFlush();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Algoritmo basico de circunferencias");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-320, 320, -240, 240);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
