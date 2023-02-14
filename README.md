
# IoT Based Home Automation Solution | Emertxe Internship

Simulates the home automation system on the PICSIMLAB simulator and uses the Blynk IoT application to control the devices. Also, controls the lights, temperature of the home, inflow and outflow of water in the water tank.

> ## Components
 ![comp](https://user-images.githubusercontent.com/97796804/218394172-2e64b3ee-ae22-42d7-9ee7-bfe7b7b8473a.JPG)

> ## Business Benifits
**(a) Saves Energy:**

By turning ON and OFF the equipment at the scheduled times, energy is saved.

**(b) Improved Security:**

Incorporating safety features on remote devices can get security alerts if needed.

**(c) Convenience Factor:**

Managing all the devices in one place improves efficiency to a great extent.

**(d) Insights from collected data:**

Provides valuable data from which one can manage one’s energy consumption.

> ## Connection Diagram
![cnxn](https://user-images.githubusercontent.com/97796804/218395858-1e1e4cc8-ea42-4d39-ab9b-cb98603b9938.JPG)

__(I) Garden Lights Control:__
> Based on the reading from LDR sensor, the brightness of the LED is varied, which resembles controlling the garden lights based on the availability of sunlight. LDR sensor has variable resistance where the resistance of the LDR is inversely proportional to voltage or light present. <br />
> _Pulse Width Modulation (PWM) is a technique used to achieve average voltages by varying the active time and inactive time in a fixed period_.<br />
<p align="center">
  <img width="400" src="https://user-images.githubusercontent.com/97796804/218396585-9942c6cb-f754-441c-b3d1-73476a126aa0.JPG">
</p>

__(II) Temperature Control System:__
> \+ The temperature control system consists of a _heating resistor, an LM35 temperature sensor, and a cooler._ The temperature is read from the sensor and displayed on CLCD and gauge widget. <br />
> \+ The temperature of system is controlled by turning ON/OFF the heater and cooler through the _Blynk IOT mobile app._ Also, the temperature is compared against a threshold value of 35°C, if temperature exceeds the value, the heater is turned OFF and the notification is displayed in the app and CLCD.<br />
<p align="center">
  <img width="400" src="https://user-images.githubusercontent.com/97796804/218398835-f88bd6cb-0848-4539-ae5a-76280f826636.JPG">
</p>

__(III) Water Tank Control:__
> \+ The volume of water in the tank is read through Serial Communication interface and it is displayed on the CLCD and gauge widget. It is controlled by controlling the inlet and outlet valve by sending commands through serial communication interface. <br />
> \+ The inlet valve and outlet valve is controlled through the _Blynk IoT app_ by turning ON/OFF the inlet/ outlet valve button. Also, the volume is compared against a threshold value of 2000 ltrs, if volume is less than the value, the inlet valve is turned ON and the notification is displayed in the app and CLCD.<br />
<p align="center">
  <img width="400" src="https://user-images.githubusercontent.com/97796804/218399027-8412df3b-42bc-49a7-8efb-10004de775a3.JPG">
</p>

> ## App Screenshots
![shots](https://user-images.githubusercontent.com/97796804/218400839-1d8b1dbb-3e27-4c09-85ea-b0049fa8c73a.JPG)
