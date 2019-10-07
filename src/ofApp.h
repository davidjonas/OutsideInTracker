#pragma once

#include "ofMain.h"
#include "ofxWebcamTracker.h"
#include "ofxGui.h"
#include "ofxOsc.h"


// send host as Multicast
#define HOST "255.255.255.255"
/// send port
#define PORT 1111

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxWebcamTracker tracker;

		//GUI
    void setupGUI();
    void drawGUI();
    void updateGUI();
		bool guiActive;
    ofxPanel calibrateGui;
    ofxFloatSlider threshold;
    ofxFloatSlider blurAmount;
    ofxToggle blur;
    ofxFloatSlider minBlobSize;
    ofxFloatSlider edgeThreshold;
    ofxFloatSlider tolerance;
    ofxToggle captureBackground;
    ofxToggle outdoorMode;
    ofxToggle showAll;
		ofxToggle render;

		//OSC
		ofxOscSender sender;
		void sendBlobs();
		bool connected;
};
