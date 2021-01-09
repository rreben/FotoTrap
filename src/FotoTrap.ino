/*
  FotoTool
  There are two major modes:
  1. High speed fotography: When the microphone detects a sound the flash is triggered
  2. Foto trap: When the PIR detects a motion the autofocus is triggered and then the shutter is triggered

  In each major mode there are two submodes. The tool can be inactive, or waiting for motion (or sound respectively)

 */


int flash = 2;        // when high the opto coupler shortcuts the pc cable
int shutter = 3;      // when high the opto coupler shortcuts the base and the tip from the "klinke", this triggers the shutter
int autofocus = 4;    // when high the opto coupler shortcuts the base and the middle from the "klinke", this starts auto focus
int pir = 5;          // this gets high when a motion is detected
int button = 6;       // internal pull up button for testing purposes
int microphone = 7;   // gets LOW (1) when sound is detected
int relais = 8;       // high pulls the relais
int externalLED = 10; // when high the LED on the front panes is on
int externalRedButton = 11;    // pull up button
int externalGreenButton = 12;  // pull up button
int buildInLED = 13;

int fotoTrapMode = 0; // is 1 when in fototrap mode
int highSpeedMode = 0;// is 1 when in high speed fotography mode

int fotoTrapSubMode = 0; // is 0 when inactive, is 1 when waiting for motion
int externalRedButtonValue = 0;        // Red button triggers foto trap mode
int externalRedButtonOldValue = 0;

int highSpeedSubMode = 0; // is 0 when inactive, is 1 when waiting for sound
int externalGreenButtonValue = 0;      // Green button triggers high speed mode
int externalGreenButtonOldValue = 0;

int soundDetected = 0;
int motionDetected = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(buildInLED, OUTPUT);
  pinMode(externalLED, OUTPUT);
  pinMode(flash, OUTPUT);
  pinMode(shutter, OUTPUT);
  pinMode(autofocus, OUTPUT);
  pinMode(relais, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(microphone, INPUT);
  pinMode(button, INPUT);
  pinMode(externalRedButton, INPUT);
  pinMode(externalGreenButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  externalRedButtonValue = digitalRead(externalRedButton);
  if ((externalRedButtonValue == HIGH) && (externalRedButtonOldValue == LOW)){
    fotoTrapMode = 1;
    highSpeedMode = 0;
    fotoTrapSubMode = 1 -fotoTrapSubMode;
    delay(10);
  }
  externalRedButtonOldValue = externalRedButtonValue;
  if (fotoTrapMode == 1){
    if (fotoTrapSubMode == 1){
      digitalWrite(buildInLED, HIGH);
      digitalWrite(externalLED, HIGH);
      motionDetected = digitalRead(pir);
      if (motionDetected == HIGH){
        digitalWrite(autofocus, HIGH); // trigger autofocus
        delay(500);                    // the camera needs some time to trigger the autofocus
        digitalWrite(autofocus, LOW);
        delay(500);                    // wait some time before ..
        digitalWrite(shutter, HIGH);   // triggering the shutter
        delay(500);                    // camera needs a long pulse to trigger the shutter
        digitalWrite(shutter, LOW);
        motionDetected = 0;
        // blink external LED and wait some time before detecting motion again
        digitalWrite(externalLED, LOW);
        delay(1000);
        digitalWrite(externalLED, HIGH);
        delay(1000);
        digitalWrite(externalLED, LOW);
        delay(1000);
        digitalWrite(externalLED, HIGH);
        delay(1000);
        digitalWrite(externalLED, LOW);
        delay(1000);
        digitalWrite(externalLED, HIGH);
        delay(1000);
      }
    }else{
      digitalWrite(buildInLED, LOW);
      digitalWrite(externalLED, LOW);
    }
  }
  externalGreenButtonValue = digitalRead(externalGreenButton);
  if ((externalGreenButtonValue == HIGH) && (externalGreenButtonOldValue == LOW)){
    fotoTrapMode = 0;
    highSpeedMode = 1;
    highSpeedSubMode = 1;
    delay(10);
    digitalWrite(buildInLED, HIGH);   // We do this for testing purposes, e.g. calibrating the mic via potentiometer
    digitalWrite(relais, HIGH);       // pull the relais to shut a lamp of and darken the room
    digitalWrite(shutter, HIGH);      // we now open the shutter we do this before listening, because the relais or shutter sound
                                      // might trigger the flash
    // fast blink external LED and wait some time before detecting motion again
    digitalWrite(externalLED, LOW);
    delay(500);
    digitalWrite(externalLED, HIGH);
    delay(500);
    digitalWrite(externalLED, LOW);
    delay(500);
    digitalWrite(externalLED, HIGH);
    delay(500);
    digitalWrite(externalLED, LOW);
    delay(500);
    digitalWrite(externalLED, HIGH);
    delay(500);
    digitalWrite(externalLED, LOW);   // end with low, so that the LED does not radiate light when shutter is open
  }
  externalGreenButtonOldValue = externalGreenButtonValue;
  if (highSpeedMode == 1){
    if (highSpeedSubMode == 1){
      soundDetected = digitalRead(microphone);
      if (soundDetected == LOW){
        digitalWrite(flash, HIGH);        // trigger flash
        delay(5);                         // some time for the flash to be triggered
        digitalWrite(flash, LOW);         // let the flash reload
        digitalWrite(shutter, LOW);       // close shutter
        digitalWrite(relais, LOW);        // turn light back on
        digitalWrite(buildInLED, LOW);
        highSpeedSubMode = 0;
      }
    }
  }
}
