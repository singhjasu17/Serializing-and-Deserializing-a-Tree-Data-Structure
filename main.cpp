#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#include<sstream>
using namespace std;

// Declaring node for tree
typedef struct nod
{
    string str;
    struct nod* left;
    struct nod* right;
    nod(string word,struct nod *temp1,struct nod *temp2) : str(word),left(NULL),right(NULL)
        {
        }
}node;

// creates node with the given string value
node *create_node(string str)
{
    node *temp=new node(str,NULL,NULL);
    return temp;
}

// constructs tree by assiging position to string.
//It makes a BST with the condition thet strings having size small as compared to their parent are on left side whereas the ones that are larger, are on right side;
node *make_tree(node *root,string str)
{
   if(root==NULL)
   {
       node *temp=new node(str,NULL,NULL);
       return temp;
   }
   if(str.length() < (root->str).length())
   {
       root->left=make_tree(root->left,str);
   }
   else
   {
       root->right=make_tree(root->right,str);
   }
   return root;
}

// inserts a root in the binary tree;
void *insert(node **root,string str)
{
    *root=make_tree(*root,str);
}

 // reading data from the file and storing that in the vector
void read(vector<string> &text,char * filename)
{
    fstream fileopen;
    fileopen.open(filename,ios::in);
    string sentence,word,temp;
    while(fileopen >> sentence)
    {

         stringstream str(sentence);

         while(getline(str,temp,','))
         {
             text.push_back(temp);
         }
    }

}
// Displayinng the tree;
void printTree(node *root)
{
  if(root==NULL)
    return;
  cout<<root->str<<" ";
  printTree(root->left);
  printTree(root->right);
}
// writing contents to binary file
void writeToFile(vector <string> rect,char *filename)
{
    ofstream fout;
    fout.open(filename,ios::out | ios::binary);
    for(int i=0;i<rect.size();i++)
    {

        fout.write((char *)rect[i].c_str(),sizeof(rect[i]));
    }
    fout.close();
}
// display contents of binary file
void display(char *filename)
{

ifstream fileopen;
    fileopen.open(filename, ios::binary | ios::in);
    string save;
     while(fileopen.read((char*)save.c_str(), sizeof(save)))
    {
        cout<<save;
    }

}

// main function
int main(int argc,char *argv[])
{
     vector <string> rum;
     char operation[strlen(argv[1])];
     strcpy(operation,argv[1]);
     char create[]={'c','r','e','a','t', 'e','\0'};
     char load[]={'l','o','a', 'd','\0'};
     if(strcmp(operation,create)==0)
     {
     char filename[strlen(argv[2])];
     char arr[strlen(filename) + 1];
     strcpy(arr,filename);
     read(rum,arr);
     node *root=NULL;
     for(int i=0;i<rum.size();i++)
     {
         insert(&root,rum[i]);
     }
     writeToFile(rum,argv[3]);
     }
     else if(strcmp(load,argv[1])==0)
     {
     display(argv[2]);

     }

}
