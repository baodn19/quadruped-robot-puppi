#include "Servo1.h"

TwoWire I2C = TwoWire(0);
Servo1 pwm = Servo1(PCA9685_I2C_ADDRESS, I2C);
#define SCL_PIN 33
#define SDA_PIN 32
#define SERVO_REFRESH_RATE 50 // Hz

void InitiateServo() {
  I2C.begin(SDA_PIN, SCL_PIN, 26000000); // Initialize I2C with SDA and SCL pins
  pwm.begin(); // Initialize the PCA9685
  pwm.setOscillatorFrequency(26000000); // Set the oscillator frequency
  pwm.setPWMFreq(SERVO_REFRESH_RATE); // Set the PWM frequency for servos
  Wire.setClock(100000); // Set I2C clock speed to 100kHz
  delay(10); // Allow time for the PCA9685 to initialize
}

void setup() {
  InitiateServo(); // Call the function to initialize the servo
  pwm.setPWM(1, 0, 386);
}

void loop() {
  // Swing within 45 degrees range
  pwm.setPWM(0, 0, 286); 
  delay(500);
  pwm.setPWM(0, 0, 386); 
  delay(500); 
}