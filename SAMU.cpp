#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#define INT_MAX 9999

using namespace std;

float **Aloca_MatrizFloat(int l, int c, float **m)
{
	m = (float**) malloc(l * sizeof(float*));
	for (int i = 0; i < l; i++)
		m[i] = (float*)malloc( c * sizeof (float));
	return m;
}

float **Ent_Grafo(float **Md, char Arq[30])
{
	int C, L, nv, Peso = 0;
	FILE *arquivo;
	arquivo = fopen(Arq, "r");
	if (!arquivo)
	{
		printf("O arquivo %s nao pode ser aberto", Arq);
		getchar();
		exit(1);
	}
	else
	{
		L = 0;
		C = 0;
		fscanf(arquivo, "%d", &nv);
		Md = Aloca_MatrizFloat(nv, nv, Md);
		while (!feof(arquivo))
		{
			fscanf(arquivo, "%d", &Peso);
			if (Peso != -1) // -1 marca o fim do arquivo
			{
				Md[L][C] = Peso;
			}
			if(Peso == -1) // marca o fim da linha
			{
				L++;
				C = 0;
			}
			else
				C++;
		}  //fim do arquivo

	}
	//Fechando arquivo
	fclose(arquivo);
	//G->dist=Md;
	return Md;
}  //Fim da função Ent_Grafo


void Imprime_Matriz(int n, float** Md)
{
	int i, j;
	cout << "\t----------------------------------" << endl;
	cout << "\t      Matriz de Distancias" << endl;
	cout << "\t----------------------------------" << endl;
	for(i = 0; i < n; i++)
	{
		if(i != 0) cout << endl;
		for(j = 0; j < n; j++)
			cout << "\t" << Md[i][j];
	}
	cout << endl;
	system("pause");
}

void Libera_Matriz(float **m, int n)
{
	int i;
	for(i = 0; i < n; i++)
		free(m[i]);
	free(m);
}

void Sorteia_Vertices(int num_vertices, float **matriz_distancias)
{
    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios

    int v1 = rand() % num_vertices; // Sorteia o primeiro vértice entre 0 e num_vertices - 1
    int v2 = rand() % num_vertices; // Sorteia o segundo vértice entre 0 e num_vertices - 1

    cout << "Acidente 1: " << v1 << endl;
    cout << "Acidente 2: " << v2 << endl;
}

void Dijkstra(int NV, int inicio, float **custo, int v1, int v2)
{
    int *distancia, *pred;
    int *visitado, cont, distanciamin, proxno, i, j;
    visitado = (int *)malloc(NV * sizeof(int));
    pred = (int *)malloc(NV * sizeof(int));
    distancia = (int *)malloc(NV * sizeof(int));
    for (i = 0; i < NV; i++)
    {
        distancia[i] = custo[inicio][i];
        pred[i] = inicio;
        visitado[i] = 0;
    }
    distancia[inicio] = 0;
    visitado[inicio] = 1;
    cont = 1;
    while (cont < NV - 1)
    {
        distanciamin = 9999;
        for (i = 0; i < NV; i++)
            if (distancia[i] < distanciamin && !visitado[i])
            {
                distanciamin = distancia[i];
                proxno = i;
            }
        // verifica se existe melhor caminho através do próximo nó
        visitado[proxno] = 1;
        for (i = 0; i < NV; i++)
        {
            if (!visitado[i])
                if (distanciamin + custo[proxno][i] < distancia[i])
                {
                    distancia[i] = distanciamin + custo[proxno][i];
                    pred[i] = proxno;
                }
        }
        cont++;
    }
    // Imprime o menor caminho para os vértices de destino, se eles foram alcançados
    for (j = 0; j < NV; j++)
    {
        if (j != inicio && (j == v1 || j == v2))
        {
            cout << "\nCusto/Distancia: " << inicio << " ao acidente " << j << " = " << distancia[j] << endl;
            cout << "Caminho: " << j;
            int k = j;
            do
            {
                k = pred[k];
                cout << " <- " << k;
            } while (k != inicio);
        }
    }
    cout << endl;
    free(visitado);
    free(pred);
    free(distancia);
}


int main()
{
    float **Md = NULL;
    int nv;
    char nomeArquivo[30] = "DistSAMU_110.txt";
    int opcao;

    // Carregar número de vértices do arquivo
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo)
    {
        printf("O arquivo %s nao pode ser aberto", nomeArquivo);
        getchar();
        exit(1);
    }
    else
    {
        fscanf(arquivo, "%d", &nv);
        fclose(arquivo);
    }

    // Menu
    do
    {
        cout << "\n===== MENU =====" << endl;
        cout << "1. Sortear vertices" << endl;
        cout << "2. Monitorar Acidentes" << endl;
		cout << "3. Imprimir matriz de distancias" << endl;
        cout << "4. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
        	system("cls");
        	int v1, v2;
            srand(time(NULL));
            v1 = rand() % nv;
            v2 = rand() % nv;
            Md = Ent_Grafo(Md, nomeArquivo);
            Sorteia_Vertices(nv, Md);
            Libera_Matriz(Md, nv);
            break;
        case 2:
        	system("cls");
        	cout << "Acidente 1: " << v1 << endl;
        	cout << "Acidente 2: " << v2 << endl;
            Md = Ent_Grafo(Md, nomeArquivo);
            Dijkstra(nv, 83, Md, v1, v2); // Central de Samu até os dois acidentes
            Dijkstra(nv, 19, Md, v1, v2); // Dos dois acidentes até o hospital 19
            Dijkstra(nv, 40, Md, v1, v2); // Dos dois acidentes até o hospital 40
            Dijkstra(nv, 82, Md, v1, v2); // Dos dois acidentes até o hospital 82
            Libera_Matriz(Md, nv);
            break;
        case 3:
        	system("cls");
        	Md = Ent_Grafo(Md, nomeArquivo);
            Imprime_Matriz(nv, Md);
            Libera_Matriz(Md, nv);
            break;
        	
        case 4:
        	 system("cls");
            cout << "Encerrando o programa..." << endl;
            break;
        default:
        	system("cls");
            cout << "Opção inválida! Tente novamente." << endl;
            break;
        }

    } while (opcao != 4);

    return 0;
}