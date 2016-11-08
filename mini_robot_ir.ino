
/*

- remote control by IR
- Motor 
    B = right Motor (in1,in2)
    A = left  Motor (in3,in4)
    
pin connection:
  pin
  4 - motor controller in1
  5 - motor controller in2
  6 - motor controller in3
  7 - motor controller in4
  11 - IR  
 */





// pin for IR receiver 
#include <IRremote.h> 
int receiver = 11; // pin 11 of IR receiver to Arduino digital pin 11
IRrecv irrecv(receiver); 
decode_results results;

// pin for motors
int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;
int delayTime = 1000;  //  delaytime; 



//////////////////////////////////////////////////////////////////////////////////////////////////
// Setup / Loop
//////////////////////////////////////////////////////////////////////////////////////////////////

// the setup routine runs once when you press reset:
void setup() 
{                

  Serial.begin(9600); 
  irrecv.enableIRIn();  // Start the receiver

  // initialize motor pins
  // A = right motor
  // B = left motor
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 

}

// the loop routine runs over and over again forever:
void loop() 
{


  // Receive IR signal

  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    Serial.println(results.value, HEX); // display it on serial monitor in hexadecimal
    irrecv.resume(); // receive the next value
    switch(results.value)
    {
      case 0xFF906F : 
          movement_forward();
          break;
      case 0xFFA857 : 
          movement_backward();
          break;
      case 0xFF02FD  : 
          movement_turnLeft();
          break;
      case 0xFFC23D  : 
          movement_turnRight();
          break;
      case 0xFFA25D  : 
          movement_stop();
          break;
      default      :
          Serial.println("Other Button"); 
    }
  }  
}




//////////////////////////////////////////////////////////////////////////////////////////////////
//  Movement Control
//////////////////////////////////////////////////////////////////////////////////////////////////

void movement_forward()
{
  motorA_forward();
  motorB_forward();

  delay(delayTime);
  movement_stop();  
}

void movement_backward() 
{
  motorA_backward();
  motorB_backward();

  delay(delayTime);
  movement_stop();  
}

void movement_turnRight() // doesn't change moevementState
{
  motorB_backward();
  motorA_forward();
  
  delay(delayTime);
  movement_stop();
}

void movement_turnLeft() // doesn't change moevementState
{
  motorB_forward();
  motorA_backward();
  delay(delayTime);

  movement_stop();
}

void movement_stop()
{
  motorA_stop();
  motorB_stop();
}




  

//////////////////////////////////////////////////////////////////////////////////////////////////
//  Motor Control
//////////////////////////////////////////////////////////////////////////////////////////////////

void motorA_forward()
{
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);   
}

void motorA_backward()
{
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);   
}

void motorA_stop()
{
  // break movement
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, HIGH);   
}

void motorB_forward()
{
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);   
}

void motorB_backward()
{
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);   
}

void motorB_stop()
{
  // break movement
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, HIGH);   
}




