/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
    :
    wnd(wnd),
    gfx(wnd),
    brd(gfx),
    snek({ 20, 15 }),
    rng(std::random_device()()),
    xDist(1, brd.GetBoardWidth() - 1),
    yDist(1, brd.GetBoardHeight() - 1),
    goal_loc({xDist(rng), yDist(rng)}),
    goal(rng, brd, snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    if (!gameIsStarted) {
        gameIsStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
    }
    if (!gameIsOver && gameIsStarted) {
        if (wnd.kbd.KeyIsPressed('W')) {
            if (delta_loc.y != 1) {
                delta_loc = { 0, -1 };
            }
        }
        else if (wnd.kbd.KeyIsPressed('S')) {
            if (delta_loc.y != -1) {
                delta_loc = { 0, 1 };
            }
        }
        else if (wnd.kbd.KeyIsPressed('D')) {
            if (delta_loc.x != -1) {
                delta_loc = { 1, 0 };
            }
        }
        else if (wnd.kbd.KeyIsPressed('A')) {
            if (delta_loc.x != 1) {
                delta_loc = { -1, 0 };
            }
        }
        snekMoveCounter++;
        if (snekMoveCounter == snekMovePeriod) {
            if (goalsEaten == 3) {
                snekMovePeriod--;
                goalsEaten = 0;
            }
            const Location next = snek.GetNextLocation(delta_loc);
            snekMoveCounter = 0;
            if (!brd.IsInsideBoard(next) || snek.IsInTileExceptEnd(next)) {
                gameIsOver = true;
            }
            else {
                const bool eating = goal.ProcessConsumption(next);
                if (goal.ProcessConsumption(next)) {
                    snek.Grow();
                    goalsEaten++;
                }
                snek.MoveBy(delta_loc);
                if (eating) {
                    goal.RespawnGoal(rng, brd, snek);
                }
            }
        }
    }
}

void Game::ComposeFrame()
{
    if (!gameIsStarted) {
        SpriteCodex::DrawTitle(gfx.ScreenWidth / 2 - 110, gfx.ScreenHeight / 2 - 100, gfx);
    }
    else {
        brd.DrawBorder();
        snek.Draw(brd);
        goal.DrawGoal(brd);
        if (gameIsOver) {
            SpriteCodex::DrawGameOver(gfx.ScreenWidth / 2 - 50, gfx.ScreenHeight / 2 - 50, gfx);
        }
    }
}
