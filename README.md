#Wavelogger
The Wavelogger hardware is based around the ATMEGA line of Atmel processors, a MicroSD card, and a stackable I2C bus that allows alternate power regulation and analog front ends to be used.  There are four circular printed circuit boards, each 1.2 inches in diameter; a CPU/MicroSD board, a power regulation and temperature sensing board, an analog and digital IO board, and an analog signal conditioning board.  There is an additional board that contains a USB to RS232 converter that allows the hardware stack to interface with a computer and be powered by the computer.  This allows the stack to be used as a connected data gathering device in the lab.

The software is written in C for the firmware and C++/Python for the analysis software on the host.

The firmware has a simple operating system for the ATMEGA that contains block device drivers for the MicroSD card and it's partitions.  These device drivers are used to implement a FAT16 file system.  There are also timer drivers to run the sampler and serial drivers for the I2C bus and the RS232 connection to the host.

The PC side analysis software consists of a processor that takes the binary data files and generates CSV files from segments of the data with minimal processing, and a Python GUI that can render a stripchart with realtime data from each sampling channel.
