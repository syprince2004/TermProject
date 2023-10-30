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
�������� ���ϴ� ����ڰ� �������ϴ� ��ġ(��ǥ��)
�Լ� ���� : ��ǥ���� �˷��ܰ� ���ÿ� �������� ��ǥ���� ���ϸ鼭 0.5�ʸ��� ���� ������ �Ѿ�� ȭ�鿡 ������
return �� : �����Ѱ����� ���� ������� ��ġ
���� �����丮 :
���¼ҽ� :
���̺귯�� :
*/

int Rand_future(int UD)
{
	/* 
	//��ǥ���� �������� ���ϴ� �ڵ�
	srand(time(NULL)); //�Ź� �ٸ� �� �õ� ����
	int targetFloor = 0;
	if (UD == 1) {
		targetFloor = (rand() % (110 - currentFloor)) + currentFloor+1; //���� ��ġ���� ���� ��ġ�� ������ ��
	}
	else
		targetFloor = (rand() % currentFloor-1) + 1; //���� ��ġ���� ���� ��ġ�� ������ ��
	*/

	int currentFloor = Rand_Now(UD);

	int targetFloor = 0;

	int initialFloor = 1;

	double timePerFloor = 0.5; // �� �� �̵��� �ɸ��� �ð� (��)

	if (initialFloor == targetFloor) {
		printf("���������ʹ� �̹� ��ǥ ���� �����߽��ϴ�.\n"); //�ʱ����� �������� ���Ͽ� ���ٸ� ���� ���
	}
	else if (initialFloor < currentFloor) {
		printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", initialFloor, currentFloor); //�ʱ����� ���������� �۴ٸ� �ʱ������� ���������� ����
		while (initialFloor < currentFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� 0.5�� ���
			initialFloor++; //
			printf("���� %d��\n", initialFloor); //���ڸ� �ϳ��� �������ָ鼭 �� ������
		}
		printf("���������Ͱ� ����� �� %d�� �����߽��ϴ�.\n", currentFloor);
		currentFloor = initialFloor; //�ٽ� �Է� �޴� ��� �ʱ� ������������ ��ġ�� �޶���
	}
	else {
		printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", initialFloor, currentFloor); //�ʱ����� ���������� ũ�ٸ� �ʱ������� ���������� ����
		while (initialFloor > currentFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� ���
			initialFloor--;
			printf("���� %d��\n", initialFloor); //���ڸ� �ϳ��� �������ָ鼭 �� ������
		}
		printf("���������Ͱ� ��ǥ �� %d�� �����߽��ϴ�.\n", currentFloor);
		currentFloor = initialFloor; //�ٽ� �Է� �޴� ��� �ʱ� ������������ ��ġ�� �޶���
	}

	printf("�������ϴ� ���� �Է��Ͻÿ� > ");
	scanf_s("%d", &targetFloor);

	if (currentFloor == targetFloor) {
		printf("���������ʹ� �̹� ��ǥ ���� �����߽��ϴ�.\n"); //�������� ��ǥ���� ���Ͽ� ���ٸ� ���� ���
	}
	else if (currentFloor < targetFloor) {
		printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", currentFloor, targetFloor); //�������� ��ǥ������ �۴ٸ� ���������� ��ǥ������ ����
		while (currentFloor < targetFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� 0.5�� ���
			currentFloor++; //
			printf("���� %d��\n", currentFloor); //���ڸ� �ϳ��� �������ָ鼭 �� ������
		}
		printf("���������Ͱ� ��ǥ �� %d�� �����߽��ϴ�.\n", targetFloor);
	}
	else {
		printf("���������Ͱ� %d������ %d������ �̵��մϴ�.\n", currentFloor, targetFloor); //�������� ��ǥ������ ũ�ٸ� ���������� ��ǥ������ ����
		while (currentFloor > targetFloor) {
			Sleep((int)(timePerFloor * 1000)); // Sleep �Լ��� ����Ͽ� ���
			currentFloor--; 
			printf("���� %d��\n", currentFloor); //���ڸ� �ϳ��� �������ָ鼭 �� ������
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

void UD_Button(int button)
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





/*���� ������ �ʱ� ���������� ���� 1������ �ʱ�ȭ ��. ������ �ι�° ��ư�� �Է������� ���� ���´� ��ǥ������ ���´� �ʱⰪ���� �ٽ� ������ �ؾ���.. ���� �ּ��� ���� */