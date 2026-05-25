#pragma once

// 슬롯 머신 게임 만들기
// Homework03_Run(); 함수로 실행 가능해야 함.
// - 시작 금액 10000
// - 한판에 무조건  최소 100 배팅해야 함.만약 소지금액이 100 이하일 경우 게임 종료.
// - 같은 숫자 3개가 나오면 50배로 돌려 받는다.
// - 만약 777이면 10000배 받음

void Homework_03();

void Homework_03_Play(int MyMoney);

int InputBettingMoney(int MyMoney);

int SpinRoulette();

int GetNumber();

