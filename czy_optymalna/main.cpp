#include <iostream>
#include <fstream> //biblioteka odpowiedzialna za prace z plikami
#include <cstdlib> //biblioteka dla exit(0);
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*Funkcja zwraca wartoœæ:
0- jeszcze nie optymalne,
1- funkcja optymalna (jeden wierzcho³ek)-nie ma ¿adnych zer
2- funkcja optymalna (odcinek)- jest zero i da sie przeliczyæ,bo nie wszystkie wartoœci s¹ ujemne
3 -funkcja optymalna (pó³prosta)- jest zero, ale nie da siê przeliczyæ bo same ujemne s¹.
*/


using namespace std;


struct tablica_struct{
unsigned w,k;
float **tablica;
};

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

tablica_struct implementacja_tablicy(tablica_struct t)
{
float **wsk=new float*[t.w];
for (int i=0;i<t.w;i++)
wsk[i]=new float[t.k];
t.tablica=wsk;
return t;
}

void kasowanie(tablica_struct t)
{

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

        tablica_struct t;
        t.k=k;
        t.w=w;
        t=implementacja_tablicy(t);
        plik.close();
        fstream plik(sciezka, ios::in);
        unsigned wiersz=0,pozycja;
        string pomocnicza;
        while ((!plik.eof()))
            {
                getline(plik, linia);
                for (int i=0;i<k;i++)
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

void wyswietl(tablica_struct t)
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


int main()
{
    char* plik="tabela_simplex0.txt";
    tablica_struct tablica;
    tablica=odczytaj(plik);
    wyswietl(tablica);


    unsigned a=0;
    for (unsigned i=2;i<tablica.w;i++)
    {
       if (tablica.tablica[i][1]>=0)
        a=a+1;
    }

    int optymalny;
    if (a==(tablica.w)-2)
    {
        optymalny=1;
        for (unsigned i=2;i<tablica.k;i++)
        {
            if (tablica.tablica[1][i]==0)
            //if (tablica.tablica[1][i]==0 && optymalny~=3)
            {
              int b=0;
              for (unsigned j=2;j<tablica.w;j++)
                 if (tablica.tablica[j][i]<0)
                    b=b+1;

            if (b==(tablica.w-2))
                optymalny=3;
            else{
                optymalny=2;
            }
            }
        }
    }
    else
         optymalny=0;




    cout<<"Optymalny="<<optymalny<<endl;

    return 0;
}
