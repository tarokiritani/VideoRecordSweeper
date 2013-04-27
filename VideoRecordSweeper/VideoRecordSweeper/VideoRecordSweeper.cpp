// VideoRecordSweeper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sisoIo.h"
#include "fgrab_struct.h"
#include "fgrab_prototyp.h"
#include "fgrab_define.h"
#include <string>
#include <sstream> 
#include <iostream>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <map>
#include <algorithm>
#include <time.h> 
using namespace std;

std::map<string, string> getParams(){
	std::ifstream t;
	int length;
	t.open("config.txt");
	if (t.is_open()){      // open input file
		t.seekg(0, std::ios::end);    // go to the end
		length = t.tellg();           // report location (this is the length)
		t.seekg(0, std::ios::beg);    // go back to the beginning
		char* buffer = new char[length];    // allocate memory for a buffer of appropriate dimension
		t.read(buffer, length);       // read the whole file into the buffer
		t.close();
		string fileContent(buffer);
		regex e("\\b[a-zA-Z]+(\\s*)=(\\s*)\\S+;");
		regex_iterator<string::iterator> rit ( fileContent.begin(), fileContent.end(), e );
		regex_iterator<string::iterator> rend;
		std::map<string, string> parameterList;
		while (rit!=rend) {
			size_t pos = 0;
			string paramPair = rit->str();
			paramPair.erase(std::remove(paramPair.begin(), paramPair.end(), ' '), paramPair.end());
			paramPair.erase(std::remove(paramPair.begin(), paramPair.end(), '	'), paramPair.end());
			size_t eqLoc = paramPair.find('=', pos);
			string key = paramPair.substr(0, eqLoc);
			int len = paramPair.size();
			string val = paramPair.substr(eqLoc + 1, len - eqLoc - 2);
			std::cout << key << " = ";
			std::cout << val << endl;
			parameterList.insert(std::pair<string, string>(key,val));
			++rit;
		}
		return parameterList;
	}
}

int main(int argc, char* argv[], char* envp[]){
	
	std::map<string, string> parameterList = getParams();
	cout << "in main" << endl;
	cout << parameterList.find("height")->second;
	Fg_Struct *fg           = NULL;
	int boardNr             = 0;
	int camPort             = PORT_A;
	int nrOfPicturesToGrab  = atoi(parameterList.find("nrOfPicturesToGrab")->second.c_str());
	int nbBuffers           = nrOfPicturesToGrab + 1;;
	int width               = atoi(parameterList.find("width")->second.c_str());
	int height			    = atoi(parameterList.find("height")->second.c_str());
	int samplePerPixel      = 1;
	int bytePerSample       = 1;
	int number;
	double frameRate = atof(parameterList.find("frameRate")->second.c_str());
	void *AviRef;
	int timeout = atoi(parameterList.find("timeout")->second.c_str());
	int iterationNum = atoi(parameterList.find("iterationNum")->second.c_str());
	string folderName = parameterList.find("folderName")->second.c_str();
	string filePrefix = parameterList.find("filePrefix")->second.c_str();
	string fileAvi;

	for (int k = 0;k<iterationNum;k++) {
		if((fg = Fg_Init("FullAreaGray8.dll",boardNr)) == NULL) {
			return FG_ERROR;
		}

		int dispId0 = CreateDisplay(8*bytePerSample*samplePerPixel,width,height);
		SetBufferWidth(dispId0,width,height);

		int totalBufferSize = width * height * samplePerPixel * bytePerSample * nbBuffers;
		unsigned long  *ptrMem = (unsigned long*) Fg_AllocMem(fg,totalBufferSize,nbBuffers,camPort);
		if ( ptrMem == NULL) {
			return FG_ERROR;
		}

		/*Image width of the acquisition window.*/
		if (Fg_setParameter(fg,FG_WIDTH,&width,camPort) < 0 ) {
			return FG_ERROR;
		}

		/*Image height of the acquisition window.*/
		if (Fg_setParameter(fg,FG_HEIGHT,&height,camPort) < 0 ) {
			return FG_ERROR;
		}

		if((Fg_Acquire(fg,camPort,nrOfPicturesToGrab)) < 0){
			return FG_ERROR;
		}

		int last_pic_nr = 0;

		while((last_pic_nr = Fg_getLastPicNumberBlocking(fg,last_pic_nr+1,camPort,timeout))< nrOfPicturesToGrab) {
			if (last_pic_nr < 0) {
				Fg_stopAcquire(fg,camPort);
				Fg_FreeMem(fg,camPort);
				Fg_FreeGrabber(fg);
				return FG_ERROR;
			}
			DrawBuffer(dispId0,Fg_getImagePtr(fg,last_pic_nr,camPort),last_pic_nr,"");
		}

		CloseDisplay(dispId0);
		Fg_stopAcquire(fg,camPort);
		ostringstream convert;
		convert << k;
		fileAvi = folderName + filePrefix + convert.str() + ".avi";
		cout << fileAvi.c_str();
		IoCreateAVIGray(&AviRef, fileAvi.c_str(), width, height, frameRate);
		number = 0;

		while(number < nrOfPicturesToGrab){
			IoWriteAVIPicture(AviRef,number+1,(unsigned char *)ptrMem);
			ptrMem = ptrMem + width*height/4;
			number++;
		}
		IoCloseAVI(AviRef);
		Fg_FreeMem(fg,camPort);
		Fg_FreeGrabber(fg);
	}

	return FG_OK;
}

