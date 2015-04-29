# Introduction #

SDCards have a lot of variability in their performance characteristics.  The two parameters that are most important for use in the Wavelogger are the current consumption when not idle and the time it takes the card to return to an idle state after a write or read.  The wavelogger can be used to test these parameters with the addition of an oscilloscope and a resistor.

The best SDCards that we have tested draw about 13mA (milliamps) and can power down in about 12ms (milliseconds).  Since the Wavelogger writes to the card once every two seconds the resulting average current draw is:

`13mA * 12ms / 2s = 78uA`

The worst SDCards that we have tested draw about 56mA and take about 300ms to power down.  Thus they average:

`56mA * 300ms / 2s = 8.4mA`

That is more than two orders of magnitude more current.  Since the rest of the Wavelogger only draws a few milliamps on average this is a very significant amount of current.

# Details #

Measuring the current draw of an SDCard can be accomplished by putting a small (4.7ohm) resistor in series with a 9 volt battery.  The voltage drop across the resistor can be used to compute the total current draw of the Wavelogger using:

`current (Amps) = voltage drop (Volts) / 4.7 (Ohms)`

The resistor can be any small value you like.  I found that 4.7 ohms was a good balance.  Anything smaller and the signal is getting too small and there is a lot of noise.  Anything much larger and the voltage drop across the resistor can become a problem for the Wavelogger.  With a 9 volt battery that is less of a problem than with a 3.7 volt lithium battery.

The circuit I used to measure Wavelogger current consumption is shown below.  The O\_TIP and O\_GND points are the Oscilloscope tip and ground clamp connection points respectively.

![http://wavelogger.googlecode.com/files/current_measurement.png](http://wavelogger.googlecode.com/files/current_measurement.png)

Here are some pictures of the setup I use to monitor power usage.

<img src='http://wavelogger.googlecode.com/files/CurrentMeasurement.jpg' width='384' height='512'>
<img src='http://wavelogger.googlecode.com/files/CurrentMeasurementCloseUp.jpg' width='384' height='512'>

Once you have that all wired up you need to initialize an SDCard correctly so the wavelogger will write to it and you will be able to see the current usage patterns that result.  You can see how to do this on the <a href='SDCardSetup.md'>SDCardSetup</a> page.<br>
<br>
<h1>Oscilloscope Setup</h1>

Measurement of the current draw while the card is active can be done on a Tektronix TDS 1012 or equivalent oscilloscope.  For the Tektronix set the options as follows.<br>
<br>
<ul><li>Trigger:<br>
<ul><li>Type: Edge<br>
</li><li>Source: CH1<br>
</li><li>Slope: Rising<br>
</li><li>Mode: Normal<br>
</li><li>Coupling: DC<br>
</li><li>Level: 100mV<br>
</li></ul></li><li>Channel 1:<br>
<ul><li>Volts/Division: 50mV<br>
</li><li>Seconds/Division: 25ms