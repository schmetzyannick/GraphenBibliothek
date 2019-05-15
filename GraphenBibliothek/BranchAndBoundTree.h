#pragma once
#include "Kante.h"
#include "Knoten.h"

class Node {
public:

	double kostenBisher;
	vector<Node*> nachfolger;
	vector<Kante> genutzteKanten;
	Knoten knoten;
	//besser in rekursiven aufruf von bandb verschieben => weniger Aufwand
	shared_ptr<vector<bool>> besuchteKnoten;

	Node(double, Knoten, shared_ptr<vector<bool>>);
	Node() {};
};

class BABTree {
public:
	double besteTour;
	//beste tour
	vector<Kante> tour;
	Node root;

	BABTree(Knoten,int);
};
