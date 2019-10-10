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
  tracker.setOutdoorModeBgRefreshRate(10);
  tracker.setOutdoorModeMinSpeed(0);
  setupGUI();

  //OSC
  connected = sender.setup(HOST, PORT);
  if(connected){
    ofLogNotice("OutsideInTracker") << "Successfuly connected";
  }
  else {
    ofLogNotice("OutsideInTracker") << "Error connecting to server";
  }
}

//--------------------------GUI---------------------------------
void ofApp::setupGUI()
{
	guiActive = true;
	calibrateGui.setup("Calibrate", "calibrate.xml", 10, 10);
	calibrateGui.add(threshold.setup("Threshold", 5, 0.0, 255.0));
	calibrateGui.add(blurAmount.setup("Blur Amount", 9.0, 0.0, 100.0));
	calibrateGui.add(blur.setup("Blur", false));
	calibrateGui.add(minBlobSize.setup("Minimum Blob Area", 100.0, 0.0, 1000.0));
	calibrateGui.add(edgeThreshold.setup("Edge Threshold", 10.0, 0.0, 100.0));
	calibrateGui.add(tolerance.setup("Tracker tolerance", 50.0, 10.0, 500.0));
	calibrateGui.add(captureBackground.setup("Capture Background", false));
	calibrateGui.add(outdoorMode.setup("Outdoor Mode", true));
	calibrateGui.add(showAll.setup("Show all", false));
	calibrateGui.add(render.setup("render", true));

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
  tracker.update();
  if(tracker.getNumActiveBlobs() > 0){
    sendBlobs();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(46, 51, 55);
  if(render){
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
  }

  drawGUI();

  if(guiActive)
  {
    ofSetColor(46, 51, 55, 80);
    ofFill();
		ofDrawRectangle(10, 250, 210, 50);
    ofSetColor(46, 255, 55, 255);
    if(connected){
      ofDrawBitmapString("Connected to server", 15, 265);
      ofDrawBitmapString("Persons: " + to_string(tracker.getNumActiveBlobs()), 15, 295);
    }
    else {
      ofSetColor(46, 55, 255, 255);
      ofDrawBitmapString("Failed connection...", 15, 265);
      ofSetColor(46, 255, 55, 255);
      ofDrawBitmapString("Persons: " + to_string(tracker.getNumActiveBlobs()), 15, 295);
    }
  }
}

void ofApp::sendBlobs(){
  ofxOscMessage m;
  ofJson blobsJson;
  vector<ofxWebcamBlob> blobs = tracker.getActiveBlobs();

  for(vector<ofxWebcamBlob>::iterator b=blobs.begin(); b<blobs.end(); b++)
  {
    ofJson blob;

    blob["id"] = b->id;
    blob["speed"] = b->speed;
    blob["direction"]["x"] = b->direction.x;
    blob["direction"]["y"] = b->direction.y;
    blob["position"]["x"] = b->blob.centroid.x/(float)tracker.getWidth();
    blob["position"]["y"] = b->blob.centroid.y/(float)tracker.getHeight();
    blob["overlap"] = b->isOverlapping();

    blobsJson.push_back(blob);
    if(blobsJson.size() > 4){
      m.setAddress("/blobs");
    	m.addStringArg(blobsJson.dump());
    	sender.sendMessage(m, false);
      blobsJson.clear();
    }
  }

	m.setAddress("/blobs");
	m.addStringArg(blobsJson.dump());
	sender.sendMessage(m, false);
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
