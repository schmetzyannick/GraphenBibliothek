#pragma once
#include "Kante.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Graph {
private:
	bool gerichtet;
	vector<Kante> kantenListe;
	vector<Knoten> knotenListe;

public:
	Graph(bool);
	Graph(bool, vector<Kante>, vector<Knoten>);

	bool getGerichtet();
	vector<Kante> getKantenListe();
	vector<Knoten> getKnotenListe();

	void setGerichtet(bool);
	void setKantenListe(vector<Kante>);
	void setKnotenListe(vector<Knoten>);

	void GraphFromTextfile();

	inline Knoten ersterUnmarkierter();
	inline void Breitensuche(int start);
	int Zusammenhangskomponenten();
};