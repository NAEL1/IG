//**************************************************************************
// Práctica 2 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;

//const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor=2);

//void	draw_puntos_color(int grosor=4);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor=2);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);

};





//*************************************************************************
// clase ply
//*************************************************************************


class _ply: public _triangulos3D
{

public:

	_ply();
	void cargar_ply(char * archivo );

};


//*************************************************************************
// clase rotacion
//*************************************************************************

class _rotacion: public _triangulos3D
{

public:
	_rotacion();
	void cargar_rotacion(vector<_vertex3f> &perfil, int num);

};


//*************************************************************************
// clase parte
//*************************************************************************

class _parte: public _triangulos3D{
public:
	_parte();
  void cargar_parte(char * archivo);
  void draw_parte(char modo, float r1, float g1, float b1, float r2, float g2, float b2);
};



//*************************************************************************
// clase andy
//*************************************************************************


class _andy: public _triangulos3D{

private:
	_parte cabeza;
	_parte tronco;
	_parte extremidad;
	

public:
	_andy();
	void draw_andy(char modo, float r1, float g1, float b1, float r2, float g2, float b2);
	
	
float ang_cabeza;
int ang_mano,ang_antena;
};
