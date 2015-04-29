# Introduction #

There are a number of tools that need to be installed in order to build and use the Wavelogger and its associated tools.  There are three major categories of tools that are required.  First, tools needed to build the firmware and flash the device.  Second, tools that are needed to build the data processing code on a desktop.  And finally, tools that are needed to communicate with the Wavelogger for calibration and initial setup.  There are also some fundamental development tools that must be installed for all setups.

All of these steps assume that you are using the built in terminal.  It can be found in Applications->Accessories->Terminal.

# Linux Development Tools #

The basic development tools can be installed with the following commands:

  * `sudo apt-get install make`
  * `sudo apt-get install g++`
  * `sudo apt-get install gcc-4.1`

And finally, you'll want to install subversion so that you can check out a copy of the Wavelogger source files.  Subversion can be installed with:

  * `sudo apt-get install subversion`

Once you have those tools you can checkout the Wavelogger source files.  That can be done with:

  * `svn checkout http://wavelogger.googlecode.com/svn/trunk/ wavelogger`

This will check out all of the files needed to build and use the wavelogger.  The files will be placed in a directory called `wavelogger` in the current directory.

# FirmwareTools #

To build the download the firmware you need to install a number of packages.  The command lines are:

  * `sudo apt-get install avrdude`
  * `sudo apt-get install gcc-avr`
  * `sudo apt-get install avr-libc`

From the wavelogger directory you can build the firmware by typing `make`.

# DesktopTools #

The base install of the development tools satisfies the requirements for building the desktop tools.

From the tools directory you can build the desktop tools by typing `make`.  If you previously built the firmware the desktop tools will already be built.

Once the tools have been built you can run the `process` program from the `wavelogger/tools/process` directory with the following command:

  * `./release/process`

This will give you the usage output for `process`.

# CommunicationTools #

There are a number of ways to communicate with the Wavelogger.  You can use a general serial terminal program, such as CuteCom.  You can use the stripchart program found in wavelogger/tools/stripchart.  Or you can use the builtin `screen` command.

The Wavelogger will show up as a device file called `/dev/ttyUSB0`, assuming that you have no other USB serial devices attached to your computer.

## Screen ##

You can test the Wavelogger and USB serial connection with the following command:

  * `screen /dev/ttyUSB0 57600`

This command will allow you to communicate with the Wavelogger.  You can exit the screen program with `<ctrl>a \`.

## CuteCom ##

CuteCom can be installed using:

  * `sudo apt-get install cutecom`

## Stripchart ##

To use the stripchart program you need to install python and a number of python libraries.  That can be done with the following commands:

  * `sudo apt-get install python-serial`
  * `sudo apt-get install python-wxversion`
  * `sudo apt-get install python-opengl`

You can run stripchart with the following command in the wavelogger/tools/stripchart directory:

  * `./stripchart`