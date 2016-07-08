#include <iostream>
#include <stdlib.h>     /* malloc, free, rand */
using namespace std;


struct nodo{
	int ciudad;
	int color;
	struct nodo *sgte;
	struct arista *ady;//puntero hacia la primera arista del nodo
};
struct arista{
	struct nodo *destino;//puntero al nodo de llegada
	struct arista *sgte;
};
typedef struct nodo *Tnodo;//  Tipo Nodo
typedef struct arista *Tarista; //Tipo Arista

class Grafo
{
private:
		Tnodo p;//puntero cabeza
		int nArcos, nVertices;
public:
	Grafo();
	~Grafo();
	void insertar_nodo(int ciudad);
	void agrega_arista(Tnodo &, Tnodo &, Tarista &);
	void setEdge(int ini, int fin);
	void vaciar_aristas(Tnodo &);
	void eliminar_nodo(int ciudad);
	void deleteEdge(int inicio, int fin);
	void mostrar_grafo();
	void mostrar_aristas(int var);
	void setMark(int ciudad, int color);
	int getMark(int ciudad);
	int nVertex();
	int nEdges();
	int first(int nodo);
	int next(int nodo, int posicion);
};
Grafo::Grafo(){
	p = NULL;
	nArcos = 0;
	nVertices = 0;
}
Grafo::~Grafo(){
	Tnodo aux,next;
	aux=p;
	next = NULL;
	// Grafo Vacio
	if(p==NULL){
		return;
	}
	while(aux!=NULL){
		next = aux->sgte;
		eliminar_nodo(aux->ciudad);
		aux=next;
	}
}
void Grafo::insertar_nodo(int ciudad){
	Tnodo t,nuevo=new struct nodo;
	nuevo->ciudad = ciudad;
	nuevo->sgte = NULL;
	nuevo->ady=NULL;
	nuevo->color=-1;
// Verificar si hay nodos
	if(p==NULL){
		p = nuevo;
	}
// Buscar donde lo podemos insertar
	else{
		int flag = false;
		t = p;
		while(t->sgte!=NULL){
			if(t->sgte->ciudad == ciudad){
				flag = true;
			}
			t = t->sgte;
		}
		if(flag == false && ciudad != 0){
		//	cout<< "agregando "<<ciudad << endl;
			t->sgte = nuevo;
		}
		else{
			// delete(t);
			delete(nuevo);
		}
	}
	nVertices+=1;
}
void Grafo::agrega_arista(Tnodo &aux, Tnodo &aux2, Tarista &nuevo){
	Tarista q;
	if(aux->ady==NULL){
		aux->ady=nuevo;
		nuevo->destino=aux2;
	}
	else{
	q=aux->ady;
		while(q->sgte!=NULL)
			q=q->sgte;
		nuevo->destino=aux2;
		q->sgte=nuevo;
	}
	nArcos+=1;
}
void Grafo::setEdge(int ini,int fin){
	Tarista nuevo=new struct arista;
	Tnodo aux, aux2;

	// Grafo vacio
	if(p==NULL){
		return;
	}
	nuevo->sgte=NULL;
	aux=p;
	aux2=p;
	while(aux2!=NULL){
		if(aux2->ciudad==fin){
			break;
		}
		aux2=aux2->sgte;
	}
	while(aux!=NULL){
		if(aux->ciudad==ini){
			agrega_arista(aux,aux2, nuevo);
			return;
		}
		aux = aux->sgte;
	}
}
void Grafo::vaciar_aristas(Tnodo &aux)
{
    Tarista q,r;
    q=aux->ady;
    if(q->sgte == NULL){
    	delete(q);
    }
    else{
		while(q->sgte!=NULL){
	        r=q;
	        q=q->sgte;
	        delete(r);
	   	}
	   	delete(q);
    }
    aux->ady = NULL;
  //  mostrar_grafo();
}
void Grafo::eliminar_nodo(int ciudad){
	Tnodo aux,ant;
	aux=p;
	// Grafo Vacio
	if(p==NULL){
		return;
	}
	while(aux!=NULL){
		if(aux->ciudad==ciudad){
			if(aux->ady!=NULL){
				vaciar_aristas(aux);
			}
			if(aux==p){
				p=p->sgte;
				delete(aux);
				return;
			}
			else {
				ant->sgte = aux->sgte;
				delete(aux);
				return;
			}
		}
		else
		{
			ant=aux;
			aux=aux->sgte;
		}
	}

	nVertices -=1;
}
void Grafo::deleteEdge(int inicio,int fin){
	Tnodo aux, aux2;
	Tarista q,r;
	aux=p;
	aux2=p;
	while(aux2!=NULL){
		if(aux2->ciudad==fin){
			break;
		}
		else
			aux2=aux2->sgte;
	}
	while(aux!=NULL){
		if(aux->ciudad==inicio){
			q=aux->ady;
			while(q!=NULL){
				if(q->destino==aux2){
					if(q==aux->ady)
						aux->ady=aux->ady->sgte;
					else
						r->sgte=q->sgte;
					delete(q);
					return;
				}
			}
			r=q;
			q=q->sgte;
		}
		aux = aux->sgte;
	}
	nArcos-=1;
}
void Grafo::mostrar_grafo(){
	Tnodo ptr;
	Tarista ar;
	ptr=p;
	cout<<"NODO|COLOR|LISTA DE ADYACENCIA|\n";
	while(ptr!=NULL){
	   cout<<"   "<<ptr->ciudad<<"|";
   	   cout<<"   "<<ptr->color<<"|";
	if(ptr->ady!=NULL)
	{
		ar=ptr->ady;
		while(ar!=NULL){
		   cout<<" "<<ar->destino->ciudad;
			ar=ar->sgte;
		}
	}
	ptr=ptr->sgte;
	cout<<endl;
	}
}
void Grafo::mostrar_aristas(int var)
{
	Tnodo aux;
	Tarista ar;
	aux=p;
	while(aux!=NULL)
	{
		if(aux->ciudad==var){
			if(aux->ady==NULL){
				cout<<"EL NODO NO TIENE ARISTAS...!!!!";
				return;
			}
			else{
				cout<<"NODO|LISTA DE ADYACENCIA\n";
				cout<<"   "<<aux->ciudad<<"|";
				ar=aux->ady;

				while(ar!=NULL){
					cout<<ar->destino->ciudad<<" ";
					ar=ar->sgte;
				}
				cout<<endl;
				return;
			}
		}
		else
			aux=aux->sgte;
	}
}
void Grafo::setMark(int ciudad, int color){
	Tnodo aux;
	aux=p;
	// Grafo Vacio
	if(p==NULL){
		return;
	}
	while(aux!=NULL){
		if(aux->ciudad==ciudad){
			aux->color = color;
			return;
		}
		else{
			aux=aux->sgte;
		}
	}
}
int Grafo::getMark(int ciudad){
	Tnodo aux;
	aux=p;
	// Grafo Vacio
	if(p==NULL){
		return -1;
	}
	while(aux!=NULL){
		if(aux->ciudad==ciudad){
			return aux->color;
		}
		else{
			aux=aux->sgte;
		}
	}
	return -1;
}
int Grafo::nVertex(){
	return nVertices;
}
int Grafo::nEdges(){
	return nArcos;
}
int Grafo::first(int ciudad){
	Tnodo aux;
	aux=p;
	// Grafo Vacio
	if(p==NULL){
		return -1;
	}
	while(aux!=NULL){
		if(aux->ciudad==ciudad){

			return aux->ady->destino->ciudad;
		}
		else{
			aux=aux->sgte;
		}
	}
	return -1;
}
int Grafo::next(int ciudad, int posicion){
	Tnodo aux;
	Tarista ar;
	aux=p;
	// Grafo Vacio
	if(p==NULL){
		return -1;
	}
	while(aux!=NULL){
		if(aux->ciudad==ciudad){
			ar=aux->ady;
			int i = 0;
			while(ar!=NULL){
				if(i == posicion){
					return ar->destino->ciudad;
				}
				ar=ar->sgte;
				i++;
			}
		}
		else{
			aux=aux->sgte;
		}
	}
	return -1;
}


int main(){
	Grafo G;
	int N, // Número de ciudades a trabjar
	M,     // Cantidad de vuelos entre pares de ciudades que tiene la compañía
	Q,     // El número de consultas que se harán sobre el grafo
	i,
	aux1,
	aux2;    
	cin >> N;
	cin >> M;

	// Procesar
	// Agregar Nodos y Arcos
	i = 0;
	while(i < M){
		cin >> aux1;
		G.insertar_nodo(aux1);
		cin >> aux2;
		G.insertar_nodo(aux2);
		G.setEdge(aux1,aux2);
		i++;
	}
	G.mostrar_grafo();
	//Número de consultas a realizar
	cin >> Q;
	i = 0;
	int w;
	cout<<Q<<endl;
	while(i < Q){
		cin >> aux1; // Vertice a trabjar
		//cout<<aux1<<endl;
	// Buscar vertices no alcanzables desde aux1;
		//vertices que llego desde aux1;
		for(w= G.first(aux1); w<G.nVertex(); w=G.next(aux1,w)){
			cout<<G.nVertex()<<endl;
			cout<<w<<endl;
			cout<<G.next(aux1,w)<<endl;
			G.setMark(w,Q);
		}
		//recorrer grafo y ver si esta marcado;
		int cvert=0;
		for (i=0; i<G.nVertex(); i++){
			if (G.getMark(i)!=Q){
				//obtener ese nodo que no es alcanzable de aux1 
				//SACAR ESOS NODOS...
				//s
				cvert++;
			}
		}
	
		i++;
	 }



	// Salida

	// cout << Q << endl;


	G.~Grafo();

	return 0;
}