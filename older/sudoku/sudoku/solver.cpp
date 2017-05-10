#include "stdafx.h"
#include "board.h"
#include "solver.h"
#include <algorithm>

int NUM_BITS(unsigned mask){
	int	num = 0;

	while(mask){
		num += mask & 1;
		mask = mask / 2;
	}
	return num;
}

int BIT_POS_for_sudoku(int mask){
	int	num = 0;

	while(mask){
		mask = mask >> 1;
		num++;			
		if (mask & 1)
		{
			return num;
		}
	}
	return num;
}

CSolver::~CSolver()
{
};

bool CSolver::SolveNextStep()
{
	int possibleRowValues[9];
	int possibleColValues[9];
	int possibleBoxValues[9];

	std::fill_n(possibleRowValues, 9, 1022); //1111111110
	std::fill_n(possibleColValues, 9, 1022);
	std::fill_n(possibleBoxValues, 9, 1022);

	FOR9(i)
	{
		FOR9(j)
		{
			int val = puzzle.GetCell(i,j)->GetValue();
            if (val)
			{
				possibleRowValues[i] &= ~(1 << val);
				possibleColValues[j] &= ~(1 << val);
				possibleBoxValues[BOX_NUM(i,j)] &= ~(1 << val);
			}
		}
	}

	FOR9(i)
	{
		FOR9(j)
		{
			if (!(puzzle.GetCell(i,j)->GetValue()))
			{
				int bit_mask = possibleRowValues[i] &
					possibleColValues[j] &
					possibleBoxValues[BOX_NUM(i,j)];
				if (NUM_BITS(bit_mask) == 1)
				{
					puzzle.GetCell(i,j)->SetValue(BIT_POS_for_sudoku(bit_mask));
					return true;
				}
			}
		}
	}
    return false;
}

bool CSolver::Solve()
{
	while(SolveNextStep());
	return puzzle.IsComplete();
}
