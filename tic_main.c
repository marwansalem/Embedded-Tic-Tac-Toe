/*
 * Project name:
     tic.mcpar
 :
   Created by Marwan Saad Salem
 * Date of creation
     05/08/2019
 * Test configuration:
     MCU:             STM32F107VC
     Dev.Board:       EasyMx_PRO_v7_for_STM32_ARM
                      http://www.mikroe.com/easymx-pro/stm32/
     Oscillator:      72000000 Hz
     SW:              mikroC PRO for ARM
                      http://www.mikroe.com/mikroc/arm/
 */

#include "tic_objects.h"
void clear_cells();
int check_win(int,int);
int within_board(int,int);
unsigned int cells[3][3];


char curr = 'x';
unsigned int game_end=0;
unsigned int round=0;
void main() {


  /*for(i=0;i<9;i++)
       pre[i]=0;*/


  Start_TP();
  clear_cells();
  while (1) {
    Check_TP();
    if(game_end){
       game_end=0;
       clear_cells();
       round = 0;
       curr= 'x';
       Delay_ms(2000);
       DrawScreen(&Screen1);
    }
  }
}
void clear_cells(){
 int i,j,c;
 c=0;
 for(i=0;i<3;i++)
   for(j=0;j<3;j++){
     cells[i][j]=0;

     //Screen1_Buttons[c]->Active=1;
     Screen1_Buttons[c++]->Caption[0]=' ';
     }


}

/*int within_board(int r,int c){
  if(r<0 || r>2 || c<0 || c>2)
     return 0;
  return 1;
}*/

int check_win(int r,int c){
 int i,count;
 if(round<5)
   return 0;


    count=0;
    for(i=0;i<3;i++)
   {
   if(cells[r][i]!=curr)
         break;

   count++;
   }
   if(count==3){
    return 1;
   }


  count=0;
  for(i=0;i<3;i++){

   if(cells[i][c]!=curr)
         break;

   count++;
   }
   if(count==3){
    return 1;
   }

   count = 0;
   
   for(i=0;i<3;i++){
      if(cells[i][i]!=curr)
        break;
      count++;
   }
   if(count==3)
     return 1;

   count=0;
   for(i=0;i<3;i++){
    if(cells[2-i][i]!=curr)
       break;
    count++;
   }
   if(count==3)
     return 1;

  return 0;
}


/*int check_win_org(int r,int c){
    if(r<0 || r>2 || c<0 ||c>2 ||cells[r][c]==0 ||visit_once[r][c]<round )
      return 0;
    if(round<5)
      return 0;
    if(within_board(r+1,c) && within_board(r+2,c)){ //infinte calls

     if((cells[r+1][c] == cells[r+2][c])  && cells[r+1][c] ==curr){
      return 1;
     }
    }else {
          if( check_win(r+1,c) || check_win(r-1,c) )
             return 1;
    }
    if(within_board(r,c+1) &&within_board(r,c+2)){
     if((cells[r][c+1] == cells[r][c+2])  && cells[r][c+1] ==curr ){
       return 1;
     }
    }else {
          if( check_win(r,c+1) || check_win(r,c+2) )
             return 1;
    }

    return 0;

}*/