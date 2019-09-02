void Setting(){  
  printPage(9);//config background
  TXTbackcolr();
  titles("Pump Setting");
  drawFrameButton(SetgCoord[0],SetgCoord[1],SetgCoord[2],SetgCoord[3],0,2);//select top value "Pump Control"
  SlctdButnChld = 300;//select top button "Pump control"
  
  ReadSD(name[5], 1);//read settings from SD card
  arrCountr=0;
  for(int i=0;i<6; i++){
    Serial.println(Settings[i]);
  }
  for(int i=0;i<3;i++){
    pumpConfig(i);//icons info pump configuration
  }
  
}
float GreaterLessThan(float Valu1, float Valu2, float steps, bool comp){
  if(comp == 0){
    if(Valu1 > Valu2){
      Valu1 = Valu1 - steps;
    }
  }
  if(comp == 1){
    if(Valu1 < Valu2){
      Valu1 = Valu1 + steps;
    }
  }
  return Valu1;
}
void CursorSetting(String prsd, int slBtn){
  if (prsd == "UP"){
    if(slBtn > 300){
      SlctdButnChld = SlctdButnChld - 1;
      int btn = (SlctdButnChld - 300)*4;//get button coordinations from button number
      clearFrameButton(SetgCoord[btn+4],SetgCoord[btn+5],SetgCoord[btn+6],SetgCoord[btn+7],0);//select top value "Pump Control"
      drawFrameButton(SetgCoord[btn],SetgCoord[btn+1],SetgCoord[btn+2],SetgCoord[btn+3],0,2);
    }
  }
  if (prsd == "DWN"){
    if(slBtn < 308){
      int btn = (SlctdButnChld - 300)*4;
      clearFrameButton(SetgCoord[btn],SetgCoord[btn+1],SetgCoord[btn+2],SetgCoord[btn+3],0);//select top value "Pump Control"
      drawFrameButton(SetgCoord[btn+4],SetgCoord[btn+5],SetgCoord[btn+6],SetgCoord[btn+7],0,2);
      SlctdButnChld++;
    }
  }
  if (prsd == "LFT"){
    if(slBtn == 300){
      Settings[0] = "Local";//control local/remote
      //pumpConfig(1);//icon status??? freezes here
      printEditVal(Settings[0], SetgCoord[0]+248, 44,1);
      Serial.println(Settings[0]);
    }
    if(slBtn == 301){
      Settings[1] = GreaterLessThan(Settings[1].toFloat(),150,1,0);//pulse width microseconds
      printEditVal(Settings[1], SetgCoord[0]+248, 64,1);
    }
    if(slBtn == 302){
      Settings[2] = GreaterLessThan(Settings[2].toFloat(),1,1,0);//calibration for 0.1 ml
      printEditVal(Settings[2], SetgCoord[0]+248, 84,1);
    }
    if(slBtn == 303){
      Settings[3] = GreaterLessThan(Settings[3].toFloat(),1,0.1,0);//calibration for 1 ml
      printEditVal(Settings[3], SetgCoord[0]+248, 104,1);
    }
    if(slBtn == 304){
      Settings[4] = "CW";//pump direction
      //pumpConfig(2);//icon status??? freezes here
      printEditVal(Settings[4], SetgCoord[0]+248, 124,1);
    }
    if(slBtn == 305){
      Settings[5] = GreaterLessThan(Settings[5].toFloat(),1,1,0);//default pump speed only for Fill/Empty
      printEditVal(Settings[5], SetgCoord[0]+248, 144,1);
    }
    if(slBtn == 308){
      SlctdButnChld = SlctdButnChld - 1;
      int btn = (SlctdButnChld - 300)*4;//get button coordinations from button number
      clearFrameButton(SetgCoord[btn+4],SetgCoord[btn+5],SetgCoord[btn+6],SetgCoord[btn+7],0);//select top value "Pump Control"
      drawFrameButton(SetgCoord[btn],SetgCoord[btn+1],SetgCoord[btn+2],SetgCoord[btn+3],0,2);
    }
  }
  if (prsd == "RGHT"){
    if(slBtn == 300){
      Settings[0] = "Remote";
      //pumpConfig(1);//icon status??? freezes here
      printEditVal(Settings[0], SetgCoord[0]+248, 44,1);//control local/remote
      Serial.println(Settings[0]);
    }
    if(slBtn == 301){
      Settings[1] = GreaterLessThan(Settings[1].toFloat(),10000,1,1);//pulse width microseconds
      printEditVal(Settings[1], SetgCoord[0]+248, 64,1);
    }
    if(slBtn == 302){
      Settings[2] = GreaterLessThan(Settings[2].toFloat(),1000,1,1);//calibration for 0.1 ml
      printEditVal(Settings[2], SetgCoord[0]+248, 84,1);
    }
    if(slBtn == 303){
      Settings[3] = GreaterLessThan(Settings[3].toFloat(),100,0.1,1);//calibration for 1 ml
      printEditVal(Settings[3], SetgCoord[0]+248, 104,1);
    }
    if(slBtn == 304){
      Settings[4] = "ACW";//pump direction
      //pumpConfig(2);//icon status??? freezes here
      printEditVal(Settings[4], SetgCoord[0]+248, 124,1);
    }
    if(slBtn == 305){
      Settings[5] = GreaterLessThan(Settings[5].toFloat(),100,1,1);//default pump speed only for Fill/Empty
      printEditVal(Settings[5], SetgCoord[0]+248, 144,1);
    }
    if(slBtn == 307){
      int btn = (SlctdButnChld - 300)*4;
      clearFrameButton(SetgCoord[btn],SetgCoord[btn+1],SetgCoord[btn+2],SetgCoord[btn+3],0);//select top value "Pump Control"
      drawFrameButton(SetgCoord[btn+4],SetgCoord[btn+5],SetgCoord[btn+6],SetgCoord[btn+7],0,2);
      SlctdButnChld++;
    }
  }
  
  if (prsd == "OK"){
    if(slBtn == 306){
      resetSett = 1;//set flag factory settings
      WriteSD(name[5], 6, 0);//Save changes cfg.txt to SD card
      Serial.println("The reset was successful!");
      foot("The reset was successful!");
    }
    if(slBtn == 307){
      WriteSD(name[5], 6, 0);//Save changes cfg.txt to SD card
      Serial.println("Changes are saved to SD card!");
      foot("Changes are saved to SD card!");
    }
    if(slBtn == 308){
      Serial.println("Quit Setting!");
      Screen = 0;
      Home();
      SlctdButn = 0;
    }
  }
  
  
}

