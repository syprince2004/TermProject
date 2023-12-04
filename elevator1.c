#define _CRT_SECURE_NO_WARNINGS
#define ELEVATOR_COUNT 2 

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>
#include <stdbool.h>

#define SWAP(x,y,t) ( (t)=(x) , (x) = (y) , (y) =(t) )
#define INCREASE_ELEVATOR 10

unsigned _stdcall thread_el1(void* arg);
void DrawElevator();
void Gotxy(int x, int y);
void MinMax();
void Closed_Button();



int elevator2 = 0;
int elevatorIdx = 0;
int totalweight = 0;
int totalpeople = 0;
int Min = 100;
int Max = 0;
bool Doors = false;
bool Userio = false;
bool start = true;


struct person
{
	int man;
	int woman;
};

struct Elevator
{
	int currentFloor;
	int targetFloor;
	char button;
	int people;
	int rank;
	int cl_button;
	struct person weight;
};

struct Elevator elevator[100] = { 0, };

struct Elevator1_status
{
	int elevator1;
	int status;
};

struct Elevator1_status status;

int main()
{
	_beginthreadex(NULL, 0, thread_el1, 0, 0, NULL);
	/*HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, thread_el1, 0, 0, NULL);
	if (hThread == NULL)
	{
		printf("Thread creation failed!\n");
		return 1;
	}*/

	int button = 0;
	int targetf = 0;
	int currentf = 0;
	int rank = 0;
	while (1)
	{
		srand(time(NULL));
		currentf = rand() % 50 + 1;
		Gotxy(0, 13);
		printf("사용자가 있는 층 : %d층\n", currentf);
		printf("위(1), 아래(2) >> ");
		scanf("%d", &button);
		if (button == 1 || button == 2) {
			if (button == 1)
			{			
				while (1)
				{
					Gotxy(0, 14);
					printf("가고자하는 층을 입력: ");
					scanf("%d", &targetf);
					if (targetf > currentf)
					{		
						if (status.elevator1 < currentf) {
							if (status.status == 0) {
								Max = targetf;
								Min = currentf;
								start = false;
								status.status = 1;
							}
							rank = 1;

						}
						else if (status.elevator1 >= currentf) {
							rank = 2;
						}
						break;
					}
					else
					{
						continue;
					}
				}
			}
			else if (button == 2)
			{
				while (1)
				{
					Gotxy(0, 14);
					printf("가고자하는 층을 입력: ");
					scanf("%d", &targetf);

					if (targetf < currentf)
					{
						if (status.elevator1 > currentf) {
							if (status.status == 0) {
								Min = targetf;
								Max = currentf;
								start = false;
								status.status = 2;
							}
							rank = 1;

						}
						else if (status.elevator1 >= currentf) {
							rank = 2;
						}
						break;
					}
					else
					{
						continue;
					}
				}
			}

			for (int i = 0; i < 100; i++) {
				if (elevator[i].currentFloor == 0) {
					srand(time(NULL));
					elevator[i].button = button;
					elevator[i].currentFloor = currentf;
					elevator[i].targetFloor = targetf;
					elevator[i].people = rand() % 26 + 1;
					elevator[i].weight.man = rand() % (elevator[i].people + 1);
					elevator[i].weight.woman = elevator[i].people - elevator[i].weight.man;
					elevator[i].rank = rank;
					if (targetf < Min) {
						Min = targetf;
					}
					if (targetf > Max) {
						Max = targetf;
					}
					if (currentf < Min) {
						Min = currentf;
					}
					if (currentf > Max) {
						Max = currentf;
					}
					break;
				}
			}
		}
		system("cls");
	}
}


unsigned _stdcall thread_el1(void* arg)
{
	status.status = 0; //멈춰있는 상태
	status.elevator1 = 1; //엘리베이터 초기층
	while (1)
	{
		if(status.status > 0){
			if(status.status == 1){
				for (int i = 0; i < 100; i++) {
					if (elevator[i].button == 1) {
						if (status.elevator1 == elevator[i].currentFloor) {
							totalweight += elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
							totalpeople += elevator[i].people;
							Doors = true;
							DrawElevator();
							Closed_Button();
							Doors = false;
						}
						else if (status.elevator1 == elevator[i].targetFloor) {
							if (elevator[i].rank == 2) {
								DrawElevator();
								Sleep(500);
								continue;
							}
							else {
								totalweight -= elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
								totalpeople -= elevator[i].people;
								Doors = true;
								DrawElevator();
								Sleep(3000);
								Doors = false;
								elevator[i].currentFloor = 0;
								elevator[i].rank = 0;
								if (status.elevator1 == Max) {
									status.status = 0;
									MinMax();
								}
							}
						}
					}
					else if (elevator[i].button == 2) {
						if (status.elevator1 == Max) {
							status.status = 0;
							MinMax();
						}

					}
				}
				DrawElevator();
				if (status.status != 0) {
					status.elevator1++;
				}
				else{
					for (int i = 0; i < 100; i++) {
						if (elevator[i].currentFloor != 0) {
							status.status = 2;
							break;
						}
					}
				}
				Sleep(500);
			}
			else if (status.status == 2) {
				for (int i = 0; i < 100; i++) {
					if (elevator[i].button == 2) {
						if (status.elevator1 == elevator[i].currentFloor) {
							totalweight += elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
							totalpeople += elevator[i].people;
							Doors = true;
							DrawElevator();
							Closed_Button();
							Doors = false;
						}
						else if (status.elevator1 == elevator[i].targetFloor) {
							if (elevator[i].rank == 2) {
								DrawElevator();
								Sleep(500);
								continue;
							}
							else{
								totalweight -= elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
								totalpeople -= elevator[i].people;
								Doors = true;
								DrawElevator();
								Sleep(3000);
								Doors = false;
								elevator[i].currentFloor = 0;
								elevator[i].rank = 0;
								if (status.elevator1 == Min) {
									status.status = 0;
									MinMax();
								}
							}
						}
					}
					else if (elevator[i].button == 1) {
						if (status.elevator1 == Min) {
							status.status = 0;
							MinMax();
						}

					}
				}
				DrawElevator();
				if (status.status != 0) {
					status.elevator1--;
				}
				else {
					for (int i = 0; i < 100; i++) {
						if (elevator[i].currentFloor != 0) {
							status.status = 1;
							break;
						}
					}
				}
				Sleep(500);
			}
		}
	}
}

void Gotxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void DrawElevator()
{
	Gotxy(0, 0);
	printf("-----ELEVATOR1-----\n");
	Gotxy(0, 1);
	printf("Current floor: %d", status.elevator1);
	Gotxy(0, 2);
	if (Doors == true) {
		printf("Doors open  ");
	}
	else
		printf("Doors closed");
	Gotxy(0, 3);
	if (status.status == 0) {
		printf("상태 : 기다림    \n");
	}
	else if (status.status == 1) {
		printf("상태 : 올라가는중\n");
	}
	else if (status.status == 2) {
		printf("상태 : 내려가는중\n");
	}
	printf("인원: %d\n", totalpeople);
	printf("무게: %d\n", totalweight);
	printf("-------------------\n");
	Gotxy(0, 16);
	printf("                                             ");
	Gotxy(0, 18);
	for (int i = 0; i < 100; i++) {
		if (elevator[i].currentFloor != 0) {
			printf("버튼 :%d\n", elevator[i].button);
			printf("랭크: %d ", elevator[i].rank);
			printf("현재층 :%d ", elevator[i].currentFloor);
			printf("목표층 :%d\n", elevator[i].targetFloor);
		}
	}
	Gotxy(25, 14);
}

void MinMax()
{
	Min = 100; Max = 0;
	for (int i = 0; i < 100; i++) {
		if (elevator[i].currentFloor != 0) {
			if (elevator[i].targetFloor < Min) {
				Min = elevator[i].targetFloor;
			}
			if (elevator[i].targetFloor > Max) {
				Max = elevator[i].targetFloor;
			}
			if (elevator[i].currentFloor < Min) {
				Min = elevator[i].currentFloor;
			}
			if (elevator[i].currentFloor > Max) {
				Max = elevator[i].currentFloor;
			}
		}
	}
}

void Closed_Button()
{
	int elSeconds = 0;
	while (elSeconds < 3) {
		Gotxy(0, 14);
		printf("3초 안에 닫힘 버튼을 누르세요...(%d초 경과)", elSeconds);
		Sleep(1000);
		elSeconds++;

		// 추가: 닫힘 버튼을 입력받으면 문을 닫고 1초 후 출발
		if (_kbhit()) {
			int closeButton = _getch() - '0';
			if (closeButton == 1) { // 예시로 3을 닫힘 버튼으로 설정
				Doors = false;
				DrawElevator();
				Sleep(1000); // 추가: 1초 대기
				break;
			}
		}
	}
}