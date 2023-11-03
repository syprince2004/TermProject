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

#include <time.h> //time() 함수를 쓰기 위한 헤더파일

int Rand_Now(int currentFloor);

void UD_Button(int UDbutton);

int El_Floor(int EarlyFloor, int LaterFloor);

int main()
{
	int targetFloor = 0;

	int initialFloor = 11; //처음 시작할때 층은 무조건 1층

	while(1)
	{
		int button = 0;
		printf("가고싶은 방향을 선택하시오 위(1), 아래(2) > ");
		scanf_s("%d", &button); //가고싶은 방향 직접 입력
		UD_Button(button); //UD_Button 함수 호출

		int currentFloor = Rand_Now(button);

		currentFloor = El_Floor(initialFloor, currentFloor);

		printf("가고자하는 층을 입력하시오 > ");
		scanf_s("%d", &targetFloor);
		targetFloor += 10;

		initialFloor = El_Floor(currentFloor, targetFloor);
	}
}