#include<iostream>
#include"headers/conio.h"
#include<time.h>
#include<string>
using namespace std;

bool gameOver;
string name;
int score, tailLen=0, tailX[100], tailY[100];
int x, y, f_x, f_y;
int hight=25, width=60;
char ch,oldCh;
enum eDirection { START=0, UP, DOWN, LEFT, RIGHT };
eDirection dir;

void start() {
	cout<<"Instructions :\n  W : to move forward\n  S : to move backward\n  A : to move left\n  D : to move right\n\nType your name and hit enter to start the game : "<<endl;
	cin>>name;
	gameOver = false;
	score = 0;
	dir = START;
	y = hight / 2;
	x = width / 2;
	f_y = rand() % hight + 1;
	f_x = rand() % width + 1;
}
bool doExist(int a, int b) {
	bool ret = false;
	for (int i = 0; i < tailLen; ++i) {
		if (tailX[i] == a && tailY[i] == b)
			ret = true;
	} return ret;
}
void draw() {
	system("clear");
	for (int i = 0; i < hight; ++i)
	{
		for (int j = 0; j < width; ++j) {
			if (i == 0 || i == hight-1) {
				if (j == 0 || j == width - 1)
					cout<<"##";
				else
					cout<<"=";
			} else {
				if (j == 0 || j == width-1) {
					cout<<"||";
				} else if (j == x && i == y) {
					cout<<"S";
				} else if (i == f_y && j == f_x) {
					cout<<"o";
				} else if (doExist(j,i)) {
					cout<<"s";
				} else {
					cout<<" ";
				}
			}
		} cout<<endl;
	} cout<<"\nPlayer name : "<<name<<"\nYour score is : "<<score<<"\nPress (x) to end the game."<<endl;
}
void input() {
	if (kbhit()) {
		ch = getch();
		switch(ch) {
			case 'a':
				if (oldCh != 'd')
					oldCh = ch,	dir = LEFT;
				break;
			case 'w':
				if (oldCh != 's')
					oldCh = ch,	dir = UP;
				break;
			case 's':
				if (oldCh != 'w')
					oldCh = ch,	dir = DOWN;
				break;
			case 'd':
				if (oldCh != 'a')
					oldCh = ch, dir = RIGHT;
				break;
			case 'x':
				gameOver = true;
				break;
		}
	}
}
void sleep(int milisec){
	clock_t time_end;
	time_end = clock() + milisec * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end)
	{
	}
}
void logic() {
	int oldX = x, oldX2, oldY = y, oldY2;
	switch (dir) {
		case LEFT:
			--x;
			break;
		case UP:
			--y;
			break;
		case DOWN:
			++y;
			break;
		case RIGHT:
			++x;
			break;
		default:
			break;
	}
	if (x <= 0 || x >= width-1 || y <= 0 || y >= hight-1)
		gameOver = true;
	if (x == f_x && y == f_y) {
		f_x = rand() % width + 1;
		f_y = rand() % hight + 1;
		score += 5;
		tailLen++;
	}
	for (int i = 0; i < tailLen; ++i) {
		if (tailLen == 1)
		{
			tailX[0] = oldX;
			tailY[0] = oldY;
		} else {	
			oldX2 = tailX[i];
			oldY2 = tailY[i];
			tailX[i] = oldX;
			tailY[i] = oldY;
			oldX = oldX2;
			oldY = oldY2;
		}
	}
	for (int i=0; i < tailLen; ++i) {
		if (tailX[i] == x && tailY[i] == y){
			gameOver = true;
		}
	}

}

int main() {
	start();
	while (!gameOver) {
		draw();
		sleep(90);
		input();
		logic();
	}
	return 0;
}	
