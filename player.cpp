#include "player.hpp"

#define CORNER_BONUS 3
#define NEAR_CORNER_DEDUCTION -3
#define EDGE_BONUS 2
#define MINIMAX_SIM_DEPTH 2

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
int Player::evaluate_heuristic(Move *m, Side side, Side other, Board *cpy)
{
	cpy->doMove(m, side);
	int score = cpy->count(side) - cpy->count(other);
	score += CORNER_BONUS * (int(cpy->get(side, 0, 0)) + int(cpy->get(side, 7, 0)) 
		+ int(cpy->get(side, 0, 7)) + int(cpy->get(side, 7, 7)));
	for (int i = 0; i < 8; i++)
	{
		score += EDGE_BONUS * (int(cpy->get(side, 0, i)) + int(cpy->get(side, 7, i))
			+ int(cpy->get(side, i, 0)) + int(cpy->get(side, i, 7)));
	}
	score += NEAR_CORNER_DEDUCTION * (int(cpy->get(side, 0, 1))
		+ int(cpy->get(side, 1, 0)) + int(cpy->get(side, 1, 1)));
	score += NEAR_CORNER_DEDUCTION * (int(cpy->get(side, 0, 6))
		+ int(cpy->get(side, 1, 6)) + int(cpy->get(side, 1, 7)));
	score += NEAR_CORNER_DEDUCTION * (int(cpy->get(side, 6, 0))
		+ int(cpy->get(side, 6, 1)) + int(cpy->get(side, 7, 1)));
	score += NEAR_CORNER_DEDUCTION * (int(cpy->get(side, 6, 6))
		+ int(cpy->get(side, 6, 7)) + int(cpy->get(side, 7, 6)));
	delete cpy;
	return score;
}

/*
 * @brief minimax helper function to simulate next moves
 * 
 * @return minimum score possible
 */
int Player::evaluate_minimax(Move *m, Side side, Side other, Board *cpy, int level)
{
	cpy->doMove(m, side);
	if (level == 1)
	{
		return cpy->count(other) - cpy->count(side);
	}
	else
	{
		int minScore = numeric_limits<int>::max();
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Move *newMove = new Move(i, j);
				if (!cpy->checkMove(newMove, other))
				{
					continue;
				}
				int score = evaluate_minimax(newMove, other, side, cpy->copy(), level - 1);
				if (score < minScore)
				{
					minScore = score;
				}
			}
		}
		return minScore;
	}
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
	
	Move *bestMove = nullptr;
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
				int score;
				if (!testingMinimax)
					score = evaluate_heuristic(m, mySide, other, board->copy());
				else
					score = evaluate_minimax(m, mySide, other, board->copy(), MINIMAX_SIM_DEPTH);
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
