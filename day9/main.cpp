

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <vector>
#include "./stb/stb_image.h"
#include "./stb/stb_image_write.h"

struct RGB
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Coordinate
{
    int x;
    int y;
};

class Shape
{
public:
    virtual void draw(std::vector<std::vector<RGB>> &canvas, RGB stroke, RGB fill) = 0;
};

class Rectangle : public Shape
{
public:
    Rectangle(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}

    void draw(std::vector<std::vector<RGB>> &canvas, RGB stroke, RGB fill) override
    {
        for (int i = x; i < x + width; ++i)
        {
            canvas[y][i] = stroke;
            canvas[y + height][i] = stroke;
        }
        for (int i = y; i < y + height; ++i)
        {
            canvas[i][x] = stroke;
            canvas[i][x + width] = stroke;
        }
        for (int i = x + 1; i < x + width; ++i)
        {
            for (int j = y + 1; j < y + height; ++j)
            {
                canvas[j][i] = fill;
            }
        }
    }

private:
    int x, y, width, height;
};

class Line : public Shape
{
public:
    Line(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

    void draw(std::vector<std::vector<RGB>> &canvas, RGB stroke, RGB fill) override
    {
        int dx = std::abs(x2 - x1), dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (true)
        {
            canvas[y1][x1] = stroke;

            if (x1 == x2 && y1 == y2)
                break;

            int e2 = 2 * err;
            if (e2 > -dy)
            {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx)
            {
                err += dx;
                y1 += sy;
            }
        }
    }

private:
    int x1, y1, x2, y2;
};

class Polygon : public Shape
{
public:
    Polygon(const std::vector<Coordinate> &points) : coordinates(points) {}

    void draw(std::vector<std::vector<RGB>> &canvas, RGB stroke, RGB fill) override
    {
        for (int i = 0; i < coordinates.size(); ++i)
        {
            int x1 = coordinates[i].x;
            int y1 = coordinates[i].y;
            int x2 = coordinates[(i + 1) % coordinates.size()].x;
            int y2 = coordinates[(i + 1) % coordinates.size()].y;

            Line(x1, y1, x2, y2).draw(canvas, stroke, fill);
        }
    }

private:
    std::vector<Coordinate> coordinates;
};

class Filter
{
public:
    Filter(int w, int h) : width(w), height(h) {}

    std::vector<std::vector<RGB>> convertTo2D(const unsigned char *imageData)
    {
        std::vector<std::vector<RGB>> output;
        int length = width * height * 3;
        RGB color;

        for (int i = 0; i < height; ++i)
        {
            std::vector<RGB> row;
            for (int j = 0; j < width * 3; j += 3)
            {
                color.r = imageData[i * width * 3 + j + 0];
                color.g = imageData[i * width * 3 + j + 1];
                color.b = imageData[i * width * 3 + j + 2];
                row.emplace_back(color);
            }
            output.emplace_back(row);
        }

        return output;
    };

    void saveToPNG(const std::vector<std::vector<RGB>> &imageData, const char *filename)
    {
        std::vector<unsigned char> imageFlat;
        imageFlat.reserve(width * height * 3);

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                const RGB &color = imageData[i][j];
                imageFlat.emplace_back(color.r);
                imageFlat.emplace_back(color.g);
                imageFlat.emplace_back(color.b);
            }
        }

        if (stbi_write_png(filename, width, height, 3, imageFlat.data(), width * 3))
        {
            std::cout << "Image saved successfully to " << filename << std::endl;
        }
        else
        {
            std::cout << "Failed to save image!" << std::endl;
        }
    }

    void convertToGrayscale(std::vector<std::vector<RGB>> &imageData)
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                RGB &color = imageData[i][j];
                float gray = color.r * 0.2989f + color.g * 0.5870f + color.b * 0.1140f;
                color.r = gray;
                color.g = gray;
                color.b = gray;
            }
        }
    };

    void normalizePic(std::vector<std::vector<RGB>> &firstImage, std::vector<std::vector<RGB>> &secondImage)
    {
        for (int i = 0; i < firstImage.size(); ++i)
        {
            for (int j = 0; j < firstImage[i].size(); ++j)
            {
                RGB &color1 = firstImage[i][j];
                RGB &color2 = secondImage[i][j];

                color1.r = (color1.r + color2.r) / 2;
                color1.g = (color1.g + color2.g) / 2;
                color1.b = (color1.b + color2.b) / 2;
            }
        }
    };

    void sobelEdgeDetection(std::vector<std::vector<RGB>> &imageData)
    {
        const int Gx[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}};
        const int Gy[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}};

        std::vector<std::vector<RGB>> originalImage = imageData;

        for (int i = 1; i < height - 1; ++i)
        {
            for (int j = 1; j < width - 1; ++j)
            {
                float gx = 0.0f;
                float gy = 0.0f;

                for (int k = -1; k <= 1; ++k)
                {
                    for (int l = -1; l <= 1; ++l)
                    {
                        float intensity = originalImage[i + k][j + l].r;
                        gx += Gx[k + 1][l + 1] * intensity;
                        gy += Gy[k + 1][l + 1] * intensity;
                    }
                }

                float gradientMagnitude = std::sqrt(gx * gx + gy * gy);

                gradientMagnitude = std::min(std::max(gradientMagnitude, 0.0f), 255.0f);

                imageData[i][j].r = gradientMagnitude;
                imageData[i][j].g = 0.0f;
                imageData[i][j].b = 0.0f;
            }
        }
    };

    void applyBlur(std::vector<std::vector<RGB>> &imageData, int kernelSize)
    {
        std::vector<std::vector<RGB>> originalImage = imageData;
        int offset = kernelSize / 2;

        for (int i = offset; i < height - offset; ++i)
        {
            for (int j = offset; j < width - offset; ++j)
            {
                int rSum = 0, gSum = 0, bSum = 0;
                int count = 0;

                for (int k = -offset; k <= offset; ++k)
                {
                    for (int l = -offset; l <= offset; ++l)
                    {
                        const RGB &pixel = originalImage[i + k][j + l];
                        rSum += pixel.r;
                        gSum += pixel.g;
                        bSum += pixel.b;
                        count++;
                    }
                }

                imageData[i][j].r = rSum / count;
                imageData[i][j].g = gSum / count;
                imageData[i][j].b = bSum / count;
            }
        }
    }

private:
    int width;
    int height;
};

int main()
{
    int width, height, channels;
    unsigned char *imageData = stbi_load("./images/traffic.jpg", &width, &height, &channels, 3);
    unsigned char *secondData = stbi_load("./test.png", &width, &height, &channels, 3);

    Filter filter(width, height);
    auto image = filter.convertTo2D(imageData);
    auto image2 = filter.convertTo2D(secondData);

    filter.convertToGrayscale(image);
    filter.sobelEdgeDetection(image);

    filter.normalizePic(image, image2);

    filter.saveToPNG(image, "red.png");
    stbi_image_free(imageData);
    stbi_image_free(secondData);

    return 0;
}
