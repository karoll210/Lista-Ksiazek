#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

class Menu;

class Ksiazka
{
	public:
		fstream plik;
	protected:
		string l;	
		vector<string> vbooks;

	public:
		Ksiazka();
		~Ksiazka();
		void sortuj();
		void wypisz();
};

class Edytuj : public Ksiazka
{
	public:
		Edytuj();
		~Edytuj();
		void DodajTekst(Menu&  m);
		void UsunTekst(Menu&  n);
};

class Menu : public Ksiazka
{
	friend class Edytuj;

	private:
		string dodaj;
		int usun;
	
	public:
		Menu(string d, int u);
		void setDodaj(string s);
		string getDodaj();
		void setUsun(int a);
		int getUsun();
};

//Metody klasy Ksiazka

Ksiazka::Ksiazka()
{
	vbooks.clear();
	ifstream plik("books.txt");
	if (! plik) cout << "Brak pliku 'books.txt' w katalogu z programem. Sproboj ponownie\n" << endl;
	while (getline(plik, l)) vbooks.push_back(l); //zapisywanie tresci do wektora
}

Ksiazka::~Ksiazka()
{
	plik.close();
}

void Ksiazka::sortuj()
{
	sort( vbooks.begin(), vbooks.end() ); //sortowanie
	for (int i=0; i<vbooks.size(); i++)
	{
		plik << vbooks[i] << endl;
	}
}

void Ksiazka::wypisz()
{
	for (int i=0; i<vbooks.size(); i++)
	{
		cout << i + 1 << ". " <<  vbooks[i] << endl;
	}
}

//Metody klasy Edytuj

Edytuj::Edytuj()
{
	plik.open("books.txt", ios::out);
}

Edytuj::~Edytuj()
{
	plik.close();
}

void Edytuj::DodajTekst(Menu&  m)
{	
	vbooks.push_back(m.dodaj);  
	sort( vbooks.begin(), vbooks.end() ); 
	for (int i=0; i<vbooks.size(); i++)
	{
		plik << vbooks[i] << endl;
	}

}

void Edytuj::UsunTekst(Menu&  n)
{
	int h = (n.usun - 1);
	vbooks.erase(vbooks.begin() + h);
	sort( vbooks.begin(), vbooks.end() ); 
	for (int i=0; i<vbooks.size(); i++)
	{
		plik << vbooks[i] << endl;
	}
}

//Metody klasy Menu
Menu::Menu(string d, int u)
{
	setDodaj(d);
	setUsun(u);
}

void Menu::setDodaj(string d)
{
	dodaj = d;
}

string Menu::getDodaj()
{
	return dodaj;
}

void Menu::setUsun(int a)
{
	usun = a;
}

int Menu::getUsun()
{
	return usun;
}

int main()
{
	int wybor = 0;

	cout << "\n\nProgram wypisuje liste ksiazek" << endl;
	cout << "\n" << "************************************" << "\n\n" << endl;
	Ksiazka s;
	s.sortuj();
	s.wypisz();
	cout << "\n" << "************************************" << "\n\n" << endl;

	cout << "Wybierz jedna z opcji:" << endl;

	while(wybor != 4)
	{
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>\n" <<
			"1. Dodaj ksiazke do listy \n" <<
			"2. Usun ksiazke z listy\n" <<
			"3. Wypisz liste\n" <<
			"4. Zakoncz program" << 
			"\n<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>\n" << endl;

		cin >> wybor;

		switch(wybor)
		{
			case 1:
			{
				string v;
				string tytol;
				string autor;
				string gatunek;
				string l = ", ";
				getline(cin, tytol);
				cout << "Podaj tytul ksiazki: " << endl;
				getline(cin, tytol);
				cout << "Podaj autora: " << endl;
				getline(cin, autor);
				cout << "Podaj gatunek: " << endl;
				getline(cin, gatunek);
				v = tytol + l + autor + l + gatunek;
				Menu y(v, 0);
				Edytuj dk;
				dk.DodajTekst(y);
			}
			break; 
		
			case 2:
			{
				string a = "\0";
				int b = 0;
				cout << "Podaj nr wiersza ktory chcesz usunac: " << endl;
				cin >> b;
				Menu g(a, b);
				Edytuj uk;
				uk.UsunTekst(g);
			}
			break;

			case 3:
			{
				cout << endl;
				Ksiazka ks;
				ks.sortuj();
				ks.wypisz();
				cout << endl;
			}
			break;

			case 4:
				cout << "Zyczymy milego czytania!" << endl;
			
			default:
				cout << "Niema takiej opcji, sprubuj ponownie" << endl;	
		}

	}

	return 0;
}
