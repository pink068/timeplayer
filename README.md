# numbers<br />
Numbers station transmission generator.<br />
Designed to be a radio beacon controller which sends voice messages, as wav, at the correct times through the day.<br />
loads of work still to do.<br />
dependencies: make g++ libttspico-utils libsqlite3-dev libhamlib-dev libcurl4-openssl-dev alsamixer<br />
To get the files just type git clone https://github.com/pink068/TimePlayer<br/>
Then cd into the TimePlayer Folder<br/>
To build it just type make.<br />
To run it just type ./run<br /><br />
It plays a specific wav file at the specific time. EG plays 21:10 at ten past nine in the eveing. <br/>
Before playing the wav is runs a script file, if it exists, to set the transmitter frequency and power <br/>

<br />
One commnd on each line of the text file.<br/>
if the text starts with a;<br />
F set transmitter frequency to n, e.g.  F5.750 sets it to 5.750MHz<br />
P set transmitter power to n, e.g. P50 sets the transmitter to 50 watts.<br />

<br />

