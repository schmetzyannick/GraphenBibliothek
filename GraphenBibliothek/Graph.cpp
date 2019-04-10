#include "Graph.h"
#include <fstream>
#include <list>
#include <time.h>

Graph::Graph(bool gerichtet)
{
	this->gerichtet = gerichtet;
	this->kantenListe = vector<Kante>();
	this->knotenListe = vector<Knoten>();
	this->adjaListe = vector<vector<Knoten>>();
}

Graph::Graph(bool gerichtet, vector<Kante> kantenListe, vector<Knoten> knotenListe, vector<vector<Knoten>>adjaListe)
{
	this->gerichtet = gerichtet;
	this->kantenListe = kantenListe;
	this->knotenListe = knotenListe;
	this->adjaListe = adjaListe;
}

bool Graph::getGerichtet()
{
	return this->gerichtet;
}

vector<Kante> Graph::getKantenListe()
{
	return this->kantenListe;
}

vector<Knoten> Graph::getKnotenListe()
{
	return this->knotenListe;
}

vector<vector<Knoten>> Graph::getAdjaListe()
{
	return this->adjaListe;
}

void Graph::setGerichtet(bool gerichtet)
{
	this->gerichtet = gerichtet;
}

void Graph::setKantenListe(vector<Kante> kantenListe)
{
	this->kantenListe = kantenListe;
}

void Graph::setKnotenListe(vector<Knoten> knotenListe)
{
	this->knotenListe = knotenListe;
}

void Graph::setAdjaListe(vector<vector<Knoten>> adjaList)
{
	this->adjaListe = adjaList;
}

void Graph::GraphFromTextfile()
{
	char pfad[4096];
	cout << "\nBitte geben Sie einen Dateipfad ein: ";
	cin >> pfad;

	string dateipfad = pfad;

	ifstream datei(dateipfad.c_str());
	while (!datei.good() || dateipfad.find(".txt") != dateipfad.length() - 4) {
		cout << "Datei existiert nicht!\n Bitte geben Sie den Pfad erneut ein!\n";
		cout << "Bitte geben Sie einen Dateipfad ein: ";
		getline(cin, dateipfad);
		datei = ifstream(dateipfad);
	}

	//Knotenanzahl ermitteln
	int anzahlKnoten = -1;
	try {
		datei >> anzahlKnoten;
		for (int i = 0; i < anzahlKnoten; i++) {
			knotenListe.push_back(Knoten(i));
			adjaListe.push_back(vector<Knoten>());
		}

		int links;
		int rechts;
		//Kantenliste anlegen
		if (this->gerichtet == false) {
			while (datei >> links >> rechts)
			{
				kantenListe.push_back(Kante(knotenListe.at(links), knotenListe.at(rechts), 0));
				adjaListe.at(links).push_back(knotenListe.at(rechts));
				adjaListe.at(rechts).push_back(knotenListe.at(links));
			}
		}
		else {
			while (datei >> links >> rechts)
			{
				kantenListe.push_back(Kante(knotenListe.at(links), knotenListe.at(rechts), 1));
				adjaListe.at(links).push_back(knotenListe.at(rechts));
			}
		}
		datei.close();
	}
	catch (...) {
		datei.close();
		throw exception("Detei Korrupt");
	}
	return;
}

//aktuell ungenutzt (veraltet)
inline Knoten Graph::ersterUnmarkierter()
{
	for (vector<Knoten>::iterator iter = this->knotenListe.begin();
		iter != this->knotenListe.end(); ++iter) {
		if (!iter->isMarked())
			return *iter;
	}
	return Knoten(-1);
}

inline void Graph::Breitensuche(int start)
{
	list<Knoten> schlange = list<Knoten>();
	this->knotenListe.at(start).markKnoten();
	schlange.push_front(this->knotenListe.at(start));
	while (!schlange.empty()) {
		int tmp = schlange.front().getKnotenNummer();
		schlange.pop_front();
		for (vector<Knoten>::iterator iter = this->adjaListe.at(tmp).begin();
			iter != this->adjaListe.at(tmp).end(); ++iter) {
			int nr = iter->getKnotenNummer();
			if (!knotenListe.at(nr).isMarked()) {
				knotenListe.at(nr).markKnoten();
				schlange.push_back(knotenListe.at(nr));
			}
		}
	}
}

int Graph::Zusammenhangskomponenten()
{
	clock_t anfang = clock();
	Knoten naechster = this->ersterUnmarkierter();
	int komponenten = 0;
	for (vector<Knoten>::iterator iter = this->knotenListe.begin();
		iter != this->knotenListe.end(); ++iter) {

		if (!iter->isMarked()) {
			komponenten++;
			Breitensuche(iter->getKnotenNummer());
		}
	}
	clock_t ende = clock();
	cout << "Laufzeit: " << ((float)(ende - anfang) / CLOCKS_PER_SEC) << " Sekunden" << endl;
	return komponenten;
}
