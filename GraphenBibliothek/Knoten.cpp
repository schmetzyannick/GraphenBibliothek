#include "Knoten.h"
#include "Kante.h"
#include <algorithm>

Knoten::Knoten()
{
	this->knotenNummer = -1;
	this->marked = false;
	this->nachbarn = make_shared<vector<Knoten>>();
	this->anliegendeKanten = make_shared<vector<Kante>>();
}

Knoten::Knoten(int nr, bool marked, shared_ptr<vector<Knoten>> nachbarn, shared_ptr<vector<Kante>> anliegendeKanten)
{
	this->knotenNummer = nr;
	this->marked = marked;
	this->nachbarn = nachbarn;
	this->anliegendeKanten = anliegendeKanten;
}

int Knoten::getKnotenNummer()
{
	return this->knotenNummer;
}

bool Knoten::isMarked()
{
	return this->marked;
}

//zweiter meber als sortierte liste => weniger Aufwand
shared_ptr<vector<Kante>> Knoten::getKantenlisteSortet()
{
	shared_ptr<vector<Kante>> copyKantenListe = make_shared<vector<Kante>>(*anliegendeKanten);
	sort(copyKantenListe->begin(), copyKantenListe->end(), KantenVergleichenKleinerAls());
	return copyKantenListe;
}

vector<Kante> Knoten::getKantenlisteSortetNonPtr()
{
	vector<Kante> copy = vector<Kante>();
	for (int i = 0; i < anliegendeKanten->size(); i++) {
		copy.push_back(anliegendeKanten->at(i));
	}
	sort(copy.begin(), copy.end(), KantenVergleichenKleinerAls());
	return copy;
}

Kante Knoten::getGuenstigsteKante()
{
	shared_ptr<vector<Kante>> sorted = make_shared<vector<Kante>>(*getKantenlisteSortet());
	return sorted->at(0);
}

Kante Knoten::getGuenstigsteKantezuKnoten(int knoten)
{
	shared_ptr<vector<Kante>> sorted = make_shared<vector<Kante>>(*getKantenlisteSortet());
	Kante k;
	vector<Kante>::iterator iter = sorted->begin();
	for (;iter != sorted->end(); ++iter) {
		if (iter->getLinks().getKnotenNummer() == knoten || iter->getRechts().getKnotenNummer() == knoten) {
			k = *iter;
			break;
		}
	}

	if (iter == sorted->end()) {
		throw exception("Keine Kante zum angegebenen Knoten!");
	}

	return k;
}

shared_ptr<Kante> Knoten::getKanteZuKnoten(int knoten)
{
	shared_ptr<vector<Kante>> sorted = make_shared<vector<Kante>>(*getKantenlisteSortet());
	shared_ptr<Kante> k= nullptr;
	vector<Kante>::iterator iter = sorted->begin();
	for (; iter != sorted->end(); ++iter) {
		if (iter->getLinks().getKnotenNummer() == knoten || iter->getRechts().getKnotenNummer() == knoten) {
			shared_ptr<Kante> k = make_shared<Kante>((*iter));
			return k;
		}
	}
	return k;
}

void Knoten::setKnotenNummer(int nr)
{
	this->knotenNummer = nr;
}

void Knoten::markKnoten()
{
	this->marked = true;
}
