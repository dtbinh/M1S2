// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"



void erodeSansSeuil(char* entre, char* sortie){


	int nH, nW, nTaille,nB;
	int* tabR = new int[8];
	int* tabV = new int[8];
	int* tabB = new int[8];
	
	OCTET *ImgIn, *ImgOut;
   
	lire_nb_lignes_colonnes_image_ppm(entre, &nH, &nW);
	nTaille = nH * nW;
  
	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(entre, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille3);


	for (int i=0; i < nTaille3; i+=3){

		nB = 0;
		for(int k=-1; k<2; k++){
			for(int l=-1; l<2; l++){
				if( (k != 0) && (l != 0)){
					tabR[nB] =ImgIn[i + (k * l) ];
					tabV[nB] =ImgIn[(i + 1) + (k * l)];
					tabB[nB] =ImgIn[(i + 2) + (k * l) ];
					nB++;	
				}
			}
		}

			
		int maxR = 0;
		int maxV = 0;
		int maxB = 0;
		
		for(int t =0; t<8; t++){
			if((tabR[t] > maxR) && (tabR[t] != 0)){

				maxR = tabR[t];
			}
			if((tabV[t] > maxV) && (tabV[t] != 0)){
				maxV = tabV[t];

			}
			if((tabB[t] > maxB) && (tabB[t] != 0)){
				maxB = tabB[t];
			}
		}
			
        	ImgOut[i] = maxR;
        	ImgOut[i+1] = maxV;
        	ImgOut[i+2] = maxB;
        			
	}
	
		
	ecrire_image_ppm(sortie, ImgOut,  nH, nW);

	
	free(ImgIn);
	free(ImgOut);
}

void dilateSansSeuil(char* entre, char* sortie){


	int nH, nW, nTaille,nB;
	int* tabR = new int[8];
	int* tabV = new int[8];
	int* tabB = new int[8];
	
	OCTET *ImgIn, *ImgOut;
   
	lire_nb_lignes_colonnes_image_ppm(entre, &nH, &nW);
	nTaille = nH * nW;
  
	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(entre, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille3);


	for (int i=0; i < nTaille3; i+=3){

		nB = 0;
		for(int k=-1; k<2; k++){
			for(int l=-1; l<2; l++){
				if( (k != 0) && (l != 0)){
					tabR[nB] =ImgIn[i + (k * l) ];
					tabV[nB] =ImgIn[(i + 1) + (k * l)];
					tabB[nB] =ImgIn[(i + 2) + (k * l) ];
					nB++;	
				}
			}
		}

			
		int minR = 255;
		int minV = 255;
		int minB = 255;
		
		for(int t =0; t<8; t++){
			if((tabR[t] < minR) && (tabR[t] != 0)){
				minR = tabR[t];
			}
			if((tabV[t] < minV) && (tabV[t] != 0)){
				minV = tabV[t];
			}
			if((tabB[t] < minB) && (tabB[t] != 0)){
				minB = tabB[t];
			}
		}
			
        	ImgOut[i] = minR;
        	ImgOut[i+1] = minV;
        	ImgOut[i+2] = minB;
        			
	}
	
		
	ecrire_image_ppm(sortie, ImgOut,  nH, nW);
	
	free(ImgIn);
	free(ImgOut);
}




int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, S;
  
  /*
  if (argc != 4) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm Seuil \n"); 
       exit (1) ;
     }*/
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   //sscanf (argv[3],"%d",&S);
   
   erodeSansSeuil(cNomImgLue, cNomImgEcrite);
   //dilateSansSeuil(cNomImgLue, cNomImgEcrite);

/*
   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
	
   for (int i=0; i < nTaille3; i+=3)
     {
       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
       if (nR < S) ImgOut[i]=0; else ImgOut[i]=255;
       if (nG < S) ImgOut[i+1]=0; else ImgOut[i+1]=255; 
       if (nB < S) ImgOut[i+2]=0; else ImgOut[i+2]=255;
     }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   */
   return 1;
}
