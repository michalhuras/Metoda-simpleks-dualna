#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
//#include "tabela_dualna_simpleks.h"
#include "menu.h"


using namespace std;

char *tr(char *str)
{
   static char buff[256];
   char cp[]="\245\206\251\210\344\242\230\276\253\244\217\250\235\343\340\227\275\215����󜿟��ʣ�ӌ��";
   if(strlen(str)>=sizeof(buff)) return str;
   char *bf=buff;
   while(*str)
     {
      char *pos=strchr(cp+18,*str);
      *(bf++)=pos?*(pos-18):*str;
      ++str;
     }
   *bf=0;
   return buff;
}

  struct tablica_struct
{
unsigned w,k;
float **tablica;
};

void wyswietlMenuGlowne()
{

    cout << tr("**** Menu g��wne programu ****") << endl;
    cout << tr("Wprowad� liczb� odpowiadaj�c� numerowi dzia�ania") << endl;
    cout << tr("1. Wczytanie tablicy simpleks z pliku") << endl;
    cout << tr("2. Pojedyncze przekszta�cenie uprzednio wczytanej tablicy simpleks ") << endl;
    cout << tr("3. Automatyczne przekszta�cenie uprzednio wczytanej tablicy simpleks") << endl;
    cout << tr("") << endl;
    cout << tr("") << endl;

}

int odczytajWybraneDzialanie()
{
    int wybraneDzialanie;
    cin.sync();
    cin>>wybraneDzialanie;
    return wybraneDzialanie;
}

void wyswietlMenuwczytywaniatabeli()
{
    cout << tr("**** Wczytywanie tablicy simpleks ****") << endl;
    cout << tr("Wprowad� nazw� �cie�ki pliku w kt�rym znajduje si� tablica i zaakceptuj enterem") << endl;
    cout << tr("") << endl;
    cout << tr("") << endl;
    cin.sync();
}

char* odczytajSciezkedostepu()
{
    char* sciezkaDostepu;
    cin>>sciezkaDostepu;
    return sciezkaDostepu;
}

unsigned ilosc_kolumn(string linia)
{
    unsigned k=1;
    for(int i=0;i<linia.length();i++)
    {
        if (linia[i]==' ')
        {
            k++;
        }
    }

    return k;
}

tablica_struct implementacjaTablicy(tablica_struct t)
{
float **wsk=new float*[t.w];
for (int i=0;i<t.w;i++)
wsk[i]=new float[t.k];
t.tablica=wsk;
return t;
}

tablica_struct pobierzDaneZPliku(char* sciezkaDostepu)
{
    fstream plik(sciezkaDostepu, ios::in);
    if(plik.good()==false)
    {
        cout<<"Nie mozna otworzyc pliku!";
        exit(0);
    }
    else
    {
        string linia;
        unsigned k,w=0;
        while ((!plik.eof()))
        {
            getline(plik, linia);
            if (w==0)
            {
                k=ilosc_kolumn(linia);
            }
            w++;
        }
        tablica_struct t;
        t.k=k;
        t.w=w;
        t=implementacjaTablicy(t);
        plik.close();
        fstream plik(sciezkaDostepu, ios::in);
        unsigned wiersz=0,pozycja;
        string pomocnicza;
        while ((!plik.eof()))
        {
            getline(plik, linia);
            for (int i=0; i<k; i++)
            {
                pozycja=linia.find(" ");
                pomocnicza=linia.substr(0,pozycja);
                linia.erase(0,pozycja+1);
                t.tablica[wiersz][i]=atof(pomocnicza.c_str());
            }
            wiersz++;
        }
    return t;
    }
}

void wyswietlTablice(tablica_struct t)
{
    for (unsigned i=0;i<t.w;i++)
            {
                for (unsigned j=0;j<t.k;j++)
                {
                    cout<<t.tablica[i][j]<<"  ";
                }
                cout<<endl;
            }
}


void wyswietlMenuPojedynczegoPrzeksztalcenia()
{
    cout << tr("**** Pojedyncze przekszta�cenie simpleks ****") << endl;
    cout << tr("") << endl;
    cout << tr("") << endl;
    cout << tr("") << endl;
}

void wyswietlMenuAutomatycznegoprzeksztalcenia()
{
    cout << tr("**** Automatyczne przekszta�cenie uprzednio wczytanej tablicy simpleks ****") << endl;
    cout << tr("Tablica zosta�a przekszta�cona. Poni�ej widniej� ") << endl;
    cout << tr("Kolejne tablice oraz wynik") << endl;
    cout << tr("Wprowad� jakikolwiek znak, aby wr�ci�") << endl;
}

void wyswietlKomunikatBleduWyboru()
{
    cout << tr("**** Wybrana funkcja jest niedost�pna ****") << endl<<endl;
}

int main()
{
    wyswietlMenuGlowne();
    switch (odczytajWybraneDzialanie())
    {
    case 1:
    {
        wyswietlMenuwczytywaniatabeli();
        tablica_struct tablicaPierwotna=pobierzDaneZPliku(odczytajSciezkedostepu());
        wyswietlTablice(tablicaPierwotna);

        break;
    }
    case 2:
    {
        wyswietlMenuPojedynczegoPrzeksztalcenia();
        break;
    }
    case 3:
    {
        wyswietlMenuAutomatycznegoprzeksztalcenia();
        break;
    }
    default :
    {
        wyswietlKomunikatBleduWyboru();
        wyswietlMenuGlowne();
        break;
    }

    }

    return 0;
}


