/**
 * @file negativeBorderColorPicker.cpp
 * @description Implements the NegativeBorderColorPicker constructor and () function
 *              for CPSC 221 2023S PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "negativeBorderColorPicker.h"
#include <math.h>

NegativeBorderColorPicker::NegativeBorderColorPicker(PNG &inputimg, PixelPoint src_px, unsigned int width, double tol)
{
    referenceimg = PNG(inputimg);
    source_px = src_px;
    borderwidth = width;
    tolerance = tol;
}

/**
 * Picks the color for pixel (x, y).
 *
 * Leaves a pixel unchanged if it is not on the border of a fill region
 *
 * If a pixel is on the border of a fill region, change it to the "negative"
 * of the original colour value in the Hue and Luminance channels.
 * Saturation and Alpha should remain unchanged.
 * Based on your understanding of HSL colour space from Lab_intro,
 * think about what would be an appropriate "negative" transformation for the
 * Hue and Luminance channels.
 *
 * Hint: a pixel is on the border of a fill region, if it is within "width"
 * pixels of a pixel which is NOT in the fill region!
 *
 * Also: the border of the image is considered to be a border of the fill region.
 */
HSLAPixel NegativeBorderColorPicker::operator()(PixelPoint p)
{
    // if (referenceimg.getPixel(p.x, p.y)->distanceTo(source_px.color) <= tolerance)
    // {
        int pointx = p.x;
        int pointy = p.y;
        for (int xx = 0; xx < borderwidth * 2 + 1; xx++)
        {
            int distx = xx - borderwidth;
            int scanx = pointx + distx;
            for (int yy = 0; yy < borderwidth * 2 + 1; yy++)
            {
                int disty = yy - borderwidth;
                int scany = pointy + disty;
                if (!((distx * distx) + (disty * disty) > borderwidth * borderwidth))
                {
                    if (!(scanx == pointx && scany == pointy) &&
                        ((scanx < 0 || scanx >= referenceimg.width()) ||
                        (scany < 0 || scany >= referenceimg.height()) ||
                        (referenceimg.getPixel(scanx, scany)->distanceTo(source_px.color) > tolerance)))
                    {
                        // cout << "border width is " << borderwidth << endl;
                        // cout << "hit on position (" << scanx << ", " << scany << ") (source was " << pointx << ", " << pointy << ") \n";
                        HSLAPixel output = HSLAPixel(p.color.h, p.color.s, p.color.l, p.color.a);
                        
                        output.h = fmod(180 + referenceimg.getPixel(pointx, pointy)->h, 360);
                        output.s = referenceimg.getPixel(pointx, pointy)->s;
                        output.l = 1.0 - referenceimg.getPixel(pointx, pointy)->l;
                        output.a = referenceimg.getPixel(pointx, pointy)->a;
                        
                        return output;
                    }
                }
            }
        }
    // }
    // Replace the line below with your implementation
    return *referenceimg.getPixel(p.x, p.y);
}

/**
 * Add your private QuarterColorPicker function implementations below
 */
