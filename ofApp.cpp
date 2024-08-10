#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofNoFill();
	ofSetCircleResolution(60);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofColor color;
	for (int i = 0; i < 15; i++) {

		this->location_list.push_back(glm::vec2(ofRandom(-300, 300), ofRandom(-300, 300)));
		this->life_list.push_back(0);

		color.setHsb((ofGetFrameNum() * 3) % 255, 255, 255);
		this->color_list.push_back(color);
	}

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		if (glm::length(this->location_list[i]) > 250) {

			this->location_list.erase(this->location_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		auto deg = ofMap(ofNoise(this->location_list[i].x * 0.01, this->location_list[i].y * 0.01, ofGetFrameNum() * 0.01), 0, 1, -360, 360);
		auto next = this->location_list[i] + glm::vec2(5 * cos(deg * DEG_TO_RAD), 5 * sin(deg * DEG_TO_RAD));

		for (int k = i + 1; k < this->location_list.size(); k++) {

			auto distance = glm::distance(this->location_list[i], this->location_list[k]);
			if (distance < 40) {

				ofSetColor(this->color_list[i], ofMap(distance, 0, 40, 255, 0));
				ofDrawLine(this->location_list[i], this->location_list[k]);
			}
		}

		ofSetColor(this->color_list[i]);
		ofDrawCircle(this->location_list[i], 3);
		
		this->location_list[i] = next;
		this->life_list[i] += 4;
	}

	ofSetColor(255);
	ofDrawCircle(glm::vec2(), 250);

	/*
	int start = 300;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}