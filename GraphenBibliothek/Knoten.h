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