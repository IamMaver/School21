#include <ncurses.h>
#include <stdlib.h>

#include "../../brickgame.h"

int main() {
  WINDOW *mainwin = initscr();
  brickGameInfo bginfo;
  figure *curFigure = calloc(1, sizeof(figure));
  figure *nextFigure = calloc(1, sizeof(figure));

  do {
    resetBGInfo(&bginfo);
    bginfo.xCoord = 4;
    bginfo.yCoord = 0;
    getNewFigure(curFigure);
    bginfo.fig = curFigure;
    getNewFigure(nextFigure);
    bginfo.nextFig = nextFigure;
    bginfo.maxScore = getMaxScore();

    keypad(mainwin, TRUE);

    halfdelay(1);

    int input = 0;
    int currentDelay = 0;

    while (input != 'q' && !checkEndGame(&bginfo)) {
      draw(bginfo);
      input = wgetch(mainwin);

      if (input == KEY_LEFT) {
        tryMove2Left(&bginfo);
        input = 0;
      }
      if (input == KEY_RIGHT) {
        tryMove2Right(&bginfo);
        input = 0;
      }
      if (input == KEY_DOWN) {
        while (figureDescByOneString(&bginfo));
        copyFigure(bginfo.fig, bginfo.nextFig);
        getNewFigure(nextFigure);
        copyFigure(bginfo.nextFig, nextFigure);
        bginfo.xCoord = 4;
        bginfo.yCoord = 0;
      }
      if (input == KEY_UP) {
        tryRotate(&bginfo);
      }
      if (input == ' ') {
        nocbreak();
        wgetch(mainwin);
        halfdelay(1);
      }
      currentDelay++;
      if (currentDelay > 11 - bginfo.level) {
        if (figureDescByOneString(&bginfo) == 0) {
          copyFigure(bginfo.fig, bginfo.nextFig);
          getNewFigure(nextFigure);
          copyFigure(bginfo.nextFig, nextFigure);
          bginfo.xCoord = 4;
          bginfo.yCoord = 0;
        }
        currentDelay = 0;
      }
      checkStates(&bginfo);
    }
    if (bginfo.score > bginfo.maxScore) putMaxScore(bginfo.score);
    nocbreak();
    drawExitDialog();
  } while (wgetch(mainwin) == 'y');
  endwin();
  free(nextFigure);
  free(curFigure);
  return 0;
}

void resetBGInfo(brickGameInfo *bGInfo) {
  for (size_t i = 0; i <= sizeof(*bGInfo); i++) {
    *((char *)bGInfo + i) = 0;
  }
}

void getNewFigure(figure *figure) {
  switch (rand() % 7) {
    case 0:
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          if (i == 0) {
            figure->figureBlocks[i][j] = 1;
          } else {
            figure->figureBlocks[i][j] = 0;
          }
        }
      }
      figure->height = 1;
      figure->width = 4;
      break;
    case 1:
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          figure->figureBlocks[i][j] = 0;
        }
      }
      figure->figureBlocks[0][0] = 1;
      figure->figureBlocks[1][0] = 1;
      figure->figureBlocks[1][1] = 1;
      figure->figureBlocks[1][2] = 1;
      figure->height = 2;
      figure->width = 3;
      break;
    case 2:
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          figure->figureBlocks[i][j] = 0;
        }
      }
      figure->figureBlocks[0][2] = 1;
      figure->figureBlocks[1][0] = 1;
      figure->figureBlocks[1][1] = 1;
      figure->figureBlocks[1][2] = 1;
      figure->height = 2;
      figure->width = 3;
      break;
    case 3:
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          figure->figureBlocks[i][j] = 0;
        }
      }
      figure->figureBlocks[0][0] = 1;
      figure->figureBlocks[0][1] = 1;
      figure->figureBlocks[1][0] = 1;
      figure->figureBlocks[1][1] = 1;
      figure->height = 2;
      figure->width = 2;
      break;
    case 4:
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          figure->figureBlocks[i][j] = 0;
        }
      }
      figure->figureBlocks[0][1] = 1;
      figure->figureBlocks[0][2] = 1;
      figure->figureBlocks[1][0] = 1;
      figure->figureBlocks[1][1] = 1;
      figure->height = 2;
      figure->width = 3;
      break;
    case 5:
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          figure->figureBlocks[i][j] = 0;
        }
      }
      figure->figureBlocks[0][1] = 1;
      figure->figureBlocks[1][0] = 1;
      figure->figureBlocks[1][1] = 1;
      figure->figureBlocks[1][2] = 1;
      figure->height = 2;
      figure->width = 3;
      break;
    case 6:
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          figure->figureBlocks[i][j] = 0;
        }
      }
      figure->figureBlocks[0][0] = 1;
      figure->figureBlocks[0][1] = 1;
      figure->figureBlocks[1][1] = 1;
      figure->figureBlocks[1][2] = 1;
      figure->height = 2;
      figure->width = 3;
      break;
  }
}

void copyFigure(figure *dst, figure *src) {
  dst->height = src->height;
  dst->width = src->width;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      dst->figureBlocks[i][j] = src->figureBlocks[i][j];
    }
  }
}

int figureDescByOneString(brickGameInfo *bGInfo) {
  if (bGInfo->yCoord == 20 - bGInfo->fig->height) {
    putFigure2Field(bGInfo);
    return 0;
  }
  for (int j = 0; j < bGInfo->fig->width; j++) {
    for (int i = 0; i < bGInfo->fig->height; i++) {
      if ((bGInfo->fig->figureBlocks[i][j] == 1) &&
          (bGInfo->field[i + 1 + bGInfo->yCoord][j + bGInfo->xCoord] == 1)) {
        putFigure2Field(bGInfo);
        return 0;
      }
    }
  }
  bGInfo->yCoord++;
  return 1;
}

void putFigure2Field(brickGameInfo *bGInfo) {
  for (int i = 0; i < bGInfo->fig->height; i++) {
    for (int j = 0; j < bGInfo->fig->width; j++) {
      if (bGInfo->fig->figureBlocks[i][j] == 1) {
        bGInfo->field[bGInfo->yCoord + i][bGInfo->xCoord + j] = 1;
      }
    }
  }
}

void tryMove2Left(brickGameInfo *bGInfo) {
  if (bGInfo->xCoord == 0) return;
  for (int j = 0; j < bGInfo->fig->width; j++) {
    for (int i = 0; i < bGInfo->fig->height; i++) {
      if ((bGInfo->fig->figureBlocks[i][j] == 1) &&
          (bGInfo->field[i + bGInfo->yCoord][j - 1 + bGInfo->xCoord] == 1)) {
        return;
      }
    }
  }
  bGInfo->xCoord--;
}

void tryMove2Right(brickGameInfo *bGInfo) {
  if (bGInfo->xCoord + bGInfo->fig->width == 10) return;
  for (int j = 0; j < bGInfo->fig->width; j++) {
    for (int i = 0; i < bGInfo->fig->height; i++) {
      if ((bGInfo->fig->figureBlocks[i][j] == 1) &&
          (bGInfo->field[i + bGInfo->yCoord][j + 1 + bGInfo->xCoord] == 1)) {
        return;
      }
    }
  }
  bGInfo->xCoord++;
}

void tryRotate(brickGameInfo *bGInfo) {
  figure dst;
  dst.width = bGInfo->fig->height;
  dst.height = bGInfo->fig->width;
  if (bGInfo->yCoord + bGInfo->fig->height > 19 ||
      bGInfo->yCoord + bGInfo->fig->width > 19)
    return;
  if (dst.width != dst.height) {
    if (dst.width == 4 || dst.height == 4) {
      for (int i = 0; i < 4; i++) {
        dst.figureBlocks[i][0] = bGInfo->fig->figureBlocks[0][i];
        dst.figureBlocks[0][i] = bGInfo->fig->figureBlocks[i][0];
      }
    } else {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          dst.figureBlocks[i][j] =
              bGInfo->fig->figureBlocks[2 - j][(3 + i) % 3];
        }
      }

      if (!dst.figureBlocks[0][0] && !dst.figureBlocks[0][1] &&
          !dst.figureBlocks[0][2]) {
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            if (i < 2) {
              dst.figureBlocks[i][j] = dst.figureBlocks[(i + 1) % 3][j];
            } else {
              dst.figureBlocks[i][j] = 0;
            }
          }
        }
      }
      if (!dst.figureBlocks[0][0] && !dst.figureBlocks[1][0] &&
          !dst.figureBlocks[2][0]) {
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            if (j < 2) {
              dst.figureBlocks[i][j] = dst.figureBlocks[i][(j + 1) % 3];
            } else {
              dst.figureBlocks[i][j] = 0;
            }
          }
        }
      }
    }
    copyFigure(bGInfo->fig, &dst);
  }
}

void checkStates(brickGameInfo *bGInfo) {
  int deletedLines = 0;
  for (int i = 0; i < 20; i++) {
    int brickInLine = 0;
    for (int j = 0; j < 10; j++) {
      brickInLine += bGInfo->field[i][j];
    }
    if (brickInLine == 10) {
      for (int k = i; k > 0; k--) {
        for (int j = 0; j < 10; j++) {
          bGInfo->field[k][j] = bGInfo->field[k - 1][j];
        }
      }
      deletedLines++;
    }
  }
  switch (deletedLines) {
    case 1:
      bGInfo->score += 100;
      break;
    case 2:
      bGInfo->score += 300;
      break;
    case 3:
      bGInfo->score += 700;
      break;
    case 4:
      bGInfo->score += 1500;
      break;
  }
  if (bGInfo->level < 11) {
    bGInfo->level = bGInfo->score / 600;
    if (bGInfo->level > 10) {
      bGInfo->level = 10;
    }
  }
}

int checkEndGame(brickGameInfo *bGInfo) {
  int endGame = 0;
  for (int i = 0; i < bGInfo->fig->height; i++) {
    for (int j = 0; j < bGInfo->fig->width; j++) {
      if (bGInfo->fig->figureBlocks[i][j] == 1 &&
          bGInfo->field[bGInfo->yCoord + i][bGInfo->xCoord + j] == 1) {
        endGame = 1;
      }
    }
  }
  return endGame;
}

int getMaxScore() {
  FILE *fp = fopen("tetris.ini", "r");
  if (fp == NULL) {
    return 0;
  }
  int score = 0;
  fscanf(fp, "%d", &score);
  fclose(fp);
  return score;
}

void putMaxScore(int score) {
  FILE *fp = fopen("tetris.ini", "w");
  if (fp == NULL) {
    return;
  }
  fprintf(fp, "%d", score);
  fclose(fp);
  return;
}