#include <stdio.h>
#include <limits.h>
#define SIZE 8
#define M INT_MAX

int minVertex(int D[], int chk[]) {
	int i, minValue = M, minIndex = 0;
	
	for (i = 0; i < SIZE; i++) {
		if (chk[i] == 0 && minValue > D[i]) {
			minValue = D[i];
			minIndex = i;
		}
	}
	return minIndex;
}
void Dijkstra(int G[SIZE][SIZE], int D[], int P[], int i) {
	int j, cnt = 0, chk[SIZE] = { 0, };
	for (j = 0; j < SIZE; j++)
		if (G[i][j] > 0 && G[i][j] < M) {
			D[j] = G[i][j]; P[j] = i;
		}
	chk[i] = 1; cnt++;
	
	while (cnt < SIZE) {
		i = minVertex(D, chk);
		for (j = 0; j < SIZE; j++)
			if (G[i][j] > 0 && G[i][j] < M) //인접해 있고
				if (D[j] > D[i] + G[i][j]) { //axis를 거치는 경로가 짧다면
					D[j] = D[i] + G[i][j]; //짧은 거리로 업데이트
					P[j] = i; //axis를 거치도록 경로 설정
				}
			chk[i] = 1; //살펴 볼 축에서 제외
			cnt++;
		}
}


int main() {
	int G[SIZE][SIZE] = { {0, 12, 15, 18, M, M, M, M},
						  {12, 0, M, M, 33, 26, M, M},
						  {15, M, 0, 7, M, 10, M, M},
						  {18, M, 7, 0, M, M, 11, M},
						  {M, 33, M, M, 0, 17, M, 15},
						  {M, 26, 10, M, 17, 0, M, 28},
						  {M, M, M, 11, M, M, 0, 20},
						  {M, M, M, M, 15, 28, 20, 0} };
	char V[SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	char aV, bV;
	int D[SIZE] = { M, M, M, M, M, M, M, M };

	int P[SIZE] = { 0, };
	int i;
	printf("출발 정점: ");
	scanf_s("%c", &aV, 1);
	getchar();
	printf("도착 정점: ");
	scanf_s("%c", &bV, 1);
	
	for (i = 0; i < SIZE; i++) if (bV == V[i]) break;
	D[i] = 0;
	P[i] = i;
	Dijkstra(G, D, P, i);
	for (i = 0; i < SIZE; i++) if (aV == V[i]) break;
	printf("\n%c에서 %c까지 최단거리: %d\n", aV, bV, D[i]);
	printf("최단경로: % c", aV);
	while (V[i] != bV) {
		i = P[i];
		printf(" -> %c", V[i]);
	}
	printf("\n");
	return 0;

}

