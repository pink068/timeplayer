# timeplayer<br />
Another version of 
Numbers station transmission generator.<br />
Designed to be a radio beacon controller which sends voice messages, as wav, at the correct times through the day.<br />
loads of work still to do.<br />
dependencies: make g++ libhamlib-dev alsamixer sox<br />
To get the files just type git clone https://github.com/pink068/timeplayer<br/>
Then cd into the timeplayer Folder<br/>
To build it just type make.<br />
To run it just type ./run<br /><br />
It plays a specific wav file at the specific time. EG plays 2110.wav at ten past nine in the evening. <br/>
Before playing the wav is runs a script file, if it exists, to set the transmitter frequency and power <br/> 
or run other commands. See below.

On startup the program will set the radio to a defualt frequency and power, <br/>
then look for 2500.txt to set the local startup settings<br />

<br />
One commnd on each line of the text file.<br/>
if the text starts with a;<br />
C send the callsign e.g. C<br />
D Send the time as a date time group  e.g. D<br />
G Send following test as groups of 5 phonetics   e.g. Gabcdefghij<br />
F set transmitter frequency to n, e.g.  F5.750 sets it to 5.750MHz<br />
P set transmitter power to n, e.g. P50 sets the transmitter to 50 watts.<br />
S speak the following text e.g. Sthis is a message<br />
<br />

Example file<br />
.........................<br />
F5.750<br />
P50<br />
C<br />
D<br />
Gabcdefghij<br />
Sthis is a message<br />
.........................<br />
