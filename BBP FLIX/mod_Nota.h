#include <stdio.h>
#include <stdlib.h>

FILE *ex_Nota; //Ponteiro do arquivo para excluir uma nota//
FILE *mod_Nota; //Ponteiro do arquivo para modificar uma nota//

//estrutura pra armazenar os dados lidos do arquivo ASCII//
struct mod_Notas{
  int id;
  char titulo[150];
  char tipo[13];
  int ano_Lanc;
  float notas;
};
/****
  Título: modificar_Nota();
  Data de Criação: 20/11/2021
  Ultima Modificação: 27/11/2021
  *
  Descrição: Função responsável por modificar a nota do item que o usuário especificou seu ID. Assim, através do ID informado pelo usuário, o programa buscará tal item com esse ID e mostrará seus dados ao usuário, que optará por mudar a nota ou não.
****/
void modificar_Nota(){
  
  struct mod_Notas nova_Nota;
  int mod_Item;//Variável para armazenar o ID que do item que tera sua nota modificada//
  int mod_Contador = 1; //Contador para controlar a leitura do arquivo no WHILE// 
  int ver_Mod_ID = 0; //Variável para verificar se o ID existe//
  int opc_Mod_Nota;//Variável para confirmar a mudança da nota//
  float new_Nota;//Variável para armazenar a nova nota//
  char carac_Mod_Nota;//Variável para verificar a continuação do arquivo//

  system("clear");
  printf("\t====== Modificar Nota ======\n\n");
  printf("Informe o ID do item que deseja modificar a nota: ");
  scanf("%i", &mod_Item);
  setbuf(stdin, NULL);

  ex_Nota = fopen("itens.dat", "r");
  mod_Nota = fopen("itens2.dat", "a");

  // Verificação da abertura dos arquivos//
  if((ex_Nota == NULL) || (mod_Nota == NULL)){
    printf("\nERROR: Houve um erro ao abrir o arquivo.");
  }else{
    rewind(ex_Nota);
    rewind(mod_Nota);   
    nova_Nota.id = -1; //caso o programa inicie com o primeiro item com seu id excluido, a listagem começara com o id = -1, fazendo com que o dados do primeiro item não apareça de inicio//
    
    /****
      Começo de uma estrutura de repetição do tipo while() que fará a leitura do arquivo pegando os dados e armazenando nas variaveis da estrutura do nova_Nota, assim a cada @ o contador aumenta passando para o próximo if com o bloco de comando para pegar dada informação do item 
    ****/
    while(fscanf(ex_Nota, "%c", &carac_Mod_Nota) != EOF){
      if(mod_Contador == 1){
        fseek(ex_Nota, ftell(ex_Nota)-1, SEEK_SET);
        fscanf(ex_Nota,"%i", &nova_Nota.id);
        mod_Contador++;
      }else if(mod_Contador == 2){
        fscanf(ex_Nota,"%[^'@']s",&nova_Nota.titulo);
        mod_Contador++;
      }else if(mod_Contador == 3){
        fscanf(ex_Nota, "%[^'@']s",&nova_Nota.tipo);
        mod_Contador++;
      }else if(mod_Contador == 4){
        fscanf(ex_Nota,"%i", &nova_Nota.ano_Lanc);
        mod_Contador++;
      }else if(mod_Contador == 5){
        fscanf(ex_Nota,"%f", &nova_Nota.notas);      
        mod_Contador++;
      }//Fim do while

      // Condição para verificar se chegou a um '\n'//
      if(carac_Mod_Nota == '\n'){
        if(nova_Nota.id == mod_Item){
          ver_Mod_ID = 1;
          printf("\n\t==== Dados do Item ====\n\n");
          printf("ID: %i",nova_Nota.id);
          printf("\n");
          printf("Título: %s\n",nova_Nota.titulo);
          printf("Tipo: %s\n",nova_Nota.tipo);
          printf("Data de Lançamento: %i\n",nova_Nota.ano_Lanc);
          printf("Nota: %.1f\n",nova_Nota.notas);
          printf("\n");
          printf("Deseja realmente modificar a nota desse item:\n1. Sim\n2. Não\n");
          do{
            printf("\nOpção: ");
            scanf("%i", &opc_Mod_Nota);
            setbuf(stdin, NULL);
            switch(opc_Mod_Nota){
              case 1:
              printf("\nInforme a nova nota do Item: ");
              scanf("%f", &new_Nota);
              setbuf(stdin, NULL);
              fprintf(mod_Nota,"%i@%s@%s@%d@%.1f\n", nova_Nota.id, nova_Nota.titulo, nova_Nota.tipo, nova_Nota.ano_Lanc, new_Nota);
              printf("\n\tNota alterada com sucesso!\n");
              break;
              case 2:
              fprintf(mod_Nota,"%i@%s@%s@%d@%.1f\n", nova_Nota.id, nova_Nota.titulo, nova_Nota.tipo, nova_Nota.ano_Lanc, nova_Nota.notas);
              break;
              default:
              printf("\nERROR: Informe uma opção válida!");
              break;
            }//Fim do switch
          }while((opc_Mod_Nota > 2) || (opc_Mod_Nota < 1));
        }else if(nova_Nota.id == -1){
          fprintf(mod_Nota,"@%s@%s@%d@%.1f\n", nova_Nota.titulo, nova_Nota.tipo, nova_Nota.ano_Lanc, nova_Nota.notas);
        }else{
          fprintf(mod_Nota,"%i@%s@%s@%d@%.1f\n", nova_Nota.id, nova_Nota.titulo, nova_Nota.tipo, nova_Nota.ano_Lanc, nova_Nota.notas);
        }//Fim do if
        nova_Nota.id = -1;
        mod_Contador = 1;
      }//Fim do if
    }//Fim do while
  }//Fim do if

  fclose(ex_Nota);
  fclose(mod_Nota);

  remove("itens.dat"); //comando para apagar o arquivo ASCII antigo//
  rename("itens2.dat", "itens.dat"); //comando para renomear o novo arquivo ASCII para o nome correto dado nas especificações do projeto//
  
  //estrutura condicional para verificar se o programa encontrou o ID informado pelo usuário, se a variável ver_MOD_ID for igual a 0, significa que o ID não foi encontrado, porém se o ID foi achado dentro do arquivo ASCII, a variável ver_ID armazenará o valor 1, logo não entrando no bloco dessa condicional//
  if(ver_Mod_ID == 0){
    printf("\nO ID não foi encontrado!\n\n");
  }//Fim do if

  printf("\n\tPressione Enter para prosseguir...");
  getchar();
}//Fim da Função modificar_Nota