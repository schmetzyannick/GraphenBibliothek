#pragma once
#include "Kante.h"
#include <vector>
#include <iostream>
#include <string>
#include "DisjointedSetKnoten.h"

using namespace std;

class Graph {
private:
	bool gerichtet;
	bool gewichtet;
	vector<Kante> kantenListe;
	vector<Knoten> knotenListe;

public:
	Graph(bool, bool);
	Graph(bool, bool, vector<Kante>, vector<Knoten>);

	bool getGerichtet();
	bool getGewichtet();
	vector<Kante> getKantenListe();
	vector<Knoten> getKnotenListe();

	void setGerichtet(bool);
	void setGewichtet(bool);
	void setKantenListe(vector<Kante>);
	void setKnotenListe(vector<Knoten>);

	void GraphFromTextfile();

	inline Knoten ersterUnmarkierter();
	inline void Breitensuche(int start);
	int Zusammenhangskomponenten();

	shared_ptr<vector<Kante>> KruskalMST();
	void sortKantenListe();
	void mergeSort(int l, int r);
	void merge(int links, int mitte, int rechts);
};
