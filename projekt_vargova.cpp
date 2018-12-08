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
	AUTA *p_prvy; //hlavny prvy prvok zoznamu
	p_prvy = NULL; //na zaciatku prazdny zoznam
	int pocet_prvkov = 1; //pocet prvkov zoznamu

	while (1)
	{
		char funkcia;
		scanf("%c", &funkcia); // nacitanie funcie, kt. chceme vykonat

		if (funkcia == 'k') break; //ukonci program - nekonecny cyklus 
	}

	return 0;
}