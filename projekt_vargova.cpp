#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void nacitanie(AUTA **p_prvy, int *p_pocet_prvkov) 
{
	FILE * f_subor;
	AUTA *prvy, *akt;
	int pocet_prvkov = 1; //na zaciatku bude mat 1. zaznam hodnotu 1
	char c[2]; // nacitanie dolarovej znacky

	if ((f_subor = fopen("auta.txt", "r")) == NULL)
		printf("Zaznamy neboli nacitane\n"); //ak sa subor nepodarilo otvorit;

	prvy = (AUTA *)malloc(sizeof(AUTA)); //nacitanie prveho prvku zaznamu
	prvy->hodnota = pocet_prvkov++;  //pocet_prvkov sa zvacsi aby dalsia nacitana hodnota bola 2
	fscanf(f_subor, " %s", c);
	fscanf(f_subor, " %[^\n]", prvy->kategoria);
	fscanf(f_subor, " %[^\n]", prvy->znacka);
	fscanf(f_subor, " %[^\n]", prvy->predajca);
	fscanf(f_subor, " %int", &prvy->cena);
	fscanf(f_subor, " %int", &prvy->rok_vyroby);
	fscanf(f_subor, " %[^\n]", prvy->stav_vozidla);

	akt = prvy; //aktualny prvok na zaciatku je aj prvy
	while (!feof(f_subor))
	{
		akt->dalsi = (AUTA *)malloc(sizeof(AUTA));
		akt = akt->dalsi; //presun na dalsi prvok

		akt->hodnota = pocet_prvkov++; //nacitanie poloziek dalsieho prvku, kt. je teraz aktualny
		fscanf(f_subor, " %[^\n]", c); // precita dollar na zaciatku zaznamu
		fscanf(f_subor, " %[^\n]", akt->kategoria);
		fscanf(f_subor, " %[^\n]", akt->znacka);
		fscanf(f_subor, " %[^\n]", akt->predajca);
		fscanf(f_subor, " %int", &akt->cena);
		fscanf(f_subor, " %int", &akt->rok_vyroby);
		fscanf(f_subor, " %[^\n]", akt->stav_vozidla);
	}
	akt->dalsi = NULL; //ukoncenie zoznamu 

	if (fclose(f_subor) == EOF)
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
void uvolni(AUTA *prvy, int pocet_prvkov, AUTA **uvolneny)
{
	AUTA *akt;
	int poradie;

	akt = prvy;
	for (poradie = 1; poradie < pocet_prvkov; poradie++)
	{
		akt = prvy;
		prvy = prvy->dalsi; // aktualny presun na dalsi prvok
		free(akt);	//uvolnenie pomocneho prvku, kt. momentalne = aktualny;
	}

	*uvolneny = prvy; //odoslanie uvoleneho zoznamu do mainu
}

//PRIDAVANIE PRVKU DO ZOZNAMU
void pridanie(AUTA *prvy, int pocet_prvkov, AUTA **novy) // novy - pointer na novy zoznam
{
	int miesto_vlozenia, poradie;
	AUTA *akt, *pridany;

	printf("Na aku poziciu chces vlozit zaznam? \n");
	scanf("%int", &miesto_vlozenia);
	if (miesto_vlozenia > pocet_prvkov) miesto_vlozenia = pocet_prvkov; //ak pozícia vacsia ako pocet prvkov tak prida na koniec zoznamu

	pridany = (AUTA *)malloc(sizeof(AUTA)); //nacitanie prvku, kt chceme pridat
	
	pridany->hodnota = miesto_vlozenia;
	
	printf("\nKategoria auta: \n"); 
	scanf(" %[^\n]", pridany->kategoria);
	
	printf("Znacka auta: \n");
	scanf(" %[^\n]", pridany->znacka);
	
	printf("Predajca: \n");
	scanf(" %[^\n]", pridany->predajca);
	
	printf("Cena: \n");
	scanf(" %int", &pridany->cena);
	
	printf("Rok vyroby: \n");
	scanf(" %int", &pridany->rok_vyroby);
	
	printf("Stav vozidla: \n");
	scanf(" %[^\n]", pridany->stav_vozidla);
	
	pridany->dalsi = NULL;

	if (miesto_vlozenia == 1) //ak pridanie na 1. pozíciu
	{
		pridany->dalsi = prvy; // prvý prvok sa presúva na 2. 
		prvy = pridany;  // pridany prvok na 1. pozíciu
	}
	else //ak vkladáme na hociktoru inu poziciu
	{
		akt = prvy;
		for (poradie = 0; poradie < miesto_vlozenia - 2; poradie++)
			akt = akt->dalsi;

		pridany->dalsi = akt->dalsi;
		akt->dalsi = pridany;
	}

	akt = prvy;
	for (poradie = 1; poradie <= pocet_prvkov; poradie++) // prepis poradovych cisel zoznamu po pridnai prvku
	{
		akt->hodnota = poradie;
		akt = akt->dalsi;
	}

	printf("\nPrvok pridany- ak chces vidiet zoznam zadaj 'v'. \n \n");

	*novy = prvy; //vratenie noveho zoznamu do mainu
}

//AKTUALIZACIA ZOZNAMU
void aktualizacia(AUTA *prvy, int pocet_prvkov, AUTA **novy)
{
	AUTA *akt;
	int poradie, vybrany_rok, zmena = 0, porovnanie;
	char vybrana_znacka[51]; 

	printf("Zadaj znacku auta: \n");
	scanf(" %[^\n]", vybrana_znacka);

	printf("Zadaj rok: \n");
	scanf(" %int", &vybrany_rok);

	akt = prvy;
	for (poradie = 1; poradie < pocet_prvkov; poradie++)
	{
		porovnanie = strcmp(vybrana_znacka, akt->znacka);

		if (porovnanie == 0 && vybrany_rok == akt->rok_vyroby)
		{
			zmena++; //kolko sa aktualizovalo
			akt->cena = akt->cena - 100;
			if (akt->cena < 0) akt->cena = 0; //ak je cena po zmenseni o 100 zaporna tak sa rovná 0
		}
		akt = akt->dalsi;
	}

	printf("Aktualizovalo sa %d zaznamov \n \n", zmena);
	*novy = prvy;
}

//HLAVNY PROGRAM
int main()
{
	AUTA *p_prvy; //hlavny prvy prvok zoznamu
	p_prvy = NULL; //na zaciatku prazdny zoznam
	int pocet_prvkov = 1; //pocet prvkov zoznamu

	printf("Zadavaj funkciu, kt. chces vykonat: \n('n'- nacitanie prvkov suboru / 'v'- vypis / 'p'- pridanie prvku / 'k'- koniec) \n");

	while (1) //nekonecny cyklus
	{
		char funkcia;	
		scanf("%c", &funkcia); // nacitanie funcie, kt. chceme vykonat

		if (funkcia == 'k') break; //ukonci program - nekonecny cyklus 
		
		switch (funkcia)
		{
		case 'n':
			if (p_prvy != NULL) //ak zoznam existuje - ma prvky uvolni existujuci zoznam a nacita novy
				uvolni(p_prvy, pocet_prvkov, &p_prvy);

			p_prvy = (AUTA *)malloc(sizeof(AUTA));  
			nacitanie(&p_prvy, &pocet_prvkov); break; // alokacia pred nacitanim zoznamu a jeho nacitanie

		case 'v': vypis(p_prvy, pocet_prvkov); break;
		
		case 'p': pridanie(p_prvy, pocet_prvkov, &p_prvy); pocet_prvkov++; break;  //pridali sme prvok --> zvacsil sa nam zoznam o 1 --> pocet prvkov +1
		
		case 'a': aktualizacia(p_prvy, pocet_prvkov, &p_prvy); break;
		}
	}

	uvolni(p_prvy, pocet_prvkov, &p_prvy);  //po vystupe z cyklu ak funkcia = 'k' uvolnenie zoznamu a koniec programu
	return 0;
}