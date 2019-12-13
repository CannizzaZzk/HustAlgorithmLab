#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define Y 0
#define X 1
#define MAX 100
const double infinite = 0x1ffffff;
struct point{
	double x;
	double y;
	int id_x;//按X坐标升序排列的位置 
}point_list[MAX],strip_area[MAX];
int point_num;

typedef struct point point;

struct point_pair{
	int left;
	int right;
	double dis;
}min_pair[MAX];
typedef struct point_pair point_pair;
int min_pair_num;

int exist(point_pair a)
{
	int i,is_found;
	is_found = 0;
	for(i=0;i<min_pair_num;i++)
	{
		if(a.left==min_pair[i].left&&a.right==min_pair[i].right)
			is_found = 1;	
	}	
	
	return is_found;
} 


int cmp_x(point a,point b)
{
	if(a.x<b.x)
		return 1;
		
	return 0;
}

int cmp_y(point a,point b)
{
	if(a.y<b.y)
		return 1;
	return 0;	
}

double cal_dis(point a,point b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

void swap(point* a,point* b)
{
	point temp;
	
	//temp=a
	temp.x=a->x;
	temp.y=a->y;
	temp.id_x=a->id_x;
	
	//a=b
	a->x=b->x;
	a->y=b->y;
	a->id_x=b->id_x;
	
	//b=temp
	b->x=temp.x;
	b->y=temp.y;
	b->id_x=temp.id_x; 
	
	return ; 
}

void sort(point* arry,int length,int choice)
{

	int i,j;
	if(choice == X)
	{
		for(i=0;i<length-1;i++)
		{
			for(j=0;j<length-1-i;j++)
			{
				if(arry[j].x>arry[j+1].x)
					swap(&arry[j],&arry[j+1]);	
			}	
		}
		
	}
	else if(choice == Y)
	{
		for(i=0;i<length-1;i++)
		{
			for(j=0;j<length-1-i;j++)
			{
				if(arry[j].y>arry[j+1].y)
					swap(&arry[j],&arry[j+1]);	
			}	
		}
		
	}
}

double find_min_pair(int left,int right)
{
	double min_dis = infinite;
	
	if(left==right)
		return infinite;
	else if(right == left + 1)
	{
		min_dis = cal_dis(point_list[left],point_list[right]);
		if(min_dis < min_pair[0].dis)
		{
			min_pair_num = 0;
			min_pair[min_pair_num].dis = min_dis;
			min_pair[min_pair_num].left = left;
			min_pair[min_pair_num].right = right;
			min_pair_num+=1;	
		}
		else if(min_dis == min_pair[0].dis)
		{
		
			min_pair[min_pair_num].dis = min_dis;
			min_pair[min_pair_num].left = left;
			min_pair[min_pair_num].right = right;
			min_pair_num+=1;	
			
		}	
		
		return min_dis; 
	}
		
	int mid = (left+right)/2;
	
	double left_min,right_min;
	left_min = find_min_pair(left,mid);
 	right_min =find_min_pair(mid,right);
	
	min_dis = (left_min<right_min)?left_min:right_min;
	
	//将相应的点放入带状区域 
	int count,strip_num;
	strip_num = 0;
	double strip_left,strip_right;
	strip_left = point_list[mid].x-min_dis;
	strip_right = point_list[mid].x+min_dis;
	for(count=0;count<=(right-left);count++)
	{
		if(point_list[count].x>=strip_left&&point_list[count].x<=strip_right)
		{
			strip_area[strip_num] = point_list[count];
			strip_num+=1;
		}
		else if(point_list[count].x>strip_right)
			break;
	}
	
	//将带状区域的点按照y的升序排列 
	sort(strip_area,strip_num,Y);
	
	int j,pair_num;
	pair_num = 0;
	double strip_dis,min_strip_dis;
	min_strip_dis = infinite;
	point_pair strip_pairs[MAX];//point_pair数组用来保存距离最近点对 
	//每一个点与其后七个点计算距离
	for(count=0;count<strip_num;count++)
	{	
		if(strip_num-count<7)//余下的点不足七个
		{
			for(j=1;(count+j)<strip_num;j++)
			{
				strip_dis = cal_dis(strip_area[count],strip_area[count+j]);
				if(strip_dis == min_strip_dis)
				{
					strip_pairs[pair_num].left = (strip_area[count].id_x<strip_area[count+j].id_x)?strip_area[count].id_x:strip_area[count+j].id_x;
					strip_pairs[pair_num].right = (strip_area[count].id_x>strip_area[count+j].id_x)?strip_area[count].id_x:strip_area[count+j].id_x;
					strip_pairs[pair_num].dis = strip_dis;
					pair_num+=1;	
				}
				else if(strip_dis < min_strip_dis)
				{
					min_strip_dis = strip_dis;
					pair_num = 0;
					strip_pairs[pair_num].dis = min_strip_dis;
					strip_pairs[pair_num].left = (strip_area[count].id_x<strip_area[count+j].id_x)?strip_area[count].id_x:strip_area[count+j].id_x;
					strip_pairs[pair_num].right = (strip_area[count].id_x>strip_area[count+j].id_x)?strip_area[count].id_x:strip_area[count+j].id_x;
					pair_num+=1;
				}
					
			}
		}
		else 
		{
			for(j=1;j<=7;j++)
			{
				strip_dis = cal_dis(strip_area[count],strip_area[count+j]);
				if(strip_dis == min_strip_dis)
				{
					strip_pairs[pair_num].left = (strip_area[count].id_x<strip_area[count+j].id_x)?strip_area[count].id_x:strip_area[count+j].id_x;
					strip_pairs[pair_num].right = (strip_area[count].id_x>strip_area[count+j].id_x)?strip_area[count].id_x:strip_area[count+j].id_x;
					strip_pairs[pair_num].dis = strip_dis;
					pair_num+=1;	
				}
				else if(strip_dis < min_strip_dis)
				{
					min_strip_dis = strip_dis;
					pair_num = 0;
					strip_pairs[pair_num].dis = min_strip_dis;
					strip_pairs[pair_num].left = (strip_area[count].id_x<strip_area[count+j].id_x)?strip_area[count].id_x:strip_area[count+j].id_x;
					strip_pairs[pair_num].right = (strip_area[count].id_x>strip_area[count+j].id_x)?strip_area[count].id_x:strip_area[count+j].id_x;
					pair_num+=1;
				}
			}
		}
	
	
	 } 
	 
	 if(min_strip_dis<min_pair[0].dis)
	 {
	 	min_pair_num = 0;
		for(min_pair_num=0;min_pair_num<pair_num;min_pair_num++)
		{
			min_pair[min_pair_num].dis = strip_pairs[min_pair_num].dis;	
			min_pair[min_pair_num].left = strip_pairs[min_pair_num].left;	
			min_pair[min_pair_num].right = strip_pairs[min_pair_num].right;	
		}	
	 }
	 else if(min_strip_dis==min_pair[0].dis)
	 {
	 	for(j=0;j<pair_num;j++)
	 	{	
	 		if(!exist(strip_pairs[j]))	 		
		 	{
				min_pair[min_pair_num+j].dis = strip_pairs[j].dis;	
				min_pair[min_pair_num+j].left = strip_pairs[j].left;	
				min_pair[min_pair_num+j].right = strip_pairs[j].right;	
				min_pair_num+=1;		
			}
		}
	
	 }
	 
	min_dis = (min_strip_dis<min_dis)?min_strip_dis:min_dis; 
	
	return min_dis;
	
}

void input_by_file(FILE *fp)
{
	int i;
	fscanf(fp,"%d",&point_num);
	for(i=0;i<point_num;i++)
	{
		fscanf(fp,"%lf",&point_list[i].x);
		fscanf(fp,"%lf",&point_list[i].y);
	
	}
	
	return;
}

void input_by_hand(void)
{
	int i;
	printf("平面上存在点数为？\n");
	scanf("%d",&point_num);
	printf("输入点的坐标（x,y）：\n");
	for(i=0;i<point_num;i++)
	{
		scanf("%lf",&point_list[i].x);
		scanf("%lf",&point_list[i].y);
	
	}
	
	return;
}

int main(void)
{
	int i,n,times;
	FILE *fp,*fp_out;
	fp = fopen("in.dat","r");
	fp_out = fopen("out.dat","w+");
	fscanf(fp,"%d",&times);
	for(n=0;n<times;n++)
	{
		input_by_file(fp);
		min_pair_num = 0;
		for(i=0;i<=MAX;i++)
			min_pair[i].dis = infinite;
		sort(point_list,point_num,X);
		for(i=0;i<point_num;i++)
			point_list[i].id_x = i;
		
		double distance;
		distance = find_min_pair(0,point_num-1);
		
	/*	if(distance==infinite)
		{
			fprintf(,"infinite\n");
			return 0;
		}
		
		//printf("%lf\n",distance);
		putchar('\n');
	*/	
		int typ_chg_px,typ_chg_py,typ_chg_qx,typ_chg_qy;
		
		for(i=0;i<min_pair_num;i++)
		{
			typ_chg_px = point_list[min_pair[i].left].x;
			typ_chg_py = point_list[min_pair[i].left].y;
			typ_chg_qx = point_list[min_pair[i].right].x;
			typ_chg_qy = point_list[min_pair[i].right].y;
			fprintf(fp_out,"%d %d ",typ_chg_px,typ_chg_py);
			fprintf(fp_out,"%d %d ",typ_chg_qx,typ_chg_qy);
		}
		
		fprintf(fp_out,"\n");
		//putchar('\n');
		//putchar('\n');
	}
	
	fclose(fp);
	fclose(fp_out);
	return 0;
}


