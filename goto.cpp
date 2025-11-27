// label - goto;

#include <stdio.h>

void in_menu(){
	printf("1. Tong\n");
	printf("2. Hieu\n");
	printf("3. Thuong\n");
	printf("4. Tich\n");
	printf("0. Thoat\n");
}

void inTong(){
	float a,b;
	printf("Xin moi nhap so thu 1:");
	scanf("%f",&a);
	printf("Xin moi nhap so thu 2:");
	scanf("%f",&b);
	
	printf("Vay tong la %.4f\n", (a+b));
}

void inHieu(){
	float a,b;
	printf("Xin moi nhap so thu 1:");
	scanf("%f",&a);
	printf("Xin moi nhap so thu 2:");
	scanf("%f",&b);
	
	printf("Vay hieu la %.4f\n", (a-b));
}

int main(){
	
	start: // lable ; (ten):
	in_menu();
	int luachon; 
	printf("Xin moi nhap lua chon: ");
	scanf("%i", &luachon);
	
	switch(luachon){
		case 1: { inTong();
			goto start; // goto lable
			break;
		}
		case 2: { inHieu();
		goto start;
			break;
		}
		
		default: {
			printf("Chon sai!\n");
			goto start;
			break;
		}
		case 0: {
			printf("Bye bye!\n");
			return 0;
		}
		
	}
}
