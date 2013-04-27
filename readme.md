videoRecordSweeper
==================
videoRecordSweeper.exe repetitively records movies from microEnableIV frame grabber.

Hardware
========
This program works with the following frame grabber and camera:
Frame grabber: microEnable IV AD4-CL (http://www.silicon-software.de/en/microenable4.html) 
Camera: OPTRONIS CL600X2-FULL-M (http://www.stemmer-imaging.co.uk/en/products/article/10802) 


Installation
============
It might be necessary to first install Visual C++ Redistributable (http://www.microsoft.com/en-us/download/details.aspx?id=30679).



Click "ZIP" button, and download the repository. The installation file (setup) is found
in \VideoRecordSweeper\VideoRecordSweeper\Setup1\Setup1\Express\CD_ROM\DiskImages\DISK1



How to use the program
======================
1. Edit a configuration called config.txt found in VideoSweep.

	a. width and height: these have to be a multiple of 32?
	
	b. nrOfPicturesToGrab: the number of frames in each movie.
	
	c. frameRate: this number is written int the avi files.
	folderName: the absolute path of the folder where the movies are stored.  
	
	d. timeout: the program waits for data from the camera for the specified time in seconds.
	
	e. iterationNum: the number of movie files.
	
	f. folderName: the absolute path of the folder where the movies are stored.
	
	g. filePrefix: numbers are attached to this.
2. Change the settings of the camera accoridngly.
3. Run the program by double clicking the icon.
4. If this software is useful to you, we'd appreciate it if you acknowledged my work with
the URL (https://github.com/tarokiritani/VideoRecordSweeper)


How to program
==============
This program is written in Microsoft Visual Studio Professional 2012.
