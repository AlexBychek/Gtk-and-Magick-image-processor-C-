//
// Created by https://github.com/AlexBychek
//

#ifndef IMAGEPROCESSOR_WATERMARK_H
#define IMAGEPROCESSOR_WATERMARK_H

#include <image.h>

class Watermark : public Image
{
private:
    uint32_t scale_;
    uint32_t opacity_;
    uint32_t xOffset_;
    uint32_t yOffset_;

public:
    Watermark();
    ~Watermark() = default;

    Watermark( std::string path );

    void setParams( uint32_t scale, uint32_t opacity, uint32_t xOffset, uint32_t yOffset );
    void addWatermark( Image& to_image );
};

#endif //IMAGEPROCESSOR_WATERMARK_H
