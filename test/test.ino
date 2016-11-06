#include <ax12.h>

//---------------------------------------------------------------
union Data {
   char bufc[10];
   unsigned short int bufi[5];
};

uint16_t desired_loc[]= {512, 512, 512, 512, 512};
uint16_t current_loc[]= {512, 512, 512, 512, 512};

int cur_pos = 0;
boolean correctmsg = true;

//---------------------------------------------------------------
void go_to(){
  for (int i = 0; i < 8; i++) {
    if ((i != 2) && (i != 4) && (i != 6) ) {
      cur_pos = GetPosition(i+1);
      Serial.print("servo ");
      Serial.print(i+1);
      Serial.print("  cur pos:  ");
      Serial.println(cur_pos);
      if ( (cur_pos < desired_loc[i]-5) || (cur_pos > desired_loc[i]+5) ) {
        if (i == 1) {
          Serial.println("Move Servo 2");
          SetPosition(i+1,desired_loc[i]);
          SetPosition(i+2,1024-desired_loc[i]);
        }
        else if(i == 3) {
          Serial.println("Move Servo 4");
          SetPosition(i+1,desired_loc[i]);
          SetPosition(i+2,1024-desired_loc[i]);
        }
        else {
          Serial.println("Move Servo 1/6/8");
          SetPosition(i+1,desired_loc[i]);
        }
      }
    }  
  }
  //Serial.println("Reach the end of go to");
}

//---------------------------------------------------------------
void setup(){
  Serial.begin(38400); //start serial communications at 38400bps
  Serial.setTimeout(2); 
  Serial.println("SetUp Done");
}

//---------------------------------------------------------------
void loop(){
  delay(10);
  
  //----------------
  //SetPositions
  if (Serial.available() == 16) {
    union Data data;
    
    //read
    for (int i=0; i<16; ++i) {
      data.bufc[i] = Serial.read();
      if (data.bufc[i] == -1) --i;
    }
    
    //check start
    if (data.bufi[0] == -1) {
      correctmsg = false;
      Serial.println("-1");
    } 
    //check end
    if (data.bufi[7] == 0xAA55) {
      correctmsg = false;
      Serial.println("-1");
    }
    //calculate sum
    int sum = 0;
    for (int i=2; i<7; ++i) {
      sum = sum + data.bufi[i];
    }
    //check sum
    if (data.bufi[1] != sum) {
      correctmsg = false;
      Serial.println("-1");
    }
    if (correctmsg) {
      for (int i=0; i<5; i++) {
        desired_loc[i] = data.bufi[i+2];
      }
      //go_to();
    }
    correctmsg = true;
  }
  //----------------
  //GetPositions
  else if (Serial.available() == 2) {
    union Data data;
    
    //read
    for (int i=0; i<2; ++i) {
      data.bufc[i] = Serial.read();
      if (data.bufc[i] == -1) --i;
    }
    
    //check num
    if (data.bufi[0] != -9999) {
      correctmsg = false;
      Serial.println("-1");
    }
    
    if (correctmsg) {
     
      current_loc[0] = GetPosition(1);
      current_loc[1] = GetPosition(2);
      current_loc[2] = GetPosition(4);
      current_loc[3] = GetPosition(6);
      current_loc[4] = GetPosition(8);
      
      for (int i=0; i<5; ++i) {
        Serial.print(i+1);
        Serial.println(current_loc[i]);
      }
    }
    correctmsg = true;
  }
  //----------------
  //error msg
  else {
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
  
} // loop


//---------------------------------------------------------------
  /*
    if (Serial.available() == 4){
      // A READ JOINTS COMMAND 
      // READ ALL BYTES
      //READ START BYTES (2 of them)
      //READ END BYTES
      // WRITE JOINTS OR SOMETHING FOR TESTING
      
      //Serial.println('A');
    }    
    else if (Serial.available() == 14 ){
      // A SET JOINTS COMMAND
      // READ ALL BYTES
      // CHECK START BYTES
      // CHECK END BYTES
      // DO THE BEHAVIOR
    }
    else{ 
      // FLUSH
      Serial.flush();
    }
    */
    //Serial.flush();
