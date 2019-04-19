#include "Kante.h"

Kante::Kante()
{
	this->links = Knoten();
	this->rechts = Knoten();
	richtung = ungerichtet;
	this->gewicht = 0.0;
}

Kante::Kante(Knoten links, Knoten rechts, int richtung/*=0*/, double gewicht/*=0.0.*/)
{
	this->links = links;
	this->rechts = rechts;
	if (richtung >= 0 && richtung <= 2) {
		this->richtung = KantenRichtung(richtung);
	}
	else {
		this->richtung = KantenRichtung(0);
	}
	this->gewicht=gewicht;
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

double Kante::getGewicht()
{
	return this->gewicht;
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

void Kante::setGewicht(double gewicht)
{
	this->gewicht = gewicht;
}
