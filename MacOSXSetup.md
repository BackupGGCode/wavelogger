# Introduction #

There are a number of tools that need to be installed on OS X in order to build and use the Wavelogger and its associated tools.  There are three major categories of tools that are required.  First, tools needed to build the firmware and flash the device.  Second, tools that are needed to build the data processing code on a desktop.  And finally, tools that are needed to communicate with the Wavelogger for calibration and initial setup.  There are also some fundamental development tools that must be installed for all setups.

All of these steps assume that you are using the built in terminal program on OS X.  You can find the terminal program in Applications/Utilities/Terminal.

# Mac OS X Development Tools #

First, XCode and MacPorts need to be installed.  XCode can be downloaded from http://developer.apple.com/technology/xcode.html.  Make sure you get a version of XCode that is compatible with your version of OS X.  MacPorts can be downloaded from http://www.macports.org/.

Along with the above tools you should install gmake as the make that comes with older versions of XCode has some bugs that the Wavelogger makefiles hit.  You can do that with:

  * `sudo port install gmake`

And finally, you'll want to install subversion so that you can check out a copy of the Wavelogger source files.  Subversion can be installed with:

  * `sudo port install subversion`

Once you have those tools you can checkout the Wavelogger source files.  That can be done with:

  * `svn checkout http://wavelogger.googlecode.com/svn/trunk/ wavelogger`

This will check out all of the files needed to build and use the wavelogger.  The files will be placed in a directory called `wavelogger` in the current directory.

# FirmwareTools #

To build the download the firmware you need to install a number of ports from MacPorts.  The latest version of avr-gcc that is in the MacPorts repository does not support the CPU on the main sampling board so you won't actually be able to build the firmware on OS X currently.  I imagine that a new version will be updated soon.  The command lines, for future reference, are:

  * `sudo port install avrdude`
  * `sudo port install avr-gcc`
  * `sudo port install avr-libc`

From the wavelogger directory you can build the firmware by typing `gmake`.

# DesktopTools #

The base install of OS X development tools satisfies the requirements for building the desktop tools.

From the tools directory you can build the desktop tools by typing `gmake`.  If you previously built the firmware the desktop tools will already be built.

Once the tools have been built you can run the `process` program from the `wavelogger/tools/process` directory with the following command:

  * `./release/process`

This will give you the usage output for `process`.

# CommunicationTools #

There are a number of ways to communicate with the Wavelogger.  You can use a general serial terminal program, such as CuteCom.  You can use the stripchart program found in wavelogger/tools/stripchart.  Or you can use the builtin `screen` command.  Either way you will need to install the USB Serial drivers from FTDI.  These drivers can be found here: http://www.ftdichip.com/Drivers/VCP.htm.

Once the FTDI driver has been installed and your computer rebooted, you will be able to communicate with the Wavelogger.  The FTDI drivers create a device file in the `/dev` directory for the USB connected Wavelogger.  The file will be called `/dev/tty.usbserial-<ID>`, where `<ID>` is a unique serial number for each Wavelogger.

## Screen ##

You can test the Wavelogger and USB serial driver with the following command:

  * `screen /dev/tty.usbserial-<ID> 57600`

Make sure you replace `<ID>` with the correct unique identifier.  This command will allow you to communicate with the Wavelogger.  You can use exit the screen program with `<ctrl>A <ctrl>\`.

## CuteCom ##

To install CuteCom you will need the CuteCom source code.  It can be downloaded here: http://cutecom.sourceforge.net/.  You will also need to install the QT development libraries and cmake before you can build and use CuteCom.  Installing qt4-mac-devel can take a very long time.  That can be done with:

  * `sudo port install qt4-mac-devel`
  * `sudo port install cmake`

In order to build CuteCom you need to make a small change to the cmake configuration files.  The version of qt4 that was installed creates a qmake-mac instead of qmake executable, and this confuses cmake.  This can be fixed by editing the part of cmake that finds qmake.

  * `sudo nano /opt/local/share/cmake-2.6/Modules/FindQt4.cmake`

Once you have the file opened you should add qmake-mac to the list of qmakes that are searched for.  That list is on line 339.  Put qmake-mac right after qmake-qt4.

You will also need to unpackage the source code you downloaded for CuteCom.  You can do this with the following command:

  * `tar xvf ~/Downloads/cutecom-0.22.0.tar`

That will unpackage the CuteCom source code into a directory called cutecom-0.22.0 in your current directory.

Once everything is installed and patched you can build CuteCom from the cutecom-0.22.0 directory by typing:

  * `cmake .`
  * `make`
  * `sudo make install`

You can then find CuteCom in the Applications folder in the Finder.  You can find out more about using CuteCom from the CuteCom page.

## Stripchart ##

To use the stripchart program you need to install python and a number of python libraries.  That can be done with the following commands:

  * `sudo port install py25-serial`
  * `sudo port install py25-wxpython`
  * `sudo port install py25-opengl`

You can run stripchart with the following command in the wavelogger/tools/stripchart directory:

  * `python2.5 stripchart`