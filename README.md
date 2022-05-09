# IoT Smart Farming Project

## Project Progress Report

### Week 1
- Requirements and Design Finalization
- Project Proposal Presentation

### Week 2
- Hardware Purchase
    - Narmeen: Strawberry plant (Recieved)
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

### Week 6

- Hardware part completed.
-  Mapping for Soil moisture sensor with the Water pump is done
- Some modifications are needed in the code accordingly for the plant

### Week 7 
- Discovered overshoot problem in soil moisture sensor
- Tried different methods to work on the solution
- Implemented manual water pump control

### Week 8 (Final week)
- Solved overshoot issue by adding intervals to the pump control
- All work related to NETPIE and mobile app notifications

## Conceptual Design
![image](https://user-images.githubusercontent.com/70487222/167365560-96df4388-e939-43ba-83f6-0ecd7bdf6271.png)


## Features
- Real time measurement:  
  - Temperature of the surroundings   
  - Humidity of the surroundings  
  - Soil Moisture of the Plant   

- Real time display:  
  - Temperature of the surroundings   
  - Humidity of the surroundings    
  - Soil Moisture of the Plant   

- Water Pump On/Off Status
- Water pump is controlled by a manual control and an automatic control (depending on soil moisture)
- Send alert notification on mobile application if temperature or soil moisture is not in optimum limits
- Send alert notification when water pump is turned on 
- Send alert notification when water pump is turned off.

## System Components
- The MCU: ESP8266
- Mini Water Pump DC 3-6V 3W
- Humidity sensor DHT11 
- Temperature sensor DHT11
- Soil Moisture sensor
- Water pipe (outlet from pump; outer dia 7.5mm, inner dia 4.5 mm )

## Software Flowchart
![Blank diagram (5)](https://user-images.githubusercontent.com/70487222/167365470-f3baab3c-721e-4a31-8e62-1b8746e010da.png)


## Software Features
- Display humidity, temperature, soil moisture and water pump status on mobile app
- Enable user to control pump through mobile app (manual control)
- If temperature > 35 oC send notification
- If soil moisture < 30: turn on pump
- If soil moisture >= 30: turn off pump
- If soil moisture > 30: send notification

## Software Modules/Functions
**Function: MeasureTemp**   
Input: measurement unit ( Celcius ), output: temperature value   
**Function: SendTempNotification:**   
Input: temperature value, minimum/maximum allowed temperature    
**Function: MeasureHumidity**   
Input: measurement unit ( percentage), output: humidity value   
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

**Hafsa**
- Soil Moisture Sensor
- Water Pump and its control

## Project Timeline
![Screenshot 2022-03-31 214126](https://user-images.githubusercontent.com/70487222/161082366-5172f5cf-57a7-482e-a0d4-cc3428c5dcf1.jpg)




