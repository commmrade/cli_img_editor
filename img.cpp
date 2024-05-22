#include "img.hpp"
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION



#include<stb/stb_image.h>
#include<stb/stb_image_write.h>

Image::Image(const std::string file_path)
{
    data = stbi_load(file_path.c_str(), &width, &height, &channels, 0); //Idk what 0 means
    std::print("Width: {}\nHeight: {}\nChannels: {}\n", width, height, channels);
}
void Image::write(const std::string file_path)
{
    stbi_write_jpg(file_path.c_str(), width, height, channels, data, width * sizeof(int)); // width * sizeof(int) iss good goida 
    //No .png because of this btw
}
void Image::flipHorizontally()
{
    for(auto i : std::views::iota(0, width / 2))
    {
        for(auto j : std::views::iota(0, height))
        {
            int index = (j * width + i) * channels;
            //int indexR = ((j * width + width) - (width / 2)) * channels;
            int indexR = (j * width + (width - i - 1)) * channels; //Yeah damn....

            std::swap(data[indexR], data[index]); 
            std::swap(data[indexR + 1], data[index + 1]);
            std::swap(data[indexR + 2], data[index + 2]);
        }
    }
}
void Image::flipVertically()
{
    for(auto i : std::views::iota(0, width))
    {
        for(auto j : std::views::iota(0, height / 2))
        {
            int index = (j * width + i) * channels;
            //int indexR = ((j * width + width) - (width / 2)) * channels;
            int indexR = ((height - j - 1) * width + i) * channels;

            std::swap(data[indexR], data[index]);
            std::swap(data[indexR + 1], data[index + 1]);
            std::swap(data[indexR + 2], data[index + 2]);



        }
    }
}
void Image::scale(int scale_factor)
{
    int new_width = width / scale_factor;
    int new_height = height / scale_factor;

    IMAGE *newData = new unsigned char[new_width * new_height * channels];

    for(auto i : std::views::iota(0, new_width))
    {
        for(auto j : std::views::iota(0, new_height))
        {
            int index = (j * new_width + i) * channels;
            int indexOld = ((j * scale_factor) * width + (i * scale_factor)) * channels; //Old image indexes

            //Color clr = GetPixel(i, j);
            newData[index] = data[indexOld];
            newData[index + 1] = data[indexOld + 1];
            newData[index + 2] = data[indexOld + 2];

        }
    }

    delete []data; //Dealloc memory

    data = newData;
    width = new_width;
    height = new_height;


}
void Image::printResolution()
{
    std::print("Width: {}\nHeight: {}\nChannels: {}\n", width, height, channels);
}

