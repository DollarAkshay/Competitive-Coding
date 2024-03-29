/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.hackerrank.com/challenges/mancala6

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
#define SIZE 6
#define CYCLE_SIZE 13 // SIZE*2 + 1

const double C = 1.20;
const char INIT_COUNT = 4;
const double SCORE_WIN = 1.0;
const int TIME_LIMIT = 1700 * (CLOCKS_PER_SEC / 1000); // 1700 ms

struct Move {
  public:
	int pos;
	bool getFreeTurn;

	Move() {
		pos = -1;
	}

	Move(int pos) {
		this->pos = pos;
	}

	Move(int pos, bool getFreeTurn) {
		this->pos = pos;
		this->getFreeTurn = getFreeTurn;
	}

	bool operator==(const struct Move rhs) const {
		return pos == rhs.pos;
	}
};

struct GameState {

  public:
	int playerId, opponentId;
	bool isPlayerTurn;

	// 0 is the hole farthest from the mancala
	// 5 is the hole closes to the mancala
	// 6 is the mancala.
	int board[2][SIZE + 1];
	int stonesInHoles[2];
	int winScoreDiff = 0;
	bool playerWinState, opponentWinState, drawState;

	struct Move moveList[SIZE];
	int moveCount = 0;

	GameState() {
		playerId = -1;
		opponentId = -1;
	}

	void init(int playerId, int boardState[2][SIZE + 1]) {
		playerWinState = false;
		opponentWinState = false;
		drawState = false;
		isPlayerTurn = true;
		this->playerId = playerId;
		opponentId = playerId == 0 ? 1 : 0;
		REP(i, 2) {
			REP(j, SIZE + 1) {
				board[i][j] += boardState[i][j];
				stonesInHoles[i] += boardState[i][j];
			}
			stonesInHoles[i] -= boardState[i][SIZE];
		}
	}

	// Check if a terminal state has been reached
	void checkTerminalState() {
		if (stonesInHoles[0] == 0 || stonesInHoles[1] == 0) {
			int playerStones = board[playerId][SIZE] + stonesInHoles[playerId];
			int opponentStones = board[opponentId][SIZE] + stonesInHoles[opponentId];
			winScoreDiff = playerStones - opponentStones;
			if (playerStones > opponentStones) {
				playerWinState = true;
			}
			else if (opponentStones > playerStones) {
				opponentWinState = true;
			}
			else {
				drawState = true;
			}
		}
	}

	// Do a move and return whether or not it is still the players turn
	bool doMove(struct Move move) {
		int pos = move.pos;
		int turnPlayerId = isPlayerTurn ? playerId : opponentId;
		int stones = board[turnPlayerId][pos];
		int sideId = turnPlayerId;

		board[sideId][pos] = 0;
		stonesInHoles[sideId] -= stones;
		pos++;

		while (stones > 0) {

			// Put stones in the holes
			while (pos <= SIZE - 1 && stones > 0) {
				board[sideId][pos] += 1;
				stonesInHoles[sideId] += 1;
				stones--;
				pos++;
			}

			// Put stones in the mancala
			if (sideId == turnPlayerId && stones > 0) {
				board[sideId][pos] += 1;
				stones--;
				pos++;
			}

			if (stones > 0) {
				sideId = !sideId;
				pos = 0;
			}
		}
		pos--;

		// If the last position played was the players mancala the he/she gets a free turn
		if (pos == SIZE) {
			checkTerminalState();
			return true;
		}

		// If the last position played was on your side and empty then transfer all the mancala form the other side to yours
		if (sideId == turnPlayerId && board[sideId][pos] == 1) {
			int stonesTransferCount = board[!sideId][SIZE - 1 - pos];
			board[sideId][pos] += stonesTransferCount;
			stonesInHoles[sideId] += stonesTransferCount;
			board[!sideId][SIZE - 1 - pos] = 0;
			stonesInHoles[!sideId] -= stonesTransferCount;
		}
		isPlayerTurn = !isPlayerTurn;
		checkTerminalState();
		return false;
	}

	// Generate moves for a given board state
	// Do not generate moves for a terminal state
	void generateMoves() {
		moveCount = 0;

		if (playerWinState == false && opponentWinState == false && drawState == false) {
			int turnId = isPlayerTurn ? playerId : opponentId;
			REP(i, SIZE) {
				if (board[turnId][i] > 0) {
					moveList[moveCount] = Move(i, board[turnId][i] % CYCLE_SIZE == SIZE - i);
					moveCount += 1;
				}
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
		generateMoves();
		doMove(moveList[fastrand() % moveCount]);
	}

	void displayBoard() {

		REP(i, SIZE + 2) {
			DB("+----");
		}
		DB("+\n");

		REP(i, SIZE + 2) {
			DB("|    ");
		}
		DB("|\n");

		DB("|    ");
		FORD(i, SIZE - 1, 0) {
			DB("| %2d ", board[1][i]);
		}
		DB("|    |\n");

		REP(i, SIZE + 2) {
			DB("|    ");
		}
		DB("|\n");

		DB("| %2d ", board[1][SIZE]);
		FOR(i, 1, SIZE) {
			DB("+----");
		}
		DB("| %2d ", board[0][SIZE]);
		DB("|\n");

		REP(i, SIZE + 2) {
			DB("|    ");
		}
		DB("|\n");

		DB("|    ");
		REP(i, SIZE) {
			DB("| %2d ", board[0][i]);
		}
		DB("|    |\n");

		REP(i, SIZE + 2) {
			DB("|    ");
		}
		DB("|\n");

		REP(i, SIZE + 2) {
			DB("+----");
		}
		DB("+\n\n\n");
	}
};

struct Node {
  public:
	double score;
	int visits;
	bool isPlayerNode;
	struct Move move;
	struct Node *firstChild;
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
		DB("Move     : %d %d\n", move.pos);
		DB("Children : %d\n", childCount);
	}

	inline double calcUCB(int parentVisits) {
		return visits == 0 ? 1E32 : score / visits + C * sqrt(log(parentVisits) / visits);
	}
};

// FILE *treeFp = fopen("D:\\Competitive_Coding\\data\\tree.json", "w+");
// FILE *fp = fopen("D:\\Competitive_Coding\\data\\data_6.csv", "w+");

int mctsIterations;
int nodesExpanded;
int simulationMoves;
int simulationWins;
int simulationLosses;
int backpropNodes;

int nodeCount;
vector<struct Node> tree(10000000);
struct Node *rootNode;

clock_t turnClock;

struct GameState game;

inline bool checkTime() {
	return clock() - turnClock >= TIME_LIMIT ? true : false;
}

// Write the tree state to a file
int debugTreeToFile(FILE *treeFp, struct Node *node, int parentId, int parentVisits, int id, int depth) {

	if (parentId < 0) {
		DB("Writing Tree ...");
		fprintf(treeFp, "[\n");
	}

	int curId = ++id;
	if (parentId != -1) {
		fprintf(treeFp, "  { \"nodeID\": %d, \"parentID\": %d, \"nodeType\": \"%c\", \"string\": \"%.2f/%d\",  \"UCBValue\": \"%.3f\" }, \n",
				curId, parentId, node->isPlayerNode ? 'P' : 'O', node->score, node->visits, node->calcUCB(parentVisits));
	}
	REP(i, node->childCount) {
		id = debugTreeToFile(treeFp, node->firstChild + i, curId, node->visits, id, depth + 1);
	}

	if (parentId < 0) {
		fprintf(treeFp, "  { \"nodeID\": %d, \"parentID\": null, \"nodeType\": \"%c\", \"string\": \"%.2f/%d\",  \"UCBValue\": \"%.3f\" }\n",
				curId, node->isPlayerNode ? 'P' : 'O', node->score, node->visits, node->calcUCB(parentVisits));
		fprintf(treeFp, "]\n");
		DB("Done\n");
		fflush(treeFp);
	}

	return id;
}

// Find a leaf node
struct Node *exploreTree(struct GameState &game, vector<int> &searchList) {

	struct Node *parent = rootNode;

	while (parent->childCount > 0) {
		searchList.push_back(parent - &tree[0]);
		//Find Maximum UCB
		double bestUCB = -1E32;
		int bestChildIndex = -1;
		REP(i, parent->childCount) {
			struct Node *child = parent->firstChild + i;
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
struct Node *expandNode(struct Node *nodePtr, struct GameState &game, vector<int> &searchList) {

	if (nodePtr->visits != 0 && nodePtr->childCount == -1) {
		game.generateMoves();
		nodePtr->childCount = game.moveCount;
		nodesExpanded += 1;
		if (nodePtr->childCount == 0) {
			return nodePtr;
		}
		nodePtr->firstChild = &tree[nodeCount];
		REP(i, game.moveCount) {
			tree[nodeCount].move = game.moveList[i];
			tree[nodeCount].isPlayerNode = game.isPlayerTurn;
			nodeCount += 1;
		}
		game.doMove(nodePtr->firstChild->move);
		searchList.push_back(nodePtr->firstChild - &tree[0]);
		return nodePtr->firstChild;
	}
	else {
		return nodePtr;
	}
}

// Simulate a set of random moves and return the score of the final state
int simulateRandomMoves(struct GameState &game) {

	int score = 0;
	while (game.playerWinState == false && game.opponentWinState == false && game.drawState == false) {
		simulationMoves += 1;
		game.doRandomMove();
		// game.displayBoard();
	}

	if (game.playerWinState) {
		score = SCORE_WIN + game.winScoreDiff * 0.1;
		simulationWins += 1;
	}
	else if (game.opponentWinState) {
		score = -SCORE_WIN + game.winScoreDiff * 0.1;
		simulationLosses += 1;
	}
	return score;
}

//Backpropogate the scores up the tree
void backPropogateScore(vector<int> &searchList, int simScore) {

	REP(i, searchList.size()) {
		tree[searchList[i]].visits += 1;
		tree[searchList[i]].score += tree[searchList[i]].isPlayerNode ? simScore : -simScore;
		backpropNodes += 1;
	}

	backpropNodes += 1;
}

void MCTSIteration(struct GameState game) {

	// long long int ns;
	// high_resolution_clock::time_point timer;
	vector<int> searchList;

	mctsIterations += 1;

	// Exploration
	// timer = high_resolution_clock::now();
	struct Node *nodePtr = exploreTree(game, searchList);
	// ns = duration_cast<nanoseconds>(high_resolution_clock::now() - timer).count();
	// fprintf(fp, "%lld,", ns);
	// DB("Explored\n");

	//Expansion
	// timer = high_resolution_clock::now();
	nodePtr = expandNode(nodePtr, game, searchList);
	// ns = duration_cast<nanoseconds>(high_resolution_clock::now() - timer).count();
	// fprintf(fp, "%lld,", ns);
	// DB("Expanded\n");

	//Simulate
	// timer = high_resolution_clock::now();
	int simScore = simulateRandomMoves(game);
	// ns = duration_cast<nanoseconds>(high_resolution_clock::now() - timer).count();
	// fprintf(fp, "%lld,", ns);
	// DB("Simulated\n");

	//Backpropogate
	// timer = high_resolution_clock::now();
	backPropogateScore(searchList, simScore);
	// ns = duration_cast<nanoseconds>(high_resolution_clock::now() - timer).count();
	// fprintf(fp, "%lld\n", ns);
	// DB("Backpropogated\n\n");
}

struct Move getBestMove() {

	mctsIterations = 0;
	nodesExpanded = 0;
	simulationMoves = 0;
	simulationWins = 0;
	simulationLosses = 0;
	backpropNodes = 0;

	// fprintf(fp, "search,expansion,simulation,backprop\n");
	while (!checkTime()) {
		REP(i, 100) {
			MCTSIteration(game);
		}
	}
	// fflush(fp);

	// debugTreeToFile(treeFp, rootNode, -1, 0, 0, 1);

	// Find the best move and return it
	double bestMoveScore = -1E32;
	struct Move bestMove;
	REP(i, rootNode->childCount) {
		struct Node *child = rootNode->firstChild + i;
		double curMoveScore = child->score / child->visits;
		if (curMoveScore > bestMoveScore) {
			bestMoveScore = curMoveScore;
			bestMove = child->move;
		}
	}
	return bestMove;
}

void printMove(struct Move &bestMove) {

	DB("Metrics : \n");
	DB("-----------------------------\n");
	DB("Time Taken        : %.2f ms\n", (double)1000 * (clock() - turnClock) / CLOCKS_PER_SEC);
	DB("MCTS Iterations   : %d\n", mctsIterations);
	DB("Nodes Expanded    : %d\n", nodesExpanded);
	DB("Simulation Moves  : %d\n", simulationMoves);
	DB("Simulation Wins   : %d\n", simulationWins);
	DB("Simulation Losses : %d\n", simulationLosses);
	DB("Backprop Nodes    : %d\n", backpropNodes);

	printf("%d\n", bestMove.pos + 1);
}

void readInput() {

	int playerId;
	int boardState[2][SIZE + 1];

	scanf("%d\n", &playerId);

	REP(i, 2) {
		scanf("%d", &boardState[i][SIZE]);
		REP(j, SIZE) {
			scanf("%d", &boardState[i][j]);
		}
	}

	game.init(playerId - 1, boardState);
	nodeCount = 0;
	rootNode = &tree[nodeCount];
	rootNode->visits = 1;
	rootNode->isPlayerNode = false;
	nodeCount += 1;
}

int main() {

	readInput();
	turnClock = clock();
	struct Move bestMove = getBestMove();
	printMove(bestMove);
	return 0;
}
