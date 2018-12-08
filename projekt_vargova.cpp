#include <stdio.h>

//STRUKTURA ZOZNAMU
typedef struct	auta
{
	int hodnota;
	char kategoria[51];
	char znacka[51];
	char predajca[51];
	int cena;
	int rok_vyroby;
	char stav_vozidla[201];
	struct auta *dalsi;
} AUTA;

int main()
{
	AUTA *p; //hlavny prvy prvok zoznamu
	p = NULL; //na zaciatku prazdny zoznam
	int n = 1; //pocet prvkov zoznamu

	while (1)
	{
		char f;
		scanf("%c", &f); // nacitanie funcie, kt. chceme vykonat

		if (f == 'k') break; //ukonci program - nekonecny cyklus 
	}

	return 0;
}