  //includes and imports
  #include <Servo.h> 
  
  //servo stuff
  Servo leftservo, rightservo; // create servo object to control a servo 
  
  int halftime = 600;
  int fulltime = 1200;
  int halfspeed = 30;
  int fullspeed = 120; //variables to control delay time
  
  
  //directions pins
  int right = 2;
  int up = 3;
  int down =  4;
  int left = 5;
  
  //switches pins
  int bin3 = 10;
  int bin2 =  11;
  int bin1 = 12;
  
  //method choosing button
  int buttonPin = 8;
  int button;
  
  //hand glove control
  int  r1 , r2 , r3;
  int FirstF, secondF, ThirdF;
  
  // variables to control directions
  int l, d, u, r;
  
  //variables to obtain DIPs
  String bit1, bit2, bit3;
  
  //the variable that will hold the value of any binary input
  String binary;
  
  //string for activating directions
  char robotdirection;
  
  
  //functions prototypes----------------------------------
  int gloveRead (int, int, int);
  void robotmove (int, char);
  

void setup()
{
  //declarations
  Serial.begin(9600);

  //initialize pin modes
  //butons
  pinMode(right, INPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(left, INPUT);

  //binary inputs
  pinMode(bin3, INPUT);
  pinMode(bin2, INPUT);
  pinMode(bin1, INPUT);
  pinMode(buttonPin, INPUT);
  
   //servo pins 6 + 13
  leftservo.attach(6);
  rightservo.attach(13);

}




void loop()
{ 
    
  button = digitalRead(buttonPin);
  
  delay(4);
  
    
   
    
  //if button is zero, input method is DIP
  if ((button == 0) ) ///check it
  { 
    r = digitalRead(right);
  delay(4);
  l = digitalRead(left);
  delay(4);
  u = digitalRead(up);
  delay(4);
  d = digitalRead(down);
  delay(4);
  Serial.println(r);
  Serial.println(l);
  Serial.println(u);
  Serial.println(d);
  Serial.println(button);
   
    robotdirection='n';
  
  if  (l ==HIGH && r == LOW && d == LOW && u == LOW ){
    robotdirection = 'l';
    Serial.println("l is high"); }
  else if (l ==LOW && r == HIGH && d == LOW && u == LOW){
    Serial.println("r is high");
    robotdirection = 'r'; }
  else if (l ==LOW && r == LOW && d == LOW && u == HIGH){
    Serial.println("u is high");
    robotdirection = 'u';}
  else if (l ==LOW && r == LOW && d == HIGH && u == LOW){
    Serial.println("d is high");
    robotdirection = 'd'; }

    //switches code ---------------------------------------------------------

    //echo the input
    bit3 = (String)digitalRead(bin3);
    bit2 = (String) digitalRead(bin2);
    bit1 = (String) digitalRead(bin1); 
    binary = bit1 + bit2 + bit3;
    int binaryValue = 0;
    
    //convert steps # to intigers!!!!!
    /* int j =0;
    for (int i = binary.length()-1 ; i >=0 ;i--){
      binaryValue = (binary[i] == 0 ? 0 : pow(2,j));
      j++;
    }
    */
        
           if ( binary == "000")
            binaryValue = 0;
          else if ( binary == "001")
           binaryValue = 1;
          else if ( binary =="010")
           binaryValue = 2;
          else if ( binary =="011")
            binaryValue = 3;
          else if ( binary =="100")
            binaryValue = 4;
          else if ( binary =="101")
            binaryValue = 5;
          else if ( binary =="110")
            binaryValue = 6;
          else if ( binary =="111")
            binaryValue = 7;
     
   Serial.println(binaryValue);
  robotmove(binaryValue, robotdirection);
  }
   
    
  



  //if button is 1, input method is glove
  else if (button ==1 ) // check it
    {
    //glove code -------------------------------------------------------------------------------------------

  r = digitalRead(right);
  delay(4);
  l = digitalRead(left);
  delay(4);
  u = digitalRead(up);
  delay(4);
  d = digitalRead(down);
  delay(4);
  Serial.println(r);
  Serial.println(l);
  Serial.println(u);
  Serial.println(d);
  Serial.println(button);
   
    robotdirection='n';
  
  if  (l ==HIGH && r == LOW && d == LOW && u == LOW ){
    robotdirection = 'l';
    Serial.println("l is high"); }
  else if (l ==LOW && r == HIGH && d == LOW && u == LOW){
    Serial.println("r is high");
    robotdirection = 'r'; }
  else if (l ==LOW && r == LOW && d == LOW && u == HIGH){
    Serial.println("u is high");
    robotdirection = 'u';}
  else if (l ==LOW && r == LOW && d == HIGH && u == LOW){
    Serial.println("d is high");
    robotdirection = 'd'; }
    
    
    FirstF = analogRead(A0);
    secondF = analogRead(A2);
    ThirdF = analogRead(A5);
    int gloveBinaryValue = gloveRead( FirstF, secondF, ThirdF);
    robotmove( gloveBinaryValue, robotdirection);
    }
    delay(20);
    } // end of void loop





//robot moving function
      
void robotmove (int steps, char directions)
      {
       int checkmate =0;
       for (int stepcounter = 1; stepcounter <= steps; stepcounter++)
       {  
         //go left function
           if ( directions == 'l')
            { 
              if (checkmate==0){
              leftservo.write(90 + halfspeed);
              rightservo.write(90 + halfspeed);
              delay(halftime);
              Serial.println("turning left");
              leftservo.write(90);
              rightservo.write(92);
              delay(1000);
              checkmate++;  }
              leftservo.write(fullspeed);
              rightservo.write(-fullspeed);
              delay(1000);
              Serial.println("going up");
              leftservo.write(90);
              rightservo.write(92);
            }
            
            //go forward
            else if ( directions == 'u')
            { 
              leftservo.write(fullspeed);
              rightservo.write(-fullspeed);
              delay(fulltime);
              leftservo.write(90);
              rightservo.write(92);
              delay(1000);
              Serial.println("going up");
            }
            
            //going down
            else  if ( directions == 'd')
            { 
              leftservo.write(-fullspeed);
              rightservo.write(+fullspeed);
              delay(fulltime);
              leftservo.write(90);
              rightservo.write(92);
              Serial.println("going down");
              delay(1000);
            }
            
            //going right
            else if ( directions == 'r')
            { 
              if (checkmate==0){
              leftservo.write(90 - halfspeed);
              rightservo.write(90 - halfspeed);
              delay(halftime);
              Serial.println("turning right");
              leftservo.write(90);
              rightservo.write(92);
              delay(1000);
              
              checkmate++;  }
              leftservo.write(fullspeed);
              rightservo.write(-fullspeed);
              delay(1000);
              Serial.println("going up");
              leftservo.write(90);
              rightservo.write(92);
              
              /*leftservo.write(90 - halfspeed);
              rightservo.write(90- halfspeed);
              delay(halftime);
              leftservo.write(90);
              rightservo.write(92);
              Serial.println("going right");
              delay(1000);*/
            }
       }
   
      } //end of robotmove function





//read glove input function
int gloveRead (int x, int y, int z){
          /* if ( x > 700)
            r1 = "1";
          else 
            r1 = "0" ;
          if ( y > 200)
            r2 = "1";
          else 
            r2 = "0" ;
          if ( z > 250)
            r3 = "1";
          else 
            r3 = "0" ;
          //end of glove related code
          binary = r3 + r2 + r1;
          //glove binary conditions
          if ( binary == "000")
            return 0;
          else if ( binary == "001")
            return 1;
          else if ( binary =="010")
            return 2;
          else if ( binary =="011")
            return 3;
          else if ( binary =="100")
            return 4;
          else if ( binary =="101")
            return 5;
          else if ( binary =="110")
            return 6;
          else if ( binary =="111")
       
            return 7; */
          if ( x > 700)
r1 = 1;

else 
r1 = 0 ;

if ( y > 200)
r2 = 1;

else 
r2 = 0 ;

if ( z > 250)
r3 = 1;

else 
r3 = 0 ;



if ( r1 == 0 && r2 == 0 && r3 == 0){
//servo 
  return 0 ;

}
if ( r1 == 0 && r2 == 0 && r3 == 1){
//servo 
  return 1 ;

}
if ( r1 == 0 && r2 == 1 && r3 == 0){
//servo 
 return 2;

}
if ( r1 == 0 && r2 == 1 && r3 == 1){
//servo 
  return 3 ;
  

}
if ( r1 == 1 && r2 == 0 && r3 == 0){
//servo 
  return 4 ;

}
if ( r1 == 1 && r2 == 0 && r3 == 1){
//servo 
  return 5 ;

}
if ( r1 == 1 && r2 == 1 && r3 == 0){
//servo 
  return 6 ;

}
if ( r1 == 1 && r2 == 1 && r3 == 1){
//servo 
  return 7 ;

}
      }

//end of code

