#ifndef _MNT_C_USERS_USER_OODLAB_OTHELLO_FINAL_JUDGE_H_
#define _MNT_C_USERS_USER_OODLAB_OTHELLO_FINAL_JUDGE_H_
#include <string>
#include <utility>
#include <vector>
#include "Player.h"
#include "Board.h"

/* 게임 진행 당 필요한 심판은 1명이므로 sigleton pattern 적용 */
class Judge {
 public:
    static Judge* GetInstance();
    void StartGame();
    bool IsGameContinue(char color);
    bool CheckValid(int row, int col, char color);
    void SetPlayers();
    void SetScore();
    void CreateBoard();
    bool PlayerInput();
    void SignStone(int row, int col, char color);
    void ModStoneStatus(int row, int col, char color);
    char ChangeTurn(char color);
    std::string GetPlayerName(char color);
    std::string CheckWinner();
    std::vector<std::pair<int, int>> GetCandidate();
    Board* GetBoard();
    Player* GetP1();
    Player* GetP2();

 private:
    Judge();
    int turn_, row_, col_;
    std::vector<std::pair<int, int>> candidate_;
    static Judge* instance_;
    Board* board_;
    Player* p1_;
    Player* p2_;
};

#endif  // _MNT_C_USERS_USER_OODLAB_OTHELLO_FINAL_JUDGE_H_
