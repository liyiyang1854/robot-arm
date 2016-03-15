#include <ax12.h>

//===========================================================================
String instring; 
int servo_num;
int cur_pos;
int desire_pos;
//===========================================================================
void setup()
{
  delay(100);
  Serial.begin(38400); //start serial communications at 38400bps
  delay(100);
  
  SetPosition(1,512);
  Serial.println("setting up done");
  delay(1000);
}


//============================================================================
//============================================================================
void loop() 
{
  
  if (Serial.available() > 0) 
  {
    Serial.println("get Serial");
    // read the incoming byte:
    instring = Serial.readString();
    
    // say what you got:
    Serial.print("I received: ");
    Serial.print(instring);   
    char c = instring[0];
    servo_num = (int)c-48;
    Serial.print("servo number: ");
    Serial.println(servo_num);
    
    int len = instring.length();
    Serial.print("temp length: ");
    Serial.println(len);
    
    int temp = instring.toInt(); 
    Serial.print("instring in integer: ");
    Serial.println(temp);
    int s = servo_num*pow(10,len-2);
    Serial.print("redundant part: ");
    Serial.println(s); 
    desire_pos = temp - s;
    Serial.print("desired postion: ");
    Serial.println(desire_pos);
    
    cur_pos = GetPosition(servo_num);  
    Serial.print("current position: ");
    Serial.println(cur_pos);
     
    Serial.println("Start to adjust servo");
    if (cur_pos < desire_pos)
    {
      for(int i=cur_pos;i<desire_pos;i++)
      {
        SetPosition(servo_num,i);
      }
      Serial.println("set");
      delay(1000);
    }
    else if (cur_pos > desire_pos)
    {
      for(int i= cur_pos; i > desire_pos; i--)
      {
        SetPosition(servo_num,i);
      }
      Serial.println("set");
      delay(1000);
    }
    Serial.println("done");
    Serial.println("--------------------------");
    
  }
  
}  
