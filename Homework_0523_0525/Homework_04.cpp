#include "Homework_04.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int PoolLength = 12;

const int StartMoney = 10000;
const int MinBetting = 100;

const int DealerSelectNumber = 2;

const enum CardAlphabet
{
	Jocker = 0,
	A = 1,
	J = 10,
	Q = 11,
	K = 12,
};

void Homework_04()
{
	srand(time(0));

	int MyMoney = StartMoney;
	int BettingMoney = MinBetting;

	int DealerCards[3] = { 0, };	// 셔플 전 마지막 장은 항상 조커
	int CardPool[PoolLength];	// 조커 제외
	// 카드에 1~12 (A~K) 번호 부여
	for (int i = 0; i < PoolLength; i++)
	{
		CardPool[i] = i + 1;
	}
	
	int PlayerCard = 0;
	int PlayerAgain = 0;

	do
	{
		// 초기화
		PlayerAgain = 0;
		PlayerCard = 0;
		for (int i = 0; i < DealerSelectNumber; i++)
		{
			DealerCards[i] = 0;
		}

		// 배팅
		BettingMoney = InputBetting(MyMoney);
		MyMoney -= BettingMoney;

		// 딜러 카드 2장 선택 (중복X)
		DealerSelectCard(DealerCards, CardPool, PoolLength);

		// 딜러 카드들 + 조커 카드 중 플레이어가 카드 선택
		PlayerCard = PlayerSelect(DealerCards, DealerSelectNumber);

		// 게임 결과 판단
		PrintResult(BettingMoney, PlayerCard);
		// 조커 뽑으면 플레이어 승리 -> 배팅 금액의 2배 획득
		if (PlayerCard == Jocker)
		{
			MyMoney += BettingMoney * 2;
			printf("현재 금액: %d원\n\n", MyMoney);
		}
		// 조커를 못 뽑으면 플레이어 패배 -> 다음 게임 시작 또는 배팅 금액 추가 지불 후 한 번 더 선택
		else
		{
			printf("여기서 포기하실 건가요?\n");
			printf("현재 금액: %d원\n", MyMoney);
			printf("이전 배팅 금액: %d원\n", BettingMoney);
			printf("1. 새로 배팅하기\n");
			printf("2. 배팅 금액을 2배로 올리고 다시 선택하기 (단, 한 번만 가능)\n");
			printf("당신의 선택을 입력하세요(숫자만): ");
			cin >> PlayerAgain;
			
			if (PlayerAgain == 2)
			{
				if (MyMoney >= BettingMoney * 2)
				{
					// 배팅할 돈 충분
					BettingMoney *= 2;
					MyMoney -= BettingMoney;
					printf("배팅 금액: %d\n", BettingMoney);

					// 카드 새로 선택
					PlayerCard = DealerCards[PlayerInput()];

					// 게임 결과 판단
					PrintResult(BettingMoney, PlayerCard);
					if (PlayerCard == Jocker)
					{
						MyMoney += BettingMoney * 2;
						printf("현재 금액: %d원\n\n", MyMoney);
					}
				}
				else
				{
					// 배팅할 돈 없음
					printf("돈이 부족합니다.\n판을 새로 시작합니다.\n\n");
				}
			}
		}

		printf("========================================\n");
	} while (MyMoney > 100);

	printf("현재 보유 금액: %d\n", MyMoney);
	printf("돈이 부족합니다.\n새로운 판을 시작할 수 없습니다.\n\n");
}

int InputBetting(int MyMoney)
{
	int BettingMoney = 0;

	while (BettingMoney < MinBetting || BettingMoney > MyMoney)
	{
		printf("배팅 가능 금액: 100 ~ %d원\n", MyMoney);
		printf("배팅할 금액을 입력하세요: ");
		cin >> BettingMoney;

		if (BettingMoney < MinBetting)
		{
			printf("배팅 금액이 너무 적습니다.\n100원 이상 배팅하세요.\n\n");
		}
		else if (BettingMoney > MyMoney)
		{
			printf("가지고 있는 돈 안에서 배팅하세요.\n\n");
		}
	}

	return BettingMoney;
}

void DealerSelectCard(int* SelectedArray, int* PoolArray, int PoolLength)
{
	// 카드 섞기
	FisherYatesShuffle(PoolArray, PoolLength);

	// 카드 선택
	for (int i = 0; i < DealerSelectNumber; i++)
	{
		SelectedArray[i] = PoolArray[i];
	}
}

// 플레이어가 선택한 카드의 숫자 반환
int PlayerSelect(int* PoolArray, int PoolLength)
{
	// 카드 섞기
	FisherYatesShuffle(PoolArray, PoolLength);

	// 카드 선택
	int SelectedNumber = PlayerInput();

	// 선택된 카드 숫자 반환
	return PoolArray[SelectedNumber];
}

// 선택할 카드 입력
int PlayerInput()
{
	int SelectedNumber = 0;
	printf("선택 가능 카드 번호: 1 ~ %d\n", DealerSelectNumber + 1);
	printf("카드를 선택하세요 (숫자만 입력): ");
	cin >> SelectedNumber;

	return SelectedNumber - 1;
}

void PrintResult(int BettingMoney, int PlayerSelectedCard)
{
	int Result = 0;

	if (PlayerSelectedCard == Jocker)
	{
		printf("축하합니다! 조커를 뽑으셨습니다!\n");
		printf("[승리] %d원 획득!\n", BettingMoney * 2);
	}
	else
	{
		printf("조커가 아닙니다.\n[패배] 배팅금을 잃습니다.\n");
	}
}

void FisherYatesShuffle(int* Array, int Length)
{
	int idx = -1, tmp = 0;
	for (int ptr = Length - 1; ptr > 0; ptr--)
	{
		idx = rand() % ptr + 1;
		tmp = Array[ptr];
		Array[ptr] = Array[idx];
		Array[idx] = tmp;
	}
}