
#include <Servo.h>

Servo servo_control[6];  // create servo object array to control a servo or motor
char serial_buf[5] = {};
uint8_t serial_in = 0;

void setup() {
  // put your setup code here, to run once:
  uint8_t i;

  Serial.begin(9600);
  
  servo_control[0].attach(A0);
  servo_control[1].attach(A1);
  servo_control[2].attach(A2);
  servo_control[3].attach(A3);
  servo_control[4].attach(A4);
  servo_control[5].attach(A5);

  for (i = 0; i < 6; i++) {
    servo_control[i].write(0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  char temp_buf;
  uint16_t i;

  if (Serial.available()) {
    temp_buf = Serial.read();
    //Serial.write(temp_buf);
    
    if (serial_in == 0) {
      if ('A' <= temp_buf && temp_buf <= 'F') {
        serial_buf[serial_in] = temp_buf;
        serial_in++;
      }
    } else {
      if ('0' <= temp_buf && temp_buf <= '9') {
        serial_buf[serial_in] = temp_buf;
        serial_in++;
      } else {
        serial_in = 0;
      }
    }

    if (serial_in == 5) {
      i = (serial_buf[1] - '0') * 1000 + (serial_buf[2] - '0') * 100 + (serial_buf[3] - '0') * 10 + (serial_buf[4] - '0') * 1;
      i = map(i, 0, 1023, 0, 180);
      servo_control[serial_buf[0] - 'A'].write(i);
      serial_in = 0;
    }
  }
}
