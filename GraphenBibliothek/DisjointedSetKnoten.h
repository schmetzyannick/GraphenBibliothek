#pragma once

class DisjointedSetKnoten {
public:
	int *parent, *rang;
	int n;

	DisjointedSetKnoten(int n);
	int find(int nr);
	void unionByRang(int x, int y);
};