//
// Created by https://github.com/AlexBychek
//

#ifndef IMAGEPROCESSOR_IMAGE_H
#define IMAGEPROCESSOR_IMAGE_H

#include <cstdint>
#include <string>
#include <Magick++.h>
#include <glib.h>
#include <memory>

class Image
{
protected:
    std::string path_;
    Magick::Image image_;
public:

    Image() = default;
    ~Image() = default;

    Image( std::string path );

    std::string absolutePath();
    std::string fileSize();
    std::string imageSize();

    void load( std::string path );
    void flop();
    void negative();
    void modulate();
    void blur( uint32_t sigma );
    void reset();

    void save();
    void saveAs( std::string path );
    void rotate( uint32_t degrees );
    void resize( uint32_t width, uint32_t height, bool save_aspect_ratio );
    int  getWeight() const;
    int  getHeight() const;

    Magick::Image& getRef();
};


#endif //IMAGEPROCESSOR_IMAGE_H
