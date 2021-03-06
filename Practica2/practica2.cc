//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <objetos.h>
#include <vector>
#include <string.h>
// Variables Globales: 

char forma='C';  // 'c' para Cubo  't' para Tetraedro
char tipo= 'S';	 // 'p' punto 'l' linea 'a' ajedrez 's' solido
int tam=3;       // tamaño de las formas
int al=tam+1; 	 // altura de las formas
int	angx=-9;
int	angy=9;
int angz=0;

//Objetos:
_piramide piramide(tam,al);
_cubo cubo(tam);
_ply fig;
_ply aux;
_rotacion rot;


void mensaje(char * msg){
for (int i = 0; i < strlen(msg); i++) {
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, (int) msg[i]);
}
}
// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
/*
GLfloat Vertices[8][3]= {{5,0,0},{4,4,0},{0,5,0},{-4,4,0},{-5,0,0},{-4,-4,0},{0,-5,0},{4,-4,0}};
int i;
glColor3f(0,1,0);
glPointSize(4);

glBegin(GL_POINTS);
for (i=0;i<8;i++){
	glVertex3fv((GLfloat *) &Vertices[i]);
	}
glEnd();
*/

char msg1[] = "C - Cubo  T - Tetraedro F - Figura ply R-Rotacion ";
glRasterPos3f(angx, angy,angz);
mensaje(msg1);
char msg2[] = "P - Punto  L - Alambre  A - Ajedrez  S - Solido";
glRasterPos3f(angx, angy-0.5,angz);
mensaje(msg2);
char msg3[] = "Z - Zoom++   X - Zoom --";
glRasterPos3f(angx, angy-1,angz);
mensaje(msg3);

if(toupper(forma)=='T'){
	switch(toupper(tipo)){
		case'P':piramide.draw_puntos(1,0,0,5); 	break;
		case'L':piramide.draw_aristas(0,1,0,2); 	break;
		case'A':piramide.draw_solido_ajedrez(0,1,0,0,0,1);	break;
		case'S':piramide.draw_solido(0,0,1); 	break;	
		
		}
}
else if(toupper(forma)=='C'){
	switch(toupper(tipo)){
		case'P':cubo.draw_puntos(1,0,0,5); 	break;
		case'L':cubo.draw_aristas(0,1,0,2);  	break;
		case'A':cubo.draw_solido_ajedrez(0,1,0,0,0,1); 	break;
		case'S':cubo.draw_solido(0,0,1); 	break;	
		}
}
else if(toupper(forma)=='F'){
	if(fig.vertices.empty()){
		exit(3);
	}
	
	switch(toupper(tipo)){
		case'P':fig.draw_puntos(1,0,0,1); 	break;
		case'L':fig.draw_aristas(184/255.0,0,138/255.0,1);  	break;
		case'A':fig.draw_solido_ajedrez(0,1,0,0,0,1); 	break;
		case'S':fig.draw_solido(0,0,1); 	break;
	}
}
else if(toupper(forma)=='R'){
	if(rot.vertices.empty()){
		exit(4);
	}
	switch(toupper(tipo)){
		case'P':rot.draw_puntos(1,0,0,1); 	break;
		case'L':rot.draw_aristas(184/255.0,0,138/255.0,1);  	break;
		case'A':rot.draw_solido_ajedrez(0,1,0,0,0,1); 	break;
		case'S':rot.draw_solido(0,0,1); 	break;
	}
}

}



//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)) {
	case 'Q': 
		exit(0);
		break;
	case 'P':
		tipo='P';
		break;
	case 'L':
		tipo='L';
		break;
	case 'A':
		tipo='A';
		break;
	case 'S' : 
		tipo='S';
		break;

	case 'C':
		forma = 'C';
		break;
	case 'T':
		forma = 'T';
		break;
	case 'F':
		forma = 'F';
		break;
	case 'R':
		forma = 'R';
		break;
	case 'Z':{
		if(tam<6){
		tam++;
		al++;
		break;
		}
		}
	case 'X':{
		if(tam>1){
		tam--;
		al--;
		break;
		}
		}
	case 'Y':{
		angy-=0.5;
		break;
		}
		
				
		
	/*case 'U':{
		angy+=1;
		break;
		}
	case 'H':{
		angx-=1;
		break;
		}
	case 'J':{
		angx+=1;
		break;
		}
	case 'N':{
		angz-=1;
		break;
		}
	case 'M':{
		angz+=1;
		break;
		}*/


}
glutPostRedisplay();


}
	
//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

fig.cargar_ply((char*)"beethoven.ply");
aux.cargar_ply((char*)"rotacion.ply");
rot.cargar_rotacion(aux.vertices,20);

if(argc==3){
	if(strcmp(argv[1], "-p") == 0){
		fig.vertices.clear();
		fig.caras.clear();
		fig.cargar_ply(argv[2]);
	}
	else if(strcmp(argv[1], "-r") == 0){
		aux.vertices.clear();
		aux.caras.clear();
		rot.vertices.clear();
		rot.caras.clear();
		aux.cargar_ply(argv[2]);
		rot.cargar_rotacion(aux.vertices,25);
		
	}else{
		cout<< "Usage: Practica2 -p pathPLY  or  Practica2 -r pathROTATION"<<endl;
	}

}

if(argc==5){
	if(strcmp(argv[1], "-p") == 0 && strcmp(argv[3], "-r") == 0){
		fig.vertices.clear();
		fig.caras.clear();
		fig.cargar_ply(argv[2]);
		aux.vertices.clear();
		aux.caras.clear();
		aux.cargar_ply(argv[4]);
		rot.vertices.clear();
		rot.caras.clear();
		rot.cargar_rotacion(aux.vertices,15);
		
	}else{
		cout<< "Usage: \n Practica2 \n Practica2 -p pathPLY \"OR\" Practica2 -r pathROTATION \n Practica2 -p pathPLY -r pathROTATION"<<endl;
	}

}

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Practica 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
