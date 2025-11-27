
// tuong duong voi if - else if(dieu kien ==) 
//  switch - case:

#include <stdio.h>

void bai1(){
	printf("bai 1");
}

void bai2(){
	printf("bai 2");
}

int main(){
	//chuyen kenh
//	int kenh = 1;
//	printf("Xin moi nhap lua chon: ");
//	scanf("%i", &kenh);
	
/*	if(kenh == 1){
		printf("VTV1");
	}
	else if(kenh == 2){
			printf("VTV2");
	}
	else if(kenh == 3){
			printf("VTV3");
	}
		else if(kenh == 4){
			printf("VTV4");
	}
	else {
		printf("Nhieu");
	}
	
	*/
	
//	switch(kenh) {
//		case 1: {
//		bai1();
//			break;
//		}
//			case 2: {
//		bai2();
//			break;
//		}
//			case 3: {
//		printf("VTV3");
//			break;
//		}
//			case 4: {
//		printf("VTV4");
//			break;
//		}
//		default:{
//			printf("Nhieu");
//			break;
//		}
//	}
	
	float so;
	printf("Xin moi ban nhap so: ");
	scanf("%f",&so);
	
	printf("phan nguyen cua so ban vua nhap la %d", (int)so);
	if(so == (int)so){
		printf("\nso ban vua nhap la so nguyen");
	}else{
		printf("khum");
	}

}

	



