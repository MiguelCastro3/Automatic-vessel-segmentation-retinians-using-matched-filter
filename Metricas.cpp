#include "Metricas.h"


Metricas::Metricas(cv::Mat& imagem, cv::Mat& mascara, cv::Mat& mascara_vasos) {
        imagem_entrada = imagem;
        mascara_entrada = mascara;
        mascara_vasos_entrada = mascara_vasos;
    }


std::vector<float> Metricas::metricas(cv::Mat& imagem, cv::Mat& mascara, cv::Mat& mascara_vasos) { //cálculo das métricas

    using namespace std;
    using namespace cv;

    vector<float> sens_espe_exat(3); //vetor com as três métricas calculdas
    float verdadeiros_positivos = 0;  
    float verdadeiros_negativos = 0;
    float falsos_positivos = 0;
    float falsos_negativos = 0;
    for (int y = 0; y < imagem.size().height; y++) { 
        for (int x = 0; x < imagem.size().width; x++) {
            if (mascara.at<uchar>(y,x) == 255) { //apenas procura nos pontos dentro da máscara
                if (imagem.at<uchar>(y,x) == 255 && mascara_vasos.at<uchar>(y,x) == 255) { //verdadeiros positivos => imagem calculada = 1 e mascara da DRIVE = 1
                    verdadeiros_positivos = verdadeiros_positivos + 1;
                }
                else if (imagem.at<uchar>(y,x) == 0 && mascara_vasos.at<uchar>(y,x) == 0) { //verdadeiros negativos => imagem calculada = 0 e mascara da DRIVE = 0
                    verdadeiros_negativos = verdadeiros_negativos + 1;
                }
                else if (imagem.at<uchar>(y,x) == 255 && mascara_vasos.at<uchar>(y,x) == 0) { //falsos positivos => imagem calculada = 1 e mascara da DRIVE = 0
                    falsos_positivos = falsos_positivos + 1;
                }
                else if (imagem.at<uchar>(y,x) == 0 && mascara_vasos.at<uchar>(y,x) == 255) { //falsos negativos => imagem calculada = 0 e mascara da DRIVE = 1
                    falsos_negativos = falsos_negativos + 1;
                }
            }
        }
    }
    sens_espe_exat[0] = verdadeiros_positivos / (verdadeiros_positivos + falsos_negativos) * 100;
    sens_espe_exat[1] = verdadeiros_negativos / (verdadeiros_negativos + falsos_positivos) * 100;
    sens_espe_exat[2] = (verdadeiros_positivos + verdadeiros_negativos) / (verdadeiros_positivos + verdadeiros_negativos + falsos_positivos + falsos_negativos) * 100;

    return sens_espe_exat;
}


