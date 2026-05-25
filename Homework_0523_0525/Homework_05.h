// 미로 탈출 게임에 랜덤 인카운터를 추가하여 적과의 턴제 전투 만들기
// Homework05_Run(); 함수로 실행 가능해야 함.
// - HP는 100으로 시작
// - 공격을 할 때 상대방에게 5~15의 데미지를 준다.
// - 10 % 의 확률로 크리티컬이 발생해 2배의 데미지를 준다.
// - 상대방의 HP가 0 이하가 되면 승리한다.

#pragma once

void Homework_05();

char MazeGame_PlayerInput();

bool MazeGame_GetPlayerNextPos(int* PlayerNextPos, int* PlayerPos, char PlayerInput);

void MazeGame_PrintMaze(int* Maze, int RowSize, int ColSize, int* PlayerPos);

void AppearEnemy();

void PrintEnemyInfo(int EnemyHP);

void Fight(int EnemyHP);

int Attack();