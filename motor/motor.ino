/*INCLUDES HEADERS*/

/*DEFINES*/
//M1
#define IN11    6
#define IN21    7
//M2
#define IN32    5
#define IN42    4
//M3
#define IN12    2
#define IN22    3
//M4
#define IN31    8
#define IN41    9

/*GLOBAL VARIABLES*/

/*MAIN FUNCTION*/
/**
 * @fn 
 * @brief configuracion de los pines usados para el proyecto
 * @param []
 * @return none
 */
void PinoutsConfig(void);
/**
 * @fn 
 * @brief 
 * @param []
 * @return none
 */
void TurnLeft(void);
 /**
 * @fn 
 * @brief 
 * @param []
 * @return none
 */
void TurnRight(void);
 /**
 * @fn 
 * @brief 
 * @param []
 * @return none
 */
void Straight(void);
 /**
 * @fn 
 * @brief 
 * @param []
 * @return none
 */
void back(void);


void setup() {
  // put your setup code here, to run once:
  PinoutsConfig();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  Straight();
  delay(1000);
  TurnLeft();
  delay(500);
  back();
  delay(1000);
  TurnRight();
  delay(500);
}


/**
 * @fn 
 * @brief configuracion de los pines usados para el proyecto
 * @param []
 * @return none
 */
void PinoutsConfig(void){
  pinMode(IN11,OUTPUT);
  pinMode(IN21,OUTPUT);
  pinMode(IN31,OUTPUT);
  pinMode(IN41,OUTPUT);
  pinMode(IN12,OUTPUT);
  pinMode(IN22,OUTPUT);
  pinMode(IN32,OUTPUT);
  pinMode(IN12,OUTPUT);
  return;
}
 /**
 * @fn 
 * @brief 
 * @param []
 * @return none
 */
void TurnLeft(void){
  //M1
  digitalWrite(IN11,HIGH);
  digitalWrite(IN21,LOW);
  //M2
  digitalWrite(IN32,HIGH);
  digitalWrite(IN42,LOW);
  //M3
  digitalWrite(IN12,LOW);
  digitalWrite(IN22,HIGH);
  //M4
  digitalWrite(IN31,HIGH);
  digitalWrite(IN41,LOW);
  return;
}
 /**
 * @fn 
 * @brief 
 * @param []
 * @return none
 */
void TurnRight(void){
  //M1
  digitalWrite(IN11,LOW);
  digitalWrite(IN21,HIGH);
  //M2
  digitalWrite(IN32,LOW);
  digitalWrite(IN42,HIGH);
  //M3
  digitalWrite(IN12,HIGH);
  digitalWrite(IN22,LOW);
  //M4
  digitalWrite(IN31,LOW);
  digitalWrite(IN41,HIGH);
  return;
}
 /**
 * @fn 
 * @brief 
 * @param []
 * @return none
 */
void Straight(void){
  //M1
  digitalWrite(IN11,HIGH);
  digitalWrite(IN21,LOW);
  //M2
  digitalWrite(IN32,LOW);
  digitalWrite(IN42,HIGH);
  //M3
  digitalWrite(IN12,LOW);
  digitalWrite(IN22,HIGH);
  //M4
  digitalWrite(IN31,LOW);
  digitalWrite(IN41,HIGH);
  return;
}
 /**
 * @fn 
 * @brief 
 * @param []
 * @return none
 */
void back(void){
  //M1
  digitalWrite(IN11,LOW);
  digitalWrite(IN21,HIGH);
  //M2
  digitalWrite(IN32,HIGH);
  digitalWrite(IN42,LOW);
  //M3
  digitalWrite(IN12,HIGH);
  digitalWrite(IN22,LOW);
  //M4
  digitalWrite(IN31,HIGH);
  digitalWrite(IN41,LOW);
  return;
}
