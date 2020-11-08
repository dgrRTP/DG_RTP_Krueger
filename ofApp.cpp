#include "ofApp.h"
void ofApp::dilate(ofImage & threshold, ofImage & imgDest) {
	for (int i = 0; i < threshold.getWidth(); i++) {
		for (int j = 0; j < threshold.getHeight(); j++) {

			// step determines "thickness" of edge offsets
			int step = 4;
			int twostep = (step * 3);

			// constrain values to stay within canvas edges:
			int i_m_1 = ofClamp(i - step, 0, threshold.getWidth() - step);
			int i_p_1 = ofClamp(i + step, 0, threshold.getWidth() - step);
			int j_m_1 = ofClamp(j - step, 0, threshold.getHeight() - step);
			int j_p_1 = ofClamp(j + step, 0, threshold.getHeight() - step);

			int i_m_2 = ofClamp(((i_m_1)-twostep), 0, threshold.getWidth() - step);
			int i_p_2 = ofClamp(((i_p_1)+twostep), 0, threshold.getWidth() - step);
			int j_m_2 = ofClamp(((j_m_1)-twostep), 0, threshold.getHeight() - step);
			int j_p_2 = ofClamp(((j_p_1)+twostep), 0, threshold.getHeight() - step);


			// neighbour values
			ofColor n_ = threshold.getColor(i, j_p_1);
			ofColor ne = threshold.getColor(i_p_1, j_p_1);
			ofColor e_ = threshold.getColor(i_p_1, j);
			ofColor se = threshold.getColor(i_p_1, j_m_1);
			ofColor s_ = threshold.getColor(i, j_m_1);
			ofColor sw = threshold.getColor(i_m_1, j_m_1);
			ofColor w_ = threshold.getColor(i_m_1, j);
			ofColor nw = threshold.getColor(i_m_1, j_p_1);

			if (n_.getBrightness() < 127 ||
				ne.getBrightness() < 127 ||
				e_.getBrightness() < 127 ||
				se.getBrightness() < 127 ||
				s_.getBrightness() < 127 ||
				sw.getBrightness() < 127 ||
				w_.getBrightness() < 127 ||
				nw.getBrightness() < 127) {
				imgDest.setColor(i, j, ofColor(0));

				//v1. "Waves" 
				imgDest.setColor(i_m_1, j_m_1, ofColor(255));
				imgDest.setColor(i_p_1, j_m_1, ofColor(0));

				// v2. Dilation
				//imagePass1.setColor(i_p_2, j_m_2, ofColor(0));
				//imagePass1.setColor(i_p_2, j_p_2, ofColor(255));



			}
			else {
				imgDest.setColor(i, j, ofColor(255));
				//imgDest.setColor(i_p_2, j_p_2, ofColor(255));

			}


		}
	}
	imgDest.update();
	imagePass1.update();

}
//--------------------------------------------------------------
void ofApp::setup(){
	//grabber.listDevices();
	grabber.setDeviceID(0);
	grabber.setup(640, 480);

	threshold.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_COLOR);
	imagePass1.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_COLOR);
	imgDest.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_COLOR);
	imgFinal.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_COLOR);

	//threshold.update();
	dilate(threshold, imgDest);
	imgDest.update();

}

//--------------------------------------------------------------
void ofApp::update(){
	grabber.update();
	if (grabber.isFrameNew()) {
		for (int i = 0; i < grabber.getWidth(); i++) {
			for (int j = 0; j < grabber.getHeight(); j++) {
				ofColor color = grabber.getPixels().getColor(i, j);
				// constrain values to stay within canvas edges:

				if (color.getBrightness() > mouseX) {
					threshold.setColor(i, j, ofColor(0));
				} else {
					threshold.setColor(i, j, ofColor(34,125,234));
				}
			}
		}
		}
	threshold.update();
	dilate(threshold, imagePass1);
	dilate(imagePass1, imgDest);
	}


//--------------------------------------------------------------
void ofApp::draw(){
	//grabber.draw(0,0);
	threshold.draw(0, 0);
	imagePass1.draw(grabber.getWidth(),0 );
	imgFinal.draw((2 * grabber.getWidth()), 0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	for (int i = 0; i < threshold.getWidth(); i++) {
		for (int j = 0; j < threshold.getHeight(); j++) {
			ofColor c = imagePass1.getColor(i, j);
			ofColor f = imgFinal.getColor(i, j);
			if (c.getBrightness() < f.getBrightness()) {
				imgFinal.setColor(i, j, ofColor(0));
			}	else {
				//imgFinal.setColor(i, j, ofColor(255));
			}

			
		}
	}
	
	imgFinal.update();

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
