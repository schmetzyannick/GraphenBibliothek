#pragma once
#include "Kante.h"
#include "Knoten.h"

class Node {
public:

	double kostenBisher;
	vector<Node*> nachfolger;
	vector<Kante> genutzteKanten;
	Knoten knoten;
	shared_ptr<vector<bool>> besuchteKnoten;
	bool kill;

	Node(double, Knoten, shared_ptr<vector<bool>>);
	Node() {};
};

class BABTree {
public:
	bool firstTourFound;
	double besteTour;
	vector<Kante> tour;
	Node root;

	BABTree(Knoten,int);
};
