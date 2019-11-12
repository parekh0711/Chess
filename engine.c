#include "engine.h"

/* Stack Functions for Move Generator*/
int isempty(){
  if(moves!=NULL){
    return 0;
  }
  return 1;
}   //checks if moves stack is empty
int push(int p, int q, int r, int s, char pi, int tempboard[8][8]){
  int i,j;
  node *temp = (node*)malloc(sizeof(node));
  if(moves==NULL){
    temp->r1=p;
    temp->r2=q;
    temp->c1=r;
    temp->c2=s;
    temp->piece=pi;
    for(i=0;i<8;i++){
      for(j=0;j<8;j++){
        temp->tb[i][j]=tempboard[i][j];
      }
    }
    temp->tb[q][s]=temp->tb[p][r];
    temp->tb[p][r]=0;
    temp->score=evaluate(p,q,r,s,tempboard);
    temp->link=NULL;
    moves=temp;
  }
  else{
    temp->r1=p;
    temp->r2=q;
    temp->c1=r;
    temp->c2=s;
    temp->piece=pi;
    for(i=0;i<8;i++){
      for(j=0;j<8;j++){
        temp->tb[i][j]=tempboard[i][j];
      }
    }
    temp->tb[q][s]=temp->tb[p][r];
    temp->tb[p][r]=0;
    temp->score=evaluate(p,q,r,s,tempboard);
    temp->link=moves;
    moves=temp;
  }
} //pushes into moves
int pop(){
  node *temp;
  if(moves==NULL){
    return -1;
  }
  else{
    temp=moves;
    moves=moves->link;
    free(temp);
  }
  return 1;
}  //pops from moves
int print(){
  node* temp;
  temp=moves;
  printf("Printing Moves Stack\n");
  while(temp!=NULL){
    printf("%c%d%d%d%d\t score - %lf\n",temp->piece,temp->r1,temp->c1,temp->r2,temp->c2,temp->score);
    temp=temp->link;
  }
}   //prints moves

/*  Engine  */
int move_generator(){
  char piece, oldpos[3],newpos[3];
  int i,j,k;
  while(!isempty()){
    pop();
  }
  if(color==1){
    for(i=0;i<8;i++){
      for(j=0;j<8;j++){
        if(board[i][j]<=0);
        else if(board[i][j]==100){
          piece='P';
          row1=i;
          column1=j;
          row2=i-1;
          column2=j;
          if(row2<7&&row2>0&&column2<8&&column2>=0){
            k=validate_pawn(0);
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i-2;
          if(row2<7&&row2>0&&column2<8&&column2>=0){
            k=validate_pawn(0);
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i-1;
          column2=j+1;
          if(row2<7&&row2>0&&column2<8&&column2>=0){
            k=validate_pawn(0);
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j-1;
          if(row2<7&&row2>0&&column2<8&&column2>=0){
            k=validate_pawn(0);
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
        }
        else if(board[i][j]==300){
          piece='N';
          row1=i;
          column1=j;
          row2=i-1;
          column2=j+2;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);

            }
          }
          column2=j-2;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);

            }
          }
          row2=i+1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);

            }
          }
          column2=j+2;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);

            }
          }
          row2=i+2;
          column2=j+1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);

            }
          }
          column2=j-1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);

            }
          }
          row2=i-2;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);

            }
          }
          column2=j+1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);

            }
          }
        }
        else if(board[i][j]==400){
          piece='B';
          row1=i;
          column1=j;
          row2=i+1;
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_bishop();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
            column2++;
          }
          row2=i-1;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_bishop();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
            column2--;
          }
          row2=i+1;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_bishop();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
            column2--;
          }
          row2=i-1;
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_bishop();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
            column2++;
          }
        }
        else if(board[i][j]==500){
          piece='R';
          row1=i;
          column1=j;
          row2=i;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_rook();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            column2--;
          }
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_rook();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            column2++;
          }
          column2=j;
          row2=i+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_rook();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
          }
          row2=i-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_rook();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
          }
        }
        else if(board[i][j]==900){
          piece='Q';
          row1=i;
          column1=j;
          row2=i+1;
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
            column2++;
          }
          row2=i-1;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
            column2--;
          }
          row2=i+1;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
            column2--;
          }
          row2=i-1;
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
            column2++;
          }
          row2=i;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            column2--;
          }
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
              push(row1,row2,column1,column2,piece,board);
            }
            column2++;
          }
          column2=j;
          row2=i+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
          }
          row2=i-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
          }
        }
        else if(board[i][j]==10000){
          piece='K';
          row1=i;
          column1=j;
          row2=7;
          column2=6;
          if(white_kcastle==1){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=2;
          if(white_qcastle==1){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i+1;
          column2=j+1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j-1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j+1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i-1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j-1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
        }
      }
    }
  }
  else if(color==2){
    for(i=0;i<8;i++){
      for(j=0;j<8;j++){
        if(board[i][j]>=0);
        else if(board[i][j]==-100){
          piece='P';
          row1=i;
          column1=j;
          row2=i+1;
          column2=j;
          if(row2<7&&row2>0&&column2<8&&column2>=0){
            k=validate_pawn(0);
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i+2;
          if(row2<7&&row2>0&&column2<8&&column2>=0){
            k=validate_pawn(0);
            if(k){
            push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i+1;
          column2=j+1;
          if(row2<7&&row2>0&&column2<8&&column2>=0){
            k=validate_pawn(0);
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j-1;
          if(row2<7&&row2>0&&column2<8&&column2>=0){
            k=validate_pawn(0);
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
        }
        else if(board[i][j]==-300){
          piece='N';
          row1=i;
          column1=j;
          row2=i-1;
          column2=j+2;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j-2;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i+1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j+2;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i+2;
          column2=j+1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j-1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i-2;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j+1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_knight();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
        }
        else if(board[i][j]==-400){
          piece='B';
          row1=i;
          column1=j;
          row2=i+1;
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_bishop();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
            column2++;
          }
          row2=i-1;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_bishop();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
            column2--;
          }
          row2=i+1;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_bishop();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
            column2--;
          }
          row2=i-1;
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_bishop();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
            column2++;
          }
        }
        else if(board[i][j]==-500){
          piece='R';
          row1=i;
          column1=j;
          row2=i;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_rook();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            column2--;
          }
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_rook();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            column2++;
          }
          column2=j;
          row2=i+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_rook();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
          }
          row2=i-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_rook();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
          }
        }
        else if(board[i][j]==-900){
          piece='Q';
          row1=i;
          column1=j;
          row2=i+1;
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
            column2++;
          }
          row2=i-1;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
            column2--;
          }
          row2=i+1;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
            column2--;
          }
          row2=i-1;
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
            column2++;
          }
          row2=i;
          column2=j-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            column2--;
          }
          column2=j+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            column2++;
          }
          column2=j;
          row2=i+1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2++;
          }
          row2=i-1;
          while(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_queen();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
            row2--;
          }
        }
        else if(board[i][j]==-10000){
          piece='K';
          row1=i;
          column1=j;
          row2=0;
          column2=6;
          if(black_kcastle==1){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=2;
          if(black_qcastle==1){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i+1;
          column2=j+1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j-1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j+1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          row2=i-1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j-1;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
          column2=j;
          if(row2<8&&row2>=0&&column2<8&&column2>=0){
            k=validate_king();
            if(k){
              push(row1,row2,column1,column2,piece,board);
            }
          }
        }
      }
    }
  }
}   //generates all legal moves from given position
double evaluate(int p, int q, int r, int s,int board[8][8]){
  int i,j,doubled_pawns=0,white_bishop=0,black_bishop=0,wp=0,bp=0,white_centre=0;
  int tempboard[8][8],black_centre=0;
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      tempboard[i][j]=board[i][j];
    }
  }
  tempboard[q][s]=tempboard[p][r];
  tempboard[p][r]=0;
  double score=0;
  for(i=0;i<8;i++){       //parameter 1 - simple addition of piece values
    for(j=0;j<8;j++){     //parameter 2 - bishop pair
      if(tempboard[i][j]==400){
        score+=300;
        white_bishop++;
      }
      else if(tempboard[i][j]==-400){
        score-=300;
        black_bishop++;
      }
      else{
        score+=tempboard[i][j];
      }
    }
  }
  score/=100;
  for(j=0;j<8;j++){      //parameter 3 - doubled pawns
    for(i=0;i<8;i++){
      if(tempboard[i][j]==100){
        wp++;
      }
      else if(tempboard[i][j]==-100){
        bp++;
      }
    }
    doubled_pawns=doubled_pawns+wp-bp;
    wp=0;
    bp=0;
  }
  score=score-(0.08*doubled_pawns);
  if(white_bishop==2){
    score+=0.05;
  }
  if(black_bishop==2){
    score-=0.05;
  }
  if(tempboard[4][3]==100){   //parameter 4 - control of centre
    white_centre+=1;
  }
  else if(tempboard[4][3]==-100){
    black_centre+=1;
  }
  if(tempboard[4][4]==100){
    white_centre+=1;
  }
  else if(tempboard[4][4]==-100){
    black_centre+=1;
  }
  if(tempboard[4][2]==100){
    white_centre+=1;
  }
  else if(tempboard[4][2]==-100){
    black_centre+=1;
  }
  if(tempboard[4][5]==100){
    white_centre+=1;
  }
  else if(tempboard[4][5]==-100){
    black_centre+=1;
  }
  if(tempboard[3][3]==100){
    white_centre+=1;
  }
  else if(tempboard[3][3]==-100){
    black_centre+=1;
  }
  if(tempboard[3][4]==100){
    white_centre+=1;
  }
  else if(tempboard[3][4]==-100){
    black_centre+=1;
  }
  if(tempboard[3][2]==100){
    white_centre+=1;
  }
  else if(tempboard[3][2]==-100){
    black_centre+=1;
  }
  if(tempboard[3][5]==100){
    white_centre+=1;
  }
  else if(tempboard[3][5]==-100){
    black_centre+=1;
  }
  white_centre-=black_centre;
  score=score+(white_centre*0.08);
  //parameter5 penalty for bad position of knight
  for(i=0;i<=7;i+=7){
    for(j=0;j<8;j++){
      if(tempboard[i][j]==-300){
        score+=0.9;
      }
      else if(tempboard[i][j]==300){
        score-=0.9;
      }
    }
  }
  for(j=0;j<=7;j+=7){
    for(i=0;i<8;i++){
      if(tempboard[i][j]==-300){
        score+=0.8;
      }
      else if(tempboard[i][j]==300){
        score-=0.8;
      }
    }
  }
  //parameter6 penalty for bad position of bishop
  if(tempboard[0][2]==-400){
    score+=1.299;
  }
  if(tempboard[0][5]==-400){
    score+=1.299;
  }
  if(tempboard[7][2]==400){
    score-=1.3;
  }
  if(tempboard[7][5]==400){
    score-=1.3;
  }
  //parameter 7 of castling handled by heisenberg()
  return score;
} //evaluates position based on different parameters
int makemove(int row1, int row2, int column1,int column2){
  Node *temp=(Node*)malloc(sizeof(Node));
  int i,j;
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      temp->bd[i][j]=board[i][j];
    }
  }
  temp->c=color;
  temp->wqcastle=white_qcastle;
  temp->wkcastle=white_kcastle;
  temp->bkcastle=black_kcastle;
  temp->bqcastle=black_qcastle;
  temp->castle=castling;
  temp->link=NULL;
  if(history==NULL){
    history=temp;
  }
  else{
    temp->link=history;
    history=temp;
  }
  board[row2][column2]=board[row1][column1];
  board[row1][column1]=0;
  (color==1)?(color=2):(color=1);
  update_castle();
} //makes move on board
int unmakemove(){
  int i,j;
  Node *temp=history;
  if(temp==NULL){
    return -1;
  }
  else{
    for(i=0;i<8;i++){
      for(j=0;j<8;j++){
        board[i][j]=temp->bd[i][j];
      }
    }
    color=history->c;
    white_qcastle=history->wqcastle;
    white_kcastle=history->wkcastle;
    black_qcastle=history->bqcastle;
    black_kcastle=history->bkcastle;
    castling=history->castle;
    history=history->link;
    free(temp);
  }
} //unmakes move on board
void best_move(){
    MergeSort(&moves);
    if(color==2){
      move[0]=moves->piece;
      move[1]=moves->r1;
      move[2]=moves->c1;
      move[3]=moves->r2;
      move[4]=moves->c2;
    }
    else{
      node *temp=moves;
      while(temp->link!=NULL){
        temp=temp->link;
      }
      move[0]=temp->piece;
      move[1]=temp->r1;
      move[2]=temp->c1;
      move[3]=temp->r2;
      move[4]=temp->c2;
    }
} //returns the best move from moves stack
void heisenberg(){
  int i,f=1;
  move_generator(); //created level 1
  level1=moves;
  moves=NULL;
  level2=NULL;
  level3=NULL;
  level4=NULL;
  node *k;
  node *temp=level1;
  node *temp2=level2;
  node *temp3=level3;
  while(temp!=NULL){
    printf("*");
    makemove(temp->r1,temp->r2,temp->c1,temp->c2);
    move_generator();  //created moves of level 2
    level2=moves;
    if(level2==NULL){
      if(color==2){
        temp->score=999;
      }
      else{
        temp->score=-999;
      }
    }
    moves=NULL;
    temp2=level2;    //pointing to first move of level 2
    while(temp2!=NULL){
      makemove(temp2->r1,temp2->r2,temp2->c1,temp2->c2);
      move_generator();   //creating moves of level 3
      level3=moves;
      if(level3==NULL){
        if(color==2){
          temp2->score=999;
        }
        else{
          temp2->score=-999;
        }
      }
      moves=NULL;
      temp3=level3;
      while(temp3!=NULL){
        makemove(temp3->r1,temp3->r2,temp3->c1,temp3->c2);
        move_generator();  //creates level 4
        MergeSort(&moves);  //sorts level 4
        if(moves!=NULL){
          if(color==2){
            temp3->score=moves->score;
          }
          else{
            k=moves;
            while(k->link!=NULL){
              k=k->link;
            }
            temp3->score=k->score;
          }
        }
        else{
          if(color==2){
            temp3->score=999;
          }
          else{
            temp3->score=-999;
          }
        }
        temp3=temp3->link;
        unmakemove();
      } //level 3 has been assigned scores;
      moves=level3;
      MergeSort(&moves);
      level3=moves;
      moves=NULL;
      if(level3!=NULL){
        if(color==2){
          temp2->score=level3->score;
        }
        else{
          k=level3;
          while(k->link!=NULL){
            k=k->link;
          }
          temp2->score=k->score;
        }
      }
      k=level3;
      while(k!=NULL){
        level3=level3->link;
        free(k);
        k=level3;
      }
      temp2=temp2->link;
      unmakemove();
    }   // we have assigned values to level 2,
    moves=level2;
    MergeSort(&moves);
    level2=moves;
    moves=NULL;
    if(level2!=NULL){
      if(color==2){
        temp->score=level2->score;
        if(temp->r1==temp->r2&&temp->c1==4&&(temp->c2==6||temp->c2==2)){
            temp->score+=2;
        }
      }
      else{
        k=level2;
        while(k->link!=NULL){
          k=k->link;
        }
        temp->score=k->score;
        if(temp->r1==temp->r2&&temp->c1==4&&(temp->c2==6||temp->c2==2)){
            temp->score-=2;
        }
      }
    }
    k=level2;
    while(k!=NULL){
      level2=level2->link;
      free(k);
      k=level2;
    }
    temp=temp->link;
    unmakemove();
  }
  moves=level1;
  best_move();
  row1=move[1];
  column1=move[2];
  row2=move[3];
  column2=move[4];
  if(row1==row2&&column1==4&&(column2==6||column2==2)){
    castling=1;
  }
  return;
}  //Novice level engine which searches upto depth 5

/*  Sorting Algorithm */
void MergeSort(node** headRef){
  node* head = *headRef;
  node* a;
  node* b;
  if ((head == NULL) || (head->link == NULL)){
      return;
  }
  FrontBackSplit(head, &a, &b);
  MergeSort(&a);
  MergeSort(&b);
  *headRef = SortedMerge(a, b);
}
node* SortedMerge(node* a, node* b){
    node* result = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (a->score <= b->score) {
        result = a;
        result->link = SortedMerge(a->link, b);
    }
    else {
        result = b;
        result->link = SortedMerge(a, b->link);
    }
    return (result);
}
void FrontBackSplit(node* source, node** frontRef, node** backRef){
    node* fast;
    node* slow;
    slow = source;
    fast = source->link;
    while (fast != NULL) {
        fast = fast->link;
        if (fast != NULL) {
            slow = slow->link;
            fast = fast->link;
        }
    }
    *frontRef = source;
    *backRef = slow->link;
    slow->link = NULL;
}
