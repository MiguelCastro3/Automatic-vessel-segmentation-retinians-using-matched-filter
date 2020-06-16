#ifndef Matched_Filter_h
#define Matched_Filter_h


#include <cstdlib>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#define PI 3.14159265358979323846

class Matched_Filter{
public:
    Matched_Filter(cv::Mat& imagem, cv::Mat& mascara, cv::Mat& mascara_vasos) ;


	cv::Mat padding_imagem(cv::Mat& imagem);


	cv::Mat convolucao_filtro_media(cv::Mat& imagem, cv::Mat& kernel) ;


	cv::Mat criacao_kernel(float angulo) ;


	cv::Mat convolucao_kernel(cv::Mat& imagem, cv::Mat& kernel) ;


	cv::Mat selecao_maximos(cv::Mat& imagem) ;


	cv::Mat binarizacao(cv::Mat& imagem) ;


	cv::Mat aplicacao_mascara(cv::Mat& imagem, cv::Mat& mascara) ;


	cv::Mat conversao_CV_8U(cv::Mat& imagem) ;


	cv::Mat unpadding_imagem(cv::Mat& imagem) ;


private:
    cv::Mat imagem_entrada;
    cv::Mat mascara_entrada;
    cv::Mat mascara_vasos_entrada;
    float const sigma = 2, L = 9; 
};



#endif   //Matched_Filter