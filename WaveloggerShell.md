# Introduction #

The Wavelogger shell can be accessed over a serial connection using Screen, CuteCom or Stripchart.  The shell is a simple command line based interactive user interface that allows you to calibrate the Wavelogger, as well as set system parameter, such as the date and time, and debug the hardware and software.

# Calibration #

  * `gain <value>`
> > The value parameter can be from 0 to 255.  The hardware is set up to have a gain
> > specified by the following equations.
> > <br><code>Gain = 1 + ((1000060 - value * 3906.25) / 1050)</code>
<blockquote><br><code>Gain ~ 953.44 - value * 3.72</code>
<br>Thus the gain can range from about 5x to about 950x in 3.72x increments.  The<br>
manufacturer of the amplifier recommends that the gain be set no lower than 9x<br>
however.</blockquote></li></ul>

<ul><li><code>search</code>
<blockquote>Search will do a binary search to determine the correct offset voltage to apply to<br>
the amplifiers.  This is used to compensate for unbalanced bridges.  It should be run<br>
once before sampling from the bridge.</blockquote></li></ul>

<ul><li><code>average &lt;samples&gt;</code>
<blockquote>Average will continuously sample and report averages every <code>samples/100</code> seconds.<br>
The <code>&lt;samples&gt;</code> parameter can be from 1 to 200.</blockquote></li></ul>

<h1>Real Time Clock</h1>

<ul><li><code>rtc</code>
<blockquote>Print out the current value of the real time clock.</blockquote></li></ul>

<ul><li><code>rtc_date &lt;day&gt; &lt;month&gt; &lt;year&gt;</code>
<blockquote>Set the real time clocks date fields.  The day is from 1 to 31, the month is from 1<br>
to 12 and the year is from 00 to 99.</blockquote></li></ul>

<ul><li><code>rtc_time &lt;hour&gt; &lt;minute&gt; &lt;second&gt;</code>
<blockquote>Set the real time clocks time fields.  The hour is from 0 to 23, the minute is from<br>
0 to 59 and the second is from 0 to 59.</blockquote></li></ul>

<h1>File System</h1>

<ul><li><code>ls</code>
<blockquote>List the contents of the current directory.</blockquote></li></ul>

<ul><li><code>cd &lt;directory&gt;</code>
<blockquote>Change directories to the directory specified by <code>&lt;directory&gt;</code>.  <code>&lt;directory&gt;</code> must<br>
be a directory in the current directory or <code>..</code> for the parent directory.</blockquote></li></ul>

<ul><li><code>cat &lt;file&gt;</code>
<blockquote>Print out the contents of a file to the console.