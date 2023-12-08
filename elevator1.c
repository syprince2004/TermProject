#define _CRT_SECURE_NO_WARNINGS
#define ELEVATOR_COUNT 2 

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define SWAP(x,y,t) ( (t)=(x) , (x) = (y) , (y) =(t) )

unsigned _stdcall thread_el1(void* arg);
unsigned _stdcall UI(void* arg);
void DrawElevator(int n);
void Gotxy(int x, int y);
void MinMax(int str, int choice);
void Closed_Button(int n);
int choice_elevator(int currentf);
int choice_elevator(int currentf);
void Check();
void textcolor(int colorNum);
void RemovePeople(int n);
void ElevatorInspection(int elevatorNumber);



bool Userio = false;
bool start = true;
bool display = true;
int inspection = 0;
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
	bool call;
	bool Doors;
	bool insinspection;
	int totalweight;
	int totalpeople;
	int Min;
	int Max;
	int elevator;
	int floor;
	int status;
};

struct Elevator1_status status[6];


int main()
{
	int button = 0;
	int targetf = 0;
	int currentf = 0;
	int rank = 0;
	int choice = 0;
	int insinspection = 0;
	for (int i = 0; i < 6; i++)
	{
		status[i].floor = 1;
		status[i].Min = 100;
		status[i].Max = 0;
		status[i].insinspection = false;
		_beginthreadex(NULL, 0, thread_el1, i, 0, NULL);
	}
	_beginthreadex(NULL, 0, UI, 1, 0, NULL);

	while (1)
	{
		srand(time(NULL));
		currentf = rand() % 50 + 1;
		Gotxy(0, 13);
		printf("사용자가 있는 층 : %d층\n", currentf);
		printf("위(1), 아래(2), 관리자(3) >> ");
		scanf("%d", &button);
		if (button == 3) {
			while (1) {
				system("cls");
				display = false;
				Gotxy(0, 0);
				printf("                                                                                  ");
				Gotxy(0, 0);
				printf("비밀번호 확인 >>  ");
				scanf("%s", &pass);
				if (strcmp(password, pass) == 0) {
					usertype = 'a';
					Gotxy(0, 0);
					printf("                                                         ");
					Gotxy(0, 0);
					printf("비밀번호 확인 완료");
					system("cls");
					display = true;
					break;
				}
			}
			while (1)
			{
				Gotxy(0, 14);
				printf("원하는 메뉴를 입력 비밀번호 변경(1), 점검할 엘리베이터(2), 관리자 메뉴 나가기(3)");
				scanf("%d", &menu);
				if (menu == 1)
				{
					display = false;
					system("cls");
					Check();
					display = true;
				}
				else if (menu == 2)
				{
					printf("점검을 원하는 엘리베이터 번호 입력");
					scanf("%d", &inspection);
					if (inspection >= 1 && inspection <= 6) { // 사용자가 입력한 엘리베이터를 점검
						if (status[inspection - 1].insinspection = false) {
							status[inspection - 1].insinspection = true;
						}
						else {
							status[inspection - 1].insinspection = false; // 점검 중 플래그 설정
						}
					}
					else {
						printf("잘못된 엘리베이터 번호입니다.\n");
					}
				}
				else if (menu == 3)
				{
					system("cls");
					usertype = 'u';
					break;
				}
			}
		}
		else if (button == 1 || button == 2) {
			choice = choice_elevator(currentf);
			usertype = 'u';
			if (button == 1)
			{
				while (1)
				{
					Gotxy(0, 14);
					printf("가고자하는 층을 입력:          ");
					Gotxy(22, 14);
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
					printf("가고자하는 층을 입력:            ");
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
		system("cls");
	}
}


unsigned _stdcall thread_el1(void* arg)
{
	int n = (int)arg;
	status[n].status = 0; //멈춰있는 상태
	status[n].floor = 1; //엘리베이터 초기층
	status[n].call = false;
	status[n].Doors = false;
	while (1)
	{
		if (status[n].insinspection == false) {
			if (status[n].status > 0) {
				if (status[n].status == 1) {
					for (int i = 0; i < 100; i++) {
						if (elevator[i].elevator_num == n) {
							if (elevator[i].button == 1) {
								if (status[n].floor == elevator[i].currentFloor) {
									status[n].totalweight += elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
									status[n].totalpeople += elevator[i].people;
									status[n].Doors = true;
									if (usertype == 'u')
										Closed_Button(n);
									else {
										Sleep(3000);
									}
									Sleep(3000);
									status[n].Doors = false;
								}
								else if (status[n].floor == elevator[i].targetFloor) {
									status[n].call = false;
									if (elevator[i].rank == 2) {
										Sleep(500);
									}
									else {
										status[n].totalweight -= elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
										status[n].totalpeople -= elevator[i].people;
										status[n].Doors = true;
										Sleep(3000);
										status[n].Doors = false;
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
					if (status[n].status != 0) {
						status[n].call = true;
						status[n].floor++;
					}
					else {
						for (int i = 0; i < 100; i++) {
							if (elevator[i].elevator_num == n) {
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
						if (elevator[i].elevator_num == n) {
							if (elevator[i].button == 2) {
								if (status[n].floor == elevator[i].currentFloor) {
									status[n].totalweight += elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
									status[n].totalpeople += elevator[i].people;
									status[n].Doors = true;
									if (usertype == 'u')
										Closed_Button(n);
									else {
										Sleep(3000);
									}
									Sleep(3000);
									status[n].Doors = false;
								}
								else if (status[n].floor == elevator[i].targetFloor) {
									status[n].call = false;
									if (elevator[i].rank == 2) {
										Sleep(500);
									}
									else {
										status[n].totalweight -= elevator[i].weight.woman * 55 + elevator[i].weight.man * 75;
										status[n].totalpeople -= elevator[i].people;
										status[n].Doors = true;
										Sleep(3000);
										status[n].Doors = false;
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
					if (status[n].status != 0) {
						status[n].call = true;
						status[n].floor--;
					}
					else {
						for (int i = 0; i < 100; i++) {
							if (elevator[i].elevator_num == n) {
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
}

unsigned _stdcall UI(void* arg)
{
	while (1) {
		for (int i = 0; i < 6; i++) {
			if (status[i].insinspection = false) {
				DrawElevator(i);
				Sleep(50);
			}
			else {
				ElevatorInspection(i); // 엘리베이터 정보 초기화
				DrawElevator(i);
				Sleep(50);
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
	if (display) {
		int wt = n * 20;
		if (usertype == 'u') {
			Gotxy(wt, 0);
			printf("-----ELEVATOR%d-----\n", n + 1);
			if (status[n].insinspection) {
				Gotxy(wt, 1);
				printf("             ");
				Gotxy(wt, 2);
				printf("점검중");
				Gotxy(wt, 3);
				printf("             ");
			}
			else {
				Gotxy(wt, 1);
				if (status[n].call) {
					printf("호출됨       ");
				}
				else {
					printf("호출되지 않음");
				}
				Gotxy(wt, 2);
				printf("Current floor: %d", status[n].floor);
				Gotxy(wt, 3);
				if (status[n].status == 0) {
					printf("상태 : 기다림    \n");
				}
				else if (status[n].status == 1) {
					printf("상태 : 올라가는중\n");
				}
				else if (status[n].status == 2) {
					printf("상태 : 내려가는중\n");
				}
			}
			Gotxy(wt, 4);
			printf("-------------------\n");
			Gotxy(0, 15);
		}
		else if (usertype == 'a') {
			Gotxy(wt, 0);
			printf("-----ELEVATOR%d-----\n", n + 1);
			Gotxy(wt, 1);
			if (status[n].insinspection) {
				printf("점검중      ");
			}
			else
			{
				if (status[n].call) {
					printf("호출됨       ");
				}
				else {
					printf("호출되지 않음");
				}
			}
			Gotxy(wt, 2);
			printf("Current floor: %d", status[n].floor);
			Gotxy(wt, 3);
			if (status[n].Doors == true) {
				printf("Doors open  ");
			}
			else
				printf("Doors closed");
			Gotxy(wt, 4);
			if (status[n].status == 0) {
				printf("상태 : 기다림    \n");
			}
			else if (status[n].status == 1) {
				printf("상태 : 올라가는중\n");
			}
			else if (status[n].status == 2) {
				printf("상태 : 내려가는중\n");
			}
			Gotxy(wt, 5);
			printf("                  ");
			Gotxy(wt, 5);
			printf("최대최소 : %d %d\n", status[n].Max, status[n].Min);
			Gotxy(wt, 6);
			printf("                  ");
			Gotxy(wt, 6);
			printf("인원: %d\n", status[n].totalpeople);
			Gotxy(wt, 7);
			printf("                  ");
			Gotxy(wt, 7);
			printf("무게: %d\n", status[n].totalweight);
			Gotxy(wt, 8);
			printf("-------------------\n");
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
			Gotxy(0, 13);
		}
	}
}

void MinMax(int str, int choice)
{
	for (int i = 0; i < 100; i++) {
		if (elevator[i].elevator_num == choice) {
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
		Gotxy(0, 10);
		printf("3초 안에 닫힘 버튼(space bar)을 누르세요...(%d초 경과)", elSeconds + 1);
		Sleep(1000);
		Gotxy(0, 10);
		printf("                                                                      ");
		elSeconds++;

		// 추가: 닫힘 버튼을 입력받으면 문을 닫고 1초 후 출발
		if (_kbhit()) {
			int closeButton = _getch();
			if (closeButton == 32) { // 예시로 space bar를 닫힘 버튼으로 설정
				status[n].Doors = false;
				DrawElevator(n);
				Sleep(1000); // 추가: 1초 대기
				status[n].status = 1;
				break;
			}
		}
	}
}

int choice_elevator(int currentf)
{
	int diff[6];
	int Min = INT_MAX; // 최소값을 찾기 위해 초기값을 최대값으로 설정
	int el = 0;

	for (int i = 0; i < 6; i++)
	{
		if (status[i].status == 0)
			diff[i] = abs(status[i].floor - currentf); // 기다리는 엘리베이터의 거리 계산
		else if (status[i].status == 1 && status[i].floor <= currentf)
			diff[i] = abs(status[i].Max - currentf); // 올라가는 엘리베이터의 거리 계산
		else if (status[i].status == 2 && status[i].floor >= currentf)
			diff[i] = abs(status[i].Min - currentf); // 내려가는 엘리베이터의 거리 계산
		else
			diff[i] = INT_MAX; // 다른 상태의 엘리베이터는 선택되지 않도록 최대값 설정

		if (diff[i] < Min)
		{
			Min = diff[i];
			el = i;
		}
	}

	return el;
	
}


void Check()
{
	int space = 0, num = 0, length = 0, upper = 0, lower = 0, special = 0;
	Gotxy(0, 0);
	printf("변경할 비밀번호 입력 >                           ");
	Gotxy(22, 0);
	scanf("%s", &pass);
	length = strlen(pass);
	if (strlen(pass) >= 8) {
		for (int i = 0; i < length; i++) {
			if (isupper(pass[i]))
				upper++;
			else if (islower(pass[i]))
				lower++;
			else if (isdigit(pass[i]))
				num++;
			else if (isspace(pass[i]) || isblank(pass[i]))
				space++;
			else
				special++;
		}
		if (num > 0 || special > 0) {
			strcpy(password, pass);
		}
		else {
			Gotxy(0, 1);
			printf("암호 생성 조건에 일치하지 않습니다.\n");
			return Check();
		}

	}
	else
		return Check();

}

void textcolor(int colorNum)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void ElevatorInspection(int elevatorNumber) {
	status[elevatorNumber].call = false;
	status[elevatorNumber].Doors = false;
	status[elevatorNumber].totalweight = 0;
	status[elevatorNumber].totalpeople = 0;
	status[elevatorNumber].Min = 100;
	status[elevatorNumber].Max = 0;
	status[elevatorNumber].floor = 1;
	status[elevatorNumber].status = 0;
}

//void RemovePeople(int n)
//{
//	for (int i = 0; i < 100; i++) {
//		if (elevator[i].elevator_num == n) {
//			// 몸무게가 최대 허용치를 초과하는 경우 랜덤으로 사람을 내림
//			while (elevator[i].weight.man * 75 + elevator[i].weight.woman * 55 > MAX_WEIGHT) {
//				int randomPerson = rand() % elevator[i].people; // 랜덤으로 내릴 사람 선택
//				if (elevator[i].weight.man > 0 && elevator[i].weight.woman > 0) {
//					if (rand() % 2 == 0) {
//						elevator[i].weight.man--;
//					}
//					else {
//						elevator[i].weight.woman--;
//					}
//				}
//				else if (elevator[i].weight.man > 0) {
//					elevator[i].weight.man--;
//				}
//				else if (elevator[i].weight.woman > 0) {
//					elevator[i].weight.woman--;
//				}
//				elevator[i].people--;
//			}
//		}
//	}
//}S