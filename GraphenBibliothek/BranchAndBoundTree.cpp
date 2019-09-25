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

#include "BranchAndBoundTree.h"

Node::Node(double kosten, shared_ptr<Knoten> k, shared_ptr<vector<bool>> besuchteKnoten)
{
	kostenBisher = kosten;
	knoten = k;
	nachfolger = vector<Node*>();
	this->besuchteKnoten = make_shared<vector<bool>>(*besuchteKnoten);
	this->genutzteKanten = vector<Kante>();
}

BABTree::BABTree(shared_ptr<Knoten> k, int size)
{
	shared_ptr<vector<bool>> besuchteKnoten = make_shared<vector<bool>>();
	for (int i = 0; i < size; i++) {
		besuchteKnoten->push_back(false);
	}
	besuchteKnoten->at(k->getKnotenNummer()) = true;
	root = Node(0.0, k, besuchteKnoten);
	besteTour = INFINITY;
}
