#include <stdio.h>

int main(){
	// Khai bao <Kieu du lieu> <tenbien> = gtmd;
	//so: int: so nguyen, float: so thap phan, double: so thap phan nhung to 
	
	// Phep tinh
	// +, -, *, /, %, =, &
	
	// phep logic: != ,==, >, <, <=, >= , &&, || 
	
	int so1 = 0 , so2= 0;
	printf("Xin moi nhap so thu 1: ");
	scanf("%i", &so1);
	
	printf("Xin moi nhap so thu 2: ");
	scanf("%d", &so2);
	
	//Tinh tong, hieu, tich, thuong, du
	
	//Chung minh 2 so bang, lon hon, nho hon, chia het
	
	// if(dk) { logic thuc hien } else {logic neu khong thoa man if}
	
	if((so1==so2)){
		printf("2 so vua nhap bang nhau\n");
	}
	
   else	if(so1>so2){
		printf("%i lon hon %i\n",so1,so2);
	}
	
 else	if(so2<so1){
		printf("%i nho hon %i\n",so2,so1);
	}
	
		else	if(so1<so2){
		printf("%i nho hon %i\n",so1,so2);
	}
	
else	if(so2>so1){
		printf("%i lon hon %i\n",so2,so1);
	}
	
	
 	if(so1!=so2){
		printf("2 so vua nhap khong bang nhau\n");
	}
	
	if(so1%so2==0){
		printf("%i chia het cho %d\n",so1, so2);
	}else{
		printf("%i chia cho %d du %d\n",so1, so2, (so1 % so2));
	}
	
	//In ra so nao la chan, so nao le
	if(so1%2!=0){
		printf("So 1 la so le\n");
	}else{
		printf("So 1 la so chan\n");
	}
	

	
	// Cach rut gon: toan tu 3 ngoi
//	(dk) ? logic neu dung ? (logic neu sai) 
	
	(so2%2==0) ?
	 printf("So 2 la so chan") :
	 printf("So 1 la so le");
	 
	 // 0 : false, !=0  : true
	 if(123){
	 	printf("\nkhong loi");
	 }
	
}
