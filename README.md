# Arduino Webpanel
This webpanel is created to access and control multiple sensors from one interface. The webserver is designed to run on an Arduino-ESP8266-Board and trigger other ESP8266 servers. The webpage is designed to run on mobile devices. To get the best experience, try to use the progressive webapp. The filesystem LittleFS is used for storing and streaming the webserver files.

Further informations of the used [LittleFS - Filesystem](https://github.com/earlephilhower/arduino-esp8266littlefs-plugin/).

# Requirements
- 2 x ESP8266 Arduino Boards
- Sensor/Relay to get triggered
- LittleFS Data Uploader

# Functionalities
<img align="right" border="2px" src="https://media.giphy.com/media/L3oiSAxIGtFkT5pFhj/giphy.gif" style="border-color:Gray; border:2px; border-style:solid; border-radius:2px;">

The gif tries to show every functionality. Down below is a short and long version of the features.

__Short__

- progressive webapp integration
- unlimited items
- automatic statuscheck on startup
- switch toggles offline if sensor cant be reached

__Long__

You can add the webpage as a progressive webapp to the homescreen of your phone. The gif shows you a short introduction (on android with chrome). The webapp comes with its own icon and flash-screen and behaves kind of as an app.

If you want to, you can add as many items to your panel as you want. Just be sure to add the IP/DNS to the "ID" of the object in the html container.

If you try to toggle a device that does not respond, the script aborts after 2 seconds and resets the toggled switch to the offline state.

On startup of the webpage the javascript checks every sensorstate and sets the toggle-switches to the right state.

If you toggle a device that does not respond, the switch will change to offline after 2 seconds. The status is collected with a 'GET'-Request. To switch a state the 'POST'-Request is used.

# Custom additions
If you want a frequent status check just add an recursive call to the getReques()-function. But keep in mind that you are adressing a tiny webserver and keep the refresh-rate low. With multiple active clients your webserver could suffer performance real quick.

If you want to change the name/color/icon etc. of the progressive webapp, just customize the [manifest.webmanifest](/managementServer/data/manifest.webmanifest) and change the image in the [data](/managementServer/data/) folder.

# Setup guide
Make sure you select the right board, port etc. in your ArduinoIDE

1) Clone/download this repository to your workstation
2) Setup your ArduinoIDE with the littleFS-Data uploader
    - Download [ESP8266LittleFS-x.x.x.zip](https://github.com/earlephilhower/arduino-esp8266littlefs-plugin/releases)
    - unzip and copy folder to %arduinoIDE%/tools/
    - start/restart ArduinoIDE
3) Change the IP-Adresses, names etc. in the [index.html](/managementServer/data/index.html)
    - delete the objects you dont need
    - make sure to set the right ips which you later want to flash to your "switchservers"

4) (ESP8266 No.1) Open the [managementServer.ino](/managementServer/managementServer.ino) sketch 
    - change the IP-configurations and your wifi credentials
    - Upload the data - "Tools" --> "ESP8266 LittleFS Data Upload"
    - After uploading the data, upload the sketch
    - you should be able to access your webpanel now
5) (ESP8266 No.2) Open the [sensorServer.ino](/sensorServer/SensorServer.ino) sketch
   - set the wifi parameters - make sure to use the ip you used in the [index.html](/managementServer/data/index.html)
   - setup your switch/relay - there are comments in the code to guide you
   - upload the sketch to your arduino
   - test your completed setup

If you want to use the the progressive webapp, try to follow the animation.  
