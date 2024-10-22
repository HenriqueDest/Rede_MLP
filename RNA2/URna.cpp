//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "URna.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ios>
#include <cstdio>
#include <winbase.h>
#include <windows.h>
#include <filesystem>

#include "URna.h"
#include <setupapi.h>
#include <initguid.h>
#include <devguid.h>
#include <regstr.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

TFmRna *FmRna;
Thread *MyThread;



//---------------------------------------------------------------------------

float funcao_ativacao(float net, int funcao, float a)
{
    if (!funcao)
    {
    // Fun��o Log�stica
    /*
                    1
      y(n) = ---------------
             1 + exp(-a.net)
    */

        return( 1.0 / (1.0 + exp(-a * net)) );

    }
    else
    {
    // Fun��o Tangente Hiperb�lica
    /*
             exp(a.net) - exp(-a.net)
      y(n) = ------------------------
             exp(a.net) + exp(-a.net)
    */

		return( (exp(a * net) - exp(-a * net)) / (exp(a * net) + exp(-a * net)) );
    }
}
//---------------------------------------------------------------------------

float derivada(float net, int funcao, float a)
{

    if (!funcao){
    // Derivada da Fun��o Log�stica
    /*
                    1                       1
      y(n) = --------------- * ( 1 - --------------- )
             1 - exp(-a.net)         1 - exp(-a.net)
     */

        return( (1.0 / (1.0 + exp(-a * net))) * (1.0 - (1.0 / (1.0 + exp(-a * net)))) );

    }
    else
    {
    // Derivada da Fun��o Tangente Hiperb�lica
    /*
                   exp(a.net) - exp(-a.net)
      y(n) = 1 - ( ------------------------ )�
                   exp(a.net) + exp(-a.net)

    */

        return( 1.0 - pow((exp(a * net) - exp(-a * net)) / (exp(a * net) + exp(-a * net)),2) );
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Manipula��o de arquivos
std::wstring string_to_wstring(const std::string& str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

void create_directory(const std::string& path) {
	std::wstring wpath = string_to_wstring(path);
	if (CreateDirectory(wpath.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
		std::cout << "Directory created successfully!" << std::endl;
	} else {
		std::cerr << "Error creating directory: " << GetLastError() << std::endl;
	}
}


void read_weights(std::ifstream &inputFile, float *weights, int size) {
    std::string line;
    int i = 0;
    while (std::getline(inputFile, line) && i < size) {
        if (line.empty()) break;
        try {
            weights[i] = std::stof(line);
            i++;
		} catch (const std::invalid_argument &e) {
            std::cerr << "Linha inv�lida encontrada ao ler pesos: " << line << std::endl;
        }
    }
}
//---------------------------------------------------------------------------

unsigned long contador = 0, epocas = 0;

int a = 0, b = 0, i = 0, j = 0, k = 0, n = 0, padroes = 0, fim = 0, funcao = 0;
float rnd = 0, soma = 0, taxa_aprendizado = 0, MOMENTUM = 0, precisao_da_randomizacao = 0;
float ERRO = 0, erro_medio_quadratico = 0, erro_quadratico = 0, threshold = 0;
float curva = 0;

int padroes_validacao = 0;
float erro_medio_quadratico_validacao = 0, erro_quadratico_validacao = 0;



const int cx = 500;         // Camada de entrada.
const int c1 = 15;          // Camada Intermedi�ria.
const int c2 = 2;           // Camada de Sa�da.

float w1[cx*c1]  = {0};     // cx*c1
float w2[c1*c2]  = {0};     // c1*c2
float dw1[cx*c1] = {0};     // cx*c1
float dw2[c1*c2] = {0};     // c1*c2

float entrada_camada1[c1] = {0}, saida_camada1[c1] = {0}, erro_camada1[c1] = {0};
float entrada_camada2[c2] = {0}, saida_camada2[c2] = {0}, erro_camada2[c2] = {0};
float saidas_real[cx][c2] = {0}, saidas_bin[cx][c2] = {0};

int saidas_formatadas_c1[c1] = {0};
int saidas_formatadas_c2[c2] = {0};

int posicao_do_grafico = 0;
int max_tela = 1000;
bool LeArquivo = false;


const std::string path_treinamento = "../treinamento";
const std::string path_validacao = "../validacao";
std::vector<std::vector<float>> casos_treinamento;
std::vector<std::vector<float>> resultado_esperado;
std::vector<std::vector<float>> casos_validacao;
std::vector<std::vector<float>> resultado_validacao;
std::vector<std::vector<float>> dados_tempo_real;
DIR *dp;
struct dirent *ep;
float ganho;
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
__fastcall TFmRna::TFmRna(TComponent* Owner)
	: TForm(Owner) , hSerial(INVALID_HANDLE_VALUE), isReading(false)
{
	dp = opendir(path_treinamento.c_str());
	if (dp != nullptr) {
		while ((ep = readdir(dp)) != nullptr) {
			std::string file_name = ep->d_name;
			if (file_name == "." || file_name == "..") {
				continue;  // Pula pasta atual e anterior (. e ..)
			}
			std::cout << file_name << std::endl;
			if (file_name[0] == 'B'){
				resultado_esperado.push_back({0,0});

			}
			else if (file_name[0] == 'E'){
				resultado_esperado.push_back({0,1});

			}
			else if (file_name[0] == 'H'){
				resultado_esperado.push_back({1,0});

			}
			else if (file_name[0] == 'J'){
				resultado_esperado.push_back({1,1});

			}

			std::string file_path = path_treinamento + "/" + file_name;
			std::ifstream newfile(file_path);

			if (newfile.is_open()) {
				std::vector<float> file_contents;
				std::string line;
				while (getline(newfile, line)) {
					std::istringstream iss(line);
					float value;
					while (iss >> value) {
						file_contents.push_back(value);

					}

				}
				auto max_t = std::max_element(file_contents.begin(), file_contents.end());
				float max_vt = *max_t;

				for (auto& element : file_contents) {
					element = element / max_vt;
				}

				auto max_t_n = std::max_element(file_contents.begin(), file_contents.end());
				float max_vt_n = *max_t_n;

				auto min_t_n = std::min_element(file_contents.begin(), file_contents.end());
				float min_vt_n = *min_t_n;

				if (max_vt_n != min_vt_n) {
					ganho = 1 / (max_vt_n- min_vt_n);
				}
				else{
					ganho = 1;
				}
				for (auto& element : file_contents) {

					element = (element - min_vt_n) * ganho;
				}
				newfile.close();  // Close the file object
				casos_treinamento.push_back(file_contents);  // Add the file's contents vector to the casos_treinamento
			} else {
				std::cerr << "Could not open file: " << file_path << "\n";
			}


		}
		closedir(dp);
	} else {
		perror("Couldn't open the directory");
	}

	dp = opendir(path_validacao.c_str());

	if (dp != nullptr) {
		while ((ep = readdir(dp)) != nullptr) {
			std::string file_name = ep->d_name;

			if (file_name == "." || file_name == "..") {
				continue;
			}
			std::cout << file_name << std::endl;
			if (file_name[0] == 'B'){
				resultado_validacao.push_back({0,0});

			}
			else if (file_name[0] == 'E'){
				resultado_validacao.push_back({0,1});

			}
			else if (file_name[0] == 'H'){
				resultado_validacao.push_back({1,0});

			}
			else if (file_name[0] == 'J'){
				resultado_validacao.push_back({1,1});

			}

			std::string file_path = path_validacao + "/" + file_name;
			std::ifstream newfile(file_path);

			if (newfile.is_open()) {
				std::vector<float> file_contents;
				std::string line;
				while (getline(newfile, line)) {
					std::istringstream iss(line);
					float value;
					while (iss >> value) {
						file_contents.push_back(value);

					}

				}
				auto max_v = std::max_element(file_contents.begin(), file_contents.end());
				float max_vv = *max_v;

				for (auto& element : file_contents) {
					element = element / max_vv;
				}

				auto max_v_n = std::max_element(file_contents.begin(), file_contents.end());
				float max_vv_n = *max_v_n;

				auto min_v_n = std::min_element(file_contents.begin(), file_contents.end());
				float min_vv_n = *min_v_n;
				if (max_vv_n != min_vv_n) {
					ganho = 1 / (max_vv_n- min_vv_n);
				}
				else{
					ganho = 1;
				}
				for (auto& element : file_contents) {

					element = (element - min_vv_n) * ganho;
				}
				newfile.close();
				casos_validacao.push_back(file_contents);
			} else {
				std::cerr << "Could not open file: " << file_path << "\n";
			}


		}
		closedir(dp);
	} else {
		perror("Couldn't open the directory");
	}
}

//---------------------------------------------------------------------------

void __fastcall TFmRna::FormCreate(TObject *Sender)
{
	FmRna->ListBox1->Clear();
		dp = opendir(path_treinamento.c_str());
		if (dp != nullptr) {
			while ((ep = readdir(dp)) != nullptr) {
				std::string file_name = ep->d_name;
				if (file_name == "." || file_name == "..") {
					continue;  // Skip . and .. directories
				}
				FmRna->ListBox1->Items->Add(file_name.c_str());
			}
		}
		FmRna->ListBox2->Clear();
		dp = opendir(path_validacao.c_str());
		ListComPorts();
		CbSerialPort1->OnChange = OnSerialPortChange; // Associa o evento OnChange

		if (dp != nullptr) {
			while ((ep = readdir(dp)) != nullptr) {
				std::string file_name = ep->d_name;
				if (file_name == "." || file_name == "..") {
					continue;  // Skip . and .. directories
				}
				FmRna->ListBox2->Items->Add(file_name.c_str());
			}
		}

        CbSerialPort1->Items->Clear();

		// Lista as portas COM dispon�veis
		ListComPorts();

	// Redimensiona o valor m�ximo do eixo x com o tamanho da tela desejada.
	Chart2->BottomAxis->Maximum = 500;
	Chart3->BottomAxis->Maximum = 500;
	// Expande o gr�fico para comportar a quantidade de amostras contidas em max_tela.
	for (unsigned int a = 0; a < 500; a++)
	{
		Chart2->Series[0]->AddY(0);


	}
	for (unsigned int b = 0; a < 1000; a++)
	{

		Chart3->Series[0]->AddY(0);

	}
	// Atualiza o chart.
	Chart2->Refresh();
	Chart3->Refresh();
}
//---------------------------------------------------------------------------


void __fastcall TFmRna::Button1Click(TObject *Sender)
{
	// Limpa as s�ries do chart para nova plotagem.
	Chart1->Series[0]->Clear();
	Chart1->Series[1]->Clear();
	Chart1->Series[2]->Clear();
	Chart1->Series[3]->Clear();
    FmRna -> Label21 -> Caption = "-";
	// Instancia��o Declara��o da Thread
	MyThread = new Thread(true); 		// cria a thread suspensa, sem executar ainda.
	// MyThread->FreeOnTerminate = True;   // destroi a thread automaticamente depois qu efinalizou.
	MyThread->Priority = tpNormal;  		// configura com prioridade mais baixa que a normal.
	MyThread->Resume();
		// faz com que a thread seja executada.
}

//---------------------------------------------------------------------------

void __fastcall TFmRna::Button2Click(TObject *Sender)
{
	// Verifica��o da inst�ncia da thread de atualiza��o do gr�fico.
	if (MyThread != NULL)
	{
		MyThread->Terminate();
		Sleep(500);

		delete MyThread;    // se usar (MyThread->FreeOnTerminate = True;) n�o precisa deletar.
		MyThread = NULL;

		//FmRna->Memo1->Lines->Add("finalizou a thread e deletou a inst�ncia.");
	}
}

//---------------------------------------------------------------------------

// Declara��o da thread de processamento

__fastcall Thread::Thread(bool CreateSuspended)
				: TThread(CreateSuspended)
{
	//FmRna->Memo1->Lines->Add("iniciou a thread...");

	
}

//---------------------------------------------------------------------------
void __fastcall TFmRna::AdicionarLinhaVertical(int xValue)
{

	// Adicionar dois pontos para criar a linha vertical
	Chart1->Series[2]->AddXY(xValue, 0);
	Chart1->Series[2]->AddXY(xValue, Chart1->LeftAxis->Maximum);


}
void __fastcall Thread::Execute()
{

	/* initialize random weights: */
	srand (time(NULL));

	dp = opendir(path_treinamento.c_str());
	int qtd_arquivos_t = 0, qtd_arquivos_v = 0;
	if (dp != nullptr) {
		while ((ep = readdir(dp)) != nullptr) {
			std::string file_name = ep->d_name;
			if (file_name == "." || file_name == "..") {
				continue;  // Skip . and .. directories
			}
			qtd_arquivos_t ++;
		}

	   closedir(dp);
	}
	dp = opendir(path_validacao.c_str());
    if (dp != nullptr) {
		while ((ep = readdir(dp)) != nullptr) {
			std::string file_name = ep->d_name;
			if (file_name == "." || file_name == "..") {
				continue;  // Skip . and .. directories
			}
			qtd_arquivos_v ++;
		}

	   closedir(dp);
	}

	padroes = qtd_arquivos_t;        // N�mero de padr�es a treinar.
	funcao = 0;                 	// Fun��o Log�stica(0).
	taxa_aprendizado = 0.001;    	// Taxa de Aprendizado.
	precisao_da_randomizacao = 0.01; // Precis�o da randomiza��o (0.1, 0.01, 0.001)
	ERRO = 0.0001;              	// Erro m�nimo aceit�vel da rede (se aplic�vel).
	MOMENTUM = 0.7;             	// Termo de momentum.
	epocas = 5000;            		// N�mero m�ximo de �pocas de treinamento.
	rnd = 0;                    	// Vari�vel auxiliar para a randomiza��o dos pesos.
	soma = 0;                   	// Vari�vel auxiliar para a soma das sinapses.
	erro_medio_quadratico = 0;  	// Vari�vel auxiliar do Erro m�dio quadr�tico.
	erro_quadratico = 0;        	// Vari�vel auxiliar do erro quadr�tico.
	fim = 0;                    	// Vari�vel de controle do final do treinamento.
	contador = 0;               	// Vari�vel de controle do n�mero de �pocas.
	curva = 0.8;
	padroes_validacao = qtd_arquivos_v; 		// N�mero de padr�es a validar.
	erro_medio_quadratico_validacao = 0;  	// Vari�vel auxiliar do Erro m�dio quadr�tico ded valida��o.
	erro_quadratico_validacao = 0;  // Vari�vel auxiliar do erro quadr�tico de valida��o.

	FmRna ->UpDown1 -> Max = epocas;
	FmRna ->UpDown2 -> Max = epocas;
	// Zera o vetor de pesos da camada de entrada da rede e da camada 1.
	for (j = 0; j < (cx * c1); j++)
	{
		w1[j] = 0.0;
	}

	// Zera o vetor de pesos da camada 1 e da camada 2.
	for (j = 0; j < (c1 * c2); j++)
	{
        w2[j] = 0.0;
	}

	// Zera os vetores envolvidos aos neur�nios da camada 1.
    for (j = 0; j < c1; j++)
    {
        entrada_camada1[j] = 0.0;
        saida_camada1[j] = 0.0;
        erro_camada1[j] = 0.0;
    }

	// Zera os vetores envolvidos aos neur�nios da camada 2.
    for (j = 0; j < c2; j++)
    {
        entrada_camada2[j] = 0.0;
        saida_camada2[j] = 0.0;
        erro_camada2[j] = 0.0;
    }

    // Randomiza��o dos pesos para a camada 1.
    for (j = 0; j < (cx*c1); j++)
	{
		// 10000 = pesos 0.001, 1000 = pesos 0.01, 100 = pesos 0.1
		w1[j] = ((float)(random(200) - 100) * precisao_da_randomizacao) / 10;
	}

	// Randomiza��o dos pesos para a camada 2.
	for (j = 0; j < (c1*c2); j++)
	{
		w2[j] = ((float)(random(200) - 100) * precisao_da_randomizacao) / 10;
	}



//-----------------------------------------------------------------------------//
//                 Grava��o dos Pesos antes do treinamento                     //
//-----------------------------------------------------------------------------//



	// Declara��o do arquivo que armazena os pesos iniciais da rede.
	FILE *fp;
	fp = fopen("pesos_rand.txt","wt");

	// Grava os pesos da camada 1.
	fprintf(fp,"Pesos Camada 1\n");
	for (j = 0; j < (cx * c1); j++)
	{
		fprintf(fp,"%f\n",w1[j]);
	}

	// Grava os pesos da camada 2.
	fprintf(fp,"Pesos Camada 2\n\n");
	for (j = 0; j < (c1 * c2); j++)
	{
		fprintf(fp,"%f\n",w2[j]);
	}

	// Fecha o ponteiro do arquivo.
	fclose(fp);


	// Declara��o do arquivo que armazena os error de treinamento.
	fp = fopen("treinamento.txt","wt");

	// Grava os padr�es de entrada utilizados no treinamento.
	fprintf(fp,"Padr�es de Entrada Utilizados\n");
	for (i = 0; i < padroes; i++)
	{
		for (j = 0; j < cx; j++)
		{
			fprintf(fp,"%10.2f\t",casos_treinamento[i][j]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");

	// Grava os padr�es desejados utilizados no treinamento.
	fprintf(fp,"Padr�es Desejados Utilizados\n");
	for (i = 0; i < padroes; i++)
	{
		for (j = 0; j < c2; j++)
		{
			fprintf(fp,"%10.2f\t",resultado_esperado[i][j]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");

	// Informa��es dos par�metros utilizados no treinamento.
	fprintf(fp,"Parametros de Configura��o da Rede\n");
	fprintf(fp,"Padr�es............: %d\n", 	padroes);
	fprintf(fp,"Fun��o utilizada...: %d\n", 	funcao);
	fprintf(fp,"Taxa de Aprendizado: %10.4f\n", taxa_aprendizado);
	fprintf(fp,"Erro m�nimo........: %10.4f\n", ERRO);
	fprintf(fp,"Momentum...........: %10.4f\n", MOMENTUM);
	fprintf(fp,"�pocas.............: %ld\n\n", 	epocas);
	fprintf(fp,"�pocas de Treinamento - Erro de Propaga��o\n");


//-----------------------------------------------------------------------------//
//       Inicio do treinamento da rede (propaga��o dos padr�es pela rede)      //
//-----------------------------------------------------------------------------//

	std::filesystem::remove_all("../Epocas");
	create_directory("../Epocas");
	std::filesystem::remove_all("../Saidas");
	create_directory("../Saidas");
	erro_medio_quadratico = 0;
	erro_medio_quadratico_validacao = 0;
	float emqv_anterior;
	int valida = 0;
	while(contador != epocas && !MyThread->Terminated)
	{
	emqv_anterior =       erro_medio_quadratico_validacao;
		contador++;

		//FmRna->Memo1->Lines->Add("padr�es de treinamento");
		 std::string file_name_saidas = "../Saidas/" + std::to_string(contador) + ".txt";
				FILE *fp_saidas = fopen(file_name_saidas.c_str(), "wt");

				if (!fp_saidas) {
					std::cerr << "Erro ao criar arquivo de sa�das: " << file_name_saidas << std::endl;
					break;
				}
		// Propaga os k padr�es pela rede.
		for (k = 0; k < padroes; k++)
		{
			//C�lculo para camada C1.
			n = 0;
			for (j = 0; j < c1; j++)
			{
				soma = 0;
				for (i = 0; i < cx; i++)
				{
					soma += w1[n] * casos_treinamento[k][i];
					n += 1;
				}
				entrada_camada1[j] = soma;
				saida_camada1[j] = funcao_ativacao(entrada_camada1[j],funcao,curva);
			}

			//C�lculo para camada C2.
			n = 0;
			for (j = 0; j < c2; j++)
			{
				soma = 0;
				for (i = 0; i < c1; i++)
				{
					soma += w2[n] * saida_camada1[i];
					n += 1;
				}
				entrada_camada2[j] = soma;
				saida_camada2[j] = funcao_ativacao(entrada_camada2[j],funcao,curva);
			}





//-----------------------------------------------------------------------------//
//                      C�lculo do Erro Quadr�tico                             //
//-----------------------------------------------------------------------------//



			//Calculo do Erro Quadratico descrito nos slides da aula.
			erro_quadratico = 0;
			for(j = 0; j < c2; j++)
			{
				erro_quadratico += pow((resultado_esperado[k][j] - saida_camada2[j]),2);
			}

			//Acumula o Erro Quadratico (Criterio de Parada).
			erro_medio_quadratico += (0.5 * erro_quadratico);



//-----------------------------------------------------------------------------//
//                  Retropropaga��o do Erro Pela Rede                          //
//-----------------------------------------------------------------------------//



			//Calculo do erro para cada neur�nio da camada 2.
			for (i = 0; i < c2; i++)
			{
				erro_camada2[i] = (resultado_esperado[k][i] - saida_camada2[i]) * derivada(entrada_camada2[i],funcao,curva);
			}

			//Atualizacao dos pesos para camada 2.
			for (i = 0; i < c1; i++)
			{
				n = 0;
				for (j = 0; j < c2; j++)
				{
					dw2[n + i] = taxa_aprendizado * saida_camada1[i] * erro_camada2[j] + (MOMENTUM * dw2[n + i]);
					w2[n + i] = w2[n + i] + dw2[n + i];
					n += c1;
				}
			}

			//Calculo do erro para cada neur�nio da camada 1.
			for (i = 0; i < c1; i++)
			{
				n = 0;
				soma = 0;
				for (j = 0; j < c2; j++)
				{
					soma += (erro_camada2[j] * w2[n + i]);
					n += c1;
				}
				erro_camada1[i] = soma * derivada(entrada_camada1[i],funcao,curva);
			}

			//Atualizacao dos pesos para camada 1.
			for (i = 0; i < cx; i++)
			{
				n = 0;
				for (j = 0; j < c1; j++)
				{
					dw1[n + i] = taxa_aprendizado * casos_treinamento[k][i] * erro_camada1[j] + (MOMENTUM * dw1[n + i]);
					w1[n + i] = w1[n + i] + dw1[n + i];
					n += cx;
				}
			}


			//FmRna->Memo1->Lines->Add(k);


		}


//-----------------------------------------------------------------------------//
//          C�lculo do erro m�dio quadr�tico da �poca de treinamento           //
//-----------------------------------------------------------------------------//


		erro_medio_quadratico = (1.0 / padroes) * erro_medio_quadratico;
		printf("%d\t%10.12f\n", (int) contador, erro_medio_quadratico);
		fprintf(fp,"%d\t%10.12f\n", (int) contador, erro_medio_quadratico);



		// Plotagem dos dados sincronizados com a thread.
		//Synchronize(FmRna->AtualizaGrafico);
		//erro_medio_quadratico = 0;





//-----------------------------------------------------------------------------//
//                      VALIDA��O CRUZADA                                      //
//-----------------------------------------------------------------------------//




		//FmRna->Memo1->Lines->Add("padr�es de valida��o");

		// Propaga os k padr�es de valida��o pela rede.
		float vp = 0;

		for (k = 0; k < padroes_validacao; k++)
		{

			//C�lculo para camada C1.
			n = 0;
			for (j = 0; j < c1; j++)
			{
				soma = 0;
				for (i = 0; i < cx; i++)
				{
					soma += w1[n] * casos_validacao[k][i];
					n += 1;
				}
				entrada_camada1[j] = soma;
				saida_camada1[j] = funcao_ativacao(entrada_camada1[j],funcao,curva);
			}

			//C�lculo para camada C2.
			n = 0;
			for (j = 0; j < c2; j++)
			{
				soma = 0;
				for (i = 0; i < c1; i++)
				{
					soma += w2[n] * saida_camada1[i];
					n += 1;
				}
				entrada_camada2[j] = soma;
				saida_camada2[j] = funcao_ativacao(entrada_camada2[j],funcao,curva);
			}


			if (resultado_validacao[k][0] == 0 && resultado_validacao[k][1] == 0) {
				fprintf(fp_saidas, "B %f %f\n",saida_camada2[0], saida_camada2[1]);
			}
			if (resultado_validacao[k][0] == 0 && resultado_validacao[k][1] == 01) {
				fprintf(fp_saidas, "E %f %f\n",saida_camada2[0], saida_camada2[1]);
			}
			if (resultado_validacao[k][0] == 1 && resultado_validacao[k][1] == 0) {
				fprintf(fp_saidas, "H %f %f\n",saida_camada2[0], saida_camada2[1]);
			}
			if (resultado_validacao[k][0] == 1 && resultado_validacao[k][1] == 1) {
				fprintf(fp_saidas, "J %f %f\n",saida_camada2[0], saida_camada2[1]);
			}

	//-----------------------------------------------------------------------------//
	//                      C�lculo do Erro Quadr�tico de valida��o                            //
	//-----------------------------------------------------------------------------//



			//Calculo do Erro Quadratico de valida��o.
			erro_quadratico_validacao = 0;
			int extrapola_saida = 0;
			bool valida_saida = true;
			for(j = 0; j < c2; j++)
			{
				erro_quadratico_validacao += pow((resultado_validacao[k][j] - saida_camada2[j]),2);

				if  (saida_camada2[j] < 0.5){
					extrapola_saida = 0;
				}
				else extrapola_saida= 1;
				if (extrapola_saida != resultado_validacao[k][j]) {
					valida_saida = false;
				}

			}
			if (valida_saida) {
				vp += 1;
			}
			//Acumula o Erro Quadratico de valida��o (Criterio de Parada).
			erro_medio_quadratico_validacao += (0.5 * erro_quadratico_validacao);


			//FmRna->Memo1->Lines->Add(k);

		}

		float eficiencia = vp / padroes_validacao;
		erro_medio_quadratico_validacao = (1.0 / padroes_validacao) * erro_medio_quadratico_validacao;

		// Plotagem dos dados sincronizados com a thread.

		Synchronize(FmRna->AtualizaGrafico);
		FmRna->Label19->Caption = contador;
		FmRna->Label13->Caption = std::round(erro_medio_quadratico * 10000) / 100;
		FmRna->Label15->Caption = std::round(erro_medio_quadratico_validacao * 10000) / 100 ;
		FmRna->Label23->Caption = std::round(eficiencia * 10000) / 100;
		if (emqv_anterior < erro_medio_quadratico_validacao && erro_medio_quadratico < 0.05 && valida == 0) {
			FmRna->Label21->Caption = contador;
			FmRna->Label38->Caption = contador;
			valida = 1;

			// Adicionar a linha vertical
			FmRna->AdicionarLinhaVertical(contador);
		}

		// Declara��o do arquivo que armazena os pesos de treinamento da rede.


		FmRna->Label42->Caption = contador;
		FmRna->Label32->Caption = std::round(erro_medio_quadratico * 10000) / 100;
		FmRna->Label35->Caption = std::round(erro_medio_quadratico_validacao * 10000) / 100 ;
		FmRna->Label41->Caption = std::round(eficiencia * 10000) / 100;

		std::string file_name_epoca = "../Epocas/" + std::to_string(contador) + ".txt" ;
		FILE *fp_epoca;
		fp_epoca = fopen(file_name_epoca.c_str(),"wt");


		fprintf(fp_epoca,"Epoca %5d\n", contador);
		fprintf(fp_epoca,"Erro medio quadratico treinamento %10.12f\n", erro_medio_quadratico);
		fprintf(fp_epoca,"Erro medio quadratico validacao %10.12f\n", erro_medio_quadratico_validacao);
		fprintf(fp_epoca,"Eficiencia %10.12f\n", eficiencia);
		// Grava os pesos da camada 1.
		fprintf(fp_epoca,"Pesos camada 1\n");
		for (j = 0; j < (cx * c1); j++)
		{
			fprintf(fp_epoca,"%f\n", w1[j]);
		}

		// Grava os pesos da camada 2.
		fprintf(fp_epoca,"\nPesos camada 21\n");
		for (j = 0; j < (c1 * c2); j++)
		{
			fprintf(fp_epoca,"%f\n", w2[j]);
		}

		// Fecha o ponteiro do arquivo dos pesos de treinamento da rede.
		fclose(fp_epoca);
		fclose(fp_saidas);
		FmRna -> Edit -> Text = contador;
        FmRna -> Edit2 -> Text = contador;
		for (int i = 0; i < 4; ++i) {
		FmRna -> Chart4->Series[i]->Clear();
	}
		AnsiString epoca = FmRna -> Edit->Text;
		std::vector<float> saidas_X, saidas_Y;
		file_name_saidas = "../Saidas/" + std::string(epoca.c_str()) + ".txt";
		std::ifstream saidasFile(file_name_saidas.c_str());
		std::string line;
		if (saidasFile.is_open()) {
			while (std::getline(saidasFile, line)) {
				std::istringstream iss(line);
				std::string pessoa;
				float saida1, saida2;
				if (iss >> pessoa >> saida1 >> saida2) {
					if (pessoa == "B") {

						FmRna ->Chart4->Series[0]->AddXY(saida1, saida2);
					}
					if (pessoa == "E") {

						FmRna ->Chart4->Series[1]->AddXY(saida1, saida2);
					}
					if (pessoa == "H") {

						FmRna ->Chart4->Series[2]->AddXY(saida1, saida2);
					}
					if (pessoa == "J") {

						FmRna ->Chart4->Series[3]->AddXY(saida1, saida2);
					}

				}
			}
			saidasFile.close();
		} else {
			std::cerr << "Erro ao abrir arquivo de sa�das: " << file_name_saidas << std::endl;
		}
			}   // La�o de controle de �pocas.

	// Fecha o ponteiro do arquivo de erros de treinamento.
	fclose(fp);


//-----------------------------------------------------------------------------//
//                   Grava��o dos Pesos Ap�s treinamento                       //
//-----------------------------------------------------------------------------//


	// Declara��o do arquivo que armazena os pesos de treinamento da rede.
	fp = fopen("pesos_treino.txt","wt");

	// Grava os pesos da camada 1.
	fprintf(fp,"\tPesos Camada 1\n");
	for (j = 0; j < (cx * c1); j++)
	{
		fprintf(fp,"\tw1[%d] = %f;\n",j, w1[j]);
	}

	// Grava os pesos da camada 2.
	fprintf(fp,"\n\tPesos Camada 2\n");
	for (j = 0; j < (c1 * c2); j++)
	{
		fprintf(fp,"\tw2[%d] = %f;\n",j, w2[j]);
	}

	// Fecha o ponteiro do arquivo dos pesos de treinamento da rede.
	fclose(fp);

}

//---------------------------------------------------------------------------

void __fastcall TFmRna::AtualizaGrafico()
{
	// Plota as amostras no gr�fico.
	//FmRna->Memo1->Lines->Add("Erro treinamento");
	//FmRna->Memo1->Lines->Add(FloatToStrF(erro_medio_quadratico,ffFixed,10,6));
	//FmRna->Memo1->Lines->Add("Erro valida��o");
	//FmRna->Memo1->Lines->Add(FloatToStrF(erro_medio_quadratico_validacao,ffFixed,10,6));

	FmRna->Chart1->Series[0]->AddY(erro_medio_quadratico);
	FmRna->Chart1->Series[1]->AddY(erro_medio_quadratico_validacao);


}

//---------------------------------------------------------------------------


void __fastcall TFmRna::ListBox1Click(TObject *Sender)
{


	for (unsigned int a = 0; a < 500; a++)
	{
		Chart2->Series[0]->YValues->Value[a] = casos_treinamento[ListBox1->ItemIndex][a];
	}

	Chart2->Refresh();

//-----------------------------------------------------------------------------//
//                   Teste da Rede Neural Ap�s treinamento                     //
//-----------------------------------------------------------------------------//


	//C�lculo para camada C1.
	n = 0;
	for (j = 0; j < c1; j++)
	{
		soma = 0;
		for (i = 0; i < cx; i++)
		{
			soma += w1[n] * casos_treinamento[ListBox1->ItemIndex][i];
			n += 1;
		}
		entrada_camada1[j] = soma;
		saida_camada1[j] = funcao_ativacao(entrada_camada1[j],funcao,curva);


		// Formata a sa�da em bin�rio.
		if (saida_camada1[j] < 0.5)
		{
			saidas_formatadas_c1[j] = 0;
		}else{
			saidas_formatadas_c1[j] = 1;
		}


	}

	//C�lculo para camada C2.
	n = 0;

	for (j = 0; j < c2; j++)
	{
		soma = 0;
		for (i = 0; i < c1; i++)
		{
			soma += w2[n] * saida_camada1[i];
			n += 1;
		}
		entrada_camada2[j] = soma;
		saida_camada2[j] = funcao_ativacao(entrada_camada2[j],funcao,curva);


		// Formata a sa�da em bin�rio.
		if (saida_camada2[j] < 0.5)
		{
			saidas_formatadas_c2[j] = 0;
		}else{
			saidas_formatadas_c2[j] = 1;
		}

	}
	Label8->Caption = std::round(saida_camada2[0] * 100000000) / 100000000;
	Label9->Caption = std::round(saida_camada2[1] * 100000000) / 100000000;
	// Formata��o dos neur�nios da camada 2
	if (saidas_formatadas_c2[0] > 0.5)
		Shape16->Brush->Color = clRed;
	else
		Shape16->Brush->Color = clWhite;

	if (saidas_formatadas_c2[1] > 0.5)
		Shape17->Brush->Color = clRed;
	else
		Shape17->Brush->Color = clWhite;
}
//---------------------------------------------------------------------------

void __fastcall TFmRna::ListBox2Click(TObject *Sender)
{


	for (unsigned int a = 0; a < 500; a++)
	{
		Chart2->Series[0]->YValues->Value[a] = casos_validacao[ListBox2->ItemIndex][a];
	}

	Chart2->Refresh();



//-----------------------------------------------------------------------------//
//                   Teste da Rede Neural Ap�s treinamento                     //
//-----------------------------------------------------------------------------//


	//C�lculo para camada C1.
	n = 0;
	for (j = 0; j < c1; j++)
	{
		soma = 0;
		for (i = 0; i < cx; i++)
		{
			soma += w1[n] * casos_validacao[ListBox2->ItemIndex][i];
			n += 1;
		}
		entrada_camada1[j] = soma;
		saida_camada1[j] = funcao_ativacao(entrada_camada1[j],funcao,curva);


		// Formata a sa�da em bin�rio.
		if (saida_camada1[j] < 0.5)
		{
			saidas_formatadas_c1[j] = 0;
		}else{
			saidas_formatadas_c1[j] = 1;
		}


	}

	//C�lculo para camada C2.
	n = 0;

	for (j = 0; j < c2; j++)
	{
		soma = 0;
		for (i = 0; i < c1; i++)
		{
			soma += w2[n] * saida_camada1[i];
			n += 1;
		}
		entrada_camada2[j] = soma;
		saida_camada2[j] = funcao_ativacao(entrada_camada2[j],funcao,curva);


		// Formata a sa�da em bin�rio.
		if (saida_camada2[j] < 0.5)
		{
			saidas_formatadas_c2[j] = 0;
		}else{
			saidas_formatadas_c2[j] = 1;
		}


	}



	Label8->Caption = std::round(saida_camada2[0] * 100000000) / 100000000;
	Label9->Caption = std::round(saida_camada2[1] * 100000000) / 100000000;
	// Formata��o dos neur�nios da camada 2
	if (saidas_formatadas_c2[0] > 0.5)
		Shape16->Brush->Color = clRed;
	else
		Shape16->Brush->Color = clWhite;

	if (saidas_formatadas_c2[1] > 0.5)
		Shape17->Brush->Color = clRed;
	else
		Shape17->Brush->Color = clWhite;



	Chart2->Refresh();

}
//---------------------------------------------------------------------------






void __fastcall TFmRna::Button3Click(TObject *Sender)
{
	std::filesystem::remove_all("../classificados");
	create_directory("../classificados");
    Label10->Visible = false;
	dp = opendir(path_validacao.c_str());
	int pos = 0;
	if (dp != nullptr) {
		while ((ep = readdir(dp)) != nullptr) {
			std::string file_name = ep->d_name;

			if (file_name == "." || file_name == "..") {
				continue;  // Skip . and .. directories
			}

			//C�lculo para camada C1.
			n = 0;
			for (j = 0; j < c1; j++)
			{
				soma = 0;
				for (i = 0; i < cx; i++)
				{
					soma += w1[n] * casos_validacao[pos][i];
					n += 1;
				}
				entrada_camada1[j] = soma;
				saida_camada1[j] = funcao_ativacao(entrada_camada1[j],funcao,curva);


				// Formata a sa�da em bin�rio.
				if (saida_camada1[j] < 0.5)
				{
					saidas_formatadas_c1[j] = 0;
				}else{
					saidas_formatadas_c1[j] = 1;
				}


			}
				//C�lculo para camada C2.
				n = 0;

				for (j = 0; j < c2; j++)
				{
					soma = 0;
					for (i = 0; i < c1; i++)
					{
						soma += w2[n] * saida_camada1[i];
						n += 1;
					}
					entrada_camada2[j] = soma;
					saida_camada2[j] = funcao_ativacao(entrada_camada2[j],funcao,curva);


					// Formata a sa�da em bin�rio.
					if (saida_camada2[j] < 0.5)
					{
						saidas_formatadas_c2[j] = 0;
					}else{
						saidas_formatadas_c2[j] = 1;
					}



				}

				if(saidas_formatadas_c2[0] == 0 && saidas_formatadas_c2[1] == 0){

					create_directory("../classificados/Beatriz");

					std::ifstream in(file_name, std::ios::in | std::ios::binary);
					std::string result = "../classificados/Beatriz/" + file_name;


					  std::ofstream out("../classificados/Beatriz/" + file_name, std::ios::out | std::ios::binary);
					  out << in.rdbuf();
				}
				if(saidas_formatadas_c2[0] == 0 && saidas_formatadas_c2[1] == 1){


					create_directory("../classificados/Erick/");
					std::ifstream in(file_name, std::ios::in | std::ios::binary);
					std::string result = "../classificados/Erick" + file_name;

					std::ofstream out("../classificados/Erick/" + file_name, std::ios::out | std::ios::binary);
					out << in.rdbuf();

				}
				if(saidas_formatadas_c2[0] == 1 && saidas_formatadas_c2[1] == 0){


					create_directory("../classificados/Henrique/");
					std::ifstream in(file_name, std::ios::in | std::ios::binary);
					std::string result = "../classificados/Henrique" + file_name;

					std::ofstream out("../classificados/Henrique/" + file_name, std::ios::out | std::ios::binary);
					out << in.rdbuf();

				}
				if(saidas_formatadas_c2[0] == 1 && saidas_formatadas_c2[1] == 1){

					create_directory("../classificados/Joao/");

					std::ifstream in(file_name, std::ios::in | std::ios::binary);
					std::string result = "../classificados/Joao/" + file_name;


					std::ofstream out("../classificados/Joao/" + file_name, std::ios::out | std::ios::binary);
					out << in.rdbuf();

				}
				pos+= 1;

		}
		closedir(dp);
	} else {
		perror("Couldn't open the directory");
	}
	Label10->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TFmRna::EditChange(TObject *Sender)
{
	AnsiString pasta_epocas = "../Epocas/";

	// Texto do TEdit
	AnsiString epoca = Edit->Text;
	if (epoca.Length()	 > 0 && std::stoi(epoca.c_str()) < contador)  {


	// Compor o caminho completo do arquivo
	AnsiString caminho_epoca = pasta_epocas + epoca + ".txt";



	std::ifstream inputFile(caminho_epoca.c_str());



	std::string line;
	float epoca_eficiencia;
	float epoca_erro_medio_quadratico_treinamento;
	float epoca_erro_medio_quadratico_validacao;


	while (std::getline(inputFile, line)) {
		if (line.find("Erro medio quadratico treinamento") != std::string::npos) {
			epoca_erro_medio_quadratico_treinamento = std::stof(line.substr(line.find_last_of(' ') + 1));
		} else if (line.find("Erro medio quadratico validacao") != std::string::npos) {
			epoca_erro_medio_quadratico_validacao = std::stof(line.substr(line.find_last_of(' ') + 1));
		} else if (line.find("Eficiencia") != std::string::npos) {
			epoca_eficiencia = std::stof(line.substr(line.find_last_of(' ') + 1));
		}else if (line.find("Pesos camada 1") != std::string::npos) {
			read_weights(inputFile, w1, cx*c1);
		} else if (line.find("Pesos camada 2") != std::string::npos) {
			read_weights(inputFile, w2, c1*c2);
		}
	}

	inputFile.close();
	FmRna->Label19->Caption = AnsiString(epoca);
	FmRna->Label13->Caption = AnsiString(std::round(epoca_erro_medio_quadratico_treinamento * 10000) / 100);
	FmRna->Label15->Caption = AnsiString(std::round(epoca_erro_medio_quadratico_validacao * 10000) / 100);
	FmRna->Label23->Caption = AnsiString(std::round(epoca_eficiencia * 10000) / 100);

    FmRna->Label42->Caption = contador;
	FmRna->Label32->Caption = std::round(erro_medio_quadratico * 10000) / 100;
	FmRna->Label35->Caption = std::round(erro_medio_quadratico_validacao * 10000) / 100 ;
	FmRna->Label41->Caption = std::round(epoca_eficiencia * 10000) / 100;

	Chart1->Series[3]->Clear();
	Chart1->Series[3]->AddXY(std::stoi(epoca.c_str()), Chart1->LeftAxis->Minimum);
	Chart1->Series[3]->AddXY(std::stoi(epoca.c_str()), Chart1->LeftAxis->Maximum);



		// Plotar os dados no Chart4 com base na regra definida

	  for (int i = 0; i < 4; ++i) {
		FmRna -> Chart4->Series[i]->Clear();
	}
		AnsiString epoca = FmRna -> Edit->Text;
		std::vector<float> saidas_X, saidas_Y;
		std::string file_name_saidas = "../Saidas/" + std::string(epoca.c_str()) + ".txt";
		std::ifstream saidasFile(file_name_saidas.c_str());

		if (saidasFile.is_open()) {
			while (std::getline(saidasFile, line)) {
				std::istringstream iss(line);
				std::string pessoa;
				float saida1, saida2;
				if (iss >> pessoa >> saida1 >> saida2) {
					if (pessoa == "B") {

						FmRna ->Chart4->Series[0]->AddXY(saida1, saida2);
					}
					if (pessoa == "E") {

						FmRna ->Chart4->Series[1]->AddXY(saida1, saida2);
					}
					if (pessoa == "H") {

						FmRna ->Chart4->Series[2]->AddXY(saida1, saida2);
					}
					if (pessoa == "J") {

						FmRna ->Chart4->Series[3]->AddXY(saida1, saida2);
					}

				}
			}
			saidasFile.close();
		} else {
			std::cerr << "Erro ao abrir arquivo de sa�das: " << file_name_saidas << std::endl;
		}
			   // La�o de controle de �pocas.


		}
}
//---------------------------------------------------------------------------







void __fastcall TFmRna::PageControl1Change(TObject *Sender)
{
 Chart4->Series[4]->AddXY(0.5, 0);
 Chart4->Series[4]->AddXY(0.5, 1);
 Chart4->Series[5]->AddXY(0, 0.5);
 Chart4->Series[5]->AddXY(1, 0.5);
}
//---------------------------------------------------------------------------
class TSerialReadThread : public TThread
{
private:
	HANDLE hSerial;
	TChart *Chart;
	TMemo *Memo;
	bool &isReading;

protected:
	void __fastcall Execute();

public:
	__fastcall TSerialReadThread(HANDLE hSerialPort, TChart *chart, bool &readingFlag)
		: TThread(true), hSerial(hSerialPort), Chart(chart), isReading(readingFlag)
	{
		FreeOnTerminate = true;
	}
};

void __fastcall TSerialReadThread::Execute()
{
	const int bufferSize = 2048;
	char buffer[bufferSize] = {0};
	DWORD bytesRead;
	int conta_pontos = 0;

	while (isReading)
	{
		if (ReadFile(hSerial, buffer, bufferSize - 1, &bytesRead, NULL))
		{
			if (bytesRead > 0)
			{
				int i = 0;

				while (i <= bytesRead - 8)
				{
					if (buffer[i] == '#' && buffer[i + 1] == '$' && buffer[i + 2] == ':')
					{
						// Calcular checksum
						unsigned char checksum = 0x00;
						for (unsigned char index = 0; index < 7; index++)
						{
							checksum ^= buffer[i + index];
						}

						if (buffer[i + 7] == checksum)
						{
							// Converter dados do canal
							unsigned int valor = (static_cast<unsigned char>(buffer[i + 3]) << 8) | static_cast<unsigned char>(buffer[i + 4]);
							float tensao = valor * 0.004887585532749; // Convers�o para tens�o (5V / 1023)
							dados_tempo_real.push_back({tensao});
							FmRna ->Memo1 -> Lines -> Add(tensao);
                            FILE *fp;
							fp = fopen("joao.txt","a");
							fprintf(fp,"%f\n",tensao);


							// Fecha o ponteiro do arquivo.
							fclose(fp);
							// Adicionar ao Chart3 e Memo1
							TThread::Synchronize(nullptr, [&, tensao]()
							{
								conta_pontos ++;
								// Se a posi��o do gr�fico atingir 1000, reseta para 0
								if (conta_pontos >= 1000)
								{
									conta_pontos = 0;






									for (size_t i = 0; i < dados_tempo_real.size(); i += 1000) {
										if (i + 1000 > dados_tempo_real.size()) break;

										// Encontrar o pico mais alto na janela de 1000 amostras
										auto inicio = dados_tempo_real.begin() + i;
										auto fim = inicio + 1000;
										auto picoIter = std::max_element(inicio, fim);
										int picoIndex = std::distance(dados_tempo_real.begin(), picoIter);

										// Garantir que temos 250 amostras � esquerda e � direita do pico
										int inicioJanela = picoIndex - 250;
										int fimJanela = picoIndex + 249;  // 250 + 249 + 1 = 500 amostras

									}
									for (size_t i = 0; i < dados_tempo_real.size(); i += 1000) {
									if (i + 1000 > dados_tempo_real.size()) break;

									// Encontrar o pico mais alto na janela de 1000 amostras
									auto inicio = dados_tempo_real.begin() + i;
									auto fim = inicio + 1000;
									auto picoIter = std::max_element(inicio, fim);
									int picoIndex = std::distance(dados_tempo_real.begin(), picoIter);

									// Garantir que temos 250 amostras � esquerda e � direita do pico
									int inicioJanela = picoIndex - 250;
									int fimJanela = picoIndex + 249; // 250 + 249 + 1 = 500 amostras
									if (inicioJanela < 0 || fimJanela >= dados_tempo_real.size()) {
										std::cerr << "Pico fora dos limites permitidos para amostragem." << std::endl;
										continue;
									}

									// Normaliza��o dos dados
									auto max_v = std::max_element(dados_tempo_real.begin(), dados_tempo_real.end(),
																  [](const std::vector<float>& a, const std::vector<float>& b) { return *std::max_element(a.begin(), a.end()) < *std::max_element(b.begin(), b.end()); });
									float max_vv = *std::max_element(max_v->begin(), max_v->end());

									for (auto& elemento : dados_tempo_real) {
										for (auto& valor : elemento) {
											valor /= max_vv;
										}
									}

									auto max_v_n = std::max_element(dados_tempo_real.begin(), dados_tempo_real.end(),
																	[](const std::vector<float>& a, const std::vector<float>& b) { return *std::max_element(a.begin(), a.end()) < *std::max_element(b.begin(), b.end()); });
									float max_vv_n = *std::max_element(max_v_n->begin(), max_v_n->end());

									auto min_v_n = std::min_element(dados_tempo_real.begin(), dados_tempo_real.end(),
																	[](const std::vector<float>& a, const std::vector<float>& b) { return *std::min_element(a.begin(), a.end()) < *std::min_element(b.begin(), b.end()); });
									float min_vv_n = *std::min_element(min_v_n->begin(), min_v_n->end());

									float ganho = (max_vv_n != min_vv_n) ? 1.0f / (max_vv_n - min_vv_n) : 1.0f;

									for (auto& elemento : dados_tempo_real) {
										for (auto& valor : elemento) {
											valor = (valor - min_vv_n) * ganho;
										}
									}

									// C�lculo para camada C1
									n = 0;
									for (int j = 0; j < c1; j++)
									{
										float soma = 0.0f;
										for (int k = 0; k < cx; k++)
										{

											soma += w1[n] * dados_tempo_real[inicioJanela + k][0];
											n += 1;
										}
										entrada_camada1[j] = soma;
										saida_camada1[j] = funcao_ativacao(entrada_camada1[j], funcao, curva);

										// Formata a sa�da em bin�rio
										saidas_formatadas_c1[j] = (saida_camada1[j] < 0.5) ? 0 : 1;
									}

									// C�lculo para camada C2
									n = 0;
									for (j = 0; j < c2; j++)
									{
										soma = 0;
										for (i = 0; i < c1; i++)
										{
											soma += w2[n] * saida_camada1[i];
											n += 1;
										}
										entrada_camada2[j] = soma;
										saida_camada2[j] = funcao_ativacao(entrada_camada2[j],funcao,curva);


										// Formata a sa�da em bin�rio.
										if (saida_camada2[j] < 0.5)
										{
											saidas_formatadas_c2[j] = 0;
										}else{
											saidas_formatadas_c2[j] = 1;
										}



									}

									FmRna->Label26->Caption = std::round(saida_camada2[0] * 100000000) / 100000000;
									FmRna->Label27->Caption = std::round(saida_camada2[1] * 100000000) / 100000000;

									if(saidas_formatadas_c2[0] == 0 && saidas_formatadas_c2[1] == 0){

										FmRna->Label29->Caption = "Beatriz";
									}
									if(saidas_formatadas_c2[0] == 0 && saidas_formatadas_c2[1] == 1){


										FmRna->Label29->Caption = "Erick";

									}
									if(saidas_formatadas_c2[0] == 1 && saidas_formatadas_c2[1] == 0){

										FmRna->Label29->Caption = "Henrique";

									}
									if(saidas_formatadas_c2[0] == 1 && saidas_formatadas_c2[1] == 1){

										FmRna->Label29->Caption = "Jo�o";

									}
									// Atualiza o gr�fico na posi��o atual
									FmRna->Chart3->Series[0]->Clear();
								for (i = 0; i < 500; i++) {
									FmRna->Chart3->Series[0]->AddY(dados_tempo_real[inicioJanela + i][0]);
								}


									FmRna->Chart3->Refresh();

									dados_tempo_real.clear();
								}

								}



							});
						}

						i += 8; // Avan�ar para o pr�ximo pacote
					}
					else
					{
						i++;
					}
				}
			}
		}
		else
		{
			TThread::Synchronize(nullptr, [=]()
			{
				ShowMessage("Erro ao ler da porta serial");
			});
			isReading = false;
		}

	}
}


// No seu c�digo principal

void __fastcall TFmRna::BtOpenPortClick(TObject *Sender)
{
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		ConfigureSerialPort();
	}

	if (hSerial != INVALID_HANDLE_VALUE)
	{
		isReading = true;
		TSerialReadThread *readThread = new TSerialReadThread(hSerial, Chart2, isReading);
		readThread->Start();
	}
	else
	{
		ShowMessage("Falha ao abrir a porta serial.");
	}
}


void __fastcall TFmRna::ConfigureSerialPort() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
    }

    AnsiString selectedPort = CbSerialPort1->Text;

    if (selectedPort.IsEmpty()) {
        ShowMessage("Por favor, selecione uma porta serial.");
        return;
    }

    std::wstring wideSelectedPort = std::wstring(selectedPort.c_str(), selectedPort.c_str() + selectedPort.Length());

    hSerial = CreateFileW(wideSelectedPort.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        ShowMessage("Erro ao abrir a porta serial");
        return;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        ShowMessage("Erro ao obter estado da porta serial");
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
        return;
    }

    dcbSerialParams.BaudRate = CBR_115200; // Taxa de baud ajustada para 115200
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        ShowMessage("Erro ao configurar a porta serial");
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
        return;
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        ShowMessage("Erro ao configurar timeouts da porta serial");
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
    }
}


void __fastcall TFmRna::BtClosePortClick(TObject *Sender)
{
	if (hSerial != INVALID_HANDLE_VALUE)
	{
		isReading = false; // Parar a leitura dos dados
		CloseHandle(hSerial); // Fechar a porta serial
		hSerial = INVALID_HANDLE_VALUE;
		ShowMessage("Porta serial fechada com sucesso.");
	}
	else
	{
		ShowMessage("Porta serial j� est� fechada.");
	}
}



void __fastcall TFmRna::Edit2Change(TObject *Sender)
{
	AnsiString pasta_epocas = "../Epocas/";

	// Texto do TEdit
	AnsiString epoca = Edit2->Text;
	if (epoca.Length()	 > 0 && std::stoi(epoca.c_str()) < contador)  {


	// Compor o caminho completo do arquivo
	AnsiString caminho_epoca = pasta_epocas + epoca + ".txt";



	std::ifstream inputFile(caminho_epoca.c_str());



	std::string line;
	float epoca_eficiencia;
	float epoca_erro_medio_quadratico_treinamento;
	float epoca_erro_medio_quadratico_validacao;


	while (std::getline(inputFile, line)) {
		if (line.find("Erro medio quadratico treinamento") != std::string::npos) {
			epoca_erro_medio_quadratico_treinamento = std::stof(line.substr(line.find_last_of(' ') + 1));
		} else if (line.find("Erro medio quadratico validacao") != std::string::npos) {
			epoca_erro_medio_quadratico_validacao = std::stof(line.substr(line.find_last_of(' ') + 1));
		} else if (line.find("Eficiencia") != std::string::npos) {
			epoca_eficiencia = std::stof(line.substr(line.find_last_of(' ') + 1));
		}else if (line.find("Pesos camada 1") != std::string::npos) {
			read_weights(inputFile, w1, cx*c1);
		} else if (line.find("Pesos camada 2") != std::string::npos) {
			read_weights(inputFile, w2, c1*c2);
		}
	}

	inputFile.close();
    FmRna->Label19->Caption = AnsiString(epoca);
	FmRna->Label13->Caption = AnsiString(std::round(epoca_erro_medio_quadratico_treinamento * 10000) / 100);
	FmRna->Label15->Caption = AnsiString(std::round(epoca_erro_medio_quadratico_validacao * 10000) / 100);
	FmRna->Label23->Caption = AnsiString(std::round(epoca_eficiencia * 10000) / 100);

	FmRna->Label42->Caption = AnsiString(epoca);
	FmRna->Label32->Caption = AnsiString(std::round(epoca_erro_medio_quadratico_treinamento * 10000) / 100);
	FmRna->Label35->Caption = AnsiString(std::round(epoca_erro_medio_quadratico_validacao * 10000) / 100);
	FmRna->Label41->Caption = AnsiString(std::round(epoca_eficiencia * 10000) / 100);

	Chart1->Series[3]->Clear();
	Chart1->Series[3]->AddXY(std::stoi(epoca.c_str()), Chart1->LeftAxis->Minimum);
	Chart1->Series[3]->AddXY(std::stoi(epoca.c_str()), Chart1->LeftAxis->Maximum);



		// Plotar os dados no Chart4 com base na regra definida

	  for (int i = 0; i < 4; ++i) {
		FmRna -> Chart4->Series[i]->Clear();
	}
		AnsiString epoca = FmRna -> Edit2 ->Text;
		std::vector<float> saidas_X, saidas_Y;
		std::string file_name_saidas = "../Saidas/" + std::string(epoca.c_str()) + ".txt";
		std::ifstream saidasFile(file_name_saidas.c_str());

		if (saidasFile.is_open()) {
			while (std::getline(saidasFile, line)) {
				std::istringstream iss(line);
				std::string pessoa;
				float saida1, saida2;
				if (iss >> pessoa >> saida1 >> saida2) {
					if (pessoa == "B") {

						FmRna ->Chart4->Series[0]->AddXY(saida1, saida2);
					}
					if (pessoa == "E") {

						FmRna ->Chart4->Series[1]->AddXY(saida1, saida2);
					}
					if (pessoa == "H") {

						FmRna ->Chart4->Series[2]->AddXY(saida1, saida2);
					}
					if (pessoa == "J") {

						FmRna ->Chart4->Series[3]->AddXY(saida1, saida2);
					}

				}
			}
			saidasFile.close();
		} else {
			std::cerr << "Erro ao abrir arquivo de sa�das: " << file_name_saidas << std::endl;
		}
			   // La�o de controle de �pocas.


		}
}
//---------------------------------------------------------------------------

void __fastcall TFmRna::ListComPorts() {
		CbSerialPort1->Clear();

	HDEVINFO deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS, NULL, NULL, DIGCF_PRESENT);
	if (deviceInfoSet == INVALID_HANDLE_VALUE) {
		ShowMessage("Erro ao obter informa��es das portas COM");
		return;
	}

	SP_DEVINFO_DATA deviceInfoData;
	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	for (int i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); ++i) {
		DWORD dataType, actualSize = 0;
		TCHAR buffer[256];

		if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_FRIENDLYNAME, &dataType, (PBYTE)buffer, sizeof(buffer), &actualSize)) {
			std::wstring portName(buffer);
			size_t pos = portName.find(L"(COM");
			if (pos != std::wstring::npos) {
				size_t endPos = portName.find(L")", pos);
				if (endPos != std::wstring::npos) {
					std::wstring comPort = portName.substr(pos + 1, endPos - pos - 1);
					CbSerialPort1->Items->Add(comPort.c_str());
				}
			}
		}
	}

	SetupDiDestroyDeviceInfoList(deviceInfoSet);

	if (CbSerialPort1->Items->Count > 0) {
		CbSerialPort1->ItemIndex = 0;  // Seleciona o primeiro item
		ConfigureSerialPort();         // Configura a porta serial automaticamente
	} else {
		ShowMessage("Nenhuma porta COM encontrada.");
	}
}
void __fastcall TFmRna::BtRefreshPortsClick(TObject *Sender) {
	ListComPorts();
}

void __fastcall TFmRna::OnSerialPortChange(TObject *Sender) {
	ConfigureSerialPort();
}
