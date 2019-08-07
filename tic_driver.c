#include "tic_objects.h"
#include "tic_resources.h"
#include "built_in.h"


// TFT module connections
sbit TFT_BLED at GPIOE_ODR.B9;
sbit TFT_CS at GPIOE_ODR.B15;
unsigned int TFT_DataPort at GPIOE_ODR;
sbit TFT_RD at GPIOE_ODR.B10;
sbit TFT_RS at GPIOE_ODR.B12;
sbit TFT_RST at GPIOE_ODR.B8;
sbit TFT_WR at GPIOE_ODR.B11;
// End TFT module connections

// Touch Panel module connections
sbit DriveX_Left at GPIOB_ODR.B1;
sbit DriveX_Right at GPIOB_ODR.B8;
sbit DriveY_Up at GPIOB_ODR.B9;
sbit DriveY_Down at GPIOB_ODR.B0;
// End Touch Panel module connections

// Global variables
unsigned int Xcoord, Ycoord;
const ADC_THRESHOLD = 1500;
char PenDown;
void *PressedObject;
int PressedObjectType;
unsigned int caption_length, caption_height;
unsigned int display_width, display_height;
unsigned int pressed_button=20;

int _object_count; //
unsigned short object_pressed;//
TButton *local_button;
TButton *exec_button;
int button_order;    //


void Init_ADC() {
  ADC_Set_Input_Channel(_ADC_CHANNEL_8 | _ADC_CHANNEL_9);
  ADC1_Init();
  Delay_ms(100);
}
static void InitializeTouchPanel() {
  Init_ADC();
  TFT_Init(320, 240);

  TFT_Init_ILI9341_8bit(320,240);
  TP_TFT_Init(320, 240, 8, 9);                                  // Initialize touch panel
  TP_TFT_Set_ADC_Threshold(ADC_THRESHOLD);                              // Set touch panel ADC threshold

  PenDown = 0;
  PressedObject = 0;
  PressedObjectType = -1;
}

void Calibrate() {
  TFT_Set_Pen(CL_WHITE, 3);
  TFT_Set_Font(TFT_defaultFont, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text("Touch selected corners for calibration", 50, 80);
  TFT_Line(315, 239, 319, 239);
  TFT_Line(309, 229, 319, 239);
  TFT_Line(319, 234, 319, 239);
  TFT_Write_Text("first here", 210, 220);

  TP_TFT_Calibrate_Min();                      // Calibration of TP minimum
  Delay_ms(500);

  TFT_Set_Pen(CL_BLACK, 3);
  TFT_Set_Font(TFT_defaultFont, CL_BLACK, FO_HORIZONTAL);
  TFT_Line(315, 239, 319, 239);
  TFT_Line(309, 229, 319, 239);
  TFT_Line(319, 234, 319, 239);
  TFT_Write_Text("first here", 210, 220);

  TFT_Set_Pen(CL_WHITE, 3);
  TFT_Set_Font(TFT_defaultFont, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text("now here ", 20, 5);
  TFT_Line(0, 0, 5, 0);
  TFT_Line(0, 0, 0, 5);
  TFT_Line(0, 0, 10, 10);

  TP_TFT_Calibrate_Max();                       // Calibration of TP maximum
  Delay_ms(500);
}


/////////////////////////
  TScreen*  CurrentScreen;

  TScreen                Screen1;
  TButton               Button1;
char Button1_Caption[3] = "  ";

  TButton               Button2;
char Button2_Caption[3] = "  ";

  TButton               Button3;
char Button3_Caption[3] = "  ";

  TButton               Button4;
char Button4_Caption[3] = "  ";

  TButton               Button5;
char Button5_Caption[3] = "  ";

  TButton               Button6;
char Button6_Caption[3] = "  ";

  TButton               Button7;
char Button7_Caption[3] = "  ";

  TButton               Button8;
char Button8_Caption[3] = "  ";

  TButton               Button9;
char Button9_Caption[3] = "  ";
  TButton                * const code Screen1_Buttons[9]=
         {
         &Button1,             
         &Button2,             
         &Button3,
         &Button4,
         &Button5,
         &Button6,
         &Button7,
         &Button8,
         &Button9
         };



static void InitializeObjects() {
  Screen1.Color                     = 0x5AEB;
  Screen1.Width                     = 320;
  Screen1.Height                    = 240;
  Screen1.ButtonsCount              = 9; //
  Screen1.Buttons                   = Screen1_Buttons;
  Screen1.ObjectsCount              = 9; //


  Button1.OwnerScreen     = &Screen1;
  Button1.Order           = 0;    //
  Button1.Left            = 50;
  Button1.Top             = 39;
  Button1.Width           = 69;
  Button1.Height          = 58;
  Button1.Pen_Width       = 1;
  Button1.Pen_Color       = 0x0000;
  Button1.Visible         = 1;
  Button1.Active          = 1;
  Button1.Transparent     = 1;
  Button1.Caption         = Button1_Caption;
  Button1.TextAlign       = _taCenter;
  Button1.TextAlignVertical= _tavMiddle;
  Button1.FontName        = Tahoma11x13_Regular;
  Button1.PressColEnabled = 1;
  Button1.Font_Color      = 0x0000;
  Button1.VerticalText    = 0;
  Button1.Gradient        = 1;
  Button1.Gradient_Orientation = 0;
  Button1.Gradient_Start_Color = 0xFFFF;
  Button1.Gradient_End_Color = 0xC618;
  Button1.Color           = 0xC618;
  Button1.Press_Color     = 0xE71C;
  Button1.OnUpPtr         = 0;
  Button1.OnDownPtr       = 0;
  Button1.OnClickPtr      = mark;
  Button1.OnPressPtr      = 0;   //

  Button2.OwnerScreen     = &Screen1;
  Button2.Order           = 1;
  Button2.Left            = 124;
  Button2.Top             = 39;
  Button2.Width           = 69;
  Button2.Height          = 58;
  Button2.Pen_Width       = 1;
  Button2.Pen_Color       = 0x0000;
  Button2.Visible         = 1;
  Button2.Active          = 1;
  Button2.Transparent     = 1;
  Button2.Caption         = Button2_Caption;
  Button2.TextAlign       = _taCenter;
  Button2.TextAlignVertical= _tavMiddle;
  Button2.FontName        = Tahoma11x13_Regular;
  Button2.PressColEnabled = 1;
  Button2.Font_Color      = 0x0000;
  Button2.VerticalText    = 0;
  Button2.Gradient        = 1;
  Button2.Gradient_Orientation = 0;
  Button2.Gradient_Start_Color = 0xFFFF;
  Button2.Gradient_End_Color = 0xC618;
  Button2.Color           = 0xC618;
  Button2.Press_Color     = 0xE71C;
  Button2.OnUpPtr         = 0;
  Button2.OnDownPtr       = 0;
  Button2.OnClickPtr      = mark;
  Button2.OnPressPtr      = 0;

  Button3.OwnerScreen     = &Screen1;
  Button3.Order           = 2;
  Button3.Left            = 197;
  Button3.Top             = 39;
  Button3.Width           = 69;
  Button3.Height          = 58;
  Button3.Pen_Width       = 1;
  Button3.Pen_Color       = 0x0000;
  Button3.Visible         = 1;
  Button3.Active          = 1;
  Button3.Transparent     = 1;
  Button3.Caption         = Button3_Caption;
  Button3.TextAlign       = _taCenter;
  Button3.TextAlignVertical= _tavMiddle;
  Button3.FontName        = Tahoma11x13_Regular;
  Button3.PressColEnabled = 1;
  Button3.Font_Color      = 0x0000;
  Button3.VerticalText    = 0;
  Button3.Gradient        = 1;
  Button3.Gradient_Orientation = 0;
  Button3.Gradient_Start_Color = 0xFFFF;
  Button3.Gradient_End_Color = 0xC618;
  Button3.Color           = 0xC618;
  Button3.Press_Color     = 0xE71C;
  Button3.OnUpPtr         = 0;
  Button3.OnDownPtr       = 0;
  Button3.OnClickPtr      = mark;
  Button3.OnPressPtr      = 0;
  
  Button4.OwnerScreen     = &Screen1;
  Button4.Order           = 3;    //
  Button4.Left            = 50;
  Button4.Top             = 109;
  Button4.Width           = 69;
  Button4.Height          = 58;
  Button4.Pen_Width       = 1;
  Button4.Pen_Color       = 0x0000;
  Button4.Visible         = 1;
  Button4.Active          = 1;
  Button4.Transparent     = 1;
  Button4.Caption         = Button4_Caption;
  Button4.TextAlign       = _taCenter;
  Button4.TextAlignVertical= _tavMiddle;
  Button4.FontName        = Tahoma11x13_Regular;
  Button4.PressColEnabled = 1;
  Button4.Font_Color      = 0x0000;
  Button4.VerticalText    = 0;
  Button4.Gradient        = 1;
  Button4.Gradient_Orientation = 0;
  Button4.Gradient_Start_Color = 0xFFFF;
  Button4.Gradient_End_Color = 0xC618;
  Button4.Color           = 0xC618;
  Button4.Press_Color     = 0xE71C;
  Button4.OnUpPtr         = 0;
  Button4.OnDownPtr       = 0;
  Button4.OnClickPtr      = mark;
  Button4.OnPressPtr      = 0;   //
  
  Button5.OwnerScreen     = &Screen1;
  Button5.Order           = 4;
  Button5.Left            = 124;
  Button5.Top             = 109;
  Button5.Width           = 69;
  Button5.Height          = 58;
  Button5.Pen_Width       = 1;
  Button5.Pen_Color       = 0x0000;
  Button5.Visible         = 1;
  Button5.Active          = 1;
  Button5.Transparent     = 1;
  Button5.Caption         = Button5_Caption;
  Button5.TextAlign       = _taCenter;
  Button5.TextAlignVertical= _tavMiddle;
  Button5.FontName        = Tahoma11x13_Regular;
  Button5.PressColEnabled = 1;
  Button5.Font_Color      = 0x0000;
  Button5.VerticalText    = 0;
  Button5.Gradient        = 1;
  Button5.Gradient_Orientation = 0;
  Button5.Gradient_Start_Color = 0xFFFF;
  Button5.Gradient_End_Color = 0xC618;
  Button5.Color           = 0xC618;
  Button5.Press_Color     = 0xE71C;
  Button5.OnUpPtr         = 0;
  Button5.OnDownPtr       = 0;
  Button5.OnClickPtr      = mark;
  Button5.OnPressPtr      = 0;
  
  Button6.OwnerScreen     = &Screen1;
  Button6.Order           = 5;
  Button6.Left            = 197;
  Button6.Top             = 109;
  Button6.Width           = 69;
  Button6.Height          = 58;
  Button6.Pen_Width       = 1;
  Button6.Pen_Color       = 0x0000;
  Button6.Visible         = 1;
  Button6.Active          = 1;
  Button6.Transparent     = 1;
  Button6.Caption         = Button6_Caption;
  Button6.TextAlign       = _taCenter;
  Button6.TextAlignVertical= _tavMiddle;
  Button6.FontName        = Tahoma11x13_Regular;
  Button6.PressColEnabled = 1;
  Button6.Font_Color      = 0x0000;
  Button6.VerticalText    = 0;
  Button6.Gradient        = 1;
  Button6.Gradient_Orientation = 0;
  Button6.Gradient_Start_Color = 0xFFFF;
  Button6.Gradient_End_Color = 0xC618;
  Button6.Color           = 0xC618;
  Button6.Press_Color     = 0xE71C;
  Button6.OnUpPtr         = 0;
  Button6.OnDownPtr       = 0;
  Button6.OnClickPtr      = mark;
  Button6.OnPressPtr      = 0;
  
  Button7.OwnerScreen     = &Screen1;
  Button7.Order           = 6;    //
  Button7.Left            = 50;
  Button7.Top             = 179;
  Button7.Width           = 69;
  Button7.Height          = 58;
  Button7.Pen_Width       = 1;
  Button7.Pen_Color       = 0x0000;
  Button7.Visible         = 1;
  Button7.Active          = 1;
  Button7.Transparent     = 1;
  Button7.Caption         = Button7_Caption;
  Button7.TextAlign       = _taCenter;
  Button7.TextAlignVertical= _tavMiddle;
  Button7.FontName        = Tahoma11x13_Regular;
  Button7.PressColEnabled = 1;
  Button7.Font_Color      = 0x0000;
  Button7.VerticalText    = 0;
  Button7.Gradient        = 1;
  Button7.Gradient_Orientation = 0;
  Button7.Gradient_Start_Color = 0xFFFF;
  Button7.Gradient_End_Color = 0xC618;
  Button7.Color           = 0xC618;
  Button7.Press_Color     = 0xE71C;
  Button7.OnUpPtr         = 0;
  Button7.OnDownPtr       = 0;
  Button7.OnClickPtr      = mark;
  Button7.OnPressPtr      = 0;
  
  Button8.OwnerScreen     = &Screen1;
  Button8.Order           = 7;
  Button8.Left            = 124;
  Button8.Top             = 179;
  Button8.Width           = 69;
  Button8.Height          = 58;
  Button8.Pen_Width       = 1;
  Button8.Pen_Color       = 0x0000;
  Button8.Visible         = 1;
  Button8.Active          = 1;
  Button8.Transparent     = 1;
  Button8.Caption         = Button8_Caption;
  Button8.TextAlign       = _taCenter;
  Button8.TextAlignVertical= _tavMiddle;
  Button8.FontName        = Tahoma11x13_Regular;
  Button8.PressColEnabled = 1;
  Button8.Font_Color      = 0x0000;
  Button8.VerticalText    = 0;
  Button8.Gradient        = 1;
  Button8.Gradient_Orientation = 0;
  Button8.Gradient_Start_Color = 0xFFFF;
  Button8.Gradient_End_Color = 0xC618;
  Button8.Color           = 0xC618;
  Button8.Press_Color     = 0xE71C;
  Button8.OnUpPtr         = 0;
  Button8.OnDownPtr       = 0;
  Button8.OnClickPtr      = mark;
  Button8.OnPressPtr      = 0;
  
  Button9.OwnerScreen     = &Screen1;
  Button9.Order           = 8;
  Button9.Left            = 197;
  Button9.Top             = 179;
  Button9.Width           = 69;
  Button9.Height          = 58;
  Button9.Pen_Width       = 1;
  Button9.Pen_Color       = 0x0000;
  Button9.Visible         = 1;
  Button9.Active          = 1;
  Button9.Transparent     = 1;
  Button9.Caption         = Button9_Caption;
  Button9.TextAlign       = _taCenter;
  Button9.TextAlignVertical= _tavMiddle;
  Button9.FontName        = Tahoma11x13_Regular;
  Button9.PressColEnabled = 1;
  Button9.Font_Color      = 0x0000;
  Button9.VerticalText    = 0;
  Button9.Gradient        = 1;
  Button9.Gradient_Orientation = 0;
  Button9.Gradient_Start_Color = 0xFFFF;
  Button9.Gradient_End_Color = 0xC618;
  Button9.Color           = 0xC618;
  Button9.Press_Color     = 0xE71C;
  Button9.OnUpPtr         = 0;
  Button9.OnDownPtr       = 0;
  Button9.OnClickPtr      = mark;
  Button9.OnPressPtr      = 0;
  
  
}

static char IsInsideObject (unsigned int X, unsigned int Y, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height) { // static
  if ( (Left<= X) && (Left+ Width - 1 >= X) &&
       (Top <= Y)  && (Top + Height - 1 >= Y) )
    return 1;
  else
    return 0;
}


#define GetButton(index)              CurrentScreen->Buttons[index]

void DrawButton(TButton *Abutton) {
unsigned int ALeft, ATop;
  if (Abutton->Visible != 0) {
    if (object_pressed == 1) {
      object_pressed = 0;
      TFT_Set_Brush(Abutton->Transparent, Abutton->Press_Color, Abutton->Gradient, Abutton->Gradient_Orientation, Abutton->Gradient_End_Color, Abutton->Gradient_Start_Color);
    }
    else {
      TFT_Set_Brush(Abutton->Transparent, Abutton->Color, Abutton->Gradient, Abutton->Gradient_Orientation, Abutton->Gradient_Start_Color, Abutton->Gradient_End_Color);
    }
    TFT_Set_Pen(Abutton->Pen_Color, Abutton->Pen_Width);
    TFT_Rectangle(Abutton->Left, Abutton->Top, Abutton->Left + Abutton->Width - 1, Abutton->Top + Abutton->Height - 1);
    if (Abutton->VerticalText != 0)
      TFT_Set_Font(Abutton->FontName, Abutton->Font_Color, FO_VERTICAL_COLUMN);
    else
      TFT_Set_Font(Abutton->FontName, Abutton->Font_Color, FO_HORIZONTAL);
    TFT_Write_Text_Return_Pos(Abutton->Caption, Abutton->Left, Abutton->Top);
    if (Abutton->TextAlign == _taLeft)
      ALeft = Abutton->Left + 4;
    else if (Abutton->TextAlign == _taCenter)
      ALeft = Abutton->Left + (Abutton->Width - caption_length) / 2;
    else if (Abutton->TextAlign == _taRight)
      ALeft = Abutton->Left + Abutton->Width - caption_length - 4;

    if (Abutton->TextAlignVertical == _tavTop)
      ATop = Abutton->Top + 4;
    else if (Abutton->TextAlignVertical == _tavMiddle)
      ATop = Abutton->Top + ((Abutton->Height - caption_height) / 2);
    else if (Abutton->TextAlignVertical == _tavBottom)
      ATop = Abutton->Top + (Abutton->Height - caption_height - 4);

    TFT_Write_Text(Abutton->Caption, ALeft, ATop);
  }
}

void DrawScreen(TScreen *aScreen) {
 unsigned int order;
  unsigned short button_idx;
  TButton *local_button;
  char save_bled;

  object_pressed = 0;
  order = 0;
  button_idx = 0;
  CurrentScreen = aScreen;

  if ((display_width != CurrentScreen->Width) || (display_height != CurrentScreen->Height)) {
    save_bled = TFT_BLED;
    TFT_BLED           = 0;
    TFT_Init(CurrentScreen->Width, CurrentScreen->Height);
    TP_TFT_Init(CurrentScreen->Width, CurrentScreen->Height, 8, 9);                                  // Initialize touch panel
    TP_TFT_Set_ADC_Threshold(ADC_THRESHOLD);                              // Set touch panel ADC threshold
    TFT_Fill_Screen(CurrentScreen->Color);
    display_width = CurrentScreen->Width;
    display_height = CurrentScreen->Height;
    TFT_BLED           = save_bled;
  }
  else
    TFT_Fill_Screen(CurrentScreen->Color);


  while (order < CurrentScreen->ObjectsCount) {
    if (button_idx < CurrentScreen->ButtonsCount) {
      local_button = GetButton(button_idx);
      if (order == local_button->Order) {
        button_idx++;
        order++;
        DrawButton(local_button);
      }
    }

  }
}

void Get_Object(unsigned int X, unsigned int Y) {
  button_order        = -1;
  //  Buttons
  for ( _object_count = 0 ; _object_count < CurrentScreen->ButtonsCount ; _object_count++ ) {
    local_button = GetButton(_object_count);
    if (local_button->Active != 0) {
      if (IsInsideObject(X, Y, local_button->Left, local_button->Top,
                         local_button->Width, local_button->Height) == 1) {
        button_order = local_button->Order;
        exec_button = local_button;
      }
    }
  }

  _object_count = -1;
  if (button_order >  _object_count )
    _object_count = button_order;
}


void Process_TP_Press(unsigned int X, unsigned int Y) {
  exec_button         = 0;

  Get_Object(X, Y);

  if (_object_count != -1) {
    if (_object_count == button_order) {
      if (exec_button->Active != 0) {
        if (exec_button->OnPressPtr != 0) {

            
          exec_button->OnPressPtr();
          return;
        }
      }
    }

  }
}

void Process_TP_Up(unsigned int X, unsigned int Y) {

  switch (PressedObjectType) {
    // Button
    case 0: {
      if (PressedObject != 0) {
        exec_button = (TButton*)PressedObject;
        if ((exec_button->PressColEnabled != 0) && (exec_button->OwnerScreen == CurrentScreen)) {
          DrawButton(exec_button);
        }
        break;
      }
      break;
    }
  }


  Get_Object(X, Y);


  if (_object_count != -1) {
  // Buttons
    if (_object_count == button_order) {
      if (exec_button->Active != 0) {
        if (exec_button->OnUpPtr != 0)
          exec_button->OnUpPtr();
        if (PressedObject == (void *)exec_button)
          if (exec_button->OnClickPtr != 0){
          
            if(exec_button==&Button1)
            pressed_button=1;
          else if(exec_button==&Button2)
            pressed_button=2;
          else if(exec_button==&Button3)
            pressed_button=3;
          else if(exec_button==&Button4)
            pressed_button=4;
          else if(exec_button==&Button4)
            pressed_button=4;
          else if(exec_button==&Button5)
            pressed_button=5;
          else if(exec_button==&Button6)
            pressed_button=6;
          else if(exec_button==&Button7)
            pressed_button=7;
          else if(exec_button==&Button8)
            pressed_button=8;
          else if(exec_button==&Button9)
            pressed_button=9;
          
            exec_button->OnClickPtr();
            
            }
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  }
  PressedObject = 0;
  PressedObjectType = -1;
}

void Process_TP_Down(unsigned int X, unsigned int Y) {

  object_pressed      = 0;
  exec_button         = 0;

  Get_Object(X, Y);

  if (_object_count != -1) {
    if (_object_count == button_order) {
      if (exec_button->Active != 0) {
        if (exec_button->PressColEnabled != 0) {
          object_pressed = 1;
          DrawButton(exec_button);
        }
        PressedObject = (void *)exec_button;
        PressedObjectType = 0;
        if (exec_button->OnDownPtr != 0) {
          exec_button->OnDownPtr();
          return;
        }
      }
    }

  }
}

void Check_TP() {
  if (TP_TFT_Press_Detect()) {
    if (TP_TFT_Get_Coordinates(&Xcoord, &Ycoord) == 0) {
    // After a PRESS is detected read X-Y and convert it to Display dimensions space
      Process_TP_Press(Xcoord, Ycoord);
      if (PenDown == 0) {
        PenDown = 1;
        Process_TP_Down(Xcoord, Ycoord);
      }
    }
  }
  else if (PenDown == 1) {
    PenDown = 0;
    Process_TP_Up(Xcoord, Ycoord);
  }
}

void Init_MCU() {
  GPIO_Digital_Output(&GPIOE_BASE, _GPIO_PINMASK_9);
  TFT_BLED = 1;
  TFT_Set_Default_Mode();
  TP_TFT_Set_Default_Mode();
}

void Start_TP() {
  Init_MCU();

  InitializeTouchPanel();

  Delay_ms(1000);
  TFT_Fill_Screen(0);
  Calibrate();
  TFT_Fill_Screen(0);

  InitializeObjects();
  display_width = Screen1.Width;
  display_height = Screen1.Height;
  DrawScreen(&Screen1);
}