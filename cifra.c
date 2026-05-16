#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

int main(void){
    srand((unsigned)time(NULL));
    FILE *mensagem;
    FILE *livro;
    FILE *cifra;
    char strMen[50], strLiv[50];
    char arqMen[50], arqLiv[50], arqCifra[50];
    int plv, pos; // plv = posicao da palavra -> pos = posicao na palavra
    int cont, sort; // cont = total de ocorrencias do caractere -> sort = recebe rand de 1 ate cont
    int i, j, k;

    printf("Nome do arquivo da mensagem: ");
    scanf("%s", arqMen);
    printf("Nome do arquivo do livro: ");
    scanf("%s", arqLiv);
    printf("Nome do arquivo da cifra: ");
    scanf("%s", arqCifra);


    mensagem = fopen(arqMen, "r");
    if(mensagem == NULL){ printf("Erro ao abrir mensagem\n"); return 1; }
    livro = fopen(arqLiv, "r");
    if(livro == NULL){ printf("Erro ao abrir livro\n"); return 1; }
    cifra = fopen(arqCifra, "w");
    if(cifra == NULL){ printf("Erro ao abrir cifra\n"); return 1; }

    while(fscanf(mensagem, "%s", strMen) != EOF){
        for(i=0; strMen[i]; i++)
            if(isalpha(strMen[i])){
                cont=0;
                fseek(livro, 0, SEEK_SET);
                while(fscanf(livro, "%s", strLiv) != EOF){
                    for(j=0; strLiv[j]; j++)
                        if(tolower(strLiv[j]) == tolower(strMen[i]))
                            cont++;
                }
                if(cont>0)
                    sort = rand()%cont+1;
                j=0;
                fseek(livro, 0, SEEK_SET);
                while(fscanf(livro, "%s", strLiv) != EOF){
                    for(k=0; strLiv[k]; k++)
                        if(tolower(strMen[i]) == tolower(strLiv[k])){
                            sort--; // Decremento sort pra plv e pos receber a "sort" ocorrencia
                            if(sort==0){
                                plv = j+1;
                                pos = k+1;
                                fprintf(cifra, "%d,%d ", plv, pos);
                                break;
                            }
                        }
                    j++;
                }
            }
    }

    fclose(mensagem);
    fclose(livro);
    fclose(cifra);

    return 0;
}
