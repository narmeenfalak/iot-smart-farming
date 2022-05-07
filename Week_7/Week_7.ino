  #include <ESP8266WiFi.h>
  #include <MicroGear.h>
  #include "DHT.h"
  // ----- Change following 6 config variables ---------------------
  const char* ssid     = "OnePlus 5T";       // WiFi ssid
  const char* password = "123456789";   // WiFi password
  #define APPID   "IoT2022"              // use group AppID 
  #define KEY     "shU7ZaS8NQsbDqs"                // use group Key
  #define SECRET  "vxXa0j8WLPEUqUZbS5jyQndch"             // use group Secret
  #define ALIAS   "A01"  // your device name, ex. "A01"
  // -------------------------------------------------------------------
  #define LEDSTATETOPIC "/ledstate/" ALIAS  // topic for LED status
  #define DHTDATATOPIC "/dht/" ALIAS         // topic for dht
  #define DHTPIN    D7        // DHT data pin
  #define DHTTYPE   DHT22     // e.g. DHT11, DHT21, DHT22

  #define LEDPIN     D0  // LED on NodeMCU board 
  #define SWPIN     D6
  DHT dht(DHTPIN, DHTTYPE);
  WiFiClient client;

  int SWState = 0;         // current state of the button
int LastSWState = 0;     // previous state of the button


  int timer = 0;
  int lastDHTRead = 0;
  int currentLEDState = 1;
  int notify = 0;
  MicroGear microgear(client);


  
void updateLED(int state) {
    // LED on NodeMCU is on when LEDPIN=LOW
    if(state==1 && currentLEDState == 0){
        currentLEDState = 1;
        digitalWrite(LEDPIN, HIGH);    //LED ON
    }
    else if (state==0 && currentLEDState == 1) {
        currentLEDState = 0;
        digitalWrite(LEDPIN, LOW);  //LED OFF
    }
    Serial.print("UPdateLED = ");
    Serial.println(currentLEDState);
    microgear.publish(LEDSTATETOPIC, currentLEDState);

}


/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
    
    if (*(char *)msg == '0') updateLED(0);
    else if (*(char *)msg == '1') updateLED(1);

}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
    updateLED(0);
}



int sensorPin = A0;
int sensorValue; 
float perc;

void setup() {

pinMode(LEDPIN, OUTPUT);    // set LEDPIN as OUTPUT
digitalWrite(LEDPIN, LOW);  //LED OFF
pinMode (SWPIN, INPUT);
    /* Add Event listeners */

    /* Call onMsghandler() when new message arraives */
    microgear.on(MESSAGE,onMsghandler);

    /* Call onFoundgear() when new gear appear */
    microgear.on(PRESENT,onFoundgear);

    /* Call onLostgear() when some gear goes offline */
    microgear.on(ABSENT,onLostgear);

    /* Call onConnected() when NETPIE connection is established */
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
    Serial.println("Starting...");
    dht.begin(); // initialize DHT Sensor
    /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
    /* You may want to use other method that is more complicated, but provide better user experience */
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);

    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);

}

void loop() {
    /* To check if the microgear is still connected */
    sensorValue = analogRead(sensorPin);
    //Serial.println(sensorValue);
    perc = ((1024.0-(float)sensorValue)/1024.0)*100.0; 
    
    if (microgear.connected()) {
     //   Serial.println("connected");

        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();
        ReadDHTandSend();
        //CheckSW1();
    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}

void ReadDHTandSend () {if(millis() - lastDHTRead > 2000){        // setup a 2-second period
    float humid = dht.readHumidity();     // read humidity
    float temp  = dht.readTemperature();  // read temperature
    lastDHTRead = millis();
          
    Serial.print("Humid: "); Serial.print(humid); Serial.print(" %, ");
    Serial.print("Temp: "); Serial.print(temp); Serial.println(" °C ");
    
    if (isnan(humid) || isnan(temp)) { // check humid/temp is valid or not
      Serial.println("Failed to read from DHT sensor!");
    }
    else{
      // from a string in this format --> "{humid},{temp}"
      String datastring = (String)humid+","+(String)temp+","+(String)perc;
      Serial.print("Sending --> ");
      Serial.println(datastring);
      microgear.publish(DHTDATATOPIC,datastring);       
      if((temp>30)&&(notify==0))
      {
           notify = 1;  
        
           microgear.publish("/@push/owner","Temperature is high" + (String)temp);

      }
      else if(temp<28)
      {
        notify=0;
      }
      }
    }  
}

void CheckSW1()
 {
    // read the pushbutton input pin:
  SWState = digitalRead(SWPIN);

  // compare the buttonState to its previous state
  if (SWState != LastSWState) {
    // if the state has changed, increment the counter
    if (SWState == LOW) {
          if( currentLEDState == 0) updateLED(1);
          else updateLED(0);
       
    } 
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  LastSWState = SWState;
 }
