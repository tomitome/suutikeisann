#include<stdio.h>

int main(void){
    //a:積分区間
    //b:積分区間
    //n:分割数
    //h:刻み幅
    double a, b, n, h, x;
    double f_1, f_2n, f_i, f_i_total=0;
    double f_haji;
    double total_1, total_2;
    int i;

    printf("台形公式により,以下の積分計算を行います.\n");
    printf("\tf(x) = 1/(1+x^2)\n\n");
    printf("積分区間[a,b]を入力してください.\n");
    printf("\ta = ");
    scanf("%lf%*c",&a);
    printf("\tb = ");
    scanf("%lf%*c",&b);
    printf("分割数を入力してください.\n");
    printf("\tn = ");
    scanf("%lf%*c",&n);
    printf("\n---- 計算過程の表示 ----\n\n");

    h = (b-a)/n;
    printf("\t刻み幅 h = %10.8lf\n\n",h);

    f_1 = 1/(1+a*a);
    f_2n = 1/(1+b*b);
    f_haji = f_1 + f_2n;
    printf("\tf(a) + f(b) = %10.8lf",f_haji);

    x = a;
    for(i=0;i<n-1;i++){
    x += h;
    f_i = 1/(1+x*x);
    f_i_total += f_i;
    }
    printf("\n\tΣf(xi)(両端以外) = %10.8lf",f_i_total);

    total_1 = f_1 + f_2n + 2*f_i_total;
    printf("\n\tf(a) + f(b) + 2 * Σf(xi)(両端以外) = %10.8lf",total_1);

    total_2 = h/2*total_1;
    printf("\n\th / 2.0 * (f(a) + f(b) + 2 * Σf(xi)(両端以外)) = %10.8lf",total_2);
    
    printf("\n\n---- 計算結果の表示 ----\n\n");
    printf("\t積分値は,%10.6lf です.",total_2);

    return 0;
}