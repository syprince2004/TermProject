/*
���������� ���� ���α׷�
���� ȯ�� : VS2022, C���, Windows
���� ���� : ���������� ���� ���α׷��� ������ ���� ���α׷��� �ɷ� ���
���� ��� :
���� �����丮 :
	2023.10.02 - main �Լ����� �Է¿� ���� if�� ����, �������� ��ǥ�� �Է�
	2023.10.07 - main �Լ����� ������ ȣ��, ������ ����
	2023.10.11 - �������� �Լ��� �̿��� ���������� currentFloor, targetFloor �迭�� ������������
	2023.10.13 - ���������� currentFloor, targetFloor �迭�� ���ο� �迭�� ����
	2023.10.20 - �ִ밪�� �ּڰ��� ���ϴ� �Լ�
	2023.10.23 - �������� �Լ�
	2023.10.26 - â�� ����� �ڵ�� ���ϴ� xy��ǥ�� ����� �� �ִ� �Լ�
	2023.10.30 - ����� ���� �Է�(3)�� �������� �������� �������� �����̴� �ڵ�
���¼ҽ� :
���̺귯�� :
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>
//#include <cstdio>
#include <conio.h>


#define SWAP(x,y,t) ( (t)=(x) , (x) = (y) , (y) =(t) ) // �ΰ��� �ڸ��� �ٲ���

//CRITICAL_SECTION mutex; // ���ؽ� �߰�

int newcurrent[100] = { 0 };
int newtarget[100] = { 0 };
int elevator1 = 0;
int el1_currentMax = 0;
int el1_currentMin = 0;
int el1_targetMax = 0;
int el1_targetMin = 0;
int i = 0;


unsigned _stdcall thread_el1(void* arg);

void BubbleSort(int list[], int n);

void MinMax(int list[], int* min, int* max, int size);

int Cl_Button(int Close);

void Gotxy(int x, int y);

//void MoveElevator();

struct Elevator
{
	int currentFloor[100];
	int targetFloor[100];
	int button[100];
	int people[100];
};

struct Elevator elevator[100];

/*
�����Լ�
�Լ� ���� : ��� ������ �̷������ ����
return �� :
���� �����丮 :
	2023.10.02 - �Է¿� ���� if�� ����, ����� ������(currentFloor) �������� �Է¹ޱ�, �������ϴ� ��(targetFloor) �Է¹ޱ�
	2023.10.07 - ������ ȣ��
	2023.10.26 - â�� ����� �ڵ� �ۼ�
	2023.10.30 - ���� �Է�(3)�� �������� �������� �۵��Ǵ� �ڵ�
*/
int main()
{

	_beginthreadex(NULL, 0, thread_el1, 0, 0, NULL); // ������ ȣ��


	while (1)
	{

		int targetf;
		int currentf;
		int a;
		srand(time(NULL));
		//system("cls");
		printf("��(1), �Ʒ�(2), ���ǻ����(3)");
		scanf("%d", &a); //���ڷ� �Է�
		//printf("%d", button);
		if (a == 1 || a == 2) { // 1 or 2�� �Է�������
			elevator[i].button[i] = a;
			currentf = rand() % 100 + 1; // �������� 1~100���� �������� ����
			elevator[i].currentFloor[i] = currentf; // ���������� �����currentFloor�� ����
			printf("�������ϴ� ���� �Է�");
			scanf("%d", &targetf); // ��ǥ���� �Է¹���
			elevator[i].targetFloor[i] = targetf; // ���������� ����� targetFloor�� ����
			/*printf("%d %d\n", currentFloor[i], targetFloor[i]);*/
			i++;
		}
		else if (a == 3) {
			srand(time(NULL));
			elevator[i].button[i] = rand() % 2 + 1; //��ư�� ���� ������ �Ʒ��� ������ ����
			currentf = rand() % 100 + 1; //���� ���� ����
			elevator[i].currentFloor[i] = currentf;
			if (elevator[i].button[i] == 1) { //���� �� ���
				targetf = rand() % (99 - currentf) + currentf; // �������� ��ǥ������ ������ �ȵǹǷ� ����
			}
			else if (elevator[i].button[i] == 2) {
				targetf = rand() % (currentf - 1) + 1; //�������� ��ǥ������ ������ �ȵǹǷ� ����
			}
			elevator[i].targetFloor[i] = targetf;
			i++;
		}
		else
			printf("�ٽ� �Է��ϼ���\n");
		continue;

	}
}

//void MoveElevator()
//{
//	while (1)
//	{
//		printf("%d\n", i);
//		printf("%d\n", elevator[i].currentFloor[i]);
//		/*int el1_currentMin, el1_currentMax, el1_targetMin, el1_targetMax;*/
//		MinMax(elevator[i].currentFloor[i], el1_currentMin, el1_currentMax, i); // �ִ밪, �ּڰ�
//		BubbleSort(elevator[i].currentFloor, i);//�������� �Լ� ȣ��(currentFloor �迭�� ����)
//		for (int j = 0; j < i; j++) {
//			newcurrent[j] = elevator[i].currentFloor[j]; // newcurrent�迭�� ����
//		}
//		printf("%d %d", el1_currentMin, el1_currentMax);
//		MinMax(elevator[i].targetFloor, el1_targetMin, el1_targetMax, i);
//		BubbleSort(elevator[i].targetFloor, i);//�������� �Լ� ȣ��
//		for (int j = 0; j < i; j++) {
//			newtarget[j] = elevator[i].targetFloor[j]; // newtarget�迭�� ����
//		}
//		printf("%d %d", el1_targetMin, el1_targetMax);
//	}
//}

/*
���������� �����̴� ������
�Լ� ���� : ���ο��� �Է¹ް� ���������� �迭�� ������ ���������� ��ġ�� ��
���� �����丮 :
	2023.10.07 - ������ ����
	2023.10.11 - ���������� currentFloor, targetFloor �迭�� ��������
	2023.10.13 - ���������� currentFloor, targetFloor �迭�� ���ο� �迭�� ����
	2023.10.20 - �ִ��ּҰ��� ã�� �Լ� ����
	2023.10.23 - ������ư �Լ� ȣ��
*/
unsigned _stdcall thread_el1(void* arg)
{
	while (1)
	{
		int i = 0;
		/*printf("%d\n", i);*/
		/*printf("%d %d\n", elevator[i].currentFloor[i], elevator);*/
		MinMax(elevator[i].currentFloor, &el1_currentMin, &el1_currentMax, i); // �ִ밪, �ּڰ�
		BubbleSort(elevator[i].currentFloor, i);//�������� �Լ� ȣ��(currentFloor �迭�� ����)
		for (int j = 0; j < i; j++) {
			newcurrent[j] = elevator[i].currentFloor[j]; // newcurrent�迭�� ����
		}
		/*printf("%d %d", el1_currentMin, el1_currentMax);*/
		MinMax(elevator[i].targetFloor, &el1_targetMin, &el1_targetMax, i);
		BubbleSort(elevator[i].targetFloor, i);//�������� �Լ� ȣ��
		for (int j = 0; j < i; j++) {
			newtarget[j] = elevator[i].targetFloor[j]; // newtarget�迭�� ����
		}
		/*printf("%d %d", el1_targetMin, el1_targetMax);*/

		if (elevator[i].currentFloor[i] != 0 && elevator[i].targetFloor[i] != 0) {
			int current = elevator[i].currentFloor[i];
			int target = elevator[i].targetFloor[i];
			/*elevator[i].currentFloor[i] = El_Floor(current, target)*/;
			if (elevator[i].currentFloor[i] == target) {
				printf("���������Ͱ� %d�� �����߽��ϴ�.\n", target);

				// ���������� ����
				Sleep(3000); // 3�� ���� ����

				// ���������� ��� �� �ʱ�ȭ
				//elevator[i].currentFloor[i] = 0;
				//elevator[i].targetFloor[i] = 0;
			}
			Sleep(500);
			printf("%d\n", elevator1);
			elevator1++;
		}
		//if (elevator1 <= elevator[i].currentFloor[i]) {//�迭�� 0�� �ƴ϶��(�迭�� ���ڰ� ���ִٴ� ��)
		//	Sleep(500);
		//	elevator1++;
		//	printf("%d", elevator1);
		//	for (int k = 0; k < i; k++)
		//	{
		//		if (elevator1 == newcurrent[k])
		//		{
		//			int close;
		//			printf("������ư(1)>");
		//			scanf("%d", &close); //������ư�� �Է�
		//			Cl_Button(close); // �Լ� �̵�
		//		}
		//	}
		//	for (int k = 0; k < i; k++)
		//	{
		//		if (elevator1 == newtarget[k])
		//		{
		//			Sleep(3000); // ��ǥ���� �����ϸ� ����� ������ 3���� ��
		//			printf("���� ��: %d\n", elevator1);
		//		}
		//	}
		//}



		/*�ä����°��� �ʴ밨
		�������� ���� �ּҰ�
		���� �������� ��
		 �h�� ���������� ���� :�ö󰡴��� ��������
		����
		���������� ���ļ����� ��������*/

	}

}

/*
��������
�Լ� ���� : ������������ ��������
���� �����丮 :
	2023.10.11 - ���������� ���� �������� ����
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
�ִ��ּҰ�
�Լ� ���� : �ִ밪�� �ּҰ��� ����
���� �����丮 :
	2023.10.20 - min, max ���� ����
*/
void MinMax(int list[], int* min, int* max, int size) { //
	//while(1){
	//	if (i <= 0) {
	//		// �迭�� ������� ���� ���� ó��
	//		return MinMax;
	//	}
	//	else
	//		break;
	//}
	if (size <= 0) {
		*min = 0;
		*max = 0;
		return;
	}
	*min = list[0]; // �ʱ� ������ min���� list[0]
	*max = list[0]; // �ʱ� ������ max���� list[0]
	for (int j = 0; j < size; j++) {
		if (list[j] < *min) { // list[j]�� min ���� �۴ٸ� 
			*min = list[j]; // min�� list[j] ���� ����
		}
		if (list[j] > *max) { // list[j]�� max ���� ũ�ٸ�
			*max = list[j]; // max�� list[j] ���� ����
		}
	}
}

/*
������ư�� ��뿩��
�Լ� ���� : ������ư�� ������ 1������ ������ �ȴ����� 3���Ŀ� ����
return �� : �����Ѱ����� ���� ���� ����� ��ġ
���� �����丮 :
	2023.10.23 - Sleep �Լ��� �̿��� ������ư�� ������ 1�ʵ� ���̴����ϴ� ��� �ƴ϶�� 3�ʵ� ���
*/
int Cl_Button(int Close)
{
	if (Close == 1) {
		Sleep(1000);
	}
	else
		Sleep(3000);
	printf("���� �����ϴ�\n");
	return 0;
}

/*
cmdȯ�濡�� ��ġ �������ִ� �Լ�
�Լ� ���� : �Լ��� �����ϸ� x,y�� ��ǥ���� ǥ��
return �� :
���� �����丮 :
	2023.10.26 - ��ǥ������ ��ǥ��ġ�� ���
*/
void Gotxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

/*
�ʱ������� ������� ������ ���� �ڵ�
�Լ� ���� : �ʱⰪ�� ���������� �ٲ� ���� ������ �ٲ۴�
return �� : �ٲ� �ʱⰪ
���� �����丮 :
	(2023-11-09) - �ʱ������� ���������� ���� ���������� ��ǥ������ ���� �Լ� ����(���������� ������ �ӵ��� Sleep�Լ��� ����� 0.5��)
*/
int El_Floor(int EarlyFloor, int LaterFloor) {
	double timePerFloor = 0.5; // �� �� �̵��� �ɸ��� �ð� (��)

	if (EarlyFloor == LaterFloor) {
		printf("���������ʹ� �̹� ���� �����߽��ϴ�.\n"); //�������� ��ǥ���� ���Ͽ� ���ٸ� ���� ���
	}
	else if (EarlyFloor < LaterFloor) {
		printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", EarlyFloor - 10, LaterFloor - 10); //�������� ��ǥ������ �۴ٸ� ���������� ��ǥ������ ����
		while (EarlyFloor < LaterFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� 0.5�� ���
			EarlyFloor++; //
			printf("���� %d��\n", EarlyFloor - 10); //���ڸ� �ϳ��� �������ָ鼭 �� ������
		}
		printf("���������Ͱ� %d�� �����߽��ϴ�.\n", LaterFloor - 10);
		EarlyFloor = LaterFloor;
	}
	else {
		printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", EarlyFloor - 10, LaterFloor - 10); //�������� ��ǥ������ ũ�ٸ� ���������� ��ǥ������ ����
		while (EarlyFloor > LaterFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� ���
			EarlyFloor--;
			printf("���� %d��\n", EarlyFloor - 10); //���ڸ� �ϳ��� �������ָ鼭 �� ������
		}
		printf("���������Ͱ� %d�� �����߽��ϴ�.\n", LaterFloor - 10);
		EarlyFloor = LaterFloor;
	}
	return EarlyFloor;
}