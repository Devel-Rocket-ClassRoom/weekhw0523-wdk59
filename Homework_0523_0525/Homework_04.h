#pragma once

// 도둑 잡기 만들기
// Homework04_Run(); 함수로 실행 가능해야 함.
// - 시작 금액 10000
// - 한판에 무조건 최소 100 배팅해야 함.만약 소지금액이 100 이하일 경우 게임 종료.
// - 딜러는 A~K까지의 트럼프 카드 중 2장을 중복없이 선택하고 조커 카드가 추가된다.
// - 플레이어는 딜러의 카드 중 한장을 선택한다.
// - 만약 플레이어가 조커를 뽑았다면 플레이어의 승리.배팅 금액의 2배를 받는다.
// - 플레이어가 조커를 뽑지 못했다면 다음 게임을 시작하거나 배팅 금액의 2배를 추가로 지불하고 한번 더 선택할 수 있다.

void Homework_04();

int InputBetting(int MyMoney);

void DealerSelectCard(int* SelectedArray, int* PoolArray, int PoolLength);

int PlayerSelect(int* PoolArray, int PoolLength);

int PlayerInput();

void PrintResult(int BettingMoney, int PlayerSelectedCard);

void FisherYatesShuffle(int* Array, int Length);

