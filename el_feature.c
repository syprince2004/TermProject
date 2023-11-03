/*
엘리베이터 관리 프로그램
개발 환경 : VS2022, C언어, Windows
개발 목적 : 엘리베이터 관리 프로그램의 개발을 통한 프로그래밍 능력 향상
개발 결과 : 사용자가 방향을 눌렀을때 가장 가까이 있는 엘리베이터가 옴
개발 히스토리 :
오픈소스 :
라이브러리 :
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <stdlib.h> //랜덤 함수를 쓰기 위한 헤더파일

#include <time.h> //time 함수를 쓰기 위한 헤더파일

#include <windows.h> //usleep 함수를 쓰기 위한 헤더파일

int El_Floor(int EarlyFloor, int LaterFloor);

void UD_Button(int UDbutton);

int El_Floor(int EarlyFloor, int LaterFloor);

/*
랜덤으로 받는 현재 사용자 위치
함수 목적 : 램덤으로 받은 입력으로 사용자의 현재 위치를 알려줌
return 값 : 램덤한값으로 받은 현재 사용자 위치
개발 히스토리 : 
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
랜덤으로 정하는 사용자가 가고자하는 위치(목표층)
함수 목적 : 목표층을 알려줌과 동시에 현재층과 목표층을 비교하면서 0.5초마다 다음 층으로 넘어가고 화면에 보여줌
return 값 : 램덤한값으로 받은 가고싶은 위치
개발 히스토리 :
오픈소스 :
라이브러리 :
*/

//int Rand_future(int UD)
//{
//	/* 
//	//목표층을 랜덤으로 구하는 코드
//	srand(time(NULL)); //매번 다른 값 시드 생성
//	int targetFloor = 0;
//	if (UD == 1) {
//		targetFloor = (rand() % (110 - currentFloor)) + currentFloor+1; //현재 위치보다 높은 위치중 랜덤한 값
//	}
//	else
//		targetFloor = (rand() % currentFloor-1) + 1; //현재 위치보다 낮은 위치중 랜덤한 값
//	*/
//
//	int currentFloor = Rand_Now(UD);
//
//	int targetFloor = 0;
//
//	int initialFloor = 1;
//
//	while(1)
//	{
//		currentFloor = El_Floor(initialFloor, currentFloor);
//
//		printf("가고자하는 층을 입력하시오 > ");
//		scanf_s("%d", &targetFloor);
//
//		initialFloor = El_Floor(currentFloor, targetFloor);
//	}
//
//	//if (initialFloor == targetFloor) {
//	//	printf("엘리베이터는 이미 목표 층에 도착했습니다.\n"); //초기층과 현재층을 비교하여 같다면 문구 출력
//	//}
//	//else if (initialFloor < currentFloor) {
//	//	printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", initialFloor, currentFloor); //초기층이 현재층보다 작다면 초기층에서 현재층으로 증가
//	//	while (initialFloor < currentFloor) {
//	//		Sleep((int)(timePerFloor * 1000)); // Sleep 함수를 사용하여 0.5초 대기
//	//		initialFloor++; //
//	//		printf("현재 %d층\n", initialFloor); //숫자를 하나씩 증가해주면서 층 보여줌
//	//	}
//	//	printf("엘리베이터가 사용자 층 %d에 도착했습니다.\n", currentFloor);
//	//	currentFloor = initialFloor; //다시 입력 받는 경우 초기 엘리베이터의 위치가 달라짐
//	//}
//	//else {
//	//	printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", initialFloor, currentFloor); //초기층이 현재층보다 크다면 초기층에서 현재층으로 증가
//	//	while (initialFloor > currentFloor) {
//	//		Sleep((int)(timePerFloor * 1000)); // Sleep 함수를 사용하여 대기
//	//		initialFloor--;
//	//		printf("현재 %d층\n", initialFloor); //숫자를 하나씩 감소해주면서 층 보여줌
//	//	}
//	//	printf("엘리베이터가 목표 층 %d에 도착했습니다.\n", currentFloor);
//	//	currentFloor = initialFloor; //다시 입력 받는 경우 초기 엘리베이터의 위치가 달라짐
//	//}
//
//	//
//
//	//if (currentFloor == targetFloor) {
//	//	printf("엘리베이터는 이미 목표 층에 도착했습니다.\n"); //현재층과 목표층을 비교하여 같다면 문구 출력
//	//}
//	//else if (currentFloor < targetFloor) {
//	//	printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", currentFloor, targetFloor); //현재층이 목표층보다 작다면 현재층에서 목표층으로 증가
//	//	while (currentFloor < targetFloor) {
//	//		Sleep((int)(timePerFloor * 1000)); // Sleep 함수를 사용하여 0.5초 대기
//	//		currentFloor++; //
//	//		printf("현재 %d층\n", currentFloor); //숫자를 하나씩 증가해주면서 층 보여줌
//	//	}
//	//	printf("엘리베이터가 목표 층 %d에 도착했습니다.\n", targetFloor);
//	//}
//	//else {
//	//	printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", currentFloor, targetFloor); //현재층이 목표층보다 크다면 현재층에서 목표층으로 증가
//	//	while (currentFloor > targetFloor) {
//	//		Sleep((int)(timePerFloor * 1000)); // Sleep 함수를 사용하여 대기
//	//		currentFloor--; 
//	//		printf("현재 %d층\n", currentFloor); //숫자를 하나씩 감소해주면서 층 보여줌
//	//	}
//	//	printf("엘리베이터가 목표 층 %d에 도착했습니다.\n", targetFloor);
//	//}
//
//
//	//return(targetFloor);
//}

/*
가고싶은 방향을 받는 입력(위, 아래)
함수 목적 : 가고싶은 방향을 입력받고 return값으로 보냄
return 값 : 사용자가 방향을 눌렀을때 가장 가까이 있는 엘리베이터가 옴
개발 히스토리 :
오픈소스 :
라이브러리 :
*/

void UD_Button(int UDbutton)
{
	while (getchar() != '\n'); //문자 예외처리
	if (UDbutton == 1 || UDbutton == 2) { 
		return 0; //받은값(가고싶은 방향)이 1 or 2 라면 Rand_futuer 함수 호출
	}
	else {
		printf("error!\n"); //받고자하는 숫자가 아니라면 문구 출력
		printf("다시입력하시오\n");
	}
}


/*
초기층에서 가고싶은 층으로 가는 코드
함수 목적 : 초기값을 끝날때마다 바꿔 시작 지점을 바꾼다
return 값 : 바뀐 초기값
개발 히스토리 :
오픈소스 :
라이브러리 :
*/


int El_Floor(int EarlyFloor, int LaterFloor) {
	double timePerFloor = 0.5; // 한 층 이동에 걸리는 시간 (초)

	if (EarlyFloor == LaterFloor) {
		printf("엘리베이터는 이미 목표 층에 도착했습니다.\n"); //현재층과 목표층을 비교하여 같다면 문구 출력
	}
	else if (EarlyFloor < LaterFloor) {
		printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", EarlyFloor-10, LaterFloor-10); //현재층이 목표층보다 작다면 현재층에서 목표층으로 증가
		while (EarlyFloor < LaterFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep 함수를 사용하여 0.5초 대기
			EarlyFloor++; //
			printf("현재 %d층\n", EarlyFloor-10); //숫자를 하나씩 증가해주면서 층 보여줌
		}
		printf("엘리베이터가 목표 층 %d에 도착했습니다.\n", LaterFloor-10);
		EarlyFloor = LaterFloor;
	}
	else {
		printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", EarlyFloor-10, LaterFloor-10); //현재층이 목표층보다 크다면 현재층에서 목표층으로 증가
		while (EarlyFloor > LaterFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep 함수를 사용하여 대기
			EarlyFloor--;
			printf("현재 %d층\n", EarlyFloor-10); //숫자를 하나씩 감소해주면서 층 보여줌
		}
		printf("엘리베이터가 목표 층 %d에 도착했습니다.\n", LaterFloor-10);
		EarlyFloor = LaterFloor;
	}
	return EarlyFloor;
}

