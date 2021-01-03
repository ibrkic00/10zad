#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct stablo* Cvor;

typedef struct stog* Pozicija;

typedef struct stablo
{
	char vrijednost[5];
	Cvor lijevi;
	Cvor desni;
}Stablo;

typedef struct stog
{
	Cvor element;
	Pozicija next;
}Stog;

void PushStog(Pozicija , Cvor);

Cvor PopStog(Pozicija);

Pozicija AlocirajElement();

Cvor AlocirajCvor(char[]);

void inorder(Cvor);

bool isNum(char);

int main()
{
	FILE* datoteka;
	Cvor n1 = NULL, n2 = NULL, n3 = NULL;
	Pozicija headStoga = AlocirajElement();
	char buffer[5];
	datoteka = fopen("file.txt", "r");

	while (!feof(datoteka))
	{
		fscanf(datoteka, "%s", buffer);
		if (isNum(buffer[0]))
		{
			n1 = AlocirajCvor(buffer);
			PushStog(headStoga, n1);
		}
		else
		{
			n1 = AlocirajCvor(buffer);
			n2 = PopStog(headStoga);
			n3 = PopStog(headStoga);

			n1->desni = n2;
			n1->lijevi = n3;
			PushStog(headStoga, n1);
		}
	}

	inorder(headStoga->next->element);

	fclose(datoteka);
	return 0;
}

void PushStog(Pozicija headStoga, Cvor element)
{
	Pozicija novi;
	novi = AlocirajElement();
	if (headStoga->next == NULL)
	{
		headStoga->next = novi;
		novi->element = element;
	}
	else
	{
		while (headStoga->next != NULL)
			headStoga = headStoga->next;
		headStoga->next = novi;
		novi->element = element;
	}
}

Cvor PopStog(Pozicija headStoga)
{
	Cvor pop;
	while (headStoga->next->next != NULL)
		headStoga = headStoga->next;
	pop = headStoga->next->element;
	free(headStoga->next);
	headStoga->next = NULL;
	return pop;
}

Pozicija AlocirajElement()
{
	Pozicija novi;
	novi = (Pozicija)malloc(sizeof(Stog));
	novi->element = NULL;
	novi->next = NULL;
	return novi;
}

bool isNum(char znak)
{
	return (znak >= '0' && znak <= '9');
}

Cvor AlocirajCvor(char buffer[])
{
	Cvor novi;
	novi = (Cvor)malloc(sizeof(Stablo));
	strcpy(novi->vrijednost, buffer);
	novi->desni = NULL;
	novi->lijevi = NULL;
	return novi;
}

void inorder(Cvor t)
{
	if (t)
	{
		if(!isNum(t->vrijednost[0]))
			printf(" ( ");
		inorder(t->lijevi);
		printf("%s", t->vrijednost);
		inorder(t->desni);
		if(!isNum(t->vrijednost[0]))
			printf(" ) ");
	}
}