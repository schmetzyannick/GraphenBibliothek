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
