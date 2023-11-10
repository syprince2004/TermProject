/*
���������� ���� ���α׷�
���� ȯ�� : VS2022, C���, Windows
���� ���� : ���������� ���� ���α׷��� ������ ���� ���α׷��� �ɷ� ���
���� ��� : 
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

int Cl_Button(int Close);

unsigned _stdcall elevator1(void* arg);

unsigned _stdcall elevator2(void* arg);


/*
�����Լ�
�Լ� ���� : ��� ������ �̷������ ����
return �� :
���� �����丮 :
	2023-11-09 - 
*/

int main()
{
	int targetFloor = 0;

	int initialFloor = 11; //ó�� �����Ҷ� ���� ������ 1��

	_beginthreadex(NULL, 0, elevator1, 0, 0, NULL);

	Sleep(1000);

	_beginthreadex(NULL, 0, elevator2, 0, 0, NULL);

	while (1)
	{

		int button = 0;
		int close = 0;
		UD_Button(button); //UD_Button �Լ� ȣ��

		int currentFloor = Rand_Now(button);

		currentFloor = El_Floor(initialFloor, currentFloor); //El_Floor �Լ� ȣ���� return ���� currentFloor�� ����

		printf("�������ϴ� ���� �Է��Ͻÿ� > ");
		scanf("%d", &targetFloor); //������� ���� ����ڰ� �Է�
		targetFloor += 10; //110���� �⺻���� �ϱ� ������ +10������ ��

		printf("������ư(1) > ");
		scanf("%d", &close); //������ư ���� ����ڰ� �Է�
		Cl_Button(close);

		initialFloor = El_Floor(currentFloor, targetFloor);
	}
}
/*
����ü ���� : ����, ž���ο��� ����
���� �����丮 : 
	(2023-11-10) - 
*/

struct {
	char gender; //����
	int num_people; // ���������Ϳ� Ÿ�� �ο���
}People;


/*
��� ���ư��� ����������1
�Լ� ���� : ��� �������� �Է¹ް� ���ư��� ����������1
return �� :
���� �����丮 : 
	(2023-11-09) - �������� ������ġ�� �ް� ������� ��ġ�� �������� �޴� ����������1 �Լ� ����
*/

unsigned _stdcall elevator1(void* arg)
{
	int targetFloor = 0;
	int initialFloor = 11;
	
	while(1){
		int button = 0;
		int close = 0;
		srand(time(NULL));//�Ź� �ٸ� �� �õ� ����
		button = (rand() % 2) + 1;
		int currentFloor = Rand_Now(button);
		currentFloor = El_Floor(initialFloor, currentFloor); //El_Floor �Լ� ȣ���� return ���� currentFloor�� ����
		targetFloor = (rand() % 110) - 10;
		close = (rand() % 2);
		Cl_Button(close);
		initialFloor = El_Floor(currentFloor, targetFloor); //El_Floor �Լ� ȣ���� return ���� initialFloor�� ����
	}
}


/*
��� ���ư��� ����������2
�Լ� ���� : ��� �������� �Է¹ް� ���ư��� ����������2
return �� :
���� �����丮 :
	(2023-11-09) - �������� ������ġ�� �ް� ������� ��ġ�� �������� �޴� ����������2 �Լ� ����
*/

unsigned _stdcall elevator2(void* arg)
{
	int targetFloor = 0;
	int initialFloor = 11;

	while (1) {
		int button = 0;
		int close = 0;
		srand(time(NULL));//�Ź� �ٸ� �� �õ� ����
		button = (rand() % 2) + 1;
		int currentFloor = Rand_Now(button);
		currentFloor = El_Floor(initialFloor, currentFloor); //El_Floor �Լ� ȣ���� return ���� currentFloor�� ����
		targetFloor = (rand() % 110) - 10;
		close = (rand() % 2);
		Cl_Button(close);
		initialFloor = El_Floor(currentFloor, targetFloor); //El_Floor �Լ� ȣ���� return ���� initialFloor�� ����
	}
}


/*
������ư�� ��뿩��
�Լ� ���� : ������ư�� ������ 1������ ������ �ȴ����� 3���Ŀ� ����
return �� : �����Ѱ����� ���� ���� ����� ��ġ
���� �����丮 : 
	(2023-11-10) - Sleep �Լ��� �̿��� ������ư�� ������ 1�ʵ� ���̴����ϴ� ��� �ƴ϶�� 3�ʵ� ���
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
�������� �޴� ���� ����� ��ġ
�Լ� ���� : �������� ���� �Է����� ������� ���� ��ġ�� �˷���
return �� : �����Ѱ����� ���� ���� ����� ��ġ
���� �����丮 : 2023-11-09
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
���� �����丮 : 2023-11-09
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