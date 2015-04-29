# Storage Capacity #

Micro SD cards are a very cheap form of mass storage for a data logger.  The wavelogger records two 10-bit channels at a 100Hz sample rate.  It records a full 512 byte block of data to the micro SD card every two seconds.  A 2 gigabyte memory card can store about `(2^31) / (2^9)`, or `2^22`, or 4 mega blocks of data.  Some of these blocks will be used by the FAT file system, and some will be used by the configuration and metadata files that the wavelogger requires.  Say you only end up with 4 million blocks (`4 * 10^6`, instead of `2^22`).  Then you can store 8 million seconds of data.  That's over 90 days of data.

# Files #

There are three files that need to be placed on the SD card.  The first is a configuration file that specifies what other files the wavelogger should look for, and what values to use for channel gains.

The second is a file called metadata.dat that tells the wavelogger how much it has recorded, and whether it should start recording right away, or wait for the operator to start recording by placing a magnet beside the device.

The third is the actual data file.  It is called wavedata.dat and is initialized to all zeros.  This is required because the the wavelogger firmware cannot create or expand files.  So we have to make it one beforehand that it'll fill in.

# Commands to Create the Files for Deployment #

These commands should be executed from a terminal in the SDCards top level directory.  This directory is probably something like "/Volumnes/NO NAME" on Mac OS X and "/media/disk" on Linux.  The number format `\0xxx` is a way of inserting raw bytes into the files.  The numbers are base 8, or octal.  So \0377 is the same as 255 which is the same as 0xff in hexadecimal.  \0144 is the same as 100, and \0363 is the same as 243.

`echo -n -e "\0377\0377\0377\0377" > metadata.dat`

`echo -n -e "wavedata.dat\0000" > config.dat` <br>
<code>echo -n -e "metadata.dat\0000" &gt;&gt; config.dat</code> <br>
<code>echo -n -e "\0000\0144" &gt;&gt; config.dat</code> <br>
<code>echo -n -e "\0363" &gt;&gt; config.dat</code>

<code>dd if=/dev/zero of=wavedata.dat bs=512 count=3800000</code>

The third line that writes to the config.dat file above sets the number of samples per second to record.  Currently that value is ignored and the Wavelogger always records 100 samples per second.  The fourth line sets the gain to use while recording.  A value of \0363 (243 in decimal) sets the gain to about 50.  More detail on the setting of the gain value can be found on the WaveloggerShell page.  The count value of 3800000 above will fit in a two gigabyte SDCard, but won't fit in a one gigabyte card.  A value of 1900000 will though.  The <code>dd</code> command will take a minute or two, depending on the speed of your SDCard reader and SDCard.<br>
<br>
<h1>Commands to Create the Files for Current Measurement</h1>

When measuring the current consumption of the Wavelogger there are a couple of things you can do differently.  Firstly, you probably don't want the Wavelogger to wait for you to activate it with a magnet.  To do this we write 0 instead of 0xffffffff to the metadata.dat file.  Also, you probably don't need to have such a large wavedata.dat file.  The commands to generate this version of the required files are:<br>
<br>
<code>echo -n -e "\0000\0000\0000\0000" &gt; metadata.dat</code>

<code>echo -n -e "wavedata.dat\0000" &gt; config.dat</code> <br>
<code>echo -n -e "metadata.dat\0000" &gt;&gt; config.dat</code> <br>
<code>echo -n -e "\0000\0144" &gt;&gt; config.dat</code> <br>
<code>echo -n -e "\0363" &gt;&gt; config.dat</code>

<code>dd if=/dev/zero of=wavedata.dat bs=512 count=3600</code>

The wavedata.dat file created can store 2 hours of data, plenty of time to test out SDCards.