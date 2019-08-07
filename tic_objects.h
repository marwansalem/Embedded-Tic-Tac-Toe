typedef enum {_taLeft, _taCenter, _taRight} TTextAlign;
typedef enum {_tavTop, _tavMiddle, _tavBottom} TTextAlignVertical;

typedef struct Screen TScreen;

typedef struct  Button {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          Pen_Width;
  unsigned int  Pen_Color;
  char          Visible;
  char          Active;
  char          Transparent;
  char          *Caption;
  TTextAlign    TextAlign;
  TTextAlignVertical TextAlignVertical;
  const char    *FontName;
  unsigned int  Font_Color;
  char          VerticalText;
  char          Gradient;
  char          Gradient_Orientation;
  unsigned int  Gradient_Start_Color;
  unsigned int  Gradient_End_Color;
  unsigned int  Color;
  char          PressColEnabled;
  unsigned int  Press_Color;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TButton;

struct Screen {
  unsigned int           Color;
  unsigned int           Width;
  unsigned int           Height;
  unsigned int           ObjectsCount;
  unsigned int           ButtonsCount;
  TButton                * const code *Buttons;
};

extern   TScreen                Screen1;
extern   TButton               Button1;
extern   TButton               Button2;
extern   TButton               Button3;
extern   TButton               Button4;
extern   TButton               Button5;
extern   TButton               Button6;
extern   TButton               Button7;
extern   TButton               Button8;
extern   TButton               Button9;
extern   TButton                * const code Screen1_Buttons[9];


/////////////////////////
// Events Code Declarations
void mark();
/////////////////////////

/////////////////////////////////
// Caption variables Declarations
extern char Button1_Caption[];
extern char Button2_Caption[];
extern char Button3_Caption[];
extern char Button4_Caption[];
extern char Button5_Caption[];
extern char Button6_Caption[];
extern char Button7_Caption[];
extern char Button8_Caption[];
extern char Button9_Caption[];
/////////////////////////////////

void DrawScreen(TScreen *aScreen);
void DrawButton(TButton *aButton);
void Check_TP();
void Start_TP();
void Process_TP_Press(unsigned int X, unsigned int Y);
void Process_TP_Up(unsigned int X, unsigned int Y);
void Process_TP_Down(unsigned int X, unsigned int Y);