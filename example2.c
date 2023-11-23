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
	2023.10.23 - Sleep �Լ��� �̿��� ������ư�� ������ 1�ʵ� ���̴����ϴ� ��� �ƴ϶�� 3�ʵ� ���
���¼ҽ� :
���̺귯�� :
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>

#define SWAP(x,y,t) ( (t)=(x) , (x) = (y) , (y) =(t) ) // �ΰ��� �ڸ��� �ٲ���

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
�����Լ�
�Լ� ���� : ��� ������ �̷������ ����
return �� :
���� �����丮 :
	2023.10.02 - �Է¿� ���� if�� ����, ����� ������(currentFloor) �������� �Է¹ޱ�, �������ϴ� ��(targetFloor) �Է¹ޱ�
	2023.10.07 - ������ ȣ��
*/
int main()
{
	_beginthreadex(NULL, 0, thread_el1, 0, 0, NULL); // ������ ȣ��
	while (1)
	{
		int targetf;
		int currentf;
		srand(time(NULL));
		printf("��(1), �Ʒ�(2), ���ǻ����(3)");
		scanf("%d", &button[i]); //���ڷ� �Է�
		//printf("%d", button);
		if (button[i] == 1 || button[i] == 2) { // 1 or 2�� �Է�������
			currentf = rand() % 100 + 1; // �������� 1~100���� �������� ����
			currentFloor[i] = currentf; // ���������� �����currentFloor�� ����
			printf("�������ϴ� ���� �Է�");
			scanf("%d", &targetf); // ��ǥ���� �Է¹���
			targetFloor[i] = targetf; // ���������� ����� targetFloor�� ����
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
���������� �����̴� ������
�Լ� ���� : ���ο��� �Է¹ް� ���������� �迭�� ������ ���������� ��ġ�� ��
���� �����丮 :
	2023.10.07 - ������ ����
	2023.10.11 - ���������� currentFloor, targetFloor �迭�� ��������
	2023.10.13 - ���������� currentFloor, targetFloor �迭�� ���ο� �迭�� ����
	2023.10.20 - �ִ��ּҰ��� ã�� �Լ� ����
*/
unsigned _stdcall thread_el1(void* arg)
{
	while (1)
	{
		/*printf("%d\n", i);
		printf("%d\n", currentFloor[i]);*/
		BubbleSort(currentFloor, i); //�������� �Լ� ȣ��(currentFloor �迭�� ����)
		MinMax(currentFloor, &el1_currentMin, &el1_currentMax); // �ִ밪, �ּڰ�
		for (int j = 0; j < i; j++) {
			newcurrent[j] = currentFloor[j]; // newcurrent�迭�� ����
		}
		/*printf("%d %d", el1_currentMin, el1_currentMax);*/
		BubbleSort(targetFloor, i); //�������� �Լ� ȣ��
		MinMax(targetFloor, &el1_targetMin, &el1_targetMax);
		for (int j = 0; j < i; j++) {
			newtarget[j] = targetFloor[j]; // newtarget�迭�� ����
		}
		/*printf("%d %d", el1_targetMin, el1_targetMax);*/
		if (newcurrent[0] != 0) {//�迭�� 0�� �ƴ϶��(�迭�� ���ڰ� ���ִٴ� ��)
			while (elevator1 < newcurrent[0]) {
				Sleep(500);
				elevator1++;
				printf("%d", elevator1);
				for (int k = 0; k < i; k++)
				{
					if (elevator1 == newcurrent[k])
					{
						int close;
						printf("������ư(1)>");
						scanf("%d", &close);
						Cl_Button(close);
					}
				}
			}
		}



		//�ä����°��� �ʴ밨
		//�������� ���� �ּҰ�
		//���� �������� ��
		// �h�� ���������� ���� :�ö󰡴��� ��������
		//����
		//���������� ���ļ����� ��������

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
void MinMax(int list[], int* min, int* max) { //
	*min = list[0]; // �ʱ� ������ min���� list[0]
	*max = list[0]; // �ʱ� ������ max���� list[0]
	for (int j = 0; j < i; j++) {
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
������ư�� ��뿩��
�Լ� ���� : ������ư�� ������ 1������ ������ �ȴ����� 3���Ŀ� ����
return �� : �����Ѱ����� ���� ���� ����� ��ġ
���� �����丮 :
	2023.10.23 - Sleep �Լ��� �̿��� ������ư�� ������ 1�ʵ� ���̴����ϴ� ��� �ƴ϶�� 3�ʵ� ���
*/
void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}