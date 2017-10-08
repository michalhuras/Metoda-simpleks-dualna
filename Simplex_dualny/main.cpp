#include <iostream>
#include <fstream> //biblioteka odpowiedzialna za prace z plikami
#include <cstdlib> //biblioteka dla exit(0);
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

struct tablica_struct{
unsigned w,k;
float **tablica;
};

unsigned ilosc_kolumn(string linia)
{
    unsigned k=0;
    for(int i=0;i<linia.length();i++)
    {
        if (linia[i]==' ')
        {
            k++;
        }
    }
    return k;
}

float **implementacja_tablicy(unsigned w,unsigned k)
{
float **t=new float*[w];
for (int i=0;i<w;i++)
t[i]=new float[k];
return t;
}

void kasowanie(tablica_struct t)
{ //funkcja do zadania 6.2.3

    for (int i=0;i<t.w;i++)
        delete [] t.tablica[i];
    delete [] t.tablica;
}

tablica_struct odczytaj(char * sciezka)
{
    fstream plik(sciezka, ios::in);
    if(plik.good()==false)
        {
        cout<<"Nie mozna otworzyc pliku!";
        exit(0);
        }

    else{
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
        float **wsk=implementacja_tablicy(w,(k+1));
        tablica_struct t;
        t.k=k;
        t.w=w;
        t.tablica=wsk;
        plik.close();
        fstream plik(sciezka, ios::in);
        unsigned wiersz=0,pozycja;
        string pomocnicza;
        while ((!plik.eof()))
            {
                getline(plik, linia);
                for (int i=0;i<k+1;i++)
                {
                    pozycja=linia.find(" ");
                    pomocnicza=linia.substr(0,pozycja);
                    linia.erase(0,pozycja+1);
                    wsk[wiersz][i]=atof(pomocnicza.c_str());
                }
                wiersz++;
            }
    return t;
    }
}

void wyswietl(tablica_struct t)
{
    for (int i=0;i<t.w;i++)
            {
                for (int j=0;j<t.k+1;j++)
                {
                    cout<<t.tablica[i][j]<<"  ";
                }
                cout<<endl;
            }
}


int main()
{
    /*
    Program odczytuj¹cy tablice simplex z pliku tekstowego .txt
    nastepnie wykonuje przekszta³cenie simpleks. Wersja C++
    matlabowego skryptu "simplex"
    */

    char* plik="tabela_simplex.txt";
    tablica_struct tablica;
    tablica=odczytaj(plik);
    wyswietl(tablica);
    kasowanie(tablica);



    return 0;
}
