//제산 함수 구현 코드. 충돌 해결 방법은 동거자 체인

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//학생 데이터 구조체
struct member {
	int student_No;
	char name[9];
	char phoneNo[12];
	char email[30];
	struct member* link;
};

int divider; //나눌 수

//해시 테이블에 저장하는 함수
void storeMember(struct member* bucket, struct member* overflowArea, int m, int n) {
	FILE* f;
	static int overflowAddr = 0;//이전 값을 기억하고 있어야 하므로 static으로 준비
	struct member someMem, * ptr;
	int addr, cnt = 0;

	//해시 테이블에 저장할 임의의 데이터를 nameList.txt로 준비해 놓음
	fopen_s(&f, "nameList.txt", "r");

	printf("\n해시 테이블 몇 번째 저장했는지를 출력\n");

	//nameList.txt에 준비된 데이터를 하나씩 읽어와서 해시 테이블에 저장함
	do {

		//구조체 하나를 읽어 옴
		fscanf_s(f, "%d\t%s\t%s\t%s\n", &someMem.student_No, someMem.name, 9, someMem.phoneNo, 12, someMem.email, 30);

		//제산함수 적용하여 상대적 저장 위치 구함
		addr = (someMem.student_No % divider) * m / divider;

		//절대적 저장 위치 구함
		ptr = bucket + addr;

		//충돌이 발생하였다면(저장 위치에 이미 데이터가 있다면)
		if (ptr->name[0] != '\0') {

			printf("학번 %d, 주소 %d에서 충돌이 발생하여 독립 구역에 저장하고 연결함!\n", someMem.student_No, addr);

			//독립 구역으로 연결이 있으면 끝까지 이동한 다음
			while (ptr->link != NULL) ptr = ptr->link;

			//독립 구역의 다음 공간을 현재 리스트의 끝에 연결함
			ptr->link = overflowArea + overflowAddr;

			//독립 구역을 초과하면 더 이상 저장 불가
			if (++overflowAddr > n) {
				printf("\n예비영역 초과로 저장 불가!\n");
				return; //함수 종료
			}

			//독립 구역의 다음 저장 공간으로 이동
			ptr = ptr->link;

		}
		else printf("학번 %d, %d번째 저장함!\n", someMem.student_No, addr);

		//nameList.txt에서 읽어 온 구조체 멤버를 해시 테이블에 저장함
		ptr->student_No = someMem.student_No;
		strcpy_s(ptr->name, 9, someMem.name);
		strcpy_s(ptr->phoneNo, 12, someMem.phoneNo);
		strcpy_s(ptr->email, 30, someMem.email);
		ptr->link = NULL;

		cnt++;

	} while (cnt < m);

}

//검색 함수
void searchMember(struct member* bucket, int m, int n) {
	int addr, no, cnt = 0;
	char yn;
	struct member* ptr;

	do {
		printf("\n찾을 학번: ");
		scanf_s("%d", &no);
		getchar();

		addr = (no % divider) * m / divider;

		ptr = bucket + addr;

		while (ptr != NULL) {

			if (ptr->student_No == no) {
				if (cnt == 0) printf("\n%d 위치에서 직접 찾음!", addr);
				else printf("\n%d번 전진하여 찾음!", cnt);

				printf("\n찾은 데이터는 %d, %s, %s, %s\n", ptr->student_No, ptr->name, ptr->phoneNo, ptr->email);
				break;//반복을 빠져나감
			}

			ptr = ptr->link;

			cnt++;
		}

		if (ptr == NULL) printf("없는 데이터!\n");

		printf("\n계속 검색?(y/n) : ");
		scanf_s("%c", &yn, 1);
		getchar();

		cnt = 0;

	} while (yn == 'y');

}

int HashingFunctionDivider(int memberNo) {
	int i;

	//소수 또는 소수에 가까운 숫자(20보다 작은 소수를 약수로 갖지 않는 수) 선택
	do {

		for (i = 2; i <= 19; i++)
			if (memberNo % i == 0) break;

		if (i == 20) return memberNo;

		memberNo++;

	} while (1);

}

int main(void) {
	int m = 120; //m은 데이터 개수
	int i, n;
	struct member* bucket, * overflowArea;

	printf("Hash Table 구현, 해싱 함수는 제산 함수, 충돌 해결 방법은 동거자 체인\n\n");
	printf("데이터 수: %d\n\n", m);
	printf("적재율: 70%%\n\n");

	n = (int)(m * 3 / 7);//독립 구역의 크기

	divider = HashingFunctionDivider(m);

	printf("나눌 수: %d\n", divider);

	bucket = (struct member*)calloc(m, sizeof(struct member));
	overflowArea = (struct member*)calloc(n, sizeof(struct member));

	//데이터 구역 초기화
	for (i = 0; i < m; i++) bucket[i].name[0] = '\0';

	//독립 구역 초기화
	for (i = 0; i < n; i++) overflowArea[i].name[0] = '\0';

	//준비된 파일 차례로 읽어와서 학번을 key로 하여 해시 테이블에 저장
	storeMember(bucket, overflowArea, m, n);

	//학번을 입력 받아 해시 테이블에서 찾음 
	searchMember(bucket, m, n);

	//데이터 구역과 독립 구역의 메모리 점유를 해제함
	free(bucket);
	free(overflowArea);

	return 0;
}