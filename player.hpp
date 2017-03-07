#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <limits>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

	int evaluate_heuristic(Move *m, Side side, Side other, Board *cpy);
	int evaluate_minimax(Move *m, Side side, Side other, Board *cpy, int level);
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board * board;
    Side mySide;
};

#endif
