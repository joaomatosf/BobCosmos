/* solar.c

 BobCosmos: The Solar System written in C + OpenGL + glut
 https://github.com/joaomatosf/bobcosmos

 Copyright 2008 João Filho Matos Figueiredo

 This project was written in the year 2008 when
 I was still a student of Computer Science at
 the Federal University of Paraíba.


 Sistema Solar 3D, usando OpenGL e Freeglut
 Computacao Grafica - Joao Filho Matos Figueiredo - 10621020
 Licença: Creative Commons
 www.joaomatosf.com


apt-get install freeglut3-dev
gcc -c texture.c
gcc -o solar solar.c texture.o -lglut -lGLU -lGL -lm

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
      http://www.apache.org/licenses/LICENSE-2.0
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/


#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include "texture.h"

GLuint textura[10];

int rodaX = 0;
int rodaY = 0;
int rodaZ = 0;
float zoom = -90;
int rotacionaX = 0;
int rotacionaY = 0;
float moveX =0;
float moveY =0;
int movimento = 1;
GLuint planetas[8];
GLuint orbitas =0;
GLuint eixos=0;
//int moveZ =0;
int maisInf = -1;





//============================================================================//
// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (float r, float g, float b)
{

	GLfloat luzAmbiente[4]={r,g,b,1.0};
	GLfloat luzDifusa[4]={r,g,b,1.0};	   // "cor"
	GLfloat luzEspecular[4]={r, g, b, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 0.0, 0.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 10;

	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);


	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
//FIM DE FUNCAO
//============================================================================//


//============================================================================//
//desenha todo sistema solar... ainda preciso organizar...
void meuObjeto(void)
{

	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	double a = t; //*10.0;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glTranslated(0, 0, zoom);
	glTranslated(moveX, 0, 0);
	glTranslated(0, moveY, 0);




	glRotated(-70, 1, 0, 0);

	glRotated(rodaX, 1, 0, 0);
	glRotated(rodaY, 0, 1, 0);
	glRotated(rodaZ, 0, 0, 1);


	//Desenha o Sol
	GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textura[0]);
	glPushMatrix();
	glRotated(30*a, 0, 0, 1);
	gluSphere(qobj,1.39,25,25);
	glPopMatrix();
	//gluDeleteQuadric(qobj);
	glDisable(GL_TEXTURE_2D);

	int i;
	float angulo;

	//Desenha orbitas dos planetas
	glCallList(orbitas);


	//mercurio
	glPushMatrix();
	glRasterPos2f(0,-1.9);
		glutBitmapString(GLUT_BITMAP_9_BY_15, "Mercurio");
	glTranslated(0, -1.9, 0);
	//translação do planeta
	if(movimento ==1)
		glTranslatef((2.3 * cos(2.0 * 3.14 * a*3.7 / 100)),(1.9 +1.9 * sin(2.0 * 3.14 * a*3.7 / 100)), 0);
//glRasterPos2f((2.3 * cos(2.0 * 3.14 * a*3.7 / 100)),(1.9 +1.9 * sin(2.0 * 3.14 * a*3.7 / 100)));

	//rotação do planeta
	glRotated(-20*a, 0, 0, 1);
	glCallList(planetas[1]);
	glPopMatrix();



	//venus
	glPushMatrix();
	glRasterPos2f(0,-2.8);
		glutBitmapString(GLUT_BITMAP_9_BY_15, "Venus");
	glTranslated(0, -2.8, 0);
	//translação
	if(movimento ==1)
		glTranslatef((2.84 * cos(2.0 * 3.14 * a*2.5 / 100)),(2.8+ 2.8 * sin(2.0 * 3.14 * a*2.5 / 100)), 0);
	//rotacao
	glRotated(-20*a, 0, 0, 1);
	glCallList(planetas[2]);
	glPopMatrix();


	//terra
	glPushMatrix();
	glRasterPos2f(0,-3.4);
		glutBitmapString(GLUT_BITMAP_9_BY_15, "Terra");
	glTranslated(0, -3.4, 0);
	//translacao
	if(movimento ==1)
		glTranslatef((3.55 * cos(2.0 * 3.14 * a*1.9 / 100)),(3.4 + 3.4 * sin(2.0 * 3.14 * a*1.9 / 100)), 0);
	//rotacao
	glRotated(-20*a, 0, 0, 1);
	glCallList(planetas[3]);

	//inclinacao da lua
	glRotated(27, 1, 0, 0);
	//translacao da lua
	glTranslatef(0.2*(cos(2.0 * 3.14 * a*13 / 100)),(0.2*sin(2.0 * 3.14 * a*13 / 100)), 0);

	glBindTexture(GL_TEXTURE_2D,textura[9]);
	gluSphere(qobj,0.02,50,50);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//glTranslated(0, 2.9, 0);


	//marte
	glRasterPos2f(0,-4.2);
		glutBitmapString(GLUT_BITMAP_9_BY_15, "Marte");

	glPushMatrix();
	glTranslated(0, -4.2, 0);
	//translacao
	if(movimento ==1)
		glTranslatef((4.51 * cos(2.0 * 3.14 * a*2.4 / 100)),(4.2 +4.2 * sin(2.0 * 3.14 * a*2.4 / 100)), 0);
	//rotacao
	glRotated(-20*a, 0, 0, 1);
	glCallList(planetas[4]);

	glPopMatrix();


	//jupter
	glPushMatrix();
	glRasterPos2f(0,-7.0);
		glutBitmapString(GLUT_BITMAP_9_BY_15, "Jupter");

	glTranslated(0, -7.0, 0 );
	//translacao
	if(movimento ==1)
		glTranslatef((8.2 * cos(2.0 * 3.14 * a*1.3 / 100)),(7 + 7 * sin(2.0 * 3.14 * a*1.3 / 100)), 0);
	//rotacao
	glRotated(-20*a, 0, 0, 1);
	glCallList(planetas[5]);

	glPopMatrix();

	//saturno
	glRasterPos2f(0,-11);
		glutBitmapString(GLUT_BITMAP_9_BY_15, "Saturno");

	glPushMatrix();
	glTranslated(0, -11, 0);
	//translacao
	if(movimento ==1)
		glTranslatef((12.2 * cos(2.0 * 3.14 * a*0.9 / 100)),(11 + 11 * sin(2.0 * 3.14 * a*0.9 / 100)), 0);

	//inclinacao do planeta e aneis
	glRotated(27, 1, 0, 0);
	//rotacao
	glRotated(-20*a, 0, 0, 1);
	glCallList(planetas[6]);

	//Lua de saturno
	glTranslatef((cos(2.0 * 3.14 * a*10 / 100)),(sin(2.0 * 3.14 * a*10 / 100)), 0);
	glutSolidSphere(0.05, 25,25);
	glPopMatrix();



	//urano
	glPushMatrix();
	glRasterPos2f(0,-20);
		glutBitmapString(GLUT_BITMAP_9_BY_15, "Urano");

	glTranslated(0, -20, 0);
	//translacao
	if(movimento ==1)
		glTranslatef((22 * cos(2.0 * 3.14 * a*0.6 / 100)),(20+ 20 * sin(2.0 * 3.14 * a*0.6 / 100)), 0);
	//rotacao
	glRotated(-20*a, 0, 0, 1);
	glCallList(planetas[7]);
	glPopMatrix();


	//netuno
	glPushMatrix();
	glRasterPos2f(0,-34);
		glutBitmapString(GLUT_BITMAP_9_BY_15, "Netuno");

	glTranslated(0, -34, 0);
	//translacao
	if(movimento ==1)
		glTranslatef((37 * cos(2.0 * 3.14 * a*0.5 / 100)),(34 + 34 * sin(2.0 * 3.14 * a*0.5 / 100)), 0);
	//rotacao
	glRotated(-20*a, 0, 0, 1);
	glCallList(planetas[8]);
	glPopMatrix();


	glutSwapBuffers();


}
//FIM DE FUNCAO
//============================================================================//


//============================================================================//
//Funcao callbak desenha.
void Desenha(void)
{


	/* usar buffer duplo, manda escrever no buffer de traz */
	glDrawBuffer(GL_BACK);

	// Limpa a janela de visualizao com a cor de fundo especificada
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





	//desenha todos os objetos na tela
	if(maisInf == -1)
		meuObjeto();
	else MenuMaisInformacoes(maisInf);



	glutSwapBuffers();

}
//FIM DE FUNCAO
//============================================================================//



//============================================================================//
// Inicializa parmetros de rendering
void Inicializa (void)
{


	//Obs: o uso de textura consiste apenas em dois passos: Carga e Aplicação.

	// Habilitar o uso de texturas
	glEnable ( GL_TEXTURE_2D );
	glEnable(GL_COLOR_MATERIAL);
	// Definir a forma de armazenamento dos pixels na textura (1= alinhamento por byte)
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

	// Definir quantas texturas serão usadas no programa
	//GLuint texture_id[10]; // vetor com os números das texturas
	glGenTextures (10, textura);  // 1 = uma textura;
					// texture_id = vetor que guarda os números das texturas(para ir trocando depois)
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	//carregar texturas
	textura[0] = LoadBitmap("sol.bmp");
	textura[1] = LoadBitmap("mercurio.bmp");
	textura[2] = LoadBitmap("venus.bmp");
	textura[3] = LoadBitmap("terra.bmp");
	textura[4] = LoadBitmap("marte.bmp");
	textura[5] = LoadBitmap("jupter.bmp");
	textura[6] = LoadBitmap("saturno.bmp");
	textura[7] = LoadBitmap("urano.bmp");
	textura[8] = LoadBitmap("netuno.bmp");
	textura[9] = LoadBitmap("lua.bmp");


	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);


	//negocio para nao ficar mais transparente
	glEnable(GL_DEPTH_TEST);

	// Define a cor de fundo da janela de visualizao como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	//chama metodo para compilar os objetos e gerar a listas de exibicao
	compilarObjetosDaCena();

}
//FIM DE FUNCAO
//============================================================================//



//============================================================================//
//Criar as listas dos objetos que serão usados na cena
void compilarObjetosDaCena()
{

	//Cria os 8 indices das listas para os 8 planetas
	int i;
	for( i = 1; i <9; i++)
		planetas[i] = glGenLists(i);

	orbitas = glGenLists(9);
	eixos = glGenLists(10);

	//compila eixos coordenados
	glNewList(eixos, GL_COMPILE);
	     glColor3f(1.0f, 0.0f, 0.0f);

	     glBegin(GL_LINES);
	     	glVertex3i(0, 0, 0);
	     	glVertex3i(200, 0, 0);
	     glEnd();

	     //Cor e desenho do eixo y
	     glColor3f(0.0f, 1.0f, 0.0f);

	     glBegin(GL_LINES);
	     	glVertex3i(0, 0, 0);
	     	glVertex3i(0, 200, 0);
	     glEnd();


	     //Cor e desenho do eixo z
	     glColor3f(0.0f, 0.0f, 1.0f);

	     glBegin(GL_LINES);
	     	glVertex3i(0, 0, 0);
	     	glVertex3i(0, 0, 200);
	     glEnd();
	glEndList();

	glNewList(planetas[1], GL_COMPILE);
		GLUquadric *qobj = gluNewQuadric();
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura[1]);

		gluSphere(qobj,0.048,50,50);
		glDisable(GL_TEXTURE_2D);

	glEndList();


	glNewList(planetas[2], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura[2]);
		gluSphere(qobj,0.121,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();

	glNewList(planetas[3], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura[3]);
		gluSphere(qobj,0.127,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();

	glNewList(planetas[4], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura[4]);
		gluSphere(qobj,0.068,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();

	glNewList(planetas[5], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura[5]);
		gluSphere(qobj,0.543,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();


	glNewList(planetas[6], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura[6]);
		gluSphere(qobj,0.320,50,50);
		glDisable(GL_TEXTURE_2D);

	glBegin(GL_LINE_LOOP);
	for (i = 0; i < 100 + 1; i++) {  // +1 para cerrar
		DefineIluminacao(0.86415094, 0.86328125, 0.8515625);
		glVertex2f(0.6 * cos(2.0 * 3.14 * i / 100), 0.6 * sin(2.0 * 3.14 * i / 100) );
			glVertex2f(0.5 * cos(2.0 * 3.14 * i / 100),
					0.5 * sin(2.0 * 3.14 * i / 100) );
		glColor3f(0.80078125f, 0.6875f, 0.4296875f);
		glVertex2f(0.4 * cos(2.0 * 3.14 * i / 100),
					0.4 * sin(2.0 * 3.14 * i / 100) );

	}
	glEnd();
	glEndList();


	glNewList(planetas[7], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura[7]);
		gluSphere(qobj,0.21,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();

	glNewList(planetas[8], GL_COMPILE);
		gluQuadricTexture(qobj,GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textura[8]);
		gluSphere(qobj,0.19,50,50);
		glDisable(GL_TEXTURE_2D);
	glEndList();

	//----------- COMPILA ORBITAS --------//
	glNewList(orbitas, GL_COMPILE);
		//orbita mercurio
		glPushMatrix();

	//glRasterPos2f(0,0);
	//	glutBitmapString(GLUT_BITMAP_9_BY_15, "Mercurio");
glTranslated(0, -1.9, 0);
	DefineIluminacao(0.6226415, 0.47265, 0.289062);
	//cincunferencia
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_POLYGON);
	for (i = 0; i < 100 + 1; i++) {  // +1 para cerrar
		glVertex2f( 2.3 * cos(2.0 * 3.14 * i / 100),
		1.9 + 1.9 * sin(2.0 * 3.14 * i / 100) );
	}
	glEnd();
	glPopMatrix();

	//Orbirta venus
	glPushMatrix();
	glTranslated(0, -2.8, 0);
	DefineIluminacao(0.762264, 0.6875, 0.54296);
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_POLYGON);
	for (i = 0; i < 100 + 1; i++) {  // +1 para cerrar
		glVertex2f(2.84 * cos(2.0 * 3.14 * i / 100),
		2.8 + 2.8 * sin(2.0 * 3.14 * i / 100) );
	}
	glEnd();
	glPopMatrix();

	//orbita terra
	glPushMatrix();
	glTranslated(0, -3.4, 0);
	DefineIluminacao(0.09375,0.0859375, 0.33203125);
	//glColor3f(0.09375f, 0.0859375f, 0.33203125f);
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_POLYGON);
	for (i = 0; i < 100 + 1; i++) {  // +1 para cerrar
		glVertex2f(3.55 * cos(2.0 * 3.14 * i / 100),
				3.4 + 3.4 * sin(2.0 * 3.14 * i / 100) );
	}
	glEnd();
	glPopMatrix();

	//orbita marte
	glPushMatrix();
	glTranslated(0, -4.2, 0);
	DefineIluminacao(0.83203125, 0.25390625, 0.12109375);
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_POLYGON);
	for (i = 0; i < 100 + 1; i++) {  // +1 para cerrar
		glVertex2f(4.51 * cos(2.0 * 3.14 * i / 100),
				4.2+ 4.2 * sin(2.0 * 3.14 * i / 100) );
	}
	glEnd();
	glPopMatrix();

	//orbita jupter
	glPushMatrix();
	glTranslated(0, -7.0, 0 );
	DefineIluminacao(0.86415094, 0.86328125, 0.8515625);
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_POLYGON);
	for (i = 0; i < 100 + 1; i++) {  // +1 para cerrar
		glVertex2f(8.2 * cos(2.0 * 3.14 * i / 100),
				7 + 7 * sin(2.0 * 3.14 * i / 100) );
	}
	glEnd();
	glPopMatrix();

	//orbita saturno
	glPushMatrix();
	glTranslated(0, -11, 0);
	DefineIluminacao(0.80078125, 0.687, 0.429687);
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_POLYGON);
	for (i = 0; i < 100 + 1; i++) {  // +1 para cerrar
		glVertex2f(12.2 * cos(2.0 * 3.14 * i / 100),
				11 + 11 * sin(2.0 * 3.14 * i / 100) );
	}
	glEnd();
	glPopMatrix();

	//orbita urano
	glPushMatrix();
	glTranslated(0, -20, 0);
	DefineIluminacao(0.5742187, 0.644531, 0.730468);
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_POLYGON);
	for (i = 0; i < 100 + 1; i++) {  // +1 para cerrar
		glVertex2f(22 * cos(2.0 * 3.14 * i / 100),
				20 + 20 * sin(2.0 * 3.14 * i / 100) );
	}
	glEnd();
	glPopMatrix();

	//netuno
	glPushMatrix();
	glTranslated(0, -34, 0);
//DefineIluminacao(0.2773437, 0.507812, 0.8125);
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_POLYGON);
	for (i = 0; i < 100 + 1; i++) {  // +1 para cerrar
		glVertex2f(37 * cos(2.0 * 3.14 * i / 100),
				34 + 34 * sin(2.0 * 3.14 * i / 100) );
	}
	glEnd();
	glPopMatrix();

	glEndList();


}
//FIM DE FUNCAO
//============================================================================//


//============================================================================//
//Funcao das opcoes do meu principal
void MenuPrincipal(int op)
{

	switch(op) {
		case 8: maisInf = -1;
}
}
//FIM DE FUNCAO
//============================================================================//


//============================================================================//
//Funcao das opcoes do submenu mais informacoes
void MenuMaisInformacoes(int op)
{
	maisInf = op;

	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    	double a = t;
	char texto[1000];

	switch(maisInf) {

		case 0:
			//restaura matriz identidade
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glPushMatrix();	//salva para por o texto
			//strcpy(texto,
			glColor3d( 255,255,255 );
			glRasterPos3f(0.3,2.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Massa (kg)	3.303e+23 \n"
 "Raio equatorial (km)	2,439.7 \n"
 "Densidade media (gm/cm^3)	5.42 \n"
 "Distancia media ao Sol (km)	57,910,000 \n"
 "Periodo de rotacao (dias)	58.6462 \n"
 "Periodo orbital (dias)	87.969 \n"
 "Velocidade orbital media (km/seg)	47.88 \n"
 "Excentricidade orbital	0.2056 \n"
 "Inclinacao do eixo (graus)	0.00 \n"
 "Inclinacao orbital (graus)	7.004 \n"
 "Gravidade a superficie no equador(m/seg^2)	2.78 \n"
 "Velocidade de escape no equador (km/seg)	4.25 \n"
 "Albedo geometrico visual	0.10 \n"
 "Magnitude (Vo)	-1.9 \n"
 "Temperatura media a superficie	179 C \n"
 "Temperatura maxima a superficie	427 C \n"
 "Temperatura minima a superficie	-173 C \n"
 "Composicao atmosferica\n"
    "Helio     42%\n"
    "Sodio     42%\n"
    "Oxigenio  15%\n"
    "Outros    1%\n" );
glPushMatrix();
glRasterPos3f(-6.5,-2.5, -30);
glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Curiosidades\n");
glRasterPos3f(-6.5,-3, -30);
glutBitmapString(GLUT_BITMAP_9_BY_15, "-Segundo os cientistas, existe ouro em Marte, \nMercurio e em Venus.\n"
"-Mercurio recebe sete vezes mais luz do que a Terra.");
glPopMatrix();
  			glColor3d( 255,255,0 );
			glRasterPos3f(0.3,3.5, -30);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Mercurio\n");
			// DesenhaTexto(texto, 0.5f,0.5f);
			glPopMatrix(); //restaura para por o planeta


			glPushMatrix();

				//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glTranslated(0, 0, -1);

			glTranslated(-0.1, 0, 0);

			glRotated(rodaX, 1, 0, 0);
			glRotated(rodaY, 0, 1, 0);
			glRotated(rodaZ, 0, 0, 1);
			glRotated(90, 1, 0, 0);
			glRotated(-20*a, 0, 0, 1);
			glCallList(planetas[1]);
			glPopMatrix();
			break;
		case 1:

			//restaura matriz identidade
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glPushMatrix();	//salva para por o texto
			//strcpy(texto,
			glColor3d( 255,255,255 );
			glRasterPos3f(0.3,2.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,
 "Massa (kg)	4.869e+24 \n"
 "Raio equatorial (km)	6,051.8  \n"
 "Densidade media (gm/cm^3)	5.25  \n"
 "Distancia media do Sol (km)	108,200,000  \n"
 "Periodo de rotacao (dias)	-243.0187  \n"
 "Periodo orbital (dias)	224.701  \n"
 "Velocidade orbital media(km/s)	35.02  \n"
 "Excentricidade orbital	0.0068  \n"
 "Inclinacao do eixo (graus)	177.36  \n"
 "Inclinacao orbital (graus)	3.394  \n"
 "Gravidade equatorial na superfície (m/seg^2)	8.87  \n"
 "Velocidade de escape no equador(km/seg)	10.36 \n"
 "Albedo geometrico visual	0.65  \n"
 "Magnitude (Vo)	-4.4  \n"
 "Temperatura media na superficie	482°C  \n"
 "Pressao Atmosferica (bars)	92  \n"
 "Composicao atmosferica \n"
 "   Dioxido de Carbono 96%\n"
 "   Nitrogenio 3+%\n"

  "        Vestigios de : Dioxido de enxofre, vapor de agua,\n "
"monoxido de carbono, argon, helio, neon,\n"
" cloreto de hidrogenio e fluoreto de hidrogenio. "  );
glPushMatrix();
glRasterPos3f(-6.5,-2.5, -30);
glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Curiosidades\n");
glRasterPos3f(-6.5,-3, -30);
glutBitmapString(GLUT_BITMAP_9_BY_15, "- 45% dos Americanos nao sabem que o Sol e uma estrela.\n"
"-Todos os planetas do Sistema Solar rodam no sentido\n contrario ao dos ponteiros do relogio, excepto Venus.");
glPopMatrix();
  			glColor3d( 255,255,0 );
			glRasterPos3f(0.3,3.5, -30);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Venus\n");
			// DesenhaTexto(texto, 0.5f,0.5f);
			glPopMatrix(); //restaura para por o planeta
				//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glTranslated(0, 0, -1.6);
			glTranslated(-0.2, 0, 0);
			glRotated(rodaX, 1, 0, 0);
			glRotated(rodaY, 0, 1, 0);
			glRotated(rodaZ, 0, 0, 1);
			//rotação do planeta
			glRotated(-90, 1, 0, 0);
			glRotated(-20*a, 0, 0, 1);
			glCallList(planetas[2]);
			break;

		case 2:
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
				//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glPushMatrix();	//salva para por o texto
			//strcpy(texto,
			glColor3d( 255,255,255 );
			glRasterPos3f(0.3,2.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,
 "Massa (kg)	5,976e+24 \n"
 "Raio equatorial (km)	6.378,14 \n"
 "Densidade media (g/cm^3)	5,515 \n"
 "Distancia media do Sol (km)	149.600.000 \n"
 "Periodo de rotacao (dias)	0,99727 \n"
 "Periodo de rotacao (horas)	23,9345 \n"
 "Periodo Orbital (dias)	365,256\n"
 "Velocidade orbital media (km/s)	29,79 \n"
 "Excentricidade orbital	0,0167 \n"
 "Inclinacao do Eixo (graus)	23,45 \n"
 "Inclinacao orbital (graus)	0,000 \n"
 "Velocidade de escape no equador (km/s)	11,18 \n"
 "Gravidade a superficie no equador (m/s^2)	9,78 \n"
 "Albedo visual geometrico	0,37 \n"
 "Temperatura media a superficie	15°C \n"
 "Pressao atmosferica (bar)	1,013 \n"
 "Composicao atmosferica\n"
    "Azoto 77%\n"
    "Oxigenio 21%\n"
    "Outros 2%\n"	 );
glPushMatrix();
glRasterPos3f(-6.5,-2.5, -30);
glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Curiosidades\n");
glRasterPos3f(-6.5,-3, -30);
glutBitmapString(GLUT_BITMAP_9_BY_15, "-Cerca de 150 toneladas de fragmentos de\n meteoritos embatem na Terra todos os anos.\n"
"-E possivel ver 500.000 crateras na Lua olhando-se da Terra.\n-A Terra nao e redonda; e ligeiramente achatada nos polos. ");
glPopMatrix();
  			glColor3d( 255,255,0 );
			glRasterPos3f(0.3,3.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Terra\n");
			// DesenhaTexto(texto, 0.5f,0.5f);
			glPopMatrix(); //restaura para por o planeta

			glTranslated(0, 0, -1.6);
			glTranslated(-0.2, 0, 0);
			glRotated(rodaX, 1, 0, 0);
			glRotated(rodaY, 0, 1, 0);
			glRotated(rodaZ, 0, 0, 1);
			//rotação do planeta
			glRotated(-90, 1, 0, 0);
			glRotated(-20*a, 0, 0, 1);
			glCallList(planetas[3]);
			break;

		case 3:
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
				//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glPushMatrix();	//salva para por o texto
			//strcpy(texto,
			glColor3d( 255,255,255 );
			glRasterPos3f(0.3,3, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,
 "Massa (kg)	6.421e+23 \n"
 "Raio equatorial (km)	3,397.2 \n"
 "Densidade media (gm/cm^3)	3.94 \n"
 "Distancia media ao Sol (km)	227,940,000 \n"
 "Periodo de rotacao (horas)	24.6229 \n"
 "Periodo de rotacao (dias)	1.025957 \n"
 "Periodo orbital (dias)	686.98 \n"
 "Velocidade media orbital (km/seg)	24.13 \n"
 "Excentricidade orbital	0.0934 \n"
 "Inclinacao do eixo (graus)	25.19 \n"
 "Inclinacao orbital (graus)	1.850 \n"
 "Gravidade a superficie no equador (m/seg^2)	3.72 \n"
 "Velocidade de escape no equador (km/seg)	5.02 \n"
 "Albedo geometrico visual	0.15 \n"
 "Magnitude (Vo)	-2.01 \n"
 "Temperatura minima a superficie	-140°C \n"
 "Temperatura media a superficie	-63°C \n"
 "Temperatura maxima a superfície	20°C \n"
 "Pressao atmosferica (bars)	0.007 \n"
 "Composicao atmosferica\n"
    "Dioxido de Carbono (C02) 95.32% - Azoto (N2) 2.7%\n"
    "Argon (Ar) 1.6% - Oxigenio (O2) 0.13%\n"
    "Monoxido de Carbono (CO) 0.07% - Agua (H2O) 0.03%\n"
    "Neon (Ne) 0.0025% - Kripton (Kr) 0.00003%\n"
    "Xenon (Xe) 0.000008% - Ozono (O3) 	0.000003%\n"
	 );
glPushMatrix();
glRasterPos3f(-6.5,-2.5, -30);
glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Curiosidades\n");
glRasterPos3f(-6.5,-3, -30);
glutBitmapString(GLUT_BITMAP_9_BY_15, "-Por causa da sua cor vermelho-sangue,\n Marte recebeu o nome do Deus da Guerra.\n "
"-O maior vulcao existente chama-se Olympus\n Mons e situa-se em Marte.\n "
"-E possivel ver 500.000 crateras na Lua olhando-se da Terra.\n");
glPopMatrix();
  			glColor3d( 255,255,0 );
			glRasterPos3f(0.3,3.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Marte\n");
			// DesenhaTexto(texto, 0.5f,0.5f);
			glPopMatrix(); //restaura para por o planeta

			glTranslated(0, 0, -1);
			glTranslated(-0.1, 0, 0);
			glRotated(rodaX, 1, 0, 0);
			glRotated(rodaY, 0, 1, 0);
			glRotated(rodaZ, 0, 0, 1);

			//rotação do planeta
			glRotated(90, 1, 0, 0);
			glRotated(-20*a, 0, 0, 1);
			glCallList(planetas[4]);
			break;

		case 4:
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glPushMatrix();	//salva para por o texto
			//strcpy(texto,
			glColor3d( 255,255,255 );
			glRasterPos3f(0.3,2.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,
 "Massa (kg)	1.900e+27 \n"
 "Raio equatorial (km)	71,492 \n"
 "Raio equatorial (Terra = 1)	1.1209e+01 \n"
 "Densidade media (gm/cm^3)	1.33 \n"
 "Distancia media ao Sol (km)	778,330,000 \n"
 "Distancia media ao Sol (Terra = 1)	5.2028\n"
 "Periodo de rotacao (dias)	0.41354 \n"
 "Periodo orbital (dias)	4332.71 \n"
 "Velocidade orbital media (km/seg)	13.07 \n"
 "Excentricidade orbital	0.0483 \n"
 "Inclinacao do eixo (graus)	3.13 \n"
 "Inclinacao orbital (graus)	1.308 \n"
 "Gravidade a superficie no equador (m/seg^2)	22.88 \n"
 "Velocidade de escape no equador (km/seg)	59.56 \n"
 "Albedo geometrico visual	0.52 \n"
 "Magnitude (Vo)	-2.70 \n"
 "Temperatura media das nuvens	-121°C \n"
 "Pressao atmosferica (bars)	0.7 \n"
 "Composicao atmosferica\n"
    "Hidrogenio 90%\n"
    "Helio 10%\n"
	 );
glPushMatrix();
glRasterPos3f(-6.5,-2.5, -30);
glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Curiosidades\n");
glRasterPos3f(-6.5,-3, -30);
glutBitmapString(GLUT_BITMAP_9_BY_15, "-Jupter tem 3 vezes mais massa do que todos\nos outros planetar juntos.\n "
"-Calcula-se que Jupiter possua 70%\n de toda a materia que gira em torno do Sol.\n ");

glPopMatrix();
  			glColor3d( 255,255,0 );
			glRasterPos3f(0.3,3.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Jupter\n");
			// DesenhaTexto(texto, 0.5f,0.5f);
				//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glPopMatrix(); //restaura para por o planeta

			glTranslated(0, 0, -6);
			glTranslated(-0.58, 0, 0);
			glRotated(rodaX, 1, 0, 0);
			glRotated(rodaY, 0, 1, 0);
			glRotated(rodaZ, 0, 0, 1);

			//rotação do planeta
			glRotated(90, 1, 0, 0);
			glRotated(-20*a, 0, 0, 1);
			glCallList(planetas[5]);
			break;

		case 5:
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
				//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

			glPushMatrix();	//salva para por o texto
			//strcpy(texto,
			glColor3d( 255,255,255 );
			glRasterPos3f(0.3,2.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,
 "Massa (kg)	5.688e+26 \n"
 "Raio Equatorial (km)	60,268  \n"
 "Densidade Media (gm/cm^3)	0.69  \n"
 "Distancia media do Sol (km)	1,429,400,000  \n"
 "Periodo rotacional (horas)	10.233  \n"
 "Periodo orbital (anos)	29.458  \n"
 "Velocidade media orbital (km/seg)	9.67  \n"
 "Excentricidade orbital	0.0560  \n"
 "Inclinacao do eixo (graus)	25.33  \n"
 "Inclinacao orbital (graus)	2.488  \n"
 "Gravidade a superficie no equador (m/seg^2)	9.05  \n"
 "Velocidade de escape no equador (km/seg)	35.49  \n"
 "Albedo geometrico visual	0.47  \n"
 "Magnitude (Vo)	0.67  \n"
 "Temperatura media das nuvens	-125°C  \n"
 "Pressao atmosferica (bars)	1.4  \n"
 "Composicao atmosferica \n"
 "   Hidrogenio 97% \n"
 "   Helio 3% \n"
	 );
glPushMatrix();
glRasterPos3f(-6.5,-2.5, -30);
glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Curiosidades\n");
glRasterPos3f(-6.5,-3, -30);
glutBitmapString(GLUT_BITMAP_9_BY_15, "-Em Saturno, os ventos sao 10 vezes mais\n fortes do que um furacao."
"-Saturno tem sete majestosos aneis ao seu redor.\n Cada anel e composto por centenas de aneis menores\nEles ficam uns"
" dentro dos outros e\n sao feitos por bilioes de particulas de gelo.");

glPopMatrix();
  			glColor3d( 255,255,0 );
			glRasterPos3f(0.3,3.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Saturno\n");
			// DesenhaTexto(texto, 0.5f,0.5f);
				//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glPopMatrix(); //restaura para por o planeta


			glTranslated(0, 0, -5);
			glTranslated(-0.56, 0, 0);
			glRotated(27, 1, 0, 0);
			glRotated(10, 0, 0, 1);
			glRotated(rodaX, 1, 0, 0);
			glRotated(rodaY, 0, 1, 0);
			glRotated(rodaZ, 0, 0, 1);

			//rotação do planeta
			glRotated(90, 1, 0, 0);
			glRotated(-20*a, 0, 0, 1);
			glCallList(planetas[6]);
			break;

		case 6:
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
				//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

			glPushMatrix();	//salva para por o texto
			//strcpy(texto,
			glColor3d( 255,255,255 );
			glRasterPos3f(0.3,2.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,
 "Descoberto por	William Herschel \n"
 "Data da descoberta	1781 \n"
 "Massa (kg)	8.686e+25 \n"
 "Raio equatorial (km)	25,559 \n"
 "Raio equatorial (Terra = 1)	4.0074 \n"
 "Densidade media (gm/cm^3)	1.29 \n"
 "Distancia media ao Sol (km)	2,870,990,000 \n"
 "Distancia media ao Sol (Terra = 1)	19.1914 \n"
 "Periodo de rotacao (horas)	-17.9 \n"
 "Periodo orbital (anos)	84.01 \n"
 "Velocidade orbital media (km/seg)	6.81 \n"
 "Excentricidade orbital	0.0461 \n"
 "Inclinacao do eixo (graus)	97.86 \n"
 "Inclinacao orbital (graus)	0.774 \n"
 "Gravidade a superficie no equador (m/seg^2)	7.77 \n"
 "Velocidade de escape no equador (km/seg)	21.30 \n"
 "Albedo geometrico visual	0.51 \n"
 "Magnitude (Vo)	5.52 \n"
 "Temperatura media das nuvens	-193°C \n"
 "Pressao atmosferica (bars)	1.2 \n"
 "Composicao atmosferica\n"
    "Hidrogenio 83%\n"
    "Helio 15%\n"
    "Metano 2%	\n"
	 );
glPushMatrix();
glRasterPos3f(-6.5,-2.5, -30);
glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Curiosidades\n");
glRasterPos3f(-6.5,-3, -30);
glutBitmapString(GLUT_BITMAP_9_BY_15, "-Em Urano, o verao dura 21 anos...\n e o inverno tambem."
);

glPopMatrix();
  			glColor3d( 255,255,0 );
			glRasterPos3f(0.3,3.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Urano\n");
			// DesenhaTexto(texto, 0.5f,0.5f);
				//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glPopMatrix(); //restaura para por o planeta

			glTranslated(0, 0, -3);
			glTranslated(-0.35, 0, 0);
			glRotated(rodaX, 1, 0, 0);
			glRotated(rodaY, 0, 1, 0);
			glRotated(rodaZ, 0, 0, 1);

			//rotação do planeta
			glRotated(90, 1, 0, 0);
			glRotated(-20*a, 0, 0, 1);
			glCallList(planetas[7]);
			break;

		case 7:
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
				//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glPushMatrix();	//salva para por o texto
			//strcpy(texto,
			glColor3d( 255,255,255 );
			glRasterPos3f(0.3,2.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18,
 "Descoberto por	Johann Gotfried Galle \n"
 "Data da descoberta	23 de Setembro de 1846  \n"
 "Massa (kg)	1.024e+26  \n"
 "Raio equatorial (km)	24,746  \n"
 "Densidade media (gm/cm^3)	1.64  \n"
 "Distancia media do Sol (km)	4,504,300,000  \n"
 "Distancia media do Sol (Terra = 1)	30.0611  \n"
 "Periodo rotacional (horas)	16.11  \n"
 "Periodo orbital (anos)	164.79  \n"
 "Velocidade media orbital (km/seg)	5.45  \n"
 "Excentricidade orbital	0.0097  \n"
 "Inclinacao do eixo (graus)	28.31  \n"
 "Inclinacao orbital (graus)	1.774  \n"
 "Gravidade equatorial a superficie (m/seg^2)	11.0  \n"
 "Velocidade de escape no equador (km/seg)	23.50  \n"
 "Albedo visual geometrico	0.41 \n"
 "Magnitude (Vo) 7.84  \n"
 "Temperatura media das nuvens	-193 a -153°C  \n"
 "Pressao atmosferica (bars)	1-3  \n"
 "Composicao atmosferica \n"
    "Hidrogenio 85% \n"
    "Helio 13% \n"
    "Metano 2% \n"
	 );
glPushMatrix();
glRasterPos3f(-6.5,-2.5, -30);
glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Curiosidades\n");
glRasterPos3f(-6.5,-3, -30);
glutBitmapString(GLUT_BITMAP_9_BY_15, "-Neptuno, com nome do deus romano do mar,\neste planeta azul e cheio de tempestades e\n" "ventos arrasadores, circundado por oito\nsatelites naturais e cinco aneis, \nalem de uma camada de poeira."
);

glPopMatrix();


  			glColor3d( 255,255,0 );
			glRasterPos3f(0.3,3.5, -30);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Neptuno\n");
			// DesenhaTexto(texto, 0.5f,0.5f);
				//gluLookAt(0.0, 0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glPopMatrix(); //restaura para por o planeta


			glTranslated(0, 0, -3);
			glTranslated(-0.3, 0, 0);
			glRotated(rodaX, 1, 0, 0);
			glRotated(rodaY, 0, 1, 0);
			glRotated(rodaZ, 0, 0, 1);

			//rotação do planeta
			glRotated(90, 1, 0, 0);
			glRotated(-20*a, 0, 0, 1);
			glCallList(planetas[8]);
			break;



		case 8: maisInf = -1;
			break;
	}

}
//FIM DE FUNCAO
//============================================================================//



//============================================================================//
//Funcao das opcoes do submenu associar-se
void MenuAssociarse(int op)
{
}
//FIM DE FUNCAO
//============================================================================//





//============================================================================//
//Funca que cria o menu principal
void CriaMenu()
{
    int menu,submenu1,submenu2, submenu3;

    submenu1 = glutCreateMenu(MenuMaisInformacoes);
    glutAddMenuEntry("Mercurio",0);
    glutAddMenuEntry("Venus",1);
    glutAddMenuEntry("Terra",2);
    glutAddMenuEntry("Marte",3);
    glutAddMenuEntry("Jupter",4);
    glutAddMenuEntry("Saturno",5);
    glutAddMenuEntry("Urano",6);
    glutAddMenuEntry("Netuno",7);

    submenu2 = glutCreateMenu(MenuAssociarse);
    glutAddMenuEntry("Mercurio",0);
    glutAddMenuEntry("Venus",1);
    glutAddMenuEntry("Terra",2);
    glutAddMenuEntry("Marte",3);
    glutAddMenuEntry("Jupter",4);
    glutAddMenuEntry("Saturno",5);
    glutAddMenuEntry("Urano",6);
    glutAddMenuEntry("Netuno",7);



    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Mais Informacoes",submenu1);
   // glutAddSubMenu("Associar-se",submenu2);
    glutAddMenuEntry("Pausar Trasnlacao  (p)",0);

    glutAddMenuEntry("Voltar (v)", 8);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
//FIM DE FUNCAO
//============================================================================//



//============================================================================//
// Funcao callback chamada quando o tamanho da janela  alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
                   // Evita a divisao por zero
                   if(h == 0) h = 1;

		GLfloat b =(GLfloat) w/(GLfloat)h;

		// Especifica as dimenses da Viewport - melhor ficar no metodo desenha
    		 glViewport(0, 0, w,h);

        // Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa matriz de coordenadas de projeção
	glLoadIdentity();

	   /*** PARA TRABALHARMOS EM 3D ***/
                //glFrustum(-14, 14, -7.2, 7.2, 10, 800.0);

                gluPerspective (16, b, 1, 800);
	printf("\n%d", b);
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(0,80,200, 50,-20,30, 0,1,0);
	// Maior qualidade nos gráficos
   	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );



}
//FIM DE FUNCAO
//============================================================================//




//============================================================================//
//funcao chamada sempre que o opengl está desocupado
//fica sempre atualizadno a tela
static void
idle(void)
{
    glutPostRedisplay();
}
//FIM DE FUNCAO
//============================================================================//




//============================================================================//
//funcao que trata eventos do teclado
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case '0':
   	while(1)
   	{

   		rodaX++;
   		rodaY++;

   		Desenha();
   	}
   	break;
     case '3':
	glEnable(GL_DEPTH_TEST); //abilitar remover transparencia
	break;
      case '4':
	glDisable(GL_DEPTH_TEST);
	break;
	case 'p':
		if(movimento == 1)
			movimento = 0;
		else movimento = 1;
		break;
      case 'q':
         rodaX +=2;
	 glutPostRedisplay();
         break;
      case 'w':
         rodaX -=2;
	 glutPostRedisplay();
         break;
      case 'a':
         rodaY+=2;
	 glutPostRedisplay();
         break;
      case 's':
         rodaY-=2;
	 glutPostRedisplay();
         break;
      case 'z':
         rodaZ+=2;
	 glutPostRedisplay();
         break;
      case 'x':
         rodaZ-=2;
	 glutPostRedisplay();
         break;
	case '1':
         zoom+=0.3;
	 glutPostRedisplay();
         break;
	case '2':
         zoom-=0.3;
	 glutPostRedisplay();
         break;
	case 'm':

	break;


      case 27:
         exit(0);
	 break;
   }
}
//FIM DE FUNCAO
//============================================================================//



//============================================================================//
//funcao que trata eventos do mouse
/*
Três valores são válidos para o parâmetro button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON e GLUT_RIGHT_BUTTON. O parâmetro state pode ser GLUT_UP ou GLUT_DOWN
*/
void HandleMouse ( int button, int state, int x, int y )
{


	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_UP)
			CriaMenu();

	if(button == 3) //rolagem para cima(nao funcionou no windows)
		zoom+=2;
	else if(button == 4) //rolagem para baixo
		zoom-=2;


    // debug of keys
	//if(button == GLUT_MIDDLE_BUTTON)
	//	printf("\nzoom = %f", zoom);
	//if (button == GLUT_RIGHT_BUTTON)
	//	printf("\n(%d,%d)", x, y);

	//if(state == GLUT_UP)
		//printf("\n(%d,%d)", x, y);

	//if ( state == GLUT_UP )
	//		printf("\napertou");
	//if ( state == GLUT_DOWN )
	//	printf("\nsoltou");


     glutPostRedisplay(); //redesenha tela
}
//FIM DE FUNCAO
//============================================================================//




//============================================================================//
//funcao que trata evento de teclas especiais
void keyboard2(int key, int x, int y)
{
   switch (key) {
	case GLUT_KEY_PAGE_UP:
		glutFullScreen ( );
	break;
	case GLUT_KEY_PAGE_DOWN:
		glutInitWindowSize(1200,720);
	break;
 case GLUT_KEY_UP:
   	moveY += 0.5f;
	printf("\nup");
   break;

 case GLUT_KEY_DOWN:
   	moveY -= 0.5f;
	printf("\ndown");
   break;

 case GLUT_KEY_LEFT:
   	moveX -= 0.5f;
	printf("\nleft");
   break;

 case GLUT_KEY_RIGHT:
   	moveX += 0.5f;
   break;


   }

	glutPostRedisplay(); //redesenha tela

}
//FIM DE FUNCAO
//============================================================================//




//============================================================================//
//funcao que trata eventos de movimento passivo do mouse
void MoveMouse(int x, int y)
{
     printf("\n(%d,%d)", x, y);
     glutPostRedisplay();
}
//FIM DE FUNCAO
//============================================================================//




//============================================================================//
//Funcao que trata eventos do mouse enquanto o botao permanece pressionado
int Y=0, X=0;
void MoveMouseBotaoPressionado(int x, int y)
{

	if(y > Y)
		moveY -= 0.07;
	else moveY += 0.07;

	if(x > X)
		moveX += 0.07;
	else moveX -= 0.07;

	Y = y;
	X = x;


      glutPostRedisplay();
}
//FIM DE FUNCAO
//============================================================================//



//============================================================================//
// Programa Principal
int main(int argc, char **argv) {

     glutInit(&argc,argv);

     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH ); //GLUT_DEPTH: buffer para evitar transparencia(por profundidade)
     glutInitWindowSize(1200,720); //tamanha inicial da janela
     glutInitWindowPosition(10,10); //posicao inicial
     glutCreateWindow("BobCosmos Sistema Solar - Joao F M Figueiredo"); //nome da janela
     glutDisplayFunc(Desenha); //funcao onde fica todas as rotinas de desenho
     glutMouseFunc(HandleMouse); //cliques do mouse
     //glutPassiveMotionFunc(MoveMouse); //movimento passivo do mouse
     glutMotionFunc(MoveMouseBotaoPressionado);
     glutReshapeFunc(AlteraTamanhoJanela); //configura o tamanho da janela, camera e etc
     Inicializa(); //inicializa alguns parametros
     glutKeyboardFunc(keyboard); //teclas
     glutSpecialFunc(keyboard2); //teclas especiais
     glutIdleFunc(idle); //enquanto o gl nao esta fazendo nada
     glutMainLoop(); //inicia maquina de estados
}
//FIM DE FUNCAO
//============================================================================//