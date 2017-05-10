// sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sudoku.h"
#include "board.h"
#include "solver.h"

#include "examples.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	CBoard puz(puzzle);
	cout << "Original puzzle:" << endl << puz;
	CSolver solver(puz);

	if (solver.Solve())
	{
		CBoard sol = solver.GetBoard();
		cout << endl << "Solution:" << endl << sol;
	}
	else
	{
		cout << endl << "Can't solve or puzzle is not a valid sudoku board" << endl;
	}

    cout << endl << "Press (ctrl+q, enter) to quit" << endl;
	cin >> ws;
    
	return 0;
}
