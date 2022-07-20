/******************************************************************************

  Application: Smart Shopping Cart System (Graduation Project)

  File Name: Smart_Shopping_Cart_System.ino (Arduino File)

  Description: Source file for application

  Author: Mohamed Ashraf

*******************************************************************************/

#include <WiFi.h> /* To use Wifi */
#include <HTTPClient.h> /* to send and recieve from internet */
#include <ArduinoJson.h> /* to use JSON */
#include <LiquidCrystal.h> /* to use LCD */

/*******************************************************************************
                                  Definitions
 ******************************************************************************/

#define RXD2 16
#define TXD2 17
#define BUFFER_SIZE 9                                      /* Size of Bar Code */
#define TRUE 1
#define FALSE 0
#define HTTPS_LOGGED_IN 200
#define HTTPS_LOGGED_OUT 201

/*******************************************************************************
                             Global Variables
 ******************************************************************************/

const char* ssid = "WE/Zeft";                                                                           /* WiFi Name */
const char* password = "5432154321";                                                                   /* WiFi Password */
const char* serverName = "https://smartcart-helwan.herokuapp.com/api/add_orderItems";                 /* API */
const char* Login_serverName = "https://smartcart-helwan.herokuapp.com/api/login-cart";              /* API */
const char* Logout_serverName = "https://smartcart-helwan.herokuapp.com/api/logout-cart";           /* API */
const char* Inform_Login_API = "https://smartcart-helwan.herokuapp.com/api/confirm-login-cart";    /* API */
const char* Inform_Logout_API = "https://smartcart-helwan.herokuapp.com/api/confirm-logout-cart"; /* API */
int httpResponseCode;                                                                            /* Variable to store HTTP response code */
char counter = 0;                                                                               /* Counter Loop */
char Data = 0;                                                                                 /* Variable to read incoming serial data */
char Buffer_counter = 0;                                                                      /* Variable to track elements */
char Bar_Code[BUFFER_SIZE];                                                                  /* Array to store data */
char login_barcode[BUFFER_SIZE];
char logout_barcode[BUFFER_SIZE];
char Logic = FALSE;                                                                        /* Variable to track Logic of Logging in */
char Logged_IN = FALSE;
char Logged_OUT = TRUE;
char First_POST_Data = FALSE;
int Login_Counter = 0;
int Logout_Counter = 0;
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

/*******************************************************************************
                                   Objects
 *******************************************************************************/

LiquidCrystal lcd(19, 18, 4, 0, 2, 15);                             /* LCD config */
HTTPClient http;
HTTPClient login;
HTTPClient logout;
String payload;                                                 /* String to store response of add_orderItems API */
String payloadd;                                               /* String to store response of Login API */
String payload_logout;                                        /* String to store response of Logout API */

/********************************************************************************
                                 Function Definitions
 *******************************************************************************/

void Logout_POST_Request(void) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient Client;
    Client.begin(Inform_Logout_API);
    Client.addHeader("Content-Type", "application/json");
    String requestBody;                           /* String to store post request */
    StaticJsonDocument<200> doc;                 /* JSON document to store request */
    doc["Status"] = "Logged out";
    serializeJson(doc, requestBody);
    Client.POST(requestBody);
    // Free resources
    Client.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

void Login_POST_Request(void) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient Client;
    Client.begin(Inform_Login_API);
    Client.addHeader("Content-Type", "application/json");
    String requestBody;                           /* String to store post request */
    StaticJsonDocument<200> doc;                 /* JSON document to store request */
    doc["Status"] = "Logged In";
    serializeJson(doc, requestBody);
    Client.POST(requestBody);
    // Free resources
    Client.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

char Login_GET_Request(void) {
  HTTPClient Client;
  if (WiFi.status() == WL_CONNECTED) {
    if (strcmp(Bar_Code, "000111222") == 0) {
      Client.begin(Login_serverName);
      Serial.println("Logging in...");
      for (Login_Counter = 0; Login_Counter < 30; Login_Counter++) {
        Serial.print("Request: ");
        Serial.println(Login_Counter + 1);
        httpResponseCode = Client.GET();
        if (httpResponseCode > 0) {
          payloadd = Client.getString();
          //Serial.println(payloadd);
          if (payloadd.length() > 3) {
            Serial.print("Logged in with Token: ");
            Serial.println(payloadd);

            /* CREATE ORDER */
            //            HTTPClient Cart;
            //            Cart.begin(Inform_Logout_API);
            //            String CartTOKEN;
            //            CartTOKEN = payloadd.substring(1, 41);
            //            String CreateOrder = "Token " + CartTOKEN;
            //            Cart.addHeader("Authorization", CreateOrder);
            //            Cart.addHeader("Content-Type", "application/json");
            //            String requestBody;                           /* String to store post request */
            //            StaticJsonDocument<200> Cartdoc;
            //            Cartdoc["cart"] = "1";
            //            Serial.println(requestBody);
            //            serializeJson(Cartdoc, requestBody);
            //            Cart.POST(requestBody);
            //            if (httpResponseCode > 0) {
            //            String payload = http.getString();
            //            Serial.println(payload);
            //             }
            //          // Free resources
            //             Cart.end();
            /* ********* */

            strcpy(Bar_Code, "");
            lcd.clear();
            lcd.print("Successfully logged in!");
            delay(2000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Bar Code:");
            lcd.setCursor(0, 1);
            return HTTPS_LOGGED_IN;
          }
        }
        else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }
        // Free resources
        Client.end();
        delay(500);
      }
    }
  }
  return 0;
}


char Logout_GET_Request(void) {
  HTTPClient Client;
  if (WiFi.status() == WL_CONNECTED) {
    if (strcmp(Bar_Code, "444555666") == 0) {
      Client.begin(Logout_serverName);
      Serial.println("Logging out...");
      for (Logout_Counter = 0; Logout_Counter < 30; Logout_Counter++) {
        Serial.print("Request: ");
        Serial.println(Logout_Counter + 1);
        httpResponseCode = Client.GET();
        if (httpResponseCode > 0) {
          payload_logout = Client.getString();
          //Serial.println(payloadd);
          if (payload_logout.length() > 3) {
            Serial.print("Logged out with Message: ");
            Serial.println(payload_logout);
            strcpy(Bar_Code, "");
            lcd.clear();
            lcd.print("Successfully logged out!");
            delay(2000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Bar Code:");
            lcd.setCursor(0, 1);
            return HTTPS_LOGGED_OUT;
          }
        }
        else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }
        // Free resources
        Client.end();
        delay(500);
      }
    }
  }
  return 0;
}

/*******************************************************************************
                                   Application
*******************************************************************************/

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  lcd.begin(16, 2);
  lcd.print("Bar Code:");
  lcd.setCursor(0, 1);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (Serial2.available() > 0) {
    // read the incoming bytes:
    Data = Serial2.read();
    switch (Data) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        Serial.print(Data);
        lcd.print(Data);
        Bar_Code[Buffer_counter] = Data;
        Buffer_counter++;
        if (Buffer_counter == 9) { //_000111222_
          Bar_Code[Buffer_counter] = '\0';
        }
        break;
    }
    counter++;
    if (counter == 11) {
      //Serial2.flush();
      Serial.println();
      lcd.setCursor(0, 1);
      counter = 0;
      Buffer_counter = 0;

      if (Logged_IN == FALSE) {
        if (Login_GET_Request() == HTTPS_LOGGED_IN) {
          Logic = TRUE;
          Logged_IN = TRUE;
          Logged_OUT = FALSE;
          Login_POST_Request();
        }
        else {
          if (Login_Counter == 30) {
            Login_Counter = 0;
            Logged_IN = FALSE;
            Serial.println("Login failed");
            Serial.println("please re-login");
            lcd.setCursor(0, 0);
            lcd.print("Login failed");
            lcd.setCursor(0, 1);
            lcd.print("please re-login");
            delay(3000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Bar Code:");
            lcd.setCursor(0, 1);
          }
        }
      }

      if (Logged_OUT  == TRUE) {
        /* do nothing */
      }

      if (Logged_OUT == FALSE) {
        if (Logout_GET_Request() == HTTPS_LOGGED_OUT) {
          Logic = FALSE;
          Logged_IN = FALSE;
          Logged_OUT = TRUE;
          Logout_POST_Request();
          First_POST_Data = FALSE;
          ESP.restart();
        }
        else {
          if (Logout_Counter == 30) {
            Logout_Counter = 0;
            Logged_IN = TRUE;
            Logic = TRUE;
            Serial.println("Logout failed");
            Serial.println("please logout");
            lcd.setCursor(0, 0);
            lcd.print("Login failed");
            lcd.setCursor(0, 1);
            lcd.print("please logout`");
            delay(3000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Bar Code:");
            lcd.setCursor(0, 1);
          }
        }
      }
      if (Logic == TRUE) {
        if (WiFi.status() == WL_CONNECTED) {
          if (strcmp(Bar_Code,"") != 0) {
            http.begin(serverName);
            http.addHeader("Content-Type", "application/json");
            String TOKEN;
            TOKEN = payloadd.substring(1, 41);
            String something = "Token " + TOKEN;
            Serial.println(something);
            http.addHeader("Authorization", something);
            String requestBody;                           /* String to store post request */
            StaticJsonDocument<200> doc;                 /* JSON document to store request */
            doc["barcode"] = Bar_Code;
            serializeJson(doc, requestBody);
            // Send HTTP POST request
            Serial.println(requestBody);
            httpResponseCode = http.POST(requestBody);
            if (httpResponseCode > 0) {
              payload = http.getString();
              Serial.println(payload);
            }
            // Free resources
            http.end();
          }
        }
        else {
          Serial.println("WiFi Disconnected");
        }
      }
    }
  }
}
