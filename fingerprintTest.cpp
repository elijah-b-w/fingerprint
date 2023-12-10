/*
Test file for fingerprint class
Tests fingerprint matching
*/

#include <iostream>
#include <string>

#include "fingerprint.h"

// change
// using namespace cv;

int main() {
    /*
    // sample making sure opencv is working
    std::string image_path = "images/101_1.tif";
    cv::Mat img = imread(image_path, IMREAD_GRAYSCALE); // read in grayscale

    // error handling
    if (img.empty()) {
        std::cout << "Image not found" << std::endl;

        return -1;
    }

    cv::namedWindow("window");
    cv::imshow("window", img);
    int k = cv::waitKey(0); // wait for a keystroke to close
    */

    // Test image 1
    const std::string imagePath = "images/101_1.tif";
    Fingerprint testPrint1 = Fingerprint(imagePath);

    // show with mask
    // testPrint1.setMask();

    // get keypoints
    testPrint1.setKeypoints();

    //  add keypoints to image
    testPrint1.displayKeypoints();

    // testPrint1.displayPrint();

    // Test image 1 copy
    // const std::string image_path2 = "images/101_1.tif";
    // Fingerprint testPrint2 = Fingerprint(image_path2);

    // get keypoints
    // testPrint2.setKeypoints();
    // testPrint2.setKeypoints();

    // Test image 2 - should match 1
    const std::string imagePath2 = "images/101_3.tif";
    Fingerprint testPrint2 = Fingerprint(imagePath2);

    testPrint2.setKeypoints();

    
    // testPrint1.fingerMatches(testPrint1, testPrint2);
    // testPrint1.displayMatches(testPrint1, testPrint2);


    /*
    // checks if prints are equal
    if (testPrint1 == testPrint2) {
        std::cout << "Success!" << std::endl;
    }
    */


    return 0;
}
