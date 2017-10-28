#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 50

#define isLetter(a) ((((a)>='a')&&((a)<='z'))||(((a)>='A')&&((a)<='Z')))
#define LENGH(a) (sizeof(a)/sizeof(a[0]))

//邻接矩阵结构
typedef struct _matrix_udg{
	char vexs[Max];
	int vexs_num;
	int edg_num;
	int Matrix[Max][Max];
}Graph,*PGraph;

//返回当前顶点在matrix中的位置
int get_position(Graph g,char ch){
	for (int i = 0; i < g.vexs_num; i++){
		if (g.vexs[i] == ch){
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

//手动输入数据
Graph *Create_Graph(){
	Graph *pg;
	int v, e;
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
	if ((pg = (Graph *)malloc(sizeof(Graph)) )== NULL){
		return NULL;
	}
	// 初始化 分配内存
	memset(pg, 0, sizeof(Graph));
	//初始化 顶点 和 边数
	pg->vexs_num = v;
	pg->edg_num = e;
	//初始化顶点
	for (int i = 0; i < pg->vexs_num; i++){
		printf("vertex(%d)", i);
		pg->vexs[i] = read_char();
		printf("\n");
	}
	//初始化边
	for (int i = 0; i < pg->edg_num; i++){
		printf("edge(%d)", i);
		//输入起点和终点
		c1 = read_char();
		c2 = read_char();
		p1 = get_position(*pg, c1);
		p2 = get_position(*pg, c2);
		if (p1 == -1 || p2 == -1){
			printf("\ninput error:invalid edge\n");
			free(pg);
			return NULL;
		}
		pg->Matrix[p1][p2] = 1;
		pg->Matrix[p2][p1] = 1;
	}
	return pg;
}

//使用已有数据
Graph *Create_example_graph(){
	Graph *pg = NULL;
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
	if ((pg = (Graph *)malloc(sizeof(Graph))) == NULL){
		return pg;
	}
	memset(pg, 0, sizeof(Graph));
	pg->vexs_num = LENGH(vexs);
	pg->edg_num = LENGH(edges);
	//初始化顶点
	for (int i = 0; i < pg->vexs_num; i++){
		printf("vexs(%d)\n", i);
		pg->vexs[i] = vexs[i];
	}
	//初始化边
	for (int i = 0; i < pg->edg_num; i++){
		printf("edge(%d)\n", i);
		//起点和结束位置
		p1 = get_position(*pg, edges[i][0]);
		p2 = get_position(*pg, edges[i][1]);
		pg->Matrix[p1][p2] = 1;
		pg->Matrix[p2][p1] = 1;
	}

	return pg;
}

//打印矩阵
void print_graph(Graph *pg){
	for (int i = 0; i < pg->vexs_num; i++){
		for (int j = 0; j < pg->vexs_num; j++){
			if (pg->Matrix[i][j] == 1){
				printf("%c->%c\n", pg->vexs[i], pg->vexs[j]);
			}
		}
	}
}

int main(){
	//Graph *pg = Create_example_graph();
	Graph *pg = Create_Graph();
	print_graph(pg);
	getchar();
	return 0;
}
