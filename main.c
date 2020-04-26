#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "lista.h"
#include "coada.h"
#include "stiva.h"

typedef struct 
{
	int id;
	int size;
} TResursa;

typedef struct
{
	char url[21];
	int num_res;
	TResursa *resources;
} TPagina;

typedef struct 
{
	TPagina *apag;
	AS back_stack;
	AS forward_stack;
} TTab;

TPagina* PaginaInit(char url[], int num_res) 
{
	// todo
}

TTab* TabInit() 
{
	// todo
}

void PaginaDestroy(TPagina* apag) 
{
	// todo
}

void TabDestroy(TTab* atab) 
{
	// todo
}

void TabBack(TTab* atab) 
{
	// tdo
}

void TabForward(TTab* atab) 
{
	// todo
}

void TabGoto(TTab* atab, char url[]) 
{
	// todo

}

AQ IstoricInit()
{
	// todo
}

void IstoricDestroy(AQ aist)
{
	// todo

}

void IstoricClear(AQ aist, int n) 
{
	// todo

}

void IstoricAdd(AQ aist, char url[])
{
	// todo

}

int main(int argc, char *argv[])
{
	char linie[258];
	char comanda[258];
	char *p, *r;

	FILE *fin, *fout;
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	while (1) {
		// citesc o linie
		r = fgets(linie, 256, fin);
		if (r == NULL) {
			break;
		}

		// elimin newline de la final pus de fgets
		if (linie[strlen(linie)-1] == '\n') {
			linie[strlen(linie)-1] = '\0';
		}

		// gasesc primul cuvant din linie
		p = strtok(linie, " ");
		strcpy(comanda, p);

		if (strcmp(comanda, "set_band") == 0) {
			// 4.1
			
		} else if (strcmp(comanda, "newtab") == 0) {
			// 4.2
		} else if (strcmp(comanda, "deltab") == 0) {
			// 4.3
		} else if (strcmp(comanda, "change_tab") == 0) {
			// 4.4
		} else if (strcmp(comanda, "print_open_tabs") == 0) {
			// 4.5
		} else if (strcmp(comanda, "goto") == 0) {
			// 4.6
		} else if (strcmp(comanda, "back") == 0) {
			// 4.7
		} else if (strcmp(comanda, "forward") == 0) {
			// 4.8
		} else if (strcmp(comanda, "history") == 0) {
			// 4.9
		} else if (strcmp(comanda, "del_histroy") == 0) {
			// 4.10
		} else if (strcmp(comanda, "list_dl") == 0) {
			// 4.11
		} else if (strcmp(comanda, "downloads") == 0) {
			// 4.12
		} else if (strcmp(comanda, "download") == 0) {
			// 4.13
		} else if (strcmp(comanda, "wait") == 0) {
			// 4.14
		}
	}	

	/*

	// TESTING QUEUE ----------------------------------------------

	AQ aq = InitQ(sizeof(int));
	int x;

	x = 15;
	InsertQ(aq, &x);
	x = 27;
	InsertQ(aq, &x);
	x = 100;
	InsertQ(aq, &x);

	int *p;

	p = PeakQ(aq);
	printf("%d should be 15 \n", *p);
	p = ExtractQ(aq);
	printf("%d // 15 \n", *p);
	p = ExtractQ(aq);
	printf("%d // 27 \n", *p);
	p = ExtractQ(aq);
	printf("%d // 100 \n", *p);
	p = ExtractQ(aq);
	printf("%p should be nil \n", p);

	// TESTING STACK -----------------------------------------------

	AS as = InitS(sizeof(int));

	x = 30;
	Push(as, &x);
	x = 42;
	Push(as, &x);
	x = 1000;
	Push(as, &x);

	p = Top(as);
	printf("%d // 1000\n", *p);
	p = Pop(as);
	printf("%d // 1000\n", *p);
	p = Pop(as);
	printf("%d // 42\n", *p);
	p = Pop(as);
	printf("%d // 30\n", *p);
	p = Pop(as);
	printf("%p // nil\n", p);

	// ------------------------------------------------------------
	*/
	
	return 0;
}
