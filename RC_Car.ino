
#define CH1 3
#define CH3 5

#define LeftMotorS 10
#define LeftMotorP 9
#define LeftMotorM 8
#define RightMotorS 11
#define RightMotorP 7
#define RightMotorM 6


// Integers to represent values from sticks and pots
int Turn;
int Throtle;
bool Shifter; // for switch

// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}


// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}


void setup(){
  // Set up serial monitor
  // Serial.begin(115200);
  
  // Reciver pin mode
  pinMode(CH1, INPUT);
  pinMode(CH3, INPUT);
  // Motor pin mode
  pinMode(LeftMotorS, OUTPUT);
  pinMode(LeftMotorP, OUTPUT);
  pinMode(LeftMotorM, OUTPUT);
  pinMode(RightMotorS, OUTPUT);
  pinMode(RightMotorP, OUTPUT);
  pinMode(RightMotorM, OUTPUT);

}

// =============================== Left Motor =================================
void LeftMotorForword(int speed, int Direction){
  // Forword
  if(Direction == 0){
    digitalWrite(LeftMotorP, HIGH);
    digitalWrite(LeftMotorM, LOW);
  }else{
    digitalWrite(LeftMotorP, LOW);
    digitalWrite(LeftMotorM, HIGH);
  }
  // speed
  analogWrite(LeftMotorS, speed);
}


void LeftMotorBackword(int speed, int Direction){
  // Backword
  if(Direction == 0){
    digitalWrite(LeftMotorP, LOW);
    digitalWrite(LeftMotorM, HIGH);
  }else{
    digitalWrite(LeftMotorP, HIGH);
    digitalWrite(LeftMotorM, LOW);
  }
  // speed
  analogWrite(LeftMotorS, speed);
}

// ================================ Right Motor ==========================
void RightMotorForword(int speed, int Direction){
  // Forword
  if(Direction == 0){
    digitalWrite(RightMotorP, HIGH);
    digitalWrite(RightMotorM, LOW);
  }else{
    digitalWrite(RightMotorP, LOW);
    digitalWrite(RightMotorM, HIGH);
  }
  // speed
  analogWrite(RightMotorS, speed);
}


void RightMotorBackword(int speed, int Direction){
  // Backword
  if(Direction == 0){
    digitalWrite(RightMotorP, LOW);
    digitalWrite(RightMotorM, HIGH);
  }else{
    digitalWrite(RightMotorP, HIGH);
    digitalWrite(RightMotorM, LOW);
  }
  // speed
  analogWrite(RightMotorS, speed);
}


void loop() {
  // Get values for each channel
  Shifter = readSwitch(12, false);
  
  int TurnData = readChannel(CH1, -100, 100, -100);
  Turn = map(TurnData, -100, 100, 0, 255);

  int ThrotleData = readChannel(CH3, -100, 100, -100);
  Throtle = map(ThrotleData, -100, 100, 0, 255);

  if(Turn != 0){
    // Turn right
    if(Turn > 180){
      LeftMotorForword(Throtle, Shifter);
      RightMotorBackword(Throtle, Shifter);
    }
    // Turn Left
    if(Turn < 100){
      RightMotorForword(Throtle, Shifter);
      LeftMotorBackword(Throtle, Shifter);
    }
    if(Turn > 100 && Turn < 180){
      RightMotorForword(Throtle, Shifter);
      LeftMotorForword(Throtle, Shifter);
    }
  }

  delay(50);
}