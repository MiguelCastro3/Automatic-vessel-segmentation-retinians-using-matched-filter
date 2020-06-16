#include "Entrada_Saida_Imagens.h"

Entrada_Saida_Imagens::Entrada_Saida_Imagens(std::string test_training) {
    test_training_entrada = test_training;
}


std::vector<std::vector<cv::Mat> > Entrada_Saida_Imagens::entrada_imagens(std::string test_training) {

    using namespace std;
    using namespace cv;

    vector<Mat> vetor_imagens_entrada;
    vector<Mat> vetor_mascara_entrada;
    vector<Mat> vetor_mascara_vasos_entrada;
    vector<vector<Mat>> vetor_final;
    string numero, caminho_imagem, caminho_mascara, caminho_mascara_vasos;

    //processamento das imagens test
    if (test_training == "test") {
        for (int i = 1; i < 21; i++) {
            if (i < 10) {
                numero = to_string(i);
                caminho_imagem = "DRIVE/test/images/0" + numero + "_test.tif";
                caminho_mascara = "DRIVE/test/mask/mask0" + numero + ".png";
                caminho_mascara_vasos = "DRIVE/test/1st_manual/0" + numero + "_manual1.png";
            }
            else {
                numero = to_string(i);
                caminho_imagem = "DRIVE/test/images/" + numero + "_test.tif";
                caminho_mascara = "DRIVE/test/mask/mask" + numero + ".png";
                caminho_mascara_vasos = "DRIVE/test/1st_manual/" + numero + "_manual1.png";
            }

            //leitura da imagem e seleção do canal verde
            Mat imagem = imread(caminho_imagem, IMREAD_COLOR); //leitura da imagem escolhida
            Mat channels[3]; //channels <=> número de canais da imagem; channels[1] = canal
            split(imagem, channels);
            Mat imagem_verde = channels[1].clone(); //colocação da imagem em tons de cinza e cópia desta
            vetor_imagens_entrada.push_back(imagem_verde);
            Mat mascara = imread(caminho_mascara, IMREAD_GRAYSCALE); //leitura da máscara indicada
            vetor_mascara_entrada.push_back(mascara);
            Mat mascara_vasos = imread(caminho_mascara_vasos, IMREAD_GRAYSCALE); //leitura da máscara indicada
            vetor_mascara_vasos_entrada.push_back(mascara_vasos);
        }
        vetor_final.push_back(vetor_imagens_entrada);
        vetor_final.push_back(vetor_mascara_entrada);
        vetor_final.push_back(vetor_mascara_vasos_entrada);
    }

    //processamento das imagens training
    else if (test_training == "training") {
        for (int i = 21; i < 41; i++) {
            numero = to_string(i);
            caminho_imagem = "DRIVE/training/images/" + numero + "_training.tif";
            caminho_mascara = "DRIVE/training/mask/mask" + numero + ".png";
            caminho_mascara_vasos = "DRIVE/training/1st_manual/" + numero + "_manual1.png";

            //leitura da imagem e seleção do canal verde
            Mat imagem = imread(caminho_imagem, IMREAD_COLOR); //leitura da imagem escolhida
            Mat channels[3]; //channels <=> número de canais da imagem; channels[1] = canal
            split(imagem, channels);
            Mat imagem_verde = channels[1].clone(); //colocação da imagem em tons de cinza e cópia desta
            vetor_imagens_entrada.push_back(imagem_verde);
            Mat mascara = imread(caminho_mascara, IMREAD_GRAYSCALE); //leitura da máscara indicada
            vetor_mascara_entrada.push_back(mascara);
            Mat mascara_vasos = imread(caminho_mascara_vasos, IMREAD_GRAYSCALE); //leitura da máscara indicada
            vetor_mascara_vasos_entrada.push_back(mascara_vasos);
        }
        vetor_final.push_back(vetor_imagens_entrada);
        vetor_final.push_back(vetor_mascara_entrada);
        vetor_final.push_back(vetor_mascara_vasos_entrada);
    }


    return vetor_final;
}


void Entrada_Saida_Imagens::saida_imagens(std::string test_training, cv::Mat& imagem, int i) { //concolução da imagem com o filtro média

    using namespace std;
    using namespace cv;

    string numero, caminho_nome_imagem;

    //saída das imagens test
    if (test_training == "test") {
            if (i < 10) {
            numero = to_string(i);
            caminho_nome_imagem = "Imagens segmentadas/test/imagem_final_0" + numero + ".png";
        }
        else {
            numero = to_string(i);
            caminho_nome_imagem = "Imagens segmentadas/test/imagem_final_" + numero + ".png";
        }
        //saída da imagem final => segmentação concluída
        imwrite(caminho_nome_imagem, imagem);
    }

    //saída das imagens training
    else if (test_training == "training") {
        numero = to_string(i);
        caminho_nome_imagem = "Imagens segmentadas/training/imagem_final_" + numero + ".png";
        //saída da imagem final => segmentação concluída
        imwrite(caminho_nome_imagem, imagem);
    }

}
