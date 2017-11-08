#include <iostream>
#include <fstream> //biblioteka odpowiedzialna za prace z plikami
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include<vector>

//Podprogram ma sprawdzaæ najszybsz¹ metodê odczytu danych z pliku vector vs odczyt pierwotny zliczaj¹cy
//Pomiar czasu w milisekundach :http://www.cplusplus.com/reference/ctime/clock/

using namespace std;

struct tablica_struct{
unsigned w,k;
float **tablica;
};

tablica_struct implementacja_tablicy(tablica_struct t)
{
float **wsk=new float*[t.w];
for (unsigned i=0;i<t.w;i++)
wsk[i]=new float[t.k];
t.tablica=wsk;
return t;
}

vector < vector < float > > wektor;
unsigned ilosc_kolumn(string linia);
tablica_struct odczytaj(char * sciezka);
void wyswietl(tablica_struct t);
void wyswietl(vector < vector < float > > wektor);
bool czyZawieraZnak(string linia);
vector < vector < float > >  odczytaj2(char * sciezka);


int main()
{
    char* plik="tabela_simplex.txt";

    //wersja 1-pierwotny odczyt zliczaj¹cy
    clock_t t=clock();
    tablica_struct tablica;
    tablica=odczytaj(plik);
    wyswietl(tablica);
    t = clock() - t;
    cout<<"Czas wykonywania pierwszej metody:  "<<(((float)t)/CLOCKS_PER_SEC)<<endl;




    //wersja 2-z wykorzystaniem vectora
    t=clock();
    vector < vector < float > > wektor=odczytaj2(plik);
    wyswietl(wektor);
    t = clock() - t;
    cout<<endl<<"Czas wykonywania drugiej metody:  "<<(((float)t)/CLOCKS_PER_SEC);


    //Szybciej jest z wykorzystaniem z wektora

    return 0;
}


unsigned ilosc_kolumn(string linia)
{
    int k=1;
    for(int i=0;i<linia.length();i++)
    {
        if (linia[i]==' ')
        {
            k++;
        }
    }

    return k;
}


void kasowanie(tablica_struct t)
{

    for (unsigned i=0;i<t.w;i++)
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

void wyswietl(vector < vector < float > > wektor)
{
    for (int i=0;i<wektor.size();i++)
    {
        cout<<endl;
        for (int j=0;j<wektor[i].size();j++)
        {
           cout<<wektor[i][j]<<"   ";
        }
    }
}

bool czyZawieraZnak(string linia)
{
    for (int i=0;i<linia.length();i++)
       if (linia[i]==' ')
            return true;
    return false;
}

vector < vector < float > >  odczytaj2(char * sciezka)
{
    fstream plik(sciezka, ios::in);
    if(plik.good()==false)
        {
        cout<<"Nie mozna otworzyc pliku!";
        exit(0);
        }

    else{
        string linia;
        unsigned k=0,wiersz=0,pozycja=0;
        string pomocnicza;
        while ((!plik.eof()))
            {
                getline(plik, linia);
                wektor.push_back( vector < float >());
                k=0;
                while(linia!="")
                {
                    pozycja=linia.find(" ");
                    if(czyZawieraZnak(linia))
                    {
                        pomocnicza=linia.substr(0,pozycja);
                        linia.erase(0,pozycja+1);
                        wektor[wiersz].push_back(atof(pomocnicza.c_str()));
                        k++;
                    }
                    else
                    {
                         pomocnicza=linia.substr(0,linia.length());
                        linia.erase(0,linia.length());
                        wektor[wiersz].push_back(atof(pomocnicza.c_str()));
                        k++;
                    }

                }
                wiersz++;
            }
    return wektor;
    }
}


