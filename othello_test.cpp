#include "gtest/gtest.h"
#include "Judge.h"
#include "Board.h"
#include "Player.h"

// 시작 테스트 1(이름 선택)
TEST(OthelloTest, StartNameTest) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test->GetBoard()->SetSize(8);

  judge_test->GetP1()->SetName("p1name");
  judge_test->GetP2()->SetName("p2name");
  std::string end = "p1namep2name";
  std::string to = judge_test->GetP1()->GetName();
  to += judge_test->GetP2()->GetName();
  EXPECT_EQ(to, end);
}

// 시작 테스트 2(색 선택)
TEST(OthelloTest, StartColorTest) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test->GetBoard()->SetSize(8);

  judge_test-> GetP1()->SetColor('B');
  judge_test->GetP2()->SetColor('W');
  std::string end = "BW";
  std::string to = "";
  to += judge_test->GetP1()->GetColor();
  to += judge_test->GetP2()->GetColor();
  EXPECT_EQ(to, end);
}

// 시작 후 보드 기본 상태
TEST(OthelloTest, StartSetBoardTest) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test->GetBoard()->SetSize(8);

  bool one = true;
  bool two = true;
  // 실제 배열을 받음
  std::vector<std::vector<char>> matrix_now = judge_test->
  GetBoard()->Getmatrix();

  for (int i = 0; i < matrix_now.size(); i++) {
    for (int j = 0; j < matrix_now[i].size(); j++) {
        if (i == 3 || i == 4 || j == 3 || j == 4) {
            if ((i == 3 && j == 3) || (i == 4 && j == 4)) {
                if (matrix_now[i][j] != 'B') {
                    two = false;
                    break;
                }
            }
            if ((i == 4 && j == 3) || (i == 3 && j == 4)) {
                if (matrix_now[i][j] != 'W') {
                    two = false;
                    break;
                }
            }
        } else {
            // 다른곳에서 돌이 나왔을경우
            if (matrix_now[i][j] == 'B' || matrix_now[i][j] == 'W') {
                two = false;
                break;
            }
        }
    }
  }
  EXPECT_EQ(one, two);
}

// RestoreBoard 동작 여부 (뒤집히지 않은 상태임)
TEST(OthelloTest, StartPutStoneTest) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test -> GetBoard()->SetSize(8);
  std::vector<std::vector<char>> matrix_now_test = judge_test->
  GetBoard()->Getmatrix();

  // 돌을 놓은 상태
  judge_test->GetBoard()->PutStone(3, 5, 'B');
  judge_test->ModStoneStatus(3, 5, 'B');
  judge_test->ChangeTurn('B');
  judge_test->GetBoard()->RestoreBoard();

  bool to = true;
  bool from = true;
  // 예상 배열 제작
  matrix_now_test[3][4] = 'B';
  matrix_now_test[3][5] = 'B';

  matrix_now_test[2][3] = '.';
  matrix_now_test[2][5] = '.';
  matrix_now_test[4][5] = '.';

  matrix_now_test[2][4] = '.';
  matrix_now_test[4][2] = '.';
  matrix_now_test[5][3] = '.';
  std::vector<std::vector<char>> matrix_prev = judge_test->
  GetBoard()->Getmatrix();
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (matrix_now_test[i][j] != matrix_prev[i][j]) {
        from = false;
        break;
      }
    }
  }
  EXPECT_EQ(to, from);
}

// 스코어 테스트 p1
TEST(OthelloTest, ScoreTest1) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test->GetBoard()->SetSize(8);
  std::vector<std::vector<char>> matrix_now = judge_test->
  GetBoard()->Getmatrix();

  // 돌을 놓은 상태
  judge_test->GetBoard()->PutStone(3, 5, 'B');
  judge_test->ModStoneStatus(3, 5, 'B');
  judge_test->ChangeTurn('B');
  judge_test->GetBoard()->RestoreBoard();

  // 점수 설정
  judge_test->SetScore();
  int p1_test_score = 4;
  int p1_real_score = judge_test->GetP1()->GetScore();
  EXPECT_EQ(p1_test_score, p1_real_score);
}

// 스코어 테스트 p2
TEST(OthelloTest, ScoreTest2) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test->GetBoard()->SetSize(8);
  std::vector<std::vector<char>> matrix_now = judge_test->
  GetBoard()->Getmatrix();

  // 돌을 놓은 상태
  judge_test->GetBoard()->PutStone(3, 5, 'B');
  judge_test->ModStoneStatus(3, 5, 'B');
  judge_test->ChangeTurn('B');
  judge_test->GetBoard()->RestoreBoard();

  int p2_test_score = 1;
  int p2_real_score = judge_test->GetP2()->GetScore();

  EXPECT_EQ(p2_test_score, p2_real_score);
}

// CheckValid 정상 실행 여부
TEST(OthelloTest, CheckValidTest) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test->GetBoard()->SetSize(8);
  std::vector<std::vector<char>> matrix_now = judge_test->
  GetBoard()->Getmatrix();

  // 돌을 놓은 상태
  judge_test->GetBoard()->PutStone(3, 5, 'B');
  judge_test->ModStoneStatus(3, 5, 'B');
  judge_test->ChangeTurn('B');
  judge_test->GetBoard()->RestoreBoard();

  bool to = false;
  bool from = judge_test->CheckValid(0, 0, 'B');
  EXPECT_EQ(to, from);
}

// candidate 정상 실행 여부
TEST(OthelloTest, CandidateTest) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test->GetBoard()->SetSize(8);

  // 돌을 놓은 상태
  judge_test->GetBoard()->PutStone(3, 5, 'B');
  judge_test->ModStoneStatus(3, 5, 'B');
  judge_test->ChangeTurn('B');
  judge_test->GetBoard()->RestoreBoard();

  bool to = true;
  bool from = true;
  std::vector<std::pair<int, int>> candidate_test =
  judge_test->GetCandidate();
  // (2, 3), (2, 5), (4, 5)
  std::pair<int, int> pair1(2, 3);
  std::pair<int, int> pair2(2, 5);
  std::pair<int, int> pair3(4, 5);
  for (int i = 0; i < candidate_test.size(); i++) {
    if (candidate_test[i] != pair1 && candidate_test[i] != pair2
    && candidate_test[i] != pair3) {
        from = false;
        break;
    }
  }
  EXPECT_EQ(to, from);
}

// IsFullBoard 정상 여부
TEST(OthelloTest, IsFullBoardTest) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test->GetBoard()->SetSize(8);
  std::vector<std::vector<char>> matrix_now = judge_test->
  GetBoard()->Getmatrix();

  bool to = false;
  bool from = judge_test->GetBoard()->IsFullBoard();
  EXPECT_EQ(to, from);
}

// IsGameContinue 정상 여부
TEST(OthelloTest, IsGameContinueTest) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test->GetBoard()->SetSize(8);
  std::vector<std::vector<char>> matrix_now = judge_test->
  GetBoard()->Getmatrix();

  bool to = true;
  bool from = judge_test->IsGameContinue('B');
  EXPECT_EQ(to, from);
}

// HasOnlyOneType 정상 여부
TEST(OthelloTest, HasOnlyOneTypeTest) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test -> GetBoard()->SetSize(8);
  std::vector<std::vector<char>> matrix_now = judge_test->
  GetBoard()->Getmatrix();

  // 돌을 놓은 상태
  judge_test->GetBoard()->PutStone(3, 5, 'B');
  judge_test->ModStoneStatus(3, 5, 'B');
  judge_test->ChangeTurn('B');
  judge_test->GetBoard()->RestoreBoard();

  bool to = false;
  bool from = judge_test->GetBoard()->HasOnlyOneType();
  EXPECT_EQ(to, from);
}

// 정상 게임 종료 여부
TEST(OthelloTest, EndingTest) {
  // 기본 설정
  Judge* judge_test = Judge::GetInstance();
  judge_test -> GetBoard()->SetSize(8);
  std::vector<std::vector<char>> matrix_now = judge_test->
  GetBoard()->Getmatrix();

  // 돌을 놓은 상태
  judge_test->GetBoard()->PutStone(3, 5, 'B');
  judge_test->ModStoneStatus(3, 5, 'B');
  judge_test->ChangeTurn('B');
  judge_test->GetBoard()->RestoreBoard();

  // 현재로는 p1이 돌이 더 많음.
  std::string to = judge_test->GetP1()->GetName();
  std::string from = judge_test->CheckWinner();
  EXPECT_EQ(to, from);
}
