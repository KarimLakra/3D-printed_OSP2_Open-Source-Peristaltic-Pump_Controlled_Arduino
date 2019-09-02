void progs(const char *filename, word result, int count, int dataSD){
  //count is the line number
  if (result==BUFFER_OVERFLOW){
    Serial.print(textBuffer);//print the hole line from text file
  }else{
    //Serial.println(textBuffer);
    String textb = String(textBuffer);
    if(dataSD == 0){
      if(filename == "FIX.TXT"){
        if(count > 1){
          //line3
          textb.remove(0,8);
        }else{
          //line 1 and 2
          textb.remove(0,10); 
        }
        printVar(textb, 140, 1, 0);
        //printVar(textb, 140, 0);
        yVa = yVa + 20;
      }
      
      if(filename == "INC.TXT"){
        if(count == 0){textb.remove(0,10);}//line1
        if(count == 1){textb.remove(0,16);}//line2
        if(count == 2){textb.remove(0,11);}//line3
        if(count == 3){textb.remove(0,8);}//line3
        
        printVar(textb, 361, 1, 0);
        //printVar(textb, 361, 0);
        yVa = yVa + 20;
      }
  
      if(filename == "PROG00.TXT" or filename == "PROG01.TXT" or filename == "PROG02.TXT"){
        if(count == 0){textb.remove(0,14);printVar(textb, 35, 0,0);}//line1
        if(count > 0 and count < 2){
          //line2
          textb.remove(0,10);
          progDataArray[arrCountr] = textb;
          arrCountr++;
        }
        if(count > 1 and count < 11){
          //line3-11
          textb.remove(0,7);
          progDataArray[arrCountr] = textb;
          arrCountr++;
        }
        if(count > 10 and count < 99){
          //line12--
          textb.remove(0,8);
          progDataArray[arrCountr] = textb;
          arrCountr++;
        }
      }
    }
    if(dataSD == 1){
      if(filename == "CFG.TXT"){
        textb.remove(0,14);        
        printVar(textb, SetgCoord[0]+248, 1, 1);
        yVa = yVa + 20;
      }
    }
    
  }
}
//print variables
void printVar(String vari, int xVa, int fnt, int dataSD){
  if(fnt == 0 ){myGLCD.setFont(SmallFont);}//small for program from file text, like program name "default program"
  if(fnt == 1 ){myGLCD.setFont(BigFont);}//big for numeric values
  TXTbackcolr();
  TXTcolr();
  
  if(dataSD == 0){
    progDataArray[arrCountr] = vari;
    myGLCD.print(progDataArray[arrCountr], xVa, yVa); // Prints the string on the screen
  }
  if(dataSD == 1){
    Settings[arrCountr] = vari;
    myGLCD.print(Settings[arrCountr], xVa, yVa); // Prints the string on the screen
  }
  arrCountr++;
}
