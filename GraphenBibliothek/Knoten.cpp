#include "Knoten.h"

Knoten::Knoten()
{
	this->knotenNummer = -1;
	this->markBreitensuche = false;
	this->nachbarn = new vector<Knoten>();
}

Knoten::Knoten(int nr, bool marked, vector<Knoten> *nachbarn)
{
	this->knotenNummer = nr;
	this->markBreitensuche = marked;
	this->nachbarn = nachbarn;
}

Knoten::~Knoten()
{
	delete nachbarn;
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
