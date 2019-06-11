#include "Knoten.h"
#include "Kante.h"
#include <algorithm>

Knoten::Knoten()
{
	this->knotenNummer = -1;
	this->marked = false;
	this->nachbarn = vector<shared_ptr<Knoten>>();
	this->anliegendeKanten = vector<shared_ptr<Kante>>();
	this->aktuelleBalance = 0.0;
	this->balance = 0.0;
}

Knoten::Knoten(int nr, bool marked, vector<shared_ptr<Knoten>> nachbarn, vector<shared_ptr<Kante>> anliegendeKanten)
{
	this->knotenNummer = nr;
	this->marked = marked;
	this->nachbarn = nachbarn;
	this->anliegendeKanten = anliegendeKanten;
	this->aktuelleBalance = 0.0;
	this->balance = 0.0;
}

int Knoten::getKnotenNummer()
{
	return this->knotenNummer;
}

bool Knoten::isMarked()
{
	return this->marked;
}

double Knoten::getAktuelleBalance()
{
	return this->aktuelleBalance;
}

double Knoten::getBalance()
{
	return this->balance;
}

//zweiter meber als sortierte liste => weniger Aufwand
vector<shared_ptr<Kante>> Knoten::getKantenlisteSortet()
{
	vector<shared_ptr<Kante>> copy = vector<shared_ptr<Kante>>();
	for (int i = 0; i < anliegendeKanten.size(); i++) {
		copy.push_back(shared_ptr<Kante>(anliegendeKanten[i]));
	}
	sort(copy.begin(), copy.end(), KantenVergleichenKleinerAls());
	return copy;
}

//vector<Kante> Knoten::getKantenlisteSortetNonPtr()
//{
//	vector<Kante> copy = vector<Kante>();
//	for (int i = 0; i < anliegendeKanten->size(); i++) {
//		copy.push_back(anliegendeKanten->at(i));
//	}
//	sort(copy.begin(), copy.end(), KantenVergleichenKleinerAls());
//	return copy;
//}
//
//Kante Knoten::getGuenstigsteKante()
//{
//	shared_ptr<vector<Kante>> sorted = make_shared<vector<Kante>>(*getKantenlisteSortet());
//	return sorted->at(0);
//}
//
shared_ptr<Kante> Knoten::getGuenstigsteKantezuKnoten(int knoten)
{
	vector<shared_ptr<Kante>> sorted = getKantenlisteSortet();
	shared_ptr<Kante> k;
	vector<shared_ptr<Kante>>::iterator iter = sorted.begin();
	for (;iter != sorted.end(); ++iter) {
		if ((*iter)->getLinks()->getKnotenNummer() == knoten || (*iter)->getRechts()->getKnotenNummer() == knoten) {
			k = *iter;
			break;
		}
	}

	if (iter == sorted.end()) {
		throw exception("Keine Kante zum angegebenen Knoten!");
	}

	return k;
}
//
//Kante* Knoten::getKanteZuKnoten(int knoten)
//{
//	shared_ptr<vector<Kante>> sorted = make_shared<vector<Kante>>(*getKantenlisteSortet());
//	shared_ptr<Kante> k= nullptr;
//	vector<Kante>::iterator iter = sorted->begin();
//	for (; iter != sorted->end(); ++iter) {
//		if (iter->getLinks()->getKnotenNummer() == knoten || iter->getRechts()->getKnotenNummer() == knoten) {
//			return &(*iter);
//		}
//	}
//	return nullptr;
//}

void Knoten::setKnotenNummer(int nr)
{
	this->knotenNummer = nr;
}

void Knoten::setAktuelleBalance(double b)
{
	this->aktuelleBalance = b;
}

void Knoten::setBalance(double b)
{
	this->balance = b;
}

void Knoten::markKnoten()
{
	this->marked = true;
}
