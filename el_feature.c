/*
엘리베이터 관리 프로그램
개발 환경 : VS2022, C언어, Windows
개발 목적 : 엘리베이터 관리 프로그램의 개발을 통한 프로그래밍 능력 향상
개발 결과 : 사용자가 방향을 눌렀을때 가장 가까이 있는 엘리베이터가 옴
개발 히스토리 :
오픈소스 :
라이브러리 :
*/
#include <stdio.h>

#include <stdlib.h> //랜덤 함수를 쓰기 위한 헤더파일

#include <time.h> //time 함수를 쓰기 위한 헤더파일

#include <windows.h> //usleep 함수를 쓰기 위한 헤더파일

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
랜덤으로 정하는 사용자가 가고자하는 위치
함수 목적 : 사용자가 가고싶은 위치를 알려줌
return 값 : 램덤한값으로 받은 가고싶은 위치
개발 히스토리 :
오픈소스 :
라이브러리 :
*/

int Rand_future(int UD)
{
	int currentFloor = Rand_Now(UD);
	srand(time(NULL)); //매번 다른 값 시드 생성
	int targetFloor = 0;
	if (UD == 1) {
		targetFloor = (rand() % (110 - currentFloor)) + currentFloor+1; //현재 위치보다 높은 위치중 랜덤한 값
	}
	else
		targetFloor = (rand() % currentFloor-1) + 1; //현재 위치보다 낮은 위치중 랜덤한 값

	double timePerFloor = 0.5; // 한 층 이동에 걸리는 시간 (초)

	if (currentFloor == targetFloor) {
		printf("엘리베이터는 이미 목표 층에 도착했습니다.\n"); //현재층과 목표층을 비교하여 같다면 문구 출력
	}
	else if (currentFloor < targetFloor) {
		printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", currentFloor, targetFloor); //현재층이 목표층보다 작다면 
		while (currentFloor < targetFloor) {
			Sleep((int)(timePerFloor * 1000)); // usleep 함수를 사용하여 0.5초 대기
			currentFloor++;
			printf("현재 %d층\n", currentFloor);
		}
		printf("엘리베이터가 목표 층 %d에 도착했습니다.\n", targetFloor);
	}
	else {
		printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", currentFloor, targetFloor);
		while (currentFloor > targetFloor) {
			Sleep((int)(timePerFloor * 1000)); // usleep 함수를 사용하여 대기
			currentFloor--;
			printf("현재 %d층\n", currentFloor);
		}
		printf("엘리베이터가 목표 층 %d에 도착했습니다.\n", targetFloor);
	}


	return(targetFloor);
}

/*
가고싶은 방향을 받는 입력(위, 아래)
함수 목적 : 가고싶은 방향을 입력받고 return값으로 보냄
return 값 : 사용자가 방향을 눌렀을때 가장 가까이 있는 엘리베이터가 옴
개발 히스토리 :
오픈소스 :
라이브러리 :
*/

int UD_Button(int button)
{
	while (getchar() != '\n'); //문자 예외처리
	if (button == 1 || button == 2) { 
		Rand_future(button); //받은값(가고싶은 방향)이 1 or 2 라면 Rand_futuer 함수 호출
	}
	else {
		printf("error!\n"); //받고자하는 숫자가 아니라면 문구 출력
		printf("다시입력하시오\n");
	}
}
