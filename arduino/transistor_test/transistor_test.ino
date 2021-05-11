// Quick Triode Model Transistor test for NodeMCU and TIP31C

//define new pin names
//NPN transistor pin connecctions
#define Base       D0
#define Collector  D1
#define Emitter    D2

void setup() {
  // initialize serial communication at 9600 baud:
  Serial.begin(9600);
}

void trans_test_npn (){
  // Transistor diode tests a la triode model
  // Test diodes in forward bias

  pinMode(Base, OUTPUT);
  pinMode(Collector, INPUT);
  pinMode(Emitter, INPUT);

  digitalWrite(Base, HIGH);

  bool collector_diode_forward = digitalRead(Collector);
  bool emitter_diode_forward = digitalRead(Emitter);

  digitalWrite(Base, LOW);

  Serial.println("Both diodes should be high for the forward bias diode test (1)");
  
  Serial.print("The collector diode is ");
  Serial.println(collector_diode_forward);

  Serial.print("The emitter diode is ");
  Serial.println(emitter_diode_forward);

  if (collector_diode_forward && emitter_diode_forward) {
    Serial.println("Forward bias diode test successful");
  } else {
    Serial.println("Forward bias diode test failed - transistor is faulty");
  }

  // Test diodes in reverse bias

  pinMode(Base, INPUT);
  pinMode(Collector, OUTPUT);
  pinMode(Emitter, OUTPUT);
  
  digitalWrite(Collector, HIGH);

  bool collector_diode_reverse = digitalRead(Base);

  digitalWrite(Collector, LOW);
  digitalWrite(Emitter, HIGH);

  bool emitter_diode_reverse = digitalRead(Base);

  Serial.println("Both diodes should be low for the reverse bias diode test (0)");
  
  Serial.print("The collector diode is ");
  Serial.println(collector_diode_reverse);

  Serial.print("The emitter diode is ");
  Serial.println(emitter_diode_reverse);

  if (!collector_diode_reverse && !emitter_diode_reverse) {
    Serial.println("Reverse bias diode test successful");
  } else {
    Serial.println("Reverse bias diode test failed - transistor is faulty");
  }

  if (collector_diode_forward && emitter_diode_forward && !collector_diode_reverse && !emitter_diode_reverse) {
    Serial.println("The transistor appears to be working correctly");
  } else {
    Serial.println("The transistor appears to be faulty");
  }
}

void loop(){
  trans_test_npn();
  Serial.println();
  delay(2000);
}
