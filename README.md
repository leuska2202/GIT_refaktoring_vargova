# GIT_refaktoring_vargova

projekt na MIP git + refaktoring

Zadanie:
Napíšte program, ktorý bude pracovať so záznamami v dynamickom spájanom zozname. Záznamy uložené v súbore auta.txt budú predstavovať ponuku autobazárov v internetovom obchode. Pred každým záznamom v súbore bude jeden riadok obsahujúci znak $, ktorý záznamy viditeľne oddelí. Jednotlivé položky záznamu budú v súbore umiestnené vždy v samostatnom riadku. 

Význam položiek záznamu bude nasledujúci:
kategoria (maximálne 50 znakov)
znacka (maximálne 50 znakov)
predajca (maximálne 100 znakov)
cena (celé číslo)
rok_vyroby (celé číslo)
stav_vozidla (maximálne 200 znakov)

Ukážka obsahu súboru auta.txt:
$
osobny automobil
Ferrari
Autobazar Pestovatelska 4 Bratislava
5620
2005
udrziavane cervene dvojdverove
$
kamion
Renault
AUTO Modranska 5 Senec
18000 
2011
po havarii opraveny v dobrom stave

Funkcie:
n – je príkaz na načítanie záznamov o autách zo súboru auta.txt do spájaného zoznamu štruktúr.
Ak zoznam predtým existoval, je potrebné uvoľniť pamäť. Ak nie je možné súbor otvoriť, program vypíše správu Zaznamy neboli nacitane ukončenú znakom konca riadku. Ak sa podarilo záznamy načítať, vypíše správu Nacitalo sa x zaznamov.

v – je príkaz na výpis celého spájaného zoznamu záznamov.

p – je príkaz na pridanie záznamu do dynamického zoznamu.
Príkaz je v ďalšom riadku nasledovaný celým číslom k > 0 vyjadrujúcim pozíciu (počítanú od 1), na ktorú sa má záznam pridať. Potom nasleduje ďalších 6 riadkov, každý ukončený znakom konca riadku a obsahujúcim položky záznamu v poradí v akom sú aj v súbore auta.txt. Ak pozícia k v zozname neexistuje, záznam sa pridá na koniec zoznamu. 

h - umožní používateľovi vyhľadať a vypísať všetky položky záznamu podľa značky auta a ceny ponuky.

a – je príkaz na aktualizáciu (zmenu) záznamu podľa značky auta a roku výroby.
Riadok s príkazom a je nasledovaný riadkom obsahujúcim značku auta ukončenom znakom konca riadku a rok výroby ukončený znakom konca riadku. Program aktualizuje všetky záznamy obsahujúce zadanú značku auta a rok výroby tak, že pri všetkých týchto záznamoch zníži cenu vozidla o 100. V prípade ak by po znížení bola cena auta záporné číslo cena sa upraví na 0.


k – je príkaz na ukončenie programu.
Ak spájaný zoznam existoval, treba uvoľniť pamäť.
