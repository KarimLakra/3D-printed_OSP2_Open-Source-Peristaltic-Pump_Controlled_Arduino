void pumpContrl(String dirP, int speedP, int strStpP){
  //DIR, CLK, ENBL
  //values as 300 means no changes  pumpConfig(300, 300, 300)
  int d = 0;
  if(Settings[4] == "CW"){d = 0;}
  if(Settings[4] == "ACW"){d = 1;}
  
  if(strStpP == 0){
    // In the Fill/empty page, when the button Start is green, reset direction, enable and clock.
    strStpPump = 0;
    StartPulses = 0;   
    analogWrite(DIR, 0);
    digitalWrite(CLK, 0);
    analogWrite(ENBL, 0);
  }else{
    // If the pump is not started no output changes happen
      if (strStpP < 300){
      StartPulses = 1;
      analogWrite(ENBL, 255);
      digitalWrite(CLK, CLKout);
      analogWrite(DIR, d * 255);
      strStpPump = strStpP;      
    }
    if (dirP == "CW" or dirP == "ACW"){
      analogWrite(DIR, d * 255 * strStpPump);
      Settings[4] = dirP;
    }
    if (speedP < 300){
      digitalWrite(CLK, CLKout);
      Settings[5] = speedP;
    }
  }
}



