#include "MazeGen.hpp"

void MazeGenerator::displayMaze()
{
	for (auto row : maze)
	{
		for (auto col : row)
			std::cout << col << " ";
		std::cout << "\n";
	}
}

void MazeGenerator::displayCells()
{
	size_t k = 0;
	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < N; j++)
			if (cells[k].second.first == i && cells[k].second.second == j)
			{
				std::cout << "1 ";
				k++;
			}
			else
				std::cout << "0 ";

		std::cout << "\n";
	}
}

uint32_t MazeGenerator::getIdx(uint32_t x, uint32_t y, std::vector<std::pair<uint32_t, std::pair<uint32_t, uint32_t>>> cell_list)
{
	for (uint32_t i = 0; i < cell_list.size(); i++)
	{
		if (cell_list[i].second.first == x && cell_list[i].second.second == y)
			return cell_list[i].first;
	}
	std::cout << "getIdx() couldn't find the index!" << std::endl;
	return -1;
}

void MazeGenerator::createMaze()
{
	while (!m_stack.empty())
	{
		m_stack.pop();
	}

	// auto offset = [&](int x, int y) {
	//   return (m_stack.top().second.second + y) * M +
	//          (m_stack.top().second.first + x);
	// };

	startX = Random::RNG(m);
	startY = Random::RNG(n);
	longestPath = 0;
	maze.clear();
	cells.clear();
	visited.clear();

	maze.assign(M, std::vector<uint32_t>(N));
	visited.assign(m * n, false);
	uint32_t cellID = 0;

	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			if (!(i & 1) || !(j & 1))
				maze[i][j] = WALL;
			else
			{
				cells.push_back(std::make_pair(cellID, std::make_pair(i, j)));
				cellID++;
			}
		}
	}
	uint32_t exCell = startX * startY;
	m_stack.push(cells[exCell]);
	maze[cells[exCell].second.first][cells[exCell].second.second] = EXIT;
	visited[exCell] = true;
	visitedCells = 1;

	while (visitedCells < m * n)
	{
		// Step 1 : Create a set of unvisited neighbours
		std::vector<uint32_t> neighbours;
		// North Neighbour
		if (m_stack.top().second.first > 1)
		{
			if (!visited[getIdx(m_stack.top().second.first - 2,
								m_stack.top().second.second + 0, cells)])
			{
				neighbours.push_back(0);
			}
		}
		// East
		if (m_stack.top().second.second < N - 2)
		{
			if (!visited[getIdx(m_stack.top().second.first + 0,
								m_stack.top().second.second + 2, cells)])
			{
				neighbours.push_back(1);
			}
		}
		// South
		if (m_stack.top().second.first < M - 2)
		{
			if (!visited[getIdx(m_stack.top().second.first + 2,
								m_stack.top().second.second + 0, cells)])
			{
				neighbours.push_back(2);
			}
		}
		// West
		if (m_stack.top().second.second > 1)
		{
			if (!visited[getIdx(m_stack.top().second.first + 0,
								m_stack.top().second.second - 2, cells)])
			{
				neighbours.push_back(3);
			}
		}

		// Neighbours available?
		if (!neighbours.empty())
		{
			// Choose a random direction
			uint32_t next_cell_dir =
				neighbours[Random::RNG(neighbours.size() - 1)];
			// Create a path between this cell and neighbour
			switch (next_cell_dir)
			{
			case 0: // North
				maze[m_stack.top().second.first - 1]
					[m_stack.top().second.second + 0] = 0;
				m_stack.push(cells[getIdx(m_stack.top().second.first - 2,
										  m_stack.top().second.second + 0, cells)]);
				break;
			case 1: // East
				maze[m_stack.top().second.first + 0]
					[m_stack.top().second.second + 1] = 0;
				m_stack.push(cells[getIdx(m_stack.top().second.first + 0,
										  m_stack.top().second.second + 2, cells)]);
				break;
			case 2: // South
				maze[m_stack.top().second.first + 1]
					[m_stack.top().second.second + 0] = 0;
				m_stack.push(cells[getIdx(m_stack.top().second.first + 2,
										  m_stack.top().second.second + 0, cells)]);
				break;
			case 3: // West
				maze[m_stack.top().second.first + 0]
					[m_stack.top().second.second - 1] = 0;
				m_stack.push(cells[getIdx(m_stack.top().second.first + 0,
										  m_stack.top().second.second - 2, cells)]);
				break;
			}

			visited[m_stack.top().first] = true;
			visitedCells++;
			currentPath++;
		}
		else
		{
			if (currentPath > longestPath)
			{
				longestPath = currentPath;
				exit.first = m_stack.top().second.first;
				exit.second = m_stack.top().second.second;
			}
			currentPath = 0;
			m_stack.pop();
		}
	}
	maze[exit.first][exit.second] = ENTRANCE;
}

void MazeGenerator::printToFile()
{
	std::ofstream levelFile;
	levelFile.open("level");
	for (auto row : maze)
	{
		for (auto col : row)
			levelFile << col << " ";
		levelFile << "\n";
	}
}

std::vector<uint32_t> MazeGenerator::getArray()
{
	std::vector<uint32_t> mazeArr = {};
	mazeArr.reserve(M * N);
	for (auto row : maze)
	{
		for (auto col : row)
			mazeArr.push_back(col);
	}
	// mazeArr.shrink_to_fit();
	return mazeArr;
}