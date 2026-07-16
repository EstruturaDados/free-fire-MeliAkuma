#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int ExibirMenu(int Itens); //Exibe o menu no terminal
void LimparBufferEntrada(); //Limpar Buffer de entrada
#define MaxItens 10 //Número máximo de itens na mochila

typedef struct{ //Dados da mochila
    char nome[30];
    char tipo[20];
    int quantidade;
}DMochila; //Dados Da mochila

void ExibirItens(DMochila *Mochila, int Titens); //Exibe a lista de Itens da mochila no terminal
void AdicionarItem(int *Titens, DMochila *Mochila); //Adiciona um item a mochila
void RemoverItem(DMochila *Mochila, int *Titens); //Remove um item da mochila


int main() {
    int TItens = 0; //Total de itens na mochila
    int Sair = 0; //Variavel de controle
    DMochila Mochila[MaxItens]; //Definir tamanho da struct

    do{
        switch(ExibirMenu(TItens)){
            case 1:
                AdicionarItem(&TItens, Mochila);
                break;
            case 2: 
                ExibirItens(Mochila, TItens);
                RemoverItem(Mochila, &TItens);
                break;
            case 3:
                ExibirItens(Mochila, TItens);
                if(TItens > 0){printf("Pressione Enter para voltar..."); LimparBufferEntrada(); getchar();};
                break;
            case 0: 
                printf("\n0Saindo...");
                Sair = 1;
                break;
            default:
                printf("\nOpção invalida pressione Enter e escolha novamente... ");
                LimparBufferEntrada();
                getchar();
                break;
        }
    }while (Sair == 0);  

    return 0;
}

void ExibirItens(DMochila *Mochila, int Titens){
        if(Titens <= 0){printf("Não tem Itens na mochila pressione enter para voltar... "); LimparBufferEntrada(); getchar(); return;};
        printf("===============================================\n");
        printf("              -Itens da Mochila-               \n");
        printf("===============================================\n");      
    for(int n = 0; Titens > n; n++){       
        printf("-----------------------------------------------\n");
        printf("|Nome: %s |Tipo: %s |Quantidade: %d \n", Mochila[n].nome, Mochila[n].tipo, Mochila[n].quantidade);
    }
        printf("-----------------------------------------------\n");
}

void AdicionarItem(int *Titens, DMochila *Mochila){
    if(*Titens >= 10){printf("Quantidade Maxima da mochila foi atiginda..."); LimparBufferEntrada(); getchar(); return;};
    char nome[30];
    char tipo[20];
    int quantidade;

    printf("\n\n-----------------------\n");
    printf("Adicionando item...\n");
    printf("-------------------------\n");
    printf("Digite o nome do item: ");
    scanf("%s", nome);
    strcpy(Mochila[*Titens].nome, nome);

    printf("Digite o tipo do item (Cura, Arma...): ");
    scanf("%s", tipo);
    strcpy(Mochila[*Titens].tipo,tipo);

    printf("Quantos foram encontrados? : ");
    scanf("%d", &quantidade);
    Mochila[*Titens].quantidade = quantidade;

    (*Titens)++;
    printf("\nItem adicionado com sucesso pressione Enter para sair...");
    LimparBufferEntrada();
    getchar();
}

void RemoverItem(DMochila *Mochila, int *Titens){
    if(*Titens >= 1){
        char nome[30];
        int quantidade;
        int pos = -1;
        printf("Qual item deseja remover? : ");
        scanf("%s",nome);
        for(int n = 0; n < *Titens; n++){
            if(strcmp(nome,Mochila[n].nome) == 0){
                pos = n;
            }
        };
        if(pos == -1){
            printf("Item não existe, pressione Enter para voltar...");
            LimparBufferEntrada();
            getchar();
            return;
        };
        if(Mochila[pos].quantidade > 1){
            printf("Qual a quantidade a remover? : ");
            scanf("%d",&quantidade);
        };
        if(Mochila[pos].quantidade <= 1 || quantidade == Mochila[pos].quantidade){
            for(int n = pos; n < *Titens; n++)
            {
                if(*Titens > 1){
                 Mochila[n] = Mochila[n+1];
                };
            };
            (*Titens)--;
            printf("Item removido com sucesso! Pressione Enter para voltar...");
            LimparBufferEntrada();
            getchar();
        }else{
            if(quantidade > Mochila[pos].quantidade){printf("Quantidade Superior ao total, pressione Enter parar voltar..."); LimparBufferEntrada(); getchar(); return;}
            Mochila[pos].quantidade - quantidade;
            printf("Unidade do item removida com sucesso, pressione Enter para voltar...");
            LimparBufferEntrada();
            getchar();
        };
       
    };    
}



//----------------------------------------------------------------------//

int ExibirMenu(int Itens){
    int opcao = 5;
    printf("==============================\n");
    printf("Mochila do jogador: %d/%d Itens\n",Itens,MaxItens);
    printf("==============================\n");

    printf(" 01: Adicionar Item.\n 02: Remover Item. \n 03: Listar Itens.\n 00: Sair.\n---------------------- \n Opção: ");
    
    scanf("%d",&opcao);
    return opcao;

}

void LimparBufferEntrada() {
     int c;
    while((c = getchar()) != '\n' && c != EOF);

};