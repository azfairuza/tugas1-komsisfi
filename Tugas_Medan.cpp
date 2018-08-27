#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

const double k= 9000000000; /*9*10^9*/

typedef struct{
    double x,y;
} vektor;

vektor MakeVektor (double absis, double ordinat); //membuat vektor baru
double getAbsis (vektor r); //mendapatkan nilai sumbu x dari vektor
double getOrdinat (vektor r); //mendapatkan nilai sumbu y dari vektor
double dotproduct(vektor r); //mendapatkan nilai dot product dari vektor
double panjangVektor(vektor r); //mendapatkan besar suatu vektor (panjang vektor)
vektor arahVektor(vektor r); //mendapatkan arah vektor, (vektor ketika besarnya 1)
vektor selisihPanjang(vektor r1,vektor r2); //vektor 1 - vektor 2
vektor tambahVektor(vektor r1,vektor r2); //vektor 1 + vektor 2
double BesarMedan1Titik(vektor r, vektor rq, double medan);
vektor Medan1Titik(vektor r, vektor rq, double medan);
vektor MedanTotal (vektor r, vektor *rq, double *medan, int N);

int main(){

    /*KAMUS*/
    int N;
    double x,y,bataskiri,bataskanan,batasatas,batasbawah,dx,dy;
    ofstream fout;

    /*Algoritma*/
    printf("Masukkan jumlah titik muatan : ");
    scanf("%d",&N);

    /*KAMUS2*/
    vektor r[N];
    double q[N];

    /*inisialisai nilai */
    bataskiri=0;
    bataskanan=10;
    batasbawah=0;
    batasatas=10;
    dx=0.1;
    dy=0.1;

    for (int i=0; i<N; i++){
        printf("Masukkan posisi x muatan %d : ",i+1);
        scanf("%lf",&x);
        printf("Masukkan posisi y muatan %d : ",i+1);
        scanf("%lf",&y);
        r[i]=MakeVektor (x,y);
        printf("Masukkan besar muatan %d : ",i+1);
        scanf("%lf",&q[i]);
        printf("\n");
    }

    fout.open("medan.dat");

    fout << "x\ty\tEx\tEy\tE\n";

    for (x=bataskiri; x<=bataskanan; x+=dx){
        for (y=batasbawah;y<=batasatas;y+=dy){
            vektor titik = MakeVektor(x,y);
            vektor Medan = MedanTotal(titik,r,q,N);
            fout << x << "\t";
            fout << y << "\t";
            fout << getAbsis(arahVektor(Medan)) << "\t";
            fout << getOrdinat(arahVektor(Medan)) << "\t";
            fout << panjangVektor(Medan) << "\n";
        }
    }
    fout.close();
return 0;
}

vektor MakeVektor (double absis, double ordinat){
    vektor r;
    r.x=absis;
    r.y=ordinat;
    return r;
}

double getAbsis (vektor r){
    return r.x;
}

double getOrdinat (vektor r){
    return r.y;
}

double dotproduct (vektor r){
    return getAbsis(r)*getAbsis(r)+getOrdinat(r)*getOrdinat(r);
}

double panjangVektor (vektor r){
    return sqrt(dotproduct(r));
}

vektor arahVektor (vektor r){
    return MakeVektor(getAbsis(r)/panjangVektor(r),getOrdinat(r)/panjangVektor(r));
}

vektor selisihPanjang (vektor r1,vektor r2){
    return MakeVektor(getAbsis(r2)-getAbsis(r1),getOrdinat(r2)-getOrdinat(r1));
}

vektor tambahVektor (vektor r1,vektor r2){
    return MakeVektor(getAbsis(r1)+getAbsis(r2),getOrdinat(r1)+getOrdinat(r2));
}

int isVektorSama(vektor r1,vektor r2){
    if (getAbsis(r1)==getAbsis(r2)&&getOrdinat(r1)==getOrdinat(r2)) return 1;
    else return 0;
}

double BesarMedan1Titik (vektor r, vektor rq, double medan){
    return k*medan/dotproduct(selisihPanjang(rq,r));
}

vektor Medan1Titik (vektor r, vektor rq, double medan){
    vektor arah=arahVektor(selisihPanjang(rq,r));
    return MakeVektor(BesarMedan1Titik(r,rq,medan)*getAbsis(arah),BesarMedan1Titik(r,rq,medan)*getOrdinat(arah));
}

vektor MedanTotal (vektor r, vektor *rq,double *medan, int N){
    vektor sum = MakeVektor(0.0000,0.0000);

    for (int i=0; i<N; i++){
        if (isVektorSama(r,rq[i])) return MakeVektor(0.0000,0.0000);
        sum= tambahVektor(sum,Medan1Titik(r,rq[i],medan[i]));
    }
    return sum;
}

