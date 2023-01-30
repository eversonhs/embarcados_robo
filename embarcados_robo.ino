#include <Stepper.h> 

const int stepsPerRevolution = 64; 

#define VELOCIDADE 300

#define M1_IN1 8
#define M1_IN2 9
#define M1_IN3 10
#define M1_IN4 11

#define M2_IN1 42
#define M2_IN2 43
#define M2_IN3 44
#define M2_IN4 45

#define BT_ESQ 34
#define BT_FRT 35
#define BT_ONOFF 36
#define BT_DIR 37 

#define P_ECHO 2
#define P_TGR 3

//Stepper motor1(stepsPerRevolution, M1_IN1, M1_IN3, M1_IN2, M1_IN4);
Stepper motor2(stepsPerRevolution, M2_IN1, M2_IN3, M2_IN2, M2_IN4);

void setup() {
  pinMode(BT_ESQ, INPUT);
  pinMode(BT_FRT, INPUT);
  pinMode(BT_ONOFF, INPUT);
  pinMode(BT_DIR, INPUT);

  pinMode(P_ECHO, INPUT);
  pinMode(P_TGR, OUTPUT);

//  motor1.setSpeed(VELOCIDADE);
  motor2.setSpeed(VELOCIDADE);
  Serial.begin(9600);
}

float calcular_distancia(int p_trg, int p_ech) {
  digitalWrite(p_trg, LOW);
  delayMicroseconds(2);
  digitalWrite(p_trg, HIGH);
  delayMicroseconds(2);
  digitalWrite(p_trg, LOW);
  delayMicroseconds(2);

  unsigned long tempo = pulseIn(p_ech, HIGH);
  float distancia = tempo / 29 /2; 
  return distancia;        
}

void moverFrente() {
  //motor1.step(500);
   //for (int i = 10; i<=60; i=i+10){
   //motor1.setSpeed(i);
   //motor1.step(40*i);
   //}
  for (int i = 0; i<=3; i++)
   {
   motor2.step(-512); 
   delay(2000);
   }
}


void loop() {
    Serial.print("besq: ");
    Serial.println(digitalRead(BT_ESQ));
    
    Serial.print("bfrt: ");
    Serial.println(digitalRead(BT_FRT));
    
    Serial.print("bonoff: ");
    Serial.println(digitalRead(BT_ONOFF));

    Serial.print("bDIR: ");
    Serial.println(digitalRead(BT_DIR));
    if(digitalRead(BT_DIR) == LOW){
      moverFrente();
    }
    delay(100);
}
