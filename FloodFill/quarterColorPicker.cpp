/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 2023S PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"
#include <cmath>
#define PI 3.14159265

QuarterColorPicker::QuarterColorPicker(PNG& inputimg)
{
    referenceimg = PNG(inputimg);
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image.
 *
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the H/S/L/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 *
 * Since interpolation will be the exact average between exactly two pixels, then
 * the Hue channel should be averaged over the shortest arc between the two values.
 * e.g. The average of H_1 = 10 and H_2 = 320 is H_avg = 345 and NOT 165.
 * In the case of two diametric hues being averaged, e.g. 10 and 190, the average will
 * have the smaller value, i.e. 100 and NOT 280.
 * 
 * @pre referenceimg width and height are both even
 */
HSLAPixel QuarterColorPicker::operator()(PixelPoint p)
{
    HSLAPixel *ulPixel, *urPixel, *dlPixel, *drPixel;
    
    ulPixel = referenceimg.getPixel((p.x % (referenceimg.width()/2))*2,   (p.y % (referenceimg.height()/2))*2);
    urPixel = referenceimg.getPixel((p.x % (referenceimg.width()/2))*2+1, (p.y % (referenceimg.height()/2))*2);
    dlPixel = referenceimg.getPixel((p.x % (referenceimg.width()/2))*2,   (p.y % (referenceimg.height()/2))*2+1);
    drPixel = referenceimg.getPixel((p.x % (referenceimg.width()/2))*2+1, (p.y % (referenceimg.height()/2))*2+1);

    double averageSat = (((ulPixel->s + urPixel->s)/2) + ((dlPixel->s + drPixel->s)/2))/2;
    double averageLum = (((ulPixel->l + urPixel->l)/2) + ((dlPixel->l + drPixel->l)/2))/2;
    double averageAlp = (((ulPixel->a + urPixel->a)/2) + ((dlPixel->a + drPixel->a)/2))/2;

    double averageHueTopR = averageAngles(ulPixel->h * PI / 180, urPixel->h * PI / 180);
    double averageHueBotR = averageAngles(dlPixel->h * PI / 180, drPixel->h * PI / 180);

    double averageHue = fmod(360 + (averageAngles(averageHueTopR, averageHueBotR) * 180 / PI), 360);
    
    return HSLAPixel(averageHue, averageSat, averageLum, averageAlp);
}

/**
 * Add your private QuarterColorPicker function implementations below
 */
 double QuarterColorPicker::averageAngles(double angle1, double angle2) {
	//if (fmod((angle1 + PI), 2*PI) == angle2) {
	// 	return fmod((angle1+angle2)/2, 2*PI);
	// } else {
		return atan2((sin(angle1)+sin(angle2)), (cos(angle1)+cos(angle2)));
	// }
        // double a = fmod(angle1, 360);
        // double b = fmod(angle2, 360);

        // double sum = a + b;
        // if (sum > 360 && sum < 540)
        // {
        //     sum = fmod(sum, 180);
        // }
        // return sum / 2;
 }