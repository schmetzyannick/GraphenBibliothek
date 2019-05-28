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
	double flusswert;
	bool resKante;
	double obereKapazit�t;
	shared_ptr<Kante> residualKante;

public:
	

	Kante();
	Kante(Knoten, Knoten, int gerichtet=0, double gewichtet=0.0);
	Kante(Knoten, Knoten, int gerichtet, double gewicht, double kapa, double flussert, bool);

	Knoten getLinks();
	Knoten getRechts();
	int getRichtung();
	double getGewicht();
	double getConstGewicht() const { return this->gewicht; }
	double getKapazit�t();
	bool getResidualNatur();
	shared_ptr<Kante> getResidualKante();

	void setLinks(Knoten);
	void setRechts(Knoten);
	void setRichtung(int);
	void setGewicht(double);
	void setKapazit�t(double);
	void setResidualKante(shared_ptr<Kante>);

};

class KantenVergleichen {
public:
	int operator() (const Kante& p1, const Kante& p2)
	{
		return p1.getConstGewicht() > p2.getConstGewicht();
	}
};

class KantenVergleichenKapa {
public:
	int operator() (const Kante& p1, const Kante& p2)
	{
		Kante *k1= const_cast<Kante*>(&p2);
		Kante *k = const_cast<Kante*>(&p1);
		return k->getKapazit�t() > k1->getKapazit�t();
	}
};

class KantenVergleichenKleinerAls {
public:
	int operator() (const Kante& p1, const Kante& p2)
	{
		return p1.getConstGewicht() < p2.getConstGewicht();
	}
};