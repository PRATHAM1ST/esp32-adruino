#include <Notecard.h>
#include <NotecardPseudoSensor.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define usbSerial Serial
#define txRxPinsSerial Serial1

#define NOTE_PRODUCT_UID "com.gmail.the.listner01:chatjpk"

using namespace blues;


Notecard notecard; 
NotecardPseudoSensor sensor(notecard);
Adafruit_MPU6050 mpu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);


  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

   mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");     
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  // txRxPinsSerial.begin(9600);
  // txRxPinsSerial.println("\n");
  // delay(250);

  // notecard.begin();
  notecard.begin(txRxPinsSerial, 9600); 
  // notecard.begin(txRxPinsSerial); 

  txRxPinsSerial.begin(9600);
  txRxPinsSerial.println("\n");
  delay(250);

  txRxPinsSerial.println("{\"req\":\"hub.set\",\"product\":\"" NOTE_PRODUCT_UID "\",\"mode\":\"continuous\"}");

  delay(250); // wait for the Notecard to respond
  while (txRxPinsSerial.available() > 0) {
      char incomingByte = txRxPinsSerial.read();
      if (incomingByte != '\r' && incomingByte != '\n') {
        usbSerial.print(incomingByte);
      }
  }

  usbSerial.println(); 

  char json_request[150];
  snprintf(json_request, sizeof(json_request), "{\"req\":\"note.add\",\"file\":\"twilio.qo\",\"sync\":true,\"body\":{\"twilioBody\":\"This msg is sent from esp32 using twilio.\"}}");

  txRxPinsSerial.println(json_request);
  delay(250); // wait for the Notecard to respond
  while (txRxPinsSerial.available() > 0) {
      char incomingByte = txRxPinsSerial.read();
      if (incomingByte != '\r' && incomingByte != '\n') {
          usbSerial.print(incomingByte);
      }
  }
  usbSerial.println();


}

void loop() {

  // put your main code here, to run repeatedly:
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float temperature = sensor.temp();
  float humidity = sensor.humidity();


  char json_request[150];
snprintf(json_request, sizeof(json_request),
    "{"
      "\"req\":\"note.add\","
      "\"file\":\"sensors.qo\","
      "\"sync\":true,"
      "\"body\":{"
        "\"temp\":%d.%02d,"
        "\"humidity\":%d.%02d"
      "}"
    "}",
    (int)temperature, abs(((int)(temperature*100.0)%100)),
    (int)humidity, (int)(humidity*100.0)%100
);

  txRxPinsSerial.println(json_request);

  while (txRxPinsSerial.available() > 0) {
      char incomingByte = txRxPinsSerial.read();
      if (incomingByte != '\r' && incomingByte != '\n') {
          usbSerial.print(incomingByte);
      }
  }
  usbSerial.println();  

  delay(5000);
}
