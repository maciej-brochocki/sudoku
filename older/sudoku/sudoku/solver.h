#pragma once

class CSolver
{
    CBoard puzzle;
public:
	CSolver(){}
	CSolver(const CBoard & _puzzle): puzzle(_puzzle) {}
	~CSolver();
	bool SolveNextStep();
	CBoard &GetBoard() { return puzzle;}
	bool Solve();
private:
};
int NUM_BITS(unsigned mask);
int BIT_POS_for_sudoku(int mask);
