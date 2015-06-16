#include <stdlib.h>
#include <stdio.h>
#include <iostream>


using namespace std;

//Funcao que mostra o vetor na tela
void print_array(int vet[], int length) {
    for(int i = 0; i < length; i++) {
        if(i > 0) cout << " | ";
        cout << vet[i];
    }
    cout << endl;
}

void quick_sort(int vet[], int start, int finish) {
    //Indices da esquerda e direita
    int aIndex = start;
    int bIndex = finish;

    //Valor pivo ou de referencia
    int refVal = vet[(finish + start) / 2];

    while(aIndex <= bIndex) {

        //Procura valores no vetor que nao estao ordenados
        while(vet[aIndex] < refVal && aIndex < finish) {
            aIndex++;
        }
        while(vet[bIndex] > refVal && bIndex > start) {
            bIndex--;
        }

        //Substitui o valor calor nao tenham se cuzado(realmente estejam desordenados)
        if(aIndex <= bIndex) {
            swap(vet[aIndex], vet[bIndex]);
            aIndex++;
            bIndex--;
        }
    }

    //Ordena as outras partes se necessario(nao tenham chegado a algum extremo do vetor)
    if(bIndex > start) {
        quick_sort(vet, start, bIndex);
    }
    if(aIndex < finish) {
        quick_sort(vet, aIndex, finish);
    }

}

void bubble_sort(int vet[], int length) {
    bool change = true;

    //Realiza varredura ate alguma delas nao mudar o vetor
    while(change) {
        change = false;

        //Varre vetor procurando pares desordenados
        for(int i = 0; i < length - 1; i++) {

            //Substitui se caso nao estejam ordenados
            if(vet[i] > vet[i + 1]) {
                swap(vet[i], vet[i + 1]);
                change = true;
            }
        }
    }
}
void selection_sort(int vet[], int length) {
    int index, temp;

    //Varre vetor e utiliza o restante a direita para achar o menor valor
    for(int i = 0; i < length - 1; i++) {
        index = i;

        //Procura menor valor no restante do vetor
        for(int j = i + 1; j < length; j++) {
            if(vet[j] < vet[index]) {
                index=j;
            }
        }

        //Troca menor valor com a posicao atual
        swap(vet[i], vet[index]);
    }
}
void insertion_sort(int vet[], int length) {
    int j, n;

    //Varre vetor
    for (int i = 1; i < length; i++) {
        n = vet[i];
        j = i - 1;

        //Move o valor na posicao i ate que o valor em i - 1 seja menor que ele, e i + 1 maior
        while (j >= 0 && n < vet[j]) {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = n;
    }
}

bool get_continue() {
    int opt = -1;

    //Enquanto opcao nao eh valida mostra o menu
    while(opt < 0 || opt > 1) {
        cout << "Deseja realizar outra leitura?" << endl;
        cout << " 1. Sim." << endl;
        cout << " 0. Sair do programa." << endl;
        cout << endl;
        cout << "Digite sua opcao: ";
        cin >> opt;
    }

    //Retorna opcao escolhida em forma booleana
    if(opt == 1) return true;
    return false;
}

//Funcao que mostra menu e retorna opcao de ordenacao que o usuario escolheu
int get_sort_type() {
    int opt = -1;

    //Enquanto opcao nao eh valida mostra o menu
    while(opt < 1 || opt > 4) {
        cout << "Qual algoritmo de ordenacao deseja utilizar? " << endl;
        cout << " 1. Selection sort" << endl;
        cout << " 2. Insertion sort" << endl;
        cout << " 3. Quick sort" << endl;
        cout << " 4. Bubble sort" << endl;
        cout << endl;
        cout << "Digite sua opcao: ";
        cin >> opt;
    }

    return opt;
}
int main () {
    //Boolean para repeticao
    bool cont = true;

    //Enquanto usuario quer repetir a leitura
    while(cont) {

        //Char temporario para leitura do arquivo
        char ch;

        //String para armazenar o conteudo do arquivo
        string input = "";

        //Quantidade de numeros no arquivo, deduzida a partir da quantidade de caracteres \n
        int numberCount = 1;

        //Objeto para leitura do arquivo
        FILE *arq;

        //Abre stream do arquivo para leitura
        arq = fopen("input.txt", "r");

        //Se objeto for nulo, algum erro ocorreu
        if (arq == NULL) {
            cout << "Erro, nao foi possivel abrir o arquivo \n";
        } else {
            //Varre o arquivo inteiro contando novas linhas e armazenando o conteudo numa variavel
            while((ch = fgetc(arq)) != EOF) {
                if(ch == '\n') numberCount++;
                input += ch;
            }
        }
        //Fecha stream do arquivo
        fclose(arq);

        //Cria vetor para armazenar os numeros no arquivo
        int numbers[numberCount];
        int j = 0;

        //String temporaria para ler o numero
        string temp = "";
        for(int i = 0; i <= input.size(); i++) {
            //Vai armazenando o numero em string ate achar quebra de linha ou chegar no final do arquivo
            if(input[i] != '\n' && i != input.size()) {
                temp += input[i];
            } else {
                //Converte string para int
                numbers[j] = atoi(temp.c_str());
                j++;
                temp = "";
            }
        }

        //Mostra vetor desordenado
        print_array(numbers, numberCount);
        cout << endl;

        //Le qual algoritmo usuario quer utilizar
        int sort_type = get_sort_type();

        //Realiza ordenacao de acordo com a escolha do usuario
        switch(sort_type) {
        case 1:
            selection_sort(numbers, numberCount);
            break;
        case 2:
            insertion_sort(numbers, numberCount);
            break;
        case 3:
            quick_sort(numbers, 0, numberCount - 1);
            break;
        case 4:
            bubble_sort(numbers, numberCount);
            break;
        }
        cout << endl;

        //Mostra vetor depois da ordenacao
        print_array(numbers, numberCount);
        cout << endl;

        //Le se o usuario quer continuar fazendo outra leitura o fechar o programa
        cont = get_continue();
        if(cont) system("cls");
    }

}













