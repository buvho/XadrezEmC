#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

char tabuleiro[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},
                        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},
                        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},
                        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},
                        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};
int Nmove[8][2] = {{1, 2},  {-1, 2},  {2, 1},  {-2, 1},
                   {1, -2}, {-1, -2}, {2, -1}, {-2, -1}};
int Kmove[8][2] = {{1, 0},  {-1, 0}, {1, 1},  {0, 1},
                   {-1, 1}, {1, -1}, {0, -1}, {-1, -1}};
char Wpiece[6] = {'p', 'r', 'n', 'b', 'k', 'q'};
char Bpiece[6] = {'P', 'R', 'N', 'B', 'K', 'Q'};
bool Redo = false, black = false, foi = false;
char charX, nota;
int posX, posY;

char Board(int X, int Y) {
  if (X + Y % 2 == 0) {
    return ' ';
  } else {
    return '#';
  }
}

bool Check(int X) {
  if (X < 7 || X > 0) {
    return true;
  }
  return false;
}

void Print() {
  printf("  A B C D E F G H\n");
  for (int i = 0; i < 8; i++) {
    printf("%d ", i + 1);
    for (int j = 0; j < 8; j++) {
      printf("%c ", tabuleiro[i][j]);
    }
    printf("\n");
  }
}
void Move(int Y, int X, char P) {
  tabuleiro[Y][X] = Board(Y, X);
  tabuleiro[posY][posX] = P;
  foi = true;
}

void BlackPawn() {
  if (Check(posX - 1) && tabuleiro[posY][posX] != ' ' && tabuleiro[posY][posX] != '#' && tabuleiro[posY - 1][posX] == 'P') {
    if (tabuleiro[posY - 1][posX] == 'P') {
      Move(posY - 1, posX, 'P');
    } else if (posY == 3 && tabuleiro[posY - 2][posX] == 'P') {
      Move(posY - 2, posX, 'P');
    } else {
      for (int i = 0; i < 6; i++) {
        if (tabuleiro[posY][posX] == Bpiece[i]) {
          if (Check(posX - 1) && tabuleiro[posY + 1][posX - 1] == 'P') {
            Move(posY + 1, posX - 1, 'P');
          } else if (Check(posX + 1) && tabuleiro[posY + 1][posX + 1] == 'P' &&
                     !foi) {
            Move(posY + 1, posX + 1, 'P');
          }
        }
      }
    }
  }
}

void WhitePawn() {
  if (Check(posY + 1) &&
      (tabuleiro[posY][posX] == ' ' || tabuleiro[posY][posX] == '#') &&
      tabuleiro[posY + 1][posX] != 'P') {
    if (tabuleiro[posY + 1][posX] == 'p') {
      Move(posY + 1, posX, 'p');
    } else if (posY == 4 && tabuleiro[posY + 2][posX] == 'p') {
      Move(posY + 2, posX, 'p');
    } else {
      for (int i = 0; i < 6; i++) {
        if (tabuleiro[posY][posX] == Bpiece[i]) {
          if (Check(posX - 1) && tabuleiro[posY + 1][posX - 1] == 'p') {
            Move(posY + 1, posX - 1, 'p');
          } else if (Check(posX + 1) && tabuleiro[posY + 1][posX + 1] == 'p' &&
                     !foi) {
            Move(posY + 1, posX + 1, 'p');
          }
        }
      }
    }
  }
}

char PC(char A) {
  if (!black)
    return tolower(A);
  else
    return toupper(A);
}

void Rook(char R) {
  for (int i = posY; i < 8; i++) {
    if (tabuleiro[i][posX] != ' ' && tabuleiro[i][posX] != '#') {
      break;
    } else if (tabuleiro[i][posX] == R) {
      Move(i, posX, R);
      break;
    }
  }
  if (!foi) {
    for (int i = posY; i >= 0; i--) {
      if (tabuleiro[i][posX] != ' ' && tabuleiro[i][posX] != '#') {
        break;
      } else if (tabuleiro[i][posX] == R) {
        Move(i, posX, R);
        break;
      }
    }
  }
  if (!foi) {
    for (int i = posX; i < 8; i++) {
      if (tabuleiro[i][posX] != ' ' && tabuleiro[i][posX] != '#') {
        break;
      } else if (tabuleiro[posY][i] == R) {
        Move(posY, i, R);
        break;
      }
    }
  }
  if (!foi) {
    for (int i = posX; i >= 0; i--) {
      if (tabuleiro[i][posX] != ' ' && tabuleiro[i][posX] != '#') {
        break;
      }
      if (tabuleiro[posY][i] == R) {
        Move(posY, i, R);
        break;
      }
    }
  }
}

void Bishop(char B) {
  for (int i = posY, j = posX; i < 8 && j < 8; i++, j++) {
    if (tabuleiro[i][posX] != ' ' && tabuleiro[i][posX] != '#') {
      break;
    }
    if (tabuleiro[i][i] == B) {
      Move(i, j, B);
      break;
    }
  }
  if (!foi) {
    for (int i = posY, j = posX; i < 8 && j >= 0; i++, j--) {
      if (tabuleiro[i][posX] != ' ' && tabuleiro[i][posX] != '#') {
        break;
      }
      if (tabuleiro[i][i] == B) {
        Move(i, j, B);
        break;
      }
    }
  }
  if (!foi) {
    for (int i = posY, j = posX; i >= 0 && j < 8; i--, j++) {
      if (tabuleiro[i][posX] != ' ' && tabuleiro[i][posX] != '#') {
        break;
      }
      if (tabuleiro[i][i] == B) {
        Move(i, j, B);
        break;
      }
    }
  }
  if (foi) {
    for (int i = posY, j = posX; i >= 0 && j >= 0; i--, j--) {
      if (tabuleiro[i][posX] != ' ' && tabuleiro[i][posX] != '#') {
        break;
      }
      if (tabuleiro[i][i] == B) {
        Move(i, j, B);
        break;
      }
    }
  }
}

void DoMove() {
  for (int i = 0; i < 6; i++) {
    if (black) {
      if (tabuleiro[posY][posX] == Bpiece[i])
        nota = '0';
    } else {
      if (tabuleiro[posY][posX] == Wpiece[i])
        nota = '0';
    }
  }
  switch (nota) {
  case 'P':
    if (!black) {
      WhitePawn();
    } else {
      BlackPawn();
    }
    break;

  case 'R':
    Rook(PC('R'));
    break;

  case 'B':
    Bishop(PC('B'));
    break;

  case 'N':
    for (int i = 0; i < 8; i++) {
      if (Check(posY + Nmove[i][0]) && Check(posX + Nmove[i][1])) {
        if (tabuleiro[posY + Nmove[i][0]][posX + Nmove[i][1]] == PC('N')) {
          Move(posY + Nmove[i][0], posX + Nmove[i][1], PC('N'));
          break;
        }
      }
    }
    break;
  case 'Q': {
    printf("1");
    Rook(PC('Q'));
    if (!foi) {
      printf("2");
      Bishop(PC('Q'));
    }
    break;
  }
  case 'K':
    for (int i = 0; i < 8; i++) {
      if (Check(posY + Kmove[i][0]) && Check(posX + Kmove[i][1])) {
        if (tabuleiro[posY + Kmove[i][0]][posX + Kmove[i][1]] == PC('K')) {
          Move(posY + Kmove[i][0], posX + Kmove[i][1], PC('K'));
          break;
        }
      }
    }
    break;
  }
}

void GetPos() {
  do {
    scanf("%c"
          "%c"
          "%d",
          &nota, &charX, &posY);
    scanf("%c");
    posY -= 1;
    if (posY > 7 || posY < 0) {
      Redo = true;
    }
    switch (charX) {
    case 'a':
      posX = 0;
      break;
    case 'b':
      posX = 1;
      break;
    case 'c':
      posX = 2;
      break;
    case 'd':
      posX = 3;
      break;
    case 'e':
      posX = 4;
      break;
    case 'f':
      posX = 5;
      break;
    case 'g':
      posX = 6;
      break;
    case 'h':
      posX = 7;
      break;
    default:
      Redo = true;
      break;
    }
  } while (Redo);
}

int main(void) {
  Print();
  while (true) {

    printf("Vez do branco, insira uma jogada (Ex: Pe2):\n");
    do {
      GetPos();
      black = false;
      DoMove();
    } while (!foi);
    Print();
    foi = false;

    printf("Vez do preto, insira uma jogada (Ex: Pe2):\n");
    do {
      GetPos();
      black = true;
      DoMove();
    } while (!foi);
    Print();
    foi = false;
  }
  return 0;
}
