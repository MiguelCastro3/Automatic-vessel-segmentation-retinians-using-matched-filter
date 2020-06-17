# Automatic vessel segmentation retinians using matched filter
**PROJECT:** 

Creation of an algorithm that allows to automatically segment the retinal vessels in images of the fundus. This algorithm was based on the matched filter. OpenCV was used to read and write the image files.

**STEPS:** 

* Implementation of the matched filter algorithm;
* Restructuring the algorithm to classes.

**FILES:** 
* [DRIVE](https://github.com/MiguelCastro3/Automatic-vessel-segmentation-retinians/tree/master/DRIVE) - (Digital Retinal Images for Vessel Extraction) - contains image data sets (test and training) with images for segmentation, respective mask and respective manual segmentation.
* [Segmentation results](https://github.com/MiguelCastro3/Automatic-vessel-segmentation-retinians/tree/master/Segmentation%20results) - contains the images resulting from the algorithm developed for automatic segmentation of retinal vessels.
* [Entrada_Saida_Imagens.h](https://github.com/MiguelCastro3/Automatic-vessel-segmentation-retinians/blob/master/Entrada_Saida_Imagens.h) and [Entrada_Saida_Imagens.cpp](https://github.com/MiguelCastro3/Automatic-vessel-segmentation-retinians/blob/master/Entrada_Saida_Imagens.cpp) - class Entrada_Saida_Images with the code referring to the reading and writing of the images used in the algorithm.
* [Matched_Filter.h](https://github.com/MiguelCastro3/Automatic-vessel-segmentation-retinians/blob/master/Matched_Filter.h) and [Matched_Filter.cpp](https://github.com/MiguelCastro3/Automatic-vessel-segmentation-retinians/blob/master/Matched_Filter.cpp) - Matched_Filter class with the code for most of the algorithm. This is where all image processing and automatic segmentation take place.
* [Metricas.h](https://github.com/MiguelCastro3/Automatic-vessel-segmentation-retinians/blob/master/Metricas.h) and [Metricas.cpp](https://github.com/MiguelCastro3/Automatic-vessel-segmentation-retinians/blob/master/Metricas.cpp) - Metricas class compares the image resulting from the algorithm with DRIVE segmentation by calculating some metrics, sensitivity, specificity and accuracy, for future discussion of algorithm quality.

**RESULTS:** 

An example of the results obtained. 
![21_imagem_segmentada - Cópia](https://user-images.githubusercontent.com/66881028/84839586-483e0200-b035-11ea-8922-f8215ce8b44b.png)
| Image/Metrics  | Sensitivity | Specificity | Accuracy |
| ------------- | ------------- | ------------- | ------------- |
| 21_training  | 51.3892  | 99.3362 | 94.0216 |
