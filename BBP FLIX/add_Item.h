#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

FILE *adic_Item; // Ponteiro que apontará para o arquivo

/****
  Estrutura utilizada para conseguir identificar o ano atual (usando o mesmo site da função buscar_Item() como referência)
****/
struct tm *data_hora_atual;

/****
  Estrutura com as variáveis que irão guardar as informações do item que será armazenado no arquivo ASCII
****/
struct inserir_Item {
  int id;
  char *titulo;
  char tipo[3][13];
  int ano_Lanc;
  float nota;
};

//Funções usadas na biblioteca add_Item.h além da função principal adicionar_Item()//
int qtd_Linhas();
int buscar_Ano(int ano);

/****
  Título: adicionar_Item();
  Data de Criação: 06/11/2021
  Ultima Modificação: 26/11/2021
  *
  Descrição: Essa função é responsavel por adquirir e inserir as informações do item no arquivo ASCII. Por meio de uma variável do tipo struct inserir_Item, os dados informados pelo usuário serão guardados nas variáveis da estrutura e logo após finalizar o processo de obtenção de informações, virá uma mensagem pedindo para o usuário confirmar se os dados estão corretos e se deseja salvar o item.
****/
void adicionar_Item(){
  
  int ano_Atual = buscar_Ano(ano_Atual); //Variável utilizada para armazenar o valor retornado pela função buscar_Ano que será o ano atual, para assim fazer a comparação na parte de informar o ano do item//
  int controle_Menu_Tipo; //Criando variável para controlar o do-while do menu de alocação dinâmica dos tipos dos itens do catálogo.//
  int opc_Confirm_Dados; //Variável para armazenar a opção escolhida pelo usuário a respeito da confirmação dos dados informados//
  int opc_Novo_Cad;//Variável para armazenar a opção escolhida pelo usuário a respeito da continuação e cadastro de um novo item//
  int ver_arro;//Variavel de controle usada para ver se o título tem @//
  char *novo_Item_Tipo; //Variável para armazenar o tipo do item no menu de tipos//

  struct inserir_Item novo_Item; //Criando uma variável do tipo struct inserir_Item de nome novo_Item, para guardar os dados fornecidos pelo usuário//

  //Os três strcpy a seguir tem como finalidade armazenar em uma "lista" os três tipos de itens que são permitidos no programa, assim se utilizando de uma matriz, eles serão guardados na ordem apresentada respectivamente//
  strcpy(novo_Item.tipo[0], "Filme");
  strcpy(novo_Item.tipo[1], "Serie");
  strcpy(novo_Item.tipo[2], "Documentario");

  /****
    Começo de uma estrutura de repetição do tipo do while() onde vai servir como ponto de retorno para quando o usuário querer cadastrar outro item ao final do processo de cadastramento de um item atual,assim tendo como parâmetro a variável opc_Novo_Cad, se for uma resposta positiva, o usuário voltará a esse ponto, podendo começar o cadastro de um novo item.
  ****/
  do{

    novo_Item.id = qtd_Linhas(); //Chamando a função qtd_Linhas() que irá retornar o ID para o novo item cadastrado//
    
    /****
      Começo de uma estrutura de repetição do tipo do while() englobando todo o processo de obtenção das informações do item, para que no final, ao aparecer a mensagem perguntando se os dados estão corretos, (levando a variável opc_Confirm_Dados como parâmetro) com a resposta negativa, voltará a esse ponto do código para que assim o usuário informe os dados corretamente.
    ****/
    do{
      system("clear");
      printf("\t====== Inserir Item ======\n");
      
      do{
        ver_arro = 0;
        printf("\nInforme o título do item: ");
        novo_Item.titulo = (char *) calloc(150, sizeof(char)); // Utiliza alocação dinâmica para reservar 150 espaços (tamanho um pouco maior que o necessário para armazenar o maior título de filme já criado) para armazenar o título do filme//
        fgets(novo_Item.titulo, 150, stdin); //Obtem o título do filme e armazena na variável novo_Item.título//
        novo_Item.titulo = (char *) realloc(novo_Item.titulo, strlen(novo_Item.titulo) * sizeof(char)); //Realoca o armazenamento da variável novo_Item.titulo para se adaptar ao título dado pelo usuário, e assim liberar o espaço não utilizado//
        for(int i = 0; i < strlen(novo_Item.titulo); i++){
          if(novo_Item.titulo[i] == '@'){
            printf("\nERROR: Informe um titulo sem @!");
            ver_arro = 1;
            break;
          }//Final do if
        }//Final do for
      }while(ver_arro == 1);
      novo_Item.titulo[strcspn(novo_Item.titulo, "\n")] = 0; //Retira a quebra de linha do título se usando da função strcspn//
      setbuf(stdin, NULL); //Comando para limpar o lixo do teclado//

      printf("\nInforme o tipo do item: \n1. Filme\n2. Série\n3. Documentário\n\n");
      
      /****
        Inicio de uma estrutura de repetição do tipo Do-While onde ira alocar dinamicamente os espaços do tipo (Filme, Serie, Documentario) de cada item inserido no catálogo.
      ****/
      do{
        printf("Opção: ");
        scanf("%i", &controle_Menu_Tipo);
        setbuf(stdin, NULL);

        switch(controle_Menu_Tipo){
          case 1: novo_Item_Tipo = (char *) calloc(strlen(novo_Item.tipo[0]), sizeof(char));
                  novo_Item_Tipo = novo_Item.tipo[0];
                  break;
          case 2: novo_Item_Tipo = (char *) calloc(strlen(novo_Item.tipo[1]), sizeof(char));
                  novo_Item_Tipo = novo_Item.tipo[1];
                  break;
          case 3: novo_Item_Tipo = (char *) calloc(strlen(novo_Item.tipo[2]), sizeof(char));
                  novo_Item_Tipo = novo_Item.tipo[2];
                  break;
          default:printf("\nERROR: Opção inválida! Digite novamente.\n");
                  break;
        }//Fim do switch
      }while((controle_Menu_Tipo < 1) || (controle_Menu_Tipo > 3));

      /****
        Início de uma estrutura de repetição do tipo do while() onde ira verificar se o usuário informou um ano válido. Se a variável novo_Item.ano_Lanc tiver armazenado com um ano que seja antes de 1888 (ano do filme mais antigo registrado) ou maior que o ano atual (que está armazenado na variável ano_Atual), ira retornar para a parte de informar o ano, dessa vez com uma mensagem de ERROR.
      ****/
      do{
        printf("\nInforme o ano de lançamento do item: ");
        scanf("%i", &novo_Item.ano_Lanc);
        setbuf(stdin, NULL);

        if((novo_Item.ano_Lanc < 1888) || (novo_Item.ano_Lanc > ano_Atual)){
          printf("\nERROR: Digite um ano válido!");
        }//Fim do if
      }while((novo_Item.ano_Lanc < 1888) || (novo_Item.ano_Lanc > ano_Atual));

      /****
        Início de uma estrutura de repetição do tipo do while() onde ira verificar se o usuário informou uma nota válida. Se a variável novo_Item.nota tiver armazenado com uma nota menor que 1 ou maior que 5, ira retornar para a parte de informar a nota, dessa vez com uma mensagem de ERROR.
      ****/
      do{
        printf("\nInforme uma nota para o item: ");
        scanf("%f",&novo_Item.nota);
        setbuf(stdin, NULL);

        if((novo_Item.nota < 1) || (novo_Item.nota > 5)){
          printf("ERROR: Digite uma nota válida (1,0-5,0)\n");
        }//Fim do if
      }while((novo_Item.nota < 1) || (novo_Item.nota > 5));

      system("clear"); //ao terminar a parte de obter os dados, a tela será limpa e irá para a parte de confirmação de salvamento

      //os printf a seguir serão usados para mostrar as usuários as informações informadas por ele, para que o mesmo verifique se estão corretos, para assim prosseguir para a parte de salvamento//
      printf("\t---Dados Informados---\t\n\n");
      printf("Titulo do Item: %s\n", novo_Item.titulo);
      printf("Tipo do Item: %s\n", novo_Item_Tipo);
      printf("Ano de lançamento do Item: %i\n", novo_Item.ano_Lanc);
      printf("Nota do Item: %.1f\n", novo_Item.nota);

      /****
      Inicio de uma estrutura de repetição do tipo do while() onde ocorrerá uma verificação se o usuário informou uma opção válida, assim depois do usuário informar se deseja salvar os dados do item, se ele informou uma opção não válida, ela voltará para a parte de informar se deseja salvar novamente, dessa vez com uma mensagem de ERROR
      ****/
      do{
        printf("\nDeseja salvar o item (verifique se as informações estão corretas):\n1. Sim\n2. Não\n");      
        printf("\nOpção: ");
        scanf("%i", &opc_Confirm_Dados);
        setbuf(stdin, NULL);
        if((opc_Confirm_Dados != 1) && (opc_Confirm_Dados != 2)){
        printf("\nERROR: Digite uma opção válida!");
          //esse if verificará se a opção escolhida foi igual a 1, só assim irá abrir o arquivo e salvará os dados informados, o fechando no final e emitindo uma mensagem de confirmação se os dados foram salvos, caso contrário, se o arquivo não abrir, mostrará uma mensagem de ERROR para o usuário//
        }else if(opc_Confirm_Dados == 1){
          adic_Item = fopen("itens.dat", "a"); //abertura do arquivo em que será armazenado os dados do item//
        if (adic_Item == NULL) { //verificação se o arquivo conseguiu abrir ou não//
            printf ("\nERROR: Houve um erro ao abrir o arquivo.");
          }else{
            fprintf(adic_Item, "%i@%s@%s@%d@%.1f\n", novo_Item.id, novo_Item.titulo, novo_Item_Tipo, novo_Item.ano_Lanc,novo_Item.nota); //comando para gravar no arquivo os dados formatados do jeito que foi indicado no projeto//
            printf("\nDados salvos com sucesso!\n\nPressione Enter para continuar...");
            getchar(); //comando para dar uma pausa no programa e não pular diretamente para o menu principal//
          }//Fim do if
          fclose(adic_Item); //fechamento do arquivo que foi utilizado para gravar os dados//
        }// Fim do else-if
      }while((opc_Confirm_Dados != 1) && (opc_Confirm_Dados != 2));

    }while(opc_Confirm_Dados == 2);
    system("clear");
    printf("\nDeseja cadastrar um novo item:\n1. Sim\n2. Não\n");
    /****
      Inicio de uma estrutura de repetição do tipo do while() onde ocorrerá uma verificação se o usuário informou uma opção válida, assim depois do usuário informar se deseja salvar dados de um novo item, se ele informou uma opção não válida, ela voltará para a parte de informar se deseja salvar, dessa vez com uma mensagem de ERROR
    ****/
    do{
      printf("\nOpção: ");
      scanf("%i", &opc_Novo_Cad);
      setbuf(stdin, NULL);
      if((opc_Novo_Cad != 1) && (opc_Novo_Cad != 2)){
        printf ("\nERROR: Escolha uma opção válida.");
      }//Fim do if
    }while((opc_Novo_Cad != 1) && (opc_Novo_Cad != 2));
  }while(opc_Novo_Cad == 1);
}//Fim da função adicionar_Item

/****
  Título: qtd_Linhas();
  Data de Criação: 06/11/2021
  Ultima Modificação: 25/11/2021
  *
  Descrição: Essa função será responsável por ler a quantidade de linhas do arquivo ASCII, para assim usar essa quantidade como base para o ID do item. Ela foi inspirada na função apresentada pelo usuário "leofontes" no site: || https://pt.stackoverflow.com/questions/167966/contar-as-linhas-de-um-arquivo-txt-em-c-c ||
  *
  Valor de retorno: Essa função retorna um valor inteiro que representa o número da ultima linha lida do arquivo, assim atribuindo esse valor a variável que armazena o ID do item na função adicionar_Item();
****/
int qtd_Linhas(){

  int linhas = 1; //Variável que guardará a quantidade de linhas presentes no arquivo, começa em 1 por que sempre existirá pelo menos uma linha no arquivo//
  char carac; //Variável que guardará os caracteres um por um para fazer comparação com a quebra de linha (\n)//

  adic_Item = fopen("itens.dat", "r"); //comando para abrir o arquivo em modo de leitura//
  
  if(adic_Item == NULL){
    printf("\nERROR: Houve um erro ao abrir o arquivo.");
  }else{
    /****
      Começo de uma estrutura de repetição do tipo while() que ira ter como parametro os dados guardados ma variável do tipo char com nome carac, para a cada repetição fazer uma comparação (utilizando a estrutura condicional do tipo if) com '\n', que é uma quebra de linha. Se for igual ira ser contabilizado mais 1 na quantidade guardada na variável inteira de nome linhas. A repetição ocorrerá até a variável carac for igual ao EOF (End Of File).
    ***/
    while(fscanf(adic_Item, "%c", &carac) != EOF){
      if(carac == '\n'){
        linhas++;
      }//Fim do if
    }//Fim do while
  }//Fim do if

  fclose(adic_Item); //comando para fechar o arquivo informado antes//
  return linhas;
}//Fim da função qtd_Linhas

/****
  Título: buscar_Ano();
  Data de Criação: 06/11/2021
  Ultima Modificação: 25/11/2021
  *
  Descrição: Função responsável por retornar o ano atual que será armazenada na variável ano_Atual, para assim fazer a verificação do ano de lançamento do item. Função inspirada pelo código apresentado no site: || http://linguagemc.com.br/exibindo-data-e-hora-com-time-h/ ||
  *
  Parâmetros: (int ano) [variável inteira usada para armazenar o ano atual]
  *
  Valor de Retorno: Retorna um valor inteiro que é o ano atual, que será armazenado na variável ano_Atual da função adicionar_Item()
****/ 
int buscar_Ano(int ano){

  time_t segundos;
  time(&segundos);
  data_hora_atual = localtime(&segundos);

  ano = data_hora_atual->tm_year + 1900;

  return ano;
}//Fim da função buscar_Ano