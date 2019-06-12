/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.hackerrank.com/challenges/domineering/problem

#pragma GCC optimize("O3", "unroll-loops", "omit-frame-pointer", "inline")

#include <algorithm>
#include <assert.h>
#include <chrono>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <math.h>
#include <queue>
#include <random>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace std::chrono;

#define REP(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORD(i, a, b) for (int i = a; i >= b; --i)
#define DB(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define MSX(a, row) memset(a, row, sizeof(a))
#define SORT(a, n) sort(begin(a), begin(a) + n)
#define MOD 1000000007
#define DEBUG false
#define ull unsigned long long
#define ll long long
#define BOARD_SIDE 8
#define BOARD_SIZE 64

const double C = 0.8;
const char BLANK = '-';
const char PLAYER_V = 'v';
const char PLAYER_H = 'h';
const int TOKEN_ID_V = 0;
const int TOKEN_ID_H = 1;
const int TOKEN_ID_BOTH = 2;
const int SCORE_WIN = 1;
const int TIME_LIMIT = 1800 * (CLOCKS_PER_SEC / 1000); // 1500 ms

class Move {
  public:
	int index1, index2;

	Move() {
		index1 = -1;
		index2 = -1;
	}

	Move(int index, char token) {
		index1 = index;
		index2 = token == PLAYER_V ? index + BOARD_SIDE : index + 1;
	}

	int getX() {
		return index1 % BOARD_SIDE;
	}

	int getY() {
		return index1 / BOARD_SIDE;
	}

	bool operator==(const class Move rhs) const {
		return index1 == rhs.index1 && index2 == rhs.index2;
	}
};

class GameState {
  public:
	char player, opponent;
	int playerTokenId, opponentTokenId;
	bool isPlayerTurn;
	bool playerWinState, opponentWinState;
	class Move moveList[64];
	int moveCount = 0;

	// 0 = V
	// 1 = H
	// 2 = Both
	ull int board[3];
	ull int moves[2];

	GameState() {
		player = BLANK;
		opponent = BLANK;
		isPlayerTurn = false;
		MSX(board, 0);
		MSX(moves, 0);
	}

	// Initialize the game state
	void init(char playerToken, char boardState[BOARD_SIZE]) {

		playerWinState = false;
		opponentWinState = false;
		isPlayerTurn = true;

		if (playerToken == PLAYER_V) {
			this->player = PLAYER_V;
			this->opponent = PLAYER_H;
			playerTokenId = TOKEN_ID_V;
			opponentTokenId = TOKEN_ID_H;
		}
		else {
			this->player = PLAYER_H;
			this->opponent = PLAYER_V;
			playerTokenId = TOKEN_ID_H;
			opponentTokenId = TOKEN_ID_V;
		}

		// Make all moves possible
		moves[playerTokenId] = ~(moves[playerTokenId] & 0);
		moves[opponentTokenId] = ~(moves[opponentTokenId] & 0);

		REP(i, BOARD_SIZE) {
			int disallowMove = false;
			if (boardState[i] == player) {
				board[playerTokenId] |= 1LL << i;
				board[TOKEN_ID_BOTH] |= 1LL << i;
				disallowMove = true;
			}
			else if (boardState[i] == opponent) {
				board[opponentTokenId] |= 1LL << i;
				board[TOKEN_ID_BOTH] |= 1LL << i;
				disallowMove = true;
			}

			if (disallowMove == true) {
				moves[TOKEN_ID_V] &= ~(1LL << i);
				moves[TOKEN_ID_H] &= ~(1LL << i);

				if (i >= BOARD_SIDE) {
					moves[TOKEN_ID_V] &= ~(1LL << (i - BOARD_SIDE));
				}
				if (i % BOARD_SIDE > 0) {
					moves[TOKEN_ID_H] &= ~(1LL << (i - 1));
				}
			}
		}

		// Disallow Moves on the edges
		REP(i, BOARD_SIDE) {
			moves[TOKEN_ID_V] &= ~(1LL << (i + BOARD_SIZE - BOARD_SIDE));
			moves[TOKEN_ID_H] &= ~(1LL << ((i + 1) * BOARD_SIDE - 1));
		}
	}

	// If a player has a token at i then remove respective moves for both players
	inline void disallowMove(int i) {
		moves[TOKEN_ID_V] &= ~(1LL << i);
		moves[TOKEN_ID_H] &= ~(1LL << i);

		if (i >= BOARD_SIDE) {
			moves[TOKEN_ID_V] &= ~(1LL << (i - BOARD_SIDE));
		}
		if (i % BOARD_SIDE > 0) {
			moves[TOKEN_ID_H] &= ~(1LL << (i - 1));
		}
	}

	// Check if the game has reached a terminal state
	inline void checkTerminalState() {
		playerWinState = !isPlayerTurn && moves[opponentTokenId] == 0 ? true : false;
		opponentWinState = isPlayerTurn && moves[playerTokenId] == 0 ? true : false;
	}

	// Make a move on the board
	void doMove(class Move &move) {
		int tokenId = isPlayerTurn ? playerTokenId : opponentTokenId;
		board[tokenId] |= 1LL << move.index1;
		board[tokenId] |= 1LL << move.index2;
		board[TOKEN_ID_BOTH] |= 1LL << move.index1;
		board[TOKEN_ID_BOTH] |= 1LL << move.index2;
		disallowMove(move.index1);
		disallowMove(move.index2);
		isPlayerTurn = !isPlayerTurn;
		checkTerminalState();
	}

	// Generate moves for a given board state
	void generateMoves() {
		moveCount = 0;
		int token = isPlayerTurn ? player : opponent;
		int tokenId = isPlayerTurn ? playerTokenId : opponentTokenId;

		REP(i, BOARD_SIZE) {
			if (moves[tokenId] & (1LL << i)) {
				moveList[moveCount] = Move(i, token);
				moveCount += 1;
			}
		}
	}

	inline int fastrand() {
		static unsigned int g_seed = 42;
		g_seed = (214013 * g_seed + 2531011);
		return (g_seed >> 16) & 0x7FFF;
	}

	// Generate moves and do a random move
	void doRandomMove() {

		moveCount = 0;
		int token = isPlayerTurn ? player : opponent;
		int tokenId = isPlayerTurn ? playerTokenId : opponentTokenId;

		REP(i, BOARD_SIZE) {
			if (moves[tokenId] & (1LL << i)) {
				moveList[moveCount] = Move(i, token);
				moveCount += 1;
			}
		}

		doMove(moveList[fastrand() % moveCount]);
	}
};

class Node {
  public:
	int score;
	int visits;
	class Move move;
	class Node *firstChild;
	int childCount;

	Node() {
		score = 0;
		visits = 0;
		firstChild = NULL;
		childCount = -1;
	}

	void debug() {
		DB("Node : \n");
		DB("S/V      : %d/%d\n", score, visits);
		DB("Move     : %d %d\n", move.index1, move.index2);
		DB("Children : %d\n", childCount);
	}

	inline double calcUCB(int parentVisits) {
		if (visits == 0) {
			return 1E32;
		}
		return (double)score / visits + C * sqrt((double)log(parentVisits) / visits);
	}
};

FILE *treeFp = fopen("D:\\Competitive_Coding\\data\\tree_small.json", "w+");
FILE *fp = fopen("D:\\Competitive_Coding\\data\\data_1.csv", "w+");

int mctsIterations;
int nodesExpanded;
int simulationMoves;
int simulationWins;
int simulationLosses;
int backpropNodes;

int nodeCount;
vector<class Node> tree(10000000);
class Node *rootNode;

clock_t turnClock;

class GameState game;

inline bool checkTime() {
	return clock() - turnClock >= TIME_LIMIT ? true : false;
}

// Write the tree state to a file
int debugTreeToFile(FILE *treeFp, class Node *node, int parentId, int id, int depth) {

	if (parentId < 0) {
		DB("Writing Tree ...");
		fprintf(treeFp, "[\n");
	}

	int curId = ++id;
	if (parentId != -1) {
		fprintf(treeFp, "  { \"nodeID\": %d, \"parentID\": %d, \"nodeType\": \"%c\", \"string\": \"%d/%d\" }, \n", curId, parentId, depth % 2 == 0 ? 'O' : 'P', node->score, node->visits);
	}
	REP(i, node->childCount) {
		id = debugTreeToFile(treeFp, node->firstChild + i, curId, id, depth + 1);
	}

	if (parentId < 0) {
		fprintf(treeFp, "  { \"nodeID\": %d, \"parentID\": null, \"nodeType\": \"%c\", \"string\": \"%d/%d\" }\n", curId, depth % 2 == 0 ? 'O' : 'P', node->score, node->visits);
		fprintf(treeFp, "]\n");
		DB("Done\n");
		fflush(treeFp);
	}

	return id;
}

// Find a leaf node
class Node *exploreTree(class GameState &game, vector<int> &searchList) {

	class Node *parent = rootNode;

	while (parent->childCount > 0) {
		searchList.push_back(parent - &tree[0]);
		//Find Maximum UCB
		double bestUCB = -1E32;
		int bestChildIndex = -1;
		REP(i, parent->childCount) {
			class Node *child = parent->firstChild + i;
			double curUCB = child->calcUCB(parent->visits);
			if (curUCB > bestUCB) {
				bestUCB = curUCB;
				bestChildIndex = i;
			}
		}
		parent = parent->firstChild + bestChildIndex;
		game.doMove(parent->move);
	}

	searchList.push_back(parent - &tree[0]);
	return parent;
}

// If a given node has already been visited atleast once
// expand the node by finding its children and choosing one of them
class Node *expandNode(class Node *nodePtr, class GameState &game) {

	if (nodePtr->visits != 0 && nodePtr->childCount == -1) {
		game.generateMoves();
		nodePtr->childCount = game.moveCount;
		if (nodePtr->childCount == 0) {
			return nodePtr;
		}
		nodePtr->firstChild = &tree[nodeCount];
		REP(i, game.moveCount) {
			tree[nodeCount].move = game.moveList[i];
			nodeCount += 1;
			nodesExpanded += 1;
		}
		game.doMove(nodePtr->firstChild->move);
		return nodePtr->firstChild;
	}
	else {
		return nodePtr;
	}
}

// Simulate a set of random moves and return the score of the final state
int simulateRandomMoves(class GameState &game) {

	int score = 0;
	while (game.playerWinState == false && game.opponentWinState == false) {
		simulationMoves += 1;
		game.doRandomMove();
	}

	if (game.playerWinState) {
		score += SCORE_WIN;
		simulationWins += 1;
	}
	else if (game.opponentWinState) {
		score -= SCORE_WIN;
		simulationLosses += 1;
	}
	return score;
}

//Backpropogate the scores up the tree
void backPropogateScore(vector<int> &searchList, int simScore) {

	simScore = -simScore;
	REP(i, searchList.size()) {
		tree[searchList[i]].visits += 1;
		tree[searchList[i]].score += simScore;
		simScore = -simScore;
		backpropNodes += 1;
	}

	backpropNodes += 1;
}

void MCTSIteration(class GameState game) {

	long long int ns;
	high_resolution_clock::time_point timer;
	vector<int> searchList;

	mctsIterations += 1;

	// Exploration
	timer = high_resolution_clock::now();
	class Node *nodePtr = exploreTree(game, searchList);
	ns = duration_cast<nanoseconds>(high_resolution_clock::now() - timer).count();
	fprintf(fp, "%lld,", ns);
	// DB("Explored\n");

	//Expansion
	timer = high_resolution_clock::now();
	nodePtr = expandNode(nodePtr, game);
	ns = duration_cast<nanoseconds>(high_resolution_clock::now() - timer).count();
	fprintf(fp, "%lld,", ns);
	// DB("Expanded\n");

	//Simulate
	timer = high_resolution_clock::now();
	int simScore = simulateRandomMoves(game);
	ns = duration_cast<nanoseconds>(high_resolution_clock::now() - timer).count();
	fprintf(fp, "%lld,", ns);
	// DB("Simulated\n");

	//Backpropogate
	timer = high_resolution_clock::now();
	backPropogateScore(searchList, simScore);
	ns = duration_cast<nanoseconds>(high_resolution_clock::now() - timer).count();
	fprintf(fp, "%lld\n", ns);
	// DB("Backpropogated\n");
}

class Move getBestMove() {

	mctsIterations = 0;
	nodesExpanded = 0;
	simulationMoves = 0;
	simulationWins = 0;
	simulationLosses = 0;
	backpropNodes = 0;

	fprintf(fp, "search,expansion,simulation,backprop\n");
	// while (!checkTime()) {
	REP(i, 1000000) {
		MCTSIteration(game);
	}
	// }
	fflush(fp);

	// debugTreeToFile(treeFp, rootNode, -1, 0, 1);

	// Find the best move and return it
	int bestMoveScore = 0;
	class Move bestMove;
	REP(i, rootNode->childCount) {
		class Node *child = rootNode->firstChild + i;
		int curMoveScore = child->visits;
		if (curMoveScore > bestMoveScore) {
			bestMoveScore = curMoveScore;
			bestMove = child->move;
		}
	}
	return bestMove;
}

void printMove(class Move &bestMove) {

	DB("Metrics : \n");
	DB("-----------------------------\n");
	DB("Time Taken        : %.2f ms\n", (double)1000 * (clock() - turnClock) / CLOCKS_PER_SEC);
	DB("MCTS Iterations   : %d\n", mctsIterations);
	DB("Nodes Expanded    : %d\n", nodesExpanded);
	DB("Simulation Moves  : %d\n", simulationMoves);
	DB("Simulation Wins   : %d\n", simulationWins);
	DB("Simulation Losses : %d\n", simulationLosses);
	DB("Backprop Nodes    : %d\n", backpropNodes);

	printf("%d %d\n", bestMove.getY(), bestMove.getX());
}

void readInput() {

	char playerToken;
	char boardState[BOARD_SIZE];

	scanf("%c\n", &playerToken);
	REP(i, BOARD_SIDE) {
		char row[BOARD_SIDE + 1];
		scanf("%s", &row);
		REP(j, BOARD_SIDE) {
			boardState[i * BOARD_SIDE + j] = row[j];
		}
	}

	game.init(playerToken, boardState);
	nodeCount = 0;
	rootNode = &tree[nodeCount];
	rootNode->visits = 1;
	nodeCount += 1;
}

int main() {
	turnClock = clock();
	readInput();
	class Move bestMove = getBestMove();
	printMove(bestMove);
	return 0;
}