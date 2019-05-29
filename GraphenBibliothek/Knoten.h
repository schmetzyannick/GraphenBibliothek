#pragma once
#include <vector>
#include <iostream>

class Kante;

using namespace std;
class Knoten {
private:
	int knotenNummer;
	bool marked;

public:
	vector<shared_ptr<Knoten>> nachbarn;
	vector<shared_ptr<Kante>> anliegendeKanten;

	Knoten();
	Knoten(int, bool, vector<shared_ptr<Knoten>>, vector<shared_ptr<Kante>>);

	int getKnotenNummer();
	bool isMarked();
	vector<shared_ptr<Kante>> getKantenlisteSortet();
	vector<Kante> getKantenlisteSortetNonPtr();
	Kante getGuenstigsteKante();
	shared_ptr<Kante> getGuenstigsteKantezuKnoten(int);
	Kante* getKanteZuKnoten(int);

	void markKnoten();
	void setKnotenNummer(int);
	
};