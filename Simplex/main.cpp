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

void krok (tablica_struct tab,tablica_struct tab2)
{
    unsigned w=tab.w,k=tab.k;

    unsigned m,n;
    for(unsigned i=2;i<k;i++)
    {
        if (tab.tablica[1][i]==0)
        {
            m=i;
            break;
        }
    }

    float wyznacznik,a,mini;
    for (unsigned i=2;i<w;i++)
    {
        if (tab.tablica[i][m]>0)
        {
            wyznacznik=tab.tablica[i][1]/tab.tablica[i][m];
            if (a==0)
                {
                mini=wyznacznik;
                n=i;
                a=a+1;
                }
            if (wyznacznik<mini)
                {
                mini=wyznacznik;
                n=i;
                }
        }
    }
wyswietl(tab2);
    int zerowa[w][k];
    for (int i=0;i<w;i++)
    {
        for(int j=0;j<k;j++)
        {
           tab2.tablica[i][j]=tab.tablica[i][j];
           zerowa[i][j]=1;
        }

    }

    for (int i=0;i<k;i++)
        zerowa[0][i]=0;
    for(int i=0;i<w;i++)
        zerowa[i][0]=0;


    tab2.tablica[0][m]=tab.tablica[n][0];
    tab2.tablica[n][0]=tab.tablica[0][m];

    for(int i=1;i<k;i++)
        {
        if(i==m)
            tab2.tablica[n][i]=1/tab.tablica[n][m];
        else
            tab2.tablica[n][i]=tab.tablica[n][i]/tab.tablica[n][m];

        zerowa[n][i]=0;
        }

    for(int i=1;i<w;i++)
        if(i!=n)
        {
            tab2.tablica[i][m]=-1*(tab.tablica[i][m]/tab.tablica[n][m]);
            zerowa[i][m]=0;
        }




    for (int i=1;i<k;i++)
        for(int j=1;j<w;j++)
            if (zerowa[j][i]!=0)
                tab2.tablica[j][i]=tab.tablica[j][i]-((tab.tablica[n][i]*tab.tablica[j][m])/tab.tablica[n][m]);

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

    //KROK
    tablica_struct tablica2;
    tablica2.w=tablica.w;
    tablica2.k=tablica.k;
    tablica2=implementacja_tablicy(tablica2);

    cout<<"kupa"<<endl;

    krok(tablica,tablica2);
    wyswietl(tablica2);
    /*
    string nowy_plik;
    cout<<"Wpisz nazwe do ktorej zapisac nowa tablice"<<endl;
    cin>>nowy_plik;
    nowy_plik=nowy_plik+".txt";
    char* plikstr=&nowy_plik[0];
    fstream plik2(plikstr, ios::out);


    for (int i=0;i<tablica.w;i++)
    {
        for (int j=0;j<tablica.k;j++)
        {
           plik2<<tablica2.tablica[i][j]<<" ";
        }
         plik2<<endl;
    }
    */
    kasowanie(tablica);
    kasowanie(tablica2);

    return 0;
}
