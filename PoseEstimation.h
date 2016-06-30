#pragma once
#define _USE_MATH_DEFINES

#include "OSDetect.h"

#include <math.h>

#if __AR_USER_ == 0
    #include <opencv/cv.h>
#else
    #include <opencv2/opencv.hpp>
#endif

#include <opencv/cxcore.h>
#include <vector>
#include <algorithm>
#include <iostream>

/** 
 * computes the orientation and translation of a square
 * @param result result as 4x4 matrix
 * @param p2D coordinates of the four corners in clock-wise order. 
 *        the origin is assumed to be at the camera's center of projection
 * @param markerSize side-length of marker. Origin is at marker center.
 */
void estimateSquarePose_( float* result,  CvPoint2D32f* p2D, float markerSize );


void estimateSquarePose( float* result, const cv::Point2f* p2D_, float markerSize );
/**
 * Returns Matrix in Row-major format
 * @param result a 3x3 homogeneous matrix
 * @param quadrangle the coordinates of the corners counter-clockwise
 */
void calcHomography( float* pResult, const CvPoint2D32f* pQuad );
