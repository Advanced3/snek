#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc)
{
	segments[0].InitHead(loc);
	for (int i = 1; i < nSegmentsMax; i++) {
		segments[i].InitBody(bodyColors[i % 5]);
	}
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax) {
		nSegments++;
	}
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; --i) {
		segments[i].Follow(segments[i-1]);
	}
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextLocation(const Location& delta_loc) const
{	
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments ; i++) {
		segments[i].Draw(brd);
	}
}

bool Snake::IsInTileExceptEnd(const Location& target) const
{
	for (int i = 0; i < nSegments - 1; i++) {
		if (segments[i].GetLocation() == target ) {
			return true;	
		}
	}
	return false;
}

bool Snake::IsInTile(const Location& target) const
{
	for (int i = 0; i < nSegments; i++) {
		if (segments[i].GetLocation() == target) {
			return true;
		}
	}
	return false;
}

void Snake::Segment::Follow(Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(const Color color)
{
	c = color;
}

void Snake::Segment::Draw(Board& brd) const
{	
	brd.DrawCell(loc, c);
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
