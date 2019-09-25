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

	Graph g(gerichtet, gewichtet);
	/*try {
		g.GraphFromTextfile(false, false, false);
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
	//cout << "\nKruskal: \n";
	//g.KruskalMST();
	//cout << "\nPrim: \n";
	//g.PrimMST(0);
	//system("pause");

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
	*/
	/*vector<Kante> tour = g.BranchAndBoundTSP();
	vector<Kante> alle = g.TSPAusprobieren();*/
	
	//P4
	//double kosten = 0.0;
	//deque<shared_ptr<Kante>> weg = g.DijkstraSTP(0, 1, kosten);
	//cout << kosten << endl;
	//double kosten1 = 0.0;
	//deque<shared_ptr<Kante>> weg1 = g.MooreBellmanFordSTP(0,1, kosten1);
	//cout << kosten1 << endl;

	//P5
	//try {
	//	g.GraphFromTextfile(true, false, false);
	//}
	//catch (exception e) {
	//	cout << e.what() << endl;
	//	system("pause");
	//	return -1;
	//}
	//double kosten=0.0;
	//g.fordFulkerson(0, 7, kosten);
	//cout << kosten << endl;

	//P6
	/*try {
		g.GraphFromTextfile(true, true, false);
	}
	catch (exception e) {
		cout << e.what() << endl;
		system("pause");
		return -1;
	}
	double kosten=0.0;
	g.CycleCancelingCMF(kosten);*/
	//g.SuccesivShortestPathCMF(kosten);

	int anzahl = 0;
	try {
		g.GraphFromTextfile(true, false, true);
	}
	catch (exception e) {
		cout << e.what() << endl;
		system("pause");
		return -1;
	}
	g.MaxMatching(anzahl);
	system("pause");
	return 0;
}