  #include <ESP8266WiFi.h>
  #include <MicroGear.h>
  #include "DHT.h"
  // ----- Change following 6 config variables ---------------------
   const char* ssid     = "OnePlus 5T";       // WiFi ssid
  const char* password = "123456789";   // WiFi password
  #define APPID   "IoT2022"              // use group AppID 
  #define KEY     "shU7ZaS8NQsbDqs"                // use group Key
  #define SECRET  "vxXa0j8WLPEUqUZbS5jyQndch"             // use group Secret
  #define ALIAS   "Node1"  // your device name, ex. "A01"--------------
  // -------------------------------------------------------------------
  #define LEDSTATETOPIC "/ledstate/" ALIAS  // topic for LED status
  #define DHTDATATOPIC "/dht/" ALIAS         // topic for dht
  #define DHTPIN    D7        // DHT data pin
  #define DHTTYPE   DHT22     // e.g. DHT11, DHT21, DHT22

  #define LEDPIN     D0  // LED on NodeMCU board 

  int relayPin = 0;

  DHT dht(DHTPIN, DHTTYPE);
  WiFiClient client;
  
  int timer = 0;
  int lastDHTRead = 0;
  int currentLEDState = 0;
  int notify = 0;
  unsigned long currentMillis = 0;
 unsigned long t_on = 0;
 unsigned long t_start = 0;
 unsigned long t_off = 1000000;
 unsigned long t_end = 0;
 unsigned long notif_time = 0;
 unsigned long notif_limit = 0;
  MicroGear microgear(client);
  float humid = 0;
  float temp = 0;


void updateLED(int state) {

    // LED on NodeMCU is on when LEDPIN=LOW
    if(state==1 && currentLEDState == 0){
        currentLEDState = 1;
        digitalWrite(LEDPIN, HIGH);    //LED ON
        digitalWrite(relayPin, HIGH);


        t_off = 0;
        if(t_on == 0){ 
           t_start = currentMillis;
        }
        t_on = 1;
        
    }
    else if (state==0 && currentLEDState == 1) {
        currentLEDState = 0;
        digitalWrite(LEDPIN, LOW);  //LED OFF
        digitalWrite(relayPin, LOW);

        t_on = 0;
        if (t_off == 0){t_end = currentMillis;}
        t_off = 1;
        
    }
    microgear.publish(LEDSTATETOPIC, currentLEDState);

}


/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
    
    if (*(char *)msg == '0') updateLED(0);
    else if (*(char *)msg == '1') updateLED(1);
    else if (*(char *)msg == 'A'){ 
      //notif_limit = 1000*60*60*5; // Change! Inactual Implementation = Uncomment (5 Hrs)
      notif_limit = 30000; // Chnage! Inactual Implementation = Comment (60 Seconds)
      notify = 0;
    }

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
pinMode(relayPin, OUTPUT);

pinMode(LEDPIN, OUTPUT);    // set LEDPIN as OUTPUT
digitalWrite(LEDPIN, LOW);  //LED OFF
digitalWrite(relayPin, LOW); // Pump OFF
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

    humid = dht.readHumidity();     // read humidity
    temp  = dht.readTemperature();  // read temperature
    sensorValue = analogRead(sensorPin); // Solid Moisture
  
}

void loop() {

  currentMillis = millis();
  
    sensorValue = analogRead(sensorPin);
    //Serial.println(sensorValue);
    perc = ((1024.0-(float)sensorValue)/1024.0)*100.0;



   if(t_on<15000){
    if(t_on>0){
    t_on = currentMillis-t_start;}
    if(t_off>0){
      t_off = currentMillis-t_end;}
    if(perc<30 && currentLEDState == 0 && t_off>15000){
    currentLEDState = 1;
    digitalWrite(LEDPIN, HIGH);    //LED ON
    digitalWrite(relayPin, HIGH);
    t_off = 0;
    if(t_on == 0){ 
      t_start = currentMillis;
      microgear.publish("/@push/owner","Pump ON - Dont Worry, Your Plant is in Good Care!");
      }
    t_on = 1;
    }
   }
   else
   {
    currentLEDState = 0;
    digitalWrite(LEDPIN, LOW);  //LED OFF
    digitalWrite(relayPin, LOW);
    t_on = 0;
    if (t_off == 0){t_end = currentMillis;
    microgear.publish("/@push/owner","All Hydrated Now :D");
    }
    t_off = 1;
   }

    //temp  = dht.readTemperature();  // read temperature
             // Notifications ------------
      if(temp>35 && currentMillis>(notif_time+notif_limit))
      {
           notify = 1;  
           microgear.publish("/@push/owner","Temperature High :( , Please Take Action and Take Care of Plant");
           notif_time = currentMillis;
           //notif_limit = 1000*60*60*1; // Change! Inactual Implementation = Uncomment (1 Hrs)
           notif_limit = 10000; // Change! Inactual Implementation = Comment (10 Seconds)
      }
      else
      {
        if (temp<35){
        notify = 0;
        notif_limit = 0;
        notif_time = 0;
        } 
      }
   
    /* To check if the microgear is still connected */
    if (microgear.connected()) {
     //   Serial.println("connected");

        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();
        ReadDHTandSend();
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

void ReadDHTandSend () {if(millis() - lastDHTRead > 2000){        // Change! SAMPLING FREQUENCY CONTROL
    humid = dht.readHumidity();     // read humidity
    temp  = dht.readTemperature();  // read temperature
    sensorValue = analogRead(sensorPin); // Solid Moisture
    lastDHTRead = millis();

      
          
    Serial.print("Humid: "); Serial.print(humid); Serial.print(" %, ");
    Serial.print("Temp: "); Serial.print(temp); Serial.println(" °C ");
    
    if (isnan(humid) || isnan(temp)) { // check humid/temp is valid or not
      Serial.println("Failed to read from DHT sensor!");
    }
    else{
      // from a string in this format --> "{humid},{temp}"
      //String datastring = (String)humid+","+(String)temp+","+(String)perc;
      String datastring = (String)humid+","+(String)temp+","+(String)perc+","+(String)currentLEDState+","+(String)notify;
      Serial.print("Sending --> ");
      Serial.println(datastring);
      microgear.publish(DHTDATATOPIC,datastring);
      }
      
    }  
}
