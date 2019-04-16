#pragma once
#include <vector>

using namespace std;
class Knoten {
private:
	int knotenNummer;
	bool markBreitensuche;

public:
	vector<Knoten> *nachbarn;

	Knoten();
	Knoten(int, bool, vector<Knoten>*);
	~Knoten();

	int getKnotenNummer();
	bool isMarked();


	void markKnoten();
	void setKnotenNummer(int);
};