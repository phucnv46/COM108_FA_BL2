#include<stdio.h>

int main(){
	//Ghi chu
	//Nhap vao 2 so va in ra tong
	// Bien: luu tru gia tri
	// kieu du lieu <tenbien> = (gtmd)
	// So, kitu
	
	//So: So thuc, so nguyen, so nguyen duong
	// Dinh dang nhap va in cua so nguyen: %i
	int so1 = 3.5 , so2 = 4  ; // (-2 m den 2 m)
	
	
	float soT1 = 3.5 , soT2 = 5;
	
	printf("Moi nhap so thu 1: ");
	
	//Nhap : scanf(dinh danh muon nhap, diachi cua bien)
	// diachi cua bien = &tenbien
	scanf("%lf", &soT1);
	
	printf("Moi nhap so thu 2: ");
	
	scanf("%lf", &soT2);
	
	printf("Tong cua 2 so %.2f", (soT1 + soT2));
	
	//Phep toan: +, - , * , /, %
	// % : lay du  
}
