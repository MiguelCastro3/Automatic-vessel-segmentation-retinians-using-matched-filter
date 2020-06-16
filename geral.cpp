#include "Entrada_Saida_Imagens.h"
#include "Matched_Filter.h"
#include "Metricas.h"

int main() {

    using namespace std;
    using namespace cv;

    cout << "Insira o nome da pasta (test ou training) que deseja segmentar: " << endl;
    string test_training;
    cin >> test_training;
    cout << "" << endl;

    if (test_training == "test") {
        for (int i = 1; i < 21; i++) {
            //classe Entrada_Saida_Imagens
            Entrada_Saida_Imagens entrada_saida_imagens = Entrada_Saida_Imagens(test_training);
            vector<vector<Mat> > image_masca_vasos = entrada_saida_imagens.entrada_imagens(test_training);
            

            //classe Matched Filter
            Matched_Filter matched_filter = Matched_Filter(image_masca_vasos[0][i-1], image_masca_vasos[1][i-1], image_masca_vasos[2][i-1]);

            //padding da imagem
            Mat padding = matched_filter.padding_imagem(image_masca_vasos[0][i-1]); 

            //concolução da imagem com o filtro média
            Mat filtro_media = Mat::ones(5, 5, CV_8U); //criação do filtro média
            Mat imagem_filtrada = matched_filter.convolucao_filtro_media(padding, filtro_media);

            //criação dos kernels, convolução e seleção dos pontos máximos, umas dentro das outras
            Mat imagem_maximos = matched_filter.selecao_maximos(imagem_filtrada);

            //binarização da imagem
            Mat imagem_binaria = matched_filter.binarizacao(imagem_maximos);

            //aplicação de uma máscara de modo a obter apenas os vasos
            Mat imagem_binaria_sem_back =  matched_filter.aplicacao_mascara(imagem_binaria, image_masca_vasos[1][i-1]);

            //conversão para CV_8U
            Mat imagem_convertida = matched_filter.conversao_CV_8U(imagem_binaria_sem_back);

            //unpadding da imagem final e conversão
            Mat unpadding = matched_filter.unpadding_imagem(imagem_convertida);

            //saída da imagem final => segmentação concluída
            entrada_saida_imagens.saida_imagens(test_training, unpadding, i);

            //nome da imagem a ser tratada
            string numero = to_string(i);
            if (i < 10) {
                cout << "Imagem: 0" + numero + "_manual1" << endl;
            }
            else {
                cout << "Imagem: " + numero + "_manual1" << endl;
            }

            //classe Metricas
            Metricas metricas = Metricas(unpadding, image_masca_vasos[1][i-1], image_masca_vasos[2][i-1]);

            //resultado das métricas
            std::vector<float> sens_espe_exat = metricas.metricas(unpadding, image_masca_vasos[1][i-1], image_masca_vasos[2][i-1]);
            cout << "Sensibilidade: " << sens_espe_exat[0] << endl;
            cout << "Especificidade: " << sens_espe_exat[1] << endl;
            cout << "Exatidão: " << sens_espe_exat[2] << endl << endl;
        }
    }

    else if (test_training == "training") {
        for (int i = 21; i < 41; i++) {
            //classe Entrada_Saida_Imagens
            Entrada_Saida_Imagens entrada_saida_imagens = Entrada_Saida_Imagens(test_training);
            vector<vector<Mat> > image_masca_vasos = entrada_saida_imagens.entrada_imagens(test_training);


            //classe Matched Filter
            Matched_Filter matched_filter = Matched_Filter(image_masca_vasos[0][i-21], image_masca_vasos[1][i-21], image_masca_vasos[2][i-21]);

            //padding da imagem
            Mat padding = matched_filter.padding_imagem(image_masca_vasos[0][i-21]); 

            //concolução da imagem com o filtro média
            Mat filtro_media = Mat::ones(5, 5, CV_8U); //criação do filtro média
            Mat imagem_filtrada = matched_filter.convolucao_filtro_media(padding, filtro_media);

            //criação dos kernels, convolução e seleção dos pontos máximos, umas dentro das outras
            Mat imagem_maximos = matched_filter.selecao_maximos(imagem_filtrada);

            //binarização da imagem
            Mat imagem_binaria = matched_filter.binarizacao(imagem_maximos);

            //aplicação de uma máscara de modo a obter apenas os vasos
            Mat imagem_binaria_sem_back =  matched_filter.aplicacao_mascara(imagem_binaria, image_masca_vasos[1][i-21]);

            //conversão para CV_8U
            Mat imagem_convertida = matched_filter.conversao_CV_8U(imagem_binaria_sem_back);

            //unpadding da imagem final e conversão
            Mat unpadding = matched_filter.unpadding_imagem(imagem_convertida);

            //saída da imagem final => segmentação concluída
            entrada_saida_imagens.saida_imagens(test_training, unpadding, i);

            //nome da imagem a ser tratada
            string numero = to_string(i);
            cout << "Imagem: " + numero + "_manual1" << endl;

            //classe Metricas
            Metricas metricas = Metricas(unpadding, image_masca_vasos[1][i-21], image_masca_vasos[2][i-21]);

            //resultado das métricas
            std::vector<float> sens_espe_exat = metricas.metricas(unpadding, image_masca_vasos[1][i-21], image_masca_vasos[2][i-21]);
            cout << "Sensibilidade: " << sens_espe_exat[0] << endl;
            cout << "Especificidade: " << sens_espe_exat[1] << endl;
            cout << "Exatidão: " << sens_espe_exat[2] << endl << endl;
        }
    }

    else {
        cout << "ERRO! Pasta não encontrada." << endl << endl;
    }

    return 0;
}


/*
//funções criadas
cv::Mat padding_imagem(cv::Mat& imagem); //padding da imagem
cv::Mat convolucao_filtro_media(cv::Mat& imagem, cv::Mat& kernel); //concolução da imagem com o filtro média
cv::Mat criacao_kernel(float angulo); //criação de um kernel que irá variar com os diferentes ângulos
cv::Mat convolucao_kernel(cv::Mat& imagem, cv::Mat& kernel); //convolução da imagem com o kernel criado anteriormente
cv::Mat selecao_maximos(cv::Mat& imagem); //seleção dos pontos máximos
cv::Mat binarizacao(cv::Mat& imagem); //binarização da imagem
cv::Mat aplicacao_mascara(cv::Mat& imagem, cv::Mat& mascara); //aplicação da máscara do TPC5
cv::Mat unpadding_imagem(cv::Mat& imagem); //unpadding da imagem e obteção da segmentação
cv::Mat conversao_CV_8U(cv::Mat& imagem); //conversão para CV_8U necessária caso contrário não iria funcionar
std::vector<float> metricas(cv::Mat& imagem, cv::Mat& mascara, cv::Mat& mascara_vasos); //cálculo das métricas
*/