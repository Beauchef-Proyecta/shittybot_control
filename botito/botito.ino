#include <Stepper.h>
int motorSpeed = 16;
int Lswitch = 7;
int stepsPerRevolution = 2038;  // change this to fit the number of steps per revolution
int abs_pos = 0; // initial position of server
int val; // initial value of input
#define INPUT_SIZE 30
int stepPermm = 102; // steps aproximados por mm lineal recorrido
float resto = 0.0;

// initialize the stepper library on pins 8 through 11
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);



void home() {
  while (digitalRead(Lswitch) == HIGH) {
    myStepper.step(-1);
  }
  abs_pos = 0;
  //Serial.println("Tamos en 0");
}

//move_axis function
void move_axis(int Id, int position) {
  if (Id == 1) {
    resto = abs_pos - position ;
    Goto(position);
    abs_pos = position;
  }
  if (Id == 2) {
    home();
  }
}

void Goto(int position) {
  //Serial.println("Goto");

  while (resto > 0) {
    myStepper.step(-1);
    resto = resto - 1;

  }
  while (resto < 0) {
    myStepper.step(1);
    resto = resto + 1;
  }

}


void getmessage() {

  // Get next command from Serial (add 1 for final 0)
  char input[INPUT_SIZE + 1];
  byte size = Serial.readBytes(input, INPUT_SIZE);
  // Add the final 0 to end the C string
  input[size] = 0;

  // Read each command pair
  char* command = strtok(input, "&");

  while (command != 0)
  {
    // Split the command in two values
    char* separator = strchr(command, ':');

    if (separator != 0)
    {
      // Actually split the string in 2: replace ':' with 0
      *separator = 0;
      int Id = atoi(command);
      //Serial.println(servoId);
      ++separator;
      int position = atoi(separator);
      //Serial.println(position);

      // Do something with servoId and position
      move_axis(Id, position);
    }

    // Find the next command in input string
    command = strtok(0, "&");
  }
}





void setup() {
  // nothing to do inside the setup
  pinMode(Lswitch, INPUT);
  Serial.begin(9600);
  myStepper.setSpeed(motorSpeed);
  home();

}
void loop() {
  getmessage();
}
