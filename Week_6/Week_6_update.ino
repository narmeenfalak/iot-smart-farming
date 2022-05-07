int relayPin = 0;
int sensor_pin = A0; // Soil Sensor input at Analog PIN A0
int output_value ;
int mapped_output_value;
void setup()
{
Serial.begin(9600);
pinMode(relayPin, OUTPUT);
pinMode(sensor_pin, INPUT);
Serial.println("Reading From the Sensor ...");
delay(200);
}

void loop()
{
output_value= analogRead(sensor_pin);
Serial.print("Analog Value: ");
Serial.println(output_value);
mapped_output_value = map(output_value,1024,300,0,100);
Serial.print("Mositure : ");
Serial.print(mapped_output_value);
Serial.println("%");
if(mapped_output_value<=0){
digitalWrite(relayPin, HIGH);
}
else
{
digitalWrite(relayPin, LOW);
}
delay(1000);
}
