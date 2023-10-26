/*
엘리베이터 관리 프로그램
개발 환경 : VS2022, C언어, Windows
개발 목적 : 엘리베이터 관리 프로그램의 개발을 통한 프로그래밍 능력 향상
개발 결과 : 사용자가 방향을 눌렀을때 가장 가까이 있는 엘리베이터가 옴
개발 히스토리 :
오픈소스 :
라이브러리 :
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <stdlib.h> //랜덤 함수를 쓰기 위한 헤더파일

#include <time.h> //time() 함수를 쓰기 위한 헤더파일

int Rand_Input(int UD); //Rand_Input 함수 선언
int UD_Button(int button); //UD_Button 함수 선언

int main()
{
	while(1)
	{
		int button = 0;
		printf("가고싶은 방향을 선택하시오 위(1), 아래(2) > ");
		scanf("%d", &button); //가고싶은 방향 직접 입력
		UD_Button(button); //UD_Button 함수 호출
	}
}