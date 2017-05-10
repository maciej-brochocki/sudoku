#include "stdafx.h"
#include "board.h"
#include <set>
#include <vector>

int CCell::GetValue()
{
	return value;
};

void CCell::SetValue(int newValue)
{
	value = newValue;
};

CRow * CCell::GetRow()
{
	return row;
};

CCol * CCell::GetCol()
{
	return col;
};

CBox * CCell::GetBox()
{
	return box;
};

CCell * CContainer::GetCell(int i)
{
	return cells[i];
};

int CContainer::GetNumber()
{
	return number;
};

void CRow::AttachCells(CCell * boardCells[9][9])
{
	FOR9(i)
	{
		cells[i] = boardCells[number][i];
	}
};

void CCol::AttachCells(CCell * boardCells[9][9])
{
	FOR9(i)
	{
		cells[i] = boardCells[i][number];
	}
};

void CBox::AttachCells(CCell * boardCells[9][9])
{
	FOR9(i)
	{
		cells[i] = boardCells[BOX_NUM(number,i)][CELL_NUM(number,i)];
	}
};

void CBoard::InitStructures()
{
	FOR9(i)
	{
		rows[i] = new CRow(i);
		cols[i] = new CCol(i);
		boxes[i] = new CBox(i);
	}
	FOR9(i)
	{
		FOR9(j)
		{
			cells[i][j] = new CCell(rows[i], cols[j], boxes[BOX_NUM(i,j)], 0);
		}
	}
	FOR9(i)
	{
		rows[i]->AttachCells(cells);
		cols[i]->AttachCells(cells);
		boxes[i]->AttachCells(cells);
	}
};

CBoard::CBoard()
{
	InitStructures();
}

CBoard::CBoard(int puzzle[9][9])
{
	InitStructures();
	FOR9(i)
	{
		FOR9(j)
		{
			GetCell(i,j)->SetValue(puzzle[i][j]);
		}
	}
};

CBoard::CBoard(const CBoard &b)
{
	InitStructures();
	FOR9(i)
	{
		FOR9(j)
		{
			GetCell(i,j)->SetValue(b.GetCell(i,j)->GetValue());
		}
	}
};

CBoard::~CBoard()
{
	FOR9(i)
	{
		delete rows[i];
		delete cols[i];
		delete boxes[i];
	}
	FOR9(i)
	{
		FOR9(j)
		{
			delete cells[i][j];
		}
	}
};

CBoard & CBoard::operator=(const CBoard &rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	FOR9(i)
	{
		FOR9(j)
		{
			GetCell(i,j)->SetValue(rhs.GetCell(i,j)->GetValue());
		}
	}
	return *this;
}

bool CBoard::operator==(const CBoard &other) const
{
	bool result = true;
	FOR9(i)
	{
		FOR9(j)
		{
			result = result && (GetCell(i,j)->GetValue() == other.GetCell(i,j)->GetValue());
		}
	}
	return result;
};

bool CBoard::operator!=(const CBoard &other) const
{
	return !(*this == other);
}

ostream & operator<< (ostream &os, const CBoard &b)
{
	FOR9(i)
	{
		if (!(i%3))
		{
			os << endl;
		}
		FOR9(j)
		{
			if (!(j%3))
			{
				os << "  ";
			}
			os << b.GetCell(i,j)->GetValue() << ", ";
		}
		os << endl;
	}
	return os;
}

CRow * CBoard::GetRow(int i) const
{
	return rows[i];
};

CCol * CBoard::GetCol(int i) const
{
	return cols[i];
};

CBox * CBoard::GetBox(int i) const
{
	return boxes[i];
};

CCell * CBoard::GetCell(int row, int col) const
{
	return cells[row][col];
};

bool CBoard::IsComplete()
{
	FOR9(i)
	{
		FOR9(j)
		{
			if (!GetCell(i,j)->GetValue())
			{
				return false;
			}
		}
	}
	return true;
}

bool CBoard::IsCorrect()
{
	for(int i=0; i<9;++i) // test dla 9 wierszy
	{
		std::set<int> wiersz;
		std::set<int> kolumna;
		for(int j=0; j<9;++j) // test dla pojedynczego wiersza 
		{
			int wartosc = GetCell(i,j)->GetValue();
			if( wartosc != 0 ) {
				if(wiersz.find(wartosc) != wiersz.end())
					return false;
				wiersz.insert(wartosc);
			}

			int wartosc1 = GetCell(j,i)->GetValue();
			if( wartosc1 != 0 ) {
				if(kolumna.find(wartosc1) != kolumna.end())
					return false;
				kolumna.insert(wartosc1);
			}
	
		}
	}

	std::vector<std::set<int> > kwadraciki;
	kwadraciki.resize(9);

	for(int i=0; i<9; ++i) 
	{
		for(int j=0; j<9; ++j) 
		{
			int val = GetCell(i,j)->GetValue();
			if( val != 0 ) {
				std::set<int>& box = kwadraciki.at(BOX_NUM(i,j));
				if( box.find(val) != box.end() )
					return false;
				box.insert(val);
			}
		}
	}

	return true;
}
