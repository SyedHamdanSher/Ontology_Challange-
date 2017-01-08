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
lastwalker@Chelsea:~/Documents/techie$ g++ Ontology.cpp 
lastwalker@Chelsea:~/Documents/techie$ ./a.out
Enter number of Topics (N)
6
N topics arranged in a flat tree:Animals ( Reptiles Birds ( Eagles Pigeons Crows ) )
Enter Number of questions(M)
5
Animals ( Reptiles Birds ( Eagles Pigeons Crows ) )Each line contains a topic name, followed by a colon and a space, and then the question text

Reptiles: Why are many reptiles green?
Birds: How do birds fly?
Eagles: How endangered are eagles?
Pigeons: Where in the world are pigeons most densely populated?
Eagles: Where do most eagles live?
Number of queries (K)
4
Line M+5...M+K+4: Each line contains a topic name, followed by a space, and then the query text

Eagles How en
Birds Where
Reptiles Why do
Animals Wh
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
#include <cstring>
using namespace std;
#define MAX 10
//int N=0;
string MS,nr;

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

CNODE CCUR;
TNODE CUR;

int func(TNODE cur,string source,TNODE root,string q){
	int i=0;
	if (cur->value==source)
	{
		while(i<MAX)
		{
			if(cur->ques[i].empty())
			{
				cur->ques[i].assign(q);
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
				ccur->ques[i].assign(q);
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
void display(TNODE root)
{
	int i;
	CNODE ccur;
	TNODE cur;
	cur=root;
	ccur=root->more;
	for(i=0;i<2;i++){
		cout<<cur->value<<":"<<cur->ques[i]<<endl;
		cur=root->llink;
		cout<<cur->value<<":"<<cur->ques[i]<<endl;
		cur=root->rlink;
		cout<<cur->value<<":"<<cur->ques[i]<<endl;
	}
	while(!ccur->cvalue.empty()){
		for(i=0;i<2;i++){
			cout<<ccur->cvalue<<":"<<ccur->ques[i]<<endl;
		}
		ccur=ccur->next;
	}

}
void check(string s, CNODE cur,int *count)
{
	int i=0;
	if(cur==NULL)
		return;
	while(!cur->ques[i].empty())
		{cout<<s<<endl;
			if((cur->ques[i].find(s))>=0)
				*count=*count+1;
			i++;
		}
		check(s,cur->next,count);
}
void check(string s, TNODE root,int *count)
{
	int i=0;
	TNODE cur,temp,temp1,cur1;
	CNODE ccur;
	cur=root;
	if(root==NULL)
		return;
	
	while(!cur->ques[i].empty())
		{
			if(cur->ques[i].find(s)!=-1){
				
				*count=*count+1;
			}
			i++;
		}
		check(s,root->llink,count);
		check(s,root->rlink,count);
		check(s,root->more,count);
}


void outresult(string s,TNODE root){
	TNODE cur,temp;
	CNODE ccur;
	string sflag,sflag1;
	cur=root;
	ccur=NULL;
	int i=0;
	int count;
	count=0;
	sflag=s.substr(0,s.find_first_of(" "));
	sflag1=s.substr(sflag.length()+1);
	if(cur->value==sflag)
	{
		check(sflag1,cur,&count);
		cout<<count<<endl;
	}else{
		temp=cur=root->llink;
		if(cur->value==sflag)
		{
			check(sflag1,cur,&count);
			cout<<count<<endl;	
		}else{
			cur=root->rlink;
			if(cur->value==sflag)
			{
				check(sflag1,cur,&count);
				cout<<count<<endl;	
			}else{
				if(ccur!=NULL){
				while(!ccur->cvalue.empty()){
					if(ccur->cvalue==sflag){
						check(sflag1,ccur,&count);
						cout<<count<<endl;
						return;
						}else{
						cout<<"Not found"<<endl;	
					}ccur=ccur->next;	
				}}else{
					outresult(s,cur);
					//outresult(s,temp);
				}
			}
		}
		
	}
}
string cutter(string delimiter,string s)
{
	size_t pos = 0,endpos,startpos;
	string ss;
	pos = s.find(delimiter);
    ss = s.substr(0, pos);
    endpos = ss.find_last_not_of(" \t");
	if( string::npos != endpos )
	{
    	ss = ss.substr( 0, endpos+1 );
	}
	startpos = ss.find_first_not_of(" \t");
	if( string::npos != startpos )
	{
    	ss = ss.substr( startpos );
	}
    return ss;
}


TNODE constructTree(string s,TNODE root)
{
	int pos;
	string ss,delimiter="(";
	char flag;
	if(s[0]=='('||s[0]==' '){
		for(pos=0;s[pos]=='('||s[pos]==')'||s[pos]==' ';pos++)
		{
			
		}
		s.erase(0, pos);
	}

	pos = s.find(delimiter);
	if(pos!=-1){
	ss=cutter(delimiter,s);
	root=insert_node(ss,root);
	s.erase(0, pos + delimiter.length()+1);
	}
	while(s[0]!='('&&s[0]!=')'){		
		delimiter=" ";
		pos = s.find(delimiter);
		ss=cutter(delimiter,s);
		root=insert_node(ss,root);
		s.erase(0, pos + delimiter.length());
	}
	MS.assign(s);
	nr.assign(ss);
	return root;
}



void search(CNODE root,string s)
{
	if(root==NULL)
		return;
	if(root->cvalue==s)
	{
		CCUR=root;
	}
	else{
		search(root->next,s);
	}
}
void search(TNODE root,string s)
{
	if(root==NULL)
		return;
	if(root->value==s)
	{
		CUR=root;
	}
	else{
		search(root->llink,s);
		search(root->rlink,s);
		search(root->more,s);
	}
}


void distribute(string s,TNODE root)
{
	TNODE cur,c1,c2;
	cur=root;
	int pos;
	string ss,delimiter=":";
	ss=cutter(delimiter,s);
	pos = s.find(delimiter);
	s.erase(0, pos + delimiter.length());
	nr=ss;
	search(root,ss);
	if(CUR!=NULL)
	{
		cur=insert_ques(s,CUR,ss);
	}else if(CCUR!=NULL){
		cur=insert_ques(s,CUR,ss);
	}else{
		cout<<"NOT found"<<endl;
	}
}

int main(){

	TNODE root=NULL,cur=NULL,temp=NULL;
	string flattree,S[10],S1[10];
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
	cout << "Number of queries (K)\n";
	cin >> K;
	cin.ignore();
	cout << "Line M+5...M+K+4: Each line contains a topic name, followed by a space, and then the query text\n"<<endl;
	for (i = 0; i < K; i++)
	{
		getline(cin, S1[i]);
	}
	CNODE ccur;
	root=constructTree(flattree,root);
	CUR=NULL;
	search(root,nr);
	if(CUR!=NULL)
		cur=constructTree(MS,CUR);
	for (i = 0; i < M; i++)
	{
		distribute(S[i],root);
	}
	for (i = 0; i < K; i++)
	{
		outresult(S1[i],root);
	}
	return 0;
}

