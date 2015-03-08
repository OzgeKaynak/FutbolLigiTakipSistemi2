#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct takimlar
{
    int takim_kodu;
    char takim_adi[21];
    int galibiyet;
    int beraberlik;
    int maglubiyet;
    int atilan_gol;
    int yedigi_gol;
    struct skorlar *skor_durumu;
};
struct futbolcular
{
    int takim_kodu;
    int forma_num;
    char ad_soyad [21];
    int attigi_gol;
    struct futbolcular *forma_no_sonraki;

};
struct skorlar
{
    int hafta_no;
    int ev_sahibi_takim_kodu;
    int mis_takim_kodu;
    int ev_sahibi_gol;
    int mis_gol;

    struct skorlar *mis_kod_sonraki;
    struct skorlar *ev_kod_sonraki;


};

int menu_secim();
int sayi_al(int,int);
void yeni_takim_ekle(struct takimlar *takim[], struct futbolcular oyuncu_hash[]);
void forma_noya_gore_sirali_ekle(struct futbolcular *liste_basi_ptr,struct futbolcular *yeni);
struct futbolcular *forma_noya_gore_ara (struct futbolcular *liste_basi_ptr,int aranan_no);
struct futbolcular *forma_noya_gore_dairesel_cikar(struct futbolcular oyuncu_hash[],int cikarilacak);
void lig_disindan_futbolcu_ekle(struct takimlar *takim[],struct futbolcular oyuncu_hash[]);
void transfer (struct takimlar *takim[],struct futbolcular oyuncu_hash[]);
void futbolcu_sil(struct takimlar *takim[], struct futbolcular oyuncu_hash[]);
void mac_skorlari_kaydet(struct takimlar *takim[],struct futbolcular oyuncu_hash[]);
void ev_kod_gore_sirali_ekle(struct skorlar **ilk,struct skorlar *yeni);
void mis_koda_gore_sirali_ekle(struct skorlar **ilk,struct skorlar *yeni);
void takimi_futbolculari_listele(struct futbolcular oyuncu_hash[],struct takimlar *takim[]);
void takimin_suanki_durumu_ve_maclari_listele(struct takimlar *takim[]);
void tum_takimlari_listele(struct takimlar *takim[]);
void encok_gol_atan_listele(struct takimlar *takim[]);
void deplasmanda_golcu(struct takimlar *takim[]);
void golcu_futbolcu(struct takimlar *takim[],struct futbolcular oyuncu_hash[]);

int main()
{
    struct futbolcular oyuncu_hash[99];
    struct takimlar *takim[99]= {NULL};
    int i,secenek;

    for(i=0; i<99; i++)
    {
        oyuncu_hash[i].forma_no_sonraki = &oyuncu_hash[i];

    }

    do
    {
        secenek=menu_secim();
        switch(secenek)
        {
        case 1:
            yeni_takim_ekle (takim,oyuncu_hash);
            break;

        case 2:
            lig_disindan_futbolcu_ekle(takim,oyuncu_hash);
            break;

        case 3:
            transfer(takim,oyuncu_hash);
            break;

        case 4:
            futbolcu_sil(takim,oyuncu_hash);
            break;

        case 5:
            mac_skorlari_kaydet(takim,oyuncu_hash);
            break;

        case 6:
            takimi_futbolculari_listele(oyuncu_hash,takim);
            break;

        case 7:
            takimin_suanki_durumu_ve_maclari_listele(takim);
            break;

        case 8:
            tum_takimlari_listele(takim);
            break;

        case 9:
            encok_gol_atan_listele(takim);
            break;

        case 10 :
            deplasmanda_golcu(takim);
            break;

        case 11:
            golcu_futbolcu(takim,oyuncu_hash);
            break;

        }

    }
    while(secenek!=12);


    printf("\nFutbol Ligi Takip Sistemi Programindan Ciktiniz.\n");

    return 0;
}
int menu_secim()
{
    int secim;

    printf("\n  1. Yeni takim ekle\n");
    printf("  2. Bir takima lig disindan yeni bir futbolcunun transfer edilmesi\n");
    printf("  3. Bir takimdaki bir fulbolcunun ligdeki baska bir takima transfer edilmesi\n");
    printf("  4. Bir takimdaki futbolcunun lig disindaki bir takima transfer edilmesi \n");
    printf("  5. Mac skorlarinin kaydedilmesi\n");
    printf("  6. Bir takimin su anki durumunun ve futbolcularinin listelenmesi \n");
    printf("  7. Bir takimin su anki durumunun ve oynadigi maclarin listelenmesi \n");
    printf("  8. Tum takimlarin durumlarinin listelenmesi\n");
    printf("  9. En cok gol atan ve en az gol yiyen takimlarin listelenmesi\n");
    printf(" 10. Deplasmanda en cok gol atan takimin listelenmesi \n");
    printf(" 11. Her takimda en cok gol atan futbolcunun ve ligin gol kralinin listelenmesi \n");
    printf(" 12. Cikis\n\n");

    printf("\nLutfen Seciminizi Giriniz:");
    secim=sayi_al(1,12);

    return secim;
}
int sayi_al(int alt,int ust)
{
    int sayi;

    scanf("%d",&sayi);
    while(sayi<alt || sayi>ust)
    {
        printf("Hatali giris yaptiniz,uygun aralikta tekrar giriniz:");
        scanf("%d",&sayi);
    }
    return sayi;
}

void yeni_takim_ekle(struct takimlar *takim[], struct futbolcular oyuncu_hash[])
{
    int kod;
    struct takimlar *bir_takim;


    printf("Eklemek istediginiz takimin takim kodunu giriniz.\n");
    kod=sayi_al(1,99);

    if(takim[kod]!= NULL)
    {
        printf("Boyle bir takim zaten var.\n");

    }
    else
    {
        bir_takim=malloc(sizeof(struct takimlar));
        bir_takim->takim_kodu=kod;
        printf("Bu takimin adini giriniz.\n");
        fflush(stdin);
        gets(bir_takim->takim_adi);

        bir_takim->skor_durumu=NULL;
        bir_takim->atilan_gol=0;
        bir_takim->beraberlik=0;
        bir_takim->galibiyet=0;
        bir_takim->maglubiyet=0;
        bir_takim->yedigi_gol=0;


        takim[bir_takim->takim_kodu]=bir_takim;
        printf("Takim basari ile eklendi.\n");

    }


}

void forma_noya_gore_sirali_ekle(struct futbolcular *liste_basi_ptr,struct futbolcular *yeni)
{
    struct futbolcular *onceki,*gecici;


    onceki=liste_basi_ptr;
    gecici=liste_basi_ptr->forma_no_sonraki;
    while(gecici!=liste_basi_ptr && gecici->forma_num<yeni->forma_num)
    {
        onceki=gecici;
        gecici=gecici->forma_no_sonraki;
    }
    yeni->forma_no_sonraki=gecici;
    onceki->forma_no_sonraki=yeni;
}

struct futbolcular *forma_noya_gore_ara (struct futbolcular *liste_basi_ptr,int aranan_no)
{
    struct futbolcular *gecici;

    gecici=liste_basi_ptr->forma_no_sonraki;
    while (gecici!=liste_basi_ptr && aranan_no>=gecici->forma_num)
    {
        if (gecici->forma_num==aranan_no) return gecici;
        gecici=gecici->forma_no_sonraki;
    }
    return NULL;

}
struct futbolcular *forma_noya_gore_dairesel_cikar(struct futbolcular *liste_basi_ptr,int cikarilacak)//ogrencinin numaraya gore notlar dugumundeki yeri dairesel tek bagli listeden cikartiliyor
{
    struct futbolcular *onceki, *gecici;

    onceki=liste_basi_ptr;
    gecici=liste_basi_ptr->forma_no_sonraki;
    while(gecici!=liste_basi_ptr && gecici->forma_num<cikarilacak)
    {
        onceki=gecici;
        gecici=gecici->forma_no_sonraki;
    }
    if(gecici==liste_basi_ptr || gecici->forma_num>cikarilacak)
        return NULL;
    else
    {
        onceki->forma_no_sonraki=gecici->forma_no_sonraki;
        return gecici;
    }
}

void lig_disindan_futbolcu_ekle(struct takimlar *takim[],struct futbolcular oyuncu_hash[])
{
    int tak_kod;
    int forma_no;
    struct futbolcular *bir_futbolcu;

    printf("Eklemek istediginiz futbolcunun takim kodunu giriniz(1-99):");
    tak_kod=sayi_al(1,99);

    if(takim[tak_kod]!=NULL)
    {
        printf("Eklemek istediginiz futbolcunun forma numarasini giriniz.\n");
        forma_no=sayi_al(1,99);

        bir_futbolcu=forma_noya_gore_ara(&oyuncu_hash[tak_kod],forma_no);
        if(bir_futbolcu==NULL)
        {

            bir_futbolcu=malloc(sizeof(struct futbolcular));
            bir_futbolcu->forma_num=forma_no;
            bir_futbolcu->attigi_gol=0;


            printf("Futbolcunun adini ve soyadini giriniz:");
            fflush(stdin);
            gets(bir_futbolcu->ad_soyad);

            forma_noya_gore_sirali_ekle(&oyuncu_hash[tak_kod],bir_futbolcu);
            printf("Yeni Futbolcu basariyla eklendi\n");

        }
        else
        {
            printf("Bu futbolcu numarasina sahip futbolcu vardir.\n");
        }

    }

    else
        printf("Boyle bir takim yoktur.\n");
}

void transfer (struct takimlar *takim[],struct futbolcular oyuncu_hash[])
{
    struct futbolcular *bir_futbolcu;
    int takimno,formano,takimno2,formano2;
    printf("Transfer etmek istediginiz futbolcunun takim kodunu giriniz:");
    takimno=sayi_al(1,100);
    if(takim[takimno]!=NULL)
    {
        printf("\nTransfer etmek istediginiz futbolcunun forma numarasini giriniz:");
        formano=sayi_al(1,100);
        bir_futbolcu=malloc(sizeof(struct futbolcular));
        bir_futbolcu=forma_noya_gore_ara(&oyuncu_hash[takimno],formano);
        if(bir_futbolcu==NULL)
            printf("Girdiginiz %d nolu futbolcu yoktur\n",formano);
        else
        {
            printf("Transfer etmek istediginiz yeni takim numarasini giriniz:");
            takimno2=sayi_al(1,100);
            if(takim[takimno2]!=NULL)
            {
                printf("Futbolcunun yeni forma numarasini giriniz:");
                formano2=sayi_al(1,100);
                bir_futbolcu=forma_noya_gore_dairesel_cikar(&oyuncu_hash[takimno],formano);
                bir_futbolcu->forma_num=formano2;
                bir_futbolcu->attigi_gol=0;
                forma_noya_gore_sirali_ekle(&oyuncu_hash[takimno2],bir_futbolcu);
            }
            else
                printf("Girdiginiz %d koda sahip takim yoktur\n",takimno2);

        }
    }
    else
        printf("Girdiginiz %d koda sahip takim yoktur\n",takimno);
}

void futbolcu_sil(struct takimlar *takim[],struct futbolcular oyuncu_hash[])
{

    int tak_kod,forma_no;
    struct futbolcular *bir_futbolcu;
    printf("Silinecek futbolcunun takim kodunu giriniz:");
    tak_kod=sayi_al(1,99);
    if(takim[tak_kod]==NULL)
        printf("Bu takim koduna sahip takim yok.\n");
    else
    {
        printf("Silinecek futbolcunun forma numarasini giriniz.\n");
        forma_no=sayi_al(1,99);
        bir_futbolcu=forma_noya_gore_dairesel_cikar(&oyuncu_hash[tak_kod],forma_no);
        if(bir_futbolcu==NULL)
            printf("Cikarilacak bu futbolcu bulunmamaktadir.\n");
        free(bir_futbolcu);

        printf("Futbolcu lig disina transfer edildi.\n");
    }
}

void mac_skorlari_kaydet(struct takimlar *takim[],struct futbolcular oyuncu_hash[])
{

    struct skorlar *bir_skor;
    struct futbolcular *bir_futbolcu;
    struct futbolcular *bir_futbolcu2;
    char devam;
    int golsay=0,golsay2=0,forma_no;
    int toplam=0;
    int toplam2=0;

    do
    {
        printf("Hafta numarasini giriniz:");
        bir_skor=malloc(sizeof(struct skorlar));
        scanf("%d",&bir_skor->hafta_no);

        printf("******EV SAHIBI TAKIMININ*****\n");
        printf("Takim kodunu giriniz:\n");
        bir_skor->ev_sahibi_takim_kodu=sayi_al(1,99);

        if(takim[bir_skor->ev_sahibi_takim_kodu]==NULL)
            printf("Ekleme yapmak istediginiz %d nolu takim bulunmamaktadir.\n",bir_skor->ev_sahibi_takim_kodu);
        else
        {
            printf("Bu takimin attigi gol sayisini giriniz.\n");
            scanf("%d",&bir_skor->ev_sahibi_gol);

            printf("*******BU MACTA GOL ATAN HER FUTBOLCU ICIN*****\n");
            do
            {
                printf("Forma numarasini giriniz.\n");
                scanf("%d",&forma_no);
                bir_futbolcu=forma_noya_gore_ara(&oyuncu_hash[bir_skor->ev_sahibi_takim_kodu],forma_no);
                if(bir_futbolcu!=NULL)
                {
                    printf("Attigi gol sayisini giriniz.\n");
                    scanf("%d",&golsay);


                    while(golsay>bir_skor->ev_sahibi_gol)
                    {
                        printf("YANLIS GIRIS YAPTINIZ:\n\n");
                        printf("Futbolcunun attigi gol sayisini giriniz:\n");
                        scanf("%d",&golsay);

                    }

                    toplam+=golsay;
                    if(toplam>bir_skor->ev_sahibi_gol)
                    {
                        toplam-=golsay;
                        printf("Yanlis girilmistir.Lutfen dogru gol sayisini girin.\n");
                        scanf("%d",&golsay);
                        toplam+=golsay;
                        // son girilenle beraber toplam gol sayysy ev_sahibi_gol u
                        //gecerse,son golu siler ve kullanycynyn yeniden girmesi saglanir.
                    }


                }
                else
                {
                    printf("Bu forma numarasina sahip futbolcu yoktur\n");
                }
                bir_futbolcu->attigi_gol+=golsay;
                golsay=0;
            }
            while(toplam!=bir_skor->ev_sahibi_gol);

            //  -------------------------------------------------------------------------------------------------------------------------------


            printf("******MISAFIR TAKIMININ*****\n");
            printf("Takim kodunu giriniz:\n");
            bir_skor->mis_takim_kodu=sayi_al(1,99);

            if(takim[bir_skor->mis_takim_kodu]==NULL)
                printf("Ekleme yapmak istediginiz %d nolu takim bulunmamaktadir.\n",bir_skor->mis_takim_kodu);
            else
            {


                printf("Bu takimin attigi gol sayisini giriniz.\n");
                scanf("%d",&bir_skor->mis_gol);

                printf("*******BU MACTA GOL ATAN HER FUTBOLCU ICIN*****\n");
                do
                {
                    printf("Forma numarasini giriniz.\n");
                    scanf("%d",&forma_no);
                    bir_futbolcu2=forma_noya_gore_ara(&oyuncu_hash[bir_skor->mis_takim_kodu],forma_no);
                    if(bir_futbolcu2!=NULL)
                    {
                        printf("Attigi gol sayisini giriniz.\n");
                        scanf("%d",&golsay2);


                        while(golsay2>bir_skor->mis_gol)
                        {
                            printf("YANLIS GIRIS YAPTINIZ:\n\n");
                            printf("Futbolcunun attigi gol sayisini giriniz:\n");
                            scanf("%d",&golsay2);

                        }

                        toplam2+=golsay2;
                        if(toplam2>bir_skor->mis_gol)
                        {
                            toplam2-=golsay2;
                            printf("Yanlis girilmistir.Lutfen dogru gol sayisini girin.\n");
                            scanf("%d",&golsay2);
                            toplam2+=golsay2;
                            // son girilenle beraber toplam gol sayysy ev_sahibi_gol u
                            //gecerse,son golu siler ve kullanycynyn yeniden girmesi saglanir.
                        }

                    }
                    else
                    {
                        printf("Bu forma numarasina sahip futbolcu yoktur\n");
                    }

                    bir_futbolcu2->attigi_gol+=golsay2;
                    golsay2=0;
                }
                while(toplam2!=bir_skor->mis_gol);



                if(bir_skor->ev_sahibi_gol>bir_skor->mis_gol)
                {
                    takim[bir_skor->ev_sahibi_takim_kodu]->galibiyet++;
                }

                else if(bir_skor->ev_sahibi_gol==bir_skor->mis_gol)
                {
                    takim[bir_skor->ev_sahibi_takim_kodu]->beraberlik++;
                }

                else if(bir_skor->ev_sahibi_gol<bir_skor->mis_gol)
                {
                    takim[bir_skor->ev_sahibi_takim_kodu]->maglubiyet++;
                }




                if(bir_skor->mis_gol>bir_skor->ev_sahibi_gol)
                {
                    takim[bir_skor->mis_takim_kodu]->galibiyet++;
                }

                else if(bir_skor->mis_gol==bir_skor->ev_sahibi_gol)
                {
                    takim[bir_skor->mis_takim_kodu]->beraberlik++;
                }

                else if(bir_skor->mis_gol<bir_skor->ev_sahibi_gol)
                {
                    takim[bir_skor->mis_takim_kodu]->maglubiyet++;
                }

                takim[bir_skor->ev_sahibi_takim_kodu]->yedigi_gol+=bir_skor->mis_gol;
                takim[bir_skor->mis_takim_kodu]->atilan_gol+=bir_skor->mis_gol;
                takim[bir_skor->ev_sahibi_takim_kodu]->atilan_gol+=bir_skor->ev_sahibi_gol;
                takim[bir_skor->mis_takim_kodu]->yedigi_gol+=bir_skor->ev_sahibi_gol;

                do
                {
                    printf("BU HAFTAYA AIT BASKA BITEN MAC VAR MI:(e/E/h/H)\n");
                    fflush(stdin);
                    devam=getchar();
                }
                while(devam!='e'  && devam!='E' && devam!='h'  && devam!='H');

            }


            ev_kod_gore_sirali_ekle(&takim[bir_skor->ev_sahibi_takim_kodu]->skor_durumu,bir_skor);
            mis_koda_gore_sirali_ekle(&takim[bir_skor->mis_takim_kodu]->skor_durumu,bir_skor);

        }
        golsay=0;
        golsay2=0;
        toplam=0;
        toplam2=0;

    }
    while(devam=='e'|| devam=='E');

}

void ev_kod_gore_sirali_ekle(struct skorlar **ilk,struct skorlar *yeni)//ogrenci numarasina gore tek bagli listeye ogrenci ekliyecek olan fonksiyon
{

    struct skorlar *gecici,*onceki;

    if (*ilk==NULL)//liste bossa basa ekleme
    {
        yeni->ev_kod_sonraki=NULL;
        *ilk=yeni;
    }
    else if (yeni->hafta_no<(*ilk)->hafta_no)//ilk siraya ekleme
    {

        yeni->ev_kod_sonraki=*ilk;
        *ilk=yeni;

    }
    else
    {
        //araya veya sona sirali olarak ekleme

        onceki=*ilk;

        if((*ilk)->ev_sahibi_takim_kodu==yeni->ev_sahibi_takim_kodu)      //takimin ilk macta ev sahibi veya misafir oldugu belirlenir
            gecici=(*ilk)->ev_kod_sonraki;
        else
            gecici=(*ilk)->mis_kod_sonraki;


        while ((gecici!=NULL) && (gecici->hafta_no<yeni->hafta_no))
        {
            onceki=gecici;

            if(gecici->ev_sahibi_takim_kodu==yeni->ev_sahibi_takim_kodu)      //takimin macta ev sahibi veya misafir oldugu belirlenir
                gecici=gecici->ev_kod_sonraki;
            else
                gecici=gecici->mis_kod_sonraki;

        }

        yeni->ev_kod_sonraki=gecici;

        if(onceki->ev_sahibi_takim_kodu==yeni->ev_sahibi_takim_kodu)      //takimin macta ev sahibi veya misafir oldugu belirlenir
            onceki->ev_kod_sonraki=yeni;
        else
            onceki->mis_kod_sonraki=yeni;;

    }
}
void mis_koda_gore_sirali_ekle(struct skorlar **ilk,struct skorlar *yeni)//ogrenci numarasina gore tek bagli listeye ogrenci ekliyecek olan fonksiyon
{

    struct skorlar *gecici,*onceki;

    if (*ilk==NULL)//liste bossa basa ekleme
    {
        yeni->mis_kod_sonraki=NULL;
        *ilk=yeni;
    }
    else if (yeni->hafta_no<(*ilk)->hafta_no)//ilk siraya ekleme
    {

        yeni->mis_kod_sonraki=*ilk;
        *ilk=yeni;

    }
    else
    {
        //araya veya sona sirali olarak ekleme
        onceki=*ilk;

        if((*ilk)->ev_sahibi_takim_kodu==yeni->mis_takim_kodu)      //takimin ilk macta ev sahibi veya misafir oldugu belirlenir
            gecici=(*ilk)->ev_kod_sonraki;
        else
            gecici=(*ilk)->mis_kod_sonraki;


        while ((gecici!=NULL) && (gecici->hafta_no<yeni->hafta_no))
        {

            onceki=gecici;

            if(gecici->ev_sahibi_takim_kodu==yeni->mis_takim_kodu)      //takimin macta ev sahibi veya misafir oldugu belirlenir
                gecici=gecici->ev_kod_sonraki;
            else
                gecici=gecici->mis_kod_sonraki;

        }
        yeni->mis_kod_sonraki=gecici;

        if(onceki->ev_sahibi_takim_kodu==yeni->mis_takim_kodu)      //takimin macta ev sahibi veya misafir oldugu belirlenir
            onceki->ev_kod_sonraki=yeni;
        else
            onceki->mis_kod_sonraki=yeni;;
    }
}
void takimi_futbolculari_listele(struct futbolcular oyuncu_hash[],struct takimlar *takim[])
{
    int OO,AVR,Puan,tak_kod,i, bulundu=0;
    struct futbolcular *gecici;
    char takim_ismi[21];
    printf("Bilgilerini gormek istediginiz takimin adini giriniz.\n");
    fflush(stdin);
    gets(takim_ismi);

    for(i=0; i<99; i++)
    {
        if(takim[i]!=NULL)
        {
            if(strcmp(takim_ismi,takim[i]->takim_adi)==0)
            {
                bulundu=1;
                tak_kod=i;
                break;
            }
        }

    }
    if(bulundu==0)
        printf("Bu ada sahip takim yok.\n");
    else
    {

        OO=takim[tak_kod]->galibiyet+takim[tak_kod]->maglubiyet+takim[tak_kod]->beraberlik;
        AVR=takim[tak_kod]->atilan_gol-takim[tak_kod]->yedigi_gol;
        Puan=takim[tak_kod]->galibiyet*3+takim[tak_kod]->beraberlik;

        printf("Takim Kodu     Takim Adi             OO  GG  BB  MM  AA  YY  AVR  Puan\n");
        printf("..........     ..............        ..  ..  ..  ..  ..  ..  ...  ....\n");

        printf("%3d            %-21s%3d %3d %3d %3d %3d %3d %3d %4d\n",takim[tak_kod]->takim_kodu,takim[tak_kod]->takim_adi,OO,takim[tak_kod]->galibiyet,takim[tak_kod]->beraberlik,takim[tak_kod]->maglubiyet,takim[tak_kod]->atilan_gol,takim[tak_kod]->yedigi_gol,AVR,Puan);

        if(oyuncu_hash[tak_kod].forma_no_sonraki!=&oyuncu_hash[tak_kod])
        {
            printf("Bu takimda oynayan futbolcular ve bilgileri:\n");
            printf("Forma No    Ad Soyad            AA\n");
            printf("........    .................   ..\n");



            gecici=oyuncu_hash[tak_kod].forma_no_sonraki;
            while (gecici!=&oyuncu_hash[tak_kod])
            {

                printf("%3d         %-15s     %-2d \n",gecici->forma_num,gecici->ad_soyad,gecici->attigi_gol);

                gecici=gecici->forma_no_sonraki;
            }

        }

        else
            printf("Bu takima ait futbolcu yok.\n");
    }
    printf("\n");
}

void takimin_suanki_durumu_ve_maclari_listele(struct takimlar * takim[])
{
    int tak_kod,OO,AVR,Puan;
    struct skorlar *yazdirilacak_skor;
    printf("Kullanicidan bilgilerini gormek istediginiz takimin kodunu giriniz.\n");
    tak_kod=sayi_al(1,99);

    if(takim[tak_kod]==NULL)
        printf("Girmis oldugunuz koda sahip takim bulunmamaktadir.\n");
    else
    {

        yazdirilacak_skor=takim[tak_kod]->skor_durumu;
        OO=takim[tak_kod]->galibiyet+takim[tak_kod]->maglubiyet+takim[tak_kod]->beraberlik;
        AVR=takim[tak_kod]->atilan_gol-takim[tak_kod]->yedigi_gol;
        Puan=takim[tak_kod]->galibiyet*3+takim[tak_kod]->beraberlik;

        printf("Takim Kodu     Takim Adi             OO  GG  BB  MM  AA  YY  AVR  Puan\n");
        printf("..........     ................      ..  ..  ..  ..  ..  ..  ...  ....\n");
        printf("%3d            %-21s%3d %3d %3d %3d %3d %3d %3d %4d\n",takim[tak_kod]->takim_kodu,takim[tak_kod]->takim_adi,OO,takim[tak_kod]->galibiyet,takim[tak_kod]->beraberlik,takim[tak_kod]->maglubiyet,takim[tak_kod]->atilan_gol,takim[tak_kod]->yedigi_gol,AVR,Puan);


        printf("\n--------Oynadigi Maclarin Skorlari---------\n\n");
        printf("        EV SAHIBI                  MISAFIR           \n");
        printf("Hafta   Takim Adi         AA       AA  Takim Adi\n");
        printf(".....   ............      ..       ..  ............\n");
        while(yazdirilacak_skor!=NULL)
        {
            printf("%d       %-18s%2d       %2d  %-18s\n",yazdirilacak_skor->hafta_no,takim[yazdirilacak_skor->ev_sahibi_takim_kodu]->takim_adi,yazdirilacak_skor->ev_sahibi_gol,yazdirilacak_skor->mis_gol,takim[yazdirilacak_skor->mis_takim_kodu]->takim_adi);

            if(tak_kod == yazdirilacak_skor->ev_sahibi_takim_kodu)
                yazdirilacak_skor = yazdirilacak_skor->ev_kod_sonraki;
            else if(tak_kod == yazdirilacak_skor->mis_takim_kodu)
                yazdirilacak_skor= yazdirilacak_skor->mis_kod_sonraki;

        }

    }
    printf("\n");

}
void tum_takimlari_listele(struct takimlar *takim[])
{
    int i,OO,AVR,Puan;
    printf("Takim Kodu     Takim Adi             OO GG BB MM AA YY AVR Puan\n");
    printf("..........     ............          .. .. .. .. .. .. ... ....\n");

    for(i=0; i<99; i++)
    {
        if(takim[i]!=NULL)
        {
            OO=takim[i]->galibiyet+takim[i]->maglubiyet+takim[i]->beraberlik;
            AVR=takim[i]->atilan_gol-takim[i]->yedigi_gol;
            Puan=takim[i]->galibiyet*3+takim[i]->beraberlik;

            printf("%3d            %-21s%2d %2d %2d %2d %2d %2d %2d %3d\n",takim[i]->takim_kodu,takim[i]->takim_adi,OO,takim[i]->galibiyet,takim[i]->beraberlik,takim[i]->maglubiyet,takim[i]->atilan_gol,takim[i]->yedigi_gol,AVR,Puan);

        }
    }
    printf("\n");
}

void encok_gol_atan_listele(struct takimlar *takim[])//9.maddde
{
    struct takimlar *bir_takim,*bir_takim2;

    int max1=0,i,k,OO,OO2,AVR,AVR2,Puan,Puan2;
    int min=100,bulundu1=0,bulundu2=0;
    int ye_gol1;
    int atil_gol;
    char takim1[21];
    char takim2[21];

    for(i=0; i<99; i++)
    {
        if(takim[i]!=NULL)
        {

            if(takim[i]->atilan_gol>max1)
            {
                bir_takim=takim[i];
                max1=bir_takim->atilan_gol;
                strncpy(takim1,bir_takim->takim_adi,21);
                ye_gol1=bir_takim->yedigi_gol;

                OO=bir_takim->galibiyet+bir_takim->maglubiyet+bir_takim->beraberlik;
                AVR=bir_takim->atilan_gol-bir_takim->yedigi_gol;
                Puan=bir_takim->galibiyet*3+bir_takim->beraberlik;
                bulundu1=1;

            }

        }
    }


    for(k=0; k<99; k++)
    {
        if(takim[k]!=NULL)
        {

            if(takim[k]->yedigi_gol<min)
            {
                bir_takim2=takim[k];
                min=bir_takim2->yedigi_gol;
                strncpy(takim2,bir_takim2->takim_adi,21);
                atil_gol=bir_takim2->atilan_gol;
                OO2=bir_takim2->galibiyet+bir_takim2->maglubiyet+bir_takim2->beraberlik;
                AVR2=bir_takim2->atilan_gol-bir_takim2->yedigi_gol;
                Puan2=bir_takim2->galibiyet*3+bir_takim2->beraberlik;
                bulundu2=1;
            }
        }
    }

    if(bulundu1==0 && bulundu2==1)
    {
        printf("GOL ATAN VE GOL YIYEN TAKIM YOK (0/0)!!!\n");
    }
    if(bulundu1==1 && bulundu2==1)
    {
        printf("Takim Kodu     Takim Adi             OO  GG  BB  MM  AA  YY  AVR  Puan\n");
        printf("..........     ............          ..  ..  ..  ..  ..  ..  ...  ....\n");
        printf("%3d            %-21s%3d %3d %3d %3d %3d %3d %3d %4d\n",bir_takim->takim_kodu,takim1,OO,bir_takim->galibiyet,bir_takim->beraberlik,bir_takim->maglubiyet,max1,ye_gol1,AVR,Puan);
        printf("%3d            %-21s%3d %3d %3d %3d %3d %3d %3d %4d\n",bir_takim2->takim_kodu,takim2,OO2,bir_takim2->galibiyet,bir_takim2->beraberlik,bir_takim2->maglubiyet,atil_gol,min,AVR2,Puan2);
    }
}

void deplasmanda_golcu(struct takimlar *takim[])//10.madde
{
    int bulundu=0,i;
    int miskod;
    int max=0;
    struct takimlar *bir_takim;


    for(i=0; i<99; i++)
    {
        if(takim[i]!=NULL)
        {

            if(takim[i]->skor_durumu->mis_gol!=NULL)
            {
                if(takim[i]->skor_durumu->mis_gol>=max)
                {
                    max=takim[i]->skor_durumu->mis_gol;
                    miskod=takim[i]->skor_durumu->mis_takim_kodu;
                    bulundu=1;
                }
                bir_takim=takim[i];
            }
        }
    }
    if(bulundu==1)
    {
        int OO=bir_takim->beraberlik+bir_takim->galibiyet+bir_takim->maglubiyet;
        int puan=bir_takim->galibiyet*3+bir_takim->beraberlik;
        int AVR= bir_takim->atilan_gol-bir_takim->yedigi_gol;
        printf("\n");
        printf("Takim Kodu     Takim Adi             OO  GG  BB  MM  AA  YY  AVR  Puan\n");
        printf("..........     .............         ..  ..  ..  ..  ..  ..  ...  ....\n");
        printf("%3d            %-21s%3d %3d %3d %3d %3d %3d %3d %4d\n",miskod,bir_takim->takim_adi,OO,bir_takim->galibiyet,bir_takim->beraberlik,bir_takim->maglubiyet,max,bir_takim->yedigi_gol,AVR,puan);
        printf("\n\n");

    }
    else
        printf("DEPLASMANDA GOL ATAN TAKIM YOK!!!!\n");

}

void golcu_futbolcu(struct takimlar *takim[],struct futbolcular oyuncu_hash[])//11 icin...
{
    struct futbolcular *gecici;
    struct takimlar *bir_takim;
    int max=0,gol_krali=0,takim_kodu;
    int bulundu1=0,bulundu2=0;
    char ad[21];
    char ad_2[21];
    int num,num_2,i,j;
    printf("Takim Kodu   Takim Adi       FormaNo  Ad Soyad          AA\n");
    printf("----------   --------------- -------  ----------------  --\n");


    for(i=0; i<99; i++)
    {
        if(takim[i]!=NULL)
        {
            max=0;
            bulundu1=0;
            bir_takim=takim[i];
            for(j=0; j<99; j++)
            {

                if(oyuncu_hash[i].forma_no_sonraki!=&oyuncu_hash[i])
                {


                    gecici=oyuncu_hash[i].forma_no_sonraki;
                    while (gecici!=&oyuncu_hash[i])
                    {
                        if(max<gecici->attigi_gol)
                        {
                            max=gecici->attigi_gol;
                            strncpy(ad,gecici->ad_soyad,21);
                            num=gecici->forma_num;
                            bulundu1=1;
                        }
                        if(max>gol_krali)
                        {
                            gol_krali=max;
                            strncpy(ad_2,gecici->ad_soyad,21);
                            num_2=gecici->forma_num;
                            takim_kodu=i;
                            bulundu2=1;

                        }

                        gecici=gecici->forma_no_sonraki;
                    }
                }
            }
            if(bulundu1==1)
            {

                printf("%3d          %-15s   %-3d    %-18s%2d\n",bir_takim->takim_kodu,bir_takim->takim_adi,num,ad,max);
            }
            else printf("\n%d kodlu takimda gol atan futbolcu YOK!!!\n",bir_takim->takim_kodu);
        }
    }
    printf("\n");
    if(bulundu2==1)
    {
        printf("\nLigin gol krali:\n");
        printf("Takim Kodu   Takim Adi       FormaNo  Ad Soyad          AA\n");
        printf("----------   --------------- -------  ----------------  --\n");
        printf("%3d          %-15s   %-3d    %-18s%2d\n",takim_kodu,takim[takim_kodu]->takim_adi,num_2,ad_2,gol_krali);
    }
    else printf("Gol atan futbolcu olmadigi icin Ligin gol krali yoktur...!!!!\n");
    printf("\n");

}
