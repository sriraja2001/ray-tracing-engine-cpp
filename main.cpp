#include <fstream>
#include "ProgressBar.h"
#include "vec3.h"
#include "color.h"

using namespace std;

int main() {
    constexpr int imageHeight = 256;
    constexpr int imageWidth = 256;

    const ProgressBar progress(imageHeight);

    ofstream outputFile("image.ppm");  // Save in current directory

    outputFile << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int i = 0; i < imageHeight; i++) {
        for (int j = 0; j < imageWidth; j++) {
            const color pixelColor = color(static_cast<double>(j) / (imageWidth - 1), static_cast<double>(i) / (imageHeight - 1), 0.0);
            write_color(outputFile, pixelColor);
        }
        progress.update(i + 1);
    }

    progress.finish();
    outputFile.close();

    return 0;
}