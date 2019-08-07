#include "tic_objects.h"
#include "tic_resources.h"

//--------------------- User code ---------------------//

//----------------- End of User code ------------------//

// Event Handlers



extern unsigned int game_end;
extern unsigned int round;
extern unsigned int cells[3][3];
extern unsigned int pressed_button;
extern char curr ;
extern unsigned int round;
extern int check_win(int,int);


void mark() {


     int row = (pressed_button-1)/3;
     int col = (pressed_button-1)%3;
     TButton* pressed_btt=Screen1_Buttons[pressed_button-1];

     if( cells[row][col] ==0 ) {
        cells[row][col]= curr;
        
        round++;
        //pressed_btt->Active = 0;

        pressed_btt->caption[0]=curr-32;
        DrawButton(pressed_btt);

        if(check_win(row,col)){
           if(curr=='x')
           TFT_Write_Text("X WINS! ", 20, 5);
           else if(curr=='o'){
           TFT_Write_Text("O WINS! ", 20, 5);
           }
           game_end=1;//
           
        }else if(round==9){
         game_end =1;
         TFT_Write_Text("Tie ! :( ", 20, 5);

        }
         //convert to upper
     if(curr=='x'){
        //strcpy(pressed_btt->Caption,"X");

     curr ='o';
     }
     else if(curr=='o'){
       //strcpy(pressed_btt->Caption,"O");
     curr='x';
     }




     //}
     
    }
}