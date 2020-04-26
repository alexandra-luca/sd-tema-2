#include "lista.h"
#include <stdlib.h>

#ifndef _STIVA_H_
#define _STIVA_H_

typedef struct stiva
{
	size_t dime;
	ACel vf;
} TStiva, *AS;

AS InitS(size_t dime);
void DestroyS(AS as);
void Push(AS as, void *elem);
void* Pop(AS as);
void* Top(AS as);

#endif