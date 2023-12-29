# illi Robot
## A compact programmable desktop robot

Watch the illi video: https://www.youtube.com/watch?v=qA74jBnlvLI

![de298807-1e43-4e8a-aacb-07bc80e611c2](https://github.com/cassio-hsp/illi/assets/38111232/43dd9743-0c51-4910-ab54-05e66cd5b1e9)


## This project integrates:
1. ESP32 Wemos Lolin Lite.
2. Dual Channel H Bridge MX1508
3. Four N20 Motors 500 RPM 6v.
4. Led sticks WS2812
5. Lithium Battery 18650.
6. Passive Buzzer
7. AMS1117-3.3 Voltage Regulator

![6f3e3a3b-c189-4cb9-83b0-b9c4cf363fd6](https://github.com/cassio-hsp/illi/assets/38111232/44ca9452-f09c-4d6a-b2d1-48b5c135ad09)
  
![illi-board](https://github.com/cassio-hsp/illi/assets/38111232/e9c04319-5a2a-4242-b593-b36cd923d8ba)

![a3a47e1d-7989-43e8-abf6-2358916360d3](https://github.com/cassio-hsp/illi/assets/38111232/3d253763-553d-4de6-8c7b-00fbae2b04f8)

## CAD Model

The chassis was manufactured under a personal use license from Fusion 360. It has three parts.

![illi1](https://github.com/cassio-hsp/illi/assets/38111232/86ba09ef-5c52-44b1-bbed-d3d01af795bb)

![illi2](https://github.com/cassio-hsp/illi/assets/38111232/68c9c109-258a-4bc2-927d-e5334d6f0071)

![illi5](https://github.com/cassio-hsp/illi/assets/38111232/e9e248cc-d94d-4ca3-bfed-9dcfcaf2557b)

## PCB 
The PCB is a main board that receives one microcontroller, the h bridge, a LDO 3.3v regulator and the headers. The fabrication files (fab.rar) is ready to upload on a company do manufacturing it (JLCPCB, eg.)

![illi-schematic](https://github.com/cassio-hsp/illi/assets/38111232/6f347280-a710-43ec-a061-724df1f1a508)

![pcb1](https://github.com/cassio-hsp/illi/assets/38111232/7edd37e5-0d3d-40af-a840-9216a17acebc)

![pcb2](https://github.com/cassio-hsp/illi/assets/38111232/eac1569e-5f03-434f-8548-c87c468008f7)


## Future desired functions:
* Oled Display Module.
* Built-in buzzer on PCB.
* Swarm control via MQTT.
* Webserver for bot control.
* Accelerometer control.
