/*
 * Nombre: Animación
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

class Color{
public:
	int r;
	int g;
	int b;
	void setColorPixel(int r, int g, int b);
	void getColorPixel(int x, int y);
};

void Color::setColorPixel(int nr, int ng, int nb){
	r = nr;
	g = ng;
	b = nb;
}

void Color::getColorPixel(int x, int y){
	unsigned char pixel[4];
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
	r = (int)pixel[0]/255;
	g = (int)pixel[1]/255;
	b = (int)pixel[2]/255;
	cout << r << endl;
	cout << g << endl;
	cout << b << endl;
}

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

int pixel(int x, int y, Color old){
	unsigned char pixel[4];
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

	int r, g, b;
	r = (int)pixel[0]/255;
	g = (int)pixel[1]/255;
	b = (int)pixel[2]/255;

	if (r == old.r && g == old.g && b == old.b) {
		return 1;
	} else {
		return 0;
	}
}

void changeColor(int x, int y, Color nw){
	
	glBegin(GL_POINTS);
	glColor3f(nw.r, nw.g, nw.b);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void flooding4(int x, int y, Color old, Color nw){
	int p = pixel(x, y, old);
	if (p) {
		changeColor(x, y, nw);
		flooding4(x + 1, y, old, nw);
		flooding4(x, y - 1, old, nw);
		flooding4(x - 1, y, old, nw);
		flooding4(x, y + 1, old, nw);
	}
}

void TrazarFigura(Color nw, int tx, int ty, int s){

	glColor3f(nw.r, nw.g, nw.b);

	linea((100 + -50 + tx) * s, (100 + -30 + ty) * s, (100 + -40 + tx) * s, (100 + -50 + ty) * s);
	linea((100 + -40 + tx) * s, (100 + -50 + ty) * s, (100 + -30 + tx) * s, (100 + -70 + ty) * s);
	linea((100 + -30 + tx) * s, (100 + -70 + ty) * s, (100 + -30 + tx) * s, (100 + -60 + ty) * s);
	linea((100 + -30 + tx) * s, (100 + -60 + ty) * s, (100 + -20 + tx) * s, (100 + -40 + ty) * s);
	linea((100 + -20 + tx) * s, (100 + -40 + ty) * s, (100 + -10 + tx) * s, (100 + 0 + ty) * s);

	linea((100 + -70 + tx) * s, (100 + 10 + ty) * s,(100 + -80 + tx) * s,(100 + 40 + ty) * s);
	linea((100 + -80 + tx) * s, (100 + 40 + ty) * s,(100 + -90 + tx) * s,(100 + 70 + ty) * s);
	linea((100 + -90 + tx) * s, (100 + 70 + ty) * s,(100 + -80 + tx) * s,(100 + 100 + ty) * s);
	linea((100 + -80 + tx) * s, (100 + 100 + ty) * s,(100 + -70 + tx) * s,(100 + 100 + ty) * s);
	linea((100 + -70 + tx) * s, (100 + 100 + ty) * s,(100 + -50 + tx) * s,(100 + 90 + ty) * s);
	linea((100 + -50 + tx) * s, (100 + 90 + ty) * s,(100 + -30 + tx) * s,(100 + 70 + ty) * s);
	linea((100 + -30 + tx) * s, (100 + 70 + ty) * s,(100 + -20 + tx) * s,(100 + 60 + ty) * s);
	linea((100 + -20 + tx) * s, (100 + 60 + ty) * s,(100 + 0 + tx) * s,(100 + 70 + ty) * s);
	linea((100 + 0 + tx) * s, (100 + 70 + ty) * s,(100 + 20 + tx) * s,(100 + 60 + ty) * s);
	linea((100 + 20 + tx) * s, (100 + 60 + ty) * s,(100 + 30 + tx) * s,(100 + 70 + ty) * s);
	linea((100 + 30 + tx) * s, (100 + 70 + ty) * s,(100 + 50 + tx) * s,(100 + 90 + ty) * s);
	linea((100 + 50 + tx) * s, (100 + 90 + ty) * s,(100 + 70 + tx) * s,(100 + 100 + ty) * s);
	linea((100 + 70 + tx) * s, (100 + 100 + ty) * s,(100 + 80 + tx) * s,(100 + 100 + ty) * s);
	linea((100 + 80 + tx) * s, (100 + 100 + ty) * s,(100 + 90 + tx) * s,(100 + 70 + ty) * s);
	linea((100 + 90 + tx) * s, (100 + 70 + ty) * s,(100 + 80 + tx) * s,(100 + 40 + ty) * s);
	linea((100 + 80 + tx) * s, (100 + 40 + ty) * s,(100 + 70 + tx) * s,(100 + 10 + ty) * s);
	linea((100 + 70 + tx) * s, (100 + 10 + ty) * s,(100 + 30 + tx) * s,(100 + 40 + ty) * s);
	linea((100 + 30 + tx) * s, (100 + 40 + ty) * s,(100 + 0 + tx) * s,(100 + 10 + ty) * s);
	linea((100 + 0 + tx) * s, (100 + 10 + ty) * s,(100 + -30 + tx) * s,(100 + 40 + ty) * s);
	linea((100 + -30 + tx) * s, (100 + 40 + ty) * s,(100 + -70 + tx) * s,(100 + 10 + ty) * s);

	linea((100 +-50 + tx) * s,(100 + 0 + ty) * s,(100 + -40 + tx) * s,(100 + 0 + ty) * s);
	linea((100 +-40 + tx) * s,(100 + 0 + ty) * s,(100 + -20 + tx) * s,(100 + -10 + ty) * s);
	linea((100 +-20 + tx) * s,(100 + -10 + ty) * s,(100 + -40 + tx) * s,(100 + -10 + ty) * s);
	linea((100 +-40 + tx) * s,(100 + -10 + ty) * s,(100 + -50 + tx) * s,(100 + 0 + ty) * s);

	linea((100 +50 + tx) * s,(100 + -30 + ty) * s,(100 + 40 + tx) * s,(100 + -50 + ty) * s);
	linea((100 +40 + tx) * s,(100 + -50 + ty) * s,(100 + 30 + tx) * s,(100 + -70 + ty) * s);

	linea((100 +70 + tx) * s,(100 + 10 + ty) * s,(100 + 80 + tx) * s,(100 + -30 + ty) * s);
	linea((100 +80 + tx) * s,(100 + -30 + ty) * s,(100 + 90 + tx) * s,(100 + -70 + ty) * s);
	linea((100 +90 + tx) * s,(100 + -70 + ty) * s,(100 + 80 + tx) * s,(100 + -70 + ty) * s);
	linea((100 +80 + tx) * s,(100 + -70 + ty) * s,(100 + 70 + tx) * s,(100 + -60 + ty) * s);
	linea((100 +70 + tx) * s,(100 + -60 + ty) * s,(100 + 40 + tx) * s,(100 + -90 + ty) * s);
	linea((100 +40 + tx) * s,(100 + -90 + ty) * s,(100 + 10 + tx) * s,(100 + -100 + ty) * s);
	linea((100 +10 + tx) * s,(100 + -100 + ty) * s,(100 + -10 + tx) * s,(100 + -100 + ty) * s);
	linea((100 +-10 + tx) * s,(100 + -100 + ty) * s,(100 + -40 + tx) * s,(100 + -90 + ty) * s);
	linea((100 +-40 + tx) * s,(100 + -90 + ty) * s,(100 + -70 + tx) * s,(100 + -60 + ty) * s);
	linea((100 +-70 + tx) * s,(100 + -60 + ty) * s,(100 + -80 + tx) * s,(100 + -70 + ty) * s);
	linea((100 +-80 + tx) * s,(100 + -70 + ty) * s,(100 + -90 + tx) * s,(100 + -60 + ty) * s);
	linea((100 +-90 + tx) * s,(100 + -60 + ty) * s,(100 + -80 + tx) * s,(100 + -20 + ty) * s);
	linea((100 +-80 + tx) * s,(100 + -20 + ty) * s,(100 + -70 + tx) * s,(100 + 10 + ty) * s);

	linea((100 +50 + tx) * s,(100 + 0 + ty) * s,(100 + 40 + tx) * s,(100 + -10 + ty) * s);
	linea((100 +40 + tx) * s,(100 + -10 + ty) * s,(100 + 20 + tx) * s,(100 + -10 + ty) * s);
	linea((100 +20 + tx) * s,(100 + -10 + ty) * s,(100 + 40 + tx) * s,(100 + 0 + ty) * s);
	linea((100 +40 + tx) * s,(100 + 0 + ty) * s,(100 + 50 + tx) * s,(100 + 0 + ty) * s);

	linea((100 +10 + tx) * s,(100 + 0 + ty) * s,(100 + 20 + tx) * s,(100 + -40 + ty) * s);
	linea((100 +20 + tx) * s,(100 + -40 + ty) * s,(100 + 30 + tx) * s,(100 + -60 + ty) * s);
	linea((100 +30 + tx) * s,(100 + -60 + ty) * s,(100 + 30 + tx) * s,(100 + -70 + ty) * s);
	linea((100 +30 + tx) * s,(100 + -70 + ty) * s,(100 + 10 + tx) * s,(100 + -80 + ty) * s);

	linea((100 +-40 + tx) * s,(100 + -10 + ty) * s,(100 + -40 + tx) * s,(100 + 0 + ty) * s);
	linea((100 +-40 + tx) * s,(100 + 0 + ty) * s,(100 + -30 + tx) * s,(100 + -10 + ty) * s);

	linea((100 +-30 + tx) * s,(100 + -70 + ty) * s,(100 + -10 + tx) * s,(100 + -80 + ty) * s);
	linea((100 +-10 + tx) * s,(100 + -80 + ty) * s,(100 + 10 + tx) * s,(100 + -80 + ty) * s);
	linea((100 +10 + tx) * s,(100 + -80 + ty) * s,(100 + 20 + tx) * s,(100 + -60 + ty) * s);
	linea((100 +20 + tx) * s,(100 + -60 + ty) * s,(100 + 10 + tx) * s,(100 + -50 + ty) * s);
	linea((100 +10 + tx) * s,(100 + -50 + ty) * s,(100 + -10 + tx) * s,(100 + -50 + ty) * s);
	linea((100 +-10 + tx) * s,(100 + -50 + ty) * s,(100 + -20 + tx) * s,(100 + -60 + ty) * s);
	linea((100 +-20 + tx) * s,(100 + -60 + ty) * s,(100 + -10 + tx) * s,(100 + -80 + ty) * s);

	linea((100 +40 + tx) * s,(100 + 60 + ty) * s,(100 + 70 + tx) * s,(100 + 90 + ty) * s);
	linea((100 +70 + tx) * s,(100 + 90 + ty) * s,(100 + 70 + tx) * s,(100 + 50 + ty) * s);
	linea((100 +70 + tx) * s,(100 + 50 + ty) * s,(100 + 60 + tx) * s,(100 + 40 + ty) * s);
	linea((100 +60 + tx) * s,(100 + 40 + ty) * s,(100 + 40 + tx) * s,(100 + 50 + ty) * s);
	linea((100 +40 + tx) * s,(100 + 50 + ty) * s,(100 + 40 + tx) * s,(100 + 60 + ty) * s);

	linea((100 +40 + tx) * s,(100 + -10 + ty) * s,(100 + 40 + tx) * s,(100 + 0 + ty) * s);
	linea((100 +40 + tx) * s,(100 + 0 + ty) * s,(100 + 30 + tx) * s,(100 + -10 + ty) * s);

	linea((100 +-70 + tx) * s,(100 + 40 + ty) * s,(100 + -70 + tx) * s,(100 + 90 + ty) * s);
	linea((100 +-70 + tx) * s,(100 + 90 + ty) * s,(100 + -40 + tx) * s,(100 + 60 + ty) * s);
	linea((100 +-40 + tx) * s,(100 + 60 + ty) * s,(100 + -40 + tx) * s,(100 + 50 + ty) * s);
	linea((100 +-40 + tx) * s,(100 + 50 + ty) * s,(100 + -60 + tx) * s,(100 + 30 + ty) * s);
	linea((100 +-60 + tx) * s,(100 + 30 + ty) * s,(100 + -70 + tx) * s,(100 + 40 + ty) * s);

}

void renderScene(void){

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	Color ini;
	Color old, nw;

	int x = 120;
	int y = 110;

	int tx = 0;
	int ty = 0;

	int s = 1;

	ini.setColorPixel(0, 0, 0);

	old.getColorPixel(x, y);
	
	nw.setColorPixel(0, 1, 1);

	TrazarFigura(ini, tx, ty, s);

	flooding4(x, y, old, nw);

	s = 2;

	tx = 100;

	x += tx;

	x = x * s;

	nw.setColorPixel(1, 0, 1);

	TrazarFigura(ini, tx, ty, s);

	flooding4(x, y, old, nw);
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(650, 500);
	glutCreateWindow("Animacion");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 650, 0, 500);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
