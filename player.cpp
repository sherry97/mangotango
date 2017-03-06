#include "player.hpp"

#define CORNER_BONUS 100

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    cerr << "Testing side: " << side << endl;
    board = new Board();
    mySide = side;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete board;
}

/*
 * @brief helper function to evaluate heuristic score of making given move
 * 
 * @param m move to make
 * @param side
 * 
 * @return int value of score of move
 */
int Player::evaluate(Move *m, Side side, Side other)
{
	Board *cpy = board->copy();
	cpy->doMove(m, side);
	int score = cpy->count(side) - cpy->count(other);
	score += CORNER_BONUS * (int(cpy->get(side, 0, 0)) + int(cpy->get(side, 7, 0)) 
		+ int(cpy->get(side, 0, 7)) + int(cpy->get(side, 7, 7)));
	delete cpy;
	return score;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {

    Side other = (mySide == BLACK) ? WHITE : BLACK;
	board->doMove(opponentsMove, other);
	
	Move *bestMove = new Move(-1, -1);
	int bestMoveScore = numeric_limits<int>::min();
	
	if (board->isDone())
	{
		return nullptr;
	}
	else if (board->hasMoves(mySide))
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Move *m = new Move(i, j);
				if (!board->checkMove(m, mySide))
				{
					continue;
				}
				int score = evaluate(m, mySide, other);
				if (score > bestMoveScore)
				{
					bestMoveScore = score;
					bestMove = m;
				}
			}
		}
	}
	
	if (bestMoveScore > numeric_limits<int>::min())
	{
		board->doMove(bestMove, mySide);
		return bestMove;
	}
	else
	{
		return nullptr;
	}
}
