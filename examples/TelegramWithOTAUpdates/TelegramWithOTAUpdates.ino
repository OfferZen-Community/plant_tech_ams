// Libraries.
#include <Arduino_JSON.h>
#include <JSON.h>
#include <JSONVar.h>
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>
#include "AsyncTelegram.h"

// Define bot and inline keyboard.
AsyncTelegram telegramBot;
InlineKeyboard waterBoard;
WiFiClientSecure client;

// Pins.
#define ANA A0
#define POMPOUT D6
#define SENSORPOWER D1

// WiFi settings.
#define WIFISSID "YOURWIFISSID" // Add your WiFi SSID Here.
#define WIFIPASSWORD "YOURWIFIPASSWORD" // Add your Wifi password Here.

// Telegram settings.
#define TELEGRAMBOTID "XXXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" // Your Bot's Telegram ID.
#define TELEGRAMUSERID "XXXXXXXXX;" // Your Telegram ID.

// Time variables.
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24L)

// Elapsed time variables.
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)  
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define numberOfHours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)  


// Settings.
// Version number.
char versionNumber[10] = "1.0.0"; // Current version of this app.
// Default variables
unsigned long currentMillis, lastCheckTimePlant, lastCheckTimeWiFi, lastPumpTime, ledTime; // Variables to hold millis.
char timePassed[10], analogValueAsText[10] = "Unknown"; // Char pointers for time and analogValue text.
bool ledOn = true; // Default led status
double analogValue = 0.0; // Default water measure value.
int moisturePercentage = 0; // Default water percentage level.
// Variables that can be tuned for your application.
int amountOfMeasurements = 10; // How many times to measure the moist in the plant per check.
int pumpTime = 2000; // How long it should pump on the default check in miliseconds.
int threshold = 500; // Your analog value threshold to automatically pump water.
int manualPumpThreshold = 400; // Threshold to be met to allow manual pumping of water.
int sleepTimeLed = 3000; // LED should be on for 3 Seconds when a new telegram message arrives (just for fun).
int sleepTimePlantCheck = 3600000; // Automatically check the plant status every 1 hour.
int sleepTimePumpCheck = 3600000; // Allow pumping water once every 1 hour.
int sleepTimeWiFiCheck = 300000; // Check WiFi every 5 minutes.

void setup() {
  // Start serial.
  Serial.begin(115200);
  Serial.setTimeout(2000);
  
  // Set pinmodes.
  pinMode(ANA, INPUT);
  pinMode(POMPOUT, OUTPUT);
  pinMode(SENSORPOWER, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Disable automatic reboot after httpUpdate. We have to handle reboot manually after sync with Telegram server.
  ESPhttpUpdate.rebootOnUpdate(false);

  // Create client for rom download.
  client.setInsecure();
  client.setNoDelay(true);

  // Start WiFi.
  scanWiFi();

  // Set last check times.
  lastCheckTimeWiFi = millis();
  ledTime = (millis() - sleepTimeLed);
  lastCheckTimePlant = (millis() - sleepTimePlantCheck);
  lastPumpTime = (millis() - sleepTimePumpCheck);

  // Add keyboard with buttons to water the plant.
  // The 2nd parameter is the amount of millisecs it will water the plant.
  waterBoard.addButton("1 SECONDS", "1000", KeyboardButtonQuery, waterPressed);
  waterBoard.addButton("2 SECONDS", "2000", KeyboardButtonQuery, waterPressed);
  waterBoard.addRow();
  waterBoard.addButton("3 SECONDS", "3000", KeyboardButtonQuery, waterPressed);
}

void loop() {
  // Store telegram message data.
  TBMessage msg;

  if (telegramBot.getNewMessage(msg)) {
    // There is a new message.
    Serial.println("Received message from:");
    Serial.println(msg.sender.firstName);
    Serial.println(msg.sender.lastName);
    Serial.println(msg.sender.id);
    Serial.println(msg.text);
    
    // Flash LED on new message.
    digitalWrite(LED_BUILTIN, LOW);
    ledOn = true;
    ledTime = millis();
    
    // Let's check the MessageType
    MessageType msgType = msg.messageType;
    switch (msgType) {
      // If the message is a text message.
      case MessageText:
        // Some if statements to check the text in a message.
        // It ignores case, so you can send /StAtUs and still be answered with below text.
        // Status will return the general status of your plant, and if water pumping is allowed.
        if (msg.text.equalsIgnoreCase("/STATUS")) {
          String replyStatus;
          replyStatus = "Water status:\n";
          replyStatus += analogValueAsText;
          replyStatus += " (";
          replyStatus += analogValue;
          replyStatus += ", ";
          replyStatus += moisturePercentage;
          replyStatus += "%).";
          replyStatus += "\nTime passed since last check:\n";
          calculateTimePassed(timePassed, (currentMillis - lastCheckTimePlant)/1000);
          replyStatus += timePassed;
          replyStatus += "\n\nPump Status.\n";
          if (currentMillis - lastPumpTime >= sleepTimePumpCheck && analogValue > manualPumpThreshold) {
            replyStatus += "Manual water pumping allowed.\n";
          } else {
            replyStatus += "Manual water pumping not allowed yet.\n";
          }
          replyStatus += "Time passed since last water pump:\n";
          calculateTimePassed(timePassed, (currentMillis - lastPumpTime)/1000);
          replyStatus += timePassed;
          telegramBot.sendMessage(msg, replyStatus);
        // Version will return the current version of your platform. 
        } else if (msg.text.equalsIgnoreCase("/VERSION")) {
          String replyVersion;
          replyVersion = "Version: ";
          replyVersion += versionNumber;
          telegramBot.sendMessage(msg, replyVersion);
        // Water status will return JUST the water status of your plant.
        } else if (msg.text.equalsIgnoreCase("/WATER_STATUS")) {
          String replyStatus;
          replyStatus = "Water status:\n";
          replyStatus += analogValueAsText;
          replyStatus += " (";
          replyStatus += analogValue;
          replyStatus += ", ";
          replyStatus += moisturePercentage;
          replyStatus += "%).";
          replyStatus += "\nTime passed since last check:\n";
          calculateTimePassed(timePassed, (currentMillis - lastCheckTimePlant)/1000);
          replyStatus += timePassed;
          telegramBot.sendMessage(msg, replyStatus);
        // Pump status will return JUST the status of manual water pumping.
        } else if (msg.text.equalsIgnoreCase("/PUMP_STATUS")) {
          String replyStatus;
          replyStatus = "Pump status:\n";
          if (currentMillis - lastPumpTime >= sleepTimePumpCheck && analogValue > manualPumpThreshold) {
            replyStatus += "Manual water pumping allowed.\n";
          } else {
            replyStatus += "Manual water pumping not allowed yet.\n";
          }
          replyStatus += "Time passed since last water pump:\n";
          calculateTimePassed(timePassed, (currentMillis - lastPumpTime)/1000);
          replyStatus += timePassed;
          telegramBot.sendMessage(msg, replyStatus);
        // Pump water will check if water pumping is allowed, and if it is, it will show buttons to water the plant.
        } else if (msg.text.equalsIgnoreCase("/PUMP_WATER")) {
          if (analogValue > manualPumpThreshold) {
            if (currentMillis - lastPumpTime >= sleepTimePumpCheck) {
              telegramBot.sendMessage(msg, "Choose how long you wish to water:", waterBoard);
            } else {
              pumpDenied(msg, false);
            }
          } else {
            pumpDenied(msg, true);
          }
        // Admin functions start here!
        // Force check status forces a new check on the water status of your plant.
        } else if (msg.text.equalsIgnoreCase("/FORCE_CHECK_STATUS") && msg.sender.id == atoi(TELEGRAMUSERID)) {
          telegramBot.sendMessage(msg, "Measuring water status, please wait.");
          waterStatus();
          String replyStatus;
          replyStatus = "Water status:\n";
          replyStatus += analogValueAsText;
          replyStatus += " (";
          replyStatus += analogValue;
          replyStatus += ", ";
          replyStatus += moisturePercentage;
          replyStatus += "%).";
          telegramBot.sendTo(atoi(TELEGRAMUSERID), replyStatus);
        // Force pump water forces water to be pumped to your plant for the default amount of seconds.
        } else if (msg.text.equalsIgnoreCase("/FORCE_PUMP_WATER") && msg.sender.id == atoi(TELEGRAMUSERID)) {
          pumpWater(msg, pumpTime, true);
        // Start will show all accepted commands, including admin commands if the admin requests this.
        } else if (msg.text.equalsIgnoreCase("/START")) {
          String reply;
          reply = "Welcome " ;
          reply += msg.sender.firstName;
          reply += ".\n\nAccepted commands:\n";
          reply += "- /status\n";
          reply += "- /water_status\n";
          reply += "- /pump_status\n";
          reply += "- /pump_water\n";
          reply += "- /version\n";
          reply += "- More to come!\n";
          // Show admin functions to the admin.
          if (msg.sender.id == atoi(TELEGRAMUSERID)) {
            reply += "\nAdmin commands:\n";
            reply += "- /force_check_status\n";
            reply += "- /force_pump_water\n";
            reply += "Or send a firmware update file with caption /fw_update.";
          }
          telegramBot.sendMessage(msg, reply);
        }
        break;
      // If the message is a file.
      case MessageDocument:
        if (msg.sender.id == atoi(TELEGRAMUSERID)) {
          if (msg.document.file_exists) {
            // Caption is '/fw_update' and file exist
            if (msg.text.equalsIgnoreCase("/fw_update")) {
              String reply;
              reply = "Update started!\nFile name: ";
              reply += msg.document.file_name;
              reply += "\nFile size: ";
              reply += msg.document.file_size;
              telegramBot.sendMessage(msg, reply.c_str());
        
              // Install firmware update
              t_httpUpdate_return updateReturn = ESPhttpUpdate.update(client, msg.document.file_path);

              // Inform the admin on the status.
              switch (updateReturn) {
                case HTTP_UPDATE_FAILED: {
                  String replyUpdateStatus;
                  replyUpdateStatus = "HTTP_UPDATE_FAILED Error (";
                  replyUpdateStatus += ESPhttpUpdate.getLastError();
                  replyUpdateStatus += "): ";
                  replyUpdateStatus += ESPhttpUpdate.getLastErrorString();
                  telegramBot.sendMessage(msg, replyUpdateStatus);
                  break;
                }
                case HTTP_UPDATE_NO_UPDATES:
                  telegramBot.sendMessage(msg, "HTTP_UPDATE_NO_UPDATES");
                  break;        
                case HTTP_UPDATE_OK:
                  telegramBot.sendMessage(msg, "Update OK.\nRestarting now.");
                  Serial.println("Waiting for reboot.");
                  
                  // Wait until the bot synced with telegram to prevent cyclic reboots.
                  while (!telegramBot.getUpdates()) {
                    Serial.print(".");
                    delay(50);
                  }
                  // Actually restart the ESP board.
                  ESP.restart();
                  break;
              }
            } else {
              // Admin sent a file, but did not include the caption /fw_update.
              telegramBot.sendMessage(msg, "Error: file caption is not '/fw_update'");
            }
          } else {
            // Can't find the file or file too big.
            telegramBot.sendMessage(msg, "File is unavailable. Maybe size limit 20MB was reached or the file deleted");
          }
        } else {
          // User is not admin, tell them we don't do file handling here.
          telegramBot.sendMessage(msg, "This bot cannot handle files.");
        }
        break;
    }
  }
  // Set currentMillis.
  currentMillis = millis();
  
  // Check if we need to turn off the led.
  if (currentMillis - ledTime >= sleepTimeLed && ledOn == true) {
    digitalWrite(LED_BUILTIN, HIGH);
    ledOn = false;
  }
  
  // Check if we need to check the connection.
  if (currentMillis - lastCheckTimeWiFi >= sleepTimeWiFiCheck) {
    char timePassedWiFi[10];
    calculateTimePassed(timePassedWiFi, (currentMillis - lastCheckTimeWiFi)/1000);
    lastCheckTimeWiFi = millis();
    testConnections();
  }
  
  // Check if we need to measure the plant water status.
  if (currentMillis - lastCheckTimePlant >= sleepTimePlantCheck) {
    testConnections();
    waterStatus();
    // Send a message to let us know it has been done.
    String reply;
    reply = "Automatically checked plant.\n\n";
    reply += "Water status:\n";
    reply += analogValueAsText;
    reply += " (";
    reply += analogValue;
    reply += ", ";
    reply += moisturePercentage;
    reply += "%).";
    
    // Start pumping water if analogValue > threshold.
    if (analogValue > threshold) {
      pumpWater(msg, pumpTime, false);
      reply += "Automatically watered plant.\n\n";
      reply += "Plant has been watered for ";
      reply += pumpTime/1000;
      reply += " seconds.";
    }
    Serial.println(reply);
    telegramBot.sendTo(atoi(TELEGRAMUSERID), reply);
  }
}

void testConnections() {
  // Test if we are still connected.
  Serial.println("Testing if we are still connected.");
  int statusWiFi = WiFi.status();
  if (statusWiFi == WL_CONNECTION_LOST || statusWiFi == WL_DISCONNECTED || statusWiFi == WL_SCAN_COMPLETED) {
    // We lost our connection. Let's try to re-connect
    Serial.println("WiFi lost. Reconnecting.");
    scanWiFi();
  } else {
    // We are still connected. Let's test our Telegram server connection.
    Serial.println("WiFi connected. Testing telegram.");
    if (!telegramBot.begin()) {
      Serial.println("Telegram connection lost. Reconnecting.");
      connectTelegram();
    } else {
      Serial.println("Telegram still connected.");
    }
  }
}

void waterStatus() {
  // Set last check time plant.
  lastCheckTimePlant = millis();
  
  // Reset analogValue.
  analogValue = 0;
  moisturePercentage = 0;

  // Power on sensor and wait a bit to start.
  digitalWrite(SENSORPOWER, HIGH);
  delay(2000);

  // Measure multiple times.
  for (int i = 0; i < amountOfMeasurements; i++){
    Serial.println("Measurement:");
    Serial.println(analogRead(ANA));
    analogValue += analogRead(ANA);
    delay(500);
  }
  
  // Turn off power sensor.
  digitalWrite(SENSORPOWER, LOW);
  
  // Calculate the average measurement.
  analogValue = analogValue / amountOfMeasurements;

  // Calculate the percentage of moist.
  moisturePercentage = convertToPercent(analogValue);

  // Set text based on the analogValue.
  if (analogValue > 700) {
    strcpy(analogValueAsText, "Dry");
  } else if (analogValue > 400) {
    strcpy(analogValueAsText, "Moist");
  } else {
    strcpy(analogValueAsText, "Wet");
  }
  
  Serial.println("The avarage measure is:");
  Serial.println(analogValue);
}

void waterPressed(const TBMessage &queryMsg) {
  // Double check if water pumping is allowed.
  if (currentMillis - lastPumpTime >= sleepTimePumpCheck) {
    // Get the chosen time to pump from the callbackQueryData.
    int chosenPumpTime = atoi(queryMsg.callbackQueryData);

    // Start pumping.
    pumpWater(queryMsg, chosenPumpTime, false);

    // Send an alert to the user saying the plant has been watered.
    char reply[40];
    int seconds = chosenPumpTime/1000;
    snprintf(reply, 40, "Plant has been watered for %d seconds.", seconds);
    Serial.println(reply);
    telegramBot.endQuery(queryMsg, reply, true);

    // If the user was not the admin, send a message to the admin.
    if (queryMsg.sender.id != atoi(TELEGRAMUSERID)) {
      String notifyAdmin;
      notifyAdmin = "Someone other than you watered your plant:\n";
      notifyAdmin += queryMsg.sender.id;
      notifyAdmin += " - ";
      notifyAdmin += queryMsg.sender.firstName;
      notifyAdmin += " ";
      notifyAdmin += queryMsg.sender.lastName;
      notifyAdmin += "\n\nPlant has been watered for ";
      notifyAdmin += chosenPumpTime/1000;
      notifyAdmin += " seconds.";
      telegramBot.sendTo(atoi(TELEGRAMUSERID), notifyAdmin);
    }
  } else {
    pumpDenied(queryMsg, false);
  }
}

void pumpWater(const TBMessage &msg, long timer, bool message) {
  // Set new last pump time.
  lastPumpTime = millis();

  // Pump water.
  digitalWrite(POMPOUT, HIGH);
  delay(timer);
  digitalWrite(POMPOUT, LOW);
  
  // Send message to admin if needed.
  if (message) {
    String reply;
    reply = "Plant has been watered for ";
    reply += timer/1000;
    reply += " seconds.";
    Serial.println(reply);
    telegramBot.sendTo(atoi(TELEGRAMUSERID), reply);
  }
}

void pumpDenied(const TBMessage &msg, bool tooWet) {
  // Inform the user that pumping water was denied at this time.
  char timePassedPump[10];
  calculateTimePassed(timePassedPump, (currentMillis - lastPumpTime)/1000);
  String replyStatus;
  replyStatus = "Could not water the plant!\n";
  if (tooWet) {
    replyStatus += "The plant is still too wet for it to be watered.\n";
  } else {
    replyStatus += "The plant has already been watered not so long ago.\n";
  }
  replyStatus += "Please don't drown it and wait a bit before you water again.\n";
  if (tooWet) {
    replyStatus += "Water status:\n";
    replyStatus += analogValueAsText;
    replyStatus += " (";
    replyStatus += analogValue;
    replyStatus += ", ";
    replyStatus += moisturePercentage;
    replyStatus += "%).";
  } else {
    replyStatus += "\nTime passed since last pump:\n";
    replyStatus += timePassedPump;
  }
  telegramBot.sendMessage(msg, replyStatus);
}

void connectTelegram() {
  // Start or reset the connection to the Telegram servers.
  Serial.println("Starting Telegram connection...");
  telegramBot.setUpdateTime(1000);
  telegramBot.setTelegramToken(TELEGRAMBOTID);
  if (!telegramBot.begin()) {
    if (telegramBot.reset()) {
      String reply;
      reply = "Telegram connected succesfully.";
      telegramBot.sendTo(atoi(TELEGRAMUSERID), reply);
      Serial.println(reply);
    } else {
      Serial.println("Telegram connection failed.");
    }
  } else {
    String reply;
    reply = "Telegram connected succesfully.";
    telegramBot.sendTo(atoi(TELEGRAMUSERID), reply);
    Serial.println(reply);
  }
}

void connectWiFi() {
  bool tryingToConnect = true; // Set boolean that wifi is connecting
  WiFi.begin(WIFISSID, WIFIPASSWORD);
  Serial.println("Connecting.");
  while(tryingToConnect){ //while connecting
    delay(500);
    Serial.print(".");
    if (WiFi.status() == WL_CONNECTED){ // If connected set bool to false, so we can continue
      tryingToConnect = false;
      Serial.println("\nConnected to WiFi network with IP Address: ");
      Serial.println(WiFi.localIP());
      connectTelegram();
    } else if (WiFi.status() == WL_CONNECT_FAILED || WiFi.status() == WL_NO_SSID_AVAIL){ 
      // If error dont send anything, wifi might be down, better luck next time
      Serial.println("Connection failed. Retry in 5 min.");
    }
  }
}

void scanWiFi() {
  // Scan WiFi networks.
  int numSSID = WiFi.scanNetworks();
  Serial.println("Scanning all networks.");

  // If there are no SSID's.
  if (numSSID == -1) {
    Serial.println("No SSID's found.");
  }

  // Loop through found SSID's and check if our SSID is in the list.
  for (int netList = 0; netList < numSSID; netList++) {
    if (WiFi.SSID(netList) == WIFISSID) {
      // Great! our SSID is found. Let's connect the WiFi.
      Serial.println("Configured SSID found.");
      connectWiFi();
    }
  }
}

void calculateTimePassed(char *stringTime, long val) {
  // Calculate how much time has passed based on millis().
  // This will return the time in this format: 0:00:00:00
  int days = elapsedDays(val);
  int hours = numberOfHours(val);
  int minutes = numberOfMinutes(val);
  int seconds = numberOfSeconds(val);
  int minutesSpace = 0, hoursSpace = 0, daysSpace = 0;
  // Start building the time string, only include days if 1 or more days have passed.
  if (days > 0) {
    daysSpace = snprintf(stringTime, 10, "%d:", days);
  }
  hoursSpace = snprintf(stringTime + daysSpace, 10 - daysSpace, "%02d:", hours);
  minutesSpace = snprintf(stringTime + hoursSpace + daysSpace, 10 - hoursSpace - daysSpace, "%02d:", minutes);
  snprintf(stringTime + minutesSpace + hoursSpace + daysSpace, 10 - minutesSpace - hoursSpace - daysSpace, "%02d", seconds);
}

int convertToPercent(int value) {
  // Convert the given value to a percentage.
  int percentValue = 0;
  percentValue = map(value, 1024, 235, 0, 100);
  return percentValue;
}
