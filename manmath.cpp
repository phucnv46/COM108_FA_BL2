#include<stdio.h>
#include<math.h>

int main(){
	
	float so = 0;
	printf("Xin moi nhap so: ");
	scanf("%f", &so);
	printf("Can bac 2 cua so vua nhap la %f", sqrt(so) );
	
	float mu = 1; 
	// /n xuong dong
	// /t 1 tab
	printf("\nXin moi nhap so mu: ");
	scanf("%f", &mu);
	
	printf("%f mu %f la %.4f",so , mu, pow(so,mu));
	
	// Tinh dien tich hinh tron, ban kinh do nguoi dung nhap
	// PI * R * R
	
	float R;
	printf("\n Xin moi nhap ban kinh: ");
	scanf("%f", &R);
	printf("Vay dien tich la: %f", (M_PI * R * R));
	
}
