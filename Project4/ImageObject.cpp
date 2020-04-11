//
// Created by Raggdoll on 4/4/2020.
//

#include "ImageObject.hpp"
#include <iostream>
ImageObject::ImageObject(int l, std::vector<std::vector<int>> initialImage){
    label = l;
    setDensity(initialImage);
    setSymmetry(initialImage);
    setIntersections(initialImage);

}


void ImageObject::setDensity(std::vector<std::vector<int>> initialImage){
    double total = 0;
    for(int i = 0; i < initialImage.size(); i++){
        for(int j = 0; j < initialImage[i].size(); j++)
        {
            total = initialImage[i][j] + total;
        }
    }

    ImageProcessed[0] = total / (initialImage.size() * initialImage.size());

}
void ImageObject::setSymmetry(std::vector<std::vector<int>> initialImage){

     unsigned int total = 0;
    for(int i = 0; i < initialImage.size()/2; i++){
        for(int j = 0; j < initialImage[i].size(); j++){
            total = total + (static_cast<unsigned int>(initialImage[i][j]) ^ static_cast<unsigned int>(initialImage[i][initialImage.size() - j - 1]));
          //  total = total + (abs(initialImage[i][j] - initialImage[initialImage.size()-i - 1][j]));
        }
    }

ImageProcessed[1] = total / ((static_cast<double>(initialImage.size())/2) * initialImage.size());

}

void ImageObject::setIntersections(std::vector<std::vector<int>> initialImage)
{
    int horizontalTotalCount = 0;
    int maxHorizontalCount = 0;
    int horizontalCount = 0;
    int verticalTotalCount = 0;
    int verticalCount = 0;
    int maxVerticalTotalCount = 0;
    std::vector<std::vector<bool>> outputVector;
    outputVector.resize(initialImage.size());
    for(auto & vec :outputVector){
        vec.resize(initialImage.size());
    }

    for(int i = 0; i < initialImage.size(); i++){
        horizontalCount = 0;
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
                    horizontalCount++;
                    if(maxHorizontalCount  < horizontalCount){
                        maxHorizontalCount = horizontalCount;
                    }
                }
            }
            if(j != 0){
                if(outputVector[i][j] != outputVector[i][j-1]){
                    verticalTotalCount++;
                    verticalCount++;
                    if(maxVerticalTotalCount < verticalCount){
                        maxVerticalTotalCount = verticalCount;
                    }
            }
        }
        }
    }

    ImageProcessed[2] = maxHorizontalCount;
    ImageProcessed[3] = horizontalTotalCount / 28.0;
    ImageProcessed[4] = maxVerticalTotalCount;
    ImageProcessed[5] = verticalTotalCount / 28.0;

}


