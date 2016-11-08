
/*

- remote control by bluetooth
- Motor 
    A = right Motor (in1,in2)
    B = left  Motor (in3,in4)
    
pin connection:
  pin
  2 - bluetooth Rx
  3 - bluetooth Tx
  4 - motor controller in1
  5 - motor controller in2
  6 - motor controller in3
  7 - motor controller in4
  
 */




/* DIO used to communicate with the Bluetooth module's RXD pin */
/* DIO used to communicate with the Bluetooth module's TXD pin */
/* Initialise the software serial port */
#include <SoftwareSerial.h>
#define BT_SERIAL_RX_DIO 2
#define BT_SERIAL_TX_DIO 3
SoftwareSerial BluetoothSerial(BT_SERIAL_TX_DIO, BT_SERIAL_RX_DIO);

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

  Serial.begin(9600); // for serial monitor output
  BluetoothSerial.begin(9600);

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

  if (BluetoothSerial.available())
  {
    char c=BluetoothSerial.read();
    Serial.println(c);

    switch(c)
    {
      case 'F' : 
          Serial.println("Forward"); 
          movement_backward();
          break;
      case 'B' : 
          Serial.println("Backward"); 
          movement_forward();
          break;
      case 'L' : 
          Serial.println("Turn Left"); 
          movement_turnLeft();
          break;
      case 'R' :
          Serial.println("Turn Right"); 
          movement_turnRight();
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
  motorA_backward();
  motorB_forward();
  
  delay(delayTime);
  movement_stop();
}

void movement_turnLeft() // doesn't change moevementState
{
  motorA_forward();
  motorB_backward();
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



