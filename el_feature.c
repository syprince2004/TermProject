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

#include <time.h> //time �Լ��� ���� ���� �������

#include <windows.h> //usleep �Լ��� ���� ���� �������

int El_Floor(int EarlyFloor, int LaterFloor);

void UD_Button(int UDbutton);

int El_Floor(int EarlyFloor, int LaterFloor);

/*
�������� �޴� ���� ����� ��ġ
�Լ� ���� : �������� ���� �Է����� ������� ���� ��ġ�� �˷���
return �� : �����Ѱ����� ���� ���� ����� ��ġ
���� �����丮 : 
���¼ҽ� :
���̺귯�� :
*/

int Rand_Now(int currentFloor)
{
	srand(time(NULL)); //�Ź� �ٸ� �� �õ� ����

	currentFloor = (rand() % 110) + 1; //1~110�� �� �ϳ��� �������� ����

	return(currentFloor);
}

/*
�������� ���ϴ� ����ڰ� �������ϴ� ��ġ(��ǥ��)
�Լ� ���� : ��ǥ���� �˷��ܰ� ���ÿ� �������� ��ǥ���� ���ϸ鼭 0.5�ʸ��� ���� ������ �Ѿ�� ȭ�鿡 ������
return �� : �����Ѱ����� ���� ������� ��ġ
���� �����丮 :
���¼ҽ� :
���̺귯�� :
*/

//int Rand_future(int UD)
//{
//	/* 
//	//��ǥ���� �������� ���ϴ� �ڵ�
//	srand(time(NULL)); //�Ź� �ٸ� �� �õ� ����
//	int targetFloor = 0;
//	if (UD == 1) {
//		targetFloor = (rand() % (110 - currentFloor)) + currentFloor+1; //���� ��ġ���� ���� ��ġ�� ������ ��
//	}
//	else
//		targetFloor = (rand() % currentFloor-1) + 1; //���� ��ġ���� ���� ��ġ�� ������ ��
//	*/
//
//	int currentFloor = Rand_Now(UD);
//
//	int targetFloor = 0;
//
//	int initialFloor = 1;
//
//	while(1)
//	{
//		currentFloor = El_Floor(initialFloor, currentFloor);
//
//		printf("�������ϴ� ���� �Է��Ͻÿ� > ");
//		scanf_s("%d", &targetFloor);
//
//		initialFloor = El_Floor(currentFloor, targetFloor);
//	}
//
//	//if (initialFloor == targetFloor) {
//	//	printf("���������ʹ� �̹� ��ǥ ���� �����߽��ϴ�.\n"); //�ʱ����� �������� ���Ͽ� ���ٸ� ���� ���
//	//}
//	//else if (initialFloor < currentFloor) {
//	//	printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", initialFloor, currentFloor); //�ʱ����� ���������� �۴ٸ� �ʱ������� ���������� ����
//	//	while (initialFloor < currentFloor) {
//	//		Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� 0.5�� ���
//	//		initialFloor++; //
//	//		printf("���� %d��\n", initialFloor); //���ڸ� �ϳ��� �������ָ鼭 �� ������
//	//	}
//	//	printf("���������Ͱ� ����� �� %d�� �����߽��ϴ�.\n", currentFloor);
//	//	currentFloor = initialFloor; //�ٽ� �Է� �޴� ��� �ʱ� ������������ ��ġ�� �޶���
//	//}
//	//else {
//	//	printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", initialFloor, currentFloor); //�ʱ����� ���������� ũ�ٸ� �ʱ������� ���������� ����
//	//	while (initialFloor > currentFloor) {
//	//		Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� ���
//	//		initialFloor--;
//	//		printf("���� %d��\n", initialFloor); //���ڸ� �ϳ��� �������ָ鼭 �� ������
//	//	}
//	//	printf("���������Ͱ� ��ǥ �� %d�� �����߽��ϴ�.\n", currentFloor);
//	//	currentFloor = initialFloor; //�ٽ� �Է� �޴� ��� �ʱ� ������������ ��ġ�� �޶���
//	//}
//
//	//
//
//	//if (currentFloor == targetFloor) {
//	//	printf("���������ʹ� �̹� ��ǥ ���� �����߽��ϴ�.\n"); //�������� ��ǥ���� ���Ͽ� ���ٸ� ���� ���
//	//}
//	//else if (currentFloor < targetFloor) {
//	//	printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", currentFloor, targetFloor); //�������� ��ǥ������ �۴ٸ� ���������� ��ǥ������ ����
//	//	while (currentFloor < targetFloor) {
//	//		Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� 0.5�� ���
//	//		currentFloor++; //
//	//		printf("���� %d��\n", currentFloor); //���ڸ� �ϳ��� �������ָ鼭 �� ������
//	//	}
//	//	printf("���������Ͱ� ��ǥ �� %d�� �����߽��ϴ�.\n", targetFloor);
//	//}
//	//else {
//	//	printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", currentFloor, targetFloor); //�������� ��ǥ������ ũ�ٸ� ���������� ��ǥ������ ����
//	//	while (currentFloor > targetFloor) {
//	//		Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� ���
//	//		currentFloor--; 
//	//		printf("���� %d��\n", currentFloor); //���ڸ� �ϳ��� �������ָ鼭 �� ������
//	//	}
//	//	printf("���������Ͱ� ��ǥ �� %d�� �����߽��ϴ�.\n", targetFloor);
//	//}
//
//
//	//return(targetFloor);
//}

/*
������� ������ �޴� �Է�(��, �Ʒ�)
�Լ� ���� : ������� ������ �Է¹ް� return������ ����
return �� : ����ڰ� ������ �������� ���� ������ �ִ� ���������Ͱ� ��
���� �����丮 :
���¼ҽ� :
���̺귯�� :
*/

void UD_Button(int UDbutton)
{
	while (getchar() != '\n'); //���� ����ó��
	if (UDbutton == 1 || UDbutton == 2) { 
		return 0; //������(������� ����)�� 1 or 2 ��� Rand_futuer �Լ� ȣ��
	}
	else {
		printf("error!\n"); //�ް����ϴ� ���ڰ� �ƴ϶�� ���� ���
		printf("�ٽ��Է��Ͻÿ�\n");
	}
}


/*
�ʱ������� ������� ������ ���� �ڵ�
�Լ� ���� : �ʱⰪ�� ���������� �ٲ� ���� ������ �ٲ۴�
return �� : �ٲ� �ʱⰪ
���� �����丮 :
���¼ҽ� :
���̺귯�� :
*/


int El_Floor(int EarlyFloor, int LaterFloor) {
	double timePerFloor = 0.5; // �� �� �̵��� �ɸ��� �ð� (��)

	if (EarlyFloor == LaterFloor) {
		printf("���������ʹ� �̹� ��ǥ ���� �����߽��ϴ�.\n"); //�������� ��ǥ���� ���Ͽ� ���ٸ� ���� ���
	}
	else if (EarlyFloor < LaterFloor) {
		printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", EarlyFloor-10, LaterFloor-10); //�������� ��ǥ������ �۴ٸ� ���������� ��ǥ������ ����
		while (EarlyFloor < LaterFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� 0.5�� ���
			EarlyFloor++; //
			printf("���� %d��\n", EarlyFloor-10); //���ڸ� �ϳ��� �������ָ鼭 �� ������
		}
		printf("���������Ͱ� ��ǥ �� %d�� �����߽��ϴ�.\n", LaterFloor-10);
		EarlyFloor = LaterFloor;
	}
	else {
		printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", EarlyFloor-10, LaterFloor-10); //�������� ��ǥ������ ũ�ٸ� ���������� ��ǥ������ ����
		while (EarlyFloor > LaterFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� ���
			EarlyFloor--;
			printf("���� %d��\n", EarlyFloor-10); //���ڸ� �ϳ��� �������ָ鼭 �� ������
		}
		printf("���������Ͱ� ��ǥ �� %d�� �����߽��ϴ�.\n", LaterFloor-10);
		EarlyFloor = LaterFloor;
	}
	return EarlyFloor;
}

