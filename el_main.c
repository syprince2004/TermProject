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

int Rand_Input(int UD); //Rand_Input �Լ� ����
int UD_Button(int button); //UD_Button �Լ� ����

int main()
{
	while(1)
	{
		int button = 0;
		printf("������� ������ �����Ͻÿ� ��(1), �Ʒ�(2) > ");
		scanf("%d", &button); //������� ���� ���� �Է�
		UD_Button(button); //UD_Button �Լ� ȣ��
	}
}