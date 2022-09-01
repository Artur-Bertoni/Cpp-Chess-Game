#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.c>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//Variáveis Globais
int i, l, c, score1=0, score2=0,
	ultimaJogada, jogador, L_inicial,
	C_inicial, L_final, C_final,
	sorteio, contMB, contMP, revive;
	
bool GameOver, validade, sair, validPeca, regraP, roqueDP, roqueEP, roqueDB, roqueEB;

char jogador1[20] = "Player 1",
	 jogador2[20] = "Player 2",
	 corJ1[8] = "brancas",
	 corJ2[8] = "pretas",
	 
	 vazio[] = "\u00A0 ",
	 torreP[] = "\u265C ",
	 torreB[] = "\u2656 ",
	 cavaloP[] = "\u265E ",
	 cavaloB[] = "\u2658 ",
	 bispoP[] = "\u265D ",
	 bispoB[] = "\u2657 ",
	 reiP[] = "\u265A ",
	 reiB[] = "\u2654 ",
	 rainhaP[] = "\u265B ",
	 rainhaB[] = "\u2655 ",
	 peaoP[] = "\u265F",
	 peaoB[] = "\u2659 ",
	 
	 *tab[9][9], *peca,
	 *pecaB[7] = {torreB,cavaloB,bispoB,reiB,rainhaB,peaoB,vazio},
	 *pecaP[7] = {torreP,cavaloP,bispoP,reiP,rainhaP,peaoP,vazio},
	 *mortasP[16], *mortasB[16];

void tela_inicial(),
	 infos(),
	 zerando_jogo(),
	 print_tabuleiro(),
	 jogo(),
	 end_game(),
	 tela_final(),
	 game_rules(),
	 regra_peao(),
	 erro(),
	 fonte_jogo(),
	 sleep(int milliseconds);

int main (){ //Execução Main
	
	int reis;
	
	srand(time(NULL));
	
	system("color 80");
	
    keybd_event (VK_MENU, 0x36, 0, 0);
	keybd_event (VK_RETURN, 0x1C, 0, 0);
	keybd_event (VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
	keybd_event (VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	
	fonte_jogo();
	tela_inicial();
	infos();
	
	do{
		zerando_jogo();
		
		do{
			jogo();
			
			reis=0;
			
			for (l=1;l<=8;l++){
				for (c=1;c<9;c++){
					if (tab[l][c] == reiB || tab[l][c] == reiP){
						reis++;
					}
				}
			}
			
			if (reis == 1){
				GameOver = true;
				
				if (jogador == 1){
					score1++;
					ultimaJogada = 1;
				}
				else if (jogador == 2){
					score2++;
					ultimaJogada = 2;
				}
			}
			else{
				GameOver = false;
			}
		}while(GameOver == false);
		
		end_game();
	}while(sair == false);
	
	tela_final();
	
	printf("\n\t");
	
	system("pause");
	return 0;
}

void tela_inicial(){ //Apresentação do programa
	
	printf("\n\n\tBem vindos ao Xadrez Local!\n\tProgramado por Artur Bertoni dos Santos");
	
	sleep(1500);
	
	printf("\n\n\tVamos agora definir os apelidos dos jogadores:\n\n\t"
		   "Jogador 1: ");
	fflush(stdin);
	gets(jogador1);
	
	printf("\n\tJogador 2: ");
	fflush(stdin);
	gets(jogador2);
	
	printf("\n\n\tMuito bem, estamos prontos pra come\u00E7ar\n\n\t");
	
	system("pause");
	system("cls");
}

void infos(){ //Apresentação das informações do jogo
	
	CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 15;
    cfi.dwFontSize.Y = 30;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    
    //wcscpy(cfi.FaceName, L"Dejavu Sans Mono");
    //wcscpy(cfi.FaceName, L"MS Gothic");
    //wcscpy(cfi.FaceName, L"MS Mincho");
    wcscpy(cfi.FaceName, L"NSimSun");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	
	keybd_event (VK_MENU, 0x36, 0, 0);
	keybd_event (VK_RETURN, 0x1C, 0, 0);
	keybd_event (VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
	keybd_event (VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	
	keybd_event (VK_MENU, 0x36, 0, 0);
	keybd_event (VK_RETURN, 0x1C, 0, 0);
	keybd_event (VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
	keybd_event (VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	
	printf("\n\n\n    Vamos agora apresentar algumas informa\u00E7\u00F5es importantes sobre o jogo:\n\n\n\n");
	
	sleep(1000);
	
	printf("    1: Na hora de jogar, escolha primeiramente a posi\u00E7\u00E3o da pe\u00E7a que deseja, respeitando o padr\u00E3o\n"
		   "       linha / coluna, ap\u00F3s escolher a pe\u00E7a, digite novamente uma coordenada para onde deseja\n"
		   "       mover a pe\u00E7a, se o movimento for v\u00E1lido, o programa mover\u00E1 a pe\u00E7a;\n\n\n");
	
	sleep(1000);
	
	printf("    2: Quando seu pe\u00E3o atravessar o tabuleiro ele poder\u00E1 ser substitu\u00EDdo por qualquer pe\u00E7a sua que\n"
		   "       j\u00E1 tiver morrido, olhe na barra de pe\u00E7as mortas e digite o n\u00FAmero correspondente \u00E0 pe\u00E7a que\n"
		   "       desejar, o programa as substituir\u00E1 em sequ\u00EAncia;\n\n\n");
	
	sleep(1000);
	
	printf("    3: A jogada ROQUE est\u00E1 habilitada, para realis\u00E1-la, basta mover seu rei para a posi\u00E7\u00E3o onde o rei\n"
		   "       deve ficar ao final do ROQUE, nesse caso a torre se mover\u00E1 automaticamente.\n\n\n      ");
	
	system("pause");
	system("cls");
}

void zerando_jogo(){ //Zerar o tabuleiro
	
	GameOver = true;
	regraP = false;
	roqueDP = true;
	roqueEP = true;
	roqueDB = true;
	roqueEB = true;
	
	sorteio = rand()%2;
	
	if (sorteio == 0){
		strcpy(corJ1,"brancas");
		strcpy(corJ2,"pretas");
		
		jogador = 2;
	}
	else{
		strcpy(corJ1,"pretas");
		strcpy(corJ2,"brancas");
		
		jogador = 1;
	}
	
	for (l=1;l<=8;l++){
		for (c=1;c<9;c++){
			tab[l][c] = vazio;
		}
	}
	
	for (i=0;i<16;i++){
		mortasP[i] = vazio;
		mortasB[i] = vazio;
	}
	
	contMB = 0;
	contMP = 0;
	revive = 0;
	
	printf("\n\n\tSorteando as cores das\n\tpe\u00E7as de cada jogador. . .");
	
	sleep(1000);
	
	printf("\n\n\t%s: %s\n\n\t%s: %s\n\n\t",jogador1,corJ1,jogador2,corJ2);
	
	system("pause");
	system("cls");
	
	//Torres
	tab[1][1] = torreP;
	tab[1][8] = torreP;
	tab[8][1] = torreB;
	tab[8][8] = torreB;
	
	//Cavalos
	tab[1][2] = cavaloP;
	tab[1][7] = cavaloP;
	tab[8][2] = cavaloB;
	tab[8][7] = cavaloB;
	
	//Bispos
	tab[1][3] = bispoP;
	tab[1][6] = bispoP;
	tab[8][3] = bispoB;
	tab[8][6] = bispoB;
	
	//Reis / Rainhas
	tab[1][5] = reiP;
	tab[1][4] = rainhaP;
	tab[8][5] = reiB;
	tab[8][4] = rainhaB;
	
	//Peões
	for (l=2;l<=7;l+=5){
		for (c=1;c<9;c++){
			if (l == 2){
				tab[l][c] = peaoP;
			}
			else{
				tab[l][c] = peaoB;
			}
		}
	}
}

void print_tabuleiro(){ //Imprimir o tabuleiro na tela
	
	system("color 80");
	
	printf("\n\n\t  A B C D E F G H\n");
	
	for (l=1;l<9;l++){
		printf("\t%d ",l);
		for (c=1;c<9;c++){
			if ((l + c)%2 != 0){
				if (l == L_inicial && c == C_inicial){
					textbackground(GREEN);
			    	printf("%s",tab[l][c]);
			    	regraP = false;
				}
				else{
					textbackground(7);
			    	printf("%s",tab[l][c]);
				}
			}
			else{
				if (l == L_inicial && c == C_inicial){
					textbackground(GREEN);
			    	printf("%s",tab[l][c]);
			    	regraP = false;
				}
				else{
					textbackground(15);
			    	printf("%s",tab[l][c]);
				}
			}
		}
		textbackground(8);
		printf("\n");
	}
	printf("\n\n\tPe\u00E7as mortas:\n\tBrancas:");
	
	for (i=0;i<16;i++){
		printf("%s",mortasB[i]);
	}
	
	printf("\n\tPretas:\t");
	
	for (i=0;i<16;i++){
		printf("%s",mortasP[i]);
	}
	
	printf("\n\t\t");
	
	if (contMP > contMB){
		for (i=1;i<=contMP;i++){
			printf("%d ",i);
		}
	}
	else{
		for (i=1;i<=contMB;i++){
			printf("%d ",i);
		}
	}
}

void jogo(){ //Executar o jogo
	
	char colunaInicial, colunaFinal;
	
	if (jogador == 1){
		jogador = 2;
	}
	else if (jogador == 2){
		jogador = 1;
	}
	
	do{
		L_inicial = 0;
		C_inicial = 0;
		
		validade = false;
		
		system("cls");
		print_tabuleiro();
		
		if (jogador == 1){
			gotoxy(33,3);
			printf("Jogador: %s (%s)",jogador1,corJ1);
		}
		else if (jogador == 2){
			gotoxy(33,3);
			printf("Jogador: %s (%s)",jogador2,corJ2);
		}
		
		gotoxy(33,5);
		printf("Coordenadas da pe\u00E7a:");
		gotoxy(33,6);
		printf("Linha: "); scanf(" %d",&L_inicial);
		gotoxy(33,7);
		fflush(stdin);
		printf("Coluna: "); scanf(" %c",&colunaInicial);
		
		switch(toupper(colunaInicial)){
			case 'A':{
				C_inicial = 1;
				break;
			}
			case 'B':{
				C_inicial = 2;
				break;
			}
			case 'C':{
				C_inicial = 3;
				break;
			}
			case 'D':{
				C_inicial = 4;
				break;
			}
			case 'E':{
				C_inicial = 5;
				break;
			}
			case 'F':{
				C_inicial = 6;
				break;
			}
			case 'G':{
				C_inicial = 7;
				break;
			}
			case 'H':{
				C_inicial = 8;
				break;
			}
		}
		
		peca = tab[L_inicial][C_inicial];
		
		for (i=0; i<7; i++){ //Valida a cor da peça do jogador
			if (jogador == 1 && sorteio == 0 && (peca == pecaB[i] && peca != vazio)){
				validPeca = true;
				break;
			}
			else if(jogador == 2 && sorteio == 0 && (peca == pecaP[i] && peca != vazio)){
				validPeca = true;
				break;
			}
			else if(jogador == 1 && sorteio == 1 && (peca == pecaP[i] && peca != vazio)){
				validPeca = true;
				break;
			}
			else if(jogador == 2 && sorteio == 1 && (peca == pecaB[i] && peca != vazio)){
				validPeca = true;
				break;
			}
			else{
				validPeca = false;
			}
		}
		
		if (validPeca == true){
			gotoxy(1,1);
			print_tabuleiro();
			
			gotoxy(33,10);
			printf("Destino (%s):",peca);
			gotoxy(33,11);
			printf("Linha: "); scanf(" %d",&L_final);
			gotoxy(33,12);
			fflush(stdin);
			printf("Coluna: "); scanf(" %c",&colunaFinal);
			
			switch(toupper(colunaFinal)){
				case 'A':{
					C_final = 1;
					break;
				}
				case 'B':{
					C_final = 2;
					break;
				}
				case 'C':{
					C_final = 3;
					break;
				}
				case 'D':{
					C_final = 4;
					break;
				}
				case 'E':{
					C_final = 5;
					break;
				}
				case 'F':{
					C_final = 6;
					break;
				}
				case 'G':{
					C_final = 7;
					break;
				}
				case 'H':{
					C_final = 8;
					break;
				}
			}
			
			game_rules();
		}
		else{ //SENÃO [cor da peça válida]
			validade = false;
			gotoxy(33,10);
			printf("Cor inv\u00E1lida, jogue com a sua cor");
		
			sleep(1500);
		}
	}while (validade == false);
	
	for (i=0; i<7; i++){ //Percorre peças brancas
		if (tab[L_final][C_final] == pecaB[i] && tab[L_final][C_final] != vazio){ //SE destino for peça branca
			mortasB[contMB] = tab[L_final][C_final];
			contMB++;
			break;
		}
		else if (tab[L_final][C_final] == pecaP[i] && tab[L_final][C_final] != vazio){ //SE destino for peça preta
			mortasP[contMP] = tab[L_final][C_final];
			contMP++;
			break;
		}
	}
	
	regra_peao();
	
	if (peca == torreP){
		if (C_inicial == 1){
			roqueEP = false;
		}
		else if (C_inicial == 8){
			roqueDP = false;
		}
	}
	else if (peca == torreB){
		if (C_inicial == 1){
			roqueEB = false;
		}
		else if (C_inicial == 8){
			roqueDB = false;
		}
	}
	else if (peca == reiP){
		roqueEP = false;
		roqueDP = false;
	}
	else if (peca == reiB){
		roqueEB = false;
		roqueDB = false;
	}
	
	tab[L_inicial][C_inicial] = vazio;
	tab[L_final][C_final] = peca;
}

void end_game(){ //Finalizador de turno
	
	system("cls");
	
	char vencedorRound[20], s_sair[3], s_rules[3];
	
	if (ultimaJogada == 1){
		strcpy(vencedorRound,jogador1);
	}
	else if (ultimaJogada == 2){
		strcpy(vencedorRound,jogador2);
	}
	
	print_tabuleiro();
	
	gotoxy(33,3);
	printf("XEQUE-MATE!");
	gotoxy(33,5);
	printf("Parab\u00E9ns %s pela vit\u00F3ria!",vencedorRound);
	gotoxy(33,7);
	printf("Desejam jogar outra partida?");
	gotoxy(33,8);
	fflush(stdin);
	gets(s_sair);
	
	if (strcasecmp(s_sair,"sim") == 0 || strcasecmp(s_sair,"s") == 0 || strcasecmp(s_sair,"ss") == 0){
		sair = false;
		
		gotoxy(33,9);
		printf("Desejam mudar seus apelidos?");
		gotoxy(33,10);
		fflush(stdin);
		gets(s_rules);
		
		if (strcasecmp(s_rules,"sim") == 0 || strcasecmp(s_rules,"s") == 0 || strcasecmp(s_rules,"ss") == 0){
			gotoxy(33,12);
			printf("Jogador 1: ");
			fflush(stdin);
			gets(jogador1);
			gotoxy(33,13);
			printf("Jogador 2: ");
			fflush(stdin);
			gets(jogador2);
			
			printf("\n\t");
			system("pause");
			system("cls");
		}
		else{
			gotoxy(33,12);
			printf("Ent\u00E3o vamos ao jogo!!\n\n\t");
			
			system("pause");
			system("cls");
		}
	}
	else{
		sair = true;
		
		gotoxy(33,12);
		printf("\n\t");
		system("pause");
		system("cls");
	}
}

void tela_final(){ //Finalizador do Programa
	
	char vencedorFinal[20];
	int scoreFinal;
	
	if (score1 > score2){
		strcpy(vencedorFinal, jogador1);
		scoreFinal = score1;
	}
	else if (score2 > score1){
		strcpy(vencedorFinal, jogador2);
		scoreFinal = score2;
	}
	else{
		printf("\n\n\n\tParece que tivemos um empate entre os jogadores!\n\n\t"
			   "Ambos tiveram um score de %d vit\u00F3ria(s)\n\n\t"
			   "Mesmo assim, espero que ambos tenham se divertido!\n\t"
			   "Agrade\u00E7o por jogarem o Xadrez Local\n\n\n\t"
			   "Um abra\u00E7o do criador\n\tAss: Artur Bertoni dos Santos\n\n\t",score1);
		
		return;
	}
	
	printf("\n\n\n\tParab\u00E9ns %s!!!\n\tVoc\u00EA foi o(a) vencedor(a) final do Xadrez Local!\n\n\t"
		   "Com um score de %d vit\u00F3rias!\n\n\tAgrade\u00E7o aos dois por jogarem\n\n\n\t"
		   "Um abra\u00E7o do criador\n\tAss: Artur Bertoni dos Santos\n\n\t",vencedorFinal,scoreFinal);
}

void game_rules(){ //Testar a possibilidade da jogada ser executada
	
	int limpo=0, cont=0;
	
	if (peca == torreP || peca == torreB){ //TORRES
		if (peca == torreP){ //Torre PRETA
			if (L_final > L_inicial && C_final == C_inicial){ //SE pra baixo
				for (i=(L_inicial+1); i<L_final; i++){ //Percorre o trageto
					if (tab[i][C_inicial] == vazio){ //SE casa for vazia
						limpo++;
					}
					cont++;
				}
				if (limpo == cont){ //SE percursso vazio
					for (i=0; i<7; i++){ //Percorre peças brancas
						if (tab[L_final][C_final] == pecaB[i]){ //SE destino for peça branca/vazio
							validade = true;
							break;
						}
						else{ //SENÃO [destino for peça branca/vazio]
							validade = false;
						}
					}
					if (validade == false){ //SE n rolou
						erro();
					}
				}
				else{ //SENÃO [percursso vazio]
					validade = false;
					erro();
				}
			}
			else if (L_final < L_inicial && C_final == C_inicial){ //SE pra cima
				for (i=(L_inicial-1); i>L_final; i--){ //Percorre o trageto
					if (tab[i][C_inicial] == vazio){ //SE casa for vazia
						limpo++;
					}
					cont++;
				}
				if (limpo == cont){ //SE percursso vazio
					for (i=0; i<7; i++){ //Percorre peças brancas
						if (tab[L_final][C_final] == pecaB[i]){ //SE destino for peça branca/vazio
							validade = true;
							break;
						}
						else{ //SENÃO [destino for peça branca/vazio]
							validade = false;
						}
					}
					if (validade == false){ //SE n rolou
						erro();
					}
				}
				else{ //SENÃO [percursso vazio]
					validade = false;
					erro();
				}
			}
			else if (L_final == L_inicial && C_final > C_inicial){ //SE pra direita
				for (i=(C_inicial+1); i<C_final; i++){ //Percorre o trageto
					if (tab[L_inicial][i] == vazio){ //SE casa for vazia
						limpo++;
					}
					cont++;
				}
				if (limpo == cont){ //SE percursso vazio
					for (i=0; i<7; i++){ //Percorre peças brancas
						if (tab[L_final][C_final] == pecaB[i]){ //SE destino for peça branca/vazio
							validade = true;
							break;
						}
						else{ //SENÃO [destino for peça branca/vazio]
							validade = false;
						}
					}
					if (validade == false){ //SE n rolou
						erro();
					}
				}
				else{ //SENÃO [percursso vazio]
					validade = false;
					erro();
				}
			}
			else if (L_final == L_inicial && C_final < C_inicial){ //SE pra esquerda
				for (i=(C_inicial-1); i>C_final; i--){ //Percorre o trageto
					if (tab[L_inicial][i] == vazio){ //SE casa for vazia
						limpo++;
					}
					cont++;
				}
				if (limpo == cont){ //SE percursso vazio
					for (i=0; i<7; i++){ //Percorre peças brancas
						if (tab[L_final][C_final] == pecaB[i]){ //SE destino for peça branca/vazio
							validade = true;
							break;
						}
						else{ //SENÃO [destino for peça branca/vazio]
							validade = false;
						}
					}
					if (validade == false){ //SE n rolou
						erro();
					}
				}
				else{ //SENÃO [percursso vazio]
					validade = false;
					erro();
				}
			}
			else{ //SENÃO [movimento válido]
				validade = false;
				erro();
			}
		}
		else if (peca == torreB){ //Torre BRANCA
			if (L_final > L_inicial && C_final == C_inicial){ //SE pra baixo
				for (i=(L_inicial+1); i<L_final; i++){ //Percorre o trageto
					if (tab[i][C_inicial] == vazio){ //SE casa for vazia
						limpo++;
					}
					cont++;
				}
				if (limpo == cont){ //SE percursso vazio
					for (i=0; i<7; i++){ //Percorre peças pretas
						if (tab[L_final][C_final] == pecaP[i]){ //SE destino for peça preta/vazio
							validade = true;
							break;
						}
						else{ //SENÃO [destino for peça preta/vazio]
							validade = false;
						}
					}
					if (validade == false){ //SE n rolou
						erro();
					}
				}
				else{ //SENÃO [percursso vazio]
					validade = false;
					erro();
				}
			}
			else if (L_final < L_inicial && C_final == C_inicial){ //SE pra cima
				for (i=(L_inicial-1); i>L_final; i--){ //Percorre o trageto
					if (tab[i][C_inicial] == vazio){ //SE casa for vazia
						limpo++;
					}
					cont++;
				}
				if (limpo == cont){ //SE percursso vazio
					for (i=0; i<7; i++){ //Percorre peças pretas
						if (tab[L_final][C_final] == pecaP[i]){ //SE destino for peça preta/vazio
							validade = true;
							break;
						}
						else{ //SENÃO [destino for peça preta/vazio]
							validade = false;
						}
					}
					if (validade == false){ //SE n rolou
						erro();
					}
				}
				else{ //SENÃO [percursso vazio]
					validade = false;
					erro();
				}
			}
			else if (L_final == L_inicial && C_final > C_inicial){ //SE pra direita
				for (i=(C_inicial+1); i<C_final; i++){ //Percorre o trageto
					if (tab[L_inicial][i] == vazio){ //SE casa for vazia
						limpo++;
					}
					cont++;
				}
				if (limpo == cont){ //SE percursso vazio
					for (i=0; i<7; i++){ //Percorre peças pretas
						if (tab[L_final][C_final] == pecaP[i]){ //SE destino for peça preta/vazio
							validade = true;
							break;
						}
						else{ //SENÃO [destino for peça preta/vazio]
							validade = false;
						}
					}
					if (validade == false){ //SE n rolou
						erro();
					}
				}
				else{ //SENÃO [percursso vazio]
					validade = false;
					erro();
				}
			}
			else if (L_final == L_inicial && C_final < C_inicial){ //SE pra esquerda
				for (i=(C_inicial-1); i>C_final; i--){ //Percorre o trageto
					if (tab[L_inicial][i] == vazio){ //SE casa for vazia
						limpo++;
					}
					cont++;
				}
				if (limpo == cont){ //SE percursso vazio
					for (i=0; i<7; i++){ //Percorre peças pretas
						if (tab[L_final][C_final] == pecaP[i]){ //SE destino for peça preta/vazio
							validade = true;
							break;
						}
						else{ //SENÃO [destino for peça preta/vazio]
							validade = false;
						}
					}
					if (validade == false){ //SE n rolou
						erro();
					}
				}
				else{ //SENÃO [percursso vazio]
					validade = false;
					erro();
				}
			}
			else{ //SENÃO [movimento válido]
				validade = false;
				erro();
			}
		}
	}
	else if (peca == peaoP || peca == peaoB){ //PEÕES
		if (peca == peaoP){ //Peão PRETO
			if ((C_final == C_inicial && L_final > L_inicial) && tab[L_final][C_final] == vazio){ //SE movimento for pra baixo e vazio
				if (L_inicial == 2){ //SE estiver na casa inicial
					if ((L_final - L_inicial) <= 2){ //SE movimentação for de até 2 casas
						for (i=(L_inicial+1); i<L_final; i++){ //Percorre o trageto
							if (tab[i][C_inicial] == vazio){ //SE casa for vazia
								limpo++;
							}
							cont++;
						}
						if (limpo == cont){ //SE caminho limpo
							if (tab[L_final][C_final] == vazio){ //SE destino for peça vazio
								validade = true;
							}
							else{ //SENÃO [destino for peça vazio]
								validade = false;
							}
						}
						if (validade == false){ //SE n rolou
							erro();
						}
					}
					else{ //SENÃO [movimentação for de até 2 casas]
						validade = false;
						erro();
					}
				}
				else{ //SENÃO [estiver na casa inicial]
					if ((L_final - L_inicial) <= 1){ //SE movimentação for de até 1 casa
						if (tab[L_final][C_final] == vazio){ //SE destino for peça vazio
							validade = true;
						}
						else{ //SENÃO [destino for peça vazio]
							validade = false;
							erro();
						}
					}
					else{ //SENÃO [movimentação for de até 1 casa]
						validade = false;
						erro();
					}
				}
			}
			else if (((C_final - C_inicial) == 1 || (C_final - C_inicial) == -1) && L_final > L_inicial && (L_final - L_inicial) == 1){ //SE movimento for 1 casa na diagonal pra baixo
				for (i=0; i<7; i++){ //Percorre peças brancas
					if ((tab[L_final][C_final] == pecaB[i]) && tab[L_final][C_final] != vazio){ //SE destino for peça branca
						validade = true;
						break;
					}
					else{ //SENÃO [destino for peça branca]
						validade = false;
					}
				}
				if (validade == false){ //SE n rolou
					erro();
				}
			}
			else{ //SENÃO [movimento for válido]
				validade = false;
				erro();
			}
		}
		else if (peca == peaoB){ //Peão BRANCO
			if ((C_final == C_inicial && L_final < L_inicial) && tab[L_final][C_final] == vazio){ //SE movimento for pra cima e vazio
				if (L_inicial == 7){ //SE estiver na casa inicial
					if ((L_inicial - L_final) <= 2){ //SE movimentação for de até 2 casas
						for (i=(L_inicial-1); i>L_final; i--){ //Percorre o trageto
							if (tab[i][C_inicial] == vazio){ //SE casa for vazia
								limpo++;
							}
							cont++;
						}
						if (limpo == cont){ //SE caminho limpo
							if (tab[L_final][C_final] == vazio){ //SE destino for peça vazio
								validade = true;
							}
							else{ //SENÃO [destino for peça vazio]
								validade = false;
							}
						}
						if (validade == false){ //SE n rolou
							erro();
						}
					}
					else{ //SENÃO [movimentação for de até 2 casas]
						validade = false;
						erro();
					}
				}
				else{ //SENÃO [estiver na casa inicial]
					if ((L_inicial - L_final) <= 1){ //SE movimentação for de até 1 casa
						if (tab[L_final][C_final] == vazio){ //SE destino for casa vazia
							validade = true;
						}
						else{ //SENÃO [destino for casa vazia]
							validade = false;
							erro();
						}
					}
					else{ //SENÃO [movimentação for de até 1 casa]
						validade = false;
						erro();
					}
				}
			}
			else if (((C_final - C_inicial) == 1 || (C_final - C_inicial) == -1) && L_final < L_inicial && (L_final - L_inicial) == -1){ //SE movimento for 1 casa na diagonal pra cima
				for (i=0; i<7; i++){ //Percorre peças pretas
					if ((tab[L_final][C_final] == pecaP[i]) && tab[L_final][C_final] != vazio){ //SE destino for peça preta
						validade = true;
						break;
					}
					else{ //SENÃO [destino for peça preta]
						validade = false;
					}
				}
				if (validade == false){ //SE n rolou
					erro();
				}
			}
			else{ //SENÃO [movimento for válido]
				validade = false;
				erro();
			}
		}
	}
	else if (peca == cavaloP || peca == cavaloB){ //CAVALOS
		if (peca == cavaloP){ //Cavalo PRETO
			for (i=0; i<7; i++){ //Percorre peças brancas
				if (tab[L_final][C_final] == pecaB[i]){ //SE destino for branca/vazio
					validade = true;
					break;
				}
				else{ //SENÃO [destino for branca/vazio]
					validade = false;
				}
			}
			if (validade == true){ //SE rolou
				if (((L_final - L_inicial) == 2 || (L_final - L_inicial == -2)) && (((C_final - C_inicial) == 1 || (C_final - C_inicial) == -1))){ //SE movimento em L1
					validade = true;
				}
				else if (((L_final - L_inicial) == 1 || (L_final - L_inicial) == -1) && ((C_final - C_inicial) == 2) || ((C_final - C_inicial) == -2)){
					validade = true;
				}
				else{ //SENÃO [movimento válido]
					validade = false;
					erro();
				}
			}
			else{ //SENÃO [rolou]
				validade = false;
				erro();
			}
		}
		else if (peca == cavaloB){ //Cavalo BRANCO
			for (i=0; i<7; i++){ //Percorre peças pretas
				if (tab[L_final][C_final] == pecaP[i]){ //SE destino for preta/vazio
					validade = true;
					break;
				}
				else{ //SENÃO [destino for preta/vazio]
					validade = false;
				}
			}
			if (validade == true){ //SE rolou
				if (((L_final - L_inicial) == 2 || (L_final - L_inicial == -2)) && (((C_final - C_inicial) == 1 || (C_final - C_inicial) == -1))){ //SE movimento em L
					validade = true;
				}
				else if (((L_final - L_inicial) == 1 || (L_final - L_inicial) == -1) && ((C_final - C_inicial) == 2) || ((C_final - C_inicial) == -2)){
					validade = true;
				}
				else{ //SENÃO [movimento em L]
					validade = false;
					erro();
				}
			}
			else{ //SENÃO [rolou]
				validade = false;
				erro();
			}
		}
	}
	else if (peca == bispoP || peca == bispoB){ //BISPOS
		if (peca == bispoP){ //bispo PRETO
			for (i=0; i<7; i++){ //Percorre peças brancas
				if (tab[L_final][C_final] == pecaB[i]){ //SE destino for branca/vazio
					validade = true;
					break;
				}
				else{ //SENÃO [destino for branca/vazio]
					validade = false;
				}
			}
			if (validade == true){ //SE destino ok
				if (L_final > L_inicial && C_final > C_inicial){ //SE diagonal inferior direita
					for (l=(L_inicial+1), c=(C_inicial+1); l<L_final, c<C_final; l++,c++){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();							
							break;
						}
					}
					if (((L_inicial + C_inicial) + (L_final + C_final)) % 2 == 0){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
				else if (L_final > L_inicial && C_final < C_inicial){ //SE diagonal inferior esquerda
					for (l=(L_inicial+1), c=(C_inicial-1); l<L_final, c>C_final; l++,c--){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if ((L_inicial + C_inicial) == (L_final + C_final)){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
				else if (L_final < L_inicial && C_final > C_inicial){ //SE diagonal superior direita
					for (l=(L_inicial-1), c=(C_inicial+1); l>L_final, c<C_final; l--,c++){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if ((L_inicial + C_inicial) == (L_final + C_final)){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
				else if (L_final < L_inicial && C_final < C_inicial){ //SE diagonal superior esquerda
					for (l=(L_inicial-1), c=(C_inicial-1); l>L_final, c>C_final; l--,c--){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if (((L_inicial + C_inicial) + (L_final + C_final)) % 2 == 0){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
				else{ //SENÃO [for diagonal]
					validade = false;
					erro();
				}
			}
			else{ //SENÃO [destino ok]
				validade = false;
				erro();
			}
		}
		else if (peca == bispoB){ //bispo BRANCO
			for (i=0; i<7; i++){ //Percorre peças pretas
				if (tab[L_final][C_final] == pecaP[i]){ //SE destino for preta/vazio
					validade = true;
					break;
				}
				else{ //SENÃO [destino for preta/vazio]
					validade = false;
				}
			}
			if (validade == true){ //SE destino ok
				if (L_final > L_inicial && C_final > C_inicial){ //SE diagonal inferior direita
					for (l=(L_inicial+1), c=(C_inicial+1); l<L_final, c<C_final; l++,c++){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if (((L_inicial + C_inicial) + (L_final + C_final)) % 2 == 0){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
				else if (L_final > L_inicial && C_final < C_inicial){ //SE diagonal inferior esquerda
					for (l=(L_inicial+1), c=(C_inicial-1); l<L_final, c>C_final; l++,c--){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if ((L_inicial + C_inicial) == (L_final + C_final)){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
				else if (L_final < L_inicial && C_final > C_inicial){ //SE diagonal superior direita
					for (l=(L_inicial-1), c=(C_inicial+1); l>L_final, c<C_final; l--,c++){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if ((L_inicial + C_inicial) == (L_final + C_final)){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
				else if (L_final < L_inicial && C_final < C_inicial){ //SE diagonal superior esquerda
					for (l=(L_inicial-1), c=(C_inicial-1); l>L_final, c>C_final; l--,c--){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if (((L_inicial + C_inicial) + (L_final + C_final)) % 2 == 0){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
				else{ //SENÃO [for diagonal]
					validade = false;
					erro();
				}
			}
			else{ //SENÃO [destino ok]
					validade = false;
					erro();
				}
			}
	}
	else if (peca == rainhaP || peca == rainhaB){ //RAINHAS
		if (peca == rainhaP){ //SE rainha PRETA
			for (i=0; i<7; i++){ //Percorre peças brancas
				if (tab[L_final][C_final] == pecaB[i]){ //SE destino for branca/vazio
					validade = true;
					break;
				}
				else{ //SENÃO [destino for branca/vazio]
					validade = false;
				}
			}
			if (validade == true){ //SE destino ok
			   	if (L_inicial == L_final){ //SE movimento em linha
	   	   		   if (L_final == L_inicial && C_final > C_inicial){ //SE pra direita
				  	 for (i=(C_inicial+1); i<C_final; i++){ //Percorre o trageto
						if (tab[L_inicial][i] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{
							validade = false;
							erro();
							break;
						}
					 }
			 	}
				  else if (L_final == L_inicial && C_final < C_inicial){ //SE pra esquerda
					for (i=(C_inicial-1); i>C_final; i--){ //Percorre o trageto
						if (tab[L_inicial][i] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{
							validade = false;
							erro();
							break;
						}
					}
				}
			  	}
			  	else if (C_inicial == C_final){ //SE movimento em coluna
			   		if (L_final > L_inicial && C_final == C_inicial){ //SE pra baixo
						for (i=(L_inicial+1); i<L_final; i++){ //Percorre o trageto
							if (tab[i][C_inicial] == vazio){ //SE casa for vazia
								validade = true;
							}
							else{
								validade = false;
								erro();
								break;
							}
						}
					}
					else if (L_final < L_inicial && C_final == C_inicial){ //SE pra cima
						for (i=(L_inicial-1); i>L_final; i--){ //Percorre o trageto
							if (tab[i][C_inicial] == vazio){ //SE casa for vazia
								validade = true;
							}
							else{
								validade = false;
								erro();
								break;
							}
						}
					}
			   }
			  	else if (L_final > L_inicial && C_final > C_inicial){ //SE para diagonal inferior direita
					for (l=(L_inicial+1), c=(C_inicial+1); l<L_final, c<C_final; l++,c++){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if (((L_inicial + C_inicial) + (L_final + C_final)) % 2 == 0){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
			  	else if (L_final > L_inicial && C_final < C_inicial){ //SE para diagonal inferior esquerda
					for (l=(L_inicial+1), c=(C_inicial-1); l<L_final, c>C_final; l++,c--){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if ((L_inicial + C_inicial) == (L_final + C_final)){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
			  	else if (L_final < L_inicial && C_final > C_inicial){ //SE para diagonal superior direita
					for (l=(L_inicial-1), c=(C_inicial+1); l>L_final, c<C_final; l--,c++){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if ((L_inicial + C_inicial) == (L_final + C_final)){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
			  	else if (L_final < L_inicial && C_final < C_inicial){ //SE para diagonal superior esquerda
					for (l=(L_inicial-1), c=(C_inicial-1); l>L_final, c>C_final; l--,c--){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if (((L_inicial + C_inicial) + (L_final + C_final)) % 2 == 0){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
			}
			else{ //SENÃO [destino ok]
				erro();
			}
		}
		else if (peca == rainhaB){ //SE rainha BRANCA
			for (i=0; i<7; i++){ //Percorre peças pretas
				if (tab[L_final][C_final] == pecaP[i]){ //SE destino for preta/vazio
					validade = true;
					break;
				}
				else{ //SENÃO [destino for preta/vazio]
					validade = false;
				}
			}
			if (validade == true){ //SE destino ok
			   	if (L_inicial == L_final){ //SE movimento em linha
			   	  if (L_final == L_inicial && C_final > C_inicial){ //SE pra direita
				  	 for (i=(C_inicial+1); i<C_final; i++){ //Percorre o trageto
						if (tab[L_inicial][i] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{
							validade = false;
							erro();
							break;
						}
					 }
				}
				  else if (L_final == L_inicial && C_final < C_inicial){ //SE pra esquerda
					for (i=(C_inicial-1); i>C_final; i--){ //Percorre o trageto
						if (tab[L_inicial][i] == vazio){ //SE casa for vazia
							limpo++;
						}
						cont++;
					}
					if (limpo == cont){ //SE percursso vazio
						for (i=0; i<7; i++){ //Percorre peças pretas
							if (tab[L_final][C_final] == pecaP[i]){ //SE destino for peça preta/vazio
								validade = true;
								break;
							}
							else{ //SENÃO [destino for peça preta/vazio]
								validade = false;
							}
						}
						if (validade == false){ //SE n rolou
							erro();
						}
					}
					else{ //SENÃO [percursso vazio]
						validade = false;
						erro();
					}
				}
			   	}
			   	else if (C_inicial == C_final){ //SE movimento em coluna
			   		if (L_final > L_inicial && C_final == C_inicial){ //SE pra baixo
						for (i=(L_inicial+1); i<L_final; i++){ //Percorre o trageto
							if (tab[i][C_inicial] == vazio){ //SE casa for vazia
								validade = true;
							}
							else{
								validade = false;
								erro();
								break;
							}
						}
					}
					else if (L_final < L_inicial && C_final == C_inicial){ //SE pra cima
						for (i=(L_inicial-1); i>L_final; i--){ //Percorre o trageto
							if (tab[i][C_inicial] == vazio){ //SE casa for vazia
								validade = true;
							}
							else{
								validade = false;
								erro();
								break;
							}
						}
					}
			   	}
			   	else if (L_final > L_inicial && C_final > C_inicial){ //SE para diagonal inferior direita
					for (l=(L_inicial+1), c=(C_inicial+1); l<L_final, c<C_final; l++,c++){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if (((L_inicial + C_inicial) + (L_final + C_final)) % 2 == 0){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
				else if (L_final > L_inicial && C_final < C_inicial){ //SE para diagonal inferior esquerda
					for (l=(L_inicial+1), c=(C_inicial-1); l<L_final, c>C_final; l++,c--){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if ((L_inicial + C_inicial) == (L_final + C_final)){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
				else if (L_final < L_inicial && C_final > C_inicial){ //SE para diagonal superior direita
					for (l=(L_inicial-1), c=(C_inicial+1); l>L_final, c<C_final; l--,c++){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if ((L_inicial + C_inicial) == (L_final + C_final)){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
				else if (L_final < L_inicial && C_final < C_inicial){ //SE para diagonal superior esquerda
					for (l=(L_inicial-1), c=(C_inicial-1); l>L_final, c>C_final; l--,c--){ //Percorre a diagonal
						if (tab[l][c] == vazio){ //SE casa for vazia
							validade = true;
						}
						else{// SENÃO [casa for vazia]
							validade = false;
							erro();
							break;
						}
					}
					if (((L_inicial + C_inicial) + (L_final + C_final)) % 2 == 0){ //SE for diagonal
						validade = true;
					}
					else{ //SENÃO [for diagonal]
						validade = false;
						erro();
					}
				}
			}
			else{ //SENÃO [destino ok]
				erro();
			}
		}
	}
	else if (peca == reiP || peca == reiB){ //REIS
		if (peca == reiP){ //SE rei PRETO
			for (i=0; i<7; i++){ //Percorre peças brancas
				if (tab[L_final][C_final] == pecaB[i]){ //SE destino for branca/vazio
					validade = true;
					break;
				}
				else{ //SENÃO [destino for branca/vazio]
					validade = false;
				}
			}
			if (validade == true){ //SE destino ok
				if (((L_final - L_inicial) == 1 && C_final == C_inicial) || ((L_final - L_inicial) == -1 && C_final == C_inicial)){ //SE movimentação em linha E 1 casa somente
					validade = true;
				}
				else if ((L_final == L_inicial && (C_final - C_inicial) == 1) || (L_final == L_inicial && (C_final - C_inicial) == -1)){ //SE movimentação em coluna E 1 casa somente
					validade = true;
				}
				else if (((L_final - L_inicial) == 1 && (C_final - C_inicial) == 1) || ((L_final - L_inicial) == -1 && (C_final - C_inicial) == -1) ||
					 	((L_final - L_inicial) == 1 && (C_final - C_inicial) == -1) || ((L_final - L_inicial) == -1 && (C_final - C_inicial) == 1)){ //SE movimentação em diagonal E 1 casa somente
					validade = true;
				}
				else if (((L_final == L_inicial && C_final == 3) && (tab[1][1] == torreP) && ((tab[1][2] == vazio) && (tab[1][3] == vazio) && (tab[1][4] == vazio)) && roqueEP == true) ||
					 	((L_final == L_inicial && C_final == 7) && (tab[1][8] == torreP) && ((tab[1][7] == vazio) && (tab[1][6] == vazio)) && roqueDP == true)){ //SE roque
					validade = true;
					if (C_final == 3){
						tab[1][1] = vazio;
						tab[1][4] = torreP;
					}
					else if(C_final == 7){
						tab[1][8] = vazio;
						tab[1][6] = torreP;
					}
				}
				else{ //SENÃO [movimento válido]
					validade = false;
					erro();
				}
			}
			else{ // SENÃO [destino ok]
				erro();
			}
		}
		else if (peca == reiB){ //SE rei BRANCO
			for (i=0; i<7; i++){ //Percorre peças pretas
				if (tab[L_final][C_final] == pecaP[i]){ //SE destino for preta/vazio
					validade = true;
					break;
				}
				else{ //SENÃO [destino for preta/vazio]
					validade = false;
				}
			}
			if (validade == true){ //SE destino ok
				if (((L_final - L_inicial) == 1 && C_final == C_inicial) || ((L_final - L_inicial) == -1 && C_final == C_inicial)){ //SE movimentação em linha E 1 casa somente
					validade = true;
				}
				else if ((L_final == L_inicial && (C_final - C_inicial) == 1) || (L_final == L_inicial && (C_final - C_inicial) == -1)){ //SE movimentação em coluna E 1 casa somente
					validade = true;
				}
				else if (((L_final - L_inicial) == 1 && (C_final - C_inicial) == 1) || ((L_final - L_inicial) == -1 && (C_final - C_inicial) == -1) ||
					 	((L_final - L_inicial) == 1 && (C_final - C_inicial) == -1) || ((L_final - L_inicial) == -1 && (C_final - C_inicial) == 1)){ //SE movimentação em diagonal E 1 casa somente
					validade = true;
				}
				else if (((L_final == L_inicial && C_final == 3) && (tab[8][1] == torreB) && ((tab[8][2] == vazio) && (tab[8][3] == vazio) && (tab[8][4] == vazio)) && roqueEB == true) ||
					 	((L_final == L_inicial && C_final == 7) && (tab[8][8] == torreB) && ((tab[8][7] == vazio) && (tab[8][6] == vazio)) && roqueDB == true)){ //SE roque
					validade = true;
					if (C_final == 3){
						tab[8][1] = vazio;
						tab[8][4] = torreB;
					}
					else if(C_final == 7){
						tab[8][8] = vazio;
						tab[8][6] = torreB;
					}
				}
				else{ //SENÃO [movimento válido]
					validade = false;
					erro();
				}
			}
			else{ // SENÃO [destino ok]
				erro();
			}
		}
	}
}

void erro(){ //Erro de movimentação de peça
	gotoxy(33,14);
	printf("Jogada inv\u00E1lida, insira um novo movimento");
	
	sleep(2000);
}

void regra_peao(){ //Substituir peão SE na última casa adversária por uma peça morta
	if (validade == true && (peca == peaoP)){
		if (L_final == 8){
			tab[L_inicial][C_inicial] = vazio;
			tab[L_final][C_final] = peca;
			L_inicial = L_final;
			C_inicial = C_final;
			
			system("cls");
			print_tabuleiro();
			
			if (jogador == 1){
				gotoxy(33,3);
				printf("Jogador: %s (%s)",jogador1,corJ1);
			}
			else if (jogador == 2){
				gotoxy(33,3);
				printf("Jogador: %s (%s)",jogador2,corJ2);
			}
			
			gotoxy(33,5);
			printf("Seu pe\u00E3o atravessou o tabuleiro,");
			gotoxy(33,6);
			printf("escolha o n\u00FAmero de uma pe\u00E7a");
			gotoxy(33,7);
			printf("morta da sua cor para substituir esse pe\u00E3o: ");
			gotoxy(33,8);
			scanf(" %d",&revive);
			
			peca = mortasP[revive-1];
			mortasP[revive-1] = peaoP;
			regraP = true;
		}
	}
	else if (validade == true && (peca == peaoB)){
		if (L_final == 1){
			tab[L_inicial][C_inicial] = vazio;
			tab[L_final][C_final] = peca;
			L_inicial = L_final;
			C_inicial = C_final;
			
			system("cls");
			print_tabuleiro();
			
			if (jogador == 1){
				gotoxy(33,3);
				printf("Jogador: %s (%s)",jogador1,corJ1);
			}
			else if (jogador == 2){
				gotoxy(33,3);
				printf("Jogador: %s (%s)",jogador2,corJ2);
			}
			
			gotoxy(33,5);
			printf("Seu pe\u00E3o atravessou o tabuleiro,");
			gotoxy(33,6);
			printf("escolha o n\u00FAmero de uma pe\u00E7a");
			gotoxy(33,7);
			printf("morta da sua cor para substituir esse pe\u00E3o: ");
			gotoxy(33,8);
			scanf(" %d",&revive);
			
			peca = mortasB[revive-1];
			mortasB[revive-1] = peaoB;
			regraP = true;
		}
	}
}

void fonte_jogo(){ //Carregar a fonte do HUD
	
	CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 15.5;
    cfi.dwFontSize.Y = 35;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    
    //wcscpy(cfi.FaceName, L"Dejavu Sans Mono");
    //wcscpy(cfi.FaceName, L"MS Gothic");
    //wcscpy(cfi.FaceName, L"MS Mincho");
    wcscpy(cfi.FaceName, L"NSimSun");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    
    SetConsoleOutputCP(65001);
}

void sleep(int milliseconds){ //Clock de Sleep
    
	clock_t time_end;
	
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    
    while (clock() < time_end){
    }
}
