//Modul Praktikum 3 - Sistem Kendali PID
//Nama Tim :Bintang Jaya 
//Nama Anggota 1 : Faidh Faziellah
//Nama anggota 2 : M.Ridzky Farhan
//Versi Program : 1.0

//pin buat sensor analog
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;
int baca_sensor[6];

//pin buat enable
int pinEnable =4;
int pinEnable2 = 2;

//pin buat motor kiri
int motor_kiri1 = 5;
int motor_kiri2 = 6;

//pin buat motor kanan
int motor_kanan1 = 3;
int motor_kanan2 = 11;

//bantuan
int x;

//Error Code
int Last_Error = 0;
int error = 0;
int mtrSPDright, mtrSPDleft, setPointSPD = 255, PID_movement; 

void setup(){
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);
   
  pinMode(pinEnable, OUTPUT);
  pinMode(pinEnable2, OUTPUT);
  pinMode(motor_kiri1, OUTPUT);
  pinMode(motor_kiri2, OUTPUT);
  pinMode(motor_kanan1, OUTPUT);
  pinMode(motor_kanan2, OUTPUT);
  
  Serial.begin(9600);
}

void readsensor() { 
  baca_sensor[0] = analogRead(sensor1);
  baca_sensor[1] = analogRead(sensor2);
  baca_sensor[2] = analogRead(sensor3);
  baca_sensor[3] = analogRead(sensor4);
  baca_sensor[4] = analogRead(sensor5);
  baca_sensor[5] = analogRead(sensor6);
/*    
  for (x = 0; x <= 5; x++){
    Serial.println (baca_sensor[x]);
  }  
*/
}

void If_Error(){
//just sensor 1 thats on 
if (baca_sensor[0] < 34 && baca_sensor[1] > 34 && 
    baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
    baca_sensor[4] > 34 && baca_sensor[5] > 34){  

    Last_Error = -2;
    try_PID(Last_Error);
   }

//just Sensor 2 thats on
if (baca_sensor[0] > 34 && baca_sensor[1] < 34 && 
    baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
    baca_sensor[4] > 34 && baca_sensor[5] > 34){
  Last_Error = -1;
  try_PID(Last_Error);
   }

//just sensor 3 thats on 
if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
    baca_sensor[2] < 34 && baca_sensor[3] > 34 && 
    baca_sensor[4] > 34 && baca_sensor[5] > 34){

  Last_Error = 0;

  digitalWrite(pinEnable, HIGH);
  analogWrite(motor_kiri1, 255);
  analogWrite(motor_kiri2, 0);

  digitalWrite(pinEnable2, HIGH);
  analogWrite(motor_kanan1, 255);
  analogWrite(motor_kanan2, 0);
   }

//just sensor 4 thats on
if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
    baca_sensor[2] > 34 && baca_sensor[3] < 34 && 
    baca_sensor[4] > 34 && baca_sensor[5] > 34){
  
  Last_Error = 0;
  try_PID(Last_Error);
   }

//just sensor 5 thats on
if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
    baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
    baca_sensor[4] < 34 && baca_sensor[5] > 34){
  
  Last_Error = 1;
  try_PID(Last_Error);
   }  

//just sensor 6 thats on
if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
    baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
    baca_sensor[4] > 34 && baca_sensor[5] < 34){
  
  Last_Error = 2;
  try_PID(Last_Error);
   }  
}

void loop(){
    
  readsensor();
  //Sensor 1 dan 2 mendeteksi gelap, sisanya terang 
  if (baca_sensor[0] < 34 && baca_sensor[1] < 34 && 
      baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
      baca_sensor[4] > 34 && baca_sensor[5] > 34){

    Last_Error = -2;
    try_PID(Last_Error);
  }
  //Sensor 2 dan 3 mendeteksi gelap, sisanya terang 
  if (baca_sensor[0] > 34 && baca_sensor[1] < 34 && 
      baca_sensor[2] < 34 && baca_sensor[3] > 34 && 
      baca_sensor[4] > 34 && baca_sensor[5] > 34){

    Last_Error = -1;
    try_PID(Last_Error);
  }
  //Sensor 3 dan 4 mendeteksi gelap, sisanya terang 
  if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
      baca_sensor[2] < 34 && baca_sensor[3] < 34 && 
      baca_sensor[4] > 34 && baca_sensor[5] > 34){
    
    Last_Error = 0;

    digitalWrite(pinEnable, HIGH);
    analogWrite(motor_kiri1, 255);
    analogWrite(motor_kiri2, 0);

    digitalWrite(pinEnable2, HIGH);
    analogWrite(motor_kanan1, 255);
    analogWrite(motor_kanan2, 0);
  }
  //Sensor 4 dan 5 mendeteksi gelap, sisanya terang 
  if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
      baca_sensor[2] > 34 && baca_sensor[3] < 34 && 
      baca_sensor[4] < 34 && baca_sensor[5] > 34){
    
    Last_Error = 1;
    try_PID(Last_Error);
  }  
  //Sensor 5 dan 6 mendeteksi gelap, sisanya terang 
  if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
      baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
      baca_sensor[4] < 34 && baca_sensor[5] < 34){

    Last_Error = 2;
    try_PID(Last_Error);
  }  
  //Semua sensor mendeteksi terang 
  if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
      baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
      baca_sensor[4] > 34 && baca_sensor[5] > 34){

      digitalWrite(pinEnable, HIGH);
      analogWrite(motor_kiri1, 0);
      analogWrite(motor_kiri2, 0);

      digitalWrite(pinEnable2, HIGH);
      analogWrite(motor_kanan1, 0);
      analogWrite(motor_kanan2, 0);
  }
  If_Error();
}

void try_PID(int Last_Error){

//  Serial.print ("Error Sensor Detect : ");
//  Serial.println (Last_Error);
//  Serial.print ("\n");

  int kp = 30, ki = 0, kd = 0; // kp range = 1 - 5
  int rate = error - Last_Error; // 0 - (-2) = 2
  PID_movement = (kp*Last_Error) + (kd*rate) + (ki/rate);
  mtrSPDright = setPointSPD + PID_movement; // 255 - 60 = 195
  mtrSPDleft = setPointSPD - PID_movement; // 255 + 60 = 60


  Serial.print ("error : ");
  Serial.print (error);
  Serial.print ("\n");
  Serial.print ("rate : ");
  Serial.print (rate);
  Serial.print ("\n");
  Serial.print ("PID : ");
  Serial.print (PID_movement);
  Serial.print ("\n");
  Serial.print ("Motor Kanan : ");
  Serial.print (mtrSPDright);
  Serial.print ("\n");
  Serial.print ("Motor Kiri : ");
  Serial.print (mtrSPDleft);
  Serial.print ("\n");
  delay (1000);
  
  digitalWrite(pinEnable, HIGH);
  analogWrite(motor_kiri1, mtrSPDleft);
  analogWrite(motor_kiri2, 0);

  digitalWrite(pinEnable2, HIGH);
  analogWrite(motor_kanan1, mtrSPDright);
  analogWrite(motor_kanan2, 0);
}