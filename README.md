# Welcome to Foundational Project 2025
EIG's Foundational Project is back for 2025 with a bang! Dive into a 3-week hands-on journey where you'll learn:

1. 3D Modelling in Fusion 360 (17 July)
2. ESP32 Programming (24 July)
3. Wireless Connectivity & Assembly (31 July)

With no prior experience needed, you too are able to build a laser pointer/game controller of your own with components we provide!
It's a valuable hands-on experience that can enrich your portfolio!

📍 Venue: ESC #08-03-02

🕠 Time: 4:30PM–7:00PM on 17, 24 and 31 July

🎯 Open to all SOE students & EIG members

## Files in this Github
- eig-fp-2025.ino is the code template we used in our workshops, note that it is **INCOMPLETE** with parts purposefully left out for participants to fill in.
- Solution.txt is the file which contains the code for the **COMPLETE** version of the code.
- README.md is just this bunch of text you're reading (hence readme), for those who have not touched GitHub before

For Solution.txt, you can toggle between two modes: Slides Clicker and Tetris (yes. tetris)
- To toggle Slides Clicker, uncomment lines 63 and 78 while commenting lines 64 and 79.
It will look like this:
```c++
// This is line 63 and 64
Keyboard.write(KEY_ESC); 
// Keyboard.write(' '); 

// And this is line 78 and 79
mouse(x_value, y_value);
// wasd(x_value, y_value);
```
- To toggle Tetris, uncomment lines 64 and 79 while commenting lines 63 and 78.
It will look like this:
```c++
// This is line 63 and 64
// Keyboard.write(KEY_ESC); 
Keyboard.write(' '); 

// And this is line 78 and 79
// mouse(x_value, y_value);
wasd(x_value, y_value);
```
Remember to upload your code to the ESP32, else its behaviour won't update

## Pre-Installation
1. [CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)
 - This is needed so that you can easily upload code onto your ESP32.  
2. [ESP32-BLE-Combo](https://github.com/ethanetexplorer/ESP32-BLE-Combo)
   
 - This library contains all the keyboard and mouse related functions that you will need for this workshop.

   **Installation Steps**
   
   a. Download the folders in [ESP32-BLE-Combo](https://github.com/ethanetexplorer/ESP32-BLE-Combo) as a zip file
   
   b. In Arduino IDE, go to the top menu bar, and add the library by Sketch -> Include Library -> Add .ZIP library


**Most importantly**, you need the [Arduino IDE](https://www.arduino.cc/en/software/). Make sure to download the correct version for your operating system!
- For Windows, please choose the (Windows 10 or newer, 64 bits) version.

## Examples
Examples and sample code can be found in this repository. Well - that's if I remember to update this with more examples lol (ethan), else it's just one single file.
