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

#endif