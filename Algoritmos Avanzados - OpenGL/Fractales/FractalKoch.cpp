/*
 * Nombre: Fractal de Koch
 *
 * Autor: Sebastian Marroquin
 */

#include <iostream>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std; 

int num;

int signo(int num){

    int resultado;

	if (num<0) {
		resultado=-1;
	}

	if (num>0) {
       resultado=1;
	}

	if (num==0){
       resultado=0;
	}

	return(resultado);
}

void linea(int x1, int y1, int x2, int y2){
	float e,ax,ay,temp;

	int s1,s2,intercambio,i,x,y;

	x = x1;
	y = y1;
	ax = abs(x2 - x1);
	ay = abs(y2 - y1);
	s1 = signo(x2 - x1);
	s2 = signo(y2 - y1);

	if (ay > ax) {
		temp = ax;
		ax = ay;
		ay = temp;
		intercambio = 1;
   	} else {
		intercambio=0;
	}

	e=2*ay-ax;

	glBegin(GL_POINTS);
	for (i = 1; i <= ax; i++) {
		glVertex2i(x, y);
		if(e >= 0) {
			if (intercambio == 1) {
 				x = x + s1;
			} else {
				y = y + s2;
			}
			e = e - (2 * ax);
		}

		if (intercambio == 1) {
			y = y + s2;
		} else {
			x = x + s1;
		}
		e = e + 2 * ay;
	}
	glEnd();
	glFlush();
}

void koch(int x1, int y1, int x2, int y2, int n){
	if (n <= 0) {
		linea(x1, y1, x2, y2);
	} else {
		float sin60 = sin(M_PI/3);
		float dx = (float) (x2 - x1) / 3;
		float dy = (float) (y2 - y1) / 3;
		double x = x1 + 3 * dx / 2 - dy * sin60;
		double y = y1 + 3 * dy / 2 + dx * sin60;
		koch(x1, y1, x1+dx, y1+dy, n -1);
		koch(x1+dx, y1+dy, x, y, n -1);
		koch(x, y, x2-dx, y2-dy, n -1);
		koch(x2-dx, y2-dy, x2,y2, n -1);
	}
}

void renderScene(void){
	/*
	int x1 = 5;
	int y1 = 5;
	int x2 = 635;
	int y2 = 5;

	koch(x1, y1, x2, y2, num);
	*/

	int x1 = 120;
	int y1 = 440;
	int x2 = 520;
	int y2 = 440;
	int x3 = 320;
	int y3 = 40;

	koch(x1, y1, x2, y2, num);
	koch(x2, y2, x3, y3, num);
	koch(x3, y3, x1, y1, num);

}

int main(int argc, char *argv[]){

	int n;

	cout << "Ingrese el número de recursiones: " << endl;
	cin >> n;

	num = n;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Fractal de Koch");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 640, 0, 640);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
