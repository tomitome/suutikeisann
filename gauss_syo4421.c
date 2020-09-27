#include<stdio.h>
#include<math.h>
#include<stdlib.h>//exit関数を使うため
#define N 7

//拡大係数行列の行列表示
void hyouji(double a[N-1][N],int n){
    int k,j;

    printf("┌");                               //罫線
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

//行の入れかえを行う
void irekae(double a[N-1][N],int i,int n){
    int m,j,k;
    double kaname;
    m = i;
    for(k=i+1;k<=n;k++){
        if(fabs(a[m][i])<fabs(a[k][i])) m=k;
    }
    for(j=0;j<=n;j++){
        kaname=a[m][j];
        a[m][j]=a[i][j];
        a[i][j]=kaname;
    }
    printf("%d行目と%d行目を入れ替えました。\n",i+1,m+1);
}

int main(void){
    int k,j,i,n;                                      //kとjはループに使う　　Nは方程式の数
    char z;                                         //zはyes or no で使うだけ
    char mitisuu[]={'x','y','z','u','v','w'};
    static double p, q, s, a[N-1][N], x[N-1];            // a[N-1][N]は拡大係数行列     x[N-1]は解を示す
    printf("ガウスの消去法による連立１次方程式の解法\n");

//数値の入力
    while(1){
        printf("何元連立１次方程式ですか。(1 < n < 7) n = ");
        scanf("%d%*c",&n);
        if((n<=1)||(7<=n))  continue;
        printf("係数と右辺の値を入力してください。\n\n");
        for(k=0;k<=n-1;k=k+1){
            printf("第%d式\n",k+1);
            for(j=0;j<=n-1;j++){
            printf("\t%cの係数 A(%d, %d) = ",mitisuu[j],k+1,j+1);
            scanf("%lf%*c",&a[k][j]);
            }
            printf("\n");
            printf("\t右辺の値 A(%d, %d) = ",k+1,j+1);
            scanf("%lf%*c",&a[k][j]);
        }
        printf("\n正しく入力しましたか。 (y/n) ");
        scanf("%c%*c",&z);
        if(z == 'y') break;
    }
    printf("\n入力された拡大係数行列\n");
    hyouji(a,n);

//入れ替えとか行う
    for(i=0;i<n;i++){
        if(i<n-1){
            irekae(a,i,n);
            hyouji(a,n);
        }
        p = a[i][i];
        if(fabs(p) < 1.0e-6){                      //double型の絶対値をとるfabs
            printf("一意解が存在しません\n");        //10のマイナス6乗より小さければ0とみなすから
            exit(-1);                              //プログラム終了exit(-1)
        }

        //掃き出し行う
        for(j=i;j<=n;j++){
            a[i][j]=a[i][j]/p;
        }
        for(k=i+1;k<=n;k++){
            q=a[k][i];
            for(j=i;j<=n+1;j++){
                a[k][j]=a[k][j]-a[i][j]*q;
            }
        }
        printf("(%d,%d)成分を軸として掃き出した行列\n",i+1,i+1);
        hyouji(a,n);
    }

//逆進代入
        for(i=n-1;i>=0;i--){
            s=0;
            for(j=i+1;j<=n;j++){
                s=s+a[i][j]*x[j];
            }
            x[i]=a[i][n]-s;
        }
        printf("連立１次方程式の解は\n");
        for (k=0;k<n;k++){
            printf("%c = ",mitisuu[k]);
            printf("%10.6lf\n",x[k]);
        }
        return 0;
    }