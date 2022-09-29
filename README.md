# KB Smart Home Automation Using NodeMCU

In this IoT project, you control any electrical appliances with the help of Google assistant & Amazon's Alexa.
I have written the code in a way so that if Internet/Wi-Fi gets disconnected or not available, and the relay control from Web Page, IR Remote will go on independent of Wi-Fi.
A lot of commercial devices already exist in the market for such application but, I wanted to have my own simple and low-cost device and it’s always fun to learn new things. :)

<br />



**Features**

- Control over Internet from anywhere in the world
- Voice Control using Google Assistant & Alexa
- Control from Blynk App
- Control from IR remote
-	Control over Web Page
-	Save the switch state even after micro controller restarts.

<br />

**If you lose Internet Connection**
- You won't be able to control over internet and from Blynk, Google Assistant and Alexa.
- Web Page and IR Remote will work.	

**If you lose Wi-Fi Connection**
- Only IR Remote will work.
- Internet and Wi-Fi connection will be restored automatically if disconnected.

<br />


**Things you need**
1.	Internet Connection
2.	Smart Phone
3.	Arduino IDE on your computer
4.	NodeMCU ESP8266 Wi-Fi
5.	AC To DC 5V Buck Converter (or any 5V AC to DC Charger)
6.	3Pins IR Receiver
7.	8 Channel Relay Module
8.	Jumper Wires
9.	IR Remote (Optional)

<br />

**Installation**
<img src="https://user-images.githubusercontent.com/23693439/118782890-fbe3ed80-b8a7-11eb-8187-d3ce7302f683.gif" />

<h2> Homebridge To Google Home App</h2>
<p><strong>You should only add the Homebridge Action once you have configured the homebridge-gsh plugin and restarted your instance.</strong></p>
<h3>

</a>Step 1: Add A New Device</h3>
<p>From the Google Home app, click the Add button:</p>
<table>

 <tr>
   <td style="text-align:center;">
   <img width="230" src="https://user-images.githubusercontent.com/23693439/118789007-c510d600-b8ad-11eb-9fce-ce0899bd2edd.png">
   </td>
   
   <td>
   <img width="230" src="https://user-images.githubusercontent.com/23693439/118789009-c5a96c80-b8ad-11eb-8f00-f4587d7f34cd.png">
   </td>
   
   <td>
   <img width="230" src="https://user-images.githubusercontent.com/23693439/118789000-c3dfa900-b8ad-11eb-8b13-ba787c9e2292.png">
   </td>
  
 </tr>
</table>

<h3>
  Step 2: Add The Homebridge Action</h3>

  <table>
  <tr>
   <td style="text-align:center;">
   <img width="230" src="https://user-images.githubusercontent.com/23693439/118789360-220c8c00-b8ae-11eb-8ab0-a1fe69c662be.png">
   </td>
   <td>
   <img width="230" src="https://user-images.githubusercontent.com/23693439/118789353-20db5f00-b8ae-11eb-85f8-60608d2573c5.png">
   </td>
 </tr>
</table>

<br>








_________________________________________
#### Creating and maintaining project consume a lot of time and effort, if you would like to share your appreciation, feel free to "Star". 

_________________________________________
