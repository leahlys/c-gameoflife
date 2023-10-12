#include "main.h"

void boardPrintNbCells(u8 *board,gConfig *config, int nturns);
void initGame(u8 **pboard, gConfig *config, int argc, char *argv[]);

int main(int argc, char *argv[]) {
	gConfig config;
	u8 *board;

	initGame(&board, &config, argc, argv);
	
	mainLoop(board, &config);

	return 0;
}

void initGame(u8 **pboard, gConfig *config, int argc, char *argv[]) {
	const int NROWS = 20;
	const int NCOLS = 50;

	initscr();

	(*config).nrows = NROWS;
	(*config).ncols = NCOLS;
	(*config).refreshTime = 500;
	(*config).population = 32;
	getConfig(config, argc, argv);

	*pboard=(u8 *) malloc(sizeof(u8)*(*config).nrows*(*config).ncols);
	boardInit( *pboard, config);
	keypad(stdscr, TRUE);
}

int getConfig(gConfig *config, int argc, char *argv[]) {
	for (int i=1; i+1<argc; i++) {
		if (!strncmp(argv[i],"-nrows",7)) {
			(*config).nrows = atoi(argv[++i]);
		} else if (!strncmp(argv[i],"-ncols",7)) {
			(*config).ncols = atoi(argv[++i]);
		} else if (!strncmp(argv[i],"-refreshtime",13)) {
			(*config).refreshTime = atoi(argv[++i]);
		} else if (!strncmp(argv[i],"-pop",5)) {
			(*config).population = atoi(argv[++i]);
		}
	}

	return 0;
}

void boardInit(u8 *board, gConfig *config) {
	int nrows = (*config).nrows;
	int ncols = (*config).ncols;
	for (int i=0;i<nrows;i++) {
		for (int j=0;j<ncols;j++) {
		GETVAL(board, ncols, i, j) = \
			((u8) rand() > (*config).population) ? 0 : 1;
		}
	}
}

void leave(u8 *board) {
	endwin();	
	free(board);
}

void mainLoop(u8 *board, gConfig *config) {
	int nturns = 0;

	while(1) {
		clear();
		//boardPrintNbCells( board, config, nturns); //DEBUG
		playTurn( board, config);
		boardPrint( board, config, nturns);
		refresh();
		//nanosleep(&ts, &ts);
		timeout((*config).refreshTime);
		int c = getch(); //DEBUG
		if (c == 'q') {leave(board); break;}
		nturns++;
	}
}

void playTurn(u8 *board, gConfig *config) {
	int nrows = (*config).nrows;
	int ncols = (*config).ncols;
	for (int i=0;i<nrows;i++) {
		for (int j=0;j<ncols;j++) {
		u8 nbCells = GETVAL(board, ncols, (i+1)%nrows, j)
			+ GETVAL(board, ncols, i, (j+1)%ncols)
			+ GETVAL(board, ncols, (i-1)%nrows, j)
			+ GETVAL(board, ncols, i, (j-1)%nrows)
			+ GETVAL(board, ncols, (i+1)%nrows, (j+1)%ncols)
			+ GETVAL(board, ncols, (i+1)%nrows, (j-1)%ncols)
			+ GETVAL(board, ncols, (i-1)%nrows, (j-1)%ncols)
			+ GETVAL(board, ncols, (i-1)%nrows, (j+1)%ncols);
		
		
		u8 newVal = (
			((GETVAL(board, ncols, i, j) == 1) && (
				(nbCells==2) || (nbCells==3)
				)) ||
			((GETVAL(board, ncols, i, j) == 0) && (nbCells==3))
			) ? 1 : 0;

		GETVAL(board, nrows, i, j) = newVal;
		}
	}
}

void boardPrint(u8 *board,gConfig *config, int nturns) {
	int nrows = (*config).nrows;
	int ncols = (*config).ncols;
	for (int i=0;i<nrows;i++) {
		for (int j=0;j<ncols;j++) {
		printw("%c", GETVAL(board, ncols, i, j) ? '@' : ' ');
		}
		printw("\n");
	}
	printw("\n");
	printw("TOUR %d\n", nturns);
}

void boardPrintNbCells(u8 *board,gConfig *config, int nturns) {
	int nrows = (*config).nrows;
	int ncols = (*config).ncols;
	for (int i=0;i<nrows;i++) {
		for (int j=0;j<ncols;j++) {
		u8 nbCells = GETVAL(board, nrows, (i+1)%nrows, j)
			+ GETVAL(board, nrows, i, (j+1)%ncols)
			+ GETVAL(board, nrows, (i-1)%nrows, j)
			+ GETVAL(board, nrows, i, (j-1)%nrows)
			+ GETVAL(board, nrows, (i+1)%nrows, (j+1)%ncols)
			+ GETVAL(board, nrows, (i+1)%nrows, (j-1)%ncols)
			+ GETVAL(board, nrows, (i-1)%nrows, (j-1)%ncols)
			+ GETVAL(board, nrows, (i-1)%nrows, (j+1)%ncols);
		printw("%d", nbCells);
		}
		printw("\n");
	}
	printw("\n");
	printw("TOUR %d\n", nturns);
}
