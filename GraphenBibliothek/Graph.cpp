/*
	<GraphenBibliothek>
	Copyright(C) < 2019 > <Yannick Luc Schmetz>

	This program is free software : you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.If not, see < https://www.gnu.org/licenses/>.
*/

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
	this->kantenListe = vector<shared_ptr<Kante>>();
	this->knotenListe = vector<shared_ptr<Knoten>>();
}

Graph::Graph(bool gerichtet, bool gewichtet, vector<shared_ptr<Kante>> kantenListe, vector<shared_ptr<Knoten>> knotenListe)
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

vector<shared_ptr<Kante>> Graph::getKantenListe()
{
	return this->kantenListe;
}

vector<shared_ptr<Knoten>> Graph::getKnotenListe()
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

void Graph::setKantenListe(vector<shared_ptr<Kante>> kantenListe)
{
	this->kantenListe = kantenListe;
}

void Graph::setKnotenListe(vector<shared_ptr<Knoten>> knotenListe)
{
	this->knotenListe = knotenListe;
}

void Graph::GraphFromTextfile(bool kapazität, bool balancen, bool mengenAngaben)
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
	this->file = pfad;
	//Knotenanzahl ermitteln
	int anzahlKnoten = -1;
	double balance;
	try {
		datei >> anzahlKnoten;
		for (int i = 0; i < anzahlKnoten; i++) {
			vector<shared_ptr<Knoten>> nachbarn = vector<shared_ptr<Knoten>>();
			vector<shared_ptr<Kante>> anliegend = vector<shared_ptr<Kante>>();
			this->knotenListe.push_back(make_shared<Knoten>(i, false, nachbarn, anliegend));
		}

		if (mengenAngaben) {
			int ueberlesen;
			datei >> ueberlesen;
		}
		

		if (balancen) {
			for (int i = 0; i < anzahlKnoten; i++) {
				datei >> balance;
				knotenListe[i]->setBalance(balance);
			}
		}

		int links;
		int rechts;
		double gewicht;
		double kapa;
		//Kantenliste anlegen
		if (this->gerichtet == false) {
			if (!gewichtet) {
				if (!kapazität) {
					while (datei >> links >> rechts)
					{
						kantenListe.push_back(make_shared<Kante>(knotenListe.at(links), knotenListe.at(rechts)));
						knotenListe[links]->nachbarn.push_back(shared_ptr<Knoten>(knotenListe[rechts]));
						knotenListe[rechts]->nachbarn.push_back(shared_ptr<Knoten>(knotenListe[links]));
					}
				}
				else {
					while (datei >> links >> rechts >> kapa)
					{
						kantenListe.push_back(make_shared<Kante>(knotenListe.at(links), knotenListe.at(rechts), 0, 0.0, kapa, 0, false));
						knotenListe[links]->nachbarn.push_back(shared_ptr<Knoten>(knotenListe[rechts]));
						knotenListe[rechts]->nachbarn.push_back(shared_ptr<Knoten>(knotenListe[links]));
					}
				}
			}
			else {
				while (datei >> links >> rechts >> gewicht)
				{
					kantenListe.push_back(make_shared<Kante>(knotenListe.at(links), knotenListe.at(rechts), 0, gewicht));
					knotenListe[links]->nachbarn.push_back(shared_ptr<Knoten>(knotenListe[rechts]));
					knotenListe[rechts]->nachbarn.push_back(shared_ptr<Knoten>(knotenListe[links]));
				}
			}
		}
		else {
			if (!gewichtet) {
				if (!kapazität) {
					while (datei >> links >> rechts)
					{
						kantenListe.push_back(make_shared<Kante>(knotenListe.at(links), knotenListe.at(rechts), 1));
						knotenListe[links]->nachbarn.push_back(shared_ptr<Knoten>(knotenListe[rechts]));
					}
				}
				else {
					while (datei >> links >> rechts >> kapa)
					{
						kantenListe.push_back(make_shared<Kante>(knotenListe.at(links), knotenListe.at(rechts), 1, 0.0, kapa, 0, false));
						knotenListe[links]->nachbarn.push_back(shared_ptr<Knoten>(knotenListe[rechts]));
					}
				}
			}
			else {
				if (!kapazität) {
					while (datei >> links >> rechts >> gewicht)
					{
						kantenListe.push_back(make_shared<Kante>(knotenListe.at(links), knotenListe.at(rechts), 1, gewicht));
						knotenListe[links]->nachbarn.push_back(shared_ptr<Knoten>(knotenListe[rechts]));
					}
				}
				else {
					while (datei >> links >> rechts >> gewicht >> kapa)
					{
						kantenListe.push_back(make_shared<Kante>(knotenListe.at(links), knotenListe.at(rechts), 1, gewicht, kapa, 0, false));
						knotenListe[links]->nachbarn.push_back(shared_ptr<Knoten>(knotenListe[rechts]));
					}
				}
				
			}
		}
		datei.close();
	}
	catch (exception e) {
		throw e;
	}

	vector<shared_ptr<Kante>>::iterator iterKante = this->kantenListe.begin();
	for (; iterKante != kantenListe.end(); ++iterKante) {
		if (gerichtet) {
			knotenListe[(*iterKante)->getLinks()->getKnotenNummer()]->anliegendeKanten.push_back(shared_ptr<Kante>((*iterKante)));
		}
		else {
			knotenListe[(*iterKante)->getLinks()->getKnotenNummer()]->anliegendeKanten.push_back(shared_ptr<Kante>((*iterKante)));
			knotenListe[(*iterKante)->getRechts()->getKnotenNummer()]->anliegendeKanten.push_back(shared_ptr<Kante>((*iterKante)));
		}
	}
	return;
}

inline void Graph::Breitensuche(int start)
{
	list<shared_ptr<Knoten>> schlange = list<shared_ptr<Knoten>>();
	this->knotenListe.at(start)->markKnoten();
	schlange.push_front(this->knotenListe.at(start));
	while (!schlange.empty()) {
		int tmp = schlange.front()->getKnotenNummer();
		schlange.pop_front();
		for (vector<shared_ptr<Knoten>>::iterator iter = knotenListe[tmp]->nachbarn.begin();
			iter != knotenListe[tmp]->nachbarn.end(); ++iter) {
			int nr = (*iter)->getKnotenNummer();
			if (!knotenListe.at(nr)->isMarked()) {
				knotenListe.at(nr)->markKnoten();
				schlange.push_back(knotenListe.at(nr));
			}
		}
	}
}

int Graph::Zusammenhangskomponenten()
{
	/*clock_t anfang = clock();*/
	shared_ptr<Knoten> naechster = knotenListe[0];
	int komponenten = 0;
	for (vector<shared_ptr<Knoten>>::iterator iter = this->knotenListe.begin();
		iter != this->knotenListe.end(); ++iter) {

		if (!(*iter)->isMarked()) {
			komponenten++;
			Breitensuche((*iter)->getKnotenNummer());
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

	vector<shared_ptr<Kante>> copyKantenListe = this->getKantenListe();
	this->sortKantenListe();

	DisjointedSetKnoten dsKnoten(knotenListe.size());
	vector<shared_ptr<Kante>>::iterator iterator;

	double mst_kosten = 0;
	shared_ptr<vector<Kante>> mst = make_shared<vector<Kante>>();
	for (iterator = kantenListe.begin(); (iterator != kantenListe.end())
		|| mst->size() != this->knotenListe.size()-1; ++iterator) {

		int links = (*iterator)->getLinks()->getKnotenNummer();
		int rechts = (*iterator)->getRechts()->getKnotenNummer();

		int set_links = dsKnoten.find(links);
		int set_rechts = dsKnoten.find(rechts);

		if (set_links != set_rechts) {
			mst->push_back(*(*iterator));
			mst_kosten += (*iterator)->getGewicht();
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
	vector<shared_ptr<Kante>> copyLinks, copyRechts;

	for (int i = 0; i < n1; i++)
		copyLinks.push_back(kantenListe[links + i]);
	for (int j = 0; j < n2; j++)
		copyRechts.push_back(kantenListe[mitte + 1 + j]);


	int i = 0;		// Initial index des linken vectors
	int j = 0;		// Initial index des rechten vectors
	int k = links;  // Initial index des ergebnis vectors
	while (i < n1 && j < n2)
	{
		if (copyLinks.at(i)->getGewicht() <= copyRechts.at(j)->getGewicht())
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

vector<Kante> Graph::PrimMST(int start)
{
	clock_t anfang = clock();
	
	//Kanten werden automatisch nach ihrem gewicht sortiert
	priority_queue<Kante, vector<Kante>, KantenVergleichen> pq = priority_queue<Kante, vector<Kante>, KantenVergleichen>();

	//Kanten des mst
	vector<Kante> mst = vector<Kante>();

	shared_ptr<Knoten> aktuellerKnoten = knotenListe[start];

	//hält die bereits besuchten Knoten
	//Verbesserung: array mit bool stelle = Knotennummer
	set<int> besuchteKnoten = set<int>();
	besuchteKnoten.insert(aktuellerKnoten->getKnotenNummer());

	double weight = 0.0;
	bool addKanten = true;

	while (mst.size() < knotenListe.size() - 1) {
		//wurde der aktuelleKnoten geaendert und somit eine Kante zum mst hinzugefuegt?
		if (addKanten) {
			//fuege Kanten des neuen Knoten in die pq
			//Verbesserung: nur Kanten bei denen nicht beide Knoten besucht sind
			for (vector<shared_ptr<Kante>>::iterator iterKanten = aktuellerKnoten->anliegendeKanten.begin();
				iterKanten != aktuellerKnoten->anliegendeKanten.end(); ++iterKanten) {
				pq.push(*(*iterKanten));
			}
		}
		
		Kante toInsert = pq.top();
		pq.pop();
		//linker Knoten noch nicht besucht
		if (besuchteKnoten.find(toInsert.getLinks()->getKnotenNummer()) == besuchteKnoten.end()) {
			mst.push_back(toInsert);
			weight += toInsert.getGewicht();
			besuchteKnoten.insert(toInsert.getLinks()->getKnotenNummer());
			aktuellerKnoten = toInsert.getLinks();
			addKanten = true;
		}//rechter Knoten noch nicht besucht
		else if(besuchteKnoten.find(toInsert.getRechts()->getKnotenNummer()) == besuchteKnoten.end()){
			mst.push_back(toInsert);
			weight += toInsert.getGewicht();
			besuchteKnoten.insert(toInsert.getRechts()->getKnotenNummer());
			aktuellerKnoten = toInsert.getRechts();
			addKanten = true;
		}//beide Knoten bereits besucht
		else {
			addKanten = false;
		}
	}

	cout << "Kosten: " << weight << endl;
	/*clock_t ende = clock();
	cout << "Laufzeit: " << ((float)(ende - anfang) / CLOCKS_PER_SEC) << " Sekunden" << endl;*/
	return mst;
}

vector<Kante> Graph::NearestNeighborTSP(int startKnoten)
{
	if (startKnoten > knotenListe.size() - 1) {
		throw exception("Startknoten existiert nicht!");
	}

	clock_t anfang = clock();

	//zum markieren der bereits besuchten Knoten
	deque<int> besuchteKnoten = deque<int>();
	for (int i = 0; i < knotenListe.size(); i++) {
		besuchteKnoten.push_back(false);
	}

	vector<Kante> tour = vector<Kante>();
	shared_ptr<Knoten> aktuell = knotenListe[startKnoten];
	besuchteKnoten[startKnoten] = true;

	double kosten = 0.0;
	int counter = 1;

	//n-1 Kanten -> danach tour schließen
	while (counter < knotenListe.size()) {
		shared_ptr<Kante> k;
	
		vector<shared_ptr<Kante>> anliegendeKantenSorted = aktuell->getKantenlisteSortet();
		vector<shared_ptr<Kante>>::iterator iter = anliegendeKantenSorted.begin();
		//finde die guenstigste Kante zu einem noch nicht besuchten Knoten
		for (; iter != anliegendeKantenSorted.end(); ++iter) {
			k = *iter;
			if ((k->getLinks()->getKnotenNummer() == aktuell->getKnotenNummer())
				&& (besuchteKnoten[k->getRechts()->getKnotenNummer()] == false)) {

				tour.push_back(*k);
				kosten += k->getGewicht();

				aktuell = k->getRechts();
				besuchteKnoten[k->getRechts()->getKnotenNummer()] = true;

				break;
			}
			else if ((k->getRechts()->getKnotenNummer() == aktuell->getKnotenNummer())
				&& (besuchteKnoten[k->getLinks()->getKnotenNummer()] == false)) {

				tour.push_back(*k);
				kosten += k->getGewicht();

				aktuell = k->getLinks();
				besuchteKnoten[k->getLinks()->getKnotenNummer()] = true;

				break;
			}
		}
		counter++;
	}

	//schließe die tour
	try {
		shared_ptr<Kante> k = aktuell->getGuenstigsteKantezuKnoten(startKnoten);
		kosten += k->getGewicht();
		tour.push_back(*k);
	}
	catch (exception e) {
		throw e;
	}

	cout << "Kosten: " << kosten << endl;
	clock_t ende = clock();
	cout << "Laufzeit: " << ((float)(ende - anfang) / CLOCKS_PER_SEC) << " Sekunden" << endl;
	return tour;
}

//int anzahl bes. knoten
void Graph::BranchAndBound(Node aktuellerNode, BABTree* tree, bool bound/*=true*/)
{
	//iteriere ueber anliegende Kanten
	vector<shared_ptr<Kante>> copyAnliegend = aktuellerNode.knoten->getKantenlisteSortet();
	for (int i = 0; i < copyAnliegend.size(); i++) {

		if (copyAnliegend[i]->getLinks()->getKnotenNummer() == aktuellerNode.knoten->getKnotenNummer() &&
			aktuellerNode.besuchteKnoten->at(copyAnliegend[i]->getRechts()->getKnotenNummer()) == false) {
			//Kante zu Knoten gefunden, der noch nicht besucht wurde im aktuellen ast
			double kosten = copyAnliegend[i]->getGewicht() + aktuellerNode.kostenBisher;
			shared_ptr<vector<bool>> copy = make_shared<vector<bool>>(*(aktuellerNode.besuchteKnoten));
			copy->at(copyAnliegend[i]->getRechts()->getKnotenNummer()) = true;

			Node n = Node(kosten, copyAnliegend[i]->getRechts(), copy);
			n.genutzteKanten = aktuellerNode.genutzteKanten;
			n.genutzteKanten.push_back(*copyAnliegend[i]);

			//Bounding
			//direkt nach kostenberechnung => Node muss nicht berechnet / erzeugt werden.
			if ((bound && n.kostenBisher < tree->besteTour) || !bound) {
				aktuellerNode.nachfolger.push_back(&n);
				//Branching
				BranchAndBound(n, tree, bound);
			}
			else {
				aktuellerNode.nachfolger.push_back(&n);
			}
			
		}
		else if (copyAnliegend[i]->getRechts()->getKnotenNummer() == aktuellerNode.knoten->getKnotenNummer() &&
			aktuellerNode.besuchteKnoten->at(copyAnliegend[i]->getLinks()->getKnotenNummer()) == false) {
			//Kante zu Knoten gefunden, der noch nicht besucht wurde im aktuellen ast
			double kosten = copyAnliegend[i]->getGewicht() + aktuellerNode.kostenBisher;
			shared_ptr<vector<bool>> copy = make_shared<vector<bool>>(*(aktuellerNode.besuchteKnoten));
			copy->at(copyAnliegend[i]->getLinks()->getKnotenNummer()) = true;

			Node n = Node(kosten, copyAnliegend[i]->getLinks(), copy);
			n.genutzteKanten = aktuellerNode.genutzteKanten;
			n.genutzteKanten.push_back(*copyAnliegend[i]);

			//Bounding
			if ((bound && n.kostenBisher < tree->besteTour) || !bound) {
				aktuellerNode.nachfolger.push_back(&n);
				//Branching
				BranchAndBound(n, tree, bound);
			}
			else {
				aktuellerNode.nachfolger.push_back(&n);
			}
		}
	}//end for

	//tour schließen
	if (aktuellerNode.nachfolger.empty()) {
		int nr = tree->root.knoten->getKnotenNummer();
		shared_ptr<Kante> k = aktuellerNode.knoten->getGuenstigsteKantezuKnoten(nr);
		aktuellerNode.genutzteKanten.push_back(*k);
		aktuellerNode.kostenBisher += k->getGewicht();
		if (aktuellerNode.kostenBisher < tree->besteTour) {
			tree->besteTour = aktuellerNode.kostenBisher;
			tree->tour = aktuellerNode.genutzteKanten;
		}
	}
}

vector<Kante> Graph::BranchAndBoundTSP()
{
	clock_t anfang = clock();
	BABTree tree = BABTree(this->knotenListe[0], this->knotenListe.size());
	BranchAndBound(tree.root, &tree, true);

	cout << "Kosten: " << tree.besteTour << endl;
	clock_t ende = clock();
	cout << "Laufzeit: " << ((float)(ende - anfang) / CLOCKS_PER_SEC) << " Sekunden" << endl;

	return tree.tour;
}

vector<Kante> Graph::TSPAusprobieren()
{
	clock_t anfang = clock();
	BABTree tree = BABTree(this->knotenListe[0], this->knotenListe.size());
	BranchAndBound(tree.root, &tree, false);

	cout << "Kosten: " << tree.besteTour << endl;
	clock_t ende = clock();
	cout << "Laufzeit: " << ((float)(ende - anfang) / CLOCKS_PER_SEC) << " Sekunden" << endl;
	return tree.tour;
	return vector<Kante>();
}

//tiefensuche einfacher allgemeiner 
vector<Kante> Graph::DoppelterBaumTSP(int startKnoten)
{
	if (startKnoten > knotenListe.size() - 1) {
		throw exception("Startknoten existiert nicht!");
	}

	clock_t anfang = clock();

	//min spannbaum mit prim => eulertour moeglich, die genau
	//in der reihenfolge der Kantenliste die Knoten abarbeitet
	vector<Kante> mstVec = PrimMST(startKnoten);
	deque<Kante> mst = deque<Kante>();
	for (int i = 0; i < mstVec.size(); i++) {
		mst.push_back(mstVec[i]);

	}

	vector<Kante> tspTour = vector<Kante>();

	vector<bool> besucht = vector<bool>();
	for (int i = 0; i < knotenListe.size(); i++) {
		besucht.push_back(false);
	}
	besucht[startKnoten] = true;
	int aktuellerKnoten = startKnoten;
	double kosten = 0.0;


	while (!mst.empty()) {
		Kante k = mst[0];
		//Kante kann aus mst genommen werden
		if (k.getLinks()->getKnotenNummer() == aktuellerKnoten && besucht[k.getRechts()->getKnotenNummer()] == false) {
			tspTour.push_back(k);
			mst.pop_front();

			kosten += k.getGewicht();
			besucht[k.getRechts()->getKnotenNummer()] = true;
			aktuellerKnoten = k.getRechts()->getKnotenNummer();
		}else if (k.getRechts()->getKnotenNummer() == aktuellerKnoten && besucht[k.getLinks()->getKnotenNummer()] == false) {
			tspTour.push_back(k);
			mst.pop_front();

			kosten += k.getGewicht();
			besucht[k.getLinks()->getKnotenNummer()] = true;
			aktuellerKnoten = k.getLinks()->getKnotenNummer();
		}
		else {//aktueller Knoten nicht in mst => abkuerzung
			if (besucht[k.getLinks()->getKnotenNummer()] == false) {

				shared_ptr<Kante> kurz = knotenListe[aktuellerKnoten]->getGuenstigsteKantezuKnoten(k.getLinks()->getKnotenNummer());
				mst.pop_front();
				tspTour.push_back(*kurz);
				kosten += kurz->getGewicht();

				besucht[k.getLinks()->getKnotenNummer()] = true;
				aktuellerKnoten = k.getLinks()->getKnotenNummer();

			}else if (besucht[k.getRechts()->getKnotenNummer()] == false) {

				shared_ptr<Kante> kurz = knotenListe[aktuellerKnoten]->getGuenstigsteKantezuKnoten(k.getRechts()->getKnotenNummer());
				mst.pop_front();
				tspTour.push_back(*kurz);
				kosten += kurz->getGewicht();

				besucht[k.getRechts()->getKnotenNummer()] = true;
				aktuellerKnoten = k.getRechts()->getKnotenNummer();
			}
		}
	}

	if (aktuellerKnoten = tspTour.back().getLinks()->getKnotenNummer()) {
		shared_ptr<Kante> k = tspTour.back().getLinks()->getGuenstigsteKantezuKnoten(startKnoten);
		tspTour.push_back(*k);
		kosten += k->getGewicht();
	}
	else if (aktuellerKnoten = tspTour.back().getRechts()->getKnotenNummer()) {
		shared_ptr<Kante> k = tspTour.back().getRechts()->getGuenstigsteKantezuKnoten(startKnoten);
		tspTour.push_back(*k);
		kosten += k->getGewicht();
	}

	cout << "Kosten: " << kosten << endl;
	clock_t ende = clock();
	cout << "Laufzeit: " << ((float)(ende - anfang) / CLOCKS_PER_SEC) << " Sekunden" << endl;

	//augabe:
	aktuellerKnoten = startKnoten;
	cout << startKnoten;
	vector<Kante>::iterator iterErgeb = tspTour.begin();
	for (; iterErgeb != tspTour.end(); ++iterErgeb) {
		if (iterErgeb->getLinks()->getKnotenNummer() == aktuellerKnoten) {
			aktuellerKnoten = iterErgeb->getRechts()->getKnotenNummer();
		}
		else {
			aktuellerKnoten = iterErgeb->getLinks()->getKnotenNummer();
		}
		cout << " -> " << aktuellerKnoten;
	}
	cout << endl;
	return tspTour;
}

vector<shared_ptr<KWBNode>>Graph::Dijkstra(int start)
{
	vector<shared_ptr<KWBNode>> kwbNodes = vector<shared_ptr<KWBNode>>();
	deque<shared_ptr<KWBNode>> nichtBetrachtet = deque<shared_ptr<KWBNode>>();

	shared_ptr<KWBNode> kstart = make_shared<KWBNode>(start, 0.0);
	kstart->vorgaenger = kstart;
	nichtBetrachtet.push_back(kstart);

	for (int i = 0; i < this->knotenListe.size(); i++) {
		if (i != start) {
			shared_ptr<KWBNode> k = make_shared<KWBNode>(i);
			kwbNodes.push_back(k);
			nichtBetrachtet.push_back(k);
		}
		else {
			kwbNodes.push_back(kstart);
		}
	}
	

	while (!nichtBetrachtet.empty() && nichtBetrachtet[0]->distanz < INFINITY) {
		shared_ptr<KWBNode> k = nichtBetrachtet[0];
		vector<shared_ptr<Kante>> anliegendeKanten = this->knotenListe[k->knotenNr]->getKantenlisteSortet();
		vector<shared_ptr<Kante>>::iterator iter = anliegendeKanten.begin();
		for (; iter != anliegendeKanten.end(); ++iter) {
			if ((*iter)->getLinks()->getKnotenNummer() == k->knotenNr) {
				if (k->distanz + (*iter)->getGewicht() < kwbNodes[(*iter)->getRechts()->getKnotenNummer()]->distanz) {
					kwbNodes[(*iter)->getRechts()->getKnotenNummer()]->distanz = k->distanz + (*iter)->getGewicht();
					kwbNodes[(*iter)->getRechts()->getKnotenNummer()]->vorgaenger = k;
				}
			}
			else {
				if (k->distanz + (*iter)->getGewicht() < kwbNodes[(*iter)->getLinks()->getKnotenNummer()]->distanz) {
					kwbNodes[(*iter)->getLinks()->getKnotenNummer()]->distanz = k->distanz + (*iter)->getGewicht();
					kwbNodes[(*iter)->getLinks()->getKnotenNummer()]->vorgaenger = k;
				}
			}
		}
		nichtBetrachtet.pop_front();
		std::sort(nichtBetrachtet.begin(), nichtBetrachtet.end(), KWBVergleich());
	}
	
	return kwbNodes;
}

vector<shared_ptr<KWBNode>> Graph::MooreBellmanFord(int start, bool findCycle)
{
	//Schritt1
	vector<shared_ptr<KWBNode>> kwbNodes = vector<shared_ptr<KWBNode>>();
	for (int i = 0; i < this->knotenListe.size(); i++) {
		if (i != start) {
			shared_ptr<KWBNode> k = make_shared<KWBNode>(i);
			kwbNodes.push_back(k);
		}
		else {
			shared_ptr<KWBNode> k = make_shared<KWBNode>(start, 0.0);
			k->vorgaenger = k;
			kwbNodes.push_back(k);
		}
	}

	vector<int> changedInLastIter = vector<int>();
	//Schritt2
	for (int i = 0; i < knotenListe.size()-1; i++) {
		vector<shared_ptr<Kante>>::iterator iter = this->kantenListe.begin();
		for (; iter != this->kantenListe.end(); ++iter) {

			if (kwbNodes[(*iter)->getLinks()->getKnotenNummer()]->distanz + (*iter)->getGewicht()
				< kwbNodes[(*iter)->getRechts()->getKnotenNummer()]->distanz) {
				kwbNodes[(*iter)->getRechts()->getKnotenNummer()]->distanz = kwbNodes[(*iter)->getLinks()->getKnotenNummer()]->distanz + (*iter)->getGewicht();
				kwbNodes[(*iter)->getRechts()->getKnotenNummer()]->vorgaenger = kwbNodes[(*iter)->getLinks()->getKnotenNummer()];
				if (findCycle && i == kantenListe.size() - 2) {
					changedInLastIter.push_back((*iter)->getRechts()->getKnotenNummer());
				}
			}

			if (this->gerichtet == false) {
				//andersrum betrachten
				if (kwbNodes[(*iter)->getRechts()->getKnotenNummer()]->distanz + (*iter)->getGewicht()
					< kwbNodes[(*iter)->getLinks()->getKnotenNummer()]->distanz) {
					kwbNodes[(*iter)->getLinks()->getKnotenNummer()]->distanz = kwbNodes[(*iter)->getRechts()->getKnotenNummer()]->distanz + (*iter)->getGewicht();
					kwbNodes[(*iter)->getLinks()->getKnotenNummer()]->vorgaenger = kwbNodes[(*iter)->getRechts()->getKnotenNummer()];
				}
			}

		}
	}

	//Schritt 3
	vector<shared_ptr<Kante>>::iterator iter = this->kantenListe.begin();
	for (; iter != this->kantenListe.end(); ++iter) {

		if (kwbNodes[(*iter)->getLinks()->getKnotenNummer()]->distanz + (*iter)->getGewicht()
			< kwbNodes[(*iter)->getRechts()->getKnotenNummer()]->distanz) {
			if (findCycle == true) {
				int i = (*iter)->getLinks()->getKnotenNummer();
				bool *visited = new bool[knotenListe.size()];
				for (int j = 0; j < knotenListe.size(); j++) {
					visited[j] = false;
				}

				//einen Knoten aus dem zyklus finden
				while (visited[i]==false) {
					visited[i] = true;
					i = kwbNodes[i]->vorgaenger->knotenNr;
				}

				vector<shared_ptr<KWBNode>> kantenCycle = vector<shared_ptr<KWBNode>>();
				int laufVar=i;
				do {
					kantenCycle.push_back(kwbNodes[laufVar]->vorgaenger);
					laufVar = kwbNodes[laufVar]->vorgaenger->knotenNr;
				} while (laufVar != i);
				

				return kantenCycle;
			}
			else {
				kwbNodes.clear();
				break;
			}
		}
		if (this->gerichtet == false) {
			//andersrum betrachten
			if (kwbNodes[(*iter)->getRechts()->getKnotenNummer()]->distanz + (*iter)->getGewicht()
				< kwbNodes[(*iter)->getLinks()->getKnotenNummer()]->distanz) {
				kwbNodes.clear();
				break;
			}
		}

	}

	if (findCycle) {
		kwbNodes.clear();
		return kwbNodes;
	}
	return kwbNodes;
}

deque<shared_ptr<Kante>> Graph::DijkstraSTP(int start, int ende, double &kosten)
{
	//KWB errechnen
	vector<shared_ptr<KWBNode>> kwb = Dijkstra(start);

	//Dann auf kwb den web suchen
	kosten = kwb[ende]->distanz;
	deque<shared_ptr<Kante>> weg = deque<shared_ptr<Kante>>();
	shared_ptr<KWBNode> aktuell = kwb[ende];

	if (aktuell->distanz == INFINITY) {
		return deque<shared_ptr<Kante>>();
	}

	while (aktuell != kwb[start]) {
		shared_ptr<Knoten> k = this->knotenListe[aktuell->vorgaenger->knotenNr];
		weg.push_front(k->getGuenstigsteKantezuKnoten(aktuell->knotenNr));
		aktuell = kwb[k->getKnotenNummer()];
	}
	kosten = kwb[ende]->distanz;
	return weg;
}

deque<shared_ptr<Kante>> Graph::MooreBellmanFordSTP(int start , int ende, double & kosten)
{
	//KWB errechnen
	vector<shared_ptr<KWBNode>> kwb = MooreBellmanFord(start);

	if (kwb.empty()) {
		kosten = INFINITY;
		return deque<shared_ptr<Kante>>();
	}

	//Dann auf kwb den web suchen
	kosten = kwb[ende]->distanz;
	deque<shared_ptr<Kante>> weg = deque<shared_ptr<Kante>>();
	shared_ptr<KWBNode> aktuell = kwb[ende];

	if (aktuell->distanz == INFINITY) {
		return deque<shared_ptr<Kante>>();
	}

	while (aktuell != kwb[start]) {
		shared_ptr<Knoten> k = this->knotenListe[aktuell->vorgaenger->knotenNr];
		weg.push_front(k->getGuenstigsteKantezuKnoten(aktuell->knotenNr));
		aktuell = kwb[k->getKnotenNummer()];
	}
	kosten = kwb[ende]->distanz;
	return weg;
	
}

bool Graph::bfs(shared_ptr<Graph> g, int s, int t, int *parent)
{
	bool *visited = new bool[g->knotenListe.size()];
	for (int i = 0; i < g->knotenListe.size(); i++) {
		visited[i] = false;
	}

	deque <int> q;
	q.push_back(s);
	visited[s] = true;
	parent[s] = -1;
	int markCounter = 1;
	while (!q.empty())
	{
		int u = q.front();
		q.pop_front();

		vector<shared_ptr<Kante>>::iterator iterNachbarn = knotenListe[u]->anliegendeKanten.begin();
		for(; iterNachbarn != knotenListe[u]->anliegendeKanten.end(); ++iterNachbarn)
		//for (int v = 0; v < g->knotenListe.size(); v++)
		{
			if (visited[(*iterNachbarn)->getRechts()->getKnotenNummer()] == false)
			{	
				if ((*iterNachbarn)->getKapazität() > 0.0) {
					q.push_back((*iterNachbarn)->getRechts()->getKnotenNummer());
					parent[(*iterNachbarn)->getRechts()->getKnotenNummer()] = u;
					visited[(*iterNachbarn)->getRechts()->getKnotenNummer()] = true;
				}
			}
		}
	}
	return (visited[t] == true);
}

deque<shared_ptr<Kante>> Graph::bfs(shared_ptr<Graph> g, int s, int t)
{
	int *parent = new int[g->knotenListe.size()];
	for (int i = 0; i < g->knotenListe.size(); i++) {
		parent[i] = NULL;
	}

	this->bfs(g, s, t, parent);

	int vorgaenger = parent[t];
	if (vorgaenger == NULL) {
		return deque<shared_ptr<Kante>>();
	}

	int aktuell = t;
	deque<shared_ptr<Kante>> weg = deque<shared_ptr<Kante>>();
	while (vorgaenger != -1) {
		weg.push_front(knotenListe[vorgaenger]->getGuenstigsteKantezuKnoten(aktuell));
		aktuell = vorgaenger;
		vorgaenger = parent[aktuell];
	}
	return weg;
}

void Graph::updateKnotenKanten()
{
	for (int i = 0; i < knotenListe.size(); i++) {
		vector<shared_ptr<Kante>> liste = vector<shared_ptr<Kante>>();
		if (this->gerichtet) {
			vector<shared_ptr<Kante>>::iterator iter = kantenListe.begin();
			for (; iter != this->kantenListe.end(); ++iter) {
				if ((*iter)->getLinks()->getKnotenNummer() == knotenListe[i]->getKnotenNummer()) {
					liste.push_back(shared_ptr<Kante>((*iter)));
				}
			}
			this->knotenListe[i]->anliegendeKanten = liste;
		}
	}
}

shared_ptr<Graph> Graph::getResidualgraphFF()
{

	shared_ptr<Graph> res = make_unique<Graph>(*this);
	vector<shared_ptr<Kante>> kantenOrignalGraph = vector<shared_ptr<Kante>>();
	vector<shared_ptr<Knoten>> knotenOrignalGraph = vector<shared_ptr<Knoten>>();

	vector<shared_ptr<Kante>>::iterator iter = res->kantenListe.begin();
	for (; iter != res->kantenListe.end(); ++iter) {
		kantenOrignalGraph.push_back(make_shared<Kante>(*(*iter)));
	}

	vector<shared_ptr<Knoten>>::iterator iterKno = res->knotenListe.begin();
	for (; iterKno != res->knotenListe.end(); ++iterKno) {
		knotenOrignalGraph.push_back(make_shared<Knoten>(*(*iterKno)));
	}

	res->kantenListe.clear();
	res->knotenListe.clear();

	for (int i = 0; i < knotenOrignalGraph.size(); i++) {
		vector<shared_ptr<Knoten>> nachbarn = vector<shared_ptr<Knoten>>();
		vector<shared_ptr<Kante>> anliegend = vector<shared_ptr<Kante>>();
		res->knotenListe.push_back(make_shared<Knoten>(i, false, nachbarn, anliegend));
		res->knotenListe.back()->setBalance(knotenOrignalGraph[i]->getBalance());
		res->knotenListe.back()->setAktuelleBalance(knotenOrignalGraph[i]->getAktuelleBalance());
	}

	vector<shared_ptr<Kante>>::iterator iterKanten = kantenOrignalGraph.begin();
	for (; iterKanten != kantenOrignalGraph.end(); ++iterKanten) {

		shared_ptr<Kante> vor = make_shared<Kante>((*iterKanten)->getLinks(), (*iterKanten)->getRechts(), 1, (*iterKanten)->getConstGewicht(),
			((*iterKanten)->getKapazität() - (*iterKanten)->getFlusswert()), 0, false);

		shared_ptr<Kante> rueck = make_shared<Kante>((*iterKanten)->getRechts(), (*iterKanten)->getLinks(), 1, (-1 * (*iterKanten)->getConstGewicht()),
			((*iterKanten)->getFlusswert()), 0, true);

		vor->setResidualKante(rueck);
		rueck->setResidualKante(vor);

		res->knotenListe[rueck->getLinks()->getKnotenNummer()]->anliegendeKanten.push_back(rueck);
		res->knotenListe[rueck->getLinks()->getKnotenNummer()]->nachbarn.push_back(res->knotenListe[rueck->getRechts()->getKnotenNummer()]);
		res->kantenListe.push_back(rueck);

		res->knotenListe[vor->getLinks()->getKnotenNummer()]->anliegendeKanten.push_back(vor);
		res->knotenListe[vor->getLinks()->getKnotenNummer()]->nachbarn.push_back(res->knotenListe[vor->getRechts()->getKnotenNummer()]);
		res->kantenListe.push_back(vor);

	}
	return res;
}

vector<shared_ptr<Kante>> Graph::fordFulkerson(int s, int t, double &flusswert)
{
	shared_ptr<Graph> residualGraph = getResidualgraphFF();
	flusswert = 0.0;
	while (true) {
		double cost;
		deque<shared_ptr<Kante>> weg = residualGraph->bfs(residualGraph, s, t);
		if (weg.empty()) {
			break;
		}
		
		double max = INFINITY;
		for (int i=0; i < weg.size(); i++) {
			if (max > weg[i]->getKapazität()) {
				max = weg[i]->getKapazität();
			}
		}

		
		for (int i = 0; i < weg.size(); i++) {
			if (weg[i]->getResidualNatur() == false) {
				double wert = weg[i]->getKapazität() - max;
				weg[i]->setKapazität(wert);
				shared_ptr<Kante> res = weg[i]->getResidualKante();
				wert = res->getKapazität() + max;
				res->setKapazität(wert);
			}
			else {
				double wert = weg[i]->getKapazität() - max;
				weg[i]->setKapazität(wert);
				shared_ptr<Kante> orig = weg[i]->getResidualKante();
				wert = orig->getKapazität() + max;
				orig->setKapazität(wert);
			}
		}
		
		flusswert += max;
	}

	vector<shared_ptr<Kante>> fluss = vector<shared_ptr<Kante>>();
	vector<shared_ptr<Kante>>::iterator iterKanten = residualGraph->kantenListe.begin();
	for (; iterKanten != residualGraph->kantenListe.end(); ++iterKanten) {
		if ((*iterKanten)->getResidualNatur() == true) {
			(*iterKanten)->getResidualKante()->setFlusswert((*iterKanten)->getKapazität());
			(*iterKanten)->getResidualKante()->setKapazität((*iterKanten)->getKapazität() + (*iterKanten)->getResidualKante()->getKapazität());
			(*iterKanten)->setKapazität(0);
			fluss.push_back((*iterKanten)->getResidualKante());
		}
	}

	vector<shared_ptr<Kante>>::iterator iterFlussKanten = fluss.begin();
	vector<shared_ptr<Kante>>::iterator iterGKanten = this->kantenListe.begin();
	for (; iterFlussKanten != fluss.end(); ++iterFlussKanten) {
		iterGKanten = this->kantenListe.begin();
		for (; iterGKanten != this->kantenListe.end(); ++iterGKanten) {
			if ((*iterGKanten)->getLinks()->getKnotenNummer() == (*iterFlussKanten)->getLinks()->getKnotenNummer()
				&& (*iterGKanten)->getRechts()->getKnotenNummer() == (*iterFlussKanten)->getRechts()->getKnotenNummer()) {
				(*iterGKanten)->setFlusswert((*iterFlussKanten)->getFlusswert());
			}
		}
	}

	iterGKanten = this->kantenListe.begin();
	for (; iterGKanten != this->kantenListe.end(); ++iterGKanten) {
		(*iterGKanten)->setResidualKante(nullptr);
	}
	return fluss;
}

shared_ptr<Graph> Graph::getResidualgraph()
{
	shared_ptr<Graph> res = make_unique<Graph>(*this);
	vector<shared_ptr<Kante>> kantenOrignalGraph = vector<shared_ptr<Kante>>();
	vector<shared_ptr<Knoten>> knotenOrignalGraph = vector<shared_ptr<Knoten>>();

	vector<shared_ptr<Kante>>::iterator iter = res->kantenListe.begin();
	for (; iter != res->kantenListe.end(); ++iter) {
		kantenOrignalGraph.push_back(make_shared<Kante>(*(*iter)));
	}

	vector<shared_ptr<Knoten>>::iterator iterKno = res->knotenListe.begin();
	for (; iterKno != res->knotenListe.end(); ++iterKno) {
		knotenOrignalGraph.push_back(make_shared<Knoten>(*(*iterKno)));
	}

	res->kantenListe.clear();
	res->knotenListe.clear();

	for (int i = 0; i < knotenOrignalGraph.size(); i++) {
		vector<shared_ptr<Knoten>> nachbarn = vector<shared_ptr<Knoten>>();
		vector<shared_ptr<Kante>> anliegend = vector<shared_ptr<Kante>>();
		res->knotenListe.push_back(make_shared<Knoten>(i, false, nachbarn, anliegend));
		res->knotenListe.back()->setBalance(knotenOrignalGraph[i]->getBalance());
		res->knotenListe.back()->setAktuelleBalance(knotenOrignalGraph[i]->getAktuelleBalance());
	}

	vector<shared_ptr<Kante>>::iterator iterKanten = kantenOrignalGraph.begin();
	for (; iterKanten != kantenOrignalGraph.end(); ++iterKanten) {

		shared_ptr<Kante> vor = make_shared<Kante>((*iterKanten)->getLinks(), (*iterKanten)->getRechts(), 1, (*iterKanten)->getConstGewicht(),
			((*iterKanten)->getKapazität() - (*iterKanten)->getFlusswert()), 0, false);

		shared_ptr<Kante> rueck = make_shared<Kante>((*iterKanten)->getRechts(), (*iterKanten)->getLinks(), 1, (-1*(*iterKanten)->getConstGewicht()),
			((*iterKanten)->getFlusswert()), 0, true);

		if ((*iterKanten)->getFlusswert() == (*iterKanten)->getKapazität()) {
			res->knotenListe[rueck->getLinks()->getKnotenNummer()]->anliegendeKanten.push_back(rueck);
			res->knotenListe[rueck->getLinks()->getKnotenNummer()]->nachbarn.push_back(res->knotenListe[rueck->getRechts()->getKnotenNummer()]);
			res->kantenListe.push_back(rueck);
		}
		else if ((*iterKanten)->getFlusswert() == 0) {
			res->knotenListe[vor->getLinks()->getKnotenNummer()]->anliegendeKanten.push_back(vor);
			res->knotenListe[vor->getLinks()->getKnotenNummer()]->nachbarn.push_back(res->knotenListe[vor->getRechts()->getKnotenNummer()]);
			res->kantenListe.push_back(vor);
		}
		else {
			vor->setResidualKante(rueck);
			rueck->setResidualKante(vor);

			res->knotenListe[rueck->getLinks()->getKnotenNummer()]->anliegendeKanten.push_back(rueck);
			res->knotenListe[rueck->getLinks()->getKnotenNummer()]->nachbarn.push_back(res->knotenListe[rueck->getRechts()->getKnotenNummer()]);
			res->kantenListe.push_back(rueck);
			
			res->knotenListe[vor->getLinks()->getKnotenNummer()]->anliegendeKanten.push_back(vor);
			res->knotenListe[vor->getLinks()->getKnotenNummer()]->nachbarn.push_back(res->knotenListe[vor->getRechts()->getKnotenNummer()]);
			res->kantenListe.push_back(vor);
		}
	}
	return res;
}

vector<shared_ptr<Kante>> Graph::CycleCancelingCMF(double &kosten)
{
	double k;
	kosten = 0.0;

	//einführen super quelle und senke für ford fulkerson
	int superQ = this->knotenListe.size();
	int superS = this->knotenListe.size()+1;
	vector<shared_ptr<Knoten>> superQNachbarn = vector<shared_ptr<Knoten>>();
	vector<shared_ptr<Kante>> superQAnliegend = vector<shared_ptr<Kante>>();

	vector<shared_ptr<Knoten>> superSNachbarn = vector<shared_ptr<Knoten>>();
	vector<shared_ptr<Kante>> superSAnliegend = vector<shared_ptr<Kante>>();

	this->knotenListe.push_back(make_shared<Knoten>(superQ, false, superQNachbarn, superQAnliegend));
	this->knotenListe.push_back(make_shared<Knoten>(superS, false, superSNachbarn, superSAnliegend));

	vector<shared_ptr<Knoten>>::iterator iterKnoten = this->knotenListe.begin();
	for (; iterKnoten != this->knotenListe.end(); ++iterKnoten) {
		if ((*iterKnoten)->getBalance() > 0) {
			superQNachbarn.push_back(shared_ptr<Knoten>((*iterKnoten)));
			shared_ptr<Kante> k = make_shared<Kante>(knotenListe[superQ], knotenListe[(*iterKnoten)->getKnotenNummer()], 1, 0, (*iterKnoten)->getBalance(), 0, false);
			superQAnliegend.push_back(k);
			this->kantenListe.push_back(k);
		}
		else if ((*iterKnoten)->getBalance() < 0) {
			superSNachbarn.push_back(shared_ptr<Knoten>((*iterKnoten)));
			shared_ptr<Kante> k = make_shared<Kante>(knotenListe[(*iterKnoten)->getKnotenNummer()], knotenListe[superS], 1, 0, (-1* (*iterKnoten)->getBalance()), 0, false);
			superSAnliegend.push_back(k);
			this->kantenListe.push_back(k);
		}
	}

	fordFulkerson(superQ, superS, k);
	
	//prüfen ob gültiger b-Fluss
	vector<shared_ptr<Kante>>::iterator iterSuperQ = knotenListe[superQ]->anliegendeKanten.begin();
	for (; iterSuperQ != knotenListe[superQ]->anliegendeKanten.end(); ++iterSuperQ) {
		if ((*iterSuperQ)->getFlusswert() != (*iterSuperQ)->getKapazität()) {
			kosten = INFINITY;
			return vector<shared_ptr<Kante>>();
		}
	}

	vector<shared_ptr<Kante>>::iterator iterSuperS = knotenListe[superS]->anliegendeKanten.begin();
	for (; iterSuperS != knotenListe[superS]->anliegendeKanten.end(); ++iterSuperS) {
		if ((*iterSuperS)->getFlusswert() != (*iterSuperS)->getKapazität()) {
			kosten = INFINITY;
			return vector<shared_ptr<Kante>>();
		}
	}
	
	//entfernen super quelle und senke
	vector<shared_ptr<Kante>>::iterator iterKanten = kantenListe.begin();
	for (; iterKanten != kantenListe.end();) {
		if ((*iterKanten)->getLinks()->getKnotenNummer() == superQ || (*iterKanten)->getRechts()->getKnotenNummer() == superS) {
			iterKanten=kantenListe.erase(iterKanten);
		}
		else
		{
			++iterKanten;
		}
	}

	knotenListe.pop_back();
	knotenListe.pop_back();

	vector<shared_ptr<KWBNode>> cycle;
	do {
		shared_ptr<Graph> res = getResidualgraph();

		//funktioniert so nicht
		bool *visited = new bool[this->knotenListe.size()];
		for (int i = 0; i < knotenListe.size(); i++) {
			visited[i] = false;
		}

		for (int i = 0; i < knotenListe.size(); i++) {
			cycle = res->MooreBellmanFord(i, true);
			if (!cycle.empty())
				break;
			else {
				for (int j = 0; j < cycle.size(); j++) {
					visited[cycle[j]->knotenNr] = true;
				}
				for (int j = 0; j < cycle.size(); j++) {
					if (visited[cycle[j]->knotenNr] == false) {
						i = cycle[j]->knotenNr - 1;
					}
				}
			}
		}

		vector<shared_ptr<Kante>> cycleKanten = vector<shared_ptr<Kante>>();
		for (int i = 0; i < cycle.size(); i++) {
			cycleKanten.push_back(res->knotenListe[cycle[i]->vorgaenger->knotenNr]->getGuenstigsteKantezuKnoten(cycle[i]->knotenNr));
		}

		double gamma = INFINITY;
		for (int i = 0; i < cycleKanten.size(); i++) {
			if (gamma > cycleKanten[i]->getKapazität()) {
				gamma = cycleKanten[i]->getKapazität();
			}
		}

		vector<shared_ptr<Kante>>::iterator iterCycleKanten = cycleKanten.begin();
		for (; iterCycleKanten != cycleKanten.end(); ++iterCycleKanten) {
			if ((*iterCycleKanten)->getResidualNatur()) {
				shared_ptr<Kante> k = this->knotenListe[(*iterCycleKanten)->getRechts()->getKnotenNummer()]->getGuenstigsteKantezuKnoten((*iterCycleKanten)->getLinks()->getKnotenNummer());
				k->setFlusswert((k->getFlusswert() - gamma));
			}
			else {
				shared_ptr<Kante> k = this->knotenListe[(*iterCycleKanten)->getLinks()->getKnotenNummer()]->getGuenstigsteKantezuKnoten((*iterCycleKanten)->getRechts()->getKnotenNummer());
				k->setFlusswert((k->getFlusswert() + gamma));
			}
		}
	} while (!cycle.empty());


	vector<shared_ptr<Kante>> fluss = vector<shared_ptr<Kante>>();
	iterKanten = this->kantenListe.begin();
	for (; iterKanten != kantenListe.end(); ++iterKanten) {
		if ((*iterKanten)->getFlusswert() > 0) {
			kosten += ((*iterKanten)->getFlusswert()*(*iterKanten)->getGewicht());
			fluss.push_back((*iterKanten));
		}
	}
	cout << kosten << endl;
	return fluss;
}

vector<shared_ptr<Kante>> Graph::SuccesivShortestPathCMF(double & kosten)
{
	//negative Kanten belasten
	vector<shared_ptr<Kante>>::iterator iterKanten = kantenListe.begin();
	for (; iterKanten != kantenListe.end(); ++iterKanten) {
		if ((*iterKanten)->getGewicht() < 0) {
			(*iterKanten)->setFlusswert((*iterKanten)->getKapazität());
		}
	}

	//aktuelle Balancen berechenen
	vector<shared_ptr<Knoten>> pseudoQuelle = vector<shared_ptr<Knoten>>();
	vector<shared_ptr<Knoten>> pseudoSenken = vector<shared_ptr<Knoten>>();
	for (int i = 0; i < knotenListe.size(); i++) {
		double eingehend = 0.0;
		double ausgehend = 0.0;
		vector<shared_ptr<Kante>>::iterator iterKantenListe = kantenListe.begin();
		for (; iterKantenListe != kantenListe.end(); ++iterKantenListe) {
			if ((*iterKantenListe)->getLinks()->getKnotenNummer()==i) {
				ausgehend+=(*iterKantenListe)->getFlusswert();
			}
			else if ((*iterKantenListe)->getRechts()->getKnotenNummer() == i) {
				eingehend+= (*iterKantenListe)->getFlusswert();
			}
		}

		knotenListe[i]->setAktuelleBalance(ausgehend - eingehend);

		if (knotenListe[i]->getBalance() - knotenListe[i]->getAktuelleBalance() > 0) {
			pseudoQuelle.push_back(knotenListe[i]);
		}
		else if (knotenListe[i]->getBalance() - knotenListe[i]->getAktuelleBalance() < 0) {
			pseudoSenken.push_back(knotenListe[i]);
		}
	}

	while (!pseudoQuelle.empty() || !pseudoSenken.empty())
	{
		if (pseudoQuelle.empty()) {
			cout << "Es sind nur noch Pseudo-Senken verfügbar!" << endl;
			kosten = INFINITY;
			return vector<shared_ptr<Kante>>();
		}
		shared_ptr<Graph> res = getResidualgraph();
		shared_ptr<Knoten> s = pseudoQuelle[pseudoQuelle.size() - 1];
		shared_ptr<Knoten> t = nullptr;

		int *parent = new int[knotenListe.size()];
		vector<shared_ptr<Knoten>>::iterator iterPseudoSenken = pseudoSenken.begin();
		for (; iterPseudoSenken != pseudoSenken.end(); ++iterPseudoSenken) {
			if (res->bfs(res, s->getKnotenNummer(), (*iterPseudoSenken)->getKnotenNummer(), parent) == true) {
				t = (*iterPseudoSenken);
				break;
			}
		}

		if (t == nullptr) {
			cout << "Zu einer Pseudo-Quelle konnte keine Pseudo-Senke gefunden werden!" << endl;
			kosten = INFINITY;
			return vector<shared_ptr<Kante>>();
		}

		double cost;
		deque<shared_ptr<Kante>> p = res->MooreBellmanFordSTP(s->getKnotenNummer(), t->getKnotenNummer(), cost);
		deque<shared_ptr<Kante>>::iterator iterP = p.begin();

		double gamma = INFINITY;
		for (; iterP != p.end(); ++iterP) {
			if (gamma > (*iterP)->getKapazität()) {
				gamma = (*iterP)->getKapazität();
			}
		}

		if (gamma > (s->getBalance() - s->getAktuelleBalance())) {
			gamma = s->getBalance() - s->getAktuelleBalance();
		}

		if (gamma > (t->getAktuelleBalance() - t->getBalance())) {
			gamma = t->getAktuelleBalance() - t->getBalance();
		}

		iterP= p.begin();
		for (; iterP != p.end(); ++iterP) {
			if ((*iterP)->getResidualNatur()) {
				shared_ptr<Kante> k = this->knotenListe[(*iterP)->getRechts()->getKnotenNummer()]->getGuenstigsteKantezuKnoten((*iterP)->getLinks()->getKnotenNummer());
				k->setFlusswert((k->getFlusswert() - gamma));
			}
			else {
				shared_ptr<Kante> k = this->knotenListe[(*iterP)->getLinks()->getKnotenNummer()]->getGuenstigsteKantezuKnoten((*iterP)->getRechts()->getKnotenNummer());
				k->setFlusswert((k->getFlusswert() + gamma));
			}
		}
		
		s->setAktuelleBalance(s->getAktuelleBalance() + gamma);
		t->setAktuelleBalance(t->getAktuelleBalance() - gamma);
		if (s->getAktuelleBalance() == s->getBalance()) {
			pseudoQuelle.pop_back();
		}
		if (t->getAktuelleBalance() == t->getBalance()) {
			iterPseudoSenken = pseudoSenken.erase(iterPseudoSenken);
		}
	}
		
	vector<shared_ptr<Kante>> fluss = vector<shared_ptr<Kante>>();
	iterKanten = this->kantenListe.begin();
	for (; iterKanten != kantenListe.end(); ++iterKanten) {
		if ((*iterKanten)->getFlusswert() > 0) {
			kosten += ((*iterKanten)->getFlusswert()*(*iterKanten)->getGewicht());
			fluss.push_back((*iterKanten));
		}
	}
	cout << kosten << endl;
	return fluss;
}


shared_ptr<Graph> Graph::copyGraph()
{
	shared_ptr<Graph> g = make_shared<Graph>(this->gerichtet, this->gewichtet);
	g->file = this->file;
	g->gerichtet = this->gerichtet;
	g->gewichtet = this->gewichtet;

	for (int i = 0; i < this->knotenListe.size(); i++) {
		vector<shared_ptr<Knoten>> nachbarn = vector<shared_ptr<Knoten>>();
		vector<shared_ptr<Kante>> anliegend = vector<shared_ptr<Kante>>();
		g->knotenListe.push_back(make_shared<Knoten>(i, false, nachbarn, anliegend));
	}

	for (int i = 0; i < this->kantenListe.size(); i++) {
		g->kantenListe.push_back(make_shared<Kante>(g->knotenListe.at(this->kantenListe[i]->getLinks()->getKnotenNummer()),
			g->knotenListe.at(this->kantenListe[i]->getRechts()->getKnotenNummer()),
			this->kantenListe[i]->getRichtung(), this->kantenListe[i]->getGewicht(),
			this->kantenListe[i]->getKapazität(), this->kantenListe[i]->getFlusswert(),
			this->kantenListe[i]->getResidualNatur()));

		if (this->kantenListe[i]->getRichtung() == 0) {
			g->knotenListe[this->kantenListe[i]->getLinks()->getKnotenNummer()]->nachbarn.push_back(
				shared_ptr<Knoten>(g->knotenListe[this->kantenListe[i]->getRechts()->getKnotenNummer()])
			);
			int z = this->kantenListe[i]->getLinks()->getKnotenNummer();
			g->knotenListe[z]->anliegendeKanten.push_back(
				shared_ptr<Kante>(g->kantenListe[g->kantenListe.size() - 1])
			);

			g->knotenListe[this->kantenListe[i]->getRechts()->getKnotenNummer()]->nachbarn.push_back(
				shared_ptr<Knoten>(g->knotenListe[this->kantenListe[i]->getLinks()->getKnotenNummer()])
			);
			g->knotenListe[this->kantenListe[i]->getRechts()->getKnotenNummer()]->anliegendeKanten.push_back(
				shared_ptr<Kante>(g->kantenListe[g->kantenListe.size() - 1])
			);
		}
		else {
			g->knotenListe[this->kantenListe[i]->getLinks()->getKnotenNummer()]->nachbarn.push_back(
				shared_ptr<Knoten>(g->knotenListe[this->kantenListe[i]->getRechts()->getKnotenNummer()])
			);
			g->knotenListe[this->kantenListe[i]->getLinks()->getKnotenNummer()]->anliegendeKanten.push_back(
				shared_ptr<Kante>(g->kantenListe[g->kantenListe.size() - 1])
			);
		}
	}
	return g;
}

vector<shared_ptr<Kante>> Graph::MaxMatching(int &counter)
{
	counter = 0;
	ifstream is(this->file);
	int anzKnoten, mengenGroeße;
	is >> anzKnoten; is >> mengenGroeße;
	shared_ptr<Graph> copyG = copyGraph();

	bool *mengeA = new bool[knotenListe.size()];
	bool *mengeB = new bool[knotenListe.size()];

	for (int i = 0; i < mengenGroeße; i++) {
		mengeA[i] = true;
		mengeB[i] = false;
	}
	for (int i = mengenGroeße; i < knotenListe.size(); i++) {
		mengeA[i] = false;
		mengeB[i] = true;
	}

	//Graph richten
	/*vector<shared_ptr<Knoten>>::iterator knotenIter = copyG->knotenListe.begin();
	for (; knotenIter != copyG->knotenListe.end(); ++knotenIter) {
		(*knotenIter)->anliegendeKanten = vector<shared_ptr<Kante>>();
		(*knotenIter)->nachbarn = vector<shared_ptr<Knoten>>();
	}
	copyG->gerichtet = true;
	vector<shared_ptr<Kante>>::iterator kantenIter = copyG->kantenListe.begin();
	for (; kantenIter != copyG->kantenListe.end(); ++kantenIter) {
		(*kantenIter)->setRichtung(1);
		(*kantenIter)->setKapazität(1);

		if(mengeB[(*kantenIter)->getLinks()->getKnotenNummer()]==true){
			shared_ptr<Knoten> tmp = shared_ptr<Knoten>((*kantenIter)->getLinks());
			(*kantenIter)->setLinks((*kantenIter)->getRechts());
			(*kantenIter)->setRechts(tmp);
		}

		(*kantenIter)->getLinks()->nachbarn.push_back(shared_ptr<Knoten>((*kantenIter)->getRechts()));
		(*kantenIter)->getLinks()->anliegendeKanten.push_back(shared_ptr<Kante>((*kantenIter)));
	}*/

	//Super Quelle
	int numSuperQ = copyG->knotenListe.size();
	int numSuperS = copyG->knotenListe.size()+1;

	vector<shared_ptr<Knoten>> superQNachbar = vector<shared_ptr<Knoten>>();
	vector<shared_ptr<Kante>> superQAnliegend = vector<shared_ptr<Kante>>();

	vector<shared_ptr<Knoten>> superSNachbar = vector<shared_ptr<Knoten>>();
	vector<shared_ptr<Kante>> superSAnliegend = vector<shared_ptr<Kante>>();

	shared_ptr<Knoten> superQ = make_shared<Knoten>(numSuperQ, false, superQNachbar, superQAnliegend);
	shared_ptr<Knoten> superS = make_shared<Knoten>(numSuperS, false, superSNachbar, superSAnliegend);

	int origKnotenSize = copyG->knotenListe.size();
	copyG->knotenListe.push_back(superQ);
	copyG->knotenListe.push_back(superS);
	for (int i = 0; i < mengenGroeße; i++) {
		shared_ptr<Kante> k = make_shared<Kante>(copyG->knotenListe[numSuperQ], copyG->knotenListe[i],
												1,0,1,0,false);
		copyG->kantenListe.push_back(shared_ptr<Kante>(k));
		copyG->knotenListe[numSuperQ]->anliegendeKanten.push_back(shared_ptr<Kante>(k));
		copyG->knotenListe[numSuperQ]->nachbarn.push_back(shared_ptr<Knoten>(copyG->knotenListe[i]));
	}

	for (int i = mengenGroeße; i < origKnotenSize; i++) {
		shared_ptr<Kante> k = make_shared<Kante>(copyG->knotenListe[i], copyG->knotenListe[numSuperS],
			1, 0, 1, 0, false);
		copyG->kantenListe.push_back(shared_ptr<Kante>(k));
		copyG->knotenListe[i]->anliegendeKanten.push_back(shared_ptr<Kante>(k));
		copyG->knotenListe[i]->nachbarn.push_back(shared_ptr<Knoten>(copyG->knotenListe[numSuperS]));
	}

	double c;
	vector<shared_ptr<Kante>> kanten = copyG->fordFulkerson(numSuperQ, numSuperS, c);
	
	vector<shared_ptr<Kante>> matchingKanten = vector<shared_ptr<Kante>>();
	vector<shared_ptr<Kante>>::iterator iterFFKanten = kanten.begin();
	for (; iterFFKanten != kanten.end(); ++iterFFKanten) {
		if ((*iterFFKanten)->getLinks()->getKnotenNummer() == numSuperQ) {
			continue;
		}
		if ((*iterFFKanten)->getRechts()->getKnotenNummer() == numSuperS) {
			continue;
		}
		vector<shared_ptr<Kante>>::iterator iterOrigKanten = this->kantenListe.begin();
		for (; iterOrigKanten != this->kantenListe.end(); ++iterOrigKanten) {
			if ((*iterFFKanten)->getLinks()->getKnotenNummer() == (*iterOrigKanten)->getLinks()->getKnotenNummer()) {
				counter++;
				matchingKanten.push_back(shared_ptr<Kante>((*iterOrigKanten)));
				break;
			}
			else if ((*iterFFKanten)->getRechts()->getKnotenNummer() == (*iterOrigKanten)->getLinks()->getKnotenNummer()) {
				counter++;
				matchingKanten.push_back(shared_ptr<Kante>((*iterOrigKanten)));
				break;
			}
		}
	}

	return matchingKanten;
}

