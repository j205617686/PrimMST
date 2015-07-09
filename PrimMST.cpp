#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define INF 9999




	int init(int key[],int n);
	void del();
	bool isin();
	int keyval(int VertexW);
	void decrease(int VertexW,int NewWeight);








struct Container
{
	void (*dele)(bool isin[],int key[],int *next_vertex,int *min,int n,struct Container *self);
	void (*dec)(int *key,int *adj_matrix,int next_vertex ,int count,struct Container *self);
	int (*keyv)(int key,struct Container *self);
		
};







void delet(bool isin[],int key[],int *next_vertex,int *min,int n,struct Container *self)
{
	for (int j=0; j<n; j++)
	  {
			if (isin[j]!=true && key[j] < *min) //���@������key ��̤p�����
            {
                *next_vertex = j;  // �O���o�@�I����
                *min = key[j];     
            }
	}
}

void decrease(int *key,int *adj_matrix,int next_vertex ,int count,struct Container *self)
{
	*key = *adj_matrix; 
}

int keyval(int key,struct Container *self)
{
	return(key);
}





void prim(int **adj_matrix,int start,int parent [],Container &h,int vertex)
{
	int n=vertex;	//�@�X���I

	int *key;		//KEY�N��ثe�����I�̪�dist
	key=new int[vertex];

	     
	bool *isin;		//�����I���S������F,��l�����S��(false)
	isin=new bool[vertex];
	
	int pathsum=0;

	for(int i=0;i<n;i++)
	{
		key[i]=INF;      //��}�l���Ҧ��I��dist����l�Ƭ�Infinite
	}

	key[start]=0;
	parent[start] =start; 
	
	printf("all the path : \n");



	for (int i=0; i<n; i++)
    {
		int next_vertex=-1,min=INF;

	  h.dele(isin,key,&next_vertex,&min,n,&h); //���@������key ��̤p�����,�^���I����

	  if(i<n)
	  {
	  printf("( %d , %d )",parent[next_vertex],next_vertex);
	  if(i!=n-1)
	   printf("->");
	  }

	  
	  pathsum+=min;


	   if (next_vertex == -1)    
	   {}
	   else
       isin[next_vertex] = true;  //�p�G���F�� �N���I��isin�]��true,�N���L
	   

		int count=0;

		while(count<n)
		{
            if  (isin[count]!=true && adj_matrix[next_vertex][count] < h.keyv(key[count],&h))  //�s�_�ӫ�,�p�G����ثe��key�}�C�p��,�N���N��
            {
				parent[count] = next_vertex;

                h.dec(&key[count],&adj_matrix[next_vertex][count],next_vertex,count,&h);   //��key���ȧ令�ثe�̤p��
            }
			count++;

		}

	}
	
	printf("\n\npath length sum: %d",pathsum);


	delete [] key;
	delete []isin;




}






int main(void)
{
	
    FILE *in;
    int vertex=0;
	int NUM_edge=0;
	int *V1;
	int *V2;
	int *E;
	int *parent;

	in=fopen("input.txt","r");
   
	
	assert(in!=NULL);

    if (in==NULL)
    {
    printf("Can't open input file\n");
    }
    else
    {
		fscanf(in,"%d \n",&vertex);
		fscanf(in, "%*[^\n]");
		fscanf(in,"%d ",&NUM_edge);
		fscanf(in, "%*[^\n]");
         
		
	parent=new int[vertex];
	
	V1=new int[NUM_edge];
	
	V2=new int[NUM_edge];
	
	E=new int[NUM_edge];


        for(int i=0;i<NUM_edge;i++)
		{
         fscanf(in,"%d %d %d",&V1[i],&V2[i],&E[i]);
		 fscanf(in, "%*[^\n]");
		}
        
     }


	

	int **graph;
	

	Container h;    //�e��ADT

	h.dele = delet;
	h.dec = decrease;
	h.keyv = keyval;


	graph=new int*[vertex];
	
	for(int i=0;i<vertex;i++)
	{
		graph[i]=new int[vertex];
	
	}

	
     
	assert(graph!=NULL);
	
	for(int j=0;j<vertex;j++)
	{
		graph[j][j]=0;
	}
	

	for(int i=0;i<vertex;i++)
	{
		for(int j=0;j<vertex;j++)
		{
			if(i!=j)
			{
				graph[i][j]=INF;
			}
	
		}
	}
	for(int i=0;i<NUM_edge;i++)
	{
	 graph[V1[i]][V2[i]]=E[i];
	 graph[V2[i]][V1[i]]=E[i];

	}
	
	
	printf("Adjacency Matrix: \n"); 
	for(int i=0;i<vertex;i++)
	{
		for(int j=0;j<vertex;j++)
		{
			if(graph[i][j]==INF)
				printf("%4d",-1);
			else
				printf("%4d",graph[i][j]);
		}
		printf("\n");
	}
     printf("\n");  
      

	 

	prim(graph,0,parent,h,vertex);




	

	for(int i=0;i<vertex;i++)
	{
		delete [] graph[i];
	}

	delete [] graph;

	delete [] parent;
	delete [] V1;
	delete [] V2;
	delete [] E;




	system("pause");
	return(0);
}