/*
 * Nombre: Algoritmo de punto medio para la elipse
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

	int x = 0;
	int y = ry;
	float d = pow((float)ry, 2) - pow((float)rx, 2) * (float)ry +
			  (1 / 4) * pow((float)rx, 2);

	glBegin(GL_POINTS);

		do {
			glVertex2i(x, y);
			glVertex2i(x, -y);
			glVertex2i(-x, y);
			glVertex2i(-x, -y);
			if (d < 0){
				d = d + pow((float)ry, 2) * (2 * (float)x + 1); //E
			}else{
				d = d + pow((float)ry, 2) * (2 * (float)x + 3) +
				    2 * pow((float)rx, 2) * (1 - (float)y); //SE
				    y--;
			}
			x++;
		} while (pow(ry,2) * x < pow(rx,2) * y);

		x = rx;
		y = 0;
		d = pow((float)rx, 2) - (float)rx * pow((float)ry, 2) +
			(1 / 4) * pow((float)ry, 2);

		do {
			glVertex2i(x, y);
			glVertex2i(x, -y);
			glVertex2i(-x, y);
			glVertex2i(-x, -y);
			if (d < 0){
				d = d + pow((float)rx, 2) * (2 * (float)y + 3); //E
			}else{
				d = d + pow((float)rx, 2) * (2 * (float)y + 3) +
				    2 * pow((float)ry, 2) * (1 - (float)x);//SE
				    x--;
			}
			y++;

		} while (pow(ry,2) * x >= pow(rx,2) * y);

	glEnd();
	glFlush();
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Algoritmo de punto medio para la elipse");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-320, 320, -240, 240);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
