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
long innumber;
//===========================================================================
void setup()
{
  delay(100);
  Serial.begin(38400); //start serial communications at 38400bps
  delay(100);
  
  SetPosition(1,512);
  Serial.println("Set up done");
  delay(1000);
}


//============================================================================
//============================================================================
// user input sample
// 1500b2300b3400
// move all the servos at the same time
// s1 s2
// return position
void loop() 
{
  //delay(1000);
  //Serial.println("loop");
  
  run = 1;
  
  if (Serial.available() > 0) 
  {
    Serial.println("get Serial");
    // read the incoming byte:
    instring = Serial.readString();
    int servo_num = 0;
    for (int i = 0; i < instring.length();i++)
    {
      if (instring[i] == 'r')
      {
        servo_num = int(instring[i+1])-48;
        Serial.print("servo ");
        Serial.print(instring[i+1]);
        Serial.print("'s postion: ");
        Serial.println(GetPosition(servo_num));
        i++;
      }
      else if ((instring[i] == '1' )
                || (instring[i] == '2' )
                || (instring[i] == '3' )
                || (instring[i] == '4' )
                || (instring[i] == '5' )
                || (instring[i] == '6' )
                || (instring[i] == '8' )
                )
      { 
        Serial.print("get servo num: ");
        Serial.println(instring[i]);
        servo_num = int(instring[i])-48;
        String desire_pos = "";
        i++;
        while (instring[i] != 'b')
        {
          desire_pos += instring[i];
          i++;
        }
        Serial.print("desire pos: ");
        Serial.println(desire_pos);
        int temp = desire_pos.toInt();
        Serial.print("temp: ");
        Serial.println(temp);
        if (instring[i] == '2' )
        {
          SetPosition(2,temp);
          SetPosition(3,1024-temp);
        }
        else if (instring[i] == '3' )
        {
          SetPosition(3,temp);
          SetPosition(2,1024-temp);
        }
        else if (instring[i] == '4' )
        {
          SetPosition(4,temp);
          SetPosition(5,1024-temp);
        }
        else if (instring[i] == '5' )
        {
          SetPosition(5,temp);
          SetPosition(4,1024-temp);
        }
        else
        {
          SetPosition(servo_num,temp);
        }
      }
    }
    Serial.flush(); 
  }
    /*
    //count num of commands
    unsigned char count_b = 0;
    Serial.print("initialcount_b: ");
    Serial.println(count_b);
    for (int i = 0; i < instring.length();i++)
    {
      if (instring[i] == 'b') count_b ++;
    }
    Serial.print("latter count_b: ");
    Serial.println(count_b);
    // create an array for command info
    int data[count_b+1];
    Serial.print("size of data: ");
    Serial.println(sizeof(data)/2);
    if (count_b == 0)
    {
      data[0] = instring.toInt();
    }
    else 
    { 
      unsigned char index = 0;
      String str = "";
      for (int i = 0; i < instring.length()-1; i++)
      {
        
        if (instring[i] == 'b') 
        {
          data[index] = str.toInt();
          index ++;
          str = "";
        }
        else
        {
         
          str += instring[i];
        }
      } 
      data[index] = str.toInt();
    }
    for (int i = 0; i < sizeof(data)/2;i++)
    {
      Serial.print("data: ");
      Serial.println(data[i]);
    }
  }
    
    // say what you got:
    Serial.print("I received: ");
    Serial.print(instring);
    innumber = instring.toInt(); 
    Serial.print("instring in integer: ");
    Serial.println(innumber);
    Serial.println("-----------------------------------");
    
    long temp = innumber;
    digits = 0;
    while (temp)
    {
      temp = temp/10;  
      digits++;
    }
    
    Serial.print("temp size: ");
    Serial.println(digits);
    Serial.print("instring length: ");
    Serial.println(instring.length()-1); //instring has one more digit
    
    if (digits != (instring.length()-1))
    {
      //check if integer
      run = false;
      Serial.println("instring has char, input number");
    }
    
    Serial.print("char check, run: ");
    Serial.println(run);
    Serial.println("-----------------------------------");
    
    if (digits < 2 && run)
    {
      //length check
      run = false;
      Serial.println("input more digits");
    }
    else if (digits > 1 && run)
    {   
      char c = instring[0];
      servo_num = (int)c-48;
      Serial.print("first servo number: ");
      Serial.println(servo_num);
    }
    
    Serial.print("instring length check, run: ");
    Serial.println(run);
    Serial.println("-----------------------------------");
    
    if ((servo_num == 3 || servo_num == 5) && run)
    {
      //error check
      run = false;
      Serial.println("first servo is 3 or 5");
    }
    
    if (run)
    {
      cur_pos = GetPosition(servo_num);  
      Serial.print("current position for first servo: ");
      Serial.println(cur_pos);
    }
    Serial.print("current position check, run: ");
    Serial.println(run);
    Serial.println("-----------------------------------");
    
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
      Serial.println("-----------------------------------");
    
    }
    else if ((servo_num == 2 || servo_num == 4) && run)
    {
      Serial.println("first servo is 2 or 4");
      if (digits > 2) //length check
      {
        single_servo = false;
        
        long s = servo_num*pow(10,digits-1);
        char c = instring[1];
        servo_num2 = (int)c -48;
        Serial.print("second servo: ");
        Serial.println(servo_num2);
        s += servo_num2*pow(10,digits-2);
        Serial.print("redundant part: ");
        Serial.println(s);  
        
        desire_pos = innumber - s;
        Serial.print("desired postion: ");
        Serial.println(desire_pos);
        
        Serial.print("current position for second servo: ");
        Serial.println(GetPosition(servo_num2));
        if (cur_pos != GetPosition(servo_num2))
        {
          SetPosition(servo_num2,1024-cur_pos);
        }
        Serial.println("-----------------------------------");
        
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
           if (!single_servo)
           {
             SetPosition(servo_num2,1024-i);
           }
         }
         Serial.println("set");
         delay(1000);
        }   
        else if (cur_pos > desire_pos)
        {
          for(int i= cur_pos; i > desire_pos; i--)
          {
            SetPosition(servo_num,i);
            if (!single_servo){SetPosition(servo_num2,1024-i);}
          }
          Serial.println("set");
          delay(1000);
        }
        
        Serial.println("done");
        Serial.println("================================================");
    }
    Serial.flush(); //clear the serial input buffer 
  }
  */
 
  
}  
