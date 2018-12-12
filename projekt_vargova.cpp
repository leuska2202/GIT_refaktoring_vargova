#include <stdio.h>
#include <stdlib.h>

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

//NACITANIE ZOZNAMU
void nacitanie(AUTA **p_prvy, int *p_pocet_prvkov) //n - smernik na hodnotu pocet_prvkov zoznamu p_prvy - smernik na pvu polozku zoznamu
{
	FILE * fp;
	AUTA *prvy, *akt;
	char c[2]; // nacitanie dolarovej znacky
	int pocet_prvkov = 1; //na zaciatku bude mat 1. zaznam hodnotu 1

	if ((fp = fopen("auta.txt", "r")) == NULL)
		printf("Zaznamy neboli nacitane\n"); //ak sa subor nepodarilo otvorit;

	prvy = (AUTA *)malloc(sizeof(AUTA)); //nacitanie prveho prvku zaznamu
	prvy->hodnota = pocet_prvkov++;  //pocet_prvkov sa zvacsi aby dalsia nacitana hodnota bola 2
	fscanf(fp, " %s", c);
	fscanf(fp, " %[^\n]", prvy->kategoria);
	fscanf(fp, " %[^\n]", prvy->znacka);
	fscanf(fp, " %[^\n]", prvy->predajca);
	fscanf(fp, " %int", &prvy->cena);
	fscanf(fp, " %int", &prvy->rok_vyroby);
	fscanf(fp, " %[^\n]", prvy->stav_vozidla);

	akt = prvy; //aktualny prvok na zaciatku je aj prvy
	while (!feof(fp))
	{
		akt->dalsi = (AUTA *)malloc(sizeof(AUTA));
		akt = akt->dalsi; //presun na dalsi prvok

		akt->hodnota = pocet_prvkov++; //nacitanie poloziek dalsieho prvku, kt. je teraz aktualny
		fscanf(fp, " %[^\n]", c); // precita dollar na zaciatku zaznamu
		fscanf(fp, " %[^\n]", akt->kategoria);
		fscanf(fp, " %[^\n]", akt->znacka);
		fscanf(fp, " %[^\n]", akt->predajca);
		fscanf(fp, " %int", &akt->cena);
		fscanf(fp, " %int", &akt->rok_vyroby);
		fscanf(fp, " %[^\n]", akt->stav_vozidla);
	}
	akt->dalsi = NULL; //ukoncenie zoznamu 

	if (fclose(fp) == EOF)
		printf("Subor sa nepodarilo zatvorit\n");

	printf("Nacitalo sa %d zaznamov. \n \n", pocet_prvkov - 1); 

	*p_prvy = prvy; //odoslanie zoznamu do mainu 
	*p_pocet_prvkov = pocet_prvkov; // odoslanie poctu prvkov zoznamu do mainu
}

//VYPIS ZOZNAMU
void vypis(AUTA *prvy, int p_pocet_prvkov) // n -pocet prvkov
{
	AUTA *akt;
	akt = prvy;
	int poradie; // premenna cyklu 

	for (poradie = 1; poradie < p_pocet_prvkov; poradie++)
	{
		printf("%d. \n", akt->hodnota);
		printf("kategoria: %s \n", akt->kategoria);
		printf("znacka: %s \n", akt->znacka);
		printf("predajca: %s \n", akt->predajca);
		printf("cena: %d \n", akt->cena);
		printf("rok_vyroby: %d \n", akt->rok_vyroby);

		printf("stav_vozidla: %s \n", akt->stav_vozidla);
		printf("\n");

		akt = akt->dalsi; // presun na dalsi prvok
	}
}

//UVOLNENIE PRVKOV ZOZNAMU
void uvolni(AUTA *prvy, int n, AUTA **uvolneny)
{
	AUTA *akt;
	int i;

	akt = prvy;
	for (i = 1; i < n; i++)
	{
		akt = prvy;
		prvy = prvy->dalsi; // aktualny presun na dalsi prvok
		free(akt);	//uvolnenie pomocneho prvku, kt. momentalne = aktualny;
	}

	*uvolneny = prvy; //odoslanie uvoleneho zoznamu do mainu
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
		else if (funkcia == 'v')
			vypis(p_prvy, pocet_prvkov);
	}

	uvolni(p_prvy, pocet_prvkov, &p_prvy);  //po vystupe z cyklu ak funkcia = 'k' uvolnenie zoznamu a koniec programu
	return 0;
}