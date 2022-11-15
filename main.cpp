#include <iostream>
#include "Board.h"
#include "Judge.h"
#include "Player.h"

int main() {
    Judge* judge = Judge::GetInstance();
    judge->StartGame();
}
