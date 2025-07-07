#include "Servo1.h"

TwoWire I2C = TwoWire(0); // Create a TwoWire object for I2C communication
Servo1 pwm = Servo1(PCA9685_I2C_ADDRESS, I2C); // Create a Servo1 object with the default I2C address
#define SCL_PIN 33
#define SDA_PIN 32
#define SERVO_REFRESH_RATE 50 // 50Hz for servos
int initial_position = 86; // 45 degrees
int position = 86;

void InitiateServo() {
  I2C.begin(SDA_PIN, SCL_PIN, 26000000); // Initialize I2C with SDA and SCL pins
  pwm.begin(); // Initialize the PCA9685
  pwm.setPWMFreq(SERVO_REFRESH_RATE); // Set the PWM frequency for servos
  pwm.setOscillatorFrequency(26000000);
  Wire.setClock(100000); // Set I2C clock speed to 100kHz
  delay(10);
}

void ServoStep(byte servo_ID, int step) {
  for(int i = initial_position; i <= 484; i += step) {
    pwm.setPWM(servo_ID, 0, i); // Set the servo position
    delay(50);
  }
}

void setup() {
  InitiateServo(); // Set up the servo
  pwm.setPWM(1, 0, 386); // Servo 1 to 135 degrees
  pwm.setPWM(0, 0, 86); // Servo 0 to 0 degrees
}

void loop() {
  // Example usage of ServoStep
  ServoStep(0, 1);
}