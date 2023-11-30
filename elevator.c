///*
//엘리베이터 관리 프로그램
//개발 환경 : VS2022, C언어, Windows
//개발 목적 : 엘리베이터 관리 프로그램의 개발을 통한 프로그래밍 능력 향상
//개발 결과 :
//개발 히스토리 :
//	2023.10.02 - main 함수에서 입력에 따른 if문 생성, 현재층과 목표층 입력
//	2023.10.07 - main 함수에서 쓰레드 호출, 쓰레드 생성
//	2023.10.21 - 버블정렬 함수를 이용해 전역변수인 currentFloor, targetFloor 배열을 오름차순정렬
//	2023.10.24 - 버블정렬한 currentFloor, targetFloor 배열을 새로운 배열에 저장
//	2023.10.29 - 최대값과 최솟값을 구하는 함수
//	2023.10.30 - 닫힘여부 함수
//	2023.11.03 - 창을 지우는 코드와 원하는 xy좌표에 출력할 수 있는 함수
//	2023.11.05 - 사용자 임의 입력(3)을 눌렀을때 랜덤으로 정해지고 움직이는 코드
//	2023.11.06 - 초기층에서 현재층으로 가고 현재층에서 목표층으로 가는 함수
//	2023.11.08 - 구조체 선언
//	2023.11.09 - 프로세스 생성하는 함수
//	2023.11.10 - 프로세스 생성하는 함수 주석처리(경로가 맞지않음)
//	2023.11.13 - 엘리베이터층이 현재층, 목표층이랑 같다면 멈춤
//오픈소스 :
//라이브러리 :
//*/
//
//
//#define _CRT_SECURE_NO_WARNINGS
//#define ELEVATOR_COUNT 2 
//
//#include <stdio.h>
//#include <time.h>
//#include <stdlib.h>
//#include <Windows.h>
//#include <process.h>
////#include <cstdio>
//#include <conio.h>
//#include <tchar.h>
//
//
//#define SWAP(x,y,t) ( (t)=(x) , (x) = (y) , (y) =(t) ) // 두개의 자리를 바꿔줌
//
////CRITICAL_SECTION mutex; // 뮤텍스 추가
//
//int newcurrent[100] = { 0 };
//int newtarget[100] = { 0 };
//int elevator1 = 0;
//int elevator2 = 0;
//int el1_currentMax = 0;
//int el1_currentMin = 0;
//int el1_targetMax = 0;
//int el1_targetMin = 0;
//int el2_currentMax = 0;
//int el2_currentMin = 0;
//int el2_targetMax = 0;
//int el2_targetMin = 0;
//int i = 0;
//
//
//unsigned _stdcall thread_el1(void* arg);
//
//unsigned _stdcall thread_el2(void* arg);
//
//unsigned _stdcall userIO(void* arg);
//
//void BubbleSort(int list[], int n);
//
//void MinMax(int list[], int* min, int* max, int size);
//
//int Cl_Button(int Close);
//
//void Gotxy(int x, int y);
//
//int El_Floor(int EarlyFloor, int LaterFloor);
//
////void CreateElevatorProcess();
//
//void MoveElevator();
//
//void GetUserInput();
//
//
//
///*
//엘리베이터에 필요한 구조체
//구조체 목적 : 각각 4개의 배열이 하나의 구조체 배열에 들어감 사람하나당 구조체 배열에 추가
//return 값 :
//개발 히스토리 :
//	2023.11.08 - 전역변수로 썼던 변수 4개를 구조체로 바꿈
//*/
//struct Elevator
//{
//	int currentFloor[100];
//	int targetFloor[100];
//	int button[100];
//	int people[100];
//};
//
//struct Elevator elevator[ELEVATOR_COUNT][100];
//
///*
//메인함수
//함수 목적 : 모든 진행이 이루어지는 공간
//return 값 :
//개발 히스토리 :
//	2023.10.02 - 입력에 따른 if문 생성, 사용자 현재층(currentFloor) 랜덤으로 입력받기, 가고자하는 층(targetFloor) 입력받기
//	2023.10.07 - 쓰레드 호출
//	2023.11.03 - 창을 지우는 코드 작성
//	2023.11.05 - 임의 입력(3)을 눌렀을때 랜덤으로 작동되는 코드
//	2023.11.06 - 엘리베이터 움직이는 함수 호출
//*/
//int main()
//{
//	_beginthreadex(NULL, 0, thread_el1, 0, 0, NULL);
//	_beginthreadex(NULL, 0, thread_el2, 0, 0, NULL);
//	while (1)
//	{
//		/*GetUserInput();*/
//		/*MoveElevator();*/
//		int targetf;
//		int currentf;
//		int a;
//		int j;
//		srand(time(NULL));
//		//system("cls");
//		Gotxy(0, 14);
//		printf("위(1), 아래(2), 임의사용자(3)");
//		Gotxy(0, 13);
//		scanf("%d", &a); //숫자로 입력
//		system("cls");
//		//printf("%d", button);
//		if (a == 1) { // 1 or 2를 입력했을때
//			if (elevator1 >= elevator2) {
//				j = 0;
//			}
//			else if (elevator1 < elevator2) {
//				j = 1;
//			}
//			elevator[j][i].button[i] = a;
//			currentf = rand() % 100 + 1; // 현재층을 1~100층중 랜덤으로 결정
//			elevator[j][i].currentFloor[i] = currentf; // 전역변수로 선언된currentFloor에 대입
//			while (1) {
//				Gotxy(0, 14);
//				printf("가고자하는 층을 입력: ");
//				Gotxy(0, 13);
//				scanf("%d", &targetf); // 목표층을 입력받음
//				Gotxy(0, 13);
//				printf("                                                    ");
//				if (targetf > currentf) {
//					elevator[j][i].targetFloor[i] = targetf; // 전역변수로 선언된 targetFloor에 대입
//					/*printf("%d %d\n", currentFloor[i], targetFloor[i]);*/
//					i++;
//					break;
//				}
//				else {
//					/*system("cls");*/
//					continue;
//				}
//			}
//		}
//		else if (a == 2) { // 1 or 2를 입력했을때
//			if (elevator1 >= elevator2) {
//				j = 0;
//			}
//			else if (elevator1 < elevator2) {
//				j = 1;
//			}
//			elevator[j][i].button[i] = a;
//			currentf = rand() % 100 + 1; // 현재층을 1~100층중 랜덤으로 결정
//			elevator[j][i].currentFloor[i] = currentf; // 전역변수로 선언된currentFloor에 대입
//			while (1) {
//				Gotxy(0, 14);
//				printf("가고자하는 층을 입력: ");
//				Gotxy(0, 13);
//				scanf("%d", &targetf); // 목표층을 입력받음
//				Gotxy(0, 13);
//				printf("                                                    ");
//				if (targetf < currentf) {
//					elevator[j][i].targetFloor[i] = targetf; // 전역변수로 선언된 targetFloor에 대입
//					/*printf("%d %d\n", currentFloor[i], targetFloor[i]);*/
//					i++;
//					break;
//				}
//				else {
//					/*system("cls");*/
//					continue;
//				}
//			}
//		}
//		else if (a == 3) {
//			if (elevator1 >= elevator2) {
//				j = 0;
//			}
//			else if (elevator1 < elevator2) {
//				j = 1;
//			}
//			srand(time(NULL));
//			elevator[j][i].button[i] = rand() % 2 + 1; //버튼도 위로 갈건지 아래로 갈건지 랜덤
//			currentf = rand() % 100 + 1; //현재 층도 랜덤
//			elevator[j][i].currentFloor[i] = currentf;
//			if (elevator[j][i].button[i] == 1) { //위로 갈 경우
//				targetf = rand() % (99 - currentf) + currentf; // 현재층이 목표층보다 높으면 안되므로 랜덤
//			}
//			else if (elevator[j][i].button[i] == 2) {
//				targetf = rand() % (currentf - 1) + 1; //현재층이 목표층보다 낮으면 안되므로 랜덤
//			}
//			elevator[j][i].targetFloor[i] = targetf;
//			i++;
//		}
//		else {
//			printf("다시 입력하세요\n");
//			continue;
//		}
//		/*CreateElevatorProcess();*/
//	}
//	
//}
//
////void GetUserInput()
////{
////	int targetf;
////	int currentf;
////	int a;
////	srand(time(NULL));
////
////	Gotxy(0, 14);
////	printf("위(1), 아래(2), 임의사용자(3)");
////	Gotxy(0, 13);
////	scanf("%d", &a);
////	Gotxy(0, 13);
////	printf("                                             \n");
////	if (a == 1 || a == 2)
////	{
////		int direction = (a == 1) ? 1 : -1;
////		elevator[i].button[i] = a;
////		currentf = rand() % 100 + 1;
////		elevator[i].currentFloor[i] = currentf;
////		while (1)
////		{
////			Gotxy(0, 14);
////			printf("가고자하는 층을 입력");
////			Gotxy(0, 13);
////			scanf("%d", &targetf);
////			printf("                                                \n");
////			if ((direction == 1 && targetf > currentf) || (direction == -1 && targetf < currentf))
////			{
////				elevator[i].targetFloor[i] = targetf;
////				i++;
////				break;
////			}
////			else
////			{
////				continue;
////			}
////		}
////	}
////	else if (a == 3)
////	{
////		elevator[i].button[i] = rand() % 2 + 1;
////		currentf = rand() % 100 + 1;
////		elevator[i].currentFloor[i] = currentf;
////		if (elevator[i].button[i] == 1)
////		{
////			targetf = rand() % (99 - currentf) + currentf;
////		}
////		else if (elevator[i].button[i] == 2)
////		{
////			targetf = rand() % (currentf - 1) + 1;
////		}
////		elevator[i].targetFloor[i] = targetf;
////		i++;
////	}
////	else
////	{
////		printf("다시 입력하세요\n");
////	}
////}
//
////void MoveElevator()
////{
////	for (int j = 0; j < i; j++)
////	{
////		int current = elevator[j].currentFloor[j];
////		int target = elevator[j].targetFloor[j];
////
////		// 엘리베이터가 이미 도착한 경우
////		if (elevator1 == current)
////		{
////			Gotxy(0, 0);
////			puts("elevator1---------------------------\n");
////			printf("currnet floor: %d\n", elevator1);
////			puts("doors open  \n");
////			Sleep(3000);
////
////			// 엘리베이터 멈춤
////			// 엘리베이터 출발 전 초기화
////			//elevator[j].currentFloor[j] = 0;
////			//elevator[j].targetFloor[j] = 0;
////		}
////
////		// 엘리베이터가 이미 도착한 경우
////		if (elevator1 == target)
////		{
////			Gotxy(0, 0);
////			puts("elevator1---------------------------\n");
////			printf("currnet floor: %d\n", elevator1);
////			puts("doors open  \n");
////			Sleep(3000);
////
////			// 엘리베이터 멈춤
////			// 엘리베이터 출발 전 초기화
////			//elevator[j].currentFloor[j] = 0;
////			//elevator[j].targetFloor[j] = 0;
////		}
////		else
////		{
////			Gotxy(0, 0);
////			puts("elevator1---------------------------\n");
////			printf("currnet floor: %d\n", elevator1);
////			puts("doors closed\n");
////		}
////
////		Sleep(500);
////
////		elevator1++;
////	}
////}
//
///*
//독립적으로 움직이는 쓰레드
//함수 목적 : 메인에서 입력받고 전역변수의 배열에 넣으면 엘리베이터 위치와 비교
//개발 히스토리 :
//	2023.10.07 - 쓰레드 생성
//	2023.10.21 - 전역변수인 currentFloor, targetFloor 배열을 버블정렬
//	2023.10.24 - 버블정렬한 currentFloor, targetFloor 배열을 새로운 배열에 저장
//	2023.10.29 - 최대최소값을 찾는 함수 선언
//	2023.11.05 - 닫힘버튼 함수 호출
//	2023.11.13 - 엘리베이터와 현재층, 목표층이 같다면 멈춤
//*/
//unsigned _stdcall thread_el1(void* arg)
//{
//	
//	while (1)
//	{
//		int i = 0;
//		/*printf("%d\n", i);*/
//		/*printf("%d %d\n", elevator[i].currentFloor[i], elevator);*/
//		MinMax(elevator[0][i].currentFloor, &el1_currentMin, &el1_currentMax, i); // 최대값, 최솟값
//		BubbleSort(elevator[0][i].currentFloor, i);//버블정렬 함수 호출(currentFloor 배열을 정렬)
//		for (int j = 0; j < i; j++) {
//			newcurrent[j] = elevator[0][i].currentFloor[j]; // newcurrent배열에 저장
//		}
//		/*printf("%d %d", el1_currentMin, el1_currentMax);*/
//		MinMax(elevator[0][i].targetFloor, &el1_targetMin, &el1_targetMax, i);
//		BubbleSort(elevator[0][i].targetFloor, i);//버블정렬 함수 호출
//		for (int j = 0; j < i; j++) {
//			newtarget[j] = elevator[0][i].targetFloor[j]; // newtarget배열에 저장
//		}
//		/*printf("%d %d", el1_targetMin, el1_targetMax);*/
//		if (elevator[0][i].currentFloor[i] != 0 && elevator[0][i].targetFloor[i] != 0) {
//			/*elevator[i].currentFloor[i] = El_Floor(current, target)*/;
//			if (elevator1 == elevator[0][i].currentFloor[i]) {
//				Gotxy(0, 0);
//				puts("elevator1---------------------------\n");
//				printf("currnet floor: %d\n", elevator1);
//				puts("doors open  \n");
//				Gotxy(0, 13);
//				Sleep(3000);
//				
//				/*elevator[i].currentFloor[i] = elevator[i].targetFloor[i];
//				Gotxy(0, 0);
//				puts("elevator1---------------------------\n");
//				printf("current floor: %d\n", elevator1);
//				puts("doors closed\n");
//				Gotxy(0, 13);
//				Sleep(500);*/
//				// 엘리베이터 멈춤
//
//				// 엘리베이터 출발 전 초기화
//				//elevator[i].currentFloor[i] = 0;
//				//elevator[i].targetFloor[i] = 0;
//			}
//			else if (elevator1 == elevator[0][i].targetFloor[i]) {
//				Gotxy(0, 0);
//				puts("elevator1----------------------------\n");
//				printf("currnet floor: %d\n", elevator1);
//				puts("doors open  \n");
//				Gotxy(0, 13);
//				Sleep(3000);
//
//				/*elevator[i].currentFloor[i] = elevator[i].targetFloor[i];
//				Gotxy(0, 0);
//				puts("elevator1----------------------------\n");
//				printf("current floor: %d\n", elevator1);
//				puts("doors closed\n");
//				Gotxy(0, 13);
//				Sleep(500);*/
//				// 엘리베이터 멈춤
//
//				// 엘리베이터 출발 전 초기화
//				//elevator[i].currentFloor[i] = 0;
//				//elevator[i].targetFloor[i] = 0;
//			}
//			else{
//				Gotxy(0, 0);
//				puts("elevator1----------------------------\n");
//				printf("currnet floor: %d\n", elevator1);
//				puts("doors closed\n");
//				Gotxy(0, 13);
//				Sleep(500);
//				
//				
//			}
//			
//			elevator1++;
//			
//
//			/*if (elevator1 > el1_targetMax) {
//				int temp = elevator[1][i].targetFloor[i];
//				elevator[1][i].targetFloor[i] = elevator[1][i].currentFloor[i];
//				elevator[1][i].currentFloor[i] = temp;
//			}
//			else
//				elevator1++;*/
//			
//		}
//		//if (elevator1 <= elevator[i].currentFloor[i]) {//배열에 0이 아니라면(배열에 숫자가 들어가있다는 뜻)
//		//	Sleep(500);
//		//	elevator1++;
//		//	printf("%d", elevator1);
//		//	for (int k = 0; k < i; k++)
//		//	{
//		//		if (elevator1 == newcurrent[k])
//		//		{
//		//			int close;
//		//			printf("닫힘버튼(1)>");
//		//			scanf("%d", &close); //닫힘버튼을 입력
//		//			Cl_Button(close); // 함수 이동
//		//		}
//		//	}
//		//	for (int k = 0; k < i; k++)
//		//	{
//		//		if (elevator1 == newtarget[k])
//		//		{
//		//			Sleep(3000); // 목표층에 도착하면 사람이 내리고 3초후 감
//		//			printf("도착 층: %d\n", elevator1);
//		//		}
//		//	}
//		//}
//
//
//
//		/*올ㄹ가는값 ㅚ대감
//		내려가는 층의 최소감
//		현재 엘리이터 층
//		 h재 엘리베이터 항태 :올라가느지 내려가진
//		정렬
//		내려갈때는 정렬순서가 내림차순*/
//
//	}
//
//}
//
///*
//독립적으로 움직이는 쓰레드 엘리베이터 2
//함수 목적 : 메인에서 입력받고 전역변수의 배열에 넣으면 엘리베이터 위치와 비교
//개발 히스토리 :
//	
//*/
//unsigned _stdcall thread_el2(void* arg)
//{
//
//	while (1)
//	{
//		int i = 0;
//		/*printf("%d\n", i);*/
//		/*printf("%d %d\n", elevator[i].currentFloor[i], elevator);*/
//		MinMax(elevator[1][i].currentFloor, &el2_currentMin, &el2_currentMax, i); // 최대값, 최솟값
//		BubbleSort(elevator[1][i].currentFloor, i);//버블정렬 함수 호출(currentFloor 배열을 정렬)
//		for (int j = 0; j < i; j++) {
//			newcurrent[j] = elevator[1][i].currentFloor[j]; // newcurrent배열에 저장
//		}
//		/*printf("%d %d", el1_currentMin, el1_currentMax);*/
//		MinMax(elevator[1][i].targetFloor, &el2_targetMin, &el2_targetMax, i);
//		BubbleSort(elevator[1][i].targetFloor, i);//버블정렬 함수 호출
//		for (int j = 0; j < i; j++) {
//			newtarget[j] = elevator[1][i].targetFloor[j]; // newtarget배열에 저장
//		}
//		/*printf("%d %d", el1_targetMin, el1_targetMax);*/
//		if (elevator[1][i].currentFloor[i] != 0 && elevator[1][i].targetFloor[i] != 0) {
//			/*elevator[i].currentFloor[i] = El_Floor(current, target)*/;
//			if (elevator2 == elevator[1][i].currentFloor[i]) {
//				Gotxy(0, 5);
//				puts("elevator2---------------------------\n");
//				printf("currnet floor: %d\n", elevator1);
//				puts("doors open  \n");
//				Gotxy(0, 13);
//				Sleep(3000);
//
//				/*elevator[i].currentFloor[i] = elevator[i].targetFloor[i];
//				Gotxy(0, 0);
//				puts("elevator1---------------------------\n");
//				printf("current floor: %d\n", elevator1);
//				puts("doors closed\n");
//				Gotxy(0, 13);
//				Sleep(500);*/
//				// 엘리베이터 멈춤
//
//				// 엘리베이터 출발 전 초기화
//				//elevator[i].currentFloor[i] = 0;
//				//elevator[i].targetFloor[i] = 0;
//			}
//			else if (elevator2 == elevator[1][i].targetFloor[i]) {
//				Gotxy(0, 5);
//				puts("elevator2----------------------------\n");
//				printf("currnet floor: %d\n", elevator1);
//				puts("doors open  \n");
//				Gotxy(0, 13);
//				Sleep(3000);
//
//				/*elevator[i].currentFloor[i] = elevator[i].targetFloor[i];
//				Gotxy(0, 0);
//				puts("elevator1----------------------------\n");
//				printf("current floor: %d\n", elevator1);
//				puts("doors closed\n");
//				Gotxy(0, 13);
//				Sleep(500);*/
//				// 엘리베이터 멈춤
//
//				// 엘리베이터 출발 전 초기화
//				//elevator[i].currentFloor[i] = 0;
//				//elevator[i].targetFloor[i] = 0;
//			}
//			else {
//				Gotxy(0, 5);
//				puts("elevator2----------------------------\n");
//				printf("currnet floor: %d\n", elevator2);
//				puts("doors closed\n");
//				Gotxy(0, 13);
//				Sleep(500);
//
//
//			}
//
//			elevator2++;
//
//			/*if (elevator2 > el1_targetMax) {
//				int temp = elevator[2][i].targetFloor[i];
//				elevator[2][i].targetFloor[i] = elevator[2][i].currentFloor[i];
//				elevator[2][i].currentFloor[i] = temp;
//			}
//			else
//				elevator2++;*/
//
//		}
//		//if (elevator1 <= elevator[i].currentFloor[i]) {//배열에 0이 아니라면(배열에 숫자가 들어가있다는 뜻)
//		//	Sleep(500);
//		//	elevator1++;
//		//	printf("%d", elevator1);
//		//	for (int k = 0; k < i; k++)
//		//	{
//		//		if (elevator1 == newcurrent[k])
//		//		{
//		//			int close;
//		//			printf("닫힘버튼(1)>");
//		//			scanf("%d", &close); //닫힘버튼을 입력
//		//			Cl_Button(close); // 함수 이동
//		//		}
//		//	}
//		//	for (int k = 0; k < i; k++)
//		//	{
//		//		if (elevator1 == newtarget[k])
//		//		{
//		//			Sleep(3000); // 목표층에 도착하면 사람이 내리고 3초후 감
//		//			printf("도착 층: %d\n", elevator1);
//		//		}
//		//	}
//		//}
//
//
//
//		/*올ㄹ가는값 ㅚ대감
//		내려가는 층의 최소감
//		현재 엘리이터 층
//		 h재 엘리베이터 항태 :올라가느지 내려가진
//		정렬
//		내려갈때는 정렬순서가 내림차순*/
//
//	}
//
//}
//
///*
//버블정렬
//함수 목적 : 오름차순으로 정렬해줌
//개발 히스토리 :
//	2023.10.24 - 버블정렬을 통해 오름차순 정렬
//*/
//void BubbleSort(int list[], int n) {
//	int i, j, temp;
//
//	for (i = n - 1; i > 0; i--) {
//		for (j = 0; j < i; j++) {
//			if (list[j] > list[j + 1])
//				SWAP(list[j], list[j + 1], temp);
//		}
//	}
//}
//
///*
//최대최소값
//함수 목적 : 최대값과 최소값을 구함
//개발 히스토리 :
//	2023.10.29 - min, max 값을 구함
//*/
//void MinMax(int list[], int* min, int* max, int size) { //
//	//while(1){
//	//	if (i <= 0) {
//	//		// 배열이 비어있을 때의 예외 처리
//	//		return MinMax;
//	//	}
//	//	else
//	//		break;
//	//}
//	if (size <= 0) {
//		*min = 0;
//		*max = 0;
//		return;
//	}
//	*min = list[0]; // 초기 포인터 min값을 list[0]
//	*max = list[0]; // 초기 포인터 max값을 list[0]
//	for (int j = 0; j < size; j++) {
//		if (list[j] < *min) { // list[j]가 min 보다 작다면 
//			*min = list[j]; // min에 list[j] 값을 대입
//		}
//		if (list[j] > *max) { // list[j]가 max 보다 크다면
//			*max = list[j]; // max에 list[j] 값을 대입
//		}
//	}
//}
//
///*
//닫힘버튼을 사용여부
//함수 목적 : 닫힘버튼을 누르면 1초이후 닫히고 안누르면 3초후에 닫힘
//return 값 : 램덤한값으로 받은 현재 사용자 위치
//개발 히스토리 :
//	2023.10.30 - Sleep 함수를 이용해 닫힘버튼을 누르면 1초뒤 문이닫힘니다 출력 아니라면 3초뒤 출력
//*/
//int Cl_Button(int Close)
//{
//	if (Close == 1) {
//		Sleep(1000);
//	}
//	else
//		Sleep(3000);
//	printf("문이 닫힘니다\n");
//	return 0;
//}
//
///*
//cmd환경에서 위치 지정해주는 함수
//함수 목적 : 함수를 선언하면 x,y의 좌표값에 표현
//return 값 :
//개발 히스토리 :
//	2023.11.03 - 좌표지정해 좌표위치에 출력
//*/
//void Gotxy(int x, int y)
//{
//	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD pos;
//	pos.X = x;
//	pos.Y = y;
//	SetConsoleCursorPosition(handle, pos);
//}
//
///*
//초기층에서 가고싶은 층으로 가는 코드
//함수 목적 : 초기값을 끝날때마다 바꿔 시작 지점을 바꾼다
//return 값 : 바뀐 초기값
//개발 히스토리 :
//	2023.11.06 - 초기층에서 현재층으로 가고 현재층에서 목표층으로 가는 함수 구현(엘리베이터 한층당 속도는 Sleep함수를 사용해 0.5초)
//*/
////int El_Floor(int EarlyFloor, int LaterFloor) {
////	double timePerFloor = 0.5; // 한 층 이동에 걸리는 시간 (초)
////
////	if (EarlyFloor == LaterFloor) {
////		printf("엘리베이터는 이미 층에 도착했습니다.\n"); //현재층과 목표층을 비교하여 같다면 문구 출력
////	}
////	else if (EarlyFloor < LaterFloor) {
////		printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", EarlyFloor - 10, LaterFloor - 10); //현재층이 목표층보다 작다면 현재층에서 목표층으로 증가
////		while (EarlyFloor < LaterFloor) {
////			Sleep((int)(timePerFloor * 1000)); // Sleep 함수를 사용하여 0.5초 대기
////			EarlyFloor++; //
////			printf("현재 %d층\n", EarlyFloor - 10); //숫자를 하나씩 증가해주면서 층 보여줌
////		}
////		printf("엘리베이터가 %d에 도착했습니다.\n", LaterFloor - 10);
////		EarlyFloor = LaterFloor;
////	}
////	else {
////		printf("엘리베이터가 %d층에서 %d층으로 이동합니다.\n", EarlyFloor - 10, LaterFloor - 10); //현재층이 목표층보다 크다면 현재층에서 목표층으로 증가
////		while (EarlyFloor > LaterFloor) {
////			Sleep((int)(timePerFloor * 1000)); // Sleep 함수를 사용하여 대기
////			EarlyFloor--;
////			printf("현재 %d층\n", EarlyFloor - 10); //숫자를 하나씩 감소해주면서 층 보여줌
////		}
////		printf("엘리베이터가 %d에 도착했습니다.\n", LaterFloor - 10);
////		EarlyFloor = LaterFloor;
////	}
////	return EarlyFloor;
////}
//
///*
//프로세스 함수 생성
//함수 목적 : 엘리베이터가 움직이는 모습이 프로세스에서만 움직이게
//개발 히스토리 :
//	2023.11.09 - 프로세스를 생성
//	2023.11.10 - 주석처리
//*/
////void CreateElevatorProcess()
////{
////	STARTUPINFO si;
////	PROCESS_INFORMATION pi;
////
////	ZeroMemory(&si, sizeof(si));
////	si.cb = sizeof(si);
////	ZeroMemory(&pi, sizeof(pi));
////
////	// 프로세스 생성
////	if (!CreateProcess(
////		_T("D:\\program\\finall\\TremProject\\process1.exe"), // 실행 파일 경로
////		NULL,                            // 커맨드 라인
////		NULL,                            // 보안 속성
////		NULL,                            // 보안 속성
////		FALSE,                           // 상속 여부
////		0,                               // 플래그
////		NULL,                            // 환경 변수
////		NULL,                            // 현재 디렉토리
////		&si,                             // 시작 정보 구조체
////		&pi))                            // 프로세스 정보 구조체
////	{
////		printf("프로세스 생성에 실패했습니다. 오류 코드: %lu\n", GetLastError());
////		LPVOID errorMessage;
////		FormatMessage(
////			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
////			NULL,
////			GetLastError(),
////			0, // Default language
////			(LPWSTR)&errorMessage,
////			0,
////			NULL
////		);
////		wprintf(L"에러 메시지: %s\n", errorMessage);
////		LocalFree(errorMessage);
////	}
////
////	// 프로세스 및 스레드 핸들 닫기
////	CloseHandle(pi.hProcess);
////	CloseHandle(pi.hThread);
////}