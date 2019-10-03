#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  vector<ofVideoDevice> devices = tracker.getDevices();
  vector<ofVideoDevice> active;
  ofLogNotice("Example:") << "We have " << devices.size() << " cameras connected.";
  if(devices.size() > 1)
  {
    ofLogNotice("Example:") << "Setting up camera: " << devices[0].deviceName;
    active.push_back(devices[0]);
  }
  tracker.init(active);

  //tracker.grabBackground();
  setupGUI();
}

//--------------------------GUI---------------------------------
void ofApp::setupGUI()
{
	guiActive = true;
	calibrateGui.setup("Calibrate", "calibrate.xml", 10, 10);
	calibrateGui.add(threshold.setup("Threshold", 5, 0.0, 255.0));
	calibrateGui.add(blurAmount.setup("Blur Amount", 9.0, 0.0, 100.0));
	calibrateGui.add(blur.setup("Blur", false));
	calibrateGui.add(minBlobSize.setup("Minimum Blob Area", 100.0, 0.0, (tracker.getWidth()*tracker.getHeight())/2));
	calibrateGui.add(edgeThreshold.setup("Edge Threshold", 10.0, 0.0, 100.0));
	calibrateGui.add(tolerance.setup("Tracker tolerance", 50.0, 10.0, 500.0));
	calibrateGui.add(captureBackground.setup("Capture Background", false));
	calibrateGui.add(outdoorMode.setup("Outdoor Mode", true));
	calibrateGui.add(showAll.setup("Show all", false));

	calibrateGui.loadFromFile("calibrate.xml");
}

void ofApp::drawGUI() {
	if(guiActive)
  {
		calibrateGui.draw();
	}
}

void ofApp::updateGUI() {
	tracker.setThreshold(threshold);
	tracker.setBlurAmount(blurAmount);
	tracker.setBlur(blur);
	tracker.setMinBlobSize(minBlobSize);
	tracker.setEdgeThreshold(edgeThreshold);
	tracker.setTolerance(tolerance);
  tracker.setOutdoorMode(outdoorMode);

	if(captureBackground){
		captureBackground = false;
		tracker.grabBackground();
	}
}

//--------------------------------------------------------------
void ofApp::update(){
  updateGUI();
  ofBackground(46, 51, 55);
  tracker.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  if(showAll)
	{
		tracker.drawDebug(0,0,3);
	}
	else
	{
		tracker.drawRGB(0,0,3);
		tracker.drawContours(0,0,3);
		tracker.drawBlobPositions(0,0,3);
		tracker.drawEdgeThreshold(0,0,3);
	}

  drawGUI();

  if(guiActive)
  {
    ofSetColor(46, 51, 55, 30);
    ofFill();
		ofDrawRectangle(10, 200, 210, 50);
    ofSetColor(46, 255, 55, 255);
		ofDrawBitmapString("Persons: " + to_string(tracker.getNumActiveBlobs()), 15, 225);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  switch (key){
		case ' ':
			tracker.grabBackground();
			break;
    case '\t':
      guiActive = !guiActive;
      break;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
