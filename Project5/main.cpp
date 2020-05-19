#include <iostream>
#include <vector>
#include <cstddef>
#include <random>
#include <fstream>
#include <limits>
#include <string>
#include <array>
#include <algorithm>
#include <locale>
#include <codecvt>
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
            out << ((image.at(row, col) >= 128) ? '#' : '-');
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
    std::cout << dataSet[0] << '\n';
   // for (auto& digit : dataSet) {
     //   std::cout << digit << '\n';
  //  }
}


std::vector<ImageObject> getImages() {
    auto dataSet = readDataSet("train-labels.idx1-ubyte", "train-images.idx3-ubyte");
/*
    dataSet.erase(std::remove_if(
            dataSet.begin(), dataSet.end(), [&](auto& digitData) {
                return digitData.label != 7 && digitData.label != 9;
            }),
                  dataSet.end()
    );
*/
    showDataset(dataSet); // uncomment to see dataset

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




void NeuralNetworkTrain(std::vector<ImageObject>trainImages, std::vector<ImageObject> validatedImages, std::vector<perceptron> &neuralNetwork, double adjustIncrement,  int iterations,double (*validation)(std::vector<ImageObject>validationImages, std::vector<perceptron> &neuralNetwork, bool debugOutput));
double validationPart1(std::vector<ImageObject>validationImages, std::vector<perceptron> &neuralNetwork, bool debugOutput);
double validationPart2(std::vector<ImageObject>validationImages, std::vector<perceptron> &neuralNetwork, bool debugOutput);
void NeuralNetworkTest(std::vector<ImageObject>testImages, std::vector<perceptron> &neuralNetwork);

void initializePart1(std::vector<perceptron> & NNetwork);
void initializePart2(std::vector<perceptron> & NNetwork);

double getWeightedSum(const ImageObject &image, const perceptron &perceptron);
std::vector<ImageObject> getImages(std::vector<std::string> s, bool isLabels);
std::vector<std::vector<std::vector<double>>> getFilter(std::string s);
double Sigmoid(double weightedSum);
std::vector<std::vector<std::vector<int>>> getImageNonObject(std::vector<std::string> s, std::vector<int> & labels, bool isLabels);
std::vector<std::vector<std::vector<double>>> getFilter(std::string s);
std::vector<std::vector<std::vector<double>>> convolution(std::vector<std::vector<std::vector<double>>> filters/*filters that will be applied */, std::vector<std::vector<int>> image /*image 28x28*/);
std::vector<std::vector<double>> CNNTrain(std::vector<std::vector<std::vector<int>>> imageVectors, std::vector<int> labels, std::vector<std::vector<std::vector<double>>> filters, std::vector<std::vector<double>> & hiddenLayerNeurons, std::vector<std::vector<double>> & outputLayerNeurons);
std::vector<std::vector<std::vector<double>>> ReLU(std::vector<std::vector<std::vector<double>>> const x);
std::vector<double> ReLU1x100(std::vector<double> const x);
std::vector<std::vector<std::vector<double>>> Conv(std::vector<std::vector<int>> image, std::vector<std::vector<std::vector<double>>> filters);
std::vector<std::vector<std::vector<double>>> Pool(std::vector<std::vector<std::vector<double>>> const x);
std::vector<double> reshape(std::vector<std::vector<std::vector<double>>> const x);
std::vector<double> Softmax(std::vector<double> const x);
int main()
{

    //todo export Part 1 and Part 2 to txt files
    //todo figure out sigmoid function and its relevance to part 2.
    //todo write import function for his txt files
    //todo clean up your fucking messy ass code

   std::vector<std::string> testFilename = {"test1.csv"};
   auto test = getImages(testFilename, false);
  // std::cout << test.size() << std::endl;
   // ImageObject soloImage = test[0];
/*
  std::cout << "Solo Image Label: " << soloImage.getImageLabel() << std::endl;
  std::cout << "Image Vector: " << std::endl;
  for(int i = 0; i < 7; i++){
      std::cout << " Feature: " << i << " Feature Value: " << soloImage.getImageVector(i) << " " << std::endl;
  }

*/

    std::vector<std::string> Part2TrainFiles = {"train0.csv", "train1.csv", "train2.csv", "train3.csv", "train4.csv",
                                                "train5.csv", "train6.csv", "train7.csv", "train8.csv", "train9.csv"};
    std::vector<std::string> Part2ValidateFiles = {"valid0.csv", "valid1.csv", "valid2.csv", "valid3.csv", "valid4.csv",
                                                   "valid5.csv", "valid6.csv", "valid7.csv", "valid8.csv",
                                                   "valid9.csv"};



    std::vector<int> labels(10000);
    std::vector<std::vector<std::vector<double>>> filtersVector;
    filtersVector = getFilter("filters.txt");
    std::vector<std::vector<std::vector<int>>> imageVector;
    imageVector = getImageNonObject(Part2TrainFiles, labels, false);

    std::vector<std::vector<double>> hiddenLayerNeurons(2000,std::vector<double>(100));
    std::vector<std::vector<double>> outputLayerNeurons(100,std::vector<double>(10));

    CNNTrain(imageVector, labels, filtersVector, hiddenLayerNeurons, outputLayerNeurons);


    std::cin.get();



    std::vector<std::string> Part1TrainFiles = {"train7.csv", "train9.csv"};
    std::vector<std::string> Part1ValidateFiles = {"valid7.csv", "valid9.csv"};
    //std::vector<std::string> Part1TestFiles = {"test7.csv","test9.csv"};

    //  std::vector<ImageObject> trainImages;
    //  std::vector<ImageObject> validatedImages;
    // std::vector<ImageObject> testImages;
    std::vector<perceptron> neuralNetwork;
    float adjustIncrement = 0.1;
    int iterations = 1000;
    int x = 0;
    for (int i = 0; i < 2; i++)
    {
        auto train = (i == 0) ? getImages(Part1TrainFiles, true) : getImages(Part2TrainFiles, true);
        auto validate = (i == 0) ? getImages(Part1ValidateFiles, true) : getImages(Part2ValidateFiles, true);


        if (i == 0)
        {
            initializePart1(neuralNetwork);
            NeuralNetworkTrain(train, validate, neuralNetwork, adjustIncrement, iterations, validationPart1);
        }
        else
        {
            initializePart2(neuralNetwork);
            NeuralNetworkTrain(train, validate, neuralNetwork, adjustIncrement, iterations, validationPart2);
        }

    //    NeuralNetworkTrain(train, validate, neuralNetwork, adjustIncrement, iterations, validationPart1);

        std::cout << "Part " << (i + 1) << ": " << std::endl;

       // unsigned int badCountForPart1 = Validation(validate, neuralNetwork, false);

       // double errorRateForPart1 = static_cast<double>(badCountForPart1) / validate.size();
        double errorRateUsingPart1 = validationPart1(validate, neuralNetwork, false);

        std::cout << "Weights used:" << std::endl;
        std::cout << std::endl;
        if(i == 0){
            x = 2;
        }else{
            x = 10;
        }
        for (int i = 0; i < x; i++)
        {
            std::cout << "Label: " << neuralNetwork[i].labels << std::endl;
            std::cout << "Weights: ";
            for (int j = 0; j < 7; j++)
            {
                std::cout << neuralNetwork[i].weights[j] << " , ";
            }
            std::cout << std::endl << std::endl;
        }
        std::cout << "Error Rate for Test: " << errorRateUsingPart1 << std::endl;

        std::cout << "Minimum Fraction: " << (errorRateUsingPart1 * validate.size()) << " / " << validate.size() << std::endl;
        std::cout << std::endl;
        NeuralNetworkTest(test, neuralNetwork);

    }

}

void NeuralNetworkTrain(std::vector<ImageObject> allImages, std::vector<ImageObject> validatedImages, std::vector<perceptron> &neuralNetwork , double adjustIncrement,  int iterations, double (*validation)(std::vector<ImageObject>validationImages, std::vector<perceptron> &neuralNetwork, bool debugOutput))
{
   // std::vector<ImageObject> newAllImages(allImages.begin(), allImages.begin() + 1000);
 std::mt19937 g(1234);

  double lowestError = 1;
  std::vector<perceptron> lowestErrorWeights;
    for(int i = 0; i < iterations; i++){
        int goodCount = 0;
        std::shuffle( allImages.begin(),allImages.end(),g);

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
                                //if part 2
                                //use log (1 - fx) when percetron label == feature label

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

           // int badCount = allImages.size()*neuralNetwork.size() - goodCount;
         //   std::cout << goodCount << " Good Count for Epoch" << std::endl;
         //   std::cout << badCount << " Bad Count for Epoch" << std::endl;
          //  std::cout << "Error for Epoch " << i << " is: " << badCount / (allImages.size()*neuralNetwork.size()) << std::endl;

        //todo Run Validation set for error saving Perceptron with lowest error rate


       // double errorRate = static_cast<double>(Validation(validatedImages, neuralNetwork, false)) / validatedImages.size();

            double errorRate = validation(validatedImages, neuralNetwork, false);

        //todo use Sigmoid function to make a better guess for which perceptron should be used.
        //todo instead of using errorRate < lowestError
        // todo use LL = sigmoid of maxSum < sigmoid of weightedSum
        // todo lowestLL < LL then choose LL  Return NN of LowestLL


        if(errorRate < lowestError){
            lowestError = errorRate;
            lowestErrorWeights = neuralNetwork;
        }

        }

        neuralNetwork = lowestErrorWeights;
        //todo display ratio between correct answers and number of epochs.
    }



double validationPart1(std::vector<ImageObject>validationImages, std::vector<perceptron> &neuralNetwork, bool debugOutput)
{
    int goodCount = 0;

    for (auto &image : validationImages)
    {
        double maxSum = -std::numeric_limits<double>::infinity();
        int guess = -1;
        for (auto &perceptron : neuralNetwork)
        {

            double weightedSum = getWeightedSum(image, perceptron);


            if(maxSum < weightedSum){
                maxSum = weightedSum;
                guess = perceptron.labels;

            }

        }
        if(debugOutput)
        {
            std::cout << " Image Label: " << image.getImageLabel() << " Guess label" << guess << std::endl;
            std::cout << " Image VS Guess " << (image.getImageLabel() == guess) << std::endl;
        }
        goodCount += image.getImageLabel() == guess;

    }


    return static_cast<double>(validationImages.size() - goodCount)/validationImages.size();
}

double validationPart2(std::vector<ImageObject>validationImages, std::vector<perceptron> &neuralNetwork, bool debugOutput)
{

    double sigmoidValue = 0;
    double totalError = 0;
    for (auto &image : validationImages)
    {
        int guess = -1;
        for (auto &perceptron : neuralNetwork)
        {
            sigmoidValue = Sigmoid(getWeightedSum(image, perceptron));

            if(image.getImageLabel() == perceptron.labels){
                totalError +=  log(1- sigmoidValue);
            }else{
                totalError += log(sigmoidValue);
            }
        }
        if(debugOutput)
        {
            std::cout << " Image Label: " << image.getImageLabel() << " Guess label" << guess << std::endl;
            std::cout << " Image VS Guess " << (image.getImageLabel() == guess) << std::endl;
        }

    }

    return totalError;
}

double Sigmoid(double weightedSum)
{
    return 1 / (1 + exp(-weightedSum));
}

void NeuralNetworkTest(std::vector<ImageObject> testImages, std::vector<perceptron> &neuralNetwork)
{

    for (auto &image : testImages)
    {
        double maxSum = -std::numeric_limits<double>::infinity();
        int guess = -1;
        for (auto &perceptron : neuralNetwork)
        {
            double weightedSum = getWeightedSum(image, perceptron);

            if (maxSum < weightedSum)
            {
                maxSum = weightedSum;
                guess = perceptron.labels;
            }
        }
        std::cout << guess << " ";
    }
}



void initializePart1(std::vector<perceptron> & NNetwork){
    NNetwork.resize(10);
    std::mt19937 eng(1234);
    std::uniform_real_distribution<double> distr(-0.1, 0.1);

    for (int i = 0; i < 2; i++)
    {
        NNetwork[i].weights.resize(7);
        for (int j = 0; j < 7; j++)
        {
            NNetwork[i].weights[j] = distr(eng);
        }
        if (i == 0)
        {
            NNetwork[i].labels = 7;
        }
        else
        {
            NNetwork[i].labels = 9;
        }
    }
}

void initializePart2(std::vector<perceptron> &NNetwork){
    NNetwork.resize(10);
    std::mt19937 eng(1234);
    std::uniform_real_distribution<double> distr(-0.1, 0.1);

    for (int i = 0; i < 10; i++)
    {
        NNetwork[i].weights.resize(7);
        for (int j = 0; j < 7; j++)
        {
            NNetwork[i].weights[j] = distr(eng);
        }
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


std::vector<ImageObject> getImages(std::vector<std::string> s, bool isLabels)
{
    int label;
    std::vector<std::vector<int>> vectorFromFiles(28);
    for (auto &row : vectorFromFiles)
    {
        row.resize(28);
    }

    std::vector<ImageObject> images;
    std::wifstream inputStream;
    inputStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

    for (int i = 0; i < s.size(); i++)
    {
        inputStream.open(s[i], std::ios::in);    // open for reading
        if (!inputStream.is_open())
        {
            std::cout << "Unable to open " << s[i] << ". Terminating...";
            exit(2);
        }

        int x;
        while (inputStream && !inputStream.eof())
        {
            if (isLabels)
            {
                inputStream >> x;
                label = x;
            }
            for (int j = 0; j < 28; j++)
            {
                for (int k = 0; k < 28; k++)
                {
                    if (isLabels || (k != 0 || j != 0))
                    {
                        inputStream.ignore(1);
                    }

                    inputStream >> x;
                    vectorFromFiles[j][k] = x;

                }
            }
            images.emplace_back(label, vectorFromFiles);
        }
        inputStream.close();
    }

    return images;
}

std::vector<std::vector<std::vector<double>>> getFilter(std::string s)
{

    std::vector<std::vector<std::vector<double>>> vectorFilter(20, std::vector<std::vector<double>>(9, std::vector<double>(9)));

    std::wifstream inputStream;
    inputStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

            inputStream.open(s, std::ios::in);    // open for reading
            if (!inputStream.is_open())
            {
                std::cout << "Unable to open " << s << ". Terminating...";
                exit(2);
            }
                double x = 0;

        while (inputStream && !inputStream.eof())
        {

            for (int i = 0; i < 9; i++) //rows
            {
                for (int k = 0; k < 9; k++) //column
                {
                    for (int j = 0; j < 20; j++) // matrices
                    {

                        inputStream >> x;

                            if(inputStream.fail()){
                                inputStream.clear();
                                inputStream.ignore( 11,'\r\n');
                                inputStream >> x;
                                if(inputStream.eof()){
                                    break;
                                }

                            }

                            vectorFilter[j][i][k] = x;
                           // std::cout << vectorFilter[j][i][k] << " == " << x << std::endl;
                    }
                    }
                }
            }

         inputStream.close();
/*
    for (int j = 0; j < 20; j++) // matrices
    {
        for(int i = 0; i < 9; i++) //rows
        {

            for (int k = 0; k < 9; k++) //column
            {
                    std::cout << vectorFilter[j][i][k] << ' ';


            }
            std::cout << std::endl;
        }

    }
*/

    return vectorFilter;

}




std::vector<std::vector<std::vector<double>>> convolution(std::vector<std::vector<std::vector<double>>> filters/*filters that will be applied */, std::vector<std::vector<int>> image /*image 28x28*/)
{

    std::vector<std::vector<std::vector<double>>> returnMe;

return returnMe;
}

std::vector<std::vector<std::vector<int>>> getImageNonObject(std::vector<std::string> s,  std::vector<int> & labels, bool isLabels)
{
    int label;
    std::vector<std::vector<int>> vectorFromFiles(28);
    for (auto &row : vectorFromFiles)
    {
        row.resize(28);
    }

    std::wifstream inputStream;
    inputStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

    std::vector<std::vector<std::vector<int>>> images;

    for (int i = 0; i < s.size(); i++)
    {
        inputStream.open(s[i], std::ios::in);    // open for reading
        if (!inputStream.is_open())
        {
            std::cout << "Unable to open " << s[i] << ". Terminating...";
            exit(2);
        }

        int x;
        while (inputStream && !inputStream.eof())
        {
            if (isLabels)
            {
                inputStream >> x;
                labels.push_back(x);
            }
            for (int j = 0; j < 28; j++)
            {
                for (int k = 0; k < 28; k++)
                {
                    if (isLabels || (k != 0 || j != 0))
                    {
                        inputStream.ignore(1);
                    }

                    inputStream >> x;
                    vectorFromFiles[j][k] = x;


                }
            }
            images.emplace_back(vectorFromFiles);
        }
        inputStream.close();

    }
    return images;
}




std::vector<std::vector<double>> CNNTrain(std::vector<std::vector<std::vector<int>>> imageVectors, std::vector<int> labels, std::vector<std::vector<std::vector<double>>> filters, std::vector<std::vector<double>> & hiddenLayerNeurons, std::vector<std::vector<double>> & outputLayerNeurons)
{
    int n = labels.size();
    double alpha = 0.01;
    int bsize = 100;
  // std::vector<std::vector<std::vector<std::vector<int>>>> batch(100, std::vector<std::vector<std::vector<int>>>(100,std::vector<std::vector<int>>(28,std::vector<int>(28))));

    std::vector<std::vector<int>> blist(1000, std::vector<int>(100));
    std::vector<std::vector<std::vector<double>>> y1(20, std::vector<std::vector<double>>(20, std::vector<double>(20)));
    std::vector<std::vector<std::vector<double>>> y2(20, std::vector<std::vector<double>>(20, std::vector<double>(20)));
    std::vector<std::vector<std::vector<double>>> y3(10, std::vector<std::vector<double>>(10, std::vector<double>(10)));
    std::vector<double> y4(2000);
    std::vector<double> v5(100);
    std::vector<double> y5(100);
    std::vector<double> e5(100);
    std::vector<double> v(10);
    std::vector<double> delta(10);
    std::vector<double> d(10);
    std::vector<double> y;


    std::vector<std::vector<double>> dW5hiddenLayerNeurons(2000,std::vector<double>(100, 0.0));  //dW5 = matrix of order 2000 by 100 initialized to 0.0
    std::vector<std::vector<double>> dW0outputLayerNeurons(100,std::vector<double>(10, 0.0));  //dWo = matrix of order 100 by 10 initialized to 0.0



    std::vector<std::vector<std::vector<std::vector<int>>>> batchList(100, std::vector<std::vector<std::vector<int>>>(100,std::vector<std::vector<int>>(28,std::vector<int>(28))));

    for (int col = 0; col < bsize; col++) // batches
    {
        for (int row = 0; row < bsize; row++) // rows
        {
            batchList[col][row] = imageVectors[col * 100 + row];  //[1,101,201, .... 7901];  What type for blist?????
        }
    }

  //  % a single epoch loop%
    for(unsigned int batch = 1; batch < batchList.size(); batch++){  //for batch = 1 to 100 // length(blist)
                                                  // % Mini-batch lo
     int begin = batchList[batch];

     for(int k = begin; k < begin + bsize-1; k++){//for k = begin to (begin+bsize-1)
     //Forward pass - evaluate the output for input using current weights
         std::vector<std::vector<int>> x  = imageVectors[k];                      // x is the k-th row of size 28x28
         y1 = Conv(x, filters);              // applying all 20 filters to generate a 20x20x20 matrix
          y2 = ReLU(y1);                 // y2 is also a 20 x 20 x 20 matrix
          y3 = Pool(y2);                 // Mean-Pooling results in 10x10x20 matrix
         y4 = reshape(y3);              // converts y3 into a 1-dim matrix of order 1 x 2000
           v5 = y4 * hiddenLayerNeurons;                    // multiplying by hidden-layer matrix gives a 1 x 100 matrix
           y5 = ReLU1x100(v5);                 // just replace -ve values in v5 by 0; v5 is also 1 x 100
           v  = y5 * outputLayerNeurons;                    // multiplying by output-layer matrix gives a 1 x 10 matrix
           y  = Softmax(v);               // apply Softmax function to turn v into a vector that sums to 1

            d = correctOutput; // d is a 1 by 10 matrix in which d[i] = 1 where i is the label associated with the input; 0 else
            // Thus, if the D[k] = i, then d[i] = 1, and for all j != i, d[j] = 0
    //Backpropagation
          delta  = d - y;                   // error at the output layer; delta is 1 x 10
        e5     = delta * Wo';           // Wo' is just the transpose of Wo. e5 is 1 x 100
         delta5 = ReLu(e5);
           dW5hiddenLayerNeurons = dW5hiddenLayerNeurons + y4' * delta5;
          dW0outputLayerNeurons = dW0outputLayerNeurons + y5' * delta ;
   } //end-for (inner)

   // % Update weights for the mini-match
    dW5hiddenLayerNeurons = dW5hiddenLayerNeurons / bsize;
     dW0outputLayerNeurons = dW0outputLayerNeurons / bsize;
   hiddenLayerNeurons  = hiddenLayerNeurons + alpha * dW5hiddenLayerNeurons;
    outputLayerNeurons  = outputLayerNeurons + alpha * dW0outputLayerNeurons;
    return hiddenLayerNeurons;
    // end-for (outer)
}

    //end (of function)





}


std::vector<std::vector<std::vector<double>>> ReLU(std::vector<std::vector<std::vector<double>>> const x)
{
    std::vector<std::vector<std::vector<double>>> A(20,std::vector<std::vector<double>>(20, std::vector<double>(20)));
    for( int i = 0; i< 20; ++i )
        for (int j=0; j< 20; ++j) {
            for(int k = 0; k < 20; k++)
            {
                if (x[i][j][k] <= 0)
                {
                    A[i][j][k] = (0.0);
                }
                else A[i][j][k] = (x[i][j][k]);
            }
        }

    return A;
}


std::vector<double> ReLU1x100(std::vector<double> const x){

    std::vector<double> returnMe;
    return returnMe;
}

std::vector<std::vector<std::vector<double>>> Conv(std::vector<std::vector<int>> image, std::vector<std::vector<std::vector<double>>> filters){
    std::vector<std::vector<std::vector<double>>> convolutionMatrix;
    double product = 0.0;
    //will apply the filters using dot product to sub section 9x9 of the image
    for(int filter = 0; filter<20; filter++)
    {
        for(int shiftdown = 0; shiftdown<20 ; shiftdown++)
        {
            for (int shiftright = 0; shiftright < 20; ++shiftright) {
                for (int subimage = 0; subimage < 9; ++subimage) {
                    for (int kthfilter = 0; kthfilter < 9; ++kthfilter) {
                        product = product + filters[filter][subimage][kthfilter]*image[shiftdown+subimage][shiftright+kthfilter];
                        convolutionMatrix[filter][shiftdown][shiftright] = product;
                    }

                }
            }

        }
    }

    return convolutionMatrix;
    //the result should be a 20x20x20 matrix

}



std::vector<std::vector<std::vector<double>>> Pool(std::vector<std::vector<std::vector<double>>> const x){



    std::vector<std::vector<std::vector<double>>> returnMe;

    return returnMe;

}
std::vector<double> reshape(std::vector<std::vector<std::vector<double>>> const x){
    std::vector<double> returnMe;
    return returnMe;
}

std::vector<double> Softmax(std::vector<double> const x){

    std::vector<double> returnMe;
    return returnMe;
}