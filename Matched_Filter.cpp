#include "Matched_Filter.h"



Matched_Filter::Matched_Filter(cv::Mat& imagem, cv::Mat& mascara, cv::Mat& mascara_vasos) {
        imagem_entrada = imagem;
        mascara_entrada = mascara;
        mascara_vasos_entrada = mascara_vasos;
    }


cv::Mat Matched_Filter::padding_imagem(cv::Mat& imagem) { //padding da imagem

    using namespace std;
    using namespace cv;

    Mat padding = Mat::zeros(imagem.size().height+16, imagem.size().width+16, CV_8U);   //CV_8V = 8 bit/pixel, vai de 0 a 255
    for (int y = 0; y < imagem.size().height; y++) { 
        for (int x = 0; x < imagem.size().width; x++) {
            padding.at<uchar>(y+8,x+8) = imagem.at<uchar>(y,x);
        }
    }

    return padding;
}


cv::Mat Matched_Filter::convolucao_filtro_media(cv::Mat& imagem, cv::Mat& kernel) { //concolução da imagem com o filtro média

    using namespace std;
    using namespace cv;

    Mat imagem_filtrada = Mat::zeros(imagem.size(), CV_8U);
    for (int y = 8; y < imagem.size().height-7; y++) { //corro apenas a imagem sem o padding
        for (int x = 8; x < imagem.size().width-7; x++) {
            float acumulacao = 0;
            float soma_peso = 0;
            for (int i = -2; i <= 2; i++) { //tamanho do kernel que vai ser usado
                for (int j = -2; j <= 2; j++) {
                    acumulacao = acumulacao + imagem.at<uchar>(y+i, x+j) * kernel.at<uchar>(2+i, 2+j); //multiplo o kernel pelo ponto na imagem e somo o valor
                    soma_peso = soma_peso + kernel.at<uchar>(2+i, 2+j); //somatório do peso por causa do filtro, dá sempre 25 porque o kernel é 5x5
                }
            } 
        imagem_filtrada.at<uchar>(y,x) = acumulacao / soma_peso; //imagem filtrada com o filtro média
        }
    }

    return imagem_filtrada;
}


cv::Mat Matched_Filter::criacao_kernel(float angulo) { //criação de um kernel que irá variar com os diferentes ângulos

    using namespace std;
    using namespace cv;

    Mat kernel_calculo = Mat::zeros(15, 16, CV_32F);
    float numero_pontos = 0;  
    float soma = 0;
    for (int y = -7; y < 8; y++) {  //corre todas as linhas do kernel; usamos de -7 a 8 (equivalente a 16 linhas«) de modo a trabalharmos com o centro do kernel    
        for (int x = -7; x < 9; x++) {  //corre todas as colunas do kernel; usamos de -7 a 7 (equivalente a 15 colunas) de modo a trabalharmos com o centro do kernel
            float u = x * cos(angulo) + y * -sin(angulo);  //pi(u,v) = p(x,y) * ri(transposta);     ri = [cos(k) -sin(k)
            float v = x * sin(angulo) + y * cos(angulo);  //pi(u,v) = p(x,y) * ri(transposta);            sin(k)  cos(k)]
            if (abs(u) <= (3 * sigma) && abs(v) <= (L / 2) ) {  //é igual a N => verificação dos pontos de vizinhança
                kernel_calculo.at<float>(y+7,x+7) = -exp((-u * u) / (2 * sigma * sigma));  //define o kernel em [0 0]
                numero_pontos = numero_pontos + 1;  //números de pontos existentes na vizinhança N
                soma = soma + kernel_calculo.at<float>(y+7,x+7);
            }
            else {
                kernel_calculo.at<float>(y+7,x+7) = 0;  //valores fora da vizinhança são excluído (igualados a 0)
            }
        }
    }
    float media = soma / numero_pontos;  //valor médio do kernel
    for (int y = -7; y < 8; y++) { 
        for (int x = -7; x < 9; x++) { 
            float u = x * cos(angulo) + y * -sin(angulo);
            float v = x * sin(angulo) + y * cos(angulo);
            if (abs(u) <= (3 * sigma) && abs(v) <= (L / 2) ) {
                kernel_calculo.at<float>(y+7,x+7) = round(10 * (kernel_calculo.at<float>(y+7,x+7) - media - 0.015));  //1º - retiramos a média para normalizar; 2º - coeficientes * 10 e truncados (round) no inteiro mais próximo
            }
        }
    }
    Mat kernel = Mat::zeros(15, 16, CV_32F);  //1º - y = 15 = linhas; 2º - x = 16 = colunas
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 16; x++) {
            kernel.at<float>(y,x) = kernel_calculo.at<float>((14-y),x);  //simetria do kernel_calculo de modo a ter o kernel real porque o y está a ser corrido ao contrário do seu eixo
        }      
    }
    
    return kernel;
}


cv::Mat Matched_Filter::convolucao_kernel(cv::Mat& imagem, cv::Mat& kernel) { //convolução da imagem com o kernel criado anteriormente

    using namespace std;
    using namespace cv;

    Mat imagem_calculos = Mat::zeros(imagem.size(), CV_32F);
    for (int y = 8; y < imagem.size().height-7; y++) { //corro apenas a imagem sem o padding
        for (int x = 8; x < imagem.size().width-7; x++) {
            float acumulacao = 0;
            for (int yy = -7; yy < 8; yy++) {  
                for (int xx = -7; xx < 9; xx++) { 
                    acumulacao = acumulacao + imagem.at<uchar>(y+yy, x+xx) * kernel.at<float>(7+yy, 7+xx); //multiplo o kernel pelo ponto na imagem e somo o valor
                }
            } 
        imagem_calculos.at<float>(y,x) = acumulacao; //imagem filtrada com o kernel
        }
    }

    return imagem_calculos;
}


cv::Mat Matched_Filter::selecao_maximos(cv::Mat& imagem) { //seleção dos pontos máximos

    using namespace std;
    using namespace cv;

    Mat imagem_maximos = Mat::ones(imagem.size(), CV_32F) * -1e12; //para ter valores extremamente grandes e negativos //CV_32F é float; 32bit/pixel
    float pi = M_PI;
    for (float ang = 0; ang < (pi - pi/12); ang = ang + pi/12) {  //12 kernels com diferentes ângulos de pi/12 em pi/12   
        Mat kernel = criacao_kernel(ang); //criação de um kernel que irá variar com os diferentes ângulos
        Mat imagem_convoluida = convolucao_kernel(imagem, kernel); //concolução da imagem com o kernel criado anteriormente    
        for (int y = 0; y < imagem_convoluida.size().height; y++) {
            for (int x = 0; x < imagem_convoluida.size().width; x++) {
                if (imagem_convoluida.at<float>(y,x) > imagem_maximos.at<float>(y,x)) {
                    imagem_maximos.at<float>(y,x) = imagem_convoluida.at<float>(y,x);
                }
            }
        }
    }

    return imagem_maximos;
}


cv::Mat Matched_Filter::binarizacao(cv::Mat& imagem) { //binarização da imagem

    using namespace std;
    using namespace cv;

    float threshold = -100;
    Mat imagem_binaria = Mat::zeros(imagem.size(), CV_32F);
    for (int y = 0; y < imagem.size().height; y++) {
        for (int x = 0; x < imagem.size().width; x++) {
            if (imagem.at<float>(y,x) > threshold) {
                imagem_binaria.at<float>(y,x) = 255;
            }
        }
    }

    return imagem_binaria;
}


cv::Mat Matched_Filter::aplicacao_mascara(cv::Mat& imagem, cv::Mat& mascara) { //aplicação da máscara efetuada no TPC5 de modo a eliminar o background

    using namespace std;
    using namespace cv;

    Mat mascara_padding = padding_imagem(mascara); 
    for (int y = 0; y < mascara_padding.size().height; y++) {
        for (int x = 0; x < mascara_padding.size().width; x++) { 
            if (mascara_padding.at<uchar>(y,x) == 0) {
                imagem.at<float>(y,x) = 0;
            }
        }
    }

    return imagem;
}


cv::Mat Matched_Filter::conversao_CV_8U(cv::Mat& imagem) { //unpadding da imagem e obteção da segmentação

    using namespace std;
    using namespace cv;

    Mat imagem_convertida = Mat::zeros(imagem.size(), CV_8U);
    imagem.convertTo(imagem_convertida, CV_8U);

    return imagem_convertida;
}


cv::Mat Matched_Filter::unpadding_imagem(cv::Mat& imagem) { //conversão para CV_8U necessária caso contrário não iria funcionar

    using namespace std;
    using namespace cv;

    Mat imagem_segmentada = Mat::zeros(imagem.size().height-16, imagem.size().width-16, CV_8U);
    for (int y = 0; y < imagem_segmentada.size().height; y++) { 
        for (int x = 0; x < imagem_segmentada.size().width; x++) {
            imagem_segmentada.at<uchar>(y,x) = imagem.at<uchar>(y+8,x+8);
        }
    }

    return imagem_segmentada;
}

