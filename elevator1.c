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



int elevator2 = 0;
int elevatorIdx = 0;
int totalweight = 0;
int totalpeople = 0;
int tarMin = 100;
int tarMax = 0;
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
	while (1)
	{
		srand(time(NULL));
		currentf = rand() % 100 + 1;
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
							if (start == true) {
								tarMax = targetf;
								start = false;
							}
							if (status.elevator1 < tarMax) {
								status.status = 1;
							}

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
					printf("가고자하는 층을 입력: ");
					scanf("%d", &targetf);

					if (targetf < currentf)
					{
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
					if (targetf < tarMin) {
						tarMin = targetf;
					}
					if (targetf > tarMax) {
						tarMax = targetf;
					}
					break;
				}
			}
		}
	}
}


unsigned _stdcall thread_el1(void* arg)
{
	status.status = 0; //멈춰있는 상태
	status.elevator1 = 1; //엘리베이터 초기층
	while (1)
	{
		if(status.status > 0){
			int upcount = 0;
			int douwncount = 0;
			for (int i = 0; i < 100; i++) {
				if (elevator[i].button == 1) {
					if (status.elevator1 == elevator[i].currentFloor) {
						totalweight += elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
						totalpeople += elevator[i].people;
						Doors = true;
						DrawElevator();
						Sleep(3000);
						Doors = false;
						/*elevator1++;*/
						upcount++;
					}
					else if (status.elevator1 == elevator[i].targetFloor) {
						totalweight -= elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
						totalpeople -= elevator[i].people;
						Doors = true;
						DrawElevator();
						Sleep(3000);
						Doors = false;
						elevator[i].currentFloor = 0;
					}
				}
				else if (upcount == 0 && elevator[i].button == 2) {
					if (status.elevator1 == elevator[i].currentFloor) {
						totalweight += elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
						totalpeople += elevator[i].people;
						Doors = true;
						DrawElevator();
						Sleep(3000);
						Doors = false;
						douwncount++;
					}
					else if (status.elevator1 == elevator[i].targetFloor) {
						totalweight -= elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
						totalpeople -= elevator[i].people;
						Doors = true;
						DrawElevator();
						Sleep(3000);
						Doors = false;
						elevator[i].currentFloor = 0;
					}
				}
				if (status.elevator1 == tarMin || status.elevator1 == tarMax) {
					status.status = 0;
				}
			}
			
			/*if (upcount == 0) {

			}*/

			DrawElevator();
			status.elevator1++;
			Sleep(500);
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
	printf("인원: %d\n", totalpeople);
	printf("무게: %d\n", totalweight);
	printf("-------------------\n");
	Gotxy(25, 14);
	printf("          ");
	Gotxy(25, 14);
}