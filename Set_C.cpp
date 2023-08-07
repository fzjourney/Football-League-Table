#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(); //tampilan menu
void score(); //input menang,seri,dan kalah
void table(); //menampilkan klasemen
void sData(); //scanf file txt

struct data
{
	char team[201];
	int win = 0;
	int tie = 0;
	int lose = 0;
} league[201];

int main()
{
	menu();
	return 0;
}

void sData() //function scan file txt
{
	FILE *ptr;
	int x=0;
	
	ptr=fopen("euclub.txt","r");
	while(fscanf(ptr, "%[^,],%d,%d,%d\n",&league[x].team, &league[x].win, &league[x].tie, &league[x].lose) !=EOF)
	{
		x++;
	}
	fclose(ptr);
}

void menu() //function tampilan menu
{
	int n;
	system("cls");
	printf("\t==================================\n");
	printf("\t	    Main Menu			\n");
	printf("\t==================================\n");
	printf("\t1. Input hasil pertandingan\n");
	printf("\t2. Klasemen Liga\n");
	printf("\t0. Exit\n");
	
	printf("\n\t Pilih menu yang dituju (1,2,0): ");
	scanf("%d", &n);
	getchar();
	
	switch(n)
	{
		case 1 : // Input hasil pertandingan
		score();
		break;
		
		case 2 : // klasemen liga
		table();
		break;
		
		case 0 : // exit program
		exit(0);
		break;
		
		default : //jika tidak ada di menu
		printf("\t Pilih angka yang ada pada menu, tekan tombol apa saja untuk kembali...");
		getchar();
		menu();
		break;
	}
}

void score() //function input score
{
	sData();
	char name[201];
	system("cls");
	
	printf("\t==================================\n");
	printf("\t	    Input Score			\n");
	printf("\t==================================\n");
	
	printf("\tClub: ");
	scanf("%[^\n]", &name);
	getchar();
	
	int temp = -1;
	int i;
	for(i=0;i<9;++i)
	{
		if(strcmp(name, league[i].team)==0)
		{
			temp=i;
		}
	}
	if(temp==-1)
	{
		printf("\tClub Tidak ditemukan\n");
		getchar();
		menu();
	}
	else if(temp!= -1)
	{
		int w,t,l,i;
		printf("\tWin	: "); scanf("%d",&w);
		printf("\tTie	: "); scanf("%d",&t);
		printf("\tLose	: "); scanf("%d",&l);
		
		league[temp].win += w;
		league[temp].tie += t;
		league[temp].lose += l;
		
		FILE *ptr;
		ptr = fopen("euclub.txt", "w");
		for(i=0;i < 9;++i)
		{
			fprintf(ptr,"%s,%d,%d,%d\n", league[i].team, league[i].win, league[i].tie, league[i].lose);
		}
		fclose(ptr);
		menu();
	}
}

void table() //function klasemen liga
{
	sData();
	system("cls");
	int i,j;
	
	for(i=0;i < 9;++i)
	{
		for(j=0;j < 9-1-i; ++j)
		{
			if(league[j].win < league[j+1].win)
			{
				data temp = league[j+1];
				league[j+1]=league[j];
				league[j]=temp;
			}
		}
	}
	printf("\t====================================================\n");
	printf("\t\tClub \t\t     Points     W    D   L  \n");
	printf("\t====================================================\n");	
	
	int k;
	for(k=0;k < 9;++k)
	{
		int formula=(league[k].win*3)+(league[k].tie*1)+(league[k].lose*0);
		printf("\t\t%-22s %-8d %-4d %-3d %d\n",league[k].team, formula,league[k].win,league[k].tie,league[k].lose);
		printf("\t----------------------------------------------------\n");
	}
	printf("\t====================================================\n");
	printf("\t\tTekan tombol apa saja untuk kembali... \n");
	printf("\t====================================================\n");
	getchar();
	menu();	
}
