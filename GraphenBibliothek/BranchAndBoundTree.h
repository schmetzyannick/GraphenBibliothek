#pragma once
#include "Kante.h"
#include "Knoten.h"

class Node {
public:

	double kostenBisher;
	vector<Node*> nachfolger;
	vector<Kante> genutzteKanten;
	shared_ptr<Knoten> knoten;
	//besser in rekursiven aufruf von bandb verschieben => weniger Aufwand
	shared_ptr<vector<bool>> besuchteKnoten;

	Node(double, shared_ptr<Knoten>, shared_ptr<vector<bool>>);
	Node() {};
};

class BABTree {
public:
	double besteTour;
	//beste tour
	vector<Kante> tour;
	Node root;

	BABTree(shared_ptr<Knoten>,int);
};
