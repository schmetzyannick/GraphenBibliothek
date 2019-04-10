#pragma once

class Knoten {
private:
	int knotenNummer = -1;
	bool markBreitensuche = false;
public:
	Knoten() {};
	Knoten(int nr);

	int getKnotenNummer();
	bool isMarked();

	void markKnoten();
	void setKnotenNummer(int);
};