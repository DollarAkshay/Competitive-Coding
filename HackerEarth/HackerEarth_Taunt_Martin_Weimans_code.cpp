#include <bits/stdc++.h>
#define COLOR 1
#define YELLOW 0
#define GREEN 1

#define TYPE 6
#define BACKER 0
#define FRONTER 2
#define DIAGONAL 4

#define DIRECTION 8
#define DOWN 0
#define UP 8

#define EMPTY 16

//#define DEBUG_POLICY
//#define DEBUG_PRINT
#define DEBUG_ERROR
#define INF 1000000000
#define BOARD_SIZE 8

using namespace std;

#define rep(i, a, b) for (int i = (a); i < int(b); ++i)
#define rrep(i, a, b) for (int i = (a)-1; i >= int(b); --i)
#define trav(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()
#define sz(x) (int)(x).size()

typedef double fl;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;

FILE *recordMoveFile;

fl *alloc(int size) {
	return (fl *)_mm_malloc(sizeof(fl) * size, 32);
}

int numEvalsSaved;
int depthSaved;
int lowerBoundsSaved;
int forbidden[8][8];
int tmpBoard[8][8];
int doTranspose;
int dx[4] = {1, 1, -1, -1};
int dy[4] = {-1, 1, 1, -1};
bool tuning = false;
bool makingMassiveStats = false;
bool doMassiveSearch;
float playerExplorationCoefficient[2];
unordered_map<ll, pair<float, ll>> massiveStats;
int iterMod;
float timeFactor = 1;
int massiveIterationCount = 20000;
bool recordMove = false;
int prunedUsingBounds;
int earlyGameValues;
bool curTurn;
int winProbToWeight[10000];
bool responsibleMemoryUsage = false;
int maxDepth;
int depth;
int rolloutIterations;
bool printEvalOutput = false;
clock_t startTime;
bool aborted;
int statesDone;
ll totalStatesDone[2];
ll totalMillisUsed[2];
int checkTime;
int pseudoRandomVal;
// Value of a draw for second player
float drawValue = 0.5;
bool generateOpeningBook = false;
int reusedNodes;
int newNodes;
int threats[10][4][2];

char openings[] = "";

struct Bot {
	float backerValue;
	float fronterValue;
	float diagonalValue;
	bool useThreatAnalysis;
	bool useFancyEval;
	bool quiescenceSearch;
	float positionScore;
	bool uniformlyRandom;
	bool randomizeTimeLimit;
	bool replaceSmallNode;
	bool probCutSmallDepthBonus;
	bool checkEnded;
	bool useStrength;
	bool simpleEval;
	bool ABCompleteAllSearches;
	bool preferUnfinishedLayers;
	float ABMCTSProbCutCoefficient;
	bool useABMCTSProbCut;
	bool fancyABOrderMoves;
	bool useFuzzyPreweight;
	int fuzzyPreweightN;
	bool useFuzzyEval2;
	int fancyABMaxDepth;
	bool useFileParams;
	bool useMTDf;
	bool useOldEval;
	bool useBestMove2;
	bool useFancyAB;
	bool useProbCut;
	float probCutExponential;
	float probCutCoefficient;
	float linearProbCutCoefficient;
	int safeProbCutCoefficient;
	int subtreeExploreNumber;
	int maxStatesCheck;
	bool useMiniMaxForLargeN;
	bool useExclusion;
	bool useBounds;
	bool useEffectiveN;
	bool useHashMap;
	bool stayInSubtree;
	bool useOpeningBook;
	bool useAlphaBeta;
	bool useMCTS;
	bool MCTSUseEval;
	bool MCTSChooseBestScore;
	bool undoMovesDuringRollout;
	bool usePseudoRandom;
	bool completeSearchTree;
	bool rolloutFindWinning;
	bool useAccurateRollout;
	bool setLeafUsingRollout;
	bool useTimeManagement;
	bool timeSaveForEnd;
	bool MCTSWeightLeaves;
	bool ucb1Tuned;
	bool checkBoundAdvanced;
	bool expandAllChildren;
	float explorationCoefficient;
	float explorationCoefficientLowDepth;
	string name;
	float timeLimit;
	float baseTimeLimit;
	float timeEvenCoefficient;
	float timeEvenExponentCoefficient;
	int heuristicDoneValue;
	bool alternativeProbCut;
	bool isHuman;

	Bot() {}

	Bot(string _name) {
		backerValue = 0.5f;
		fronterValue = 0.6f;
		diagonalValue = 0.7f;
		useThreatAnalysis = false;
		useFancyEval = false;
		quiescenceSearch = false;
		positionScore = 0;
		uniformlyRandom = false;
		randomizeTimeLimit = false;
		replaceSmallNode = false;
		probCutSmallDepthBonus = 0;
		useStrength = false;
		checkEnded = false;
		simpleEval = false;
		ABCompleteAllSearches = false;
		preferUnfinishedLayers = false;
		useABMCTSProbCut = false;
		ABMCTSProbCutCoefficient = 15000;
		fancyABOrderMoves = false;
		useFuzzyPreweight = false;
		fuzzyPreweightN = 0;
		useFuzzyEval2 = false;
		fancyABMaxDepth = 100;
		isHuman = false;
		linearProbCutCoefficient = 0;
		useFileParams = false;
		useMTDf = false;
		useOldEval = false;
		useProbCut = false;
		alternativeProbCut = false;
		useBestMove2 = false;
		useFancyAB = false;
		probCutCoefficient = 1000;
		safeProbCutCoefficient = 10000;
		probCutExponential = 1;
		useMiniMaxForLargeN = false;
		subtreeExploreNumber = 1;
		maxStatesCheck = 5000;
		timeLimit = 0.7;
		baseTimeLimit = 0.15;
		timeEvenCoefficient = 1.6;
		timeEvenExponentCoefficient = 0.5;
		name = _name;
		useExclusion = false;
		useBounds = false;
		useEffectiveN = false;
		useHashMap = false;
		stayInSubtree = false;
		useOpeningBook = false;
		useAlphaBeta = true;
		useMCTS = false;
		MCTSUseEval = false;
		MCTSChooseBestScore = false;
		undoMovesDuringRollout = true;
		usePseudoRandom = false;
		completeSearchTree = false;
		rolloutFindWinning = false;
		useAccurateRollout = false;
		setLeafUsingRollout = false;
		useTimeManagement = false;
		MCTSWeightLeaves = false;
		ucb1Tuned = false;
		expandAllChildren = false;
		timeSaveForEnd = false;
		explorationCoefficient = sqrt(2);
		explorationCoefficientLowDepth = -1;
		heuristicDoneValue = 10;
	}

} bot;

struct Tensor {
	vector<Tensor> c;
	fl *c2 = 0;
	int num;

	Tensor() : c2(0), num(0) {}
	Tensor(const Tensor &) = delete;
	~Tensor() {
		if (c2)
			_mm_free(c2);
	}
	Tensor(Tensor &&other) {
		c = move(other.c);
		c2 = other.c2;
		other.c2 = 0;
		num = other.num;
	}
	Tensor &operator=(Tensor &&other) {
		c = move(other.c);
		c2 = other.c2;
		other.c2 = 0;
		num = other.num;
		return *this;
	}
	Tensor(int size) : num(size) {
		c2 = alloc(size);
	}

	void read(stringstream *fin, int rank) {
		if (rank == 2 && doTranspose) {
			int num1, num2;
			(*fin) >> num1 >> num2;
			assert(num1);
			c.reserve(num2);
			rep(i, 0, num2) {
				c.emplace_back(num1);
			}
			this->num = num2;
			rep(i, 0, num1) {
				int num3;
				if (i) {
					(*fin) >> num3;
					assert(num3 == num2);
				}
				rep(j, 0, num2) {
					fl val;
					(*fin) >> val;
					c[j].c2[i] = val;
				}
			}
			return;
		}
		(*fin) >> num;
		if (rank == 1) {
			c2 = alloc(num);
			rep(i, 0, num)(*fin) >> c2[i];
			return;
		}
		c.reserve(num);
		rep(i, 0, num) {
			c.emplace_back();
			c.back().read(fin, rank - 1);
		}
	}

	void print() {
		printf("[");
		if (c2) {
			rep(i, 0, num) {
				if (c2[i] == 0)
					printf("0");
				else
					printf("%.4f", c2[i]);
				if (i != num - 1)
					printf(", ");
			}
		}
		else {
			rep(i, 0, c.size()) {
				c[i].print();
				if (i != sz(c) - 1)
					printf(", ");
			}
		}
		printf("]");
	}

	Tensor operator+(const Tensor &other) const {
		if (c2) {
			assert(num == other.num);
			Tensor ret(num);
			rep(i, 0, num) {
				ret.c2[i] = c2[i] + other.c2[i];
			}
			return ret;
		}
		assert(other.c.size() == c.size());
		Tensor ret;
		rep(i, 0, sz(c)) {
			ret.c.push_back(c[i] + other.c[i]);
		}
		return ret;
	}

	Tensor elu() {
		if (c2) {
			int size = num;
			Tensor ret(size);
			int i = 0;
			while (i < size) {
				if (c2[i] > 0)
					ret.c2[i] = c2[i];
				else
					ret.c2[i] = exp(c2[i]) - 1;
				i++;
			}
			return ret;
		}
		Tensor ret;
		rep(i, 0, c.size()) {
			ret.c.push_back(c[i].elu());
		}
		return ret;
	}

	Tensor sigmoid() {
		if (c2) {
			Tensor ret(num);
			rep(i, 0, num) {
				ret.c2[i] = 1.0f / (1.0f + exp(-c2[i]));
			}
			return ret;
		}
		Tensor ret;
		rep(i, 0, c.size()) {
			ret.c.push_back(c[i].sigmoid());
		}
		return ret;
	}
};

Tensor readTensor(stringstream *fin) {
	string name;
	int rank;
	(*fin) >> name >> rank;
	Tensor ret;
	ret.read(fin, rank);
	return ret;
}

void printPos(int x, int y) {
	printf("%c%d", 'a' + y, x + 1);
}

struct Move {
	int x, y;
	int tox, toy;

	Move() {
	}

	Move(int _x, int _y, int _tox, int _toy) {
		x = _x;
		y = _y;
		tox = _tox;
		toy = _toy;
	}

	bool operator<(const Move &other) const {
		if (x != other.x)
			return x < other.x;
		if (y != other.y)
			return y < other.y;
		if (tox != other.tox)
			return tox < other.tox;
		if (toy != other.toy)
			return toy < other.toy;
		return 0;
	}

	bool operator==(const Move &other) const {
		return !((*this) < other || other < (*this));
	}

	bool operator!=(const Move &other) const {
		return !((*this) == other);
	}

	void print() {
		printf("%d %d\n", x, y);
		printf("%d %d\n", tox, toy);
	}

	void printUgly() {
		print();
	}
};

map<ll, Move> openingMove;

float gamePart[4];
float partCoefficient[120][3];
float threatValue[3];
float posval[3][480];
float backerValue[3];
float fronterValue[3];
float diagonalValue[3];
float centerBackerValue[3];
float centerFronterValue[3];
float centerDiagonalValue[3];

void createOpeningBook() {
}

void computeEvalHelpers() {
	rep(i, 0, 120) {
		double x = (gamePart[1] * 100 - i) / (gamePart[1] * 100 - gamePart[0]);
		if (x < 0 || x > 1)
			partCoefficient[i][0] = 0;
		else
			partCoefficient[i][0] = x * x * (3 - 2 * x);
		x = (gamePart[1] * 100 - i) / (gamePart[1] * 100 - gamePart[3]);
		if (x < 0 || x > 1)
			partCoefficient[i][2] = 0;
		else
			partCoefficient[i][2] = x * x * (3 - 2 * x);
		partCoefficient[i][1] = 1 - partCoefficient[i][0] - partCoefficient[i][2];
	}
}

void initEvalConstants() {
	gamePart[0] = -1.0;
	gamePart[1] = 0.244973;
	gamePart[2] = -1.0;
	gamePart[3] = 110.0;
	threatValue[0] = 0.0;
	backerValue[0] = 1.27824;
	fronterValue[0] = 1.33292;
	diagonalValue[0] = 1.18229;
	centerBackerValue[0] = -0.0741023;
	centerFronterValue[0] = 0.0436772;
	centerDiagonalValue[0] = 0.360549;
	threatValue[1] = 0.0;
	backerValue[1] = 1.5286;
	fronterValue[1] = 1.63786;
	diagonalValue[1] = 1.34976;
	centerBackerValue[1] = 0.100066;
	centerFronterValue[1] = 0.0745716;
	centerDiagonalValue[1] = 0.200393;
	threatValue[2] = 0.0;
	backerValue[2] = 0.583351;
	fronterValue[2] = 1.33117;
	diagonalValue[2] = 1.22381;
	centerBackerValue[2] = -0.330157;
	centerFronterValue[2] = -0.0624622;
	centerDiagonalValue[2] = -0.0354921;
	computeEvalHelpers();
}

char *fileNameConstants;

void initFileConstants() {
	FILE *fin = fopen(fileNameConstants, "r");
	ignore = fscanf(fin, "%f", &bot.backerValue);
	ignore = fscanf(fin, "%f", &bot.fronterValue);
	ignore = fscanf(fin, "%f", &bot.diagonalValue);
	fclose(fin);
}

float sigmoid(float x) {
	return 1.0 / (1.0 + exp(-x));
}

/*float tanh(float x){
	float tmp=exp(-2*x);
	return (1.0-tmp)/(1.0+tmp);
}*/

struct State {
	char f[10][4];
	int turn;
	int turnNumber;

	void init() {
		turnNumber = 0;
		turn = 0;
		rep(i, 0, 10)
			rep(j, 0, 4) {
			f[i][j] = EMPTY;
		}
		f[0][0] = YELLOW | DIAGONAL | DOWN;
		f[0][1] = YELLOW | DIAGONAL | DOWN;
		f[0][2] = YELLOW | DIAGONAL | DOWN;
		f[0][3] = YELLOW | FRONTER | DOWN;
		f[1][0] = YELLOW | FRONTER | DOWN;
		f[1][1] = YELLOW | FRONTER | DOWN;
		f[1][2] = YELLOW | BACKER;
		f[1][3] = YELLOW | BACKER;
		f[2][0] = YELLOW | BACKER;
		f[9][3] = GREEN | DIAGONAL | UP;
		f[9][2] = GREEN | DIAGONAL | UP;
		f[9][1] = GREEN | DIAGONAL | UP;
		f[9][0] = GREEN | FRONTER | UP;
		f[8][3] = GREEN | FRONTER | UP;
		f[8][2] = GREEN | FRONTER | UP;
		f[8][1] = GREEN | BACKER;
		f[8][0] = GREEN | BACKER;
		f[7][3] = GREEN | BACKER;
	}

	vector<Move> getMoves() {
		if (turnNumber >= 100) {
			vector<Move> ret;
			Move move;
			move.x = -1;
			move.y = -1;
			ret.push_back(move);
			return ret;
		}
		vector<Move> ret;
		rep(i, 0, 10)
			rep(j, 0, 4) {
			if (f[i][j] & EMPTY)
				continue;
			if ((f[i][j] & COLOR) != turn)
				continue;
			switch (f[i][j] & TYPE) {
			case BACKER: {
				int dx[4] = {-1, 0, 1, 0};
				int dy[4] = {0, 1, 0, -1};
				rep(k, 0, 4) {
					int x = i + dx[k];
					int y = j + dy[k];
					if (x < 0 || y < 0 || x >= 10 || y >= 4)
						continue;
					if (!(f[x][y] & EMPTY) && (f[x][y] & COLOR) == (f[i][j] & COLOR))
						continue;
					ret.emplace_back(i, j, x, y);
				}
				break;
			}
			case FRONTER: {
				int d = (f[i][j] & DIRECTION) == DOWN ? 1 : -1;
				int dx[4] = {2 * d, 0, 0};
				int dy[4] = {0, 1, -1};
				if (i + dx[0] == -1 || i + dx[0] == 10)
					dx[0] = 0;
				rep(k, 0, 3) {
					int x = i + dx[k];
					int y = j + dy[k];
					if (x < 0 || y < 0 || x >= 10 || y >= 4)
						continue;
					if (!(f[x][y] & EMPTY) && (f[x][y] & COLOR) == (f[i][j] & COLOR) &&
						(dx[k] || dy[k]))
						continue;
					ret.emplace_back(i, j, x, y);
				}
				break;
			}
			case DIAGONAL: {
				int d = (f[i][j] & DIRECTION) == DOWN ? 1 : -1;
				int dx[3] = {2 * d, 2 * d, 2 * d};
				int dy[3] = {-2, 0, 2};
				rep(k, 0, 3) {
					int x = i + dx[k];
					int y = j + dy[k];
					if (y == j && (y == 0 || y == 3))
						continue;
					if (x == -1 || x == 10)
						x = i;
					if (x < 0 || y < 0 || x >= 10 || y >= 4)
						continue;
					if (!(f[x][y] & EMPTY) && (f[x][y] & COLOR) == (f[i][j] & COLOR) &&
						(x != i || y != j))
						continue;
					ret.emplace_back(i, j, x, y);
				}
				break;
			}
			}
		}
		if (ret.empty()) {
			Move move;
			move.x = -1;
			move.y = -1;
			ret.push_back(move);
		}
		return ret;
	}

	bool performMove(Move move) {
		if (move.x < 0) {
			return false;
		}
		bool isCapture = false;
		char piece = f[move.x][move.y];
		if (f[move.x][move.y] != EMPTY) {
			f[move.x][move.y] = EMPTY;
			isCapture = true;
		}
		int midx = (move.x + move.tox) / 2;
		int midy = (move.y + move.toy) / 2;
		if ((piece & TYPE) == DIAGONAL) {
			if (midy == move.y) {
				if (midy == 1)
					midy--;
				else
					midy++;
			}
			if (midx == move.x) {
				if (midx == 1)
					midx--;
				else
					midx++;
			}
		}
		if ((piece & TYPE) == FRONTER) {
			if (midx == move.x && move.toy == move.y) {
				if (midx == 1)
					midx--;
				else {
					assert(midx == 8);
					midx++;
				}
			}
		}
		if ((f[midx][midy] & COLOR) != (piece & COLOR) && f[midx][midy] != EMPTY) {
			f[midx][midy] = EMPTY;
			isCapture = true;
		}
		f[move.tox][move.toy] = piece;
		if ((move.tox == 0 || move.tox == 9) && move.tox != move.x)
			f[move.tox][move.toy] ^= DIRECTION;
		else if (move.tox == move.x && move.toy % 2 == move.y % 2)
			f[move.tox][move.toy] ^= DIRECTION;
		turn ^= 1;
		turnNumber++;
		return isCapture;
	}

	void print(int indent) {
		printf("Turn %d\n", turnNumber);
		rep(j, 0, indent)
			printf("  ");
		rep(j, 0, 11)
			printf("_");
		printf("\n");
		rep(i, 0, 10) {
			rep(j, 0, indent)
				printf("  ");
			printf("|");
			rep(j, 0, 4) {
				char c = f[i][j];
				if (c & EMPTY) {
					printf("  ");
					continue;
				}
				else if ((c & COLOR) == YELLOW)
					cout << "\033[31m";
				else
					cout << "\033[32m";
				if ((c & TYPE) == BACKER)
					cout << "◎ ";
				else if ((c & TYPE) == FRONTER)
					cout << "◍ ";
				else if ((c & TYPE) == DIAGONAL)
					cout << "◉ ";
				cout << "\033[39m";
			}
			printf("|");
			printf("\n");
		}
		rep(j, 0, indent)
			printf("  ");
		rep(j, 0, 11) {
			printf("‾");
		}
		printf("\n");
	}

	void printUgly(FILE *fout) {
		rep(i, 0, 10) {
			rep(j, 0, 4) {
				int c = f[i][j];
				fprintf(fout, "%d ", c);
			}
			fprintf(fout, "\n");
		}
		fprintf(fout, "%d\n", (int)turn);
		fprintf(fout, "%d\n", (int)turnNumber);
	}

	void print() {
		print(0);
	}

	int fuzzyEval() {
		//print();
		float ret = 0;
		float timeCoefficient[3];
		rep(partIndex, 0, 3) {
			timeCoefficient[partIndex] = partCoefficient[100 - turnNumber][partIndex];
		}
		if (bot.useThreatAnalysis) {
			rep(i, 0, 10)
				rep(j, 0, 4) {
				threats[i][j][0] = 0;
				threats[i][j][1] = 0;
			}
			int numMoves[2] = {0, 0};
			rep(i, 0, 10)
				rep(j, 0, 4) {
				if (f[i][j] & EMPTY)
					continue;
				int c = (f[i][j] & COLOR);
				switch (f[i][j] & TYPE) {
				case BACKER: {
					int dx[4] = {-1, 0, 1, 0};
					int dy[4] = {0, 1, 0, -1};
					rep(k, 0, 4) {
						int x = i + dx[k];
						int y = j + dy[k];
						if (x < 0 || y < 0 || x >= 10 || y >= 4)
							continue;
						++threats[x][y][c];
						if (!(f[x][y] & EMPTY) && (f[x][y] & COLOR) == (f[i][j] & COLOR))
							continue;
						++numMoves[c];
					}
					break;
				}
				case FRONTER: {
					int d = (f[i][j] & DIRECTION) == DOWN ? 1 : -1;
					int dx[4] = {2 * d, 0, 0};
					int dy[4] = {0, 1, -1};
					if (i + dx[0] == -1 || i + dx[0] == 10)
						dx[0] = 0;
					rep(k, 0, 3) {
						int x = i + dx[k];
						int y = j + dy[k];
						if (x < 0 || y < 0 || x >= 10 || y >= 4)
							continue;
						++threats[x][y][c];
						if (y % 2 == j % 2) {
							if (x == i) {
								if (x == 1)
									++threats[0][y][c];
								else
									++threats[9][y][c];
							}
							else {
								++threats[i + d][y][c];
							}
						}
						if (!(f[x][y] & EMPTY) && (f[x][y] & COLOR) == (f[i][j] & COLOR) &&
							(dx[k] || dy[k]))
							continue;
						++numMoves[c];
					}
					break;
				}
				case DIAGONAL: {
					int d = (f[i][j] & DIRECTION) == DOWN ? 1 : -1;
					int dx[3] = {2 * d, 2 * d, 2 * d};
					int dy[3] = {-2, 0, 2};
					rep(k, 0, 3) {
						int x = i + dx[k];
						int y = j + dy[k];
						if (y == j && (y == 0 || y == 3))
							continue;
						if (x == -1 || x == 10)
							x = i;
						if (x < 0 || y < 0 || x >= 10 || y >= 4)
							continue;
						int my;
						if (j == y) {
							my = 3 * (j - 1);
						}
						else
							my = (j + y) / 2;
						int mx = (i + x) / 2;
						if (i == x) {
							if (x == 1)
								mx = 0;
							else
								mx = 9;
						}
						++threats[mx][my][c];
						if (!(f[x][y] & EMPTY) && (f[x][y] & COLOR) == (f[i][j] & COLOR) &&
							(x != i || y != j))
							continue;
						++numMoves[c];
					}
					break;
				}
				}
			}
			ret += 0.01 * (numMoves[turn] - numMoves[!turn]);
		}
		rep(i, 0, 10)
			rep(j, 0, 4) {
			if (f[i][j] & EMPTY)
				continue;
			if (bot.useFancyEval) {
				int p = f[i][j];
				float mul = 1;
				if (turn != (p & COLOR))
					mul = -mul;
				int type = p & TYPE;
				rep(t, 0, 3) {
					if (type == BACKER)
						ret += timeCoefficient[t] * mul * backerValue[t];
					else if (type == FRONTER)
						ret += timeCoefficient[t] * mul * fronterValue[t];
					else
						ret += timeCoefficient[t] * mul * diagonalValue[t];
				}
				if (j == 1 || j == 2) {
					rep(t, 0, 3) {
						if (type == BACKER)
							ret += timeCoefficient[t] * mul * centerBackerValue[t];
						else if (type == FRONTER)
							ret += timeCoefficient[t] * mul * centerFronterValue[t];
						else
							ret += timeCoefficient[t] * mul * centerDiagonalValue[t];
					}
				}
			}
			/*rep(t,0,3){
					ret += mul*posval[t][p][0][0]*timeCoefficient[t];
				}*/
			else {
				int p = f[i][j];
				int c = p & COLOR;
				float mul = 1;
				if (turn != (p & COLOR))
					mul = -mul;
				int type = p & TYPE;
				if (bot.useThreatAnalysis && threats[i][j][!c] && !threats[i][j][c]) {
					if (c == turn) {
						if (type == BACKER)
							ret += 0.4 * mul;
						else if (type == FRONTER)
							ret += 0.6 * mul;
						else
							ret += 0.5 * mul;
					}
					else {
						if (type == BACKER)
							ret += 0.2 * mul;
						else if (type == FRONTER)
							ret += 0.3 * mul;
						else
							ret += 0.25 * mul;
					}
				}
				else {
					if (type == BACKER)
						ret += bot.backerValue * mul;
					else if (type == FRONTER)
						ret += bot.fronterValue * mul;
					else
						ret += bot.diagonalValue * mul;
				}
				if (p & COLOR)
					ret -= mul * bot.positionScore * i;
				else
					ret -= mul * bot.positionScore * (9 - i);
			}
		}
		float tmp = sigmoid(ret);
		return ret * 10000;
	}

	float eval() {
		int count[3] = {0, 0, 0};
		rep(i, 0, 10)
			rep(j, 0, 4) if (!(f[i][j] & EMPTY))++ count[f[i][j] & COLOR];
		if (count[0] == count[1])
			return 0.5;
		if (count[turn] < count[1 - turn])
			return 0;
		return 1;
	}

	bool operator<(const State &other) const {
		return 0;
	}

	ll getHash() {
		ll ret = 2573 * turn + turnNumber * 787523;
		rep(i, 0, 10)
			rep(j, 0, 4) {
			//ret=(791*ret+f[i][j]^ret)%183972817238475LL;
			ret = (791 * ret + f[i][j] ^ ret) % 1844319728172384753LL;
		}
		return ret;
	}
};

State randomStateInGame;
int scoreList[82];
int rolloutDepth;
ll totRolloutDepth;
bool rolloutOnlyOneMove = false;

float accurateRollout(State *s, float alpha, float beta) {
	++rolloutDepth;
	if (rolloutDepth > 150) {
		printf("Error");
		assert(0);
	}
#ifdef DEBUG_POLICY
	s->print();
	getchar();
#endif
	++rolloutIterations;
	vector<Move> moveList = s->getMoves();
	int moveN = min(80, (int)moveList.size());
	if (s->turnNumber == 100 || moveList[0].x == -1) {
#ifdef DEBUG_POLICY
		printf("Returned because all moves were excluded\n");
#endif
		return s->eval();
	}
	rep(i, 0, moveN)
		scoreList[i] = 1;
	int totalScore = moveN;
	int r = ((rand() % 10000) * 10000 + (rand() % 10000)) % totalScore;
	rep(i, 0, moveN) {
		r -= scoreList[i];
		if (r < 0) {
			Move move = moveList[i];
#ifdef DEBUG_POLICY
			printf("Chose move: ");
			move.print();
#endif
			s->performMove(move);
			float sc = 1 - accurateRollout(s, 1 - beta, 1 - alpha);
			return sc;
		}
	}
	assert(0);
}

bool deleteNodesRecursively;
set<ll> printedMoves;
int fuzzyPreweightN;

struct Node {
	vector<pair<Move, Node *>> children;
	float score;
	ll n;
	bool isLeaf;
	float preWeight;
	float effectiveN;
	float effectiveScore;
	float lowerBound;
	float upperBound;
	float baseScore;
	float baseN;
	bool selectedMassiveSearch;

	Node() {
		score = 0;
		n = 0;
		isLeaf = 0;
		preWeight = 0;
		effectiveN = 0;
		effectiveScore = 0;
		lowerBound = 0;
		upperBound = 1;
		selectedMassiveSearch = false;
	}

	float getScore(int depth, float N) {
		if (!n)
			return 1000000;
		float explorationCoefficient = (depth < 2 && bot.explorationCoefficientLowDepth > 0) ? bot.explorationCoefficientLowDepth : bot.explorationCoefficient;
		return 1 - (score) / (n) + explorationCoefficient * sqrt(log(N) / (n));
	}

	void recPrint(State *s, int d, bool principalVariation) {
		if (!principalVariation) {
			if (d > 2)
				return;
		}
		s->print(d);
		printf("%lld\n", s->getHash());
		rep(i, 0, d)
			printf("  ");
		if (isLeaf) {
			printf("%f (Completed search, %lld)\n", score, n);
		}
		else {
			printf("%f/%lld=%f (%f/%f=%f)\n", score, n, score / n, effectiveScore, effectiveN, effectiveScore / effectiveN);
		}
		int bestChild = -1;
		int bestN = -1;
		if (principalVariation) {
			rep(i, 0, children.size()) {
				if (children[i].second->n > bestN) {
					bestN = children[i].second->n;
					bestChild = i;
				}
			}
		}
		rep(i, 0, children.size()) {
			if (principalVariation && i != bestChild)
				continue;
			/*if(children[i].second->n < 1000)
				continue;*/
			/*if(d == 1 && !(children[i].first.x == 8 && children[i].first.y == 5))
				continue;
			if(d == 0 && !(children[i].first.x == 0 && children[i].first.y == 8))
				continue;*/
			State tmpState = *s;
			s->performMove(children[i].first);
			children[i].second->recPrint(s, d + 1, principalVariation);
			*s = tmpState;
		}
	}

	void writeOpeningBookFromStats(State *s, FILE *file, bool printMove) {
		vector<Move> moves = s->getMoves();
		rep(i, 0, moves.size()) {
			Move move = moves[i];
			State tmpState = *s;
			s->performMove(move);
			ll h = s->getHash();
			newNodes++;
			upperBound = 1;
			children.push_back(make_pair(move, new Node()));
			if (massiveStats.count(h)) {
				pair<float, ll> e = massiveStats[h];
				Node *c = children.back().second;
				c->score = e.first;
				c->selectedMassiveSearch = true;
				if (e.second == -1) {
					c->isLeaf = true;
					c->n = 1;
				}
				else
					c->n = e.second;
				c->baseScore = c->score;
				c->baseN = c->n;
				c->effectiveScore = c->score / c->n;
				c->effectiveN = c->n;
			}
			else {
				*s = tmpState;
				return;
			}
			*s = tmpState;
		}
		float bestVis = -1;
		float bestFinalVis = -1;
		float bestFinalScore = -1;
		float bestMoveScore = -1;
		Move bestMove;
		Move bestFinalMove;
		int bestMoveInd;
		int bestFinalMoveInd;
		rep(i, 0, children.size()) {
			Move move = children[i].first;
			if (children[i].second->isLeaf) {
				if (1 - children[i].second->score > bestFinalScore || (1 - children[i].second->score == bestFinalScore && children[i].second->n > bestFinalVis)) {
					bestFinalScore = 1 - children[i].second->score;
					bestFinalMove = children[i].first;
					bestFinalVis = children[i].second->n;
					bestFinalMoveInd = i;
				}
				continue;
			}
			float sc;
			sc = children[i].second->n - children[i].second->score;
			if (sc > bestVis) {
				bestVis = sc;
				bestMove = children[i].first;
				bestMoveInd = i;
				bestMoveScore = 1 - children[i].second->effectiveScore;
			}
		}
		if (bestFinalScore > bestMoveScore || bestFinalScore == 1) {
			bestMove = bestFinalMove;
			bestMoveInd = bestFinalMoveInd;
		}
		if (max(bestVis, bestFinalVis) < 1000000 && bestFinalScore == -1) {
			bestMoveScore = 0;
			rep(i, 0, children.size()) {
				Move move = children[i].first;
				float sc;
				sc = 1 - children[i].second->effectiveScore;
				if (sc > bestMoveScore) {
					bestMove = children[i].first;
					bestMoveInd = i;
					bestMoveScore = sc;
				}
			}
		}
		if (printMove && n > 100000) {
			State tmpState = *s;
			Move tmpMove = bestMove;
			rep(t, 0, 1) {
				if (!printedMoves.count(tmpState.getHash())) {
					printedMoves.insert(tmpState.getHash());
					openingMove[tmpState.getHash()] = tmpMove;
					fprintf(file, "openingMove[%lld]=Move(%d,%d);\n", tmpState.getHash(), tmpMove.x, tmpMove.y);
					if (!t) {
						puts("New book move:");
						tmpState.print();
						tmpMove.print();
						State tmpState2 = tmpState;
						tmpState2.performMove(tmpMove);
						tmpState2.print();
						getchar();
					}
				}
			}
		}
		rep(i, 0, children.size()) {
			Move move = children[i].first;
			if (printMove && !(bestMove == move))
				continue;
			State tmpState = *s;
			s->performMove(move);
			children[i].second->writeOpeningBookFromStats(s, file, !printMove);
			*s = tmpState;
		}
	}

	void writeStats(State *s, FILE *file) {
		if (n < massiveIterationCount && !selectedMassiveSearch)
			return;
		if (!isLeaf && n <= massiveStats[s->getHash()].second) {
			/*s->print();
			printf("ERROR! New n is %lld but old n is %lld\n", n, massiveStats[s->getHash()].second);
			assert(0);*/
			return;
		}
		if (isLeaf || n != massiveStats[s->getHash()].second) {
			s->print();
			if (isLeaf)
				printf("Leaf: %f\n", score);
			else
				printf("%f (%lld)\n", score / n, n);
		}
		rep(i, 0, children.size()) {
			Move move = children[i].first;
			State tmpState = *s;
			s->performMove(move);
			children[i].second->writeStats(s, file);
			*s = tmpState;
		}
		//massiveStats[s->getHash()]=make_pair(score, isLeaf?-1:n);
		State tmpState = *s;
		ll h = tmpState.getHash();
		massiveStats[h] = make_pair(score, isLeaf ? -1 : n);
	}

	void writeToOpeningBook(State *s, FILE *file, int minVis, bool printMove) {
		if (n < minVis)
			return;
		printMove = true;
		float bestVis = -1;
		float bestFinalVis = -1;
		float bestFinalScore = -1;
		float bestMoveScore = -1;
		Move bestMove;
		Move bestFinalMove;
		int bestMoveInd;
		int bestFinalMoveInd;
		rep(i, 0, children.size()) {
			//if(!printMove){
			Move move = children[i].first;
			State tmpState = *s;
			/*int tmpNx=s->nextX;
				int tmpNy=s->nextY;*/
			s->performMove(move);
			children[i].second->writeToOpeningBook(s, file, minVis, !printMove);
			/*s->undoMove(move);
				s->nextX=tmpNx;
				s->nextY=tmpNy;*/
			*s = tmpState;
			//}
			if (children[i].second->isLeaf) {
				if (1 - children[i].second->score > bestFinalScore || (1 - children[i].second->score == bestFinalScore && children[i].second->n > bestFinalVis)) {
					bestFinalScore = 1 - children[i].second->score;
					bestFinalMove = children[i].first;
					bestFinalVis = children[i].second->n;
					bestFinalMoveInd = i;
				}
				continue;
			}
			float sc;
			sc = children[i].second->n;
			if (sc > bestVis) {
				bestVis = sc;
				bestMove = children[i].first;
				bestMoveInd = i;
				bestMoveScore = 1 - children[i].second->score / children[i].second->n;
			}
		}
		if (bestFinalScore > bestMoveScore || bestFinalScore == 1) {
			bestMove = bestFinalMove;
			bestMoveInd = bestFinalMoveInd;
		}
		if (printMove) {
			/*puts("s is");
			s->print();*/
			State tmpState = *s;
			Move tmpMove = bestMove;
			openingMove[tmpState.getHash()] = tmpMove;
			fprintf(file, "openingMove[%lld]=Move(%d,%d);\n", tmpState.getHash(), tmpMove.x, tmpMove.y);
			/*puts("New book move:");
			tmpState.print();
			tmpMove.print();
			State tmpState2=tmpState;
			tmpState2.performMove(tmpMove);
			tmpState2.print();
			getch();*/
			//openingMove[s->getHash()]=bestMove;
			//fprintf(file, "openingMove[%lld]=Move(%d,%d);\n", s->getHash(), bestMove.x, bestMove.y);
			/*int tmpNx=s->nextX;
			State tmpState3=*s;
			int tmpNy=s->nextY;
			s->performMove(bestMove);
			children[bestMoveInd].second->writeToOpeningBook(s, file, minVis, !printMove);
			s->undoMove(bestMove);
			s->nextX=tmpNx;
			s->nextY=tmpNy;
			*s=tmpState3;*/
		}
	}

	~Node() {
		if (deleteNodesRecursively) {
			rep(i, 0, children.size()) {
				delete (children[i].second);
			}
		}
		children.clear();
	}

	pair<float, int> rec(State *s, int depth, float alpha, float beta, bool hasRepeated);
};

unordered_map<ll, Node *> hashMap[2];
unordered_map<ll, State> debugStateMap;
bool unexpanded = false;

pair<float, int> Node::rec(State *s, int depth, float alpha, float beta, bool hasRepeated) {
	if (doMassiveSearch) {
		swap(playerExplorationCoefficient[0], playerExplorationCoefficient[1]);
		bot.explorationCoefficient = playerExplorationCoefficient[0];
	}
	if (depth > 80) {
		//assert(0);
		s->print();
		printf("Too large depth!!!");
	}
	if (n < massiveIterationCount && doMassiveSearch) {
		float totSc = 0;
		int totN = 0;
		printf("Analyzing\n");
		s->print();
		/*printf("%lld\n", s->getHash());
		if(s->f[1][1]&(1<<8)){
			printf("Center\n");
		}*/
		doMassiveSearch = false;
		bot.explorationCoefficient = 0.5;
		int numTimes = massiveIterationCount < n + 50 ? massiveIterationCount : n + 50;
		selectedMassiveSearch = true;
		State tmpState = *s;
		while (totN < numTimes) {
			pair<float, int> res = rec(s, depth, alpha, beta, 0);
			totSc += res.first;
			totN += res.second;
			if (isLeaf) {
				*s = tmpState;
				return make_pair(score, 1);
			}
			*s = tmpState;
		}
		doMassiveSearch = true;
		unexpanded = true;
		tmpState = *s;
		tmpState.print();
		/*printf("%f / %lld\n", score, n);
		if(s->f[1][1]&(1<<8)){
			printf("Center\n");
		}*/
		ll h = tmpState.getHash();
		massiveStats[h] = make_pair(score, isLeaf ? -1 : n);
		return make_pair(totSc, totN);
	}
	alpha = max(alpha, lowerBound);
	beta = min(beta, upperBound);
	maxDepth = max(maxDepth, depth);
	if (s->turnNumber >= 100) {
		isLeaf = true;
		score = s->eval();
		assert(score >= 0 && score <= 1);
		return make_pair(score, 1);
	}
	if (isLeaf) {
		return make_pair(score, 1);
	}
	if (n == 0) {
		State tmpState = *s;
		rolloutDepth = 0;
		++statesDone;
		float sc = accurateRollout(s, alpha, beta);
		baseScore = sc;
		baseN = 1;
		effectiveN = 1;
		effectiveScore = sc;
		totRolloutDepth += rolloutDepth;
		*s = tmpState;
		score += sc;
		n = 1;
		return make_pair(sc, 1);
	}
	if (children.empty()) {
		vector<Move> moves = s->getMoves();
		float newScore = 0;
		int newN = 0;
		upperBound = 0;
		rep(i, 0, moves.size()) {
			Move move = moves[i];
			if (bot.useHashMap) {
				State tmpState = *s;
				s->performMove(move);
				ll h = s->getHash();
				auto it = hashMap[curTurn].find(h);
				if (it != hashMap[curTurn].end()) {
					Node *newChild = it->second;
					lowerBound = max(lowerBound, 1 - newChild->upperBound);
					upperBound = max(upperBound, 1 - newChild->lowerBound);
					reusedNodes++;
					children.push_back(make_pair(move, newChild));
				}
				else {
					newNodes++;
					upperBound = 1;
					children.push_back(make_pair(move, new Node()));
					hashMap[curTurn][h] = children.back().second;
					if (makingMassiveStats && massiveStats.count(h)) {
						pair<float, ll> e = massiveStats[h];
						Node *c = children.back().second;
						c->selectedMassiveSearch = true;
						c->score = e.first;
						if (e.second == -1)
							c->isLeaf = true;
						else
							c->n = e.second;
						c->baseScore = c->score;
						c->baseN = c->n;
						c->effectiveScore = c->score / c->n;
						c->effectiveN = c->n;
					}
				}
				*s = tmpState;
			}
		}
		if (isLeaf) {
			return make_pair(score, 1);
		}
		if (children[0].first.x == -1) {
			isLeaf = true;
			score = s->eval();
			assert(score >= 0 && score <= 1);
			return make_pair(score, 1);
		}
	}
	float bestScore = -1000000;
	float bestFinalScore = 0;
	int best = -1;
	rep(i, 0, children.size()) {
		if (children[i].second->isLeaf) {
			bestFinalScore = max(bestFinalScore, 1 - children[i].second->score);
			continue;
		}
	}
	rep(i, 0, children.size()) {
		if (bot.completeSearchTree) {
			if (children[i].second->isLeaf) {
				continue;
			}
		}
		if (bot.useBounds && 1 - children[i].second->lowerBound <= alpha) {
			if (!children[i].second->isLeaf)
				++prunedUsingBounds;
			children.erase(children.begin() + i);
			--i;
			continue;
		}
		float sc;
		sc = children[i].second->getScore(depth, n);
		if (sc > bestScore) {
			bestScore = sc;
			best = i;
		}
	}
	if (best == -1 || bestFinalScore == 1) {
		score = bestFinalScore;
		isLeaf = true;
		assert(score >= 0 && score <= 1);
		return make_pair(score, 1);
	}
	State tmpState = *s;
	int iterN = 1;
	float totSc = 0;
	int totN = 0;
	rep(i, 0, iterN) {
		s->performMove(children[best].first);
		pair<float, int> res = children[best].second->rec(s, depth + 1, 1 - beta, 1 - alpha, hasRepeated || (iterN > 1));
		assert(res.second == 1 || iterN == 1);
		float sc = res.second - res.first;
		// Ensure that we don't let the ancestors think this node may be a lost position when it's at least a draw.
		if (isLeaf && bestFinalScore > sc) {
			sc = bestFinalScore;
		}
		//printf("d=%d, i=%d, added=%f/%d\n", depth, i, sc, res.second);
		totSc += sc;
		totN += res.second;
		*s = tmpState;
	}
	score += totSc;
	n += totN;
	if (!(totSc >= 0 && totSc <= totN)) {
		printf("totSc = %f, totN = %d\n", totSc, totN);
		assert(0);
	}
	if (makingMassiveStats && doMassiveSearch) {
		State tmpState = *s;
		tmpState.print();
		printf("%f / %lld\n", score, n);
		ll h = tmpState.getHash();
		massiveStats[h] = make_pair(score, isLeaf ? -1 : n);
	}
	return make_pair(totSc, totN);
}

State parseState() {
	State ret;
	rep(i, 0, 10)
		rep(j, 0, 4) {
		string inp;
		cin >> inp;
		if (inp == "000")
			ret.f[i][j] = EMPTY;
		else {
			ret.f[i][j] = 0;
			if (inp[0] == '1')
				ret.f[i][j] |= YELLOW;
			if (inp[0] == '2')
				ret.f[i][j] |= GREEN;
			if (inp[1] == '1')
				ret.f[i][j] |= BACKER;
			if (inp[1] == '2')
				ret.f[i][j] |= FRONTER;
			if (inp[1] == '3')
				ret.f[i][j] |= DIAGONAL;
			if (inp[2] == '1')
				ret.f[i][j] |= DOWN;
			if (inp[2] == '0')
				ret.f[i][j] |= UP;
		}
	}

	int turn;
	cin >> ret.turnNumber >> turn;
	ret.turn = turn - 1;
	return ret;
}

State parseState2() {
	State ret;
	int i = 0, j = 0;
	char s[200];
	int p = 0;
	ret.init();
	rep(i, 0, 10)
		rep(j, 0, 4)
			ret.f[i][j] = 0;
	rep(i, 0, 10)
		rep(j, 0, 4) {
		int in;
		ignore = scanf("%d", &in);
		if (in)
			ret.f[i][j] = in;
	}
	int in;
	ignore = scanf("%d", &in);
	ret.turn = in;
	ignore = scanf("%d", &in);
	ret.turnNumber = in;
	ret.print();
	return ret;
}

int statesChecked;
int startD = 0;
bool printStuff;

void createMassiveStats() {
	assert(0);
	FILE *stats = fopen("stats.txt", "r");
	ll h, n;
	float score;
	while (fscanf(stats, "%lld%f%lld", &h, &score, &n) == 3) {
		massiveStats[h] = make_pair(score, n);
	}
	fclose(stats);
}

int ABLowerBoundScore;
Move ABBestMove;
bool fullSearch;
float probCutCoefficient;
float linearProbCutCoefficient;

int getProbCutBonus(int d, int d2, bool finishedLastLayer, int childN, int parentN) {
	if (bot.useABMCTSProbCut && parentN > 1000) {
		float ret = bot.ABMCTSProbCutCoefficient * sqrt(log(float(parentN)) / childN);
		if (d - d2 > 15 || fullSearch)
			ret += 200000000;
		if (ret > 1000000000)
			ret = 1000000000;
		return ret;
	}
	if (bot.alternativeProbCut) {
		float ret = (linearProbCutCoefficient + probCutCoefficient * (d - d2)) * (d - d2);
		if (bot.preferUnfinishedLayers && !finishedLastLayer && d > d2 + 1)
			ret += linearProbCutCoefficient;
		if (d < 3)
			ret += bot.probCutSmallDepthBonus;
		//double ret=bot.probCutCoefficient*exp((d-d2)*bot.probCutExponential);
		if (d - d2 > 15 || fullSearch)
			ret += 200000000;
		if (ret > 1000000000)
			ret = 1000000000;
		return ret;
	}
	int ret = bot.probCutCoefficient * (d - d2);
	if (d2 < 5)
		ret += 4 * bot.probCutCoefficient * (5 - d2);
	if (d - d2 > 15 || fullSearch)
		ret += 200000000;
	if (ret > 1000000000)
		ret = 1000000000;
	return ret;
}

struct ABNode {
	vector<int> lowerBounds;
	vector<int> upperBounds;
	State s;
	vector<ABNode *> children;
	vector<Move> childrenMoves;
	bool isLeaf;
	bool checkedLeaf;
	int leafScore;
	//int parentScore;
	ll subtreeSize;
	vector<char> excludedMoves;
	bool hasFoundChildren;

	ABNode() {
		lowerBounds.push_back(-INF);
		upperBounds.push_back(INF);
		isLeaf = false;
		checkedLeaf = false;
		subtreeSize = 1;
		hasFoundChildren = false;
	}

	ABNode(State _s) {
		s = _s;
		lowerBounds.push_back(-INF);
		upperBounds.push_back(INF);
		isLeaf = false;
		checkedLeaf = false;
		subtreeSize = 1;
		hasFoundChildren = false;
	}

	void recPrint(int d, int maxD) {
		s.print(d);
		if (isLeaf) {
			printf("  ");
			printf("Leaf: %d\n", leafScore);
		}
		else {
			rep(i, 0, lowerBounds.size()) {
				rep(j, 0, d)
					printf("  ");
				printf("%d: %d - %d\n", i, lowerBounds[i], upperBounds[i]);
			}
		}
		if (d < maxD) {
			rep(i, 0, children.size()) {
				ABNode *child = children[i];
				child->recPrint(d + 1, maxD);
			}
		}
	}

	int rec(int d, int alpha, int beta);

	Move getBestMove() {
		Move bestMove;
		int bestLo, bestHi;
		rrep(d, ((int)lowerBounds.size()) - 1, 0) {
			bestLo = -INF - 1;
			bestHi = -INF - 1;
			int bestOtherHi = -INF - 1;
			bool ok = 1;
			rep(i, 0, children.size()) {
				ABNode *child = children[i];
				int lo, hi;
				if (child->isLeaf) {
					lo = -child->leafScore;
					hi = -child->leafScore;
				}
				else {
					if (child->lowerBounds.size() <= d) {
						//ok=0;
						continue;
					}
					lo = -child->upperBounds[d];
					hi = -child->lowerBounds[d];
				}
				Move move = childrenMoves[i];
				if (lo > bestLo || (lo == bestLo && hi > bestHi)) {
					bestOtherHi = max(bestOtherHi, bestHi);
					bestLo = lo;
					bestHi = hi;
					bestMove = move;
				}
				else {
					bestOtherHi = max(bestOtherHi, hi);
				}
			}
			if (ok && bestOtherHi <= bestLo) {
				assert(d >= ((int)lowerBounds.size()) - 3);
				ABLowerBoundScore = bestLo;
				return bestMove;
			}
		}
		assert(0);
	}

	Move getBestMoveEndgame() {
		Move bestMove;
		int bestLo = -INF - 1;
		int bestSize = 0;
		rep(i, 0, children.size()) {
			ABNode *child = children[i];
			int sc = -child->leafScore;
			if (!child->isLeaf) {
				if (child->upperBounds.empty())
					continue;
				sc = -child->upperBounds.back();
			}
			if (sc < -999950)
				sc = -1000000;
			if (sc > 999950)
				sc = 1000000;
			if (sc > bestLo || (sc == bestLo && child->subtreeSize > bestSize)) {
				bestLo = sc;
				bestSize = child->subtreeSize;
				bestMove = childrenMoves[i];
			}
		}
		return bestMove;
	}

	int getApproximateScore() {
		if (isLeaf)
			return leafScore;
		rrep(d, lowerBounds.size(), 0) {
			if (upperBounds[d] < INF)
				return upperBounds[d];
		}
		return upperBounds.back();
	}

	Move getBestMove2() {
		recPrint(0, 1);
		ABNode *bestChild = NULL;
		Move bestMove;

		rep(i, 0, children.size()) {
			ABNode *child = children[i];
			if (!bestChild) {
			}
			else if (child->isLeaf || bestChild->isLeaf) {
				if (child->getApproximateScore() >= bestChild->getApproximateScore())
					continue;
			}
			else if (child->lowerBounds.size() > bestChild->lowerBounds.size()) {
			}
			else if (child->lowerBounds.size() < bestChild->lowerBounds.size()) {
				continue;
			}
			else {
				bool better = 0;
				rrep(d, ((int)child->lowerBounds.size()), 0) {
					if (child->upperBounds[d] < bestChild->upperBounds[d]) {
						better = 1;
						break;
					}
					else if (child->upperBounds[d] > bestChild->upperBounds[d]) {
						better = 0;
						break;
					}
				}
				if (!better)
					continue;
			}
			bestChild = child;
			bestMove = childrenMoves[i];
		}
		if (bestChild->lowerBounds.back() != bestChild->upperBounds.back())
			return Move(-2, -2, -2, -2);
		ABLowerBoundScore = -bestChild->getApproximateScore();
		return bestMove;
	}

	Move getBestMove3(Move prevBestMove) {
		//recPrint(0, 1);
		ABNode *bestChild = NULL;
		Move bestMove;
		rep(i, 0, children.size()) {
			if (childrenMoves[i] == prevBestMove)
				bestChild = children[i];
		}
		assert(bestChild);
		bestMove = prevBestMove;
		if (bestChild->isLeaf)
			return bestMove;
		rep(i, 0, children.size()) {
			ABNode *child = children[i];
			if (child->isLeaf)
				continue;
			if (child->lowerBounds.size() < bestChild->upperBounds.size())
				continue;
			assert(child->lowerBounds.size() == bestChild->upperBounds.size());
			if (-child->upperBounds.back() > -bestChild->lowerBounds.back()) {
				bestChild = child;
				bestMove = childrenMoves[i];
			}
		}
		ABLowerBoundScore = -bestChild->getApproximateScore();
		return bestMove;
	}

	void updateLowerBound(int d) {
		lowerBounds[d] = -INF;
		bool anyLeafOrRightDepth = false;
		rep(i, 0, children.size()) {
			ABNode *child = children[i];
			if (child->isLeaf) {
				anyLeafOrRightDepth = true;
				if (-child->leafScore > lowerBounds[d])
					lowerBounds[d] = -child->leafScore;
				//lowerBounds[d]=max(lowerBounds[d], -child->leafScore);
			}
			else {
				if (child->lowerBounds.size() >= d) {
					anyLeafOrRightDepth = true;
					if (-child->upperBounds[d - 1] > lowerBounds[d])
						lowerBounds[d] = -child->upperBounds[d - 1];
					//lowerBounds[d]=max(lowerBounds[d], -child->upperBounds[d-1]);
				}
			}
		}
		if (!bot.replaceSmallNode && lowerBounds[d] > 999950) {
			//if(lowerBounds[d] == INF)
			isLeaf = true;
			leafScore = lowerBounds[d];
		}
		if (bot.replaceSmallNode && !anyLeafOrRightDepth) {
			lowerBounds[d] = -INF;
		}
	}

	void updateUpperBound(int d) {
		bool nonLeafChild = false;
		upperBounds[d] = -INF;
		rep(i, 0, children.size()) {
			ABNode *child = children[i];
			if (child->isLeaf) {
				if (-child->leafScore > upperBounds[d])
					upperBounds[d] = -child->leafScore;
				//upperBounds[d]=max(upperBounds[d], -child->leafScore);
			}
			else {
				nonLeafChild = true;
				if (child->lowerBounds.size() >= d) {
					//upperBounds[d]=max(upperBounds[d], -child->lowerBounds[d-1]);
					if (-child->lowerBounds[d - 1] > upperBounds[d])
						upperBounds[d] = -child->lowerBounds[d - 1];
				}
				else if (bot.useProbCut) {
					int d2 = child->lowerBounds.size() - 1;
					int bonus = getProbCutBonus(d, d2, child->lowerBounds.back() == child->upperBounds.back(), child->subtreeSize, subtreeSize); //+upperBounds[d-1]-upperBounds[d2];
					upperBounds[d] = min(max(upperBounds[d], -child->lowerBounds[d2] + bonus), INF);
				}
				else {
					upperBounds[d] = INF;
				}
			}
		}
		if (!nonLeafChild || (upperBounds[d] < -999950)) {
			isLeaf = true;
			leafScore = upperBounds[d];
		}
	}
};

vector<ABNode *> allocated;
vector<int> allocatedIndices;
int allocatedNumber;

ABNode *getNewNode(State *s) {
	if (allocatedIndices.empty()) {
		allocated.push_back(new ABNode(*s));
		return allocated.back();
	}
	else {
		ABNode *ret = allocated[allocatedIndices.back()];
		ret->s = *s;
		ret->lowerBounds.clear();
		ret->upperBounds.clear();
		ret->lowerBounds.push_back(-INF);
		ret->upperBounds.push_back(INF);
		ret->isLeaf = false;
		ret->checkedLeaf = false;
		ret->children.clear();
		ret->childrenMoves.clear();
		ret->excludedMoves.clear();
		ret->subtreeSize = 1;
		ret->hasFoundChildren = false;
		allocatedIndices.pop_back();
		return ret;
	}
}

#define AB_MAP_SIZE 20
#define AB_MAP_LIST_SIZE 7

struct unordered_AB_map {
	//vector<pair<ll, ABNode*> > table[(1<<20)];
	ll tableH[(1 << AB_MAP_SIZE)][AB_MAP_LIST_SIZE];
	ABNode *tableN[(1 << AB_MAP_SIZE)][AB_MAP_LIST_SIZE];
	int tableListSize[(1 << AB_MAP_SIZE)];
	int tableListPos[(1 << AB_MAP_SIZE)];

	ABNode *get(ll h) {
		int H = (h & ((1LL << AB_MAP_SIZE) - 1));
		rep(i, 0, tableListSize[H]) if (tableH[H][i] == h) return tableN[H][i];
		return NULL;
	}

	void add(ll h, ABNode *node) {
		int H = (h & ((1LL << AB_MAP_SIZE) - 1));
		if (tableListSize[H] < AB_MAP_LIST_SIZE) {
			tableH[H][tableListSize[H]] = h;
			tableN[H][tableListSize[H]++] = node;
		}
		else {
			if (bot.replaceSmallNode) {
				if (tableN[H][tableListPos[H]]->subtreeSize < 100000) {
					tableH[H][tableListPos[H]] = h;
					tableN[H][tableListPos[H]] = node;
				}
				++tableListPos[H];
				if (tableListPos[H] == AB_MAP_LIST_SIZE)
					tableListPos[H] = 0;
			}
			else {
				tableH[H][tableListPos[H]] = h;
				tableN[H][tableListPos[H]] = node;
				++tableListPos[H];
				if (tableListPos[H] == AB_MAP_LIST_SIZE)
					tableListPos[H] = 0;
			}
		}
		//else
		//	printf("Full\n");
		//tableH[H]=h;
		//tableN[H]=node;
		//table[H].emplace_back(h, node);
	}

	void clear() {
		rep(i, 0, (1 << AB_MAP_SIZE))
			tableListSize[i] = 0;
		//table[i].clear();
	}
};

//unordered_map<ll, ABNode*> ABHashMap;
unordered_AB_map ABHashMap;
int numEvals;
float globalTimeLimit;

void clearHashMap() {
	if (!tuning)
		puts("Clearing hash map");
	rep(i, 0, 2) {
		for (auto el : hashMap[i]) {
			delete el.second;
		}
		hashMap[i].clear();
	}
	debugStateMap.clear();
	allocatedIndices.clear();
	rep(i, 0, allocated.size()) {
		if (bot.replaceSmallNode && allocated[i]->subtreeSize >= 100000) {
			allocated[i]->hasFoundChildren = false;
			allocated[i]->childrenMoves.clear();
			allocated[i]->children.clear();
		}
		else {
			allocatedIndices.push_back(i);
		}
	}
	//for(auto el : ABHashMap){
	//delete el.second;
	//}
	if (!bot.replaceSmallNode)
		ABHashMap.clear();
}

bool canReach[10][4];

int ABNode::rec(int d, int alpha, int beta) {
	if (aborted)
		return 0;
	if (!hasFoundChildren && d != startD) {
		while (lowerBounds.size() > 1) {
			lowerBounds.pop_back();
			upperBounds.pop_back();
		}
	}
	int startAlpha = alpha;
	int startBeta = beta;
	//s.print(startD-d);
	/*if(d == startD)
		recPrint(0, 1);*/
	statesDone += 1;
	if (statesDone > checkTime && startD > 1) {
		checkTime += 1000;
		float timeElapsed = timeFactor * ((float(clock() - startTime)) / CLOCKS_PER_SEC);
		if (!bot.replaceSmallNode && timeElapsed > globalTimeLimit) {
			aborted = 1;
			return 0;
		}
	}
	if (isLeaf) {
		return leafScore;
	}
	if (s.turnNumber >= 100) {
		float val;
		val = s.eval();
		isLeaf = true;
		leafScore = 1000000 - startD;
		if (val < 0.1)
			leafScore = -leafScore;
		else if (val < 0.9)
			leafScore = 0;
		lowerBounds[0] = leafScore;
		upperBounds[0] = leafScore;
		return leafScore;
	}
	while (lowerBounds.size() <= d) {
		lowerBounds.push_back(-INF);
		upperBounds.push_back(INF);
		if (hasFoundChildren) {
			updateLowerBound(lowerBounds.size() - 1);
			updateUpperBound(lowerBounds.size() - 1);
		}
	}
	if (hasFoundChildren) {
		updateLowerBound(d);
		updateUpperBound(d);
	}
	if (beta <= lowerBounds[d])
		return lowerBounds[d];
	if (alpha >= upperBounds[d])
		return upperBounds[d];
	if (d == 0) {
		++numEvals;
		int val;
		val = s.fuzzyEval();
		leafScore = val;
		lowerBounds[0] = val;
		upperBounds[0] = lowerBounds[0];
		return val;
	}
	if (lowerBounds[d] > alpha)
		alpha = lowerBounds[d];
	if (upperBounds[d] < beta)
		beta = upperBounds[d];
	if (!hasFoundChildren) {
		vector<Move> moves = s.getMoves();
		if (moves[0].x < 0) {
			isLeaf = true;
			float val;
			val = s.eval();
			isLeaf = true;
			leafScore = 1000000 - startD;
			if (val < 0.1)
				leafScore = -leafScore;
			else if (val < 0.9)
				leafScore = 0;
			lowerBounds[0] = leafScore;
			upperBounds[0] = leafScore;
			return leafScore;
		}
		hasFoundChildren = true;
		rep(i, 0, moves.size()) {
			Move move = moves[i];
			State newState = s;
			bool isCapture = newState.performMove(move);
			if (startD == d) {
				childrenMoves.push_back(move);
			}
			ABNode *tmpNode = NULL;
			ll h;
			if (bot.useHashMap) {
				h = newState.getHash();
				tmpNode = ABHashMap.get(h);
			}
			if (tmpNode) {
				++reusedNodes;
				children.push_back(tmpNode);
			}
			else {
				//++subtreeSize;
				children.push_back(getNewNode(&newState));
				//children.back()->parentScore=leafScore;
				if (bot.useHashMap)
					ABHashMap.add(h, children.back());
				//ABHashMap[h]=children.back();
				children.back()->rec(0, -beta, -alpha);
			}
			ABNode *newChild = children[children.size() - 1];
			if (newChild->isLeaf) {
				if (-newChild->leafScore > lowerBounds[1])
					lowerBounds[1] = -newChild->leafScore;
				//lowerBounds[1]=max(lowerBounds[1], -newChild->leafScore);
			}
			else {
				if (-newChild->upperBounds[0] > lowerBounds[1])
					lowerBounds[1] = -newChild->upperBounds[0];
				//lowerBounds[1]=max(lowerBounds[1], -newChild->upperBounds[0]);
			}
			if (lowerBounds[d] > alpha)
				alpha = lowerBounds[d];
		}
		rep(i, 1, d + 1) {
			updateLowerBound(i);
			updateUpperBound(i);
		}
	}
	if (beta <= alpha) {
		return lowerBounds[d];
	}
	while (true) {
		//recPrint(0, 1);
		ABNode *bestChild;
		int bestChildInd;
		int bestScore;
		int bestDepth = -1;
		int maxDepth;
		int finalDepthScore = -INF;
		rep(i, 0, children.size()) {
			ABNode *child = children[i];
			if (child->isLeaf) {
				continue;
			}
			if (child->lowerBounds.size() > maxDepth)
				maxDepth = child->lowerBounds.size();
			if (child->lowerBounds.size() >= d) {
				finalDepthScore = max(finalDepthScore, -child->upperBounds[d - 1]);
			}
			if (child->lowerBounds.size() >= d && -child->lowerBounds[d - 1] <= alpha) {
				if (!fullSearch || d < startD || child->lowerBounds[d - 1] == child->upperBounds[d - 1])
					continue;
			}
			//int sc=-child->upperBounds.back();
			int sc = -child->lowerBounds.back();
			if ((int)child->lowerBounds.size() > bestDepth || ((int)child->lowerBounds.size() == bestDepth && sc > bestScore)) {
				if (bot.useProbCut) {
					int d2 = child->lowerBounds.size() - 1;
					int bonus = getProbCutBonus(d, d2, child->lowerBounds.back() == child->upperBounds.back(), child->subtreeSize, subtreeSize);
					if (d2 < d && -child->lowerBounds.back() + bonus < alpha) {
						//printf("Cut");
						//child->s.print();
						continue;
					}
				}
				bestDepth = child->lowerBounds.size();
				bestScore = sc;
				bestChild = child;
				bestChildInd = i;
			}
		}
		if (bestDepth == -1) {
			updateLowerBound(d);
			updateUpperBound(d);
			if (lowerBounds[d] < startAlpha)
				alpha = startAlpha;
			else
				alpha = lowerBounds[d];
			if (upperBounds[d] > startBeta)
				beta = startBeta;
			else
				beta = upperBounds[d];
			if (beta > alpha) {
				assert(0);
			}
			return lowerBounds.back();
		}
		int newD = min((int)bestChild->lowerBounds.size(), d - 1);
		//if(bot.ABCompleteAllSearches && newD == bestChild->lowerBounds.size() && newD && bestChild->lowerBounds.back() != bestChild->upperBounds.back())
		//	--newD;
		int newAlpha = -beta;
		int newBeta = -alpha;
		if (maxDepth == d)
			newAlpha = newBeta - 1;
		if (newD < d - 1) {
			newAlpha = -upperBounds[newD + 1];
			newBeta = -lowerBounds[newD + 1];
			if (bot.ABCompleteAllSearches) {
				newBeta = newAlpha + 1;
			}
		}
		if (bestChild->lowerBounds.size() < d - 1) {
			if ((int)bestChild->lowerBounds.size() < d - 6) {
				newAlpha = -INF;
				newBeta = INF;
			}
			else {
				newAlpha = -beta;
				newBeta = -alpha;
			}
		}
		else if (finalDepthScore > -INF) {
			if (d > 100 && bestChild->lowerBounds.size() == d - 1 && finalDepthScore > -INF) {
				int bonus = 500; //getProbCutBonus(1, 0, 0, bestChild->subtreeSize, subtreeSize);
				newAlpha = -finalDepthScore + bonus;
				newBeta = newAlpha + 1;
			}
			else if (bestChild->lowerBounds.size() <= d - 1 || -bestChild->upperBounds[d - 1] < finalDepthScore) {
				//newAlpha=newBeta-1;
			}
		}
		if (fullSearch && d >= startD) {
			newAlpha = -INF;
			newBeta = INF;
		}
		//ll prevChildSize = bestChild->subtreeSize;
		int prevNumEvals = numEvals;
		bestChild->rec(newD, newAlpha, newBeta);
		//subtreeSize += bestChild->subtreeSize-prevChildSize;
		subtreeSize += numEvals - prevNumEvals;
		if (aborted)
			return 0;
		// Incorrect, for some reason
		//lowerBounds[newD+1]=max(lowerBounds[newD+1], -bestChild->upperBounds[newD]);

		// It shouldn't be necessary to update the lower bound in this way

		updateLowerBound(newD + 1);
		updateUpperBound(newD + 1);
		if (lowerBounds[d] < startAlpha)
			alpha = startAlpha;
		else
			alpha = lowerBounds[d];
		if (upperBounds[d] > startBeta)
			beta = startBeta;
		else
			beta = upperBounds[d];
		//alpha=max(startAlpha, lowerBounds[d]);
		//beta=min(startBeta, upperBounds[d]);
		if (beta <= alpha) {
			if (d == startD) {
			}
			return lowerBounds[d];
		}
	}
	assert(0);
	return -1;
}

double scoreToPrint;

Move findMove(State s, int millisecondsLeft) {
	fuzzyPreweightN = bot.fuzzyPreweightN;
	curTurn = s.turn;
	numEvals = 0;
	globalTimeLimit = bot.timeLimit; //*exp(-(rand()%100)*0.01);
	if (bot.randomizeTimeLimit)
		globalTimeLimit *= exp(-(rand() % 100) * 0.02);
	/*if(bot.isHuman){
		string moveS;
		cin >> moveS;
		while(true){
			bool ok=1;
			if(moveS.size() != 2 || moveS[0] < 'a' || moveS[0] > 'i' || moveS[1] < '1' || moveS[1] > '9'){
				ok=0;
			}
			else{
				Move move;
				move.y=moveS[0]-'a';
				move.x=moveS[1]-'1';
				if(s.okMove(move))
					return move;
			}
			puts("Invalid move");
			cin >> moveS;
		}
	}*/
	if (bot.useFileParams) {
		initFileConstants();
	}
	s.fuzzyEval();
	/*if(!bot.useOpeningBook)
		cerr << "No opening book" << endl;
	cerr << "hash = " << s.getHash() << endl;
	if(!openingMove.count(s.getHash()))
		cerr << "Not in opening book" << endl;*/
	if (bot.useOpeningBook && openingMove.count(s.getHash())) {
		cerr << "Book move" << endl;
		/*if(bot.usePonder && millisecondsLeft > 9500){
			ponder(s, millisecondsLeft-9500);
		}*/
		return openingMove[s.getHash()];
	}
#ifdef DEBUG_ERROR
	cerr << millisecondsLeft << " ms left" << endl;
	;
#endif
	rolloutIterations = 0;
	statesChecked = 0;
	Move bestMove(-1, -1, -1, -1);
	Move lastBestMove = bestMove;
	bool lastBestMoveExists = 0;
	bool anyMove = false;
	int bestScore = -1000000001;
	vector<Move> moves = s.getMoves();
	if (moves[0].x == -1)
		return Move(-2, -2, -2, -2);
#ifdef DEBUG_PRINT
	if (!tuning)
		cout << bot.name << " ";
#endif
	int timeLimit = bot.timeLimit;
	checkTime = 1000;
	if (bot.uniformlyRandom) {
		return moves[rand() % moves.size()];
	}
	if (bot.useMCTS) {
		maxDepth = 0;
		Node *root;
		if (bot.useHashMap && hashMap[curTurn].count(s.getHash())) {
			root = hashMap[curTurn][s.getHash()];
		}
		else {
			root = new Node();
			ll h = s.getHash();
			if (massiveStats.count(h)) {
				pair<float, ll> e = massiveStats[h];
				root->score = e.first;
				if (e.second == -1)
					root->isLeaf = true;
				else
					root->n = e.second;
				root->baseScore = root->score;
				root->baseN = root->n;
				root->effectiveScore = root->score / root->n;
				root->effectiveN = root->n;
			}
		}
		totRolloutDepth = 0;
		statesDone = 0;
		int iterN = 0;
		while (!aborted && !root->isLeaf) {
			if (false && iterN > 500) {
				break;
				//cerr << "Hi" << endl;
			}
			iterN++;
			if (reusedNodes + newNodes + statesDone > checkTime && !makingMassiveStats) {
				checkTime += 2000;
				float timeElapsed = timeFactor * (float(clock() - startTime)) / CLOCKS_PER_SEC;
				if (timeElapsed > bot.timeLimit) {
					aborted = 1;
					break;
				}
			}
			root->rec(&s, 1, 0, 1, 0);
			/*root->recPrint(&s, 1, false);
			getchar();*/
			if (makingMassiveStats) {
				clearHashMap();
				root = new Node();
				ll h = s.getHash();
				if (massiveStats.count(h)) {
					pair<float, ll> e = massiveStats[h];
					root->score = e.first;
					if (e.second == -1)
						root->isLeaf = true;
					else
						root->n = e.second;
					root->baseScore = root->score;
					root->baseN = root->n;
					root->effectiveScore = root->score / root->n;
					root->effectiveN = root->n;
				}
			}
			//root->recPrint(&s, 1);
			//getch();
		}
		/*if(generateOpeningBook){
			FILE* stats = fopen("stats.txt", "w");
			for(auto entry : massiveStats){
				fprintf(stats, "%lld %.1f %lld\n", entry.first, entry.second.first, entry.second.second);
			}
			fclose(stats);
		}*/
		//root->recPrint(&s, 0, false);
		float bestVis = -1;
		float bestFinalScore = -1;
		int bestFinalVis = -1;
		float bestMoveScore = -1;
		Move bestFinalMove;
		rep(i, 0, root->children.size()) {
			if (bot.useEffectiveN && !root->children[i].second->isLeaf) {
				root->children[i].second->score = root->children[i].second->effectiveScore * root->children[i].second->effectiveN;
				root->children[i].second->n = root->children[i].second->effectiveN;
			}
			//if(root.children[i].second->n > bestVis){
			float sc;
			if (root->children[i].second->isLeaf) {
				if (1 - root->children[i].second->score > bestFinalScore || (1 - root->children[i].second->score == bestFinalScore && root->children[i].second->n > bestFinalVis)) {
					bestFinalScore = 1 - root->children[i].second->score;
					bestFinalMove = root->children[i].first;
					bestFinalVis = root->children[i].second->n;
				}
				continue;
			}
			if (1 - root->children[i].second->upperBound > bestFinalScore || (1 - root->children[i].second->upperBound == bestFinalScore && root->children[i].second->n > bestFinalVis)) {
				bestFinalScore = 1 - root->children[i].second->upperBound;
				bestFinalMove = root->children[i].first;
				bestFinalVis = root->children[i].second->n;
			}
			if (1 - root->children[i].second->lowerBound < bestFinalScore)
				continue;
			if (bot.MCTSChooseBestScore) {
				if (root->children[i].second->isLeaf) {
					sc = 1;
				}
				else {
					sc = 1 - root->children[i].second->score / root->children[i].second->n;
				}
			}
			else
				sc = root->children[i].second->n;
			if (sc > bestVis) {
				bestVis = sc;
				bestMove = root->children[i].first;
				bestMoveScore = 1 - root->children[i].second->score / root->children[i].second->n;
			}
		}
		if (bestFinalScore > bestMoveScore || bestFinalScore == 1) {
			bestMove = bestFinalMove;
		}
#ifdef DEBUG_ERROR
		cerr << "Bot: " << bot.name << endl;
		cerr << "Playoffs: " << statesDone << endl;
		cerr << "Rollout iterations: " << rolloutIterations << endl;
		cerr << "Maximum depth: " << maxDepth << endl;
		if (root->isLeaf) {
			cerr << "Expected score: " << root->score << endl;
			scoreToPrint = root->score;
		}
		else {
			cerr << "Expected score: " << root->score / root->n << endl;
			scoreToPrint = root->score / root->n;
		}
#endif
		/*if(responsibleMemoryUsage && !bot.useHashMap){
			deleteNodesRecursively=true;
			delete(root);
			deleteNodesRecursively=false;
		}*/
	}
	if (bot.useFancyAB) {
		int maxD = 80;
		s.eval();
		ABNode root(s);
		Move bestMove;
		probCutCoefficient = bot.probCutCoefficient;
		linearProbCutCoefficient = bot.linearProbCutCoefficient;
		/*if(probCutCoefficient > 400){
			printf("L");
			exit(0);
		}
		if(probCutCoefficient > 0){
			if(random()%2)
				printf("W");
			else
				printf("L");
			exit(0);
		}*/
		//printf("W");
		//exit(0);
		cerr << "Bot: " << bot.name << endl;
		int MTDfGuess = 0;
		aborted = false;
		rep(d, 0, maxD) {
			if (d > 90 || (d && abs(ABLowerBoundScore) >= 1000000))
				fullSearch = true;
			else
				fullSearch = false;
			startD = d;
			root.rec(d, -INF, INF);
			if (d && !aborted) {
				bestMove = root.getBestMove();
			}
			if (fullSearch && !aborted) {
				Move prevBestMove = bestMove;
				bestMove = root.getBestMoveEndgame();
				if (bestMove != prevBestMove) {
					cerr << "Changed best move" << endl;
				}
			}
			if (aborted && d > 2)
				break;
			if (!root.isLeaf) {
				//printf("%d: E: %d S: %d\n", d, numEvals, root.lowerBounds.back());
				//bestMove.print();
			}
			if (root.lowerBounds.back() >= 150000) {
				probCutCoefficient = bot.safeProbCutCoefficient;
			}
			else {
				probCutCoefficient = bot.probCutCoefficient;
			}
			float timeElapsed = timeFactor * ((float(clock() - startTime)) / CLOCKS_PER_SEC);
			if (timeElapsed > globalTimeLimit) {
				assert(!bot.replaceSmallNode || !aborted);
				break;
			}
			//cerr << d << ": " << numEvals << endl;
		}

		if (!tuning) {
			numEvalsSaved = numEvals;
			depthSaved = (root.lowerBounds.size() - 1);
			lowerBoundsSaved = ABLowerBoundScore;
			cerr << "Evals: " << numEvals << endl;
			cerr << "Depth: " << (root.lowerBounds.size() - 1) << endl;
			cerr << "Lower bound: " << ABLowerBoundScore << endl;
			int millisUsed = timeFactor * (1000 * float(clock() - startTime)) / CLOCKS_PER_SEC;
			cerr << "Evals per second: " << 1000 * (double(numEvals) / (millisUsed + 1)) << endl;
			cerr << "Millis used: " << millisUsed << endl;
			cerr << "Reused nodes: " << reusedNodes << endl;
		}
		int timeElapsed = timeFactor * (1000 * float(clock() - startTime)) / CLOCKS_PER_SEC;
		//abDepth=root.lowerBounds.size();
		//abPrintScore=ABLowerBoundScore;
		return bestMove;
	}
	s.eval();
	return bestMove;
}

vector<Bot> bots;

char fileName[] = "data/data000001";
char moveFileName[] = "move_data/move_data000001";

FILE *getNextFile() {
	if (!recordMove)
		return NULL;
	while (FILE *file = fopen(fileName, "r")) {
		fclose(file);
		int i;
		for (i = strlen(fileName) - 1; fileName[i] == '9'; --i) {
			fileName[i] = '0';
		}
		fileName[i]++;
	}
	return fopen(fileName, "w");
}

FILE *getNextMoveFile() {
	if (!recordMove)
		return NULL;
	while (FILE *file = fopen(moveFileName, "r")) {
		fclose(file);
		int i;
		for (i = strlen(moveFileName) - 1; moveFileName[i] == '9'; --i) {
			moveFileName[i] = '0';
		}
		moveFileName[i]++;
	}
	return fopen(moveFileName, "w");
}

Bot randomBot;
Bot decentBot;

void duel(Bot bot1, Bot bot2) {
	recordMove = true;
	responsibleMemoryUsage = true;
	bool startingBot = 0;
	int stats[2][3] = {{0, 0, 0}, {0, 0, 0}};
	FILE *fout = getNextFile();
	recordMoveFile = getNextMoveFile();
	int numberPrinted = 0;
	while (true) {
		if (numberPrinted == 20 && recordMove) {
			numberPrinted = 0;
			fclose(fout);
			fout = getNextFile();
			//fclose(recordMoveFile);
			//recordMoveFile=getNextMoveFile();
		}
		++numberPrinted;
		startingBot ^= 1;
		State s;
		s.init();
		int turn = 0;
		int millisLeft[2] = {10000, 10000};
		int movesDone = 0;
		float finalResult;
		vector<State> allStatesInGame;
		while (true) {
			clearHashMap();
			++movesDone;
			//getch();
			statesDone = 0;
			aborted = 0;
			checkTime = 0;
			if (turn == startingBot)
				bot = bot1;
			else
				bot = bot2;
			if (rand() % 3 < 2 && movesDone < 10)
				bot = randomBot;
			/*if(tuning){
			timeFactor=((rand()%100)+50)*0.01;
		}*/
			printEvalOutput = true;
			if (rand() % movesDone == 0) {
				randomStateInGame = s;
			}
			allStatesInGame.push_back(s);
			printEvalOutput = false;
			millisLeft[turn] += 500;
			if (millisLeft[turn] > 10000)
				millisLeft[turn] = 10000;
			startTime = clock();
			Move bestMove = findMove(s, millisLeft[turn]);
			if (bestMove.x < 0) {
				float e = s.eval();
				//printf("end eval: %f\n", e);
				if (s.eval() > 0.9) {
					stats[turn ^ startingBot][2]++;
					stats[turn ^ startingBot ^ 1][0]++;
					finalResult = !turn;
				}
				else if (s.eval() < 0.1) {
					stats[turn ^ startingBot][0]++;
					stats[turn ^ startingBot ^ 1][2]++;
					finalResult = turn;
				}
				else {
					stats[turn ^ startingBot][1]++;
					stats[turn ^ startingBot ^ 1][1]++;
					finalResult = 0.5;
				}
				break;
			}
			int millisUsed = timeFactor * (1000 * float(clock() - startTime)) / CLOCKS_PER_SEC;
			int index = (bot.name == "TeExStE0.5" ? 0 : 1);
			totalStatesDone[index] += reusedNodes + newNodes;
			totalMillisUsed[index] += millisUsed;
			if (!tuning && false) {
				printf("Total states: %lld\n", totalStatesDone[index]);
				printf("%lld states/s\n", (1000 * totalStatesDone[index] / (totalMillisUsed[index] + 1)));
				printf("%d ms\n", millisUsed);
				printf("Reused nodes: %d/%d\n", reusedNodes, reusedNodes + newNodes);
				if (prunedUsingBounds)
					printf("Nodes pruned using bounds: %d\n", prunedUsingBounds);
				if (earlyGameValues)
					printf("Early game values: %d\n", earlyGameValues);
			}

			reusedNodes = 0;
			newNodes = 0;
			prunedUsingBounds = 0;
			earlyGameValues = 0;
			millisLeft[turn] -= millisUsed;
			//assert(millisLeft[turn] > 0);
			s.performMove(bestMove);
			turn = !turn;
			if (!tuning) {
				//#ifdef DEBUG_PRINT
				s.print();
				//#endif
				bestMove.print();
			}
		}
		if (tuning) {
			if (finalResult > 0 && finalResult < 1) {
				if (random() % 2)
					printf("W");
				else
					printf("L");
			}
			else {
				if ((finalResult == 0) == (bot1.name == "bot5"))
					printf("W");
				else
					printf("L");
			}
			exit(0);
		}
//exit(0);
#ifdef DEBUG_PRINT
		s.print();
#endif
		if (recordMove) {
			/*randomStateInGame.eval();
		randomStateInGame.printUgly(fout);
		fprintf(fout, "%.1f\n", finalResult);*/
			for (auto stateInGame : allStatesInGame) {
				stateInGame.eval();
				stateInGame.printUgly(fout);
				fprintf(fout, "%.1f\n", finalResult);
			}
		}
		printf("Drawn games: %d\n", stats[0][1]);
		cout << bot1.name << ": " << (stats[0][1] + 2 * stats[0][2]) << endl;
		cout << bot2.name << ": " << (stats[1][1] + 2 * stats[1][2]) << endl;
		clearHashMap();
	}
	responsibleMemoryUsage = false;
}

void readStringOpeningBook() {
	string g = string(openings);
	stringstream fin;
	fin.str(g);
	int sz;
	fin >> sz;
	rep(i, 0, sz) {
		ll h;
		fin >> h;
		Move move;
		fin >> move.x >> move.y >> move.tox >> move.toy;
		openingMove[h] = move;
	}
}

void init() {
	//createOpeningBook();
	//readStringOpeningBook();
}

void makeMassiveStats() {
	makingMassiveStats = true;
	createMassiveStats();
	responsibleMemoryUsage = true;
	State s;
	s.init();
	while (true) {
		int forPlayer = rand() % 2;
		printf("forPlayer = %d\n", forPlayer);
		startTime = clock();
		statesDone = 0;
		checkTime = 0;
		aborted = 0;
		++iterMod;
		generateOpeningBook = true;
		doMassiveSearch = true;
		bot.explorationCoefficient = 0.5;
		playerExplorationCoefficient[forPlayer] = 0.7;
		playerExplorationCoefficient[!forPlayer] = 0.7;
		findMove(s, 6000);
		clearHashMap();
	}
}

void writeOpeningBookFromStats() {
	createMassiveStats();
	Node *root = new Node();
	State s;
	s.init();
	ll h = s.getHash();
	if (massiveStats.count(h)) {
		pair<float, ll> e = massiveStats[h];
		root->score = e.first;
		if (e.second == -1)
			root->isLeaf = true;
		else
			root->n = e.second;
		root->baseScore = root->score;
		root->baseN = root->n;
		root->effectiveScore = root->score / root->n;
		root->effectiveN = root->n;
	}
	else
		assert(0);
	assert(0);
	FILE *file = fopen("better_opening_book.txt", "w");
	root->writeOpeningBookFromStats(&s, file, true);
	root->writeOpeningBookFromStats(&s, file, false);
	fclose(file);
}

void makeOpeningBook() {
	Bot mainBot = bot;
	createOpeningBook();
	responsibleMemoryUsage = true;
	while (true) {
		clearHashMap();
		cerr << "Opening book size: " << openingMove.size() << endl;
		State s;
		s.init();
		int forPlayer = rand() % 2;
		while (s.turn != forPlayer || openingMove.count(s.getHash())) {
			if (s.turn == forPlayer) {
				s.performMove(openingMove[s.getHash()]);
			}
			else {
				startTime = clock();
				statesDone = 0;
				checkTime = 0;
				aborted = 0;
				generateOpeningBook = false;
				bot = randomBot;
				if (rand() % 2 == 0)
					bot = decentBot;
				Move move = findMove(s, 10000);
				s.performMove(move);
				clearHashMap();
				generateOpeningBook = true;
			}
		}
		startTime = clock();
		statesDone = 0;
		checkTime = 0;
		aborted = 0;
		puts("Generating opening book for");
		generateOpeningBook = true;
		s.print();
		bot = mainBot;
		Move move = findMove(s, 600000);
		generateOpeningBook = false;
		clearHashMap();
		openingMove[s.getHash()] = move;
		/*FILE* openingBook = fopen("openings.txt", "w");
	for(auto entry : openingMove){
		fprintf(openingBook, "openingMove[%lld]=Move(%d,%d,vector<pair<int, int> >());\n", entry.first, entry.second.x, entry.second.y);
		for(int i=0; i < entry.second.jumps.size(); ++i)
			fprintf(openingBook, "openingMove[%lld].jumps.emplace_back(%d, %d);\n", entry.first, entry.second.jumps[i].first, entry.second.jumps[i].second);
	}*/
		s.performMove(move);
		s.print();
		//fclose(openingBook);
	}
}

void writeStringOpeningBook() {
	assert(0);
	FILE *fout = fopen("openings_string.txt", "w");
	fprintf(fout, "%d ", (int)openingMove.size());
	for (auto entry : openingMove) {
		fprintf(fout, "%lld ", entry.first);
		fprintf(fout, "%d %d %d %d ", entry.second.x, entry.second.y, entry.second.tox, entry.second.toy);
	}
	fclose(fout);
}

int main(int argc, char *argv[]) {
	init();
	initEvalConstants();
	startTime = clock();
	srand(time(0));
	Bot bot1("bot1");
	bot1.useAlphaBeta = false;
	bot1.useMCTS = true;
	bot1.undoMovesDuringRollout = false;
	bot1.usePseudoRandom = true;
	bot1.completeSearchTree = true;
	bot1.useAccurateRollout = true;
	bot1.explorationCoefficient = 0.7;
	bot1.setLeafUsingRollout = true;
	bot1.useTimeManagement = true;
	bot1.useHashMap = true;
	bot1.timeSaveForEnd = true;
	bot1.useExclusion = true;
	bot1.stayInSubtree = true;
	bot1.subtreeExploreNumber = 1;
	bot1.useEffectiveN = false;
	bot1.useOpeningBook = false;
	bot1.timeLimit = 0.2;
	bots.push_back(bot1);
	randomBot = bot1;
	bot = bot1;

	Bot bot2 = bot1;
	bot2.name = "bot2";
	bot2.explorationCoefficient = 0.5;
	Bot bot4("bot4");
	bot4.useMCTS = false;
	bot4.useFancyAB = true;
	bot4.timeLimit = 0.9;
	bot4.randomizeTimeLimit = false;
	bot4.useProbCut = true;
	bot4.probCutCoefficient = 50;
	bot4.linearProbCutCoefficient = 500;
	bot4.probCutSmallDepthBonus = 300;
	bot4.safeProbCutCoefficient = 3000;
	bot4.alternativeProbCut = true;
	bot4.useHashMap = true;
	bot4.useTimeManagement = true;
	bot4.probCutExponential = 0.6;
	bot4.useOpeningBook = false;
	bot4.ABCompleteAllSearches = true;
	Bot bot5 = bot4;
	bot5.name = "bot5";
	bot5.useThreatAnalysis = true;
	Bot bot6 = bot4;
	bot6.name = "bot6";
	bot6.useFancyEval = true;
	bot = bot5;
	if (argc > 1) {
		tuning = true;
		bot5.useFileParams = true;
		bot = bot5;
		fileNameConstants = argv[1];
		srand(time(0));
		initFileConstants();
		initEvalConstants();
		cerr << "Initialized file constants";
		computeEvalHelpers();
		if (rand() % 2)
			duel(bot, bot4);
		else
			duel(bot4, bot);
	}
	/*State s=parseState2();
	s.print();
	s.eval();
	s.fuzzyEval();
	findMove(s, 10000);*/
	//writeStringOpeningBook();
	//duel(bot5, bot4);
	//makeOpeningBook();
	State curState = parseState();
	Move move = findMove(curState, 10000);
	move.printUgly();
	printf(" %d %d %d\n", lowerBoundsSaved, numEvalsSaved, depthSaved);
	//printf(" %.4lf\n", scoreToPrint);
}