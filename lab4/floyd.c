#include <stdio.h>
#include <string.h>
#define INF_PATH -1
#define INF_EDGE 32767 
#define N 20 

int Dis[N][N];
int Path[N][N];
int path_stack[N];
int stack_count;

void initial(FILE* fp,int n);
void floyd(int n);
void out_put(int n,FILE* fp_out);
void in_stack_path(int i,int j);
void print_path(FILE* fp_out);

int main(void)
{
	int times,i;
	
	int n;
	FILE *fp,*fp_out;
	
	fp = fopen("in.dat", "r");
	fp_out = fopen("out.dat","w+");
    if (fp == NULL)
    {
        printf("Cannot open the file! \n");
        exit(0);
    }
	fscanf(fp,"%d",&times);
	fprintf(fp_out,"%d\n",times);
	
	for(i=0;i<times;i++)
	{
		fscanf(fp,"%d",&n);
		fprintf(fp_out,"%d\n",n);
		initial(fp,n);
		floyd(n);
		out_put(n,fp_out); 
	}
	
	fclose(fp);
	fclose(fp_out);
	
	return 0; 
}

void out_put(int n,FILE* fp_out)
{
	int i,j;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(Dis[i][j]==INF_EDGE)
				fprintf(fp_out,"32767 ");
			else
				fprintf(fp_out,"%d ",Dis[i][j]);
		}
		fprintf(fp_out,"\n");
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			
			if(i==j)
			{
				fprintf(fp_out,"(%d,%d) %d \n",i+1,i+1,i+1);
				continue;
			}	
			else if(Path[i][j]==INF_PATH)
			{
				fprintf(fp_out,"NULL\n");
				continue;
			}
	
			stack_count = 0;
			fprintf(fp_out,"(%d,%d) ",i+1,j+1);
			in_stack_path(i,j);
			print_path(fp_out);
			fprintf(fp_out,"\n");
		}
	}
}

void in_stack_path(int i,int j)
{

	if(i==j)
	{
		path_stack[stack_count] = i+1;
		return ;
	}
	else 
	{
		path_stack[stack_count] = j+1;
		stack_count += 1;
		in_stack_path(i,Path[i][j]);
	}
	
	return ;
}

void print_path(FILE* fp_out)
{
	int i;
	
	//fprintf(fp_out,"%d ",path_stack[stack_count]);
	while(stack_count != 0)
	{
		fprintf(fp_out,"%d ",path_stack[stack_count]);
		stack_count-=1;
	}
	fprintf(fp_out,"%d ",path_stack[0]);
	
	return ;
}


void initial(FILE* fp,int n)//半成品 
{
	int i,j;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			Dis[i][j] = INF_EDGE;
			
			if(i==j)
				Dis[i][j] = 0;
		}
	}
	//文件中读入数据
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(fp,"%d",&Dis[i][j]);
			
			if(Dis[i][j] == 100)
				Dis[i][j] = INF_EDGE;
			
			if(i==j)
				Dis[i][j] = 0;
		}
	}
	
	
	//前驱矩阵初始化
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j || Dis[i][j]==INF_EDGE)
				Path[i][j] = INF_PATH;
			if(i!=j && Dis[i][j]!=INF_EDGE)
				Path[i][j] = i;
		}
	}
	
	return ;
}

void floyd(int n)
{
	int i,j,k;
	
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			for (j = 0; j < n; j++) 
			{
				if (Dis[i][j] > Dis[i][k] + Dis[k][j])
				{
					Dis[i][j] = Dis[i][k] + Dis[k][j];
					Path[i][j] = Path[k][j];
				}
			}
		}
	}
	
	return ;
}
