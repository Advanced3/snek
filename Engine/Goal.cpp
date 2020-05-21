#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snek)
{
	RespawnGoal(rng, brd, snek);
}

bool Goal::ProcessConsumption(const Location& in_loc) const
{
	return (loc.x == in_loc.x && loc.y == in_loc.y );
}

void Goal::RespawnGoal(std::mt19937& rng, const Board& brd, const Snake& snek)
{
	std::uniform_int_distribution<int> xDist(brd.GetBoardStartHeight(), brd.GetBoardWidth() - 1);
	std::uniform_int_distribution<int> yDist(brd.GetBoardStartWidth(), brd.GetBoardHeight() - 1);

	Location newLoc;
	do {
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snek.IsInTile(newLoc));
	loc = newLoc;
}

void Goal::DrawGoal(Board& brd) const
{
	brd.DrawCell(loc, c);
}
