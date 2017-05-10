#pragma once
#include <iostream>

using namespace std;

#define FOR9(x) for(int x=0;x<9;x++)
#define BOX_NUM(i,j) ((i/3)*3 + (j/3))
#define CELL_NUM(i,j) ((i%3)*3 + (j%3))

class CRow;
class CCol;
class CBox;

class CCell
{
public:
    CCell(CRow * r, CCol * c, CBox * b, int v) : row(r) , col(c) , box(b) , value(v) {};
	int GetValue();
	void SetValue(int newValue);
	CRow * GetRow();
	CCol * GetCol();
	CBox * GetBox();
private:
	CRow * row;
	CCol * col;
	CBox * box;
	int value;
};

class CContainer
{
public:
	CContainer(int i) : number(i) {};
	virtual CCell * GetCell(int i);
	virtual void AttachCells(CCell * boardCells[9][9]) = 0;
	virtual GetNumber();
	CCell *cells[9];
	int number;
};

class CRow : public CContainer
{
public:
	CRow(int i) : CContainer(i) {};
	virtual void AttachCells(CCell * boardCells[9][9]);
};

class CCol : public CContainer
{
public:
	CCol(int i) : CContainer(i) {};
	virtual void AttachCells(CCell * boardCells[9][9]);
};

class CBox : public CContainer
{
public:
	CBox(int i) : CContainer(i) {};
	virtual void AttachCells(CCell * boardCells[9][9]);
};

class CBoard
{
public:
	CBoard();
	CBoard(int puzzle[9][9]);
	CBoard(const CBoard &b);
	~CBoard();
	CBoard & operator=(const CBoard &rhs);
	bool operator==(const CBoard &other) const;
	bool operator!=(const CBoard &other) const;
	friend ostream & operator<< (ostream &os, const CBoard &b);
	CRow * GetRow(int i) const;
	CCol * GetCol(int i) const;
	CBox * GetBox(int i) const;
	CCell * GetCell(int row, int col) const;
	bool IsComplete();
	bool IsCorrect();
private:
	CCell *cells[9][9];
	CRow *rows[9];
	CCol *cols[9];
	CBox *boxes[9];
	void InitStructures();
};
