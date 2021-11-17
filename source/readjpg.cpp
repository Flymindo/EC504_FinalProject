#include <iostream>
#include "../opencv/build/install/include/opencv2/highgui.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    cv::String s(argv[1]);
    cv::Mat im = cv::imread(s);

    cv::imshow("image", im);

    int key = cv::waitKey(0);

    if (key == 'q') {
        cv::destroyAllWindows();
    }
    
    return EXIT_SUCCESS;
}
