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

	//getter
	bool getGerichtet();
	bool getGewichtet();
	vector<Kante> getKantenListe();
	vector<Knoten> getKnotenListe();

	//setter
	void setGerichtet(bool);
	void setGewichtet(bool);
	void setKantenListe(vector<Kante>);
	void setKnotenListe(vector<Knoten>);

	//einlesen
	void GraphFromTextfile();

	//P1: Breitensuche
	inline Knoten ersterUnmarkierter();
	inline void Breitensuche(int start);
	int Zusammenhangskomponenten();

	//P2: MST
	shared_ptr<vector<Kante>> KruskalMST();
	void sortKantenListe();
	void mergeSort(int l, int r);
	void merge(int links, int mitte, int rechts);

	vector<Kante> PrimMST();

	//P3: TSP
	vector<Kante> NearestNeighborTSP(int);
};
