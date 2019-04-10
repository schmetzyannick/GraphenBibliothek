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
	//gehört eigendlich zum Knoten
	vector<vector<Knoten>> adjaListe;
public:
	Graph(bool);
	Graph(bool, vector<Kante>, vector<Knoten>, vector<vector<Knoten>>);

	bool getGerichtet();
	vector<Kante> getKantenListe();
	vector<Knoten> getKnotenListe();
	vector<vector<Knoten>> getAdjaListe();

	void setGerichtet(bool);
	void setKantenListe(vector<Kante>);
	void setKnotenListe(vector<Knoten>);
	void setAdjaListe(vector<vector<Knoten>>);

	void GraphFromTextfile();

	inline Knoten ersterUnmarkierter();
	inline void Breitensuche(int start);
	int Zusammenhangskomponenten();
};