void FillEmpty(){
  printPage(1);
  TXTbackcolr();
  titles("Fill/Empty->");
  picxSS2 = 96, picySS2=96;//start stop size
  picxFE2 = 100, picyFE2=100;//Fill empty size
  
  //Pump speed
  TXTbackcolr();
  printNum(Settings[5].toInt(), 280, 75);
  myGLCD.setFont(BigFont);
  Screen = 1;
  for(int i=0;i<3;i++){
    pumpConfig(i);//icons info pump configuration
  }
}

void MoveCursorFillEmty(String prsd, int slBtn){
  //Fill/Empty screen->Pump speed percent
  if(SlctdButn == 10){drawFrameButton(224, 41, 431, 66,1,0); }//top
  if(SlctdButn == 11){drawFrameButton(224, 68, 431, 127,1,0);}//mid
  if(SlctdButn == 12){drawFrameButton(224, 128, 431, 153,1,0);}//bottom

  if (prsd == "UP"){
    if(slBtn != 0 and slBtn !=1 and Screen != 10){
      SlctdButn = SlctdButn - 2;
      clearselection(0,0,1,1,1);//clear bottom left and right
    }
    if(Screen == 10){
      if(slBtn != 10){
        if(slBtn == 11){
          if(SlctdButn == 11){clearFrameButton(224, 68, 431, 127, 1);}//mid
          SlctdButn = 10;
          drawFrameButton(224, 41, 431, 66,1,0);
        }
        if(slBtn == 12){
          if(SlctdButn == 12){clearFrameButton(224, 128, 431, 153, 1);}//bottom
          SlctdButn = 11;
          drawFrameButton(224, 68, 431, 127,1,0);
        }
      }
    }
  }
  
  if (prsd == "DWN"){
    if(slBtn != 2 and slBtn != 3 and Screen != 10){
      SlctdButn = SlctdButn + 2;
      clearselection(1,1,0,0,1);//clear top left and right
    }
    if(Screen == 10){
      if(slBtn != 12){
        if(slBtn == 10){
          //if(SlctdButn == 10){clearFrameButton(244, 41, 453, 66, 1); }//top
          clearFrameButton(224, 41, 431, 66, 1);
          SlctdButn = 11;
          drawFrameButton(224, 68, 431, 127,1,0);//mid
        }
        if(slBtn == 11){
          //if(SlctdButn == 11){clearFrameButton(244, 68, 453, 127, 1);}//mid
          clearFrameButton(224, 68, 431, 127, 1);
          SlctdButn = 12;
          drawFrameButton(224, 128, 431, 153,1,0);
        }
      }
    }
  }
  
  if (prsd == "LFT"){
    if(slBtn == 1 or  slBtn == 3){
      SlctdButn = SlctdButn - 1;
      clearselection(0,1,0,1,1);//clear top right and bottom right
    }
  }
  if (prsd == "RGHT"){
    if(slBtn != 1 and  slBtn != 3){
      if(slBtn == 0 or slBtn == 2 ){
        SlctdButn = SlctdButn + 1;
        clearselection(1,0,1,0,1);//clear top left and bottom left
      }
    }
  }
  
  if (prsd == "OK"){
    if (slBtn == 0){
      //Start Stop
      if (strStpPump == 0){
        printBMP(56,48,picxSS2,picySS2,3);//Start
        strStpPump = 1;
        pumpContrl("", 300, 1);
        Serial.println("Start!");
        state = HIGH;
      }else{
        printBMP(56,48,picxSS2,picySS2,2);//Stop
        Serial.println("Stop!");
        strStpPump = 0;
        state = LOW;
        pumpContrl("", 300, 0);
      }
    }
    
    if (slBtn == 1){
      //Pump speed
      TXTbackcolr();
      titles("Fill/Empty->Pump speed");
      Serial.println("Speed %!");
      clearFrameButton(TRX1, TRY1, TRX2, TRY2, 1);
      Screen = 10;
      SlctdButn = 10;
      drawFrameButton(224, 41, 431, 66,1,0);//top
    }
    if (slBtn == 10){
      //Pump speed UP
      if (Settings[5].toInt() < 100){
        Settings[5] = Settings[5].toInt() + 1;
        pumpContrl("", Settings[5].toInt(), 300);
      }
      Serial.println("Speed Up %!");
      Serial.println(Settings[5]); 
      printNum(Settings[5].toInt(), 280, 73);
    }
    if (slBtn == 11){
      //Leave speed setting
      myGLCD.setFont(BigFont);
      myGLCD.setColor(102, 38, 21); // Sets green color
      myGLCD.fillRoundRect (0, 0, 420, 20); // Draws filled rounded rectangle
      TXTbackcolr();
      titles("Fill/Empty->");
      Serial.println("Speed % quit!");
      clearFrameButton(224, 68, 431, 127, 1);//mid
      drawFrameButton(TRX1, TRY1, TRX2, TRY2,1,0);//top right
      Screen = 1;
      SlctdButn = 1;
    }
    
    if (slBtn == 12){
      //Pump speed UP
      if (Settings[5].toInt() > 0){
        Settings[5] = Settings[5].toInt() - 1;
        //Pulses();
        pumpContrl("", Settings[5].toInt(), 300);
      }
      Serial.println("Speed Dwn %!");
      Serial.println(Settings[5]);
      printNum(Settings[5].toInt(), 280, 73);
    }
    if (slBtn == 2){
      //Fill Empty
      //picxFE2 = 100, picyFE2=100;
      if (Settings[4] == "ACW"){
        printBMP(54,174,picxFE2,picyFE2,5);//Fill
        Serial.println("Empty!");
        Settings[4] = "CW";
        pumpContrl("CW", 300, 300);
      }else{
        printBMP(54,174,picxFE2,picyFE2,4);//Empty
        Serial.println("Fill!");
        Settings[4] = "ACW";
        pumpContrl("ACW", 300, 300);
      }
      pumpConfig(2);//icons info pump configuration
    }
    if (slBtn == 3){
      //Return button
      Serial.println("Return!");
      Screen = 0;
      Home();
      SlctdButn = 0;
    }
  }
}

void Pulses(){
  //pump speed control for Fill/empty
  while(state == HIGH and strStpPump == 1){
    digitalWrite(CLK, 1);
    delayMicroseconds(1500-(Settings[5].toInt()*11));//invert time to get increasing speed by increasing speedPump
    digitalWrite(CLK, 0);
    delayMicroseconds(1500-(Settings[5].toInt()*11));
  }
}
