#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	
	bGetSerialMessage = false;
	ofBackground(0,0,255);
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	font.loadFont("DIN.otf", 14);
	
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 115200; // baudrate is actually 125000, but setting this value is irrelevant
	serial.setup(0, baud); // open the first device
	//serial.setup("COM4", baud); // windows example
	serial.setup("/dev/tty.SLAB_USBtoUART", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
	
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
    
    
    // (1) setup digitizer
    
    // send host mode message to digitizer:
    serial.writeByte(240);
    serial.writeByte(125);
    serial.writeByte(0);
    serial.writeByte(90);
    serial.writeByte(0);
    serial.writeByte(247);
    
    // send reset message to digitizer
    serial.writeByte(240);
    serial.writeByte(125);
    serial.writeByte(0);
    serial.writeByte(34);
    serial.writeByte(247);
    
    // send interval message to digitizer to set sampling interval to 100 ms
    serial.writeByte(240);
    serial.writeByte(125);
    serial.writeByte(0);
    serial.writeByte(3);
    serial.writeByte(0);
    serial.writeByte(100);
    serial.writeByte(247);
    
    // send resolution message to digitizer to set sampling resolution to 10-bit
    serial.writeByte(240);
    serial.writeByte(125);
    serial.writeByte(0);
    serial.writeByte(2);
    serial.writeByte(64);
    serial.writeByte(247);
    
    // send stream message to digitizer to turn on continuous sampling for input 1
    serial.writeByte(240);
    serial.writeByte(125);
    serial.writeByte(0);
    serial.writeByte(1);
    serial.writeByte(64);
    serial.writeByte(247);
    
    /*
    // send stream message to digitizer to turn on continuous sampling for input 2
    serial.writeByte(240);
    serial.writeByte(125);
    serial.writeByte(0);
    serial.writeByte(1);
    serial.writeByte(65);
    serial.writeByte(247);
     */
     
}

//--------------------------------------------------------------
void testApp::update(){
	
	//if (bGetSerialMessage){
		
		// (2) read
		// now we try to read bytes
		// we may have a "lag" if we don't read fast enough
		
		nTimesRead = 0;
		nBytesRead = 0;
		int nRead  = 0;  // a temp variable to keep count per read
        int i;
		
		//unsigned char bytesReturned[100];
        memset(bytesReturned, 0, 100);
        
        // read only the sensor data message, ie. 7 bytes
		while( (nRead = serial.readBytes(bytesReturned, 7)) > 0){
			nTimesRead++;
			nBytesRead = nRead;
		};
        
   
        /*
         // read the entire buffer (of at most 100 bytes)
         while (serial.available() > 0) {
         nBytesRead++;
         bytesReturned[nBytesRead] = serial.readByte();
         }
         */
    
      
         //bytesReturnedString = "";
        if(nBytesRead > 6){
            //Just the data from input 1
            bytesReturnedString = ofToString((int)bytesReturned[4]);
        }
    
        /*
         
         for (i = 0; i < nBytesRead; i++) {
            bytesReturnedString += ofToString((int)bytesReturned[i]) + " ";
        }
    */
    
		bGetSerialMessage = false;
		readTime = ofGetElapsedTimef();
	//}
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0);
	if (nBytesRead > 0 && ((ofGetElapsedTimef() - readTime) < 0.5f)){
		//ofSetColor(200,0,0);
	} else {
		//ofSetColor(0);
	}
	string msg;
	msg += "Serial data from ICubeX:\n";
	msg += "nBytes read " + ofToString(nBytesRead) + "\n";
	msg += "nTimes read " + ofToString(nTimesRead) + "\n";
    msg += "read: " + bytesReturnedString + "\n";
	msg += "(at time " + ofToString(readTime, 3) + ")";
	font.drawString(msg, 50, 100);
    //ofDrawBitmapString(msg, 50, 100);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	
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
	bGetSerialMessage = true;
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

