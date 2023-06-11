/**
 * @file imageTileColorPicker.cpp
 * @description Implements the ImageTileColorPicker constructor and () function
 *              for CPSC 221 2023S PA2
 * 
 *              THIS FILE WILL BE SUBMITTED
 */

#include "imageTileColorPicker.h"

ImageTileColorPicker::ImageTileColorPicker(PNG& secondary_img)
{
    tileimg = PNG(secondary_img);
}

/**
 * Picks the color for pixel (x, y).
 *
 * The tile image should be tiled over the dimensions of the destination image,
 * aligned to (0, 0) in the destination image.
 *
 * The returned value will be the colour of the appropriate pixel in the tile image,
 * where it would be over the specified location in the destination image.
 */
HSLAPixel ImageTileColorPicker::operator()(PixelPoint p)
{
    HSLAPixel *colorRef = tileimg.getPixel(((p.x)%tileimg.width()), ((p.y)%tileimg.height()));
    HSLAPixel color = HSLAPixel();
    color.h = colorRef->h;
    color.s = colorRef->s;
    color.l = colorRef->l;
    color.a = colorRef->a;
    
    return color;
}

/**
 * Add your private QuarterColorPicker function implementations below
 */
