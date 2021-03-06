#include "pch.h"
#include <cstdio>
#include <time.h>
#include <cstdlib>
using namespace std;
struct poker {
	const char *rank;
	const char *suit;
	int num;
};
char ch;//读取输入
int check = 10;//检查总值是否超过21
int count = 0;//记发放扑克牌的序数
int playercount = 0;//记A还是B叫牌
int total[2] = { 0,0 };//记A、B牌的总值
int quitcount[2] = { 1,1 };//记A、B是否都不叫牌
poker card[52];
const char *srank[] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
const char *ssuit[] = { "Spade ","Heart ","Diamond ","Club " };
void fill(poker *scard,const char *crank[],const char *csuit[]);//扑克牌组的初始化
void shuffle(poker *scard);//完成洗牌过程
int showcard(poker *scard,int n);//完成一次发牌过程
void gameon();
int main()
{
	fill(card,srank,ssuit);
	shuffle(card);
	printf("DO YOU WANT TO PLAY A GAME?\n");
	printf("(y to start,q to quit):");
	ch = getchar();
	if (getchar() != '\n')
	{
		printf("no more than 1 letter.\n");
		while (getchar() != '\n') continue;
	}//处理错误输入
	if (ch == 'y') {
		showcard(card, count);
		printf("PRESS ENTER TO CLEAR THE SCREEN.\n");
		getchar();
		system("cls");//清屏
		showcard(card, count);
		printf("PRESS ENTER TO CLEAR THE SCREEN.\n");
		getchar();
		system("cls");
		gameon();
	}//游戏的第一轮发牌
	printf("GAME OVER.\nBYE.\n");
	return 0;
}
void fill(poker *scard, const char *crank[], const char *csuit[])
{
	for (int i = 0; i < 52; i++)
	{
		scard[i].rank = crank[i % 13];
		scard[i].suit = csuit[i / 13];
		scard[i].num = i % 13 + 1;
	}
}
void shuffle(poker *scard)
{
	srand(time(NULL));
	poker temp;
	for (int i = 0; i < 52; i++)
	{
		int j = rand() % 52;
		temp = scard[i];
		scard[i] = scard[j];
		scard[j] = temp;
	}
}
int showcard(poker *scard,int n)
{
	printf("Player %d:", playercount + 1);
	printf("YOU GET THE %s%s.\n", scard[n].suit, scard[n].rank);
	total[playercount] += scard[n].num;
	if (total[playercount] > 21) {
		printf("BOOM!YOU LOSE.THE TOTAL OF YOUR CARD IS %d.\n", total[playercount]);
		return 1;
	}
	playercount++;
	playercount %= 2;//player记数
	count++;
	return 0;
}
void gameon()
{
	printf("Player %d,DO YOU WANT ANOTHER CARD?\n", playercount + 1);
	printf("(y to continue ,n to stop):");
	while ((ch = getchar()) != 'q')
	{
		if (getchar() != '\n')
		{
			printf("no more than 1 letter.\n");
			while (getchar() != '\n')
				continue;
			ch = getchar();
			getchar();
		}
		switch (ch)
		{
		case 'y':
			printf("OK.\n");
			check=showcard(card, count);
			if (check) return;
			break;
		case 'n':
			printf("NOT BAD\n");
			quitcount[playercount] = 0;
			if (quitcount[0] == 0 && quitcount[1] == 0) {
				printf("Player 1,THE TOTAL OF YOUR CARD IS %d.\n", total[0]);
				printf("Player 2,THE TOTAL OF YOUR CARD IS %d.\n", total[1]);
				if (total[0] > total[1]) {
					printf("Player 1 WINS.\n");
					return;
				}
				else if (total[0] < total[1]) {
					printf("Player 2 WINS.\n");
					return;
				}
				else {
					printf("NOBODY WINS.\n");
					return;
				}
			}
			playercount++;
			playercount %= 2;
			break;
		}
		printf("PRESS ENTER TO CLEAR THE SCREEN.\n");
		getchar();
		system("cls");
		printf("Player %d,DO YOU WANT ANOTHER CARD?\n", playercount + 1);
		printf("(y to continue ,n to stop):");
	}
}