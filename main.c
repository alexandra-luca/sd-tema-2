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

	// 


	return 0;
}
