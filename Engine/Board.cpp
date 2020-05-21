#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{}

void Board::DrawCell(const Location & loc, Color c)
{
	gfx.DrawRectDim(loc.x * dimension + 1, loc.y * dimension + 1, dimension - 2, dimension - 2, c);
}

int Board::GetBoardWidth() const
{
	return width;
}

int Board::GetBoardHeight() const
{
	return height;
}

int Board::GetBoardStartWidth() const
{
	return startWidth;
}

int Board::GetBoardStartHeight() const
{
	return startHeight;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= startWidth && loc.x < width &&
		loc.y >= startHeight && loc.y < height;
}

void Board::DrawBorder()
{
	for (int x = dimension * startWidth - 5; x < dimension * width + 5; x++) {
		for (int y = dimension * startHeight - 5; y < dimension * height + 5; y++) {
			if (x <= (dimension * startWidth) || y <= (dimension * startHeight) || x >= (dimension * width) || y >= (dimension * height)) {
				gfx.PutPixel(x, y, { 0, 0, 200 });
			}
		}
	}
}

