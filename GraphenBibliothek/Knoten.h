#pragma once
#include <vector>
#include <iostream>

using namespace std;
class Knoten {
private:
	int knotenNummer;
	bool markBreitensuche;

public:
	shared_ptr<vector<Knoten>> nachbarn;

	Knoten();
	Knoten(int, bool, shared_ptr<vector<Knoten>>);

	int getKnotenNummer();
	bool isMarked();


	void markKnoten();
	void setKnotenNummer(int);
};