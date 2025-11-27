// Cú pháp chung:

/* #include <stdio.h>
	int main(){ code o day}
*/
// Bien: don vi luu chu du lieu
// Kieu du lieu: so , ky tu
// So: nguyen (int), long long, tp nho: float, 
//tp lon: double
// Khai báo: <Kieu du lieu> tenbien (= ktgt);

/*
Xuat: printf(chen cac dac ta)
dac ta : int : %i,%d
float: %f , gioi han chu so tp: %.3f
double: $lf

Nhap : scanf("dt", &bien);

Cac phep tinh: +,-,*,/,%, =
Logic: ==, >, <, >=, <=, ||, &&

dk: if, else if, else
chuyen: switch(dk):
case th:{
}

0 = false, !0 = true
*/

#include <stdio.h>

int main(){
	// In so tu 0 den 100:
	// tang bao nhieu moi lan
	// Vong lap (co kiem soat)
	
	//bien tang 1 don vi
	
	// De lap lai 1 hanh dong nao do voi for:
	// for(khai bao so bat dau, dieu kien
	
	for(int from = 0;from<=100;from = from + 1){		
		if(from==30 & from==29) continue;
		if(from==36) break;
		printf("%d ", from);	
	}
	// continue: tiep tuc lap: bo qua dieu kien
	//break: dung luon
	
    // while, do - while
    // while(dk){ logic }; 
    
    printf("\n In tu 0 - 10 bang while: ");
    
    int dk = 0;
    while(dk <=10){
    		printf("%d ", dk);
			dk=dk+1;	
	}
	
	 printf("\n In tu 0 - 10 bang do - while: ");
	 
	 int so = 11;
	 do{
	 		
	 		so=so+1;
	 		printf("%d ", so);
			
	 }while(so <= 10);
}


