#include "Kante.h"

Kante::Kante()
{
	this->links = nullptr;
	this->rechts = nullptr;
	richtung = ungerichtet;
	this->gewicht = 0.0;
	this->flusswert = 0.0;
	this->obereKapazität = 0.0;
	this->resKante = false;
}

Kante::Kante(Knoten* links, Knoten* rechts, int richtung/*=0*/, double gewicht/*=0.0.*/)
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
	this->flusswert = 0.0;
	this->obereKapazität = 0.0;
	this->resKante = false;
}

Kante::Kante(Knoten* links, Knoten* rechts, int richtung, double gewicht, double kapa, double flussert, bool resKante)
{
	this->links = links;
	this->rechts = rechts;
	if (richtung >= 0 && richtung <= 2) {
		this->richtung = KantenRichtung(richtung);
	}
	else {
		this->richtung = KantenRichtung(0);
	}
	this->gewicht = gewicht;
	this->flusswert = flussert;
	this->obereKapazität = kapa;
	this->resKante = resKante;
}

Knoten* Kante::getLinks()
{
	return links;
}

Knoten* Kante::getRechts()
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

double Kante::getKapazität()
{
	return this->obereKapazität;
}

bool Kante::getResidualNatur()
{
	return this->resKante;
}

shared_ptr<Kante> Kante::getResidualKante()
{
	return this->residualKante;
}

void Kante::setLinks(Knoten* l)
{
	this->links = l;
}

void Kante::setRechts(Knoten* r)
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

void Kante::setKapazität(double kapa)
{
	this->obereKapazität = kapa;
}

void Kante::setResidualKante(shared_ptr<Kante> k)
{
	this->residualKante = k;
}
