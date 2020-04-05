//
// Created by Raggdoll on 4/4/2020.
//

#ifndef PROJECT4_IMAGEOBJECT_HPP
#define PROJECT4_IMAGEOBJECT_HPP


class ImageObject {
public:
    ImageObject(std::vector<std::vector<int>> initialImage);
    void setDensity(std::vector<std::vector<int>> initialImage);
    void setSymmetry(std::vector<std::vector<int>> initialImage);
    void setIntersections(std::vector<std::vector<int>> initialImage);
   double getImageVector(int place) const {return ImageProcessed[place];};
   int getImageLabel(){return label;};

private:
    std::vector<double> ImageProcessed;
    int label;
    /* Note:
        ImageProcessed[0] = Density
        ImageProcessed[1] = Symmetry
        ImageProcessed[2] = Max Horizontal Intersection
        ImageProcessed[3] = Avg Horizontal Intersection
        ImageProcessed[4] = Max Vertical Intersection
        ImageProcessed[5] = Avg Vertical Intersection
        ImageProcessed[6] = ???????
    */
};


#endif //PROJECT4_IMAGEOBJECT_HPP
