#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define SEC_TO_MILISEC(x) ((x)*1000) 

#define IN1 D3
#define IN2 D4
#define ENA D2

#define IN3 D8
#define IN4 D5
#define ENB D1

#define DEBUGG



//*******PINES





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




char * ssid ="IOT 2020";
char * pass ="itba2020";
unsigned int mqttPort=1883;

const char MqttUser[]="auto1";
const char MqttPassword[]="1234";
const char MqttClientID[]="a1";

IPAddress mqttServer(192,168,2,105);

WiFiClient wclient;
PubSubClient mqtt_client(wclient);

L298_NODEMCU motorI(ENA,IN1,IN2);
L298_NODEMCU motorD(ENB,IN3,IN4);


void callback(char* topic, byte* payload, unsigned int length);
void  debug_message (char * string, bool newLine)
{
#ifdef DEBUGG
  if(string !=NULL)
  {
    if (!newLine)
    {
      Serial.print(string);
    }else
    {
      Serial.println(string);
    }
  }
  #endif
}

void setUpWifi(char * ssid, char * pass)
{
  String ip;
  debug_message(" ",true);
  debug_message(" ",true);
  debug_message("Conectandose a: ",false);
  debug_message(ssid,true);

  WiFi.begin(ssid,pass);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    debug_message(".",false);
  }
  debug_message(" ",true);
  debug_message("Coneccion realizada",true);
  debug_message("La ip es: ",false);
  ip=WiFi.localIP().toString();
  debug_message((char *)ip.c_str(),true);
}

void setUpMqtt(void)
{
  mqtt_client.setServer(mqttServer,mqttPort);
  mqtt_client.setCallback(callback);
}


void callback(char* topic, byte* payload, unsigned int length)
{
  int tiempo=0;
  payload[length]='\n';
  String message((char *)payload);
  debug_message("Llego un mensage, topic:",false);
  debug_message(topic,false);
  //debug_message(", de longitud : ",false);
  //debug_message((char *) char(length),true);
  debug_message(", payload : ",false);
  debug_message((char *)payload,true);

  if(!strcmp(topic,"auto/mI/detener"))
  { 
    motorI.L298_NODEMCU_DETENR();
    //Serial.println(atoi((char *)payload));
       debug_message("el if auto/mI/detener",true);
 
  }else if(!strcmp(topic,"auto/mI/avanzar"))
  {
    debug_message("el if auto/mI/avanzar",true);
     motorI.L298_NODEMCU_AVANZAR(atoi((char *)payload));
 
  }else if(!strcmp(topic,"auto/mI/retroceder"))
  {
    motorI.L298_NODEMCU_RETROCEDER(atoi((char *)payload));
    debug_message("el if auto/mI/retroceder",true);
 
  }else if(!strcmp(topic,"auto/mD/detener"))
  { 
    motorD.L298_NODEMCU_DETENR();
    //Serial.println(atoi((char *)payload));
       debug_message("el if auto/mD/detener",true);
 
  }else if(!strcmp(topic,"auto/mD/avanzar"))
  {
    debug_message("el if auto/mD/avanzar",true);
     motorD.L298_NODEMCU_AVANZAR(atoi((char *)payload));
 
  }else if(!strcmp(topic,"auto/mD/retroceder"))
  {
    motorD.L298_NODEMCU_RETROCEDER(atoi((char *)payload));
    debug_message("el if auto/mD/retroceder",true);
 
  }
 
}


void setup() {

  setUpWifi(ssid,pass);
  setUpMqtt();

  
  // Initialize Serial port
  Serial.begin(9600);
 
}

void reconnect()
{
  while(!mqtt_client.connected())
  {
    debug_message("Intentando conectar al servidor MQTT",true);
    if (mqtt_client.connect(MqttClientID,MqttUser,MqttPassword))
      {
            debug_message("conectado",true);
  
  
            // ...suscrivirse a topicos
           mqtt_client.subscribe("auto/mI/detener");
           mqtt_client.subscribe("auto/mI/avanzar");
           mqtt_client.subscribe("auto/mI/retroceder");
           mqtt_client.subscribe("auto/mD/detener");
           mqtt_client.subscribe("auto/mD/avanzar");
           mqtt_client.subscribe("auto/mD/retroceder");
           //mqtt_client.subscribe("bed/ch1/off");
           // mqtt_client.subscribe("bed/ch2/on");
           //mqtt_client.subscribe("bed/ch2/off");
           // mqtt_client.subscribe("timbre/off");
            


      }
      else
      {
        debug_message("intentando conetarse al broker",true);
        delay(3000);
      }
  }
}

void loop() {

  if (!mqtt_client.connected()) 
  {
      reconnect();
 }
 mqtt_client.loop(); 
  
  
 // delay(100);
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
