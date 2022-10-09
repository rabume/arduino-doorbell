# Arduino Doorbell

### Hardware
- Arduino Uno
- Adafruit Bluefruit LE Shield Bluetooth
- Some wires
- Button

### Dependencies
Add "Adafruit BluefruitLE nRF51" over the libary manager in the Arduino IDE
https://github.com/adafruit/Adafruit_BluefruitLE_nRF51

Same for the libary "ezButton"
https://github.com/ArduinoGetStarted/button

### Registry path
`Computer\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\AppKey\18`

Create a new entry with the type of "string value" and call it "ShellExecute".
This new value should contain the command which should be executed when the 
bell is pressed. In our case a powershell script. Example:

`mshta vbscript:Execute("CreateObject(""Wscript.Shell"").Run ""powershell -NoLogo -noninteractive -Command """"& 'M:\scripts\notify.ps1'"""""", 0 : window.close")`