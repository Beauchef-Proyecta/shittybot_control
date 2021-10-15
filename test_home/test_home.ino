#include <Stepper.h>
int motorSpeed = 16;
int Lswitch = 7;

int stepsPerRevolution = 2038;  // change this to fit the number of steps per revolution
int mmPerRev = 20; //mm aproximados por revolucion segun la polea
int stepPermm = 102; // steps aproximados por mm lineal recorrido


long Distancia;
char mensaje;
bool newData = false;


// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // nothing to do inside the setup
  pinMode(Lswitch, INPUT);
  Serial.begin(9600);
  myStepper.setSpeed(motorSpeed);
}


void checkSerial() {

  if (Serial.available() > 0) {
    mensaje = Serial.read();
    newData = true; //kongfirmo que hay mensaje
  }
  if (newData == true) {

    if (mensaje == 'h') {
      //pa la casa pos h "homing"
      Serial.println("");
      Serial.println("PALACASAAAAA");
      //movimiento
      while (digitalRead(Lswitch) == HIGH) {
        myStepper.step(-1);
      }
      //Disable stepper
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      //listo
      Serial.println("Ahi noma");
      Serial.print("Tamos en 0");

    }
    //PARTE PROPUESTA
    // mensaje para recorrer distancia "A200" mm
    if (mensaje == 'A') {
      Distancia = Serial.parseFloat();
      //mover
      //paondelellevo(Distancia);
      //listo

      Serial.println("Ahi noma");
      Serial.print(" Tamos en");
      Serial.print("."); //dar posicion actual

    }
  }

}

//void paondelellevo(x){


//}

void loop() {
  checkSerial();

}
