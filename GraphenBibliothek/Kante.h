#pragma once
#include "Knoten.h"

enum KantenRichtung
{
	ungerichtet,
	linksRechts,
	rechtsLinks,
};

class Kante {
private:
	Knoten links;
	Knoten rechts;
	KantenRichtung richtung;
	double gewicht;

public:
	Kante();
	Kante(Knoten, Knoten, int gerichtet=0, double gewichtet=0.0);

	Knoten getLinks();
	Knoten getRechts();
	int getRichtung();
	double getGewicht();
	double getConstGewicht() const { return this->gewicht; }

	void setLinks(Knoten);
	void setRechts(Knoten);
	void setRichtung(int);
	void setGewicht(double);
};

class KantenVergleichen {
public:
	int operator() (const Kante& p1, const Kante& p2)
	{
		return p1.getConstGewicht() > p2.getConstGewicht();
	}
};