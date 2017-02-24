//
//  ofxSlideShow.cpp
//  
//
//  Created by Guillaume Arseneault on 16-10-16.
//
//

// todo fixer le bug d'index quand on fait preview au lieu de next.

#include "ofxSlideshow.h"

void ofxSlideshow::setup(int width, int height){
    canvasWidth = width;
    canvasHeight = height;
    
    images.resize(3);
    imgWidth.resize(3);
    imgHeight.resize(3);
    canvasFbo.allocate(canvasWidth, canvasHeight, GL_RGBA);
    
    debug = false;
    
}

void ofxSlideshow::setupGui(){
    slideshowGui.setup("slideshow");
    slideshowGui.setName("slideshow");
    slideshowGui.add(imgNext.setup("next"));
    slideshowGui.add(imgPrev.setup("prev"));
    slideshowGui.add(backgroundOpacity.set("opacity", 1, 0.0, 1.0));
    slideshowGui.add(reloadFolder.set("reloadFolder",0, 0, 1));
    
    imgNext.addListener(this, &ofxSlideshow::next);
    imgPrev.addListener(this, &ofxSlideshow::prev);

}




void ofxSlideshow::resize(int width, int height){
    canvasWidth = width;
    canvasHeight = height;
    canvasFbo.allocate(canvasWidth, canvasHeight, GL_RGBA);
}


void ofxSlideshow::loadDir(string folder){
    
    folderName = folder;
    string path = folder;
    ofDirectory dir(path);
    dir.allowExt("jpg");
    dir.listDir();
    dir.sort();
    dir.listDir();
    frameTotal = dir.size();
    
    // erreur a catcher s'il n y a pas de folder.
    
    // storer les path des images dans un vector de string
    for (int i = 0; i < dir.size(); i++){
        imagePath.push_back (dir.getPath(i));
        
    }
    
    for (int i = 0; i < images.size(); i++){
        loader.loadFromDisk(images[i], imagePath[(i+imagePath.size()-1)%imagePath.size()]);
        playHead = 0;
        playHeadNames[i] =imagePath[i];
    }
    
    // identifier la resolution optimale afin d allouer un fbo assez grand
    
}



void ofxSlideshow::next(){
// loader dans une slot vide une image next, partir la transition vers la next
    //nextFrame = 1;
    
    if(lastDirection == -1) {
        frameNow = (frameNow+frameTotal+3)%frameTotal;
        
    }
    
    else {
        frameNow = (frameNow+frameTotal+1)%frameTotal;
        
    }
    playHead = (playHead+images.size()+1)%images.size();
    loadHead = (playHead+images.size()+1)%images.size();
    loader.loadFromDisk(images[loadHead], imagePath[frameNow]);
    playHeadNames[loadHead] =imagePath[loadHead];
    
    
    
    lastDirection = 1;
    
    if (debug){
    cout<< "frame now " << frameNow << " playHead " <<playHead << " loadHead "<< loadHead << " path "<<imagePath[frameNow]<< endl;
    }

    
}





void ofxSlideshow::prev(){
// loader dans une slot vide une image prev, partir la transition vers la prev
    //prevFrame = 1;
    
    //prevFrame = 0 ;
    
    if (lastDirection == 1 ){
        frameNow = (frameNow+frameTotal-3)%frameTotal;
        
    }
    else {
        frameNow = (frameNow+frameTotal-1)%frameTotal;
    }
    
    playHead = (playHead+images.size()-1)%images.size();
    loadHead = (playHead+images.size()-1)%images.size();
    loader.loadFromDisk(images[loadHead], imagePath[frameNow]);
    playHeadNames[loadHead] =imagePath[loadHead];
    

    
    lastDirection = -1;
    
    if(debug){
    cout<< "frame now " << frameNow << " playHead " <<playHead << " loadHead "<< loadHead << " path "<<imagePath[frameNow]<< endl;
    }
}


void ofxSlideshow::update(){
    
    if (reloadFolder){
        loadDir(folderName);
        reloadFolder = false;
    }
    
   
    if (oldPlayHeadIndex!=frameNow){
        actualPlayHeadName = imagePath[(frameNow-1+frameTotal)%frameTotal];
        actualPlayHeadName.erase(0, folderName.length()+1);
        oldPlayHeadIndex = frameNow;
    }
    
    canvasFbo.begin();
    ofClear(0);
    ofSetColor(255);
    images[playHead].draw(0, 0, canvasWidth , canvasHeight);
    
    if (debug){
    // draw the array of images
    for(int i = 0; i < (int)images.size(); ++i) {
        int x = (i%8);
        int y = (i/8);
        images[i].draw(x*64,y*64, 64,64);
    }
    
    ofSetColor(255, 0, 0);
    ofDrawRectangle(playHead*64+32, 64, 10, 10);
    }
    
    
    canvasFbo.end();
   

}



void ofxSlideshow::draw(int originX, int originY, int width, int height){
    ofPushStyle();
    ofSetColor(255*backgroundOpacity);
    canvasFbo.draw(originX,originY,width,height);
    ofPopStyle();
}


void ofxSlideshow::exit (){
    
    loader.stopThread();
    cout<<"killing ofxThreadedImageLoader thread"<<endl;

}



