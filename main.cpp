
#include<print>
#include "img.hpp"
#include "command.hpp"


int main(int argc, char** argv){
    
    //Image img("test.jpg");
    //std::print("{}\n", argc);
    if(argc < 2)
    {
        std::print("Please, use ./app path_to_img.jpg (no .png yet)");
        return -1;
    }

    Image img(argv[1]);
    
    Action action = Commands::Parse();
    switch (action)
    {
        case FlipHorizontal:
            printf("Flipping...\n");
            img.flipHorizontally();
            break;

        case FlipVertical:
            printf("Flipping...\n");
            img.flipVertically();
            break;

        case Scale:
            uint scale;
            printf("Enter scale (2 means 2 times smaller): ");
            std::cin >> scale;
            printf("Processing...");
            img.scale(scale);
            break;
        
        // case Blur:
        //     int blur_str;
        //     printf("Enter blur radius (0+): ");
        //     std::cin >> blur_str;
            
        //     if(blur_str < 0) {
        //         return -1;
        //     }
        //     printf("Processing...");
        //     img.blur(blur_str);
        //     break;
        
        case ImageResolution:
            img.printResolution();
            exit(EXIT_SUCCESS);
            break;
        
        // case Cut:
        //     printf("To cut an image from the source you need to enter from which Height, Width and to Height, Width you want to cut\n");
        //     int height_from;
        //     int height_to;
        //     int width_from;
        //     int width_to;

        //     printf("Enter start Height: ");
        //     std::cin >> height_from;
        //     printf("Enter end Height: ");
        //     std::cin >> height_to;

        //     printf("Enter start Width: ");
        //     std::cin >> width_from;
        //     printf("Enter end Width: ");
        //     std::cin >> width_to;

        //     img.cut(height_from, height_to, width_from, width_to);
        //     break;
        
        // case Rotate:
        //     printf("Rotating...");
        //     img.rotate();
        //     break;
        
        case Exit:
            std::cout << "Exiting..." << std::endl;
            return 0;
            break;

    }

  
    img.write("output.jpg");

}
