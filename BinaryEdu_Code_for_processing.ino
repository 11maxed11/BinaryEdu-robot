    char  reads ;
    char directions ;
    int steps;
    boolean Send = false ; 
    
    #include <Servo.h> 
  
  //servo stuff
  Servo leftservo, rightservo; // create servo object to control a servo 
  
  int halftime = 500;
  int fulltime = 1350;
  int halfspeed = 20;
  int fullspeed = 120; //variables to control delay time

     
    
    void setup() {
      
      Serial.begin(9500);
      //initialize pin modes
  //butons


  
   //servo pins 6 + 13
  leftservo.attach(6);
  rightservo.attach(13);
    }
     
    void loop() {
    
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
     }
        
      }
    }
    
    
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

    
    
    

