#ifndef Entrada_Saida_Imagens_h
#define Entrada_Saida_Imagens_h


#include <cstdlib>
#include <vector>
#include <cmath>  //para ir buscar cos, sin, exponencial(exp) e o valor de pi dado por M_PI = 3.14159
#include <opencv2/opencv.hpp>

class Entrada_Saida_Imagens{
public:
    Entrada_Saida_Imagens(std::string test_training) ;


	std::vector<std::vector<cv::Mat> > entrada_imagens(std::string test_training) ;


	void saida_imagens(std::string test_training, cv::Mat& imagem, int i) ;


private:
    std::string test_training_entrada; 
};





#endif   //Entrada_Saida_Imagens