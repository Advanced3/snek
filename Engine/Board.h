#pragma once
#include "Location.h"
#include "Graphics.h"

class Board {
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetBoardWidth() const;
	int GetBoardHeight() const;
	int GetBoardStartWidth() const;
	int GetBoardStartHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	void DrawBorder();
private:
	Graphics& gfx;
	static constexpr int startWidth = 2;
	static constexpr int startHeight = 2;
	static constexpr int width = 70 - startWidth;
	static constexpr int height = 45 - startHeight;
	static constexpr int dimension = 20;
};