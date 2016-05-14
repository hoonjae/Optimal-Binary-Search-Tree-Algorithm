#include <iostream>
using namespace std;

int avgComp = 0;

void enterNode(int keys, float **pKey)
{
	for(int i = 0; i<keys; i++)
	{
		cout<< i+1 <<"��° Ű���� Ȯ���� �Է��ϼ��� : ";
		cin>>pKey[0][i];
		cin>>pKey[1][i];
	}
}

float minimumProbability(int i, int j, float **pKey,float **A, int **rootNode)
{
	float totalp = 0;
	for(int a = i; a<=j; a++)
		totalp += pKey[1][a];

	int subRootNode = 0;
	float minprob = 0;
	for(int a = i; a<=j; a++)
	{
		if(a == i)
		{
			minprob = A[a+1][j];
			subRootNode = i;
		}
		else if(a == j)
		{
			if(minprob >= A[i][a-1] && (pKey[1][subRootNode] < pKey[1][a]))
			{
				minprob = A[i][a-1];
				subRootNode = j;
			}
		}
		else
		{
			if(minprob >= A[i][a-1] + A[a+1][j] && (pKey[1][subRootNode] < pKey[1][a]))
			{
				minprob = A[i][a-1] + A[a+1][j];
				subRootNode = a;
			}
		}
		rootNode[i][j] = subRootNode;
	}
	
	totalp = totalp + minprob;
	return totalp;
}

void initialTable(int keys, float **pKey, float **A, int **rootNode)
{
	//���̺�A�� ���̺�rootNode�� ��� ���Ҹ� -1�� �ʱ�ȭ
	for(int j = 0; j<keys; j++)
	{
		for(int i = 0; i<keys; i++)
		{
			A[i][j] = -1;
			rootNode[i][j] = -1;
		}
	}

	for(int j = 0; j<keys; j++)
	{
		for(int i = 0; i<keys; i++)
		{
			if(i+j<keys)
			{
				if(i == i+j)
				{
					A[i][i+j] = pKey[1][i];
					rootNode[i][i+j] = i;
				}

				else
				{
					A[i][i+j] = minimumProbability(i, i+j, pKey, A, rootNode);
				}
			}
		}
	}
}

void deleteNode(int keys, float **pKey, float **A, int **rootNode)
{
	for(int i = 0; i<2; i++)
		delete [] pKey[i];
	delete[] pKey;

	for(int i = 0; i<keys; i++)
	{
		delete[] A[i];
		delete[] rootNode[i];
	}
	delete[] A;
	delete[] rootNode;
}

void printResult(int start,int end, int count, float **pKey, float **A, int **rootNode)
{
	if(start <= end && end >=start)
		{
		int treeK = rootNode[start][end];
		avgComp += pKey[1][treeK] * count;
		
		if(treeK == end)
		{
			cout<<pKey[0][treeK]<<"("<<pKey[1][treeK]<<")"<<"\t";
			printResult(start, end-1, count+1, pKey, A, rootNode);
		}
		else if(treeK == start)
		{
			cout<<pKey[0][treeK]<<"("<<pKey[1][treeK]<<")"<<"\t";
			printResult(start+1, end, count+1, pKey, A, rootNode);
		}
		else
		{
			cout<<pKey[0][treeK]<<"("<<pKey[1][treeK]<<")"<<"\t";
			printResult(start, treeK-1, count+1, pKey, A, rootNode);

			cout<<endl;
			for(int i = 0; i<count; i++)
				cout<<"\t";			

			printResult(treeK+1, end, count+1, pKey, A, rootNode);
		}	
	}
}

void main()
{
	int keys;
	cout<<"����� ������ �Է��ϼ��� : ";
	cin>>keys;

	//Ű���� Ȯ�� ���� �迭
	float **pKey = new float*[2];
	for(int i = 0; i<2; i++)
		pKey[i] = new float[keys];

	enterNode(keys, pKey);


	////���Ž���ð� ���� ���̺� A
	float **A = new float * [keys];
	for(int i = 0; i<keys; i++)
		A[i] = new float[keys];

	////tree K�� root ���� ���̺� rootNode
	int **rootNode = new int * [keys];
	for(int i = 0; i<keys; i++)
		rootNode[i] = new int[keys];

	initialTable(keys, pKey, A, rootNode);


	for(int i = 0; i<keys; i++)
	{
		for(int j = 0; j<keys; j++)
			cout<<A[i][j]<<"\t";
		cout<<endl;
	}

	for(int i = 0; i<keys; i++)
	{
		for(int j = 0; j<keys; j++)
			cout<<rootNode[i][j]<<"\t";
		cout<<endl;
	}
	

	int count = 1;
	cout<<endl<<"Result Tree (Ű��(Ȯ��), depth 0 -> 1 -> ...)"<<endl;
	printResult(0, keys-1, count, pKey, A, rootNode);
	cout<<endl<<endl<<"��պ񱳼� : "<<avgComp<<endl;
	
	
	deleteNode(keys, pKey, A, rootNode);
}