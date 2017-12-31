#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define MAX 1000000
#define N 255
    int dijkstra(int dizi[][N], int baslangic_sehir, int hedef_sehir);
    char sehirlerdizi[N][N];//sehirler

    char koddizi[50][50];  //kodlar
    char sehir1[50][50];//sehir1
    char sehir2[50][50];       //sehir2
    char mesafe[50][50];    //mesafeler

    int mesafeler[N];   //inte çevrilmiş mesafeler dizisi
    int kodlar[50];     //inte çevrilmiş kodlar dizisi
    int dizi[N][N];     // komşuluk matrisi

//sehirmesafe.txt dosyasını açma
void sehirmesafedosyaacma(){
    FILE *pt2;//dosyayı açacak olan pointer
    int i;
    if((pt2 = fopen("C:\\Users\\harun yıldız\\Desktop\\mesafesehir.txt","r")) == NULL)
    {
        printf("dosya acilamadi!");
    exit(0);//açılmazsa çık
    }

    // verileri satır satır satirlar1 dizisine çekiyoruz
    char satirlar2[50][50];
    for(i=0;i<=29 ;i++){
      // verileri oku txtden okutuluyor
    fscanf(pt2, "%s", satirlar2[i]);
    }
    char *p2;
    // mesafesehir.text teki sehirleri ve kodları bölüp ayrı dizide toplayacağız
for(i=1;i<=29;i++){
        p2 = strtok (satirlar2[i],"-");
        strcpy(sehir1[i],p2);

        p2 = strtok (NULL, "-");
        strcpy(sehir2[i],p2);

        p2 = strtok (NULL, "-");
        strcpy(mesafe[i],p2);
   }
    // dosyanın kapatılması
    fclose(pt2);
}
// kod ve mesafler dizisini chardan inte çevirmek için kullancağımız fonksiyon
int cevir_inte(char *x)
{
    char basamak;
    int sonuc = 0;
    while (basamak = *(x++)){
        sonuc = sonuc * 10 + basamak - '0';
    }
    return sonuc;
}

// kodşehir.txt dosyası açma
void sehirkoddosyaacma(){
int i;
  FILE *pt1;//dosyayı açan pointer
    char satirlar1[50][50];//satırları tutan dizi

    if((pt1 = fopen("C:\\Users\\harun yıldız\\Desktop\\kodsehir.txt", "r")) == NULL)
    {
        printf("dosya acilamadi!");
        exit(0);//açılmadıysa çık
    }
// verileri satır satır satirlar1 dizisine çekiyoruz
   char *p1;
        for(i=0;i<=22 ;i++){
// verilerin txt den okunması
    fscanf(pt1, "%s", satirlar1[i]);
    printf("%s\n",satirlar1[i]);
//kullanıcının hangi kodu girdiğini bilmesi için text dosyası printf le ekrana basılır
}
// sehirkod.text teki sehirleri ve kodları bölüp ayrı dizide toplayacağız
    for(i=1;i<=22;i++){
      p1= strtok (satirlar1[i],"-");
      strcpy(sehirlerdizi[i],p1);
    while (p1!= NULL)
      {
        strcpy(koddizi[i],p1);
        p1 = strtok (NULL, "-");
      }
    }
        // dosyayı kapat:
        fclose(pt1);

    }
//dijikstra algoritmasında komşuluk matrisi oluştururken kodbul fonksiyonuna ihtiyacımız vardır
int kodbul(char sehirlerdizi[N][N],char *sehiradi){
    int sonuc,i;
    for(i=1;i<=N;i++){
        sonuc=strcmp(sehirlerdizi[i],sehiradi);
        if(sonuc==0)
        return i;
    }
 return -1;
}
//asıl metot
int dijsktra(int dizi[][N],int baslangic_sehir,int hedef_sehir)
{
    int i,j,ilkadim , ikinciaadim ,x;
        for(i=1;i< N;i++)
            for(j=1;j< N;j++)
                dizi[i][j] = MAX;
    for(x=1;x<=N;x++)
    {
        //koşuluk matrisi oluşturuluyor.
        //A ve B sehrinin kodunu bulmak için kod bul fonksiyonuna ihtiyacım var.
            ilkadim=kodbul(sehirlerdizi,sehir1[x]);
            ikinciaadim=kodbul(sehirlerdizi,sehir2[x]);
            dizi [ilkadim][ikinciaadim] = dizi[ikinciaadim][ilkadim] =mesafeler[x];

    }
    //dijikstra lagoritması//
        int yazdizi[N],secilmis[N]={0},m,min,basla,d;
        char yol[N];
        for(i=1;i< N;i++)
        {
            mesafeler[i] = MAX;
            yazdizi[i] = -1;
        }
        basla = baslangic_sehir;
        secilmis[basla]=1;
        mesafeler[basla] = 0;
        while(secilmis[hedef_sehir] ==0)
        {
            min = MAX;
            m = 0;
            for(i=1;i< N;i++)
            {
                d = mesafeler[basla] +dizi[basla][i];
                if(d< mesafeler[i]&&secilmis[i]==0)
                {
                    mesafeler[i] = d;
                    yazdizi[i] = basla;
                }
                if(min>mesafeler[i] && secilmis[i]==0)
                {
                    min = mesafeler[i];
                    m = i;
                }
            }
            basla = m;
            secilmis[basla] = 1;
                }
        basla = hedef_sehir;
        j = 0;

        while(basla != -1)
        {
           yol[j++] = basla+65;
           basla = yazdizi[basla];
        }
        yol[j]='\0';
        strrev(yol);
        printf("Geçilen yollar :%s \n", yol);//yazmaya çalıştım Ama yazdıramadım.
        return mesafeler[hedef_sehir];
    }

int main()
{
//türkçe karekterlerin okunmasında problem çıkmaması için kullandım
    setlocale(LC_ALL, "Turkish");

    sehirkoddosyaacma();//ilk dosya açılıyor
    int i,z;
//char olan koddizi yi int e cevirme
    for(i=1;i<=22;i++){
       z= cevir_inte(koddizi[i]);
       kodlar[i]=z;
    }
//ikinci dosyamı açıyorum
    sehirmesafedosyaacma();

// char olan mesafe dizisi int e çevirme

    for(i=1;i<=29;i++){
       z= cevir_inte(mesafe[i]);
       mesafeler[i]=z;
    }
//kontrol ediyorum
/*
printf("%d\n",mesafeler[5]);
printf("%d\n",kodlar[5]);
printf("%s\n",sehir1[5]);
printf("%s\n",sehir2[5]);
printf("%s\n",sehirlerdizi[5]);
int p;
p=kodbul(sehirlerdizi,sehir2[10]);
printf("%d",p);
*/
    int baslangic_sehir,hedef_sehir;
    int c;
    int secim=1;
    while(secim!=0){

        printf("\nLütfen baslangic sehir kodunu giriniz : ");
        scanf("%d",&baslangic_sehir);
        printf("\nŞimdi gidilecek olan sehir kodunu giriniz : ");
        scanf("%d",&hedef_sehir);
        c = dijsktra(dizi,baslangic_sehir,hedef_sehir);
        printf("\nEn kisa yol : %d",c);

}






        return 0;
}
