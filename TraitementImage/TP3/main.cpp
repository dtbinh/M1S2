#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ImageBase.h"

using namespace std;

void histoGris(char* fileName, char* cNomHisto){
	
	int niveau[256];
	
	
	for(int i = 0 ; i< 256; i++){
		niveau[i] = 0;
	}
	
	ImageBase imIn;
	imIn.load(fileName);
	

	fstream fichier(cNomHisto, ios::out | ios::trunc);
	
	
	for(int i =0; i < imIn.getHeight(); i++){
		for(int j =0; j < imIn.getWidth(); j++){
			niveau[imIn[i][j]] = niveau[imIn[i][j]] + 1;
		}	
	}
	
	for(int i = 0 ; i< 256; i++){
		fichier << i << " " << niveau[i] <<  endl;
	}
	
	fichier.close();
}

void histoCouleur(char* fileName, char* cNomHisto){

	int niveauR[256];
	int niveauV[256];
	int niveauB[256];
	
	ImageBase imIn;
	imIn.load(fileName);
	
	fstream fichier(cNomHisto, ios::out | ios::trunc);
	
	for(int i = 0 ; i< 256; i++){
		niveauR[i] = 0;
		niveauV[i] = 0;
		niveauB[i] = 0;
	}
	
	for(int i =0; i < imIn.getHeight(); i++){
		for(int j =0; j < imIn.getWidth(); j++){
			niveauR[imIn[i][j*3]] = niveauR[imIn[i][j*3]] + 1;
			niveauV[imIn[i][(j*3) + 1]] = niveauV[imIn[i][(j*3) + 1]] + 1;
			niveauB[imIn[i][(j*3) + 2]] = niveauB[imIn[i][(j*3) + 2]] + 1;
		}	
	}
	
	for(int i = 0 ; i< 256; i++){
		fichier << i << " " << niveauR[i] << " " << niveauV[i] << " " <<  niveauB[i] <<  endl;
	}

	fichier.close();
}


void expansionGris(char* entre, char* sortie){

	int a0, a1, alpha, beta;
	
	ImageBase imIn;
	imIn.load(entre);
	
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	a0 = 0;
	a1 = 255/10;
	
	alpha = (-255*a0)/(a1-a0);
	beta = 255/(a1-a0);
	
	for(int i = 0; i < imIn.getHeight(); i++){
		for(int j = 0; j < imIn.getWidth(); j++){
			imOut[i][j] = alpha + beta*imIn[i][j];
		}
	}
	
	imOut.save(sortie);	
}

void expansionCouleur(char* entre, char* sortie){

	int a0, a1, alpha, beta;
	
	ImageBase imIn;
	imIn.load(entre);
	
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	a0 = 0;
	a1 = 255/10;
	
	alpha = (-255*a0)/(a1-a0);
	beta = 255/(a1-a0);
	
	
	for(int i = 0; i < imIn.getHeight() * 3; i++){
		for(int j = 0; j < imIn.getWidth(); j = j+3){
			for(int k = 0; k < 3; k++){
				imOut[i][j+k] = alpha + beta*imIn[i][j+k];
			} 
		}
	}
	
	imOut.save(sortie);	
}  

int retourneA0(char* nomFichier){

	ifstream fichier(nomFichier, ios::in);
	int min;
 
        if(fichier){
        	string s;
        	while (getline(fichier, s)){
        	
        	}
      
                fichier.close();
        }
        else{
        	cerr << "Impossible d'ouvrir le fichier !" << endl;
        }     
}

void seuilCouleur(char* entre, char* sortie){

	ImageBase imIn;
	imIn.load(entre);
	
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for(int x = 0; x < imIn.getHeight() * 3; x++){
		for(int y = 0; y < imIn.getWidth(); y = y+3){
			for(int k = 0; k < 3; k++){
				if (imIn[x][y + k] < 35){
					imOut[x][y + k] = 35;
				}else if (imIn[x][y + k] > 200){
					imOut[x][y + k] = 200;
				}else{
					imOut[x][y + k] = imIn[x][y + k];
				}
			} 
		}
	}
	
	imOut.save(sortie);	
}

int main(int argc, char* argv[]){

	char* cNomImgLue = new char[256];
	char* cNomImgEcrite = new char[256];
	char* cNomHisto = new char[256];
	int nH, nW, nTaille, S;
   
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	sscanf (argv[3],"%s",cNomHisto);
     
     	//expansion(cNomImgLue,cNomImgEcrite);
     	//histoGris(cNomImgEcrite,cNomHisto);
     	//histoCouleur(cNomImgLue, cNomHisto);
     	//expansionCouleur(cNomImgLue,cNomImgEcrite);
     	
     	seuilCouleur(cNomImgLue,cNomImgEcrite);
     	histoCouleur(cNomImgEcrite, cNomHisto);
     	
  
   

   return 1;
}
