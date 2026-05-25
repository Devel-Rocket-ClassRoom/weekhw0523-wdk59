#include "Homework_03.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int StartMoney = 10000;	// 시작 금액
const int MinBetting = 100;		// 최소 배팅 금액
const int Triple = 50;			// 같은 숫자 3개에 대한 배수
const int Lucky = 10000;		// 777에 대한 배수

void Homework_03()
{
	// 랜덤 시드를 현재 시각으로 설정
	srand(time(0));
	
	int MyMoney = StartMoney;		// 현재 소지금
	
	// 슬롯 게임 시작
	Homework_03_Play(MyMoney);
}

void Homework_03_Play(int MyMoney)
{
	int BettingMoney = 0;

	int RouletteResult = 0;
	do
	{
		RouletteResult = 0;

		// 배팅 금액 입력
		BettingMoney = InputBettingMoney(MyMoney);
		MyMoney -= BettingMoney;

		// 룰렛 돌리기
		RouletteResult = SpinRoulette();
		
		// 정산 및 결과 출력
		// 결과 0: 패배 -> 돈 잃음
		// 결과 !0: 승리 -> 결과만큼 곱한 값을 MyMoney에 더하기
		if (RouletteResult != 0)
		{
			// 이겼을 때 결과 출력
			if (RouletteResult == Lucky)
			{
				printf("축하합니다!! Lucky 777!!!!!\n\n");
			}
			else
			{
				printf("축하합니다! Triple!!!\n\n");
			}

			// 정산
			MyMoney += BettingMoney * RouletteResult;
		}
		else
		{
			// 졌을 때 결과 출력
			printf("당신의 패배입니다.\n\n");
		}

		// 잔액 출력
		printf("현재 잔액 : % d원\n\n", MyMoney);
	} while (MyMoney > MinBetting);

	printf("더 이상 게임을 진행할 수 없습니다.\n게임을 종료합니다.\n\n");
}

int InputBettingMoney(int MyMoney)
{
	int PlayerInput = 0;

	while (PlayerInput < MinBetting || PlayerInput > MyMoney)
	{
		printf("배팅 가능 금액: %d원\n", MyMoney);
		printf("배팅할 금액을 입력해주세요: ");
		cin >> PlayerInput;
		if (PlayerInput < MinBetting)
		{
			printf("%d원 이상 배팅해주세요.\n\n", MinBetting);
		}
	}
	
	return PlayerInput;
}

// 룰렛을 돌려서 777이면 Lucky(10000), 같은 숫자 3개면 Triple(50), 해당하는 게 없으면 0 반환
int SpinRoulette()
{
	int Numbers[3] = { 0, };
	printf("룰렛 결과: ");
	for (int i = 0; i < 3; i++)
	{
		Numbers[i] = GetNumber();
		printf("%d ", Numbers[i]);
	}
	printf("\n");

	int Result = 0;
	// 777
	if (Numbers[0] == 7 && Numbers[1] == 7 && Numbers[2] == 7)
	{
		Result = Lucky;
	}
	// 같은 숫자 3개
	else if (Numbers[0] == Numbers[1] && Numbers[1] == Numbers[2])
	{
		Result = Triple;
	}

	// 같은 숫자가 3개 미만
	//Result = Triple;	// Test
	return Result;
}

int GetNumber()
{
	return rand() % 9 + 1;
}