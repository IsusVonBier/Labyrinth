#pragma once
#include <random>
class Random
{
	Random() {}
	std::random_device rd;
	uint32_t randomize(uint32_t a, uint32_t b)
	{
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(a, b);
		return distrib(gen);
	}

public:
	Random(const Random &) = delete;
	static Random &Get()
	{
		static Random instance;
		return instance;
	}
	static uint32_t RNG() { return Get().randomize(0, INT32_MAX); }
	static uint32_t RNG(uint32_t a) { return Get().randomize(0, a); }
};