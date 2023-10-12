#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef unsigned char u8;
typedef struct gconfig {
	int nrows;
	int ncols;
	int refreshTime;
	u8 population;
} gConfig;

#define min(a,b) \
   	({ __typeof__ (a) _a = (a); \
	 	__typeof__ (b) _b = (b); \
     		_a < _b ? _a : _b; })
#define max(a,b) \
   	({ __typeof__ (a) _a = (a); \
	 	__typeof__ (b) _b = (b); \
     		_a > _b ? _a : _b; })
#define GETVAL(board, nrows, i, j) (board[(i)*(ncols) + (j)])


int main(int argc, char *argv[]);
void boardInit(u8 *board, gConfig *config);
void boardPrint(u8 *board, gConfig *config, int nturns);
void playTurn(u8 *board, gConfig *config);
void mainLoop(u8 *board, gConfig *config);
int getConfig(gConfig *config, int argc, char *argv[]) ;
void leave(u8 *config);

