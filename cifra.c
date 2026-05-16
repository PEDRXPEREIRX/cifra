#include <stdio.h>
#include <ctype.h>

int main(void){
    FILE *mensagem = fopen("mensagem.txt", "r");
    FILE *livro = fopen("livro.txt", "r");
    char str[50];
    int i;


    while(fscanf(mensagem, "%s", str) != EOF){
        printf("%s ", str);
        for(i=0; str[i]; i++)
            if(isalpha(str[i]))
    }






    return 0;
}
