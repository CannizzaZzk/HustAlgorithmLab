#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SIZE 1000
//数字数组前两位用于存放数字位数及符号 
//X[0]中存放符号，X[1]中存放位数，在数组中数字倒置 
char ans[SIZE];
int Z[SIZE];


int max(int x,int y);
int max_arry(int X[],int Y[],int i,int scale);
void cal_choice(int X[],int Y[],int choice);
void cal_add(int X[],int Y[]);//绝对值加法 
void cal_sub(int X[],int Y[]);
 
void arry_cpy(int* A,int* B);
 
void cal_times(int X[],int Y[]);
void out_put(FILE *fp_out);


int main(void)
{
	int count,choice,i,times;
	char num_one[SIZE];
	char num_two[SIZE];
	int X[SIZE] = {0};
	int Y[SIZE] = {0};
	FILE *fp,*fp_out;
	fp = fopen("in.dat","r+");
	fp_out = fopen("out.dat","w+"); 
	fscanf(fp,"%d",&times);
	
	for(count = 0;count<times;count++)
	{
		
		memset(X,0,sizeof(X));
		memset(Y,0,sizeof(Y));
		//printf("选择运算：1.加法 2.减法 3.乘法\n");
		
		//printf("输入第一个数字：\n");
		fscanf(fp,"%s",num_one);
		//printf("输入第二个数字：\n");
		fscanf(fp,"%s",num_two);
		fscanf(fp,"%d",&choice);
		if(num_one[0]=='-')
			X[0] = 1;
		if(num_two[0]=='-')
			Y[0] = 1;
			
		X[1] = strlen(num_one)-X[0];
		Y[1] = strlen(num_two)-Y[0]; 
		
		if(Y[1]==1&&Y[2]==0)
			Y[1] = 0;
		if(X[1]==1&&X[2]==0)
			X[1] = 0;
	    
		for(i=2; i<=X[1]+1; i++)
	        X[i]=num_one[X[1]+X[0]-1-i+2]-'0';
	    
	    for(i=2; i<=Y[1]+1; i++)
	        Y[i]=num_two[Y[1]+Y[0]-1-i+2]-'0';
	        
	    cal_choice(X,Y,choice);
	    out_put(fp_out);
	    
	    if(count!=times-1)
	    	fprintf(fp_out,"\n");
	}
	
	fclose(fp);
	fclose(fp_out);
    return 0;
	
}


void out_put(FILE *fp_out)
{
	if(Z[1]==0)
	{
		fprintf(fp_out,"0");
		return ;
	}	
		
	memset(ans,0,sizeof(ans));
	int j,i,n;
	n = Z[1];
	if(Z[0]==1)
	{
		ans[0] = '-';
		j = 1;
	}
	else j=0;
	
	for(i=0;i<Z[1];i++)
	{
		ans[j+i] = Z[n+1-i] + '0';
	}
	ans[n+j] = '\0';
	//数组前移解决首位是零的特殊情况 
	if(ans[0]  == '-')
	{
		if(ans[1] == '0')
		{
			for(i=1;i<SIZE;i++)
				ans[i] = ans[i+1]; 
		}	
	}
	else
	{
		if(ans[0] == '0')
		{
			for(i=0;i<SIZE;i++)
				ans[i] = ans[i+1]; 
		} 
	} 
	
	fprintf(fp_out,"%s",ans);
	
	
	return;
	
	
}

int max(int x,int y)
{
	if(x>y)
		return 0;
	else if(y>x)
		return 1;
	else 
		return 2;
}

int max_arry(int X[],int Y[],int i,int scale)
{
	if(X[scale+2-i]>Y[scale+2-i]) return 0;
	else if(X[scale+2-i]<Y[scale+2-i]) return 1;
	else if(i == scale + 1) return 2;
	else
	{
		max_arry(X,Y,i+1,scale);
	}
}

void arry_cpy(int* A,int* B)
{
	memset(B,0,sizeof(int)*SIZE);
	int i,n;
	n = A[1];
	
	for(i=0;i<n+2;i++)
	{
		B[i] = A[i];
	}
	
	return ; 
}

void cal_choice(int X[],int Y[],int choice)
{
	if(choice == 1)
	{
		if(X[0]==Y[0])
			cal_add(X,Y);
		else 
			cal_sub(X,Y);
	}
	else if(choice == 2)
	{
		Y[0] = (Y[0]==0)?1:0;
		if(X[0]==Y[0])
			cal_add(X,Y);
		else 
			cal_sub(X,Y);
		Y[0] = (Y[0]==0)?1:0;
	}
	else cal_times(X,Y);
	
	return ;	
}

void cal_add(int X[],int Y[])//绝对值加法 
{
	int C,i,choice,scale;
	choice = max(X[1],Y[1]);
	if(choice==0) scale = X[1];
	else scale = Y[1];
	Z[1] = scale;
	C = 0;
	
	for(i=0;i<scale;i++)
	{
		Z[i+2] = (X[i+2] + Y[i+2] + C)%10;
		
		if((X[i+2] + Y[i+2] + C)>=10) C=1;
		else C = 0;
	}
	if(C==1)//处理最后的进位 
	{
		scale += 1;
		Z[scale+1] = 1;
		Z[1] = scale;
	 } 
	
	Z[0] = X[0];
	
	return ; 
}

void cal_sub(int X[],int Y[])
{	
	int bigger,scale,choice,i,C;
	int sub_C;
	sub_C = 0; 
	choice = max(X[1],Y[1]);
	if(choice==0) 
	{
		scale = X[1];
		bigger = 0; 
	} 
	else 
	{	
		scale = Y[1];
		bigger = 1;
	} 
	
	if(choice == 2)
		bigger = max_arry(X,Y,1,scale);
	C = 0;
	
	if(bigger == 2)
	{
		Z[1] = 0;//规模为零暗示结果为0 
		return ;
	}
	else if(bigger == 0)
	{
		for(i=0;i<scale;i++)
		{
			Z[i+2] = (10 + X[i+2] - Y[i+2] - C)%10;
			
			if((10 + X[i+2] - Y[i+2] - C)<10) C=1;
			else C = 0;
		}
	
	}
	else
	{
		for(i=0;i<scale;i++)
		{
			Z[i+2] = (10 + Y[i+2] - X[i+2] - C)%10;
			
			if((10 + Y[i+2] - X[i+2] - C)<10) C=1;
			else C = 0;
		}
	
	}
	
	while(Z[i+1]==0)
	{
		sub_C+=1;
		i--;
	}
	
	Z[1] = scale - sub_C;
	if(bigger == 0) Z[0] = X[0];
	else Z[0] = Y[0];
	
	return ; 
}

void cal_times(int X[],int Y[])
{
	
	int x,y,z,count,p;
	int temp[SIZE];
	memset(temp,0,sizeof(temp));
	if(X[1]==0||Y[1]==0)
	{
		Z[1] = 0;
		return;
	}
	if(X[1]==1&&Y[1]<=32)
	{	
		y = 0;
		x = X[2];
		p=1;
		for(count = 0;count<Y[1];count++)
		{
			y+=p*Y[count+2];
			p = 10*p; 
		}
		z = x*y;
		count = 2;
		while(z>10)
		{
			Z[count] = z%10;
			z = z/10;
			count++;
		}
		Z[count] = z;
		Z[1] = count -1 ;
		Z[0] = (X[0]==Y[0])?0:1;
		return ;
	}
	else if(Y[1]==1&&X[1]<=32)
	{
		x = 0;
		y = Y[2];
		p=1;
		for(count = 0;count<X[1];count++)
		{
			x+=p*X[count+2];
			p = 10*p; 
		}
		z = x*y;
		count = 2;
		while(z>10)
		{
			Z[count] = z%10;
			z = z/10;
			count++;
		}
		Z[count] = z;
		Z[1] = count -1 ;
		Z[0] = (X[0]==Y[0])?0:1;
		return ;
	}
	else if(X[1]==1&&Y[1]>32)
	{
		for(count = 0;count<X[2];count++)
		{
			cal_add(Y,temp);
			arry_cpy(Z,temp);
		}
		Z[0] = (X[0]==Y[0])?0:1;
		return ;
	}
	else if(Y[1]==1&&X[1]>32)
	{
		for(count = 0;count<Y[2];count++)
		{
			cal_add(X,temp);
			arry_cpy(Z,temp);
		}
		Z[0] = (X[0]==Y[0])?0:1;
		return ;
	}
	
	
	
	int A[SIZE],B[SIZE],C[SIZE],D[SIZE],E[SIZE],F[SIZE];
    int m1[SIZE],m2[SIZE],m3[SIZE],m4[SIZE];
    memset(A,0,sizeof(A));
    memset(B,0,sizeof(B));
    memset(C,0,sizeof(C));
    memset(D,0,sizeof(D));
    memset(E,0,sizeof(E));
    memset(F,0,sizeof(F));
    memset(m1,0,sizeof(m1));
    memset(m2,0,sizeof(m2));
    memset(m3,0,sizeof(m3));
    memset(m4,0,sizeof(m4));
    
	int choice,n,half,i,j;
	choice = max(X[1],Y[1]);
	n = (choice==0)?X[1]:Y[1];
	half = n/2;

	//X的高位为A，低位为B，Y的高位为C，低位为D
	for(i=0;i<half;i++)
	 	B[i+2] = X[i+2];
	for(i=0;i<X[1]-half;i++)
	 	A[i+2] = X[half+2+i];
	for(i=0;i<half;i++)
	 	D[i+2] = Y[i+2];
	for(i=0;i<Y[1]-half;i++)
	 	C[i+2] = Y[half+2+i];
	
	A[0] = B[0] = C[0] = D[0] = 0;
	A[1] = X[1]-half;
	B[1] = half;
	C[1] = Y[1] - half;
	D[1] = half; 	
	//一数长度小于另一数长度一半的特殊情况 
	if(X[1]<=half)
	{
		A[1] = 0;
		arry_cpy(X,B);
	}
	if(Y[1]<=half)
	{
		C[1] = 0;
		arry_cpy(Y,D); 
	}
	
	cal_times(A,C);
	arry_cpy(Z,m1);
	cal_times(B,D);
	arry_cpy(Z,m2);
	B[0] = (B[0]==0)?1:0;
	cal_sub(A,B);
	arry_cpy(Z,E);
	B[0] = (B[0]==0)?1:0;
	C[0] = (C[0]==0)?1:0;
	cal_sub(D,C);
	arry_cpy(Z,F);
	C[0] = (C[0]==0)?1:0;
	cal_times(E,F);
	arry_cpy(Z,m3);
	
	//计算m1,m2,m3的和为m4
	if(m1[0] == m2[0])
	{
		cal_add(m1,m2);
		arry_cpy(Z,m4);
	}
	else
	{
		cal_sub(m1,m2);
		arry_cpy(Z,m4);
	}
	
	if(m3[0]==m4[0])
	{
		cal_add(m3,m4);
		arry_cpy(Z,m4);
	}
	else
	{
		cal_sub(m3,m4);
		arry_cpy(Z,m4);
	}
	
	int C_in,C_chg;
	C_in = 0;
	C_chg = 0;
	
	memset(Z,0,sizeof(Z));
	Z[0] = (X[0]==Y[0])?0:1;
	//Z[1] = X[1] + Y[1] + m1[1] - n;
	Z[1] =  X[1] + Y[1];
	
	j= 2;
	C_in = 0;
	C_chg = 0;
	for(i=0;i<m2[1];i++)
	{
		if(m2[i+2] + Z[j+i] + C_in>=10) C_chg = 1;
		else C_chg = 0; 
		
		Z[j+i] = (m2[i+2] + Z[j+i] + C_in)%10;
		
		if(C_chg == 1)
			C_in = 1;
		else 
			C_in = 0;
	}
	if(C_in == 1)
		Z[j+i] += 1;
	
	j= half+2;
	C_in = 0;
	C_chg = 0;
	for(i=0;i<m4[1];i++)
	{
		if(m4[0]==0)
		{
			if(m4[i+2] + Z[j+i] + C_in>=10) C_chg = 1;
			else C_chg = 0; 
		
			Z[j+i] = (m4[i+2] + Z[j+i] + C_in)%10;
			
			if(C_chg == 1)
				C_in = 1;
			else 
				C_in = 0;
		}	
		else
		{
			if(10 + Z[j+i] - m4[i+2] + C_in<10) C_chg = 1;
			else C_chg = 0; 
		
			Z[j+i] = (10 + Z[j+i] - m4[i+2] + C_in)%10;
			
			if(C_chg == 1)
				C_in = -1;
			else 
				C_in = 0;
		}	
		
		
	}
	if(C_in==1)
		Z[j+i] += 1;
	else if(C_in==-1)
		Z[j+i] -= 1;
	
	j = 2*half+2;
	C_in = 0;
	C_chg = 0;
	for(i=0;i<m1[1];i++)
	{
		if(m1[i+2] + Z[j+i] + C_in>=10) C_chg = 1;
		else C_chg = 0; 
		
		Z[j+i] = (m1[2+i] + Z[j+i] + C_in)%10; 
		
		if(C_chg == 1)
			C_in = 1;
		else 
			C_in = 0;
	}
	if(C_in == 1)
	{
		Z[j+i] += 1;
		Z[1]+=1;
	}
	

	
	

    return ;
}
