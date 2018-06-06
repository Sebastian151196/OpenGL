/*
 * Nombre: TryFiguras
 *
 * Autor: Sebastian Marroquin
 */

#include <iostream>
#include "Figuras.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

void renderScene(void){
	triangulo(300); //Debe de cambiar a la figura que desea (las unicas implementadas estan en el archivo Figuras.h)
	cuadrilatero(500, 350);
    //trapezio(300, 150);
}

int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);
	glutCreateWindow("TryFiguras");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 640, 0, 640);
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}
