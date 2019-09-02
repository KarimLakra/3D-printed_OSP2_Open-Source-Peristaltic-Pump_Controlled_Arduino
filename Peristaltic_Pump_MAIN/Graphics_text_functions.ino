void Home(){
  //print home screen
  printPage(0);
  myGLCD.setColor(255, 204,153); // Sets color to Blue
  drawFrameButton(TLX1, TLY1, TLX2, TLY2,1,0);//Select the default button 0
  Screen = 0;//Home page
  for(int i=0;i<3;i++){
    pumpConfig(i);//icons info pump configuration
  }
}

void Fourbuttons(){
  if(SlctdButn == 0){drawFrameButton(TLX1, TLY1, TLX2, TLY2,1,0); }//top left
  if(SlctdButn == 1){drawFrameButton(TRX1, TRY1, TRX2, TRY2,1,0);}//top right
  if(SlctdButn == 2){drawFrameButton(BLX1, BLY1, BTLX2, BLY2,1,0);}//bottom left
  if(SlctdButn == 3){drawFrameButton(BRX1, BRY1, BRX2, BRY2,1,0);}//bottom right
}
 
void printPage(int imgnm){
  // Setup the LCD
  
  myGLCD.clrScr();
  myGLCD.setColor(255,255,255);
  myGLCD.fillRect (0,0,480,320);//clear background
  
  myGLCD.setColor(153,217,234);
  myGLCD.fillRect (0,0,480,22);
  myGLCD.fillRect (0,298,479,319);
  
  myGLCD.setColor(0,0,0);
  myGLCD.drawLine (0,23,436,23);
  myGLCD.drawLine (436,23,436,296);
  myGLCD.drawLine (0,296,436,296);
  //Home 
  if(imgnm == 0){
    printBMP(61, 47, 93, 98, 10);//Fill/Empty icon
    printBMP(285, 45, 89, 103, 11);//Programs icon
    printBMP(61, 171, 93, 106, 12);//Settings icon
    printBMP(293, 171, 68, 95, 13);//About icon
    
  }
  //Fill/Empty
  if(imgnm == 1){
    if(strStpPump == 0){printBMP(56, 48, 96, 96, 2);}//Start icon
    if(strStpPump == 1){printBMP(56, 48, 96, 96, 3);}//Stop icon
    printBMP(229, 43, 196, 108, 18);//inc/decrease icon
    if(Settings[4] == "CW"){printBMP(54, 174, 100, 100, 5);}//Fill icon
    if(Settings[4] == "ACW"){printBMP(54, 174, 100, 100, 4);}//Empty icon
    printBMP(286, 184, 79, 84, 19);//return icon
    
  }
  //Programs
  if(imgnm == 6){   
    printBMP(9, 44, 198, 108, 24);//fixed prog
    printBMP(229, 44, 198, 108, 25);//incremental prog
    printBMP(9, 171, 198, 108, 26);//prog from file
    printBMP(286, 184, 79, 84, 19);//return icon
  }
//Settings
  if(imgnm == 9){   
    printBMP(8, 42, 420, 140, 27);//setting fields
    printBMP(47, 258, 130, 25, 28);//Save button
    printBMP(260, 258, 130, 25, 29);//Quit button
  }
  //About
  if(imgnm == 30){   
    printBMP(0, 0, 480, 320, 30);//About image
  }
}

void printBMP(int bmpx1, int bmpy1, int bmpx2, int bmpy2, int pic){
  res=myFiles.loadBitmap(bmpx1, bmpy1, bmpx2, bmpy2, files[pic]);
  if (res!=0)
  {
    if (res==0x10)
    {
      myGLCD.print("File not found...", 0, 0);
      myGLCD.print(files[pic], 0, 14);
    }else{
      myGLCD.print("ERROR: ", 0, 0);
      myGLCD.printNumI(res, 56, 0);
    }
  }
}

//background color to clear old text
void Backcolr(){myGLCD.setColor(153,217,234);}

//background and background color for text
void TXTbackcolr(){myGLCD.setBackColor(VGA_TRANSPARENT);}//(153,217,234)

//text color
void TXTcolr(){myGLCD.setColor(0,0,0);}

// Top title
void titles(String title){
  Backcolr();
  myGLCD.fillRoundRect (0,0,480,20);//clear background
  myGLCD.setFont(BigFont);
  Backcolr(); // Sets the background color of the area where the text will be printed to
  TXTcolr();
  myGLCD.print(title, 10, 4); // Prints the string on the screen
}

// print foot page
void foot(String foot){
  Backcolr();
  myGLCD.fillRoundRect (0,298,460,320);//clear background
  myGLCD.setFont(SmallFont);
  TXTbackcolr(); // Sets the background color of the area where the text will be printed to
  TXTcolr(); // Sets blue color
  myGLCD.print(foot, 10, 300); // Prints the string on the screen
}

// Highlights the button when pressed
void drawFrameButton(int x1, int y1, int x2, int y2, int boldF, int clrs) {
  if(clrs == 0){myGLCD.setColor(23,93,255);}//Blue color for parent buttons
  if(clrs == 1){myGLCD.setColor(34, 177, 76);} //Green for Start Edit buttons
  if(clrs == 2){myGLCD.setColor(204,6,41);}//Red color for editing values buttons
  if(boldF == 1){
    //make selection bold
    myGLCD.drawRoundRect (x1-1, y1-1, x2+1, y2+1);  
    myGLCD.drawRoundRect (x1-2, y1-2, x2+2, y2+2);  
    myGLCD.drawRoundRect (x1-3, y1-3, x2+3, y2+3);  
  }
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}

//Clear selection
void clearselection(int TL, int TR, int BL, int BR, int BLD){
  if(TL == 1){clearFrameButton(TLX1, TLY1, TLX2, TLY2, BLD);}
  if(TR == 1){clearFrameButton(TRX1, TRY1, TRX2, TRY2, BLD);}
  if(BL == 1){clearFrameButton(BLX1, BLY1, BTLX2, BLY2, BLD);}
  if(BR == 1){clearFrameButton(BRX1, BRY1, BRX2, BRY2, BLD);}
}

//Clear highlight unselected button
void clearFrameButton(int x1, int y1, int x2, int y2, int boldF) {
  myGLCD.setColor(255,255,255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  if(boldF == 1){
    //clear bold selection
    myGLCD.drawRoundRect (x1-1, y1-1, x2+1, y2+1);  
    myGLCD.drawRoundRect (x1-2, y1-2, x2+2, y2+2);  
    myGLCD.drawRoundRect (x1-3, y1-3, x2+3, y2+3);  
  }
}

//print seven segment numbers
void printNum(int Val, int x, int y){
  myGLCD.setFont(SevenSegNumFont); // Sets the font to big
  myGLCD.setColor(255,255,255); // Sets green color
  myGLCD.fillRoundRect (x, y-5, x+100, y+53);
  //myGLCD.setBackColor(255,255,255);
  myGLCD.setColor(0,0,0); // Sets green color
  if (Val < 10 and Val < 100){x = x + 60;}
  if (Val >= 10 and Val < 100){x = x + 30;}
  myGLCD.printNumI(Val, x, y);
}

//clear child button highlight
void clearSelectChld(int clrChld){
  //clear selection Start/Edit
  if(clrChld == 0){
    EditFlag = 0; progFlag = 0; SlctdButnChld = 0;
    int j = 0;
    for(int i=0; i<3; i++){
      //clear all Start Edit buttons selection
      clearFrameButton(EditCoord[i+j],EditCoord[i+j+1],EditCoord[i+j+2],EditCoord[i+j+3],0);//clear selection Start button
      clearFrameButton(StartCoord[i+j],StartCoord[i+j+1],StartCoord[i+j+2],StartCoord[i+j+3],0);//clear selection Start button
      j = j + 3;
    }
  }
  //clear program from file selection
  if(clrChld == 1){
    EditFlag = 0;//exit edition mode
    SlctdButnChld = 222;//select edit button
    int j = 28;//key offset for program buttons coordinations from array
    for(int i=0; i<3; i++){
      //clear all selected program buttons
      clearFrameButton(EditValCoord[i+j],EditValCoord[i+j+1],EditValCoord[i+j+2],EditValCoord[i+j+3],0);//clear selection Start button
      j = j + 3;
    }
  }
}

//update values when user make changes
void printEditVal(String val, int posXV, int posYV, int screen){
  myGLCD.setFont(BigFont);
  myGLCD.setColor(60,121,172);
  if(screen == 0){myGLCD.fillRect (posXV, posYV, posXV+82, posYV+15);}//for program screen
  if(screen == 1){myGLCD.fillRect (posXV, posYV, posXV+170, posYV+15);}//for settings
  myGLCD.setColor(0,0,0);
  myGLCD.setBackColor(60,121,172); // Sets the background color of the area where the text will be printed to
  myGLCD.print(val, posXV, posYV); // Prints the string on the screen
  myGLCD.setBackColor(VGA_TRANSPARENT);
}

//------------------------------
// Move cursor Home screen
//prsd is the physical pressed button, slBtn is the selected button in the screen
void MoveCursor(String prsd, char slBtn){
  myGLCD.setColor(255,255,255); // Sets color to white
  if (prsd == "UP"){
    if(slBtn != 0 and slBtn !=1 ){
      SlctdButn = SlctdButn - 2;
      clearselection(0,0,1,1,1);
    }
  }
  if (prsd == "DWN"){
    if(slBtn != 2 and slBtn != 3 ){
      SlctdButn = SlctdButn + 2;
      clearselection(1,1,0,0,1);
    }
  }
  if (prsd == "LFT"){
    if(slBtn != 0 and slBtn != 2 ){
      SlctdButn = SlctdButn - 1;
      clearselection(0,1,0,1,1);
    }
  }
  if (prsd == "RGHT"){
    if(slBtn != 1 and slBtn != 3 ){
      SlctdButn = SlctdButn + 1;
      clearselection(1,0,1,0,1);
    }
  }
  if (prsd == "OK"){
    if (slBtn == 0){
      //Fill-Empty
      Serial.println("Fill-Empty!");
      pressed = "";
      prsd = "";
      FillEmpty();
      SlctdButn = 0;
    }
    if (slBtn == 1){
      //Programs
      Serial.println("Programs!");
      pressed = "";
      prsd = "";
      Screen = 2;
      Programs();
      SlctdButn = 0;
    }
    if (slBtn == 2){
      //Settings
      Serial.println("Settings!");
      Screen = 3;
      SlctdButn = 100;// no selected button
      Setting();
    }
    if (slBtn == 3){
      //About the pump
      Serial.println("About!");
      Screen = 4;
      SlctdButn = 100;// no selected button
      About();
      pressed = "";
    }
    //SlctdButn = 0;
  }
}
