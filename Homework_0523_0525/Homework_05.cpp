#include "Homework_05.h"

#include <iostream>
#include <stdlib.h>
using namespace std;

const int EnemyAppearProbability = 10;
const int CriticalProbability = 10;

int PlayerHP = 100;
bool bIsPlayerAlive = true;

void Homework_05()
{
    srand(time(0));

    // 미로 크기
    const int MAZE_ROWS = 10;
    const int MAZE_COLS = 20;

    // 미로 배열
    int Maze[MAZE_ROWS][MAZE_COLS] =
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,2,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
        {1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
        {1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
        {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
        {1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
        {1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,3,1},
        {1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // 플레이어 위치
    int PlayerPos[2] = { 1, 1 };    // (y, x)


    // 플레이어 목적지
    int PlayerNextPos[2] = { 1, 1 };    // (y, x)
    // 플레이어 이동 가능 여부
    bool CanMove = false;
    // 플레이어 입력
    char PlayerInput = NULL;
    // 잘못된 입력 처리용
    bool bIsCorrectInput = false;
    while (Maze[PlayerPos[0]][PlayerPos[1]] != 3 && bIsPlayerAlive)
    {
        // 초기화
        CanMove = false;
        PlayerInput = NULL;
        bIsCorrectInput = false;

        // 화면 출력
        MazeGame_PrintMaze(Maze[0], MAZE_ROWS, MAZE_COLS, PlayerPos);

        while (!CanMove)
        {
            // Player Input
            PlayerInput = MazeGame_PlayerInput();
            // 이동 가능 여부 판단
            bIsCorrectInput = MazeGame_GetPlayerNextPos(PlayerNextPos, PlayerPos, PlayerInput);
            // 잘못된 입력 거르기
            if (!bIsCorrectInput) {
                printf("잘못된 입력입니다.\n다시 선택 해주세요.\n\n");
                break;
            }
            // 목적지에 벽이 없으면 ㄱㄱ
            CanMove = (Maze[PlayerNextPos[0]][PlayerNextPos[1]] != 1) ? true : false;

            // 이동 결정
            if (CanMove)
            {
                // Update player position
                PlayerPos[0] = PlayerNextPos[0];
                PlayerPos[1] = PlayerNextPos[1];
            }
            else
            {
                printf("벽으로 막혀 있습니다.\n다시 선택 해주세요.\n\n");
            }

            // 적 조우
            AppearEnemy();
        }
    }

    if (bIsPlayerAlive)
        printf("축하합니다! 미로를 탈출하셨습니다.\n\n");
    else
        printf("R.I.P\n\n");
}

// 미로 맵 출력
void MazeGame_PrintMaze(int* Maze, int RowSize, int ColSize, int* PlayerPos)
{
    // 이차원 배열 출력
    for (int i = 0; i < RowSize * ColSize; i += ColSize)
    {
        for (int j = 0; j < ColSize; j++)
        {
            if (i / ColSize == PlayerPos[0] && j == PlayerPos[1])
                printf("P ");
            else if (Maze[i + j] == 0)
                printf(". ");
            else if (Maze[i + j] == 1)
                printf("# ");
            else if (Maze[i + j] == 2)
                printf("S ");
            else if (Maze[i + j] == 3)
                printf("E ");
        }
        printf("\n");
    }
    printf("\n플레이어 체력: %d\n\n", PlayerHP);
}

// 플레이어 입력
char MazeGame_PlayerInput()
{
    printf("=== 텍스트 미로 탈출 게임 ===\n");
    printf("[미로 화면 출력]\n");
    printf("이동할 방향을 선택하세요 (w: 위, s: 아래, a: 왼쪽, d: 오른쪽)\n");
    printf("w(↑) s(↓) a(←) d(→)\n");
    printf("방향 입력: ");
    char input = NULL;
    cin >> input;
    return input;
}

// 플레이어 목적지 좌표 알아내기
bool MazeGame_GetPlayerNextPos(int* PlayerNextPos, int* PlayerPos, char PlayerInput)
{
    bool bIsSuccess = true;

    // 방향 벡터 (dy, dx)
    int PlayerVector[4][2] = {
        {-1, 0},    // w
        {0, -1},    // a
        {1, 0},     // s
        {0, 1}      // d
    };

    switch (PlayerInput) {
    case 'w':
        PlayerNextPos[0] = PlayerPos[0] + PlayerVector[0][0];
        PlayerNextPos[1] = PlayerPos[1] + PlayerVector[0][1];
        break;
    case 'a':
        PlayerNextPos[0] = PlayerPos[0] + PlayerVector[1][0];
        PlayerNextPos[1] = PlayerPos[1] + PlayerVector[1][1];
        break;
    case 's':
        PlayerNextPos[0] = PlayerPos[0] + PlayerVector[2][0];
        PlayerNextPos[1] = PlayerPos[1] + PlayerVector[2][1];
        break;
    case 'd':
        PlayerNextPos[0] = PlayerPos[0] + PlayerVector[3][0];
        PlayerNextPos[1] = PlayerPos[1] + PlayerVector[3][1];
        break;
    default:
        bIsSuccess = false;
        break;
    }

    return bIsSuccess;
}

void AppearEnemy()
{
    int EnemyHP = 100;

    int EnemyAppearNumber = rand() % 100 + 1;

    // 적 출현 확률 이내: 적 출현
    if (EnemyAppearNumber <= EnemyAppearProbability)
    {
        printf("적이 등장했습니다!!\n");
        PrintEnemyInfo(EnemyHP);
        Fight(EnemyHP);
    }
    else
    {
        printf("적을 조우하지 않고 무사히 지나갑니다.\n\n");
        cout << "test AppearNumber: " << EnemyAppearNumber << endl << endl;
    }
}

void PrintEnemyInfo(int EnemyHP)
{
    printf("=======================\n");
    printf("적을 조우했습니다.\n전투를 시작합니다.\n플레이어 선공\n\n");
}

void Fight(int EnemyHP)
{
    int TurnCount = 1;
    bool bIsPlayerTurn = true;

    while (EnemyHP > 0 && bIsPlayerAlive)
    {
        printf("\n%d번째 턴 ===============\n", TurnCount++);

        printf("현재 적 HP: %d\n", EnemyHP);
        printf("현재 플레이어 HP: %d\n\n", PlayerHP);
       
        if (bIsPlayerTurn)
        {
            printf("플레이어가 공격합니다.\n");
            EnemyHP -= Attack();
            if (EnemyHP <= 0)
            {
                printf("적이 죽었습니다.\n무사히 지나갑니다.\n\n");
            }
            bIsPlayerTurn = false;
        }
        else
        {
            printf("적이 공격합니다.\n");
            PlayerHP -= Attack();
            if (PlayerHP <= 0)
            {
                printf("미로를 탈출하지 못하고 적에게 죽었습니다.\n\n");
                bIsPlayerAlive = false;
            }
            bIsPlayerTurn = true;
        }
    }

    printf("=======================\n");
}

int Attack()
{
    int Damage = rand() % 10 + 5;
    int CriticalNumber = rand() % 100 + 1;
    if (CriticalNumber <= CriticalProbability)
    {
        printf("크리티컬!!!!!\n");
        Damage *= 2;
    }
    printf("공격 데미지: %d\n", Damage);

    return Damage;
}