// Quando o usuário escolher, no menu principal, a opção 6 – Boletim do aluno, o sistema deverá:
// • perguntar se também será gerado um arquivo para o boletim a ser gerado. Em caso positivo:
// o deverá ser criado um arquivo chamado <nome do aluno>-< nome da turma>.txt
// o registrar na estrutura GRAVADO, o id_g e o nome do arquivo
// o deverá ser criada uma função que irá escrever LINHA A LINHA (recebendo a linha por argumento) tudo o que for aparecer na tela

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

struct ALUNO
{
    char nome[50];
    int idade;
    int id_t; // obtera da nossa variavel controladora do indice de turma
};

struct TURMA
{
    char nome[30];
    int turno;
};

struct MATERIA
{
    char nome[30];
    int cargah;
};

struct TXM
{
    int id_t;
    int id_m;
};

struct BOLETIM
{
    int id_a;
    int id_m;
    float nota_prova[3];
};

FILE *arq;

void gravaBoletim(char msgaux[250])
{

    fprintf(arq, "%s", msgaux);
}

void cadastraAluno(struct ALUNO *aluno, int *id_t, int *id_aux, int *sair, char *palavra, struct TURMA *turma, int *id_temp)
{
    int x = 0;
    int id_a = *id_aux;

    if (*id_t == 0)
    { // Verifica a existencia de turmas
        printf("Atencao: Cadastre uma turma primeiro!\n");
        system("pause");
        return;
    }
    printf("\n---------- Cadastro de aluno -----------\n\n\n");
    do
    {
        if (id_a >= 30)
        {
            printf("Ja alcancamos o maximo de alunos\n");
            system("pause");
            *sair = 1;
        }
        else
        {
            printf("\n\nNome do aluno %d ......: ", id_a + 1);
            fflush(stdin); // limpa o buffer de teclado
            gets(palavra);
            if (strcmp(palavra, "fim") == 0)
                *sair = 1;
            else
            {
                strcpy(aluno[id_a].nome, palavra);
                printf("Idade do aluno %d .....: ", id_a + 1);
                scanf("%d", &aluno[id_a].idade);

                printf("Turmas cadastradas:\n"); // Lista as turmas
                for (x = 0; x < *id_t; x++)
                    printf("%d - %s\t", x + 1, turma[x].nome);
                do
                { // verifica se a turma entrada existe, senao pede novamente
                    printf("\n\nTurma do aluno:");
                    scanf("%d", id_temp);
                    *id_temp -= 1;
                    if (*id_temp < 0 || *id_temp >= *id_t)
                        printf("Turma invalida");
                    else
                        aluno[id_a].id_t = *id_temp;
                } while (*id_temp < 0 || *id_temp >= *id_t);

                id_a++;
            }
        }
    } while (!*sair);

    *id_aux = id_a;
}

void cadastraTurma(int *id_aux, int *sair, char *palavra, struct TURMA *turma)
{
    int id_t = *id_aux;
    do
    {

        if (id_t >= 5)
        {
            printf("Ja alcancamos o maximo de turmas");
            system("pause");
            *sair = 1;
        }
        else
        {
            printf("\n\nNome do turma %d ......: ", id_t + 1);
            fflush(stdin); // limpa o buffer de teclado
            gets(palavra);
            if (strcmp(palavra, "fim") == 0)
                *sair = 1;
            else
            {
                strcpy(turma[id_t].nome, palavra);
                printf("Carga Horaria da turma %d .....: ", id_t + 1);
                scanf("%d", &turma[id_t].turno);

                id_t++;
            }
        }

    } while (!*sair);

    *id_aux = id_t;
}

void cadastraMateria(int *id_aux, int *sair, char *palavra, struct MATERIA *materia)
{
    int id_m = *id_aux;
    do
    {
        if (id_m >= 10)
        {
            printf("Ja alcancamos o maximo de materias");
            system("pause");
            *sair = 1;
        }
        else
        {
            printf("\n\nNome da materia %d ......: ", id_m + 1);
            fflush(stdin); // limpa o buffer de teclado
            gets(palavra);
            if (strcmp(palavra, "fim") == 0)
                *sair = 1;
            else
            {
                strcpy(materia[id_m].nome, palavra);
                printf("Carga horaria da materia %d .....: ", id_m + 1);
                scanf("%d", &materia[id_m].cargah);
                id_m++;
            }
        }
    } while (!*sair);

    *id_aux = id_m;
}

void turmaMateria(int *id_tAux, int *id_mAux, int *id_aux, struct TURMA *turma, struct MATERIA *materia, struct TXM *txm, int *sair, int *id_temp, int *id_temp2)
{
    int id_txm = *id_aux;
    int id_t = *id_tAux;
    int id_m = *id_mAux;

    // verifico a exitencia das turmas e das materias
    if (id_t == 0 || id_m == 0)
    {
        printf("Atencao: Cadastre uma turma e materia primeiro!\n");
        system("pause");
        return;
    }

    // Listamos a relação turma X materia existentes
    if (id_txm > 0)
    {

        printf("Cadastro existente\n\nTurma\tMateria\n=====\t=======\n");
        for (int x = 0; x < id_txm; x++)
            printf("%s\t%s\n", turma[txm[x].id_t].nome, materia[txm[x].id_m].nome);
    }

    // listamos as opções de turmas e de materias
    printf("\nTurmas cadastradas:\n\nCodigo\tTurma\n======\t=====\n"); // Lista as turmas
    for (int x = 0; x < id_t; x++)
        printf("%d\t%s\n", x, turma[x].nome);
    printf("\n\nMaterias cadastradas:\n\nCodigo\tMateria\n======\t=======\n"); // Lista as materias
    for (int x = 0; x < id_m; x++)
        printf("%d\t%s\n", x, materia[x].nome);
    printf("\n\n");

    //  Agora vamos cadastrar
    do
    {
        printf("\n\nCodigo da turma (-1 sair) ......: ");
        fflush(stdin); // limpa o buffer de teclado
        scanf("%d", id_temp);
        if (*id_temp < 0 || *id_temp >= id_t)
        {
            if (*id_temp == -1)
            {
                *sair = 1;
            }
            else
            {
                printf("Turma invalida, informe novamente ou cancele com -1\n");
            }
        }
        else
        {
            do
            {
                printf("\n\nCodigo da materia (-1 sair) ......: ");
                fflush(stdin); // limpa o buffer de teclado
                scanf("%d", id_temp2);
                // vamos verificar a entrada invalida ou o cancelamento da insercao txm
                if (*id_temp2 < 0 || *id_temp2 >= id_m)
                {
                    if (*id_temp2 == -1)
                    {
                        *sair = 1;
                    }
                    else
                    {
                        printf("Materia invalida, informe novamente ou cancele com -1\n");
                    }
                }
                else
                //  gravamos na estrutura, sem verificar duplicidade
                {
                    txm[id_txm].id_t = *id_temp;
                    txm[id_txm].id_m = *id_temp2;
                    id_txm++;
                    printf("Cadastro da TxM realizado");
                    *sair = 0;
                }
            } while (!*sair);
            *sair = 0;
        }
    } while (!*sair);

    *id_aux = id_txm;
    *id_tAux = id_t;
    *id_mAux = id_m;
}

void Gerarnotas(int *id_txmAux, int *id_bAux, int *id_aux, struct BOLETIM *boletim, struct ALUNO *aluno, struct TXM *txm, int *sair)
{
    int id_a = *id_aux;
    int id_txm = *id_txmAux;
    int id_b = *id_bAux;

    // variaveis para controle do randomico
    int inf = 0,   // menor limite dos numeros gerados
        sup = 100; // maior limite dos numeros gerados

    // verifico se existe aluno e TxM
    if (id_a == 0 || id_txm == 0)
    {
        printf("Atencao: nao eh possivel gerar notas sem alunos x turma x materia!\n");
        *sair = 1;
    }

    else
    {
        // Caso ja exita nota no boletim, eu reescrevo.
        id_b = 0;

        // As notas serao geradas com um laco em aluno que ira pegar a sua turma, buscar em TxM a existencia dessa
        // turma e gerar para as materias as 3 notas no boletim
        for (int x = 0; x < id_a; x++)
        {
            for (int y = 0; y < id_txm; y++)
            {
                if (aluno[x].id_t == txm[y].id_t)
                {
                    // gera as notas
                    for (int z = 0; z < 3; z++)
                    {
                        boletim[id_b].id_a = x;
                        boletim[id_b].id_m = txm[y].id_m;
                        boletim[id_b].nota_prova[z] = (float)((rand() % (sup - inf + 1)) + inf) / 10.0;
                    }
                    id_b++;
                }
            }
        }
    }
    *id_bAux = id_b;
}

void Boletimdealuno(int *id_aux, int *id_bAux, struct BOLETIM *boletim, struct ALUNO *aluno, struct MATERIA *materia, struct TURMA *turma, int *id_temp, int *sair)
{
    int id_a = *id_aux;
    int id_b = *id_bAux;
    int aux = 0;
    // verifico a exitencia das notas geradas
    if (id_b == 0)
    {
        printf("Não existem alunos com notas geradas!\n");
        system("pause");
        return;
    }

    // Listo os alunos para escolha
    printf("Matricula\tNome\n=========\t====\n");
    for (int x = 0; x < id_a; x++)
    {
        printf("%d\t\t%s\n", x, aluno[x].nome);
    }

    do
    {
        // Escolho verificando a existencia
        do
        {
            printf("De qual aluno deseja ver o boletim? ( -1 para sair ): ");
            scanf("%d", id_temp);
            if (*id_temp >= id_a)
                printf("Matricula inexistente\n");
            else if (*id_temp < 0)
            {
                *sair = 1;
            }
        } while (*id_temp >= id_a);

        aux = *id_temp;

        if (*id_temp >= 0)
        {
            char grava, msg[250], msgaux[250], nomeArq[85];

            fflush(stdin);
            printf("O sistema deverá gravar o boletim em arquivo (s/n)? : ");
            scanf("%c", &grava);
            fflush(stdin);

            if (grava == 's' || grava == 'S')
            {
                strcpy(nomeArq, aluno[aux].nome);
                strcat(nomeArq, " - ");
                strcat(nomeArq, turma[aluno[aux].id_t].nome);
                strcat(nomeArq, ".txt");
            }

            if ((arq = fopen(nomeArq, "w")) == NULL)
            {
                // crio o arquivo para gravacao
                printf("Erro na criacao do arquivo"); // verificando se deu erro
                system("pause");
                exit(1);
            }

            printf("\nBoletim do Aluno:%s, que tem %d anos.\n\n", aluno[aux].nome, aluno[aux].idade);

            // gero a linha a ser gravada com sprintf e chamo a funcao
            sprintf(msgaux, "\nBoletim do Aluno:%s, que tem %d anos.\n\n", aluno[aux].nome, aluno[aux].idade);
            gravaBoletim(msgaux);

            printf("Materia\tNota 1\tNota 2\tNota 3\n=======\t======\t======\t======\n");
            sprintf(msgaux, "Materia\tNota 1\tNota 2\tNota 3\n=======\t======\t======\t======\n");
            gravaBoletim(msgaux);

            for (int x = 0; x < id_b; x++)
            {
                if (boletim[x].id_a == aux)
                {
                    printf("%s\t", materia[boletim[x].id_m].nome);
                    sprintf(msgaux, "%s\t", materia[boletim[x].id_m].nome);
                    gravaBoletim(msgaux);

                    for (int y = 0; y < 3; y++)
                    {
                        printf("%.2f\t", boletim[x].nota_prova[y]);
                        sprintf(msgaux, "%.2f\t", boletim[x].nota_prova[y]);
                        gravaBoletim(msgaux);
                    }
                    printf("\n");
                    strcpy(msgaux, "\n");
                    gravaBoletim(msgaux);
                }
            }

            fclose(arq);
        }
    } while (!*sair);
    *sair = 0;
}

void Boletimdeturma(int *id_aux, int *id_tAux, int *id_bAux, struct BOLETIM *boletim, struct ALUNO *aluno, struct TURMA *turma, struct MATERIA *materia, int *id_temp, int *id_temp2, int *sair)
{
    int id_t = *id_tAux;
    int id_b = *id_bAux;
    int id_a = *id_aux;
    int aux = 0;
    // verifico a exitencia das notas geradas
    if (id_b == 0)
    {
        printf("Não existem alunos com notas geradas!\n");
        system("pause");
        return;
    }

    // Listo turmas para escolha
    printf("Turma\tNome\n=====\t====\n");
    for (int x = 0; x < id_t; x++)
    {
        printf("%d\t%s\n", x, turma[x].nome);
    }

    do
    {
        // Escolho verificando a existencia
        do
        {
            printf("De qual turma deseja ver o boletim? ( -1 para sair ): ");
            scanf("%d", id_temp);

            if (*id_temp >= id_t)
                printf("Turma inexistente\n");
            else if (*id_temp < 0)
            {
                *sair = 1;
            }

        } while (*id_temp >= id_a);

        aux = *id_temp;

        if (*id_temp >= 0)
        {
            printf("\nBoletim do Turma:%s do turno %d.\n\n", turma[aux].nome, turma[aux].turno);

            // percorro a estrutura de aluno para obter os alunos que são da turma escolhida,
            // indo depois no boletim para listar as notas
            for (int x = 0; x < id_a; x++)
            {
                if (aluno[x].id_t == id_temp)
                {

                    *id_temp2 = 0; //(ira verificar se continua sendo o mesmo aluno ja impresso)

                    for (int y = 0; y < id_b; y++)
                    {
                        if (boletim[y].id_a == x)
                        {
                            if (*id_temp2 == 0)
                            {
                                printf("Aluno: %s\n", aluno[x].nome);
                                printf("Materia\tNota 1\tNota 2\tNota 3\n=======\t======\t======\t======\n");
                            }
                            *id_temp2++; // para nao imprimir o cabecalho acima
                            printf("%s\t", materia[boletim[y].id_m].nome);
                            for (int z = 0; z < 3; z++)
                            {
                                printf("%.2f\t", boletim[y].nota_prova[z]);
                            }
                            printf("\n");
                        }
                    }
                    printf("\n\n");
                }
            }
        }
    } while (!*sair);

    *sair = 0;
}

main()
{

    struct ALUNO aluno[30];
    struct MATERIA materia[10];
    struct TURMA turma[5];
    struct TXM txm[50];
    struct BOLETIM boletim[300];

    int id_a = 0, id_m = 0, id_t = 0, id_txm = 0, id_b = 0; // posicao no vetor da estrutura
    int x, y, z;                                            // contadores

    int op,                // opcao do menu principal
        sair = 0,          // saida e cancelamento dos laços
        id_temp, id_temp2; // var temporaria para identificadores

    char palavra[30]; // var temporaria para verificacao de termino do laço secundario

    srand(time(0)); // inicializa o randomico

    while (!sair)
    {
        system("cls");

        printf("\n---------- Escola Saber Compartilhado -----------\n\n\n");
        printf("\n---------- Menu Principal -----------\n\n\n");
        printf("\n  1 - Cadastrar Aluno \n");
        printf("\n  2 - Cadastrar Materia \n");
        printf("\n  3 - Cadastrar Turma \n");
        printf("\n  4 - Cadastrar Turma x Materia \n");
        printf("\n  5 - Gerar notas \n");
        printf("\n  6 - Boletim de aluno \n");
        printf("\n  7 - Boletim de turma \n");
        printf("\n  0 - Sair \n");
        printf("\n\n\n\n  Opcao: \n");
        scanf("%d", &op);

        switch (op)
        {
        //  Cadastrar Aluno
        case 1:
            system("cls");
            cadastraAluno(aluno, &id_t, &id_a, &sair, palavra, turma, &id_temp);
            sair = 0;
            break;

        case 2:
            // Cadastrar Materia

            system("cls");
            printf("\n---------- Cadastro de materia -----------\n\n\n");
            cadastraMateria(&id_m, &sair, palavra, materia);
            sair = 0;
            break;

        case 3:
            // Cadastrar Turma

            system("cls");
            printf("\n---------- Cadastro de turma -----------\n\n\n");
            cadastraTurma(&id_t, &sair, palavra, turma);
            sair = 0;
            break;

        case 4:

            // Cadastrar Turma x Materia

            system("cls");
            printf("\n---------- Cadastro de turma x materia -----------\n\n\n");
            turmaMateria(&id_t, &id_m, &id_txm, turma, materia, txm, &sair, &id_temp, &id_temp2);
            sair = 0;
            break;

        case 5:

            // Gerar notas
            system("cls");
            Gerarnotas(&id_txm, &id_b, &id_a, boletim, aluno, txm, &sair);

            if (sair == 1)
            {
                printf("Notas nao geradas!\n");
                system("pause");
                sair = 0;
                break;
            }

            printf("Notas geradas com sucesso!\n");
            system("pause");
            sair = 0;
            break;

        case 6:

            // Boletim de aluno
            system("cls");
            printf("\n---------- Boletim do Aluno -----------\n\n\n");
            Boletimdealuno(&id_a, &id_b, boletim, aluno, materia, turma, &id_temp, &sair);
            sair = 0;
            break;

        case 7:

            // Boletim de turma

            system("cls");
            printf("\n---------- Boletim da turma -----------\n\n\n");
            Boletimdeturma(&id_a, &id_t, &id_b, boletim, aluno, turma, materia, &id_temp, &id_temp2, &sair);
            sair = 0;
            break;

        case 0:
            // Sair
            sair = 1;
            break;

        default:
            // Erro
            printf("Opcao invalida!\nEscolha novamente!\n");
            system("pause");
        }
    }
}
