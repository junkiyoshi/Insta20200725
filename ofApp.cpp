#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);

	this->fbo.allocate(ofGetWidth() + 25, ofGetHeight() + 25);
	this->fbo.readToPixels(this->pixels);
	this->pixels_mat = cv::Mat(this->pixels.getHeight(), this->pixels.getWidth(), CV_8UC4, this->pixels.getData());
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int radius = 240; radius > 0; radius -= 60) {

		int deg_start = ofRandom(360) + ofGetFrameNum() * ofRandom(2, 4);
		vector<glm::vec2> vertices;
		for (int deg = deg_start; deg < deg_start + 360; deg += 90) {

			vertices.push_back(glm::vec2(ofGetWidth() * 0.5 + radius * cos(deg * DEG_TO_RAD), ofGetHeight() * 0.5 + radius * sin(deg * DEG_TO_RAD)));
		}

		// ‰e
		this->fbo.begin();
		ofClear(0);

		ofSetColor(0);
		ofFill();
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofPopMatrix();
		this->fbo.end();
		this->fbo.readToPixels(this->pixels);

		cv::GaussianBlur(this->pixels_mat, this->pixels_mat, cv::Size(11, 11), 10, 10);

		// ŽÀ‘Ì
		this->fbo.begin();
		ofClear(0);

		ofSetColor(239);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofSetColor(39);
		ofNoFill();
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		this->fbo.end();

		// •`ŽÊ
		ofSetColor(255);
		ofImage draw_image;
		draw_image.setFromPixels(this->pixels);
		draw_image.draw(-5, -5);

		this->fbo.draw(-15, -15);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(512, 512, OF_WINDOW);
	ofRunApp(new ofApp());
}