#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this=NULL;
    this=(LinkedList*)malloc(sizeof(LinkedList));
    if(this!=NULL)
    {
    	this->pFirstNode=NULL;
    	this->size=0;
    }
    return this;
}
/** \brief Retorna la cantidad de elementos de la lista
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	returnAux=this->size;
    }
    return returnAux;
}
/** \brief  Obtiene un nodo de la lista
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL
 *  o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNodoAux;
    int indexAuxiliar;
    pNodoAux=NULL;
    if(this!=NULL && nodeIndex>=0 && nodeIndex<ll_len(this))
    {
    	pNodoAux=this->pFirstNode;
    	for (indexAuxiliar=0;  indexAuxiliar<nodeIndex; ++indexAuxiliar)
    	{
			pNodoAux=pNodoAux->pNextNode;
		}
    }
	return pNodoAux;
}
/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL
 *  o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{

	return getNode(this,nodeIndex);
}
/*
 * Node* test_getNode(LinkedList* this, int nodeIndex)
{

	return getNode(this, nodeIndex);
}
 */
/** \brief Agrega y enlaza un nuevo nodo a la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o
 * (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	 int returnAux=-1;
	    Node* pNodo;
	    Node* pNodoAnterior;
	    if(this!=NULL && nodeIndex>=0 && nodeIndex<=ll_len(this))
	    {
			pNodo = (Node*)malloc(sizeof(Node));
			if(pNodo!=NULL)
			{
				pNodo->pElement=pElement;
				if(nodeIndex==0)
				{
					pNodo->pNextNode = this->pFirstNode;
					this->pFirstNode = pNodo;
				}else
					{
					pNodoAnterior=getNode(this,nodeIndex-1);
					pNodo->pNextNode = pNodoAnterior->pNextNode;
					pNodoAnterior->pNextNode = pNodo;
					}
				this->size++;
				returnAux=0;
			}
	    }
return returnAux;
}
/** \brief Permite realizar el test de la funcion addNode la cual es privada
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}

/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL) //if(pElement!=NULL)???
    	{
    		addNode(this,this->size,pElement);
			returnAux=0;
		}
return returnAux;
}
/** \brief Permite realizar el test de la funcion addNode la cual es privada
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL
 *  o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 */
void* ll_get(LinkedList* this, int index)
{
	void* returnAux=NULL;
	Node* pNodoAux;
	if(this!=NULL && index>=0 && index<ll_len(this)) // && ll_len(this)>0
		{
		pNodoAux=getNode(this,index);
		returnAux=pNodoAux->pElement;
	   	}
return returnAux;
}
/** \brief Modifica un elemento de la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista
 * 	es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
int ll_set(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    Node* pNodoAux=NULL;
    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	pNodoAux=getNode(this, index);
    	pNodoAux->pElement=pElement;
    	returnAux=0;
    }
    return returnAux;
}
/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 *  o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
	int returnAux=-1;
	Node* pNodoAux;
	Node* pNodoAnterior;
	if(this != NULL && index >= 0 && index < ll_len(this))
	    {
	    if (index == 0)
	        {
	        	pNodoAux = this->pFirstNode;
	            this->pFirstNode = pNodoAux->pNextNode;
	            free(pNodoAux);

	        }
	        else if(index>=1)
				{
				pNodoAux = getNode(this,index);
				pNodoAnterior = getNode(this,index-1);
				pNodoAnterior->pNextNode=pNodoAux->pNextNode;
				free(pNodoAux);
				}
				this->size--;
				returnAux = 0;
		}
return returnAux;
}
/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux=-1;
    if(this!=NULL)
		{
    	for (int index=0;  index<ll_len(this); ++index)
			{
			ll_remove(this,0);// index
			}
			returnAux=0;
		}
return returnAux;
}
/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{

	int returnAux=-1;
    if(this!=NULL)
		{
		ll_clear(this);
		free(this);
		returnAux=0;
		}
return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux=-1;
    Node* pNodoAux;
    if(this!=NULL)
   		{
    	pNodoAux=this->pFirstNode;
   		for (int index=0;  index<ll_len(this); ++index)
			{
			if(pNodoAux->pElement==pElement)
				{
				returnAux=index;
				break;
				}
			pNodoAux=pNodoAux->pNextNode;
			}
   		}
return returnAux;
}
/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	if(ll_len(this)==0)
			{
    		returnAux=1;
			}else
				{
				returnAux=0;
				}
    }
return returnAux;
}
/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o
 * (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL && index>=0 && index<=this->size)
    {
    	returnAux=addNode(this, index, pElement);
    }
return returnAux;
}
/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o
 * (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    if(this!=NULL  && index>=0 && index<=this->size )
		{
		returnAux=ll_get(this, index);
		ll_remove(this, index);
		}
return returnAux;
}
/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux=-1;
    if(this!=NULL)
    	{
    	if(ll_indexOf(this,pElement)>=0)
			{
				returnAux=1;
			}else
				{
				returnAux=0;
				}
    	}
 return returnAux;
}
/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
	int returnAux=-1;
	Node* pNodoAuxiliar;
	//void* 	pElemntsThis2;
	int cantidad=0;
	if(this!=NULL && this2!=NULL)
	{
		pNodoAuxiliar=this2->pFirstNode;
		for (int i = 0; i < ll_len(this2); ++i)
			{
				if(ll_contains(this,pNodoAuxiliar->pElement)==1)
				{
					cantidad++;
				}
			pNodoAuxiliar=pNodoAuxiliar->pNextNode;
			}
		if(cantidad==ll_len(this2))
			{
			returnAux=1;
			}else
			{
				returnAux=0;
			}
	}
return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* pElementAux;
    int len=ll_len(this);
    if((this != NULL) && (from >= 0 && len >= to)) //(this!=NULL && from>=0 && from<=len && to>=from && to<=0)
    {
    	cloneArray=ll_newLinkedList();
    	if(cloneArray!=NULL)
    	{
    		for (int i=from ; i<to; ++i)
			{
    		pElementAux=ll_get(this, i);
    		ll_add(cloneArray,pElementAux);
			}
    	}
    }
 return cloneArray;
}
/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    void* pElementAux;
    if(this!=NULL)
    {
    	cloneArray=ll_newLinkedList();
    	for (int i=0 ; i<ll_len(this); ++i)
    		{
    	    pElementAux=ll_get(this, i);
    	    ll_add(cloneArray,pElementAux);
    		}
    }
return cloneArray;
}
/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int estadoOrden=1;
    int criterio;
    void* pElement0;
    void* pElement1;
    if(this!=NULL &&pFunc!=NULL && (order==0 || order==1))
    {
    	while (estadoOrden)
    	{
    		estadoOrden=0;
    		for (int i = 0; i < ll_len(this)-1; ++i)//SWAP
    		{
    			pElement0=ll_get(this, i);
				pElement1=ll_get(this, i+1);
				criterio=pFunc(pElement0,pElement1);
				if((order==1 && criterio==1) || (order==0 && criterio==-1))
				{
					ll_set(this, i, pElement1);
					ll_set(this, i+1, pElement0);
					estadoOrden=1;
				}
			}
    	}
    	returnAux=0;
    }
return returnAux;
}
//MAP: Permite Transformar los elementos de una lista
int ll_map(LinkedList* this, void (*pFunc)(void*))
{
	int returnAux = -1;
	void* pElement;
	if(this != NULL && pFunc != NULL)
		{
		for(int i = 0; i< ll_len(this); i++)
			{
			pElement = ll_get(this, i);//MAPEO
			if(pElement != NULL)
				{
				pFunc(pElement);
				}
			}
		returnAux = 0;
		}
return returnAux;
}
//FILTER	: Filtra todos los elementos que cumplan la condicion implementada por la funcion dada
int ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	int returnAux=-1;
	int criterio;
	void* pElement;
		if(this != NULL && pFunc != NULL)
			{
			for(int i = 0; i< ll_len(this); i++)
				{
				pElement = ll_get(this, i);
				if(pElement != NULL)
					{
					criterio=pFunc(pElement);//FILTRO
					if(criterio==0)
						{
						returnAux=ll_remove(this, i);
						}
					}
				}
			}
return returnAux;
}
//REDUCE: Ejecuta una funcion reductora sobre cada elemento, devolviendo como unico resultado un unico valor
//int ll_reduce(LinkedList* this, int (*pFunc)(void*))//UNICA NO VISTA OJOOOOOTA
/*
int ll_reduceInt(LinkedList* this, Function pFunc)
{
	void *pAux;
	int i;
	int acum = 0;

	if (this != NULL && pFunc != NULL)
	{
		for (i = 0; i < ll_len(this); i++)
		{
			pAux = ll_get(this, i);
			if (pAux != NULL)
			{
				acum = acum + pFunc(pAux);
			}
		}
	}
	return acum;
}
*/


