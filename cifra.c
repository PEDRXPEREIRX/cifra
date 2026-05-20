#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

void cifrar(char *arqMen, char *arqLiv, char *arqCifra){
    FILE *mensagem;
    FILE *livro;
    FILE *cifra;
    char strMen[99], strLiv[99];
    int plv, pos; // plv = posicao da palavra -> pos = posicao na palavra
    int cont, sort; // cont = total de ocorrencias do caractere -> sort = recebe rand de 1 ate cont
    int i, j, k;

    mensagem = fopen(arqMen, "r");
    if(mensagem==NULL){ printf("\nErro ao abrir arquivo (mensagem)!\n"); exit(1); }
    livro = fopen(arqLiv, "r");
    if(livro==NULL){ printf("\nErro ao abrir arquivo (livro)!\n"); exit(1); }
    cifra = fopen(arqCifra, "w");
    if(cifra==NULL){ printf("\nErro ao abrir arquivo (cifrado)!\n"); exit(1); }

    while(fscanf(mensagem, "%s", strMen) != EOF){
        for(i=0; strMen[i]; i++)
            if(isalpha(strMen[i])){ // usei a funcao isalpha da biblioteca ctype em troca do if(strMen[i] >= 'A' &&...
                cont=0;
                fseek(livro, 0, SEEK_SET); // Voltar sempre pro inicio do arquivo
                while(fscanf(livro, "%s", strLiv) != EOF){
                    for(j=0; strLiv[j]; j++)
                        if(tolower(strLiv[j]) == tolower(strMen[i])) // usei funcao tolower da biblioteca ctype para forçar comparar sempre letras minusculas
                            cont++; // Loop para contar o total de ocorrencias da letra atual
                }
                if(cont>0){
                    sort = rand()%cont+1;
                    j=0;
                    fseek(livro, 0, SEEK_SET);
                    while(fscanf(livro, "%s", strLiv) != EOF){
                        for(k=0; strLiv[k]; k++)
                            if(tolower(strMen[i]) == tolower(strLiv[k])){
                                sort--; // Decremento sort pra "plv" e "pos" receber a "sort" ocorrencia
                                if(!sort){
                                    plv = j+1; // +1 pra contar a partir do 1 e nao do 0
                                    pos = k+1;
                                    fprintf(cifra, "%d,%d ", plv, pos);
                                    break;
                                }
                            }
                        if(!sort) break;
                        j++;
                    }
                }
                else {
                    plv = 0; // Caso nao tenha a letra no livro
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
    char strLiv[99];
    int i, plv, pos; // plv = posicao da palavra -> pos = posicao na palavra

    mensagem = fopen(arqMen, "r");
    if(mensagem==NULL){ printf("\nErro ao abrir arquivo (cifrado)!\n"); exit(1); }
    livro = fopen(arqLiv, "r");
    if(livro==NULL){ printf("\nErro ao abrir arquivo (livro)!\n"); exit(1); }
    cifra = fopen(arqCifra, "w");
    if(cifra==NULL){ printf("\nErro ao abrir arquivo (decifrado)!\n"); exit(1); }

    while(fscanf(mensagem, "%d,%d", &plv, &pos) == 2){
        i=0;
        if(plv==0)  // caso seja uma letra que nao existe no livro
            fprintf(cifra, "#");
        else{
            fseek(livro, 0, SEEK_SET);
            while(fscanf(livro, "%s", strLiv) != EOF){
                i++; // da loop incrementando i ate chegar na palavra (dada pelo valor de plv)
                if(i==plv){
                    fprintf(cifra, "%c", tolower(strLiv[pos-1])); // pos-1 pra tirar o +1 adicionado na funcao cifrar
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
    char arqMen[99], arqLiv[99], arqCifra[99];

    printf("*** Cifrar Mensagem ***\n");
    printf("Nome do arquivo da mensagem: ");
    scanf("%s", arqMen);
    printf("Nome do arquivo do livro: ");
    scanf("%s", arqLiv);
    printf("Nome do arquivo da cifra: ");
    scanf("%s", arqCifra);
    cifrar(arqMen, arqLiv, arqCifra);
    printf("\n");

    printf("*** Decifrar Mensagem ***\n");
    printf("Nome do arquivo cifrado: ");
    scanf("%s", arqMen);
    printf("Nome do arquivo do livro: ");
    scanf("%s", arqLiv);
    printf("Nome do arquivo decifrado: ");
    scanf("%s", arqCifra);
    decifrar(arqMen, arqLiv, arqCifra);
    printf("\n*** Programa finalizado ***\n");

    return 0;
}
