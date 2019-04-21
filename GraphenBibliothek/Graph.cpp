#include "Graph.h"
#include <fstream>
#include <list>
#include <time.h>
#include <queue>
#include <math.h>
#include <set>

Graph::Graph(bool gerichtet, bool gewichtet)
{
	this->gerichtet = gerichtet;
	this->gewichtet = gewichtet;
	this->kantenListe = vector<Kante>();
	this->knotenListe = vector<Knoten>();
}

Graph::Graph(bool gerichtet, bool gewichtet, vector<Kante> kantenListe, vector<Knoten> knotenListe)
{
	this->gerichtet = gerichtet;
	this->gewichtet = gewichtet;
	this->kantenListe = kantenListe;
	this->knotenListe = knotenListe;
}

bool Graph::getGerichtet()
{
	return this->gerichtet;
}

bool Graph::getGewichtet()
{
	return this->gewichtet;
}

vector<Kante> Graph::getKantenListe()
{
	return this->kantenListe;
}

vector<Knoten> Graph::getKnotenListe()
{
	return this->knotenListe;
}

void Graph::setGerichtet(bool gerichtet)
{
	this->gerichtet = gerichtet;
}

void Graph::setGewichtet(bool gewichtet)
{
	this->gewichtet = gewichtet;
}

void Graph::setKantenListe(vector<Kante> kantenListe)
{
	this->kantenListe = kantenListe;
}

void Graph::setKnotenListe(vector<Knoten> knotenListe)
{
	this->knotenListe = knotenListe;
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
			shared_ptr<vector<Knoten>> nachbarn = make_shared<vector<Knoten>>();
			shared_ptr<vector<Kante>> anliegend = make_shared<vector<Kante>>();
			this->knotenListe.push_back(Knoten(i, false, nachbarn, anliegend));
		}

		int links;
		int rechts;
		double gewicht;
		//Kantenliste anlegen
		if (this->gerichtet == false) {
			if (!gewichtet) {
				while (datei >> links >> rechts)
				{
					kantenListe.push_back(Kante(knotenListe.at(links), knotenListe.at(rechts)));
					this->knotenListe.at(links).nachbarn->push_back(this->knotenListe.at(rechts));
					this->knotenListe.at(rechts).nachbarn->push_back(this->knotenListe.at(links));

					this->knotenListe.at(links).anliegendeKanten->push_back(this->kantenListe.back());
					this->knotenListe.at(rechts).anliegendeKanten->push_back(this->kantenListe.back());
				}
			}
			else {
				while (datei >> links >> rechts >> gewicht)
				{
					kantenListe.push_back(Kante(knotenListe.at(links), knotenListe.at(rechts), 0, gewicht));
					this->knotenListe.at(links).nachbarn->push_back(this->knotenListe.at(rechts));
					this->knotenListe.at(rechts).nachbarn->push_back(this->knotenListe.at(links));

					this->knotenListe.at(links).anliegendeKanten->push_back(this->kantenListe.back());
					this->knotenListe.at(rechts).anliegendeKanten->push_back(this->kantenListe.back());
				}
			}
		}
		else {
			if (!gewichtet) {
				while (datei >> links >> rechts)
				{
					kantenListe.push_back(Kante(knotenListe.at(links), knotenListe.at(rechts), 1));
					this->knotenListe.at(links).nachbarn->push_back(this->knotenListe.at(rechts));
					this->knotenListe.at(links).anliegendeKanten->push_back(this->kantenListe.back());
				}
			}
			else {
				while (datei >> links >> rechts >> gewicht)
				{
					kantenListe.push_back(Kante(knotenListe.at(links), knotenListe.at(rechts), 1, gewicht));
					this->knotenListe.at(links).nachbarn->push_back(this->knotenListe.at(rechts));
					this->knotenListe.at(links).anliegendeKanten->push_back(this->kantenListe.back());
				}
			}
		}
		datei.close();
	}
	catch (exception e) {
		throw e;
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
	return Knoten();
}

inline void Graph::Breitensuche(int start)
{
	list<Knoten> schlange = list<Knoten>();
	this->knotenListe.at(start).markKnoten();
	schlange.push_front(this->knotenListe.at(start));
	while (!schlange.empty()) {
		int tmp = schlange.front().getKnotenNummer();
		schlange.pop_front();
		for (vector<Knoten>::iterator iter = this->knotenListe.at(tmp).nachbarn->begin();
			iter != this->knotenListe.at(tmp).nachbarn->end(); ++iter) {
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
	/*clock_t anfang = clock();*/
	Knoten naechster = this->ersterUnmarkierter();
	int komponenten = 0;
	for (vector<Knoten>::iterator iter = this->knotenListe.begin();
		iter != this->knotenListe.end(); ++iter) {

		if (!iter->isMarked()) {
			komponenten++;
			Breitensuche(iter->getKnotenNummer());
		}
	}
	//clock_t ende = clock();
	//cout << "Laufzeit: " << ((float)(ende - anfang) / CLOCKS_PER_SEC) << " Sekunden" << endl;
	return komponenten;
}

shared_ptr<vector<Kante>> Graph::KruskalMST()
{
	if (Zusammenhangskomponenten() > 1 || this->gerichtet==true) {
		cout << "Der Graph muss zusammenhängend und ungerichtet sein! " << endl;
		return NULL;
	}

	clock_t anfang = clock();
	vector<Kante> copyKantenListe = this->getKantenListe();
	this->sortKantenListe();

	DisjointedSetKnoten dsKnoten(knotenListe.size());
	vector<Kante>::iterator iterator;

	double mst_kosten = 0;
	shared_ptr<vector<Kante>> mst = make_shared<vector<Kante>>();
	for (iterator = kantenListe.begin(); iterator != kantenListe.end() 
		|| mst->size() == knotenListe.size()-1; iterator++) {

		int links = iterator->getLinks().getKnotenNummer();
		int rechts = iterator->getRechts().getKnotenNummer();

		int set_links = dsKnoten.find(links);
		int set_rechts = dsKnoten.find(rechts);

		if (set_links != set_rechts) {
			mst_kosten += iterator->getGewicht();
			dsKnoten.unionByRang(set_links, set_rechts);
		}
	}
	this->kantenListe = copyKantenListe;
	cout << mst_kosten << endl;
	clock_t ende = clock();
	cout << "Laufzeit: " << ((float)(ende - anfang) / CLOCKS_PER_SEC) << " Sekunden" << endl;
	return mst;
}

void Graph::sortKantenListe()
{
	mergeSort(0, kantenListe.size() - 1);
}

//Merge Sort
void Graph::mergeSort(int l, int r)
{
	if (l < r) {
		int m = (l+r)/2;

		mergeSort(l, m);
		mergeSort(m + 1, r);
		merge(l, m, r);
	}
}

void Graph::merge(int links, int mitte, int rechts)
{
	int n1 = mitte - links + 1;
	int n2 = rechts - mitte;

	/* Temporäre Vectoren */
	vector<Kante> copyLinks, copyRechts;

	for (int i = 0; i < n1; i++)
		copyLinks.push_back(kantenListe[links + i]);
	for (int j = 0; j < n2; j++)
		copyRechts.push_back(kantenListe[mitte + 1 + j]);


	int i = 0;		// Initial index des linken vectors
	int j = 0;		// Initial index des rechten vectors
	int k = links;  // Initial index des ergebnis vectors
	while (i < n1 && j < n2)
	{
		if (copyLinks.at(i).getGewicht() <= copyRechts.at(j).getGewicht())
		{
			kantenListe[k] = copyLinks[i];
			i++;
		}
		else
		{
			kantenListe[k] = copyRechts[j];
			j++;
		}
		k++;
	}

	/* Rest links kopieren */
	while (i < n1)
	{
		kantenListe[k] = copyLinks[i];
		i++;
		k++;
	}
	/* Rest rechts kopieren */
	while (j < n2)
	{
		kantenListe[k] = copyRechts[j];
		j++;
		k++;
	}
}

vector<Kante> Graph::PrimMST()
{
	clock_t anfang = clock();
	
	//Kanten werden automatisch nach ihrem gewicht sortiert
	priority_queue<Kante, vector<Kante>, KantenVergleichen> pq = priority_queue<Kante, vector<Kante>, KantenVergleichen>();

	//Kanten des mst
	vector<Kante> mst = vector<Kante>();

	Knoten aktuellerKnoten = knotenListe[0];

	//hält die bereits besuchten Knoten
	set<int> besuchteKnoten = set<int>();
	besuchteKnoten.insert(aktuellerKnoten.getKnotenNummer());

	double weight = 0.0;
	bool addKanten = true;

	while (mst.size() < knotenListe.size() - 1) {
		//wurde der aktuelleKnoten geaendert und somit eine Kante zum mst hinzugefuegt?
		if (addKanten) {
			//fuege Kanten des neuen Knoten in die pq
			for (vector<Kante>::iterator iterKanten = aktuellerKnoten.anliegendeKanten->begin();
				iterKanten != aktuellerKnoten.anliegendeKanten->end(); ++iterKanten) {
				pq.push(*iterKanten);
			}
		}
		
		Kante toInsert = pq.top();
		pq.pop();
		//linker Knoten noch nicht besucht
		if (besuchteKnoten.find(toInsert.getLinks().getKnotenNummer()) == besuchteKnoten.end()) {
			mst.push_back(toInsert);
			weight += toInsert.getGewicht();
			besuchteKnoten.insert(toInsert.getLinks().getKnotenNummer());
			aktuellerKnoten = toInsert.getLinks();
			addKanten = true;
		}//rechter Knoten noch nicht besucht
		else if(besuchteKnoten.find(toInsert.getRechts().getKnotenNummer()) == besuchteKnoten.end()){
			mst.push_back(toInsert);
			weight += toInsert.getGewicht();
			besuchteKnoten.insert(toInsert.getRechts().getKnotenNummer());
			aktuellerKnoten = toInsert.getRechts();
			addKanten = true;
		}//beide Knoten bereits besucht
		else {
			addKanten = false;
		}
	}

	cout << "Kosten: " << weight << endl;
	clock_t ende = clock();
	cout << "Laufzeit: " << ((float)(ende - anfang) / CLOCKS_PER_SEC) << " Sekunden" << endl;
	return mst;
}
