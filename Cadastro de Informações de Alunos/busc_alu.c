#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

FILE *alunoss;
FILE *cpff;
FILE *idadee;
FILE *emaill;
FILE *turmaa;
FILE *seriee;

int dados_aluno(int x){
	
	setlocale(LC_ALL,"Portuguese");
	
	char nome[40];
	char cpf[15];
	char year[3];
	char mail[40];
	char turm[3];
	char seria[3];
	int cont1 = 1;
	
	printf("\n\t|| Dados do Aluno ||\t\n\n");
	
	alunoss = fopen("alunos.txt","r");
	cpff = fopen("cpfs.txt","r");
	idadee = fopen("idades.txt","r");
	emaill = fopen("emails.txt","r");
	turmaa = fopen("turmas.txt","r");
	seriee = fopen("series.txt","r");
	
	printf("Nome\t--------  ");
	rewind(alunoss);
	while(fgets(nome,40,alunoss) != NULL){
		fseek(alunoss,sizeof(2),SEEK_CUR);
		if(x == cont1){
			printf("%s",nome);
			break;
		}else{
			cont1++;
		}
	}
	
	cont1 = 1;
	
	printf("CPF\t--------  ");
	rewind(cpff);
	while(fgets(cpf,15,cpff) != NULL){
		fseek(cpff,sizeof(2),SEEK_CUR);
		if(x == cont1){
			printf("%s",cpf);
			break;
		}else{
			cont1++;
		}
	}
	
	cont1 = 0;
	
	printf("Idade\t--------  ");
	rewind(idadee);
	while(fgets(year,3,idadee) != NULL){
		fseek(idadee,sizeof(2),SEEK_CUR);
		if(x == cont1){
			printf("%s anos",year);
			break;
		}else{
			cont1++;
		}
	}
	
	cont1 = 1;
	printf("\n");
	
	
	printf("E-mail\t--------  ");
	rewind(emaill);
	while(fgets(mail,40,emaill) != NULL){
		fseek(emaill,sizeof(2),SEEK_CUR);
		if(x == cont1){
			printf("%s",mail);
			break;
		}else{
			cont1++;
		}
	}
	
	cont1 = 0;

	printf("Série\t--------  ");
	rewind(seriee);
	while(fgets(seria,3,seriee) != NULL){
		fseek(seriee,sizeof(2),SEEK_CUR);
		if(x == cont1){
			printf("%s",seria);
			break;
		}else{
			cont1++;
		}
	}
	
	cont1 = 0;
	
	printf("Turma\t--------  ");
	rewind(turmaa);
	while(fgets(turm,3,turmaa) != NULL){
		fseek(turmaa,sizeof(2),SEEK_CUR);
		if(x == cont1){
			printf("%s",turm);
			break;
		}else{
			cont1++;
		}
	}
	
	fclose(alunoss);
	fclose(cpff);
	fclose(idadee);
	fclose(emaill);
	fclose(turmaa);
	fclose(seriee);	
return 0;	
}

int buscar_nome(){
	
	setlocale(LC_ALL,"Portuguese");
	
	char nome[40];
	char comp[40];
	int cont = 1;
	
	printf("Informe o nome do aluno: ");
	fgets(nome,40,stdin);
	
	alunoss = fopen("alunos.txt","r");
	
	rewind(alunoss);
	
	while(fgets(comp,40,alunoss) != NULL){
		
		fseek(alunoss,sizeof(2),SEEK_CUR);
		//printf("%s",comp);
		if(strcmp(nome,comp) == 0){
			dados_aluno(cont);
			return 0;
			break;
		}else{
			cont++;
		}
		
	}
	
fclose(alunoss);
return printf("\nAluno não cadastrado!\n");	
}

int buscar_CPF(){
	
	setlocale(LC_ALL,"Portuguese");
	
	char CPF[15];
	char compcpf[15];
	int contcpf = 1;
	
	printf("Informe o CPF do aluno: ");
	fgets(CPF,15,stdin);
	
	cpff = fopen("cpfs.txt","r");
	
	rewind(cpff);
	
	while(fgets(compcpf,15,cpff) != NULL){
		
		fseek(cpff,sizeof(2),SEEK_CUR);
		//printf("%s",compcpf);
		if(strcmp(CPF,compcpf) == 0){
			dados_aluno(contcpf);
			return 0;
			break;
		}else{
			contcpf++;
		}
		
	}
	
fclose(cpff);
return printf("\nAluno não cadastrado!\n\n");	
}

int buscar_email(){
	
	setlocale(LC_ALL,"Portuguese");
	
	char eemail[40];
	char compemail[40];
	int contemail = 1;
	
	printf("Informe o E-mail do aluno: ");
	fgets(eemail,40,stdin);
	
	emaill = fopen("emails.txt","r");
	
	rewind(emaill);
	
	while(fgets(compemail,40,emaill) != NULL){
		
		fseek(emaill,sizeof(2),SEEK_CUR);
		if(strcmp(eemail,compemail) == 0){
			dados_aluno(contemail);
			return 0;
			break;
		}else{
			contemail++;
		}
		
	}
	
fclose(emaill);
return printf("\nAluno não cadastrado!\n\n");	
}

int busc_aluno(){
	
	setlocale(LC_ALL,"Portuguese");
	
	int op_busc;
	
	do{

		system("cls");
		printf("\t   Pesquisar\t\n\n");
		
		printf("Aluno-----------------------------\n");
		printf("||  1 - Buscar por nome\t\t||\n||  2 - Buscar por CPF\t\t||\n||  3 - Buscar por E-mail\t||\n||  4 - Voltar a tela inicial\t||\n\n Opção: ");
		scanf("%i",&op_busc);
		fflush(stdin);
		system("cls");
		
		switch(op_busc){
			
			case 1: printf("\t|| Busca por Nome ||\t\n\n");
					buscar_nome();
					break;
			
			case 2: printf("\t|| Busca por CPF ||\t\n\n");
					buscar_CPF();
					break;
			
			case 3: printf("\t|| Busca por E-mail ||\t\n\n");
					buscar_email();
					break;
			
			case 4: break;
			
			default:printf("\tOpção Inválida!\t\n\nDigite uma opção válida por favor!\n\n");
					break; 
			
		}
		
		printf("\n");
		system("pause");	
	}while(op_busc != 4);

return 0;	
}
