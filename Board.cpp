#include <iostream>
#include "Board.h"

Board* Board::instance_ = nullptr;
/*GetInstance : Singleton pattern을 적용한 함수*/
Board* Board::GetInstance() {
  if (instance_ == nullptr) { instance_ = new Board(); }
  return instance_;
}
Board::Board() {}
/*SetSize : board의 size by size 설정 및 '.'로 값 초기화하는 함수 ,
 더하여 초기설정을 하는 함수.*/
void Board::SetSize(int size) {
  matrix_ = std::vector<std::vector<char>>(size, std::vector<char>(size, '.'));
  matrix_[size / 2][size / 2] = 'B';
  matrix_[size / 2 - 1][size / 2 - 1] = 'B';
  matrix_[size / 2][size / 2 - 1] = 'W';
  matrix_[size / 2 - 1][size / 2] = 'W';
}
/*PutStone : board의 row, col 자리에 color의 돌을 놓는 함수*/
void Board::PutStone(int row, int col, char color) {
  matrix_[row][col] = color;
}
void Board::PrintBoard() {  // 보드의 상태를 출력하는 함수
  std::cout << "\\  ";
  for (int i = 0; i < matrix_.size(); i++) {
    std::cout << i << "  ";
  }
  std::cout << std::endl;
  for (int i = 0; i < matrix_.size(); i++) {
    std::cout << i << "  ";

    for (int j = 0; j < matrix_[0].size(); j++) {
      std::cout << matrix_[i][j] << "  ";
    }
    std::cout << std::endl;
  }
}
std::vector<std::vector<char>> Board::Getmatrix() { return matrix_; }
/*IsFullBoard() : 보드에 돌이 꽉 차있는지 확인하는 함수*/
bool Board::IsFullBoard() {
  for (int i = 0; i < matrix_.size(); i++) {
    for (int j = 0; j < matrix_[0].size(); j++) {
      if (matrix_[i][j] == '.') {
        return false;
      }
    }
  }
  return true;
}
/*HasOnlyOneType : board에 한가지 색상으로만 돌이 구성되어 있는지 확인하는 함수
 (게임 진행 조건을 확인하기 위함)*/
bool Board::HasOnlyOneType() {
  int p1 = 0;   // black 돌을 가진 플레이어라고 가정
  int p2 = 0;   // white 돌을 가진 플레이어라고 가정

  for (int i = 0; i < matrix_.size(); i++) {
    for (int j = 0; j < matrix_[0].size(); j++) {
      if (matrix_[i][j] == '.') { continue; }
      if (matrix_[i][j] == 'B') { p1++; }
      if (matrix_[i][j] == 'W') { p2++; }
    }
  }
  if (p1 != 0 || p2 != 0) { return false; }
  return true;
}
/*RestoreBoard : 돌을 놓은 뒤 후보군이었던 좌표들을 다시 '.'으로 바꿔주는 함수*/
void Board::RestoreBoard() {
  for (int i = 0; i < matrix_.size(); i++) {
    for (int j = 0; j < matrix_[i].size(); j++) {
      if (matrix_[i][j] == '*') { this->PutStone(i, j, '.'); }
    }
  }
}
