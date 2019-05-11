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

//nicht genutzt, kann für alternative B&B impl. genutzt werden
shared_ptr<vector<vector<double>>> Graph::buildAdjaMatrix()
{
	shared_ptr<vector<vector<double>>> adjaMatrix = make_shared<vector<vector<double>>>();

	if (!this->gewichtet) {
		if (!this->gerichtet) {//ungewichtet ungerichtet
			for (int i = 0; i < this->knotenListe.size(); i++) {
				Knoten k = knotenListe[i];
				vector<double> nachbarn = vector<double>();

				for (int j = 0; j < this->knotenListe.size(); j++) {
					if (j == i)
						nachbarn.push_back(INFINITY);
					else
						nachbarn.push_back(0);
				}

				vector<Kante>::iterator iter;
				for (iter=k.anliegendeKanten->begin();
					iter!=k.anliegendeKanten->end(); ++iter) {

					if (iter->getLinks().getKnotenNummer() == k.getKnotenNummer()) {
						nachbarn[iter->getRechts().getKnotenNummer()] = 1;
					}
					else if (iter->getRechts().getKnotenNummer() == k.getKnotenNummer()) {
						nachbarn[iter->getLinks().getKnotenNummer()] = 1;
					}
				}
				adjaMatrix->push_back(nachbarn);
			}
		}
		else {//ungewichtet gerichtet
			for (int i = 0; i < this->knotenListe.size(); i++) {
				Knoten k = knotenListe[i];
				vector<double> nachbarn = vector<double>();

				for (int j = 0; j < this->knotenListe.size(); j++) {
					if (j == i)
						nachbarn.push_back(INFINITY);
					else
						nachbarn.push_back(0);
				}

				vector<Kante>::iterator iter;
				for (iter = k.anliegendeKanten->begin();
					iter != k.anliegendeKanten->end(); ++iter) {

					if (iter->getLinks().getKnotenNummer() == k.getKnotenNummer()) {
						nachbarn[iter->getRechts().getKnotenNummer()] = 1;
					}
				}
				adjaMatrix->push_back(nachbarn);
			}
		}
	}
	else {
		if (!this->gerichtet) {//gewichtet ungerichtet
			for (int i = 0; i < this->knotenListe.size(); i++) {
				Knoten k = knotenListe[i];
				vector<double> nachbarn = vector<double>();

				for (int j = 0; j < this->knotenListe.size(); j++) {
					if (j == i)
						nachbarn.push_back(INFINITY);
					else
						nachbarn.push_back(0);
				}

				vector<Kante>::iterator iter;
				for (iter = k.anliegendeKanten->begin();
					iter != k.anliegendeKanten->end(); ++iter) {

					if (iter->getLinks().getKnotenNummer() == k.getKnotenNummer()) {
						nachbarn[iter->getRechts().getKnotenNummer()] = iter->getGewicht();
					}
					else if (iter->getRechts().getKnotenNummer() == k.getKnotenNummer()) {
						nachbarn[iter->getLinks().getKnotenNummer()] = iter->getGewicht();
					}
				}
				adjaMatrix->push_back(nachbarn);
			}
		}
		else {//gewichtet gerichtet
			for (int i = 0; i < this->knotenListe.size(); i++) {
				Knoten k = knotenListe[i];
				vector<double> nachbarn = vector<double>();

				for (int j = 0; j < this->knotenListe.size(); j++) {
					if (j == i)
						nachbarn.push_back(INFINITY);
					else
						nachbarn.push_back(0);
				}

				vector<Kante>::iterator iter;
				for (iter = k.anliegendeKanten->begin();
					iter != k.anliegendeKanten->end(); ++iter) {

					if (iter->getLinks().getKnotenNummer() == k.getKnotenNummer()) {
						nachbarn[iter->getRechts().getKnotenNummer()] = iter->getGewicht();
					}
				}
				adjaMatrix->push_back(nachbarn);
			}
		}
	}

	return adjaMatrix;
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
	for (iterator = kantenListe.begin(); (iterator != kantenListe.end())
		|| mst->size() != this->knotenListe.size()-1; ++iterator) {

		int links = iterator->getLinks().getKnotenNummer();
		int rechts = iterator->getRechts().getKnotenNummer();

		int set_links = dsKnoten.find(links);
		int set_rechts = dsKnoten.find(rechts);

		if (set_links != set_rechts) {
			mst->push_back(*iterator);
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

vector<Kante> Graph::PrimMST(int start)
{
	clock_t anfang = clock();
	
	//Kanten werden automatisch nach ihrem gewicht sortiert
	priority_queue<Kante, vector<Kante>, KantenVergleichen> pq = priority_queue<Kante, vector<Kante>, KantenVergleichen>();

	//Kanten des mst
	vector<Kante> mst = vector<Kante>();

	Knoten aktuellerKnoten = knotenListe[start];

	//hält die bereits besuchten Knoten
	//Verbesserung: array mit bool stelle = Knotennummer
	set<int> besuchteKnoten = set<int>();
	besuchteKnoten.insert(aktuellerKnoten.getKnotenNummer());

	double weight = 0.0;
	bool addKanten = true;

	while (mst.size() < knotenListe.size() - 1) {
		//wurde der aktuelleKnoten geaendert und somit eine Kante zum mst hinzugefuegt?
		if (addKanten) {
			//fuege Kanten des neuen Knoten in die pq
			//Verbesserung: nur Kanten bei denen nicht beide Knoten besucht sind
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

	/*cout << "Kosten: " << weight << endl;
	clock_t ende = clock();
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
	Knoten aktuell = knotenListe[startKnoten];
	besuchteKnoten[startKnoten] = true;

	double kosten = 0.0;
	int counter = 1;

	//n-1 Kanten -> danach tour schließen
	while (counter < knotenListe.size()) {
		Kante k;
	
		shared_ptr<vector<Kante>> anliegendeKantenSorted = aktuell.getKantenlisteSortet();
		vector<Kante>::iterator iter = anliegendeKantenSorted->begin();
		//finde die guenstigste Kante zu einem noch nicht besuchten Knoten
		for (; iter != anliegendeKantenSorted->end(); ++iter) {
			k = *iter;
			if ((k.getLinks().getKnotenNummer() == aktuell.getKnotenNummer())
				&& (besuchteKnoten[k.getRechts().getKnotenNummer()] == false)) {

				tour.push_back(k);
				kosten += k.getGewicht();

				aktuell = k.getRechts();
				besuchteKnoten[k.getRechts().getKnotenNummer()] = true;

				break;
			}
			else if ((k.getRechts().getKnotenNummer() == aktuell.getKnotenNummer())
				&& (besuchteKnoten[k.getLinks().getKnotenNummer()] == false)) {

				tour.push_back(k);
				kosten += k.getGewicht();

				aktuell = k.getLinks();
				besuchteKnoten[k.getLinks().getKnotenNummer()] = true;

				break;
			}
		}
		counter++;
	}

	//schließe die tour
	try {
		Kante k = aktuell.getGuenstigsteKantezuKnoten(startKnoten);
		kosten += k.getGewicht();
		tour.push_back(k);
	}
	catch (exception e) {
		throw e;
	}

	cout << "Kosten: " << kosten << endl;
	clock_t ende = clock();
	cout << "Laufzeit: " << ((float)(ende - anfang) / CLOCKS_PER_SEC) << " Sekunden" << endl;
	return tour;
}

//nicht genutzt, kann für alternative B&B impl. genutzt werden
void Graph::ReduceMatrix(shared_ptr<vector<vector<double>>> &matrix , double &reduktionsKosten)
{
	reduktionsKosten = 0.0;
	//zeilen minimum subtrahieren
	for (int i = 0; i < matrix->size(); i++) {
		double min = INFINITY;
		//minimum finden
		for (int j = 0; j < matrix->at(i).size(); j++) {
			if (matrix->at(i).at(j) < min) {
				min = matrix->at(i).at(j);
			}
		}

		//minumum abziehen
		for (int j = 0; j < matrix->at(i).size(); j++) {
			matrix->at(i).at(j) -= min;
		}
		reduktionsKosten += min;
	}

	//spalten minimieren
	for (int i = 0; i < matrix->at(0).size(); i++) {
		double min = INFINITY;

		for (int j = 0; j < matrix->size(); j++) {
			if (matrix->at(j).at(i) < min) {
				min = matrix->at(j).at(i);
			}
		}

		//minumum abziehen
		for (int j = 0; j < matrix->at(i).size(); j++) {
			matrix->at(j).at(i) -= min;
		}
		reduktionsKosten += min;
	}
}

void Graph::BranchAndBound(Node aktuellerNode, BABTree* tree, bool bound/*=true*/)
{
	//iteriere ueber anliegende Kanten
	shared_ptr<vector<Kante>> copyAnliegend = aktuellerNode.knoten.getKantenlisteSortet();
	for (int i = 0; i < copyAnliegend->size(); i++) {

		if (copyAnliegend->at(i).getLinks().getKnotenNummer() == aktuellerNode.knoten.getKnotenNummer() &&
			aktuellerNode.besuchteKnoten->at(copyAnliegend->at(i).getRechts().getKnotenNummer()) == false) {
			//Kante zu Knoten gefunden, der noch nicht besucht wurde im aktuellen ast
			double kosten = copyAnliegend->at(i).getGewicht() + aktuellerNode.kostenBisher;
			shared_ptr<vector<bool>> copy = make_shared<vector<bool>>(*(aktuellerNode.besuchteKnoten));
			copy->at(copyAnliegend->at(i).getRechts().getKnotenNummer()) = true;

			Node n = Node(kosten, copyAnliegend->at(i).getRechts(), copy);
			n.genutzteKanten = aktuellerNode.genutzteKanten;
			n.genutzteKanten.push_back(copyAnliegend->at(i));

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
		else if (copyAnliegend->at(i).getRechts().getKnotenNummer() == aktuellerNode.knoten.getKnotenNummer() &&
			aktuellerNode.besuchteKnoten->at(copyAnliegend->at(i).getLinks().getKnotenNummer()) == false) {
			//Kante zu Knoten gefunden, der noch nicht besucht wurde im aktuellen ast
			double kosten = copyAnliegend->at(i).getGewicht() + aktuellerNode.kostenBisher;
			shared_ptr<vector<bool>> copy = make_shared<vector<bool>>(*(aktuellerNode.besuchteKnoten));
			copy->at(copyAnliegend->at(i).getLinks().getKnotenNummer()) = true;

			Node n = Node(kosten, copyAnliegend->at(i).getLinks(), copy);
			n.genutzteKanten = aktuellerNode.genutzteKanten;
			n.genutzteKanten.push_back(copyAnliegend->at(i));

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
	}

	//tour schließen
	if (aktuellerNode.nachfolger.empty()) {
		int nr = tree->root.knoten.getKnotenNummer();
		Kante k = aktuellerNode.knoten.getGuenstigsteKantezuKnoten(nr);
		aktuellerNode.genutzteKanten.push_back(k);
		aktuellerNode.kostenBisher += k.getGewicht();
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
		if (k.getLinks().getKnotenNummer() == aktuellerKnoten && besucht[k.getRechts().getKnotenNummer()] == false) {
			tspTour.push_back(k);
			mst.pop_front();

			kosten += k.getGewicht();
			besucht[k.getRechts().getKnotenNummer()] = true;
			aktuellerKnoten = k.getRechts().getKnotenNummer();
		}else if (k.getRechts().getKnotenNummer() == aktuellerKnoten && besucht[k.getLinks().getKnotenNummer()] == false) {
			tspTour.push_back(k);
			mst.pop_front();

			kosten += k.getGewicht();
			besucht[k.getLinks().getKnotenNummer()] = true;
			aktuellerKnoten = k.getLinks().getKnotenNummer();
		}
		else {//aktueller Knoten nicht in mst => abkuerzung
			if (besucht[k.getLinks().getKnotenNummer()] == false) {

				Kante kurz = knotenListe[aktuellerKnoten].getGuenstigsteKantezuKnoten(k.getLinks().getKnotenNummer());
				mst.pop_front();
				tspTour.push_back(kurz);
				kosten += kurz.getGewicht();

				besucht[k.getLinks().getKnotenNummer()] = true;
				aktuellerKnoten = k.getLinks().getKnotenNummer();

			}else if (besucht[k.getRechts().getKnotenNummer()] == false) {

				Kante kurz = knotenListe[aktuellerKnoten].getGuenstigsteKantezuKnoten(k.getRechts().getKnotenNummer());
				mst.pop_front();
				tspTour.push_back(kurz);
				kosten += kurz.getGewicht();

				besucht[k.getRechts().getKnotenNummer()] = true;
				aktuellerKnoten = k.getRechts().getKnotenNummer();
			}
		}
	}

	if (aktuellerKnoten = tspTour.back().getLinks().getKnotenNummer()) {
		Kante k = tspTour.back().getLinks().getGuenstigsteKantezuKnoten(startKnoten);
		tspTour.push_back(k);
		kosten += k.getGewicht();
	}
	else if (aktuellerKnoten = tspTour.back().getRechts().getKnotenNummer()) {
		Kante k = tspTour.back().getRechts().getGuenstigsteKantezuKnoten(startKnoten);
		tspTour.push_back(k);
		kosten += k.getGewicht();
	}

	cout << "Kosten: " << kosten << endl;
	clock_t ende = clock();
	cout << "Laufzeit: " << ((float)(ende - anfang) / CLOCKS_PER_SEC) << " Sekunden" << endl;

	//augabe:
	aktuellerKnoten = startKnoten;
	cout << startKnoten;
	vector<Kante>::iterator iterErgeb = tspTour.begin();
	for (; iterErgeb != tspTour.end(); ++iterErgeb) {
		if (iterErgeb->getLinks().getKnotenNummer() == aktuellerKnoten) {
			aktuellerKnoten = iterErgeb->getRechts().getKnotenNummer();
		}
		else {
			aktuellerKnoten = iterErgeb->getLinks().getKnotenNummer();
		}
		cout << " -> " << aktuellerKnoten;
	}
	cout << endl;
	return tspTour;
}
