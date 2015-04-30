#include "ImageBase.h"
#include <stdio.h>
OCTET *ImgIn, *ImgOut;

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue [250], cNomImgEcrite [250];
	int S1(150);
    int S2 (70);

//	if (argc != 4)
	//{
		//printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n");
		//return 1;
	//}
	//sscanf (argv[1],"%s",cNomImgLue) ;
	//sscanf (argv[2],"%s",cNomImgEcrite);
	//sscanf (argv[3],"%d",&S);


	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load("img/09.pgm");

   // sscanf (argv[1],"%s",imIn) ;


//======================Seuillage - tp1===============================
//====================================================================
	//ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for(int x = 0; x < imIn.getHeight(); ++x)
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			if (imIn[x][y] < S1)
				imOut[x][y] = 255;
			//else if (imIn[x][y] > S1 && imIn [x][y] <S2)
              //  imOut[x][y] = 128;
            else
                imOut [x][y] = 0;
		}

	imOut.save("imsortie.pgm");

//ImageBase imOut2(imOut.getWidth(), imOut.getHeight(), imOut.getColor());

imOut.erosion();



//imOut.dilatation(imOut);

//imOut2=imOut.inversion(imOut);
//imOut2.save("iminverse.pgm");
//imIn.affichePix(true,0);
//imIn.histo();
//===============================================================

	///////////////////////////////////////// Exemple de cr�ation d'une image couleur
	ImageBase imC(50, 100, true);

	for(int y = 0; y < imC.getHeight(); ++y)
		for(int x = 0; x < imC.getWidth(); ++x)
		{
			imC[y*3][x*3+0] = 200; // R
			imC[y*3][x*3+1] = 0; // G
			imC[y*3][x*3+2] = 0; // B
		}

	imC.save("imC.ppm");




	///////////////////////////////////////// Exemple de cr�ation d'une image en niveau de gris
	ImageBase imG(50, 100, false);

	for(int y = 0; y < imG.getHeight(); ++y)
		for(int x = 0; x < imG.getWidth(); ++x)
			imG[y][x] = 50;

	imG.save("imG.pgm");




	ImageBase imC2, imG2;

	///////////////////////////////////////// Exemple lecture image couleur
	imC2.load("imC.ppm");
	///////////////////////////////////////// Exemple lecture image en niveau de gris
	imG2.load("imG.pgm");



	///////////////////////////////////////// Exemple de r�cup�ration d'un plan de l'image
	ImageBase *R = imC2.getPlan(ImageBase::PLAN_R);
	R->save("R.pgm");
	delete R;



	return 0;
}
