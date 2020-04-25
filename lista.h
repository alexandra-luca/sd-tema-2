
#ifndef _LISTA_H_
#define _LISTA_H_

typedef struct cel
{
	struct cel *urm;
	void *info;
} TCel, *ACel;

#endif
