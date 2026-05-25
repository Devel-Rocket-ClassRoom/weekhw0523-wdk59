#include "Homework_02.h"
#include <iostream>
using namespace std;

void Homework_02()
{
	int Numbers[10] = { 0, };	// 나눠진 숫자들이 저장될 배열
	int InputNumber = 0;		// 입력받은 숫자 저장
	int Length = 0;				// Numbers 배열의 길이 저장

	InputNumber = Input();		// 숫자 입력받기

	// 숫자 자릿수별로 나눠서 Numbers에 저장
	// 일의 자리 자릿수가 커지는 순서로 저장됨
	// Numbers 배열의 길이가 반환되어 Length에 저장
	Length = Divide(Numbers, InputNumber);

	int Result = AddNumbers(Numbers, Length);	// 최종 결과(자릿수들의 합) 저장
	printf("각 자릿수의 합은 %d입니다.\n", Result);
}

// 정수 입력받아서 반환
int Input()
{
	int InputNumber = 0;
	printf("int 범위 내의 정수를 입력하세요: ");
	cin >> InputNumber;

	return InputNumber;
}

// 정수를 자릿수별로 나눠서 Numbers에 저장하고, 정수의 자릿수를 반환
int Divide(int* Numbers, int InputNumber)
{
	int Length = 0;
	// InputNumber가 0이 될 때까지 자릿수 분리
	while (InputNumber)
	{
		Numbers[Length++] = InputNumber % 10;
		InputNumber /= 10;
	}

	return Length;
}

int AddNumbers(int* Numbers, int Length)
{
	int Sum = 0;
	for (int i = 0; i < Length; i++)
	{
		Sum += Numbers[i];
	}
	
	return Sum;
}