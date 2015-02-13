#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "image_ppm.h"

using namespace std;


void histoGris(char* entre, char* cNomHisto){
	
	int niveau[256];
	int nW,nH,nTaille;
	
	for(int i = 0 ; i< 256; i++){
		niveau[i] = 0;
	}
	
	OCTET *ImgIn;
	
	lire_nb_lignes_colonnes_image_pgm(entre, &nH, &nW);
	nTaille = nH * nW;
  
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(entre, ImgIn, nH * nW);
	
	fstream fichier(cNomHisto, ios::out | ios::trunc);
		
	for(int i =0; i < nH; i++){
		for(int j =0; j < nW; j++){
			niveau[ImgIn[i*nW+j]] = niveau[ImgIn[i*nW+j]] + 1;
		}	
	}
	
	for(int i = 0 ; i< 256; i++){
		fichier << i << " " << niveau[i] <<  endl;
	}
	
	fichier.close();
}

void histoCouleur(char* entre, char* cNomHisto){

	int nH, nW, nTaille;
	int niveauR[256];
	int niveauV[256];
	int niveauB[256];

	OCTET *ImgIn;
   
   	lire_nb_lignes_colonnes_image_ppm(entre, &nH, &nW);
   	nTaille = nH * nW;
  
	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(entre, ImgIn, nH * nW);	

	for(int i = 0 ; i< 256; i++){
		niveauR[i] = 0;
		niveauV[i] = 0;
		niveauB[i] = 0;
	}
	
	fstream fichier(cNomHisto, ios::out | ios::trunc);
	
	for (int i=0; i < nTaille3; i+=3){		
		niveauR[ImgIn[i]] = niveauR[ImgIn[i]] + 1;
		niveauV[ImgIn[i+1]] = niveauV[ImgIn[i+1]] + 1;
		niveauB[ImgIn[i+2]] = niveauB[ImgIn[i+2]] + 1;
	}

	free(ImgIn);

	for(int i = 0 ; i< 256; i++){
		fichier << i << " " << niveauR[i] << " " << niveauV[i] << " " <<  niveauB[i] <<  endl;
	}

	fichier.close();	

}

void couleurToGris(char* entre, char* sortie){
	
	int nH, nW, nTaille;
	
	OCTET *ImgIn, *ImgOut;
	
	lire_nb_lignes_colonnes_image_ppm(entre, &nH, &nW);
   	nTaille = nH * nW;
   	
	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(entre, ImgIn, nH * nW);	
	allocation_tableau(ImgOut, OCTET, nTaille);
	
	for(int i=0; i<nTaille3; i++){
		ImgOut[i / 3] = (ImgIn[i] + ImgIn[i + 1] + ImgIn[i + 2] ) / 3; 
	}

	
	
	ecrire_image_pgm(sortie, ImgOut, nH, nW);
	
	free(ImgIn);
	free(ImgOut);

}

void seuilGris(char* entre, char* sortie){
	int nH, nW, nTaille;
	
	OCTET *ImgIn, *ImgOut;
	
	lire_nb_lignes_colonnes_image_pgm(entre, &nH, &nW);
   	nTaille = nH * nW;
   	
   	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(entre, ImgIn, nH * nW);	
	allocation_tableau(ImgOut, OCTET, nTaille);
	
	for(int i=0; i<nTaille; i++){
		if(ImgIn[i] < 180){
			ImgOut[i] = 0;
		}else{
			ImgOut[i] = 255;
		}
	}
	
	ecrire_image_pgm(sortie, ImgOut, nH, nW);
	
	free(ImgIn);
	free(ImgOut);
	
}

void floutageCouleur(char* entre, char* sortie){

	int nH, nW, nTaille;
	
	OCTET *ImgIn, *ImgOut;
	
	
	lire_nb_lignes_colonnes_image_pgm(imgGris, &nH, &nW);
   	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(imgGris, ImgIn, nH * nW);	
	allocation_tableau(ImgOutGris, OCTET, nTaille);
	
	

	
		
	ecrire_image_ppm(sortie, ImgOut, nH, nW);
	
	free(ImgIn);
	free(ImgOut);

}

int main(int argc, char* argv[]){

	char* cNomImgLue = new char[256];
	char* cNomImgEcrite = new char[256];
	char* cNomHisto = new char[256];
	int nH, nW, nTaille, S;
   
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	sscanf (argv[3],"%s",cNomHisto);
     
	//couleurToGris(cNomImgLue, cNomImgEcrite);
	//histoGris(cNomImgEcrite,cNomHisto);
	
	//seuilGris(cNomImgLue,cNomImgEcrite);
    	
    	floutageCouleur(cNomImgLue,cNomImgEcrite,cNomHisto);

   return 1;
}
