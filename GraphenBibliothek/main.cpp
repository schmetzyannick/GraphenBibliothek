#include "Graph.h"
#include <iostream>

using namespace std;

int main() {
	cout << "Willkommen!" << endl;
	cout << "Moechten Sie einen gerichteten oder ungerichteten Graph einlesen?" << endl;
	cout << "[1] Ungerichteter Graph \n[2] Gerichteter Graph\n";
	cout << "1 oder 2 eingeben: ";

	int gerichtetInt;
	cin >> gerichtetInt;

	while (gerichtetInt < 1 || gerichtetInt >2) {
		cout << endl << "Falsche Eingabe!" << endl;
		cout << "[1] Ungerichteter Graph \n[2] Gerichteter Graph\n";
		cout << "1 oder 2 eingeben: ";
		cin >> gerichtetInt;
	}

	bool gerichtet;
	gerichtetInt == 1 ? gerichtet = false : gerichtet = true;


	cout << "Moechten Sie einen gewichteten oder ungewichteten Graph einlesen?" << endl;
	cout << "[1] Ungewichteter Graph \n[2] Gewichteter Graph\n";
	cout << "1 oder 2 eingeben: ";

	int gewichtetInt;
	cin >> gewichtetInt;

	while (gerichtetInt < 1 || gerichtetInt >2) {
		cout << endl << "Falsche Eingabe!" << endl;
		cout << "[1] Ungewichteter Graph \n[2] Gewichteter Graph\n";
		cout << "1 oder 2 eingeben: ";
		cin >> gewichtetInt;
	}

	bool gewichtet;
	gewichtetInt == 1 ? gewichtet = false : gewichtet = true;

	Graph g = Graph(gerichtet, gewichtet);
	try {
		g.GraphFromTextfile();
	}
	catch (exception e) {
		cout << e.what() << endl;
		system("pause");
		return -1;
	}

	cout << endl << endl << "Graph eingelesen! " << endl;
	//P1
	//cout << g.Zusammenhangskomponenten() << " Zusammenhangskomponenten" << endl;

	g.KruskalMST();
	g.PrimMST();
	system("pause");
	return 0;
}