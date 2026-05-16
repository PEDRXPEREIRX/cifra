#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

void cifrar(char *arqMen, char *arqLiv, char *arqCifra){
    FILE *mensagem;
    FILE *livro;
    FILE *cifra;
    char strMen[50], strLiv[50];
    int plv, pos; // plv = posicao da palavra -> pos = posicao na palavra
    int cont, sort; // cont = total de ocorrencias do caractere -> sort = recebe rand de 1 ate cont
    int i, j, k;
    mensagem = fopen(arqMen, "r");
    livro = fopen(arqLiv, "r");
    cifra = fopen(arqCifra, "w");

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
                if(cont>0){
                    sort = rand()%cont+1;
                    j=0;
                    fseek(livro, 0, SEEK_SET);
                    while(fscanf(livro, "%s", strLiv) != EOF){
                        for(k=0; strLiv[k]; k++)
                            if(tolower(strMen[i]) == tolower(strLiv[k])){
                                sort--; // Decremento sort pra "plv" e "pos" receber a "sort" ocorrencia
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
                else {
                    plv = 0;
                    pos = 0;
                    fprintf(cifra, "%d,%d ", plv, pos);
                }
            }
    }
    fclose(mensagem);
    fclose(livro);
    fclose(cifra);
}

void decifrar(char *arqMen, char *arqLiv, char *arqCifra){
    FILE *mensagem;
    FILE *livro;
    FILE *cifra;
    char strMen[50], strLiv[50];
    int i, plv, pos; // plv = posicao da palavra -> pos = posicao na palavra

    mensagem = fopen(arqMen, "r");
    livro = fopen(arqLiv, "r");
    cifra = fopen(arqCifra, "w");

    while(fscanf(mensagem, "%d,%d", &plv, &pos) == 2){
        i=0;
        if(plv==0)  // caso seja uma letra que nao existe no livro
            fprintf(cifra, "_");
        else{
            fseek(livro, 0, SEEK_SET);
            while(fscanf(livro, "%s", strLiv)){
                i++; // da loop incrementando i ate chegar na palavra (dada pelo valor de plv)
                if(i==plv){
                    fprintf(cifra, "%c", strLiv[pos-1]);
                    break;
                }
            }
        }
    }

    fclose(mensagem);
    fclose(livro);
    fclose(cifra);
}

int main(void){
    srand((unsigned)time(NULL));
    char arqMen[50], arqLiv[50], arqCifra[50];
    int escolha;

    printf("Escolha -> [1] Cifrar   [2] Decifrar: ");
    while((scanf("%d", &escolha)) != 1){
        printf("Escolha um inteiro (1 ou 2): ");
        while(getchar() != '\n');
    } while(getchar() != '\n');

    printf("Nome do arquivo da mensagem: ");
    scanf("%s", arqMen);
    printf("Nome do arquivo do livro: ");
    scanf("%s", arqLiv);
    printf("Nome do arquivo da cifra: ");
    scanf("%s", arqCifra);
    cifrar(arqMen, arqLiv, arqCifra);
    printf("\n");

    printf("Nome do arquivo cifrado: ");
    scanf("%s", arqMen);
    printf("Nome do arquivo do livro: ");
    scanf("%s", arqLiv);
    printf("Nome do arquivo decifrado: ");
    scanf("%s", arqCifra);
    decifrar(arqMen, arqLiv, arqCifra);
    printf("\n");

    return 0;
}
