#pragma once
#include "Random.hpp"
#include "TileType.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <stack>
#include <vector>
class MazeGenerator
{
	static const uint32_t MAZE_WIDTH = 53;
	static const uint32_t MAZE_HEIGHT = 31;
	static const uint32_t n = MAZE_WIDTH / 2;
	static const uint32_t m = MAZE_HEIGHT / 2;
	static const uint32_t N = 2 * n + 1;
	static const uint32_t M = 2 * m + 1;

	uint32_t startX = Random::RNG(m);
	uint32_t startY = Random::RNG(n);

	std::pair<uint32_t, uint32_t> exit;

	std::vector<std::vector<uint32_t>> maze = {};

	uint32_t visitedCells = 0;

	std::vector<std::pair<uint32_t, std::pair<uint32_t, uint32_t>>> cells;
	std::vector<bool> visited;
	std::stack<std::pair<uint32_t, std::pair<uint32_t, uint32_t>>> m_stack;

	uint32_t currentPath = 0;
	uint32_t longestPath = 0;

public:

	uint32_t gibRandom() { return Random::RNG(M / 2 + 1); }

	void displayMaze();

	void displayCells();

	uint32_t getIdx(uint32_t x, uint32_t y, std::vector<std::pair<uint32_t, std::pair<uint32_t, uint32_t>>> cell_list);

	void createMaze();

	void printToFile();

	std::vector<uint32_t> getArray();
};