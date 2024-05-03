# VST-Synth
A synthesizer written using Steinberg's VST3 SDK.

## Info
VST3 programs are repackaged DLL files intended for use in digital audio workstations (DAWs). Steinberg's VST3 SDK allows for developers to create such programs and ensure they are compatable through the use of built-in tools. This program is an attempt to use this SDK.
## Setting Up
1. Install CMake from https://cmake.org/ and Visual Studio 2022. These are required to build the ```Synth.sln``` file.
2. Install VST3 SDK from https://www.steinberg.net/vst3sdk. More information regarding this can be found [here](https://steinbergmedia.github.io/vst3_dev_portal/pages/Getting+Started/Links.html).
3. Clone this repository using ```git clone https://github.com/ShotgunApe/VST-Synth.git```.
## Compiling
1. Build the SDK using CMake. This can be done using CMake-GUI, and instructions for doing so can be found [here](https://steinbergmedia.github.io/vst3_dev_portal/pages/Tutorials/Building+the+examples/Building+the+examples+included+in+the+SDK+Windows.html).

Alternatively, command line can be used by first creating the build folder in ```../VST_SDK/vst3sdk/``` with:
```
mkdir build
cd build
```
and
```
cmake.exe -G "Visual Studio 17 2022" -A x64 ../vst3sdk-DSMTG_CREATE_PLUGIN_LINK=0
```
2. Generate the project solution file ```Synth.sln``` by navigating to ```../code/synth/```, creating the build folder, and using CMake in a similar manner above.
**CMakeLists.txt must be changed to where you installed the SDK. By default it uses ```Q:/VST_SDK/vst3sdk```.**

Should one use CMake-GUI for this as well, the project file should look like:
![CMake-GUI](https://i.imgur.com/RXWMDb1.png)

3. Open ```Synth.sln``` with Visual Studio 2022.
