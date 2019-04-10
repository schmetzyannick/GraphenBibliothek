#include "Kante.h"

Kante::Kante()
{
	this->links = Knoten();
	this->rechts = Knoten();
	richtung = ungerichtet;
}

Kante::Kante(Knoten links, Knoten rechts, int richtung)
{
	this->links = links;
	this->rechts = rechts;
	if (richtung >= 0 && richtung <= 2) {
		this->richtung = KantenRichtung(richtung);
	}
	else {
		this->richtung = KantenRichtung(0);
	}
}

Knoten Kante::getLinks()
{
	return links;
}

Knoten Kante::getRechts()
{
	return rechts;
}

int Kante::getRichtung()
{
	return richtung;
}

void Kante::setLinks(Knoten l)
{
	this->links = l;
}

void Kante::setRechts(Knoten r)
{
	this->rechts = r;
}

void Kante::setRichtung(int richtung)
{
	if (richtung >= 0 && richtung <= 2) {
		this->richtung = KantenRichtung(richtung);
	}
	else {
		this->richtung = KantenRichtung(0);
	}
}
