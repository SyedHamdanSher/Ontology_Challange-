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
#include <cstring>
using namespace std;
#define MAX 10
int N=0;
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
				cout<<cur->ques[i];
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
				cout<<ccur->ques[i];
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
	cout<<"CNODE"<<endl;
	int i=0;
	if(cur==NULL)
		return;
	while(!cur->ques[i].empty())
		{cout<<s<<endl;
			if((cur->ques[i].find(s))>=0)
				*count=*count+1;
			//else
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
		{cout<<s<<endl;
			if(cur->ques[i].find(s)!=-1){
				cout<<cur->ques[i]<<endl;
				*count=*count+1;
			}
			//cout<<cur->ques[i].find(s)<<endl;
			//else
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
	cout<<sflag<<endl;
	cout<<sflag1<<endl;
	if(cur->value==sflag)
	{
		cout<<"TNODE1"<<endl;
		check(sflag1,cur,&count);
		//check(sflag1,ccur,&count);
		cout<<count<<endl;
	}else{
		cout<<"TNODE2"<<endl;
		temp=cur=root->llink;
		if(cur->value==sflag)
		{
			cout<<"TNODE3"<<endl;
			check(sflag1,cur,&count);
			//check(sflag1,ccur,&count);
			cout<<count<<endl;	
		}else{
			cout<<"TNODE4"<<endl;
			cur=root->rlink;
			if(cur->value==sflag)
			{
				cout<<"TNODE5"<<endl;
				check(sflag1,cur,&count);
				//check(sflag1,ccur,&count);
				cout<<count<<endl;	
			}else{
				cout<<"TNODE6"<<endl;
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
    cout<<ss<<endl;
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
	cout<<ss<<endl;;
    return ss;
}


TNODE constructTree(string s,TNODE root)
{
	int pos;
	cout<<"CT1"<<endl;
	string ss,delimiter="(";
	char flag;
	if(s[0]=='('||s[0]==' '){cout<<"CT2"<<endl;
		for(pos=0;s[pos]=='('||s[pos]==')'||s[pos]==' ';pos++)
		{
			
		}
		s.erase(0, pos);
		cout<<s<<endl;
	}

	pos = s.find(delimiter);
	if(pos!=-1){cout<<"CT3"<<endl;
	ss=cutter(delimiter,s);
	root=insert_node(ss,root);
	s.erase(0, pos + delimiter.length()+1);
	cout<<s<<endl;}
	while(s[0]!='('&&s[0]!=')'){cout<<"CT4"<<endl;		
		delimiter=" ";
		cout<<s<<endl;
		pos = s.find(delimiter);
		ss=cutter(delimiter,s);
		cout<<ss<<endl;
		root=insert_node(ss,root);
		s.erase(0, pos + delimiter.length());
		cout<<s<<endl;
	}
	//display(root);
	cout<<"CT5"<<endl;
	MS.assign(s);
	nr.assign(ss);
	cout<<MS<<endl<<nr<<endl;
	return root;
}

/*TNODE search(TNODE root)
{
	//CCUR=NULL;
	TNODE cur;
	CNODE ccur;
	cur=root;
	ccur=root->more;
	while(cur!=NULL)
	{cout<<"S1"<<endl;
		if(cur->value==nr)
		{cout<<"S2"<<endl;
			N=999;
			return cur;
		}
		else
		{cout<<"S3"<<endl;
			cur=root->llink;
			if(cur->value==nr)
			{cout<<"S4"<<endl;
				N=999;
				return cur;
			}
			else
			{cout<<"S5"<<endl;
				cur=root->rlink;
				if(cur->value==nr)
				{cout<<"S6"<<endl;N=999;
					return cur;
				}
				else
				{cout<<"S7"<<endl;
					while(ccur!=NULL)
					{
						if(ccur->cvalue==nr)
						{cout<<"S8"<<endl;N=999;
							CCUR = ccur;
							return cur;
						}
						else
							ccur=ccur->next;
					}
				}

			}
		}
	}
}*/

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
	//CUR=NULL;
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


/*void distribute(string s,TNODE root)
{
	TNODE cur,c1,c2;
	cur=root;
	int pos;
	string ss,delimiter=":";
	ss=cutter(delimiter,s);
	cout<<ss<<endl;
	pos = s.find(delimiter);
	s.erase(0, pos + delimiter.length());
	cout<<s<<endl;
	nr=ss;
	cur=search(root);
	if(N==999 && CCUR==NULL){
		cur=insert_ques(s,cur,ss);
		cout<<"Found"<< ss<<" insert ques\n";
	}else if(N==999 && CCUR!=NULL){
		cur=insert_ques(s,cur,ss);
		cout<<"Found"<< ss<<" insert ques2\n";
	}else{
		c1=search(root->llink);
		if(N==999 && CCUR==NULL){
			cur=insert_ques(s,c1,ss);
			cout<<"Found"<< ss<<" insert ques\n";
		}else if(N==999 && CCUR!=NULL){
			cur=insert_ques(s,c1,ss);
			cout<<"Found"<< ss<<" insert ques2\n";
		}else{
			c2=search(root->rlink);
			if(N==999 && CCUR==NULL){
				cur=insert_ques(s,c2,ss);
				cout<<"Found"<< ss<<" insert ques\n";
			}else if(N==999 && CCUR!=NULL){
				cur=insert_ques(s,c2,ss);
				cout<<"Found"<< ss<<" insert ques2\n";
			}else{
				cout<<"NOT FOUND"<<endl;
			}
		}
	}
}*/
void distribute(string s,TNODE root)
{
	TNODE cur,c1,c2;
	cur=root;
	int pos;
	string ss,delimiter=":";
	ss=cutter(delimiter,s);
	cout<<ss<<endl;
	pos = s.find(delimiter);
	s.erase(0, pos + delimiter.length());
	cout<<s<<endl;
	nr=ss;
	search(root,ss);
	if(CUR!=NULL)
	{
		cur=insert_ques(s,CUR,ss);
		cout<<"Found"<< ss<<" insert ques\n";
	}else if(CCUR!=NULL){
		cur=insert_ques(s,CUR,ss);
		cout<<"Found"<< ss<<" insert ques\n";
	}else{
		cout<<"NOT found"<<endl;
	}
}
/*void parse(CNODE root,string s)
{
	CNODE ccur,cprev;
	ccur=root;
	while(ccur!=NULL)
	{
		if(ccur->cvalue==s)
		{
			CCUR=ccur;
			return;
		}
		else
		{
			parse(root->next,s);
		}
	}
}
void parse(TNODE root,string s)
{
	TNODE cur,prev;
	
	cur=root;
	while(cur!=NULL)
	{
		if(cur->value==s)
		{
			CUR=cur;
			return;
		}
		else
		{
			parse(root->llink,s);
			//parse(root->rlink,s);
			//parse(root->more,s);
		}
	}
}*/



//Animals ( Reptiles Birds ( Eagles Pigeons Crows ) )
int main(){

	TNODE root=NULL,cur=NULL,temp=NULL;
	//string ss;
	/*root=insert_node("Animals",root);
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
	/*cur=insert_ques("Why are many reptiles green?",root,"Reptiles");
	cout<<"Found Reptiles insert ques\n";
	cur=insert_ques("How do birds fly?",root,"Birds");
	cout<<"Found Birds insert ques\n";
	cur=insert_ques("How endangered are eagles?",root,"Eagles");
	cout<<"Found Eagles insert ques\n";
	cur=insert_ques("Where in the world are pigeons most densely populated?",root,"Pigeons");
	cout<<"Found Pigeons insert ques\n";
	cur=insert_ques("Where do most eagles live?",root,"Eagles");
	cout<<"Found Eagles insert ques\n";

	//display(root);

	outresult("Eagles How en",root);
	outresult("Birds Where",root);
	outresult("Reptiles Why do",root);
	outresult("Animals Wh",root);*/




	/*string flattree,S[10],S1[10];
	int N,M,K,i;
	TNODE root;
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
	CNODE ccur;
	root=constructTree("Animals ( Reptiles Birds ( Eagles Pigeons Crows ) )",root);
	cout<<root->value;
	CUR=NULL;
	//cur=search(root);
	search(root,nr);
	//cout<<cur->value<<endl;
	if(CUR!=NULL)
		cur=constructTree(MS,CUR);
	ccur=cur->more;
	cur=cur->rlink;
	cout<<cur->value<<endl;
	cout<<ccur->cvalue;
	/*string ss,delimiter=":";
	ss=cutter(delimiter,"Reptiles: Why are many reptiles green?");
	cout<<ss<<endl;
	while(CCUR==NULL || CUR==NULL){
		parse(root,ss);
	}
	if(CCUR!=NULL)
		cout<<CCUR->cvalue;
	else
		cout<<CUR->value;*/

	distribute("Reptiles: Why are many reptiles green?",root);
	distribute("Birds: How do birds fly?",root);
	distribute("Eagles: How endangered are eagles?",root);
	distribute("Pigeons: Where in the world are pigeons most densely populated?",root);
	distribute("Eagles: Where do most eagles live?",root);


	outresult("Eagles How en",root);
	outresult("Birds Where",root);
	outresult("Reptiles Why do",root);
	outresult("Animals Wh",root);

	return 0;
}

