#include <bits/stdc++.h>
//#define DEBUG_POLICY
#define DEBUG_PRINT
#define DEBUG_ERROR
#define INF 1000000000
#define BOARD_SIZE 5

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

float strength[BOARD_SIZE][BOARD_SIZE][3];
int numEvalsSaved;
int depthSaved;
int lowerBoundsSaved;
float expectedScoreSaved;
int forbidden[8][8];
int tmpBoard[8][8];
int doTranspose;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
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

char openings[] = "";

struct Bot {
	bool preferExplode;
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
		preferExplode = false;
		probCutSmallDepthBonus = 0;
		useStrength = false;
		checkEnded = true;
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

	Move() {
	}

	Move(int _x, int _y) {
		x = _x;
		y = _y;
	}

	bool operator<(const Move &other) const {
		if (x != other.x)
			return x < other.x;
		if (y != other.y)
			return y < other.y;
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
	}

	void printUgly() {
		print();
	}

	Move flip() {
		Move ret;
		ret.x = x;
		ret.y = BOARD_SIZE - 1 - y;
		return ret;
	}
};

map<ll, Move> openingMove;

float posval[3][BOARD_SIZE][BOARD_SIZE][4];
float gamePart[4];
float partCoefficient[120][3];
float threatValue[3];
float canMoveNValue[3];
float canMoveNCoefficient[3];
float strengthBehind[3];
float strengthNextto[3];
float strengthValue[3];
float strengthCoefficient[3];

void createOpeningBook() {
}

void computeEvalHelpers() {
	rep(i, 0, 120) {
		double x = (gamePart[1] * 80 - i) / (gamePart[1] * 80 - gamePart[0]);
		if (x < 0 || x > 1)
			partCoefficient[i][0] = 0;
		else
			partCoefficient[i][0] = x * x * (3 - 2 * x);
		x = (gamePart[1] * 80 - i) / (gamePart[1] * 80 - gamePart[3]);
		if (x < 0 || x > 1)
			partCoefficient[i][2] = 0;
		else
			partCoefficient[i][2] = x * x * (3 - 2 * x);
		partCoefficient[i][1] = 1 - partCoefficient[i][0] - partCoefficient[i][2];
	}
}

void initEvalConstants() {
	gamePart[0] = -1.0;
	gamePart[1] = 0.609613;
	gamePart[2] = -1.0;
	gamePart[3] = 80.0;
	threatValue[0] = 0.0;
	canMoveNValue[0] = -0.148244;
	canMoveNCoefficient[0] = -0.0650388;
	strengthBehind[0] = 0.1;
	strengthNextto[0] = 0.1;
	strengthValue[0] = -0.1;
	strengthCoefficient[0] = 0.1;
	posval[0][0][0][0] = 0.0;
	posval[0][0][0][1] = 0.0935007;
	posval[0][0][0][2] = 1.56269;
	posval[0][0][0][3] = 1.49961;
	posval[0][0][1][0] = 0.0;
	posval[0][0][1][1] = 0.087365;
	posval[0][0][1][2] = 0.577027;
	posval[0][0][1][3] = 1.63143;
	posval[0][0][2][0] = 0.0;
	posval[0][0][2][1] = -0.103239;
	posval[0][0][2][2] = 0.604722;
	posval[0][0][2][3] = 1.3895;
	posval[0][1][0][0] = 0.0;
	posval[0][1][0][1] = -0.335885;
	posval[0][1][0][2] = 0.0133169;
	posval[0][1][0][3] = 1.66645;
	posval[0][1][1][0] = 0.0;
	posval[0][1][1][1] = 0.00313067;
	posval[0][1][1][2] = -0.32243;
	posval[0][1][1][3] = 0.186923;
	posval[0][1][2][0] = 0.0;
	posval[0][1][2][1] = 0.0245223;
	posval[0][1][2][2] = 0.712852;
	posval[0][1][2][3] = 1.2837;
	posval[0][2][0][0] = 0.0;
	posval[0][2][0][1] = 0.352977;
	posval[0][2][0][2] = 0.108632;
	posval[0][2][0][3] = 1.50446;
	posval[0][2][1][0] = 0.0;
	posval[0][2][1][1] = 0.0544649;
	posval[0][2][1][2] = -0.633796;
	posval[0][2][1][3] = 0.10306;
	posval[0][2][2][0] = 0.0;
	posval[0][2][2][1] = -0.339173;
	posval[0][2][2][2] = -0.626246;
	posval[0][2][2][3] = 0.860917;
	threatValue[1] = 0.0;
	canMoveNValue[1] = 0.176123;
	canMoveNCoefficient[1] = 0.365522;
	strengthBehind[1] = 0.1;
	strengthNextto[1] = 0.1;
	strengthValue[1] = -0.1;
	strengthCoefficient[1] = 0.1;
	posval[1][0][0][0] = 0.0;
	posval[1][0][0][1] = 0.556644;
	posval[1][0][0][2] = 0.487323;
	posval[1][0][0][3] = 0.501082;
	posval[1][0][1][0] = 0.0;
	posval[1][0][1][1] = 0.0739222;
	posval[1][0][1][2] = 0.145298;
	posval[1][0][1][3] = 0.511793;
	posval[1][0][2][0] = 0.0;
	posval[1][0][2][1] = -0.139354;
	posval[1][0][2][2] = 0.0751189;
	posval[1][0][2][3] = 0.481377;
	posval[1][1][0][0] = 0.0;
	posval[1][1][0][1] = 0.249628;
	posval[1][1][0][2] = -0.112202;
	posval[1][1][0][3] = 0.509766;
	posval[1][1][1][0] = 0.0;
	posval[1][1][1][1] = 0.191606;
	posval[1][1][1][2] = 0.360187;
	posval[1][1][1][3] = 0.478988;
	posval[1][1][2][0] = 0.0;
	posval[1][1][2][1] = 0.0133127;
	posval[1][1][2][2] = -0.0456765;
	posval[1][1][2][3] = -0.0905369;
	posval[1][2][0][0] = 0.0;
	posval[1][2][0][1] = 0.0864951;
	posval[1][2][0][2] = 0.34266;
	posval[1][2][0][3] = 0.500389;
	posval[1][2][1][0] = 0.0;
	posval[1][2][1][1] = 0.444182;
	posval[1][2][1][2] = 0.633311;
	posval[1][2][1][3] = 0.39618;
	posval[1][2][2][0] = 0.0;
	posval[1][2][2][1] = 0.0643622;
	posval[1][2][2][2] = 0.161469;
	posval[1][2][2][3] = -0.493889;
	threatValue[2] = 0.0;
	canMoveNValue[2] = 0.428723;
	canMoveNCoefficient[2] = 0.375616;
	strengthBehind[2] = 0.1;
	strengthNextto[2] = 0.1;
	strengthValue[2] = -0.1;
	strengthCoefficient[2] = 0.1;
	posval[2][0][0][0] = 0.0;
	posval[2][0][0][1] = 0.438373;
	posval[2][0][0][2] = 0.417994;
	posval[2][0][0][3] = 0.420128;
	posval[2][0][1][0] = 0.0;
	posval[2][0][1][1] = 0.359574;
	posval[2][0][1][2] = 0.361511;
	posval[2][0][1][3] = 0.429062;
	posval[2][0][2][0] = 0.0;
	posval[2][0][2][1] = 0.384681;
	posval[2][0][2][2] = 0.29521;
	posval[2][0][2][3] = 0.422037;
	posval[2][1][0][0] = 0.0;
	posval[2][1][0][1] = 0.280865;
	posval[2][1][0][2] = 0.349141;
	posval[2][1][0][3] = 0.428504;
	posval[2][1][1][0] = 0.0;
	posval[2][1][1][1] = 0.315708;
	posval[2][1][1][2] = 0.44175;
	posval[2][1][1][3] = 0.423411;
	posval[2][1][2][0] = 0.0;
	posval[2][1][2][1] = 0.465982;
	posval[2][1][2][2] = 0.396334;
	posval[2][1][2][3] = 0.264675;
	posval[2][2][0][0] = 0.0;
	posval[2][2][0][1] = 0.243465;
	posval[2][2][0][2] = 0.391395;
	posval[2][2][0][3] = 0.423408;
	posval[2][2][1][0] = 0.0;
	posval[2][2][1][1] = 0.439686;
	posval[2][2][1][2] = 0.435945;
	posval[2][2][1][3] = 0.349913;
	posval[2][2][2][0] = 0.0;
	posval[2][2][2][1] = 0.478578;
	posval[2][2][2][2] = 0.414948;
	posval[2][2][2][3] = 0.115595;
	computeEvalHelpers();
}

void initOldEvalConstants() {
	computeEvalHelpers();
}

char *fileNameConstants;

void initFileConstants() {
	FILE *fin = fopen(fileNameConstants, "r");
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
	char f[BOARD_SIZE][BOARD_SIZE];
	char c[BOARD_SIZE][BOARD_SIZE];
	int turn;

	void init() {
		turn = 0;
		rep(i, 0, BOARD_SIZE)
			rep(j, 0, BOARD_SIZE) {
			f[i][j] = 0;
			c[i][j] = 0;
		}
	}

	State flip() {
		State ret = *this;
		ret.turn = turn;
		rep(i, 0, BOARD_SIZE)
			rep(j, 0, BOARD_SIZE) {
			ret.f[i][BOARD_SIZE - 1 - j] = f[i][j];
			ret.c[i][BOARD_SIZE - 1 - j] = c[i][j];
		}
		return ret;
	}

	vector<Move> getMoves() {
		vector<Move> ret;
		rep(i, 0, BOARD_SIZE)
			rep(j, 0, BOARD_SIZE) {
			if (c[i][j] != 1 + turn && c[i][j])
				continue;
			Move move;
			move.x = i;
			move.y = j;
			ret.push_back(move);
		}
		return ret;
	}

	int getLim(int i, int j) {
		int LIM = 4;
		if (i == 0 || i == BOARD_SIZE - 1)
			--LIM;
		if (j == 0 || j == BOARD_SIZE - 1)
			--LIM;
		return LIM;
	}

	void performMove(Move move) {
		if (move.x < 0) {
			return;
		}
		int x = move.x;
		int y = move.y;
		if (c[x][y] == 2 - turn) {
			print();
			move.print();
			assert(0);
		}
		++f[x][y];
		c[x][y] = 1 + turn;
		int iterN = 0;
		while (true) {
			++iterN;
			vector<pair<int, int>> v;
			rep(i, 0, BOARD_SIZE)
				rep(j, 0, BOARD_SIZE) {
				if (f[i][j] >= getLim(i, j)) {
					v.emplace_back(i, j);
				}
			}
			if (v.empty())
				break;
			if (eval() != 0.5)
				break;
			//print();
			rep(i, 0, v.size()) {
				int x = v[i].first;
				int y = v[i].second;
				f[x][y] -= getLim(x, y);
				if (!f[x][y])
					c[x][y] = 0;
			}
			rep(i, 0, v.size()) {
				rep(j, 0, 4) {
					int nx = v[i].first + dx[j];
					int ny = v[i].second + dy[j];
					if (nx < 0 || ny < 0 || nx >= BOARD_SIZE || ny >= BOARD_SIZE)
						continue;
					++f[nx][ny];
					c[nx][ny] = 1 + turn;
				}
			}
		}
		turn ^= 1;
	}

	void print(int indent) {
		rep(j, 0, indent)
			printf("  ");
		rep(j, 0, 18)
			printf("_");
		printf("\n");
		rep(i, 0, 5) {
			rep(j, 0, indent)
				printf("  ");
			rep(j, 0, 5) {
				printf(" %d%d", c[i][j], f[i][j]);
			}
			printf("|");
			printf("\n");
		}
		rep(j, 0, indent)
			printf("  ");
		rep(j, 0, 18) {
			printf("‾");
		}
		printf("\n");
	}

	void printUgly(FILE *fout) {
		rep(i, 0, BOARD_SIZE) {
			rep(j, 0, BOARD_SIZE) {
				fprintf(fout, "%d %d ", c[i][j], f[i][j]);
			}
			fprintf(fout, "\n");
		}
		fprintf(fout, "%d\n", (int)turn);
	}

	void print() {
		print(0);
	}

	int fuzzyEval() {
		//print();
		float ret = 0;
		int movesLeft = 0;
		int moveN = 0;
		int canMoveN[2] = {0, 0};
		rep(i, 0, BOARD_SIZE)
			rep(j, 0, BOARD_SIZE) {
			moveN += f[i][j];
			if (c[i][j] == 1)
				canMoveN[0]++;
			if (c[i][j] == 2)
				canMoveN[1]++;
		}
		//movesLeft=80-moveN;
		movesLeft = moveN;
		float timeCoefficient[3];
		rep(partIndex, 0, 3) {
			timeCoefficient[partIndex] = partCoefficient[movesLeft][partIndex];
		}
		rep(partIndex, 0, 3) {
			//ret += timeCoefficient[partIndex]*threatValue[partIndex]*hasThreat[turn];
			ret += timeCoefficient[partIndex] * canMoveNValue[partIndex] * tanh(canMoveNCoefficient[partIndex] * (canMoveN[turn] - canMoveN[!turn]));
		}
		rep(i, 0, BOARD_SIZE) {
			rep(j, 0, BOARD_SIZE) {
				int p = c[i][j];
				int mul = 0;
				if (p == 1)
					mul = 1;
				else if (p == 2)
					mul = -1;
				else
					continue;
				if (turn)
					mul = -mul;
				rep(k, 0, 3) {
					int x = i;
					int y = j;
					if (y >= 3)
						y = 4 - y;
					if (x >= 3)
						x = 4 - x;
					int num = f[i][j];
					if (num >= 4)
						num = 3;
					ret += mul * posval[k][x][y][num] * timeCoefficient[k];
				}
			}
		}
		float tmp = sigmoid(ret);
		return ret * 10000;
	}

	float eval() {
		bool exists[3] = {0, 0, 0};
		int num = 0;
		rep(i, 0, BOARD_SIZE)
			rep(j, 0, BOARD_SIZE) {
			exists[c[i][j]] = 1;
			num += f[i][j];
		}
		if (num < 2)
			return 0.5;
		if (exists[1] && !exists[2])
			return (turn == 0);
		if (exists[2] && !exists[1])
			return (turn == 1);
		return 0.5;
	}

	bool operator<(const State &other) const {
		return 0;
	}

	ll getHash() {
		ll ret = 2573 * turn;
		rep(i, 0, BOARD_SIZE)
			rep(j, 0, BOARD_SIZE) {
			ret = (791 * ret + (f[i][j] + 10 * c[i][j]) ^ ret) % 1844319728172384753LL;
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
#ifdef DEBUG_POLICY
	s->print();
	//getchar();
#endif
	float e = s->eval();
	if (e != 0.5)
		return e;
	++rolloutIterations;
	vector<Move> moveList = s->getMoves();
	int moveN = moveList.size();
	int totalScore = 0;
	rep(i, 0, moveN) {
		scoreList[i] = 1;
		Move m = moveList[i];
		if (bot.preferExplode && s->getLim(m.x, m.y) == s->f[m.x][m.y] + 1)
			scoreList[i] = 3;
		totalScore += scoreList[i];
	}
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
			rep(t, 0, 2) {
				if (t) {
					tmpState = tmpState.flip();
					tmpMove = tmpMove.flip();
				}
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
		rep(t, 0, 2) {
			tmpState = tmpState.flip();
			ll h = tmpState.getHash();
			massiveStats[h] = make_pair(score, isLeaf ? -1 : n);
		}
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
			rep(t, 0, 2) {
				tmpState = tmpState.flip();
				tmpMove = tmpMove.flip();
				openingMove[tmpState.getHash()] = tmpMove;
				fprintf(file, "openingMove[%lld]=Move(%d,%d);\n", tmpState.getHash(), tmpMove.x, tmpMove.y);
				/*puts("New book move:");
				tmpState.print();
				tmpMove.print();
				State tmpState2=tmpState;
				tmpState2.performMove(tmpMove);
				tmpState2.print();
				getch();*/
			}
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
	if (depth > 100)
		printf("Too large depth!!!");
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
		rep(t, 0, 2) {
			tmpState = tmpState.flip();
			ll h = tmpState.getHash();
			massiveStats[h] = make_pair(score, isLeaf ? -1 : n);
		}
		return make_pair(totSc, totN);
	}
	alpha = max(alpha, lowerBound);
	beta = min(beta, upperBound);
	maxDepth = max(maxDepth, depth);
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
				float e = s->eval();
				if (depth > 1 && e == 0.0) {
					isLeaf = true;
					score = 1;
					return make_pair(score, 1);
				}
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
					if (e == 0) {
						children.back().second->score = 0;
						children.back().second->isLeaf = true;
					}
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
		if (moves.empty()) {
			assert(0);
			isLeaf = true;
			score = 0;
			return make_pair(score, 1);
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
		rep(t, 0, 2) {
			tmpState = tmpState.flip();
			ll h = tmpState.getHash();
			massiveStats[h] = make_pair(score, isLeaf ? -1 : n);
		}
	}
	return make_pair(totSc, totN);
}

State parseState() {
	State ret;
	rep(i, 0, BOARD_SIZE)
		rep(j, 0, BOARD_SIZE) {
		char inp[5];
		ignore = scanf("%s", inp);
		ret.c[i][j] = inp[0] - '0';
		ret.f[i][j] = inp[1] - '0';
	}
	int turn;
	ignore = scanf("%d", &turn);
	ret.turn = turn - 1;
	return ret;
}

State parseState2() {
	State ret;
	int i = 0, j = 0;
	char s[200];
	int p = 0;
	ret.init();
	rep(i, 0, BOARD_SIZE)
		rep(j, 0, BOARD_SIZE) {
		ret.f[i][j] = 0;
		ret.c[i][j] = 0;
	}
	rep(i, 0, BOARD_SIZE)
		rep(j, 0, BOARD_SIZE)
			rep(P, 0, 2) {
		int in;
		ignore = scanf("%d", &in);
		if (P)
			ret.f[i][j] = in;
		else
			ret.c[i][j] = in;
	}
	ret.print();
	int in;
	ignore = scanf("%d", &in);
	ret.turn = in;
	return ret;
}

int statesChecked;
int startD = 0;
bool printStuff;

void createMassiveStats() {
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
			return Move(-2, -2);
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
		rep(i, 0, children.size()) {
			ABNode *child = children[i];
			if (child->isLeaf) {
				if (-child->leafScore > lowerBounds[d])
					lowerBounds[d] = -child->leafScore;
				//lowerBounds[d]=max(lowerBounds[d], -child->leafScore);
			}
			else {
				if (child->lowerBounds.size() >= d) {
					if (-child->upperBounds[d - 1] > lowerBounds[d])
						lowerBounds[d] = -child->upperBounds[d - 1];
					//lowerBounds[d]=max(lowerBounds[d], -child->upperBounds[d-1]);
				}
			}
		}
		if (lowerBounds[d] > 999950) {
			//if(lowerBounds[d] == INF)
			isLeaf = true;
			leafScore = lowerBounds[d];
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

#define AB_MAP_SIZE 21
#define AB_MAP_LIST_SIZE 5

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

	ABNode *add(ll h, ABNode *node) {
		int H = (h & ((1LL << AB_MAP_SIZE) - 1));
		if (tableListSize[H] < AB_MAP_LIST_SIZE) {
			tableH[H][tableListSize[H]] = h;
			tableN[H][tableListSize[H]++] = node;
		}
		else {
			tableH[H][tableListPos[H]] = h;
			tableN[H][tableListPos[H]] = node;
			++tableListPos[H];
			if (tableListPos[H] == AB_MAP_LIST_SIZE)
				tableListPos[H] = 0;
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
	rep(i, 0, allocated.size())
		allocatedIndices.push_back(i);
	//for(auto el : ABHashMap){
	//delete el.second;
	//}
	ABHashMap.clear();
}

bool canReach[BOARD_SIZE][BOARD_SIZE];

int ABNode::rec(int d, int alpha, int beta) {
	if (aborted)
		return 0;
	int startAlpha = alpha;
	int startBeta = beta;
	//s.print(startD-d);
	/*if(d == startD)
		recPrint(0, 1);*/
	statesDone += 1;
	if (statesDone > checkTime && startD > 1) {
		checkTime += 1000;
		float timeElapsed = timeFactor * ((float(clock() - startTime)) / CLOCKS_PER_SEC);
		if (timeElapsed > globalTimeLimit) {
			aborted = 1;
			return 0;
		}
	}
	if (isLeaf) {
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
		if (bot.checkEnded && d != startD) {
			float val = s.eval();
			if (val != 0.5) {
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
		}
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
			newState.performMove(move);
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

Move findMove(State s, int millisecondsLeft) {
	fuzzyPreweightN = bot.fuzzyPreweightN;
	curTurn = s.turn;
	numEvals = 0;
	globalTimeLimit = bot.timeLimit; //*exp(-(rand()%100)*0.01);
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
	int e = s.fuzzyEval();
	cerr << "fuzzy eval: " << e << endl;
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
	Move bestMove(-1, -1);
	Move lastBestMove = bestMove;
	bool lastBestMoveExists = 0;
	bool anyMove = false;
	int bestScore = -1000000001;
	vector<Move> moves = s.getMoves();
	if (moves.empty()) {
		s.print();
		assert(0);
	}
	if (moves[0].x == -1)
		return Move(-2, -2);
#ifdef DEBUG_PRINT
	if (!tuning)
		cerr << bot.name << " ";
#endif
	int timeLimit = bot.timeLimit;
	checkTime = 1000;
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
				if (iterN > 1000)
					break;
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
		if (generateOpeningBook) {
			FILE *stats = fopen("stats.txt", "w");
			for (auto entry : massiveStats) {
				fprintf(stats, "%lld %.1f %lld\n", entry.first, entry.second.first, entry.second.second);
			}
			fclose(stats);
		}
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
			expectedScoreSaved = root->score;
		}
		else {
			cerr << "Expected score: " << root->score / root->n << endl;
			expectedScoreSaved = root->score / root->n;
		}
#endif
		if (responsibleMemoryUsage && !bot.useHashMap) {
			deleteNodesRecursively = true;
			delete (root);
			deleteNodesRecursively = false;
		}
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
			/*if(rand()%3 < 2 && movesDone < 5)
			bot=randomBot;*/
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
			if (true) {
				float e = s.eval();
				if (s.eval() > 0.9) {
					printf("end eval: %f\n", e);
					stats[turn ^ startingBot][2]++;
					stats[turn ^ startingBot ^ 1][0]++;
					finalResult = !turn;
					break;
				}
				else if (s.eval() < 0.1) {
					printf("end eval: %f\n", e);
					stats[turn ^ startingBot][0]++;
					stats[turn ^ startingBot ^ 1][2]++;
					finalResult = turn;
					break;
				}
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
				if ((finalResult == 0) == (bot1.name == "bot41"))
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
		int js;
		Move move;
		fin >> move.x >> move.y >> js;
		openingMove[h] = move;
	}
}

void init() {
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
		while (openingMove.count(s.getHash())) {
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
				Move move = findMove(s, 10000);
				s.performMove(move);
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
		FILE *openingBook = fopen("openings.txt", "w");
		for (auto entry : openingMove) {
			fprintf(openingBook, "openingMove[%lld]=Move(%d,%d);\n", entry.first, entry.second.x, entry.second.y);
		}
		s.performMove(move);
		s.print();
		fclose(openingBook);
	}
}

int main(int argc, char *argv[]) {
	init();
	startTime = clock();
	srand(time(0));
	Bot bot1("bot1");
	bot1.useAlphaBeta = false;
	bot1.useMCTS = true;
	bot1.undoMovesDuringRollout = false;
	bot1.usePseudoRandom = true;
	bot1.completeSearchTree = true;
	bot1.useAccurateRollout = true;
	bot1.explorationCoefficient = 0.5;
	bot1.setLeafUsingRollout = true;
	bot1.useTimeManagement = true;
	bot1.useHashMap = true;
	bot1.timeSaveForEnd = true;
	bot1.useExclusion = true;
	bot1.stayInSubtree = true;
	bot1.subtreeExploreNumber = 1;
	bot1.useEffectiveN = false;
	bot1.useOpeningBook = false;
	bot1.timeLimit = 2;
	bots.push_back(bot1);
	Bot bot2 = bot1;
	bot2.name = "bot2";
	bot2.explorationCoefficient = 0.45;
	//bot2.preferExplode=true;
	//bot2.timeLimit=0.1;
	Bot bot3 = bot2;
	bot3.timeLimit = 1;
	bot3.name = "bot3";
	Bot bot4("bot4");
	bot4.useMCTS = false;
	bot4.useFancyAB = true;
	bot4.timeLimit = 1;
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
	bot4.useStrength = true;
	Bot bot5 = bot4;
	bot5.name = "bot5";
	bot5.probCutCoefficient = 50;
	bot5.linearProbCutCoefficient = 500;
	bot5.probCutSmallDepthBonus = 300;
	bot5.timeLimit = 0.9;
	bot5.useOpeningBook = true;
	//bot5.useOpeningBook=true;
	randomBot = bot2;
	initEvalConstants();
	bot = bot5;

	//makeOpeningBook();
	State curState = parseState();
	Move move = findMove(curState, 10000);
	move.printUgly();
	printf(" %d %d %d\n", lowerBoundsSaved, numEvalsSaved, depthSaved);
	//printf("%.4f\n", expectedScoreSaved);
}