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
	/*try {
		g.GraphFromTextfile(false, false);
	}
	catch (exception e) {
		cout << e.what() << endl;
		system("pause");
		return -1;
	}*/

	/*cout << endl << endl << "Graph eingelesen! " << endl;*/
	//P1
	//cout << g.Zusammenhangskomponenten() << " Zusammenhangskomponenten" << endl;

	//P2
	/*cout << "\nKruskal: \n";
	g.KruskalMST();
	cout << "\nPrim: \n";
	g.PrimMST(0);
	system("pause");*/

	//P3
	/*try {
		for (int i = 0; i <= g.getKnotenListe().size(); i++) {
			cout << "start: " << i << endl;
			g.NearestNeighborTSP(i);
		}
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	
	try {
		for (int i = 0; i <= g.getKnotenListe().size(); i++) {
			cout << "start: " << i << endl;
			g.DoppelterBaumTSP(i);
		}
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	vector<Kante> tour = g.BranchAndBoundTSP();
	vector<Kante> alle = g.TSPAusprobieren();*/
	
	//P4
	//double kosten = 0.0;
	//deque<shared_ptr<Kante>> weg = g.DijkstraSTP(0, 1, kosten);
	//cout << kosten << endl;
	/*double kosten1 = 0.0;
	deque<shared_ptr<Kante>> weg1 = g.MooreBellmanFordSTP(2, 0, kosten1);
	cout << kosten1 << endl;*/

	//P5
	/*try {
		g.GraphFromTextfile(true, false);
	}
	catch (exception e) {
		cout << e.what() << endl;
		system("pause");
		return -1;
	}
	double kosten=0.0;
	g.fordFulkerson(2, 0, kosten);
	cout << kosten << endl;*/

	//P6
	try {
		g.GraphFromTextfile(true, true);
	}
	catch (exception e) {
		cout << e.what() << endl;
		system("pause");
		return -1;
	}
	double kosten=0.0;
	g.CycleCancelingCMF(kosten);
	//g.SuccesivShortestPathCMF(kosten);
	system("pause");
	return 0;
}