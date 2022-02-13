# iot-smart-farming

## Conceptual Design
![Screenshot 2022-02-14 015408](https://user-images.githubusercontent.com/70487222/153770178-a9ecc946-c31f-47d6-984a-a3d8cbd99e1f.png)

## Features
- Real time measurement:
  - Temperature
  - Humidity
  - Soil moisture
- Data logging:
  - Maximum 1000 samples
  - sample interval – every 60 mins
- Real time display:
  - Temperature
  - Humidity
  - Moisture
  - Water pump on/off status
- Water pump is controlled by a manual control and an automatic control (depending on soil moisture)
- Send alert notification on mobile application if temperature, humidity or soil moisture is not in optimum limits
- Send alert notification when water pump is turned on and when water pump is turned off.

## System Components
- The MCU: ESP8266
- The DC Pump
- Humidity sensor 
- Temperature sensor
- Moisture sensor
- LCD Display

## Software Flowchart
![Untitled (1)](https://user-images.githubusercontent.com/70487222/153769987-5e88e035-2681-4174-aa15-c29b2d415921.jpg)

## Software Features
- Display humidity, temperature, soil moisture and pump status on mobile app
- Enable user to control pump through mobile app
- If temperature > upperLimitor || temp < lowerLimit send notification
- If humidity > upperLimit || humidity < lowerLimit: send notification
- If soil moisture < lowerLimit: turn on pump
- If soil moisture >= threshold: turn off pump
- If soil moisture > upperLimit: send notification

## Software Modules/Functions
**Function: MeasureTemp**   
Input: measurement unit ( Celcius ), output: temperature value   
**Function: SendTempNotification:**   
Input: temperature value, minimum/maximum allowed temperature    
**Function: MeasureHumidity**   
Input: measurement unit ( percentage), output: humidity value   
**Function: SendHumidityNotification:**   
Input: humidity value, minimum/maximum allowed humidity   
**Function: MeasureSoilMoisture:**   
Input: measurement unit (bars), output: soil moisture value   
**Function: RegulateMoisture:**   
Input: desired moisture value   
**Function: SendMoistureNotification:**   
Input: current moisture value, maximum/minimum allowed moisture values   
**Function: UpdateDisplay**   
Input: temperature, humidity, soil moisture and water pump status   

