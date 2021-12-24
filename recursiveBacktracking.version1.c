//미로생성 알고리즘 소개 사이트 http://www.jamisbuck.org/mazes/
/*
임의의 출발점에서 전진할 수 있는 한 방향(좌우상하 중)을 임의로 선택하여 벽을 허물고 전진(미로 표시)하다가
더 이상 전진할 수 없으면 이전으로 돌아가면서 전진할 수 있는 다른 방향으로 계속 미로를 만들어 나가는 방법
전진할 수 없는 조건은 배열 범위를 벗어나거나 기존 미로를 만나는 경우
기존 미로쪽으로 벽을 허물면 사이클이 형성되어 맴도는 경로가 만들어지기 때문에 배제되어야 함
*/

/*
미로 행열에 벽을 포함하지 않는 방법으로
미로 방을 가로 c, 세로 r개로 만들고자 할 경우
미로 행열의 행 크기는 r, 열 크기는 c로 준비하고
각 미로 방에서 허문 벽의 방향을 보관하고 있다가 출력할 때 적용함
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//미로 방 정의
struct cell {

	char searchDir; //각 방에서의 탐색 방향

	char mazeDir; //각 방에서의 미로 생성 방향

};

//미로 크기, row는 행, col은 열 크기
int row, col;

//미로를 재귀적 귀로 호출 방법으로 만들어 나감
void mazeCreating(struct cell** mazeMark, int i, int j) {
	int view_i, view_j, dir;
	int move[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };//상하좌우

	while (mazeMark[i][j].searchDir < 15) { //상하좌우 모두 살펴 볼 때까지 반복

		do {

			dir = rand() % 4; //4방향 중 임의의 방향

		} while ((mazeMark[i][j].searchDir & (1 << dir)) >= 1); //dir이 살펴본 방향이면 dir 다시 구함

		//이동 방향을 표시함. dir이 3이면 오른쪽에서 세 번째가 1이 되게 함. 00000100
		//4방향 모두 살펴보았다면 00001111 => 15
		mazeMark[i][j].searchDir |= (1 << dir);

		//이동할 방의 좌표를 구함
		view_i = i + move[dir][0];
		view_j = j + move[dir][1];

		//이동할 방의 좌표가 미로 행열 범위내에 있고
		if (view_i >= 0 && view_i < row && view_j >= 0 && view_j < col) {

			//탐색을 하지 않았다면
			if (mazeMark[view_i][view_j].searchDir == 0) {

				//미로 방향 표시. 벽을 허물고
				mazeMark[i][j].mazeDir |= (1 << dir);

				//이동한 방에서 같은 과정을 되풀이함
				mazeCreating(mazeMark, view_i, view_j);

			}

		}

	}

}

int main(void) {
	int i, j;
	struct cell** mazeMark;

	printf("미로의 행 크기: ");

	do {

		scanf_s("%d", &row);

		if (row < 1) printf("\n다시 입력하세요: ");

	} while (row < 1);

	printf("미로의 열 크기: ");

	do {

		scanf_s("%d", &col);

		if (col < 1) printf("\n다시 입력하세요: ");

	} while (col < 1);

	//2차원 배열처럼 사용할 mazeMark 준비
	mazeMark = (struct cell**)malloc(sizeof(struct cell*) * row);

	for (i = 0; i < row; i++) mazeMark[i] = (struct cell*)malloc(sizeof(struct cell) * col);

	//모든 방들을 미탐색으로 채움
	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

			mazeMark[i][j].searchDir = 0;

			mazeMark[i][j].mazeDir = 0;

		}

	}

	srand((unsigned int)time(NULL));

	//출발점을 임의로 정함
	i = (int)rand() % row;
	j = (int)rand() % col;

	//출발점 표시
	mazeMark[i][j].mazeDir |= (1 << 4);

	//재귀적 귀로 방법 호출
	mazeCreating(mazeMark, i, j);

	//미로를 출력함
	printf("\n\n재귀적 귀로(Recursive Backtracking) 방법");
	printf("\n\n●:출발점, →:미로생성 방향, ▦:벽\n\n");

	for (i = 0; i <= col * 2; i++) printf("▦");
	printf("\n");

	for (i = 0; i < row; i++) {

		printf("▦");

		for (j = 0; j < col; j++) {

			if (mazeMark[i][j].mazeDir & 16) printf("●");

			else printf("　");

			if (j == col - 1) {

				printf("▦");

				break;
			}

			if (mazeMark[i][j + 1].mazeDir & 4) printf("←");

			else if (mazeMark[i][j].mazeDir & 8) printf("→");

			else printf("▦");

		}

		printf("\n");

		if (i == row - 1) break;

		printf("▦");

		for (j = 0; j < col; j++) {

			if (mazeMark[i][j].mazeDir & 2) printf("↓");

			else if (mazeMark[i + 1][j].mazeDir & 1) printf("↑");

			else printf("▦");

			printf("▦");

		}

		printf("\n");
	}


	for (i = 0; i <= col * 2; i++) printf("▦");

	printf("\n");

	return 0;

}