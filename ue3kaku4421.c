#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define N 8

int main(void){
    int k,j,n;                                      //kとjはループに使う
    char z,zz;
    static double p, s, a[N-1][N], x[N-1];          // a[N][N+1]は拡大係数行列     x[N]は解を示す
        printf("上三角型の連立方程式の解法\n\n");

    while(1){
        printf("未知数の個数 n を入力してください。(1 < n < 7) n = ");
        scanf("%d%*c",&n);
        if((n<=1)||(7<=n))  continue;
        printf("\n");
        printf("係数と右辺の値を入力してください。\n\n");
        for(k=1;k<=n;k=k+1){
            printf("第%d式:\n",k);
            for(j=k;j<=n+1;j=j+1){
                if (j<n+1){
                    printf("\tx%d の係数 = ",j);
                    scanf("%lf%c",&a[k-1][j-1],&zz);
                }else{
                    printf("\n");
                    printf("\t右辺の値 = ");
                    scanf("%lf%c",&a[k-1][j-1],&zz);
                }
            }
            printf("\n");
        }
        printf("正しく入力しましたか？ (y/n) ");
        scanf("%c%c",&z,&zz);
        if(z == 'y') break;
    }
    // 計算開始
    for(k=1;k<=n;k=k+1){
        p = a[k-1][k-1];
        if(fabs(p) < 1.0e-6){                       //double型の絶対値をとるfabs
            printf("一意解を持ちません．\n");
            exit(-1);                               //プログラム終了exit(-1)
        }
        for(j=k;j<=n+1;j=j+1){
            a[k-1][j-1]=a[k-1][j-1]/p;
        }
    }
        for(k=n;k>=1;k=k-1){
            s=0.0;
            for(j=k+1;j<=n;j=j+1){
                s = s + a[k-1][j-1]*x[j-1];
            }
            x[k-1] = a[k-1][n] - s;
        }
        printf("\n上三角型の連立方程式の解\n\n");
        for (k=1;k<=n;k=k+1){
            printf("\tx%d = %10.6lf\n",k,x[k-1]);
        }
        return 0;
}