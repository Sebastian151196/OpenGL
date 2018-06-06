/*
 * Nombre: Fractal de Peano
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

int x = 0;
int y = 640 / 2;
float angulo = 0.0;

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

void peano(int d, int n){
	if (n <= 0) {
		int xx = x + (int)((float)d * cos(angulo));
		int yy = y - (int)((float)d * sin(angulo));
		linea(xx, yy, x, y);
		x = xx;
		y = yy;
	} else {
		peano((int)((float)d / 3), n - 1);
		angulo += (-90) * M_PI / 180;
		peano((int)((float)d / 3), n - 1);
		angulo += (90) * M_PI / 180;
		peano((int)((float)d / 3), n - 1);
		angulo += (90) * M_PI / 180;
		peano((int)((float)d / 3), n - 1);
		peano((int)((float)d / 3), n - 1);
		angulo += (90) * M_PI / 180;
		peano((int)((float)d / 3), n - 1);
		angulo += (90) * M_PI / 180;
		peano((int)((float)d / 3), n - 1);
		angulo += (90) * M_PI / 180;
		peano((int)((float)d / 3), n - 1);
		peano((int)((float)d / 3), n - 1);
	}
}

void renderScene(void){
	
	int d = 640;

	peano(d, num);

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
	glutCreateWindow("Fractal de Peano");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 640, 0, 640);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
