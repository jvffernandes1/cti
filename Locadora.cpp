#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include<locale.h>
#include<conio.c>

/* informa??es ?teis: C?digo da tecla ESC = 27 */
int aux_codigo,F;
int dados_z=0;
char tecla=0;
int l=10;
int exc=0;
int escolhas = 0;
int senha=0;
int cod=0;
int lero=0;
char erro;
char continua;
FILE *list;

struct loc_jog{

	   int chave_mestre;
       int codigo;
       char titulo[30];
       char produtora[15];
       char distribuidora[15];
       char genero[10];
       char plataforma[10];
       char excluir;
};

struct loc_pessoas{
	char nome[50];
	char email[50];
//	char senha[8];
};

struct data{
       int dia, mes, ano;
       loc_jog game;
       loc_pessoas people;
}jogo;

void gotoxyz(int x, int y)
{
	
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
 
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);

}

int consistencia(char valor, int escolha, int escolhadata, int dia, int  mes, int ano)
{
	
	
	int erro;
	switch(escolha)
	{
		case 1:
			
			break;
				
		case 2: switch(escolhadata)
				{
					case 1: if(dia > 31 or dia < 1)
								erro = 1;		
						break;
						
					case 2:	if(mes > 12 or mes < 1)
								erro = 1;
							
							if(mes == 2 and dia > 29)
								erro = 1;
						break;
						
					case 3: if(ano < 00 or ano > 15)
								erro = 1;
						break;
				}
			break;	
			
		case 3: if(valor == '27')
					erro = 1;
	}
	return erro;
}


void abrir_arquivo_jogos()
{
    if((list = fopen("Catalogo.bin", "ab+")) == NULL) /* Abre arquivo bin?rio para escrita */
    {
        gotoxyz(18,11);printf("Erro 01: Erro na abertura do arquivo!");
        exit(1);
    }
}

void abrir_arquivo_pessoas()
{
    if((list = fopen("Pessoas.bin", "ab+")) == NULL) /* Abre arquivo bin?rio para escrita */
    {
        gotoxyz(18,11);printf("Erro 01: Erro na abertura do arquivo!");
        exit(1);
    }
}

void ler_arquivo_jogos()
{
    if((list = fopen("Catalogo.bin", "rb")) == NULL) /* Abre arquivo bin?rio para escrita */
    {
        gotoxyz(18,11);printf("Erro 02: Falha na verificação do arquivo!");
		getch();
    }
}

void ler_arquivo_pessoas()
{
    if((list = fopen("Pessoas.bin", "rb")) == NULL) /* Abre arquivo bin?rio para escrita */
    {
        gotoxyz(18,11);printf("Erro 02: Falha na verificação do arquivo!");
		getch();
    }
}


//VOID DAS COORDENADAS DO COMANDO GOTOXY.


//VOID PARA CONSULTA DOS DADOS.
void consulta_jogos()
{
	int pag=1;
    ler_arquivo_jogos();
    
    system("cls");
    fflush(stdin);
    gotoxyz(13,2); printf("Bem-vindo à consulta!");
    gotoxyz(13,4); printf("Página [%d]",pag);
    gotoxyz(5,7); printf("Código");
    gotoxyz(20,7); printf("Jogo");
    gotoxyz(35,7); printf("Produtora");
    gotoxyz(50,7); printf("Gênero");
    gotoxyz(65,7); printf("Plataforma");
    
    l=9;
    while(!feof(list))
    {
        if(fread(&jogo, sizeof(jogo), 1, list)==1 && jogo.game.excluir=='N')
        {
            gotoxyz(5,l); printf("%d",jogo.game.codigo+1);
		    gotoxyz(20,l); printf("%s",jogo.game.titulo);
		    gotoxyz(35,l); printf("%s",jogo.game.produtora);
		    gotoxyz(50,l); printf("%s",jogo.game.genero);
		    gotoxyz(65,l); printf("%s",jogo.game.plataforma);

	        Sleep(100);           
           
            l++;
            if(l>20)
            {
            gotoxyz(3,23); printf("<-- Pressione Esc para voltar!");
            gotoxyz(40,23); printf("Pressione Enter para ir até a página %d -->",pag+1);
            tecla=getch();
            
			if(tecla==27)
            {
				pag=1;
                fclose(list);
                break;
            }
            
            else
			{
            l=9;
            system("cls");
            pag++;
            gotoxyz(13,2); printf("Bem-vindo à consulta!");
            gotoxyz(13,4); printf("Página[%d]",pag);
            gotoxyz(5,7); printf("Código");
    		gotoxyz(20,7); printf("Jogo");
   			gotoxyz(35,7); printf("Produtora");
    		gotoxyz(50,7); printf("Gênero");
    		gotoxyz(65,7); printf("Plataforma");
    	}
        }
    }
  

}
  gotoxyz(20,1);
  system("pause");
}

void mostra_para_exclusao()
{
    system("cls");
    fflush(stdin);
 //   gotoxyz(13,2); printf("Bem-vindo à consulta!");
 //   gotoxyz(13,4); printf("Página [%d]",pag);
    gotoxyz(5,7); printf("Código");
    gotoxyz(20,7); printf("Jogo");
    gotoxyz(35,7); printf("Produtora");
    gotoxyz(50,7); printf("Gênero");
    gotoxyz(65,7); printf("Plataforma");

    gotoxyz(5,l); printf("%d",jogo.game.codigo+1);
    gotoxyz(20,l); printf("%s",jogo.game.titulo);
    gotoxyz(35,l); printf("%s",jogo.game.produtora);
    gotoxyz(50,l); printf("%s",jogo.game.genero);
    gotoxyz(65,l); printf("%s",jogo.game.plataforma);
}

void user_para_exclusao()
{
    system("cls");
    fflush(stdin);
 //   gotoxyz(13,2); printf("Bem-vindo à consulta!");
 //   gotoxyz(13,4); printf("Página [%d]",pag);
    gotoxyz(5,7); printf("Nome");
    gotoxyz(20,7); printf("E-mail");

    gotoxyz(5,l); printf("%s",jogo.people.nome);
    gotoxyz(20,l); printf("%s",jogo.people.email);
}


void excluir_jogos() //exclusao lógica
{
	long fposicao;
	char conf;
	char continua;
	//list = fopen("Catalogo.bin", "rb+");
    if((list = fopen("Catalogo.bin", "rb+")) == NULL) /* Abre arquivo bin?rio para escrita */
    {
        gotoxyz(18,11);printf("Erro 22: Não existe arquivo para exclusão!");
        return;
    }
	do
	{	
	   gotoxyz(13,6);printf("                                                               ");
	   gotoxyz(13,8);printf("                                                               ");
		gotoxyz(10,3); printf("Digite o codigo a ser excluido (digite zero para encerrar): ");         
	   scanf("%d", &aux_codigo);
	   fflush(stdin);
	   
	   
	   if (aux_codigo!=0)
	   {
	   		aux_codigo-=1;
			F = 0;
			rewind(list);
		   do
		   {
				fread( &jogo,sizeof(jogo),1,list);
				
				if ( jogo.game.codigo == aux_codigo and jogo.game.excluir == 'N' ) 
				{
			  		F = 1;
			  		fposicao = ftell(list); 
			  		mostra_para_exclusao();
				  	gotoxyz(20,20); printf("Confirma exclusão ? (S/N): ");
				  	
					do 
				  	{
				  		fflush(stdin);
				   		gotoxyz(46,20); conf = getche();
				  	}while( conf == 's' && conf == 'S' &&conf == 'n' && conf == 'N' );
				  
				  	if( conf == 's' || conf == 'S' )
				  	{
						fseek (list,fposicao-(sizeof(jogo)),SEEK_SET); 
						jogo.game.excluir='S';
						fwrite(&list,sizeof(jogo),1,list);
						fflush (list);
				  	}
					fflush(stdin);
					gotoxyz(8,21); printf("Digite ESPAÇO para excluir outro arquivo ou ENTER para voltar ao MENU: ");
			
					gotoxyz(78,21);continua=getch();
					if(continua==32)
					{
						gotoxyz(70,15); clrscr(); // limpar de tela
						
					}
					if(continua==13)
					{
						system("cls");
						return;
					}
					
				}
			} while((F != 1) &&(!feof(list)));  	
		}
		if (F==0 && aux_codigo!=0)
		{   
			system("cls");
			gotoxyz(13,6);printf(" Código nao encontrado");
			gotoxyz(13,8);printf("Aperte enter para excluir outro código...");
			//Sleep(4000);
			getch();
			
		}
	}while(aux_codigo!=0);
	
	system("cls");
	
}

void excluir_users() //exclusao lógica
{
	long fposicao;
	char conf;
	char continua;
	//list = fopen("Catalogo.bin", "rb+");
    if((list = fopen("pessoas.bin", "rb+")) == NULL) /* Abre arquivo bin?rio para escrita */
    {
        gotoxyz(18,11);printf("Erro 21: Não existe arquivo para exclusão!");
        return;
    }
	do
	{	
	   gotoxyz(13,6);printf("                                                               ");
	   gotoxyz(13,8);printf("                                                               ");
		gotoxyz(10,3); printf("Digite o codigo a ser excluido (digite zero para encerrar): ");         
	   scanf("%d", &aux_codigo );
	   fflush(stdin);
	   
	   
	   if (aux_codigo!=0)
	   {
			F = 0;
			rewind(list);
		   do
		   {
				fread( &jogo,sizeof(jogo),1,list);
				
				if ( jogo.game.codigo == aux_codigo and jogo.game.excluir == 'N' ) 
				{
			  		F = 1;
			  		fposicao = ftell(list); 
			  		user_para_exclusao();
				  	gotoxyz(20,20); printf("Confirma exclusão ? (S/N): ");
				  	
					do 
				  	{
				  		fflush(stdin);
				   		gotoxyz(46,20); conf = getche();
				  	}while( conf == 's' && conf == 'S' &&conf == 'n' && conf == 'N' );
				  
				  	if( conf == 's' || conf == 'S' )
				  	{
						fseek (list,fposicao-(sizeof(jogo)),SEEK_SET); 
						jogo.game.excluir='S';
						fwrite(&list,sizeof(jogo),1,list);
						fflush (list);
				  	}
					fflush(stdin);
					gotoxyz(8,21); printf("Digite ESPAÇO para excluir outro arquivo ou ENTER para voltar ao MENU: ");
			
					gotoxyz(78,21);continua=getch();
					if(continua==32)
					{
						gotoxyz(70,15); clrscr(); // limpar de tela
						
					}
					if(continua==13)
					{
						system("cls");
						return;
					}
					
				}
			} while((F != 1) &&(!feof(list)));  	
		}
		if (F==0 && aux_codigo!=0)
		{   
			system("cls");
			gotoxyz(13,6);printf(" Código nao encontrado");
			gotoxyz(13,8);printf("Aperte enter para excluir outro código...");
			//Sleep(4000);
			getch();
			
		}
	}while(aux_codigo!=0);
	
	system("cls");
	
}



void consulta_pessoas()
{
	int pag=1;
    ler_arquivo_pessoas();
    
    system("cls");
    fflush(stdin);
    gotoxyz(13,2); printf("Bem-vindo à consulta!");
    gotoxyz(13,4); printf("Página [%d]",pag);
    gotoxyz(20,7); printf("Nome");
    gotoxyz(40,7); printf("E-Mail");
    l=9;
    while(!feof(list))
    {
        if(fread(&jogo, sizeof(jogo), 1, list)==1 && jogo.game.excluir=='N')
        {
            gotoxyz(20,l); printf("%s",jogo.people.nome);
            gotoxyz(40,l); printf("%s",jogo.people.email);
        Sleep(100);           
           
            l++;
            if(l>20)
            {
            gotoxyz(3,23); printf("<-- Pressione Esc para voltar!");
            gotoxyz(40,23); printf("Pressione Enter para ir até a página %d -->",pag+1);
            tecla=getch();
            
			if(tecla==27)
            {
				pag=1;
                fclose(list);
                break;
            }
            
            else
			{
            l=9;
            system("cls");
            pag++;
            gotoxyz(13,2); printf("Bem-vindo à consulta!");
            gotoxyz(13,4); printf("Página[%d]",pag);
            gotoxyz(5,7); printf("Código");
    		gotoxyz(20,7); printf("Jogo");
   			gotoxyz(35,7); printf("Produtora");
    		gotoxyz(50,7); printf("Gênero");
    		gotoxyz(65,7); printf("Plataforma");
    	}
        }
    }
  

}
  gotoxyz(20,1);
  system("pause");
}

void admin()
{
	system("cls");
	gotoxyz(13,2);printf("Bem-vindo administrador!");
	gotoxyz(8,5);printf("Por favor, digite sua senha para continuar:");
	scanf("%d",&senha);
	if(senha==1478963)
	{
		system("cls");
		gotoxyz(13,2);printf("LOGADO COM SUCESSO!");
		gotoxyz(8,4);printf("Por favor, pressione Enter para continuar.");
		getch();
		system("cls");
		excluir_jogos();
		system("cls");
		
	}
	else
	{
		gotoxyz(13,2);printf("Senha Errada!, Encerrando Programa!");
		Sleep(2000);
		exit(0);
	}
	
	
}

void creditos()
{
    system("cls");
    fflush(stdin);
    gotoxyz(13,2); printf("Programa feito por:\a");
    gotoxyz(14,4); printf("Diogenes Hernandez     nº 05");
    gotoxyz(14,5); printf("João Victor     nº 28");
    gotoxyz(14,6); printf("Victor Pereira     nº 26");
    gotoxyz(14,8); printf("71D 2015 - CTI UNESP - BAURU");
    gotoxyz(13,2); printf("BEM VINDO A LOCADORA SMIGOL!");
    gotoxyz(17,3);printf("Onde voce encontra seus jogos preciosos!");
    gotoxyz(10,7);printf("Pressione qualquer tecla para avançar!");
	gotoxyz(14,13); printf("Nossa empresa é especializada em locação de jogos em midia fisica para todas as plataformas e para todos os gostos.");
    gotoxyz(14,14); printf("e para todos os gostos. Caso seu estojo não esteja em nossa lista, insira o mesmo manualmente");
    gotoxyz(14,15); printf(" e se cadastre para poder emprestar");
	gotoxyz(13,18); printf("Pressione qualquer tecla para voltar.");
    getch();
}

void saida()
{
    system("cls");
    gotoxyz(13,3); printf("Obrigado por usar nosso programa!");
    gotoxyz(13,4); printf("By:LOCADORA Smigol!");
    fclose(list);
    exit(0);
}


void salvar_dados()
{
    if(fwrite(&jogo, sizeof(jogo), 1, list) != 1) /* Escreve a estrutura no arquivo */
    {
        system("cls");
        gotoxyz(13,11);printf("Erro 03: Erro na escrita do arquivo");
    }
    else
    {
        system("cls");
        gotoxyz(13,11);printf("Dados salvos com sucesso!");
        dados_z++;
    gotoxyz(8,21); printf("Digite ESPAÇO para recadastrar outro arquivo ou ENTER para voltar ao MENU: ");
			
		gotoxyz(78,21); continua=getch();
			if(continua==32)
				{
					gotoxyz(70,15); clrscr(); // limpar de tela
						
				}
				if(continua==13)
				{
					system("cls");
					return;
				}
        fclose(list);
    }
    getch();
}

//FUN??O PARA O USUARIO DIGITAR NA INCLUS?O
void digitos_usuario(){
	
	abrir_arquivo_jogos();
	while(!feof(list))
	 {
	 	
	 	if(fread(&jogo, sizeof(jogo), 1, list)==1 && jogo.game.excluir=='N')
	 	jogo.game.chave_mestre++;
	 	jogo.game.codigo = jogo.game.chave_mestre;
	 }
	
	jogo.game.excluir = 'N';
	fflush(stdin);
	gotoxy(21,4); printf("%d",jogo.game.codigo+1);
    gotoxyz(29,5); gets(jogo.game.titulo);
    gotoxyz(24,6); gets(jogo.game.produtora);
    gotoxyz(27,7); gets(jogo.game.distribuidora);
    gotoxyz(21,8); gets(jogo.game.genero);
    gotoxyz(25,9); gets(jogo.game.plataforma);
do{
		gotoxy(33,10); scanf("%d", &jogo.dia);
		fflush(stdin);
		erro = consistencia('a',2,1,jogo.dia,jogo.mes,jogo.ano);
    	
    	if(erro == 1)
			{	
				gotoxy(44,10); printf("Valor invalido ");
				gotoxy(33,10); printf("  ");
			}
		else
			gotoxy(44,10); printf("              ");
		    
	}while(erro == 1);

	do{
		fflush(stdin);
		gotoxy(36,10); scanf("%d", &jogo.mes);
    	erro = consistencia('a',2,2,jogo.dia,jogo.mes,jogo.ano);
		
		if(erro == 1)
			{	
				gotoxy(44,10); printf("Valor invalido ");
				gotoxy(36,10); printf("  ");
			}
		else
			gotoxy(44,10); printf("              ");
		
	}while(erro == 1);
	
	do{
		fflush(stdin);
		gotoxy(39,10); scanf("%d", &jogo.ano);
		erro = consistencia('a',2,3,jogo.dia,jogo.mes,jogo.ano);
				
		if(erro == 1)
			{	
				gotoxy(44,10); printf("Valor invalido ");
				gotoxy(39,10); printf("  ");
			}
		else
			gotoxy(44,10); printf("              ");
		
	}while(erro == 1);
    gotoxyz(13,11); printf("Deseja salvar os dados?(S/N) ");
    gotoxyz(43,11); jogo.game.excluir = getch();
    
    if (jogo.game.excluir == 's' || jogo.game.excluir == 'S')
    {
        jogo.game.excluir = 'N';
        salvar_dados();
    }
    else
    {
        gotoxyz(13,2);printf("Erro 04: Dados NÃO foram salvos com sucesso!");
        gotoxyz(13,3);printf("Pressione qualquer tecla para continuar!");
        getch();
    }
    
    
}

//VOID PARA INCLUS?O DOS DADOS.
void incluir_Jogo(){
    abrir_arquivo_jogos();
    
    system("cls");
    
    gotoxyz(13,4); printf("Código: ");
    gotoxyz(13,5); printf("Nome do título: ");
    gotoxyz(13,6); printf("Produtora: ");
    gotoxyz(13,7); printf("Ditribuidora: ");
    gotoxyz(13,8); printf("Gênero: ");
    gotoxyz(13,9); printf("Plataforma: ");
    gotoxyz(13,10); printf("Data de lançamento:   /  /  ");
    
    digitos_usuario();
    
}

void digitos_pessoa(){
    
    jogo.game.excluir = 'N';
    
    fflush(stdin);
    gotoxyz(21,4); gets(jogo.people.nome);
    gotoxyz(21,5); gets(jogo.people.email);
    
    gotoxyz(13,11); printf("Deseja salvar os dados?(S/N) ");
    gotoxyz(43,11); jogo.game.excluir = getch();
    
    if (jogo.game.excluir == 's' || jogo.game.excluir == 'S')
    {
        jogo.game.excluir = 'N';
        salvar_dados();
    }
    else
    {
        gotoxyz(13,2);printf("Erro 07: Cadastros NÃO foram salvos com sucesso!");
        gotoxyz(13,3);printf("Pressione qualquer tecla para continuar!");
        getch();
    }
    
    
}

void incluir_pessoa(){
	abrir_arquivo_jogos();
	abrir_arquivo_pessoas();
    
    system("cls");
    
    gotoxyz(13,4); printf("Nome: ");
    gotoxyz(13,5); printf("E-mail: ");
   // gotoxy(13,6); printf("Senha: ");
    
    digitos_pessoa();
    
}
void bemvindo()
{
	system("Title Locadora Smigol - BETA");
    system("cls");
    system("color 0F");
    gotoxyz(13,2); printf("BEM VINDO A LOCADORA SMIGOL!");
    gotoxyz(17,3);printf("Onde voce encontra seus jogos preciosos!");
    gotoxyz(10,7);printf("Pressione qualquer tecla para avançar!");
    getche();
    fflush(stdin);
    system("cls");    
}

main(){

    setlocale(LC_ALL, "Portuguese");
    int escolhas = 0;
    int erros=0;
    char escolha;

    bemvindo();
    
    //MENU

    do{

    fflush(stdin);
	system("color 0F");
	gotoxyz(13,1); printf("Locadora Smigol - Versão BETA");
    gotoxyz(13,3); printf("MENU:");
    gotoxyz(13,5); printf("1-Cadastrar Jogos");
    gotoxyz(13,6); printf("2-Consultar Jogos");
    gotoxyz(13,7); printf("3-Alterar Jogos");
   // gotoxyz(13,8); printf("4-Excluir Jogos");
	//gotoxyz(13,8); printf("4-Cadastrar Usuários");
    //gotoxyz(13,9); printf("5-Consultar Usuários");
    //gotoxyz(13,10); printf("6-Alterar Usuários");
    //gotoxyz(13,11); printf("7-Excluir Usuários");
    gotoxyz(13,8); printf("4-Créditos");
    gotoxyz(13,9); printf("5-Sair");
    gotoxyz(13,11); printf("| |                                           ");
    gotoxyz(14,11); scanf("%d",&escolha);
    fflush(stdin);
    //gotoxyz(14,16); escolha = getchar();
     
     switch(escolha)
     {
         case 0: admin();
         		 system("cls");
         		 fclose(list);
         		 break;
		 
		 case 1: system("color 0A"); 
		 		 incluir_Jogo();
                 system("cls");
                 fclose(list);
                 break;
        
		 case 2:
				if((list = fopen("Catalogo.bin", "rb")) == NULL) /* Abre arquivo bin?rio para escrita */
   					{
					    gotoxyz(13,18);printf("Erro 06: Nenhum jogo cadastrado!");
						getch();
					}
					else
					{
						system("color 0B");
		 				consulta_jogos();
                	 	system("cls");
                	 	fclose(list);
                 		break;
             		}
    
             
		 case 3: //alterar_jogos();
                 system("cls");
                 fclose(list);
                 break;
		
		         
     /*   case 4: system("color 0E");
		 		 incluir_pessoa();
                 system("cls");
                 break;
    
       case 5:
				if((list = fopen("Pessoas.bin", "rb")) == NULL) /* Abre arquivo bin?rio para escrita 
   					{
					    gotoxyz(13,18);printf("Erro 08: Nenhum usuário cadastrado!");
						getch();
					}
					else
					{
						system("color 0B");
		 				consulta_pessoas();
                	 	system("cls");
                 		break;
             		}
             		
    
    
    	case 6: //alterar_pessoas();
               system("cls");
               break;
               
        case 7: system("cls");
				excluir_users();
				break;*/
    
        case 4: creditos();
                system("cls");
                 break;
                
    
        case 5: saida();
                 system("cls");
                 break;
    
        default:
                gotoxyz(13,18); printf("Erro 05: Valor inválido!");
                
     }
    
     }while(escolhas == 0);

}

