#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

typedef struct Node
{
	short X, Y;
	int F;
}Node;

char Map[1010][1010];
int MapG[1010][1010], n, m, last, dx1, dy1, dx2, dy2;
Node heap[1001000], best, tmp, s, e;

//MinHeap
void Swap(int x, int y)
{
	tmp = heap[x], heap[x] = heap[y], heap[y] = tmp;
}

void InsNode()
{
	int now = last, base = last >> 1;
	while (base > 0 && heap[base].F > heap[now].F)
		Swap(now, base), now = base, base >>= 1;
}

void DelNode()
{
	int now = 1, Derived = now << 1;
	Swap(1, last--);
	while (Derived <= last)
	{
		if (heap[Derived + 1].F < heap[Derived].F && Derived < last) Derived++;
		if (heap[now].F <= heap[Derived].F) break;
		Swap(now, Derived), now = Derived, Derived <<= 1;
	}
}

//A-Star
int H(int nX, int nY)
{
	dx1 = nX - e.X, dy1 = nY - e.Y;//dx1 * dy2 - dx2 * dy1 >> '點n'越接近'線se'其值越小
	printf("Now %d , %d ; best = %d , %d \n",nX,nY,best.X,best.Y);
	printf("%d\n",abs(dx1 * dy2 - dx2 * dy1) + (abs(nX - e.X) + abs(nY - e.Y)) * 1000000);
	return abs(dx1 * dy2 - dx2 * dy1) + (abs(nX - e.X) + abs(nY - e.Y)) * 1000000;
}

void Judge(int x, int y)
{
	if (Map[x][y] != 'X' && (MapG[x][y] > MapG[best.X][best.Y] + 1 || MapG[x][y] == -1))
	{
		MapG[x][y] = MapG[best.X][best.Y] + 1;
		heap[++last].F = MapG[x][y] * 1000000 + H(x, y)
		heap[last].X = x, heap[last].Y = y;

		InsNode();
	}
}

void Astar()
{
	if (Map[s.X][s.Y] == 'X' || Map[e.X][e.Y] == 'X')
	{
		puts("ERROR");
		return;
	}
	//Clear
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			MapG[i][j] = -1;
	}
	//Astar
	last = 0, dx2 = s.X - e.X, dy2 = s.Y - e.Y;
	Judge(s.X, s.Y);
	while (last > 0)
	{
		best = heap[1];
		if (best.X == e.X && best.Y == e.Y) break;
		DelNode();
		Judge(best.X + 1, best.Y);
		Judge(best.X - 1, best.Y);
		Judge(best.X, best.Y + 1);
		Judge(best.X, best.Y - 1);
	}
	
	for(int i = 0; i < n; i++){
		for(int j=0;j < n; j++)
			printf("%3d ", MapG[i][j]);
		printf("\n");
	}

	printf("%d\n", MapG[e.X][e.Y]);
}

int main()
{
	scanf("%d %d", &n, &m);
	getchar();
	for (int i = 0; i < n; i++)
		fgets(Map[i], 1010, stdin);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d %d", &s.X, &s.Y, &e.X, &e.Y);
		Astar();
	}
	return 0;
}
