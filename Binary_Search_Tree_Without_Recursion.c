#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
}*root=NULL;

struct Stack
{
	struct Node* tree;
	struct Stack* next;	
}*head=NULL,*tail=NULL;

struct Stack* create_new_Stack()
{
	return (struct Stack*)calloc(1,sizeof(struct Stack));
}

void free_all_stack()
{
	struct Stack* ptr=head;
	while(ptr)
	{
		head=head->next;
		free(ptr);
		ptr=head;
	}
	
	head=tail=NULL;
}

struct Stack** push(struct Node* ptr)
{
	struct Stack* nd=create_new_Stack();
	
	if(!nd)
	{
		printf("\n\nERROR: Dynamic allocation failed.");
		return NULL;
	}
	
	if(head)
	tail->next=nd;
	
	else
	head=nd;
	
	tail=nd;
	
	nd->tree=ptr;
	nd->next=NULL;
	
	return &head;
}

void pop()
{
	if(!head->next)
	{
	
		head=NULL;
		
		free(tail);
		tail=head;
		
		return;
	}
	
	struct Stack *ptr=head;
	
	while(ptr->next->next)
	ptr=ptr->next;
	
	free(ptr->next);
	ptr->next=NULL;
	
	tail=ptr;
}

struct Node* top()
{
	if(!head)
	return NULL;
	
	return tail->tree;
}

struct Node* new_node_allocate()
{
	return (struct Node*)calloc(1,sizeof(struct Node));
}

struct Node* insert_node(struct Node* node,int data)
{
	struct Node* node_copy=node;
	
	if(!node_copy)
	{
		node_copy=new_node_allocate();
		
		if(!node_copy)
		printf("\n\nERROR: Dynamic allocation failed.");		
		
		else
		{
			node_copy->data=data;
			printf("\n\nMESSAGE: Insertion successful. Given data '%d' successfully inserted in the tree.");
		}
		
		return node_copy;
	}
	
	while(node_copy)
	{
		if(data<node_copy->data)
		{
			if(!node_copy->left)
			{
				node_copy->left=new_node_allocate();
			
				if(!node_copy->left)
				printf("\n\nERROR: Dynamic allocation failed.");
				
				else
				{
					node_copy->left->data=data;		
					printf("\n\nMESSAGE: Insertion successful. Given data '%d' successfully inserted in the tree.");
				}
				
				return node;	
			}	
			
			node_copy=node_copy->left;
		}
		
		else if(data>node_copy->data)
		{
			if(!node_copy->right)
			{
				node_copy->right=new_node_allocate();
				
				if(!node_copy->right)
				printf("\n\nERROR: Dynamic allocation failed.");
				
				else
				{
					node_copy->right->data=data;
					printf("\n\nMESSAGE: Insertion successful. Given data '%d' successfully inserted in the tree.");
				}
				
				return node;
			}
			
			node_copy=node_copy->right;
		}
		
		else
		{
			printf("\n\nERROR: Given data '%d' already exists in the tree.",data);
			return node;
		}
	}
}

struct Node* delete_node(struct Node* node,int data)
{	
	struct Node* curr=node, *prev1=NULL;
	
	while(curr && curr->data!=data)
	{
		prev1=curr;
		
		if(data<curr->data)
		curr=curr->left;
		
		else
		curr=curr->right;
	}
	
	if(!curr)
	{
		printf("\n\nERROR: Deletion operation failed. Given data '%d' not found in the tree.",data);
		return node;
	}
	
	if(!curr->left || !curr->right)
	{
		struct Node* temp;
		
		if(!curr->left)
		temp=curr->right;
		
		else
		temp=curr->left;
		
		if(!prev1)
		return temp;
		
		if(prev1->left==curr)
		prev1->left=temp;
		
		else
		prev1->right=temp;
		
		free(curr);
	}
	
	else
	{
		struct Node* prev2=NULL,*temp=curr->right;
		
		while(temp->left)
		{
			prev2=temp;
			temp=temp->left;
		}
		
		if(prev2)
		prev2->left=temp->right;
		
		else
		curr->right=temp->right;
		
		curr->data=temp->data;
		
		free(temp);
	}
	
	printf("\n\nMESSAGE: Deletion successful. Given data '%d' successfully deleted from the data.",data);
	
	return node;
}

void search_node(struct Node* node,int data)
{
	while(node)
	{
		if(data<node->data)
		node=node->left;
		
		else if(data>node->data)
		node=node->right;
		
		else
		{
			printf("\n\nMESSAGE: Search operation successful. Given data '%d' successfully found in the tree.",data);
			return;
		}
	}
	
	printf("\n\nERROR: Search operation failed. Given data '%d' not present in the tree.",data);
}

void pre_order(struct Node* node)
{
	push(node);
	
	while(head)
	{
		struct Node* ptr=top();
		pop();
		
		printf("%d  ",ptr->data);
		
		if(ptr->right)
		push(ptr->right);
		
		if(ptr->left)
		push(ptr->left);
	}
}

void in_order(struct Node* node)
{
	while(node || head)
	{
		while(node)
		{
			push(node);
			node=node->left;
		}
		
		node=top();
		pop();
		
		printf("%d  ",node->data);
		
		node=node->right;
	}
}

void post_order(struct Node* node)
{
	do
	{
		while(node)
		{
			if(node->right)
			push(node->right);
			
			push(node);
			
			node=node->left;
		}
		
		node=top();
		pop();
		
		if(node->right && top()==node->right)
		{
			pop();
			push(node);
			node=node->right;
		}
		
		else
		{
			printf("%d  ",node->data);
			node=NULL;
		}
	}while(head);
}

void main_menu()
{
	printf(" MAIN-MENU: (BINARY SEARCH TREE)\n---------------------------------");
	printf("\n\n0) Exit");
	printf("\n1) Insertion in the tree.");
	printf("\n2) Deletion from the tree.");
	printf("\n3) Search for a data.");
	printf("\n4) Display.");
	printf("\n5) Re-dsiplay the MAIN-MENU.");
}

void sub_menu()
{
	printf(" SUB-MENU: (DISPLAY)\n---------------------");
	printf("\n\n0) Return to MAIN-MENU.");
	printf("\n1) Pre-Order traversal.");
	printf("\n2) In-Order traversal.");
	printf("\n3) Post-Order traversal.");
	printf("\n4) Re-display the SUB-MENU.");
}

void free_all(struct Node* node)
{
	if(!node)
	return;
	
	free_all(node->left);
	free_all(node->right);
	
	free(node);
}

int main()
{
	int ch,data;
	
	main_menu();
	
	printf("\n\n");
	int i;
	for(i=0;i<130;i++)
	putchar('-');
	printf("\n\nEnter choice: ");
	scanf("%d",&ch);
	printf("\n");
	for(i=0;i<130;i++)
	putchar('-');
	
	while(ch)
	{
		
		switch(ch)
		{
			case 1:		printf("\n\nEnter the data to be inserted in the tree: ");
						scanf("%d",&data);
						
						root=insert_node(root,data);
						
						break;
			
			case 2:		printf("\n\nEnter the data to be deleted from the tree: ");
						scanf("%d",&data);
						
						if(!root)
						printf("\n\nERROR: No tree found.");
						
						else
						root=delete_node(root,data);
						
						break;
						
			case 3:		printf("\n\nEnter the data to be searched for in the tree: ");
						scanf("%d",&data);
						
						if(!root)
						printf("\n\nERROR: No tree found.");
						
						else
						search_node(root,data);
						
						break;
			
			case 4:		if(!root)
						{
							printf("\n\nERROR: No tree found.");	
							printf("\n\n");
							for(i=0;i<130;i++)
							putchar('-');
							printf("\n\nMESSAGE: Returned to MAIN-NEMU.");				
							break;
						}
			
						printf("\n\n");
			
						sub_menu();
	
						printf("\n\n");
						int i;
						for(i=0;i<130;i++)
						putchar('-');
						printf("\n\nEnter choice: ");
						scanf("%d",&ch);
						printf("\n");
						for(i=0;i<130;i++)
						putchar('-');
	
						while(ch)
						{
		
							switch(ch)
							{
								case 1:		printf("\n\nMESSAGE: Displaying the tree in pre-order traversal.\n\n");
								
											if(!root)
											printf("\n\nERROR: No tree found.");
											
											else
											{
												pre_order(root);
												printf("\n\nMESSAGE: Successfully displayed the tree in pre-order traveersal.");
											}
											
											free_all_stack();
											
											break;
				
								case 2:		printf("\n\nMESSAGE: Displaying the tree in in-order traversal.\n\n");
								
											if(!root)
											printf("\n\nERROR: No tree found.");
											
											else
											{
												in_order(root);
												printf("\n\nMESSAGE: Successfully displayed the tree in in-order traveersal.");
											}
											
											free_all_stack();
											
											break;
						
								case 3:		printf("\n\nMESSAGE: Displaying the tree in post-order traversal.\n\n");
								
											if(!root)
											printf("\n\nERROR: No tree found.");
											
											else
											{
												post_order(root);
												printf("\n\nMESSAGE: Successfully displayed the tree in post-order traveersal.");
											}
											
											free_all_stack();
											
											break;
				
								case 4:		printf("\n\nMESSAGE: Re-displaying the SUB-MENU.\n\n\n");
											sub_menu();
											break;
						
								default:	printf("\n\nERROR: Wrong choice.");
											break;
						
							};
		
							printf("\n\n");
							for(i=0;i<130;i++)
							putchar('-');
							printf("\n\nEnter choice: ");
							scanf("%d",&ch);
							printf("\n");
							for(i=0;i<130;i++)
							putchar('-');
						}
	
						printf("\n\nMESSAGE: Returned to MAIN-NEMU.");
						break;
						
			case 5:		printf("\n\nMESSAGE: Re-displaying the MAIN-MENU.\n\n\n");
						main_menu();
						break;
						
			default:	printf("\n\nERROR: Wrong choice.");
						break;
						
		};
		
		printf("\n\n");
		for(i=0;i<130;i++)
		putchar('-');
		printf("\n\nEnter choice: ");
		scanf("%d",&ch);
		printf("\n");
		for(i=0;i<130;i++)
		putchar('-');
		
	}
	
	printf("\n\nMESSAGE: Program Exited.");
	
	printf("\n\n");
	for(i=0;i<130;i++)
	putchar('-');
	
	printf("\n\n");
	
	free_all(root);
}
