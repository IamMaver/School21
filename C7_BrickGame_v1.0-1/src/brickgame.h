#ifndef S21BRICKGAME
#define S21BRICKGAME
typedef struct {
  int figureBlocks[4][4];
  int height;
  int width;
} figure;

typedef struct {
  int field[20][10];
  figure *fig;
  figure *nextFig;
  int xCoord;
  int yCoord;
  int level;  // delay??
  int score;
  int maxScore;
} brickGameInfo;

void draw(brickGameInfo bGInfo);
void resetBGInfo(brickGameInfo *bGInfo);
void getNewFigure(figure *figure);
void copyFigure(figure *dst, figure *src);
int figureDescByOneString(brickGameInfo *bGInfo);
void putFigure2Field(brickGameInfo *bGInfo);
void tryMove2Left(brickGameInfo *bGInfo);
void tryMove2Right(brickGameInfo *bGInfo);
void tryRotate(brickGameInfo *bGInfo);
void checkStates(brickGameInfo *bGInfo);
int checkEndGame(brickGameInfo *bGInfo);
int getMaxScore();
void putMaxScore(int score);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void drawExitDialog();
#endif