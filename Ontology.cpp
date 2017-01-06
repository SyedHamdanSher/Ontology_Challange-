/*Ontology

Quora has many questions on different topics, and a common product use-case for our @mention selectors and search service is to look-up questions under a certain topic as quickly as possible.

For this problem, imagine a simplified version of Quora where each question has only one topic associated with it. In turn, the topics form a simplified
ontology where each topic has a list of children, and all topics are descendants of a single root topic.

Design a system that allows for fast searches of questions under topics. There are NN topics, MM questions, and KK queries, given in this order. Each query has a desired topic as well as a desired string prefix. For each query, return the number of questions that fall under the queried topic and begin with the desired string. When considering topics, we want to include all descendants of the queried topic as well as the queried topic itself. In other words, each query searches over the subtree of the topic.

The topic ontology is given in the form of a flattened tree of topic names, where each topic may optionally have children. If a topic has children, they are listed after it within parentheses, and those topics may have children of their own, etc. See the sample for the exact input format. The tree is guaranteed to have a single root topic.

For ease of parsing, each topic name will be composed of English alphabetical characters, and each question and query text will be composed of English alphabetical characters, spaces, and question marks. Each question and query text will be well behaved: there will be no consecutive spaces or leading/trailing spaces. All queries, however, are case sensitive.

Constraints
For 100% of the test data, 1≤N,M,K≤1051≤N,M,K≤105 and the input file is smaller than 5MB
For 50% of the test data, 1≤N,M,K≤2⋅1041≤N,M,K≤2⋅104 and the input file is smaller than 1MB

Input Format
Line 1: One integer NN
Line 2: NN topics arranged in a flat tree (see sample)
Line 3: One integer MM
Line 4...M+3: Each line contains a topic name, followed by a colon and a space, and then the question text.
Line M+4: One integer KK
Line M+5...M+K+4: Each line contains a topic name, followed by a space, and then the query text.

Output Format
Line 1...K: Line ii should contain the answer for the iith query.

Sample Input
6
Animals ( Reptiles Birds ( Eagles Pigeons Crows ) )
5
Reptiles: Why are many reptiles green?
Birds: How do birds fly?
Eagles: How endangered are eagles?
Pigeons: Where in the world are pigeons most densely populated?
Eagles: Where do most eagles live?
4
Eagles How en
Birds Where
Reptiles Why do
Animals Wh


Sample Output
1
2
0
3


Explanation
The first query corresponds to the green area in the diagram, since it is looking for topics under Eagles, and the query string matches just one question: "How endangered are eagles?" The second query corresponds to the blue area in the diagram, which is the subtree of Birds, and matches two questions that begin  with "Where". The third corresponds to the red area, which does not have any questions that begin with "Why do". The final query corresponds to the entire tree, since Animals is the root topic, and matches three questions.*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;
#define MAX 10

struct chainNODE
{
	string cvalue;
	chainNODE *next;
	string ques[MAX];
	//chainNODE *prev;
};
typedef chainNODE* CNODE;
struct treeNODE
{
	string value;
	treeNODE *rlink;
	treeNODE *llink;
	CNODE more;
	string ques[MAX];
};
typedef treeNODE* TNODE;

int func(TNODE cur,string source,TNODE root,string q){
	int i=0;
	if (cur->value==source)
	{
		while(i<MAX)
		{
			if(cur->ques[i].empty())
			{
				q.copy((char *)cur->ques[i].data(),0,q.length());
				return 0;
			}
			else
				i++;
		}
	}
	else
		return 1;
}
int func1(CNODE ccur,string source,string q){
	int i=0;
	if (ccur->cvalue==source)
	{
		while(i<MAX)
		{
			if(ccur->ques[i].empty())
			{
				q.copy((char *)ccur->ques[i].data(),0,q.length());
				return 0;
			}
			else
				i++;
		}
	}
	else
		return 1;
}

TNODE insert_node(string item, TNODE root)
{
	TNODE cur,temp,prev;
	CNODE ctemp;
	int i;
	temp = (TNODE)malloc(sizeof(struct treeNODE));
	temp->value = item;
	temp->llink=temp->rlink=NULL;
	temp->more=NULL;
	/*for (i = 0; i < MAX; i++)
	{
		temp->ques[i]="";
	}*/
	if(root == NULL)
		return temp;
	prev = NULL;
	cur = root;
		prev = cur;
		if(cur->llink == NULL)
		{
			prev->llink=temp;
			return root;
		}
		else if(cur->rlink == NULL)
		{
			prev->rlink=temp;
			return root;
		}
		else
		{
			CNODE ccur;
			ctemp = (CNODE)malloc(sizeof(struct chainNODE));
			ctemp->cvalue = item;
			ctemp->next=NULL;
			/*for (i = 0; i < MAX; i++)
			{
				ctemp->ques[i]="";
			}*/
			if(cur->more==NULL){
				cur->more=ctemp;
				return root;
			}
			else
			{
				ccur=cur->more;
				while(ccur->next!=NULL)
					ccur=ccur->next;
				ccur->next=ctemp;
				return root;
			}
		}
}

TNODE insert_ques(string q,TNODE root,string source)
{
	TNODE cur,temp,prev;
	CNODE ccur;
	int i=0,flag;
	if(root == NULL)
		return NULL;
	cur = root;
	ccur=root->more;
	if (cur->value==source)
	{
		flag=func(cur,source,root,q);
		return cur;
	}
	else{
			cur=cur->llink;
			flag=func(cur,source,root,q);
			if(flag==0)
				return root;
			else{
				cur=root->rlink;
				flag=func(cur,source,root,q);
				if(flag==0)
					return root;
				else{
					while(ccur->cvalue!=source && ccur!=NULL){
					ccur=ccur->next;
					}
					if(ccur->cvalue==source){
						flag=func1(ccur,source,q);
					if(flag==0)
						return root;
					else
						return NULL;
					}
					else
						return NULL;
				}
			}
		}
}


//Animals ( Reptiles Birds ( Eagles Pigeons Crows ) )
int main(){

	TNODE root=NULL,cur=NULL;
	root=insert_node("Animals",root);
	cout<<root->value;
	cur=insert_node("Reptiles",root);
	cur=root;
	cur=cur->llink;
	cout<<cur->value;
	cur=insert_node("Birds",root);
	cur=root;
	cur=cur->rlink;
	cout<<cur->value;
	cur=insert_node("Eagles",root);
	cur=root;
	CNODE ccur;
	ccur=cur->more;
	cout<<ccur->cvalue;
	cur=insert_node("Pigeons",root);
	cur=insert_node("Crows",root);
	//root=insert_node("Mango2",root);
	cur=root;
	ccur=cur->more;
	while(ccur->next!=NULL){
		ccur=ccur->next;
		cout<<ccur->cvalue;
	}
/*
Reptiles: Why are many reptiles green?
Birds: How do birds fly?
Eagles: How endangered are eagles?
Pigeons: Where in the world are pigeons most densely populated?
Eagles: Where do most eagles live?
4
Eagles How en
Birds Where
Reptiles Why do
Animals Wh
*/
	cur=insert_ques("Why are many reptiles green?",root,"Reptiles");
	cout<<"Found Reptiles insert ques\n";
	cur=insert_ques("How do birds fly?",root,"Birds");
	cout<<"Found Birds insert ques\n";
	cur=insert_ques("How endangered are eagles?",root,"Eagles");
	cout<<"Found Eagles insert ques\n";
	root=insert_ques("Where in the world are pigeons most densely populated?",root,"Pigeons");
	cout<<"Found Pigeons insert ques\n";
	root=insert_ques("Where do most eagles live?",root,"Eagles");
	cout<<"Found Eagles insert ques\n";
	/*string flattree,S[10],S1[10];
	int N,M,K,i;
	cout << "Enter number of Topics (N)\n";
	cin >> N;
	cin.ignore();
	cout << "N topics arranged in a flat tree:";
	getline (cin, flattree);
	cout << "Enter Number of questions(M)\n";
	cin >> M;
	cout<<flattree;
	cin.ignore();
	cout<<"Each line contains a topic name, followed by a colon and a space, and then the question text\n"<<endl;
	for (i = 0; i < M; i++)
	{
	 	getline(cin, S[i]);
	}
	for (i = 0; i < M; i++)
	{
	 	cout<<S[i]<<endl;
	} 
	cout << "Number of queries (K)\n";
	cin >> K;
	cin.ignore();
	cout << "Line M+5...M+K+4: Each line contains a topic name, followed by a space, and then the query text\n"<<endl;
	for (i = 0; i < K; i++)
	{
		getline(cin, S1[i]);
	}
	for (i = 0; i < K; i++)
	{
		cout<<S1[i]<<endl;
	}*/
	return 0;
}

