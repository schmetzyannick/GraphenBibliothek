/*
	<GraphenBibliothek>
	Copyright(C) < 2019 > <Yannick Luc Schmetz>

	This program is free software : you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.If not, see < https://www.gnu.org/licenses/>.
*/

#pragma once
#include "Kante.h"
#include <vector>
#include <iostream>
#include <string>
#include "DisjointedSetKnoten.h"
#include "BranchAndBoundTree.h"
#include <queue>
#include <map>
using namespace std;

class KWBNode {
public:
	double distanz;
	int knotenNr;
	shared_ptr<KWBNode> vorgaenger;

	KWBNode(int nr) { distanz = INFINITY, knotenNr = nr; vorgaenger = nullptr; }
	KWBNode(int nr, double dis) { distanz = dis, knotenNr = nr; vorgaenger = nullptr; }
};

class KWBVergleich {
public:
	int operator() (const shared_ptr<KWBNode> p1, const shared_ptr<KWBNode> p2)
	{
		return p1->distanz < p2->distanz;
	}
};

//einlesen in eine richtung 
class Graph {
private:
	bool gerichtet;
	bool gewichtet;
	vector<shared_ptr<Kante>> kantenListe;
	vector<shared_ptr<Knoten>> knotenListe;
	string file;

public:
	Graph(bool, bool);
	Graph(bool, bool, vector<shared_ptr<Kante>>, vector<shared_ptr<Knoten>>);

	//getter
	bool getGerichtet();
	bool getGewichtet();
	vector<shared_ptr<Kante>> getKantenListe();
	vector<shared_ptr<Knoten>> getKnotenListe();

	//setter
	void setGerichtet(bool);
	void setGewichtet(bool);
	void setKantenListe(vector<shared_ptr<Kante>>);
	void setKnotenListe(vector<shared_ptr<Knoten>>);

	//einlesen
	void GraphFromTextfile(bool, bool, bool);

	//P1: Breitensuche
	inline void Breitensuche(int start);
	int Zusammenhangskomponenten();

	//P2: MST
private:
	void mergeSort(int l, int r);
	void merge(int links, int mitte, int rechts);
	void sortKantenListe();

public:
	shared_ptr<vector<Kante>> KruskalMST();
	vector<Kante> PrimMST(int start);

	//P3: TSP
private:
	void BranchAndBound(Node, BABTree*, bool bound=true);

public:
	vector<Kante> NearestNeighborTSP(int);
	vector<Kante> BranchAndBoundTSP();
	vector<Kante> TSPAusprobieren();
	vector<Kante> DoppelterBaumTSP(int);

	//P4
private:
	vector<shared_ptr<KWBNode>> Dijkstra(int);
	vector<shared_ptr<KWBNode>> MooreBellmanFord(int, bool findCycle=false);
public:
	deque<shared_ptr<Kante>> DijkstraSTP(int, int, double &kosten);
	deque<shared_ptr<Kante>> MooreBellmanFordSTP(int, int, double &kosten);

	//P5
private:
	bool bfs(shared_ptr<Graph> g, int s, int t, int *parent);
	deque<shared_ptr<Kante>> bfs(shared_ptr<Graph> g, int s, int t);
	void updateKnotenKanten();
	shared_ptr<Graph> getResidualgraphFF();
public:
	vector<shared_ptr<Kante>> fordFulkerson(int s, int t, double &kosten);

	//P6
private:
	shared_ptr<Graph> getResidualgraph();
public:
	vector<shared_ptr<Kante>> CycleCancelingCMF(double &kosten);
	vector<shared_ptr<Kante>> SuccesivShortestPathCMF(double &kosten);

	//P7
	shared_ptr<Graph> copyGraph();
	vector<shared_ptr<Kante>> MaxMatching(int &counter);
};
