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

int EmptyQ(AQ aq) 
{
	return aq->ic == NULL;
}

void DestroyQ(AQ aq) 
{
	free(aq);
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


// -------------


APQ InitPQ(size_t dime) 
{
	APQ apq = (APQ)malloc(sizeof(TPCoada));
	apq->dime = dime;
	apq->ic = NULL;

	return apq;
}

int EmptyPQ(APQ apq) 
{
	return apq->ic == NULL;
}

void DestroyPQ(APQ apq) 
{
	// todo	
}

void InsertPQ(APQ apq, void *elem, unsigned long priority) 
{
	ACel acel = (ACel)malloc(sizeof(TCel));
	acel->urm = NULL;
	acel->info = malloc(sizeof(TPQVal));

	((TPQVal*)(acel->info))->val = malloc(apq->dime);
	memcpy(((TPQVal*)(acel->info))->val, elem, apq->dime);
	((TPQVal*)(acel->info))->priority = priority;
	
	if (apq->ic == NULL) {
		apq->ic = acel;
	} else {
		ACel p = apq->ic;

		if (priority < ((TPQVal*)(p->info))->priority) {
			acel->urm = apq->ic;
			apq->ic = acel;
		} else {
			while (p->urm != NULL && ((TPQVal*)(p->urm->info))->priority <= priority) {
				p = p->urm;
			}

			acel->urm = p->urm;
			p->urm = acel;
		}
	}
}

void* ExtractPQ(APQ apq) 
{
	if (apq->ic == NULL) {
		return NULL;
	}

	void *elem = ((TPQVal*)(apq->ic->info))->val;

	ACel celula_de_sters = apq->ic;
	apq->ic = apq->ic->urm;
	free(celula_de_sters->info);
	free(celula_de_sters);

	return elem;
}

void* PeakPQ(APQ apq)
{
	if (apq->ic == NULL) {
		return NULL;
	}

	void *elem = ((TPQVal*)(apq->ic->info))->val;
	return elem;
}

unsigned long PeakPriPQ(APQ apq)
{
	if (apq->ic == NULL) {
		return 0;
	}

	return ((TPQVal*)(apq->ic->info))->priority;	
}

