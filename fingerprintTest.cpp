/*
Test file for fingerprint class
Tests fingerprint matching

sample prints from: http://bias.csr.unibo.it/fvc2000/db3.asp
*/

#include <iostream>
#include <string>

#include "fingerprint.h"

// change
// using namespace cv;

int main() {

    // Test image 1
    const std::string imagePath = "images/101_1.tif";
    Fingerprint testPrint1 = Fingerprint(imagePath);


    // get keypoints
    testPrint1.setKeypoints();

    // Test image 2 - should match 1
    const std::string imagePath2 = "images/101_3.tif";
    Fingerprint testPrint2 = Fingerprint(imagePath2);

    testPrint2.setKeypoints();

    
    testPrint1.fingerMatches(testPrint1, testPrint2);
    


    return 0;
}
