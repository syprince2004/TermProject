/*
���������� ���� ���α׷�
���� ȯ�� : VS2022, C���, Windows
���� ���� : ���������� ���� ���α׷��� ������ ���� ���α׷��� �ɷ� ���
���� ��� : ����ڰ� ������ �������� ���� ������ �ִ� ���������Ͱ� ��
���� �����丮 :
���¼ҽ� :
���̺귯�� :
*/
#include <stdio.h>

#include <stdlib.h> //���� �Լ��� ���� ���� �������

#include <time.h> //time �Լ��� ���� ���� �������

#include <windows.h> //usleep �Լ��� ���� ���� �������

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
�������� ���ϴ� ����ڰ� �������ϴ� ��ġ
�Լ� ���� : ����ڰ� ������� ��ġ�� �˷���
return �� : �����Ѱ����� ���� ������� ��ġ
���� �����丮 :
���¼ҽ� :
���̺귯�� :
*/

int Rand_future(int UD)
{
	int currentFloor = Rand_Now(UD);
	srand(time(NULL)); //�Ź� �ٸ� �� �õ� ����
	int targetFloor = 0;
	if (UD == 1) {
		targetFloor = (rand() % (110 - currentFloor)) + currentFloor+1; //���� ��ġ���� ���� ��ġ�� ������ ��
	}
	else
		targetFloor = (rand() % currentFloor-1) + 1; //���� ��ġ���� ���� ��ġ�� ������ ��

	double timePerFloor = 0.5; // �� �� �̵��� �ɸ��� �ð� (��)

	if (currentFloor == targetFloor) {
		printf("���������ʹ� �̹� ��ǥ ���� �����߽��ϴ�.\n"); //�������� ��ǥ���� ���Ͽ� ���ٸ� ���� ���
	}
	else if (currentFloor < targetFloor) {
		printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", currentFloor, targetFloor); //�������� ��ǥ������ �۴ٸ� 
		while (currentFloor < targetFloor) {
			Sleep((int)(timePerFloor * 1000)); // usleep �Լ��� ����Ͽ� 0.5�� ���
			currentFloor++;
			printf("���� %d��\n", currentFloor);
		}
		printf("���������Ͱ� ��ǥ �� %d�� �����߽��ϴ�.\n", targetFloor);
	}
	else {
		printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", currentFloor, targetFloor);
		while (currentFloor > targetFloor) {
			Sleep((int)(timePerFloor * 1000)); // usleep �Լ��� ����Ͽ� ���
			currentFloor--;
			printf("���� %d��\n", currentFloor);
		}
		printf("���������Ͱ� ��ǥ �� %d�� �����߽��ϴ�.\n", targetFloor);
	}


	return(targetFloor);
}

/*
������� ������ �޴� �Է�(��, �Ʒ�)
�Լ� ���� : ������� ������ �Է¹ް� return������ ����
return �� : ����ڰ� ������ �������� ���� ������ �ִ� ���������Ͱ� ��
���� �����丮 :
���¼ҽ� :
���̺귯�� :
*/

int UD_Button(int button)
{
	while (getchar() != '\n'); //���� ����ó��
	if (button == 1 || button == 2) { 
		Rand_future(button); //������(������� ����)�� 1 or 2 ��� Rand_futuer �Լ� ȣ��
	}
	else {
		printf("error!\n"); //�ް����ϴ� ���ڰ� �ƴ϶�� ���� ���
		printf("�ٽ��Է��Ͻÿ�\n");
	}
}
