#include <Arduino.h>
// throttle channel 3 on pin 10 
const int fwd_rev_pwm_in = 9;  // Input pin for PWM signal from RC receiver
const int lft_rgt_pwm_in = 6;  // Input pin for PWM signal from RC receiver
const int left_wheel_fwd_pin = 4;     // Output pin for DC motor
const int left_wheel_rev_pin = 2;     // Output pin for DC motor
const int right_wheel_fwd_pin = 7;     // Output pin for DC motor
const int right_wheel_rev_pin = 8;     // Output pin for DC motor
const int right_wheel_pwm_out = 3;     // Output pin for DC motor
const int left_wheel_pwm_out = 5;     // Output pin for DC motor

int turn_ratio;
int turn_motorSpeed;

void setup() {
  pinMode(fwd_rev_pwm_in, INPUT);     // Set the PWM input pin as an input
  pinMode(lft_rgt_pwm_in, INPUT);     // Set the PWM input pin as an input

  pinMode(left_wheel_fwd_pin, OUTPUT);       // Set the motor pin as an output
  pinMode(left_wheel_rev_pin, OUTPUT);       // Set the motor pin as an output

  pinMode(right_wheel_fwd_pin, OUTPUT);       // Set the motor pin as an output
  pinMode(right_wheel_rev_pin, OUTPUT);       // Set the motor pin as an output

  pinMode(right_wheel_pwm_out, OUTPUT);       // Set the motor pin as an output
  pinMode(left_wheel_pwm_out, OUTPUT);       // Set the motor pin as an output

  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
}

void loop() {

  // Grab the input pwm signals 
  int fwd_rev_pwmValue = pulseIn(fwd_rev_pwm_in, HIGH);  // Read the PWM signal
  // Serial.print("fwd_rev_PWM: ");
  // Serial.println(fwd_rev_pwmValue);

  int lft_rgt_pwmValue = pulseIn(lft_rgt_pwm_in, HIGH);  // Read the PWM signal
  // Serial.print("lft_rgt_PWM: ");
  // Serial.println(lft_rgt_pwmValue);

  int motorSpeed = map(fwd_rev_pwmValue, 990, 1992, 0, 255); // Map the PWM value to motor speed
  // Serial.print("Motor Speed: ");
  // Serial.println(motorSpeed);

  if (motorSpeed < 125) {
    motorSpeed = 125 - motorSpeed; 
    digitalWrite(left_wheel_fwd_pin, LOW); // Set the motor direction
    digitalWrite(left_wheel_rev_pin, HIGH); // Set the motor direction
    digitalWrite(right_wheel_fwd_pin, LOW); // Set the motor direction
    digitalWrite(right_wheel_rev_pin, HIGH); // Set the motor direction
  }
  else if (motorSpeed > 130) {
    motorSpeed = motorSpeed - 130; 
    digitalWrite(left_wheel_fwd_pin, HIGH); // Set the motor direction
    digitalWrite(left_wheel_rev_pin, LOW); // Set the motor direction
    digitalWrite(right_wheel_fwd_pin, HIGH); // Set the motor direction
    digitalWrite(right_wheel_rev_pin, LOW); // Set the motor direction
    
  }
  else{
    motorSpeed = 0; 
  }

  motorSpeed = motorSpeed * 2; 


  // Serial.print("Motor Speed: ");
  // Serial.println(motorSpeed);

  // Calculate left and right pwm 
  if(lft_rgt_pwmValue < 1480){
    turn_ratio = map(lft_rgt_pwmValue, 980, 1480, 0, 100);
    analogWrite(left_wheel_pwm_out, motorSpeed*turn_ratio / 100); // Set the motor speed
    // Serial.print("turn_ratio: ");
    // Serial.println(turn_ratio);
    analogWrite(right_wheel_pwm_out, motorSpeed); // Set the motor speed
  } else if(lft_rgt_pwmValue > 1500){
    turn_ratio = map(lft_rgt_pwmValue, 1500, 1995, 100, 0);
    analogWrite(left_wheel_pwm_out, motorSpeed); // Set the motor speed
    analogWrite(right_wheel_pwm_out, motorSpeed*turn_ratio / 100); // Set the motor speed
  }
  else{
    analogWrite(left_wheel_pwm_out, motorSpeed); // Set the motor speed
    analogWrite(right_wheel_pwm_out, motorSpeed); // Set the motor speed
  }

}
