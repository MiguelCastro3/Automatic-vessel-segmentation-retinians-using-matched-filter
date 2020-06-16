#ifndef Metricas_h
#define Metricas_h


#include <cstdlib>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>


class Metricas {
public:
    Metricas(cv::Mat& imagem, cv::Mat& mascara, cv::Mat& mascara_vasos) ;

	std::vector<float> metricas(cv::Mat& imagem, cv::Mat& mascara, cv::Mat& mascara_vasos) ;


private:
    cv::Mat imagem_entrada;
    cv::Mat mascara_entrada;
    cv::Mat mascara_vasos_entrada; 
};



#endif   //Metricas