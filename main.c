/*********************************************************
                  DSA Project : Chess

Author : Soham Parekh
         College of Engineering, Pune
MIS    : 111803137

**************************************************************/

#include "engine.h"

/*Global Variables*/
int board[8][8],tempboard[8][8],color=1,row1,row2,column1,column2;
int prow1=0,prow2=0,pcolumn1=0,pcolumn2=0;  //for enpassant
int white_qcastle=1,white_kcastle=1,black_kcastle=1,black_qcastle=1,castling=0;
int fiftycounter=0,totalcount=0,reps=0,brep1[8][8],brep2[8][8],dd=1;  //for draws
char move[10],error[50];

/*Graphical Allocations */
Pixmap wking_pm,wqueen_pm,wpawn_pm,wknight_pm,wbishop_pm;
Pixmap wrook_pm,bking_pm,bqueen_pm,bpawn_pm,bknight_pm,bbishop_pm,brook_pm ;
Window w;
Display *dpy;
GC gc;
int screen;
char text[255];
Pixel bg,fg;
Font font;
Screen *s;
int dark,light,whiteColor,blackColor;  //colors used in program

/*Functions for Graphics*/
void initGraphics(){
  dpy = XOpenDisplay(NIL);
  assert(dpy);
  XColor tmp;   //lightgoldenrodolive
  XParseColor(dpy, DefaultColormap(dpy,screen), "peachpuff", &tmp);
  XAllocColor(dpy,DefaultColormap(dpy,screen),&tmp);
  light=tmp.pixel;
  XParseColor(dpy, DefaultColormap(dpy,screen), "peru", &tmp);
  XAllocColor(dpy,DefaultColormap(dpy,screen),&tmp);
  dark=tmp.pixel;
  blackColor = BlackPixel(dpy, DefaultScreen(dpy));
  whiteColor = WhitePixel(dpy, DefaultScreen(dpy));
  w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0,900, 900, 0, blackColor, blackColor);
  XSelectInput(dpy, w, StructureNotifyMask|ExposureMask|ButtonPressMask|KeyPressMask);
  XMapWindow(dpy, w);
  font = XLoadFont(dpy, "*x20");
  gc = XCreateGC(dpy, w, 0, NIL);
  XSetFont(dpy,gc, font);
  s=DefaultScreenOfDisplay(dpy);
  fg=XBlackPixelOfScreen(s);
  bg=XWhitePixelOfScreen(s);
  wking_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whiteking, 60, 60, fg, bg,DefaultDepthOfScreen(s)) ;
  wqueen_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whitequeen, 60, 56, fg, bg,DefaultDepthOfScreen(s)) ;
  wpawn_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whitepawn, 60, 60, fg, bg,DefaultDepthOfScreen(s)) ;
  wknight_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whiteknight, 60, 60, fg, bg,DefaultDepthOfScreen(s)) ;
  wbishop_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whitebishop, 60, 60, fg, bg,DefaultDepthOfScreen(s)) ;
  wrook_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whiterook, 60, 60, fg, bg,DefaultDepthOfScreen(s)) ;
  bking_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whiteking, 60, 60, bg, fg,DefaultDepthOfScreen(s)) ;
  bqueen_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whitequeen, 60, 56,bg,fg,DefaultDepthOfScreen(s)) ;
  bpawn_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whitepawn, 60, 60, bg, fg,DefaultDepthOfScreen(s)) ;
  bknight_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whiteknight, 60, 60, bg, fg,DefaultDepthOfScreen(s)) ;
  bbishop_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whitebishop, 60, 60, bg, fg,DefaultDepthOfScreen(s)) ;
  brook_pm = XCreatePixmapFromBitmapData(dpy, RootWindowOfScreen(s), whiterook, 60, 60, bg, fg,DefaultDepthOfScreen(s)) ;
}   //completes all initialisation work
void dolight(){
  int i=0,j=0;
  for(i=0,j=0;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=100,j=100;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=100,j=300;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=100,j=500;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=100,j=700;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=0,j=200;i<800;i+=200){
  XFillRectangle(dpy,w,gc, i, j, 100,100);
  }
  for(i=0,j=400;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=0,j=600;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
}  //draws the light squares on the screen
void dodark(){
  int i,j;
  for(i=0,j=100;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=0,j=300;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=0,j=500;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=0,j=700;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=100,j=0;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=100,j=200;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=100,j=400;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
  for(i=100,j=600;i<800;i+=200){
  XFillRectangle(dpy, w, gc,i,j, 100, 100);
  }
} //draws the dark squares on the screen
void doboard(){
  int i,j;
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      if(board[i][j]>0){
        if(board[i][j]==100)
          XCopyArea(dpy,wpawn_pm,w,gc,0,0,60,60,j*100+20,i*100+20);
        else if(board[i][j]==300)
          XCopyArea(dpy,wknight_pm,w,gc,0,0,60,60,j*100+20,i*100+20);
        else if(board[i][j]==400)
          XCopyArea(dpy,wbishop_pm,w,gc,0,0,60,60,j*100+20,i*100+20);
        else if(board[i][j]==500)
          XCopyArea(dpy,wrook_pm,w,gc,0,0,60,60,j*100+20,i*100+20);
        else if(board[i][j]==900)
          XCopyArea(dpy,wqueen_pm,w,gc,0,0,60,56,j*100+20,i*100+20);
        else if(board[i][j]==10000)
          XCopyArea(dpy,wking_pm,w,gc,0,0,60,60,j*100+20,i*100+20);
        XSetForeground(dpy,gc,whiteColor);
        //XDrawString(dpy,w,gc,j*100+20,i*100+50, text, strlen(text));
      }
      else if(board[i][j]<0){
        if(board[i][j]==-100)
          XCopyArea(dpy,bpawn_pm,w,gc,0,0,60,60,j*100+20,i*100+20);
        else if(board[i][j]==-300)
          XCopyArea(dpy,bknight_pm,w,gc,0,0,60,60,j*100+20,i*100+20);
        else if(board[i][j]==-400)
          XCopyArea(dpy,bbishop_pm,w,gc,0,0,60,60,j*100+20,i*100+20);
        else if(board[i][j]==-500)
          XCopyArea(dpy,brook_pm,w,gc,0,0,60,60,j*100+20,i*100+20);
        else if(board[i][j]==-900)
          XCopyArea(dpy,bqueen_pm,w,gc,0,0,60,56,j*100+20,i*100+20);
        else if(board[i][j]==-10000)
          XCopyArea(dpy,bking_pm,w,gc,0,0,60,60,j*100+20,i*100+20);
        XSetForeground(dpy,gc,blackColor);
        //XDrawString(dpy,w,gc,j*100+20,i*100+50, text, strlen(text));
      }
    }
  }
} //copies the pieces on the board from the pixmaps
void close_x() {
    	XFreeGC(dpy, gc);
    	XDestroyWindow(dpy,w);
    	XCloseDisplay(dpy);
    	exit(1);
}  //frees all the resources

int detect_checkmate_and_stalemate(){
  move_generator();
  if(isempty()){
  if(detect_check(0)){
      return 1;
    }
    else{
      return 2;
    }
  }
  while(!isempty()){
    pop();
  }
  return 0;
}  //detects checkmate and stalemate on board
void update_castle(){
  if(board[7][7]!=500){
    white_kcastle=0;
  }
  if(board[7][0]!=500){
    white_qcastle=0;
  }
  if(board[7][4]!=10000){
    white_kcastle=0;
    white_qcastle=0;
  }
  if(board[0][7]!=-500){
    black_kcastle=0;
  }
  if(board[0][0]!=-500){
    black_qcastle=0;
  }
  if(board[0][4]!=-10000){
    black_kcastle=0;
    black_qcastle=0;
  }
}   //stores whether castling is allowed
void copy_board(){
  int i,j;
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      tempboard[i][j]=board[i][j];
    }
  }
}  //copies global board into a temporaryboard
void savemove(){
  FILE *fp;
  fp=fopen("savedgame.txt","a+");
  fprintf(fp,"%d\n",color);
  fprintf(fp,"%c\n",move[0]);
  fprintf(fp,"%d\n",row1);
  fprintf(fp,"%d\n",column1);
  fprintf(fp,"%d\n",row2);
  fprintf(fp,"%d\n",column2);
  fclose(fp);
}   //saves move in file
void execute_move(){
  if(board[row1][column1]==100||board[row1][column1]==-100){
    fiftycounter=-1;
  }
  if(color==1){
    if(board[row2][column2]<0){
      fiftycounter=-1;
    }
  }
  else{
    if(board[row2][column2]>0){
      fiftycounter=-1;
    }
  }
  fiftycounter++;
  totalcount++;
  board[row2][column2]=board[row1][column1];
  board[row1][column1]=0;
  prow1=row1;
  prow2=row2;
  pcolumn1=column1;
  pcolumn2=column2;
  if(castling==1){
    printf("Entered castling\n");
    if(row2==0&&column2==2){
      board[0][0]=0;
      board[0][3]=-500;
    }
    else if(row2==0&&column2==6){
      board[0][5]=-500;
      board[0][7]=0;
    }
    else if(row2==7&&column2==2){
      board[7][0]=0;
      board[7][3]=500;
    }
    else if(row2==7&&column2==6){
      board[7][5]=500;
      board[7][7]=0;
    }
  }
  update_castle();
  if(color==1){
    color=2;
  }
  else{
    color=1;
  }
  return;
}   //executes move[]
int check_castle(){
  if(detect_check(0)){
    return 0;
  }
  if(color==1){
    if(row1==row2&&column1==4&&column2==6){
      if(board[7][5]==0&&board[7][6]==0){
        board[7][5]=10000;
        board[7][4]=0;
        if(detect_check(0)){
          board[7][5]=0;
          board[7][4]=10000;
          return 0;
        }
        board[7][6]=10000;
        board[7][5]=0;
        if(detect_check(0)){
          board[7][6]=0;
          board[7][4]=10000;
          return 0;
        }
        board[7][5]=0;    //all positions in between are checked and the initial position is brought
        board[7][6]=0;
        board[7][4]=10000;
        return 1;
      }
      else{
        return 0;
      }
    }
    else{
      if(board[7][3]==0&&board[7][2]==0&&board[7][1]==0){
        board[7][3]=10000;
        board[7][4]=0;
        if(detect_check(0)){
          board[7][3]=0;
          board[7][4]=10000;
          return 0;
        }
        board[7][2]=10000;
        board[7][3]=0;
        if(detect_check(0)){
          board[7][4]=10000;
          board[7][2]=0;
          return 0;
        }
        board[7][1]=10000;
        board[7][2]=0;
        if(detect_check(0)){
          board[7][4]=10000;
          board[7][1]=0;
          return 0;
        }
        board[7][3]=0;
        board[7][2]=0;
        board[7][1]=0;
        board[7][4]=10000;
        return 1;
      }
      else{
        return 0;
      }
    }
  }
  else{
    if(row1==row2&&column1==4&&column2==6){
      if(board[0][5]==0&&board[0][6]==0){
        board[0][5]=-10000;
        board[0][4]=0;
        if(detect_check(0)){
          board[0][5]=0;
          board[0][4]=-10000;
          return 0;
        }
        board[0][6]=-10000;
        board[0][5]=0;
        if(detect_check(0)){
          board[0][6]=0;
          board[0][4]=-10000;
          return 0;
        }
        board[0][5]=0;
        board[0][6]=0;
        board[0][4]=-10000;
        return 1;
      }
      else{
        return 0;
      }
    }
    else{
      if(board[0][3]==0&&board[0][2]==0&&board[0][1]==0){
        board[0][3]=-10000;
        board[0][4]=0;
        if(detect_check(0)){
          board[0][3]=0;
          board[0][4]=-10000;
          return 0;
        }
        board[0][2]=-10000;
        board[0][3]=0;
        if(detect_check(0)){
          board[0][4]=-10000;
          board[0][2]=0;
          return 0;
        }
        board[0][1]=-10000;
        board[0][2]=0;
        if(detect_check(0)){
          board[0][4]=-10000;
          board[0][1]=0;
          return 0;
        }
        board[0][4]=-10000;
        board[0][1]=0;
        board[0][2]=0;
        board[0][3]=0;
        return 1;
      }
      else{
        return 0;
      }
    }
  }
} //checks if castling is allowed by executing intermediate positions
int detect_check(int simple){
  copy_board(); //if simple is 1, then move to be executed
  int i,j,king_row,king_column,flag=0;
  if(simple){
  tempboard[row2][column2]=board[row1][column1];
  tempboard[row1][column1]=0;   //executed move on temporary board
  }
  if(color==1){
    for(i=0;i<8;i++){
      for(j=0;j<8;j++){
        if(tempboard[i][j]==10000){
          king_row=i;
          king_column=j;
          break;
        }
      }
    }
  }
  else if(color==2){
    for(i=0;i<8;i++){
      for(j=0;j<8;j++){
        if(tempboard[i][j]==-10000){
          king_row=i;
          king_column=j;
          break;
        }
      }
    }
  }
  //gotten position of king on board
  i=0;
  j=0;
  if(color==1){       //to check 8 possible positions of knight
    i=king_row-1;
    j=king_column+2;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==-300){
        return 1;
      }
    }
    j=king_column-2;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==-300){
        return 1;
      }
    }
    i=king_row+1;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==-300){
        return 1;
      }
    }
    j=king_column+2;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==-300){
        return 1;
      }
    }
    i=king_row+2;
    j=king_column+1;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==-300){
        return 1;
      }
    }
    j=king_column-1;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==-300){
        return 1;
      }
    }
    i=king_row-2;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==-300){
        return 1;
      }
    }
    j=king_column+1;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==-300){
        return 1;
      }
    }     //all 8 knight combinations checked
    i=king_row+1;
    j=king_column+1;           //lower right bishop and queen test
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==-900){
          return 1;
        }
        if(tempboard[i][j]==-400){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i++;
        j++;
      }
    }
    i=king_row-1;       //upper right bishop and queen test
    j=king_column+1;
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==-900){
          return 1;
        }
        if(tempboard[i][j]==-400){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i--;
        j++;
      }
    }
    i=king_row-1;
    j=king_column-1;     //upper left bishop and queen test
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==-900){
          return 1;
        }
        if(tempboard[i][j]==-400){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i--;
        j--;
      }
    }
    i=king_row+1;        //lower left bishop and queen test
    j=king_column-1;
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==-900){
          return 1;
        }
        if(tempboard[i][j]==-400){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i++;
        j--;
      }
    }
    i=king_row+1;
    j=king_column;
    if(i<8&&i>=0&&j<8&&j>=0){    //bottom test for rook and queen
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==-900){
          return 1;
        }
        if(tempboard[i][j]==-500){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i++;
      }
    }
    i=king_row-1;
    if(i<8&&i>=0&&j<8&&j>=0){    //upper test for rook and queen
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==-900){
          return 1;
        }
        if(tempboard[i][j]==-500){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i--;
      }
    }
    i=king_row;
    j=king_column-1;    //left test for rook and queen
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==-900){
          return 1;
        }
        if(tempboard[i][j]==-500){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        j--;
      }
    }
    j=king_column+1;   //right test for rook and queen
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==-900){
          return 1;
        }
        if(tempboard[i][j]==-500){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        j++;
      }
    }
    i=king_row-1;
    j=king_column+1;    //checking both sides for pawns
    if(tempboard[i][j]==-100){
      return 1;
    }
    j=king_column-1;
    if(tempboard[i][j]==-100){
      return 1;
    }
  }
  else{       //to check 8 possible positions of knight
    i=king_row-1;
    j=king_column+2;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==300){
        return 1;
      }
    }
    j=king_column-2;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==300){
        return 1;
      }
    }
    i=king_row+1;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==300){
        return 1;
      }
    }
    j=king_column+2;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==300){
        return 1;
      }
    }
    i=king_row+2;
    j=king_column+1;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==300){
        return 1;
      }
    }
    j=king_column-1;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==300){
        return 1;
      }
    }
    i=king_row-2;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==300){
        return 1;
      }
    }
    j=king_column+1;
    if(i<8&&i>=0&&j<8&&j>=0){
      if(tempboard[i][j]==300){
        return 1;
      }
    }     //all 8 knight combinations checked
    i=king_row+1;
    j=king_column+1;           //lower right bishop and queen test
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==900){
          return 1;
        }
        if(tempboard[i][j]==400){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i++;
        j++;
      }
    }
    i=king_row-1;       //upper right bishop and queen test
    j=king_column+1;
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==900){
          return 1;
        }
        if(tempboard[i][j]==400){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i--;
        j++;
      }
    }
    i=king_row-1;
    j=king_column-1;     //upper left bishop and queen test
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==900){
          return 1;
        }
        if(tempboard[i][j]==400){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i--;
        j--;
      }
    }
    i=king_row+1;        //lower left bishop and queen test
    j=king_column-1;
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==900){
          return 1;
        }
        if(tempboard[i][j]==400){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i++;
        j--;
      }
    }
    i=king_row+1;
    j=king_column;
    if(i<8&&i>=0&&j<8&&j>=0){    //bottom test for rook and queen
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==900){
          return 1;
        }
        if(tempboard[i][j]==500){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i++;
      }
    }
    i=king_row-1;
    if(i<8&&i>=0&&j<8&&j>=0){    //upper test for rook and queen
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==900){
          return 1;
        }
        if(tempboard[i][j]==500){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        i--;
      }
    }
    i=king_row;
    j=king_column-1;    //left test for rook and queen
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==900){
          return 1;
        }
        if(tempboard[i][j]==500){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        j--;
      }
    }
    j=king_column+1;   //right test for rook and queen
    if(i<8&&i>=0&&j<8&&j>=0){
      for(;i<8&&j<8&&i>=0&&j>=0;){
        if(tempboard[i][j]==900){
          return 1;
        }
        if(tempboard[i][j]==500){
          return 1;
        }
        if(tempboard[i][j]!=0){
          break;
        }
        j++;
      }
    }
    i=king_row+1;
    j=king_column+1;    //checking both sides for pawns
    if(tempboard[i][j]==100){
      return 1;
    }
    j=king_column-1;
    if(tempboard[i][j]==100){
      return 1;
    }
  }
  return 0;
}  //detects whether king is under check
void make_new_board(){
  int i,j;
  for(i=0;i<8;i++){
    board[1][i]=-100;
    board[6][i]=100;
  }
  board[0][0]=-500;
  board[0][7]=-500;
  board[0][1]=-300;
  board[0][6]=-300;
  board[0][5]=-400;
  board[0][2]=-400;
  board[0][3]=-900;
  board[0][4]=-10000;
  board[7][0]=500;
  board[7][7]=500;
  board[7][1]=300;
  board[7][6]=300;
  board[7][5]=400;
  board[7][2]=400;
  board[7][3]=900;
  board[7][4]=10000;
} //makes a new board
void loadgame(){
  int ck;
  char lol,brk;
  FILE *fp;
  castling=0;
  fp=fopen("savedgame.txt","a+");
  printf("The game am loading is \n");
  while(fscanf(fp,"%d",&ck)!=EOF){
    color=ck;
    fscanf(fp,"%c",&brk);
    fscanf(fp,"%c",&lol);
    fscanf(fp,"%c",&brk);
    fscanf(fp,"%d",&row1);
    fscanf(fp,"%c",&brk);
    fscanf(fp,"%d",&column1);
    fscanf(fp,"%c",&brk);
    fscanf(fp,"%d",&row2);
    fscanf(fp,"%c",&brk);
    fscanf(fp,"%d",&column2);
    fscanf(fp,"%c",&brk);
    printf("%c%d%d%d%d\n",lol,row1,column1,row2,column2);
    if(lol=='K'&&row1==7&&row2==7&&column1==4&&(column2==6||column2==4)){
      castling=1;
    }
    execute_move();
    totalcount++;
  }
  fclose(fp);
} //loads pre saved game from file
void resetgame(){
  FILE *fp;
  fp=fopen("savedgame.txt","w");
  fclose(fp);
} //resets saved game
int detectdraw(){
  int wbishop=0,wknight=0,bbishop=0,bknight=0,i,j,flag=0;
  if(totalcount%4==0){  //after black move for threefold repetition
    if(dd==1){
      for(i=0;i<8;i++){
        for(j=0;j<8;j++){
          brep1[i][j]=board[i][j];
        }
      }
      dd++;
    }
    else if(dd==2){
      for(i=0;i<8;i++){
        for(j=0;j<8;j++){
          brep2[i][j]=board[i][j];
        }
      }
      dd++;
    }
    else{
      for(i=0;i<8;i++){
        for(j=0;j<8;j++){
           if(brep1[i][j]!=board[i][j]){
             flag=1;
          }
          if(brep1[i][j]!=brep2[i][j]){
            flag=1;
          }
        }
      }
      if(flag==0){
        printf("Draw by threefold repetition\n");
        return 1;
      }
      else{
        for(i=0;i<8;i++){
          for(j=0;j<8;j++){
            brep1[i][j]=brep2[i][j];
            brep2[i][j]=board[i][j];
          }
        }
        dd++;
      }
    }
  }
  if(fiftycounter==50){    //handles 50 move rule
    return 1;
  }
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      if(board[i][j]==0){
        continue;
      }
      else if(board[i][j]==300){
        wknight++;
      }
      else if(board[i][j]==400){
        wbishop++;
      }
      else if(board[i][j]==-300){
        bknight++;
      }
      else if(board[i][j]==-400){
        bbishop++;
      }
      else{
        return 0;
      }
    }
  }
  if(bbishop==0&&wbishop==0){
    return 1;
  }
  if((bbishop+bknight>=2) || (wbishop+wknight>=2)){
    return 0;
  }
  else{
    return 1;
  }
}
/*Functions for Validating User Entered Move*/
int convert(int c){
  if(c>0&&c<=100){
  return 0;
  }
  else if(c>100&&c<=200){
    return 1;
  }
  else if(c>200&&c<=300){
    return 2;
  }
  else if(c>300&&c<=400){
    return 3;
  }
  else if(c>400&&c<=500){
    return 4;
  }
  else if(c>500&&c<=600){
    return 5;
  }
  else if(c>600&&c<=700){
    return 6;
  }
  else if(c>700&&c<=800){
    return 7;
  }
  return -1;
}     //converts co ordinates to indices
void get_move(){
  if(board[row1][column1]==100||board[row1][column1]==-100){
    move[0]='P';
  }
  else if(board[row1][column1]==300||board[row1][column1]==-300){
    move[0]='N';
  }
  else if(board[row1][column1]==400||board[row1][column1]==-400){
    move[0]='B';
  }
  else if(board[row1][column1]==500||board[row1][column1]==-500){
    move[0]='R';
  }
  else if(board[row1][column1]==900||board[row1][column1]==-900){
    move[0]='Q';
  }
  else if(board[row1][column1]==10000||board[row1][column1]==-10000){
    move[0]='K';
  }
  move[1]=row1;
  move[2]=column1;
  move[3]=row2;
  move[4]=column2;
}        //generates the move from data entered by user
int validate_move(){
  int i,flag=0;
  castling=0;
  if(move[0]=='K'&&row1==row2&&column1==4&&column2==6){
    if(color==1){
      if(white_kcastle==1){
        return 1;
      }
    }
    else if(color==2){
      if(black_kcastle==1){
        return 1;
      }
    }
    else{
      return 0;
    }
  }
  else if(move[0]=='K'&&row1==row2&&column1==4&&column2==2){
    if(color==1){
      if(white_qcastle==1){
        return 1;
      }
      else{
        return 0;
      }
    }
    else if(color==2){
      if(black_qcastle==1){
        return 1;
      }
      else {
        return 0;
      }
    }
    else{
      return 0;
    }
  }
  else;
  if(strlen(move)!=5){
    flag=1;
  }
  if(move[0]!='P'&&move[0]!='K'&&move[0]!='Q'&&move[0]!='N'&&move[0]!='B'&&move[0]!='R'){
    strcpy(error,"Piece is invalid");
    flag=1;
  }
  if((row1==row2)&&(column1==column2)){
    strcpy(error,"Same square cant be given as new square");
    flag=1;
  }
  if(board[row1][column1]==0){
    strcpy(error,"Square you chose is empty");
    flag=1;
  }
  if(color==1){
    if(board[row1][column1]<0){
      strcpy(error,"Piece you chose is wrong color");
      flag=1;
    }
  }
  if(color==2){
    if(board[row1][column1]>0){
      strcpy(error,"Piece you chose is wrong color");
      flag=1;
    }
  }
  if(flag==1){
    return 0;
  }
  else{
    return 1;
  }
}    //validates user input move
void validate_piece(){
  int result=0;
  char ch;
  if(move[0]=='K'&&row1==row2&&column1==4&&column2==6){
    result=validate_king();
    if(result){
      savemove();
      execute_move();
      return;
    }
  }
  else if(move[0]=='K'&&row1==row2&&column1==4&&column2==6){ //kingside castle
    result=validate_king();
    if(result){
      savemove();
      execute_move();
      return;
    }
  }
  else if(move[0]=='P'&&(board[row1][column1]==100||board[row1][column1]==-100)){
    result=validate_pawn(1);
    if(result){
      savemove();
      execute_move();
      return;
    }
  }
  else if(move[0]=='R'&&(board[row1][column1]==500||board[row1][column1]==-500)){
    result=validate_rook();
    if(result){
      savemove();
      execute_move();
      return;
    }
  }
  else if(move[0]=='N'&&(board[row1][column1]==300||board[row1][column1]==-300)){
    result=validate_knight();
    if(result){
      savemove();
      execute_move();
      return;
    }
  }
  else if(move[0]=='B'&&(board[row1][column1]==400||board[row1][column1]==-400)){
    result=validate_bishop();
    if(result){
      savemove();
      execute_move();
      return;
    }
  }
  else if(move[0]=='Q'&&(board[row1][column1]==900||board[row1][column1]==-900)){
    result=validate_queen();
    if(result){
      savemove();
      execute_move();
      return;
    }
  }
  else if(move[0]=='K'&&(board[row1][column1]==10000||board[row1][column1]==-10000)){
    result=validate_king();
    if(result){
      savemove();
      execute_move();
    }
    return;
  }
  if(result==0){
    printf("Nothing was done as invalid move. \n%s\n",error);
  }
}  //validation  of particular piece, calls other functions
int validate_pawn(int ep){
  char piece;
  if(((color==1)&&(row2-row1==-2)&&(column1==column2))||((color==2)&&(row2-row1==2)&&(column1==column2))){ //for double move of white or black
    if(color==1){   //it is a white pawn
      if((row1==6)&&(board[row1-1][column1]==0)&&board[row2][column2]==0){     //White pawn is in beginning position and nothing is in between
        if(!detect_check(1)){
          return 1;
        }
        else{
          strcpy(error,"King is under Check");
          return 0;
        }
      }
      else{
        return 0;
      }
    }
    else if(color==2){     //it is a black pawn
      if((row1==1)&&(board[row1+1][column1]==0)&&board[row2][column2]==0){   //black pawn is in beginning position and nothing is in between
        if(!detect_check(1)){
          return 1;
        }
        else{
          strcpy(error,"King is under Check");
          return 0;
        }
      }
      else{
        return 0;
      }
    }
  }
  else if(((color==1)&&(row2-row1==-1)&&(column1==column2))||((color==2)&&(row2-row1==1)&&(column1==column2))){ //for single get_move
    if(color==1){   //color is white and single move forward
      if(board[row1-1][column1]==0){ //new square is empty
        if(!detect_check(1)){
          if(row2==0){
            do{
              printf("Which piece do you want to promote to?\n");
              scanf(" %c",&piece);
            }
            while(piece!='Q'&&piece!='N'&&piece!='R'&&piece!='B');
            if(piece=='Q'){
              board[row1][column1]=900;
              }
            else if(piece=='R'){
              board[row1][column1]=500;
            }
            else if(piece=='N'){
              board[row1][column1]=300;
            }
            else if(piece=='B'){
              board[row1][column1]=400;
            }
          }
          return 1;
        }
        else{
          strcpy(error,"King is under Check");
          return 0;
        }
      }
      else{    //new square is occupied
        return 0;
      }
    }
    else{    //color is black and single move forward
      if(board[row1+1][column1]==0){   //new square is empty
        if(!detect_check(1)){
          if(row2==7){
            do{
              printf("Which piece do you want to promote to?\n");
              scanf(" %c",&piece);
            }
            while(piece!='Q'&&piece!='N'&&piece!='R'&&piece!='B');
            if(piece=='Q'){
              board[row1][column1]=-900;
              }
            else if(piece=='R'){
              board[row1][column1]=-500;
            }
            else if(piece=='N'){
              board[row1][column1]=-300;
            }
            else if(piece=='B'){
              board[row1][column1]=-400;
            }
          }
          return 1;
        }
        else{
          strcpy(error,"King is under Check");
          return 0;
        }
      }
      else {      //new square is occupied
        return 0;
      }
    }
  }
  else if(color==1&&column1!=column2){     //for white pawn capture
    if((row2-row1==-1)&&(column1!=column2)){
      if(board[row2][column2]<0){   //check if new square has black piece
        if(!detect_check(1)){
          if(row2==0){
            do{
              printf("Which piece do you want to promote to?\n");
              scanf(" %c",&piece);
            }
            while(piece!='Q'&&piece!='N'&&piece!='R'&&piece!='B');
            if(piece=='Q'){
              board[row1][column1]=900;
              }
            else if(piece=='R'){
              board[row1][column1]=500;
            }
            else if(piece=='N'){
              board[row1][column1]=300;
            }
            else if(piece=='B'){
              board[row1][column1]=400;
            }
          }
          return 1;
        }
        else{
          strcpy(error,"King is under Check");
          return 0;
        }
      }
      else if(ep==1&&board[row2][column2]==0&&prow1==1&&prow2==3&&pcolumn2==column2){ //special case of en passant
        //bringing back the last move by one square.
        board[prow2][pcolumn2]=0;
        board[prow2-1][pcolumn2]=-100;
        if(!detect_check(1)){
          return 1;
        }
      }
      else{
        return 0;    //new square is empty or has white piece
      }
    }
  }
  else if(color==2&&column1!=column2){    //for black pawn capture
    if((row2-row1==1)&&(column2!=column1)){
      if(board[row2][column2]>0){   //checks if new square has white piece
        if(!detect_check(1)){
          if(row2==7){
            do{
              printf("Which piece do you want to promote to?\n");
              scanf(" %c",&piece);
            }
            while(piece!='Q'&&piece!='N'&&piece!='R'&&piece!='B');
            if(piece=='Q'){
              board[row1][column1]=-900;
              }
            else if(piece=='R'){
              board[row1][column1]=-500;
            }
            else if(piece=='N'){
              board[row1][column1]=-300;
            }
            else if(piece=='B'){
              board[row1][column1]=-400;
            }
          }
          return 1;
        }
        else{
          strcpy(error,"King is under Check");
          return 0;
        }
      }
      else if(ep==1&&board[row2][column2]==0&&prow1==6&&prow2==4&&pcolumn2==column2){ //special case of en passant
        board[prow2][pcolumn2]=0;
        board[prow2+1][pcolumn2]=100;
        if(!detect_check(1)){
          return 1;
        }
      }
      else{
        return 0;   //new square is empty or has black piece
      }
    }
  }
  return 0;     //it is neither single,double or capture move
}   //validates pawns
int validate_rook(){
  int i,j,flag=1,smaller,bigger;
    if((row1==row2)||(column1==column2)){     //it is a valid move
      flag=0;
      if(row1!=row2){
          if(row2>row1){
            bigger=row2;
            smaller=row1;
          }
          else{
            bigger=row1;
            smaller=row2;
          }
        for(i=smaller+1;i<bigger;i++){
          if(board[i][column1]!=0){    //checking empty in between squares
            flag=1;
          }
        }
      }
      else{
          if(column2>column1){
            bigger=column2;
            smaller=column1;
          }
          else{
            bigger=column1;
            smaller=column2;
          }
        for(i=smaller+1;i<bigger;i++){   //checking empty in between squares
          if(board[row1][i]!=0){
            flag=1;
          }
        }
      }
    if(board[row2][column2]!=0){ //new square is occupied
      if((color==1)&&(board[row2][column2]>0))
      flag=1;
      if((color==2)&&(board[row2][column2]<0))
      flag=1;
    }
  }
  if(flag==0){
    if(!detect_check(1)){
      return 1;
    }
    else{
      strcpy(error,"King is under Check");
      return 0;
    }
  }
  else
    return 0;
}   //validates rooks
int validate_knight(){
  int flag=1;
  if((column2-column1==2||column2-column1==-2)&&(row2-row1==1||row2-row1==-1)){
    if(color==1){
      if(board[row2][column2]<=0){
        flag=0;
      }
    }
    else{
      if(board[row2][column2]>=0){
        flag=0;
      }
    }
  }
  else if((row2-row1==2||row2-row1==-2)&&(column2-column1==1||column2-column1==-1)){
    if(color==1){
      if(board[row2][column2]<=0){
        flag=0;
      }
    }
    else{
      if(board[row2][column2]>=0){
        flag=0;
      }
    }
  }
  if(flag==0){
    if(!detect_check(1)){
      return 1;
    }
    else{
      strcpy(error,"King is under Check");
      return 0;
    }
  }
  else
    return 0;
} //validates knights
int validate_bishop(){
  int flag=1,i,j;//4 possible diagonals a bishop can move in
  if(row2!=row1&&column2!=column1){   //basic condition for diagonal move
    if((row2-row1)>0&&((row2-row1)==(column2-column1))){  //lower right diagonal
      flag=0;
      for(i=row1+1,j=column1+1;i<row2;i++,j++){    //checking squares in between
        if(board[i][j]!=0){
          flag=1;
          break;
        }
      }
    }
    else if((column2-column1)<0&&(row2-row1)==(-1*(column2-column1))){   //lower left diagonal
      flag=0;
      for(i=row1+1,j=column1-1;i<row2;i++,j--){    //checking squares in between
        if(board[i][j]!=0){
          flag=1;
          break;
        }
      }
    }
    else if((row2-row1)<0&&((row2-row1)==(column2-column1))){  //upper left diagonal
      flag=0;
      for(i=row1-1,j=column1-1;i>row2;i--,j--){    //checking squares in between
        if(board[i][j]!=0){
          flag=1;
          break;
        }
      }
    }
    else if(((row2-row1)*-1)==(column2-column1)){    //upper right diagonal
      flag=0;
      for(i=row1-1,j=column1+1;i>row2;i--,j++){    //checking squares in between
        if(board[i][j]!=0){
          flag=1;
          break;
        }
      }
    }
  }
  if(color==1){
    if(board[row2][column2]>0){
      flag=1;
    }
  }
  else{
    if(board[row2][column2]<0){
      flag=1;
    }
  }
  if(flag==0){
    if(!detect_check(1)){
      return 1;
    }
    else{
      strcpy(error,"King is under Check");
      return 0;
    }
  }
  return 0;
} //validates bishops
int validate_queen(){
  int result=0; //Queen moves as a rook or as a bishop.
  result=validate_bishop();
  if(!result){
    result=validate_rook();
  }
  if(result){
    if(!detect_check(1)){
      return 1;
    }
    else{
      strcpy(error,"King is under Check");
      return 0;
    }
  }
  else{
    return 0;
  }
} //validates queens
int validate_king(){
  int result=0; //king is just a queen with one move in either direction
  castling=0;
  if(row1==row2&&column1==4&&column2==6){
    if(color==1){
      if(white_kcastle==1){
        result=check_castle();
        castling=1;

      }
    }
    else{
      if(black_kcastle==1){
        result=check_castle();
        castling=1;
      }
    }
  }
  else if(row1==row2&&column1==4&&column2==2){
    if(color==1){
      if(white_qcastle==1){
        result=check_castle();
        castling=1;
      }
    }
    else{
      if(black_qcastle==1){
        result=check_castle();
        castling=1;
      }
    }
  }
  if((row1==row2)&&(column1-column2==1||column1-column2==-1)){
    result=validate_queen();
  }
  else if((column1==column2)&&(row1-row2==1||row1-row2==-1)){
    result=validate_queen();
  }
  else if(abs(row2-row1)==abs(column2-column1)){
    if(abs(row2-row1)==1){
      result=validate_queen();
    }
  }
  if(result){
    if(!detect_check(1)){
      return 1;
    }
    else{
      strcpy(error,"king is under check");
      return 0;
    }
  }
  else{
    return 0;
  }
} //validates kings

int main(int argc, char const *argv[]) {
  int check=0,validation,k=0,choice,col,flag,load,i,j,x,y,count=0;;
  make_new_board();
  printf("Menu\n1. Single Player\n2. Double Player\n Enter Choice \n ");
  scanf("%d",&choice);
  if(choice==1){
    try :
    printf("Enter color of player\n1 - White \n2 - Black\n");
    scanf("%d",&col);
    if(col!=1&&col!=2){
      goto try;
    }
  }
  printf("Do you want to load game?\n1 - Yes\n");
  scanf("%d",&load);
  clear();
  printf("Press s anytime to save game and exit\n");
  if(load==1){
    loadgame();
    count=totalcount;
  }
  else{
    resetgame();
  }
  initGraphics();
  XSetForeground(dpy, gc, light);
  for(;;) {
    XEvent e;
    XNextEvent(dpy, &e);
    if (e.type == MapNotify){
    break;
    }
  }
  dolight();
  XSetForeground(dpy, gc, dark);
  dodark();
  doboard();
  XEvent event;
  KeySym key;
  if(choice==2){
  while(1){
    XNextEvent(dpy, &event);
    if(event.type==KeyPress&&XLookupString(&event.xkey,text,255,&key,0)==1){
      if(text[0]=='s'){
        close_x();
      }
    }
    if (event.type==ButtonPress) {
    /* tell where the mouse Button was Pressed */
    int x=event.xbutton.x,y=event.xbutton.y;
    x=convert(x);
    y=convert(y);
    count++;
    if(x<0||y<0){
        printf("invalid input");
        break;
    }
    XSetForeground(dpy, gc, blackColor);
    XDrawRectangle(dpy,w,gc,x*100,y*100,100,100);
    if(count%2!=0){
      row1=y;
      column1=x;
      goto abc;
    }
    row2=y;
    column2=x;
    get_move();
    validation=validate_move();
    if(validation==0||check==-1){
          printf("%s\n",error);
    }
    validate_piece();
    flag=detect_checkmate_and_stalemate();
    if(flag==1){
        printf("Checkmate!\n");
        close_x();
    }
    else if(flag==2){
        printf("Game drawn!\n");
        close_x();
    }
    if(detectdraw()){
        printf("Game draw!\n");
        close_x();
    }
    printf("Done with %d move\n",k+1);
    printf("Now the color to move is %d\n",color);
    k++;
    XSetForeground(dpy, gc, light);
    dolight();
    XSetForeground(dpy, gc, dark);
    dodark();
    doboard();
    abc:
      count++;
      count--;
      }
    }
  }
else if(choice==1){
  while(1){
    if(color==col){
      XNextEvent(dpy, &event);
      if (event.type==KeyPress&&XLookupString(&event.xkey,text,255,&key,0)==1) {
        if (text[0]=='s') {
          close_x();
        }
      }
      if (event.type==ButtonPress) {
      /* tell where the mouse Button was Pressed */
        int x=event.xbutton.x,y=event.xbutton.y;
        x=convert(x);
        y=convert(y);
        count++;
        if(x<0||y<0){
          printf("invalid input");
          break;
        }
        XSetForeground(dpy, gc, blackColor);
        XDrawRectangle(dpy,w,gc,x*100,y*100,100,100);
        if(count%2!=0){
          row1=y;
          column1=x;
          goto pqr;
        }
        row2=y;
        column2=x;
        get_move();
        validation=validate_move();
        if(validation==0||check==-1){
            printf("%s\n",error);
        }
        validate_piece();
        flag=detect_checkmate_and_stalemate();
        if(flag==1){
          printf("Checkmate!\n");
          exit(1);
        }
        else if(flag==2){
          printf("Game drawn!\n");
          exit(1);
        }
        printf("Done with %d move\n",k+1);
        printf("Now the color to move is %d\n",color);
        k++;
        XSetForeground(dpy, gc, light);
        dolight();
        XSetForeground(dpy, gc, dark);
        dodark();
        doboard();
        XFlush(dpy);
        pqr:
          count++;
          count--;
      }
    }
    else{
      heisenberg();
      savemove();
      execute_move();
      flag=detect_checkmate_and_stalemate();
      if(flag==1){
        printf("Checkmate!\n");
        exit(1);
      }
      else if(flag==2){
        printf("Game drawn!\n");
        exit(1);
      }
      XSetForeground(dpy, gc, light);
      dolight();
      XSetForeground(dpy, gc, dark);
      dodark();
      doboard();
      printf("Done with %d moves\n",k+1);
      printf("Now the color to move is %d\n",color);
      k++;
    }
  }
  return 0;
  }
}
