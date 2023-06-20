#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

FILE *alunosss;
FILE *turmasss;
FILE *serieee;

int cont_linha(){
	
	alunosss = fopen("alunos.txt","r");
	
	char c; 
	char letra = '\n';
    int vezes;
	
	while(fread (&c, sizeof(char), 1, alunosss)) {
            if(c == letra) {
                vezes++;
            }
        } 
	
	fclose(alunosss);
	return vezes;
}

int turmas(){

	setlocale(LC_ALL,"Portuguese");
	
	int i = 0;
	int j = 1;
	char *nomes[j][2];
	char nome[40];
	char turm[3];
	char tur[3];
	char ser[3];
	char sirei[3];
	int id = cont_linha();
	int cont = -2;
	int cont1 = -1;
	int cont2 = -2;
	
	printf("\t|| Turmas ||\n\n");
	
	printf("Informe a Série: ");
	fgets(ser,3,stdin);
	printf("\n");
	
	printf("Informe a Turma: ");
	fgets(tur,3,stdin);
	printf("\n");
	
	alunosss = fopen("alunos.txt","r");
	turmasss = fopen("turmas.txt","r");
	serieee = fopen("series.txt","r");
	
	rewind(serieee);
	rewind(alunosss);
	rewind(turmasss);
	
	for(int i = 1; i <= (id - 1); i++){
		
		while(fgets(sirei,3,serieee) != NULL){
			fseek(serieee,sizeof(2),SEEK_CUR);
			cont2++;
			if(strcmp(ser,sirei) == 0){
				rewind(turmasss);
				cont = -2;
				while(fgets(turm,3,turmasss) != NULL){
				fseek(turmasss,sizeof(2),SEEK_CUR);
				cont++;
					if((strcmp(tur,turm) == 0) && (cont == cont2)){
						rewind(alunosss);
						cont1 = -1;
						while(fgets(nome,40,alunosss) != NULL){
							cont1++;
							fseek(alunosss,sizeof(2),SEEK_CUR);
							if(cont1 == cont){
								nomes[i][1] = nome;
								printf("%i ---- %s",j,nomes[i][1]);
								j++;
								i++;
								break;
							}
						}
						break;
					}
				}
			break;
			}
		}	
	}
	
	fclose(serieee);
	fclose(turmasss);
	fclose(alunosss);
	printf("\n");	
system("pause");
return 0;	
}
