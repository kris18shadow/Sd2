#include "Solver.h"

Solver::Solver(size_t N, size_t M, char** Map, Cell START)
{
	this->N = N;
	this->M = M;

	//Generate cell map:
	this->cellMap = new Cell*[N];
	for (size_t i = 0; i < N; i++)
		this->cellMap[i] = new Cell[M];

	//Assign values:
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			this->cellMap[i][j].setX(i);
			this->cellMap[i][j].setY(j);
			this->cellMap[i][j].setSymbol(Map[i][j]);
		}
	}

	this->START = START;
	this->pCurrent = NULL;
}

Solver::~Solver()
{
	//Handle dynamically allocated memory:
	for (size_t i = 0; i < N; i++)
		delete this->cellMap[i];
	delete this->cellMap;
}

void Solver::findPath(Cell* END)
{
	//Mark all cells as unvisited:
	for (size_t i = 0; i < N; i++)
		for (size_t k = 0; k < M; k++)
			cellMap[i][k].markUnvisited();


	//Using BFS:
	Cell* pStart = &START;
	cellQueue.push(pStart);
	bool noPath = true;

 	while (!cellQueue.empty())
	{

		pCurrent = cellQueue.peek();
		pCurrent->markVisited();
		cellMap[pCurrent->getX()][pCurrent->getY()].markVisited();
		cellQueue.pop();

		if (*pCurrent == *END)
		{
			noPath = false;
			Stack<Cell*> path;
			while (pCurrent != pStart)
			{
				path.push(pCurrent);
				pCurrent = pCurrent->getParent();
			}

			std::cout << "\n>>>>> ";
			START.printCell();
			while (!path.isEmpty())
			{
				path.peek()->printCell();
				path.pop();
			}
			std::cout << std::endl;
			cellMap[END->getX()][END->getY()].markUnvisited();
		}
		else
		{
			tryUp(false);
			tryDown(false);
			tryRight(false);
			tryLeft(false);
		}
	}	
}

void Solver::findAvailableCells()
{
	Cell* pStart = &START;
	cellQueue.push(pStart);
	bool noPath = true;

	while (!cellQueue.empty())
	{

		pCurrent = cellQueue.peek();
		pCurrent->markVisited();
		cellMap[pCurrent->getX()][pCurrent->getY()].markVisited();
		cellQueue.pop();

		//argument true == prints every step
		tryUp(true);
		tryDown(true);
		tryRight(true);
		tryLeft(true);
	}
}

void Solver::findAllPaths()
{
	for (size_t i = 0; i < availablePaths.getCurrSize(); i++)
	{
		std::cout << "\n\nPoint ";
		availablePaths[i].printCell();
		std::cout << " :\n";
		findPath(&availablePaths[i]);		
	}
	std::cout << std::endl;
}

void Solver::tryLeft(bool showStep)
{
	if (pCurrent->getY() - 1 >= 0
		&& cellMap[pCurrent->getX()][pCurrent->getY() - 1].getSymbol() == '.'
		&& !(cellMap[pCurrent->getX()][pCurrent->getY() - 1].isVisited()))
	{
		cellQueue.push(&cellMap[pCurrent->getX()][pCurrent->getY() - 1]);
		cellMap[pCurrent->getX()][pCurrent->getY() - 1].markVisited();
		
		cellMap[pCurrent->getX()][pCurrent->getY() - 1].setParent(pCurrent);

		if (showStep)
		{
			cellMap[pCurrent->getX()][pCurrent->getY() - 1].printCell();
			availablePaths.pushBack(cellMap[pCurrent->getX()][pCurrent->getY() - 1]);
		}
	}
}

void Solver::tryRight(bool showStep)
{
	if (pCurrent->getY() + 1 < M
		&& cellMap[pCurrent->getX()][pCurrent->getY() + 1].getSymbol() == '.'
		&& !(cellMap[pCurrent->getX()][pCurrent->getY() + 1].isVisited()))
	{
		cellQueue.push(&cellMap[pCurrent->getX()][pCurrent->getY() + 1]);
		cellMap[pCurrent->getX()][pCurrent->getY() + 1].markVisited();

		cellMap[pCurrent->getX()][pCurrent->getY() + 1].setParent(pCurrent);

		if (showStep)
		{
			cellMap[pCurrent->getX()][pCurrent->getY() + 1].printCell();
			availablePaths.pushBack(cellMap[pCurrent->getX()][pCurrent->getY() + 1]);
		}
	}
}

void Solver::tryDown(bool showStep)
{
	if (pCurrent->getX() + 1 < N
		&& cellMap[pCurrent->getX() + 1][pCurrent->getY()].getSymbol() == '.'
		&& !(cellMap[pCurrent->getX() + 1][pCurrent->getY()].isVisited()))
	{
		cellQueue.push(&cellMap[pCurrent->getX() + 1][pCurrent->getY()]);
		cellMap[pCurrent->getX() + 1][pCurrent->getY()].markVisited();

		cellMap[pCurrent->getX() + 1][pCurrent->getY()].setParent(pCurrent);

		if (showStep)
		{
			cellMap[pCurrent->getX() + 1][pCurrent->getY()].printCell();
			availablePaths.pushBack(cellMap[pCurrent->getX() + 1][pCurrent->getY()]);
		}
	}
}

void Solver::tryUp(bool showStep)
{
	if (pCurrent->getX() - 1 >= 0
		&& cellMap[pCurrent->getX() - 1][pCurrent->getY()].getSymbol() == '.'
		&& !(cellMap[pCurrent->getX() - 1][pCurrent->getY()].isVisited()))
	{
		cellQueue.push(&cellMap[pCurrent->getX() - 1][pCurrent->getY()]);
		cellMap[pCurrent->getX() - 1][pCurrent->getY()].markVisited();

		cellMap[pCurrent->getX() - 1][pCurrent->getY()].setParent(pCurrent);

		if (showStep)
		{
			cellMap[pCurrent->getX() - 1][pCurrent->getY()].printCell();
			availablePaths.pushBack(cellMap[pCurrent->getX() - 1][pCurrent->getY()]);
		}
	}
}