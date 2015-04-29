# Introduction #

There are two ways to debug a problem with the Wavelogger.  The first is to note the sequence of LED's that are flashing over and over again.  The table of LED flashes and possible problems is below.

The second is to restart the Wavelogger with the USB disc attached.  Then when the failure happens you can hit return a couple times in CuteCom or whatever serial console you are using and in a few seconds the Wavelogger will print out an error stack that can be used as a guide through the source code.  You can also use the shell at that point to view the contents of the file system and test individual pieces of the hardware.

# Details #

| **One** | **Two** | **Problem** |
|:--------|:--------|:------------|
| 1 | 0 | LED device driver failed to boot. |
| 1 | 1 | Serial device driver failed to boot. |
| 1 | 2 | Cylinder device driver failed to boot. |
| 1 | 3 | TWI device driver failed to boot. |
| 1 | 4 | Gain device driver failed to boot. |
| 1 | 5 | DAC device driver failed to boot. |
| 1 | 6 | ADC device driver failed to boot. <br> Is the A/D board missing from the stack? <br>
<tr><td> 1 </td><td> 7 </td><td> Analog device driver failed to boot. </td></tr>
<tr><td> 1 </td><td> 8 </td><td> SPI device driver failed to boot. </td></tr>
<tr><td> 1 </td><td> 9 </td><td> SDCard device driver failed to boot. <br> Is the SDCard missing? </td></tr>
<tr><td> 1 </td><td> 10 </td><td> FileSystem failed to boot. <br> Is the SDCard formatted with the FAT file system? </td></tr>
<tr><td> 2 </td><td> 1 </td><td> Failed to read config.dat file from SDCard. <br> Have you created the needed files on the SDCard? </td></tr>
<tr><td> 2 </td><td> 2 </td><td> Failed to open metadata file from SDCard. <br> Have you created the needed files on the SDCard? </td></tr>
<tr><td> 2 </td><td> 3 </td><td> Failed to open wavedata file from SDCard. <br> Have you created the needed files on the SDCard? </td></tr>
<tr><td> 3 </td><td> 1 </td><td> Failed to set gain of amplifiers. </td></tr>
<tr><td> 3 </td><td> 2 </td><td> Failed to read current file position from metadata file. <br> Is the metadata file empty? </td></tr>
<tr><td> 3 </td><td> 3 </td><td> Failed to seek to end of wavedata file. <br> Is the metadata file corrupt, it may have an invalid length in it, try rewriting all of the files on the SDCard. </td></tr>
<tr><td> 3 </td><td> 4 </td><td> Failed to perform auto-zeroing procedure. </td></tr>
<tr><td> 3 </td><td> 5 </td><td> Failed to write auto-zeroing results to wavedata file. <br> Is the wavedata file full? </td></tr>
<tr><td> 3 </td><td> 6 </td><td> Failed to add messages to the analog sampling queue. </td></tr>
<tr><td> 4 </td><td> 1 </td><td> Failed to write sample data to the wavedata file. <br> Is the wavedata file full? </td></tr>