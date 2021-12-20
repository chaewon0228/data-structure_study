#include <stdio.h>
#define SIZE 8

int stack[SIZE] = { 0, };
int top = -1;

typedef enum { false, true } bool;

bool push(int index) {
	stack[++top] = index;
}

int pop() {
	if (top == -1) return -1;
	return stack[top--];
}

void DepthFirstSearch(char v[], bool a[][SIZE]) {
	bool searchOk[SIZE] = { false, };
	int i, j;
	char vertex;

	printf("\n시작 정점(A~G 중 입력) : ");
	scanf_s("%c", &vertex, 1);

	for (i = 0; i < SIZE; i++) if (vertex == v[i]) break;
	printf("\n깊이우선탐색 순서 : %c", v[i]);
	searchOk[i] = true;
	do {
		for (j = 0; j < SIZE; j++) {
			if (a[i][j] == 1 && searchOk[j] == false) {
				printf(" -> %c", v[j]);
				push(i);
				searchOk[j] = true;
				i = j;
				break;
			}
		}
		if (j >= SIZE) i = pop();
	} while (i >= 0);
}

int main(void) {
	int i, j;
	char v[SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	bool a[SIZE][SIZE] = { {0, 0, 1, 0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0, 0, 0, 0},
			{1, 1, 0, 1, 1, 0, 1, 0},
			{0, 0, 1, 0, 0, 1, 1, 0},
			{0, 0, 1, 0, 0, 0, 1, 0},
			{0, 0, 0, 1, 0, 0, 0, 1},
			{0, 0, 1, 1, 1, 0, 0, 1},
			{0, 0, 0, 0, 0, 1, 1, 0} };

	printf("\n\t\t인접 정점\n");
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
			printf("%5d", a[i][j]);
		printf("\n");
	}

	DepthFirstSearch(v, a);

	return 0;
}