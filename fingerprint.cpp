
#include "fingerprint.h"

Fingerprint::Fingerprint() {
    //ctor
}

Fingerprint::Fingerprint(const std::string fileName) {
    // image is file
    image = cv::imread(fileName, cv::IMREAD_GRAYSCALE); // read in grayscale

}

Fingerprint::~Fingerprint() {
    //dtor
}


// gets keypoints from fingerprint
void Fingerprint::setKeypoints() {
    // smooth image
    cv::fastNlMeansDenoising(image, image, 30);

    // sift algorithm for finding keypoints
    const int numFeatures = 100;			// number of best features to keep
    const int nOctaveLayers = 3;			// number of layers in each octave (3 default)
    const double contrastThreshold = 0.04;	// filters out low-contrast areas (0.04 default)
    const double edgeThreshold = 30;		// filters edge like features (10 default)
    const double sigma = 1.6;				// applied to octave0 (1.6 default)
    
    // set up algorithm
    cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create(numFeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);

    // get keypoints of image
    siftPtr->detect(image, keyPoints);

    // get descriptors from keypoints
    siftPtr->compute(image, keyPoints, descriptors);

}


// gets and sets
std::vector<cv::KeyPoint> Fingerprint::getKeypoints() {
    return keyPoints;
}

cv::Mat Fingerprint::getDescriptors() {
    return descriptors;
}


// finds the matches between two prints
std::vector<cv::DMatch> Fingerprint::fingerMatches(const Fingerprint& finger1, const Fingerprint& finger2) {
    // Bruteforce
    // finds matches between the two
    cv::Ptr <cv::DescriptorMatcher> bfMatcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
    std::vector<cv::DMatch> matches;

    bfMatcher->match(finger1.descriptors, finger2.descriptors, matches);

    return matches;
    
    

}

bool operator==(const Fingerprint& lhs, const Fingerprint& rhs) {
    // finds matches between the two
    

    // TODO - add parameter checks

    return true;
}

bool operator!=(const Fingerprint& lhs, const Fingerprint& rhs) {
    return !(lhs == rhs);
}

// displays image with keypoints to screen
void Fingerprint::displayPrint() {
    
    cv::drawKeypoints(image, keyPoints, image, 1, cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    // display to screen
    cv::namedWindow("window");
    cv::imshow("window", image);
    int k = cv::waitKey(0); // wait for a keystroke to close
}

// draws keypoints to image
void Fingerprint::displayKeypoints() {
    // checks keypoints found
    if (keyPoints.size() < 1) {
        setKeypoints();
    }

    // draw keypoints to fingerprint
    cv::drawKeypoints(image, keyPoints, image);
}

// displays the matches between two prints
void Fingerprint::displayMatches(const Fingerprint& finger1, const Fingerprint& finger2) {

    // find matches between the two
    std::vector<cv::DMatch> matches = fingerMatches(finger1, finger2);

    // draw matches
    cv::Mat matchesImage;
    cv::drawMatches(finger1.image, finger1.keyPoints, finger2.image, finger2.keyPoints, matches, matchesImage);
    int k = cv::waitKey(0); // wait for a keystroke to close


}
