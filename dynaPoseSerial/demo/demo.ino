#include <ax12.h>

//===========================================================================
String instring; 
int servo_num;
int cur_pos;
int desire_pos;
boolean single_servo;
int servo_num2;
boolean run = true;
int digits = 0;
int innumber;
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
    
    innumber = instring.toInt(); 
    Serial.print("instring in integer: ");
    Serial.println(innumber);
    
    int temp = innumber;
    digits = 0;
    while (temp)
    {
      temp = temp/10;  
      digits++;
    }
    
    Serial.print("temp size: ");
    Serial.println(digits);
    Serial.print("instring length: ");
    Serial.println(instring.length());
    
    if (digits != (instring.length()-1))
    {
      //check if integer
      run = false;
      Serial.println("instring has char, input number");
    }
    
    if (digits < 2 && run)
    {
      //length check
      run = false;
      Serial.println("input more digits");
    }
    else if (digits > 1 && run)
    {
      Serial.print("I received: ");
      Serial.print(instring);   
      char c = instring[0];
      servo_num = (int)c-48;
      Serial.print("servo number: ");
      Serial.println(servo_num);
    }
    
    if ((servo_num == 3 || servo_num == 5) && run)
    {
      //error check
      run = false;
    }
    
    if (run)
    {
      cur_pos = GetPosition(servo_num);  
      Serial.print("current position for first servo: ");
      Serial.println(cur_pos);
    }
    
    if ((servo_num == 1 || servo_num == 6 || servo_num == 8) && run)
    {
      //error check
      
      single_servo = true;
      
      int s = servo_num*pow(10,digits-1);
      Serial.print("redundant part: ");
      Serial.println(s); 
      desire_pos = innumber - s;
      Serial.print("desired postion: ");
      Serial.println(desire_pos);
    
    }
    else if ((servo_num == 2 || servo_num == 4) && run)
    {
      if (digits > 2) //length check
      {
        single_servo = false;
        
        int s = servo_num*pow(10,digits-1);
        servo_num2 = instring[1];
        Serial.print("second servo: ");
        Serial.println(servo_num2);
        s += servo_num2*pow(10,digits-2);
        Serial.print("redundant part: ");
        Serial.println(s);  
        
        desire_pos = innumber - s;
        Serial.print("desired postion: ");
        Serial.println(desire_pos);
        
        cur_pos = GetPosition(servo_num);  
        Serial.print("current position: ");
        Serial.println(cur_pos);
        
        SetPosition(servo_num2,cur_pos);    
      }
    }
    
    if (run)
    {
       Serial.println("Start to adjust servo");
       
       if (cur_pos < desire_pos)
       {
         for(int i=cur_pos;i<desire_pos;i++)
         {
           SetPosition(servo_num,i);
           if (!single_servo){SetPosition(servo_num2,i);}
          }
          Serial.println("set");
          delay(1000);
        }   
        else if (cur_pos > desire_pos)
        {
          for(int i= cur_pos; i > desire_pos; i--)
          {
            SetPosition(servo_num,i);
            if (!single_servo){SetPosition(servo_num2,i);}
          }
          Serial.println("set");
          delay(1000);
        }
        
        Serial.println("done");
        Serial.println("--------------------------");
    }
    
  }
 
  
}  
