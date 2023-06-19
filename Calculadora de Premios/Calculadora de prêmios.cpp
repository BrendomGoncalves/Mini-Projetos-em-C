//Universidade Estadual de Santa Cruz
//Alunos: Brendom Gonçalves e Bruno Felipe

//Calcula o premio de cada participante baseado no valor apostado por ele

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main(void) {
  
  setlocale(LC_ALL, "portuguese");
  
  // DECLARAÇÃO DE VARIÁVEIS
  int i, controle;
  int q_ganhadores;
  float v_premio, total_aposta, valor_base;
  
  // INICIO DO CÓDIGO
  do {
    printf("------ RESULTADO DA LOTERIA ------\n");
    
	// VALOR DO PRÊMIO
    printf("Valor do prêmio: R$ ");
    scanf("%f", &v_premio);
	
	// QUANTIDADE DE GANHADORES
	printf("Quantidade de ganhadores: ");
    scanf("%i", &q_ganhadores);
	
	// DECLARAÇÃO DE VARIÁVEIS A PARTIR DA QUANTIDADE
	char nome[q_ganhadores][20];
	float v_aposta[q_ganhadores], premio_part[q_ganhadores];
	
	// NOME DOS PARTICIPANTES
	system("cls");
	printf("----Ganhadores----\n");
    for (i=0;i<q_ganhadores;i++){
      printf("\nNome do participante: ");
      scanf("%s", &nome[i]);
      printf("Valor da aposta: R$ ");
      scanf("%f", &v_aposta[i]);
    }

	// CÁLCULO DO PRÊMIO DE CADA PARTICIPANTE
	for (i=0;i<q_ganhadores;i++){
		total_aposta += v_aposta[i];
	}
	
	valor_base = (v_premio / total_aposta);
	
	for (i=0;i<q_ganhadores;i++){
		premio_part[i] = (v_aposta[i] * valor_base);
	}
	
	// RESULTADO DO PRÊMIO DE CADA PARTICIPANTE
	if (q_ganhadores == 1){
		printf("\n\nO premio do participante é:\n\n");
	}else{
		printf("\n\nO premio dos participantes são:\n\n");
	}
	for (i=0;i<q_ganhadores;i++){
		printf("--%s ganhou R$%.2f.\n", nome[i], premio_part[i]);
	}

	// OPÇÃO DE SAÍDA
    pergunta : printf("\n\nDeseja verificar outro sorteio? / 1 (SIM) - 0 (NÃO)");
    scanf("%i", &controle);

    if ((controle != 1) && (controle != 0)){
      	printf("\n\nOpção inválida! Digite novamente.\n");
      	goto pergunta;
    }else if (controle == 1){
    	system("cls");
	}

  }while(controle == 1);

  printf("Programa finalizado...");

  return 0;
}
