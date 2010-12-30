#include "testApp.h"
#include "stdio.h"




//--------------------------------------------------------------
void testApp::setup(){	 
	
		// load the settings
	settings.loadSettings("AppSettings.xml");	
	
	ofBackground(255,255,255);	
	
	// 0 output channels, 
	// 2 input channels
	// 22050 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
//	ofSoundStreamSetup(0,2,this, 44100, 256, 4);	
//	left = new float[256];
//	right = new float[256];
//	
//	
//	bufferCounter = 0;
//	drawCounter = 0;
	
	channelAIcon.allocate(640, 480, OF_IMAGE_COLOR);
	channelBIcon.allocate(640, 480, OF_IMAGE_COLOR);	
	
	channelASource.allocate(640, 480, OF_IMAGE_COLOR);
	channelBSource.allocate(640, 480, OF_IMAGE_COLOR);
	
	mixResult.allocate(640, 480, OF_IMAGE_COLOR);
	
	channelAImages.resize(0);
	channelBImages.resize(0);
	
		//control panel
	
//	grabber.initGrabber(320, 240);
//	
//    motion.setup(grabber.width, grabber.height);
//	bgExample.setup(grabber.width, grabber.height);
//	w
//	camDraw.setup(&motion.gray, &motion.motionField);
//	threshDraw.setup(&motion.motion, &motion.motionField);	
	
	ofxControlPanel::setBackgroundColor(simpleColor(30, 30, 60, 200));
	ofxControlPanel::setTextColor(simpleColor(240, 50, 50, 255));
	
	gui.loadFont("MONACO.TTF", 8);		
	gui.setup("LOUD TATE 2010 - Jammer vs. Hellicar&Lewis vs. Workshop Team", 0, 0, 900, 800);
	gui.addPanel("Select Image Folders and Mix", 4, false);
	
//	ofxControlPanel::setBackgroundColor(simpleColor(60, 30, 30, 200));	
//	gui.addPanel("Camera Background", 4, false);
//	
//	ofxControlPanel::setBackgroundColor(simpleColor(70, 70, 30, 200));	
//	gui.addPanel("Camera Average Motion", 4, false);
	
	ofxControlPanel::setBackgroundColor(simpleColor(30, 30, 30, 200));	
	
		//--------- PANEL 1
	gui.setWhichPanel(0);
	
	gui.setWhichColumn(0);
	
	gui.addDrawableRect("Channel A", &channelASource, 200, 150);	
	listerChannelA.listDir("images/");
	gui.addFileLister("Channel A Images", &listerChannelA, 200, 300);
	vector <string> drawModeNames;
	drawModeNames.push_back("select on level");
	drawModeNames.push_back("next image on peak");
	drawModeNames.push_back("next image unless peak");
	drawModeNames.push_back("next image on space");
	gui.addTextDropDown("draw mode", "DRAW_MODE_A", 0, drawModeNames);	
	
	gui.setWhichColumn(1);
	gui.addSlider("Mix", "MIX", 0.f, 0.f, 1.f, false);	
	gui.addDrawableRect("Output", &mixResult, 200, 150);

	gui.setWhichColumn(2);	
	
	gui.addDrawableRect("Channel B", &channelBSource, 200, 150);	
	listerChannelB.listDir("images/");	
	gui.addFileLister("Channel B Images", &listerChannelB, 200, 300);	
	gui.addTextDropDown("draw mode", "DRAW_MODE_B", 0, drawModeNames);	
	
	gui.setWhichColumn(3);
	gui.addSlider("minium audio level", "AUDIO_MIN", 0.01f, 0.f, 0.1f, false);	
	gui.addSlider("maximum audio level", "AUDIO_MAX", 0.05f, 0.f, 0.3f, false);
	gui.addSlider("audio decay rate", "AUDIO_DECAY", 0.95f, 0.7f, 1.f, false);	
	gui.addSlider("manual audio level", "AUDIO_MANUAL_LEVEL", 0.f, 0.f, 1.f, false);
	gui.addSlider("trigger audio level", "AUDIO_TRIGGER_LEVEL", 0.5f, 0.f, 1.f, false);
	gui.addToggle("Brightness on Audio?", "AUDIO_BRIGHTNESS_ON_LEVEL", 0);
	gui.addToggle("Scale on Audio?", "AUDIO_SCALE_ON_LEVEL", 0);
	vector <string> audioModeNames;
	audioModeNames.push_back("normal audio");
	audioModeNames.push_back("decay audio");
	audioModeNames.push_back("manual audio");
	gui.addTextDropDown("audio mode", "AUDIO_MODE", 0, audioModeNames);	
	
//		//--------- PANEL 2
//	gui.setWhichPanel(1);	
//	
//	gui.setWhichColumn(0);
//	gui.addDrawableRect("video", &bgExample.gray, 200, 150);	
//	
//	gui.setWhichColumn(1);
//	gui.addDrawableRect("background", &bgExample.background, 200, 150);
//	
//	gui.setWhichColumn(2);
//	gui.addDrawableRect("thresholded image", &bgExample.thresh, 200, 150);	
//	
//	gui.setWhichColumn(3);
//	gui.addToggle("grab background", "GRAB_BACKGROUND", 0);		
//	
//	gui.addButtonSlider("threshold", "BG_THRESHOLD", 29.0, 1.0, 255.0, false);		
//	
//		//some dummy vars we will update to show the variable lister object
//	elapsedTime		= ofGetElapsedTimef();
//	appFrameCount	= ofGetFrameNum();	
//	appFrameRate	= ofGetFrameRate();
//	
//	vector <guiVariablePointer> vars;
//	vars.push_back( guiVariablePointer("elapsed time", &elapsedTime, GUI_VAR_FLOAT, 2) );
//	vars.push_back( guiVariablePointer("elapsed frames", &appFrameCount, GUI_VAR_INT) );
//	vars.push_back( guiVariablePointer("app fps", &appFrameRate, GUI_VAR_FLOAT, 2) );
//	
//	vars.push_back( guiVariablePointer("mouse x", &mouseX, GUI_VAR_INT) );
//	vars.push_back( guiVariablePointer("mouse y", &mouseY, GUI_VAR_INT) );
//	
//	gui.addVariableLister("app vars", vars);
//	
//	gui.addChartPlotter("some chart", guiStatVarPointer("app fps", &appFrameRate, GUI_VAR_FLOAT, true, 2), 200, 100, 200, 40, 80);
//	
//	vector <string> names;
//	names.push_back("abs diff");
//	names.push_back("greater than");
//	names.push_back("less than");
//	gui.addTextDropDown("difference mode", "DIFF_MODE", 0, names);	
	
	
		//--------- PANEL 3
//	gui.setWhichPanel(2);
//	
//	gui.setWhichColumn(0);
//	gui.addDrawableRect("video and motion", &camDraw, 200, 150);
//	
//	gui.setWhichColumn(1);
//	gui.addDrawableRect("motion diff", &threshDraw, 200, 150);
//	
//	gui.setWhichColumn(2);
//	stats.setDrawScale(2000.0);
//	gui.addDrawableRect("average motion", &stats, 200, 150);
//	
//	gui.setWhichColumn(3);
//	gui.addSlider("motion threshold", "MOTION_THRESHOLD", 29.0, 1.0, 255.0, false);	
//	gui.addSlider("motion fade amnt", "MOTION_FADE", 0.67, 0.0, 1.0, false);	
//	gui.addSlider("field draw scale", "FIELD_DRAW_SCALE", 1.0, 1.0, 10.0, false);	
	
		//SETTINGS AND EVENTS
	
		//load from xml!
	gui.loadSettings("controlPanelSettings.xml");
	
		//if you want to use events call this after you have added all your gui elements
	gui.setupEvents();
	gui.enableEvents();
	
		//  -- SPECIFIC EVENTS -- this approach creates an event group and only sends you events for the elements you describe. 
		//	vector <string> list;
		//	list.push_back("FIELD_DRAW_SCALE");
		//	list.push_back("DIFF_MODE");
		//	gui.createEventGroup("TEST_GROUP", list);
		//	ofAddListener(gui.getEventGroup("TEST_GROUP"), this, &testApp::eventsIn);
	
		//  -- PANEL EVENTS -- this approach gives you back an ofEvent for only the events from panel 0
		//	ofAddListener(gui.getEventsForPanel(0), this, &testApp::eventsIn);
	
		//  -- this gives you back an ofEvent for all events in this control panel object
	ofAddListener(gui.guiEvent, this, &testApp::eventsIn);
	
		//  --EVENT FOR SINGLE GUI OBJECT
//	ofAddListener(gui.createEventGroup("GRAB_BACKGROUND"), this, &testApp::grabBackgroundEvent);
	
	//from avsys/analysis2/aubioExample
	
		// 0 output channels, 
		// 2 input channels
		// 44100 samples per second
		// 256 samples per buffer
		// 4 num buffers (latency)
	
		//setup of sound input
	ofSoundStreamSetup(0, 2, this, 44100, BUFFER_SIZE, 4);	
	
	pitchAmplitudeLeft = new float[BUFFER_SIZE];
	pitchAmplitudeRight = new float[BUFFER_SIZE];
	
	FFTLeft = new float[BUFFER_SIZE];
	FFTRight = new float[BUFFER_SIZE];
	
	AA.setup();
	
//	dinFont.loadFont("DIN.otf", 50);
	
	//from avsys/analysis2/fft
	
		// 0 output channels, 
		// 2 input channels
		// 44100 samples per second
		// BUFFER_SIZE samples per buffer
		// 4 num buffers (latency)
	
//	ofSoundStreamSetup(0,2,this, 44100, BUFFER_SIZE, 4);	
//	
//	left = new float[BUFFER_SIZE];
//	right = new float[BUFFER_SIZE];
	
	ofSetColor(0x666666);
	
	FFTanalyzer.setup(44100, BUFFER_SIZE/2, 2);
	
	FFTanalyzer.peakHoldTime = 15; // hold longer
	FFTanalyzer.peakDecayRate = 0.95f; // decay slower
	FFTanalyzer.linearEQIntercept = 0.9f; // reduced gain at lowest frequency
	FFTanalyzer.linearEQSlope = 0.01f; // increasing gain at higher frequencies
	
		//ofSetFrameRate(60);
	
	decayedAudioLevel = 0.f;
	
	loudestAudioLevelRecieved = 0.f;
	
	currentChannelAIndex = 0;
	currentChannelBIndex = 0;
	
	spaceDown = false;

}

//	// this is our callback function for the GRAB_BACKGROUND toggle - everytime it changes this gets fired
//	//--------------------------------------------------------------
//void testApp::grabBackgroundEvent(guiCallbackData & data){
//	
//		//we use the event callback to capture the background - we then set the toggle value back to its previous value
//	if( data.isElement( "GRAB_BACKGROUND" ) && data.getInt(0) == 1 ){
//		bgExample.captureBackground();
//		gui.setValueB("GRAB_BACKGROUND", false);
//	}
//}

	//this captures all our control panel events - unless its setup differently in testApp::setup
	//--------------------------------------------------------------
void testApp::eventsIn(guiCallbackData & data){
	
//		//lets send all events to our logger
//	if( !data.isElement( "events logger" ) ){
//		string logStr = data.getXmlName();
//		
//		for(int k = 0; k < data.getNumValues(); k++){
//			logStr += " - " + data.getString(k);
//		}
//		
//		logger.log(OF_LOG_NOTICE, "event - %s", logStr.c_str());
//	}
	
		// print to terminal if you want to 
		//this code prints out the name of the events coming in and all the variables passed
//	printf("testApp::eventsIn - name is %s - \n", data.getXmlName().c_str());
//	if( data.getDisplayName() != "" ){
//		printf(" element name is %s \n", data.getDisplayName().c_str());
//	}
//	for(int k = 0; k < data.getNumValues(); k++){
//		if( data.getType(k) == CB_VALUE_FLOAT ){
//			printf("%i float  value = %f \n", k, data.getFloat(k));
//		}
//		else if( data.getType(k) == CB_VALUE_INT ){
//			printf("%i int    value = %i \n", k, data.getInt(k));
//		}
//		else if( data.getType(k) == CB_VALUE_STRING ){
//			printf("%i string value = %s \n", k, data.getString(k).c_str());
//		}
//	}
//	
//	printf("\n");
//	
		//process events coming from the file listers
	
//	simpleFileLister listerChannelA;
//	simpleFileLister contentChannelA;
//	simpleFileLister listerChannelB;
//	simpleFileLister contentChannelB;
	
		//example output
	
//	testApp::eventsIn - name is CHANNEL_A_IMAGES - 
//	element name is Channel A Images 
//	0 int    value = 2 
//	1 string value = ../../../data/images/joelHands 
//	2 string value = joelHands 
	
	if(data.getDisplayName() == "Channel A Images"){
		std::ostringstream localOSS;
		
		string contentDirectoryName = data.getString(2).c_str();
		
		localOSS << "images/" << contentDirectoryName;
		
		string directoryToList = localOSS.str();		
		
		int numberOfImages = contentChannelA.listDir(directoryToList);
		
		channelAImages.resize(numberOfImages); //resize the vector, maybe back to zero
		
		if(channelAImages.size() > 0){
				//we have some content, load in the first image as a preview
			std::ostringstream contentOSS;
			
			contentOSS << directoryToList << "/" << contentChannelA.entries[0].filename;
			
			string iconPath = contentOSS.str();
			
			channelAIcon.loadImage(iconPath); //known to be safe
			
			
			
			for(int i=0; i < channelAImages.size(); i++){
				std::ostringstream contentPathOSS;
				
				contentPathOSS << directoryToList << "/" << contentChannelA.entries[i].filename;
				
				string contentPath = contentPathOSS.str();
				
				channelAImages[i].loadImage(contentPath);
			}
		}
	}
	
		//lazy but pragmatic
	
	if(data.getDisplayName() == "Channel B Images"){
		std::ostringstream localOSS;
		
		string contentDirectoryName = data.getString(2).c_str();
		
		localOSS << "images/" << contentDirectoryName;
		
		string directoryToList = localOSS.str();		
		
		int numberOfImages = contentChannelB.listDir(directoryToList);
		
		channelBImages.resize(numberOfImages); //resize the vector, maybe back to zero
		
		if(channelBImages.size() > 0){
				//we have some content, load in the first image as a preview
			std::ostringstream contentOSS;
			
			contentOSS << directoryToList << "/" << contentChannelB.entries[0].filename;
			
			string iconPath = contentOSS.str();
			
			channelBIcon.loadImage(iconPath); //known to be safe
			
			for(int i=0; i < channelBImages.size(); i++){
				std::ostringstream contentPathOSS;
				
				contentPathOSS << directoryToList << "/" << contentChannelB.entries[i].filename;
				
				string contentPath = contentPathOSS.str();
				
				channelBImages[i].loadImage(contentPath);
			}
		}
	}
}

	//--------------------------------------------------------------
void testApp::update(){
		//some dummy vars we will update to show the variable lister object
//	elapsedTime		= ofGetElapsedTimef();
//	appFrameCount	= ofGetFrameNum();	
//	appFrameRate	= ofGetFrameRate();
//	
//	camDraw.setDrawScale(gui.getValueF("FIELD_DRAW_SCALE"));
//	threshDraw.setDrawScale(gui.getValueF("FIELD_DRAW_SCALE"));
	
//	grabber.update(); 
//	
//	if( grabber.isFrameNew() ){	
//		if( gui.getSelectedPanel() == 1 ){
//			bgExample.update(grabber.getPixels(), grabber.width, grabber.height);
//		}else if( gui.getSelectedPanel() == 2){
//			motion.update(grabber.getPixels(), grabber.width, grabber.height);
//			stats.updateFromField(motion.motionField, 0.97);
//		}
//	}
//	
//	motion.setThreshold(gui.getValueI("MOTION_THRESHOLD"));
//	motion.setFadeAmnt(gui.getValueF("MOTION_FADE"));
//	
//	bgExample.setDifferenceMode(gui.getValueI("DIFF_MODE"));
//	bgExample.setThreshold(gui.getValueI("BG_THRESHOLD"));
	
	gui.update();
}


//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0,0,0);
	
		//audio level
	
	float levelToUse = 0.5f;
	
	float rawAudioLevel = AA.amplitude;
	
	if(rawAudioLevel > loudestAudioLevelRecieved){
		loudestAudioLevelRecieved = rawAudioLevel;
	}
	
	float scaledAmplitude = ofNormalize(rawAudioLevel, gui.getValueF("AUDIO_MIN"), gui.getValueF("AUDIO_MAX"));
	
	if(scaledAmplitude > decayedAudioLevel){
		decayedAudioLevel = scaledAmplitude;
	}else{
			//decay it
		decayedAudioLevel = decayedAudioLevel * gui.getValueF("AUDIO_DECAY");
	}
	
	decayedAudioLevel = ofNormalize(decayedAudioLevel, gui.getValueF("AUDIO_MIN"), 1.f);
	
	int audioMode = gui.getValueI("AUDIO_MODE");
	
	if(audioMode == 0){
			//normal mode
		levelToUse = scaledAmplitude;
	}else if(audioMode == 1){
			//decay mode
		levelToUse = decayedAudioLevel;
	}else if(audioMode == 2){
			//manual mode
		levelToUse = gui.getValueF("AUDIO_MANUAL_LEVEL");
	}
	
//	// draw the left:
//	ofSetColor(0x333333);
//	ofRect(100,100,256,200);
//	ofSetColor(0xFFFFFF);
//	for (int i = 0; i < 256; i++){
//		ofLine(100+i,200,100+i,200+left[i]*100.0f);
//	}
//	
//	// draw the right:
//	ofSetColor(0x333333);
//	ofRect(600,100,256,200);
//	ofSetColor(0xFFFFFF);
//	for (int i = 0; i < 256; i++){
//		ofLine(600+i,200,600+i,200+right[i]*100.0f);
//	}
	
//    
//
//	ofSetColor(0x333333);
//	drawCounter++;
//	char reportString[255];
//	sprintf(reportString, "buffers received: %i\ndraw routines called: %i\n", bufferCounter,drawCounter);
//	ofDrawBitmapString(reportString,80,380);

	//from avsys/analysis2/aubioExample
	
		// draw the pitchAmplitudeLeft:
	ofSetColor(0x333333);
	ofRect(0,0,BUFFER_SIZE,200);
	ofSetColor(0xFFFFFF);
	for (int i = 0; i < BUFFER_SIZE; i++){
		ofLine(i,100,i,100+pitchAmplitudeLeft[i]*200);
	}
	
	ofSetColor(255,0,0);
	
	ofDrawBitmapString("pitch is : " + ofToString((int)AA.pitch), 50, 300);
	ofDrawBitmapString("raw audio is : " + ofToString(rawAudioLevel, 3), 50, 320);
	ofDrawBitmapString("scaled audio is : " + ofToString(scaledAmplitude, 3), 50, 340);
	ofDrawBitmapString("decayed audio is : " + ofToString(decayedAudioLevel, 3), 50, 360);	
	ofDrawBitmapString("loudest raw  audio is : " + ofToString(loudestAudioLevelRecieved, 3), 50, 380);	
	ofDrawBitmapString("used audio is : " + ofToString(levelToUse, 3), 50, 400);	
	
	
	//from avsys/analysis2/fft
	
	static int index=0;
	float avg_power = 0.0f;	
	
	/* do the FFT	*/
	myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, FFTLeft,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
	
	for (int i = 0; i < (int)(BUFFER_SIZE/2); i++){
		freq[i] = magnitude[i];
	}
	
	FFTanalyzer.calculate(freq);
	
	ofSetColor(0xffffff);
	for (int i = 0; i < (int)(BUFFER_SIZE/2 - 1); i++){
			//ofRect(200+(i*4),600,4,-freq[i]*10.0f);
	}
	
	for (int i = 0; i < FFTanalyzer.nAverages; i++){
		ofRect(i*20,600,20,-FFTanalyzer.averages[i] * 6);
	}
	
	ofSetColor(0xff0000);
	for (int i = 0; i < FFTanalyzer.nAverages; i++){
		ofRect(i*20,600-FFTanalyzer.peaks[i] * 6,20,-4);
	}	
	
		//display each channel
	ofSetColor(0xffffff);
	
		//mixing
	
		//mixResult.clear();
	
	float mix = 1.f-gui.getValueF("MIX");
	
	int AMix = 255*mix;
	int BMix = 255-AMix;
	
		//cout << "Scaled amplitude " << scaledAmplitude << endl;
	
	float triggerLevel = gui.getValueF("AUDIO_TRIGGER_LEVEL");
	
	if(channelAImages.size() > 0){
		int imageIndexToUse = 0;//default to first image
		
		int drawModeA = gui.getValueI("DRAW_MODE_A");
		
		if(drawModeA == 0){
				//select on level
			imageIndexToUse = levelToUse*(channelAImages.size()-1);
		}else if(drawModeA == 1){
				//next image on peak
			if(levelToUse > triggerLevel){
				currentChannelAIndex++;
			} 
			
			if (currentChannelAIndex > (channelAImages.size()-1)) {
				currentChannelAIndex = 0;
			}
			
			imageIndexToUse = currentChannelAIndex;
		}else if(drawModeA == 2){
				//next image unless peak
			if(!(levelToUse > triggerLevel)){
				currentChannelAIndex++;
			}
			
			if (currentChannelAIndex > (channelAImages.size()-1)) {
				currentChannelAIndex = 0;
			}
			
			imageIndexToUse = currentChannelAIndex;
		}else if (drawModeA == 3) {
				//next image on space
			if(spaceDown){
				currentChannelAIndex++;
			}
			
			if (currentChannelAIndex > (channelAImages.size()-1)) {
				currentChannelAIndex = 0;
			}
			
			imageIndexToUse = currentChannelAIndex;			
		}
		
		channelASource.resize(channelAImages[imageIndexToUse].width,channelAImages[imageIndexToUse].height);
		channelASource.setFromPixels(channelAImages[imageIndexToUse].getPixels(), channelAImages[imageIndexToUse].width, channelAImages[imageIndexToUse].height, OF_IMAGE_COLOR);	
		
		channelASource.draw(0,600, 160, 120);
	}
	
	if(channelBImages.size() > 0){
		int imageIndexToUse = 0;//default to first image
		
		int drawModeB = gui.getValueI("DRAW_MODE_B");
		
		if(drawModeB == 0){
				//select on level
			imageIndexToUse = levelToUse*(channelBImages.size()-1);
		}else if(drawModeB == 1){
				//next image on peak
			if(levelToUse > triggerLevel){
				currentChannelBIndex++;
			} 
			
			if (currentChannelBIndex > (channelBImages.size()-1)) {
				currentChannelBIndex = 0;
			}
			
			imageIndexToUse = currentChannelBIndex;
		}else if(drawModeB == 2){
				//next image unless peak
			if(!(levelToUse > triggerLevel)){
				currentChannelBIndex++;
			}
			
			if (currentChannelBIndex > (channelBImages.size()-1)) {
				currentChannelBIndex = 0;
			}
			
			imageIndexToUse = currentChannelBIndex;
		}else if (drawModeB == 3) {
				//next image on space
			if(spaceDown){
				currentChannelBIndex++;
			}
			
			if (currentChannelBIndex > (channelBImages.size()-1)) {
				currentChannelBIndex = 0;
			}
			
			imageIndexToUse = currentChannelBIndex;			
		}
		
		channelBSource.resize(channelBImages[imageIndexToUse].width,channelBImages[imageIndexToUse].height);
		channelBSource.setFromPixels(channelBImages[imageIndexToUse].getPixels(), channelBImages[imageIndexToUse].width, channelBImages[imageIndexToUse].height, OF_IMAGE_COLOR);	
		
		channelBSource.draw(160,600, 160, 120);
		
		if(channelAImages.size() > 0){
			setMixImageFromImages(&channelASource, &channelBSource, mix);
		}
	}
	
//	gui.addToggle("Brightness on Audio?", "AUDIO_BRIGHTNESS_ON_LEVEL", 0);
//	gui.addToggle("Scale on Audio?", "AUDIO_SCALE_ON_LEVEL", 0);	
	
	float imageScale = 1.f;
	
	float centreProjectionX = settings.GUI_W + (settings.PROJECTION_W/2.f);
	float centreProjectionY = (settings.PROJECTION_H/2.f);
	
	if(gui.getValueB("AUDIO_SCALE_ON_LEVEL")){
		imageScale = levelToUse;
	}
	
	ofPushStyle();
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofEnableAlphaBlending();
	
	if(gui.getValueB("AUDIO_BRIGHTNESS_ON_LEVEL")){
	   ofSetColor(255, 255, 255, (int)(levelToUse*255.f));		
	}else {
		ofSetColor(255, 255, 255, 255);	
	}

	mixResult.draw(centreProjectionX, centreProjectionY, imageScale*settings.PROJECTION_W, imageScale*settings.PROJECTION_H);
	
	ofDisableAlphaBlending();
	ofPopStyle();
	
	ofSetColor(0xffffff);
	gui.draw();
	
	spaceDown = false;
}

void testApp::setMixImageFromImage(ofImage* sourceImage, float mixAmount){
	mixResult.resize(sourceImage->width, sourceImage->height);//safety
	
	unsigned char * sourcePixels = sourceImage->getPixels();
	unsigned char * destPixels = mixResult.getPixels();
	
	for(int i = 0; i< (mixResult.width*mixResult.height); i++){
//		int destIndex = i*4; //alpha pixels,
//		int srcIndex = i*3; //no alpha pixels
		
		int index = i*3;
		
		destPixels[index] += (int)((float)sourcePixels[index]*mixAmount);
		destPixels[index+1] += (int)((float)sourcePixels[index+1]*mixAmount);
		destPixels[index+2] += (int)((float)sourcePixels[index+2]*mixAmount);
			//destPixels[index+3] = mixAmount;
	}
}

void testApp::setMixImageFromImages(ofImage* sourceImage1, ofImage* sourceImage2, float mixAmount){
	mixResult.resize(sourceImage1->width, sourceImage1->height);//safety
	
	unsigned char * sourcePixels1 = sourceImage1->getPixels();
	unsigned char * sourcePixels2 = sourceImage2->getPixels();
	unsigned char * destPixels = mixResult.getPixels();
	
	for(int i = 0; i< (mixResult.width*mixResult.height); i++){
			//		int destIndex = i*4; //alpha pixels,
			//		int srcIndex = i*3; //no alpha pixels
		
		int index = i*3;
		
		destPixels[index] = (int)((float)sourcePixels1[index]*mixAmount) + (int)((float)sourcePixels2[index]*(1.f-mixAmount));
		destPixels[index+1] = (int)((float)sourcePixels1[index+1]*mixAmount) + (int)((float)sourcePixels2[index+1]*(1.f-mixAmount)); 
		destPixels[index+2] = (int)((float)sourcePixels1[index+2]*mixAmount) + (int)((float)sourcePixels2[index+2]*(1.f-mixAmount));
			//destPixels[index+3] = mixAmount;
	}
}


//static float adder = 0;
////--------------------------------------------------------------
//void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){	
//	// samples are "interleaved"
//	for (int i = 0; i < bufferSize; i++){
//		left[i] = input[i*2];
//		right[i] = input[i*2+1];
//	}
//	bufferCounter++;
//	
//}

//from avsys/analysis2/aubioExample
	//--------------------------------------------------------------
void testApp::audioReceived (float * input, int bufferSize, int nChannels){	
	
	
		// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		pitchAmplitudeLeft[i]	= input[i*2];
		FFTLeft[i]				= input[i*2];
		pitchAmplitudeRight[i]	= input[i*2+1];
		FFTRight[i]				= input[i*2+1];	
	}
	
	AA.processAudio(pitchAmplitudeLeft, bufferSize);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	    //if you need to adjust the camera properties
	switch (key){
		case 'f':{
			ofToggleFullscreen();
			break;				
		}
		case 'h':{
			gui.toggleView();	
			break;
		}
		case 'r':{
			loudestAudioLevelRecieved = 0.f;
		}
		case ' ':{
			spaceDown = true;
		}
		default:{
			break;
		}
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	gui.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	gui.mousePressed(x, y, button);	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	gui.mouseReleased();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}



