#include <stdio.h>
#include<stdlib.h>

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

//NACITANIE SUBOROV
void nacitanie(AUTA **p_prvy, int *n) //n - smernik na hodnotu pocet_prvkov zoznamu p_prvy - smernik na pvu polozku zoznamu
{
	FILE * fp;
	char c[2]; // nacitanie dolarovej znacky

	AUTA *prvy;
	int pocet_prvkov = 1; //na zaciatku bude mat 1. zaznam hodnotu 1

	if ((fp = fopen("auta.txt", "r")) == NULL)
		printf("Zaznamy neboli nacitane\n"); //ak sa subor nepodarilo otvorit

	prvy = (AUTA *)malloc(sizeof(AUTA)); //nacitanie prveho prvku zaznamu
	prvy->hodnota = pocet_prvkov++;  //pocet_prvkov sa zvacsi 
	fscanf(fp, " %s", c);
	fscanf(fp, " %[^\n]", prvy->kategoria);
	fscanf(fp, " %[^\n]", prvy->znacka);
	fscanf(fp, " %[^\n]", prvy->predajca);
	fscanf(fp, " %int", &prvy->cena);
	fscanf(fp, " %int", &prvy->rok_vyroby);
	fscanf(fp, " %[^\n]", prvy->stav_vozidla);

	if (fclose(fp) == EOF)
		printf("Subor sa nepodarilo zatvorit\n");

	*p_prvy = prvy; //odoslanie zoznamu do mainu 
	*n = pocet_prvkov; // odoslanie poctu prvkov zoznamu do mainu
}

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
		
		else if (funkcia == 'n')
		{
			p_prvy = (AUTA *)malloc(sizeof(AUTA));  
			nacitanie(&p_prvy, &pocet_prvkov);
		}
	}

	return 0;
}