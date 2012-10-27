#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetFrameRate(60);
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofBackground(0xFFFFFF);
	
	//
	// Box2d
	//
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.createGround();
	box2d.setFPS(60.0);
	box2d.registerGrabbing();
	
	// Circles
	float radius;
	for (int i = 0; i < 160; i++) {
		radius = ofRandom(4, 20);
		ofxBox2dCircle circle;
		
		circle.setPhysics(3.0, 0.53, 0.1);
		circle.setup(box2d.getWorld(), ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), radius);
		circles.push_back(circle);
		
		//
		isDrawLines.push_back(false);
		//
		motionVectors.push_back(ofVec2f(1, 0));
		// distances
		distances.push_back(50000);
	}
}

//--------------------------------------------------------------
void testApp::update() {
	float range = 50000;
	float theta;
	float angle;
	float distance;
	
	box2d.update();
	for (int i = 0; i < circles.size(); i++) {
		ofxBox2dCircle circle = circles[i];
		ofVec2f position = circle.getPosition();
		ofVec2f velocity = circle.getVelocity();
		distance = ofDistSquared(position.x, position.y, mouseX, mouseY);
		theta = atan2(mouseX - position.x, mouseY - position.y) - (PI/2);
		angle = ofRadToDeg(theta);
		if (distance < range) {
			ofVec2f v = motionVectors[i];
			isDrawLines[i] = true;
			v.x = (range - distance) / 6000;
			v.y = 0;
			v.rotate(angle);
			v.x = -v.x;
			circle.setVelocity(v.x, v.y);
//			circle.setVelocity(v.x + velocity.x, v.y + velocity.y);
			distances[i] = distance;
		} else {
			isDrawLines[i] = false;
		}
	}
}

//--------------------------------------------------------------
void testApp::draw() {
	int l = circles.size();
	float range = 50000;
	for(int i = 0; i < l; i++) {
		ofFill();
		ofSetColor(144, 212, 243 / (range / distances[i]));
		
		fixEdge(circles[i]);
		circles[i].draw();
	}
	for(int i = 0; i < l; i++) {
		if (isDrawLines[i]) {
			ofSetColor(0, 0, 0, 120);
			ofVec2f position = circles[i].getPosition();
			ofSetLineWidth(0.2);
			ofLine(position.x, position.y, mouseX, mouseY);
			ofDrawBitmapStringHighlight(ofToString(floor(distances[i])), position.x + 10, position.y - 10);
		}
	}
	
	ofSetHexColor(0x000000);
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 0, 20);
}

//--------------------------------------------------------------
void testApp::fixEdge(ofxBox2dCircle circle) {
	float radius = circle.getRadius();
	ofVec2f p = circle.getPosition();
	ofVec2f v = circle.getVelocity();
	if (p.x < radius) {
		circle.setPosition(radius, p.y);
		circle.setVelocity(0, v.y);
	} else if (p.x > ofGetWidth() - radius) {
		circle.setPosition(ofGetWidth() - radius, p.y);
		circle.setVelocity(0, v.y);
	}
	if (p.y < radius) {
		circle.setPosition(p.x, radius);
		circle.setVelocity(v.x, 0);
	} else if (p.y > ofGetHeight() - radius) {
		circle.setPosition(p.x, ofGetHeight() - radius);
		circle.setVelocity(v.x, 0);
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}