#include "lista.h"
#include <stdlib.h>

#ifndef _COADA_H_
#define _COADA_H_

typedef struct coada
{
	size_t dime;
	ACel ic, sc;
} TCoada, *AQ;

AQ InitQ(size_t dime);
void DestroyQ(AQ aq);
void InsertQ(AQ aq, void *elem);
void* ExtractQ(AQ aq);
void* PeakQ(AQ aq);
int EmptyQ(AQ aq);

typedef struct 
{
	size_t dime;
	ACel ic;
} TPCoada, *APQ;

typedef struct 
{
	void *val;
	int priority;
} TPQVal;

APQ InitPQ(size_t dime);
void DestroyPQ(APQ apq);
void InsertPQ(APQ apq, void *elem, unsigned long priority);
void* ExtractPQ(APQ apq);
void* PeakPQ(APQ apq);
int EmptyPQ(APQ apq);
unsigned long PeakPriPQ(APQ apq);

#endif