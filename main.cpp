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
public:
	Grafo();
	~Grafo();
	void insertar_nodo(int ciudad);
	void agrega_arista(Tnodo &, Tnodo &, Tarista &);
	void insertar_arista(int ini, int fin);
	void vaciar_aristas(Tnodo &);
	void eliminar_nodo(int ciudad);
	void eliminar_arista(int inicio, int fin);
	void mostrar_grafo();
	void mostrar_aristas(int var);
	void pintar(int ciudad, int color);
};
Grafo::Grafo(){
	p = NULL;
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
		// cout<< "borrando"<<endl;
	}
	mostrar_grafo();
	delete(p);
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
		t = p;
		while(t->sgte!=NULL){
			t = t->sgte;
		}
		t->sgte = nuevo;
	}
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

}
void Grafo::insertar_arista(int ini,int fin){
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
	   	//	cout << aux->ciudad << "-" <<q->destino->ciudad << endl;
	        r=q;
	        q=q->sgte;
	        delete(r);
	   	}
	   	delete(q);
    }
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
}
void Grafo::eliminar_arista(int inicio,int fin){
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
void Grafo::pintar(int ciudad, int color){
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
int main(){
	Grafo G;
	G.insertar_nodo(1);
	G.insertar_nodo(2);
	G.insertar_nodo(3);
	G.insertar_nodo(4);
	G.insertar_arista(1,2);
	// G.insertar_arista(1,3);
	// G.insertar_arista(1,4);
	G.insertar_arista(2,1);
	// G.insertar_arista(2,3);
	// G.insertar_arista(2,4);
	G.insertar_arista(3,1);
	// G.insertar_arista(3,2);
	// G.insertar_arista(3,4);
	G.insertar_arista(4,1);
	// G.insertar_arista(4,2);
	// G.insertar_arista(4,3);

	G.pintar(2,5);
	G.pintar(3,5);
	G.pintar(3,2);
	G.pintar(1,5);
	G.mostrar_grafo();
	G.~Grafo();

	return 0;
}