#ifndef _MNT_C_USERS_USER_OODLAB_OTHELLO_FINAL_BOARD_H_
#define _MNT_C_USERS_USER_OODLAB_OTHELLO_FINAL_BOARD_H_
#include <string>
#include <vector>

class Board {  // 게임 내 보드는 한개이므로 sigleton 활용
 public:
  static Board* GetInstance();
  void SetSize(int size);                   // size 설정
  void PutStone(int x, int y, char color);  // 입력 받은 좌표의 상태를 바꾸기
  void PrintBoard();                        // 보드판 상태 출력하는 함수
  std::vector<std::vector<char>> Getmatrix();
  bool IsFullBoard();
  bool HasOnlyOneType();
  void RestoreBoard();

 private:
  Board();
  static Board* instance_;
  std::vector<std::vector<char>> matrix_;         // matrix 변수
};

#endif  // _MNT_C_USERS_USER_OODLAB_OTHELLO_FINAL_BOARD_H_
