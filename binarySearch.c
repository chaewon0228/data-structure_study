#include<stdio.h>

int binarySearch(int a[], int n, int key) {
    int left = 0, right = n - 1, middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (key > a[middle]) left = middle + 1;
        else if (key < a[middle]) right = middle - 1;
        else return middle;
    }
    return -1;
}
int main(void) {
    int key, i, index, n;
    int a[] = { 3,7,10,12,14,18,21,33,35,48 };
    n = sizeof(a) / sizeof(int);
    printf("찾을 대상 : ");
    for (i = 0; i < n; i++) printf("%5d", a[i]);
    printf("\n찾을 값 : ");
    scanf_s("%d", &key);
    index = binarySearch(a, n, key);
    if (index < 0) printf("\n찾고자 하는 값이 없다!\n");
    else printf("\n%d을(를) %d에서 찾음! \n", key, index);
    return 0;
}