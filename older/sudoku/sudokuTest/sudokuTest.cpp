// sudokuTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "board.h"
#include "solver.h"

#include "examples.cpp"

class SudokuTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( SudokuTest );
  CPPUNIT_TEST( testBoardTraversing );
  CPPUNIT_TEST( testBoardCopy );
  CPPUNIT_TEST( testBoardComplete );
  CPPUNIT_TEST( testBoardCorrect );
  CPPUNIT_TEST( testNUM_BITS );
  CPPUNIT_TEST( testBIT_POS );
  CPPUNIT_TEST( testSolverNextStep );
  CPPUNIT_TEST( testSolverSolve );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() {};
  void tearDown() {};

  void testBoardTraversing() {
	CBoard board(solution);
	FOR9(i)
	{
		FOR9(j)
		{
			CPPUNIT_ASSERT( board.GetRow(i)->GetCell(j)->GetValue() == solution[i][j] );
			CPPUNIT_ASSERT( board.GetCol(j)->GetCell(i)->GetValue() == solution[i][j] );
			CPPUNIT_ASSERT( board.GetBox(BOX_NUM(i,j))->GetCell(CELL_NUM(i,j))->GetValue()  == solution[i][j] );
			CPPUNIT_ASSERT( board.GetCell(i,j)->GetValue() == solution[i][j] );
			CPPUNIT_ASSERT( board.GetCell(i,j)->GetRow()->GetNumber() == i );
			CPPUNIT_ASSERT( board.GetCell(i,j)->GetCol()->GetNumber() == j );
			CPPUNIT_ASSERT( board.GetCell(i,j)->GetBox()->GetNumber() == BOX_NUM(i,j) );
		}
	}
	cout << board;
  };

  void testBoardCopy() {
    CBoard board(solution);
	CBoard boardCopy = board;
	FOR9(i)
	{
		FOR9(j)
		{
			board.GetCell(i,j)->SetValue(0);
			CPPUNIT_ASSERT( boardCopy.GetRow(i)->GetCell(j)->GetValue() == solution[i][j] );
			CPPUNIT_ASSERT( boardCopy.GetCol(j)->GetCell(i)->GetValue() == solution[i][j] );
			CPPUNIT_ASSERT( boardCopy.GetBox(BOX_NUM(i,j))->GetCell(CELL_NUM(i,j))->GetValue()  == solution[i][j] );
			CPPUNIT_ASSERT( boardCopy.GetCell(i,j)->GetValue() == solution[i][j] );
			CPPUNIT_ASSERT( boardCopy.GetCell(i,j)->GetRow()->GetNumber() == i );
			CPPUNIT_ASSERT( boardCopy.GetCell(i,j)->GetCol()->GetNumber() == j );
			CPPUNIT_ASSERT( boardCopy.GetCell(i,j)->GetBox()->GetNumber() == BOX_NUM(i,j) );
		}
	}
	CPPUNIT_ASSERT ( boardCopy == CBoard(solution) );
	CPPUNIT_ASSERT ( !(boardCopy == CBoard(puzzle)) );
	CPPUNIT_ASSERT ( boardCopy != CBoard(puzzle) );
	CPPUNIT_ASSERT ( !(boardCopy != CBoard(solution)) );
	CBoard board2;
	board2 = boardCopy;
	CPPUNIT_ASSERT ( board2 == boardCopy );
  }

  void testBoardComplete() {
	  CBoard puz(puzzle);
	  CBoard sol(solution);
	  CPPUNIT_ASSERT( puz.IsComplete() == false );
	  CPPUNIT_ASSERT( sol.IsComplete() == true );
  }

  void testBoardCorrect() {
	  CBoard puz(puzzle);
	  CBoard sol(solution);
	  CBoard badPuz(badPuzzle);
	  CBoard badSol(badSolution);
	  CPPUNIT_ASSERT( puz.IsCorrect() == true );
	  CPPUNIT_ASSERT( sol.IsCorrect() == true );
	  CPPUNIT_ASSERT( badPuz.IsCorrect() == false );
	  CPPUNIT_ASSERT( badSol.IsCorrect() == false );
  }

  void testSolverNextStep() {
	  CBoard puz(puzzle);
	  CSolver solver(puz);
	  CPPUNIT_ASSERT(solver.SolveNextStep());
	  CPPUNIT_ASSERT(solver.GetBoard().IsCorrect());
  }

  void testNUM_BITS() {
	CPPUNIT_ASSERT(NUM_BITS(8)==1);
	CPPUNIT_ASSERT(NUM_BITS(8|32)==2);
	CPPUNIT_ASSERT(NUM_BITS(8|64|128)==3);
	CPPUNIT_ASSERT(NUM_BITS(-1)==32);
	CPPUNIT_ASSERT(NUM_BITS(0)==0);
  }

  void testBIT_POS() {
	  FOR9(i) {
		CPPUNIT_ASSERT(BIT_POS_for_sudoku( 1 << (i+1)) == i+1 );
	  }
  }

  void testSolverSolve() {
	  CBoard puz(puzzle);
	  CSolver solver(puz);
	  CPPUNIT_ASSERT(solver.Solve());
	  CBoard sol(solution);
	  CPPUNIT_ASSERT(solver.GetBoard() == sol);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( SudokuTest );

int _tmain(int argc, _TCHAR* argv[])
{
  // Get the top level suite from the registry
  CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();

  // Adds the test to the list of test to run
  CPPUNIT_NS::TextUi::TestRunner runner;
  runner.addTest( suite );

  // Change the default outputter to a compiler error format outputter
  runner.setOutputter( new CPPUNIT_NS::CompilerOutputter( &runner.result(),
                                                          CPPUNIT_NS::stdCOut() ) );
  // Run the test.
  bool wasSucessful = runner.run();

  cout << endl << "Press (ctrl+q, enter) to quit" << endl;
  cin >> ws;

  // Return error code 1 if the one of test failed.
  return wasSucessful ? 0 : 1;
}
