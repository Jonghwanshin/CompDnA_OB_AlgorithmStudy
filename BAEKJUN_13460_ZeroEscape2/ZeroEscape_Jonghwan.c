#include <stdio.h>

#define MAX_SIZE 30
#define STACK_SIZE 30
#define MAX_DIST 900

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#define BLUE 0
#define RED 1

int mapSizeX, mapSizeY;
int initPosRedX, initPosRedY;
int initPosBlueX, initPosBlueY;
int finalPosX, finalPosY;
int map[MAX_SIZE][MAX_SIZE];
char mapChar[MAX_SIZE][MAX_SIZE];
int minimumMovement;

int rollToEdge(int MOVE, int* x, int* y) {
	int movedDist = 0;
	int posX, posY;
	posX = *x;
	posY = *y;
	switch(MOVE){
	case UP:
		while (map[posX][posY] != MAX_DIST || (posX != finalPosX && posY != finalPosY)) {
			posY--;
			movedDist++;
		}
		break;
	case DOWN:
		while (map[posX][posY] != MAX_DIST || (posX != finalPosX && posY != finalPosY)) {
			posY++;
			movedDist++;
		}
		break;
	case RIGHT:
		while (map[posX][posY] != MAX_DIST || (posX != finalPosX && posY != finalPosY)) {
			posX++;
			movedDist++;
		}
		break;
	case LEFT:
		while (map[posX][posY] != MAX_DIST || (posX != finalPosX && posY != finalPosY)) {
			posX--;
			movedDist++;
		}
		break;
	}
	*x = posX;
	*y = posY;
	return movedDist;
}

void DFS(int redPosX, int redPosY, int bluePosX, int bluePosY, int l) {
	// 도착 지점에 도착했을 경우
	int tempRedPosX,tempRedPosY,tempBluePosX,tempBluePosY;
	int movement = 0;
	if (redPosX == finalPosX && redPosY == finalPosY)
	{
		// 현재 최소값이 l보다 크면, l이 작은 것이므로 l를 최소값으로 지정
		if (minimumMovement > l) minimumMovement = l;
		return;
	}
	tempRedPosX = redPosX; tempRedPosY = redPosY;
	tempBluePosX = bluePosX; tempBluePosY = bluePosY;
	map[tempRedPosX][tempRedPosY] = 0; // 방문했음을 표시하기 위해 MAX_DIST 대입
	map[tempBluePosX][tempBluePosY] = 0; // 방문했음을 표시하기 위해 MAX_DIST 대입

	for (int i = 0; i <= 3; i++) {
		if (rollToEdge(i, &tempRedPosX, &tempRedPosY)) {
			rollToEdge(i, &tempBluePosX, &tempBluePosY);
			DFS(tempRedPosX, tempRedPosY, tempBluePosX, tempBluePosY, l + 1);
		}
	}
	//map[][x] = 0; // 지나간 자리를 원상태로 되돌리기 위해 0을 대입

}

int main() {
	char c;
	int i, j;
	minimumMovement = MAX_DIST; // 모든 경로를 돌아다녀도 n * n이니, 이를 최소값으로 지정해둔다
	//input about map size
	scanf_s("%d %d", &mapSizeX, &mapSizeY);
	printf("%d %d", mapSizeX, mapSizeY);
	for (i = 0; i < mapSizeY; i++) {
		for (j = 0; j < mapSizeX; j++) {
			scanf_s("%c", &mapChar[i][j]);
		}
	}

	for (i = 0; i < mapSizeY; i++) {
		for (j = 0; j < mapSizeX; j++) {
			printf("%c", mapChar[i][j]);
		}
	}
	
	for (i = 0; i < mapSizeY; i++) {
		for (j = 0; j < mapSizeX; j++) {
			switch (mapChar[i][j]) {
			case '#':
				map[i][j] = MAX_DIST;
				break;
			case 'R':
				map[i][j] = MAX_DIST;
				initPosRedX = j;
				initPosRedY = i;
				break;
			case 'B':
				map[i][j] = MAX_DIST;
				initPosBlueX = j;
				initPosBlueY = i;
				break;
			case 'O':
				map[i][j] = 0;
				finalPosX = j;
				finalPosY = i;
				break;
			case '.':
				map[i][j] = 0;
				break;
			}
		}
	}

	for (i = 0; i < mapSizeY; i++) {
		for (j = 0; j < mapSizeX; j++) {
			printf("%3d", &map[i][j]);
		}
		printf("\n");
	}

	//DFS(initPosRedX, initPosRedY, initPosBlueX, initPosBlueY, 1); // DFS 시작!
	printf("최단 횟수: %d\n", minimumMovement);
	return 0;

}