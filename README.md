# IoT Smart Farming Project

## Project Progress Report

### Week 1
- Requirements and Design Finalization
- Project Proposal Presentation

### Week 2
- Hardware Purchase
    - Narmeen: Strawberry plant and LCD Display (Recieved)
    - Hafsa: Soil Moisture Sensor and Water Pump (Received)

### Week 3
- Strawberry Plant Research and Observation 
- Hardware connection for soil moisture sensor, humidity and temperature sensor (successful)

### Week 4
- Unit testing of moisture sensor and humidity and temperature sensor (successful)
- Water pump connection (failed)

### Week 5
- Acquired relay board to solve water pump connection issue
- Hinderance: Strawberry plant died 
- Considering switching to a different plant


## Conceptual Design
![Screenshot 2022-03-31 212653](https://user-images.githubusercontent.com/70487222/161079274-fda5eecf-d26b-4a70-ba9b-527d57425ca9.jpg)
    

## Features
- Real time measurement:  
  - Temperature of the surroundings   
  - Humidity of the surroundings  
  - Soil Moisture of the Plant  
- Data logging:
  - Maximum 1000 samples   
  - Default sample interval: every 60 mins   
  - Special Conditions (e.g: water pump is on): every 10 seconds until condition is normal  
- Real time display:  
  - Temperature of the surroundings   
  - Humidity of the surroundings    
  - Soil Moisture of the Plant   

- Water Pump On/Off Status
- Water pump is controlled by a manual control and an automatic control (depending on soil moisture)
- Send alert notification on mobile application if temperature, humidity or soil moisture is not in optimum limits
- Send alert notification when water pump is turned on 
- Send alert notification when water pump is turned off.

## System Components
- The MCU: ESP8266
- Mini Water Pump DC 3-6V 3W
- Humidity sensor DHT11 
- Temperature sensor DHT11
- Soil Moisture sensor
- LCD Display (16*2)
- Water pipe (inlet to pump; 5mm)
- Water pipe (outlet from pump; outer dia 7.5mm, inner dia 4.5 mm )

## Software Flowchart
![Screenshot 2022-03-31 213746](https://user-images.githubusercontent.com/70487222/161081478-fc8c2501-5bc5-4514-a7b2-9ba8ab83057c.jpg)


## Software Features
- Display humidity, temperature, soil moisture and water pump status on mobile app
- Enable user to control pump through mobile app (manual control)
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

## Task Distribution
**Narmeen**
- Humidity Sensor
- Temperature Sensor
- LCD Display

**Hafsa**
- Soil Moisture Sensor
- Water Pump and its control

## Project Timeline
![Screenshot 2022-03-31 214126](https://user-images.githubusercontent.com/70487222/161082366-5172f5cf-57a7-482e-a0d4-cc3428c5dcf1.jpg)




