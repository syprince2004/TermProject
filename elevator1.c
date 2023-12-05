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
void DrawElevator(int n);
void Gotxy(int x, int y);
void MinMax(int str, int choice);
void Closed_Button(int n);
int choice_elevator(int currentf);
void changepassword();
void userUI1(int n);
void userUI2(int n);
void adminUI(int n);


bool Doors = false;
bool Userio = false;
bool start = true;
bool display = true;
char password[20] = "seoyeon04"; // 초기 비밀번호는 seoyeon04로 지정 또한 비밀번호 최대 입력은 20자를 넘어가지 않음
char pass[20];
int menu = 0;
char usertype = 'u';


struct person
{
	int man;
	int woman;
};

struct Elevator
{
	int elevator_num;
	int currentFloor;
	int targetFloor;
	int button;
	int people;
	int rank;
	int cl_button;
	struct person weight;
};

struct Elevator elevator[100] = { 0, };

struct Elevator1_status
{
	int totalweight;
	int totalpeople;
	int Min;
	int Max;
	int elevator;
	int floor;
	int status;
};

struct Elevator1_status status[2];

int main()
{
	_beginthreadex(NULL, 0, thread_el1, 0, 0, NULL);
	_beginthreadex(NULL, 0, thread_el1, 1, 0, NULL);
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
	int choice = 0;

	status[0].Min = 100;
	status[0].Max = 0;
	status[1].Min = 100;
	status[1].Max = 0;
	while (1)
	{
		srand(time(NULL));
		currentf = rand() % 50 + 1;
		Gotxy(0, 13);
		printf("                                                                    \n");
		printf("                                                                    ");
		Gotxy(0, 13);
		printf("사용자가 있는 층 : %d층\n", currentf);
		Gotxy(0, 14);
		printf("위(1), 아래(2) 관리자(3)>> ");
		scanf("%d", &button);
		if (button == 3) {
			system("cls");
			while (1)
			{
				display = false;
				Gotxy(0, 0);
				printf("비밀번호 확인 >>");
				scanf("%s",&pass);
				if (strcmp(password, pass) == 0) {
					usertype = 'a';
					Gotxy(0, 0);
					printf("                                                         ");
					Gotxy(0, 0);
					printf("비밀번호 확인 완료");
					display = true;
					Gotxy(0, 14);
					printf("원하는 메뉴를 입력 비밀번호 변경(1), 점검할 엘리베이터(2), 관리자 메뉴 나가기(3)");
					scanf("%d", &menu);
					if (menu == 1)
					{
						changepassword();
					}
					/*else if (menu == 2)
					{
						maintenance();
					}*/
					
				}
			}
		}
		else if (button == 1 || button == 2) {
			choice = choice_elevator(currentf);
			if (button == 1)
			{			
				while (1)
				{
					Gotxy(0, 14);
					printf("                                                             ");
					Gotxy(0, 14);
					printf("가고자하는 층을 입력: ");
					scanf("%d", &targetf);
					if (targetf > currentf)
					{		
						if (status[choice].floor < currentf) {
							if (status[choice].status == 0) {
								status[choice].Max = targetf;
								status[choice].Min = currentf;
								start = false;
								status[choice].status = 1;
							}
							rank = 1;

						}
						else if (status[choice].floor >= currentf) {
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
						if (status[choice].floor > currentf) {
							if (status[choice].status == 0) {
								status[choice].Min = targetf;
								status[choice].Max = currentf;
								start = false;
								status[choice].status = 2;
							}
							rank = 1;

						}
						else if (status[choice].floor >= currentf) {
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
					elevator[i].elevator_num = choice;
					elevator[i].button = button;
					elevator[i].currentFloor = currentf;
					elevator[i].targetFloor = targetf;
					elevator[i].people = rand() % 26 + 1;
					elevator[i].weight.man = rand() % (elevator[i].people + 1);
					elevator[i].weight.woman = elevator[i].people - elevator[i].weight.man;
					elevator[i].rank = rank;
					if (targetf < status[choice].Min) {
						status[choice].Min = targetf;
					}
					if (targetf > status[choice].Max) {
						status[choice].Max = targetf;
					}
					if (currentf < status[choice].Min) {
						status[choice].Min = currentf;
					}
					if (currentf > status[choice].Max) {
						status[choice].Max = currentf;
					}
					break;
				}
			}
		}
		/*DrawElevator(0);
		DrawElevator(1);*/
	}
}


unsigned _stdcall thread_el1(void* arg)
{
	int n = (int)arg;
	status[n].status = 0; //멈춰있는 상태
	status[n].floor = 1; //엘리베이터 초기층
	DrawElevator(n);
	while (1)
	{
		if(status[n].status > 0){
			if(status[n].status == 1){
				for (int i = 0; i < 100; i++) {
					if(elevator[i].elevator_num == n){
						if (elevator[i].button == 1) {
							if (status[n].floor == elevator[i].currentFloor) {
								status[n].totalweight += elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
								status[n].totalpeople += elevator[i].people;
								Doors = true;
								DrawElevator(n);
								Closed_Button(n);
								Doors = false;
							}
							else if (status[n].floor == elevator[i].targetFloor) {
								if (elevator[i].rank == 2) {
									DrawElevator(n);
									Sleep(500);
								}
								else {
									status[n].totalweight -= elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
									status[n].totalpeople -= elevator[i].people;
									Doors = true;
									DrawElevator(n);
									Sleep(3000);
									Doors = false;
									elevator[i].currentFloor = 0;
									elevator[i].rank = 0;
									if (status[n].floor == status[n].Max) {
										status[n].status = 0;
										status[n].Min = status[n].Max;
										MinMax(0, n);
									}
								}
							}
						}
						else if (elevator[i].button == 2) {
							if (status[n].floor == status[n].Max) {
								status[n].status = 0;
								status[n].Min = status[n].Max;
								MinMax(0, n);
							}

						}
					}
				}
				DrawElevator(n);
				if (status[n].status != 0) {
					status[n].floor++;
				}
				else{
					for (int i = 0; i < 100; i++) {
						if(elevator[i].elevator_num == n){
							if (elevator[i].currentFloor != 0) {
								status[n].status = 2;
							}
							if (elevator[i].button == 2) {
								elevator[i].rank = 1;
							}
						}
					}
				}
				Sleep(500);
			}
			else if (status[n].status == 2) {
				for (int i = 0; i < 100; i++) {
					if(elevator[i].elevator_num == n){
						if (elevator[i].button == 2) {
							if (status[n].floor == elevator[i].currentFloor) {
								status[n].totalweight += elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
								status[n].totalpeople += elevator[i].people;
								Doors = true;
								DrawElevator(n);
								Closed_Button(n);
								Doors = false;
							}
							else if (status[n].floor == elevator[i].targetFloor) {
								if (elevator[i].rank == 2) {
									DrawElevator(n);
									Sleep(500);
								}
								else{
									status[n].totalweight -= elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
									status[n].totalpeople -= elevator[i].people;
									Doors = true;
									DrawElevator(n);
									Sleep(3000);
									Doors = false;
									elevator[i].currentFloor = 0;
									elevator[i].rank = 0;
									if (status[n].floor == status[n].Min) {
										status[n].status = 0;
										status[n].Max = status[n].Min;
										MinMax(0, n);
									}
								}
							}
						}
						else if (elevator[i].button == 1) {
							if (status[n].floor == status[n].Min) {
								status[n].status = 0;
								status[n].Max = status[n].Min;
								MinMax(0, n);
							}

						}
					}
				}
				DrawElevator(n);
				if (status[n].status != 0) {
					status[n].floor--;
				}
				else {
					for (int i = 0; i < 100; i++) {
						if(elevator[i].elevator_num == n){
							if (elevator[i].currentFloor != 0) {
								status[n].status = 1;
							}
							if (elevator[i].button == 1) {
								elevator[i].rank = 1;
							}
						}
					}
				}
				Sleep(500);
			}
		}
		else {
			MinMax(1, n);
			if (status[n].floor < status[n].Max) {
				status[n].status = 1;
			}
			else if (status[n].floor > status[n].Min) {
				status[n].status = 2;
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

void DrawElevator(int n)
{
	if(display){
		Sleep(300);
		if(usertype == 'a') {
			adminUI(n);
		}
		else if (usertype == 'u') {
			if (n == 0) {
				userUI1(0);
			}
			else if (n == 1) {
				userUI2(1);
			}
		}
	}
}

void userUI1(int n)
{
	int wt = 0;
	/*Gotxy(wt, 0);
	printf("                        ");*/
	Gotxy(wt, 0);
	printf("-----ELEVATOR%d-----", 1);
	/*Gotxy(wt, 1);
	printf("                        ");*/
	Gotxy(wt, 1);
	printf("Current floor: %d", status[0].floor);
	//Gotxy(wt, 2);
	//printf("                        ");
	Gotxy(wt, 2);
	if (status[0].status == 0) {
		printf("상태 : 기다림    ");
	}
	else if (status[0].status == 1) {
		printf("상태 : 올라가는중");
	}
	else if (status[0].status == 2) {
		printf("상태 : 내려가는중");
	}
	Gotxy(25, 14);
}

void userUI2(int n)
{
	int wt = 30;
	/*Gotxy(wt, 0);
	printf("                        ");*/
	Gotxy(wt, 0);
	printf("-----ELEVATOR%d-----",  2);
	/*Gotxy(wt, 1);
	printf("                        ");*/
	Gotxy(wt, 1);
	printf("Current floor: %d", status[1].floor);
	//Gotxy(wt, 2);
	//printf("                        ");
	Gotxy(wt, 2);
	if (status[1].status == 0) {
		printf("상태 : 기다림    ");
	}
	else if (status[1].status == 1) {
		printf("상태 : 올라가는중");
	}
	else if (status[1].status == 2) {
		printf("상태 : 내려가는중");
	}
	Gotxy(25, 14);
}

void adminUI(int n)
{
	int wt = n * 20;
	Gotxy(wt, 0);
	printf("                  ");
	Gotxy(wt, 0);
	printf("-----ELEVATOR%d-----", n + 1);
	Gotxy(wt, 1);
	printf("                  ");
	Gotxy(wt, 1);
	printf("Current floor: %d", status[n].floor);
	Gotxy(wt, 2);
	printf("                  ");
	Gotxy(wt, 2);
	if (Doors == true) {
		printf("Doors open  ");
	}
	else
		printf("Doors closed");
	Gotxy(wt, 3);
	printf("                  ");
	Gotxy(wt, 3);
	if (status[n].status == 0) {
		printf("상태 : 기다림    ");
	}
	else if (status[n].status == 1) {
		printf("상태 : 올라가는중");
	}
	else if (status[n].status == 2) {
		printf("상태 : 내려가는중");
	}
	Gotxy(wt, 4);
	printf("                  ");
	Gotxy(wt, 4);
	printf("최대최소 : %d %d", status[n].Max, status[n].Min);
	Gotxy(wt, 5);
	printf("                  ");
	Gotxy(wt, 5);
	printf("인원: %d", status[n].totalpeople);
	Gotxy(wt, 6);
	printf("                  ");
	Gotxy(wt, 6);
	printf("무게: %d", status[n].totalweight);
	Gotxy(wt, 7);
	printf("                  ");
	Gotxy(wt, 7);
	printf("-------------------");
	Gotxy(0, 16);
	printf("                                             ");
	Gotxy(0, 18);
	printf("                                                                          \n");
	printf("                                                                          \n");
	printf("                                                                          \n");
	printf("                                                                          \n");
	printf("                                                                          \n");
	printf("                                                                          \n");
	printf("                                                                          \n");
	printf("                                                                          \n");
	printf("                                                                          \n");
	printf("                                                                          \n");
	Gotxy(0, 18);
	for (int i = 0; i < 100; i++) {
		if (elevator[i].currentFloor != 0) {
			printf("엘리베이터 : %d ", n + 1);

			printf("버튼 :%d ", elevator[i].button);
			printf("랭크: %d ", elevator[i].rank);
			printf("현재층 :%d ", elevator[i].currentFloor);
			printf("목표층 :%d\n", elevator[i].targetFloor);
		}
	}
	Gotxy(25, 14);
}

void MinMax(int str, int choice)
{
	for (int i = 0; i < 100; i++) {
		if(elevator[i].elevator_num == choice){
			if (elevator[i].currentFloor != 0) {
				if (elevator[i].targetFloor < status[choice].Min && str == 0) {
					status[choice].Min = elevator[i].targetFloor;
				}
				if (elevator[i].targetFloor > status[choice].Max && str == 0) {
					status[choice].Max = elevator[i].targetFloor;
				}
				if (elevator[i].currentFloor < status[choice].Min) {
					status[choice].Min = elevator[i].currentFloor;
				}
				if (elevator[i].currentFloor > status[choice].Max) {
					status[choice].Max = elevator[i].currentFloor;
				}
			}
		}
	}
}

void Closed_Button(int n)
{
	int elSeconds = 0;
	while (elSeconds < 3) {
		Gotxy(0, 15);
		printf("3초 안에 닫힘 버튼(space bar)을 누르세요...(%d초 경과)", elSeconds+1);
		Sleep(1000);
		Gotxy(0, 15);
		printf("                                                                      ");
		elSeconds++;

		// 추가: 닫힘 버튼을 입력받으면 문을 닫고 1초 후 출발
		if (_kbhit()) {
			int closeButton = _getch();
			if (closeButton == 32) { // 예시로 3을 닫힘 버튼으로 설정
				Doors = false;
				DrawElevator(n);
				Sleep(1000); // 추가: 1초 대기
				break;
			}
		}
	}
}

int choice_elevator(int currentf)
{
	int diff1 = 0;
	int diff2 = 0;
	diff1 = abs(status[0].floor - currentf);
	diff2 = abs(status[1].floor - currentf);
	if (diff1 <= diff2) {
		return 0;
	}
	else {
		return 1;
	}
}

void changepassword()
{
	printf("변경할 비밀번호 입력 > ");
	scanf("%s", &pass);

}