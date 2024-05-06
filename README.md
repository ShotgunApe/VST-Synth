# VST-Synth
A synthesizer written using Steinberg's VST3 SDK.

## Info
VST3 programs are repackaged DLL files intended for use in digital audio workstations (DAWs). Steinberg's VST3 SDK allows for developers to create such programs and ensure they are compatable through the use of built-in tools. This program is an attempt to use this SDK.
## Setting Up
1. Install CMake from https://cmake.org/, ensuring that you add CMake to the system PATH.
2. Install Visual Studio 2022, as well as the "Desktop Development with C++" workload. These are required to run VS .sln files.
3. Download and extract the VST3 SDK from https://www.steinberg.net/vst3sdk into an easily accessable path, such as ```C:/VST_SDK/```. More information regarding this can be found [here](https://steinbergmedia.github.io/vst3_dev_portal/pages/Getting+Started/Links.html).
4. Install the VST3PluginTestHost located in ```../VST_SDK/vst3sdk/bin/Windows_x64/```. This is required to test VST3 files.
5. Clone this repository using ```git clone https://github.com/ShotgunApe/VST-Synth.git``` into a desired location *outside* of the SDK.
## Compiling
1. Prepare VST development by building the SDK using CMake. This can be done using CMake-GUI (instructions [here](https://steinbergmedia.github.io/vst3_dev_portal/pages/Tutorials/Building+the+examples/Building+the+examples+included+in+the+SDK+Windows.html)) OR by using CMake in the command line.
First create the build folder in ```../VST_SDK/``` with:
```
mkdir build
cd build
```
Next, from the VST_SDK folder, run the following command to build the SDK:
```
cmake.exe -G "Visual Studio 17 2022" -A x64 -B build -S vst3sdk -DSMTG_CREATE_PLUGIN_LINK=0
```
If successful, this will generate a .sln file which can view each example included in the SDK. If the error ```CMake Error: Could not create named generator Visual Studio 17 2022``` occurs, ensure that you are using the latest version of CMake.

2. Generate the project solution file ```Synth.sln``` in the github repo. Navigate to ```VST-Synth-main/code/``` and create the build folder, then use CMake again in a similar manner above:
```
cmake.exe -G "Visual Studio 17 2022" -A x64 -B build -S Synth -DSMTG_CREATE_PLUGIN_LINK=0
```
**NOTE: CMakeLists.txt must be changed to where you installed the SDK. By default it uses ```Q:/VST_SDK/vst3sdk```.**

3. Open ```Synth.sln``` with Visual Studio 2022.

## Solution Properties
```Synth.sln``` contains two solution configurations, ```Debug``` and ```Release```. When started, both launch the Synth via the VST3PluginTestHost, but using ```Debug``` allows for changes to be made to the UI. 

When launching, Post-Build Events may cause the error [MSB3073](https://learn.microsoft.com/en-us/visualstudio/msbuild/errors/msb3073?view=vs-2022&f1url=%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(MSBuild.Exec.CommandFailed)%26rd%3Dtrue) if symbolic links are not configured for use in Windows. These can be ignored as our .vst3 file is still built. We can disable this script by going to the Solution Explorer and selecting:
```
Synth >> Properties >> Configuration Properties >> Build Events >> Post-Build Event >> Use In Build >> No
```
## WIP and Current State
Currently, this synthesizer supports monophonic sine waves and a custom UI. 
