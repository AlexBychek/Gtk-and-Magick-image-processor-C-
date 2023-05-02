//
// Created by https://github.com/AlexBychek
//

#include "image.h"
#include <iostream>

Image::Image( std::string path )
    : path_( path )
{
    image_.read( path );
}

std::string Image::absolutePath()
{
    return path_;
}

std::string Image::fileSize()
{
    return std::to_string( image_.fileSize() );
}

std::string Image::imageSize()
{
    return std::string( std::to_string( image_.columns() ) + "x" + std::to_string( image_.rows() ) );
}

void Image::load( std::string path )
{
    path_ = path;
    image_.read(path );
}

void Image::flop()
{
    image_.flop();
}

void Image::negative()
{
    image_.negate();
}

void Image::modulate()
{
    image_.modulate(100, 0, 100);
}

void Image::blur( uint32_t sigma )
{
    image_.blur(0, sigma);
}

void Image::reset()
{
    image_.read( path_ );
}

void Image::save()
{
    image_.write( path_ );
}

void Image::saveAs( std::string path )
{
    image_.write(path );
}

void Image::rotate( uint32_t degrees )
{
    image_.rotate(static_cast<double>(degrees) );
}

void Image::resize( uint32_t width, uint32_t height, bool save_aspect_ratio )
{
    image_.resize(std::to_string(width) + "x" + std::to_string(height) + ( save_aspect_ratio == true ? "" : "!" ) );
}

int Image::getWeight() const
{
    return image_.columns();
}

int Image::getHeight() const
{
    return image_.rows();
}

Magick::Image& Image::getRef()
{
    return image_;
}