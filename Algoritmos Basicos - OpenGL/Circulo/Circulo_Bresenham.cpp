/*
 * Nombre: Algoritmo de punto medio para circunferencias
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
	int y = r;
	int d = 1 - r;
	glBegin(GL_POINTS);
		do{
			glVertex2i(x, y);
			glVertex2i(x, -y);
			glVertex2i(-x, y);
			glVertex2i(-x, -y);
			glVertex2i(y, x);
			glVertex2i(y, -x);
			glVertex2i(-y, x);
			glVertex2i(-y, -x);
			if (d < 0){
				d = d + 2 * x + 3;
			}else{
				d = d + 2 * (x - y) + 5;
				y--;
			}
			x++;
		} while (x <= y); //Error en algoritmo
	glEnd();
	glFlush();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Algoritmo de punto medio para circunferencias");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-320, 320, -240, 240);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
