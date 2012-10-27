#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class testApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void checkEdge(float radius);
	void fixEdge(ofxBox2dCircle circle);
    
	ofxBox2d box2d;
	vector<ofVec2f> motionVectors;
	vector<float> distances;
	vector<bool> isDrawLines;
	vector<ofxBox2dCircle> circles;
};
