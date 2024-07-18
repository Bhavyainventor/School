#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
String boy_captain1_name = "Candidate 1";
String boy_captain2_name = "Candidate 2";
String boy_captain3_name = "Candidate 3" ;

String girl_captain1_name = "Candidate 1";
String girl_captain2_name = "Candidate 2";
String girl_captain3_name = "Candidate 3";

String boy_vicecaptain1_name = "Candidate 1";
String boy_vicecaptain2_name = "Candidate 2";
String boy_vicecaptain3_name = "Candidate 3";

String girl_vicecaptain1_name = "Candidate 1";
String girl_vicecaptain2_name = "Candidate 2";
String girl_vicecaptain3_name = "Candidate 3";
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int Bc_can1 = 0; // Variables to store votes casted for Boy Captain
int Bc_can2 = 0;
int Bc_can3 = 0;
// ....................................................................................................
int Gc_can1 = 0; // Variables to store votes casted for Girl Captain
int Gc_can2 = 0;
int Gc_can3 = 0;
// ....................................................................................................
int Bvc_can1 = 0; // Variables to store Votes casted for Boy Vice captain
int Bvc_can2 = 0;
int Bvc_can3 = 0;
// ....................................................................................................
int Gvc_can1 = 0; // Variables to store Votes casted for Girl Vice Captain 
int Gvc_can2 = 0;
int Gvc_can3 = 0;
// ....................................................................................................
int button_1=4; // Variables for programming the voting buttons 
int button_2=3;
int button_3=2;
// ....................................................................................................
int J_controller = 6; // Switch for Junior 
int S_controller = 7; // Switch for Senior 
// ....................................................................................................
int buzzer = 8; // Buzzer for the evm
// ....................................................................................................
int redledevm = 9; // leds for the evm 
int greenledevm = 10;
// ....................................................................................................
int redledcontroller = 11; // leds for the controller
int greenledcontroller = 12;
// ....................................................................................................
bool boyCaptainVoteCast = false; // flag to track if a vote has been cast for Boy Captain
bool girlCaptainVoteCast = false; // flag to track if a vote has been cast for Girl Captain
bool boyViceCaptainVoteCast = false; // flag to track if a vote has been cast for Boy Vice Captain
bool girlViceCaptainVoteCast = false; // flag to track if the vote has been cast for Girl Vice Captain 
//.....................................................................................................
int temp_Bc_can1 = 0; // Temporary vote counters for the current voter
int temp_Bc_can2 = 0;// Temporary vote counters for the current voter
int temp_Bc_can3 = 0;// Temporary vote counters for the current voter
int temp_Gc_can1 = 0;// Temporary vote counters for the current voter
int temp_Gc_can2 = 0;// Temporary vote counters for the current voter
int temp_Gc_can3 = 0;// Temporary vote counters for the current voter
int temp_Bvc_can1 = 0;// Temporary vote counters for the current voter
int temp_Bvc_can2 = 0;// Temporary vote counters for the current voter
int temp_Bvc_can3 = 0;// Temporary vote counters for the current voter
int temp_Gvc_can1 = 0;// Temporary vote counters for the current voter
int temp_Gvc_can2 = 0;// Temporary vote counters for the current voter
int temp_Gvc_can3 = 0;// Temporary vote counters for the current voter
//.....................................................................................................
LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal_I2C lcd1(0x26, 16, 2);

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(button_1, INPUT_PULLUP); // Setting the digital pins to input mode. 
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);
  pinMode(J_controller, INPUT_PULLUP);
  pinMode(S_controller, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(redledevm, OUTPUT);
  pinMode(greenledevm, OUTPUT);
  pinMode(redledcontroller, OUTPUT);
  pinMode(greenledcontroller, OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd1.begin();
  lcd1.backlight();
}

void post1(){
  lcd.clear();
  lcd1.clear();
  int Bc1_button = digitalRead(button_1); // Reading the voting buttons and storing answer to BoysCaptain1 variable  
  int Bc2_button = digitalRead(button_2);
  int Bc3_button = digitalRead(button_3);

  if (Bc1_button == HIGH && Bc2_button == HIGH && Bc3_button == HIGH) {
    lcd.setCursor(0, 0);
    lcd.print("BOY CAPTAIN");
    lcd.setCursor(0, 1);
    lcd.print(boy_captain1_name);
    lcd1.setCursor(0, 0);
    lcd1.print(boy_captain2_name);
    lcd1.setCursor(0, 1);
    lcd1.print(boy_captain3_name);
    delay(1000);
  }

  if (Bc1_button == LOW) {
    Bc_can1++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: " + boy_captain1_name);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    lcd.clear();
    boyCaptainVoteCast = true;  
  }

  if (Bc2_button == LOW) {
    Bc_can2++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: " + boy_captain2_name);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    lcd.clear();
    boyCaptainVoteCast = true;
  }
  
  if (Bc3_button == LOW) {
    Bc_can3++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: " + boy_captain3_name);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    lcd.clear();
    boyCaptainVoteCast = true;
  }
}

void post2(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GIRL CAPTAIN");
  lcd.setCursor(0, 1);
  lcd.print(girl_captain1_name);
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print(girl_captain2_name);
  lcd1.setCursor(0, 1);
  lcd1.print(girl_captain3_name);
  delay(1000);
  int Gc1_button = digitalRead(button_1);
  int Gc2_button = digitalRead(button_2);
  int Gc3_button = digitalRead(button_3);
  
  if (Gc1_button == LOW) {
    Gc_can1++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: " + girl_captain1_name);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    lcd.clear();
    girlCaptainVoteCast = true;     
  }

  if (Gc2_button == LOW) {
    Gc_can2++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: " + girl_captain2_name);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    lcd.clear();
    girlCaptainVoteCast = true;  
  }

  if (Gc3_button == LOW) {
    Gc_can3++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: " + girl_captain3_name);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    girlCaptainVoteCast = true;  
  }
}

void post3(){
  lcd.clear();
  lcd1.clear();
  lcd.setCursor(0, 0);
  lcd.print("BOY VICE CAPTAIN");
  lcd.setCursor(0, 1);
  lcd.print(boy_vicecaptain1_name);
  lcd1.setCursor(0, 0);
  lcd1.print(boy_vicecaptain2_name);
  lcd1.setCursor(0, 1);
  lcd1.print(boy_vicecaptain3_name);
  delay(1000);
  int Bvc1_button = digitalRead(button_1);
  int Bvc2_button = digitalRead(button_2);
  int Bvc3_button = digitalRead(button_3);
  
  if (Bvc1_button == LOW) {
    Bvc_can1++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: " + boy_vicecaptain1_name);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    boyViceCaptainVoteCast = true;  
  }

  if (Bvc2_button == LOW) {
    Bvc_can2++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: " + boy_vicecaptain2_name);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    lcd.clear();
    boyViceCaptainVoteCast = true;      
  }

  if (Bvc3_button == LOW) {
    Bvc_can3++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: " + boy_vicecaptain3_name);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    lcd.clear();
    boyViceCaptainVoteCast = true;     
  }
}

void post4(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GIRL VICE CAPTAIN");
  lcd.setCursor(0, 1);
  lcd.print(girl_vicecaptain1_name);
  lcd1.setCursor(0, 0);
  lcd1.print(girl_vicecaptain2_name);
  lcd1.setCursor(0, 1);
  lcd1.print(girl_vicecaptain3_name);
  delay(1000);
  int Gvc1_button = digitalRead(button_1);
  int Gvc2_button = digitalRead(button_2);
  int Gvc3_button = digitalRead(button_3);
  
  if (Gvc1_button == LOW) {
    Gvc_can1++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: " + girl_vicecaptain1_name );
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    girlViceCaptainVoteCast = true;
  }
  if (Gvc2_button == LOW) {
    Gvc_can2++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: " + girl_vicecaptain2_name);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    girlViceCaptainVoteCast = true;
  }
  if (Gvc3_button == LOW) {
    Gvc_can3++;
    lcd.clear();
    lcd1.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Vote Recorded");
    lcd.setCursor(0, 1);
    lcd.print("FOR: "+ girl_vicecaptain3_name);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenledevm ,HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(buzzer, LOW);
    digitalWrite(greenledevm ,LOW);
    girlViceCaptainVoteCast = true;
  }
}


void printit(){
  Serial.println(Bc_can1);
  Serial.println(Bc_can2);
  Serial.println(Bc_can3);
  Serial.println(Gc_can1);
  Serial.println(Gc_can2);
  Serial.println(Gc_can3);
  Serial.println(Bvc_can1);
  Serial.println(Bvc_can2);
  Serial.println(Bvc_can3);
  Serial.println(Gvc_can1);
  Serial.println(Gvc_can2);
  Serial.println(Gvc_can3);
  
}

void resetVotesbool() {
  boyCaptainVoteCast = false;
  girlCaptainVoteCast = false;
  boyViceCaptainVoteCast = false;
  girlViceCaptainVoteCast = false;
}

void loop() {
  
  lcd.clear();
  lcd1.clear();
  static bool junior_pressed = false;
  static bool senior_pressed = false;

  static bool is_idle = true;
  static bool is_junior_voting = false;
  static bool is_senior_voting = false;

  int junior_status = digitalRead(J_controller);
  int senior_status = digitalRead(S_controller);

  if (is_idle) {
    lcd.setCursor(0, 0);
    lcd.print("  PLEASE WAIT");
    lcd.setCursor(0, 1);
    lcd.print(":) ---------- :)");
    digitalWrite(greenledcontroller , HIGH);
    digitalWrite(redledcontroller , LOW);
    digitalWrite(redledevm , HIGH);
    //..............................................................
    if (junior_status == LOW && !junior_pressed) {
      junior_pressed = true;
      is_idle = false;
      is_junior_voting = true;
    } else if (junior_status == HIGH && junior_pressed) {
      junior_pressed = false;
    }

    if (senior_status == LOW && !senior_pressed) {
      senior_pressed = true;
      is_idle = false;
      is_senior_voting = true;
    } else if (senior_status == HIGH && senior_pressed) {
      senior_pressed = false;
    }
  }
  else{
    digitalWrite(redledcontroller , HIGH);
    digitalWrite(greenledcontroller , LOW);
    digitalWrite(redledevm , LOW);
  }

  if (is_junior_voting == true && is_senior_voting == false) {
    if (!boyViceCaptainVoteCast) {
      post3();
    } else if (!girlViceCaptainVoteCast) {
      post4();
    } else if (boyViceCaptainVoteCast && girlViceCaptainVoteCast){
      printit();
      is_junior_voting = false;
      is_idle = true;
      resetVotesbool();
    }
  }

  if (is_senior_voting == true && is_junior_voting == false) {
    if (!boyCaptainVoteCast) {
      post1();
    } else if (boyCaptainVoteCast && !girlCaptainVoteCast) {
      post2();
    } else if (boyCaptainVoteCast && girlCaptainVoteCast && !boyViceCaptainVoteCast) {
      post3();
    } else if (boyCaptainVoteCast && girlCaptainVoteCast && boyViceCaptainVoteCast && !girlViceCaptainVoteCast) {
      post4();
    } else if(boyCaptainVoteCast && girlCaptainVoteCast && boyViceCaptainVoteCast && girlViceCaptainVoteCast) {
      printit();
      is_senior_voting = false;
      is_idle = true;
      resetVotesbool();
    }
  }
}