void About(){
  printPage(30);
}
void anykey(String prsd){
  if (prsd == "UP" or prsd == "DWN" or prsd == "LFT" or prsd == "RGHT" or prsd == "OK"){
    Screen = 0;
    Home();
    SlctdButn = 0;
  }
}

