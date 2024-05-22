#pragma once

#include<iostream>
#include<ranges>
#include<print>
#include <sys/types.h>






#define IMAGE unsigned char

struct Color
{
    int r;
    int g; 
    int b;
};

class Image
{
private:
    IMAGE *data;

    int width;
    int height; 
    int channels;

public:
    Image(const std::string file_path);

    void write(const std::string file_path);

    void flipHorizontally();
    void flipVertically();

    //void SetPixel(uint index, Color color);
    //Color GetPixel(uint width, uint height);


    void scale(int scale_factor);
    void printResolution();


};
