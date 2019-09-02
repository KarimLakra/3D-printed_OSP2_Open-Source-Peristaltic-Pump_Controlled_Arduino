void ReadSD(const char *filename, int dataSD) {
  //Serial.println();
  // Initialize tinyFAT 
  // You might need to select a lower speed than the default SPISPEED_HIGH
  res=file.initFAT(); 
  if (res!=NO_ERROR){
    Serial.print("***** ERROR: ");
    Serial.println(verboseError(res));
    while (true) {};
  } 
  
  if (file.exists(filename)){
    res=file.openFile(filename, FILEMODE_TEXT_READ);
    if (res==NO_ERROR){
      //Read data
      result=0; int count=0;
      if(filename == name[0]){yVa = 46;}
      if(filename == name[1]){yVa = 46;}
      if(filename == name[2]){yVa = 174;}
      if(filename == name[3]){yVa = 200;}
      if(filename == name[4]){yVa = 226;}
      if(filename == name[5]){yVa = 44;}
      
      while ((result!=EOF) and (result!=FILE_IS_EMPTY)){
        result=file.readLn(textBuffer, 80);
        if (result!=FILE_IS_EMPTY){
          progs(filename, result, count, dataSD);
        }else{
          Serial.println("** ERROR: File is empty...");
        }
        count++;
      }
      //Serial.println();
      file.closeFile();
    }else{
      switch(res){
        case ERROR_ANOTHER_FILE_OPEN:
          Serial.println("** ERROR: Another file is already open...");
          break;
        default:
          Serial.print("** ERROR: ");
          Serial.println(res, HEX);
          break;
      }
    }
  }else{
    Serial.println("** ERROR: missing program file!");
  }
  //Serial.println();
  //Serial.println("***** End of the program... *****");
}
