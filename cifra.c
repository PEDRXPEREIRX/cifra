#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

int main(void){
    srand((unsigned)time(NULL));
    FILE *mensagem;
    FILE *livro;
    char strMen[50], strLiv[50];
    int plv, pos; // plv = posicao da palavra -> pos = posicao na palavra
    int cont, sort; // cont = total de ocorrencias do caractere -> sort = recebe rand de 1 ate cont
    int i, j, k;

    mensagem = fopen("mensagem.txt", "r");
    livro = fopen("livro.txt", "r");

    while(fscanf(mensagem, "%s", strMen) != EOF){
        printf("%s\n", strMen);
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
                            sort--;
                            if(sort==0){
                                plv = j+1;
                                pos = k+1;
                                printf("[%d,%d] \n", plv, pos);
                                break;
                            }
                        }
                    j++;
                }
            }
    }
    fclose(mensagem);
    fclose(livro);



    return 0;
}
