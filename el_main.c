/*
���������� ���� ���α׷�
���� ȯ�� : VS2022, C���, Windows
���� ���� : ���������� ���� ���α׷��� ������ ���� ���α׷��� �ɷ� ���
���� ��� : ����ڰ� ������ �������� ���� ������ �ִ� ���������Ͱ� ��
���� �����丮 :
���¼ҽ� :
���̺귯�� :
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <stdlib.h> //���� �Լ��� ���� ���� �������

#include <time.h> //time() �Լ��� ���� ���� �������

int Rand_Now(int currentFloor);

void UD_Button(int UDbutton);

int El_Floor(int EarlyFloor, int LaterFloor);

int main()
{
	int targetFloor = 0;

	int initialFloor = 11; //ó�� �����Ҷ� ���� ������ 1��

	while(1)
	{
		int button = 0;
		printf("������� ������ �����Ͻÿ� ��(1), �Ʒ�(2) > ");
		scanf_s("%d", &button); //������� ���� ���� �Է�
		UD_Button(button); //UD_Button �Լ� ȣ��

		int currentFloor = Rand_Now(button);

		currentFloor = El_Floor(initialFloor, currentFloor);

		printf("�������ϴ� ���� �Է��Ͻÿ� > ");
		scanf_s("%d", &targetFloor);
		targetFloor += 10;

		initialFloor = El_Floor(currentFloor, targetFloor);
	}
}