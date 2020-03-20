#include <stdio.h>
#include <stdlib.h>

void anaMenu();
void sansOyunlari();
void cekilisIstatiskleri();
void sayial(int alinandizi[], int adet, int ust);
void rastgeleSayiUretimi(int rastgele[], int ust, int kactane);
void siralama(int sayilar[], int ust);
void tutanlar(int d1[], int d2[], int d1l, int d2l);
void tekrar(int oyun);
void sansTopu();
void onNumara();
void Loto(int ust);


int puan = 0, puanSayisalLoto = 0, puanSansTopu = 0, puanOnNumara = 0, puanSuperLoto = 0, puanAnlik = 0;
int istatistik[6][81] = {0};//1 sayısal loto 2 şans topu 3 on numara 4 süper loto 5 şans topu+1

int main() {
    printf("seed degeri girin:");
    int seed;
    scanf("%d", &seed);
    system("CLS");
    srand(seed);
    anaMenu();
}

//--------------------------------------ANA MENÜ---------------------------------------------
void anaMenu() {
    printf("\tANA MENU\n\n1.Sans Oyunlari\n2.Cekilis Istatistikleri\n3.Cikis\n\n\tSeciminizi giriniz:");
    int secim[1];
    sayial(secim, 1, 3);
    switch (secim[0]) {
        case 1:
            sansOyunlari();
            break;
        case 2:
            cekilisIstatiskleri();
            break;
        case 3:
            printf("emin misiniz? evet icin e hayir icin h giriniz!");
            int devam;
            char secim;
            do {
                scanf(" %s", &secim);
                system("CLS");
                if (secim == 'e' || secim == 'E') {
                    exit(3);
                } else if (secim == 'h' || secim == 'H') {
                    anaMenu();
                } else {
                    printf("lutfen e yada h giriniz");
                    devam = 1;
                }
            } while (devam);
    }
}

//------------------------------------------------ŞANS OYUNLARI-----------------------------------------
void sansOyunlari() {
    printf("\tSANS OYUNLARI ALT MENUSU\n\n1.Sayisal Loto Oynama\n2.Sans Topu Oynama\n3.On Numara Oynama\n4.Super Loto Oynama\n5.Ana Menu\n\n\t(Toplam odulunuz: %d puan) Seciminizi giriniz:",
           puan);//puan tüm oyunların puanının toplamı
    int secim[1];//sayıal fonksiyonum dizi ile çalıştğı için 1 elemanlı dizi belirledim
    sayial(secim, 1, 5);//yukarda belirlediğim dizinin 0. elemanını alıyor
    switch (secim[0]) {
        case 1:
            Loto(49);
            break;//sayısal loto
        case 2:
            sansTopu();
            break;
        case 3:
            onNumara();
            break;
        case 4:
            Loto(54);
            break;//süperloto
        case 5:
            anaMenu();
            break;
    }//sınırlamaya gerek yok alınan sayı zaten kontrol ediliyor
}

//-------------------------------------------------------istatistik fonksiyonu----------------------------------
void cekilisIstatiskleri() {
    /*çekiliş mantığım oyunda kaç sayı var ise 1 fazlası dizi oluşturup her elemanı sıfıra eşitleyip
     *her sayı çıktığında dizinin çıkan sayıdaki elemanını bir arttırmak
     *ve sonra en bu diziyi başka diziye aktarıp en büyük elemanı bularak onu yazdırıp sonrasında o
     *elamanı sıfırlayıp bir sonraki en  büyük elemanı yazdırmak bu işlemi oyunun en çok çıkan kaç sayısı isteniyorsa o kadar tekrar ettirmek*/
    int max, ust, kac, sayac = 0;
    int oyun[1], secim[1];//sayıal fonksiyonum dizi ile çalıştğı için 1 elemanlı dizi belirledim
    printf("hangi oyunun istatisklerini gormek istersiniz\n1.Sayisal Loto \n2.Sans Topu \n3.On Numara \n4.Super Loto \nseciminiz:");
    sayial(oyun, 1, 4);//hangi oyunun istatistiğinin alınacağının seçimi
    do {
        if (oyun[0] == 1) {
            ust = 49;
            kac = 6;
        } else if (oyun[0] == 2) {
            ust = 34;
            kac = 5;
        } else if (oyun[0] == 3) {
            ust = 80;
            kac = 10;
        } else if (oyun[0] == 4) {
            ust = 54;
            kac = 6;
        } else if (oyun[0] == 5) {
            ust = 14;
            kac = 1;
        }
        int dizi[ust +1];//dizi sıfırdan başladığı için 1 fazlasını alıyorum oyunun son sayısını da istatikte tutabilmesi için
        for (int j = 0; j < ust + 1; ++j) {
            dizi[j] = istatistik[oyun[0]][j];//a[0] hangi oyun için istatistik olduğu j de istatistik değerleri ana dizim bozulmasın
        }//diye başka diziye aktarıp kullanıyorum
        do {
            max = 0;
            for (int i = 0; i < ust + 1; ++i) {//en büyük elemanı bulmak için
                if (max < dizi[i])
                    max = dizi[i];

            }
            int baska[kac];//hangi sayının çıktığını tutan dizi
            for (int i = 0; i < ust + 1; ++i) {//yazdırma kısmı
                if (max == dizi[i]) {
                    baska[sayac] = i;
                    if (dizi[i] != 0)//ilk oynamadan istatistik isterse veri çıkmaması için
                        printf("%d den %d tane var\n", baska[sayac], dizi[i]);
                    sayac++;
                }

            }
            if (sayac == ust + 1)//sayac sürekli arttı ise tüm değerler eşittir yani sıfır
                printf("veri yok\n");
            for (int i = 0; i < ust + 1; ++i) {//en büyük değeri sıfırlıyor ve sonra diğer en büyüğü buluyor
                if (max == dizi[i])
                    dizi[i] = 0;
            }
        } while (sayac < kac);//kaç tane en büyük istendi ise o kadar dönmesini sağlıyo
        if (oyun[0] == 5)//sonsuz döngüye girmesini engelliyo
            goto w;
        if (oyun[0] == 2) {
            oyun[0] = 5;
            printf("+1 icin:\n");
        }
    } while (oyun[0] == 5);//sans oyunundaki +1 için tekrar istatistik buluyor
    w:
    printf("ust menu icin 1\nsans oyunlari icin 2\nana menu icin 3\nseciminiz:");//devamında hangi menüye döneceği
    sayial(secim, 1, 3);
    switch (secim[0]) {
        case 1:
            cekilisIstatiskleri();
            break;
        case 2:
            sansOyunlari();
            break;
        case 3:
            anaMenu();
            break;
    }
}

//----------------------------------KULLANICIDAN SAYI ALMA--------------------------------------
void sayial(int alinandizi[], int adet, int ust) {
    for (int j = 0; j < adet; ++j) {
        alinandizi[j] = 0;
    }
    int sayac = 0, gecici = 0;
    do {
        int x = 0;
        if (adet != 1)//seçim aldığım yerlerde sayı giriniz yazmaması için
            printf("%d. sayi giriniz:", (sayac + 1));

        while (scanf("%d", &gecici) == 0)//scanf de hatalı giriş yapıldı ise döngüye giriyor
        {
            printf("lutfen sadece sayi girin!!!\n");
            if (adet != 1)//seçim aldığım yerlerde sayı giriniz yazmaması için
                printf("%d. sayi giriniz:", (sayac + 1));
            if (adet == 1)//secim olan yerler için
                printf("Seciminizi giriniz:");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);//sonsuz döngüye dönüşmesini engelliyor
        }
        if (gecici < 1 || gecici > ust) {//girilicek aralığı belirliyor
            printf("lutfen 1 ile %d arasi girin\n", ust);
            if (adet == 1)//seçim için
                printf("Seciminizi giriniz:");
        } else {
            for (int i = 0; i < adet; ++i) {
                if (gecici ==
                    alinandizi[i]) {//önceki alınan sayılardan birisi ile aynı girildi ise sayının tekrar alınmasını sağlıyor
                    printf("ayni sayiyi birden cok kullandiniz\n");
                    x = 1;
                }
            }
            if (x == 0) {
                alinandizi[sayac] = gecici;//alınan sayı diziye atılıyor
                sayac++;
            }
        }
    } while (sayac < adet);
    siralama(alinandizi, adet);//alınan diziyi sıralıyor
    system("CLS");//ekranı temizler
}

//--------------------------------------RANDOM SAYI ÜRETME-------------------------------------------------------------
void rastgeleSayiUretimi(int rastgele[], int ust, int kactane) {
    for (int i = 0; i < kactane; i++)//kaç tane sayı alınıcağı
    {
        rastgele[i] = 1 + rand() % ust;//rastegele alınan sayıların diziye atılması
        for (int j = 1;
             j < i + 1; j++) //bilgisayardan alıdığı sayının kendisinden bi önceki alınan sayılar ile kontrol edilmesi
        {
            if (rastgele[i] ==
                rastgele[i - j])//eğer aynı sayı iki kere seçildiyse bi önceki aşamaya dönüyor ve tekrar seçiyor
            {
                i--;
            }
        }
    }
    siralama(rastgele, kactane);//dizinin sıralanması
}

//---------------------------------SIRALAMA FONKSİYONU------------------------------
void siralama(int dizi[], int ust) {
    for (int k = 0; k < ust; ++k)//kaç sayının sıralanacağı
    {
        for (int i = 0; i < ust - 1; ++i) {
            int tut;
            if (dizi[i] > dizi[i + 1]) {
                tut = dizi[i];
                dizi[i] = dizi[i + 1];
                dizi[i + 1] = tut;
            }
        }
    }
}

//-------------------İKİ DİZİDEKİ EŞLEŞENLER----------------------------------------------------------
void tutanlar(int d1[], int d2[], int d1l, int d2l) {
    for (int i = 0; i < d1l; ++i) //tutan sayıların kontrol edilmesi
    {
        for (int j = 0; j < d2l; ++j) {
            if (d1[j] == d2[i]) {
                printf("tutan=%2d\n", d2[i]);
            }
        }
    }
}

//-------------------TEKRAR OYNAMA FONKSİYONU----------------------------------------------------------
void tekrar(int oyun) {
    puanAnlik = 0;//yeni oyun başlayacağı zaman puanı sıfırlamak için
    printf("tekrar oynamak ister misiniz? evet icin e hayir icin h giriniz!");
    int devam;
    char secim;
    do {
        scanf(" %s", &secim);//%s daha az hata veriyor

        if (secim == 'e' || secim == 'E') {
            system("CLS");
            if (oyun == 1)
                Loto(49);//sayısal loto
            else if (oyun == 2)
                sansTopu();
            else if (oyun == 3)
                onNumara();
            else if (oyun == 4)
                Loto(54);//süper loto
        } else if (secim == 'h' || secim == 'H') {
            system("CLS");
            sansOyunlari();
        } else {
            printf("lutfen e yada h giriniz");
            devam = 1;//döngünün devam etmesi için
        }
    } while (devam);
}

//--------------------------------------------------OYUNLAR---------------------------------
//-------------------------------------------------------------------------------------------
void sansTopu() {
    int oyun = 2, i, sayac = 0, sayac2 = 0, sayilar[5], rastgele[5], sayi[1], random;
    printf("SANS TOPU\n---------------\n");
    //--------------------------------kullanıcıdan alınan sayı-------------------------------------------
    sayial(sayilar, 5, 34);
    printf("+1. sayi:");
    sayial(sayi, 1, 14);
    //------------------------------bilgisayarın sayı seçmesi------------------------------------------------
    rastgeleSayiUretimi(rastgele, 34, 5);
    random = 1 + rand() % 14;
    printf("----------------\n");
    sayac = 0;
    sayac2 = 0;
    if (sayi[0] == random)sayac2++;//+1 in tuttuğu
    istatistik[5][random]++;//+1 in istatistiği
    //-------------------------------istatistik hesaplama-------------------------------
    for (int l = 0; l < 5; ++l) {
        for (int j = 0; j <= 34; ++j) {
            if (rastgele[l] == j)
                istatistik[oyun][j]++;
        }
    }
//----------------------------------ekrana bastırma----------------------------
    for (i = 0; i < 5; ++i) //sayıları yazdırma
    {
        printf("k=%d\tb=%d\n", sayilar[i], rastgele[i]);
    }
    printf("----------------\n"
           "k2=%d\tb2=%d\n", sayi[0], random);
//------------------------------hangi sayıların tuttuğu-----------------------------------------------

    for (i = 0; i < 5; ++i) //tutan sayıların kontrol edilmesi
    {
        for (int j = 0; j < 5; ++j) {
            if (rastgele[j] == sayilar[i]) {
                printf("tutan=%2d\n", sayilar[i]);
                sayac++;
            }
        }
    }

//-------------------------------------------------------------------------------------------------
    int carpim = 1;
    int sayac3 = sayac + sayac2;
    if (sayac3 > 2) {
        for (int i = 0; i < (sayac3 - 2); i++) {
            carpim = carpim * 4;
        }
        if (sayac2 == 0)puanAnlik = carpim * 2;
        else puanAnlik = carpim;
    } else if (sayac == 1 && sayac2 == 1) {
        puanAnlik = 2;
    }

    puanSansTopu += puanAnlik;
    puan += puanAnlik;//burdan alınan puanın genel puana atılması
//--------------------------------------------------------------------------------------------------
    if (sayi[0] == random)
        printf("tutan=%2d\n", sayi[0]);
    printf("%d+%d tane tutturunuz\n", sayac, sayac2);
    printf("----------------\n");
    printf("bu elki puaniniz:%d\n", puanAnlik);
    printf("simdiye kadarki sans topu puaniniz:%d\n", puanSansTopu);//kaç puan aldığı

//---------------------------tekrar oynamak istemesi sorulması------------------------
    tekrar(oyun);
}

//--------------------------------------------------------------------------------
void onNumara() {
    int i, oyun = 3, sayac = 0, sayilar[10], rastgele[22];

    printf("ON NUMARA\n---------------\n");
    printf("----------------\n");
    //--------------------------------kullanıcıdan alınan sayı-------------------------------------------
    sayial(sayilar, 10, 80);
    //------------------------------bilgisayarın sayı seçmesi------------------------------------------------
    rastgeleSayiUretimi(rastgele, 80, 22);

    sayac = 0;
    for (i = 0; i < 22; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (rastgele[i] == sayilar[j]) {
                sayac++;//kaç tane tuttuğu
            }
        }
    }

    for (i = 0; i < 10; ++i) //sayıları yazdırma
    {
        printf("k=%d\tb=%d\tb=%d\t", sayilar[i], rastgele[i], rastgele[i + 10]);
        if (i == 0)
            printf("b=%d\tb=%d", rastgele[20], rastgele[21]);
        printf("\n");
    }

    for (int l = 0; l < 22; ++l) {
        for (int j = 0; j <= 80; ++j) {
            if (rastgele[l] == j)
                istatistik[oyun][j]++;
        }
    }
//------------------------------hangi sayıların tuttuğu-----------------------------------------------
    tutanlar(rastgele, sayilar, 10, 22);
    int carpim = 1;
    if (sayac > 5) {
        for (int i = 0; i < (sayac - 2); i++) {
            carpim = carpim * 2;
        }
        puanAnlik = carpim;
    } else if (sayac == 0) {
        puanAnlik = 8;
    }

    puan += puanAnlik;
    puanOnNumara += puanAnlik;
    printf("%d tane tutturunuz\n", sayac);
    printf("----------------\n");
    printf("bu elki puaniniz:%d\n", puanAnlik);

    printf("simdiye kadarki on numara puaniniz:%d\n", puanOnNumara);//kaç puan aldığı
    tekrar(oyun);
}

//------------------------------SAYISAL VE SÜPER LOTO FONKSİYONU--------------------------------------
void Loto(int ust) {
    int oyun, i, sayac = 0, sayilar[6], rastgele[6];

    if (ust == 49) {
        printf("SAYISAL LOTO\n---------------\n");
        oyun = 1;
    } else if (ust == 54) {
        printf("SUPER LOTO\n---------------\n");
        oyun = 4;
    }
//--------------------------------kullanıcıdan alınan sayı-------------------------------------------
    sayial(sayilar, 6, ust);
    rastgeleSayiUretimi(rastgele, ust, 6);
//------------------------------tutan sayıların kontrol edilmesi-------------------------------------
    printf("----------------\n");
    sayac = 0;
    for (i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (rastgele[j] == sayilar[i]) {
                sayac++;//kaç tane tuttuğu
            }
        }
    }
    //puan hesap fonksyonu
    int carpim = 1;
    if (sayac > 2) {
        for (int i = 0; i < (sayac + 2); i++) {
            carpim = carpim * 2;
        }
        puanAnlik = carpim;
    }
    if (ust == 49)
        puanSayisalLoto += puanAnlik;
    else if (ust == 54)
        puanSuperLoto += puanAnlik;
    puan += puanAnlik;
//-------------------------------istatistik hesaplama-------------------------------
    for (int l = 0; l < 6; ++l) {
        for (int j = 0; j <= ust; ++j) {
            if (rastgele[l] == j)
                istatistik[oyun][j]++;
        }
    }
//----------------------------------ekrana bastırma----------------------------
    for (int i = 0; i < 6; ++i) //sayıları yazdırma
    {
        printf("k=%d\tb=%d\n", sayilar[i], rastgele[i]);
    }
//------------------------------hangi sayıların tuttuğu-----------------------------------------------
    tutanlar(rastgele, sayilar, 6, 6);
    printf("%d tane tutturunuz\n", sayac);
    printf("----------------\n");
    printf("bu elki puaniniz:%d\n", puanAnlik);
    if (ust == 49) {
        printf("simdiye kadarki sayisal loto puaniniz:%d\n", puanSayisalLoto);//kaç puan aldığı
    } else {
        printf("simdiye kadarki super loto puaniniz:%d\n", puanSuperLoto);
    }
//---------------------------tekrar oynamak istemesi sorulması------------------------
    tekrar(oyun);
}