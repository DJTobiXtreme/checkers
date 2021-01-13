#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <vector>
#include <string>
using namespace std;

class GameLogic {
public:
	GameLogic();
	int getInfo(int x, int y);
	int getCurrentPlayer();
	int getScore1();
	int getScore2();
	string getLastMessage();
	bool input(int x1, int y1, int x2, int y2);
	
private:
	void start();
	bool is_in_board(int x,int y);
	tuple<int,int> is_valid_normal_p1(int x1, int y1, int x2, int y2, bool b);
	tuple<int,int> is_valid_normal_p2(int x1, int y1, int x2, int y2, bool b);
	tuple<int,int> is_valid_queen(int x1, int y1, int x2, int y2, bool b);
	bool is_valid(int x1, int y1, int x2, int y2, bool b);
	void check_queens();
	void check_eat_again(int x1, int y1);
	vector<vector<int>> m;
	int boardSize;
	int score1, score2;
	int player;
	int round;
	string lastMessage;
};

#endif

