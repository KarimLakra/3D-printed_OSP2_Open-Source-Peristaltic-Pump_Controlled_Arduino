void pumpConfig(int btN){
  //local remote icon
  int sizexy=38, pozx=441;
  if(btN == 0){
    int m=8; 
    if(state == HIGH){m=7;}
    printBMP(pozx,24,sizexy,sizexy,m);//icon run    
  }
  if(btN == 1){
    int m=15;
    if(Settings[0] == "Local"){m=14;}
    printBMP(pozx,64,sizexy,sizexy,m);//icon LOCAL
  }
  if(btN == 2){
    int m=17;
    if(Settings[4] == "CW"){m=16;}
    printBMP(pozx,104,sizexy,sizexy,m);//icon CW
  }
}

void blink(){
  //interrupt the pump by pressing left button
  state = !state;
  pumpConfig(0);
  //Serial.println(state);
}


