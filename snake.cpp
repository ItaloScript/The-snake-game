#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define ACIMA 72
#define ABAIXO 80
#define DIREITA 77
#define ESQUERDA 75

int estagioshu=1;


int check;
int tecla=1;
int contfruta;
int criashulauncher;
// frase animada usada no jogo
char quote[200] = ("Voce Sabia: As cobras comem a cada 15 dias, que e o tempo de digestao delas. ");
char loading [121]=("                                                                                                                        ") ;
char timer[31] =("                              ");

char nome[10];

//variavel usada para calculo
int y;
int z=121;
int b;

//função chamada para capturar a tecla clicada


//definir tamanhoo da parede verticalmente
int paredex= 100; 	
//definir tamanhoo da parede horizontalmente
int paredey= 45;	

//posição inicial da cobra
int posX = paredex/2;
int posY = paredey/2;
int wallandar;

int tamanhocobra = 1;
int estagio=0;

int velocidadenapontuacao=0;
int velocidade=110;
int velocidademaxima=30;  
int redutorvelo=5; 
//VARIAVEIS PARA CRIAR A FRUTA
int fruta=1;
int frutaX;
int frutaY;
int aleafru;
int tim;
int frutapoint;
int frutaXa ;
int frutaYa ;
int no;
int automove=90;

//VARIAVEIS PARA CRIAR SHURIKEN

int ativarshu=0;
int criashu;
int* aleashu = (int*) malloc (5 * sizeof (int));

int aleashuwall;
int xshu=99;
int timeshuriken;
int autoshuriken=40;
int shurikenwall=0;

int za;
int	ya;

//PONTEIRO PARA CRIAR CORPO DA COBRA
int* CORPOPOINX = (int*) malloc (tamanhocobra * sizeof (int));
int* CORPOPOINY = (int*) malloc (tamanhocobra * sizeof (int));

int fim=1;


void ThreadProc(void *);

// vai tornar possivel imprimir na linha e coluna desejada 
void gotoxy_2(int x, int y){
  COORD c;
  c.X = x;
  c.Y = y;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//vou poder definir a cor com a função hConsole
HANDLE  hConsole;

VOID aumentarcobra(int x,int k){
			if( x==posX && k==posY){
		contfruta++;
		fruta=1;
		estagio=1;
		
		//aumentar o tanto que a cobra aumentar com o passar do jogo
		if(velocidade>automove){
			tamanhocobra += 2;
		}else if(velocidade>autoshuriken){
			tamanhocobra += 8;
		}else{
			tamanhocobra += 16;	
		}
		//a velocidade so vai diminuir até a velocidade maxima
		if(velocidade>velocidademaxima){
			velocidade -=redutorvelo;
		}
		SetConsoleTextAttribute(hConsole, 15);
		
		// vai printar a tabela mostrando os status atuais da cobra
		gotoxy_2(paredex+5,(paredey/9)+2);
		printf("PONTOS:         %.4d",frutapoint);
		gotoxy_2(paredex+4,(paredey/9)+3);
		printf("------------------------");
	
		velocidadenapontuacao +=15;
	
		gotoxy_2(paredex+5,(paredey/9)+4);
		printf("VELOCIDADE:     %.4d",velocidadenapontuacao);
		gotoxy_2(paredex+4,(paredey/9)+5);
		printf("------------------------");
	
	}
}


int k;

void CriaWall( int wallnumgenerator,int wallandar,int xychange);
			
void SetWindow(int Width, int Height) 
{ 
    _COORD coord; 
    coord.X = Width; 
    coord.Y = Height; 

    _SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = Height - 1; 
    Rect.Right = Width - 1; 

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
} 

int telax=160;
int telay=60;
int main(){
//variavel necessaria em hConsole
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


//comando para deixar C em tela cheia
SetWindow(135,45);


//comando para mudar cor de fundo e das teclas
system("color f2");
system("cls");
for(y=0;y<35;y++){
	SetWindow(150,100);
}

//TELA INICIAL ------------------------------------------------------------------------------------------------------------------------------------------------------

//LINHA DE INTERFACE --------------------------------------------------------------------------------------------------------------------------------------------------	 		
	printf("\n 1                0            1          1            0                      0          1         0         0      1  1          0        1           1    0    0 \n \n 0       0        1      1    0        1       1              1                1       0      0       1   1     0       0      1            1                0        0 \n 0         1      0             1                  0            1          0          0                   1         1                  0                1          \n \n \n \n");

	printf( 
"                                                                                            TM                   \n"  
"                                                                          88                   \n"
"                                         ,adPPYba, 8b,dPPYba,  ,adPPYYba, 88   ,d8  ,adPPYba,  \n"
"                                         I8[    ”” 88P'   `”8a ””     `Y8 88 ,a8”  a8P      88  \n"
"                                         `”Y8ba,   88       88 ,adPPPPP88 8888[    8PP8P8P”8P  \n"
"                                         aa    ]8I 88       88 88,    ,88 88`”Yba, ”8b,         \n"
"                                         `”YbbdP”' 88       88 `”8bbdP”Y8 88   `Y8a `”Ybbd8”'  \n\n\n"
                                                      
	 ) ;

	printf(                               
	"                                          ³ ³_³ ³__   ___        __ _   __ _ _ __ ___   ____ \n"  
	"                                          ³ __³ '_ \\ / _ \\      / _` ³ / _` ³ '_ ` _ \\ / _  \\ \n"
	"                                          ³ ³ ³ ³ ³ ³ ³_³³     ³ / ³ ³³ / ³ ³ ³ ³ ³ ³ ³  I_I ³\n"
	"                                          ³ ³_³ ³ ³ ³  __/     ³ \\_³ ³³ \\_³ ³ ³ ³ ³ ³ ³  __ / \n "
	"                                          \\__³_³ ³_³\\___³      \\__, ³ \\__,_³_³ ³_³ ³_³\\___³  \n "
	"                                                                __/ ³ \n "
	"                                                                ³___/  \n"
	);
	printf("\n \n \n ");
// </LINHA DE INTERFACE --------------------------------------------------------------------------------------------------------------------------------------------------
// LINHA DE INTERFACE --------------------------------------------------------------------------------------------------------------------------------------------------	 		

	printf("\n \n \n \n \n \n");          
	printf("\n    1             0            1          1            0                      0          1         0         0      1  1          0        1           1    0    0 \n \n 0       0        1      1    0        1       1              1                1       0      0       1   1     0       0      1            1                0        0 \n 0         1      0             1                  0            1          0          0                   1         1                  0                1         ");

// </LINHA DE INTERFACE --------------------------------------------------------------------------------------------------------------------------------------------------	 


for(y=0; y<=z; y++){
	
// retardo de meio segundo para iniciar e resetar o programa
	Sleep(50);


//ANIMAÇÃO DO SLOGAN (ESPAÇO NECESSARIO PARA CENTRALIZAR NA TELA)
	gotoxy_2(30,30);
	printf("%.*s\n \n", y, quote);
	
// ANIMAÇÃO DA BARRA DE CARREGAMENTO
	SetConsoleTextAttribute(hConsole, 170);
	gotoxy_2(0,32);/* posiciona o cursor para imprimir nessas posições X coluna Y linha */
	printf("              %.*s", y, loading);
	SetConsoleTextAttribute(hConsole, 242);
	if(y==z){
printf("\n                                                     ________________________________                                 \n"
		"                                                    /                                \\                                 \n"
		"                                                   ³   PRESSIONE ENTER PARA COMECAR   ³                               \n"
		"                                                    \\________________________________/   \n \n \n \n \n \n  ");
	gotoxy_2(83,35);
	getch();
	} 
} 

//TELA INICIAL ------------------------------------------------------------------------------------------------------------------------------------------------------



//MENU JOGADORES --------------------------------------------------------------------------------------------------------------------------------------------------	 		
system("cls");
system("color f0");

printf (
"\n\n\n\n\n\n\n\n\n\n\n"
"                 __    __    __    __\n"
"                /  \\  /  \\  /  \\  /  \\\n"
"_______________/  __\\/  __\\/  __\\/  __\\_______________________________________________________________________________³\n"
"______________/  /__/  /__/  /__/  /__________________________________________________________________________________³\n"
"              | / \\   / \\   / \\   / \\  \\____                                                                          ³\n"
"              |/   \\_/   \\_/   \\_/   \\    o \\                                                                         ³\n"
"                                      \\_____/--<                                                                      ³\n"

"                                            ³      `                                                                       ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            ³                                                                              ³\n"
"                                            _______________________________________________________________________________\n"

"\n\n                                                                                    "
);

//MENU nome ----------------------------------------------------------------------------------------------------------------------------------------------------------------
gotoxy_2(70,29);
printf("NOME: _____________          ");
gotoxy_2(60,39);
printf("      DIGITE SEU NOME PARA INICIAR O JOGO      ");
gotoxy_2(60,38);
printf("                                                         ");
gotoxy_2(60,40);
printf("                                    ");
gotoxy_2(76,29);
scanf("%s",nome);
system("cls");


//criar as paredes do jogo aos quais a cobra não pode triscar
system("color 7f");
SetConsoleTextAttribute(hConsole, 588);

//Barra horizontal esquerda
for(y=0;y<=paredey;y++){
 gotoxy_2(0,y);
 printf("%c",688);
}

//Barra Vertical Superior
for(y=0;y<=paredex+30;y++){
 gotoxy_2(y,0);
 printf("%c",688);
}

//Barra Horizontal Direita
for(y=0;y<=paredex;y++){
 gotoxy_2(y,paredey);
 printf("%c",688);
}

//Barra Vertical Inferior
for(y=1;y<=paredey;y++){
 gotoxy_2(paredex,y);
 printf("%c",688);
}

//Cor do campo de centro
SetConsoleTextAttribute(hConsole,0);
for(z=1;z<paredey;z++){
	for(y=1;y<paredex;y++){
		gotoxy_2(y,z);
		printf("%c",688);
	}
	printf("\n");	
}
//Tabela lateral superior
for(z=1;z<paredey/2.2;z++){
	for(y=1;y<30;y++){
		gotoxy_2(paredex+y,z);
		printf("%c",688);
	}
	printf("\n");	
}
//barra do meio da tabela
SetConsoleTextAttribute(hConsole, 588);
for(y=1;y<=30;y++){
	gotoxy_2(paredex+y,(paredey/2.2));
	printf("%c",688);
}
//Tabela lateral inferior
SetConsoleTextAttribute(hConsole, 0);
for(z=(paredey/2.2)+1;z<paredey;z++){
	for(y=1;y<30;y++){
		gotoxy_2(paredex+y,z);
		printf("%c",688);
}
}

//desenhar um ponto verde inicial no jogo
SetConsoleTextAttribute(hConsole, 170);
gotoxy_2(posX,posY);
printf(" ");	




//fazer com que sempre gere aleatorios diferentes
srand(time(NULL));

//gerar tabela de pontos
SetConsoleTextAttribute(hConsole, 15);
	gotoxy_2(paredex+5,(paredey/9));
	printf("JOGADOR:        %s","ital");
	gotoxy_2(paredex+4,(paredey/9)+1);
	printf("------------------------");
	
	gotoxy_2(paredex+5,(paredey/9)+2);
	printf("PONTOS:         %.4d",(tamanhocobra-1)/2);
	gotoxy_2(paredex+4,(paredey/9)+3);
	printf("------------------------");
	
	
	gotoxy_2(paredex+5,(paredey/9)+4);
	printf("VELOCIDADE:     %.4d",velocidadenapontuacao);
	gotoxy_2(paredex+4,(paredey/9)+5);
	printf("------------------------");
	
	gotoxy_2(paredex+5,(paredey/9)+6);
	printf("RECORDE:        %.4d",frutapoint);
	gotoxy_2(paredex+4,(paredey/9)+7);
	printf("------------------------");
	
	gotoxy_2(paredex+5,(paredey/1.8)-2);
		printf("      RECORDES");
	
	for(y=0;y<10;y++){
		y=y+1;
		gotoxy_2(paredex+5,(paredey/1.8)+y);
		printf("UNDEFINED        %.4d",frutapoint);
		gotoxy_2(paredex+4,(paredey/1.8+y+1));
		printf("------------------------");
	}
	
	
	
	
	
	
	

while(fim!=0){
	

// vai criar uma thread que torna possivel ler valores enquanto executa o algoritmo
    DWORD waitCode;
    DWORD ThreadID = 0;
    HANDLE hThread = CreateThread(NULL, 0,
                        (LPTHREAD_START_ROUTINE)ThreadProc,
                        NULL, 0, &ThreadID);
    waitCode = WaitForSingleObject(hThread, velocidade);

	if(ativarshu==1 && velocidade<60){
aleashuwall=(rand()%2);
ativarshu=2;}
if(ativarshu==2){

	SetConsoleTextAttribute(hConsole,8);

	switch(aleashuwall){

		case 0:
		CriaWall(45,100,1);	
	
		break;
		case 1:
		CriaWall(100,45,0);	

		break;
	}
	
}
	CloseHandle(hThread);

	/*Vai checar se é possivel andar para a direção solicitada
	no caso se a cobra estiver andando para cima e quiser andar
	para baixo não irá acontecer nada;
	  Caso não haja incovenientes ira passar o valor para variavel tecla
	que sera utilizada mais a frente.
	*/	
	switch(check){
    	case ACIMA:
    		if(tecla!=ABAIXO || tamanhocobra==1){
    			tecla=check;
			}
		break;
		case ABAIXO:
    		if(tecla!=ACIMA || tamanhocobra==1){
    			tecla=check;
			}
		break;
		case DIREITA:
    		if(tecla!=ESQUERDA || tamanhocobra==1){
    			tecla=check;
			}
		break;
		case ESQUERDA:
    		if(tecla!=DIREITA || tamanhocobra==1){
    			tecla=check;
			}
		break;
	}   

	if(tamanhocobra == 1){
	/* Se o corpo da cobra for a cabeça entao ele primeiro irá apagar a cabeça
		e mais a frente irá pintar a cabeça na posição clicada		*/
		gotoxy_2(posX,posY);
		SetConsoleTextAttribute(hConsole,0);
		printf(" ");
		
	}
	if(estagio==1){
		// Aumenta o tamanho do historico sempre que o tamanho da cobra aumenta
		CORPOPOINX = (int*) realloc (CORPOPOINX, tamanhocobra* sizeof (int));
		CORPOPOINY = (int*) realloc (CORPOPOINY, tamanhocobra* sizeof (int));
		estagio=2;	
	}
	
	/* preenche a primeira casa do vetor que representa o corpo da cobra
	criando uma espécie de histórico*/
	CORPOPOINX[0] = posX;
	CORPOPOINY[0] = posY;
		
	/*repassa cada informação do histórico uma casa frente no vetor
	                    sempre que ela anda*/
	if(estagio==2){
		for(y=tamanhocobra-1;y>=1;y--){
			CORPOPOINX[y]=CORPOPOINX[y-1];
			CORPOPOINY[y]=CORPOPOINY[y-1];
		}
	if(CORPOPOINX[tamanhocobra-1]!=0 && CORPOPOINY[tamanhocobra-1]!=0){
	SetConsoleTextAttribute(hConsole,0);
	//apaga a última casa do histórico
	gotoxy_2(CORPOPOINX[tamanhocobra-1],CORPOPOINY[tamanhocobra-1]);
	printf(" ");
	}
		//pinta o corpo da cobra com um verde claro
		gotoxy_2(CORPOPOINX[0],CORPOPOINY[0]);
		SetConsoleTextAttribute(hConsole, 170);
		printf(" ");
	}
	
	
	//muda a posição da cobra de acordo com a tecla
	switch (tecla){
		case ACIMA:
			posY -= 1;
		break;		
		case ABAIXO:
			posY += 1;
		break;
		case DIREITA:
			posX += 1;
		break;	
		case ESQUERDA:
			posX -= 1;
		break;
	}

	//finalizar se a cobra triscar em si mesma
	for (y=0;y<(tamanhocobra-1);y++){
		if((posX==CORPOPOINX[y]) && (posY==CORPOPOINY[y]) && (tamanhocobra!=1)){
		fim=0;	}
	}
	
	//finalizar se a cobra triscar na parede ou parede shuriken estiver ativa
	//parede shuriken ativada
	if(((posX==1) || (posY==1) ||(posX == paredex-1) || (posY==paredey-1)) && shurikenwall==1){
		fim=0;
	//parede shuriken desativa
	}else if((posX==0) || (posY==0) ||(posX == paredex) || (posY==paredey)){
		fim=0;
	}
	
//pinta a cabeça da cobra com um emote por cima do corpo da cobra
	SetConsoleTextAttribute(hConsole, 10);
	gotoxy_2(posX,posY);
	printf("%c",1);


	
//aumenta o tamanho da cobra e a velocidade

	
//CRIA AS FRUTAS
	if(fruta==1){
		frutaX = (rand()%(paredex-3))+2;
		frutaY = (rand()%(paredey-3))+2;
		//vai desativar o criador de frutas pra não sair criando todo frame
		fruta=0;
		frutapoint++;
		
				/*se a fruta for gerada em uma das posições da cobra
		então o criador de frutas vai gerar novamente no proximo while*/
		for (y=0;y<(tamanhocobra);y++){
			if((frutaX==CORPOPOINX[y]) && (frutaY==CORPOPOINY[y])){
				fruta=1;
			}
		}
		/*se não tiver sido gerado em cima da cobra então ele vai desenhar a fruta
		 						na posição*/
		if(fruta==0){

			SetConsoleTextAttribute(hConsole,12);
			gotoxy_2(frutaX,frutaY);
			printf("%c",2);
		}
	
	}
//FAZER AS FRUTAS SE MOVEREM

		//contador utilizado para definir a velocidade com que a fruta se move
		if(velocidade<automove){
			tim++;	
		}
		
		//se a velocidade ja estiver auta o suficiente,as frutas começarão a se mover
		//ALTERAR tim%"n" para aumentar ou diminui a taxa com que a fruta se move
		if(velocidade<automove && tim%7==0){
			
		//gerar numero aleatorio para a fruta andar CIMA,BAIXO,ESQUERDA,DIREITA
		aleafru=(rand()%4);
		
		//vai receber localização atual da fruta
		frutaXa = frutaX;
		frutaYa = frutaY;	
		//vai mudar a posição da fruta de acordo com o numero aleatorio gerado
		switch (aleafru){
		case 0:
			if(frutaYa-1!=1){
				frutaYa --;	
			}else{
				frutaYa ++;	
			}
		break;
				
		case 1:
			if(frutaYa+1!=paredey-1){
				frutaYa += 1;
			}else{
				frutaYa -= 1;	
			}
		break;
		
		case 2:
			if(frutaXa+1!=paredex-1){
				frutaXa ++;
				break;
			}else{
				frutaXa --;
				break;	
			}
		
			
		case 3:
			if(frutaXa-1!=1){
				frutaXa --;
				break;
			}else{
				frutaXa ++;
				break;
			}

		}
		
		for (y=1;y<=(tamanhocobra);y++){
			//se posicao da fruta for igual a um dos historico da cobra
			if((frutaXa==CORPOPOINX[y]) && (frutaYa==CORPOPOINY[y])){
				//entao ele não vai salvar as operações feitas
				no=0;
				break;
			}else{
				//vai salvar as operações feitas
				no=1;
			}
		}
		
		//se tudo estiver OK
		if(no!=0 && estagio!=1){
			SetConsoleTextAttribute(hConsole,12);
			//pintar nova posição da fruta
			gotoxy_2(frutaXa,frutaYa);
			printf("%c",2);
			//apagar antiga posição da fruta	
			gotoxy_2(frutaX,frutaY);
			printf(" ");
			//salvar as novas posições
			frutaX=frutaXa;
			frutaY=frutaYa;	
		}
	
		}
		

//CRIAR SHURIKEN
if(ativarshu==0 && velocidade<90){
//ativar shurikens
ativarshu=1;
//diminuir campo do jogo
shurikenwall=1;

//Shuriken vertical esquerda
for(y=1;y<paredey;y++){
 gotoxy_2(1,y);
 SetConsoleTextAttribute(hConsole,8);
 printf("%c",4);
}

//Shuriken Horizontal Superior
for(y=1;y<paredex-1;y++){
 gotoxy_2(y,1);
 printf("%c",4);
}

//Shuriken Horizontal Infeior
for(y=1;y<paredex-1;y++){
 gotoxy_2(y+1,paredey-1);
  printf("%c",4);
}

//Shuriken Vertical Direita 
for(y=1;y<paredey-1;y++){
 gotoxy_2(paredex-1,y);
   printf("%c",4);
}
}



		
aumentarcobra(frutaX,frutaY);
}


free(CORPOPOINX);
free(CORPOPOINY);


system("cls");
gotoxy_2(60,30);
system("color 47");
printf("VOCE PERDEU E ISTO BOM FINAL DE SEMANA");
getch();
return 0;

}
void CriaWall( int wallnumgenerator,int wallandar,int xychange){
		if(estagioshu==1){		
			for(y=0;y<5;y++){
				aleashu[y]=(rand()%(wallnumgenerator-4)+3);
				estagioshu=2;
			}
		}
		if(estagioshu==2){
		if(za!=(wallandar-3)){	
			za++;
				if(xychange==0){
				for(y=0;y<5;y++){
			
					gotoxy_2(aleashu[y],(wallandar-za-1));
					printf(" ");
					
					gotoxy_2(aleashu[y],wallandar-za-2);
					printf("%c",4);
					if((aleashu[y]==CORPOPOINX[0]) && ((wallandar-za-2)==CORPOPOINY[0])){
							fim=0;
						}

					for (int x=1;x<(tamanhocobra-1);x++){
						if(aleashu[y]==posX && (wallandar-za-2)==(CORPOPOINY[0])){
							fim=0;
						}
						
						if( (aleashu[y]==CORPOPOINX[x]) && ((wallandar-za-2)==CORPOPOINY[x])){
							for (b=x-1;b<(tamanhocobra);b++){
							gotoxy_2(CORPOPOINX[b],CORPOPOINY[b]);
							printf(" ");	
							}
						tamanhocobra=x;
						if(tamanhocobra!=1){
						estagio=1;	
						}
						break;
						}
				
				
					}

   				}
				}else{
				for(y=0;y<5;y++){	
				gotoxy_2(wallandar-za-1,aleashu[y]);
					printf(" ");
					
					gotoxy_2(wallandar-za-2,aleashu[y]);
					printf("%c",4);
				
					if(aleashu[y]==posY && (wallandar-za-2)==posX){
					fim=0;
					}

					for (int x=1;x<(tamanhocobra-1);x++){
						if(aleashu[y]==posY && (wallandar-za-2)==(CORPOPOINX[0])){
							fim=0;
						}
						if((aleashu[y]==CORPOPOINY[x]) && ((wallandar-za-2)==CORPOPOINX[x])){
							for (b=x-1;b<(tamanhocobra);b++){
							gotoxy_2(CORPOPOINX[b],CORPOPOINY[b]);
							printf(" ");	
							}
						tamanhocobra=x;
						estagio=1;
						break;
						}
				
					}
					
				
		}
			}	
		}else{
			ativarshu=1;
			estagioshu=1;
			za=0;
		}
	}
}

void ThreadProc(void *){
	
    check = getch();
	ExitThread(0);
	
}

