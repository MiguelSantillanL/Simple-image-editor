#include <opencv2/opencv.hpp>
#include <cmath>
#include "Matriz_P.hpp"

using namespace std;
using namespace cv;

int Process_Pic();
void Image_Grayscale(int **M_Pic, int rows, int col);
void Max_Image(int **M_Pic,int rows,int col);
void Min_Image(int **M_Pic,int rows,int col);
void Rot_Image(int **M_Pic,int rows,int col);
float **GetRGB(int rows,int col,int RGBopc,Mat Color_Pic);

