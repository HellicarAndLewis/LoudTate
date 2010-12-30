#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

	//from theo gui example

	//#include "videoMotionExample.h"
#include "ofxControlPanel.h"
	//#include "backgroundSubtractionExample.h"

	//#include "customDrawer.h"

	//from avsys/analysis2/aubioExample

#include "aubioAnalyzer.h"

	//from avsys/analysis2/fft

#include "fft.h"
#include "FFTOctaveAnalyzer.h"

#include "AppSettings.h"

#define BUFFER_SIZE 512

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
	
	//from theo gui example
	
	void eventsIn(guiCallbackData & data);
		//	void grabBackgroundEvent(guiCallbackData & data);	
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
	//from avsys/analysis2/aubioExample
	
	void audioReceived		(float * input, int bufferSize, int nChannels); 
	
		//to do the mix
	
	void setMixImageFromImage(ofImage* sourceImage, float mixAmount);
	void setMixImageFromImages(ofImage* sourceImage1, ofImage* sourceImage2, float mixAmount);
	
		//from audio in example
	
//		void audioReceived 	(float * input, int bufferSize, int nChannels); 
//	
//		float * left;
//		float * right;
//		int 	bufferCounter;
//		int 	drawCounter;
	
		//from ofx control panel from theo
	
	ofxControlPanel gui;
	simpleFileLister listerChannelA;
	simpleFileLister contentChannelA;
	simpleFileLister listerChannelB;
	simpleFileLister contentChannelB;
		//simpleLogger logger;
	
//	motionStats stats;
//	motionDraw threshDraw;
//	motionDraw camDraw;
	
//	ofVideoGrabber grabber;
//	backgroundSubtractionExample bgExample;
		//	customDrawer pointAdder;
	
//	float elapsedTime;
//	int appFrameCount;
//	float appFrameRate;
	
	ofTrueTypeFont TTF;
	
//	videoMotionExample motion;	
	
	//from avsys/analysis2/aubioExample
	float * pitchAmplitudeLeft;
	float * pitchAmplitudeRight;
	
	float * FFTLeft;
	float * FFTRight;	
	
	aubioAnalyzer AA;
	
	
	
	//from avsys/analysis2/fft
	
	FFTOctaveAnalyzer FFTanalyzer;
	
private:	
	
//	float * left;
//	float * right;
	
	int 	bufferCounter;
	fft		myfft;
	
	float magnitude[BUFFER_SIZE];
	float phase[BUFFER_SIZE];
	float power[BUFFER_SIZE];
	float freq[BUFFER_SIZE/2];
	
		//images for preview of the folder
	
	ofImage channelAIcon;
	ofImage channelBIcon;
	
	vector <ofImage> channelAImages;
	vector <ofImage> channelBImages;
	
	ofImage channelASource;
	ofImage channelBSource;
	
	ofImage mixResult;
	
	float decayedAudioLevel;
	
	float loudestAudioLevelRecieved;
	
	int currentChannelAIndex;
	int currentChannelBIndex;
	
	bool spaceDown;
};

#endif	

