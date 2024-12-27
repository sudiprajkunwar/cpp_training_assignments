#include "Filter.cpp"

int main()
{
    int width, height, channels;
    unsigned char *smallImage = stbi_load("./tile1.jpg", &width, &height, &channels, 3);
    if (smallImage == nullptr)
    {
        std::cout << "Failed to load image!" << std::endl;
        return -1;
    }

    // Create a Filter object and process the image
    Filter filter(width, height);
    auto tileImage = filter.convertTo2D(smallImage);

    // Set the target canvas size (1100x1100)
    int canvasWidth = 1100;
    int canvasHeight = 1100;

    // Create a blank canvas (1100x1100)
    auto canvas = filter.createCanvas(canvasWidth, canvasHeight);

    // Define the padding size (10 pixels)
    int padding = 10;

    // Calculate the number of tiles that can fit horizontally and vertically
    int tilesPerRow = (canvasWidth + padding) / (width + padding);
    int tilesPerColumn = (canvasHeight + padding) / (height + padding);

    // Repeat the tile image to fill the canvas
    for (int row = 0; row < tilesPerColumn; ++row)
    {
        for (int col = 0; col < tilesPerRow; ++col)
        {
            // Calculate the position for each tile considering padding
            int xPos = col * (width + padding);
            int yPos = row * (height + padding);

            // Place the tile on the canvas at the calculated position
            filter.placeTileOnCanvas(canvas, tileImage, xPos, yPos);
        }
    }

    // Save the final canvas as an image
    filter.saveToPNG(canvas, "tiled_image_with_padding.png");

    stbi_image_free(smallImage);
    return 0;
}