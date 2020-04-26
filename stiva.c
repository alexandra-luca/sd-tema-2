#include "lista.h"
#include "stiva.h"
#include <stdlib.h>
#include <string.h>

AS InitS(size_t dime) 
{
	AS as = (AS)malloc(sizeof(TStiva));
	as->dime = dime;
	as->vf = NULL;

	return as;
}

void DestroyS(AS as) 
{
	// todo
}

void Push(AS as, void *elem) 
{
	ACel acel = (ACel)malloc(sizeof(TCel));
	acel->urm = as->vf;
	acel->info = malloc(as->dime);
	memcpy(acel->info, elem, as->dime);

	as->vf = acel;
}

void* Pop(AS as) 
{
	if (as->vf == NULL) {
		return NULL;
	}

	void *elem = as->vf->info;
	ACel celula_de_sters = as->vf;
	as->vf = as->vf->urm;
	free(celula_de_sters);

	return elem;
}

void* Top(AS as)
{
	if (as->vf == NULL) {
		return NULL;
	}

	void *elem = as->vf->info;
	return elem;
}