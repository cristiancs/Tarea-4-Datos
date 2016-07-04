#include <iostream>
#include <stdlib.h>     /* malloc, free, rand */
using namespace std;


struct nodo{
	char ciudad;
	struct nodo *sgte;
	struct arista *ady;//puntero hacia la primera arista del nodo
};
struct arista{
	struct nodo *destino;//puntero al nodo de llegada
	struct arista *sgte;
};
typedef struct nodo *Tnodo;//  Tipo Nodo
typedef struct arista *Tarista; //Tipo Arista

class Arbol
{
private:
		Tnodo p;//puntero cabeza
public:
	Arbol();
	void insertar_nodo(char ciudad);
	void agrega_arista(Tnodo &, Tnodo &, Tarista &);
	void insertar_arista(char ini, char fin);
	void vaciar_aristas(Tnodo &);
	void eliminar_nodo(char ciudad);
	void eliminar_arista(char inicio, char fin);
	void mostrar_grafo();
	void mostrar_aristas(char var);
};

void Arbol::insertar_nodo(char ciudad){
	Tnodo t,nuevo=new struct nodo;
	nuevo->ciudad = ciudad;
	nuevo->sgte = NULL;
	nuevo->ady=NULL;
// Verificar si hay nodos
	if(p==NULL){
		p = nuevo;
	}
// Buscar donde lo podemos insertar
	else{
		t = p;
		while(t->sgte!=NULL)
		{
			t = t->sgte;
		}
		t->sgte = nuevo;
	}
}
void Arbol::agrega_arista(Tnodo &aux, Tnodo &aux2, Tarista &nuevo){
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
		cout<<"ARISTA AGREGADA...!!!!";
	}

}
void Arbol::insertar_arista(char ini,char fin){
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
void Arbol::vaciar_aristas(Tnodo &aux)
{
    Tarista q,r;
    q=aux->ady;
    while(q->sgte!=NULL)
    {
        r=q;
        q=q->sgte;
        delete(r);
    }
}
void Arbol::eliminar_nodo(char ciudad){
	Tnodo aux,ant;
	aux=p;
	// Grafo Vacio
	if(p==NULL){
		return;
	}
	while(aux!=NULL){
		if(aux->ciudad==ciudad){
			if(aux->ady!=NULL)
				vaciar_aristas(aux);
			if(aux==p){
				p=p->sgte;
				delete(aux);
				return;
			}
			else {
				ant->sgte = aux->sgte;
				delete(aux);
				cout<<"NODO ELIMINADO...!!!!";
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
void Arbol::eliminar_arista(char inicio,char fin){
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
void Arbol::mostrar_grafo(){
	Tnodo ptr;
	Tarista ar;
	ptr=p;
	cout<<"NODO|LISTA DE ADYACENCIA\n";
	while(ptr!=NULL){
	   cout<<"   "<<ptr->ciudad<<"|";
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
void Arbol::mostrar_aristas(char var)
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
int main(){
	return 0;
}