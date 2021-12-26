#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 8

struct node {
	int adjNodeIndex;
	int weight;
	struct node* link;
};

struct node* newNode(int index, int weight) {
	struct node* p;

	p = (struct node*)malloc(sizeof(struct node));
	p->adjNodeIndex = index;
	p->weight = weight;
	p->link = NULL;

	return p;
}

int minVertex(int D[], int chk[]) {
	int i, minValue, minIndex;

	for (i = 0; i < SIZE; i++) if (chk[i] == 0) break;
	minValue = D[i];
	minIndex = i;

	for (; i < SIZE; i++)
		if (chk[i] == 0 && minValue > D[i] && D[i] > 0) {
			minValue = D[i];
			minIndex = i;
		}
	return minIndex;
}

void Dijkstra(struct node* G[], int D[], int P[], int i) {
	struct node* ptr = G[i];
	int chk[SIZE] = { 0, };
	int cnt = 0;


	while (ptr != NULL) {
		D[ptr->adjNodeIndex] = ptr->weight;
		P[ptr->adjNodeIndex] = i;
		ptr = ptr->link;
	}
	chk[i] = 1;
	cnt++;

	while (cnt < SIZE) {
		i = minVertex(D, chk);
		ptr = G[i];
		while (ptr != NULL) {
			if (D[ptr->adjNodeIndex] > D[i] + ptr->weight) { //axis를 거치는 경로가 짧다면
				D[ptr->adjNodeIndex] = D[i] + ptr->weight; //짧은 거리로 업데이트
				P[ptr->adjNodeIndex] = i; //axis를 거치도록 경로 설정
			}
			ptr = ptr->link;
		}
		chk[i] = 1; //살펴 볼 축에서 제외
		cnt++;
	}
}

int main(void) {
	struct node* G[SIZE] = { NULL };
	struct node* p;
	char V[SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	char shortestPath[SIZE];
	char departureVertex, arrivalVertex;
	int P[SIZE] = { 0, };
	int D[SIZE] = { INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX };
	int i, j, vertexNum, vertexCnt = 0, departureNum;

	//인덱스 순서대로 인접리스트를 만들 것!
	//가중치를 입력 받아 연결되도록 입력문을 작성할 필요가 있음
	G[0] = newNode(1, 12); G[0]->link = newNode(2, 15); G[0]->link->link = newNode(3, 18);
	G[1] = newNode(0, 12); G[1]->link = newNode(4, 33); G[1]->link->link = newNode(5, 26);
	G[2] = newNode(0, 15); G[2]->link = newNode(3, 7); G[2]->link->link = newNode(5, 10);
	G[3] = newNode(0, 18); G[3]->link = newNode(2, 7); G[3]->link->link = newNode(6, 11);
	G[4] = newNode(1, 33); G[4]->link = newNode(5, 17); G[4]->link->link = newNode(7, 15);
	G[5] = newNode(1, 26); G[5]->link = newNode(2, 10); G[5]->link->link = newNode(4, 17); G[5]->link->link->link = newNode(7, 28);
	G[6] = newNode(3, 11); G[6]->link = newNode(7, 20);
	G[7] = newNode(4, 15); G[7]->link = newNode(5, 28); G[7]->link->link = newNode(6, 20);

	printf("\n[인접 리스트<인접 정점과의 거리>]\n\n");
	for (i = 0; i < SIZE; i++) printf("%4c", V[i]);
	printf("\n");
	for (i = 0; i < SIZE; i++) {
		printf("%c", V[i]);
		p = G[i];
		for (j = 0; j < SIZE; j++) {
			if (p != NULL && j == p->adjNodeIndex) {
				printf("%4d", p->weight);
				p = p->link;
			}
			else printf("%4c", '-');
		}
		printf("\n");
	}

	printf("\n출발 정점(A~H) : ");
	scanf_s("%c", &departureVertex, 1);
	getchar();
	printf("도착 정점(A~H) : ");
	scanf_s("%c", &arrivalVertex, 1);
	getchar();
	while (departureVertex == arrivalVertex) {
		printf("출발과 도착이 같습니다. 도착 정점(A~H) : ");
		scanf_s("%c", &arrivalVertex, 1);
		getchar();
	}

	for (i = 0; i < SIZE; i++) if (arrivalVertex == V[i]) break;
	D[i] = 0;
	P[i] = i;

	Dijkstra(G, D, P, i);

	printf("\n각 정점에서 출발 정점 %c까지 최단 경로 및 거리\n", departureVertex);

	for (i = 0; i < SIZE; i++) {
		if (V[i] == arrivalVertex) continue;
		printf("%c", V[i]);

		if (V[i] == departureVertex) departureNum = i;

		vertexNum = i;
		while (V[vertexNum] != arrivalVertex) {
			vertexNum = P[vertexNum];
			printf(" -> %c", V[vertexNum]);
			if (V[i] == departureVertex) shortestPath[vertexCnt++] = V[vertexNum];
		}
		printf(", %d\n", D[i]);
	}

	printf("\n출발 정점 %c에서 도착 정점 %c까지 최단 경로 및 거리 : ", departureVertex, arrivalVertex);
	printf("%c", departureVertex);
	for (i = 0; i < vertexCnt; i++)
		printf(" -> %c", shortestPath[i]);
	printf(", %d\n\n", D[departureNum]);

	return 0;
}