#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUM 5
#define SIZE 21

//아래 비교 함수는 오름차순이며, return 문에서 a, b 또는 p1, p2를 바꾸면 내림차순이 됨

//정수 오름차순
int compareInt(const void* a, const void* b) {

    return *(int*)a - *(int*)b;

}

//문자열 오름차순
int compareString(const void* a, const void* b) {

    return strcmp((char*)a, (char*)b);

}

struct student {
    char studentNo[6]; //학번
    char name[11]; //성명
    char telNo[15]; //전화번호
    int age; //나이
};

//student 구조체 오름차순
int compareStruct(const void* a, const void* b) {
    struct student* p1 = (struct student*)a;
    struct student* p2 = (struct student*)b;

    //학번 기준
    return strcmp((char*)p1->studentNo, (char*)p2->studentNo);
    //성명 기준
    //return strcmp((char*)p1->name, (char*)p2->name);
    //전화번호 기준
    //return strcmp((char*)p1->telNo, (char*)p2->telNo);

}

int main(void) {
    int a[] = { 11, 8, 12, 23, 15, 36, 5, 10, 24 };
    int n1 = sizeof(a) / sizeof(int);

    char b[NUM][SIZE] = { "JAVA", "C/C++", "Python", "JavaScript", "HTML5/CSS3" };

    struct student c[NUM] = {
        {"2201", "가은", "010-3355-7878", 17},
        {"2101", "강추", "010-1234-5678", 18},
        {"2401", "고들", "010-2345-1212", 18},
        {"2301", "김산", "010-7777-2351", 18},
        {"2102", "구원", "010-4581-6527", 18} };

    printf("▼정수 정렬: ");
    qsort(a, n1, sizeof(int), compareInt);

    for (int i = 0; i < n1; i++) printf("%5d", a[i]);
    printf("\n\n\n");

    printf("▼문자열 정렬\n");
    qsort(b, NUM, sizeof(b[0]), compareString);

    for (int i = 0; i < NUM; i++) printf("%s\n", b[i]);
    printf("\n\n");

    printf("▼구조체 정렬(학번 기준)\n");
    qsort(c, NUM, sizeof(c[0]), compareStruct);

    for (int i = 0; i < NUM; i++) {
        printf("%s\t", c[i].studentNo);
        printf("%s\t", c[i].name);
        printf("%s\t", c[i].telNo);
        printf("%d\n", c[i].age);
    }
    printf("\n");

    return 0;
}