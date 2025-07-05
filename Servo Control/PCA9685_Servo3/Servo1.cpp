#include "Servo1.h"
#include <Wire.h>

//#define ENABLE_DEBUG_OUTPUT

/*!
 *    Instantiates a new PCA9685 PWM driver chip with the I2C address on a
 * TwoWire interface
 */
Servo1::Servo1()
    : _i2caddr(PCA9685_I2C_ADDRESS), _i2c(&Wire) {}

/*!
 *    Instantiates a new PCA9685 PWM driver chip with the I2C address on a
 * TwoWire interface
 *    addr The 7-bit I2C address to locate this chip, default is 0x40
 */
Servo1::Servo1(const uint8_t addr)
    : _i2caddr(addr), _i2c(&Wire) {}

/*!
 *    Instantiates a new PCA9685 PWM driver chip with the I2C address on a
 * TwoWire interface
 *    addr The 7-bit I2C address to locate this chip, default is 0x40
 *    i2c  A reference to a 'TwoWire' object that we'll use to communicate
 *  with
 */
Servo1::Servo1(const uint8_t addr,
                                                 TwoWire &i2c)
    : _i2caddr(addr), _i2c(&i2c) {}

/*!
 *    Setups the I2C interface and hardware
 *    prescale
 *          Sets External Clock (Optional)
 */
void Servo1::begin(uint8_t prescale) {
  _i2c->begin();
  reset();
  if (prescale) {
    setExtClk(prescale);
  } else {
    // set a default frequency
    setPWMFreq(1000);
  }
  // set the default internal frequency
  setOscillatorFrequency(FREQUENCY_OSCILLATOR);
}

/*!
 *    Sends a reset command to the PCA9685 chip over I2C
 */
void Servo1::reset() {
  write8(PCA9685_MODE1, MODE1_RESTART);
  delay(10);
}

/*!
 *    Puts board into sleep mode
 */
void Servo1::sleep() {
  uint8_t awake = read8(PCA9685_MODE1);
  uint8_t sleep = awake | MODE1_SLEEP; // set sleep bit high
  write8(PCA9685_MODE1, sleep);
  delay(5); // wait until cycle ends for sleep to be active
}

/*!
 *    Wakes board from sleep
 */
void Servo1::wakeup() {
  uint8_t sleep = read8(PCA9685_MODE1);
  uint8_t wakeup = sleep & ~MODE1_SLEEP; // set sleep bit low
  write8(PCA9685_MODE1, wakeup);
}

/*!
 *    Sets EXTCLK pin to use the external clock
 *    prescale
 *          Configures the prescale value to be used by the external clock
 */
void Servo1::setExtClk(uint8_t prescale) {
  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode & ~MODE1_RESTART) | MODE1_SLEEP; // sleep
  write8(PCA9685_MODE1, newmode); // go to sleep, turn off internal oscillator

  // This sets both the SLEEP and EXTCLK bits of the MODE1 register to switch to
  // use the external clock.
  write8(PCA9685_MODE1, (newmode |= MODE1_EXTCLK));

  write8(PCA9685_PRESCALE, prescale); // set the prescaler

  delay(5);
  // clear the SLEEP bit to start
  write8(PCA9685_MODE1, (newmode & ~MODE1_SLEEP) | MODE1_RESTART | MODE1_AI);

#ifdef ENABLE_DEBUG_OUTPUT
  Serial.print("Mode now 0x");
  Serial.println(read8(PCA9685_MODE1), HEX);
#endif
}

/*!
 *    Sets the PWM frequency for the entire chip, up to ~1.6 KHz
 *    freq Floating point frequency that we will attempt to match
 */
void Servo1::setPWMFreq(float freq) {
#ifdef ENABLE_DEBUG_OUTPUT
  Serial.print("Attempting to set freq ");
  Serial.println(freq);
#endif
  // Range output modulation frequency is dependant on oscillator
  if (freq < 1)
    freq = 1;
  if (freq > 3500)
    freq = 3500; // Datasheet limit is 3052=50MHz/(4*4096)

  float prescaleval = ((_oscillator_freq / (freq * 4096.0)) + 0.5) - 1;
  if (prescaleval < PCA9685_PRESCALE_MIN)
    prescaleval = PCA9685_PRESCALE_MIN;
  if (prescaleval > PCA9685_PRESCALE_MAX)
    prescaleval = PCA9685_PRESCALE_MAX;
  uint8_t prescale = (uint8_t)prescaleval;

#ifdef ENABLE_DEBUG_OUTPUT
  Serial.print("Final pre-scale: ");
  Serial.println(prescale);
#endif

  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode & ~MODE1_RESTART) | MODE1_SLEEP; // sleep
  write8(PCA9685_MODE1, newmode);                             // go to sleep
  write8(PCA9685_PRESCALE, prescale); // set the prescaler
  write8(PCA9685_MODE1, oldmode);
  delay(5);
  // This sets the MODE1 register to turn on auto increment.
  write8(PCA9685_MODE1, oldmode | MODE1_RESTART | MODE1_AI);

#ifdef ENABLE_DEBUG_OUTPUT
  Serial.print("Mode now 0x");
  Serial.println(read8(PCA9685_MODE1), HEX);
#endif
}

/*!
 *    Sets the output mode of the PCA9685 to either
 *  open drain or push pull / totempole.
 *  Warning: LEDs with integrated zener diodes should
 *  only be driven in open drain mode.
 *    totempole Totempole if true, open drain if false.
 */
void Servo1::setOutputMode(bool totempole) {
  uint8_t oldmode = read8(PCA9685_MODE2);
  uint8_t newmode;
  if (totempole) {
    newmode = oldmode | MODE2_OUTDRV;
  } else {
    newmode = oldmode & ~MODE2_OUTDRV;
  }
  write8(PCA9685_MODE2, newmode);
#ifdef ENABLE_DEBUG_OUTPUT
  Serial.print("Setting output mode: ");
  Serial.print(totempole ? "totempole" : "open drain");
  Serial.print(" by setting MODE2 to ");
  Serial.println(newmode);
#endif
}

/*!
 *    Reads set Prescale from PCA9685
 *  @return prescale value
 */
uint8_t Servo1::readPrescale(void) {
  return read8(PCA9685_PRESCALE);
}

/*!
 *    Gets the PWM output of one of the PCA9685 pins
 *    num One of the PWM output pins, from 0 to 15
 *  @return requested PWM output value
 */
uint8_t Servo1::getPWM(uint8_t num) {
  _i2c->requestFrom((int)_i2caddr, PCA9685_LED0_ON_L + 4 * num, (int)4);
  return _i2c->read();
}

/*!
 *    Sets the PWM output of one of the PCA9685 pins
 *    num One of the PWM output pins, from 0 to 15
 *    on At what point in the 4096-part cycle to turn the PWM output ON
 *    off At what point in the 4096-part cycle to turn the PWM output OFF
 *  @return result from endTransmission
 */
uint8_t Servo1::setPWM(uint8_t num, uint16_t on,
                                        uint16_t off) {
#ifdef ENABLE_DEBUG_OUTPUT
  Serial.print("Setting PWM ");
  Serial.print(num);
  Serial.print(": ");
  Serial.print(on);
  Serial.print("->");
  Serial.println(off);
#endif

  _i2c->beginTransmission(_i2caddr);
  _i2c->write(PCA9685_LED0_ON_L + 4 * num);
  _i2c->write(on);
  _i2c->write(on >> 8);
  _i2c->write(off);
  _i2c->write(off >> 8);
  return _i2c->endTransmission();
}

/*!
 *     Helper to set pin PWM output. Sets pin without having to deal with
 * on/off tick placement and properly handles a zero value as completely off and
 * 4095 as completely on.  Optional invert parameter supports inverting the
 * pulse for sinking to ground.
 *     num One of the PWM output pins, from 0 to 15
 *     val The number of ticks out of 4096 to be active, should be a value
 * from 0 to 4095 inclusive.
 *     invert If true, inverts the output, defaults to 'false'
 */
void Servo1::setPin(uint8_t num, uint16_t val, bool invert) {
  // Clamp value between 0 and 4095 inclusive.
  val = min(val, (uint16_t)4095);
  if (invert) {
    if (val == 0) {
      // Special value for signal fully on.
      setPWM(num, 4096, 0);
    } else if (val == 4095) {
      // Special value for signal fully off.
      setPWM(num, 0, 4096);
    } else {
      setPWM(num, 0, 4095 - val);
    }
  } else {
    if (val == 4095) {
      // Special value for signal fully on.
      setPWM(num, 4096, 0);
    } else if (val == 0) {
      // Special value for signal fully off.
      setPWM(num, 0, 4096);
    } else {
      setPWM(num, 0, val);
    }
  }
}

/*!
 *    Sets the PWM output of one of the PCA9685 pins based on the input
 * microseconds, output is not precise
 *    num One of the PWM output pins, from 0 to 15
 *    Microseconds The number of Microseconds to turn the PWM output ON
 */
void Servo1::writeMicroseconds(uint8_t num,
                                                uint16_t Microseconds) {
#ifdef ENABLE_DEBUG_OUTPUT
  Serial.print("Setting PWM Via Microseconds on output");
  Serial.print(num);
  Serial.print(": ");
  Serial.print(Microseconds);
  Serial.println("->");
#endif

  double pulse = Microseconds;
  double pulselength;
  pulselength = 1000000; // 1,000,000 us per second

  // Read prescale
  uint16_t prescale = readPrescale();

#ifdef ENABLE_DEBUG_OUTPUT
  Serial.print(prescale);
  Serial.println(" PCA9685 chip prescale");
#endif

  // Calculate the pulse for PWM based on Equation 1 from the datasheet section
  // 7.3.5
  prescale += 1;
  pulselength *= prescale;
  pulselength /= _oscillator_freq;

#ifdef ENABLE_DEBUG_OUTPUT
  Serial.print(pulselength);
  Serial.println(" us per bit");
#endif

  pulse /= pulselength;

#ifdef ENABLE_DEBUG_OUTPUT
  Serial.print(pulse);
  Serial.println(" pulse for PWM");
#endif

  setPWM(num, 0, pulse);
}

/*!
 *    Getter for the internally tracked oscillator used for freq
 * calculations
 *  @returns The frequency the PCA9685 thinks it is running at (it cannot
 * introspect)
 */
uint32_t Servo1::getOscillatorFrequency(void) {
  return _oscillator_freq;
}

/*!
 *   Setter for the internally tracked oscillator used for freq
 * calculations
 *   freq The frequency the PCA9685 should use for frequency calculations
 */
void Servo1::setOscillatorFrequency(uint32_t freq) {
  _oscillator_freq = freq;
}

/******************* Low level I2C interface */
uint8_t Servo1::read8(uint8_t addr) {
  _i2c->beginTransmission(_i2caddr);
  _i2c->write(addr);
  _i2c->endTransmission();

  _i2c->requestFrom((uint8_t)_i2caddr, (uint8_t)1);
  return _i2c->read();
}

void Servo1::write8(uint8_t addr, uint8_t d) {
  _i2c->beginTransmission(_i2caddr);
  _i2c->write(addr);
  _i2c->write(d);
  _i2c->endTransmission();
}