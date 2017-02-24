//
//  Slideshow.hpp
//  pix2osc
//
//  Created by Guillaume Arseneault on 16-10-16.
//
//

#ifndef ofxSlideshow_h
#define ofxSlideshow_h



#include "ofMain.h"
#include "ofxThreadedImageLoader.h"
#include "ofxGui.h"


class ofxSlideshow {
    
public:
    void setup(int width, int height);
    void setupGui();
    void resize (int width, int height);
    void loadDir(string folder);
    void exit();
    void load(int id, int index);
    void next();
    void prev();
    void update();
    void draw(int originX, int originY, int width, int height);
   
    
//    void imgNextChanged();
//    void imgPrevChanged();
    
    bool debug = false;
    
    vector<int> imgWidth;
    vector<int> imgHeight;
    
    int canvasWidth;
    int canvasHeight;
    int frameTotal;
    
    int playhead;
    
    
    ofFbo canvasFbo;
    
    bool nextFrame = 0;
    bool prevFrame = 0;
    int lastDirection = 0;
    int frameNow = 0;
    int playHead = 0;
    int loadHead = 0;
    

    
    vector<ofImage> images;
    ofxThreadedImageLoader loader;
    vector<string> imagePath;
  
    ofxGuiGroup slideshowGui;
   
    ofParameter <float> backgroundOpacity =1;
    ofxButton imgNext;
    ofxButton imgPrev;
    ofParameter <bool> reloadFolder;
    
    string folderName;
    string playHeadNames[3];
    string actualPlayHeadName;
    int oldPlayHeadIndex = 5;
    
    
    
};

#endif /* ofxSlideShow.h */
