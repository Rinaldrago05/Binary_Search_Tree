#include<stdio.h>
#include<stdlib.h>

int flag=0;

struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
}*root=NULL;

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

struct Node* new_node_allocate()
{
	return (struct Node*)calloc(1,sizeof(struct Node));
}

struct Node* insert_node(struct Node* node,int data)
{
	if(!node)
	{
		node=new_node_allocate();
		
		if(!node)
		printf("\n\nERROR: Dynamic allocation failed.");
		
		else
		{
			node->data=data;
			printf("\n\nMESSAGE: Given data '%d' successfully inserted in the tree.");
		}
	}
	
	else if(data<node->data)
	node->left=insert_node(node->left,data);
	
	else if(data>node->data)
	node->right=insert_node(node->right,data);
	
	else
	printf("\n\nERROR: Insertion operation failed. Given data '%d' already exists.",data);
	
	return node;
}

struct Node* in_order_successsor(struct Node* node)
{
	while(node && node->left)
	node=node->left;
	
	return node;
}

struct Node* delete_node(struct Node* node,int data)
{
	if(!node)
	return node;
	
	if(data<node->data)
	node->left=delete_node(node->left,data);
	
	else if(data>node->data)
	node->right=delete_node(node->right,data);
	
	else
	{
		if(!node->left)
		{
			struct Node* temp=node->right;
			
			free(node);
			
			flag=1;
			
			return temp;
		}
		
		else if(!node->right)
		{
			struct Node* temp=node->left;
			
			free(node);
			
			flag=1;
			
			return temp;
		}
		
		else
		{
			struct Node* temp=in_order_successsor(node->right);
			
			node->data=temp->data;
			
			node->right=delete_node(node->right,temp->data);
			
			flag=1;
		}
	}
	
	return node;
}

struct Node* search_node(struct Node* node,int data)
{
	if(!node)
	return node;
	
	if(node->data==data)
	{
		flag=1;
		return node;
	}
	
	search_node(node->left,data);
	search_node(node->right,data);
}

void pre_order(struct Node* node)
{
	if(!node)
	return;
	
	printf("%d  ",node->data);
	
	pre_order(node->left);
	pre_order(node->right);	
}

void in_order(struct Node* node)
{
	if(!node)
	return;
	
	in_order(node->left);
	
	printf("%d  ",node->data);
	
	in_order(node->right);
}

void post_order(struct Node* node)
{
	if(!node)
	return;
	
	post_order(node->left);
	post_order(node->right);
	
	printf("%d  ",node->data);
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
			
			case 2:		printf("\n\nEnter the deleted from the tree: ");
						scanf("%d",&data);
						
						if(!root)
						{
							printf("\n\nERROR: Deletion failed. No tree found.");						
							break;
						}						
						
						flag=0;
						root=delete_node(root,data);
						
						if(!flag)
						printf("\n\nERROR: Deletion failed. Given data '%d' is not present in the tree.",data);
						
						else
						printf("\n\nMESSAGE: Given data '%d' successfully deleted from the tree.",data);
						
						flag=0;
						break;
						
			case 3:		printf("\n\nEnter the data to be searched for in the tree: ");
						scanf("%d",&data);
						flag=0;
						search_node(root,data);
						
						if(!root)
						{
							printf("\n\nERROR: Deletion failed. No tree found.");						
							break;
						}
						
						if(!flag)
						printf("\n\nERROR: Searching failed. Given data '%d' not present in the tree.",data);
						
						else
						printf("\n\nMESSAGE: Given data '%d' successfully found in the tree.",data);
						
						flag=0;
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
											break;
				
								case 2:		printf("\n\nMESSAGE: Displaying the tree in in-order traversal.\n\n");
								
											if(!root)
											printf("\n\nERROR: No tree found.");
											
											else
											{
												in_order(root);
												printf("\n\nMESSAGE: Successfully displayed the tree in in-order traveersal.");
											}
											break;
						
								case 3:		printf("\n\nMESSAGE: Displaying the tree in post-order traversal.\n\n");
								
											if(!root)
											printf("\n\nERROR: No tree found.");
											
											else
											{
												post_order(root);
												printf("\n\nMESSAGE: Successfully displayed the tree in post-order traveersal.");
											}
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
