#pragma once
// NDisjointSets.h
// simple class for disjoint sets of integers in a range
// union without  depth

#include <iostream>
#include <string>
using namespace std;

class NDisjointSets
{
public:
	NDisjointSets();
	NDisjointSets(int);
	~NDisjointSets();
	NDisjointSets(const NDisjointSets&);

	NDisjointSets & operator=(const NDisjointSets&);

	int Find(int);
	void Union(int, int);

	int getDistinctSetCount();

	void dumpSets();
	void dumpSets(string);
	void showSet(int);
	void showSet(string, int);
	void showDistinctSets();
	void showDistinctSets(string);
	void showAllPaths(string);
	void reset();
	int getItem(int);



private:
	int *a;                    // the data (ints)
	int arraysize;             // size of the array
	int n;                     // items
	int distinctsets;          // distinct sets
	int *size;
};

NDisjointSets::NDisjointSets()
{
	n = 0;
	arraysize = 0;
	a = NULL;
	distinctsets = 0;

	size = NULL;
}

NDisjointSets::NDisjointSets(int nn)
{
	n = nn;
	arraysize = n;
	a = new int[arraysize];

	for (int i = 0; i<n; i++)
		a[i] = i;// each is its own leader

	distinctsets = n;

	size = new int[arraysize];

	for (int i = 0; i < n; i++)
		size[i] = 1;
}

NDisjointSets::~NDisjointSets()
{
	delete[] a;

	delete[] size;
}

NDisjointSets::NDisjointSets(const NDisjointSets &other)
{
	arraysize = other.arraysize;
	n = other.n;
	a = new int[arraysize];
	for (int i = 0; i<n; i++)
		a[i] = other.a[i];
	distinctsets = other.distinctsets;
}

NDisjointSets & NDisjointSets::operator=(const NDisjointSets &rhs)
{
	if (this == &rhs)      // watch for self-asst
		return *this;

	if (a != NULL)
		delete[] a;
	arraysize = rhs.arraysize;
	n = rhs.n;
	a = new int[arraysize];
	for (int i = 0; i<n; i++)
	{
		a[i] = rhs.a[i];
	}
	distinctsets = rhs.distinctsets;

	return *this;
}


void NDisjointSets::dumpSets()
{
	int j = 0;
	for (int i = 0; i<n; i++)
	{
		cout << i << ": ";
		j = i;
		while (a[j] != j)
			j = a[j];
		cout << j << endl;
	}
}

void NDisjointSets::dumpSets(string msg)
{
	cout << msg << endl;
	dumpSets();
}


void NDisjointSets::showSet(int x)
{
	int leader;
	leader = Find(x);
	cout << "Set for " << x << " has leader: " << leader << " - contains: ";
	for (int i = 0; i<n; i++)
	{
		if (Find(i) == leader)
			cout << i << " ";
	}
	cout << endl;
}

void NDisjointSets::showSet(string msg, int x)
{
	cout << msg << endl;
	showSet(x);
}

void NDisjointSets::showDistinctSets()
{
	bool *got;
	got = new bool[n];
	for (int i = 0; i<n; i++)
		got[i] = false;

	int leader = -1;
	for (int i = 0; i<n; i++)
	{
		leader = Find(i);
		if (!got[leader])
		{
			for (int j = 0; j<n; j++)
			{
				if (Find(j) == leader)
				{
					got[j] = true;
					cout << j << " ";
				}
			}
			cout << endl;
		}
	}
}

void NDisjointSets::showDistinctSets(string msg)
{
	cout << msg << endl;
	showDistinctSets();
}

int NDisjointSets::getDistinctSetCount()
{
	return distinctsets;
}

//======================================================================

// add this function's code
int NDisjointSets::Find(int x)
{
	if (x != a[x])
	{
		a[x] = Find(a[x]);
	}
	return a[x];
}

//  Add this function's code
void NDisjointSets::Union(int x, int y)
{
	int x_root = Find(x);
	int y_root = Find(y);

	if (size[x_root] > size[y_root])
	{
		a[y_root] = x_root;
		size[x_root] = size[x_root] + size[y_root];

		if (x_root != y_root)
			distinctsets--;
	}

	else
	{
		a[x_root] = y_root;
		size[y_root] = size[x_root] + size[y_root];

		if (x_root != y_root)
			distinctsets--;
	}
}

void NDisjointSets::showAllPaths(string t)
{
	cout << t << endl;

	for (int i = 0; i < n; i++)
		cout << i << ": " << a[i] << endl;
}

void NDisjointSets::reset()
{
	for (int i = 0; i < n; i++)
		a[i] = i;
}

int NDisjointSets::getItem(int i)
{
	//a
	return a[i];
}

//======================================================================
