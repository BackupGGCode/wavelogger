# Introduction #

CuteCom is a simple serial terminal emulator.  It allows you to talk to serial devices and record logs of the communications.

# Usage #

CuteComs GUI allows you to select the serial port and port parameters you wish to use.  It also lets you log a copy of the session to a file.  I have found that you need to enable logging before opening the device, otherwise the log ends up empty.  Also, once you are done with your session, quitting CuteCom seems to be the trigger to write the log file to disc.  So the steps to use it to log a session are:

  1. Run CuteCom
  1. Configure port and port parameters
  1. Open device
  1. Enable logging (select check box next to "Log to:"
  1. Communicate with Wavelogger
  1. Close device
  1. Quit CuteCom

All of the above steps may not be required, but I have verified that these steps do work in this order.  The port and port parameters for the wavelogger are:

  * `device.....: /dev/tty.usbserial-<ID> or /dev/ttyUSB0`
  * `parity.....: none`
  * `baud rate..: 57600`
  * `data bits..: 8`
  * `stop bits..: 1`
  * `handshake..: none`
  * `open for...: reading and writing`

Furthermore, If you have trouble communicating with the wavelogger, try setting the character delay parameter in the lower right corner to 0ms.  You can figure out what the device file should be by typing `ls /dev/tty*` in a terminal.  On OS X it will be something like `/dev/tty.usbserial-<ID>` where `<ID>` is a unique 8 digit serial number.  On Linux it will be `/dev/ttyUSB0`.  It might be `/dev/ttyUSB1` or similar if you have multiple USB-serial adapters connected to your system.