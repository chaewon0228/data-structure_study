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
미로 행열에 벽을 포함하지 않는 방법으로
미로 방을 가로 c, 세로 r개로 만들고자 할 경우
미로 행열의 행 크기는 r, 열 크기는 c로 준비하고
각 미로 방에서 허문 벽의 방향을 보관하고 있다가 출력할 때 적용함
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void) {
	int i, j, k = 0;
	int row, col;
	int view_i, view_j, d, chk_cnt;
	int move[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };//상하좌우
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

	printf("미로의 행 크기: ");

	scanf_s("%d", &row);

	printf("\n미로의 열 크기: ");

	scanf_s("%d", &col);

	//2차원 배열처럼 사용할 maze 생성
	maze = (int**)malloc(sizeof(int*) * row);
	for (i = 0; i < row; i++) maze[i] = (int*)malloc(sizeof(int) * col);

	//미로 방 전체 개수 
	chk_cnt = row * col;

	//미지 리스트 준비
	unknown = (struct room*)malloc(sizeof(struct room) * chk_cnt);

	//후보 미로 리스트 준비
	candidate = (struct candidate_room*)malloc(sizeof(struct candidate_room) * chk_cnt);

	//미로 행렬 전체를 0(미탐색)으로 채우고, 모든 방을 미지 리스트에 차례로 삽입
	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

			maze[i][j] = 0;

			unknown[k].r = i;

			unknown[k].c = j;

			k++;

		}

	}

	srand((unsigned int)time(NULL));

	//임의의 방을 선택
	k = rand() % chk_cnt;

	//최초 선택 표시
	maze[unknown[k].r][unknown[k].c] |= (1 << 4); //이진수 10000을 bit OR

	//미지 리스트에서 제외. 끝 방의 좌표를 k 방으로 이동
	chk_cnt--; //미지 리스트에서 하나 줄임
	unknown[k].r = unknown[chk_cnt].r;
	unknown[k].c = unknown[chk_cnt].c;

	//미지 리스트에 방이 남아 있으면 반복
	while (chk_cnt > 0) {

		//임의의 방을 선택
		k = rand() % chk_cnt;
		i = unknown[k].r;
		j = unknown[k].c;

		//후보 미로 리스트에 추가 
		k = 0;
		candidate[k].r = i;
		candidate[k].c = j;

		//출발점 표시
		maze[i][j] |= (1 << 6); //이진수 1000000을 bit OR

		//후보 미로방 표시
		maze[i][j] |= (1 << 5); //이진수 100000을 bit OR

		//미로 만날 때까지 반복
		while (1) {

			d = rand() % 4;
			view_i = i + move[d][0];
			view_j = j + move[d][1];

			//미로 범위 밖이면 다시 방향 정함 
			if (view_i < 0 || view_i >= row || view_j < 0 || view_j >= col) continue;

			//(view_i, view_j)쪽의 방향을 저장하고
			candidate[k].d = d;

			//다음 이동할 방(view_i, view_j)을 후보에 추가
			k++;
			candidate[k].r = view_i;
			candidate[k].c = view_j;

			//다음 방이 미탐색이면 전진하고 후보 미로임을 표시
			if (maze[view_i][view_j] == 0) {

				i = view_i;
				j = view_j;

				maze[i][j] |= (1 << 5); //이진수 100000을 bit OR

			}

			else if ((maze[view_i][view_j] & 31) > 0)break; //미로를 만나면 빠져나감

			else { //maze[view_i][view_j] & 32 또는 maze[view_i][view_j] & 64 일 때, 후보 미로를 만났으므로 사이클을 제거함

				//이전 후보
				k--;

				do { //(view_i, view_j)를 만날 때까지 취소해 나감

					//이전으로 되돌아 가면서 후보(32)를 취소(0)함
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

			//미로 방향 표시
			maze[candidate[i].r][candidate[i].c] |= (1 << candidate[i].d);

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
	printf("\n\nWilson's Algorithm");
	printf("\n\n◎:최초 선택, ○:출발점, →:미로생성 방향, □:미로방, ▦:벽\n\n");

	for (i = 0; i <= col * 2; i++) printf("▦");

	printf("\n");

	for (i = 0; i < row; i++) {

		printf("▦");

		for (j = 0; j < col; j++) {

			if (maze[i][j] & 64) printf("○");

			else if (maze[i][j] & 16) printf("◎");

			else printf("□");

			if (j == col - 1) {

				printf("▦");

				break;
			}

			if (maze[i][j + 1] & 4) printf("←");

			else if (maze[i][j] & 8) printf("→");

			else printf("▦");

		}

		printf("\n");

		if (i == row - 1) break;

		printf("▦");

		for (j = 0; j < col; j++) {

			if (maze[i][j] & 2) printf("↓");

			else if (maze[i + 1][j] & 1) printf("↑");

			else printf("▦");

			printf("▦");

		}

		printf("\n");
	}

	for (i = 0; i <= col * 2; i++) printf("▦");

	printf("\n");


	//미로 생성 방향 생략하고 출력
	printf("\n\n【미로 생성 방향 생략하고 출력】\n\n");

	for (i = 0; i <= col * 2; i++) printf("▦");

	printf("\n");

	for (i = 0; i < row; i++) {

		printf("▦");

		for (j = 0; j < col; j++) {

			if (maze[i][j] & 16) printf("　");

			else if (maze[i][j] & 32) printf("　");

			else printf("　");

			if (j == col - 1) {

				printf("▦");

				break;

			}

			if (maze[i][j + 1] & 4) printf("　");

			else if (maze[i][j] & 8) printf("　");

			else printf("▦");

		}

		printf("\n");

		if (i == row - 1) break;

		printf("▦");

		for (j = 0; j < col; j++) {

			if (maze[i][j] & 2) printf("　");

			else if (maze[i + 1][j] & 1) printf("　");

			else printf("▦");

			printf("▦");

		}

		printf("\n");
	}

	for (i = 0; i <= col * 2; i++) printf("▦");

	printf("\n");

	return 0;

}