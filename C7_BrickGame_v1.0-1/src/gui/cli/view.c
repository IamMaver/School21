#include <ncurses.h>

#include "../../brickgame.h"

void draw(brickGameInfo bGInfo) {
  curs_set(0);
  clear();
  move(0, 30);
  printw("BrickGame");
  print_rectangle(0, 22, 0, 21);
  print_rectangle(2, 4, 28, 48);
  move(3, 30);
  printw("LEVEL:%d", bGInfo.level);
  print_rectangle(5, 7, 28, 48);
  move(6, 30);
  printw("SCORE:%d", bGInfo.score);
  print_rectangle(8, 10, 28, 48);
  move(9, 30);
  printw("MAXSCORE:%d", bGInfo.maxScore);

  print_rectangle(11, 15, 28, 48);
  move(12, 30);
  printw("NEXT FIGURE:");

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      mvaddch(i + 13, j * 2 + 30, ' ');
      mvaddch(i + 13, j * 2 + 1 + 30, ' ');
      if (bGInfo.nextFig->figureBlocks[i][j] == 1) {
        mvaddch(i + 13, j * 2 + 30, ACS_CKBOARD);
        mvaddch(i + 13, j * 2 + 1 + 30, ACS_CKBOARD);
      }
    }
  }
  move(17, 28);
  printw("Press DOWN for throw | Press UP for rotate");
  move(19, 28);
  printw("PRESS Q TO EXIT THIS TERRIBLE PROGRAM");

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (bGInfo.field[i][j] == 1) {
        mvaddch(i + 2, j * 2 + 1, ACS_CKBOARD);
        mvaddch(i + 2, j * 2 + 2, ACS_CKBOARD);
      } else {
        mvaddch(i + 2, j * 2 + 1, ' ');
        mvaddch(i + 2, j * 2 + 2, ' ');
      }
    }
  }
  for (int i = 0; i < bGInfo.fig->height; i++) {
    for (int j = 0; j < bGInfo.fig->width; j++) {
      if (bGInfo.field[bGInfo.yCoord + i][bGInfo.xCoord + j] == 1) {
        continue;
      }
      if (bGInfo.fig->figureBlocks[i][j] == 1) {
        mvaddch(bGInfo.yCoord + i + 2, (bGInfo.xCoord + j) * 2 + 1,
                ACS_CKBOARD);
        mvaddch(bGInfo.yCoord + i + 2, (bGInfo.xCoord + j) * 2 + 2,
                ACS_CKBOARD);
      }
    }
  }
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  for (int i = left_x; i <= right_x; i++) {
    mvaddch(top_y, i, ACS_HLINE);
    mvaddch(bottom_y, i, ACS_HLINE);
  }

  for (int i = top_y; i <= bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }

  mvaddch(top_y, left_x, ACS_ULCORNER);   // Верхний левый угол
  mvaddch(top_y, right_x, ACS_URCORNER);  // Верхний правый угол
  mvaddch(bottom_y, left_x, ACS_LLCORNER);  // Нижний левый угол
  mvaddch(bottom_y, right_x, ACS_LRCORNER);  // Нижний правый угол
}

void drawExitDialog() {
  print_rectangle(8, 14, 15, 55);
  for (int i = 0; i < 5; i++) {
    move(9 + i, 16);
    printw("                                      ");
  }
  move(10, 23);
  printw("Would you like play again?");
  move(12, 27);
  printw("Press Y for repeat");
}