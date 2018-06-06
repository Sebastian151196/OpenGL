#include <stdio.h>
#include "math.h"
#include <GL/glut.h>

void initGL(){
    
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    return;
}

void MidPointLine(float x1, float y1, float x2, float y2){
    
    int aux = 0;
    int aux2 = 0;
    
    if(x1 > x2){
        int xf = x1;
        int yf = y1;
        
        x1 = x2;
        y1 = y2;
        x2 = xf;
        y2 = yf;
    }
    
    if((y2 - y1) / (x2 - x1) > 1 || (y2 - y1) / (x2 - x1) < -1){
        
        if(y1 > y2){
            aux2 = 1;
            int xfd = x1;
            int yfd = y1;
            
            x1 = x2;
            y1 = y2;
            
            x2 = xfd;
            y2 = yfd;
        }
        
        int cg=x1;
        
        x1=y1;
        y1=cg;
        
        cg=x2;
        
        x2=y2;
        y2=cg;
        
        aux = 1;
        
    }
    
    //Declaramos los angulos theta (x, y)
    
    int thetaX = x2 - x1;
    int thetaY = y2 - y1;


    int incremento = 1;
    if (y2 - y1 < 0 || aux2 == 1)
    {
    
        incremento = -1;
        thetaY = thetaY * -1;
        
    }

    int theta = 2 * thetaY - thetaX;
    int thetaE = 2 * thetaY; //Escogemos el pixel si es que esta en E
    int thetaNE = 2 * (thetaY-thetaX); //Escogemos el pixel si esta en el NE
    
    int x = 0;
    int y = 0;
    
    int maxIte = x2 - x1; //Numero maximo de interaciones

    glBegin(GL_POINTS); //Colocamos los puntos
    glColor3f(1.0f, 0.5f, 1.0f); //
    
    if( aux2 == 1 && aux == 1){
        
        glVertex2s(incremento * y + y1, x1 + x); 
        
    } else if(aux == 1){
        
        glVertex2s(y1 + y, incremento * x1 + x);
    
        
    } else{
        
        glVertex2s(x1 + x, incremento * y + y1);
        
    }
    
    printf("Los puntos son: %f, %f\n", incremento * y + y1, x1 + x);
    
    
    for(x ; x <= maxIte; x++){
        
        if(theta <= 0){
            theta = theta + thetaE;
        }else{
            y = y + 1;
            theta = theta + thetaNE;
        }
        
        if(aux2 == 1 && aux == 1){
            glVertex2s(incremento * y + y1, x1 + x);
        
            
        } else if(aux == 1){
            
            printf("2fff\n");
            glVertex2s(y1 + y, incremento * x1 + x);
            
        }else{
            
            glVertex2s(x1 + x, incremento * y + y1);
            
        }
        
    }
    
    glEnd();
    glFlush();
    return;
    
}

void Figura(){
    
    int i; 
    
    int x1 = 100;
    int y1 = 100;
    
    int x2 = x1;
    int y2 = y1;
    
    for(i = 0; i < 10; i++){
        
        x2 += 30;
        
        if(i % 2 == 0){
            
            y2 += 30;
            
        } else{
            
            y2 -= 30;
            
        }
        
        MidPointLine(x1, y1, x2, y2);
        
        x1 = x2;
        y1 = y2;
        
    }
    
    x2 = x1;
    y2 = y2;
    
    for(i = 0; i < 10; i++){
    
        y2 += 30;
        
        if(i % 2 == 0){
            
            x2 += 30;
            
        } else {
            
            x2 -= 30;
            
        }
        
        MidPointLine(x1, y1, x2, y2);
        
        x1 = x2;
        y1 = y2;
    }
    
    x2 = x1;
    y2 = y2;
    
    for (i = 0; i < 10; i++){ 
      
        x2 -= 30;
        
        if (i % 2 == 0){
        
            y2 -= 30;
       
        } else{
       
            y2 += 30;
        }
     
        MidPointLine(x1, y1, x2, y2);
        
        x1 = x2;
        y1 = y2;
   }

    x2=x1;
    y2=y2;
    
    for (i = 0; i < 10; i++){ 
      
        y2 -= 30;
        if (i % 2 == 0){
        
            x2 -= 30;
       
        } else{
       
            x2 += 30;
        }
        
        MidPointLine(x1, y1, x2, y2);
        
        x1 = x2;
        y1 = y2;
   }
 
    
    return;
       
    
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glClear(GL_COLOR_BUFFER_BIT); 
    glutCreateWindow("Figura :-)");
   	initGL();
    
    glutDisplayFunc(Figura);
    glutMainLoop();
    return 0;
}

