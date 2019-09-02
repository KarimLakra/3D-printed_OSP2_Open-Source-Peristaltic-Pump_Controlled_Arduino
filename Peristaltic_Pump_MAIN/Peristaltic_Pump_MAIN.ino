#include <tinyFAT.h>
#include <UTFT.h>
#include <UTFT_tinyFAT.h>

#include <SPI.h>
#include "SdFat.h"
const uint8_t chipSelect = SS;
SdFat sd;
SdFile Progfiles;

UTFT myGLCD(ILI9486,38,39,40,41);
UTFT_tinyFAT myFiles(&myGLCD);

//Fonts declaration
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

byte res;
word result;
char textBuffer[81];
String progDataArray[80]={};//Array to hold programs data
String Settings[6]={};//setting variables
int arrCountr=0;//counter for the array that holds the programs data
String FIXprog[] = {"Interval: ","Quantity: ","Repeat: ",
                    "Interval: ","Start quantity: ","Increment: ","Repeat: "};
String SettinTxt[] = {"Pump control: ","Pulse width : ","Calib 0.1 ml: ",
                    "Calibr. 1 ml: ","Pump direct.: ","FilEmp speed: "};
String FactorySett[] = {"Local","200","40","10","CW","1"};//data to reset settigns
bool resetSett = 0;//when set, a factory reset will be executed

//keypad pins
//int UP = A0, LFT = A1, OK = A2, RGHT = A3, DWN = A4;
int UP = A0, LFT = 21, OK = A2, RGHT = A3, DWN = A4;//LFT for interrupt
int UPState, LEFTState, OKState, RIGHTState, DOWNState;

//pump pins
int DIR = 2, CLK = 3, ENBL = 4; //direction  and enable pins
//const byte interruptPin = 21;// interrupt pin
int interruptPin = 21;// interrupt pin
volatile byte state = LOW;//state changed when the interrupt is detected

String pressed=""; //Pressed button
int Screen=0, SlctdButn, SlctdButnChld;//Home page screen= 0, selected button, and selected button child
int EditFlag=0, progFlag=0;//set Edit when a program is in edition mode, progFlag is set when OK button is pressed while a program button is selected
int yVa; // y coordination to print programs values
int slctdProg = 100;// selected program from file, 100 no program selected

//buttons coordinations
int TLX1 = 4, TLY1 = 41, TLX2 = 211, TLY2 = 153; //Top left box
int TRX1 = 224, TRY1 = 41, TRX2 = 431, TRY2 = 153; //top right box
int BLX1 = 4, BLY1 = 168, BTLX2 = 211, BLY2 = 281; //Bottom left box
int BRX1 = 224, BRY1 = 168, BRX2 = 431, BRY2 = 281; //Bottom right box

//coordination for edit text
int PosXEdtTxt = 121;//position for fixed quantity program first row

//Start array buttons coordinations, TL TR BL BR
int StartCoord[] = {8, 124, 101, 154,
                    227, 125, 319, 154,
                    8, 251, 101, 280};

//Edit array buttons coordinations, TL TR BL BR
int EditCoord[] = {113, 124, 206, 154,
                   331, 125, 424, 154,
                   112, 251, 206, 280};

//Fixed quantity values coordination 0-11, incremental 12-27, and program from files 28-39
int EditValCoord[] = {7, 42, 208, 64,
                   7, 62, 208, 84,
                   7, 82, 208, 104,
                   229, 42, 228, 61,
                   229, 62, 228, 81,
                   229, 82, 228, 101,
                   229, 102, 228, 121,
                   7, 170, 208, 195,
                   7, 196, 208, 221,
                   7, 222, 208, 247
                   };
//Setting array buttons coordinations
int SetgCoord[] = {6, 41, 430, 61,
                   6, 61, 430, 81,
                   6, 81, 430, 101,
                   6, 101, 430, 121,
                   6, 121, 430, 141,
                   6, 141, 430, 161,
                   6, 161, 430, 181,
                   45, 254, 179, 282,
                   258, 254, 391, 282};

//pump state
bool strStpPump = 0;

//Pulses & Time variables
bool CLKout; //holds the pulse stat
bool StartPulses = 0; // start stop the pulse generator
uint32_t tmr;//tmr to hold seconds for programs

//programs variables
bool fixedProg = false;

char* files480[]={"MENU.RAW","FLEMPT.RAW", "START.RAW", "STOP.RAW", "FILL.RAW", 
                  "EMPTY.RAW","PRGRMS.RAW", "RUNP.RAW", "POZP.RAW", "CFG.RAW", 
                  "FLE.RAW", "PRG.RAW", "SET.RAW", "ABT.RAW","LOC.RAW", 
                  "REM.RAW", "CW.RAW", "ACW.RAW", "IND.RAW", "RTN.RAW",
                  "FLDS.RAW","FLDB.RAW","STRT.RAW","EDT.RAW","FIXP.RAW",
                  "INCP.RAW","FLP.RAW","CFGR.RAW","SAV.RAW","QIT.RAW",
                  "ABTINF.RAW"}; // 480x320
char* files[32];

const char* name[] = {"FIX.TXT", "INC.TXT", "PROG00.TXT", "PROG01.TXT" ,"PROG02.TXT", "CFG.TXT"};
  
int picsize_x = 480, picsize_y = 320;//background screen img
int picxSS2, picySS2, picxFE2, picyFE2 ;//icons
int picxRP = 450, picyRP = 2;//run/pause coord
boolean display_rendertime=false;  // Set this to true if you want the rendertime to be displayed after a picture is loaded
boolean display_filename=true;  // Set this to false to disable showing of filename

void setup() {

  //motor control pins
  pinMode(DIR, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(ENBL, OUTPUT);

  myGLCD.InitLCD();
  myGLCD.clrScr();
  file.initFAT();

  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    Serial.println("begin failed");
    return;
  }
  
  myGLCD.setColor(255,255,255);
  myGLCD.setFont(SmallFont);
  for (int z=0; z<sizeof(files480)/sizeof(*files480);z++){
    files[z] = files480[z];
  }

  Serial.begin(9600);
  //Serial.begin(115200);
  
  //keys
  SlctdButn = 0;
  pinMode(A0, INPUT_PULLUP);
  //pinMode(A1, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin),blink, RISING);

  ReadSD(name[5], 1);//read settings from SD card

  Home();
  Serial.println("Ready!");
}

void loop() {
  
  Pulses();
  
  pressed = "";//no button pressed
  UPState = analogRead(UP);
  //LEFTState = analogRead(LFT);
  LEFTState = digitalRead(LFT);
  OKState = analogRead(OK);
  RIGHTState = analogRead(RGHT);
  DOWNState = analogRead(DWN);

  //reading inputs
  if(UPState <= 100){pressed = "UP";}
  if(LEFTState == LOW){pressed = "LFT";}
  if(OKState <= 100){pressed = "OK";}
  if(RIGHTState <= 100){pressed = "RGHT";}
  if(DOWNState <= 100){pressed = "DWN";}

  if(pressed != ""){
    if (Screen == 0){
      //Home screen
      MoveCursor(pressed, SlctdButn);
      Fourbuttons();
    }
    if (Screen == 1 or Screen == 10){
      //Fill/Empty screen
      MoveCursorFillEmty(pressed, SlctdButn);
      if (Screen == 1){Fourbuttons();}
    }
    
    if (Screen == 2){
      //programs
      MoveCursorProgs(pressed, SlctdButn, SlctdButnChld);
      Fourbuttons();
    }

    if (Screen == 3){
      //Setting
      CursorSetting(pressed, SlctdButnChld);
      //Serial.println(SlctdButnChld);
    }
    
    if (Screen == 4){
      //About
      anykey(pressed);
    }
  }

  delay(100);
}

