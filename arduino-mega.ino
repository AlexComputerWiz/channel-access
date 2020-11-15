/****************************************

by Alex Robinson

Version 1.1 (06/08/19)

****************************************/

// each input device uses their respective pins below

const byte switchPinA = 8; // AP5 Digital Pin
const byte switchPinB = 7; // Optex Beam Digital Pin

// each color in the relay is controlled by their respective pins below 
   
int relayAlarm = 2;
int relayRed = 3;
int relayYellow = 4;
int relayGreen = 5;

int k = 0; //counter
int c = 0; //counter

void setup ()
  {
  Serial.begin (115200);

  //establishes two inputs
  pinMode (switchPinA, INPUT);
  pinMode (switchPinB, INPUT);

  /* 
  establishes four outputs, turns them all off.
  Inverted logic: HIGH signal keeps it off
  LOW triggers the relay on.  
  */
  
  pinMode (relayAlarm, OUTPUT);
  digitalWrite (relayAlarm, HIGH);
  pinMode (relayRed, OUTPUT);
  digitalWrite (relayRed, HIGH);
  pinMode (relayYellow, OUTPUT);
  digitalWrite (relayYellow, HIGH);
  pinMode (relayGreen, OUTPUT);
  digitalWrite (relayGreen, HIGH);
  }  // end of setup

void loop ()
  {

  if (c < 1){
    digitalWrite (relayRed, LOW);
    Serial.println ("Red Light ON.");
    Serial.println ("SYSTEM IS ARMED AND READY!");
    c++;
  }
    
// AP-5 (K1) is activated via Key Fob
  if (digitalRead (switchPinA) == HIGH)
     {
     accessGranted();
     } // end if switchState is LOW

// Beam alarm is activated
  if (digitalRead (switchPinB) == LOW)
     {
     intruderAlert();
     } // end if switchState is HIGH
  } //end of loop

///// function definitions /////

void accessGranted(){
  Serial.println ("Access Granted.");
  
  digitalWrite (relayRed, HIGH); 
  Serial.println ("Red Light OFF.");
  digitalWrite (relayGreen, LOW);
  Serial.println ("Green Light ON.");
  delay (60000); //1 MIN
  digitalWrite (relayGreen, HIGH);
  Serial.println ("Green Light OFF.");
  Serial.println ("Yellow Light Countdown Sequence ON.");
  flashYellowLight();
  c = 0; //reset counter, rearm system
}//end void

void intruderAlert(){
  Serial.println ("Access Denied.");
  Serial.println ("Red Light Strobe ON.");
  Serial.println ("Alarm ON.");
  
  digitalWrite (relayAlarm, LOW);
  
  while (k < 20){
    digitalWrite (relayRed, LOW);
    delay (500);
    digitalWrite (relayRed, HIGH);
    delay (500);
    k++;
  }//end while

  digitalWrite (relayAlarm, HIGH);
  
  c = 0;//reset counter, rearm system
  
}//end void

void flashYellowLight(){
  digitalWrite (relayYellow, LOW);
  delay (10000);
  
  while (k < 10){
    digitalWrite (relayYellow, HIGH);
    delay (500);
    digitalWrite (relayYellow, LOW);
    delay (500);
    k++;
  } //end while

  digitalWrite (relayYellow, HIGH);

  k = 0; //reset counter
} //end void
