#ifndef FINGERPRINT_H
#define FINGERPRINT_H

// image reading functionality
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/photo.hpp>

// change
// using namespace cv;

class Fingerprint {
public:
    // constructors
    Fingerprint();
    Fingerprint(const std::string fileName);
    virtual ~Fingerprint();

    // gets and sets
    // sets
    void setKeypoints();
    void setMask();
    // gets
    std::vector<cv::KeyPoint> getKeypoints();
    cv::Mat getDescriptors();

    // finds matches
    std::vector<cv::DMatch> fingerMatches(const Fingerprint& finger1, const Fingerprint& finger2);

    // equals operations
    friend bool operator==(const Fingerprint& lhs, const Fingerprint& rhs);
    friend bool operator!=(const Fingerprint& lhs, const Fingerprint& rhs);

    // displays points for testing
    void displayPrint();        // displays fingerprint
    void displayKeypoints();    // diplays image with keypoints
    void displayMatches(const Fingerprint& finger1, const Fingerprint& finger2); // displays matches

private:
    cv::Mat image;              // image of fingerprint
    std::vector<cv::KeyPoint> keyPoints;    // vector to store keypoints in
    cv::Mat descriptors;        // descriptions of matching keypoints

};

#endif // FINGERPRINT_H
