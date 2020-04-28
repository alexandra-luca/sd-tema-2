#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "lista.h"
#include "coada.h"
#include "stiva.h"

typedef struct
{
	char url[21];
	int num_res;
	Resource *resources;
} TPagina;

typedef struct 
{
	TPagina *current_page;
	AS back_stack;
	AS forward_stack;
} TTab;

typedef ACel List;

typedef struct
{
	TTab *atab_curent;
	List tablist;
	AQ istoric;
	APQ downloading;
	List downloaded;
	int bandwidth;
} TBrowser;

// initializeaza pagina
TPagina* PaginaInit(char url[]) 
{
	TPagina *apag = (TPagina*)malloc(sizeof(TPagina));
	strcpy(apag->url, url);
	
	int n;
	apag->resources = get_page_resources(url, &n);
	apag->num_res = n;

	return apag;
}

// initializeaza tabul
TTab* TabInit() 
{
	TTab *atab = (TTab*)malloc(sizeof(TTab));
	atab->current_page = NULL;
	atab->back_stack = InitS(sizeof(TPagina));
	atab->forward_stack = InitS(sizeof(TPagina));

	return atab;
}

// dezaloca pagina
void PaginaDestroy(TPagina* apag) 
{
	free(apag);
}

// dezaloca tabul
void TabDestroy(TTab* atab) 
{
	free(atab);
}

// functie care merge la tabul anterior
void TabBack(TTab* atab) 
{
	Push(atab->forward_stack, atab->current_page);
	PaginaDestroy(atab->current_page);
	atab->current_page = Pop(atab->back_stack);
}

// functie care merge la tabul urmator
void TabForward(TTab* atab) 
{
	Push(atab->back_stack, atab->current_page);
	PaginaDestroy(atab->current_page);
	atab->current_page = Pop(atab->forward_stack);
}

// functie care merge la un anumit tab
void TabGoto(TTab* atab, char url[]) 
{
	if (atab->current_page != NULL) {
		Push(atab->back_stack, atab->current_page);
		PaginaDestroy(atab->current_page);
	}

	atab->current_page = PaginaInit(url);
}

// initializeaza istoricul
AQ IstoricInit()
{
	AQ aq = InitQ(sizeof(char)*21);
	return aq;
}

// dezaloca istoricul
void IstoricDestroy(AQ aist)
{
	// todo
}

//functie care sterge n pagini din istoric
void IstoricClear(AQ aist, int n) 
{
	int i;
	for (i = 0; i < n; i++) {
		ExtractQ(aist);
	}
}

// functie care adauga un url in istoric
void IstoricAdd(AQ aist, char url[])
{
	InsertQ(aist, url);
}

// functie care initializeaza browserul
TBrowser* BrowserInit()
{
	// creez browser
	TBrowser *abrowser = (TBrowser*)malloc(sizeof(TBrowser));

	// initializez tabul curent
	abrowser->atab_curent = TabInit();

	// initializez lista de taburi
	TCel *tabcel = (TCel*)malloc(sizeof(TCel));
	tabcel->urm = NULL;
	tabcel->info = abrowser->atab_curent;
	abrowser->tablist = tabcel;

	// initializez istoricul
	abrowser->istoric = IstoricInit();

	// initializez coada de descarcari
	abrowser->downloading = InitPQ(sizeof(Resource));

	// initializez lista de descarcari finalizate
	abrowser->downloaded = NULL;

	// initializez bandwidth
	abrowser->bandwidth = 1024;

	return abrowser;
}

//functie care seteaza bandwidth
void BrowserSetBandwidth(TBrowser *abrowser, int bandwidth) 
{
	// updatez bandwidth
	abrowser->bandwidth = bandwidth;
}

// functie care creeaza un nou tab
void BrowserNewTab(TBrowser *abrowser) 
{
	// creez tab nou si il setez ca tab curent
	abrowser->atab_curent = TabInit();

	// creez celula pentru lista de taburi
	TCel *tabcel = (TCel*)malloc(sizeof(TCel));
	tabcel->urm = NULL;
	tabcel->info = abrowser->atab_curent;

	// adaug celula la sfarsitul listei de taburi
	TCel *p = abrowser->tablist;
	if (p == NULL) {
		abrowser->tablist = tabcel;
	} else {
		while (p->urm != NULL) {
			p = p->urm;
		}
		p->urm = tabcel;
	}
}

// functie care sterge un tab din browser
void BrowserDelTab(TBrowser *abrowser)
{
	// gasesc ultimul tab
	TCel *ant;
	TCel *p = abrowser->tablist;
	ant = p;
	while (p->urm != NULL) {
		ant = p;
		p = p->urm;
	}
	
	TTab *t = p->info;
	if (abrowser->atab_curent == t) {
		abrowser->atab_curent = ant->info;
	}

	TabDestroy(t);
	free(p);
	ant->urm = NULL;
}

// functie care schimba tabul curent
void BrowserChangeTab(TBrowser *abrowser, int index) 
{
	int i = 0;
	TCel *p = abrowser->tablist;

	while (i < index) {
		p = p->urm;
		i++;
	}

	abrowser->atab_curent = p->info;
}

// functie care afiseaza taburile din browser
void BrowserPrintTabs(TBrowser *abrowser, FILE *fout)
{
	int i = 0;
	TCel *p = abrowser->tablist;

	while (p != NULL) {
		TTab *tab = p->info;
		TPagina *pag = tab->current_page;
		if (pag == NULL) {
			fprintf(fout, "(%d: %s)\n", i, "empty");
		} else {
			fprintf(fout, "(%d: %s)\n", i, pag->url);
		}

		p = p->urm;
		i++;
	}
}

// functie care afiseaza istoricul
void BrowserPrintHistory(TBrowser *abrowser, FILE *fout)
{
	AQ coada_intermediara = InitQ(sizeof(char)*21);
	char *url;

	while (!EmptyQ(abrowser->istoric)) {
		url = ExtractQ(abrowser->istoric);
		InsertQ(coada_intermediara, url);
		free(url);

		fprintf(fout, "%s\n", url);
	}

	DestroyQ(abrowser->istoric);
	abrowser->istoric = coada_intermediara;
}

// functie care afiseaza resursele din browser
void BrowserPrintResources(TBrowser *abrowser, FILE *fout)
{
	TTab *current_tab = abrowser->atab_curent;
	TPagina *current_page = current_tab->current_page;

	int i;
	for (i = 0; i < current_page->num_res; i++) {
		fprintf(fout, "[%d - \"%s\" : %ld]\n", i,
			current_page->resources[i].name, current_page->resources[i].dimension);
	}
}

// functie care descarca o resursa
void BrowserDownloadResource(TBrowser *abrowser, int index)
{
	TTab *current_tab = abrowser->atab_curent;
	TPagina *current_page = current_tab->current_page;

	unsigned long priority = current_page->resources[index].dimension;

	InsertPQ(abrowser->downloading, &(current_page->resources[index]), priority);
}

// functie care simuleaza trecerea timpului
void BrowserWait(TBrowser *abrowser, int time)
{
	APQ pq = InitPQ(sizeof(Resource));
	unsigned long bytes_de_descarcat = time * abrowser->bandwidth;

	while (!EmptyPQ(abrowser->downloading)) {
		unsigned long priority = PeakPriPQ(abrowser->downloading);

		Resource *r = ExtractPQ(abrowser->downloading);
		void *elem = r->name;

		if (priority > bytes_de_descarcat) {
			// nu am terminat de descarcat acest fisier
			priority -= bytes_de_descarcat;
			bytes_de_descarcat = 0;
			// inserez in coada cu ce a ramas de descarcat
			InsertPQ(pq, r, priority);
		} else {
			// am terminat de descarcat acest fisier
			bytes_de_descarcat -= priority;
			// inserez in lista de descarcari finalizate
			
			ACel celula = (ACel)malloc(sizeof(TCel));
			celula->info = elem;
			celula->urm = abrowser->downloaded;
			abrowser->downloaded = celula;
		}

		free(r);
	}

	DestroyPQ(abrowser->downloading);
	abrowser->downloading = pq;
}

// functie care afiseaza descarcarile
void BrowserPrintDownloads(TBrowser *abrowser, FILE *fout) 
{
	// afisez resursele in curs de descarcare
	APQ pq = InitPQ(sizeof(char)*100);

	while (!EmptyPQ(abrowser->downloading)) {
		unsigned long priority = PeakPriPQ(abrowser->downloading);

		Resource *r = ExtractPQ(abrowser->downloading);
		void *elem = r->name;

		fprintf(fout, "[\"%s\" : %ld/%ld]\n", (char*)elem, priority, r->dimension);

		InsertPQ(pq, r, priority);
		free(r);
	}

	abrowser->downloading = pq;

	// afisez descarcarile finalizate
	ACel p = abrowser->downloaded;
	while (p != NULL) {
		fprintf(fout, "[\"%s\" : completed]\n", (char*)p->info);
		p = p->urm;
	}
}

int main(int argc, char *argv[])
{
	char linie[258];
	char comanda[258];
	char *p, *r;
	int x;

	FILE *fin, *fout;
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	TBrowser *abrowser = BrowserInit();

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
			p = strtok(NULL, " ");
			x = atoi(p);

			BrowserSetBandwidth(abrowser, x);
		} else if (strcmp(comanda, "newtab") == 0) {
			// 4.2
			BrowserNewTab(abrowser);
		} else if (strcmp(comanda, "deltab") == 0) {
			// 4.3
			BrowserDelTab(abrowser);
		} else if (strcmp(comanda, "change_tab") == 0) {
			// 4.4
			p = strtok(NULL, " ");
			x = atoi(p);

			BrowserChangeTab(abrowser, x);
		} else if (strcmp(comanda, "print_open_tabs") == 0) {
			// 4.5
			BrowserPrintTabs(abrowser, fout);
		} else if (strcmp(comanda, "goto") == 0) {
			// 4.6
			p = strtok(NULL, " ");

			TabGoto(abrowser->atab_curent, p);
			IstoricAdd(abrowser->istoric, p);
		} else if (strcmp(comanda, "back") == 0) {
			// 4.7

			TabBack(abrowser->atab_curent);
		} else if (strcmp(comanda, "forward") == 0) {
			// 4.8

			TabForward(abrowser->atab_curent);
		} else if (strcmp(comanda, "history") == 0) {
			// 4.9

			BrowserPrintHistory(abrowser, fout);
		} else if (strcmp(comanda, "del_histroy") == 0) {
			// 4.10
			p = strtok(NULL, " ");
			x = atoi(p);

			IstoricClear(abrowser->istoric, x);
		} else if (strcmp(comanda, "list_dl") == 0) {
			// 4.11
			BrowserPrintResources(abrowser, fout);
		} else if (strcmp(comanda, "downloads") == 0) {
			// 4.12
			BrowserPrintDownloads(abrowser, fout);
		} else if (strcmp(comanda, "download") == 0) {
			// 4.13
			p = strtok(NULL, " ");
			x = atoi(p);

			BrowserDownloadResource(abrowser, x);
		} else if (strcmp(comanda, "wait") == 0) {
			// 4.14
			p = strtok(NULL, " ");
			x = atoi(p);

			BrowserWait(abrowser, x);
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
