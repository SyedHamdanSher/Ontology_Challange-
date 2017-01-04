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

struct chainNODE
{
	string cvalue;
	chainNODE *next;
	//chainNODE *prev;
};
typedef chainNODE* CNODE;
struct treeNODE
{
	string value;
	treeNODE *rlink;
	treeNODE *llink;
	CNODE more;
};
typedef treeNODE* TNODE;

TNODE insert_node(string item, TNODE root)
{
	TNODE cur,temp,prev;
	CNODE ctemp;
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
			return cur;
		}
		else if(cur->rlink == NULL)
		{
			prev->rlink=temp;
			return cur;
		}
		else
		{
			CNODE ccur;
			ctemp = (CNODE)malloc(sizeof(struct chainNODE));
			ctemp->cvalue = item;
			ctemp->next=NULL;
			if(cur->more==NULL){
				cur->more=ctemp;
				return cur;
			}
			else
			{
				ccur=cur->more;
				while(ccur->next!=NULL)
					ccur=ccur->next;
				ccur->next=ctemp;
				return cur;
			}
		}
}

int main(){

	TNODE root=NULL,cur;
	root=insert_node("Fruits",root);
	cout<<root->value;
	root=insert_node("Apple",root);
	cur=root;
	cur=cur->llink;
	cout<<cur->value;
	root=insert_node("Orange",root);
	cur=root;
	cur=cur->rlink;
	cout<<cur->value;
	root=insert_node("Banana",root);
	cur=root;
	CNODE ccur;
	ccur=cur->more;
	cout<<ccur->cvalue;
	root=insert_node("Mango",root);
	root=insert_node("Mango1",root);
	root=insert_node("Mango2",root);
	cur=root;
	ccur=cur->more;
	while(ccur->next!=NULL){
		ccur=ccur->next;
		cout<<ccur->cvalue;
	}

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

