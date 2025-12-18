#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================================================================
   PARTE 1 - DEFINICCO DAS ESTRUTURAS DE DADOS

   As structs sC#o estruturas que nos permitem agrupar dados relacionados.
   Aqui definimos trC*s structs principais: Livro, Usuario e Emprestimo.
   Cada struct representa uma entidade do nosso sistema.
============================================================================ */

// Estrutura para representar uma data (usada em vC!rias partes do sistema)
typedef struct {
	int dia;
	int mes;
	int ano;
} Data;

// Estrutura para armazenar informaC'C5es completas de um livro
typedef struct {
	int codigo;
	char titulo[100];
	char autor[80];
	char editora[60];
	int anoPublicacao;
	int exemplares;
	int exemplaresDiponiveis;  // Controla quantos estC#o disponC-veis para emprC)stimo
	char status[20];  // "disponivel" ou "emprestado"
} Livro;

// Estrutura para armazenar dados de usuC!rios da biblioteca
typedef struct {
	int matricula;
	char nome[100];
	char curso[50];
	char telefone[15];
	Data dataCadastro;
} Usuario;

// Estrutura para controlar os emprC)stimos realizados
typedef struct {
	int codigo;
	int matriculaUsuario;
	int codigoLivro;
	Data dataEmprestimo;
	Data dataDevolucao;
	char status[20];  // "ativo" ou "devolvido"
} Emprestimo;

/* ============================================================================
   DEFINICCO DE CONSTANTES E VARICVEIS GLOBAIS

   Constantes definem limites mC!ximos do sistema.
   Arrays globais armazenam os dados durante a execuC'C#o do programa.
============================================================================ */

#define MAX_LIVROS 100
#define MAX_USUARIOS 100
#define MAX_EMPRESTIMOS 200

// Arrays globais para armazenar os dados
Livro livros[MAX_LIVROS];
Usuario usuarios[MAX_USUARIOS];
Emprestimo emprestimos[MAX_EMPRESTIMOS];

// Contadores para saber quantos registros temos em cada array
int totalLivros = 0;
int totalUsuarios = 0;
int totalEmprestimos = 0;

/* ============================================================================
   PARTE 2 - FUNCCES AUXILIARES

   Estas funC'C5es ajudam em tarefas comuns como limpar a tela,
   pausar execuC'C#o, validar dados e trabalhar com datas.
============================================================================ */

// Limpa o buffer do teclado - evita problemas com scanf
void limparBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// Limpa a tela (funciona em Windows e alguns sistemas Unix)
void limparTela() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

// Pausa o programa e aguarda o usuC!rio pressionar Enter
void pausar() {
	printf("\nPressione ENTER para continuar...");
	limparBuffer();
	getchar();
}

// ObtC)m a data atual do sistema
Data obterDataAtual() {
	Data d;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	d.dia = tm.tm_mday;
	d.mes = tm.tm_mon + 1;
	d.ano = tm.tm_year + 1900;
	return d;
}

// Calcula a data de devoluC'C#o (7 dias apC3s o emprC)stimo)
Data calcularDataDevolucao(Data dataEmprestimo) {
	Data dataDevolucao = dataEmprestimo;
	dataDevolucao.dia += 7;

	// Tratamento simples para mudanC'a de mC*s (assume meses de 30 dias)
	if (dataDevolucao.dia > 30) {
		dataDevolucao.dia -= 30;
		dataDevolucao.mes++;
		if (dataDevolucao.mes > 12) {
			dataDevolucao.mes = 1;
			dataDevolucao.ano++;
		}
	}
	return dataDevolucao;
}

// Compara duas datas - retorna 1 se data1 > data2
int compararDatas(Data data1, Data data2) {
	if (data1.ano > data2.ano) return 1;
	if (data1.ano < data2.ano) return -1;
	if (data1.mes > data2.mes) return 1;
	if (data1.mes < data2.mes) return -1;
	if (data1.dia > data2.dia) return 1;
	if (data1.dia < data2.dia) return -1;
	return 0;
}

/* ============================================================================
   PARTE 3 - FUNCCES MODULARES PARA CADASTRO

   Cada funC'C#o abaixo C) responsC!vel por uma operaC'C#o especC-fica.
   Isso torna o cC3digo mais organizado e fC!cil de manter.
============================================================================ */

// FunC'C#o para cadastrar um novo livro no sistema
void cadastrarLivro() {
	limparTela();
	printf("=== CADASTRO DE LIVRO ===\n\n");

	if (totalLivros >= MAX_LIVROS) {
		printf("Erro: Limite de livros atingido!\n");
		pausar();
		return;
	}

	Livro novoLivro;

	printf("Codigo do livro: ");
	scanf("%d", &novoLivro.codigo);
	limparBuffer();

	// Verifica se o cC3digo jC! existe
	for (int i = 0; i < totalLivros; i++) {
		if (livros[i].codigo == novoLivro.codigo) {
			printf("Erro: Codigo ja cadastrado!\n");
			pausar();
			return;
		}
	}

	printf("Titulo: ");
	fgets(novoLivro.titulo, 100, stdin);
	novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = 0; // Remove o \n

	printf("Autor: ");
	fgets(novoLivro.autor, 80, stdin);
	novoLivro.autor[strcspn(novoLivro.autor, "\n")] = 0;

	printf("Editora: ");
	fgets(novoLivro.editora, 60, stdin);
	novoLivro.editora[strcspn(novoLivro.editora, "\n")] = 0;

	printf("Ano de publicacao: ");
	scanf("%d", &novoLivro.anoPublicacao);

	printf("Numero de exemplares: ");
	scanf("%d", &novoLivro.exemplares);

	novoLivro.exemplaresDiponiveis = novoLivro.exemplares;
	strcpy(novoLivro.status, "disponivel");

	livros[totalLivros] = novoLivro;
	totalLivros++;

	printf("\nLivro cadastrado com sucesso!\n");
	pausar();
}

// FunC'C#o para cadastrar um novo usuC!rio
void cadastrarUsuario() {
	limparTela();
	printf("=== CADASTRO DE USUARIO ===\n\n");

	if (totalUsuarios >= MAX_USUARIOS) {
		printf("Erro: Limite de usuarios atingido!\n");
		pausar();
		return;
	}

	Usuario novoUsuario;

	printf("Matricula: ");
	scanf("%d", &novoUsuario.matricula);
	limparBuffer();

	// Verifica se a matrC-cula jC! existe
	for (int i = 0; i < totalUsuarios; i++) {
		if (usuarios[i].matricula == novoUsuario.matricula) {
			printf("Erro: Matricula ja cadastrada!\n");
			pausar();
			return;
		}
	}

	printf("Nome completo: ");
	fgets(novoUsuario.nome, 100, stdin);
	novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = 0;

	printf("Curso: ");
	fgets(novoUsuario.curso, 50, stdin);
	novoUsuario.curso[strcspn(novoUsuario.curso, "\n")] = 0;

	printf("Telefone: ");
	fgets(novoUsuario.telefone, 15, stdin);
	novoUsuario.telefone[strcspn(novoUsuario.telefone, "\n")] = 0;

	novoUsuario.dataCadastro = obterDataAtual();

	usuarios[totalUsuarios] = novoUsuario;
	totalUsuarios++;

	printf("\nUsuario cadastrado com sucesso!\n");
	printf("Data de cadastro: %02d/%02d/%04d\n",
	       novoUsuario.dataCadastro.dia,
	       novoUsuario.dataCadastro.mes,
	       novoUsuario.dataCadastro.ano);
	pausar();
}

/* ============================================================================
   FUNCCES DE PESQUISA

   Estas funC'C5es permitem localizar livros e usuC!rios no sistema.
============================================================================ */

// Pesquisa livros por cC3digo, tC-tulo ou autor
void pesquisarLivro() {
	limparTela();
	printf("=== PESQUISAR LIVRO ===\n\n");
	printf("1. Pesquisar por codigo\n");
	printf("2. Pesquisar por titulo\n");
	printf("3. Pesquisar por autor\n");
	printf("Escolha uma opcao: ");

	int opcao;
	scanf("%d", &opcao);
	limparBuffer();

	int encontrado = 0;

	if (opcao == 1) {
		int codigo;
		printf("Digite o codigo: ");
		scanf("%d", &codigo);

		for (int i = 0; i < totalLivros; i++) {
			if (livros[i].codigo == codigo) {
				printf("\n--- LIVRO ENCONTRADO ---\n");
				printf("Codigo: %d\n", livros[i].codigo);
				printf("Titulo: %s\n", livros[i].titulo);
				printf("Autor: %s\n", livros[i].autor);
				printf("Editora: %s\n", livros[i].editora);
				printf("Ano: %d\n", livros[i].anoPublicacao);
				printf("Exemplares disponiveis: %d/%d\n",
				       livros[i].exemplaresDiponiveis, livros[i].exemplares);
				printf("Status: %s\n", livros[i].status);
				encontrado = 1;
				break;
			}
		}
	} else if (opcao == 2) {
		char titulo[100];
		printf("Digite o titulo (ou parte dele): ");
		fgets(titulo, 100, stdin);
		titulo[strcspn(titulo, "\n")] = 0;

		for (int i = 0; i < totalLivros; i++) {
			if (strstr(livros[i].titulo, titulo) != NULL) {
				printf("\n--- LIVRO ENCONTRADO ---\n");
				printf("Codigo: %d\n", livros[i].codigo);
				printf("Titulo: %s\n", livros[i].titulo);
				printf("Autor: %s\n", livros[i].autor);
				printf("Exemplares disponiveis: %d/%d\n",
				       livros[i].exemplaresDiponiveis, livros[i].exemplares);
				encontrado = 1;
			}
		}
	} else if (opcao == 3) {
		char autor[80];
		printf("Digite o autor (ou parte do nome): ");
		fgets(autor, 80, stdin);
		autor[strcspn(autor, "\n")] = 0;

		for (int i = 0; i < totalLivros; i++) {
			if (strstr(livros[i].autor, autor) != NULL) {
				printf("\n--- LIVRO ENCONTRADO ---\n");
				printf("Codigo: %d\n", livros[i].codigo);
				printf("Titulo: %s\n", livros[i].titulo);
				printf("Autor: %s\n", livros[i].autor);
				printf("Exemplares disponiveis: %d/%d\n",
				       livros[i].exemplaresDiponiveis, livros[i].exemplares);
				encontrado = 1;
			}
		}
	}

	if (!encontrado) {
		printf("\nNenhum livro encontrado.\n");
	}

	pausar();
}

// Pesquisa usuC!rios por matrC-cula ou nome
void pesquisarUsuario() {
	limparTela();
	printf("=== PESQUISAR USUARIO ===\n\n");
	printf("1. Pesquisar por matricula\n");
	printf("2. Pesquisar por nome\n");
	printf("Escolha uma opcao: ");

	int opcao;
	scanf("%d", &opcao);
	limparBuffer();

	int encontrado = 0;

	if (opcao == 1) {
		int matricula;
		printf("Digite a matricula: ");
		scanf("%d", &matricula);

		for (int i = 0; i < totalUsuarios; i++) {
			if (usuarios[i].matricula == matricula) {
				printf("\n--- USUARIO ENCONTRADO ---\n");
				printf("Matricula: %d\n", usuarios[i].matricula);
				printf("Nome: %s\n", usuarios[i].nome);
				printf("Curso: %s\n", usuarios[i].curso);
				printf("Telefone: %s\n", usuarios[i].telefone);
				printf("Data de cadastro: %02d/%02d/%04d\n",
				       usuarios[i].dataCadastro.dia,
				       usuarios[i].dataCadastro.mes,
				       usuarios[i].dataCadastro.ano);
				encontrado = 1;
				break;
			}
		}
	} else if (opcao == 2) {
		char nome[100];
		printf("Digite o nome (ou parte dele): ");
		fgets(nome, 100, stdin);
		nome[strcspn(nome, "\n")] = 0;

		for (int i = 0; i < totalUsuarios; i++) {
			if (strstr(usuarios[i].nome, nome) != NULL) {
				printf("\n--- USUARIO ENCONTRADO ---\n");
				printf("Matricula: %d\n", usuarios[i].matricula);
				printf("Nome: %s\n", usuarios[i].nome);
				printf("Curso: %s\n", usuarios[i].curso);
				encontrado = 1;
			}
		}
	}

	if (!encontrado) {
		printf("\nNenhum usuario encontrado.\n");
	}

	pausar();
}

/* ============================================================================
   SISTEMA DE EMPRC	STIMOS E DEVOLUCCES
============================================================================ */

// Realiza o emprC)stimo de um livro para um usuC!rio
void realizarEmprestimo() {
	limparTela();
	printf("=== REALIZAR EMPRESTIMO ===\n\n");

	if (totalEmprestimos >= MAX_EMPRESTIMOS) {
		printf("Erro: Limite de emprestimos atingido!\n");
		pausar();
		return;
	}

	int matricula, codigoLivro;
	int usuarioEncontrado = -1, livroEncontrado = -1;

	printf("Matricula do usuario: ");
	scanf("%d", &matricula);

	// Busca o usuC!rio
	for (int i = 0; i < totalUsuarios; i++) {
		if (usuarios[i].matricula == matricula) {
			usuarioEncontrado = i;
			break;
		}
	}

	if (usuarioEncontrado == -1) {
		printf("Erro: Usuario nao encontrado!\n");
		pausar();
		return;
	}

	printf("Codigo do livro: ");
	scanf("%d", &codigoLivro);

	// Busca o livro
	for (int i = 0; i < totalLivros; i++) {
		if (livros[i].codigo == codigoLivro) {
			livroEncontrado = i;
			break;
		}
	}

	if (livroEncontrado == -1) {
		printf("Erro: Livro nao encontrado!\n");
		pausar();
		return;
	}

	// Verifica disponibilidade
	if (livros[livroEncontrado].exemplaresDiponiveis <= 0) {
		printf("Erro: Nao ha exemplares disponiveis!\n");
		pausar();
		return;
	}

	// Cria o emprC)stimo
	Emprestimo novoEmprestimo;
	novoEmprestimo.codigo = totalEmprestimos + 1;
	novoEmprestimo.matriculaUsuario = matricula;
	novoEmprestimo.codigoLivro = codigoLivro;
	novoEmprestimo.dataEmprestimo = obterDataAtual();
	novoEmprestimo.dataDevolucao = calcularDataDevolucao(novoEmprestimo.dataEmprestimo);
	strcpy(novoEmprestimo.status, "ativo");

	emprestimos[totalEmprestimos] = novoEmprestimo;
	totalEmprestimos++;

	// Atualiza disponibilidade do livro
	livros[livroEncontrado].exemplaresDiponiveis--;
	if (livros[livroEncontrado].exemplaresDiponiveis == 0) {
		strcpy(livros[livroEncontrado].status, "emprestado");
	}

	printf("\nEmprestimo realizado com sucesso!\n");
	printf("Codigo do emprestimo: %d\n", novoEmprestimo.codigo);
	printf("Data de devolucao: %02d/%02d/%04d\n",
	       novoEmprestimo.dataDevolucao.dia,
	       novoEmprestimo.dataDevolucao.mes,
	       novoEmprestimo.dataDevolucao.ano);
	pausar();
}

// Realiza a devoluC'C#o de um livro emprestado
void realizarDevolucao() {
	limparTela();
	printf("=== REALIZAR DEVOLUCAO ===\n\n");

	int codigo;
	printf("Codigo do emprestimo: ");
	scanf("%d", &codigo);

	int emprestimoEncontrado = -1;

	for (int i = 0; i < totalEmprestimos; i++) {
		if (emprestimos[i].codigo == codigo &&
		        strcmp(emprestimos[i].status, "ativo") == 0) {
			emprestimoEncontrado = i;
			break;
		}
	}

	if (emprestimoEncontrado == -1) {
		printf("Erro: Emprestimo nao encontrado ou ja devolvido!\n");
		pausar();
		return;
	}

	// Atualiza o status do emprC)stimo
	strcpy(emprestimos[emprestimoEncontrado].status, "devolvido");

	// Encontra o livro e atualiza disponibilidade
	int codigoLivro = emprestimos[emprestimoEncontrado].codigoLivro;
	for (int i = 0; i < totalLivros; i++) {
		if (livros[i].codigo == codigoLivro) {
			livros[i].exemplaresDiponiveis++;
			if (livros[i].exemplaresDiponiveis > 0) {
				strcpy(livros[i].status, "disponivel");
			}
			break;
		}
	}

	// Verifica se houve atraso
	Data dataAtual = obterDataAtual();
	if (compararDatas(dataAtual, emprestimos[emprestimoEncontrado].dataDevolucao) > 0) {
		printf("\nATENCAO: Devolucao com atraso!\n");
	}

	printf("\nDevolucao realizada com sucesso!\n");
	pausar();
}

// Lista todos os emprC)stimos ativos
void listarEmprestimosAtivos() {
	limparTela();
	printf("=== EMPRESTIMOS ATIVOS ===\n\n");

	int encontrou = 0;

	for (int i = 0; i < totalEmprestimos; i++) {
		if (strcmp(emprestimos[i].status, "ativo") == 0) {
			printf("Codigo: %d\n", emprestimos[i].codigo);
			printf("Matricula Usuario: %d\n", emprestimos[i].matriculaUsuario);
			printf("Codigo Livro: %d\n", emprestimos[i].codigoLivro);
			printf("Data Emprestimo: %02d/%02d/%04d\n",
			       emprestimos[i].dataEmprestimo.dia,
			       emprestimos[i].dataEmprestimo.mes,
			       emprestimos[i].dataEmprestimo.ano);
			printf("Data Devolucao: %02d/%02d/%04d\n",
			       emprestimos[i].dataDevolucao.dia,
			       emprestimos[i].dataDevolucao.mes,
			       emprestimos[i].dataDevolucao.ano);
			printf("------------------------\n");
			encontrou = 1;
		}
	}

	if (!encontrou) {
		printf("Nenhum emprestimo ativo no momento.\n");
	}

	pausar();
}

/* ============================================================================
   PARTE 4 - MANIPULACCO DE ARQUIVOS

   Estas funC'C5es salvam e carregam dados dos arquivos.
   Isso permite que os dados persistam entre execuC'C5es do programa.
============================================================================ */

// Salva todos os livros no arquivo livros.txt
void salvarLivros() {
	FILE *arquivo = fopen("livros.txt", "w");
	if (arquivo == NULL) {
		printf("Erro ao abrir arquivo livros.txt\n");
		return;
	}

	fprintf(arquivo, "%d\n", totalLivros);
	for (int i = 0; i < totalLivros; i++) {
		fprintf(arquivo, "%d\n%s\n%s\n%s\n%d\n%d\n%d\n%s\n",
		        livros[i].codigo,
		        livros[i].titulo,
		        livros[i].autor,
		        livros[i].editora,
		        livros[i].anoPublicacao,
		        livros[i].exemplares,
		        livros[i].exemplaresDiponiveis,
		        livros[i].status);
	}

	fclose(arquivo);
}

// Carrega livros do arquivo livros.txt
void carregarLivros() {
	FILE *arquivo = fopen("livros.txt", "r");
	if (arquivo == NULL) {
		return; // Arquivo nC#o existe ainda
	}

	fscanf(arquivo, "%d\n", &totalLivros);
	for (int i = 0; i < totalLivros; i++) {
		fscanf(arquivo, "%d\n", &livros[i].codigo);
		fgets(livros[i].titulo, 100, arquivo);
		livros[i].titulo[strcspn(livros[i].titulo, "\n")] = 0;
		fgets(livros[i].autor, 80, arquivo);
		livros[i].autor[strcspn(livros[i].autor, "\n")] = 0;
		fgets(livros[i].editora, 60, arquivo);
		livros[i].editora[strcspn(livros[i].editora, "\n")] = 0;
		fscanf(arquivo, "%d\n%d\n%d\n",
		       &livros[i].anoPublicacao,
		       &livros[i].exemplares,
		       &livros[i].exemplaresDiponiveis);
		fgets(livros[i].status, 20, arquivo);
		livros[i].status[strcspn(livros[i].status, "\n")] = 0;
	}

	fclose(arquivo);
}

// Salva todos os usuC!rios no arquivo usuarios.txt
void salvarUsuarios() {
	FILE *arquivo = fopen("usuarios.txt", "w");
	if (arquivo == NULL) {
		printf("Erro ao abrir arquivo usuarios.txt\n");
		return;
	}

	fprintf(arquivo, "%d\n", totalUsuarios);
	for (int i = 0; i < totalUsuarios; i++) {
		fprintf(arquivo, "%d\n%s\n%s\n%s\n%d %d %d\n",
		        usuarios[i].matricula,
		        usuarios[i].nome,
		        usuarios[i].curso,
		        usuarios[i].telefone,
		        usuarios[i].dataCadastro.dia,
		        usuarios[i].dataCadastro.mes,
		        usuarios[i].dataCadastro.ano);
	}

	fclose(arquivo);
}

// Carrega usuC!rios do arquivo usuarios.txt
void carregarUsuarios() {
	FILE *arquivo = fopen("usuarios.txt", "r");
	if (arquivo == NULL) {
		return;
	}

	fscanf(arquivo, "%d\n", &totalUsuarios);
	for (int i = 0; i < totalUsuarios; i++) {
		fscanf(arquivo, "%d\n", &usuarios[i].matricula);
		fgets(usuarios[i].nome, 100, arquivo);
		usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = 0;
		fgets(usuarios[i].curso, 50, arquivo);
		usuarios[i].curso[strcspn(usuarios[i].curso, "\n")] = 0;
		fgets(usuarios[i].telefone, 15, arquivo);
		usuarios[i].telefone[strcspn(usuarios[i].telefone, "\n")] = 0;
		fscanf(arquivo, "%d %d %d\n",
		       &usuarios[i].dataCadastro.dia,
		       &usuarios[i].dataCadastro.mes,
		       &usuarios[i].dataCadastro.ano);
	}

	fclose(arquivo);
}

// Salva todos os emprC)stimos no arquivo emprestimos.txt
void salvarEmprestimos() {
	FILE *arquivo = fopen("emprestimos.txt", "w");
	if (arquivo == NULL) {
		printf("Erro ao abrir arquivo emprestimos.txt\n");
		return;
	}

	fprintf(arquivo, "%d\n", totalEmprestimos);
	for (int i = 0; i < totalEmprestimos; i++) {
		fprintf(arquivo, "%d\n%d\n%d\n%d %d %d\n%d %d %d\n%s\n",
		        emprestimos[i].codigo,
		        emprestimos[i].matriculaUsuario,
		        emprestimos[i].codigoLivro,
		        emprestimos[i].dataEmprestimo.dia,
		        emprestimos[i].dataEmprestimo.mes,
		        emprestimos[i].dataEmprestimo.ano,
		        emprestimos[i].dataDevolucao.dia,
		        emprestimos[i].dataDevolucao.mes,
		        emprestimos[i].dataDevolucao.ano,
		        emprestimos[i].status);
	}

	fclose(arquivo);
}

// Carrega emprC)stimos do arquivo emprestimos.txt
void carregarEmprestimos() {
	FILE *arquivo = fopen("emprestimos.txt", "r");
	if (arquivo == NULL) {
		return;
	}

	fscanf(arquivo, "%d\n", &totalEmprestimos);
	for (int i = 0; i < totalEmprestimos; i++) {
		fscanf(arquivo, "%d\n%d\n%d\n%d %d %d\n%d %d %d\n",
		       &emprestimos[i].codigo,
		       &emprestimos[i].matriculaUsuario,
		       &emprestimos[i].codigoLivro,
		       &emprestimos[i].dataEmprestimo.dia,
		       &emprestimos[i].dataEmprestimo.mes,
		       &emprestimos[i].dataEmprestimo.ano,
		       &emprestimos[i].dataDevolucao.dia,
		       &emprestimos[i].dataDevolucao.mes,
		       &emprestimos[i].dataDevolucao.ano);
		fgets(emprestimos[i].status, 20, arquivo);
		emprestimos[i].status[strcspn(emprestimos[i].status, "\n")] = 0;
	}

	fclose(arquivo);
}

// Salva todos os dados (backup automC!tico)
void salvarTodosDados() {
	salvarLivros();
	salvarUsuarios();
	salvarEmprestimos();
}

/* ============================================================================
   PARTE 5 - FUNCIONALIDADES AVANCADAS
============================================================================ */

// Gera relatC3rio dos livros mais emprestados
void relatorioLivrosMaisEmprestados() {
	limparTela();
	printf("=== RELATORIO: LIVROS MAIS EMPRESTADOS ===\n\n");

	// Array para contar emprC)stimos por livro
	int contadores[MAX_LIVROS] = {0};

	for (int i = 0; i < totalEmprestimos; i++) {
		for (int j = 0; j < totalLivros; j++) {
			if (emprestimos[i].codigoLivro == livros[j].codigo) {
				contadores[j]++;
				break;
			}
		}
	}

	// OrdenaC'C#o simples por quantidade de emprC)stimos
	for (int i = 0; i < totalLivros - 1; i++) {
		for (int j = i + 1; j < totalLivros; j++) {
			if (contadores[j] > contadores[i]) {
				int tempCont = contadores[i];
				contadores[i] = contadores[j];
				contadores[j] = tempCont;

				Livro tempLivro = livros[i];
				livros[i] = livros[j];
				livros[j] = tempLivro;
			}
		}
	}

	printf("Top 10 livros mais emprestados:\n\n");
	int limite = (totalLivros < 10) ? totalLivros : 10;
	for (int i = 0; i < limite; i++) {
		if (contadores[i] > 0) {
			printf("%d. %s - %d emprestimos\n",
			       i + 1, livros[i].titulo, contadores[i]);
		}
	}

	pausar();
}

// Gera relatC3rio de usuC!rios com emprC)stimos em atraso
void relatorioEmprestimosAtrasados() {
	limparTela();
	printf("=== RELATORIO: EMPRESTIMOS EM ATRASO ===\n\n");

	Data dataAtual = obterDataAtual();
	int encontrou = 0;

	for (int i = 0; i < totalEmprestimos; i++) {
		if (strcmp(emprestimos[i].status, "ativo") == 0) {
			if (compararDatas(dataAtual, emprestimos[i].dataDevolucao) > 0) {
				printf("Codigo Emprestimo: %d\n", emprestimos[i].codigo);
				printf("Matricula Usuario: %d\n", emprestimos[i].matriculaUsuario);

				// Busca nome do usuC!rio
				for (int j = 0; j < totalUsuarios; j++) {
					if (usuarios[j].matricula == emprestimos[i].matriculaUsuario) {
						printf("Nome: %s\n", usuarios[j].nome);
						break;
					}
				}

				printf("Codigo Livro: %d\n", emprestimos[i].codigoLivro);
				printf("Data Devolucao: %02d/%02d/%04d\n",
				       emprestimos[i].dataDevolucao.dia,
				       emprestimos[i].dataDevolucao.mes,
				       emprestimos[i].dataDevolucao.ano);
				printf("------------------------\n");
				encontrou = 1;
			}
		}
	}

	if (!encontrou) {
		printf("Nenhum emprestimo em atraso.\n");
	}

	pausar();
}

// RenovaC'C#o de emprC)stimo (estende prazo por mais 7 dias)
void renovarEmprestimo() {
	limparTela();
	printf("=== RENOVAR EMPRESTIMO ===\n\n");

	int codigo;
	printf("Codigo do emprestimo: ");
	scanf("%d", &codigo);

	int emprestimoEncontrado = -1;

	for (int i = 0; i < totalEmprestimos; i++) {
		if (emprestimos[i].codigo == codigo &&
		        strcmp(emprestimos[i].status, "ativo") == 0) {
			emprestimoEncontrado = i;
			break;
		}
	}

	if (emprestimoEncontrado == -1) {
		printf("Erro: Emprestimo nao encontrado ou ja devolvido!\n");
		pausar();
		return;
	}

	// Verifica se jC! estC! atrasado
	Data dataAtual = obterDataAtual();
	if (compararDatas(dataAtual, emprestimos[emprestimoEncontrado].dataDevolucao) > 0) {
		printf("Erro: Nao e possivel renovar emprestimos em atraso!\n");
		pausar();
		return;
	}

	// Estende a data de devoluC'C#o
	emprestimos[emprestimoEncontrado].dataDevolucao =
	    calcularDataDevolucao(emprestimos[emprestimoEncontrado].dataDevolucao);

	printf("\nEmprestimo renovado com sucesso!\n");
	printf("Nova data de devolucao: %02d/%02d/%04d\n",
	       emprestimos[emprestimoEncontrado].dataDevolucao.dia,
	       emprestimos[emprestimoEncontrado].dataDevolucao.mes,
	       emprestimos[emprestimoEncontrado].dataDevolucao.ano);
	pausar();
}

/* ============================================================================
   PARTE 2 - SISTEMA DE MENUS

   As funC'C5es de menu organizam a interface do usuC!rio.
============================================================================ */

// Menu de relatC3rios
void menuRelatorios() {
	int opcao;
	do {
		limparTela();
		printf("=== RELATORIOS ===\n\n");
		printf("1. Livros mais emprestados\n");
		printf("2. Emprestimos em atraso\n");
		printf("0. Voltar\n");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);

		switch(opcao) {
		case 1:
			relatorioLivrosMaisEmprestados();
			break;
		case 2:
			relatorioEmprestimosAtrasados();
			break;
		case 0:
			break;
		default:
			printf("Opcao invalida!\n");
			pausar();
		}
	} while(opcao != 0);
}

// Menu principal do sistema
void menuPrincipal() {
	int opcao;

	do {
		limparTela();
		printf("========================================\n");
		printf("  SISTEMA DE GERENCIAMENTO DE BIBLIOTECA\n");
		printf("========================================\n\n");
		printf("1. Cadastrar Livro\n");
		printf("2. Cadastrar Usuario\n");
		printf("3. Realizar Emprestimo\n");
		printf("4. Realizar Devolucao\n");
		printf("5. Pesquisar Livro\n");
		printf("6. Pesquisar Usuario\n");
		printf("7. Listar Emprestimos Ativos\n");
		printf("8. Renovar Emprestimo\n");
		printf("9. Relatorios\n");
		printf("0. Sair\n");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);

		switch(opcao) {
		case 1:
			cadastrarLivro();
			salvarTodosDados();
			break;
		case 2:
			cadastrarUsuario();
			salvarTodosDados();
			break;
		case 3:
			realizarEmprestimo();
			salvarTodosDados();
			break;
		case 4:
			realizarDevolucao();
			salvarTodosDados();
			break;
		case 5:
			pesquisarLivro();
			break;
		case 6:
			pesquisarUsuario();
			break;
		case 7:
			listarEmprestimosAtivos();
			break;
		case 8:
			renovarEmprestimo();
			salvarTodosDados();
			break;
		case 9:
			menuRelatorios();
			break;
		case 0:
			printf("\nSalvando dados...\n");
			salvarTodosDados();
			printf("Sistema finalizado. Ate logo!\n");
			break;
		default:
			printf("Opcao invalida!\n");
			pausar();
		}
	} while(opcao != 0);
}

/* ============================================================================
   FUNCCO PRINCIPAL (MAIN)

   Ponto de entrada do programa. Carrega dados e inicia o sistema.
============================================================================ */

int main() {
	printf("Iniciando sistema...\n");
	printf("Carregando dados...\n");

	carregarLivros();
	carregarUsuarios();
	carregarEmprestimos();

	printf("Dados carregados com sucesso!\n");
	pausar();

	menuPrincipal();

	return 0;
}