/*
엘리베이터 관리 프로그램
개발 환경 : VS2022, C언어, Windows
개발 목적 : 엘리베이터 관리 프로그램의 개발을 통한 프로그래밍 능력 향상
개발 결과 : 
개발 히스토리 : 2023-11-09
오픈소스 :
라이브러리 :
*/

#pragma warning(disable:4996)

#include <stdio.h>

#include <stdlib.h> //랜덤 함수를 쓰기 위한 헤더파일

#include <time.h> //time() 함수를 쓰기 위한 헤더파일

#include <windows.h> //sleep() 함수를 쓰기 위한 헤더파일

#include <process.h>

int Rand_Now(int currentFloor);

void UD_Button(int UDbutton);

int El_Floor(int EarlyFloor, int LaterFloor);

int Cl_Button(int Close);

unsigned _stdcall elevator1(void* arg);

unsigned _stdcall elevator2(void* arg);


/*
메인함수
함수 목적 : 모든 진행이 이루어지는 공간
return 값 :
개발 히스토리 :
	2023-11-09 - 
*/

int main()
{
	int targetFloor = 0;

	int initialFloor = 11; //처음 시작할때 층은 무조건 1층

	_beginthreadex(NULL, 0, elevator1, 0, 0, NULL);

	Sleep(1000);

	_beginthreadex(NULL, 0, elevator2, 0, 0, NULL);

	while (1)
	{

		int button = 0;
		int close = 0;
		UD_Button(button); //UD_Button 함수 호출

		int currentFloor = Rand_Now(button);

		currentFloor = El_Floor(initialFloor, currentFloor); //El_Floor 함수 호출후 return 값을 currentFloor에 넣음

		printf("가고자하는 층을 입력하시오 > ");
		scanf("%d", &targetFloor); //가고싶은 층을 사용자가 입력
		targetFloor += 10; //110층을 기본으로 하기 때문에 +10층으로 함

		printf("닫힘버튼(1) > ");
		scanf("%d", &close); //닫힘버튼 유무 사용자가 입력
		Cl_Button(close);

		initialFloor = El_Floor(currentFloor, targetFloor);
	}
}
/*
구조체 목적 : 성별, 탑승인원을 받음
개발 히스토리 : 
	(2023-11-10) - 
*/

struct {
	char gender; //성별
	int num_people; // 엘리베이터에 타는 인원수
}People;


/*
계속 돌아가는 엘리베이터1
함수 목적 : 계속 랜덤으로 입력받고 돌아가는 엘리베이터1
return 값 :
개발 히스토리 : 
	(2023-11-09) - 랜덤으로 현재위치를 받고 가고싶은 위치도 랜덤으로 받는 엘리베이터1 함수 생성
*/

unsigned _stdcall elevator1(void* arg)
{
	int targetFloor = 0;
	int initialFloor = 11;
	
	while(1){
		int button = 0;
		int close = 0;
		srand(time(NULL));//매번 다른 값 시드 생성
		button = (rand() % 2) + 1;
		int currentFloor = Rand_Now(button);
		currentFloor = El_Floor(initialFloor, currentFloor); //El_Floor 함수 호출후 return 값을 currentFloor에 넣음
		targetFloor = (rand() % 110) - 10;
		close = (rand() % 2);
		Cl_Button(close);
		initialFloor = El_Floor(currentFloor, targetFloor); //El_Floor 함수 호출후 return 값을 initialFloor에 넣음
	}
}


/*
계속 돌아가는 엘리베이터2
함수 목적 : 계속 랜덤으로 입력받고 돌아가는 엘리베이터2
return 값 :
개발 히스토리 :
	(2023-11-09) - 랜덤으로 현재위치를 받고 가고싶은 위치도 랜덤으로 받는 엘리베이터2 함수 생성
*/

unsigned _stdcall elevator2(void* arg)
{
	int targetFloor = 0;
	int initialFloor = 11;

	while (1) {
		int button = 0;
		int close = 0;
		srand(time(NULL));//매번 다른 값 시드 생성
		button = (rand() % 2) + 1;
		int currentFloor = Rand_Now(button);
		currentFloor = El_Floor(initialFloor, currentFloor); //El_Floor 함수 호출후 return 값을 currentFloor에 넣음
		targetFloor = (rand() % 110) - 10;
		close = (rand() % 2);
		Cl_Button(close);
		initialFloor = El_Floor(currentFloor, targetFloor); //El_Floor 함수 호출후 return 값을 initialFloor에 넣음
	}
}


/*
닫힘버튼을 사용여부
함수 목적 : 닫힘버튼을 누르면 1초이후 닫히고 안누르면 3초후에 닫힘
return 값 : 램덤한값으로 받은 현재 사용자 위치
개발 히스토리 : 
	(2023-11-10) - Sleep 함수를 이용해 닫힘버튼을 누르면 1초뒤 문이닫힘니다 출력 아니라면 3초뒤 출력
*/

int Cl_Button(int Close) 
{
	if (Close == 1) {
		Sleep(1000);
	}
	else
		Sleep(3000);
	printf("문이 닫힘니다\n");
	return 0;
}

/*
랜덤으로 받는 현재 사용자 위치
함수 목적 : 램덤으로 받은 입력으로 사용자의 현재 위치를 알려줌
return 값 : 램덤한값으로 받은 현재 사용자 위치
개발 히스토리 : 2023-11-09
오픈소스 :
라이브러리 :
*/

int Rand_Now(int currentFloor)
{
	srand(time(NULL)); //매번 다른 값 시드 생성

	currentFloor = (rand() % 110) + 1; //1~110층 중 하나를 무작위로 받음

	return(currentFloor);
}


/*
가고싶은 방향을 받는 입력(위, 아래)
함수 목적 : 가고싶은 방향을 입력받고 return값으로 보냄
return 값 : 사용자가 방향을 눌렀을때 가장 가까이 있는 엘리베이터가 옴
개발 히스토리 : 2023-11-09
*/

void UD_Button(int UDbutton)
{
	printf("가고싶은 방향을 선택하시오 위(1), 아래(2) > ");
	scanf("%d", &UDbutton); //가고싶은 방향 직접 입력
	while (getchar() != '\n'); //문자 예외처리
	if (UDbutton == 1 || UDbutton == 2) {
		return 0; //받은값(가고싶은 방향)이 1 or 2 라면 return 0
	}
	else {
		printf("error!\n"); //받고자하는 숫자가 아니라면 문구 출력
		printf("다시입력하시오\n");
		UD_Button(UDbutton); //재귀함수로 잘못입력하면 다시 방향 선택하도록 만듦
	}
}


/*
초기층에서 가고싶은 층으로 가는 코드
함수 목적 : 초기값을 끝날때마다 바꿔 시작 지점을 바꾼다
return 값 : 바뀐 초기값
개발 히스토리 : 
	(2023-11-09) - 초기층에서 현재층으로 가고 현재층에서 목표층으로 가는 함수 구현(엘리베이터 한층당 속도는 Sleep함수를 사용해 0.5초)
*/

int El_Floor(int EarlyFloor, int LaterFloor) {
	double timePerFloor = 0.5; // 한 층 이동에 걸리는 시간 (초)

	if (EarlyFloor == LaterFloor) {
		printf("엘리베이터는 이미 층에 도착했습니다.\n"); //현재층과 목표층을 비교하여 같다면 문구 출력
	}
	else if (EarlyFloor < LaterFloor) {
		printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", EarlyFloor - 10, LaterFloor - 10); //현재층이 목표층보다 작다면 현재층에서 목표층으로 증가
		while (EarlyFloor < LaterFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep 함수를 사용하여 0.5초 대기
			EarlyFloor++; //
			printf("현재 %d층\n", EarlyFloor - 10); //숫자를 하나씩 증가해주면서 층 보여줌
		}
		printf("엘리베이터가 %d에 도착했습니다.\n", LaterFloor - 10);
		EarlyFloor = LaterFloor;
	}
	else {
		printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", EarlyFloor - 10, LaterFloor - 10); //현재층이 목표층보다 크다면 현재층에서 목표층으로 증가
		while (EarlyFloor > LaterFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep 함수를 사용하여 대기
			EarlyFloor--;
			printf("현재 %d층\n", EarlyFloor - 10); //숫자를 하나씩 감소해주면서 층 보여줌
		}
		printf("엘리베이터가 %d에 도착했습니다.\n", LaterFloor - 10);
		EarlyFloor = LaterFloor;
	}
	return EarlyFloor;
}