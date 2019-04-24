#include "DisjointedSetKnoten.h"

DisjointedSetKnoten::DisjointedSetKnoten(int n)
{
	//Anzahl Knoten
	this->n = n;
	parent = new int[n + 1];
	rang = new int[n + 1];

	// Initial, sind alle Knoten in verschiedenen Sets
	// Die Sets haben den Rang 0
	for (int i = 0; i <= n; i++)
	{
		rang[i] = 0;
		//jedes Element ist sein eigner Parent
		//also in seinem eigenen set
		parent[i] = i;
	}
}

//Findet den parent bzw. root vom Knoten nr (des initialen Aufrufs)
//Kruskal prüft ob die Knoten im gleichen Set sind
int DisjointedSetKnoten::find(int nr)
{
	if (nr != parent[nr])
		parent[nr] = find(parent[nr]);
	return parent[nr];
}

void DisjointedSetKnoten::unionByRang(int x, int y)
{
	x = find(x), y = find(y);

	//Der Baum mit kleinerer höhe wird zum Subtree
	if (rang[x] > rang[y])
		parent[y] = x;
	else
		parent[x] = y;
	//Wenn die Bäume gleich groß waren erhöhe den rang des y
	if (rang[x] == rang[y])
		rang[y]++;
}