#include <stdio.h>
#include <stdlib.h>

FILE *list_Itens; //Criação do ponteiro que irá apontar para o arquivo//

//estrutura com as variáveis que serão usadas pra armazenar os dados lidos do arquivo ASCII//
struct listar_Itens{
  int id;
  char titulo[150];
  char tipo[13];
  int ano_Lanc;
  float notas;
};

//Funções usadas na biblioteca list_Item.h além da função principal menu_List()//
void list_Todos();
void menu_List_Tipo();
void list_Tipo(char verificar_Tipo);

/****
  Título: menu_List();
  Data de Criação: 08/11/2021
  Ultima Modificação: 26/11/2021
  *
  Descrição: Essa função é responsável por mostrar as escolhas disponíveis de listagem ao usuário, assim armazenando sua escolha na variável opc_List do tipo inteiro e usando uma estrura condicional do tipo switch para chamar a respectiva função daquela escolha.
****/
void menu_List(){
  
  int opc_List; //variável responsável por guardar a escolha do usuário em reação ao tipo de listagem que ela deseja//

  /****
    Começo do menu da biblioteca de listagem, onde, usando uma estrutura de repetição do tipo do while(),o usuário só saíra quando ele informar a opção para isso, assim evitando a necessidade de ficar entrando toda hora no menu pra fazer alguma operação. Assim até que a variável opc_List tenha o valor 3 armazenado, o usuário permanecerá nesse menu.
  ****/
  do{
    system("clear");
    printf("\t====== Listar Item ======\n\n");
    printf("1. Listar todos os itens\n");
    printf("2. Listar por tipo\n");
    printf("3. Voltar para o menu\n");
    /****
      Ínicio de uma estrutura de repetição do tipo do while(), onde irá ocorrer a verificação do conteúdo da variável opc_List, que se houver um valor inválido (que esteja representado uma opção não presente no menu) irá retornar a esse ponto, dessa vez com uma mensagem de ERROR.
    ****/
    do{
      printf("\nOpção: ");
      scanf("%d",&opc_List);
      setbuf(stdin,NULL);

      switch(opc_List){
        case 1:
        list_Todos(); //chamando a função list_Todos(), que é a responsável por listar todos os itens cadastrados no arquivo ASCII// 
        break;
        case 2:
        menu_List_Tipo(); //chamando a função menu_List_Tipo(), que é responsável por apresentar o menu de tipos para o usuário quando desejar listar itens de um tipo específico//
        break;
        case 3:
        break;
        default:
        printf("\nERROR: Informe uma opção válida!");
        break;
      }//Fim do switch
    }while(opc_List < 1 || opc_List > 3);
  }while(opc_List != 3);
}//Fim da função menu_List

/****
  Título: list_Todos();
  Data de Criação: 08/11/2021
  Ultima Modificação: 26/11/2021
  *
  Descrição: Essa função é responsável por listar todos os itens cadastrados que estão presentes no arquivo ASCII,assim mostrando ao usuário os dados separadamente.
****/
void list_Todos(){

  struct listar_Itens enu_Itens; //estrutura para armazenar os dados dos itens obtidos através da leitura do arquivo ASCII//
  char carac_List_Todos; //variável para armazenar os caracteres do arquivo ASCII//
  int contador_Tudo = 1; //variável para controlar a leitura dos dados do arquivo ASCII//
  
  system("clear");
  printf("\t==== Itens Cadastrados ====\t\n\n");

  list_Itens = fopen("itens.dat","r");

  if(list_Itens == NULL){
    printf("\nERROR: Houve um erro ao abrir o arquivo.");
  }else{
    if(fscanf(list_Itens,"%c",&carac_List_Todos) == EOF){
      printf("\tNão existe item cadastrado!\n\n");
    }else{
      rewind(list_Itens);
      enu_Itens.id = -1; //caso o programa inicie com o primeiro item com seu id excluido, a listagem começara com o id = -1, fazendo com que o dados do primeiro item não apareça de inicio//
      
      /****
        Começo de uma estrutura de repetição do tipo while() que fará a leitura do arquivo pegando os dados e armazenando nas variaveis da estrutura do enu_Item, assim a cada @ o contador aumenta passando para o próximo if com o bloco de comando para pegar dada informação do item.
      ****/
      while(fscanf(list_Itens, "%c", &carac_List_Todos) != EOF){
        if(contador_Tudo == 1){
          fseek(list_Itens, ftell(list_Itens)-1, SEEK_SET);
          fscanf(list_Itens,"%i", &enu_Itens.id);
          contador_Tudo++;
        }else if(contador_Tudo == 2){
          fscanf(list_Itens,"%[^'@']s",&enu_Itens.titulo);
          contador_Tudo++;
        }else if(contador_Tudo == 3){
          fscanf(list_Itens, "%[^'@']s",&enu_Itens.tipo);
          contador_Tudo++;
        }else if(contador_Tudo == 4){
          fscanf(list_Itens,"%i", &enu_Itens.ano_Lanc);
          contador_Tudo++;
        }else if(contador_Tudo == 5){
          fscanf(list_Itens,"%f", &enu_Itens.notas);      
          contador_Tudo++;
        }//Fim do if

        //Condicional para imprimir os dados do item lido, quando a variável carac_List_Todos tiver como conteúdo '\n', logo após essa verificação, a variável enu_Itens.id recebe -1 para que se algum item esteja excluido (com seu id apagado), não ler na próxima leitura, além disso, o contador também volta para 1 para assim a leitura começar novamente do inicio da linha e pegar os dados na ordem certa//
        if(carac_List_Todos == '\n'){
          //Condicional para verificar se o id está acima de 0, e se for verídico, irá apresentar os dados do item, se não, irá passar para o próximo laço automaticamente//
          if(enu_Itens.id > 0){
            printf("ID: %i",enu_Itens.id);
            printf("\n");
            printf("Título: %s\n",enu_Itens.titulo);
            printf("Tipo: %s\n",enu_Itens.tipo);
            printf("Data de Lançamento: %i\n",enu_Itens.ano_Lanc);
            printf("Nota: %.1f\n",enu_Itens.notas);
            printf("\n");
          }//Fim do if
          enu_Itens.id = -1;
          contador_Tudo = 1;
        }//Fim do ig
      }//Fim do while
    }//Fim do if
  }//Fim do if

  fclose(list_Itens);
  printf("Pressione Enter para prosseguir...");
  getchar();
}

/****
  Título: menu_List_Tipo();
  Data de Criação: 08/11/2021
  Ultima Modificação: 27/11/2021
  *
  Descrição: Função responsável por apresentar um menu com as opções de tipo de itens para o usuário, que ao escolher um dos três tipos, através de uma estrutura de condicional switch(), chamará a função com a inicial do tipo escolhido como parâmetro.
****/
void menu_List_Tipo(){

  int opc_Menu_Tipo; //variável responsável por armazenar o inteiro correspondente ao tipo de item disponível//

  char inicial_Tipo; //variável usada para armazenar a primeira carac_List_Todos do tipo escolhido pelo usuário para ser usada como parâmetro na função que filtrará os tipos//

  /****
    Começo de uma estrutura de repetição do tipo do while() onde quando o usuário terminar de ver a listagem do tipo desejado anteriormente voltará a apresentar essa parte do código, assim só saindo daqui quando o usuário informar a opção correspondente a essa operação
  ****/
  do{
    system("clear");
    printf("\t==== Listar por tipo ====\n\n");
    printf("Escolha um tipo:\n1. Filme\n2. Série\n3. Documentário\n4. Voltar\n");

    /****
    Começo de uma estrutura de repetição do tipo do while() onde se houver uma ocorrencia na qual o usuário informe uma opção inválida, será o ponto de retorno do código, trazendo o usuário a esta etapa para informar o tipo desejado que deseja filtrar, mas dessa vez com uma mensagem de ERROR pedindo para que informe uma opção válida
    ****/  
    do{
      printf("\nOpcão: ");
      scanf("%i", &opc_Menu_Tipo);
      setbuf(stdin, NULL);

      switch(opc_Menu_Tipo){

        case 1:
        inicial_Tipo = 'F';
        system("clear");
        printf("Tipo: Filme\n\n");
        list_Tipo(inicial_Tipo);
        break;

        case 2:
        inicial_Tipo = 'S';
        system("clear");
        printf("Tipo: Série\n\n");
        list_Tipo(inicial_Tipo);
        break;

        case 3:
        inicial_Tipo = 'D';
        system("clear");
        printf("Tipo: Documentário\n\n");
        list_Tipo(inicial_Tipo);
        break;

        case 4:
        break;

        default:
        printf("\nERROR: Informe uma opção válida!");
        break;
      }//Fim do switch

    }while((opc_Menu_Tipo < 1) || (opc_Menu_Tipo > 4));
    
  }while(opc_Menu_Tipo != 4);
}//Fim da função menu_List_Tipo

/****
  Título: menu_List_Tipo();
  Data de Criação: 14/11/2021
  Ultima Modificação: 27/11/2021
  *
  Descrição: Função responsável por apresentar os itens do tipo escolhido pelo usuário na função menu_List_Tipo(), usando a variável inicial_Tipo (aqui com o nome de verificar_Tipo) como parâmetro.
  *
  Parâmetros: (char verificar_Tipo) [uma variável que é armazena a primeira carac_List_Todos do tipo escolhido pelo usuário, com a funcionalidade de comparar essa primeira carac_List_Todos com a primeira carac_List_Todos dos tipos dos itens registrados anteriormente, assim se for igual, os dados lidos serão mostrados na tela]
****/
void list_Tipo(char verificar_Tipo){

  struct listar_Itens arrolar_Tipo; //variável do tipo struct listar_Itens que armazenará os dados lidos no arquivo ASCII para apresentar ao usuário se o tipo do item for o desejado//
  char carac_List_Tipo; //variável utilizada para ler os carcteres do arquivo ASCII, para assim fazer as pausas e quebras necessárias dentro da estrutura de repetição do tipo while()//
  int contador_Tipo = 1; //contador utilizado para separar cada campo de obtenção de dados do item, para assim guardar nas variáveis corretas e mostrar ao usuário posteriormente//

  list_Itens = fopen("itens.dat", "r");

  if(list_Itens == NULL){
    printf("\nERROR: Houve um erro ao abrir o arquivo.");
  }else{
    rewind(list_Itens);
    arrolar_Tipo.id = -1;
    while(fscanf(list_Itens, "%c", &carac_List_Tipo) != EOF){
      if(contador_Tipo == 1){
        fseek(list_Itens, ftell(list_Itens)-1, SEEK_SET);
        fscanf(list_Itens,"%i", &arrolar_Tipo.id);
        contador_Tipo++;
      }else if(contador_Tipo == 2){
        fscanf(list_Itens,"%[^'@']s",&arrolar_Tipo.titulo);
        contador_Tipo++;
      }else if(contador_Tipo == 3){
        fscanf(list_Itens, "%[^'@']s",&arrolar_Tipo.tipo);
        contador_Tipo++;
      }else if(contador_Tipo == 4){
        fscanf(list_Itens,"%i", &arrolar_Tipo.ano_Lanc);
        contador_Tipo++;
      }else if(contador_Tipo == 5){
        fscanf(list_Itens,"%f", &arrolar_Tipo.notas);    
        contador_Tipo++;
      }//Fim do if

      if(carac_List_Tipo == '\n'){
        if(arrolar_Tipo.id > 0){
          /****
            Estrutura condicional do tipo if() usada para verificar se o valor guardado na variável verificar_Tipo (do tipo char, que obtemos como parâmetro que foi passado pela variável inicial_Tipo, da função menu_List_Tipo()) é igual ao primeiro valor da variável arrolar_Tipo.tipo, que guarda a string relacionada ao tipo do item, assim se for igual, mostrará os dados do item lido
          ****/
          if(arrolar_Tipo.tipo[0] == verificar_Tipo){
            printf("ID: %i",arrolar_Tipo.id);
            printf("\n");
            printf("Título: %s\n",arrolar_Tipo.titulo);
            printf("Tipo: %s\n",arrolar_Tipo.tipo);
            printf("Data de Lançamento: %i\n",arrolar_Tipo.ano_Lanc);
            printf("Nota: %.1f\n",arrolar_Tipo.notas);
            printf("\n");
          }//Fim do if
        }//Fim do if
        arrolar_Tipo.id = -1;
        contador_Tipo = 1;
      }//Fim do if
    }//Fim do while
  }//Fim do if

  fclose(list_Itens);
  printf("Pressione Enter para prosseguir...");
  getchar();
}