//
// Created by Raggdoll on 4/4/2020.
//

#include "ImageObject.hpp"
ImageObject::ImageObject(std::vector<std::vector<int>> initialImage){
    setDensity(initialImage);
    setSymmetry(initialImage);
    setIntersections(initialImage);

}


void ImageObject::setDensity(std::vector<std::vector<int>> initialImage){
    int total = 0;
    for(int i = 0; i < initialImage.size(); i++){
        for(int j = 0; j < initialImage[i].size(); j++)
        {
            total = initialImage[i][j] + total;
        }
    }

    ImageProcessed[0] = total / (initialImage.size() * initialImage.size());

}
void ImageObject::setSymmetry(std::vector<std::vector<int>> initialImage){
    int total = 0;
    for(int i = 0; i < initialImage.size()/2; i++){
        for(int j = 0; j < initialImage[i].size(); j++){
            total = total + (initialImage[i][j] ^ initialImage[initialImage.size()-i][j]);
        }
    }
ImageProcessed[1] = total / ((initialImage.size()/2) * initialImage.size())
}

void ImageObject::setIntersections(std::vector<std::vector<int>> initialImage)
{
    int horizontalTotalCount = 0;
    int maxHorizontalCount = 0;
    int verticalTotalCount = 0;
    int maxVerticalTotalCount = 0;
    std::vector<std::vector<bool>> outputVector;
    for(int i = 0; i < initialImage.size(); i++){
        for(int j = 0; j < initialImage[i].size(); j++)
        {

            if (initialImage[i][j] < 128)
            {
                outputVector[i][j] = 1;
            }
            else
            {
                outputVector[i][j] = 0;
            }

            if(i != 0)
            {
                if (outputVector[i][j] != outputVector[i - 1][j])
                {
                    horizontalTotalCount++;
                    if(maxHorizontalCount  < horizontalTotalCount){
                        maxHorizontalCount = horizontalTotalCount;
                    }
                }
            }
            if(j != 0){
                if(outputVector[i][j] != outputVector[i][j-1]
            {
                    vertTotalCount++;
                    if(maxVerticalTotalCount < verticalTotalCount){
                        maxVerticalTotalCount = verticalTotalCount;
                    }
            }
        }
        }
    }

    ImageProcessed[2] = maxHorizontalCount;
    ImageProcessed[3] = horizontalTotalCount / 28;
    ImageProcessed[4] = maxVerticalTotalCount;
    ImageProcessed[5] = verticalTotalCount / 28;

}


