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

public:
	Kante();
	Kante(Knoten, Knoten, int);

	Knoten getLinks();
	Knoten getRechts();
	int getRichtung();

	void setLinks(Knoten);
	void setRechts(Knoten);
	void setRichtung(int);
};