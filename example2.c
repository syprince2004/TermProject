/*
엘리베이터 관리 프로그램
개발 환경 : VS2022, C언어, Windows
개발 목적 : 엘리베이터 관리 프로그램의 개발을 통한 프로그래밍 능력 향상
개발 결과 :
개발 히스토리 :
	2023.10.02 - main 함수에서 입력에 따른 if문 생성, 현재층과 목표층 입력
	2023.10.07 - main 함수에서 쓰레드 호출, 쓰레드 생성
	2023.10.11 - 버블정렬 함수를 이용해 전역변수인 currentFloor, targetFloor 배열을 오름차순정렬
	2023.10.13 - 버블정렬한 currentFloor, targetFloor 배열을 새로운 배열에 저장
	2023.10.20 - 최대값과 최솟값을 구하는 함수
	2023.10.23 - Sleep 함수를 이용해 닫힘버튼을 누르면 1초뒤 문이닫힘니다 출력 아니라면 3초뒤 출력
오픈소스 :
라이브러리 :
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>

#define SWAP(x,y,t) ( (t)=(x) , (x) = (y) , (y) =(t) ) // 두개의 자리를 바꿔줌

int currentFloor[100] = { 0 };
int newcurrent[100] = { 0 };
int targetFloor[100] = { 0 };
int newtarget[100] = { 0 };
int button[100] = { 0 };
int people[100] = { 0 };
int elevator1 = 0;
int* el1_currentMax = 0;
int* el1_currentMin = 0;
int* el1_targetMax = 0;
int* el1_targetMin = 0;
int i = 0;

unsigned _stdcall thread_el1(void* arg);

void BubbleSort(int list[], int n);

void MinMax(int list[], int* min, int* max);

/*
메인함수
함수 목적 : 모든 진행이 이루어지는 공간
return 값 :
개발 히스토리 :
	2023.10.02 - 입력에 따른 if문 생성, 사용자 현재층(currentFloor) 랜덤으로 입력받기, 가고자하는 층(targetFloor) 입력받기
	2023.10.07 - 쓰레드 호출
*/
int main()
{
	_beginthreadex(NULL, 0, thread_el1, 0, 0, NULL); // 쓰레드 호출
	while (1)
	{
		int targetf;
		int currentf;
		srand(time(NULL));
		printf("위(1), 아래(2), 임의사용자(3)");
		scanf("%d", &button[i]); //숫자로 입력
		//printf("%d", button);
		if (button[i] == 1 || button[i] == 2) { // 1 or 2를 입력했을때
			currentf = rand() % 100 + 1; // 현재층을 1~100층중 랜덤으로 결정
			currentFloor[i] = currentf; // 전역변수로 선언된currentFloor에 대입
			printf("가고자하는 층을 입력");
			scanf("%d", &targetf); // 목표층을 입력받음
			targetFloor[i] = targetf; // 전역변수로 선언된 targetFloor에 대입
			/*printf("%d %d\n", currentFloor[i], targetFloor[i]);*/
			i++;
		}
		/*else if (button == 3) {

		}
		else
			continue;*/

	}
}

/*
독립적으로 움직이는 쓰레드
함수 목적 : 메인에서 입력받고 전역변수의 배열에 넣으면 엘리베이터 위치와 비교
개발 히스토리 :
	2023.10.07 - 쓰레드 생성
	2023.10.11 - 전역변수인 currentFloor, targetFloor 배열을 버블정렬
	2023.10.13 - 버블정렬한 currentFloor, targetFloor 배열을 새로운 배열에 저장
	2023.10.20 - 최대최소값을 찾는 함수 선언
*/
unsigned _stdcall thread_el1(void* arg)
{
	while (1)
	{
		/*printf("%d\n", i);
		printf("%d\n", currentFloor[i]);*/
		BubbleSort(currentFloor, i); //버블정렬 함수 호출(currentFloor 배열을 정렬)
		MinMax(currentFloor, &el1_currentMin, &el1_currentMax); // 최대값, 최솟값
		for (int j = 0; j < i; j++) {
			newcurrent[j] = currentFloor[j]; // newcurrent배열에 저장
		}
		/*printf("%d %d", el1_currentMin, el1_currentMax);*/
		BubbleSort(targetFloor, i); //버블정렬 함수 호출
		MinMax(targetFloor, &el1_targetMin, &el1_targetMax);
		for (int j = 0; j < i; j++) {
			newtarget[j] = targetFloor[j]; // newtarget배열에 저장
		}
		/*printf("%d %d", el1_targetMin, el1_targetMax);*/
		if (newcurrent[0] != 0) {//배열에 0이 아니라면(배열에 숫자가 들어가있다는 뜻)
			while (elevator1 < newcurrent[0]) {
				Sleep(500);
				elevator1++;
				printf("%d", elevator1);
				for (int k = 0; k < i; k++)
				{
					if (elevator1 == newcurrent[k])
					{
						int close;
						printf("닫힘버튼(1)>");
						scanf("%d", &close);
						Cl_Button(close);
					}
				}
			}
		}



		//올ㄹ가는값읯 ㅚ대감
		//내려가는 층의 최소감
		//현재 엘리이터 층
		// 햔재 엘리베이터 항태 :올라가느지 내려가진
		//정렬
		//내려갈때는 정렬순서가 내림차순

	}

}

/*
버블정렬
함수 목적 : 오름차순으로 정렬해줌
개발 히스토리 :
	2023.10.11 - 버블정렬을 통해 오름차순 정렬
*/
void BubbleSort(int list[], int n) {
	int i, j, temp;

	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
		}
	}
}

/*
최대최소값
함수 목적 : 최대값과 최소값을 구함
개발 히스토리 :
	2023.10.20 - min, max 값을 구함
*/
void MinMax(int list[], int* min, int* max) { //
	*min = list[0]; // 초기 포인터 min값을 list[0]
	*max = list[0]; // 초기 포인터 max값을 list[0]
	for (int j = 0; j < i; j++) {
		if (list[j] < *min) { // list[j]가 min 보다 작다면 
			*min = list[j]; // min에 list[j] 값을 대입
		}
		if (list[j] > *max) { // list[j]가 max 보다 크다면
			*max = list[j]; // max에 list[j] 값을 대입
		}
	}
}

/*
닫힘버튼을 사용여부
함수 목적 : 닫힘버튼을 누르면 1초이후 닫히고 안누르면 3초후에 닫힘
return 값 : 램덤한값으로 받은 현재 사용자 위치
개발 히스토리 :
	2023.10.23 - Sleep 함수를 이용해 닫힘버튼을 누르면 1초뒤 문이닫힘니다 출력 아니라면 3초뒤 출력
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
닫힘버튼을 사용여부
함수 목적 : 닫힘버튼을 누르면 1초이후 닫히고 안누르면 3초후에 닫힘
return 값 : 램덤한값으로 받은 현재 사용자 위치
개발 히스토리 :
	2023.10.23 - Sleep 함수를 이용해 닫힘버튼을 누르면 1초뒤 문이닫힘니다 출력 아니라면 3초뒤 출력
*/
void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}