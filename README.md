# contiki-weather-station

Follow these steps to compile and run the **sensor-node** and **base-station** in **Cooja**.

---

## 1️⃣ Compile the Files

1. Move the project to the Contiki-NG `examples` folder:
   ```bash
   mv contiki-weather-station ~/contiki-ng/examples/
   cd ~/contiki-ng/examples/contiki-weather-station
Compile the Sensor Node:

bash-make TARGET=sky sensor-node

Compile the Base Station:
bash-make TARGET=sky base-station
This will generate the .sky firmware files required for Cooja simulation.

2️⃣ Run in Cooja
Start Cooja Simulator:

bash-
cd ~/contiki-ng/tools/cooja
ant run

Load Simulation File:

Go to File → Open Simulation

Select:
bash
simulations/weather_station.csc

Start the Simulation:
Press the green play button in Cooja.

3️⃣ Observe Output
Sensor Nodes will log messages like:
[INFO: SensorNode] Sending message: Temp: 27, Hum: 62

Base Station will log received packets:
[INFO: BaseStation] Received from [fe80::212:7401:1:101]: Temp: 27, Hum: 62
