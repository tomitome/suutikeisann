#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10
#define FN 2

double ffv(int p,double a){
    switch(p){
        case 0: return 1.0;
        case 1: return a;
        default : return a;
    }
}


void hyouji(double a[FN][FN+1],int n){
    int k,j;

    printf("┌");//罫線
    for(k=0;k<10*(n+1)+2;k++)printf(" ");
    printf("┐\n");

    for(k=0;k<n;k++){
        printf("│");
        for(j=0;j<=n;j++)printf("%10.6lf",a[k][j]);
        printf("  │\n");
    }

    printf("└");
    for(k=0;k<10*(n+1)+2;k++)printf(" ");
    printf("┘\n\n");
}

void irekae(double a[FN][FN+1],int i,int n){
    int m,j,k;
    double kaname;
    m = i;
    for(k=i+1;k<n;k++){
        if(fabs(a[m][i])<fabs(a[k][i])) m=k;
    }
    for(j=0;j<=n;j++){
        kaname=a[m][j];
        a[m][j]=a[i][j];
        a[i][j]=kaname;
    }
    if(i!=m){//同じ行でいれ替えを行ったときは表示させないため
        printf("%d行目と%d行目を入れ替えました。\n",i+1,m+1);
        hyouji(a,n);
    }
}

int main(void){
    int n,                          //データ数
        i,                          //ループカウンタ
        j,                          //
        k;                          //
    double  x,                      //x入力用
            y,                      //y入力用
            p,           
            q,                      //掃き出しの係数、軸となる成分
            a[N][FN+1],             // [A b]  10*3
            c[FN][FN+1],
            w[2];                   // tA[A b]  2*3
    char z;                         //y/n入力用

    printf("このプログラムは最小二乗法によって\n");
    printf("\ty = a*e^bx\n");
    printf("の形の曲線を当てはめるものです。\n\n");

    //double ffv(int p,double a){
    //    switch(p){
    //        case 0: return 1.0;
    //        case 1: return a;
    //        default : return a;
    //    }
    //}
    while(1){
        printf("データの個数は何個ですか。(1<n<%d) n = ",N+1);
        scanf("%d%*c",&n);
        if((n <= 1) || (N < n)) continue;
        for(i = 0; i < n ;i++){
            printf("%d個目のデータ\n",i+1);
            printf("\tx = ");
            scanf("%lf%*c",&x);
            printf("\ty = ");
            scanf("%lf%*c",&y);
            a[i][0]=ffv(0,x);
            //printf("\n    %lf",a[i][0]);
            a[i][1]=ffv(1,x);
            //printf("    %lf",a[i][1]);
            y = log(y);
            a[i][FN]=y;
            //printf("    %lf\n\n",a[i][FN]);
        }
        printf("\n正しく入力しましたか (y/n) ");
        scanf("%c%*c",&z);
        if(z=='y') break;
    }

    for(i=0;i<FN;i++){
        for(j=0;j<=FN;j++){
            c[i][j]=0;
            for(k=0;k<n;k++){
                //printf("\n%lf",a[k][i]);
                //printf("\n%lf\n",a[k][j]);
                c[i][j] = c[i][j] + a[k][i]*a[k][j];// A*tA
            }
            printf("\nha\n");
        }
    }

    printf("\n\ntA[A b]の計算結果\n");
    hyouji(c,FN);

    //ここから行列に操作を加える
    for(i=0;i<FN;i++){
        if(i<FN-1){
            irekae(c,i,FN);
        }
        p = c[i][i];
        if(fabs(p) < 1.0e-6){//double型の絶対値をとるfabs
            printf("一意解が存在しません\n");//10のマイナス6乗より小さければ0とみなすから
            exit(-1);//プログラム終了exit(-1)
        }

        //掃き出し行う
        for(j=i;j<=FN;j++){//一列横に割り算
            c[i][j]=c[i][j]/p;
        }
        for(k=0;k<FN;k++){
            if(k != i){//掃き出しを行う行を制限
                q=c[k][i];
                for(j=0;j<=FN;j++){
                    c[k][j]=c[k][j]-c[i][j]*q;
                }
            }
        }
        printf("(%d,%d)成分を軸として上下に掃き出した行列 tA[A b]->\n",i+1,i+1);
        hyouji(c,FN);
    }
    w[0]=exp(c[0][2]);
    w[1]=c[1][2];
    printf("\nxとyの関数関係は、\n\ty = %.6lf*e^%.6lfx\nです。\n",w[0],w[1]);
    return 0;
}