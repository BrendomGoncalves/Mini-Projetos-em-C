//TELA INICIAL PARA O USUÁRIO

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "cad_alu.cpp"
#include "busc_alu.cpp"
#include "series.cpp"

FILE *logos;

int tela_inicial(){
	
	setlocale(LC_ALL,"Portuguese");
	
	int op_inicial;
	
	do{
	
		system("cls");
		printf("\tBem vindo(a)\t\n");
		
		printf("Menu------------------------------\n");
				
		printf("|| 1 - Pesquisar Aluno \t\t||\n");
		printf("|| 2 - Cadastrar Aluno \t\t||\n");
		printf("|| 3 - Turmas \t\t\t||\n");
		printf("----------------------------------\n");
		printf("|| 4 - Sair sem fazer Log Off\t||\n");
		printf("|| 5 - Fazer Log off \t\t||\n\n Opção: ");
		
		scanf("%i",&op_inicial);
		fflush(stdin);
		system("cls");
		
		switch(op_inicial){
			
			case 1: busc_aluno();
					break;
				
			case 2: add_aluno();
					break;
			
			case 3: turmas();
					break;
					
			case 4: logos = fopen("log.txt","w");
					fprintf(logos,"sim");
					fclose(logos);
					printf("\tAté depois!\t\nNa próxima vez que entrar já estara logado!\n\n");
					break;
			
			case 5: logos = fopen("log.txt","w");
					fprintf(logos,"nao");
					fclose(logos);
					printf("\tAté depois\t\n");
					break;
			
			default:printf("\tOpção Inválida!\t\Escolha uma opção das opções oferecidas.\n\n");
					system("pause");
					break;
			
		}
	
		if(op_inicial == 4){
			break;
		}
	
	}while(op_inicial != 5);
	
return 0;
}
