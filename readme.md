<!-- PROJECT LOGO -->
<p align="center">
  <h3 align="center">WinSerial</h3>

  <p align="center">
    This is a PC sided companion to the ESP Power Button Project.
    <a href="https://www.youtube.com/watch?v=Uo5vbjHSwwY">Watch The Video</a>
    <a href="https://github.com/LiveSparks/ESP_Power_Button">ESP Power Button GitHub</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#build">Build</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a>
        <ul>
            <li><a href="#run-on-start-up">Run on start-up</a></li>
        </ul>
    </li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project
<div align="center">
  <a href="https://www.youtube.com/watch?v=Uo5vbjHSwwY"><img src="https://img.youtube.com/vi/Uo5vbjHSwwY/0.jpg" alt="YouTube"></a>
</div>

This is a companion app to the [ESP Power Button](https://github.com/LiveSparks/ESP_Power_Button) Project. This program runs in background on your PC and does two things:

* Provide System stats to the ESP over serial.
* Receive Button Presses from the ESP over serial and coonvert them to key presses.

You can modify the project to add more system stats to send or receive a wider range of key presses if you wish.

Download the compiled and ready to run binary from the [releases](https://github.com/LiveSparks/WinSerial/releases) page.

Data sent over serial is in the following format:
```cpp
"SYSSTATS:%d\t%d\t%d\n",cpuPer,memPer,dskPer
```


### Built With
* [PlatformIO](https://platformio.org/)
* [MinGW](http://mingw-w64.org/)



<!-- GETTING STARTED -->
## Getting Started

If you wish to run to project as is than download the latest "LS_Keyboad_Wedge.exe" from the [releases](https://github.com/LiveSparks/WinSerial/releases) page. See the [Usage](#usage) section on how to run it.
**OR**
If you wish to make some changes to the code then follow these steps:

### Prerequisites

Setup [VSCode](https://code.visualstudio.com/download) for compiling with MinGW from the instruction provided [here](https://code.visualstudio.com/docs/cpp/config-mingw).

### Build

1. Clone/Download the repo
   ```sh
   git clone https://github.com/LiveSparks/WinSerial
   ```
2. Setting up tasks.json
    * Before opening the project in VSCode, go into the .vscode folder and rename `tasks.json` to `tasks.json.bak`
    * Open the root folder in vs code and create a new `tasks.json` file by following the instructions [here](https://code.visualstudio.com/docs/cpp/config-mingw#_build-helloworldcpp).
    * Now open the new `tasks.json` file and modify the value of `"args":` variable to look like this:
    ```json
    "args": [
				"-mwindows",	// Comment-out this to see a command prompt when the program is run.
				"-g",
				"${workspaceFolder}\\*.cpp",
				"-o",
				"${fileDirname}\\LS_Keyboard_Wedge.exe",
				"-l",
				"pdh",
				"-static",
				"-static-libgcc",
				"-static-libstdc++"
			],
    ```
3. Compiling
    You can now compile the program with the keyboard shortcut `Ctrl+Shift+B`.

**NOTE:** By Default the NO window opens up when you run the program. To kill the program, you have to do so from the Task Manager. If you want a console window to appear comment out the `-mwindows` line in your `tasks.json` file.

<!-- USAGE EXAMPLES -->
## Usage

1. DO NOT run the file as is.
2. Search and open up device manager.
3. Expand `Ports(COM & PLT)`.
4. Plug in the ESP that is running the ESP Power Button Sketch.
5. Note down the new COM port that appears.
6. Open the folder that contains the LS_Keyboard_Wedge.exe file.
7. `Shift+Right Click` in this folder and click on "Open PowerShell Window here" **OR** you can type "cmd" in the top address bar to open a command prompt.
8. Inside the terminal, run the following:
    ```sh
    LS_Keyboard_Wedge.exe COM1
    ```
    Replace `COM1` with whatever COM port you noted down in step 5.
9. No new window will open up. If no error pops up and it looks like nothing is happening than the program is running successfully in the background.
10. To kill the program open up task manager and search for `LS_Keyboard_Wedge.exe`. It might be under a dropdown of `Windows Command Processor`. Select it and click "End Task".

### Run on start-up
If you want to run the programm automatically on boot-up. Make sure that the ESP is always connected to the same USB Port.
1. Right click on the `.exe` file and click `Create shortcut`.
2. Right click on the shortcut and open up properties.
3. Modify the value in the Target text box to include the COM port of your ESP at the end. Example:
    ```sh
    C:\Users\RaviK\Documents\Projects\WinSerial\LS_Keyboard_Wedge.exe COM12
    ```
4. Click OK to save and cut/copy the shortcut.
5. Press `Win+R` and type `shell:startup`.
6. Paste the shortcut in the window that appears. The Program should now run automatically on every reboot.


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License.



<!-- CONTACT -->
## Contact

Your Name - [@LiveSparksYT](https://twitter.com/LiveSparksYT) - livesparking@gmail.com

Project Link: [https://github.com/LiveSparks/WinSerial](https://github.com/LiveSparks/WinSerial)