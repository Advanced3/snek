#pragma once
#include "Location.h"
#include "Colors.h"
#include "Board.h"

class Snake {
private:
	class Segment {
	public:
		void Follow(Segment& next);
		void InitHead(const Location& in_loc);
		void InitBody(const Color color);
		void Draw(Board& brd) const;
		void MoveBy(const Location& delta_loc);
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void Grow();
	void MoveBy(const Location& delta_loc);
	Location GetNextLocation(const Location& delta_loc) const;
	void Draw(Board& brd) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
private:
	static constexpr Color headColor = Colors::Red;
	static constexpr Color bodyColors[5] = { { 21, 255, 0 }, { 44, 230, 28 }, { 16, 207, 0 }, { 16, 171, 3 }, { 58, 199, 46 } };
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};