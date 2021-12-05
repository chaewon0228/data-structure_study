/*
먼저 하나의 셀(도착점)을 정해 놓고, 다른 곳(출발점)에서
좌우상하 중 임의의 방향으로 벽을 제거하면서 전진하기를 반복하다가
현재 생성 중인 미로를 만나면 출발점으로 되돌아가서 다시 시작하고
도착점을 만나면 지금까지의 경로에 대하여 미로를 표시한다.
그 다음부터는 임의로 정한 출발점에서 기존의 미로를 만날 때까지
임의의 방향으로 전진하다가 미로를 만나면 지금까지의 경로를 미로에 추가하기를
모든 셀이 미로의 경로를 가질 때가지 이 과정을 반복한다.
최초의 도착점이나 미로를 만나기 위해 헤매는 반복횟수가 많은 방법임.
*/

/*
미로 행열에 벽을 포함하는 방법으로
미로 방을 가로 c, 세로 r개로 만들고자 할 경우
미로 행열은 행 크기는 (r*2 + 1), 열 크기는 (c*2 + 1)로 준비
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void) {
	int i, j, k = 0;
	int row, col; //벽을 포함한 미로 크기, row는 행, col은 열 크기로 3 이상의 값
	int view_i, view_j, d, chk_cnt;
	int move[4][2] = { {-2,0},{2,0},{0,-2},{0,2} };//상하좌우
	int** maze;

	struct room {
		int r;
		int c;
	}*unknown;

	struct candidate_room {
		int r;
		int c;
		int d;
	}*candidate;

	do {

		printf("벽을 포함한 미로의 행 크기<3 이상의 홀수>: ");

		scanf_s("%d", &row);

		if (row >= 3 && row % 2 == 1)break;

		printf("\n다시 입력하세요.\n");

	} while (1);

	do {

		printf("\n벽을 포함한 미로의 열 크기<3 이상의 홀수>: ");

		scanf_s("%d", &col);

		if (col >= 3 && col % 2 == 1)break;

		printf("\n다시 입력하세요.\n");

	} while (1);

	//2차원 배열처럼 사용할 maze 생성
	maze = (int**)malloc(sizeof(int*) * row);
	for (i = 0; i < row; i++) maze[i] = (int*)malloc(sizeof(int) * col);

	//미로 방 전체 개수. 벽을 제외한 방의 개수 
	chk_cnt = (row / 2) * (col / 2);

	//미지 리스트 준비
	unknown = (struct room*)malloc(sizeof(struct room) * chk_cnt);

	//후보 미로 리스트 준비
	candidate = (struct candidate_room*)malloc(sizeof(struct candidate_room) * chk_cnt);

	//미로 행렬 전체를 벽(0)으로 채우고, 모든 방을 미지 리스트에 차례로 삽입 
	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

			maze[i][j] = 0;

			if (i % 2 == 1 && j % 2 == 1) {

				unknown[k].r = i;

				unknown[k].c = j;

				k++;

			}

		}

	}

	srand((unsigned int)time(NULL));

	//임의의 방을 선택하고 미로 표시
	k = (int)rand() % chk_cnt;
	maze[unknown[k].r][unknown[k].c] = 1;

	//미지 리스트에서 제외. 끝 방의 좌표를 k 방으로 이동
	chk_cnt--; //미지 리스트에서 하나 줄임
	unknown[k].r = unknown[chk_cnt].r;
	unknown[k].c = unknown[chk_cnt].c;

	//미지 리스트에 방이 남아 있으면 반복
	while (chk_cnt > 0) {

		//임의의 방을 선택
		k = (int)rand() % chk_cnt;
		i = unknown[k].r;
		j = unknown[k].c;

		//후보 미로 리스트에 추가 
		k = 0;
		candidate[k].r = i;
		candidate[k].c = j;
		maze[i][j] = 2;

		//미로 만날 때까지 반복
		while (1) {

			d = (int)rand() % 4;
			view_i = i + move[d][0];
			view_j = j + move[d][1];

			//미로 범위 밖이면 다시 방향 정함 
			if (view_i < 1 || view_i > row - 2 || view_j < 1 || view_j > col - 2) continue;

			//미로 범위내 이면 방향 저장하고
			candidate[k].d = d;

			//다음 이동할 방을 일단 후보에 추가 
			k++;
			candidate[k].r = view_i;
			candidate[k].c = view_j;

			//다음 방이 미지이면 전진하고 후보 미로임을 표시 
			if (maze[view_i][view_j] == 0) {

				i = view_i;
				j = view_j;

				maze[i][j] = 2;

			}

			else if (maze[view_i][view_j] == 1)break; //미로를 만나면 빠져나감

			else { //maze[view_i][view_j] == 2 일 때, 후보 미로를 만났으므로 사이클을 제거함

				//이전 후보
				k--;

				do { //(view_i, view_j)를 만날 때까지 취소해 나감

					//이전으로 되돌아 가면서 후보(2)를 취소(0)함
					maze[candidate[k].r][candidate[k].c] = 0;

					k--;

				} while (candidate[k].r != view_i || candidate[k].c != view_j);

				//사이클의 원점으로 돌아와 다시 미로 찾아 나섬
				i = view_i;
				j = view_j;

			}

		}

		//임의 지점에서 미로를 만난 지점까지 미로 표시하고 미로방마다 미지리스트에서 제거함 
		for (i = 0; i < k; i++) {

			maze[candidate[i].r][candidate[i].c] = 1;

			switch (candidate[i].d) {

			case 0: maze[candidate[i].r - 1][candidate[i].c] = 1; break;

			case 1: maze[candidate[i].r + 1][candidate[i].c] = 1; break;

			case 2: maze[candidate[i].r][candidate[i].c - 1] = 1; break;

			case 3: maze[candidate[i].r][candidate[i].c + 1] = 1;

			}

			//미지 리스트에서 하나 줄임
			chk_cnt--;

			//후보 위치 탐색
			for (j = 0; j < chk_cnt; j++) if (candidate[i].r == unknown[j].r && candidate[i].c == unknown[j].c) break;

			//후보가 미로로 변경되면서 리스트에서 제외. 끝 방의 좌표를 j 방으로 이동
			unknown[j].r = unknown[chk_cnt].r;
			unknown[j].c = unknown[chk_cnt].c;

		}

	}

	//미로를 출력함 
	printf("\n");

	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

			if (maze[i][j] == 0) printf("▦");

			else printf("　");

		}

		printf("\n");

	}

	return 0;

}