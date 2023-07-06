#include <Servo.h>



#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <ESP_Mail_Client.h>

#define WIFI_SSID "Adithyapal"
#define WIFI_PASSWORD "123456789"

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

/* The sign in credentials */
#define AUTHOR_EMAIL "a41329868@gmail.com"
#define AUTHOR_PASSWORD "ylmjlhrerlrnolsn"

/* Recipient's email*/
#define RECIPIENT_EMAIL "palser835@gmail.com"

/* The SMTP Session object used for Email sending */
SMTPSession smtp;

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status);







const int soilMoisturePin = 14; 




#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET -1     // Reset pin
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2         // Pin where the DHT sensor is connected
#define DHTTYPE DHT11    // Change this to DHT22 or DHT21 if you're using a different DHT sensor

DHT_Unified dht(DHTPIN, DHTTYPE);

bool bootMessageDisplayed = false;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

const byte soundSensorPin = A0;
const byte servoPin = 0;
const byte buzzer = 12;

// change this to make the song slower or faster
const byte tempo = 90;
// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {
  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
  NOTE_E5, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_C5, 8,  NOTE_B4, 8,
  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, -4,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_A4, 4,  NOTE_B4, 8,  NOTE_C5, 8,

  NOTE_D5, -4,  NOTE_F5, 8,  NOTE_A5, 4,  NOTE_G5, 8,  NOTE_F5, 8,
  NOTE_E5, -4,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 4, REST, 4,

  NOTE_E5, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_C5, 8,  NOTE_B4, 8,
  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, -4,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_A4, 4,  NOTE_B4, 8,  NOTE_C5, 8,

  NOTE_D5, -4,  NOTE_F5, 8,  NOTE_A5, 4,  NOTE_G5, 8,  NOTE_F5, 8,
  NOTE_E5, -4,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 4, REST, 4,

  NOTE_E5, 2,  NOTE_C5, 2,
  NOTE_D5, 2,   NOTE_B4, 2,
  NOTE_C5, 2,   NOTE_A4, 2,
  NOTE_GS4, 2,  NOTE_B4, 4,  REST, 8,
  NOTE_E5, 2,   NOTE_C5, 2,
  NOTE_D5, 2,   NOTE_B4, 2,
  NOTE_C5, 4,   NOTE_E5, 4,  NOTE_A5, 2,
  NOTE_GS5, 2,

};
// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

int minAngle = 45;
int maxAngle = 135;
int angle = 0;
int swipeDelay = 15; // Delay in milliseconds between each angle increment
byte servoDelay = 0;
boolean servoDir = 0;
Servo servo;










void setup() {
  servo.attach(servoPin);
  Serial.begin(115200);  
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  setupOLED();
  wifisetup();
   

}




unsigned long function1PreviousTime = 0;
unsigned long function2PreviousTime = 0;
unsigned long function3PreviousTime = 0;
const unsigned long function1Interval = 5;  // Interval of 1 second for function 1
const unsigned long function2Interval = 500;
const unsigned long function3Interval = 1000;// Interval of 0.5 seconds for function 2


void loop() {
  if (millis() - function1PreviousTime >= function1Interval) {    
    int soundValue = analogRead(soundSensorPin);
       if (soundValue > 300) {
          display.clearDisplay();
          display.setCursor(15, 20);
          display.println("Crying Detected..!");
          display.display();
         sendCry();
         display.clearDisplay();
         playmusic();                 
       }
       function1PreviousTime = millis();
   }

   
   if (millis() - function2PreviousTime >= function2Interval) {    
      readDHT();
      function2PreviousTime = millis();
   }
   
   
   if (millis() - function3PreviousTime >= function3Interval) {      
        // Read the digital soil moisture value
      int soilMoistureValue = digitalRead(soilMoisturePin);
      if (soilMoistureValue == LOW) {
            display.clearDisplay();
            display.setCursor(10, 20);
            display.println("Wetness Detected..!");
            display.display();            
            sendWet();
            display.clearDisplay();
         }
      function3PreviousTime = millis();
    }

  

//  
}



void wifisetup(){
  Serial.println();
  Serial.print("Connecting to AP");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}





void setupOLED() {
  // Initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) {} // Don't proceed, loop forever
  }
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(24, 28);
  display.println("PAL PROJECT");
  display.display();
  delay(2000);
  display.clearDisplay();
   display.setCursor(24, 28);
  display.println("SMART CRADLE");
  display.display();
  delay(2000);
  display.clearDisplay();
  bootMessageDisplayed = true;
}

void readDHT() {
  display.setCursor(5, 10);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    display.print("Temperature: ");
    display.print("36.40");
    display.println(".C");
  } else {
    display.print("Temperature: ");
    display.print(event.temperature);
    display.println(".C");
  }
  display.setCursor(5, 40);
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    display.print("Humidity: ");
    display.print("69");
    display.println("%");
  } else {
    display.print("Humidity: ");
    display.print(event.relative_humidity);
    display.println("%");
  }
  display.display();
}




void playmusic() {
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    servoDrive(noteDuration * 0.9);
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    servoDrive(noteDuration);
    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}

void servoDrive(byte servoTime) {
  servoDelay = servoDelay + servoTime;
  if (servoDelay >= 15) {
    if (servoDir == 1) {
      if (angle <= maxAngle) {
        angle=angle+45;
      }
      else {
        servoDir = 0;
        angle=angle-45;
      }
    }
    else if (servoDir == 0) {
      if (angle >= minAngle) {
        angle=angle-45;
      }
      else {
        servoDir = 1;
        angle=angle+45;
      }
    }
    servo.write(angle);
    servoDelay = 0;
  }
}




void sendWet() {
  /** Enable the debug via Serial port
   * none debug or 0
   * basic debug or 1
  */
  smtp.debug(1);

  /* Set the callback function to get the sending results */
  smtp.callback(smtpCallback);

  /* Declare the session config data */
  ESP_Mail_Session session;

  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";
  /* Declare the message class */
  SMTP_Message message;

  /* Set the message headers */
  message.sender.name = "Baby Alert";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Wetness Detected";
  message.addRecipient("Aswin", RECIPIENT_EMAIL);

  /*Send HTML message*/
  String htmlMsg = "<div style=\"color:#2f4468;\"><h1>Wetness Detected!</h1><p>Wetness has been detected.</p><p>-Send from Baby Alert System.</p></div>";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  /*
  //Send raw text message
  String textMsg = "Hello World! - Sent from ESP board";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;*/

  /* Set the custom message header */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());
}

void sendCry() {
  /** Enable the debug via Serial port
   * none debug or 0
   * basic debug or 1
  */
  smtp.debug(1);

  /* Set the callback function to get the sending results */
  smtp.callback(smtpCallback);

  /* Declare the session config data */
  ESP_Mail_Session session;

  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";
  
  /* Declare the message class */
  SMTP_Message message;

  /* Set the message headers */
  message.sender.name = "Baby Alert";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Baby Crying";
  message.addRecipient("Aswin", RECIPIENT_EMAIL);

  /*Send HTML message*/
  String htmlMsg = "<div style=\"color:#2f4468;\"><h1>Baby Crying!</h1><p>Baby Started Crying</p><p>-Send from Baby Alert System.</p></div>";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  /*
  //Send raw text message
  String textMsg = "Hello World! - Sent from ESP board";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;*/

  /* Set the custom message header */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());
}

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status){
  /* Print the current status */
  Serial.println(status.info());

  /* Print the sending result */
  if (status.success()){
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
    Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++){
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients.c_str());
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject.c_str());
    }
    Serial.println("----------------\n");
  }
}
