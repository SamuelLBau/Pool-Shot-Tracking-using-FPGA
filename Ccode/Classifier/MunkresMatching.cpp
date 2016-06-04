// Olga Souverneva 2016
// Performs min const matching using the munkres algorithm
// Implementation based on http://csclab.murraystate.edu/bob.pilgrim/445/munkres.html

#include "stdafx.h"
#include "MunkresMatching.h"
#include "ClassifierConst.h"
#include "ClassifierTypes.h"
#include "float.h"
#include <iostream>
#include <iomanip>

using namespace std;

static float _costMatrix[MUNKRES_MAX_SIZE][MUNKRES_MAX_SIZE] = {};
static unsigned char _maskMatrix[MUNKRES_MAX_SIZE][MUNKRES_MAX_SIZE] = {};
static bool _rowCover[MUNKRES_MAX_SIZE] = {};
static bool _colCover[MUNKRES_MAX_SIZE] = {};
unsigned char _costRow = 0;
unsigned char _costCol = 0;
unsigned char _pathCnt = 0;
unsigned char _pathRow0 = 0;
unsigned char _pathCol0 = 0;
static unsigned char _path[2*MUNKRES_MAX_SIZE+1][2] = {};

static void StepOne(unsigned char& step);
static void StepTwo(unsigned char& step);
static void StepThree(unsigned char& step);
static void StepFour(unsigned char& step);
static void StepFive(unsigned char& step);
static void StepSix(unsigned char& step);
static void StepSeven(unsigned char* results);
static void OutputCostMatrix();
static void OutputMaskMatrix();
static void OutputCovers();

static void ClearPaths()
{
	for (unsigned char r = 0; r<2*MUNKRES_MAX_SIZE+1; r++)
	{
		for (unsigned char c = 0; c<2; c++)
		{
			_path[r][c] = 0;
		}
	}
}

void MunkresMatching(float costMatrix[][MUNKRES_MAX_SIZE], unsigned char* results, unsigned char costLength, unsigned char costWidth)
{
	if (costMatrix == NULL || results == NULL)
		return;

	if (_costRow > MUNKRES_MAX_SIZE || _costCol > MUNKRES_MAX_SIZE)
		return;

	// Save and reset params. Need to copy the matrix as will be replacing values with zeros.
	_costRow = costLength;
	_costCol = costWidth;
	_pathCnt = 0;
	_pathRow0 = 0;
	_pathCol0 = 0;
	ClearPaths();
	for (unsigned char r = 0; r<_costRow; r++)
	{
		for (unsigned char c = 0; c<_costCol; c++)
		{
			_costMatrix[r][c] = costMatrix[r][c];
		}
	}

	unsigned char step = 1;
	bool done = false;
	while(!done)
	{
		cout << static_cast<int>(step) << "\n\n";
		OutputCostMatrix();
		OutputMaskMatrix();
		switch(step)
		{
		case 1:
			StepOne(step);
			break;
		case 2:
			StepTwo(step);
			break;
		case 3:
			StepThree(step);
			break;
		case 4:
			StepFour(step);
			break;
		case 5:
			StepFive(step);
			break;
		case 6:
			StepSix(step);
			break;
		default:
			StepSeven(results);
			done = true;
			break;
		}
	}
}

static void StepOne(unsigned char& step)
{
	float min_in_row;

	// For each row of the matrix, find the smallest element and subtract it from every element in its row.  
	// Go to Step 2.
	for (unsigned char r = 0; r<_costRow; r++)
	{
		min_in_row = _costMatrix[r][0];
		for (unsigned char c = 0; c<_costCol; c++)
		{
			if (_costMatrix[r][c] < min_in_row)
				min_in_row = _costMatrix[r][c];
			if (_maskMatrix[r][c] != 0)
				_maskMatrix[r][c] = 0;
		}
		for (unsigned char c = 0; c<_costCol; c++)
		{
			_costMatrix[r][c] -= min_in_row;
		}
	}
	step = 2;
}

static void ClearCovers()
{
	for (unsigned char r = 0; r<_costRow; r++)
	{
		_rowCover[r] = false;
	}
	for (unsigned char c = 0; c<_costCol; c++)
	{
		_colCover[c] = false;
	}
}

static void StepTwo(unsigned char& step)
{
	// Reset row/column covers
	ClearCovers();
	
	// Find a zero (Z) in the resulting matrix.  If there is no starred zero in its row or column, star Z. 
	// Repeat for each element in the matrix. Go to Step 3.
	for (unsigned char r = 0; r<_costRow; r++)
	{
		for (unsigned char c = 0; c<_costCol; c++)
		{
			if (_costMatrix[r][c] == 0 && _rowCover[r] == false && _colCover[c] == false)
			{
				_maskMatrix[r][c] = 1;
				_rowCover[r] = true;
				_colCover[c] = true;
			}
		}
	}

	// Reset row/column covers
	ClearCovers();
	step = 3;
}

static void StepThree(unsigned char& step)
{
	// Cover each column containing a starred zero.
	for (unsigned char r = 0; r<_costRow; r++)
		for (unsigned char c = 0; c<_costCol; c++)
			if (_maskMatrix[r][c] == 1)
				_colCover[c] = true;

	unsigned char colCount = 0;
	for (unsigned char c = 0; c<_costCol; c++)
		if (_colCover[c])
			colCount++;
	 
	// If K columns are covered, the starred zeros describe a complete set of unique assignments.  
	// In this case, Go to DONE, otherwise, Go to Step 4.
	if (colCount >= _costCol || colCount >= _costRow)
		step = 7;
	else
		step = 4;
}

static bool FindZero(unsigned char& row, unsigned char& col)
{
	unsigned char r = 0;
	unsigned char c;

	while (r<_costRow)
	{
		c = 0;
		while (c < _costCol)
		{
			if (_costMatrix[r][c] == 0 && !_rowCover[r] && !_colCover[c])
			{
				row = r;
				col = c;
				return true;
			}
			c++;
		}
		r++;
	}
	return false;
}

static bool FindStarInRow(unsigned char row, unsigned char& col)
{
	for (unsigned char c = 0; c<_costCol; c++)
	{
		if (_maskMatrix[row][c] == 1)
		{
			col = c;
			return true;
		}
	}
	return false;
}

static void StepFour(unsigned char& step)
{
	unsigned char row = 0;
	unsigned char col = 0;
	bool found = false;
	bool done = false;
	
	// Find a noncovered zero and prime it.  If there is no starred zero in the row containing this 
	// primed zero, Go to Step 5.  Otherwise, cover this row and uncover the column containing the 
	// starred zero. Continue in this manner until there are no uncovered zeros left. Save the 
	// smallest uncovered value and Go to Step 6.
	while (!done)
	{
		OutputCovers();
		found = FindZero(row, col);
		if (!found)
		{
			done = true;
			step = 6;
		}
		else
		{
			_maskMatrix[row][col] = 2;
			unsigned char col2 = 0;
			found = FindStarInRow(row, col2);
			if (found)
			{
				_rowCover[row] = true;
				_colCover[col2] = false;
			}
			else
			{
				done = true;
				step = 5;
				_pathRow0 = row;
				_pathCol0 = col;
			}
		}
	}
}

static bool FindStarInCol(unsigned char& row, unsigned char col)
{
	for (unsigned char r = 0; r<_costRow; r++)
	{
		if (_maskMatrix[r][col] == 1)
		{
			row = r;
			return true;
		}
	}
	return false;
}

static bool FindPrimeInRow(unsigned char row, unsigned char& col)
{
	for (unsigned char c = 0; c<_costCol; c++)
	{
		if (_maskMatrix[row][c] == 2)
		{
			col = c;
			return true;
		}
	}
	return false;
}

static void AugmentPath()
{
	for (unsigned char p = 0; p<_pathCnt; p++)
	{
		if (_maskMatrix[_path[p][0]][_path[p][1]] == 1)
			_maskMatrix[_path[p][0]][ _path[p][1]] = 0;
		else
			_maskMatrix[_path[p][0]][ _path[p][1]] = 1;
	}
}

static void ErasePrimes()
{
	for (unsigned char r = 0; r<_costRow; r++)
	{
		for (unsigned char c = 0; c<_costCol; c++)
		{
			if (_maskMatrix[r][c] == 2)
				_maskMatrix[r][c] = 0;
		}
	}
}

static void StepFive(unsigned char& step)
{
	// Construct a series of alternating primed and starred zeros as follows.  Let Z0 represent the uncovered
	// primed zero found in Step 4.  Let Z1 denote the starred zero in the column of Z0 (if any). Let Z2 
	// denote the primed zero in the row of Z1 (there will always be one).  Continue until the series 
	// terminates at a primed zero that has no starred zero in its column.  Unstar each starred zero of the 
	// series, star each primed zero of the series, erase all primes and uncover every line in the matrix.
	// Return to Step 3.
	bool done = false;
	unsigned char r = 0;
	unsigned char c = 0;

	_pathCnt = 1;
	_path[_pathCnt-1][0] = _pathRow0;
	_path[_pathCnt-1][1] = _pathCol0;

	while (!done)
	{
		if (FindStarInCol(r, _path[_pathCnt-1][1]))
		{
			_pathCnt++;
			_path[_pathCnt-1][0] = r;
			_path[_pathCnt-1][1] = _path[_pathCnt-2][1];
		}
		else
			done = true;
		if (!done && FindPrimeInRow(_path[_pathCnt-1][0], c))
		{
			_pathCnt++;
			_path[_pathCnt-1][0] = _path[_pathCnt-2][0];
			_path[_pathCnt-1][1] = c;
		}
		OutputMaskMatrix();
	}
	AugmentPath();
	ClearCovers();
	ErasePrimes();
	step = 3;
}

static float FindSmallestUncovered()
{
	float minVal = FLT_MAX;
	for (unsigned char r = 0; r<_costRow; r++)
	{
		for (unsigned char c = 0; c<_costCol; c++)
		{
			if (!_rowCover[r] && !_colCover[c])
				if (_costMatrix[r][c] < minVal)
					minVal = _costMatrix[r][c];
		}
	}
	return minVal;
}

static void StepSix(unsigned char& step)
{
	float minVal = FindSmallestUncovered();
	for (unsigned char r = 0; r<_costRow; r++)
	{
		for (unsigned char c = 0; c<_costCol; c++)
		{
			if (_rowCover[r])
				_costMatrix[r][c]+=minVal;
			if (!_colCover[c])
				_costMatrix[r][c]-=minVal;
		}
	}
	step = 4;
}

static void StepSeven(unsigned char* results)
{
	// Each row is classified as the column with the *.
	for (unsigned char r = 0; r<_costRow; r++)
	{
		FindStarInRow(r, results[r]);
	}
}

static void OutputCostMatrix()
{
	for (unsigned char r = 0; r<_costRow; r++)
	{
		for (unsigned char c = 0; c<_costCol; c++)
		{
			cout << std::setprecision(2) << _costMatrix[r][c] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

static void OutputMaskMatrix()
{
	cout << "Mask: " << "\n";
	for (unsigned char r = 0; r<_costRow; r++)
	{
		for (unsigned char c = 0; c<_costCol; c++)
		{
			switch(_maskMatrix[r][c])
			{
			case 0:
				cout << "0 ";
				break;
			case 1:
				cout << "* ";
				break;
			case 2:
				cout << "' ";
				break;
			}
		}
		cout << "\n";
	}
	cout << "\n";
}

static void OutputCovers()
{
	cout << "Row Covers: ";
	for (unsigned char r = 0; r<_costRow; r++)
	{
		if (_rowCover[r])
			cout << static_cast<int>(r) << " ";
	}
	cout << "\n";
	cout << "Column Covers: ";
	for (unsigned char c = 0; c<_costCol; c++)
	{
		if (_colCover[c])
			cout << static_cast<int>(c) << " ";
	}
	cout << "\n";
}
