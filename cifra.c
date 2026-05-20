#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

void cifrar(char *arqLiv, char *arqMen, char *arqCifra){
    FILE *mensagem;
    FILE *livro;
    FILE *cifra;
    char strMen[99], strLiv[99];
    int plv, pos; // plv = posicao da palavra -> pos = posicao na palavra
    int cont, sort; // cont = total de ocorrencias do caractere -> sort = recebe rand de 1 ate cont
    int i, j, k;
    int totPlv=0, totPos=0, rec;

    mensagem = fopen(arqMen, "r");
    if(mensagem==NULL){ printf("\nErro ao abrir arquivo (mensagem)!\n"); exit(1); }
    livro = fopen(arqLiv, "r");
    if(livro==NULL){ printf("\nErro ao abrir arquivo (livro)!\n"); exit(1); }
    cifra = fopen(arqCifra, "w");
    if(cifra==NULL){ printf("\nErro ao abrir arquivo (cifrado)!\n"); exit(1); }

    while(fscanf(livro, "%s", strLiv) != EOF){
        totPlv++; // totPlv recebe o total de palavras no livro
        for(i=0; strLiv[i]; i++);
        if(i>totPos) totPos=i; // totPos recebe o total de letras da maior palavra
    }

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
                    rec = rand()%2; // se 0 o plv = 0 se não o pos = 0, para ficar diferente no arquivo cifrado (0,X ou X,0)
                    if(!rec){
                        plv = 0;
                        pos = rand()%totPos+1;
                    }
                    else {
                        plv = rand()%totPlv+1;
                        pos = 0;
                    }
                    fprintf(cifra, "%d,%d ", plv, pos);
                }
            }
    }
    fclose(mensagem);
    fclose(livro);
    fclose(cifra);
}

void decifrar(char *arqLiv, char *arqMen, char *arqCifra){
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

    while(fscanf(mensagem, "%d,%d", &plv, &pos) != EOF){
        i=0;
        if(plv==0 || pos==0)  // caso seja uma letra que nao existe no livro
            fprintf(cifra, "_");
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
    printf("Nome do arquivo livro: ");
    scanf("%s", arqLiv);
    printf("Nome do arquivo original: ");
    scanf("%s", arqMen);
    printf("Nome do arquivo a ser cifrado: ");
    scanf("%s", arqCifra);
    cifrar(arqLiv, arqMen, arqCifra);

    printf("\n*** Decifrar Mensagem ***\n");
    printf("Nome do arquivo do livro: ");
    scanf("%s", arqLiv);
    printf("Nome do arquivo cifrado: ");
    scanf("%s", arqMen);
    printf("Nome do arquivo a ser decifrado: ");
    scanf("%s", arqCifra);
    decifrar(arqLiv, arqMen, arqCifra);
    printf("\n*** Programa finalizado ***\n");

    return 0;
}
