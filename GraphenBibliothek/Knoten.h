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
#include <vector>
#include <iostream>

class Kante;

using namespace std;
class Knoten {
private:
	int knotenNummer;
	bool marked;
	double balance;
	double aktuelleBalance;

public:
	vector<shared_ptr<Knoten>> nachbarn;
	vector<shared_ptr<Kante>> anliegendeKanten;

	Knoten();
	Knoten(int, bool, vector<shared_ptr<Knoten>>, vector<shared_ptr<Kante>>);

	int getKnotenNummer();
	bool isMarked();
	double getAktuelleBalance();
	double getBalance();
	vector<shared_ptr<Kante>> getKantenlisteSortet();
	shared_ptr<Kante> getGuenstigsteKantezuKnoten(int);

	void markKnoten();
	void setKnotenNummer(int);
	void setAktuelleBalance(double);
	void setBalance(double);
};