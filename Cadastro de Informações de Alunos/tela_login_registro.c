/*
Universidade Estadual de Santa Cruz
Alunos: Bruno Felipe dos Santos Pereira e Brendom Gonçalves

Programa de cadastramento de alunos, onde professores e/ou coordenadores poderão fazer seu login e assim cadastrar informações de alunos,
registrar eles em séries/turmas, puxar as informações deles além de puxar os alunos de determinada série/turma. Para dinamizar e aumentar
o grau de complexidade, usamos algumas funções e ferramentas extras, como salvar os dados em um arquivo txt para usarmos futuramente e 
assim deixar o programa mais completo.
*/

// --------------Tela de registro e Login--------------//

// bibliotecas que vamos usar no programa
#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <locale.h>

#include "tela_inicial.cpp" // puxa as funções do arquivo tela_inicial.cpp que se encontra na mesma pasta que o principal

// o FILE *nome_do_ponteiro cria um ponteiro o qual vamos usar para manipular os arquivos txt
FILE * users;
FILE * pass;
FILE * log;

// Funçõo para verificar se o usuário optou por ficar logado ou não no programa
int ver_log() {

	char logo[3];
	char logo1[] = {
		"sim"
	};

	log = fopen("log.txt", "r"); // abrindo o arquivo log.txt no modo r (read) que é um modo de leitura apenas

	// laço de repetição para pegar cada linha do arquivo text e guardar no array logo 
	while (fgets(logo, 4, log) != NULL) {

		if (strcmp(logo1, logo) == 0) { // comparação se oque esta guardado na variável logo é igual ao que esta guardado na variável logo1
			fclose(log); // fechando um arquivo txt usando o ponteiro que representa ele
			return 0;
			break;
		}

	}

	fclose(log);
	return 1;
}

// Função para verificarmos quantas linhas tem o arquivo txt para colocarmos no ID importante para nós verificarmos
int cont_lin() {

	users = fopen("users.txt", "r");

	char c;
	char letra = '\n';
	int vezes;

	while (fread( & c, sizeof(char), 1, users)) { // varre o arquivo txt letra por letra
		if (c == letra) { // verificar se encontrou uma quebra de linha, representado pela variável letra (\n)
			vezes++; //  ao encontrar o contador vezes acrescenta mais 1, assim no final teremos o total de linhas que o arquivo tem
		}
	}

	fclose(users);
	return vezes; // retorno o valor da váriavel vezes
}

// Função para verificar a existência de um usuário para não ter usuário com nome repetido
int ver_ex(char x[20]) { // a função usa um paramentro que no caso vai ser o nome que o usuário digitar na hora do registro

	setlocale(LC_ALL, "Portuguese");

	char verif[20];

	users = fopen("users.txt", "a+"); // abrindo o arquivo users.txt, dessa vez no modo a+ que é para fazer a leitura além de acrescentar algo ao código

	rewind(users); // reposiciona o ponteiro que fica no arquivo (no caso o "mouse") para o inicio dele

	while (fgets(verif, 20, users) != NULL) {

		fseek(users, sizeof(2), SEEK_CUR); //  reposiciona o ponteiro a 2 bites de onde ele esta por causa do sizeof(2)

		if (strcmp(x, verif) == 0) { // verifica se o valor da variável verifca o mesmo que o parametro que foi pedido para usar na função 
			return 1;
			fclose(users);
			break;
		}

	}

	fclose(users);
	return 0;

}

// Função para cadastrar o usuário com nome e senha, dessa vez além do nome do usuário tbm temos como parametro o ID
int cad_us(char x[20], int y) {

	setlocale(LC_ALL, "Portuguese");

	char senha[20];

	// abrir os arquivos txt necessários no modo "a", que no caso é apenas para acrescentar dados ao fim do arquivo
	users = fopen("users.txt", "a");
	pass = fopen("pass.txt", "a");

	fprintf(users, "%i   %s", y, x); // escrevendo os dados no arquivo txt usando o fprintf

	// gravando a senha no arquivo txt
	printf("Informe uma senha: ");
	fgets(senha, 20, stdin);
	fprintf(pass, "%i   %s", y, senha);

	fclose(users);
	fclose(pass);
	return printf("\nCadastro feito com sucesso!\n\n");

}

// Função para verificar se a senha do usuário corresponde ao nome que ele informou
int ver_senha(char x[20]) { // o parametro tbm é o nome que o usuário digitar

	char verif[20];
	char passw[20];
	char senha[20];
	int cont = 0;
	int cont1 = 0;
	int verificador;

	users = fopen("users.txt", "r");
	pass = fopen("pass.txt", "r");

	rewind(users);

	// meio saber em qual linha esta o nome do usuário
	while (fgets(verif, 20, users) != NULL) {

		fseek(users, sizeof(2), SEEK_CUR);

		if (strcmp(x, verif) == 0) {
			break;
		} else {
			cont++; // cada vez que o while entrar nesse else, o numero da linha é gravado no cont por meio de incremento
		}
	}

	printf("Senha: ");
	fgets(senha, 20, stdin);

	rewind(pass);

	// meio para verificar se a senha informada pelo usuário é igual ao que esta no arquivo txt
	while (fgets(passw, 20, pass) != NULL) {
		fseek(pass, sizeof(2), SEEK_CUR);
		if (cont == cont1) { // se o numero da linha do arquivo pass foi igual ao cont, então executa a verificação da senha
			if (strcmp(senha, passw) == 0) {
				verificador = 1; // se a senha for igual ele retorna 1
			} else {
				verificador = 0; // se a senha for diferente ele retorna 0
			}
			break;
		} else { // enquanto o número da linha não for igual ao valor do cont, é acrescentado 1 ao cont1
			cont1++;
		}

	}

	fclose(pass);
	fclose(users);
	return verificador;

}

// Função principal de todo o programa
int main() {

	setlocale(LC_ALL, "Portuguese");

	char usuario[20]; // nome do usuario
	int op; // opção da tela de login
	int op_2; // opção no registro
	int ret; // retorno da função ver_ex
	int id = cont_lin(); // verificar qtd de linhas para ID

	// condicional para verificar se algum usuário ja esta logado, se estiver ele entra direto no programa
	if (ver_log() == 0) {
		tela_inicial();
	} else { // se não entra na tela de login e registro
		do {
			// menu da tela de login e registro
			printf("\t Bem-vindo(a) ao Sistema Escolar �nico\t\n\n");
			printf("|| 1 - Login \t||\n|| 2 - Cadastro ||\n|| 3 - Sair \t||\n\n Op��o: ");
			scanf("%i", & op);
			fflush(stdin);
			system("cls");

			switch (op) {
				// tela de login para o usuário
				case 1:
					printf("\tLogin do Us�rio\t\n\n");
					printf("Nome de usu�rio: ");
					fgets(usuario, 20, stdin);

					ret = ver_ex(usuario); // verificar se o usuário existe para esta se logando

					if (ret == 1) { // se retornar 1 é porque existe		
						if (ver_senha(usuario) == 1) { // se a senha que ele digitou for certa, ele entra no programa executando
							tela_inicial(); // a função do arquivo tela_inicial.cpp
							if (ver_log() == 0) { // se o usuário optar por permanecer logado, ele vai sair do programa nesse passo
								return 0;
							}
						} else {
							printf("\nSenha incorreta!\n\n");
						}
					} else {
						printf("\nNome de usu�rio inexistente!\n\n");
					}
					break;

				case 2:
					do { // tela de registro do usuário
						system("cls");
						printf("\tRegistro de Usuário\t\n\n");
						printf("Nome de usuário: ");
						fgets(usuario, 20, stdin);

						ret = ver_ex(usuario); // executa a função para ver se o nome do usuário já foi gravado em txt

						if (ret == 1) {
							printf("\nNome de usuário já cadastrado!\n\n");
						} else {
							cad_us(usuario, id); // faz o cadastro do usuario e senha nos arquivos txt, com o ID identificando eles
							id++; // cada vez que entra no else e executa a função cad_us() o ID aumenta automaticamente;
						}

						// escolha entre cadastrar outro usuario ou não usando a estrutura if e a ferramenta goto
						pergunta: printf("Deseja cadastrar outro usuário?\n|| 1 - Sim ||\n|| 2 - Não ||\n\nOpção: ");
						scanf("%i", & op_2);
						if ((op_2 != 1) && (op_2 != 2)) {
							printf("Opção inválida ! Digite novamente.\n\n");
							system("cls");
							goto pergunta;
						}
						fflush(stdin);
					} while (op_2 == 1);

					break;

				case 3:
					printf("\n\nO programa será finalizado...\n\n");
					break;

				default:
					printf("\n\t|| Opção inválida! ||\t\n\nInforme uma opção válida por favor.\n\n");
					break;
			}

			system("pause");
			system("cls");
		} while (op != 3); //  O programa vai executar at� quando for digitado o n�mero 3	
	}

	return 0;
}
// FIM DO PROGRAMA