
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

    // TODO - find core?

    // TODO - add mask around edge?


    // sift algorithm for finding keypoints
    // cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create();
    cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create(100, 3, 0.04, 30, 1.6);

    // get keypoints of image
    siftPtr->detect(image, keyPoints);

    // get descriptors from keypoints
    siftPtr->compute(image, keyPoints, descriptors);

}

// Adds a mask around the fingerprint
void Fingerprint::setMask() {
    // TODO - find core

    // set mask center point to core
    // TEMP - make center of image
    // cv::Point core(image.cols / 2, image.rows / 2);
    cv::Point core(145, 200);

    // add mask around the core - radius of 125px
    const int radius = 125;

    cv::Mat mask(image.size(), image.type());
    mask.setTo(0);  // initialize to be empty
    
    // sets mask as a circle around the core
    cv::circle(mask, core, radius, 255, -1);

    // apply mask to fingerprint
    // cv::Mat maskedPrint = cv::bitwise_and(image, image, mask);

    // apply mask to fingerprint
    cv::bitwise_and(image, image, mask=mask);

    // TODO - change to a return mask

    // show masked fingerprint
    // cv::namedWindow("window");
    cv::imshow("mask", mask);
    int k = cv::waitKey(0); // wait for a keystroke to close

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
    
    

    // best fit
    /*
    // finds matches between the two
    
    cv::Ptr <cv::DescriptorMatcher> bfMatcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
    std::vector<std::vector<cv::DMatch>> matches;

    bfMatcher->knnMatch(finger1.descriptors, finger2.descriptors, matches, 2);
    // bfMatcher->match(finger1.descriptors, finger2.descriptors, matches);
    

    // TODO - add parameter checks - put in a vector
    std::vector<cv::DMatch> goodMatches;

    // append if good matches
    for (int i = 1; i < matches.size(); i++) {
        //
    }
    

    return goodMatches;
    */

    /*
    // best fit sorted
    // finds matches between the two
    cv::Ptr <cv::DescriptorMatcher> bfMatcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
    std::vector<cv::DMatch> matches;

    bfMatcher->match(finger1.descriptors, finger2.descriptors, matches);

    // sort by distance between matches
    // cv::sort(matches, matches, cv::SORT_ASCENDING);

    return matches;
    */

    /*
    // store the first 50 matches or have best fit
    const double ratio = 0.75;
    int count = 0;
    std::vector<cv::DMatch> goodMatches;

    
    for (cv::DMatch i : matches) {
        // add to good matches
        goodMatches.append(i);

        // keep track of at most 50 points
        count++;

        if (count > 50) {
            break;
        }


    }
    */
    

    /*
    while (index < 50 && index < matches.size()) {
        if (matches.at(index).distance < ratio * (matches.at(index + 1).distance)) {
            goodMatches.append(cv::DMatch(matches.at(index));
        }
        else
        {
            break;
        }
    }
    */
    

    // return goodMatches;

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
    // TODO - get keypoints


    // TODO - color code keypoints by type
    // cv::drawKeypoints(image, keyPoints, image, cv::IMREAD_GRAYSCALE, cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
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


    /*
    cv::Ptr <cv::DescriptorMatcher> bfMatcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
    std::vector<std::vector<cv::DMatch>> matches;

    bfMatcher->knnMatch(finger1.descriptors, finger2.descriptors, matches, 2);
    // bfMatcher->match(finger1.descriptors, finger2.descriptors, matches);

    cv::Mat matchesImage = cv::drawMatchesKnn
    cv::imshow("Fingerprint matches", matchesImage);
    int k = cv::waitKey(0); // wait for a keystroke to close
    */
}


/*
// checks if the fingerprints are equal
bool operator==(const Fingerprint& lhs, const Fingerprint& rhs) {
    // gets the descriptors from the fingerprints
    const cv::Mat DFinger1 = lhs.descriptors;
    const cv::Mat DFinger2 = rhs.descriptors;

    // finds matches between the two
    // std::vector<cv::DMatch> matches;
    // cv::Ptr <cv::BFMatcher> bfPtr = cv::BFMatcher::create(2, true);
    // matches = bfPtr->knnMatch(lhs.descriptors, rhs.descriptors);

    // matches = knnMatch(DFinger1, DFinger2, 2);
    // std::vector<cv::DMatch> matches;
    // cv::DescriptorMatcher::knnMatch(DFinger1, DFinger2, matches);
    // std::vector<cv::DMatch> matches = bfPtr->match(DFinger1, DFinger2);


    // cv::DescriptorMatcher::knnMatch(DFinger1, DFinger2, matches, 50);
    

    // cv::DescriptorMatcher::knnMatch(DFinger1, DFinger2, matches, 50);
    // bfPtr->knnMatch(DFinger1, DFinger2, 2);
    // bfPtr->knnMatch(DFinger1, DFinger2, 2);

    // TODO - compare

    // TODO - return true if over a certain match %

    // cv::Ptr <cv::DescriptorMatcher> cv::DescriptorMatcher::create;



    // finds matches between the two
    cv::Ptr <cv::DescriptorMatcher> bfMatcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
    std::vector<cv::DMatch> matches;

    bfMatcher->match(lhs.descriptors, rhs.descriptors, matches);

    // TODO - add parameter checks



    // draw matches
    cv::Mat imgMatches;
    



    return true;
}
*/




/*
// gets keypoints from fingerprint
void Fingerprint::getKeypoints() {
    // TODO - clear background

    // TODO - get keypoints

    // smooth image
    // cv::fastNlMeansDenoising(image, image);
    cv::fastNlMeansDenoising(image, image, 30);


    // sift algorithm for finding keypoints
    // cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create();
    // std::vector<cv::KeyPoint> keyPoints;    // vector to store keypoints in

    // sift algorithm for finding keypoints
    // cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create(50, 3, 0.04, 30, 1.6);
    cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create();

    siftPtr->detect(image, keyPoints);      // get keypoints and store in vector

    // TODO - save the keypoints into object?
}
*/

/*
// gets keypoints from fingerprint
void Fingerprint::getKeypoints() {
    // smooth image
    cv::fastNlMeansDenoising(image, image, 30);

    // TODO - add filter around edge?

    // TODO - find core?

    // sift algorithm for finding keypoints
    // cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create(50, 3, 0.04, 30, 1.6);
    cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create();

    // siftPtr->detect(image, keyPoints);      // get keypoints and store in vector
    // siftPtr->detectAndCompute(image, None, keyPoints, );      // get keypoints and store in vector

    // get keypoints
    // siftPtr->detect(image, keyPoints);

    // compute
    // siftPtr->compute(image, keyPoints, descriptors);

    // TODO - save the keypoints into object?
}
*/

/*
// gets keypoints from fingerprint
void Fingerprint::getKeypoints() {
    // smooth image
    cv::fastNlMeansDenoising(image, image, 30);

    // TODO - find core?

    // TODO - add mask around edge?


    // sift algorithm for finding keypoints
    // cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create(50, 3, 0.04, 30, 1.6);
    cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create();

    // siftPtr->detect(image, keyPoints);      // get keypoints and store in vector
    // siftPtr->detectAndCompute(image, None, keyPoints, );      // get keypoints and store in vector

    // get keypoints
    // siftPtr->detect(image, keyPoints);

    // compute
    // siftPtr->compute(image, keyPoints, descriptors);

    // TODO - save the keypoints into object?
}
*/
