#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  240 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  340 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define pi 3.14159
float half_pi = pi/2.0;
int servoDelta = SERVOMAX - SERVOMIN;
int calculatedPulseLen;

void setup() 
{            
   pwm.begin();
   pwm.setPWMFreq(SERVO_FREQ); 
   ledcSetup(0, 5000, 8);
   ledcAttachPin(2, 0);
   Serial.begin(9600);
}


void loop() 
{
  for (int i = 0; i < 255; i ++) {
     ledcWrite(0, i);
     delay(15);
   }
   
  delay(500);
  sineWaveLoop();
  delay(500);

   for (int i = 255; i > 0; i --) {
     ledcWrite(0, i);
     delay(15);
   }

}


void sineWaveLoop(){
    for(int i = 0; i < 100; i ++) {
    calculatedPulseLen = SERVOMIN +servoDelta*sineWave(i);
    pwm.setPWM(0, 0, calculatedPulseLen);
    delay(30);
  }
}


float sineWave(int i) {
  return 0.5 * (sin((i/100.0)* 2 * pi) + 1);
}
