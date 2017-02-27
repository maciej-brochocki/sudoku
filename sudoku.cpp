// sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

typedef unsigned char UInt8;
typedef unsigned short UInt16;

UInt8 puzzle[9][9] = {
/*	{0, 4, 2,  0, 0, 0,  0, 0, 0},
	{0, 9, 0,  0, 0, 0,  0, 6, 0},
	{0, 0, 0,  0, 0, 0,  3, 0, 8},
	{0, 0, 0,  0, 0, 5,  0, 0, 0},
	{0, 0, 0,  0, 0, 7,  1, 0, 0},
	{8, 0, 9,  0, 0, 0,  0, 2, 0},
	{0, 0, 0,  2, 0, 0,  0, 0, 0},
	{1, 0, 0,  0, 0, 0,  7, 0, 0},
	{0, 0, 0,  9, 0, 0,  0, 0, 1}
};*/
{0,	8,	0,	4,	7,	9,	0,	3,	0},
{0,	0,	0,	0,	0,	6,	8,	7,	2},
{0,	3,	0,	0,	1,	0,	4,	0,	9},
{8,	0,	7,	0,	0,	5,	1,	0,	3},
{0,	2,	1,	8,	0,	4,	7,	0,	0},
{0,	0,	0,	0,	6,	0,	2,	0,	8},
{5,	6,	0,	0,	0,	0,	3,	0,	0},
{3,	9,	0,	6,	4,	1,	0,	8,	7},
{1,	0,	4,	5,	0,	0,	0,	2,	0}
};

UInt8 result[9][9];

UInt8 solution[9][9] = {
/*	{6, 4, 2,  3, 8, 9,  5, 1, 7},
	{3,	9, 8,  7, 5, 1,  4, 6, 2},
	{7,	1, 5,  4, 6, 2,  3, 9, 8},
	{4,	6, 1,  8, 2, 5,  9, 7, 3},
	{2,	5, 3,  6, 9, 7,  1, 8, 4},
	{8,	7, 9,  1, 4, 3,  6, 2, 5},
	{9,	3, 7,  2, 1, 4,  8, 5, 6},
	{1,	2, 6,  5, 3, 8,  7, 4, 9},
	{5,	8, 4,  9, 7, 6,  2, 3, 1}
};*/
{2,	8,	5,	4,	7,	9,	6,	3,	1},
{4,	1,	9,	3,	5,	6,	8,	7,	2},
{7,	3,	6,	2,	1,	8,	4,	5,	9},
{8,	4,	7,	9,	2,	5,	1,	6,	3},
{6,	2,	1,	8,	3,	4,	7,	9,	5},
{9,	5,	3,	1,	6,	7,	2,	4,	8},
{5,	6,	8,	7,	9,	2,	3,	1,	4},
{3,	9,	2,	6,	4,	1,	5,	8,	7},
{1,	7,	4,	5,	8,	3,	9,	2,	6}
};

/// returns bit number if only one bit is set, otherwise 0
UInt8 bitNumber(UInt16 number)
{
	if (!number)
		return 0;
	for (UInt8 i=0; i<9; i++)
	{
		if (number & 1)
		{
			if (number & 510)
				return 0;
			else
				return i+1;
		}
		number >>= 1;
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	UInt8 i,j,k;
	int knownFields, lastKnownFields;

	//initialize result with puzzle
	for (i=0; i<9; i++)
	{
		for (j=0; j<9; j++)
		{
			result[i][j] = puzzle[i][j];
		}
	}

	do {

	//calculate possibilities matrix
	lastKnownFields = 0;
	UInt16 possibilities[9][9];
	for (i=0; i<9; i++)
	{
		for (j=0; j<9; j++)
		{
			if (result[i][j])
				possibilities[i][j] = 1 << (result[i][j]-1);
			else
				possibilities[i][j] = 511; //nine ones - everything is possible
		}
	}
	for (i=0; i<9; i++)
	{
		for (j=0; j<9; j++)
		{
			if (result[i][j])
			{
				UInt8 square_row = i - i%3;
				UInt8 square_col = j - j%3;
				for (k=0; k<9; k++)
				{
					if ((k != i) && (!result[k][j]))
						possibilities[k][j] &= ~possibilities[i][j];
					if ((k != j) && (!result[i][k]))
						possibilities[i][k] &= ~possibilities[i][j];
					if (((square_row+k/3 != i) && (square_col+k%3 != j)) && (!result[square_row+k/3][square_col+k%3]))
						possibilities[square_row+k/3][square_col+k%3] &= ~possibilities[i][j];
				}
				lastKnownFields++;
			}
		}
	}

	//if there is one possibility store result
	knownFields = 0;
	for (i=0; i<9; i++)
	{
		for (j=0; j<9; j++)
		{
			if ((k = bitNumber(possibilities[i][j]))!=0)
			{
				result[i][j] = k;
				knownFields++;
			}
			else
				result[i][j] = 0;
		}
	}

	} while ((knownFields > lastKnownFields) && (knownFields < 81));

	//verify result
	for (i=0; i<9; i++)
	{
		for (j=0; j<9; j++)
		{
			if ((result[i][j]) && (result[i][j] != solution[i][j]))
			{
				cout << "error at [" << i << "," << j << "] = " << result[i][j] << endl;
				return -1;
			}
		}
	}

	//print result
	for (i=0; i<9; i++)
	{
		for (j=0; j<9; j++)
		{
			cout << (int)result[i][j] << ", ";
		}
		cout << endl;
	}

	return 0;
}
