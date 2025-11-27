#include <stdio.h>

int main(){
	// lap den khi nguoi dung khong chon thoat
	int luachon;
	do
	{
		printf("1.Cong 2 so\n");
		printf("2.Tru 2 so\n");
		printf("3.Nhan 2 so\n");
		printf("4. Chia 2 so\n");
		printf("0. Thoat\n");
		printf("Xin moi nhap lua chon: ");
	scanf("%i", &luachon);
	
	int so1 = 0, so2=0;
	
	printf("Nhap so thu 1: ");
	scanf("%d", &so1);
	
	printf("Nhap so thu 2: ");
	scanf("%d", &so2);
	
	
	switch(luachon){
		case 1: {
				printf("%d + %d = %d\n\n",so1,so2,(so1+so2));
			break;
		}
		case 2: {
			printf("%d + %d = %d\n\n",so1,so2,(so1+so2));
			break;
		}
		default: {
			printf("Chon vo van!");
			break;
		}
		
	}
	
	
	
	}while(luachon!=0);

}
