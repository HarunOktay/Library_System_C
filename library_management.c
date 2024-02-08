#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx	STRUCT SEGMENT  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
typedef struct Ogrenci{
	char ogrID[10];
	char ad[30];
	char soyad[30];
	int puan;
	struct Ogrenci *Next;
	struct Ogrenci *Prev;
}OGRENCI;

typedef struct Yazar{
	int yazarID;
	char yazarAd[30];
	char yazarSoyad[30];
	struct Yazar *Next;
}YAZAR;

typedef struct KitapOrnek{
	char EtiketNo[20];
	char Durum[8];
	struct KitapOrnek *Next;
}KITAPORNEK;

typedef struct Kitap{
	char KitapAdi[30];
	char ISBN[15];
	int adet;
	struct Kitap *Next;
	struct KitapOrnek *head;
}KITAP;

typedef struct KitapYazar{
	char ISBN[20];
	int yazarID;
}KITAPYAZAR;

typedef struct Tarih{
	int yil:12;
	int ay:4;
	int gun:5;
}TARIH;

typedef struct KitapOdunc{
	char EtiketNo[20];
	char ogrID[8];
	int islemTipi:1;
	TARIH *islemTarihi;
}KITAPODUNC;


// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX	FUNCTION DEFINITIONS    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX//
//MENU
void MENU_1(int stage);
void mainMENU(OGRENCI* STDhead, YAZAR* YAZARhead, KITAP* KITAPhead, int count);
void StudentMENU(OGRENCI* STDhead);
void YazarMENU(YAZAR* YAZARhead,int count,KITAPYAZAR** KITAPYAZARarr);
void KitapMENU(KITAP* KITAPhead);
//OGRENCI
void SetStd(OGRENCI **head);
void reSetStd(OGRENCI* head);
void ogrenciSil(OGRENCI **head);
void printList(OGRENCI* head);
void printList_S(OGRENCI* head);
void addNew_last(OGRENCI** head);
void addNew_last_S(OGRENCI** head);
void ogrenciDuzenle(OGRENCI **head);
void printOgrenci(OGRENCI* head);
//YAZAR
void reSetYazar(YAZAR* head);
int SetYazar(YAZAR **head);
int sortedInsert(YAZAR** head, int yazarCount);
void locatedInsert(YAZAR** head, char* ad, char* soyad, int id);
void yazarLocatedSil(YAZAR **head, int ID);
int yazarDuzenle(YAZAR **head,int count);
void yazarSil(YAZAR **head,KITAPYAZAR** KITAPYAZARarr);
void printYazar(YAZAR* head);
void yazarAra(YAZAR **head,int count,KITAPYAZAR** KITAPYAZARarr);
void printSpecYazar(YAZAR* head,KITAPYAZAR** KITAPYAZARarr);
void printList_Y(YAZAR* head);
//KITAP
int SetBook(KITAP **head);
void SEQKitapInsert(KITAP** head, char* kitapAd, char* ISBN);
void reSetBook(KITAP* head);
void printKitap(KITAP* head);
void printKitapList(KITAP* head);
void kitapLocatedInsert(KITAP** head, char* kitapAd, char* ISBN, int adet);
void kitapLocatedSil(KITAP **head, char* ISBN);
void kitapSil(KITAP **head);
void kitapDuzenle(KITAP **head);
void kitapInsert(KITAP** head);
//KITAPYAZAR
void printKY(KITAPYAZAR** KITAPYAZARarr, int N);
void setAuth(KITAPYAZAR** arr);
void reSetKY(KITAPYAZAR** arr,int N);
void guncelleKY(KITAPYAZAR** KITAPYAZARarr);
void addKY(KITAPYAZAR*** KITAPYAZARarr, int *N,YAZAR **YAZARhead, KITAP **KITAPhead);
void KitapYazarMENU(KITAP * KITAPhead, YAZAR* YAZARhead, KITAPYAZAR** KITAPYAZARarr);
int ctrlBook(KITAP **head, char* exID);
int ctrlYazar(YAZAR **head, int exID);
int countNewLineKY();
//EMANET ��LEMLER�
void EmanetMENU(OGRENCI* STDhead, KITAP* KITAPhead);//,KITAPODUNC** KITAPODUNCarr
void EmanetVer(KITAPODUNC** KITAPODUNCarr, KITAP** KITAPhead, OGRENCI** STDhead,int sayac);
void EmanetAl(KITAPODUNC** KITAPODUNCarr, KITAP** KITAPhead, OGRENCI** STDhead,int sayac);
//int Iskitap(KITAP* head, char* kitap, char* degergetir);
int IsOgrenci(OGRENCI* head, char* ogrenci);
void setOdunc(KITAPODUNC** arr);
void printEmanetler(KITAPODUNC** KITAPODUNCarr, int N);
int countNewLineKO();

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx	MAIN SEGMENT  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX//
int main(){
	setlocale(LC_ALL,"Turkish");
	int count,i, N;
//	TARIH* CurrentDate = (TARIH*)malloc(sizeof(TARIH)); 
//	printf("Bug�n�n tarihini giriniz:");
//	scanf("%d%d%d",CurrentDate->gun,CurrentDate->ay,CurrentDate->yil);
	OGRENCI* STDhead = NULL;
	YAZAR* YAZARhead = NULL;
	KITAP* KITAPhead = NULL;
	
	SetStd(&STDhead);	SetBook(&KITAPhead);	count = SetYazar(&YAZARhead);
	
	mainMENU(STDhead,YAZARhead,KITAPhead,count);
	return 0;
}//END MAIN

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   MENU SEGMENT 	XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX									//

void DeleteAll(){
	remove("KitapYazar.csv");
	remove("Kitaplar.csv");
	remove("Ogrenciler.csv");
	remove("Yazarlar.csv");
	remove("KitapOdunc.csv");
	printf("TUM DOSYALAR BA�ARIYLA �MHA ED�LD�!");
	getch();
}

void MENU(int stage){
	switch(stage){
		case 0:
			printf("K�t�phane Y�netim Sistemine Ho�geldiniz....\n");
			printf("Yapmak istedi�iniz i�lem t�r�n� giriniz..\n\n");
			printf("��renci i�lemleri i�in:               \"1\"\n");
			printf("Yazar i�lemleri i�in:                 \"2\"\n");
			printf("Kitap i�lemleri i�in:                 \"3\"\n");
			printf("Kitap-Yazar �li�kilendirmeleri i�in   \"4\"\n");
			printf("Emanet ��lemleri i�in                 \"5\"\n");
			printf("Programdan ��k�� i�in:                \"0\"\n");
			printf("Numaralar�n� se�iniz...\n");
			break;
		case 1:
			system("cls");
			printf("------------��RENC� ��LEMLER�--------------\n");
			printf("��renci Eklemek ��in:                 \"1\"\n");	
			printf("��renci Silmek ��in:                  \"2\"\n");
			printf("��renci Bilgilerini D�zenlemek ��in:  \"3\"\n");
			printf("��rencileri listelemek i�in:          \"4\"\n");
			printf("��renci i�lemlerinden ��k�� i�in:     \"0\"\n");
			break;
		case 2:
			system("cls");
			printf("-------------YAZAR ��LEMLER�---------------\n");
			printf("Yazar Eklemek ��in:                   \"1\"\n");	
			printf("Yazar Silmek ��in:                    \"2\"\n");
			printf("Yazar Bilgilerini D�zenlemek ��in:    \"3\"\n");
			printf("Yazarlar� listelemek i�in:            \"4\"\n");
			printf("Spesifik yazar listelemek i�in:       \"5\"\n");
			printf("Yazar i�lemlerinden ��k�� i�in:       \"0\"\n");
			break;
		case 3:
		
			system("cls");
			printf("-------------K�TAP ��LEMLER�---------------\n");
			printf("Kitap Eklemek ��in:                  \" 1\"\n");	
			printf("Kitap Silmek ��in:                    \"2\"\n");
			printf("Kitap Bilgilerini D�zenlemek ��in:    \"3\"\n");
			printf("Kitaplar� listelemek i�in:            \"4\"\n");
			printf("Kitap i�lemlerinden ��k�� i�in:       \"0\"\n");
			break;
		case 4:
			system("cls");
			printf("-------K�TAP-YAZAR �L��K�LEND�RMELER�------\n");
			printf("Kitap-Yazar listelemek i�in:          \"1\"\n");
			printf("Kitap-Yazar ili�kisi eklemek i�in:    \"2\"\n");
			printf("Kitap-Yazar ili�kisi g�ncellemek i�in:\"3\"\n");
			printf("Kitap-Yazar i�lemlerinden ��k�� i�in: \"0\"\n");
			break;
		case 5:
			system("cls");
			printf("--------------EMANET ��LEMLER�-------------\n");
			printf("Emanet Listelemek ��in:               \"1\"\n");
			printf("��renciye Kitap emanet vermek i�in:   \"2\"\n");
			printf("��renciden kitap teslim almak ��in:   \"3\"\n");
			printf("Cezal� ��renci G�r�nt�le:             \"4\"\n");
			printf("Kitap teslim etmemi� ��renci G�r�nt�le\"5\"\n");
			printf("Emanet i�lemlerinden ��k�� i�in:      \"0\"\n");
			break;
		case 6:
			printf("BURN THEM ALL");
			break;
	}
}

void mainMENU(OGRENCI* STDhead, YAZAR* YAZARhead, KITAP* KITAPhead, int count){
	int N, i,NE;
	char kill;
	N = countNewLineKY();
	KITAPYAZAR** KITAPYAZARarr = (KITAPYAZAR**)malloc(N*sizeof(KITAPYAZAR*));
	for(i = 0 ; i < N ; i++){
		KITAPYAZARarr[i] = (KITAPYAZAR*)malloc(1*sizeof(KITAPYAZAR));
 	}
 	setAuth(KITAPYAZARarr);
 	
 	
// 	NE = countNewLineKO();
//	KITAPODUNC** KITAPODUNCarr = (KITAPODUNC**)malloc(NE*sizeof(KITAPODUNC*));
//	for(i = 0 ; i < NE ; i++){
//		KITAPODUNCarr[i] = (KITAPODUNC*)malloc(1*sizeof(KITAPODUNC));
// 	}
// 	setOdunc(KITAPODUNCarr);
 	
	system("cls");
	int choice;
	MENU(0);
	scanf("%d", &choice);
	switch(choice){
	//��RENC� ��LEMLER�
		case 1:
			StudentMENU(STDhead);		
			break;
	//YAZAR ��LEMLER�
		case 2:
			YazarMENU(YAZARhead,count,KITAPYAZARarr);
			break;	
			
	//K�TAP ��LEMLER�
		case 3:
			KitapMENU(KITAPhead);	
			break;
	//K�TAP-YAZAR ��LEMLER�
		case 4:
			KitapYazarMENU(KITAPhead,YAZARhead,KITAPYAZARarr);
			break;
	//EMANET ��LEMLER�
		case 5:
			EmanetMENU(STDhead,KITAPhead);
			break;
		case 6:
			printf("Emin Misin?\nE");
			scanf(" %c",&kill);
			if(!strcmp("kill","E")) DeleteAll();
			getch();
			break;
		case 0:
			system("cls");
			printf("Program Ba�ar�yla Kapand�...");
			return;
			break;
		default:
			printf("Girdi�iniz Numaran�n ��lem Kar��l��� Bulunmamakta\nGe�erli Bir Numara Se�iniz.\n");
			getch();
			system("cls");
			break;		
	}//END SWITCH
		
	mainMENU(STDhead,YAZARhead,KITAPhead,count);
}
void EmanetMENU(OGRENCI* STDhead, KITAP* KITAPhead){//KITAPODUNC** KITAPODUNCarr
	int i, N, choice;
//	N = countNewLineKO();
//	setOdunc(KITAPODUNCarr);
	MENU(5);
	scanf("%d",&choice);
	switch(choice){
		default:
			system("cls");
			printf("PROGRAMIN BU KISMI YAPIM A�AMASINDADIR...\n");
			printf("G�ncellemeleri �uradan takip edebilirsiniz ----> %s","https://github.com/HarunOktay" );
			printf("\n\n\n\n�IKI� ���N B�RAZDAN D�ND���N�Z MENUDE 0 TU�LAYINIZ.");
			printf("\nherhangi bir tu�a bas�n�z...");
			getch();
			system("cls");
			break;
//		case 1:
//			system("cls");
//			printEmanetler(KITAPODUNCarr,N);
//			printf("Herhangi Bir Tu�a Bas�n�z.");
//			getch();
//			system("cls");
//			break;
//		case 2:
//			system("cls");
//			EmanetVer(KITAPODUNCarr,KITAPhead,STDhead,sayac);
//			break;
//		case 3:
//			system("cls");
//			EmanetAl(KITAPODUNCarr,KITAPhead,STDhead,sayac);
//			break;
		case 0:
			system("cls");
			printf("Emanet i�lemlerinden ba�ar�yla ��kt�n�z...\n Herhangi Bir Tu�a Bas�n�z.");
			getch();
			system("cls");
			return;
	}
	EmanetMENU(STDhead,KITAPhead);//,KITAPODUNCarr
}
void KitapYazarMENU(KITAP * KITAPhead, YAZAR* YAZARhead,KITAPYAZAR** KITAPYAZARarr){
	int i, N,choice;
	N = countNewLineKY();
	setAuth(KITAPYAZARarr);
	MENU(4);
	scanf("%d",&choice);
	switch(choice){
		case 1:
			system("cls");
			printKY(KITAPYAZARarr,N);
			printf("Herhangi Bir Tu�a Bas�n�z.");
			getch();
			system("cls");
			break;
		case 2:
			system("cls");
			addKY(&KITAPYAZARarr,&N,&YAZARhead, &KITAPhead);
			break;
		case 3:
			system("cls");
			guncelleKY(KITAPYAZARarr);
			break;
		case 0:
			system("cls");
			printf("Kitap-Yazar i�lemlerinden ba�ar�yla ��kt�n�z...\n Herhangi Bir Tu�a Bas�n�z.");
			getch();
			system("cls");
			return;
	}
	KitapYazarMENU(KITAPhead, YAZARhead,KITAPYAZARarr);
}
void StudentMENU(OGRENCI* STDhead){
	MENU(1);
	int choice;
	scanf("%d", &choice);
	switch(choice){
		case 1:							
			addNew_last_S(&STDhead);							
			break;
		case 2:
			ogrenciSil(&STDhead);
			printf("Kapatmak ��in Herhangi Bir Tu�a Bas�n�z...");
			getch();
			break;
		case 3:
			ogrenciDuzenle(&STDhead);
			printf("Kapatmak ��in Herhangi Bir Tu�a Bas�n�z...");
			getch();							
			break;
		case 4:
		    printList_S(STDhead);
			printf("Listeyi Kapatmak ��in Herhangi Bir Tu�a Bas�n�z...");
			getch();
			break;
		case 0:
			system("cls");
			printf("��renci i�lemlerinden ba�ar�yla ��kt�n�z...\n Herhangi Bir Tu�a Bas�n�z.");
			getch();
			system("cls");
			return;
		default:
			printf("Girdi�iniz Numaran�n ��lem Kar��l��� Bulunmamakta\nGe�erli Bir Numara Se�iniz.\n");
			system("cls");
			break;
	}
	StudentMENU(STDhead);		
}

void YazarMENU(YAZAR* YAZARhead,int count,KITAPYAZAR** KITAPYAZARarr){
	int choice;
	MENU(2);
	scanf("%d", &choice);
	switch(choice){
		case 1://YAZAR EKLE
			count = sortedInsert(&YAZARhead,count);
			reSetYazar(YAZARhead);
			break;
		case 2://YAZAR S�L
			yazarSil(&YAZARhead,KITAPYAZARarr);
			reSetYazar(YAZARhead);
			printf("Kapatmak ��in Herhangi Bir Tu�a Bas�n�z...");
			getch();
			break;
		case 3://YAZAR D�ZENLE
			count = yazarDuzenle(&YAZARhead,count);
			reSetYazar(YAZARhead);
			printf("Kapatmak ��in Herhangi Bir Tu�a Bas�n�z...");
			getch();							
			break;
		case 4:
			printList_Y(YAZARhead);//YAZAR L�STELE
			printf("Listeyi Kapatmak ��in Herhangi Bir Tu�a Bas�n�z...");
			getch();
			break;
		case 5:
			yazarAra(&YAZARhead,count,KITAPYAZARarr);
			getch();
			system("cls");
			break;
		case 0:
			system("cls");
			printf("Yazar i�lemlerinden ba�ar�yla ��kt�n�z...\n Herhangi Bir Tu�a Bas�n�z.");
			getch();
			system("cls");
			return;
			break;
		default:
			printf("Girdi�iniz Numaran�n ��lem Kar��l��� Bulunmamakta\nGe�erli Bir Numara Se�iniz.\n");
			system("cls");
			break;
		}
	YazarMENU(YAZARhead,count,KITAPYAZARarr);
}
void KitapMENU(KITAP* KITAPhead){
	MENU(3);
	int choice;
	scanf("%d",&choice);
	switch(choice){
		case 1://KITAP EKLE CASE
			kitapInsert(&KITAPhead);
			reSetBook(KITAPhead);
			break;
		case 2:
			kitapSil(&KITAPhead);
			printf("Kapatmak ��in Herhangi Bir Tu�a Bas�n�z...");
			reSetBook(KITAPhead);
			getch();
			break;
		case 3:
			kitapDuzenle(&KITAPhead);
			printf("Kapatmak ��in Herhangi Bir Tu�a Bas�n�z...");
			reSetBook(KITAPhead);
			getch();							
			break;
		case 4:
			printKitapList(KITAPhead);
			printf("Listeyi Kapatmak ��in Herhangi Bir Tu�a Bas�n�z...");
			getch();
			break;
		case 0:
			system("cls");
			printf("Kitap i�lemlerinden ba�ar�yla ��kt�n�z...\n Herhangi Bir Tu�a Bas�n�z.");
			getch();
			system("cls");
			return;
			break;
		default:
			printf("Girdi�iniz Numaran�n ��lem Kar��l��� Bulunmamakta\nGe�erli Bir Numara Se�iniz.\n");
			system("cls");
			break;
	}
	KitapMENU(KITAPhead);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX	��RENC� SEGMENT	XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX	//

void SetStd(OGRENCI **head) {
	   // Open the CSV file
	FILE *STD =fopen("Ogrenciler.csv", "r");
    if (STD == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
	int flag = 1;
    while (flag) {
     	char* id = (char*)malloc(sizeof(char)*30);
     	char* firstName = (char*)malloc(sizeof(char)*30);
     	char* lastName = (char*)malloc(sizeof(char)*30);
//		char id[30];
//   		char firstName[30];
//   		char lastName[30];
        int credit;
        int result = fscanf(STD, "%[^,],%[^,],%[^,],%d\n", id, firstName, lastName, &credit);
		
        // Check if we reached the end of the file
        if (result == EOF) {
            flag = 0;
        }
		if(flag){
	        OGRENCI *newNode = (OGRENCI*) malloc(sizeof(OGRENCI));
	        
	        strcpy(newNode->ogrID,id);strcpy(newNode->ad,firstName);strcpy(newNode->soyad,lastName);
	        free(id);free(firstName);free(lastName); //FREE MALLOCS
	        newNode->puan = credit;
	        newNode->Next = NULL;
			newNode->Prev=NULL;
	        // Add the new node to the linked list
	        if (*head == NULL) *head = newNode;
			else {
	            OGRENCI *temp = *head;
	            while (temp->Next != NULL) {
	                temp = temp->Next;
	            }
	            temp->Next = newNode;
	            newNode->Prev = temp;
	       }
		}
	}
   fclose(STD);//CLOSE FILE
}
void reSetStd(OGRENCI* head){
	FILE *STD =fopen("Ogrenciler.csv", "w");
	fclose(STD);
	STD =fopen("Ogrenciler.csv", "w+");
    if (STD == NULL) {
    	printf("Error opening file\n");
    exit(1);
    }
	while(head->Next){
		// Open the CSV file
        fprintf(STD, "%s,%s,%s,%d\n", head->ogrID, head->ad, head->soyad, head->puan);
        head = head->Next;
	}
	fprintf(STD, "%s,%s,%s,%d", head->ogrID, head->ad, head->soyad, head->puan);
	fclose(STD);
}

void ogrenciDuzenle(OGRENCI **head){
	char* id = (char*)malloc(sizeof(char)*30);
	char* ogrID = (char*)malloc(sizeof(char)*30);
	char* ad = (char*)malloc(sizeof(char)*30);
	char* soyad = (char*)malloc(sizeof(char)*30);
//	char id[30];
//	char ogrID[30] ;
//	char ad[30];
//    char soyad[30];
	int found = 0;
	printf("Bilgilerini de�i�tirmek istedi�iniz ��renci ID'si:\n");
	scanf("%s", id);
	OGRENCI *tmp = *head;
	OGRENCI *prev = NULL;
	while(tmp && !found){
		if(!strcmp(tmp->ogrID,id)){
			found = 1;
			printf("�u anki ��renci bilgileri:\n");
			printOgrenci(tmp);
			printf("��rencinizin yeni bilgilerini giriniz.");
			printf("\nAD:");
			scanf("%s",ad);
			strcpy(tmp->ad,ad);
			printf("\nSOYAD:");
			scanf("%s",soyad);
			strcpy(tmp->soyad,soyad);	
			printf("\nID");
			scanf("%s",ogrID);
			strcpy(tmp->ogrID,ogrID);
			printf("\n��renci Ba�ar�yla D�zenlendi...");
		}
		prev = tmp;
		tmp = tmp->Next;
	}
	if(!found) printf("Ogrenci Bulunamad�\n");
	else reSetStd(*head);
	free(ad); free(soyad); free(id); free(ogrID);
}


void ogrenciSil(OGRENCI **head){
	char* id = (char*)malloc(sizeof(char)*30);
//	char id[30];
	int found = 0;
	printf("Silmek istedi�iniz ��rencinin ID'sini giriniz:\n");
	scanf("%s",id);
	OGRENCI *tmp = *head;
	OGRENCI *prev = NULL;
	while(tmp && !found){
		if(!strcmp(tmp->ogrID,id)){
			printf("Sildi�iniz ��renci bilgileri:\n");
			printOgrenci(tmp);
			found = 1;
			printf("\n��renci Ba�ar�yla silindi...\n");
			if(!prev){
				*head = tmp->Next;
			}
			else prev->Next = tmp->Next;
		}
		prev = tmp;
		tmp = tmp->Next;
	}
	if(!found) printf("Ogrenci Bulunamad�\n"); 
	else reSetStd(*head);
	free(id);
}

void printOgrenci(OGRENCI* head){
	printf("��renci Ad�:%s\n��renciSoyad�:%s\n��renciNumaras�:%s\n��renciPuan�:%d\n------------------------------\n",head->ad,head->soyad,head->ogrID,head->puan);
}

void printList_S(OGRENCI* head){
	if(!head){printf("Listeniz Tamamen Bo�\n"); return;}
	while(head){
		printf("��renci Ad�:%s\n��renciSoyad�:%s\n��renciNumaras�:%s\n��renciPuan�:%d\n------------------------------\n", head->ad, head->soyad, head->ogrID, head->puan);
		head = head->Next;
	}
}

void addNew_last_S(OGRENCI** head){
	int found = 0;
	char* ID = (char*)malloc(sizeof(char)*30);
//	char ID [30];
	OGRENCI* newElement = (OGRENCI*)malloc(1*sizeof(OGRENCI));
	printf("Eklemek �stediginiz ��rencinin Bilgilerini Giriniz.\n");
	printf("\nAD: ");
	getchar();
	scanf("%[^\n]s",newElement->ad);
	printf("\nSOYAD: ");
	scanf("%s",newElement->soyad);
	printf("\nID: ");
	scanf("%s",ID);
	newElement->puan = 100;
	newElement->Next = NULL;
	newElement->Prev = NULL;
	OGRENCI* lastElement;
	lastElement = *head;

	OGRENCI *tmp = *head;
	while(tmp){
		if(!strcmp(tmp->ogrID,ID)){
			found = 1;
			printf("Halihaz�rda ayn� ID'ye sahip ��renci bulunmakta, yeni bir ID vermeyi deneyiniz");
			printf("\nID");
			scanf("%s", ID);
			tmp = *head;
		}
		if(!found) tmp = tmp->Next;
		else found = 0;
	}
	strcpy(newElement->ogrID,ID);	
			
	if(!*head){
		*head = newElement;
		reSetStd(*head);
		return;
	}
	while(lastElement->Next){
		lastElement = lastElement->Next;
	}
	lastElement->Next = newElement;
	newElement->Prev = lastElement;
	reSetStd(*head);
//	free(ID);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX	YAZAR SEGMENT XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx	//



void yazarAra(YAZAR **head,int count,KITAPYAZAR** KITAPYAZARarr){
	
	int yazarID, exID;
	char* yazarAd = (char*)malloc(sizeof(char)*30);
	char* yazarSoyad = (char*)malloc(sizeof(char)*30);
//	char yazarAd[30]; 
//    char yazarSoyad[30];
	int found = 0;
	printf("Aramak istediginiz yazar�n ad�n� giriniz.");	scanf("%s",yazarAd);
	YAZAR *tmp = *head;
	
	while(tmp && !found){
		if(tmp->yazarAd == yazarAd){
			found = 1;
			printf("\nYazar Ba�ar�yla Bulundu....");
			printSpecYazar(tmp,KITAPYAZARarr);
		}
		tmp = tmp->Next;
	}
	if(!found) printf("Yazar Bulunamad�\n");
	free(yazarAd); free(yazarSoyad);
	return;
}

int SetYazar(YAZAR **head) {
	int counter = 1;
	   // Open the CSV file
	FILE *YZR=fopen("Yazarlar.csv", "r");
    if (YZR == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
	int result = 1;
	
    while (result != EOF) {
    	char* Ad = (char*)malloc(sizeof(char)*30);
    	char* Soyad = (char*)malloc(sizeof(char)*30);
		int id;
//   		char Ad[30];
//   		char Soyad[30];
        result = fscanf(YZR, "%d,%[^,],%[^\n]\n",&id, Ad, Soyad);

        // Check if we reached the end of the file
        if (result != EOF) {
	        YAZAR *newNode = (YAZAR*) malloc(sizeof(YAZAR));
	        
	        strcpy(newNode->yazarAd, Ad);strcpy(newNode->yazarSoyad, Soyad); newNode->yazarID = id;
	
	        // Add the new node to the linked list
	        if (*head == NULL) *head = newNode;
			else {
	            YAZAR *temp = *head;
	            while (temp->Next != NULL) {
	                temp = temp->Next;
	            }
	            temp->Next = newNode;
	       }
		}
		counter = id;
		free(Ad); free(Soyad);
   }
   fclose(YZR);//CLOSE FILE
   return counter;
}

void reSetYazar(YAZAR* head){
	FILE *YZR =fopen("Yazarlar.csv", "w");
	fclose(YZR);
	YZR =fopen("Yazarlar.csv", "w+");
    if (YZR == NULL) {
    	printf("Error opening file\n");
    exit(1);
    }
	while(head->Next){
        fprintf(YZR, "%d,%s,%s\n",head->yazarID,head->yazarAd,head->yazarSoyad);
        head = head->Next;
	}
	fprintf(YZR,"%d,%s,%s",head->yazarID,head->yazarAd,head->yazarSoyad);
	fclose(YZR);
}


int sortedInsert(YAZAR** head, int yazarCount)
{
	
	YAZAR* newElement = (YAZAR*)malloc(1*sizeof(YAZAR));
	printf("Eklemek �stediginiz Yazar�n Bilgilerini Giriniz.\n");
	printf("\nAD:");	scanf("%s",newElement->yazarAd);
	printf("\nSOYAD:");	scanf("%s",newElement->yazarSoyad);
	
	yazarCount++; newElement->yazarID = yazarCount;		
	newElement->Next = NULL;
	
	
	
	locatedInsert(head,newElement->yazarAd,newElement->yazarSoyad,newElement->yazarID);
    return yazarCount;
}

void locatedInsert(YAZAR** head, char* ad, char* soyad, int id)
{
	YAZAR* newElement = (YAZAR*)malloc(1*sizeof(YAZAR));
	strcpy(newElement->yazarAd,ad);
	strcpy(newElement->yazarSoyad,soyad);
	newElement->yazarID = id;	
	newElement->Next = NULL;
	
	printf("D�zenledi�iniz yazar yeni bilgileri:\n");
	printYazar(newElement);
	
	YAZAR* lastElement;
	
    if(!*head ||(*head)->yazarID  >= newElement->yazarID){
    	newElement->Next = *head;
		*head = newElement;
		return;
	}
    lastElement = *head;
    while (lastElement->Next && lastElement->Next->yazarID < newElement->yazarID) {
            lastElement = lastElement->Next;
    }
    newElement->Next = lastElement->Next;
    lastElement->Next = newElement;
}

int yazarDuzenle(YAZAR **head,int count){
	
	int yazarID, exID;
	char* yazarAd = (char*)malloc(sizeof(char)*30);
	char* yazarSoyad = (char*)malloc(sizeof(char)*30);
//	char yazarAd[30]; 
//    char yazarSoyad[30];
	int found = 0;
	printf("Enter ID");	scanf("%d",&exID);
	YAZAR *tmp = *head;
	
	while(tmp && !found){
		if(tmp->yazarID ==exID){
			found = 1;
			printf("�u anki yazar bilgileri:\n");	printYazar(tmp);
			printf("Yazar�n yeni bilgilerini giriniz.");	printf("\nAD:");	scanf("%s",yazarAd);
			printf("\nSOYAD:");	scanf("%s",yazarSoyad);
			printf("\nID\n(D�KKAT!!!!! \n Yazar ID'sini de�i�tirmek yeni eklenen yazarlar�n kaydedilme s�ras�n�\nDo�rudan etkiler.\nEski ID'yi girmeniz tavsiye edilir.)\n");
			scanf("%d",&yazarID);
			
			yazarLocatedSil(head, exID);	locatedInsert(head, yazarAd, yazarSoyad, yazarID);
			
			printf("\nYazar Ba�ar�yla D�zenlendi...");
		}
		tmp = tmp->Next;
	}
	if(!found) printf("Yazar Bulunamad�\n");
	if(exID==yazarID || exID > yazarID){
		return count;
	}
	free(yazarAd); free(yazarSoyad);
	return yazarID;
}

void yazarLocatedSil(YAZAR **head, int ID){
	int found = 0;
	YAZAR *tmp = *head;
	YAZAR *prev = NULL;
	
	while(tmp && !found){
		if(tmp->yazarID==ID){
			printf("D�zenledi�iniz yazar eski bilgileri:\n");
			printYazar(tmp);
			found = 1;
			if(!prev){
				*head = tmp->Next;
			}
			else
				prev->Next = tmp->Next;
		}
		prev = tmp;
		tmp = tmp->Next;
	}
}

void yazarSil(YAZAR **head,KITAPYAZAR** KITAPYAZARarr){
	
	int ID, found = 0,N, i;
	YAZAR *tmp = *head;
	YAZAR *prev = NULL;
	
	printf("Enter ID");
	scanf("%d",&ID);
	
	while(tmp && !found){
		if(tmp->yazarID==ID){
			printf("Sildi�iniz yazar bilgileri:\n");
			printYazar(tmp);
			found = 1;
			if(!prev){
				*head = tmp->Next;
			}
			else
				prev->Next = tmp->Next;
			printf("\nYazar Ba�ar�yla silindi...");
		}
		prev = tmp;
		tmp = tmp->Next;
	}
	if(found){
		N = countNewLineKY();
		for(i = 0  ; i < N ; i++){
			if(KITAPYAZARarr[i]->yazarID == ID){
				KITAPYAZARarr[i]->yazarID = -1;
			}
		}
		reSetKY(KITAPYAZARarr,N);
	}
	if(!found) printf("Yazar Bulunamad�\n");
}
void printYazar(YAZAR* head){
	printf("Yazar�n Ad�:%s\nYazar�n Soyad�:%s\nYazar�n Numaras�:%d\n------------------------------\n",head->yazarAd,head->yazarSoyad,head->yazarID);
}
void printSpecYazar(YAZAR* head,KITAPYAZAR** KITAPYAZARarr){
	int N, i;
	printf("Yazar�n Ad�:%s\nYazar�n Soyad�:%s\nYazar�n Numaras�:%d\n------------------------------\n",head->yazarAd,head->yazarSoyad,head->yazarID);
	N = countNewLineKY();
	printf("yazar�n yazd��� kitaplar:\n-------------------------\n");
	for(i = 0  ; i < N ; i++){
		if(KITAPYAZARarr[i]->yazarID == head->yazarID){
			printf("%s\n", KITAPYAZARarr[i]->ISBN);
		}
	}
}

void printList_Y(YAZAR* head){
	if(!head){printf("Listeniz Tamamen Bo�\n"); return;}
	while(head){
		printf("Yazar�n Ad�:%s\nYazar�n Soyad�:%s\nYazar�n Numaras�:%d\n------------------------------\n",head->yazarAd,head->yazarSoyad,head->yazarID);
		head = head->Next;
	}
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   KITAP SEGMENT  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxxx//

int SetBook(KITAP **head){
	/*char isbn[30];
	char Name[30];*/
    int i, adet,result; 
    char* isbn = (char*)malloc(sizeof(char)*30);
    char* Name = (char*)malloc(sizeof(char)*30);
//    char isbn[30]; 
//	char Name[30]; 
	char em;
	   // Open the CSV file
	FILE *BOOK = fopen("Kitaplar.csv", "r");
    if (BOOK == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    // Read the data from the CSV file and add it to the linked list
    while (result != EOF) {
        result = fscanf(BOOK, "%[^,],%[^,],%d,%c", Name, isbn, &adet,&em);
        // Check if we reached the end of the file
        if (em == EOF) result = EOF;
        if (result != EOF) {
			for(i = 0 ; i < adet ; i++) SEQKitapInsert(head, Name, isbn);
 	  }
	}
	free(isbn); free(Name);
	fclose(BOOK);
}


void SEQKitapInsert(KITAP** head, char* kitapAd, char* ISBN){
	
	
	KITAP* newElement = (KITAP*)malloc(1*sizeof(KITAP));
	KITAPORNEK* newOrnek = (KITAPORNEK*)malloc(1*sizeof(KITAPORNEK));
	char* tmpStr = (char*)malloc(sizeof(char)*5);
//	char tmpStr[5];
	strcpy(newElement->KitapAdi,kitapAd);
	strcpy(newElement->ISBN,ISBN);
	newElement->Next = NULL;
	newElement->head = NULL;
	newOrnek->Next = NULL;
	int found = 0, i;
	
	KITAP* lastElement = *head;

	while(lastElement && !found){
		if(!strcmp(lastElement->ISBN,ISBN)){
			found = 1;			
			printf("Halihaz�rda ayn� ID'ye sahip %d kitap bulunmakta, rafa %d no:lu olarak ekleniyor",lastElement->adet,lastElement->adet+1);
			lastElement->adet++;			
			itoa(lastElement->adet,tmpStr,10);
	    	strcpy(newOrnek->EtiketNo,ISBN);	strcat(newOrnek->EtiketNo,"_");	strcat(newOrnek->EtiketNo,tmpStr);	strcpy(newOrnek->Durum,"rafta");
			KITAPORNEK *tmpb = lastElement->head;
			
			while(tmpb->Next){
				tmpb = tmpb->Next;
			}
			tmpb->Next = newOrnek;
			free(tmpStr);
			return;
		}
		lastElement = lastElement->Next;
	}	
	
	if(!*head || strcmp((*head)->ISBN,newElement->ISBN) > 0){
		itoa(1,tmpStr,10);
		strcpy(newOrnek->EtiketNo,ISBN);	strcat(newOrnek->EtiketNo,"_");	strcat(newOrnek->EtiketNo,tmpStr);	strcpy(newOrnek->Durum,"rafta");
		newElement->head = newOrnek;
    	newElement->Next = *head;
    	newElement->adet = 1;
		*head = newElement;
		free(tmpStr);
		return;
	}
	

	
    lastElement = *head;
    while (lastElement->Next && strcmp(lastElement->Next->ISBN,newElement->ISBN) < 0) {
            lastElement = lastElement->Next;
    }
    itoa(1,tmpStr,10);
    strcpy(newOrnek->EtiketNo,ISBN);	strcat(newOrnek->EtiketNo,"_");	strcat(newOrnek->EtiketNo,tmpStr);	strcat(newOrnek->Durum,"rafta");
	newElement->head = newOrnek;
    newElement->adet = 1;
    newElement->Next = lastElement->Next;
    lastElement->Next = newElement;
    free(tmpStr);
}


void reSetBook(KITAP* head){
	FILE *KTP =fopen("Kitaplar.csv", "w");
	fclose(KTP);
	KTP =fopen("Kitaplar.csv", "w+");
    if (KTP == NULL) {
    	printf("Error opening file\n");
    	exit(1);
    }
	while(head->Next){
        fprintf(KTP, "%s,%s,%d\n",head->KitapAdi, head->ISBN, head->adet);
        head = head->Next;
	}
	fprintf(KTP, "%s,%s,%d",head->KitapAdi, head->ISBN, head->adet);
	fclose(KTP);
}



void printKitap(KITAP* head){
	KITAPORNEK* tmp;
	printf("Kitab�n Ad�:%s\nKitab�n ISBNNumaras�:%d\n------------------------------\n",head->KitapAdi,head->ISBN);
	printf("\nKitap �rnekleri: %d",head->adet);
	tmp = head->head;
	while(tmp){
		printf("\nEtiket:%s ==> %s",tmp->EtiketNo,tmp->Durum);
		tmp = tmp->Next;
	}
}

void printKitapList(KITAP* head){
	KITAPORNEK* tmp;
	if(!head){printf("Listeniz Tamamen Bo�\n"); return;}
	while(head){
		printf("\nKitap Ad�:%s\nKitap ISBN no:%s",head->KitapAdi, head->ISBN,head->head->EtiketNo);
	    printf("\nKitap �rnekleri: %d",head->adet);
		tmp = head->head;
		while(tmp){
			printf("\nEtiket:%s ==> %s",tmp->EtiketNo,tmp->Durum);
			tmp = tmp->Next;
		}
		printf("\n------------------------------\n");
		head = head->Next;
	}
}

void kitapLocatedInsert(KITAP** head, char* kitapAd, char* ISBN, int adet)
{
	
	SEQKitapInsert(head, kitapAd, ISBN);

}

void kitapLocatedSil(KITAP **head, char* ISBN){
	int found = 0;
	KITAP *tmp = *head;
	KITAP *prev = NULL;
	
	while(tmp && !found){
		if(!strcmp(tmp->ISBN,ISBN)){
			printf("Sildi�iniz kitab�n bilgileri:\n");
			printKitap(tmp);
			found = 1;
			if(!prev){
				*head = tmp->Next;
			}
			else
				prev->Next = tmp->Next;
		}
		prev = tmp;
		tmp = tmp->Next;
	}
}

void kitapSil(KITAP **head){
	
	int found = 0;
	char* ISBN = (char*)malloc(sizeof(char)*30);
//	char ISBN[30];
	
	KITAP *tmp = *head;
	KITAP *prev = NULL;
	printf("Enter ISBN");
	getchar();
	scanf("%[^\n]s",ISBN);
	scanf;
	
	while(tmp && !found){
		if(!strcmp(tmp->ISBN,ISBN)){
			printf("Sildi�iniz kitap bilgileri:\n");
			printKitap(tmp);                                        
			found = 1;
			if(!prev){
				*head = tmp->Next;
			}
			else
				prev->Next = tmp->Next;
			printf("\nK�TAP Ba�ar�yla silindi...");
		}
		prev = tmp;
		tmp = tmp->Next;
	}
	free(ISBN);
	if(!found) printf("K�TAP Bulunamad�\n");
}

void kitapDuzenle(KITAP **head){
	char* neuISBN = (char*)malloc(sizeof(char)*30);
	char* exISBN = (char*)malloc(sizeof(char)*30);
	char* kitapAd = (char*)malloc(sizeof(char)*30);
//	
//	char neuISBN[30];
//	char exISBN[30];
//	char kitapAd[30];
	int found = 0;
	printf("Enter ID");
	getchar();
	scanf("%[^\n]s",exISBN);
	KITAP *tmp = *head;
	
	while(tmp && !found){
		if(!strcmp(tmp->ISBN,exISBN)){
			found = 1;
			printf("�u anki kitap bilgileri:\n");
			printKitap(tmp);
			printf("Yazar�n yeni bilgilerini giriniz.");
			printf("\nKitap Ad�:");	scanf("%s",kitapAd);
			printf("\nISBN NO:");	getchar();	scanf("%[^\n]s",neuISBN);
			kitapLocatedSil(head, exISBN);
			kitapLocatedInsert(head, kitapAd, neuISBN,0);
			printf("\nYazar Ba�ar�yla D�zenlendi...");
		}
		tmp = tmp->Next;
	}
	if(!found) printf("Yazar Bulunamad�\n");
	free(neuISBN); free(exISBN); free(kitapAd);
}


void kitapInsert(KITAP** head){
	KITAP* newElement = (KITAP*)malloc(1*sizeof(KITAP));
	KITAPORNEK* newOrnek = (KITAPORNEK*)malloc(1*sizeof(KITAPORNEK));
	char* ISBN = (char*)malloc(sizeof(char)*30);
	char* tmpStr = (char*)malloc(sizeof(char)*30);
//	char ISBN[30];
//	char tmpStr[30];
	printf("Eklemek �stediginiz Kitab�n Bilgilerini Giriniz.\n");
	printf("\nKitap Ad�:");	getchar();	scanf("%[^\n]s",newElement->KitapAdi);
	printf("\nKitap ISBN NO:");	getchar();	scanf("%[^\n]s",ISBN);
	strcpy(newElement->ISBN, ISBN);
	newElement->Next = NULL;
	newElement->head = NULL;
	newOrnek->Next = NULL;
	int found = 0, i;
	
	KITAP* lastElement = *head;

	while(lastElement && !found){
		if(!strcmp(lastElement->ISBN,ISBN)){
			found = 1;			
			printf("Halihaz�rda ayn� ID'ye sahip %d kitap bulunmakta, rafa %d no:lu olarak ekleniyor",lastElement->adet,lastElement->adet+1);
			getch();
			lastElement->adet++;			
			itoa(lastElement->adet,tmpStr,10);
	    	strcpy(newOrnek->EtiketNo,ISBN);	strcat(newOrnek->EtiketNo,"_");	strcat(newOrnek->EtiketNo,tmpStr);	strcpy(newOrnek->Durum,"rafta");
			KITAPORNEK *tmpb = lastElement->head;
			
			while(tmpb->Next){
				tmpb = tmpb->Next;
			}
			tmpb->Next = newOrnek;
			free(ISBN); free(tmpStr);
			return;
		}
		lastElement = lastElement->Next;
	}	
	
	if(!*head || strcmp((*head)->ISBN,newElement->ISBN) > 0){
		itoa(1,tmpStr,10);
		strcpy(newOrnek->EtiketNo,ISBN);	strcat(newOrnek->EtiketNo,"_");	strcat(newOrnek->EtiketNo,tmpStr);	strcpy(newOrnek->Durum,"rafta");
		newElement->head = newOrnek;
    	newElement->Next = *head;
    	newElement->adet = 1;
		*head = newElement;
		free(ISBN); free(tmpStr);
		return;
	}
	

	
    lastElement = *head;
    while (lastElement->Next && strcmp(lastElement->Next->ISBN,newElement->ISBN) < 0) {
            lastElement = lastElement->Next;
    }
    itoa(1,tmpStr,10);
    strcpy(newOrnek->EtiketNo,ISBN);	strcat(newOrnek->EtiketNo,"_");	strcat(newOrnek->EtiketNo,tmpStr);	strcat(newOrnek->Durum,"rafta");
	newElement->head = newOrnek;
    newElement->adet = 1;
    newElement->Next = lastElement->Next;
    lastElement->Next = newElement;
    free(ISBN); free(tmpStr);
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxKITAP-YAZAR SEGMENT xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void setAuth(KITAPYAZAR** arr){
	int i, result, flag = 1,count = 0,yazar,N;
	N = countNewLineKY();
	KITAPYAZAR** KITAPYAZARarr = (KITAPYAZAR**)malloc(N*sizeof(KITAPYAZAR*));
	for(i = 0 ; i < N ; i++){
		KITAPYAZARarr[i] = (KITAPYAZAR*)malloc(1*sizeof(KITAPYAZAR));
 	}
 	char* kitap = (char*)malloc(sizeof(char)*30);
//	char kitap[30];
	FILE* authIN = fopen("KitapYazar.csv","r");
	if (authIN == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
	while(result != EOF){
		result = fscanf(authIN,"%[^,],%d\n", kitap, &yazar);
		if(result != EOF){
			strcpy(arr[count]->ISBN,kitap);
			arr[count]->yazarID = yazar;
			count++;
		}
	}
	free(kitap);
	fclose(authIN);
}

void guncelleKY(KITAPYAZAR** KITAPYAZARarr){
	
	int ID, found = 0,N, i,newID,var = 0;
	
	printf("G�ncellemek istedi�iniz yazar� giriniz.");
	scanf("%d",&ID);
	printf("Yeni yazar�n ID\'sini giriniz.");
	scanf("%d",&newID);
	
	N = countNewLineKY();
	for(i = 0  ; i < N ; i++){
		if(KITAPYAZARarr[i]->yazarID == ID){
			KITAPYAZARarr[i]->yazarID = newID;
			var = 1;
		}
	}
		reSetKY(KITAPYAZARarr,N);
	if(!var) printf("G�ncellenecek yazar Bulunamad�\n");
	else printf("yazar g�ncellendi.");
}

void reSetKY(KITAPYAZAR** KITAPYAZARarr, int N){
	int i;
	FILE *fp = fopen("KitapYazar.csv", "w");
	fclose(fp);
	fp = fopen("KitapYazar.csv", "w+");
	if(fp == NULL){
		printf("error opening file");
	}
	for(i = 0  ; i < N-1 ; i++){
		fprintf(fp,"%s,%d\n",KITAPYAZARarr[i]->ISBN,KITAPYAZARarr[i]->yazarID);
	}
	fprintf(fp,"%s,%d",KITAPYAZARarr[i]->ISBN,KITAPYAZARarr[i]->yazarID);
	fclose(fp);
}

void printKY(KITAPYAZAR** KITAPYAZARarr, int N){
	int i;
	printf("%-17s %-10s\n", "ISBN-NO", "YAZAR-ID");
	printf("............. ...............\n");
	for(i = 0  ; i < N ; i++){
		printf("%s -------->  %d \n",KITAPYAZARarr[i]->ISBN,KITAPYAZARarr[i]->yazarID);
	}
}
void addKY(KITAPYAZAR*** KITAPYAZARarr, int *N,YAZAR **YAZARhead, KITAP **KITAPhead){
	int yazarID;
	char* ISBN = (char*)malloc(sizeof(char)*30);
//	char ISBN[30];
	FILE* fp;
	printf("�li�kilendirmek istedi�iniz:");
	printf("Kitap ISBN No:"); scanf("%s",ISBN);
	printf("\nYazar ID\'si:"); scanf("%d",&yazarID);
	int isYazar = ctrlYazar(YAZARhead, yazarID);
	int isBook = ctrlBook(KITAPhead, ISBN);
	KITAPYAZAR *newElement = (KITAPYAZAR*)malloc(1*sizeof(KITAPYAZAR));
	if(isBook && isYazar){
		(*N)++;
		newElement->yazarID = yazarID;
		(*KITAPYAZARarr)[*N-1] = newElement;
		FILE *fp =fopen("KitapYazar.csv", "a");
		fprintf(fp,"\n%s,%d", ISBN, yazarID);
		fclose(fp);
		printKY(*KITAPYAZARarr,*N);
		getch();
		reSetKY(*KITAPYAZARarr,*N);
	}
	else{ printf("Ge�ersiz Yazar ya da Kitap bilgileri giri�i"); getch();}
	free(ISBN);
}
int ctrlBook(KITAP **head, char* exID){
	int found = 0;
	KITAP *tmp = *head;
	while(tmp && !found){
		if(!strcmp(tmp->ISBN,exID)){
			found = 1;
		}
		tmp = tmp->Next;
	}
	return found;
}
int ctrlYazar(YAZAR **head, int exID){
	int found = 0;
	YAZAR *tmp = *head;
	while(tmp && !found){
		if(tmp->yazarID == exID){
			found = 1;
		}
		tmp = tmp->Next;
	}
	return found;
}
int countNewLineKY(){
	int N = 0; 
	char c;
	FILE* fp;
	fp = fopen("KitapYazar.csv","r");
	if (!fp)
    {
        printf("Could not open file");
    	exit(1);
    }
    c = getc(fp);
    while(c != EOF){
    	if(c == '\n') N++;
    	c = getc(fp);
	}
	if(N) N++;
	fclose(fp);
	return N;	
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  (��MD�L�K BOZUK) EMANET SEGMENT XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxxx

//void setOdunc(KITAPODUNC** arr){
//	char kitap[30];
//	char ogrID[30];
//	int islem;
//	int gun;
//	int ay;
//	int yil;
//	int count = 0 , i ,result,NE;
//	FILE *fp = fopen("KitapOdunc.csv","r");
//	if (fp == NULL) {
//        printf("Error opening file\n");
//        exit(1);
//    }
////	NE = countNewLineKO();
////	KITAPODUNC** KITAPODUNCarr = (KITAPODUNC**)malloc(NE*sizeof(KITAPODUNC*));
////	for(i = 0 ; i < NE ; i++){
////		KITAPODUNCarr[i] = (KITAPODUNC*)malloc(1*sizeof(KITAPODUNC));
////		KITAPODUNCarr[i]->islemTarihi = (TARIH*)malloc(1*sizeof(TARIH));
//// 	}
//	
//	while(result != EOF){
//		result = fscanf(fp,"%[^,],[^,],%d,%d,%d,%d\n", kitap, ogrID, &islem, &gun, &ay, &yil);
//		if(result != EOF){
//			strcpy(arr[count]->EtiketNo,kitap);
//			strcpy(arr[count]->ogrID,ogrID);
//			arr[count]->islemTipi = islem;
//			arr[count]->islemTarihi->gun = gun;
//			arr[count]->islemTarihi->ay = ay;
//			arr[count]->islemTarihi->yil = yil;
//			count++;
//		}
//	}
//	fclose(fp);
//}
//
//void printEmanetler(KITAPODUNC** arr, int N){
//	int i;
//	printf("%-17s %-10s\n", "ISBN-NO", "YAZAR-ID");
//	printf("............. ...............\n");
//	for(i = 0  ; i < N ; i++){
//		printf("%s,s,%d,%d,%d,%d", arr[i]->EtiketNo, arr[i]->ogrID, arr[i]->islemTipi, arr[i]->islemTarihi->gun, arr[i]->islemTarihi->ay, arr[i]->islemTarihi->yil);
//	}
//}
////void emanetVer(KITAP** KITAPhead, OGRENCI** OGRENCIhead){
////	FILE *STD =fopen("K�tapOdunc.csv", "w");
////    if (STD == NULL) {
////        printf("Error opening file\n");
////        exit(1);
////    }
////	int flag = 1;
////    while (flag) {
////     
////		char id[30];
////   		char firstName[30];
////   		char lastName[30];
////        int credit;
////        int result = fscanf(STD, "%[^,],%[^,],%[^,],%d\n", id, firstName, lastName, &credit);
////		
////        // Check if we reached the end of the file
////        if (result == EOF) {
////            flag = 0;
////        }
////		if(flag){
////	        OGRENCI *newNode = (OGRENCI*) malloc(sizeof(OGRENCI));
////	        
////	        strcpy(newNode->ogrID,id);strcpy(newNode->ad,firstName);strcpy(newNode->soyad,lastName);
////	        /*free(id);free(firstName);free(lastName); //FREE MALLOCS*/
////	        newNode->puan = credit;
////	        newNode->Next = NULL;
////			newNode->Prev=NULL;
////	        // Add the new node to the linked list
////	        if (*head == NULL) *head = newNode;
////			else {
////	            OGRENCI *temp = *head;
////	            while (temp->Next != NULL) {
////	                temp = temp->Next;
////	            }
////	            temp->Next = newNode;
////	            newNode->Prev = temp;
////	       }
////		}
////   }
////   fclose(STD);//CLOSE FILE
////}
//int countNewLineKO(){
//	int N = 0; 
//	char c;
//	FILE* fp;
//	fp = fopen("KitapOdunc.csv","r");
//	if (!fp)
//    {
//        printf("Could not open file");
//    	exit(1);
//    }
//    c = getc(fp);
//    while(c != EOF){
//    	if(c == '\n') N++;
//    	c = getc(fp);
//	}
//	if(N) N++;
//	fclose(fp);
//	return N;	
//}
//void EmanetVer(KITAPODUNC** KITAPODUNCarr, KITAP** KITAPhead, OGRENCI** STDhead,int sayac){
//	int res;
//	TARIH* CurrentDate = (TARIH*)malloc(1*sizeof(TARIH));
//	printf("tarihi giriniz:");
//	printf("G�n\n"); scanf("%d",CurrentDate->gun);
//	printf("Ay\n"); scanf("%d",CurrentDate->ay);
//	printf("Y�l\n"); scanf("%d",CurrentDate->yil);
//	KITAP* tempK = *KITAPhead;
//	OGRENCI* tempO = *STDhead;
//	char* degergetir = (char*)malloc(30*sizeof(char));
//	char* kitap = (char*)malloc(30*sizeof(char));
//	char* ogrenci = (char*)malloc(30*sizeof(char));							   		
//	printf("Vermek istedi�iniz kitab�n etiket No giriniz.");
//	scanf("%s",kitap);
//	res = Iskitap(tempK,kitap,degergetir);
//	if(res == 1){
//		printf("Kitab�n�z� hangi ��renciye vermek istersiniz?");
//		scanf("%s",ogrenci);
//		IsOgrenci(tempO,ogrenci);
//		if(res == 1){
//			strcpy(KITAPODUNCarr[sayac]->EtiketNo,kitap);
//			strcpy(KITAPODUNCarr[sayac]->ogrID,ogrenci);
//			KITAPODUNCarr[sayac]->islemTipi = 0;
//			KITAPODUNCarr[sayac]->islemTarihi = CurrentDate;
//		}
//	}
//	free(kitap); free(ogrenci);
//}
//void EmanetAl(KITAPODUNC** KITAPODUNCarr, KITAP** KITAPhead, OGRENCI** STDhead,int sayac){
//	int res;
//	TARIH* CurrentDate = (TARIH*)malloc(1*sizeof(TARIH));
//	printf("tarihi giriniz:");
//	printf("G�n\n"); scanf("%d",CurrentDate->gun);
//	printf("Ay\n"); scanf("%d",CurrentDate->ay);
//	printf("Y�l\n"); scanf("%d",CurrentDate->yil);
//	KITAP* tempK = *KITAPhead;
//	OGRENCI* tempO = *STDhead;
//	char* kitap[30];						   		
//	char* ogrenci[30];
//	printf("Getirilen kitab�n etiket No giriniz.");
//	scanf("%s",kitap);
//	char* degergetir = (char*)malloc(30*sizeof(char));
////	res = Iskitap(tempK,kitap,degergetir);
//		if(res != 1 && res != -2 ){
//			printf("Kitab� getiren ��renciniz %s",degergetir);
////			strcpy(KITAPODUNCarr[sayac]->EtiketNo,kitap);
////			strcpy(KITAPODUNCarr[sayac]->ogrID,ogrenci);
//			KITAPODUNCarr[sayac]->islemTipi = 0;
//			KITAPODUNCarr[sayac]->islemTarihi = CurrentDate;
//	}
//}
//int Iskitap(KITAP* head, char*kitap, char* degergetir){
//	char* temp[30];
//	KITAPORNEK *walk = head->head;
//	while(walk){
//		if(walk->EtiketNo == kitap){
//			if(!strcmp(walk->Durum,"Rafta")){
//				printf("Arad���n�z kitap musait");
//				return 1;
//			}
//		}
//		else{
//			printf("Aradiginiz kitap baska bir ��rencide.");
//			strcpy(degergetir,walk->Durum);
//			strcpy(walk->Durum, "Rafta");
////			return degergetir;
//		}
//		walk = walk->Next;
//	}
//	printf("Aradiginiz kitap bulunmamakta...");
//	return -2;
//}
//int IsOgrenci(OGRENCI* head, char* ogrenci){
//	OGRENCI *walk = head;
//	while(walk){
//		if(walk->ogrID== ogrenci){
//			if(!strcmp(walk->ogrID,ogrenci)){
//				printf("Arad���n�z ��renci bulundu");
//				return 1;
//			}
//		}
//		walk = walk->Next;
//	}
//	printf("Aradiginiz kitap bulunmamakta...");
//	return -2;
//}
