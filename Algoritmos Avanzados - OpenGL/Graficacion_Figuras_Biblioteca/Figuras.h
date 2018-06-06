/*
 * Nombre: Figuras
 *
 * Autor: Sebastian Marroquin
 */

#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int signo(int num);
void linea(int x1, int y1, int x2, int y2);
void cuadrilatero(int base, int altura);
void triangulo(int lado);
void trapezio(int bMayor, int altura);
void paralelogramo(int base, int altura);
void poligono(int perimetro, int lados);

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

void cuadrilatero(int base, int altura){

	int x = 320 - (base / 2);
	int y = 320 + (altura / 2);
	int xx;
	int yy;

	float angulo = 0;

	xx = x + (int)((float)base * cos(angulo));
	yy = y - (int)((float)base * sin(angulo));
	linea(xx, yy, x, y);
	x = xx;
	y = yy;

	angulo += (90) * M_PI / 180;
	xx = x + (int)((float)altura * cos(angulo));
	yy = y - (int)((float)altura * sin(angulo));
	linea(xx, yy, x, y);
	x = xx;
	y = yy;

	angulo += (90) * M_PI / 180;
	xx = x + (int)((float)base * cos(angulo));
	yy = y - (int)((float)base * sin(angulo));
	linea(xx, yy, x, y);
	x = xx;
	y = yy;

	angulo += (90) * M_PI / 180;
	xx = x + (int)((float)altura * cos(angulo));
	yy = y - (int)((float)altura * sin(angulo));
	linea(xx, yy, x, y);
	x = xx;
	y = yy;

}

void triangulo(int lado){
	int x = 320 - (lado / 2);
	int y = 320 - (lado / 2);
	int xx;
	int yy;

	float angulo = 0;

	xx = x + (int)((float)lado * cos(angulo));
	yy = y - (int)((float)lado * sin(angulo));
	linea(xx, yy, x, y);
	x = xx;
	y = yy;

	angulo += (-120) * M_PI / 180;
	xx = x + (int)(lado * cos(angulo));
	yy = y - (int)(lado * sin(angulo));
	linea(xx, yy, x, y);
	x = xx;
	y = yy;

	angulo += (-120) * M_PI / 180;
	xx = x + (int)(lado * cos(angulo));
	yy = y - (int)(lado * sin(angulo));
	linea(xx, yy, x, y);
	x = xx;
	y = yy;
}

void trapezio(int bMayor, int altura){
	float bMenor = (bMayor * 80) / 100;
	int x = 320 - (bMayor / 2);
	int y = 320 - (altura / 2);
	int xx = x + bMayor;
	int yy = y;

	linea(xx, yy, x, y);

	float b = (bMayor * 10) / 100;
	int x1 = xx - b; 
	int y1 = y + altura;
	int x2 = x + b; 
	int y2 = y + altura;

	linea(x1, y1, x2, y2);
	linea(x1, y1, xx, yy);
	linea(x, y, x2, y2);
}

void paralelogramo(int base, int altura){
	float h =  sin(M_PI * 90 / 180) * altura / sin(M_PI * 45 / 180);
	float angulo = -45 * M_PI / 180;
	float d = base / 2;
	int x = 320 - (d + (h / 2 * cos(angulo)));
	int y = 320 - (altura / 2);
	int xx;
	int yy;

	angulo = 0;

	xx = x + (int)((float)base * cos(angulo));
	yy = y - (int)((float)base * sin(angulo));
	linea(xx, yy, x, y);
	x = xx;
	y = yy;

	angulo += (-45) * M_PI / 180;
	xx = x + (int)((float)h * cos(angulo));
	yy = y - (int)((float)h * sin(angulo));
	linea(xx, yy, x, y);
	x = xx;
	y = yy;

	angulo += (-135) * M_PI / 180;
	xx = x + (int)((float)base * cos(angulo));
	yy = y - (int)((float)base * sin(angulo));
	linea(xx, yy, x, y);
	x = xx;
	y = yy;

	angulo += (-45) * M_PI / 180;
	xx = x + (int)((float)h * cos(angulo));
	yy = y - (int)((float)h * sin(angulo));
	linea(xx, yy, x, y);
	x = xx;
	y = yy;
}

void poligono(int perimetro, int lados){
	float medidaL = perimetro / lados;
	int x = 320 - (medidaL / 2);
	int y = 320 - (((lados - 2) * 180 / lados) / 2) * ((medidaL / 2) / 
			(180 - 90 - ((lados - 2) * 180 / lados) / 2));
	int xx;
	int yy;

	float a = 180 - ((lados - 2) * 180 / lados);
	float angulo = 0;

	for (int i = 0; i < lados; i++){
		if (i == 0) {
			xx = x + (int)((float)medidaL * cos(angulo));
			yy = y - (int)((float)medidaL * sin(angulo));
			linea(xx, yy, x, y);
			x = xx;
			y = yy;
		} else {
			angulo += (-a) * M_PI / 180;
			xx = x + (int)((float)medidaL * cos(angulo));
			yy = y - (int)((float)medidaL * sin(angulo));
			linea(xx, yy, x, y);
			x = xx;
			y = yy;
		}
	}
}
