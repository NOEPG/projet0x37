#include <stdio.h>
#include <string.h>
#include <sndfile.h>
#include <stdlib.h>
/*
The library we use to process audio files (libsndfile) is avaible on https://github.com/erikd/libsndfile/ or http://www.mega-nerd.com/libsndfile/ , and is developed by Erik de Castro Lopo

*/


/*Ce code permet de renvoyer un tableau de donnée a partir d'un fichier wav */



/* désentrelace un tableau contenant plusieurs canal, renvoit un tableau selon le canal choisit */
double * channelread(int nbchannels, double *data,int frames,int channel){
double* datachannel=NULL;
int i=0;
int l=frames/nbchannels;
datachannel=calloc(l,sizeof(*datachannel));
if(!datachannel){return NULL;}
for(i=0 ; i < l ; i++ ){
	datachannel[i]=data[i*nbchannels+channel];};

return datachannel;
}
	
int main(void){
SNDFILE* infile;
SF_INFO sfinfo;
double* data=NULL;
double* datac=NULL;
int c;	
int i;
char *infilename="test.wav";

if (! (infile = sf_open (infilename, SFM_READ, &sfinfo))) /*condition if prise dans sfprocess.c dispo dans les exemples de la biblio sndfile, permet d'afficher proprement une erreur d'importation*/
	{
		printf ("Not able to open input file %s.\n", infilename) ;
		puts (sf_strerror (NULL)) ;
		return 1 ;
		} ;

printf("samples:%ld, samplerate:%d, channels:%d, format:0x%x\n",sfinfo.frames,sfinfo.samplerate,sfinfo.channels,sfinfo.format);

data=calloc( sfinfo.frames , sizeof(*data) );
sf_read_double(infile , data, sfinfo.frames) ; // stock les données infile dans le tableau data
sf_close( infile); 
printf("Quelle canal ? , choisir entre 0 et %d", (sfinfo.channels-1) );
scanf( "%d",&c );
datac=channelread(sfinfo.channels, data, sfinfo.frames, c);
/*affiche les données brutes du fichier audio selon le canal choisi, aucune utilité, on pourra mettre un graph a la place et renvoyer le tableau vers le bloc traitement */
for( i=0 ; i < (sfinfo.frames/sfinfo.channels) ; i++ ){
	printf("%f ",datac[i]);};
return 0;
}
