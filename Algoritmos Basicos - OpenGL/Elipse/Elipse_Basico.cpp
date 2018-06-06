/*
 * Nombre: Algoritmo básico de la elipse
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
	//Radios
	int rx = 200;
	int ry = 100;

	float x = 0;
	float y = (float)ry;
	int f = ry;
	glBegin(GL_POINTS);

		while (pow(ry, 2) * (int)x < pow(rx, 2) * f){
			glVertex2i(x, f);
			glVertex2i(x, -f);
			glVertex2i(-x, f);
			glVertex2i(-x, -f);
			x++;
			y = ((float)ry / (float)rx) * sqrt(pow((float)rx, 2) - pow(x, 2));
			f = ceil(y);
		}

		y = 0;
		x = (float)rx;
		f = rx;

		while (pow(ry, 2) * f >= pow(rx, 2) * (int)y){
			glVertex2i(f, y);
			glVertex2i(f, -y);
			glVertex2i(-f, y);
			glVertex2i(-f, -y);
			y++;
			x = ((float)rx / (float)ry) * sqrt(pow((float)ry, 2) - pow(y, 2));
			f = ceil(x); //Error en algoritmo
		}

	glEnd();
	glFlush();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Algoritmo basico de la elipse");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-320, 320, -240, 240);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
