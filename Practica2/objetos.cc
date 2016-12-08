#include "objetos.h"
#include "file_ply_stl.h"

using namespace std;
//*************************************************************************
// clase punto
//*************************************************************************


_puntos3D::_puntos3D(){};

void 	_puntos3D::draw_puntos(float r, float g, float b, int grosor){

	int i;
	glPointSize(grosor);
	glColor3f(r,g,b);
	glBegin(GL_POINTS);
		for(i=0; i<vertices.size();i++)
			glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
	glEnd();
}
/*
void	draw_puntos_color(int grosor){
	
	int i;
	glPointSize(grosor);
	
	glBegin(GL_POINTS);
		for(i=0; i<vertices.size();i++)
			glColor3f(r/vertices[i].x,g/vertices[i].y,b/vertices[i].z);
			glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
	glEnd();
}
*/
//*************************************************************************
// clase triángulo
//*************************************************************************


_triangulos3D::_triangulos3D(){};

void 	_triangulos3D::draw_aristas(float r, float g, float b, int grosor){

	int i;
	glLineWidth(grosor);
	glColor3f(r,g,b);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
		for(i=0;i<caras.size();i++){
			glVertex3f(vertices[caras[i].x].x,vertices[caras[i].x].y,vertices[caras[i].x].z);
			glVertex3f(vertices[caras[i].y].x,vertices[caras[i].y].y,vertices[caras[i].y].z);
			glVertex3f(vertices[caras[i].z].x,vertices[caras[i].z].y,vertices[caras[i].z].z);
		}
	glEnd();
}

void    _triangulos3D::draw_solido(float r, float g, float b){
	int i;
	glColor3f(r,g,b);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
		for(i=0;i<caras.size();i++){
			glVertex3f(vertices[caras[i].x].x,vertices[caras[i].x].y,vertices[caras[i].x].z);
			glVertex3f(vertices[caras[i].y].x,vertices[caras[i].y].y,vertices[caras[i].y].z);
			glVertex3f(vertices[caras[i].z].x,vertices[caras[i].z].y,vertices[caras[i].z].z);
		}
	glEnd();
}

void 	_triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2){
	int i;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
		for(i=0;i<caras.size();i++){
			if ( i %2 == 0 ) 
				glColor3f(r1,g1,b1);
			else 
				glColor3f(r2,g2,b2);
			glVertex3f(vertices[caras[i].x].x,vertices[caras[i].x].y,vertices[caras[i].x].z);
			glVertex3f(vertices[caras[i].y].x,vertices[caras[i].y].y,vertices[caras[i].y].z);
			glVertex3f(vertices[caras[i].z].x,vertices[caras[i].z].y,vertices[caras[i].z].z);
		}
	glEnd();
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam){
	vertices.resize(8);
	// los 8 vertices 
	//	 7	 6
	// 	4	5̣   
	//	 3	 2
	//	0	1
		
	vertices[0].x=-tam ;vertices[0].y=-tam ;vertices[0].z=tam ;
	vertices[1].x=tam ;vertices[1].y=-tam ;vertices[1].z=tam ;
	vertices[2].x=tam ;vertices[2].y=-tam ;vertices[2].z=-tam ;
	vertices[3].x=-tam ;vertices[3].y=-tam ;vertices[3].z=-tam ;
	vertices[4].x=-tam ;vertices[4].y=tam ;vertices[4].z=tam ;
	vertices[5].x=tam ;vertices[5].y=tam ;vertices[5].z=tam ;
	vertices[6].x=tam ;vertices[6].y=tam ;vertices[6].z=-tam ;
	vertices[7].x=-tam ;vertices[7].y=tam ;vertices[7].z=-tam ;

	// los 12  triangulos descomposicion de las 6 caras desde la fronta hacia contra reloj luego suelo y techo
	//												   ¡¡ojo!!
	//	4---5		5---6		6---7		7---4		0---1		7---6
	//	| / |		| / |		| / |		| / |		| / |		| / |
	//	0---1		1---2		2---3		3---0		3---2		4---5
	caras.resize(12);
	caras[0].x=0 ;caras[0].y=1 ;caras[0].z=5 ;
	caras[1].x=5 ;caras[1].y=4 ;caras[1].z=0 ;
	caras[2].x=1 ;caras[2].y=2 ;caras[2].z=6 ;
	caras[3].x=6 ;caras[3].y=5 ;caras[3].z=1 ;
	caras[4].x=2 ;caras[4].y=3 ;caras[4].z=7 ;
	caras[5].x=7 ;caras[5].y=6 ;caras[5].z=2 ;
	caras[6].x=3 ;caras[6].y=0 ;caras[6].z=4 ;
	caras[7].x=4 ;caras[7].y=7 ;caras[7].z=3 ;
	caras[8].x=3 ;caras[8].y=2 ;caras[8].z=1 ;
	caras[9].x=1 ;caras[9].y=0 ;caras[9].z=3 ;
	caras[10].x=4 ;caras[10].y=5 ;caras[10].z=6 ;
	caras[11].x=6 ;caras[11].y=7 ;caras[11].z=4 ;

}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al){
	
	vertices.resize(5);
	// los 5 vertices
	//			4
	//		  /    \
	//		 3------2
	//		 |/	   \|
	//		 0------1
	vertices[0].x=-tam ;vertices[0].y=-al/2 ;vertices[0].z=tam ;
	vertices[1].x=tam ;vertices[1].y=-al/2 ;vertices[1].z=tam ;
	vertices[2].x=tam ;vertices[2].y=-al/2 ;vertices[2].z=-tam ;
	vertices[3].x=-tam ;vertices[3].y=-al/2 ;vertices[3].z=-tam ;
	vertices[4].x=0 ;vertices[4].y=al/2 ;vertices[4].z=0 ;
	
	caras.resize(6);
	// los 6 triangulos 
	//		4			4			4			4        0---1
	//	   / \		   / \		   / \		   / \		 | / |
	//    0---1		  1---2		  2---3		  3---0		 3---2
	//
	caras[0].x=0 ;caras[0].y=1 ;caras[0].z=4 ;
	caras[1].x=1 ;caras[1].y=2 ;caras[1].z=4 ;
	caras[2].x=2 ;caras[2].y=3 ;caras[2].z=4 ;
	caras[3].x=3 ;caras[3].y=0 ;caras[3].z=4 ;
	caras[4].x=3 ;caras[4].y=2 ;caras[4].z=1 ;
	caras[5].x=1 ;caras[5].y=0 ;caras[5].z=3 ;
}


//*************************************************************************
// clase _ply
//*************************************************************************


_ply::_ply(){};


void _ply::cargar_ply(char *archivo){

	int n_ver, n_car;
	_vertex3f ver_aux;
	_vertex3i car_aux;
    vector<float> ver_ply;
    vector<int> car_ply;
    _file_ply objeto;

	objeto.open(archivo);
	objeto.read(ver_ply,car_ply);

	n_ver=ver_ply.size()/3;
	n_car=car_ply.size()/3;


	for(int i=0;i<n_ver;i++){
		ver_aux.x=ver_ply[i*3];
		ver_aux.y=ver_ply[i*3+1];
		ver_aux.z=ver_ply[i*3+2];

		vertices.push_back(ver_aux);
	}

	for(int i=0;i<n_car;i++){
		car_aux.x=car_ply[i*3];
		car_aux.y=car_ply[i*3+1];
		car_aux.z=car_ply[i*3+2];

		caras.push_back(car_aux);
	}


}






//*************************************************************************
// clase rotacion
//*************************************************************************


_rotacion::_rotacion(){};

void _rotacion::cargar_rotacion(vector<_vertex3f> &perfil, int num){

	int n_ver, n_perf;
	_vertex3f ver_aux;
	_vertex3i car_aux;
	 float angulo = 2.0*M_PI;
	 
	for(int i=0;i<perfil.size();i++){
    	vertices.push_back(perfil[i]);
  	}
  	
  	for(int j=1;j<num;j++){
		for(int i=0;i<perfil.size();i++){
		
			ver_aux.x = cos((angulo*j)/(1.0*num))*perfil[i].x + sin((angulo*j)/(1.0*num))*perfil[i].z;
			ver_aux.y = perfil[i].y;
			ver_aux.z = -sin((angulo*j)/(1.0*num))*perfil[i].x + cos((angulo*j)/(1.0*num))*perfil[i].z;

			vertices.push_back(ver_aux); 
		}
	}
	n_ver=vertices.size();
	n_perf=perfil.size();

	for(int i=0; i<n_ver ;i++){
		
		for(int j = 0; j < n_perf-1; j++) {
			car_aux.x=i ;
			car_aux.y=(i+1) % n_ver;
			car_aux.z=(i+n_perf) % n_ver;
			caras.push_back(car_aux);

			car_aux.x=(i+1) % n_ver;
			car_aux.y=(i+1+n_perf) % n_ver;
			car_aux.z=(i+n_perf) % n_ver;
			caras.push_back(car_aux);

			i++;
		}
	}
	

// Caras de la tapa inferior

	if(fabs(perfil[0].x)>0.0) {

		ver_aux.x = 0.0;
		ver_aux.y = perfil[0].y;
		ver_aux.z = 0.0;

    	vertices.push_back(ver_aux);

		for(int i=0;i<num;i++){
			car_aux.x= vertices.size()-1 ;
			car_aux.y=i*n_perf;
			car_aux.z=((i+1)%num)*n_perf;
			

			caras.push_back(car_aux);
		}

  }
  
    // Caras de la tapa superior

  if(fabs(perfil[n_perf-1].x)>0.0) {
    ver_aux.x = 0.0;
    ver_aux.y = perfil[n_perf-1].y;
    ver_aux.z = 0.0;

    vertices.push_back(ver_aux);

    for(int i=0;i<num;i++){
    	car_aux.x= vertices.size()-1 ;
		car_aux.y=(i*n_perf)+(n_perf-1);
		car_aux.z=(((i+1)%num)*n_perf)+(n_perf-1);
    	caras.push_back(car_aux);

    }

  }


}
