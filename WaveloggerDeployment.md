# Introduction #

The wavelogger is intended to be deployed into the rocky intertidal to measure water velocity data.

# Batteries #

The wavelogger is designed to run with two AA sized 3.7v Lithium batteries.  Tadiran TL-5104's are what we use.  The batteries are wired in parallel, so both of the positive terminals should be at the same end of the battery pack.  They should both point towards the rest of the wavelogger hardware, to the end with the red wire.  The hardware I made used battery terminals that have one spring and one flat connection on each end of the battery pack.  Do not be confused by this.  The positive ends of both batteries must be at the same end of the battery pack.

<img src='http://wavelogger.googlecode.com/files/Batteries.jpg' width='512' height='384'>

<h1>SDCards</h1>

The SDCard can have a large impact on the battery life of the wevelogger.  Check out <a href='SDCardMeasurement.md'>SDCardMeasurement</a> for a discussion of the relevant factors.  We have found that the current SanDisk 2GB cards are excellent.<br>
<br>
The <a href='SDCardSetup.md'>SDCardSetup</a> page describes how to correctly configure an SDCard for use in the wavelogger.<br>
<br>
Since the SDCard has such a large influence we did a thorough testing of a number of cards to find the best performers.  The results of that testing can be found at <a href='SDCardComparison.md'>SDCardComparison</a>.  We ended up marking the best cards with whiteout to identify them later.<br>
<br>
Insertion and removal of the SDCard from the Wavelogger is done by pushing the card into the slot until it clicks.  It's easies to do this with a thumbnail.  Pushing the card in again will cause it to pop out a bit and it can then be easily removed.<br>
<br>
<h1>Boards</h1>

There are four boards that make up the wavelogger when it is deployed.  There is a fifth board that allows it to talk to a desktop or laptop using a USB connection.<br>
<br>
Analog Amplifier Board plus sensor, end cap and threaded mounting rods.<br>
<a href='http://wavelogger.googlecode.com/files/AnalogDisc.jpg'>
<img src='http://wavelogger.googlecode.com/files/AnalogDisc.jpg' width='256' height='192'>
</img>
</a>

Analog to Digital and Digital to Analog conversion Board.<br>
<a href='http://wavelogger.googlecode.com/files/ADDisc.jpg'>
<img src='http://wavelogger.googlecode.com/files/ADDisc.jpg' width='256' height='192'>
</img>
</a>

CPU and Micro SD Card Board.<br>
<a href='http://wavelogger.googlecode.com/files/CPUDisc.jpg'>
<img src='http://wavelogger.googlecode.com/files/CPUDisc.jpg' width='256' height='192'>
</img>
</a>

Power Supply, Real Time Clock, Temperature Measurement and Battery Monitoring Board.<br>
<a href='http://wavelogger.googlecode.com/files/PowerDisc.jpg'>
<img src='http://wavelogger.googlecode.com/files/PowerDisc.jpg' width='256' height='192'>
</img>
</a>

<h1>Housing</h1>

We made water tight housings for the waveloggers out of clear PVC tube with machined end caps.  There is a single O-ring that seals the housing when the end cap with the sensor is screwed into the housing.  The O-ring is coated in 100% silicone grease.<br>
<br>
<h1>Assembly</h1>

The wavelogger boards are mounted on the threaded rod hardware starting with the Analog Board.  Each board is seperated by two 7/16th inch spacers.  The remaining boards are assembled in the order, Analog to Digital, CPU, and finally Power Supply.<br>
<br>
The Micro SD Card should be setup and installed in the CPU boards slot before the batteries are connected.  Micro SD Card setup instructions can be found on the <a href='SDCardSetup.md'>SDCardSetup</a> page.<br>
<br>
The Battery holder is separated from the stack of boards by two 7/16th inch spaces, one on each threaded rod.  And finally two 4-40 nuts hold the entire assembly together.<br>
<br>
<h1>Activation</h1>

Once the wavelogger is completely assembled it will be waiting for an activation signal before it runs its auto zero routine.  To start the logger you place a magnet on the outside of the housing near the CPU board.  This will activate the magnetic reed switch on the CPU board and will start the auto zero routine.  Once the auto zero routine is complete (The LEDs will flash four times, with a few seconds pause between each flash) the wavelogger will go into the record mode.  At this time no LEDs should be flashing.  If they are you can diagnose the problem by following the instructions on the <a href='WaveloggerTroubleshooting.md'>WaveloggerTroubleshooting</a> page.<br>
<br>
<h1>Downloading</h1>

Once the wavelogger has gathered the data required it is easy to download it from the Micro SD Card.  First the housing is unscrewed.  Then the batteries are disconnected.  And finally the Micro SD Card is removed and placed in a card reader.  The three files can be copied to a directory on your computer, and the card reformatted for additional recording.<br>
<br>
<h1>Processing</h1>

The first stages of processing the data can be done with the <code>process</code> tool found in the <code>wavelogger/tools/process/release</code> directory.  This program converts the binary file format written by the wavelogger into CSV files.  The simplest command line from the <code>wavelogger/tools/process</code> directory to process a file is:<br>
<br>
<code>./release/process -file wavedata.dat -output output.csv</code>

That command line will read an input file called wavedata.dat and write to a file called output.csv.  It will dump the entire file.  You can have the program only spit out segments of the file by passing timestamps in the <code>start</code> and <code>stop</code> command line arguments.  The timestamp is the number of 100ths of seconds that have passed since January 1st 2000.<br>
<br>
The <code>./release/process</code> <code>wavedata.dat</code> and <code>output.csv</code> in the above command line are all paths.  They are all relative to the current directory, that is the directory that you are currently in (when you type ls you see the contents of the current directory).  You can run the process program from any directory.  You will need to change these three paths to point to the process program, the wavedata you want to read and the output file you want to generate respectively.