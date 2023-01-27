## Using FreeRTOS with the Raspberry Pi Pico

Code samples from a blog series published on [Embedded Computing Design](https://embeddedcomputing.com/) covering various topics like environment setup, multitasking, queues, message buffers, semaphores, event-driven design, and symmetric multiprocessing (SMP). 

[Part 1](https://embeddedcomputing.com/technology/open-source/linux-freertos-related/using-freertos-with-the-raspberry-pi-pico) | 
[Part 2](https://embeddedcomputing.com/technology/open-source/linux-freertos-related/using-freertos-with-the-raspberry-pi-pico-part-2) | 
[Part 3](https://embeddedcomputing.com/technology/open-source/linux-freertos-related/using-freertos-with-the-raspberry-pi-pico-part-3) | 
[Part 4](https://embeddedcomputing.com/technology/open-source/linux-freertos-related/using-freertos-with-the-raspberry-pi-pico-part-4)

### Setup and Instructions

Setup and instructions differ slightly from Part 1 in the blog series. The blog series uses the project name "blink" whereas this repo uses "app" as the project name.

#### Windows
* Install Git (includes Bash terminal): https://git-scm.com/downloads
* Install CMake: https://cmake.org/download/
* Install the Arm GNU Toolchain: https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain
* Install Make and MinGW using Chocolatey
  * Chocolatey should already be installed from the Git install, otherwise install it: https://chocolatey.org/
  * Run these commands from an Administrator Command Prompt:
  
    `$ choco install make`
    
    `$ choco install mingw`

#### Linux
All the tools we need, including Git and Make, should be available after installing these packages:

`$ sudo apt install cmake`

`$ sudo apt install gcc-arm-none-eabi`

`$ sudo apt install build-essential`

#### MacOS
For MacOS, ensure that Homebrew is installed and then follow these steps in the Terminal:

`$ brew install cmake`

`$ brew tap ArmMbed/homebrew-formulae`

`$ brew install arm-none-eabi-gcc`

Once you have completed the OS-specific setup, launch your terminal (Git Bash on Windows) and complete the steps below to setup the project from the command line:

`$ mkdir Projects` (or whatever container folder suits you)

`$ cd Projects`

`$ git clone https://github.com/RaspberryPi/pico-sdk --recurse-submodules`

`$ git clone -b smp https://github.com/FreeRTOS/FreeRTOS-Kernel --recurse-submodules`

`$ export PICO_SDK_PATH=$PWD/pico-sdk`

`$ export FREERTOS_KERNEL_PATH=$PWD/FreeRTOS-Kernel`

`$ git clone https://github.com/aws-iot-builder-tools/freertos-pi-pico`

### Building the Project

`$ cd freertos-pi-pico/app`

`$ mkdir build`

`$ cd build`

`$ cp ../main1.c ../main.c` (or whichever sample file you wish to build)

For Windows only:

`$ cmake -G "MinGW Makefiles" ..`

For Linux or MacOS:

`$ cmake ..`

Finally, from any environment:

`$ make`

### Flashing the Pi Pico

Once the project successfully builds, there should now be a ‘app.uf2’ in the ‘build’ directory. This file is the binary we will flash to the Pico. 

In order to flash this file, first hold down the BOOTSEL button on the Pico board while plugging it in to the USB interface. This will mount the Pico as a drive. 

Then, copy the ‘app.uf2’ file to the drive location and the Pico will automatically reboot and run the application. For example, if your drive location is D:, here is how to copy from the command line:

`$ cp app.uf2 /d/`

## Security

See [CONTRIBUTING](CONTRIBUTING.md#security-issue-notifications) for more information.

## License

This library is licensed under the MIT-0 License. See the LICENSE file.

