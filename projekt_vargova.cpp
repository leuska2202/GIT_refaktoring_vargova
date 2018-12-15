//POUZITE KNIZNICE:
#include <stdio.h>  //zakladna kniznica c
#include <stdlib.h> //na alokaciu pamati 
#include <string.h> // na prácu so stringami (porovnavanie, prepis, atd)

//STRUKTURA ZOZNAMU:
typedef struct	auta //informacie o danom aute
{
	int hodnota; //poradie v zozname
	char kategoria[51];
	char znacka[51];
	char predajca[51];
	int cena;
	int rok_vyroby;
	char stav_vozidla[201];
	struct auta *dalsi;
} AUTA;


//FUNKCIE:
//n- NACITANIE ZOZNAMU
void nacitanie(AUTA **p_prvy, int *p_pocet_prvkov)
{
	FILE * f_subor; // subor s polozkami
	AUTA *prvy, *aktualny;
	int pocet_prvkov = 1; //na zaciatku bude mat 1. zaznam hodnotu 1
	char c[2]; // nacitanie dolarovej znacky

	if ((f_subor = fopen("auta.txt", "r")) == NULL)
		printf("Zaznamy neboli nacitane\n"); //ak sa subor nepodarilo otvorit upozorni

	prvy = (AUTA *)malloc(sizeof(AUTA)); //nacitanie prveho prvku zaznamu
	prvy->hodnota = pocet_prvkov++;  //pocet_prvkov sa zvacsi aby dalsia nacitana hodnota bola 2 
	fscanf(f_subor, " %s", c);
	fscanf(f_subor, " %[^\n]", prvy->kategoria);
	fscanf(f_subor, " %[^\n]", prvy->znacka);
	fscanf(f_subor, " %[^\n]", prvy->predajca);
	fscanf(f_subor, " %int", &prvy->cena);
	fscanf(f_subor, " %int", &prvy->rok_vyroby);
	fscanf(f_subor, " %[^\n]", prvy->stav_vozidla);

	aktualny = prvy; //aktualny prvok na zaciatku je aj prvy
	while (!feof(f_subor)) //nacitanie zvysnych poloziek linearneho zoznamu az po koniec suboru
	{
		aktualny->dalsi = (AUTA *)malloc(sizeof(AUTA));
		aktualny = aktualny->dalsi; //presun na dalsi prvok
		
		fscanf(f_subor, " %[^\n]", c); // precita nepotrebny dollar na zaciatku zaznamu

		//postupne nacitanie vsetkych prvkov 
		aktualny->hodnota = pocet_prvkov++; //pocet prvkov je zaroven aj poradim, kedze 1.krat nacitujeme zoznam
		fscanf(f_subor, " %[^\n]", aktualny->kategoria);
		fscanf(f_subor, " %[^\n]", aktualny->znacka);
		fscanf(f_subor, " %[^\n]", aktualny->predajca);
		fscanf(f_subor, " %int", &aktualny->cena);
		fscanf(f_subor, " %int", &aktualny->rok_vyroby);
		fscanf(f_subor, " %[^\n]", aktualny->stav_vozidla);
	}
	aktualny->dalsi = NULL; //ukoncenie zoznamu 

	if (fclose(f_subor) == EOF)
		printf("Subor sa nepodarilo zatvorit\n"); //kontrola zatvarania suboru

	printf("Nacitalo sa %d zaznamov. \n \n", pocet_prvkov - 1); //celkovy pocet nacitanych prvkov je o 1 mensi, kedze sa pocet zvacil aj pri poslednom zazname

	*p_prvy = prvy; //odoslanie zoznamu do mainu 
	*p_pocet_prvkov = pocet_prvkov; // odoslanie poctu prvkov zoznamu do mainu
}

//v- VYPIS ZOZNAMU
void vypis(AUTA *prvy, int p_pocet_prvkov) 
{
	AUTA *aktualny;
	int poradie; // premenna cyklu 

	aktualny = prvy;
	for (poradie = 1; poradie < p_pocet_prvkov; poradie++)
	{
		//postupne vypis jednotlivych pozoziek aktualneho zaznamu
		printf("%d. \n", aktualny->hodnota);
		printf("kategoria: %s \n", aktualny->kategoria);
		printf("znacka: %s \n", aktualny->znacka);
		printf("predajca: %s \n", aktualny->predajca);
		printf("cena: %d \n", aktualny->cena);
		printf("rok_vyroby: %d \n", aktualny->rok_vyroby);
		printf("stav_vozidla: %s \n", aktualny->stav_vozidla);
		printf("\n");

		aktualny = aktualny->dalsi; // presun na dalsi prvok
	}
}

//u- UVOLNENIE PRVKOV ZOZNAMU
void uvolni(AUTA *prvy, int pocet_prvkov, AUTA **uvolneny)
{
	AUTA *aktualny;
	int poradie;

	aktualny = prvy;
	for (poradie = 1; poradie < pocet_prvkov; poradie++) // postupne mazeme vsetky prvky az po koniec zaznamu
	{
		aktualny = prvy;
		prvy = prvy->dalsi; //prvy prvok sa meni - presuva sa na nasledujuci v poradi 
		free(aktualny);	// aktualny prvok sa maze
	}

	*uvolneny = prvy; //odoslanie uvoleneho - prazdneho zoznamu do mainu
}

//p- PRIDAVANIE PRVKU DO ZOZNAMU
void pridanie(AUTA *prvy, int pocet_prvkov, AUTA **novy_zoznam) 
{
	int miesto_vlozenia, poradie;
	AUTA *aktualny, *pridany;

	printf("Na aku poziciu chces vlozit zaznam? \n");
	scanf("%int", &miesto_vlozenia);

	if (miesto_vlozenia > pocet_prvkov) miesto_vlozenia = pocet_prvkov; //ak pozícia vacsia ako pocet prvkov tak prida na koniec zoznamu

	pridany = (AUTA *)malloc(sizeof(AUTA)); //alokacia miesta pre pridany prvok

	pridany->hodnota = miesto_vlozenia; //ciselne poradie pridaneho prvku bude rovne pozicii , kt. si zvolime

	//postupne nacitanie vsetkych poloziek prvku, kt. chceme pridat
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
	pridany->dalsi = NULL; //ukoncenie pridaneho prvku

	if (miesto_vlozenia == 1) //ak pridanie na 1. pozíciu
	{
		pridany->dalsi = prvy; // prvý prvok sa presúva na 2. 
		prvy = pridany;  // pridany prvok na 1. pozíciu
	}
	else //ak vkladáme na hociktoru inu poziciu
	{
		aktualny = prvy;
		for (poradie = 0; poradie < miesto_vlozenia - 2; poradie++)
			aktualny = aktualny->dalsi;
		pridany->dalsi = aktualny->dalsi;
		aktualny->dalsi = pridany;
		// prvok na pozicii pred pridanym sa spoji s pridanym a pridany sa spoji s prvkom na pozocii, kde sme pridavali pridany
	}

	aktualny = prvy;
	for (poradie = 1; poradie <= pocet_prvkov; poradie++) // prepis poradovych cisel zoznamu po pridnai prvku
	{
		aktualny->hodnota = poradie;
		aktualny = aktualny->dalsi;
	}
	printf("\nPrvok pridany. \n \n"); // poznamka, ze funkcia prebehla

	*novy_zoznam = prvy; //vratenie noveho zoznamu do mainu
}

//a- AKTUALIZACIA ZOZNAMU
void aktualizacia(AUTA *prvy, int pocet_prvkov, AUTA **novy_zoznam)
{
	AUTA *aktualny;
	int poradie, vybrany_rok, zmena = 0;
	char vybrana_znacka[51], *hladana_znacka, *aktualna_znacka;

	printf("Zadaj znacku auta: \n");
	scanf(" %[^\n]", vybrana_znacka);
	hladana_znacka = strlwr(vybrana_znacka); //prepis naseho vstupu na male pismena

	printf("Zadaj rok: \n");
	scanf(" %int", &vybrany_rok);

	aktualny = prvy;
	for (poradie = 1; poradie < pocet_prvkov; poradie++)
	{
		aktualna_znacka = strlwr(aktualny->znacka); //prepis aktualnej znacky zaznamu na male pismena

		if (strcmp(hladana_znacka, aktualna_znacka) == 0 && vybrany_rok == aktualny->rok_vyroby) //ak porovnanie plati- zhoda
		{
			zmena++; //pocet kolko sa aktualizovalo za zvysi
			aktualny->cena = aktualny->cena - 100; //aktualizacia ceny
			if (aktualny->cena < 0) aktualny->cena = 0; //ak je cena po zmenseni o 100 zaporna tak sa rovná 0
		}
		aktualny = aktualny->dalsi; //presun k dalsiemu zaznamu
	}

	printf("Aktualizovalo sa %d zaznamov \n \n", zmena);
	*novy_zoznam = prvy;
}

//h- HLADANIE ZAZNAMU
void hladanie(AUTA *prvy, int pocet_prvkov)
{
	AUTA *aktualny;
	int suma;
	char vybrana_znacka[51], *hladana_znacka, *aktualna_znacka;
	int poradie, najdene = 0; // najdene = zistenie , ci aspon 1 polozka dostupna

	printf("Zadaj znacku auta: \n");
	scanf(" %[^\n]", vybrana_znacka);
	hladana_znacka = strlwr(vybrana_znacka); //na velkosti pisma nezalezi

	printf("Zadaj sumu, kt. mas k dispozicii: \n");
	scanf(" %int", &suma);

	aktualny = prvy;
	printf("\nDostupne vozidla: \n");

	for (poradie = 1; poradie < pocet_prvkov; poradie++)
	{
		aktualna_znacka = strlwr(aktualny->znacka); //na male pismena

		if (strcmp(hladana_znacka, aktualna_znacka) == 0 && suma > aktualny->cena)  //porovnanie- najdenie vyhovujucej polozky
		{
			printf("%d. \n", aktualny->hodnota);
			printf("kategoria: %s \n", aktualny->kategoria);
			printf("znacka: %s \n", aktualny->znacka);
			printf("predajca: %s \n", aktualny->predajca);
			printf("cena: %d \n", aktualny->cena);
			printf("rok_vyroby: %d \n", aktualny->rok_vyroby);
			printf("stav_vozidla: %s \n \n", aktualny->stav_vozidla);
			najdene = 1; //nasla sa aspon 1 polozka
		}
		aktualny = aktualny->dalsi;
	}
	if (najdene == 0) printf("V ponuke nie su pozadovane auta.\n \n"); //ak sa nic nenaslo oznami;
}

//z- ZMAZANIE ZAZNAMU	
void zmazanie(AUTA *prvy, int pocet_prvkov, AUTA **novy_zoznam, int *novy_pocet_prvkov)
{
	char vybrana_znacka[51], *hladana_znacka, *aktualna_znacka;
	int poradie = 1, mazana_pozicia, poradie_mazania, pocet_zmazanych = 0;
	AUTA *aktualny, *mazany_prvok;

	printf("Zadaj znacku, kt. chces zmazat: \n");
	scanf(" %[^\n]", vybrana_znacka);
	hladana_znacka = strlwr(vybrana_znacka); //na pisme nezalezi

	aktualny = prvy;
	while (poradie < pocet_prvkov - pocet_zmazanych)
	{
		if (poradie == 1) aktualny = prvy; //v prvom cykle

		aktualna_znacka = strlwr(aktualny->znacka); //na male pismena

		if (strstr(aktualna_znacka, hladana_znacka) != NULL) // hladanie substringu a mazanie prvkov, kt. ho obsahuju
		{
			mazana_pozicia = poradie;
			pocet_zmazanych++;
			poradie = 0; // nasiel sa prvok na zmazanie --> zmaze ho a prejde novy zoznam od zaciatku, ci je potrebne aste nieco zmazat

			if (mazana_pozicia == 1) //ak mažeme 1.pozíciu
			{
				mazany_prvok = prvy;
				prvy = mazany_prvok->dalsi;
				free(mazany_prvok); //je potrebné uvolnenie vymazaneho prvku
			}

			else //ak mažeme inú pozíciu
			{
				aktualny = prvy;
				for (poradie_mazania = 0; poradie_mazania < mazana_pozicia - 2; poradie_mazania++)
					aktualny = aktualny->dalsi;
				mazany_prvok = aktualny->dalsi;
				aktualny->dalsi = mazany_prvok->dalsi;
				free(mazany_prvok); //uvolnenie zmazaneho prvku
			}
		}
		poradie++; // dalsi v poradi cyklu
		aktualny = aktualny->dalsi;
	}
	printf("Vymazalo sa %d zaznamov \n \n", pocet_zmazanych);

	aktualny = prvy;
	for (poradie = 1; poradie < pocet_prvkov - pocet_zmazanych; poradie++) //prepisanie ciselneho poradia prvkov po zmazani niektorych prvkov zoznamu
	{
		aktualny->hodnota = poradie;
		aktualny = aktualny->dalsi;
	}

	*novy_zoznam = prvy; //odoslanie noveho zoznamu a poctu prvkov opat do mainu
	*novy_pocet_prvkov = pocet_prvkov - pocet_zmazanych; //pocet prvkov sa zmensil o pocet zmazanych
}


//HLAVNY PROGRAM :
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

			p_prvy = (AUTA *)malloc(sizeof(AUTA)); // alokacia pred nacitanim zoznamu a jeho nacitanie
			nacitanie(&p_prvy, &pocet_prvkov); break; //nacitanie nasho zoznamu

		case 'v': vypis(p_prvy, pocet_prvkov); break; //vypis zoznamu

		case 'p': pridanie(p_prvy, pocet_prvkov, &p_prvy); pocet_prvkov++; break;  //pridanie prvku do zoznamu 

		case 'a': aktualizacia(p_prvy, pocet_prvkov, &p_prvy); break; //aktualizacia ceny zoznamu

		case 'h': hladanie(p_prvy, pocet_prvkov); break; //hladanie auta v zozname 

		case 'z': zmazanie(p_prvy, pocet_prvkov, &p_prvy, &pocet_prvkov); break; //zmazanie vybranych prvkov zaznamu
		}
	}

	uvolni(p_prvy, pocet_prvkov, &p_prvy);  //po vystupe z cyklu ak funkcia = 'k' uvolnenie zoznamu (znazanie celeho linear. zoznamu) a koniec programu
	return 0;
}