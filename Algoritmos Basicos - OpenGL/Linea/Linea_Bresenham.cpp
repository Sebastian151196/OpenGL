/*
 * Nombre: Algoritmo del punto medio para la recta (Bresenham)
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
		int dx = x2 - x1;
		int dy = y2 - y1;
		int d = 2 * dy - dx;
		int dE = 2 * dy;
		int dNE = 2 * (dy - dx);
		int x = x1;
		int y = y1;
		while (x <= x2){
			if (d <= 0){
				d = d + dE;
			}else{
				d = d + dNE;
				y++;
			}
			x++;
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
	glutCreateWindow("Algoritmo punto medio para la recta");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 640, 0, 480);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
