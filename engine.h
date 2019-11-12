#include<stdio.h>
#include<stdlib.h>
#include "king.xbm"
#include "queen.xbm"
#include "rook.xbm"
#include "bishop.xbm"
#include "knight.xbm"
#include "pawn.xbm"
#include <X11/Xlib.h>
#include<Xm/Xm.h>
#include <assert.h>
#include <unistd.h>
#include<string.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#define NIL (0)
#define clear() printf("\033[H\033[J")

extern int board[8][8],tempboard[8][8],turn,color,row1,row2,column1,column2;
extern int white_qcastle,white_kcastle,black_kcastle,black_qcastle,castling;
extern char move[10],error[50];

typedef struct node{
  char piece;
  int r1,r2,c1,c2,number;
  double score;
  int tb[8][8];
  struct node *link;
}node;
node *moves,*level1,*level2,*level3,*level4,*level5;

typedef struct Node{
  int bd[8][8];
  int c,wqcastle,wkcastle,bqcastle,bkcastle,castle;
  struct Node *link;
}Node;
Node *history;

/* stack functions */
int isempty();
int push(int , int , int , int , char, int[8][8]);
int pop();
int print();

/* Board representation and move validation */
void update_castle();
void execute_move();
void print_board();
int validate_pawn(int ep);
int validate_rook();
int validate_knight();
int validate_bishop();
int validate_queen();
int validate_king();
int detect_check();
int detect_checkmate_and_stalemate();
void copy_board();
void make_new_board();
void get_move();
int validate_move();
int check_castle();
void validate_piece();
int convert(int c);
void loadgame();
void resetgame();
int detectdraw();

/*    Engine  */
void best_move();
int makemove();
int unmakemove();
int move_generator();
void heisenberg();
double evaluate(int , int , int , int ,int board[8][8]);

/*  Graphics */
void dolight();
void initGraphics();
void dodark();
void doboard();
void close_x();

/*  Sorting Algorithm */
void MergeSort(node** );
node* SortedMerge(node* , node* );
void FrontBackSplit(node* source, node** , node** );
