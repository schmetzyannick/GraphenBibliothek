#include "Knoten.h"
#include "Kante.h"

Knoten::Knoten()
{
	this->knotenNummer = -1;
	this->markBreitensuche = false;
	this->nachbarn = make_shared<vector<Knoten>>();
	this->anliegendeKanten = make_shared<vector<Kante>>();
}

Knoten::Knoten(int nr, bool marked, shared_ptr<vector<Knoten>> nachbarn, shared_ptr<vector<Kante>> anliegendeKanten)
{
	this->knotenNummer = nr;
	this->markBreitensuche = marked;
	this->nachbarn = nachbarn;
	this->anliegendeKanten = anliegendeKanten;
}

int Knoten::getKnotenNummer()
{
	return this->knotenNummer;
}

bool Knoten::isMarked()
{
	return this->markBreitensuche;
}

void Knoten::setKnotenNummer(int nr)
{
	this->knotenNummer = nr;
}

void Knoten::markKnoten()
{
	this->markBreitensuche = true;
}
