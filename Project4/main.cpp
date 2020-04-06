#include <iostream>
#include <vector>
#include <cstddef>
#include <random>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>
#include "ImageObject.hpp"
struct Image {
    std::array<uint8_t, 28*28> data;
    uint8_t label;

    Image(uint8_t label, const std::array<uint8_t, 28*28>& data) : label(label), data(data) {}
    uint8_t at(int row, int col) const {
        return data[col + row * 28];
    }
};
std::ostream& operator<<(std::ostream& out, const Image& image) {
    out << "label = " << static_cast<int>(image.label) << '\n';
    for (int row = 0; row < 28; ++row) {
        for (int col = 0; col < 28; ++col) {
            out << ((image.at(row, col) >= 128) ? '#' : ' ');
        }
        out << '\n';
    }
    return out;
}

template<int Size> std::array<uint8_t, Size> readBytes(std::istream& in) {
    std::array<uint8_t, Size> buf;
    in.read((char*)&buf[0], Size);
    return buf;
}
uint32_t read32BigEndianInt(std::istream& in) {
    auto buf = readBytes<4>(in);
    return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

std::vector<Image> readDataSet(const std::string& labelFileName, const std::string& imageFileName) {
    auto withErrorMessage = [](const std::string& message) -> std::vector<Image> {
        std::cerr << message << '\n';
        return {};
    };

    std::ifstream labelFile(labelFileName, std::ios::binary);
    std::ifstream imageFile(imageFileName, std::ios::binary);

    if (!labelFile)
        return withErrorMessage("Couldn't open label file");
    if (!imageFile)
        return withErrorMessage("Couldn't open image file");

    auto labelMagicNumber = read32BigEndianInt(labelFile);
    auto imageMagicNumber = read32BigEndianInt(imageFile);
    if (labelMagicNumber != 2049)
        return withErrorMessage("Magic number for label file is incorrect");
    if (imageMagicNumber != 2051)
        return withErrorMessage("Magic number for image file is incorrect");

    auto labelItemCount = read32BigEndianInt(labelFile);
    auto imageItemCount = read32BigEndianInt(imageFile);
    if (labelItemCount != imageItemCount)
        return withErrorMessage("Input size of label and image files are different");
    auto itemCount = labelItemCount;

    auto rowCount = read32BigEndianInt(imageFile);
    auto colCount = read32BigEndianInt(imageFile);
    if (rowCount != 28 || colCount != 28)
        return withErrorMessage("image size is not 28x28 as expected");

    std::vector<Image> dataSet;
    for (int i = 0; i < itemCount; ++i) {
        dataSet.emplace_back(readBytes<1>(labelFile)[0], readBytes<28*28>(imageFile));
    }

    return dataSet;
}

void showDataset(const std::vector<Image>& dataSet) {
    for (auto& digit : dataSet) {
        std::cout << digit << '\n';
    }
}
std::vector<ImageObject> getImages() {
    auto dataSet = readDataSet("train-labels.idx1-ubyte", "train-images.idx3-ubyte");
    //showDataset(dataSet); // uncomment to see dataset

    std::vector<ImageObject> images;
    std::vector<std::vector<int>> image2d(28);
    for (auto& row : image2d) {
        row.resize(28);
    }
    for (auto& image : dataSet) {
        for (int i = 0; i < 28; ++i) {
            for (int j = 0; j < 28; ++j) {
                image2d[i][j] = image.at(i, j);
            }
        }
        images.emplace_back(image.label, image2d);
    }

    return images;
}


struct perceptron {
    std::vector<double> weights;
    int labels;
};

void NeuralNetworkTrain(std::vector<ImageObject>allImages, std::vector<ImageObject> validatedImages, std::vector<perceptron> &neuralNetwork, double adjustIncrement,  int iterations);
//void NeuralNetworkValidate(std::vector<ImageObject>allImages, const std::vector<perceptron> &neuralNetwork, double adjustIncrement,  int iterations);
void NeuralNetworkTest(std::vector<ImageObject>allImages, std::vector<perceptron> &neuralNetwork, double adjustIncrement,  int iterations);
//std::vector<ImageObject> getImages(std::vector<std::string> fileName);
void initializePart2(std::vector<perceptron> & NNetwork);

double getWeightedSum(const ImageObject &image, const perceptron &perceptron);

int main()
{

    auto images = getImages();
    std::vector<ImageObject> trainImages(images.begin(), images.begin() + images.size() * 0.8);
    std::vector<ImageObject> testImages(images.begin() + images.size() * 0.8, images.end());



    std::vector<std::string> Part1TrainFiles = {"train7.txt","train9.txt"};
    std::vector<std::string> Part1ValidateFiles = {"valid7.txt","valid9.txt"};
    std::vector<std::string> Part1TestFiles = {"test7.txt","test9.txt"};
    std::vector<std::string> Part2TrainFiles = {"train0.txt","train1.txt","train2.txt","train3.txt","train4.txt","train5.txt","train6.txt","train7.txt","train8.txt","train9.txt"};
    std::vector<std::string> Part2TestFiles = {"test0.txt","test1.txt","test2.txt","test3.txt","test4.txt","test5.txt","test6.txt","test7.txt","test8.txt","test9.txt"};
  //  std::vector<ImageObject> trainImages;
    std::vector<ImageObject> validatedImages;
   // std::vector<ImageObject> testImages;
    std::vector<perceptron> neuralNetwork;

   // trainImages = getImages(Part1TrainFiles);
  //  validatedImages = getImages(Part1ValidateFiles);

    float adjustIncrement = 0.01;
    int iterations = 1000;
    //Training
    initializePart2(neuralNetwork); //todo initialize only 2 perceptrons
   std::cout << " Before Neural Network Train" << std::endl;
    NeuralNetworkTrain(trainImages, validatedImages,neuralNetwork, adjustIncrement, iterations);

    //Test
  //  testImages = getImages(Part1TestFiles);
NeuralNetworkTest(testImages, neuralNetwork,adjustIncrement,iterations);

    //Part 1
        //Pull data from train7 & train9

    //TODO Part 1 and Part 2 do this loop, but for different files(Main Function to call initialize, train and test only Returns Least Validation Error, Output Minimum error fraction (between 0 - 1)
   //TODO Write initialization function based on size of input
        //initializes weights for as many training points we have in file(number of inputs in the file: Might not have that data, might need to loop through file to find this)
        //

   //TODO Write update Weight function
   //TODO Write Train function for training data
        //Uses Perceptron
        //Output each loop the degree of accuracy per epoch(iteration)
        //Return the new weights
   //TODO Write Test function for training data
        //Output % correct based on size of domain
        //
}

void NeuralNetworkTrain(std::vector<ImageObject> allImages, std::vector<ImageObject> validatedImages, std::vector<perceptron> &neuralNetwork , double adjustIncrement,  int iterations)
{
   // std::vector<ImageObject> newAllImages(allImages.begin(), allImages.begin() + 1000);
  //  std::mt19937 g(1234);
    for(int i = 0; i < iterations; i++){
        int goodCount = 0;

          // std::shuffle( allImages.begin(),allImages.end(),g);
            for(auto & image : allImages){

                    for(auto & perceptron : neuralNetwork){

                        double weightedSum = getWeightedSum(image, perceptron);
                //        std::cout << "Weighted Sum " << weightedSum << std::endl;
                 //       std::cout << "Labels " << image.getImageLabel() << std::endl;
                 //       std::cout << "Perceptron Label " << perceptron.labels << std::endl;
                        if(image.getImageLabel() == perceptron.labels && weightedSum <= 0)
                        {

                            //todo adjust weights down
                            for(int j = 0; j < perceptron.weights.size(); j++)
                            {
                                perceptron.weights[j] += adjustIncrement * image.getImageVector(j);
                               //weight += adjustIncrement;
                            }

                        }else if(image.getImageLabel() != perceptron.labels && weightedSum >= 0)
                        {
                            for(int k = 0; k < perceptron.weights.size(); k++)
                            {
                                perceptron.weights[k] -= adjustIncrement * image.getImageVector(k);

                            }

                        }else{
                            goodCount++;
                        }


                    }

            }
            int badCount = allImages.size()*neuralNetwork.size() - goodCount;
         //   std::cout << goodCount << " Good Count for Epoch" << std::endl;
         //   std::cout << badCount << " Bad Count for Epoch" << std::endl;
          //  std::cout << "Error for Epoch " << i << " is: " << badCount / (allImages.size()*neuralNetwork.size()) << std::endl;
        }

        //todo display ratio between correct answers and number of epochs.
    }

void initializePart2(std::vector<perceptron> & NNetwork){
    NNetwork.resize(10);

   for(int i = 0; i < 10; i++){
       NNetwork[i].weights = {0,0,0,0,0,0,0};
       NNetwork[i].labels = i;

   }

}


double getWeightedSum(const ImageObject &image, const perceptron &perceptron)
{
    double weightedSum = 0;

    for(int k = 0; k < perceptron.weights.size(); k++)
    {
        weightedSum = weightedSum +  image.getImageVector(k) * perceptron.weights[k];
    }
    return weightedSum;
}









void NeuralNetworkTest(std::vector<ImageObject>allImages, std::vector<perceptron> &neuralNetwork, double adjustIncrement,  int iterations)
{



        int goodCount = 0;

        for (auto &image : allImages)
        {
            double maxSum = 0;
            int guess = 0;
            for (auto &perceptron : neuralNetwork)
            {

                double weightedSum = getWeightedSum(image, perceptron);

                if(maxSum < weightedSum){
                    maxSum = weightedSum;
                    guess = perceptron.labels;

                }

            }
           goodCount += image.getImageLabel() == guess;

        }
        std::cout << "Good Count " << goodCount << std::endl;
        std::cout << allImages.size() << " Total Size" << std::endl;



    }





/*
std::vector<ImageObject> getImages(std::string fileName)
{

    //ToDO create open files, and input values into an std::vector<std::vector<int>>
    //Todo close file

}

*/