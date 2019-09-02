void progFromFile(int progN){
  //program from files
  int keyArr;//the key from where the program starts
  uint32_t Intr;//Interval
  float quant;//quantity
  int rep = 18;//doses
  int repe = 0;//repeat counter
  float quantCounter = 0;//quantity counter
  
  if(progN == 0){keyArr = 7;Intr = progDataArray[8].toInt();}
  if(progN == 1){keyArr = 27;Intr = progDataArray[28].toInt();}
  if(progN == 2){keyArr = 47;Intr = progDataArray[48].toInt();}
  
  uint32_t c = 0;//counter interval
  float qua = 0;//quantity counter
  String inf = "";//show millis pumped
  
  tmr = millis();
  Serial.println(c);
  while(state == HIGH and repe < rep){
    quant = progDataArray[keyArr+2+repe].toFloat()*Settings[3].toFloat();//quantity
    c = c + Intr;//next interval
    while(state == HIGH and millis() < tmr+(c*1000)){
      if(qua < quant*Settings[2].toFloat()){
        //set pump
        //pumpContrl(int dirP, int speedP, int strStpP)
        pumpContrl("", 300, 1);
        digitalWrite(CLK, 1);
        delayMicroseconds(Settings[1].toInt());//invert time to get increasing speed by increasing speedPump
        digitalWrite(CLK, 0);
        delayMicroseconds(Settings[1].toInt());
        pumpContrl("", 300, 0);
        qua = qua + 1;
        if(qua >= quant*Settings[2].toFloat()){
          quantCounter = quantCounter + progDataArray[keyArr+2+repe].toFloat();
          inf = quantCounter;//show float if value under 10
          inf = inf +"ml";
          foot(inf);
        }
      }
      if(repe+1==rep and qua >= quant*Settings[2].toFloat()){break;}//get out from here immediately when the last dose is reached, don't wait the timing
    }
    qua = 0;repe++;    
  }
  inf = inf + " Done!";
  foot(inf);
  Serial.println("Done!");
}

