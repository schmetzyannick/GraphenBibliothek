#pragma once
#include "Kante.h"
#include <vector>
#include <iostream>
#include <string>
#include "DisjointedSetKnoten.h"
#include "BranchAndBoundTree.h"
#include <queue>
using namespace std;

class KWBNode {
public:
	double distanz;
	int knotenNr;
	int vorgaenger;

	KWBNode(int nr) { distanz = INFINITY, knotenNr = nr; vorgaenger = NULL; }
	KWBNode(int nr, double dis) { distanz = dis, knotenNr = nr; vorgaenger = nr; }

	int operator() (const KWBNode& p1, const KWBNode& p2)
	{
		return p1.distanz < p2.distanz;
	}
};

//einlesen in eine richtung 
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
	shared_ptr<vector<vector<double>>> buildAdjaMatrix();

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

	vector<Kante> PrimMST(int start);

	//P3: TSP
	vector<Kante> NearestNeighborTSP(int);
	void ReduceMatrix(shared_ptr<vector<vector<double>>>&, double&);
	void BranchAndBound(Node, BABTree*, bool bound=true);

	vector<Kante> BranchAndBoundTSP();
	vector<Kante> TSPAusprobieren();
	vector<Kante> DoppelterBaumTSP(int);

	//P4
	vector<KWBNode> Dijkstra(int);
	vector<Kante> STPDijkstra(int, int, double &kosten);
};
