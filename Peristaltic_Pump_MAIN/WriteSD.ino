void WriteSD(const char *filename, int lines, int fromDat){
  //WriteSD(filename, lines per file, Text from array, Data from buffer)
  sd.remove(filename);
  if (!Progfiles.open(filename, O_RDWR | O_CREAT | O_EXCL)) {
    sd.errorHalt(filename);
  }
  for(int i=0; i<lines; i++){
    if(i+1 == lines){
      if(filename == name[0]){Progfiles.print(FIXprog[i]+progDataArray[fromDat]);}//write last line with no new line
      if(filename == name[5] and resetSett == 0){Progfiles.print(SettinTxt[i]+Settings[fromDat]);}//write last line with no new line
      if(filename == name[5] and resetSett == 1){Progfiles.print(SettinTxt[i]+FactorySett[fromDat]);}//write last line with no new line
      
    }else{
      if(filename == name[0]){Progfiles.println(FIXprog[i]+progDataArray[fromDat]);}//user write new values for fixed quantity program
      if(filename == name[5] and resetSett == 0){Progfiles.println(SettinTxt[i]+Settings[fromDat]);}//user reset settings
      if(filename == name[5] and resetSett == 1){Progfiles.println(SettinTxt[i]+FactorySett[fromDat]);}//user changed and saves settings
    }
    fromDat++;
  }
  resetSett = 0;//reset the flag for factory settings
  Progfiles.close();
  Serial.println("Data saved!");
}
