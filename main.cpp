#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <limits>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    Mat scene = imread("scene.png");
    Mat waldo = imread("waldo.png", IMREAD_UNCHANGED);

    int leastScore = std::numeric_limits<int>::max();
    int startX = 0;
    int startY = 0;

    for (int r = 0; r < scene.rows - waldo.rows + 1; r += 1) {
        for (int c = 0; c < scene.cols - waldo.cols + 1; c += 1) {
            int total = 0;
            for (int i = 0; i < waldo.rows; i++) {
                for (int j = 0; j < waldo.cols; j++) {
                    Vec4b waldoPixel = waldo.at<Vec4b>(i, j);
                    Vec3b scenePixel = scene.at<Vec3b>(i + r, j + c);
                    if (waldoPixel[3] != 0) {
                        total += (scenePixel[0] - waldoPixel[0]) * (scenePixel[0] - waldoPixel[0]) +
                                 (scenePixel[1] - waldoPixel[1]) * (scenePixel[1] - waldoPixel[1]) +
                                 (scenePixel[2] - waldoPixel[2]) * (scenePixel[2] - waldoPixel[2]);
                    }
                }
            }
            int score = total;
            if (score < leastScore) {
                leastScore = score;
                startX = r;
                startY = c;
            }
        }
    }

    Point topLeft(startY, startX);
    Point bottomRight(startY + waldo.cols, startX + waldo.rows);

    rectangle(scene, topLeft, bottomRight, Scalar(0, 255, 0), 3);
    imshow("Scene with Waldo", scene);
