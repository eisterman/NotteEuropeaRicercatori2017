#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
}

bool DataOut[10];

void readSensor()
{
  lsm.read();
  // ACCEL X Y Z MAG X Y Z GYRO X Y Z TEMP
  if (DataOut[0]) Serial.print((int)lsm.accelData.x); Serial.print(",");
  if (DataOut[1]) Serial.print((int)lsm.accelData.y); Serial.print(",");
  if (DataOut[2]) Serial.print((int)lsm.accelData.z); Serial.print(",");
  if (DataOut[3]) Serial.print((int)lsm.magData.x); Serial.print(",");
  if (DataOut[4]) Serial.print((int)lsm.magData.y); Serial.print(",");
  if (DataOut[5]) Serial.print((int)lsm.magData.z); Serial.print(",");
  if (DataOut[6]) Serial.print((int)lsm.gyroData.x); Serial.print(",");
  if (DataOut[7]) Serial.print((int)lsm.gyroData.y); Serial.print(",");
  if (DataOut[8]) Serial.print((int)lsm.gyroData.z); Serial.print(",");
  if (DataOut[9]) Serial.print((int)lsm.temperature); Serial.print(",");
}

void setup() {
  for (int i = 0; i < 10; i++)
    DataOut[i] = true;
#ifndef ESP8266
  while (!Serial);     // attesa nel caso si utilizzi una scheda Arduino il cui Seriale non è immediatamente disponibile
#endif
  Serial.begin(9600);
  // Serial.println("");
  // Inizializza la scheda sensore e avvisa se non riesce a trovarla o a inizializzarla
  if (!lsm.begin())
  {
    Serial.println("404"); // Scheda non inizializzata
    while (1);
  }
  Serial.println("201"); // Pronti al lavoro
}

void loop() {
  while (true) {
    readSensor();
        Serial.print("\n");
        delay(100);
  }
  int opcode = Serial.readString().toInt();
  switch(opcode) {
    case 100: // Output dati
      Serial.println("200"); //OK!
      readSensor();
      Serial.println("\n100"); // Continua!
      break;
    case 300: // Modifica Impostazioni <non implementato>
      break;
    case 666:
      while(1) {
        readSensor();
        Serial.print("\n");
        delay(100);
      }
    default:
      Serial.println("400"); //Bad Request
  }
  //readSensor();
  //delay(100);
}
