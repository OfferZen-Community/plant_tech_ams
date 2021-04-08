#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESPUI.h>
#include <ESPAsyncWiFiManager.h>         //https://github.com/tzapu/WiFiManager
#define ANA A0
#define DIGI D5
#define POMPOUT D6
double analogValue = 0.0;
int digitalValue = 0;
double analogVolts = 0.0;
unsigned long timeHolder = 0;
DNSServer dnsServer;


uint16_t button1;
uint16_t switchOne;
uint16_t status;

void numberCall( Control* sender, int type ) {
  Serial.println( sender->value );
}

void textCall( Control* sender, int type ) {
  Serial.print("Text: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  Serial.println( sender->value );}

void slider( Control* sender, int type ) {
  Serial.print("Slider: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  Serial.println( sender->value );}

void buttonCallback( Control* sender, int type ) {
  switch ( type ) {
    case B_DOWN:
      Serial.println( "Button DOWN" );
      break;

    case B_UP:
      Serial.println( "Button UP" );
      break;
  }
}

void buttonExample( Control* sender, int type ) {
  switch ( type ) {
    case B_DOWN:
      Serial.println( "Status: Start" );
      ESPUI.updateControlValue( status, "Start" );

      ESPUI.getControl( button1 )->color = ControlColor::Carrot;
      ESPUI.updateControl( button1 );
      break;

    case B_UP:
      Serial.println( "Status: Stop" );
      ESPUI.updateControlValue( status, "Stop" );

      ESPUI.getControl( button1 )->color = ControlColor::Peterriver;
      ESPUI.updateControl( button1 );
      break;
  }
}

void padExample( Control* sender, int value ) {
  switch ( value ) {
    case P_LEFT_DOWN:
      Serial.print( "left down" );
      break;

    case P_LEFT_UP:
      Serial.print( "left up" );
      break;

    case P_RIGHT_DOWN:
      Serial.print( "right down" );
      break;

    case P_RIGHT_UP:
      Serial.print( "right up" );
      break;

    case P_FOR_DOWN:
      Serial.print( "for down" );
      break;

    case P_FOR_UP:
      Serial.print( "for up" );
      break;

    case P_BACK_DOWN:
      Serial.print( "back down" );
      break;

    case P_BACK_UP:
      Serial.print( "back up" );
      break;

    case P_CENTER_DOWN:
      Serial.print( "center down" );
      break;

    case P_CENTER_UP:
      Serial.print( "center up" );
      break;
  }

  Serial.print( " " );
  Serial.println( sender->id );
}

void switchExample( Control* sender, int value ) {
  switch ( value ) {
    case S_ACTIVE:
      Serial.print( "Active:" );
      break;

    case S_INACTIVE:
      Serial.print( "Inactive" );
      break;
  }

  Serial.print( " " );
  Serial.println( sender->id );
}

void selectExample( Control* sender, int value ) {
  Serial.print("Select: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  Serial.println( sender->value );
}

void otherSwitchExample( Control* sender, int value ) {
  switch ( value ) {
    case S_ACTIVE:
      Serial.print( "Active:" );
      break;

    case S_INACTIVE:
      Serial.print( "Inactive" );
      break;
  }

  Serial.print( " " );
  Serial.println( sender->id );
}



void setup() {
  // put your setup code here, to run once:
	  ESPUI.setVerbosity(Verbosity::VerboseJSON);
	  ESPUI.begin("Auto Plant Water");
  pinMode(ANA, INPUT);
  pinMode(DIGI, INPUT);
  pinMode(POMPOUT, OUTPUT);
  Serial.begin(115200);
  Serial.println("Paolo Test");
  WiFi.hostname("PlantWater");
  AsyncWiFiManager wifiManager(ESPUI.server,&dnsServer);
    //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
    //wifiManager.setAPCallback(configModeCallback);

    wifiManager.autoConnect("PlantWater");

    uint16_t tab1 = ESPUI.addControl( ControlType::Tab, "Settings 1", "Settings 1" );
    uint16_t tab2 = ESPUI.addControl( ControlType::Tab, "Settings 2", "Settings 2" );
    uint16_t tab3 = ESPUI.addControl( ControlType::Tab, "Settings 3", "Settings 3" );

    // shown above all tabs
    status = ESPUI.addControl( ControlType::Label, "Status:", "Stop", ControlColor::Turquoise );

    uint16_t select1 = ESPUI.addControl( ControlType::Select, "Select:", "", ControlColor::Alizarin, tab1, &selectExample );
    ESPUI.addControl( ControlType::Option, "Option1", "Opt1", ControlColor::Alizarin, select1 );
    ESPUI.addControl( ControlType::Option, "Option2", "Opt2", ControlColor::Alizarin, select1 );
    ESPUI.addControl( ControlType::Option, "Option3", "Opt3", ControlColor::Alizarin, select1 );

    ESPUI.addControl( ControlType::Text, "Text Test:", "a Text Field", ControlColor::Alizarin, tab1, &textCall );

    // tabbed controls
    ESPUI.addControl( ControlType::Label, "Millis:", "0", ControlColor::Emerald, tab1 );
    button1 = ESPUI.addControl( ControlType::Button, "Push Button", "Press", ControlColor::Peterriver, tab1, &buttonCallback );
    ESPUI.addControl( ControlType::Button, "Other Button", "Press", ControlColor::Wetasphalt, tab1, &buttonExample );
    ESPUI.addControl( ControlType::PadWithCenter, "Pad with center", "", ControlColor::Sunflower, tab2, &padExample );
    ESPUI.addControl( ControlType::Pad, "Pad without center", "", ControlColor::Carrot, tab3, &padExample );
    switchOne = ESPUI.addControl( ControlType::Switcher, "Switch one", "", ControlColor::Alizarin, tab3, &switchExample );
    ESPUI.addControl( ControlType::Switcher, "Switch two", "", ControlColor::None, tab3, &otherSwitchExample );
    ESPUI.addControl( ControlType::Slider, "Slider one", "30", ControlColor::Alizarin, tab1, &slider );
    ESPUI.addControl( ControlType::Slider, "Slider two", "100", ControlColor::Alizarin, tab3, &slider );
    ESPUI.addControl( ControlType::Number, "Number:", "50", ControlColor::Alizarin, tab3, &numberCall );

    /*
     * .begin loads and serves all files from PROGMEM directly.
     * If you want to serve the files from SPIFFS use ESPUI.beginSPIFFS
     * (.prepareFileSystem has to be run in an empty sketch before)
     */

    // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
    // ESPUI.sliderContinuous = true;

    /*
     * Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a
     * SECURE way of limiting access.
     * Anyone who is able to sniff traffic will be able to intercept your password
     * since it is transmitted in cleartext. Just add a string as username and
     * password, for example begin("ESPUI Control", "username", "password")
     */




}
void loop() {
  analogValue = analogRead(ANA);
  digitalValue = digitalRead(DIGI);
  // Serial data
  Serial.print("Analog raw: ");
  Serial.println(analogValue);
  Serial.print("Digital raw: ");
  Serial.println(digitalValue);
  Serial.println(" ");
  if (digitalValue == 0) {
    digitalWrite(POMPOUT, false);
  } else {
        Serial.println("PUMPIN");
      digitalWrite(POMPOUT, true);
  }
  delay(1000);
}

