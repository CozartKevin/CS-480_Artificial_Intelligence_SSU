#include <iostream>
#include <vector>
#include "ImageObject.hpp"


struct perceptron {
    std::vector<double> weights;
    int labels;
};

void NeuralNetworkTrain(std::vector<ImageObject>allImages, std::vector<ImageObject> validatedImages, std::vector<perceptron> &perceptronTracker, double adjustIncrement,  int iterations);
void NeuralNetworkValidate(std::vector<ImageObject>allImages, const std::vector<perceptron> &neuralNetwork, double adjustIncrement,  int iterations);
void NeuralNetworkTest(std::vector<ImageObject>allImages, const std::vector<perceptron> &neuralNetwork, double adjustIncrement,  int iterations);
std::vector<ImageObject> getImages(std::vector<std::string> fileName);


double getWeightedSum(const ImageObject &image, const perceptron &perceptron);

int main()
{

    std::vector<std::string> Part1TrainFiles = {"train7.txt","train9.txt"};
    std::vector<std::string> Part1ValidateFiles = {"valid7.txt","valid9.txt"};
    std::vector<std::string> Part1TestFiles = {"test7.txt","test9.txt"};
    std::vector<std::string> Part2TrainFiles = {"train0.txt","train1.txt","train2.txt","train3.txt","train4.txt","train5.txt","train6.txt","train7.txt","train8.txt","train9.txt"};
    std::vector<std::string> Part2TestFiles = {"test0.txt","test1.txt","test2.txt","test3.txt","test4.txt","test5.txt","test6.txt","test7.txt","test8.txt","test9.txt"};
    std::vector<ImageObject> trainImages;
    std::vector<ImageObject> validatedImages;
    std::vector<ImageObject> testImages;
    std::vector<perceptron> neuralNetwork;

    trainImages = getImages(Part1TrainFiles);
    validatedImages = getImages(Part1ValidateFiles);

    float adjustIncrement = 0.1;
    int iterations = 1000;
    //Training
    initializePart1(neuralNetwork); //todo initialize only 2 perceptrons
    NeuralNetworkTrain(trainImages, validatedImages,neuralNetwork, adjustIncrement, iterations);

    //Test
    testImages = getImages(Part1TestFiles);
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
    for(int i = 0; i < iterations; i++){

            for(auto & image : allImages){

                    for(auto & perceptron : neuralNetwork){

                        double weightedSum = getWeightedSum(image, perceptron);
                        if(image.getImageLabel() == perceptron.labels && weightedSum < 0)
                        {
                            //todo adjust weights down
                            for(double & weight: perceptron.weights)
                            {
                               weight += adjustIncrement;
                            }

                        }else if(image.getImageLabel() != perceptron.labels && weightedSum > 0)
                        {
                            for(double & weight: perceptron.weights)
                            {
                                weight -= adjustIncrement;
                            }
                        }

                    }
            }
        }

        //todo display ratio between correct answers and number of epochs.
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









void NeuralNetworkTest(std::vector<ImageObject>allImages,const std::vector<perceptron> &neuralNetwork, float adjustIncrement,  int iterations){




}



std::vector<ImageObject> getImages(std::string fileName)
{

    //ToDO create open files, and input values into an std::vector<std::vector<int>>
    //Todo close file

}

