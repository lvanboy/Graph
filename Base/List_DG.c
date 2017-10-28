#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max 50
#define isLetter(a)  ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGH(a) (sizeof(a)/sizeof(a[0]))


typedef struct _ENode{
	int ivex;
	struct _ENode *next_edge;
}ENode;


typedef struct _VNode{
	char data;
	ENode *first_edge;
}VNode;


//邻接表
typedef struct _LGraph{
	int vexs_num;
	int edg_num;
	VNode vexs[Max];
}LGraph;




//返回当前顶点在matrix中的位置
int get_position(LGraph g, char ch){
	for (int i = 0; i < g.vexs_num; i++){
		if (g.vexs[i].data == ch){
			return i;
		}
	}
	return -1;
}

//读取指定范围的字符
char read_char(){
	char ch;
	do{
		ch = getchar();
	} while (!isLetter(ch));
	return ch;
}

//将node链接到list的尾部
void link_last(ENode *List, ENode *node){
	ENode *p = List;
	while (p->next_edge){
		p = p->next_edge;
	}
	p->next_edge = node;
}

//数据自己输入
LGraph *Create_Lgraph(){
	int v, e;
	LGraph *pg = NULL;
	char c1, c2;
	int p1, p2;
	printf("input vertex number: ");
	scanf("%d", &v);
	printf("input edge number: ");
	scanf("%d", &e);
	if (v < 1 || e < 1){
		printf("input error: invalid parameters\n");
	}
	//分配内存  结构
	if ((pg = (LGraph *)malloc(sizeof(LGraph))) == NULL){
		return NULL;
	}
	// 初始化 分配内存
	memset(pg, 0, sizeof(LGraph));
	//初始化 顶点 和 边数
	pg->vexs_num = v;
	pg->edg_num = e;
	//初始化邻接表的顶点
	for (int i = 0; i < pg->vexs_num; i++){
		printf("vertex(%d): ", i);
		pg->vexs[i].data = read_char();
		pg->vexs[i].first_edge = NULL;
		
	}
	//初始化邻接表的边
	for (int i = 0; i < pg->edg_num; i++){
		//读入边的起点和终点
		printf("edge(%d): ",i);
		c1 = read_char();
		c2 = read_char();
		p1 = get_position(*pg, c1);
		p2 = get_position(*pg, c2);
		ENode *node1 = (ENode *)malloc(sizeof(ENode));
		node1->ivex = p2;
    node1->next_edge = NULL;
		if (pg->vexs[p1].first_edge == NULL){
			pg->vexs[p1].first_edge = node1;
		}
		else{
			link_last(pg->vexs[p1].first_edge, node1);
		}
		
		
	}
	return  pg;
}

//使用已有数据初始化图
LGraph *Create_example_graph(){
	LGraph *pg = NULL;
	int p1, p2;
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	char edges[][2] = {
		{ 'A', 'C' },
		{ 'A', 'D' },
		{ 'A', 'F' },
		{ 'B', 'C' },
		{ 'C', 'D' },
		{ 'E', 'G' },
		{ 'F', 'G' } };
	if ((pg = (LGraph *)malloc(sizeof(LGraph))) == NULL){
		return pg;
	}
	//内存初始化
	memset(pg, 0, sizeof(LGraph));
	pg->vexs_num = LENGH(vexs);
	pg->edg_num = LENGH(edges);

	//初始化顶点
	for (int i = 0; i < pg->vexs_num; i++){
		pg->vexs[i].data = vexs[i];
		pg->vexs[i].first_edge = NULL;
	}
	//初始化边
	for (int i = 0; i < pg->edg_num; i++){
	
		p1 = get_position(*pg, edges[i][0]);
		p2 = get_position(*pg, edges[i][1]);
		ENode *node1 = (ENode *)malloc(sizeof(ENode));
		if (!node1){
			return NULL;
		}
		node1->ivex = p2;
		node1->next_edge = NULL;
		if (pg->vexs[p1].first_edge == NULL){
			pg->vexs[p1].first_edge = node1;
		}
		else{
			link_last(pg->vexs[p1].first_edge, node1);
		}
		
	}
	return pg;
}


//打印
void print_graph(LGraph *pg){
	ENode *node = NULL;
	printf("List Graph:\n");
	for (int i = 0; i < pg->vexs_num; i++){
		printf("%d(%c)", i, pg->vexs[i].data);
		node = pg->vexs[i].first_edge;
		while (node){
			printf("%d(%c)", node->ivex, pg->vexs[node->ivex].data);
			node = node->next_edge;
		}
		printf("\n");
	}
}

int main(){
	LGraph* pG;
	pG = Create_example_graph();
	print_graph(pG);
	getchar();
	return 0;
}
