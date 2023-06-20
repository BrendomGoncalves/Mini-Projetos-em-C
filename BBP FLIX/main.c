/****
  UESC - Universidade Estadual de Santa Cruz
	DCET - Ciência da Computação
	Linguagem de Programação II
	Prof: Elinaldo Santos de Goes Júnior
	Alunos: Brendom Victor Gama Gonçalves / 202021652
          Bruno Felipe dos Santos Pereira / 202021653
          Pedro Henrick Borges Silva / 202021765
  Título: BBPFlix  
  Data de Criação: 05/11/2021
  Ultima Modificação: 01/12/2021
  *
  Descrição: Esse programa serve como um catálogo de itens do tipo Filme, Série e Documentário, onde o usuário pode cadastrar tais itens especificando o título, tipo, ano e nota. Além do cadastro, existe a possibilidade de listagem (de todos os itens ou por tipo),busca (por ID ou por título), modificação de nota e exclusão. O programa se utiliza de um arquivo ASCII (arquivo de texto) como um "banco de dados" para as informações fornecidas pelo usuário, assim como de bibliotecas com funções específicas para cada operação disponível.
****/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "add_Item.h" //"biblioteca" onde ficam armazenadas as funções relacionadas ao armazenamento dos itens no arquivo ASCII//
#include "list_Item.h" //"biblioteca" onde ficam armazenadas as funções relacionadas a listagem dos itens//
#include "del_Item.h" //biblioteca onde está armazenada a função relacionada a exclusão de itens no programa//
#include "mod_Nota.h" //biblioteca onde está armazenada a função relacionada a modificação de nota dos itens//
#include "buscar_Item.h" //biblioteca onde estão armazenadas as funções correpondentes a opção de busca de itens//

/****
  Título: main();
  Data de Criação: 05/11/2021
  Ultima Modificação: 25/11/2021
  *
  Descrição: A função principal do programa, ela faz o papel de menu principal para o usuário, mostrando as principais operações que podem ser feitas. A cada final de operação, o programa trás o usuário a esse menu, para assim, ele poder escolher qual nova operação ira realizar ou se deseja sair. O menu principal também tem um verificador para que quando o usuário informe uma opção inválida, ele emita uma mensagem para que informe uma opção válida, retornando a parte da escolha de opção.
****/
int main(){

  setlocale(LC_ALL,"Portuguese");

  int opc_Principal; //Variável utilizada para armazenar a escolha do usuário no menu principal// 

  /****
    Começo do menu, ele fica dentro de um laço de repetição do tipo do while() para que o programa só finalize quando o usuário desejar, assim evitando que tenha que abrir repetidamente o programa. Assim, utilizando a variável opc_Principal para guardar a opção escolhida pelo usuário, o programa só encerrará quando essa variável for igual a 6.
  ****/
  do{
    system("clear"); //comando para limpar a tela sempre quando entrar no menu principal
    printf("\t====BEM-VINDO(A)====\t\n\n");
    printf("Informe uma das opções abaixo:\n1. Adicionar Item\n2. Listar Itens\n3. Buscar Item\n4. Modificar Nota\n5. Excluir Item\n6. Sair\n");

    /****
      Esse do while(), que tem como parametro a variável opc_Principal, serve para verificar se o usuário informou uma opção válida, assim seguindo normalmente quando sim, e retornando para a escolha da opção com uma mensagem quando não tiver escolhido uma opção aceita.
    ****/
    do{
      printf("\nOpção: ");
      scanf("%i", &opc_Principal);
      setbuf(stdin, NULL); //comando para limpar a sujeita do teclado//

      //utilizando a estrutura de condicional do tipo switch para chamar a função informada pelo usuário, tendo como parâmetro a variável opc_Principal//
      switch(opc_Principal){

        case 1: 
        adicionar_Item(); //chamando a função principal da biblioteca add_Item.h//
        break;
        
        case 2: 
        menu_List(); //chamando a função principal da biblioteca list_Item.h//
        break;

        case 3: 
        menu_Busc_Item(); //chamando a função principal da biblioteca buscar_Item.h//
        break;

        case 4: 
        modificar_Nota(); //chamando a função principal da biblioteca mod_Nota.h//
        break;

        case 5: 
        excluir_Item(); //chamando a função principal da biblioteca del_Item.h//
        break;

        case 6: 
        printf("\n\tObrigado por usar o BBPFlix! Volte sempre.\t\n");
        break;

        default:  
        printf("\nEscolha uma opção válida!");
        break;

      }//Final do switch
    }while((opc_Principal > 6) || (opc_Principal < 1));
  }while(opc_Principal != 6);

  return 0; 
}//Final main