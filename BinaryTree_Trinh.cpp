#include<bits/stdc++.h>
using namespace std;

struct Node{
	int data;
	int getbalance;
	int height;
	Node *right;
	Node *left;
};

typedef struct Node* node;

class BinaryTree{
	private:
		node root = NULL;
		int size = 0;
	public:		
		node getRoot(){
			return root;
		}
		
		node createRoot(int &data){
			root = createNode(data);
		}
		
		void printTree(node tmp){
			if(tmp != NULL){
				printTree(tmp->left);
				cout<<tmp->data<<" ";
				printTree(tmp->right);
			}
		}
		
		void preOrder(node current)  {  
		    if(current != NULL)  
		    {  
		        cout << current->data << " ";  
		        preOrder(current->left);  
		        preOrder(current->right);  
		    }  
		}  
		
		node createNode(int data){
			node tmp = new Node();
			tmp->data = data;
			int height = 1;
			tmp->right = tmp->left = NULL;
			return tmp;
		}
		
		
		node search(node current, int data){
			if(current == NULL){
				return NULL;
			}else{
				if(current->data == data){
					return current;
				}else{
					if(data >= current->data){
						search(current->right, data);
					}else{
						search(current->left, data);
					}
				}
			}			
		}
		
		int height(node current){
			return current->height;
		}
		
		int getBalance(node current){
			return height(current->right) - height(current->left);
		}
		node MIN(node current){
			while(current->left != NULL){
				current = current->left;
			}
			return current;
		}
		
		node MAX(node current){
			while(current->right != NULL){
				current = current->right;
			}
			return current;
		}
		
		node Father(node current, int data){
			node child = getRoot();
			node father = NULL;
			while(child->data != data){
				father = child;
				if(data >= child->data){
					child = child->right;
				}else{
					child = child->left;
				}
			}
			return father;
		}
		
		node leftRolate(node current){
			node y = current->right;
			node z = y->left;
			//rolate
			y->left = current;
			current->right = z;
			//height			
			current->height = max(height(current->left), height(current->right)) + 1;
			y->height = max(height(y->left), height(y->right)) + 1;	
			return y;		
		}
		
		node rightRolate(node current){
			node y = current->left;
			node z = y->right;
			//rolate
			y->right = current;
			current->left = z;
			//height
			current->height = max(height(current->left), height(current->right)) + 1;
			y->height = max(height(y->left), height(y->right)) + 1;	
			return y;
		}
		
		node insertTree(node current, int data){
				if(current == NULL){
					return createNode(data);
				}else{
					if(data >= current->data){
						current->right = insertTree(current->right, data);
					}else{
						current->left = insertTree(current->left, data);
					}
					
					current->height = 1 + max(current->left->height, current->right->height);
					
					int balance = getBalance(current);
					//LEFT RIGHT
					if(balance < -1 && data > current->left->data){
						current->left = leftRolate(current->left);
						return rightRolate(current);
					}
					//LEFT LEFT
					if(balance < - 1 && data < current->left->data){
						return rightRolate(current);
					}
					//RIGHT RIGHT
					if(balance > 1 && data > current->right->data){
						return leftRolate(current);
					}
					//RIGHT LEFT
					if(balance > 1 && data < current->right->data){
						current->right = rightRolate(current->right);
						return leftRolate(current);
					}
				}			
			return current; 
			size++;				
		}
		
		node deleteNode(node current, int &data){
			if(current == NULL){
				return current;
			}else{
				if(data > current->data){
					current->right = deleteNode(current->right, data);
				}else if(data < current->data){
					current->left = deleteNode(current->left, data);
				}else{
					if(current->right == NULL){
						node tmp = current->left;
						delete current;	
						return tmp;					
					}else if(current->left == NULL){
						node tmp = current->right;
						delete current;
						return tmp;
					}else{
						node tmp = MIN(current->right);
						current->data = tmp->data;
						current->right = deleteNode(current->right, tmp->data);
					}
				}
			}	
			return current;		
			size--;
		}
};
int main(){
	BinaryTree tree;
	int n; cin>>n;
	for(int i = 0; i < n; i++){
		int data; cin>>data;
		if(i == 0){
			tree.createRoot(data);
		}else{
			tree.insertTree(tree.getRoot(), data);
		}		
	}
//	int data; cin>>data;
//	tree.deleteNode(tree.getRoot(), data);
	cout<<endl;
	tree.printTree(tree.getRoot());
	cout<<endl;
	tree.preOrder(tree.getRoot());
}
