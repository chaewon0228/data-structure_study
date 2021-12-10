#include <stdio.h>
#include <string.h>

#define SIZE 100

int stringSearch(char s[], char p[]) {
	int i, sl, pl;

	sl = strlen(s);
	pl = strlen(p);
	for (i = 0; i <= sl - pl; i++) {
		if (strncmp(s + i, p, pl) == 0) {
			return i;
		}
	}
	return -1;
}

int main(void) {
	char* s = "mirim meister newmedia interactive solution";
	char p[SIZE] = { '\0' }, * sp1;
	int sp2;

	printf("주어진 문자열: %s\n\n", s);
	printf("찾을 문자열 입력: ");
	gets_s(p, SIZE); //최대 99문자까지 입력

	//strncmp()함수 사용하는 방법
	printf("\nstrncmp()함수 사용하여 ");
	if ((sp2 = stringSearch(s, p)) == -1)
		printf("찾는 문자열이 없습니다.\n");
	else
		printf("\"%s\"는 %d위치에서 찾았습니다.\n", p, sp2);

	//strstr()함수 사용하는 방법
	printf("\nstrstr()함수 사용하여 ");
	if ((sp1 = strstr(s, p)) == NULL)
		printf("찾는 문자열이 없습니다.\n");
	else
		printf("\"%s\"는 %d위치에서 찾았습니다.\n", p, sp1 - s);

	return 0;

}