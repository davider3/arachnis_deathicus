#include <Arduino.h>

int rc_pulse3, motor_pwm5;

void setup() {
    Serial.begin(9600);
    pinMode(3, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);

}

void loop() {
    motor_pwm5 = 0;
    delay(25);
    rc_pulse3 = pulseIn(3, HIGH, 25000);
    Serial.println(rc_pulse3);
    delay(25);
    // if(rc_pulse3 > 650){
    //     motor_pwm5 = map(rc_pulse3, 650, 1600, 0, 255);
    //     // Serial.println(motor_pwm5);
    //     if(motor_pwm5 >= 0 )
    //     analogWrite(5, motor_pwm5);
    // } else {
    //     analogWrite(5, 0);
    // }
}