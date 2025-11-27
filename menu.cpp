#include <stdio.h>

// Ham la 1 khoi code co the goi lai
// ham khong tra ve: void

void inMenu(){

}

int main(){
	/* 
	1.Cong 2 so
	2.Tru 2 so
	3.Nhan 2 so
	4. Chia 2 so
	0. Thoat
	
	Lap lai menu den khi thoat
	*/
	
	//C1: Lap den khi nguoi dung chon thoat (while)
	while(6677){
		printf("1.Cong 2 so\n");
		printf("2.Tru 2 so\n");
		printf("3.Nhan 2 so\n");
		printf("4. Chia 2 so\n");
		printf("0. Thoat\n");
		printf("Xin moi nhap lua chon: ");
	int luachon;
	scanf("%i", &luachon);
	
	int so1 = 0, so2=0;
	
	printf("Nhap so thu 1: ");
	scanf("%d", &so1);
	
	printf("Nhap so thu 2: ");
	scanf("%d", &so2);

	
/*	
	if(luachon==1){
			printf("%d + %d = %d\n\n",so1,so2,(so1+so2));
	}
	else if(luachon==2){
		printf("%d - %d = %d\n\n",so1,so2,(so1-so2));
	}
	else if(luachon==0){
		return 0;
	}
	
	*/

	
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
		case 0: {
			printf("Tam biet");
			return 0;
		}
	}
	
	}
}
