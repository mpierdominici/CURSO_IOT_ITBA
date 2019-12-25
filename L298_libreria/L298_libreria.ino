#define IN1 D3
#define IN2 D2
#define ENA D1
class L298_NODEMCU {
  public:
  L298_NODEMCU(char enablePin,char in1Pin,char in2Pin);
  void L298_NODEMCU_DETENR(void);
  void L298_NODEMCU_AVANZAR(int duty);
  void L298_NODEMCU_RETROCEDER(int duty);
  
  
  private:
  char enablePin;
  char in1Pin;
  char in2Pin;
};

L298_NODEMCU motorI(ENA,IN1,IN2);
void setup() {
  
}


void loop() {
  for(int i=0;i<10;i++){
    motorI.L298_NODEMCU_AVANZAR(i*103);
    delay(500);
  }
  motorI.L298_NODEMCU_DETENR();
  delay(1000);
  for(int i=0;i<10;i++){
    motorI.L298_NODEMCU_RETROCEDER(i*103);
    delay(500);
  }
   motorI.L298_NODEMCU_DETENR();
  delay(1000);
 
}




 L298_NODEMCU::L298_NODEMCU(char enablePin,char in1Pin,char in2Pin){
  this->enablePin=enablePin;
  this->in1Pin=in1Pin;
  this->in2Pin=in2Pin;
  pinMode(this->enablePin,OUTPUT);
  pinMode(this->in1Pin,OUTPUT);
  pinMode(this->in2Pin,OUTPUT);
  digitalWrite(this->in1Pin,HIGH);
}

void L298_NODEMCU::L298_NODEMCU_DETENR(void){
  analogWrite(enablePin,0);
}

void L298_NODEMCU::L298_NODEMCU_AVANZAR(int duty){
  L298_NODEMCU_DETENR();
  digitalWrite(in1Pin,HIGH);
  digitalWrite(in2Pin,LOW);
  analogWrite(enablePin,duty);
}
void L298_NODEMCU::L298_NODEMCU_RETROCEDER(int duty){
  L298_NODEMCU_DETENR();
  digitalWrite(in1Pin,LOW);
  digitalWrite(in2Pin,HIGH);
  analogWrite(enablePin,duty);
}
