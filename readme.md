videoRecordSweeper
==================
videoRecordSweeper.exe repetitively records movies from microEnableIV frame grabber.

Hardware
========
This program works with the following frame grabber and camera.


Frame grabber: microEnable IV AD4-CL (http://www.silicon-software.de/en/microenable4.html) 


Camera: OPTRONIS CL600X2-FULL-M (http://www.stemmer-imaging.co.uk/en/products/article/10802) 


Installation
============
It might be necessary to first install Visual C++ Redistributable (http://www.microsoft.com/en-us/download/details.aspx?id=30679).

It is also necessary to install the driver for the frame grabber. This is included
in the driver CD you get from the company.

Click "ZIP" button above (main page of this repo on github), and download the repository. The installer file (setup) is found
in <extracted folder>\VideoRecordSweeper\VideoRecordSweeper\Setup1\Setup1\Express\CD_ROM\DiskImages\DISK1



How to use the program
======================
1. Edit the configuration called config.txt. The file is installed with 
videoRecordSweeper in the same folder.

	a. width and height: Pixel numbers for the frame. These have to be a multiple of 32?
	
	b. nrOfPicturesToGrab: The number of frames in each movie.
	
	c. frameRate: This number is written int the avi files.
	
	d. timeout: The program waits for data from the camera for the specified time in seconds.
	
	e. iterationNum: The number of movie files.
	
	f. folderName: The absolute path of the folder where the movies are stored.
	
	g. filePrefix: Numbers are attached to this.
2. Change the settings of the camera accoridngly.
3. Run the program by double clicking the icon.
4. If this software is useful to you, we'd appreciate it if you acknowledged my work with
the URL (https://github.com/tarokiritani/VideoRecordSweeper)


How to program
==============
This program is written in Microsoft Visual Studio Professional 2012.
