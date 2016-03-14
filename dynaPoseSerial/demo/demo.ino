#include <ax12.h>

//============================================================================================================
String temp = "0512"; 
int servo_num;
int cur_pos;
int desire_pos;
//============================================================================================================

void setup()
{
  delay(100);
  Serial.begin(38400); //start serial communications at 38400bps
  delay(100);
  
  SetPosition(1,512);
  Serial.print("setting up done");
  delay(1000);
}


//============================================================================================================
//============================================================================================================

void loop() 
{
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    temp = Serial.readString();
    
    // say what you got:
    Serial.print("I received: "+temp+" in int "+temp.toInt());
    
    char c = temp[0];
    servo_num = (int)c-48;
    Serial.print("I received: "+servo_num);
    
    int len = temp.length();
    Serial.print("temp length: "+len);
    desire_pos = temp.toInt() - servo_num*(10^(len-1)); 
    Serial.print("desired postion: "+desire_pos);
    cur_pos = GetPosition(servo_num);  
    Serial.println("get position: "+cur_pos);
    
    Serial.println("Start to adjust servo");
    if (cur_pos < desire_pos)
    {
      for(int i=cur_pos;i<desire_pos;i++)
      {
        SetPosition(servo_num,i);
        delay(100);
      }
      delay(1000);
    }
    else if (cur_pos > desire_pos)
    {
      for(int i= cur_pos; i > desire_pos; i--)
      {
        SetPosition(servo_num,i);
        delay(100);
      }
      delay(1000);
    }
    Serial.print("done");
  }
  
}  
