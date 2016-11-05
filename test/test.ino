void setup(){
  Serial.begin(38400); //start serial communications at 38400bps
  Serial.setTimeout(2); 
}


void loop(){
  delay(10);
  if (Serial.available() > 0) {
    if (Serial.available() == 4){
      // A READ JOINTS COMMAND 
      // READ ALL BYTES
      //READ START BYTES (2 of them)
      //READ END BYTES
      // WRITE JOINTS OR SOMETHING FOR TESTING
      Serial.println('THSFA');
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
    }
    
    
    
  }
}
