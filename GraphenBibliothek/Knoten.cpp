#include "Knoten.h"

Knoten::Knoten(int nr)
{
	this->knotenNummer = nr;
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
