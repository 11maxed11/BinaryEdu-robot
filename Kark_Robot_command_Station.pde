  
  import processing.serial.*;
  Serial port;
   
  PFont f = createFont("Arial", 16, true);
  
  String com = "Command : ";
  String saved = "";
  String show = "";
  String typing = "";
  String ready = "binaryedu Robot is ready to receive commands ! ";
  
  
  int py = 140 , px = 120 , w2d = 0 ; 
  int indent = 25;
  int background = 255 ;
  int R = 0 , G = 0 , B =0 ; 
  int font ; 
  int pxx = 280 ; 
  int pxn = 170 ; 
  
  void setup() {
    size(1000,700); 
    port = new Serial(this,Serial.list()[9], 9600);  
  }
  
  void draw() {
    background(background);
    int indent = 25;
    textFont(f);
    fill(R , G ,B);
    
    text(typing+(frameCount/10 % 2 == 0 ? "|" : ""), px , py);
    
    if (w2d == 1){
      com = "Number of steps : ";
      px = pxn ;   
    }
    else if (w2d == 2){
      com = "Commnad not found ! . Command : ";
      px = pxx ;
    }
    else if (w2d == 3){
      com = "Wrong Value! .  Number of steps : ";
      px = pxx ; 
    }
    else {
     com = "Command : "; 
     px = 120 ;   
    }
    
    text("======== Welcome To binaryedu Robot command Station on Earth ! ========", indent, 40);
    text(ready, indent, 70);
    text("*- To view all commands, type help", indent, 100);
    text(typing ,px , py);
    text(show,indent,130);
    text(com,indent, py);
  }
  
  void keyPressed() {
    // If the return key is pressed, save the String and clear it
    if (key == '\n' ) {
      saved = typing;   
      show += typing + "\n" ; 
    
      if( w2d == 0 || w2d == 2){ // what to do is asking for a comand ;)
      
        if ( saved.equals("help")){
          
             show += " List of all Commands : \n" ; 
             show += " * Clear : Type clear to clear the Command window \n" ;
             show += " * Move forward : Type move forward to move the robot forward  \n" ;
             show += " * Move backward : Type move backward to move the robot backward  \n" ;
             show += " * Move right : Type Move right to move the robot right  \n" ;
             show += " * Move left : Type Move left to move the robot left  \n" ;
             show += " * kark mode : Type kark mode to change the mode of command station to kark mode \n" ;
             show += " * funky mode : Type funky mode to change the mode of command station to funky mode  \n" ;
             show += " * Hacking mode : Type hacking mode to change the mode of command station to hacking mode  \n" ;
             show += " * Help : Type help to view all the command that can be used in this command station  \n " ;
             show += " * -- Note that kark robot can move 7 steps at max withen the same command --  \n \n " ;
             
             py += 300 ; 
            
             w2d = 0 ;
   
        }
        
        else if ( saved.equals("move forward")){
          println("up"); 
          w2d =1 ; // ask for number
          port.write('u');
        }
        else if ( saved.equals("move backward")){
          println("down"); 
          w2d  =1 ;
          port.write('d');
        }
        else if ( saved.equals("move right")){
          println("right"); 
           w2d =1 ;
          port.write('r');
        }
        else if ( saved.equals("move left")){
          println("left"); 
          w2d =1 ;
          port.write('l');
        }
        
        else if ( saved.equals("clear")){
          show = "\n" ; 
          py = 140 ;   
          w2d = 0 ;
          
        }
        
        else if ( saved.equals("kark mode")){
          f = createFont("Arial", 16, true);
            R = 0 ;
            G = 0 ; 
            B = 0; 
            background  = 255 ;      
          
          show = "------ KarK MODE ------\n" ; 
          py = 140 ; 
          w2d = 0 ; 
          pxx = 280 ; 
          pxn = 170 ; 
        }
        
        else if ( saved.equals("hacking mode")) {
            f = createFont("Courier", 16, true);
            R = 10;
            G = 255 ; 
            B = 10 ;  
            background  = 0 ; 
          
          show = "------ HACKING MODE ------ \n" ; 
          py = 140 ;  
          w2d = 0 ;
          pxx = 360 ;
          pxn = 200 ; 
        }
        
        else if ( saved.equals("funky mode")) {
            f = createFont("Herculanum", 16, true);
            R = 255 ;
            G = 0 ; 
            B = 127; 
            background  = 255 ;   
         
          show = "------funky m0De ------ \n" ; 
          py = 140 ;   
          w2d = 0 ;
          pxx = 330 ;
          pxn = 170 ; 
          
        }
        
        else  {
        w2d = 2 ; 
        
        }
        
      }
      else { // asking for a number 
        println(typing);
        try {
          int steps = Integer.parseInt(trim(typing));
          println(steps);
          if (steps < 8 && steps > 0 ){//valid number
            w2d = 0;
         port.write(typing);   
          }
          else{
            w2d = 3;
          } 
        }
        catch(NumberFormatException e){
           w2d = 3;
        }
      }
      typing = ""; 
      py += 28;
      
    }  
    else {  
     if (keyCode == BACKSPACE) {
       typing = typing.substring(0,max(0,typing.length()-1));
         } 
      else
         if (key != CODED) typing += key;
    }
  }
