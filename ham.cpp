/*
   lap:for : lap biet truoc khi nao dung
   for(khai bao bat dau, dkkt, tinhtien)
   , 
   while(DK lap){} ,
	do{thuc thi} - while(dk lap); 
	
	ngat lap: break;
	tiep tuc lap (bo qua dk): continue;
	
	lam menu: while; 
	do while + (if-else if) 
	/ switch- case
	go to ( se gioi thieu)
*/

#include <stdio.h>

// Ham (function): <kieu tra ve> tenham(<tham so>){}

// viet 1 ham tra ve gia tri tong 2 so truyen vao

float tong(float so1, float so2); //truyen tham so kieu tham tri

//khong tra ve gi; (thuc hien hanh dong): void

void biendoigt(int a){
	a = 5;
	printf("Dia chi cua bien trong ham la %p\n", &a);
}

//2 loai ham :
// Tra ve : bat buoc co return ;
// Kieu khong tra ve: void:

int main(){
	int so = 7;
	printf("Dia chi cua bien trong ham la %p\n", &so);
	biendoigt(so);
	printf("so sau bien doi %d\n", so);
	
	float total = tong(3.2, 5.6);
	printf("Vay tong la %f", total);
}

// != void deu co return
float tong(float so1, float so2){
	return so1+so2;
}

