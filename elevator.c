/*
���������� ���� ���α׷�
���� ȯ�� : VS2022, C���, Windows
���� ���� : ���������� ���� ���α׷��� ������ ���� ���α׷��� �ɷ� ���
���� ��� : ����ڰ� ������ �������� ���� ������ �ִ� ���������Ͱ� ��
���� �����丮 : 2023-11-09
���¼ҽ� :
���̺귯�� :
*/

#pragma warning(disable:4996)

#include <stdio.h>

#include <stdlib.h> //���� �Լ��� ���� ���� �������

#include <time.h> //time() �Լ��� ���� ���� �������

#include <windows.h> //sleep() �Լ��� ���� ���� �������

#include <process.h>

int Rand_Now(int currentFloor);

void UD_Button(int UDbutton);

int El_Floor(int EarlyFloor, int LaterFloor);

int Rand_Elevator(int elevator);

unsigned _stdcall elevator1(void* arg);


int main()
{
	int targetFloor = 0;

	int initialFloor = 11; //ó�� �����Ҷ� ���� ������ 1��

	_beginthreadex(NULL, 0, elevator1, 0, 0, NULL);

	while (1)
	{

		int button = 0;
		UD_Button(button); //UD_Button �Լ� ȣ��

		int currentFloor = Rand_Now(button);

		currentFloor = El_Floor(initialFloor, currentFloor); //El_Floor �Լ� ȣ���� return ���� currentFloor�� ����

		printf("�������ϴ� ���� �Է��Ͻÿ� > ");
		scanf("%d", &targetFloor);
		targetFloor += 10;

		initialFloor = El_Floor(currentFloor, targetFloor);
	}
}

/*
��� ���ư��� ����������
�Լ� ���� : ��� �������� �Է¹ް� ���ư��� ����������
return �� :
���� �����丮 : 2023-11-09
*/

unsigned _stdcall elevator1(void* arg)
{
	int targetFloor = 0;
	int initialFloor = 11;

	while(1){
		int button = 0;
		srand(time(NULL));//�Ź� �ٸ� �� �õ� ����
		button = (rand() % 2) + 1;
		int currentFloor = Rand_Now(button);
		currentFloor = El_Floor(initialFloor, currentFloor); //El_Floor �Լ� ȣ���� return ���� currentFloor�� ����
		targetFloor = (rand() % 110) - 10;
		initialFloor = El_Floor(currentFloor, targetFloor); //El_Floor �Լ� ȣ���� return ���� initialFloor�� ����
	}
}


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
������� ������ �޴� �Է�(��, �Ʒ�)
�Լ� ���� : ������� ������ �Է¹ް� return������ ����
return �� : ����ڰ� ������ �������� ���� ������ �ִ� ���������Ͱ� ��
���� �����丮 :
���¼ҽ� :
���̺귯�� :
*/

void UD_Button(int UDbutton)
{
	printf("������� ������ �����Ͻÿ� ��(1), �Ʒ�(2) > ");
	scanf("%d", &UDbutton); //������� ���� ���� �Է�
	while (getchar() != '\n'); //���� ����ó��
	if (UDbutton == 1 || UDbutton == 2) {
		return 0; //������(������� ����)�� 1 or 2 ��� return 0
	}
	else {
		printf("error!\n"); //�ް����ϴ� ���ڰ� �ƴ϶�� ���� ���
		printf("�ٽ��Է��Ͻÿ�\n");
		UD_Button(UDbutton); //����Լ��� �߸��Է��ϸ� �ٽ� ���� �����ϵ��� ����
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