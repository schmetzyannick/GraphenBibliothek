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
	shared_ptr<vector<Knoten>> nachbarn;
	shared_ptr<vector<Kante>> anliegendeKanten;

	Knoten();
	Knoten(int, bool, shared_ptr<vector<Knoten>>, shared_ptr<vector<Kante>>);

	int getKnotenNummer();
	bool isMarked();
	shared_ptr<vector<Kante>> getKantenlisteSortet();
	Kante getGuenstigsteKante();
	Kante getGuenstigsteKantezuKnoten(int);

	void markKnoten();
	void setKnotenNummer(int);
	
};