#include "lista.h"
#include "coada.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

AQ InitQ(size_t dime) 
{
	AQ aq = (AQ)malloc(sizeof(TCoada));
	aq->dime = dime;
	aq->ic = NULL;
	aq->sc = NULL;

	return aq;
}

void DestroyQ(AQ aq) 
{
	// todo	
}

void InsertQ(AQ aq, void *elem) 
{
	ACel acel = (ACel)malloc(sizeof(TCel));
	acel->urm = NULL;
	acel->info = malloc(aq->dime);
	memcpy(acel->info, elem, aq->dime);
	
	if (aq->sc == NULL) {
		aq->sc = acel;
		aq->ic = acel;
	} else {
		aq->sc->urm = acel;
		aq->sc = acel;
	}
}

void* ExtractQ(AQ aq) 
{
	if (aq->ic == NULL) {
		return NULL;
	}

	void *elem = aq->ic->info;

	ACel celula_de_sters = aq->ic;
	aq->ic = aq->ic->urm;
	free(celula_de_sters);

	return elem;
}

void* PeakQ(AQ aq)
{
	if (aq->ic == NULL) {
		return NULL;
	}

	void *elem = aq->ic->info;
	return elem;
}
