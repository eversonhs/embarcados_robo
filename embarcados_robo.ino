#define M1_IN1 11
#define M1_IN2 10
#define M2_IN1 9
#define M2_IN2 8

#define BT_ESQ 34
#define BT_FRT 35
#define BT_ONOFF 36
#define BT_DIR 37 

#define P_ECHO 2
#define P_TRG 3

void setup() {
  pinMode(BT_ESQ, INPUT);
  pinMode(BT_FRT, INPUT);
  pinMode(BT_ONOFF, INPUT);
  pinMode(BT_DIR, INPUT);

  pinMode(P_ECHO, INPUT);
  pinMode(P_TRG, OUTPUT);

  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);
  
  Serial.begin(9600);
}

float calcular_distancia() {
  digitalWrite(P_TRG, LOW);
  delayMicroseconds(2);
  digitalWrite(P_TRG, HIGH);
  delayMicroseconds(2);
  digitalWrite(P_TRG, LOW);
  delayMicroseconds(2);

  unsigned long tempo = pulseIn(P_ECHO, HIGH);
  float distancia = tempo / 29 /2; 
  return distancia;        
}

void moverFrente() {
  digitalWrite(M1_IN1, HIGH);
  digitalWrite(M1_IN2, LOW);

  digitalWrite(M2_IN1, HIGH);
  digitalWrite(M2_IN2, LOW);
}

void moverTras() {
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, HIGH);

  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, HIGH);
}

void moverDir() {
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, HIGH);

  digitalWrite(M2_IN1, HIGH);
  digitalWrite(M2_IN2, LOW);
}

void moverEsq() {
  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, HIGH);

  digitalWrite(M1_IN1, HIGH);
  digitalWrite(M1_IN2, LOW);
}

void parar() {
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, LOW);

  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, LOW);
}

bool ligado = false;

void loop() {
    ligado = digitalRead(BT_ONOFF) == LOW ? !ligado : ligado;
    delay(100);
    parar();
    if(ligado) {
      if(digitalRead(BT_DIR) == LOW){
        moverDir();
      }
      if(digitalRead(BT_ESQ) == LOW){
        moverEsq();
      }
      if(digitalRead(BT_FRT) == LOW){
        moverFrente();
      }
      if(calcular_distancia() < 15.0) {
        moverTras();
        delay(1000);
        moverDir();
        delay(1000);
      }    
    }
}
