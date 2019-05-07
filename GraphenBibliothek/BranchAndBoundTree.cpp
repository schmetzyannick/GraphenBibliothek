#include "BranchAndBoundTree.h"

Node::Node(double kosten, Knoten k, shared_ptr<vector<bool>> besuchteKnoten)
{
	kostenBisher = kosten;
	knoten = k;
	nachfolger = vector<Node*>();
	kill = false;
	this->besuchteKnoten = make_shared<vector<bool>>(*besuchteKnoten);
	this->genutzteKanten = vector<Kante>();
}

BABTree::BABTree(Knoten k, int size)
{
	shared_ptr<vector<bool>> besuchteKnoten = make_shared<vector<bool>>();
	for (int i = 0; i < size; i++) {
		besuchteKnoten->push_back(false);
	}
	besuchteKnoten->at(k.getKnotenNummer()) = true;
	root = Node(0.0, k, besuchteKnoten);
	besteTour = INFINITY;
	firstTourFound = false;
}
