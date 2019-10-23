/*
  Created by TEOS
  Domotic with Arduino https://goo.gl/btZpjs
  YouTube https://goo.gl/k7TUSZ
  Instagram https://goo.gl/zEIjia
  Facebook https://goo.gl/eivraR
  Twitter https://goo.gl/du5Wgn
  Github https://goo.gl/Xl5IiS
  Google Plus https://goo.gl/gBnUdh
  WEB https://www.proyecto-teos.com/
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h> //https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
#include <SD.h> //https://github.com/arduino-libraries/SD
#include "RTClib.h" //https://github.com/adafruit/RTClib/
#include <MFRC522.h> //https://github.com/miguelbalboa/rfid
#include <SPI.h>

//fileName is the name of the file that saves the data
//savedDataT saves the tag and date information, tagAuthorizedT saves an access string
String fileNameT = "datalogT.txt", savedDataT, dateT, timeT, tagAuthorizedT;

//Tag ID
const char myTagIDT[4] = {0xCA, 0x04, 0x1F, 0xCE};

//Allows access to an identified tag
bool authorizaedT;

//Pin definition
const uint8_t ledPinGreenT = 7, ledPinRedT = 6, speakerPinT = 5;
uint8_t selectedLedT;
const uint16_t intervalT = 1000;
unsigned long previousMillisT;

//Instances are created
File dataFileT;
MFRC522 mrfInstanceT(10, 9);
RTC_DS3231 RTCInstanceT;
LiquidCrystal_I2C lcdT(0x27, 20, 4);

void setup() {
  Serial.begin(9600);
  lcdT.begin();
  lcdT.backlight();

  //Pin configuration
  pinMode(ledPinGreenT, OUTPUT);
  pinMode(ledPinRedT, OUTPUT);
  pinMode(speakerPinT, OUTPUT);

  SPI.begin();
  mrfInstanceT.PCD_Init();
  delay(1000);

  //An SD module check is performed
  lcdT.setCursor(0, 0);
  lcdT.print("Iniciando modulo");
  lcdT.setCursor(0, 1);
  lcdT.print("SD...");
  if (!SD.begin(8)) {
    lcdT.setCursor(0, 0);
    lcdT.print("Imposible iniciar,");
    lcdT.setCursor(0, 1);
    lcdT.print("error: Modulo SD.");
    while (1);
  } else {
    lcdT.setCursor(0, 2);
    if (!SD.exists(fileNameT)) {
      lcdT.print("No existe el archivo");
      lcdT.setCursor(0, 3);
      lcdT.print("imposible iniciar.");
      while (1);
    } else
      lcdT.print("archivo encontrado.");
    lcdT.setCursor(6, 1);
    lcdT.print("OK");
  }
  delay(2500);

  //The cleanT() function is called to "clean" the lcd
  lcdT.setCursor(0, 2);
  lcdT.print(cleanT());
  lcdT.setCursor(0, 3);
  lcdT.print(cleanT());

  //A RTC module check is performed
  lcdT.setCursor(0, 1);
  lcdT.print("RTC...   ");
  if (!RTCInstanceT.begin()) {
    lcdT.setCursor(0, 0);
    lcdT.print("Imposible inicar,");
    lcdT.setCursor(0, 1);
    lcdT.print("error: Modulo RTC.");
    while (1);
  } else {
    //Return a date and time setting to the instance
    RTCInstanceT.adjust(DateTime(F(__DATE__), F(__TIME__)));
    lcdT.setCursor(7, 1);
    lcdT.print("OK");
  }

  delay(2500);

  //If the modules were loaded correctly, the program starts
  lcdT.clear();
  lcdT.setCursor(2, 0);
  lcdT.print("Modulos cargados");
  lcdT.setCursor(3, 1);
  lcdT.print("correctamente");
  lcdT.setCursor(2, 2);
  lcdT.print("powered by TEOS");
  delay(3000);

  lcdT.clear();
  lcdT.setCursor(3, 0);
  lcdT.print("Coloque el TAG");

  previousMillisT = millis();
}

void loop() {
  unsigned long currentMillisT = millis();
  if ((unsigned long)(currentMillisT - previousMillisT) >= intervalT) {
    //The DateTime function is invoked
    DateTime now = RTCInstanceT.now();
    getDateT(now);

    //If a card has been detected and if that card is valid, the getAccessT
    //function is performed
    if (mrfInstanceT.PICC_IsNewCardPresent()) {
      if (mrfInstanceT.PICC_ReadCardSerial())
        getAccessT();
    }

    previousMillisT = millis();
  }
}

//Function that allows to obtain the current date and time
void getDateT(DateTime date) {
  timeT = String(date.hour(), DEC) + ":" + String(date.minute(), DEC) + ":" + String(date.second(), DEC);
  dateT = String(date.day(), DEC) + "/" + String(date.month(), DEC) + "/" + String(date.year(), DEC);
  //The value that is in dateT returns a string with values of various sizes, so the
  //lcd is cleaned so there are no unwanted digits
  lcdT.setCursor(0, 3);
  lcdT.print(cleanT());
  //Data corresponding to the date and time are printed on the LCD
  lcdT.setCursor(0, 3);
  lcdT.print(timeT);
  lcdT.setCursor(10, 3);
  lcdT.print(dateT);
}

//Function that verifies if the card reading corresponds to an authorized access.
void getAccessT() {
  tagAuthorizedT = "";
  // If the card ID presented matches the saved ID, the value will be true,
  //otherwise it will be false
  authorizaedT = (comparisonTagT(mrfInstanceT.uid.uidByte, myTagIDT, 4)) ? true : false;
  tagAuthorizedT =  (authorizaedT) ? "Acceso autorizado" : "Acceso denegado  ";
  lcdT.setCursor(1, 1);
  lcdT.print(tagAuthorizedT);
  printDataFileT();
  mrfInstanceT.PICC_HaltA();
}

//Variable that returns the status of having compared an existing ID with an ID of a
//card placed in the module
bool comparisonTagT(uint8_t* incomingTagT, uint8_t* currentTagT, uint8_t length) {
  for (uint8_t indexT = 0; indexT < length; indexT++) {
    if (incomingTagT[indexT] != currentTagT[indexT])
      return false;
  }
  return true;
}

//The following function is responsible for printing all data in the dataFileT file
void printDataFileT() {
  dataFileT = SD.open(fileNameT, FILE_WRITE);
  lcdT.setCursor(1, 2);
  //If the file exists and can be read, the record is saved, otherwise an error is sent
  if (dataFileT) {
    getDataT();
    dataFileT.println(savedDataT);
    Serial.println(savedDataT);
    dataFileT.close();
    if (authorizaedT)
      lcdT.print("Registro guardado ");
  }
  else
    lcdT.print("Error en el archivo");

  selectedLedT = (authorizaedT) ? ledPinGreenT : ledPinRedT;
  digitalWrite(selectedLedT, HIGH);
  //Write a pwm signal with a value of 4
  analogWrite(speakerPinT, 4);
  delay(2000);
  lcdT.clear();
  lcdT.setCursor(3, 0);
  lcdT.print("Coloque el TAG");
  digitalWrite(selectedLedT, LOW);
  analogWrite(speakerPinT, 0);
}

//Function that builds a string with all values
void getDataT() {
  savedDataT = timeT + " " + dateT + "; ";
  for (uint8_t iT = 0; iT < 4; iT++) {
    //Card ID is obtained
    savedDataT += "0x" + String(mrfInstanceT.uid.uidByte[iT], HEX);
    savedDataT += (iT < 3 ) ? "," : "";
  }
  //Save any record, even if the ID is not authorized.
  savedDataT += (authorizaedT) ? "; Autorizado" : "; Denegado";
}

//Returns a string with a value of 20 spaces
String cleanT() {
  const String cleanLineT = "                    ";
  return cleanLineT;
}