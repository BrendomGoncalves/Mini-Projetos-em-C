#include <stdio.h>
#include <stdlib.h>

FILE *antigo_Arq; //ponteiro que apontará para o antigo arquivo onde os dados estavam armazenados, que no final da função excluir_Item() será apagado//
FILE *novo_Arq; //ponteiro que apontará para o novo arquivo ASCII, onde os dados atualizados serão garavados, e no final da função excluir_Item(), será renomeado para o nome padrão passado no trabalho final//

//estrutura com as variáveis que serão usadas pra armazenar os dados lidos do arquivo ASCII//
struct delete_Item{
  int id;
  char titulo[150];
  char tipo[13];
  int ano_Lanc;
  float notas;
};

/****
  Título: excluir_Item();
  Data de Criação: 19/11/2021
  Ultima Modificação: 27/11/2021
  *
  Descrição: Essa função é responsável por realizar a exclusão de algum item desejado pelo usuário, assim, ao informar o id correspondente do item (que será guardado na variável inteira del_Item), o mesmo, se existir no arquivo ASCII (que será verificado com uma estrutura condicional do tipo if, comparando os id informado com os id´s dos itens), terá seu id deletado, assim passando para um novo arquivo todos os itens, porém o item selecionado pelo usuário não ira com id, assim não podendo aparecer em buscas e listagens no programa.
****/
void excluir_Item(){

  struct delete_Item ex_Item; //variável o tipo struct delete_Item que servirá para armazenar os dados dos itens lidos no arquivo ASCII antigo, e assim passará os novos dados para um novo arquivo, dessa vez com o id do item desejado excluido, assim fazendo com que ele não apareça em buscas futuras no programa//
  int del_Item; //variável que armazenará o id informado pelo usuário, o qual corresponde ao item que será deletado//
  int del_Contador = 1;
  int ver_ID = 0; //variável para verificar se o ID foi encontrado ou não no arquivo, se estiver com o valor igual a 1, quer dizer que encontrou o id, caso contrário, significará que não encontoru o ID//
  int opc_Del_Item; //variável usada para armazenar o valor da opção escolhida pelo usuário relativo a excluir ou não o item encontrado com o id informado//
  char carac_Del;
  
  system("clear");
  printf("\t===== Excluir Item =====\n\n");
  printf("Informe o ID do item que deseja excluir: ");
  scanf("%i", &del_Item);
  setbuf(stdin, NULL);

  antigo_Arq = fopen("itens.dat", "r");
  novo_Arq = fopen("itens2.dat", "a");

  if((antigo_Arq == NULL) || (novo_Arq == NULL)){
    printf("\nERROR: Erro ao abrir o arquivo!\n");
  }else{
    rewind(antigo_Arq);
    rewind(novo_Arq);   
    ex_Item.id = -1; //caso o programa inicie com o primeiro item com seu id excluido, a listagem começara com o id = -1, fazendo com que o dados do primeiro item não apareça de inicio//
    
    /****
      Começo de uma estrutura de repetição do tipo while() que fará a leitura do arquivo pegando os dados e armazenando nas variaveis da estrutura do ex_Item, assim a cada @ o contador aumenta passando para o próximo if com o bloco de comando para pegar dada informação do item 
    ****/
    while(fscanf(antigo_Arq, "%c", &carac_Del) != EOF){
      if(del_Contador == 1){
        fseek(antigo_Arq, ftell(antigo_Arq)-1, SEEK_SET);
        fscanf(antigo_Arq,"%i", &ex_Item.id);
        del_Contador++;
      }else if(del_Contador == 2){
        fscanf(antigo_Arq,"%[^'@']s",&ex_Item.titulo);
        del_Contador++;
      }else if(del_Contador == 3){
        fscanf(antigo_Arq, "%[^'@']s",&ex_Item.tipo);
        del_Contador++;
      }else if(del_Contador == 4){
        fscanf(antigo_Arq,"%i", &ex_Item.ano_Lanc);
        del_Contador++;
      }else if(del_Contador == 5){
        fscanf(antigo_Arq,"%f", &ex_Item.notas);      
        del_Contador++;
      }//Fim do if

      if(carac_Del == '\n'){
        //Condicional para verificar se o id do item é igual ao id informado pelo usuário. Se for igual, a variável ver_ID armazenará o valor 1, assim futuramente não entrando na estrutura condicional usada para verificar se o id não foi encontrado, logo após os dados do item serão mostrados para o usuário acompanhado de uma confirmação para o usuário decidir se quer mesmo apagar o item, a resposta (que terá seu valor guardado na variável opc_Del_Item) seguirá para uma estrutura de condicão do tipo switch() onde se for positiva, apagará o item, e se for negativa, gravará normalmente os dados e seguirá o programa//
        if(ex_Item.id == del_Item){
          ver_ID = 1;
          printf("\n\t==== Dados do Item ====\n\n");
          printf("ID: %i",ex_Item.id);
          printf("\n");
          printf("Título: %s\n",ex_Item.titulo);
          printf("Tipo: %s\n",ex_Item.tipo);
          printf("Data de Lançamento: %i\n",ex_Item.ano_Lanc);
          printf("Nota: %.1f\n",ex_Item.notas);
          printf("\n");
          printf("Deseja realmente deletar esse item:\n1. Sim\n2. Não\n");
          /****
            estrutura de repetição do tipo do while(), onde irá ficar em um loop enquanto o usuário não informar uma resposta válida para o programa, assim sempre no final verificando se o valor armazenado na variável opc_Del_Item é um valor valido (1 ou 2), se não, retornará o usuário até esse ponto para que o mesmo refaça a escolha, agora com uma mensagem de ERROR
          ****/
          do{
            printf("\nOpção: ");
            scanf("%i", &opc_Del_Item);
            setbuf(stdin, NULL);
            switch(opc_Del_Item){
              case 1:
              fprintf(novo_Arq,"@%s@%s@%d@%.1f\n", ex_Item.titulo, ex_Item.tipo, ex_Item.ano_Lanc, ex_Item.notas);
              printf("\n\tItem excluido com sucesso!\n");
              break;

              case 2:
              fprintf(novo_Arq,"%i@%s@%s@%d@%.1f\n", ex_Item.id, ex_Item.titulo, ex_Item.tipo, ex_Item.ano_Lanc, ex_Item.notas);
              break;

              default:
              printf("\nERROR: Informe uma opção válida!");
              break;
            }//Fim do switch
          }while((opc_Del_Item > 2) || (opc_Del_Item < 1));
        }else if(ex_Item.id == -1){
          fprintf(novo_Arq,"@%s@%s@%d@%.1f\n", ex_Item.titulo, ex_Item.tipo, ex_Item.ano_Lanc, ex_Item.notas);
        }else{
          fprintf(novo_Arq,"%i@%s@%s@%d@%.1f\n", ex_Item.id, ex_Item.titulo, ex_Item.tipo, ex_Item.ano_Lanc, ex_Item.notas);
        }//Fim do if
        ex_Item.id = -1;
        del_Contador = 1;
      }//Fim do if
    }//Fim do while
  }//Fim do if
  fclose(antigo_Arq);
  fclose(novo_Arq);

  remove("itens.dat"); //comando para apagar o arquivo ASCII antigo//
  rename("itens2.dat", "itens.dat"); //comando para renomear o novo arquivo ASCII para o nome correto dado nas especificações do projeto//
  
  //estrutura condicional para verificar se o programa encontrou o ID informado pelo usuário, se a variável ver_ID for igual a 0, significa que o ID não foi encontrado, porém se o ID foi achado dentro do arquivo ASCII, a variável ver_ID armazenará o valor 1, logo não entrando no bloco dessa condicional//
  if(ver_ID == 0){
    printf("\nO ID não foi encontrado!\n");
  }//Fim do if

  printf("\nPressione Enter para prosseguir...");
  getchar();
}