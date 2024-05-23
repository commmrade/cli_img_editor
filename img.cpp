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
            //int indexOld = ((j * scale_factor) * width + (i * scale_factor)) * channels; //Old image indexes
            
            uint indexOld = getIndex(i * scale_factor, j * scale_factor);
            //uint index = getIndex(i, j);
          
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
void Image::blur(int blur_factor)
{   
    for(auto i : std::views::iota(0, width - blur_factor))
    {
        for(auto j : std::views::iota(0, height - blur_factor))
        {
            unsigned int r = 0;
            unsigned int g = 0;
            unsigned int b = 0;

            for(auto k : std::views::iota(0, blur_factor))
            {
                for(auto l : std::views::iota(0, blur_factor))
                {
                    //int index = ((j + k) * width + (l + i)) * channels;
                    uint index = getIndex(i + l, j + k);
                    r += data[index];
                    g += data[index + 1];
                    b += data[index + 2];
                }
            }

            //int index = (j * width + i) * channels;
            uint index = getIndex(i, j);

            data[index] = r / (blur_factor * blur_factor);
            data[index + 1] = g / (blur_factor * blur_factor);
            data[index + 2] = b / (blur_factor * blur_factor);

            // data[index] = 0;
            // data[index + 1] = 0;
            // data[index + 2] = 0;


        }
    }
}
unsigned int Image::getIndex(int w, int h)
{
    return (h * width + w) * channels;
}

