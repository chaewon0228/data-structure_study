#include <stdio.h>
#define R 3
int b[R] = { 0, }, cnt = 0;
void PrintPer() {
	int i;
	for (i = 0; i < R; i++) printf("%d ", b[i]);
	printf("\n"); cnt++;
}
void Swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void Permutation(int a[], int n, int r) {
	int i;
	if (r >= R) PrintPer();
	else for (i = r; i <= n; i++) {
		Swap(a + r, a + i);
		b[r] = a[r];
		Permutation(a, n, r + 1);
		Swap(a + r, a + i);
	}
}

int main(void) {
	int a[] = { 1, 2, 3, 4, 5, 6 };
	int n = sizeof(a) / sizeof(int);
	Permutation(a, n - 1, 0);
	printf("순열 개수 : %d\n", cnt);
	return 0;
}
