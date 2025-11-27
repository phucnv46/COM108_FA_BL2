//Luyen tap;

#include <stdio.h>
#include <math.h>

void inMenu(){
	printf("\n1.In so le\n");
	printf("2.In Tong\n");
	printf("3.In So chinh phuong\n");
	printf("4.Kiem tra nam nhau\n");
	printf("0.Thoat\n");
}

void in_so_le(){
	int hkt;
	printf("Nhap so: ");
	scanf("%d", &hkt);
	for(int i=0; i <= hkt; i++){
		// if(i%2!=0) printf("%i ",i);
		if(i%2==0) continue;
		printf("%i ",i);
	}
	printf("\n");
}


void ktnn(){
	int nam;
	printf("Nhap nam muon kiem tra: ");
	scanf("%d", &nam);
	if( nam % 4 == 0 && nam%100 !=0
|| nam % 400 == 0){
	printf("Day la nam nhuan!");
   }else {
   		printf("Day khong la nam nhuan!");
   }
}


void insochinhphuong(){
int hkt;
	printf("Nhap so: ");
	scanf("%d", &hkt);
	printf("Cac so chinh phuong tu 1 den %i: \n", hkt);
	for(int i=0; i <= hkt; i++){
		if(sqrt(i)== (int)sqrt(i)){
			printf("%i ", i);
		}
	}
}

void in_tong(){
	int hkt, tong =0;
	printf("Nhap so: ");
	scanf("%d", &hkt);
		for(int i=0; i <= hkt; i++){
				tong= tong + i; 
		}
		printf("Tong cac so tu 0 den %i la %i",hkt, tong);
}


int main(){
	
	for(;;){
		inMenu();
		int luachon;
		printf("Xin moi nhap lua chon: ");
		scanf("%i", &luachon);
		
		switch(luachon){
			case 0: return 0;
			case 1: {
				in_so_le();
				break;
			}
			case 2: {
				in_tong();
				break;
			}
			case 3: {
				insochinhphuong();
				break;
			}
				case 4: {
				ktnn();
				break;
			}
		}
	}
	
}
