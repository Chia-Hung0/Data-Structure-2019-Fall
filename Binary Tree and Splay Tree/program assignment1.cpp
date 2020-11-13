#include "program assignment1.h"
#include<iostream>
#include<fstream>
#include<math.h>
#include<vector>
#include<stack>
#include<bits/stdc++.h>
using namespace std;
int depth=0,order=0;
void print_prep(binarytree *T,Node *x,ofstream & fout){
    fout<<x->key_value;
    if(x->left!=NULL){
            fout<<"(";
            print_prep(T,x->left,fout);
    }
    if(x->left==NULL&&x->right!=NULL){
            fout<<"(";
            fout<<"-";
    }
    if(x->right!=NULL){
            fout<<" ";
            print_prep(T,x->right,fout);
            fout<<")";
    }
    if(x->right==NULL&&x->left!=NULL){
            fout<<"-";
            fout<<")";
    }
}
void print_boundary(Node* x, int level, int *max_level,ofstream& fout){
    if (x == NULL)
        return;
    if (*max_level < level) {
        fout<<x->key_value<<" ";
        *max_level = level;
    }
    print_boundary(x->left, level + 1,max_level,fout);
    print_boundary(x->right, level + 1,max_level,fout);
}

void store_tree(Node *x,int *depth,int *order,int *depth_store,int *order_store){
    if(x->left!=NULL){
        *depth=*depth+1;
        store_tree(x->left,depth,order,depth_store,order_store);
        depth_store[*order]=*depth;
        order_store[*order]=x->key_value;
        *order=*order+1;
    }
    if (x->left==NULL){
        depth_store[*order]=*depth;
        order_store[*order]=x->key_value;
        *order=*order+1;
    }
    if(x->right!=NULL){
        *depth=*depth+1;
        store_tree(x->right,depth,order,depth_store,order_store);
    }
    *depth=*depth-1;


}
int main(){
    ifstream fin("input.txt");
    vector<vector<int> > data;
    string sequences;
    int counting=0,digit=0;
    stack<int> Bit;

    while(getline(fin,sequences)){
        data.push_back(vector<int>());
        int num;
        for(int i=0;i<=sequences.size();i++){
            num=sequences[i];
            if(num>0&&num!=13){
                Bit.push(num-48);
                digit++;
            }
            else{
                double number,d=0;

                for (int j=0;j<digit;j++){
                    number=Bit.top();
                    Bit.pop();
                    d=d+number*pow(10,j);

                }


                if (digit!=0){
                    data[counting].push_back(d);

                }
                digit=0;
            }
        }
        counting++;

    }
    ofstream fout;
    fout.open("BTree_PRep.txt");
    for(int i=0;i<data.size();i++){
        binarytree* Btree = new binarytree();
        for (int j=0; j<data[i].size(); j++){
            Node *node = new Node();
            node->key_value=data[i][j];
            Btree->Insert(Btree,node);
        }
        int maxlevel=0;
        print_prep(Btree,Btree->root,fout);

        delete Btree;
        fout<<"\n";

    }
    fout.close();


    fout.open("STree_PRep.txt");
    for(int i=0;i<data.size();i++){
        binarytree* Stree = new binarytree();
        for (int j=0; j<data[i].size(); j++){
            Node *node = new Node();
            node->key_value=data[i][j];
            Stree->splayInsert(Stree,node);
        }
        int maxlevel=0;
        print_prep(Stree,Stree->root,fout);
        delete Stree;
        fout<<"\n";
    }
    fout.close();
    fout.open("BTree_boundary.txt");
    for(int i=0;i<data.size();i++){
        binarytree* Btree = new binarytree();
        for (int j=0; j<data[i].size(); j++){
            Node *node = new Node();
            node->key_value=data[i][j];
            Btree->Insert(Btree,node);
        }
        int maxlevel=0;
        print_boundary(Btree->root,1,&maxlevel,fout);
        delete Btree;
        fout<<"\n";
    }
    fout.close();

    fout.open("STree_boundary.txt");
    for(int i=0;i<data.size();i++){
        binarytree* Stree = new binarytree();
        for (int j=0; j<data[i].size(); j++){
            Node *node = new Node();
            node->key_value=data[i][j];
            Stree->splayInsert(Stree,node);
        }
        int maxlevel=0;
        print_boundary(Stree->root,1,&maxlevel,fout);
        delete Stree;
        fout<<"\n";
    }
    fout.close();
    fout.open("BTree.txt");
    for(int i=0;i<data.size();i++){
        binarytree* Btree = new binarytree();
        for (int j=0; j<data[i].size(); j++){
            Node *node = new Node();
            node->key_value=data[i][j];
            Btree->Insert(Btree,node);
        }
        depth=0;
        order=0;
        int b=data[i].size();
        int depth_store[b];
        int order_store[b];
        store_tree(Btree->root,&depth,&order,depth_store,order_store);
        int a;
        a=*max_element(depth_store,depth_store+b)+1;
        int matrix[a][b];
        for(int l=0;l<a;l++){
            for(int k=0;k<b;k++){
                matrix[l][k]=-1;
            }
        }
        for(int k=0;k<b;k++){
            matrix[depth_store[k]][k]=order_store[k];
        }
        for(int k=0;k<a;k++){
            for(int m=0;m<b;m++){
                if(matrix[k][m]==-1){
                    fout<<"   ";
                }
                else if(matrix[k][m]>99&&matrix[k][m]<1000){
                    fout<<matrix[k][m];
                }
                else if(matrix[k][m]>9&&matrix[k][m]<100){
                    fout<<matrix[k][m]<<" ";
                }
                else{
                    fout<<matrix[k][m]<<"  ";
                }
            }
            fout<<"\n";
        }
        delete Btree;
    }
    fout.close();
    fout.open("STree.txt");
    for(int i=0;i<data.size();i++){
        binarytree* Stree = new binarytree();
        for (int j=0; j<data[i].size(); j++){
            Node *node = new Node();
            node->key_value=data[i][j];
            Stree->splayInsert(Stree,node);
        }
        int b=data[i].size();
        int depth_store[b];
        int order_store[b];
        depth=0;
        order=0;
        store_tree(Stree->root,&depth,&order,depth_store,order_store);
        int a;
        a=*max_element(depth_store,depth_store+b)+1;
        int matrix[a][b];
        for(int l=0;l<a;l++){
            for(int k=0;k<b;k++){
                matrix[l][k]=-1;
            }
        }
        for(int k=0;k<b;k++){
            matrix[depth_store[k]][k]=order_store[k];
        }
        for(int k=0;k<a;k++){
            for(int m=0;m<b;m++){
                if(matrix[k][m]==-1){
                    fout<<"   ";
                }
                else if(matrix[k][m]>99&&matrix[k][m]<1000){
                    fout<<matrix[k][m];
                }
                else if(matrix[k][m]>9&&matrix[k][m]<100){
                    fout<<matrix[k][m]<<" ";
                }
                else{
                    fout<<matrix[k][m]<<"  ";
                }
            }
            fout<<"\n";
        }
        delete Stree;
    }
    fout.close();


}










