         
//#include <ESP8266WiFi.h>
//#include <IRremoteESP8266.h>
#include <Arduino.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
int a=100;
int tiempo=100;
const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
const uint16_t kRecvPin = 5;
unsigned long key_value = 0;
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
IRrecv irrecv(kRecvPin);
decode_results results;
String data = "";
//Definimos Funciones
void checkPhysicalButton();void ir_remote();void youtube();void tv();void Netflix();void Suspender();void Apagar();void Deportes();
void Cerrar();void Inicio();void Entrar();void Silencio();void prendido();void ledon();void ledoff();void arriba();void abajo();
void derecha();void izquierda();void atras();void entrar();void adelanto();void tv();void enter();void inicio();
int relay1State = LOW;//carga independiente
int relay2State = HIGH;// TV
int relay3State = HIGH;// Tv box
int pushButton1State = HIGH;
int pushButton2State = HIGH;
int pushButton3State = HIGH;

#define RELAY_PIN_1      14 //D1 Azul
#define RELAY_PIN_2      12   //D2 Rojo
#define RELAY_PIN_3      16  //D0 Verde
#define Indicador     13  //D0 Verde

# define alerta      15    // D8 
# define pulsador2       2  //D5
# define  pulsador3      2    // D7..13

void setup()
{
  irsend.begin();
  Serial.begin(115200);
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);
  pinMode(Indicador, OUTPUT);
  pinMode(alerta, OUTPUT);
  pinMode(pulsador2, INPUT_PULLUP);
  pinMode(pulsador3, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_1, relay1State);
  digitalWrite(RELAY_PIN_2, relay2State);
  digitalWrite(RELAY_PIN_3, relay3State);
  digitalWrite(Indicador,LOW);
  digitalWrite(alerta,HIGH);
  delay(500);
  digitalWrite(alerta,LOW);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
}

void loop()
{
  ir_remote();
  checkPhysicalButton();
  delay(100);
}

//Main o funcion principal
void ir_remote(){
  if (irrecv.decode(&results)) {
   serialPrintUint64(results.value, HEX);
   Serial.println("");
   digitalWrite(Indicador,HIGH);
   delay(300);
        //  digitalWrite(alerta,LOW);
   digitalWrite(Indicador,LOW);
        // Serial.println(results.value, HEX);   
  switch(results.value){
    case 0x807F728D: //número 1
    ledon(); 
    relay1State = LOW;
    relay2State = LOW;
    relay3State = LOW;
    digitalWrite(RELAY_PIN_1, relay1State);
    digitalWrite(RELAY_PIN_2, relay2State);
    digitalWrite(RELAY_PIN_3, relay3State);
    Serial.println("Todo encendido"); 
    delay(15000);
    prendido();
    ledoff(); break;
    case 0x807F30CF: //número 3
      ledon();
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);
      Serial.println("Carga encendida"); 
      ledoff(); break;
    case 0x807F52AD: //número 4
      ledon();
      relay2State = !relay2State;
      if (relay2State == LOW) {digitalWrite(RELAY_PIN_2, relay2State);}
      else{Inicio();Apagar();delay(5000);digitalWrite(RELAY_PIN_2, relay2State);
      Serial.println("Tvbox"); }
      ledoff(); break;
    case 0x807F906F: //número 5
      ledon();
      relay3State = !relay3State;
      if (relay3State == LOW) {digitalWrite(RELAY_PIN_3, relay3State);delay(15000);prendido();}
      else{prendido();digitalWrite(RELAY_PIN_3, relay3State);delay(1000);prendido();}
      Serial.println("Tv"); 
      ledoff(); break;
    case 0x807FB04F: //número 2 
      ledon();   
      Inicio();
      Apagar();
      delay(5000);
      irsend.sendNEC(0xFDC03F,32); 
      delay(2000);
      relay2State = HIGH;
      relay3State = HIGH;
      digitalWrite(RELAY_PIN_1, relay1State);
      digitalWrite(RELAY_PIN_2, relay2State);
      digitalWrite(RELAY_PIN_3, relay3State);
      Serial.println("todo apagado"); 
      irsend.sendNEC(0xFDC03F,32);
      ledoff(); break;
      case 0x807F20DF: //número 9
      ledon();
      prendido();
      ledoff(); break;

          default : break;         
        }    
        irrecv.resume();
        }    
       delay(100);    
  } 


//Funciones secundarias
void youtube(){
  Serial.println("Youtube");irsend.sendNEC(0x807F8877,32);delay(a);
 irsend.sendNEC(0x807F6897,32);delay(a);
 irsend.sendNEC(0x807F6897,32);delay(a);
 irsend.sendNEC(0x807F6897,32);delay(a);
 irsend.sendNEC(0x807F8A75,32);delay(a);
 irsend.sendNEC(0x807F8A75,32);delay(a);
 irsend.sendNEC(0x807F8A75,32);delay(a);
 irsend.sendNEC(0x807F58A7,32);delay(a);
 irsend.sendNEC(0x807F0AF5,32);delay(a);
 irsend.sendNEC(0x807F0AF5,32);delay(a);
 irsend.sendNEC(0x807FC837,32);}
void tv(){
  Serial.println("Spliktv");inicio();arriba();arriba();arriba();izquierda();izquierda();izquierda();abajo();derecha();enter();
  }
  void Netflix(){
  Serial.println("Netflix");inicio();arriba();arriba();arriba();izquierda();enter();
  }
  void Suspender(){
     Serial.println("Suspender");irsend.sendNEC(0x807F02FD,32);delay(100);
    }
  void Apagar(){
     Serial.println("Apagar");
    irsend.sendNEC(0x807F02FD,32);//Apagar
    irsend.sendNEC(0x807F02FD,32);//Apagar
    irsend.sendNEC(0x807F02FD,32);//Apagar
    irsend.sendNEC(0x807F02FD,32);//Inicio
    irsend.sendNEC(0x807F02FD,32);//Inicio
    irsend.sendNEC(0x807F02FD,32);//Inicio
    irsend.sendNEC(0x807F02FD,32);//Inicio
    irsend.sendNEC(0x807F02FD,32);//Inicio
    irsend.sendNEC(0x807F02FD,32);//Inicio
    irsend.sendNEC(0x807F02FD,32);//Inicio
    irsend.sendNEC(0x807F02FD,32);//Inicio
    irsend.sendNEC(0x807F02FD,32);//Inicio
    delay(2000);
    irsend.sendNEC(0x807FC837,32);//Enter
   delay(100);
    }

  void Cerrar(){
    Serial.println("Cerrar");atras();atras();atras();atras();atras();atras();delay(2000);enter();}
  void Inicio(){ inicio(); } 
  void Entrar(){ 
    Serial.println("Entrar"); enter(); }
  void Silencio(){
    irsend.sendNEC(0xFDA857,32); } 
  void prendido(){
    Serial.println("prender tv");irsend.sendNEC(0xFDC03F,32);} 
  void prender(){
    Serial.println("prender tv");irsend.sendNEC(0xFDC03F,32);}
  void adelanto(){
    Serial.println("Adelanto");arriba();derecha();derecha();
   for (int i = 0; i <= 33; i++) {enter();}} 
  void ledon(){
    for (int j = 0; j <= 2; j++) {
    digitalWrite(Indicador,HIGH);digitalWrite(alerta,HIGH);delay(200);
    digitalWrite(Indicador,LOW);digitalWrite(alerta,LOW);delay(100);}
    digitalWrite(Indicador,HIGH);digitalWrite(alerta,LOW);delay(100);}
  void ledoff(){
    digitalWrite(alerta,HIGH);delay(300);digitalWrite(alerta,LOW);digitalWrite(Indicador,LOW);}
    
  void arriba(){
    irsend.sendNEC(0x807F6897,32);delay(a);} 
  void abajo(){
    irsend.sendNEC(0x807F58A7,32);delay(a);} 
  void derecha(){
      irsend.sendNEC(0x807F0AF5,32);delay(a);} 
  void izquierda(){
     irsend.sendNEC(0x807F8A75,32);delay(a);} 
  void enter(){
     irsend.sendNEC(0x807FC837,32);delay(a);}  
  void atras(){
     irsend.sendNEC(0x807F9867,32);delay(a);
    }
  void inicio(){
     irsend.sendNEC(0x807F8877,32);delay(a); }
  void espera(){ delay(tiempo);}


//Checar estado del pulsador
void checkPhysicalButton()
{
if (digitalRead(pulsador2) == LOW) {
  while (digitalRead(pulsador2) == LOW){
    digitalRead(pulsador2);
    delay(100);
    }
  if (relay2State == HIGH){
    relay2State = LOW;
    relay3State = LOW;
    ledon(); 
    relay2State = LOW;
    relay3State = LOW;
    digitalWrite(RELAY_PIN_1, relay1State);
    digitalWrite(RELAY_PIN_2, relay2State);
    digitalWrite(RELAY_PIN_3, relay3State);
    Serial.println("Todo encendido"); 
    delay(15000);
    prendido();
    ledoff();}
  else {
    ledon();   
      Inicio();
      Apagar();
      delay(5000);
      irsend.sendNEC(0xFDC03F,32); 
      delay(2000);
      relay2State = HIGH;
      relay3State = HIGH;
      digitalWrite(RELAY_PIN_1, relay1State);
      digitalWrite(RELAY_PIN_2, relay2State);
      digitalWrite(RELAY_PIN_3, relay3State);
      Serial.println("todo apagado"); 
      irsend.sendNEC(0xFDC03F,32);
      ledoff();
  }
}}
