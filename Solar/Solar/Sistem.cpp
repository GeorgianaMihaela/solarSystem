#include <windows.h>
#include "Sistem.h"
#include <stdio.h>
#include <stdlib.h>
#include <gl.h>
#include <glu.h>
#include <glut.h>


GLenum invart=GL_TRUE;
GLenum manual=GL_FALSE;

// variabile ce controleaza viteza de rotire
float ora=0.0;
float zi=0.0;
float pas=24.0; // pasul de timp pt animatie (ore)

// pentru deplasarea pe axa Oz
 GLfloat z = 90;

// glutKeyboardFunc este apelata atunci cand se apasa 
// tastele normale
void KeyPressFunc(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'r': Key_r();
		break;
	case 's': Key_s();
		break;
	case 'z' : Key_z();
		break;
	case 'x' : Key_x();
		break;
	case 27: exit(1); // tasta escape
	}
}

// glutSpecialKey este apelata atunci se apasa o
// tasta speciala, cum ar fi sagetile
void SpecialKeyFunc(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP: Key_up();
		break;
	case GLUT_KEY_DOWN: Key_down();
		break;
	}
}

void Key_r()
{
	if(manual) // daca iesim de pe rotirea manuala
	{
		manual=GL_FALSE;
		invart=GL_TRUE; // reincepem animatia
	}
	else
		invart=!invart; // pornim sau oprim animatia
}

void Key_s()
{
	manual=GL_TRUE;
	invart=GL_TRUE;
}

void Key_z()
{
	z++;
	if(z>=91) // sa nu se duca foarte in spate
		z=90;
}
void Key_x()
{
	z--;
	if(z<=10) // sa nu se duca foarte in fata
		z=11;
}
void Key_up()
{
	// dubleaza viteza de rotire
	pas*=2.0;
}

void Key_down()
{
	// injumatateste viteza de rotire
	pas/=2.0;
}


// Modificadim() e apelata cand se redimensioneaza fereastra
void ModificaDim(int w, int h)
{
	float ratio;
	// prevenim impartirea la 0
	if(h==0)
		h=1;
	
	glViewport(0, 0, w, h);
	ratio=(float)w/(float)h;

	// setam matricea de proiectie (folosim proiectia perspectiva)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, ratio, 1.0, 425.0);

	glMatrixMode(GL_MODELVIEW);
}

// Rotatie() se ocupa de invartirea planetelor si redesenarea scenei

void Rotatie()
{
	// stergem ecranul
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	if(invart)
	{
		// actualizam miscarea
	
		ora+=pas/24.0f;
		zi+=pas/24.0f;

		ora = ora - ((int)(ora/24))*24;
        zi = zi - ((int)(zi/365))*365;

	}

	glMatrixMode(GL_MODELVIEW);
	// stergem matricea curenta (Modelview)
	glLoadIdentity();
	// inapoi 8 unitati pt a privi din origine
	
	glTranslatef(0.0, 0.0, -z);
	//glTranslatef(0.0, 0.0, -300);

	// ne rotim in jurul axei Ox cu 15 grade
	glRotatef(15.0, 1.0, 0.0, 0.0);
	
	glPushMatrix();

	// soarele
	glColor3f(0.85f, 0.85f, 0.10f);
	//glutWireSphere(1.0, 15, 15);
	glutSolidSphere(5.0, 15, 15);
	

	glPushMatrix();	
	// mercur

	glRotatef((360.0f*(3*zi/365.0f)), 0.0f, 1.0f, 0.0f);
	
	
	glTranslatef(15.0, 0.0, 0.0);
	glColor3f(0.55f, 0.13f, 0.13f);
	//glutWireSphere(0.2, 10, 10);
	glutSolidSphere(1, 10, 10);

	glPopMatrix();

	// venus 
	glPushMatrix();
	
	glRotatef(360.0f*2*zi/365.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(20.0, 0.0, 0.0);
	glColor3f(0.65f, 0.49f, 0.24f);
	glutSolidSphere(1.5, 10, 10);
	//glutWireSphere(0.3, 10, 10);
	glPopMatrix();

	
	// marte 
	glPushMatrix();
	
	glRotatef(360.0f*4*zi/365.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(30.0, 0.0, 0.0);
	glColor3f(0.30f, 0.18f, 0.18f);
    //glutWireSphere(0.3, 10, 10);
	glutSolidSphere(2.5, 10, 10);
	glPopMatrix();

	
	
	glRotatef(360.0f*5*zi/365.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(40.0, 0.0, 0.0);
	glColor3f(0.55f, 0.13f, 0.41f);
    //glutWireSphere(0.5, 10, 10);
	glutSolidSphere(4, 10, 10);
	glPopMatrix();

	// pamantul
	// il pozitionam in jurul soarelui
	// folosim zi pt a afla pozitia
	glRotatef(360.0f*zi/365.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(25.0, 0.0, 0.0);
	// salvam starea matricii
	glPushMatrix();

	// rotim pamantul in jurul axei sale
	// folosim ora sa aflam cum se roteste
	glRotatef(360.0f*ora/24.0f, 0.0f, 1.0f, 0.0f);

	// desenam pamantul
	glColor3f(0.2f, 0.2f, 1.0f);
	//glutWireSphere(0.4, 10, 10);
	glutSolidSphere(2, 10, 10);

	// restauram starea matricei
	glPopMatrix();

	// luna
	// folosim zi pt a controla rotirea in jurul pamantului
	glRotatef(360.0f*12.0f*zi/365.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(5.7f, 0.0f, 0.0f);
	glColor3f(0.90f, 0.90f, 0.98f);
	//glutWireSphere(0.1, 5, 5);
	glutSolidSphere(0.8, 5, 5);

	glFlush();
	glutSwapBuffers();

	if(manual)
		invart=GL_FALSE;

	// avem nevoie de redesenare pt ca e animatie
	glutPostRedisplay();
}

// initializam modul de randare al OpenGL

void OpenGLInit()
{
	// valori pentru lumina 
	GLfloat  dimLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat  sourceLight[] = { 0.65f, 0.65f, 0.65f, 1.0f };
	GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	// variabile lumina
	glEnable(GL_DEPTH_TEST);	// testul de adancime
	glFrontFace(GL_CCW);	//	
	glEnable(GL_CULL_FACE);		

	// activam lumina
	glEnable(GL_LIGHTING);

	// Sursa de lumina 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, dimLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	// activam color tracking
	glEnable(GL_COLOR_MATERIAL);
	
	// setam proprietatile matrialului cum sa reflecte lumina
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// background
	glShadeModel(GL_SMOOTH);
	glClearColor(0.18f, 0.18f, 0.3f, 1.0f );

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	// double buffer pt animatie
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// facem si pozitionam fereastra
	glutInitWindowPosition(0,0);
	glutInitWindowSize(800,650);
	glutCreateWindow("Planete");

	OpenGLInit();

	
	// setam functiile callback pt taste
	glutKeyboardFunc(KeyPressFunc);
	glutSpecialFunc(SpecialKeyFunc);

	// pt redim fereastra
	glutReshapeFunc(ModificaDim);

	// pt redesenarea imaginii
	glutDisplayFunc(Rotatie);

	glutMainLoop();
	return(0);
}
