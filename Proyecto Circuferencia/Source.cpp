#include <GL/glut.h>
#include <math.h>     //Librerias a usar
#include <stdlib.h>

int Alto = 500, Ancho = 500; //tamaño de la pantalla
double a, b, x, y;

void pintaPixel(int x, int y, int r, int g, int b)
{
	glPointSize(3);
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glutSwapBuffers();
}

void pintaCirculo()
{
	double r, cirx, ciry;

	r = sqrt(pow(x - a, 2) + pow(y - b, 2)); //Ecuacion para la distancia entre circulos
	cirx = a;
	while (cirx < r)
	{
		ciry = sqrt(pow(r, 2) - pow(cirx, 2));
		//Ecuacion de la circunferencia (x-h) ʌ2 y  (y-k) ʌ2=rʌ2

		//Division de las regiones
		pintaPixel(ciry + x, ciry + y, 0, 0, 1);
		pintaPixel(ciry + x, cirx + y, 0, 0, 1);
		//Region ++ (x,y)
		pintaPixel(-cirx + x, -ciry + y, 0, 0, 1);
		pintaPixel(-ciry + x, -cirx + y, 0, 0, 1);
		//Region -+ (-x,y)
		pintaPixel(-cirx + x, -ciry + y, 0, 0, 1);
		pintaPixel(-ciry + x, -cirx + y, 0, 0, 1);
		//Region --(-x,-y)
		pintaPixel(cirx + x, -ciry + y, 0, 0, 1);
		pintaPixel(ciry + x, -cirx + y, 0, 0, 1);
		//Region +- (x,-y)
		cirx++;
	}

}

void raton(int btn, int state, int x1, int y1)
{
	y1 = Alto / 2 - y1;
	x1 = x1 - Ancho / 2;

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)//SE CREA EL PUNTO MEDIO LA IGUAL SE DEFINE EL CLICK
		//Por el cual se define el centro del circulo

	{
		a = x1;
		b = y1;
	}
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)//Esto equivale a donde partira el punto de referencia
	{
		x = x1;
		y = 1;
		pintaCirculo();

	}
}

void ejes()
{
	for (int i = -Ancho; i <= Ancho; i++)//En esta funcion se van a pintar los ejes X & Y para que de ahi parta el circulo
	{
		pintaPixel(i, 0, 0, 0, 0);
	}
	for (int j = -Alto; j <= Alto; j++)
	{
		pintaPixel(0, j, 0, 0, 0);

	}
	glutMouseFunc(raton);
	glFlush();

}

int main(int argc, char* arh[])
{
	glutInit(&argc, arh);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(Alto, Ancho);
	glutCreateWindow("Circulo XD");
	gluOrtho2D(-Ancho / 2, Ancho / 2, -Alto / 2, Alto / 2);
	glClearColor(1, 1, 1, 1);
	glutDisplayFunc(ejes);
	glutMainLoop();
	return 0;
}