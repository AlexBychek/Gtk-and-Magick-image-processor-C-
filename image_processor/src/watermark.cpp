//
// Created by https://github.com/AlexBychek
//

#include <watermark.h>

Watermark::Watermark()
    : Image()
    , scale_(100)
    , xOffset_(0)
    , yOffset_(0)
{
}

Watermark::Watermark( std::string path )
    : Image(path)
    , scale_(100)
    , xOffset_(0)
    , yOffset_(0)
{
}

void Watermark::setParams( uint32_t scale, uint32_t xOffset, uint32_t yOffset )
{
    scale_ = scale;
    xOffset_ = xOffset;
    yOffset_ = yOffset;
}

#include <iostream>

void Watermark::addWatermark( Image& to_image )
{
    this->resize(to_image.getWeight(), to_image.getHeight(), true);

    uint32_t newWidth  = static_cast<int>( static_cast<double>(this->getWeight()) * static_cast<double>(scale_ / 100.0f) );
    uint32_t newHeight = static_cast<int>( static_cast<double>(this->getHeight()) * static_cast<double>(scale_ / 100.0f) );

    this->resize(newWidth, newHeight, true);

    to_image.getRef().composite(image_, xOffset_, yOffset_, Magick::OverCompositeOp);
}