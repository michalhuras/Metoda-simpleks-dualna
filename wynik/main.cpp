#include <iostream>
#include <fstream> //biblioteka odpowiedzialna za prace z plikami
#include <cstdlib> //biblioteka dla exit(0);
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//w programie matlabowy funkcja wynik


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

    char* plik="tabela_simplex1.txt";
    tablica_struct tablica;
    tablica=odczytaj(plik);
    wyswietl(tablica);


    double* punkt= new double[tablica.k-2];
    double  funkcja_celu;

    for (unsigned i=0;i<tablica.k-2;i++)
    {
        for (unsigned j=0;j<tablica.w;j++)
            if (tablica.tablica[j][0]==i+1)
            punkt[i]=tablica.tablica[j][1];

        for (unsigned j=2;j<tablica.k;j++)
            if (tablica.tablica[0][j]==i+1)
            punkt[i]=0;
    }

    funkcja_celu=-1*tablica.tablica[1][1];


    cout<<"Funkcja celu wynosi: "<<funkcja_celu<<endl;
    cout<<"Wierzcho³ki:  "<<endl;
    for (unsigned i=0;i<tablica.k-2;i++)
        cout<<punkt[i]<<endl;

    delete[]punkt;
    return 0;
}
