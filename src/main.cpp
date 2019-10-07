#include "ofMain.h"
#include "ofApp.h"

int main( ){
	ofGLFWWindowSettings settings;
	settings.setSize(1920, 1080);
	settings.windowMode = OF_WINDOW;
	settings.resizable = false;
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
