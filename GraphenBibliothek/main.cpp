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

	Graph g = Graph(gerichtet);
	try {
		g.GraphFromTextfile();
	}
	catch (exception e) {
		cout << e.what() << endl;
		system("pause");
		return -1;
	}

	cout << endl << endl << "Graph eingelesen! " << endl;
	cout << g.Zusammenhangskomponenten() << " Zusammenhangskomponenten" << endl;
	system("pause");
	return 0;
}