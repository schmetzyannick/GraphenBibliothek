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
	shared_ptr<Knoten> links;
	shared_ptr<Knoten> rechts;
	KantenRichtung richtung;
	double gewicht;
	double flusswert;
	bool resKante;
	double obereKapazität;
	shared_ptr<Kante> residualKante;

public:
	

	Kante();
	Kante(shared_ptr<Knoten>, shared_ptr<Knoten>, int gerichtet=0, double gewichtet=0.0);
	Kante(shared_ptr<Knoten>, shared_ptr<Knoten>, int gerichtet, double gewicht, double kapa, double flussert, bool);

	shared_ptr<Knoten> getLinks();
	shared_ptr<Knoten> getRechts();
	int getRichtung();
	double getGewicht();
	double getConstGewicht() const { return this->gewicht; }
	double getKapazität();
	bool getResidualNatur();
	shared_ptr<Kante> getResidualKante();
	double getFlusswert();

	void setLinks(shared_ptr<Knoten>);
	void setRechts(shared_ptr<Knoten>);
	void setRichtung(int);
	void setGewicht(double);
	void setKapazität(double);
	void setResidualKante(shared_ptr<Kante>);
	void setFlusswert(double fluss);

	bool equals(shared_ptr<Kante>);
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
		return k->getKapazität() > k1->getKapazität();
	}
};

class KantenVergleichenKleinerAls {
public:
	int operator() (const Kante& p1, const Kante& p2)
	{
		return p1.getConstGewicht() < p2.getConstGewicht();
	}

	int operator() (const shared_ptr<Kante>& p1, const shared_ptr<Kante>& p2)
	{
		return p1->getConstGewicht() < p2->getConstGewicht();
	}
};