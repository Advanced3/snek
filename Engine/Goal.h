#pragma once
#include "Location.h"
#include "Colors.h"
#include "Board.h"
#include "Snake.h"
#include <random>

class Goal {
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snek);
	bool ProcessConsumption(const Location& in_loc) const;
	void RespawnGoal(std::mt19937& rng, const Board& brd, const Snake& snek);
	void DrawGoal(Board& brd) const;	
private:
	Location loc;	
	static constexpr Color c = Colors::White;	
};