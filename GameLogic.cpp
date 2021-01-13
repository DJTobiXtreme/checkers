#include "GameLogic.h"
#include <tuple>
#include <iostream>
#include <iomanip>
using namespace std;

GameLogic::GameLogic() : boardSize(8), score1(0), score2(0), player(1), round(0),
	lastMessage("Inicio del juego"), m(8,vector<int>(8)){
	start();
}


void GameLogic::start ( ) {
	int aux;
	for(int i=0;i<boardSize;i++){
		if (i<3) aux = 2;
		else if (i>4) aux = 1;
		else aux = 0;
		if (i%2==0) {
			for(int j=1;j<boardSize;j+=2){
				m[i][j] = 9;
				m[i][j-1] = aux;
			}
		}
		else {
			for(int j=0;j<boardSize;j+=2){
				m[i][j] = 9;
				m[i][j+1] = aux;
			}
		}
	}
}


bool GameLogic::is_in_board (int x, int y) {
	if (0<=x && x<boardSize && 0<=y && y<boardSize) return true;
	return false;
}

tuple<int,int> GameLogic::is_valid_normal_p1 (int x1, int y1, int x2, int y2, bool b) {
	if (x1+1==x2 && y1-1==y2) return make_tuple(x2+1,y2-1);
	else if (x1-1==x2 && y1-1==y2) return make_tuple(x2-1,y2-1);
	else {
		if (b) { 
			lastMessage = "No es un movimiento valido para tu pieza";
			cout<<"No es un movimiento valido para tu pieza"<<endl;
		}
		return make_tuple(-2,-2);
	}
}

tuple<int,int> GameLogic::is_valid_normal_p2 (int x1, int y1, int x2, int y2, bool b) {
	if (x1-1==x2 && y1+1==y2) return make_tuple(x2-1,y2+1);
	else if (x1+1==x2 && y1+1==y2) return make_tuple(x2+1,y2+1);
	else {
		if (b) { 
			lastMessage = "No es un movimiento valido para tu pieza";
			cout<<"No es un movimiento valido para tu pieza"<<endl;
		}
		return make_tuple(-2,-2);
	}
}

tuple<int,int> GameLogic::is_valid_queen (int x1, int y1, int x2, int y2, bool b) {
	int dx = x1-x2; int dy = y1-y2;
	if(dx == dy && dx>0){
		//Diagonal principal hacia arriba
		for(int i = 1; x2+i<x1;i++){
			if (m[y2+i][x2+i]!=0){
				if (b) {
					lastMessage = "No puedes saltearte fichas";
					cout<<"No puedes saltearte fichas"<<endl;
				}
				return make_tuple(-2,-2);
			}
		}
		return make_tuple(x2-1,y2-1);
	} else if (dx == dy && dx<0){
		//Diagonal principal hacia abajo
		for(int i = 1; x1+i<x2;i++){
			if (m[y2+i][x2+i]!=0){
				if (b) {
					lastMessage = "No puedes saltearte fichas";
					cout<<"No puedes saltearte fichas"<<endl;
				}
				return make_tuple(-2,-2);
			}
		}
		return make_tuple(x2+1,y2+1);
	} else if (dx == -dy && dx>0){
		//Diagonal secundaria hacia arriba
		for(int i = 1; x2+i<x1;i++){
			if (m[y2-i][x2+i]!=0){
				if (b){
					lastMessage = "No puedes saltearte fichas";
					cout<<"No puedes saltearte fichas"<<endl;
				}
				return make_tuple(-2,-2);
			}
		}
		return make_tuple(x2-1,y2+1);
	} else if (dx == -dy && dx<0){
		//Diagonal secundaria hacia abajo 
		for(int i = 1; x1+i<x2;i++){
			if (m[y2-i][x2+i]!=0){
				if (b){
					lastMessage = "No puedes saltearte fichas";
					cout<<"No puedes saltearte fichas"<<endl;
				}
				return make_tuple(-2,-2);
			}
		}
		return make_tuple(x2+1,y2-1);
	} else{
		if (b){
			lastMessage = "No puedes saltearte fichas";
			cout<<"No puedes saltearte fichas"<<endl;
		}
		return make_tuple(-2,-2); 
	}
}

bool GameLogic::is_valid (int x1, int y1, int x2, int y2, bool b) {
	int p1 = m[y1][x1];
	int p2 = m[y2][x2];
	
	if (p1!=player && p1!=player+2){
		if (b){
			lastMessage = "No puedes elejir una pieza que no sea tuya o un lugar vacio";
			cout<<"No puedes elejir una pieza que no sea tuya o un lugar vacio"<<endl;
		}
		return false;
	};
	
	int x3; int y3;
	
	switch (p1) {
	case 1:
		tie(x3,y3) = is_valid_normal_p1(x1,y1,x2,y2,b);
		break;
	case 2:
		tie(x3,y3) = is_valid_normal_p2(x1,y1,x2,y2,b);
		break;
	case 3: case 4:
		tie(x3,y3) = is_valid_queen(x1,y1,x2,y2,b);
		break;
	}
	
	if (x3==-2) {
		return false;
	}
	
	
	if (p2==0){
		if (!b) return false;
		m[y2][x2] = p1;
		m[y1][x1] = 0;
		cout<<"Pieza movida"<<endl;
		return true;
	}

	
	if (p2 == player && p2 == player+2){
		if (b){
			lastMessage = "No puedes pisar tu propia pieza";
			cout<<"No puedes pisar tu propia pieza"<<endl;
		}
		return false;
	}
	if (!is_in_board(x3,y3)) {
		if (b){
			lastMessage = "Al comer la pieza te sales fuera del tablero";
			cout<<"Al comer la pieza te sales fuera del tablero"<<endl;
		}
		return false;
	}
	if (m[y3][x3]!=0){
		if (b){
			lastMessage = "Tu lugar luego de comer la pieza esta ocupado";
			cout<<"Tu lugar luego de comer la pieza esta ocupado"<<endl;
		}
		return false;
	}
	
	m[y1][x1] = 0;
	m[y2][x2] = 0;
	m[y3][x3] = p1;
	(player==1) ? score1++ : score2++;
	cout<<"Pieza comida"<<endl;
	check_eat_again(x3,y3);
	return true;
}

void GameLogic::check_queens ( ) {
	if (player==1){
		for(int j=0;j<boardSize;j++){
			if (m[0][j]==1) {
				cout<<"Reina"<<endl;
				m[0][j] = 3;
			}
		}
	} else {
		for(int j=0;j<boardSize;j++){
			if (m[7][j]==2) {
				cout<<"Reina"<<endl;
				m[7][j] = 4;
			}
		}
	}
}

bool GameLogic::input (int x1, int y1, int x2, int y2) {
	if (is_valid(x1,y1,x2,y2,true)){
		check_queens();
		round++;
		player = (round%2)+1;
	}
}

void GameLogic::check_eat_again (int x1, int y1) {
	for(int i=0;i<8;i++) { 
		for(int j=0;j<8;j++) { 
			is_valid(x1,y1,i,j,false);
		}
	}
}

int GameLogic::getInfo (int x, int y) {
	return m[y][x];
}

int GameLogic::getCurrentPlayer ( ) {
	return player;
}

int GameLogic::getScore1 ( ) {
	return score1;
}

int GameLogic::getScore2 ( ) {
	return score2;
}

string GameLogic::getLastMessage ( ) {
	return lastMessage;
}

