#include <stdio.h>
#include <stdlib.h>

FILE *rastrear_Item; 

//estrutura pra armazenar os dados lidos do arquivo ASCII//
struct busc_Item{
  int id;
  char titulo[150];
  char tipo[13];
  int ano_Lanc;
  float notas;
};

//Funções usadas nessa biblioteca além da principal//
void busc_ID();
void busc_Titulo();

/****
  Título: menu_Busc_Item();
  Data de Criação: 22/11/2021
  Ultima Modificação: 27/11/2021
  *
  Descrição: Função que mostra ao usuário um menu com as opções de busca disponíveis, assim armazenando o valor da escolha numa variável inteira de nome opc_Menu_Busc, e através de uma estrutura condicional do tipo switch(), chamar a função correspondente. 
****/
void menu_Busc_Item(){

  int opc_Menu_Busc;

  do{
    system("clear");
    printf("\t====== Menu de Busca ======\n\n");
    printf("Escolha uma das opções a seguir:\n1. Buscar Item por ID\n2. Buscar por Título\n3. Voltar\n");
    do{
      printf("\nEscolha: ");
      scanf("%i", &opc_Menu_Busc);

      switch(opc_Menu_Busc){

        case 1:
        busc_ID();
        break;

        case 2:
        busc_Titulo();
        break;

        case 3:
        break;

        default:
        printf("\nERROR: Digite uma opção válida!");
        break;
      }//Fim do switch
    }while((opc_Menu_Busc < 1) || (opc_Menu_Busc > 3));   
  }while(opc_Menu_Busc != 3);
}//Fim da função menu_Busc_Item

/****
  Título: busc_ID();
  Data de Criação: 22/11/2021
  Ultima Modificação: 01/12/2021
  *
  Descrição: Função usada para procurar mostrar ao usuário o item correspondente ao id informado pelo mesmo. Ao informar o id, que será armazenado na variável busca_ID, ira começar um loop pelo arquivo onde sera lido as informações linha por linha e armazenalas nas variaveis da struct previamente criada, assim, ao chegar ao \n, será feito uma decisão para saber se as informações serão ou não mostradas.
****/
void busc_ID(){

  struct busc_Item busc_ID_Item;//Declaração da struct de busca pelo id//
  int busca_ID;//Responsável por ler o id informado pelo usuário//
  int busc_ID_Count = 1;//Contador responsável por fazer uma busca de todos os dados do arquivo//
  char carac_Busc_ID;//Declarado para armazenar os dados de uma leitura do arquivo//

  //Área onde o usuário digitará o ID do item que ele deseja mudar//
  system("clear");
  printf("\t====== Menu de Busca ======\n\n");
  printf("Informe o ID do arquivo: ");
  scanf("%i", &busca_ID);
  setbuf(stdin, NULL);

  //Abertura do arquivo
  rastrear_Item = fopen("itens.dat", "r");
  if(rastrear_Item == NULL){
    printf ("\nERROR: Houve um erro ao abrir o arquivo.");
  }else{
    rewind(rastrear_Item);   
    busc_ID_Item.id = -1;//caso o programa inicie com o primeiro item com seu id excluido, a listagem começará com o id = -1, fazendo com que o dados do primeiro item não apareça de inicio//

    /****
      Começo de uma estrutura de repetição do tipo while() que fará a leitura do arquivo pegando os dados e armazenando nas variaveis da estrutura do busc_ID_Item,assim a cada @ o contador aumenta passando para o próximo if com o bloco de comando para pegar dada informação do item 
    ****/
    while(fscanf(rastrear_Item, "%c", &carac_Busc_ID) != EOF){
      if(busc_ID_Count == 1){
        fseek(rastrear_Item, ftell(rastrear_Item)-1, SEEK_SET);
        fscanf(rastrear_Item,"%i", &busc_ID_Item.id);
        busc_ID_Count++;
      }//Fim do if
      //if usado para comparar se o ID da estrutura é igual ao ID informado pelo usuário, seguindo as próximas contagens//
      if(busc_ID_Item.id == busca_ID){
        if(busc_ID_Count == 2){
          fseek(rastrear_Item, ftell(rastrear_Item)+1, SEEK_SET);
          fscanf(rastrear_Item,"%[^'@']s",&busc_ID_Item.titulo);
          busc_ID_Count++;
        }else if(busc_ID_Count == 3){
          fscanf(rastrear_Item, "%[^'@']s",&busc_ID_Item.tipo);
          busc_ID_Count++;
        }else if(busc_ID_Count == 4){
          fscanf(rastrear_Item,"%i", &busc_ID_Item.ano_Lanc);
          busc_ID_Count++;
        }else if(busc_ID_Count == 5){
          fscanf(rastrear_Item,"%f", &busc_ID_Item.notas); 
          busc_ID_Count++;
        }//Fim do if
      }//Fim do if

      if(carac_Busc_ID == '\n'){
        if(busc_ID_Item.id == busca_ID){
          printf("\n\t==== Dados do Item ====\n\n");
          printf("ID: %i",busc_ID_Item.id);
          printf("\n");
          printf("Título: %s\n",busc_ID_Item.titulo);
          printf("Tipo: %s\n",busc_ID_Item.tipo);
          printf("Data de Lançamento: %i\n",busc_ID_Item.ano_Lanc);
          printf("Nota: %.1f\n",busc_ID_Item.notas);
          printf("\n");   
          break;         
        }
        busc_ID_Item.id = -1;
        busc_ID_Count = 1;
      }//Fim do if
    }//Fim do while
  }//Fim do else

  //Fecha o arquivo
  fclose(rastrear_Item);

  printf("\nPressione Enter para prosseguir...");
  getchar();
}

/****
  Título: busc_Titulo();
  Data de Criação: 22/11/2021
  Ultima Modificação: 01/12/2021
  *
  Descrição: Função responsável por buscar itens pelo título ou parte dele fornecido pelo o usúario, se caso o titulo existir no arquivo aparecerá todos os dados do item, caso contrário será exibida uma mensagem descrevendo que não há nenhum item com aquele titulo informado.
****/
void busc_Titulo(){
  
  struct busc_Item busc_Titulo_Item;//Declaração da struct de busca pelo título//
  char titulo_Buscar[150];//Responsável por ler o titulo ou parte dele informado pelo usuário//
  int busc_Titulo_Count = 1;//Contador que faz uma busca por todos os dados do item//
  char carac_Busc_Titulo;//Declarado para armazenar os dados de uma leitura do arquivo//

  //Leitura do titulo informado pelo usuário
  system("clear");
  printf("\t====== Menu de Busca ======\n\n");
  printf("Informe o titulo do item que deseja buscar: ");
  setbuf(stdin, NULL);
  fgets(titulo_Buscar, 150, stdin);
  setbuf(stdin, NULL);

  //Abertura do arquivo itens.dat
  rastrear_Item = fopen("itens.dat", "r");
  if(rastrear_Item == NULL){
    printf ("\nERROR: Houve um erro ao abrir o arquivo.");
  }else{
    rewind(rastrear_Item);
    busc_Titulo_Item.id = -1;//caso o programa inicie com o primeiro item com seu id excluido, a listagem começara com o id = -1, fazendo com que o dados do primeiro item não apareça de inicio//
    
    /****
      Começo de uma estrutura de repetição do tipo while() que fará a leitura do arquivo pegando os dados e armazenando nas variaveis da estrutura do busc_Titulo_Item, assim a cada @ o contador aumenta passando para o próximo if com o bloco de comando para pegar dada informação do item 
    ****/
    while(fscanf(rastrear_Item, "%c", &carac_Busc_Titulo) != EOF){
      if(busc_Titulo_Count == 1){
        fseek(rastrear_Item, ftell(rastrear_Item)-1, SEEK_SET);
        fscanf(rastrear_Item,"%i", &busc_Titulo_Item.id);
        busc_Titulo_Count++;
      }else if(busc_Titulo_Count == 2){
        fscanf(rastrear_Item,"%[^'@']s",&busc_Titulo_Item.titulo);
        busc_Titulo_Count++;
      }//Fim do if
      //if usado para comparar o título informado pelo usuário e o título do arquivo//
      if((strncmp(busc_Titulo_Item.titulo, titulo_Buscar, strlen(titulo_Buscar) - 1) == 0) && (busc_Titulo_Item.id > 0)){
        if(busc_Titulo_Count == 3){
          fseek(rastrear_Item, ftell(rastrear_Item)+1, SEEK_SET);
          fscanf(rastrear_Item, "%[^'@']s",&busc_Titulo_Item.tipo);
          busc_Titulo_Count++;
        }else if(busc_Titulo_Count == 4){
          fscanf(rastrear_Item,"%i", &busc_Titulo_Item.ano_Lanc);
          busc_Titulo_Count++;
        }else if(busc_Titulo_Count == 5){
          fscanf(rastrear_Item,"%f", &busc_Titulo_Item.notas);      
          busc_Titulo_Count++;
        }//Fim do if
      }//Fim do if

      //if usado para buscar um determinado título até achar um um espaço para outro título//
      if(carac_Busc_Titulo == '\n'){
        if((strncmp(busc_Titulo_Item.titulo, titulo_Buscar, strlen(titulo_Buscar) - 1) == 0) && (busc_Titulo_Item.id > 0)){
          printf("\n\t==== Dados do Item ====\n\n");
          printf("ID: %i",busc_Titulo_Item.id);
          printf("\n");
          printf("Título: %s\n",busc_Titulo_Item.titulo);
          printf("Tipo: %s\n",busc_Titulo_Item.tipo);
          printf("Data de Lançamento: %i\n",busc_Titulo_Item.ano_Lanc);
          printf("Nota: %.1f\n",busc_Titulo_Item.notas);
          printf("\n");      
          break;    
        }//Fim do if
        busc_Titulo_Item.id = -1;
        busc_Titulo_Count = 1;
      }//Fim do if
    }//Fim do while
  }
  fclose(rastrear_Item);//Fecha o arquivo

  printf("\nPressione Enter para prosseguir...");
  getchar();
}//Fim da função busc_Titulo