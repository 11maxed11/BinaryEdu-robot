//includes and imports
#include <Servo.h> 

//servo stuff
Servo leftservo, rightservo; // create servo object to control a servo 

int halftime = 650;
int fulltime = 1575;


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
int button0Pin = 8;
int button0;
int button1Pin=13;
int button1;

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


//for the procesing program
boolean Send = false ; 
char  reads ;
char directions ;
int steps;



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
  pinMode(button0Pin, INPUT);
  pinMode(button1Pin, INPUT);
  //servo pins 6 + 9
  leftservo.attach(6);
  rightservo.attach(9);

}




void loop()
{ 

  button0 = digitalRead(button0Pin);
  delay(4);
  button1 = digitalRead(button1Pin);
  delay(4);




  //if button0 is on, and button1 is off. input method is DIP
  if ((button0 == 1 && button1==0) ) ///check it
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
    Serial.println(button0);
    Serial.println(button1);

    robotdirection='n';

    if  (l ==HIGH && r == LOW && d == LOW && u == LOW ){
      robotdirection = 'l';
      Serial.println("l is high"); 
    }
    else if (l ==LOW && r == HIGH && d == LOW && u == LOW){
      Serial.println("r is high");
      robotdirection = 'r'; 
    }
    else if (l ==LOW && r == LOW && d == LOW && u == HIGH){
      Serial.println("u is high");
      robotdirection = 'u';
    }
    else if (l ==LOW && r == LOW && d == HIGH && u == LOW){
      Serial.println("d is high");
      robotdirection = 'd'; 
    }

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






  //if button0 is off and button1 is on, input method is glove
  else if (( button0 == 0 && button1==1)){
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
    Serial.println(button0);
    Serial.println(button1);

    robotdirection='n';

    if  (l ==HIGH && r == LOW && d == LOW && u == LOW ){
      robotdirection = 'l';
      Serial.println("l is high"); 
    }
    else if (l ==LOW && r == HIGH && d == LOW && u == LOW){
      Serial.println("r is high");
      robotdirection = 'r'; 
    }
    else if (l ==LOW && r == LOW && d == LOW && u == HIGH){
      Serial.println("u is high");
      robotdirection = 'u';
    }
    else if (l ==LOW && r == LOW && d == HIGH && u == LOW){
      Serial.println("d is high");
      robotdirection = 'd'; 
    }


    FirstF = analogRead(A0);
    secondF = analogRead(A2);
    ThirdF = analogRead(A5);
    int gloveBinaryValue = gloveRead( FirstF, secondF, ThirdF);
    robotmove( gloveBinaryValue, robotdirection);
  }
 
  
  //if both buttons are 0, input method is PC
  else if (( (button0 == 0) && button1==0)){
    
     button0 = digitalRead(button0Pin);
    delay(4);
    button1 = digitalRead(button1Pin);
    delay(4);
    
    if (Serial.available() > 0) {
       
          reads = Serial.read();
       
      if (reads == 'u'){
        directions = reads; 
        Serial.println(directions);
        }  
        
        else if (reads == 'd'){
        directions = reads; 
        Serial.println(directions);
        }  
   
        else if (reads == 'r'){
        directions = reads; 
        Serial.println(directions);
        }  
      
        else if (reads == 'l'){
        directions = reads; 
        Serial.println(directions);
        }  
        
       else if (  reads > 0  ) {
          steps = reads - 48 ;
          Serial.println(steps);
         Send = true ; 
     }
     
     if ( Send ) 
     {
       robotmove( (int)steps, directions);
       Send = false ; 
     }
        
      }
     
  } 
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
        rightservo.writeMicroseconds(1700);
        leftservo.writeMicroseconds(1700);
        delay(halftime);
        Serial.println("turning left");
        rightservo.writeMicroseconds(1500);
        leftservo.writeMicroseconds(1500);
        delay(1000);
        checkmate++;  
      }
      rightservo.writeMicroseconds(1700);
      leftservo.writeMicroseconds(1300);
      delay(fulltime);
      Serial.println("going up");
      rightservo.writeMicroseconds(1500);
      leftservo.writeMicroseconds(1500);
      delay(1000);

    }
    //go forward
    else if ( directions == 'u')
    { 
      rightservo.writeMicroseconds(1700);
      leftservo.writeMicroseconds(1300);
      delay(fulltime);
      leftservo.writeMicroseconds(1500);
      rightservo.writeMicroseconds(1500);
      delay(1000);
      Serial.println("going up");
    }

    //going down
    else  if ( directions == 'd')
    { 
      leftservo.writeMicroseconds(1700);
      rightservo.writeMicroseconds(1300);
      delay(fulltime);
      leftservo.writeMicroseconds(1500);
      rightservo.writeMicroseconds(1500);
      Serial.println("going down");
      delay(1000);
    }

    //going right
    else if ( directions == 'r')
    { 
      if (checkmate==0){
        rightservo.writeMicroseconds(1300);
        leftservo.writeMicroseconds(1300);
        Serial.println("turning left");
        delay(halftime);
        rightservo.writeMicroseconds(1500);
        leftservo.writeMicroseconds(1500);
        delay(1000);
        checkmate++;  
      }
      rightservo.writeMicroseconds(1700);
      leftservo.writeMicroseconds(1300);
      delay(fulltime);
      Serial.println("going up");
      rightservo.writeMicroseconds(1500);
      leftservo.writeMicroseconds(1500);
      delay(1000);

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


