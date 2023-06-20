#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

FILE *alunos;
FILE *cpf;
FILE *idade;
FILE *email;
FILE *turma;
FILE *serie;

int cont_linh(){
	
	alunos = fopen("alunos.txt","r");
	
	char c; 
	char letra = '\n';
    int vezes;
	
	while(fread (&c, sizeof(char), 1, alunos)) {
            if(c == letra) {
                vezes++;
            }
        } 
	
	fclose(alunos);
	return vezes;
}

int ver_alu(char x[40]){
	
	setlocale(LC_ALL,"Portuguese");
	
	char verif[40];
	
	alunos = fopen("alunos.txt","a+");
	
	rewind(alunos);
	
	while(fgets(verif,40,alunos) != NULL){
		
		fseek(alunos,sizeof(2),SEEK_CUR);
		
		if(strcmp(x,verif) == 0){
			
			return 1;
			fclose(alunos);
			break;
		}
		
	}
	
	fclose(alunos);
	return 0;
	
}

int cad_aluno(char x[40]){
	
	setlocale(LC_ALL,"Portuguese");
	
	char cpff[15];
	char year[3];
	char mail[40];
	char turm[3];
	char seria[3];
	int id = cont_linh();
	
	alunos = fopen("alunos.txt","a");
	cpf = fopen("cpfs.txt","a");
	idade = fopen("idades.txt","a");
	email = fopen("emails.txt","a");
	turma = fopen("turmas.txt","a");
	serie = fopen("series.txt","a");
	
	fprintf(alunos,"%i   %s",id,x);
		
	printf("CPF: ");
	fgets(cpff,15,stdin);
	fprintf(cpf,"%i   %s",id,cpff);
	
	printf("Idade: ");
	fgets(year,3,stdin);
	fprintf(idade,"%i   %s",id,year);
	fflush(stdin);
	
	printf("Email: ");
	fgets(mail,40,stdin);
	fprintf(email,"%i   %s",id,mail);
	
	printf("Turma: ");
	fgets(turm,3,stdin);
	fprintf(turma,"%i   %s",id,turm);
	
	printf("Série: ");
	fgets(seria,3,stdin);
	fprintf(serie,"%i   %s",id,seria);
	
	fclose(alunos);
	fclose(cpf);
	fclose(idade);
	fclose(email);
	fclose(turma);
	fclose(serie);
	printf("\nCadastro feito com sucesso!\n\n");
	
}

int add_aluno(){
	
	setlocale(LC_ALL,"Portuguese");
	
	char aluno[40];
	int op_cad;
	
	do{
	
		system("cls");
		printf("\t|| Cadastro de Alunos ||\t\n\n");
		
		printf("Nome completo: ");
		fgets(aluno,40,stdin);
		
		if(ver_alu(aluno) == 1){
			
			printf("\nAluno já cadastrado!\n");
			
		}else{
			
			cad_aluno(aluno);
			
		}
	
		printf("\nDigite 1 para registrar outro aluno ou digite outra tecla pra voltar a tela inicial\n\n");
		scanf("%i",&op_cad);
		fflush(stdin);
	
	}while(op_cad == 1);
	
return 0;	
}
