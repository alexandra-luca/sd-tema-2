#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "lista.h"
#include "coada.h"
#include "stiva.h"

int main()
{

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


	return 0;
}
