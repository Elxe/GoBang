#pragma once
#include "define.h"

Position AIDraw(int BoardPosition[][BOARDSIZE], int Flag);
int IfBans(int BoardPosition[][BOARDSIZE], int Flag, Position Coord, int Bans);