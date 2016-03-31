// Motor driver Setup
// Pins L298N -> Mega board
int enA = 8;
int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;
int enB = 3;
boolean motor_active = false;
// for motor delay
unsigned long mStartMillis = 0;      // will store last time motor delay update
int course; // direction
int m_left_speed; // motor speed
int m_right_speed; // motor speed
int mdelay; // motor delay

void driveMotors()
{
    // this function will run the motors across the range of possible speeds
    // note that maximum speed is determined by the motor itself and the operating voltage
    // the PWM values sent by analogWrite() are fractions of the maximum speed possible by your hardware
      // Drive Forward  
      if (course == 1) {
        digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, HIGH); digitalWrite(in4, LOW); 
        analogWrite(enA, m_left_speed); analogWrite(enB, m_right_speed);
      }
      // Drive Backward
      else if (course == 2 ) {
        digitalWrite(in1, LOW); digitalWrite(in2, HIGH); digitalWrite(in3, LOW); digitalWrite(in4, HIGH); 
        analogWrite(enA, m_left_speed); analogWrite(enB, m_right_speed);
      }
      // Turn Right, direction forward
      else if (course == 3 ) {
        digitalWrite(in1, LOW); digitalWrite(in2, LOW); digitalWrite(in3, HIGH); digitalWrite(in4, LOW); 
        analogWrite(enA, m_left_speed); analogWrite(enB, m_right_speed);
      }
      // Turn Left, direction forward
      else if (course == 4 ) {
        digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW); 
        analogWrite(enA, m_left_speed); analogWrite(enB, m_right_speed);
      }
      // Stop
      else if (course == 0) {
        // now turn off motors
        digitalWrite(in1, LOW); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW);  
      }  
}

void stopMotors() {
      // now turn off motors
    // clean up & return
    digitalWrite(in1, LOW); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW);
    course = NULL;
    m_left_speed = NULL;
    m_right_speed = NULL;
    mdelay = NULL;
    motor_active = false;
    // return;
}

void dumpMotorValues() {
      Serial.print("course: ");
      Serial.print(course);
      Serial.print("\tleft speed: ");
      Serial.print(m_left_speed);
      Serial.print("\tright speed: ");
      Serial.print(m_right_speed);
      Serial.print("\tdelay: ");
      Serial.print(mdelay);
      Serial.println("\n");
}

void setup() {
  Serial.begin(9600);
  //Serial.println("Starting ...");
  //delay(9000);
  course = 0;
  m_left_speed = 122;
  m_right_speed = 122;
  mdelay = 500;
}

void loop() {
  // expected input:
  //  92 34 255
  //Serial.print("?> ");
  while (Serial.available() > 0) {
    course = Serial.parseInt();
    m_left_speed = Serial.parseInt();
    m_right_speed = Serial.parseInt();
    mdelay = Serial.parseInt();
    if (Serial.read() == '\n') {
      // TODO use the values
      dumpMotorValues();
      driveMotors();
      delay(mdelay);
      stopMotors();
    }
  }
  //Serial.println("END: loop()");
  //delay(3000);
}
