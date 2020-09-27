#include<stdio.h>

int main(void){
    double a, b, h, n, x;
    double f_1, f_2n, f_haji, f_i;
    double f_i_guusuu_total = 0, f_i_kisuu_total = 0;
    double total_1, total_2;
    int n1,i;

    printf("シンプソンの公式により,以下の積分計算を行います.\n");
    printf("\tf(x) = 1/(1+x^2)\n\n");
    printf("積分区間[a,b]を入力してください.\n");
    printf("\ta = ");
    scanf("%lf%*c",&a);
    printf("\tb = ");
    scanf("%lf%*c",&b);
    printf("2n分割します.分割数の1/2を入力してください.\n");
    printf("\tn = ");
    scanf("%lf%*c",&n);
    printf("\n---- 計算過程の表示 ----\n\n");

    n1 = 2*n;
    printf("\t分割数 2n = %d\n",n1);

    h = (b-a)/n1;
    printf("\t刻み幅 h = %10.8lf\n\n",h);

    f_1 = 1/(1+a*a);
    f_2n = 1/(1+b*b);
    f_haji = f_1 + f_2n;
    printf("\tf(a) + f(b) = %10.8lf",f_haji);

    x = a;
    for(i=0;i<n1-1;i++){
        x += h;
        f_i = 1/(1+x*x);
        if(i%2 == 1){
            f_i_guusuu_total += f_i;
        }else{
            f_i_kisuu_total += f_i;
        } 
    }
    printf("\n\tΣf(xi)(奇数番目) = %10.8lf",f_i_kisuu_total);
    printf("\n\tΣf(xi)(偶数番目) = %10.8lf",f_i_guusuu_total);

    total_1 = f_1 + f_2n + 4*f_i_kisuu_total + 2*f_i_guusuu_total;
    printf("\n\tf(a) + f(b) + 4 * Σf(xi)(奇数番目) 2 * Σf(xi)(偶数番目)= %10.8lf",total_1);

    total_2 = h/3.0*total_1;
    printf("\n\th / 3.0 * (f(a) + f(b) + 4 * Σf(xi)(奇数番目) + 2 * Σf(xi)(偶数番目)) = %10.8lf",total_2);
    
    printf("\n\n---- 計算結果の表示 ----\n\n");
    printf("\t積分値は,%10.6lf です.",total_2);

    return 0;
}