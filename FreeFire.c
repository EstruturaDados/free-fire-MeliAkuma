#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int ExibirMenu(int Itens); //Exibe o menu no terminal
void LimparBufferEntrada(); //Limpar Buffer de entrada
void PegarTexto(char *texto);//Usa o fget pra pegar o texto e retorna a strig
#define MaxItens 20 //Número máximo de itens na mochila

typedef struct{ //Dados da mochila
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
}DMochila; //Dados Da mochila

void ExibirItens(DMochila *Mochila, int Titens); //Exibe a lista de Itens da mochila no terminal
void AdicionarItem(int *Titens, DMochila *Mochila, int *Organizado); //Adiciona um item a mochila
void RemoverItem(DMochila *Mochila, int *Titens); //Remove um item da mochila
void ListarItemPorNome(DMochila *Mochila, int Titens,int Organizado);
void SelectionSortPrioridade(DMochila *Mochila, int Titens, int *Organizado);
void InsertionSortTipo(DMochila *Mochila, int Titens, int *Organizado);
void BubleSortNome(DMochila *Mochila, int Titens, int *Organizado);



int main() {
    int TItens = 0; //Total de itens na mochila
    int Sair = 0; //Variavel de controle
    int Organizado = 0;
    DMochila Mochila[MaxItens]; //Definir tamanho da struct

    do{
        switch(ExibirMenu(TItens)){
            case 1:
                AdicionarItem(&TItens, Mochila, &Organizado);
                break;
            case 2: 
                ExibirItens(Mochila, TItens);
                RemoverItem(Mochila, &TItens);
                break;
            case 3:
                ExibirItens(Mochila, TItens);
                if(TItens > 0){printf("Pressione Enter para voltar..."); getchar();};
                break;
            case 4: 
                int opcao;
                ExibirItens(Mochila, TItens);
                if(TItens < 1){break;};
                printf("Dejesa ordenar por nome(1), Tipo(2) ou Prioridade(3): ");
                scanf("%d",&opcao);
                switch(opcao){
                    case 1:
                        BubleSortNome(Mochila, TItens, &Organizado);
                        break;
                    case 2:
                        InsertionSortTipo(Mochila, TItens, &Organizado);                     
                        break;
                    case 3:
                        SelectionSortPrioridade(Mochila, TItens, &Organizado);
                        break;
                }
                ExibirItens(Mochila, TItens);
                if(TItens > 0){printf("Pressione Enter para voltar..."); LimparBufferEntrada(); getchar();};
                break;
            case 5:
                ListarItemPorNome(Mochila,TItens,Organizado);
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
        if(Titens <= 0){printf("Não tem Itens na mochila pressione enter para voltar... "); getchar(); return;};
        printf("===============================================\n");
        printf("              -Itens da Mochila-               \n");
        printf("===============================================\n");      
    for(int n = 0; Titens > n; n++){       
        printf("-----------------------------------------------\n");
        printf("|Nome: %s |Tipo: %s |Quantidade: %d |Prioridade: %d \n", Mochila[n].nome, Mochila[n].tipo, Mochila[n].quantidade, Mochila[n].prioridade);
    }
        printf("-----------------------------------------------\n");
}

void AdicionarItem(int *Titens, DMochila *Mochila, int *Organizado){
    if(*Titens >= 10){printf("Quantidade Maxima da mochila foi atiginda..."); LimparBufferEntrada(); getchar(); return;};
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;

    printf("\n\n-----------------------\n");
    printf("Adicionando item...\n");
    printf("-------------------------\n");
    printf("Digite o nome do item: ");
    PegarTexto(nome);
    strcpy(Mochila[*Titens].nome, nome);

    printf("Digite o tipo do item (Cura, Arma...): ");
    PegarTexto(tipo);
    strcpy(Mochila[*Titens].tipo,tipo);

    printf("Quantos foram encontrados? : ");
    scanf("%d", &quantidade);
    LimparBufferEntrada();
    Mochila[*Titens].quantidade = quantidade;

    printf("Qual a prioridade(1-5)? : ");
    scanf("%d", &prioridade);
    Mochila[*Titens].prioridade = prioridade;

    (*Titens)++;
    (*Organizado) = 0;
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
        PegarTexto(nome);
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
void BubleSortNome(DMochila *Mochila, int Titens, int *Organizado){
    DMochila temp;
    for (int n = 0; n < Titens-1; n++) //Percorre todos os itens da lista 1 por 1
    {
        for(int n2 = 0; n2 < Titens- 1 - n; n2++ ){ //Percorre toda lista a cada item comparando os vizinhos.
            if(strcmp(Mochila[n2].nome,Mochila[n2 + 1].nome) > 0){ //Compara os vizinhos para ver se n2 é maior q n2 + 1
                temp = Mochila[n2];
                Mochila[n2] = Mochila[n2 + 1];
                Mochila[n2 + 1] = temp;        
            };
        };
    };
    (*Organizado) = 1;
}

void InsertionSortTipo(DMochila *Mochila, int Titens, int *Organizado){
    DMochila temp;
    for(int n = 1; n < Titens; n++){
        temp = Mochila[n];
        int j = n - 1;
        
        while (j >= 0 && strcmp(Mochila[j].tipo, temp.tipo) > 0)
        {
            Mochila[j+1] = Mochila[j];
            j--;
        }
        Mochila[j+1] = temp;        
    };
    (*Organizado) = 0;
}

void SelectionSortPrioridade(DMochila *Mochila, int Titens, int *Organizado){
    DMochila temp;
    int Temp;
    for(int n = 0; n < Titens; n++){
        Temp = n;
        for(int n2 = n; n2 < Titens; n2++){
            if(Mochila[Temp].prioridade > Mochila[n2].prioridade){
              Temp = n2;
            };
        }
        temp = Mochila[n];
        Mochila[n] = Mochila[Temp];
        Mochila[Temp] = temp;
    }
    (*Organizado) = 0;
}

void ListarItemPorNome(DMochila *Mochila, int Titens, int Organizado){
    if(Organizado == 0){printf("Mochila não organizada... Organize por nome..."); getchar(); return;};
    if(Titens <= 0){printf("Não tem itens na mochila! Pressione Enter para voltar..."); LimparBufferEntrada(); getchar(); return;};
    char item[30];
    printf("\nDigite o nome do item procurado: ");
    PegarTexto(item);
    int inicio = 0;
    int fim = Titens-1;
    int meio;

    while (inicio <= fim)
    {
        meio = inicio + (fim - inicio)/2;
        if(strcmp(Mochila[meio].nome,item) < 0){
            inicio = meio+1;
        }else if (strcmp(Mochila[meio].nome,item) > 0)
        {
            fim = meio-1;
        }else{
            printf("\nItem Encontrado com sucesso! \n");
            printf("-------------------------");
            printf("\nNome: %s\n",Mochila[meio].nome);
            printf("Tipo: %s\n",Mochila[meio].tipo);
            printf("Quantidade: %d\n",Mochila[meio].quantidade);
            printf("Prioridade: %d\n",Mochila[meio].prioridade);
            printf("-------------------------\n");
            printf("\nPressione Enter para voltar...");
            getchar();
            return;
        };   
    };
    printf("\nO item não foi encontrado...");  
    getchar();
    return;
}


//----------------------------------------------------------------------//

int ExibirMenu(int Itens){
    int opcao = 5;
    printf("==============================\n");
    printf("Mochila do jogador: %d/%d Itens\n",Itens,MaxItens);
    printf("==============================\n");

    printf(" 01: Adicionar Item.\n 02: Remover Item. \n 03: Listar Itens. \n 04: Ordenar Itens. \n 05: Encontrar item por nome.\n 00: Sair.\n---------------------- \n Opção: ");
    
    scanf("%d",&opcao);
    LimparBufferEntrada();
    return opcao;

}

void LimparBufferEntrada() {
     int c;
    while((c = getchar()) != '\n' && c != EOF);
};

void PegarTexto(char *Texto){
    char temp[30];
    fgets(temp,30,stdin);
    temp[strcspn(temp, "\n")] = '\0';
    strcpy(Texto,temp);
    return;
}