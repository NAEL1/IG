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

	cout << "archivo ply leido: numero de vertices: " << n_ver<< endl;

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
	cout << "archivo rotacion leido: numero de vertices: " << n_ver<< endl;

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



//*************************************************************************
// clase parte
//*************************************************************************
_parte::_parte(){}

void _parte::cargar_parte(char *archivo){
	_ply aux1;
	_rotacion aux2;
	aux1.cargar_ply(archivo);
	aux2.cargar_rotacion(aux1.vertices,40);
	vertices=aux2.vertices;
	caras=aux2.caras;
}

void _parte::draw_parte(char modo, float r1, float g1, float b1, float r2, float g2, float b2){
  switch (modo) {
        case 'P': this->draw_puntos(r1,g1,b1,3);
									break;
        case 'L': this->draw_aristas(r1,g1,b1,2);
									break;
		case 'A': this->draw_solido_ajedrez(r1,g2,b1,r2,g2,b2);
									break;
        case 'S': this->draw_solido(r1,g1,b1);
									break;
  }
}


//*************************************************************************
// clase andy
//*************************************************************************

_andy::_andy(){

	cabeza.cargar_parte((char*) "cabeza.ply");
	tronco.cargar_parte((char*) "tronco.ply");
	extremidad.cargar_parte((char *)"extremidad.ply");
	ang_cabeza=0.0;
	ang_mano=35;
	ang_antena=35;

}

void _andy::draw_andy(char modo, float r1, float g1, float b1, float r2, float g2, float b2){
	
	glMatrixMode(GL_MODELVIEW);
	
		// Tronco
		glPushMatrix();
		glTranslatef(0,2.5,0);
		tronco.draw_parte(modo,r1, g1,b1,r2,g2, b2);
		glPopMatrix();
		
		/*//cuello
		glPushMatrix();
		glTranslatef(0,4.2,0);
		glScalef(1,0.09,1);
		tronco.draw_parte('S',1,1,1,1,1,1);
		glPopMatrix();
		*/
		//Cabeza con antenas
        glPushMatrix();
        	glRotatef(ang_cabeza,0,1,0);
         	glTranslatef(0,4.1,0);
         	
         	//ojo derecho
         	glPushMatrix(); 
         	glTranslatef(0.4,0.5,0.6666);
         	glRotatef(50,1,0,0);
         	glScalef(0.2,0.2,0.2);
         	cabeza.draw_parte(modo,1,1,1,1,1,1);
         	glPopMatrix();
         	
         	//ojo izquierdo
         	glPushMatrix(); 
         	glTranslatef(-0.4,0.5,0.6666);
         	glRotatef(50,1,0,0);
         	glScalef(0.2,0.2,0.2);
         	cabeza.draw_parte('S',1,1,1,1,1,1);
         	glPopMatrix();
         	
         	//cabeza
         	cabeza.draw_parte(modo,r1, g1,b1,r2,g2, b2);
         		// antena derecha
				glPushMatrix();
					glTranslatef(0.5,0.7666,0);
					glRotatef(-ang_antena,0,0,1);
					glScalef(0.2,0.4,0.2);
					extremidad.draw_parte(modo,r1, g1,b1,r2,g2, b2);
				glPopMatrix();
				//antena Izquierda
				glPushMatrix();
					glTranslatef(-0.5,0.7666,0);
					glRotatef(ang_antena,0,0,1);
					glScalef(0.2,0.4,0.2);
					extremidad.draw_parte(modo,r1, g1,b1,r2,g2, b2);
				glPopMatrix();
		// mano derecha y pie izquierdo		    
        glPopMatrix();
        	//mano derecha
        	glPushMatrix();   
		    	glTranslatef(1.3,4,0);
		    	glRotatef(ang_mano,1,0,0);
		    	glScalef(0.9,1,0.9);
		    	glTranslatef(0,-1.0,0);
		    	extremidad.draw_parte(modo,r1, g1,b1,r2,g2, b2);
		    glPopMatrix();
		    
		    //mano izquierda
        	glPushMatrix();   
		    	glTranslatef(-1.3,4,0);
		    	glRotatef(-ang_mano,1,0,0);
		    	glScalef(0.9,1,0.9);
		    	glTranslatef(0,-1.0,0);
		    	extremidad.draw_parte(modo,r1, g1,b1,r2,g2, b2);
		    glPopMatrix();
                  
            //pie derecho
        	glPushMatrix();   
		    	glTranslatef(0.45,1.5,0);
		    	glRotatef(-ang_mano,1,0,0);
		    	glScalef(0.9,1,0.9);
		    	glTranslatef(0,-1.0,0);
		    	extremidad.draw_parte(modo,r1, g1,b1,r2,g2, b2);
		    glPopMatrix();
		    
		    //pie izquierdo
        	glPushMatrix();   
		    	glTranslatef(-0.45,1.5,0);
		    	glRotatef(ang_mano,1,0,0);
		    	glScalef(0.9,1,0.9);
		    	glTranslatef(0,-1.0,0);
		    	extremidad.draw_parte(modo,r1, g1,b1,r2,g2, b2);
		    glPopMatrix();   
		            
        glPopMatrix();
        
        
        
}






