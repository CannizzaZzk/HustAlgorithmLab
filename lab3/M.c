#include<stdio.h>  

const int N = 5;//默认输入为5*5矩阵（课本要求） 
int root[6][6] = {
	0,0,0,0,0,0,
	0,1,1,2,2,2,
	0,0,2,2,2,4,
	0,0,0,3,4,5,
	0,0,0,0,4,5,
	0,0,0,0,0,5
};


void CONSTRUCT_OPTIAML_BST(int i, int j,FILE* fp)
{
	if (i == 1 && j == N)
		fprintf(fp,"k%d is the root\n", root[i][j]);
	
	if (i > j) 
		return;
	
	int num;
	num = root[i][j];
	
	if (i != num)
	{
		fprintf(fp,"k%d is the left child of k%d\n", root[i][num-1], num);
		CONSTRUCT_OPTIAML_BST(i, num - 1,fp);
	}
	else
	{
		fprintf(fp,"d%d is the left child of k%d\n",num-1, num);
		
	}

	if (j != num)
	{
		fprintf(fp,"k%d is the right child of k%d\n", root[num+1][j], num);
		CONSTRUCT_OPTIAML_BST(num + 1, j,fp);
	}
	else
	{
		fprintf(fp,"d%d is the right child of k%d\n", num, num);
		
	}
}

void in_put(FILE* fp)
{
	int i,j;
	for(i=1;i<N+1;i++)
	{
		for(j=1;j<N+1;j++)
			fscanf(fp,"%d",&root[i][j]);
	}
	
	return ;
}

int main()
{
	FILE *fp,*fp_out;
	fp = fopen("in.dat","r+");
	fp_out = fopen("out.dat","w+");
	 
	CONSTRUCT_OPTIAML_BST(1, N,fp_out);
	
	fclose(fp);
	fclose(fp_out);
	
	getchar();
	return 0;
}


 

