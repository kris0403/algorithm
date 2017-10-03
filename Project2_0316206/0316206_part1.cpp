//
//  main.cpp
//  演算法project2
//
//  Created by User on 2016/6/17.
//  Copyright © 2016年 User. All rights reserved.
//
#include <queue>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
#define MAX 10000
#define MAX_NODE 256
using namespace std;
class node{
public:
    int order,wight;
    node* left, *right, *parent;
    char c;
    bool is_char;
    
    
    node(int num){
        left = right = parent = NULL;
        this->order = num;
        this->wight = 0;
        is_char = false;
    }
    
    node(int num,char ch){//insert a node with character
        left = right = parent = NULL;
        this->order = num;
        this->wight = 0;
        is_char = true;
        this->c = ch;
    }
    
    void increase(){
        this->wight++;
    }
    
    void change_order(int num){
        this->order = num;
    }
};

class DHT{//dynamic huffman tree
public:
    int size;
    node * root, *NYT;
    node * chk_box[MAX_NODE];
    bool in_the_box[MAX_NODE];
   
   void output(node* n,FILE * of)
    {
        stack<bool>S;
        node* now = n;
        while(now!=root)
        {
            if(now->parent->left == now)S.push(false);
            else S.push(true);
            now = now->parent;
        }
        
        while(!S.empty())
        {
            bool f = S.top();
            if(f)fprintf(of,"1");
            else fprintf(of,"0");
            S.pop();
        }
    }
    
    
    void reorder()
    {
        //use BFS
        int size = 100;
        queue<node*>Q;
        Q.push(root);
        while(!Q.empty())
        {
           
            node* r = Q.front();
             Q.pop();
            chk_box[100-size] = r;
            r->order=size;
            size--;
            
            if(r->right)
            {
                Q.push(r->right);
            }
            if(r->left)
            {
                Q.push(r->left);
            }
            
        }
        
    }
    
    
    
    void swap(node*a,node*b)
    {
        node* o_parent = a->parent;
        bool is_left = false;
        if(a->parent->left == a)
        {
            is_left = true;
        }
        if(b->parent->left == b)
        {
            b->parent->left = a;
            a->parent = b->parent;
        }
        else{
            b->parent->right = a;
            a->parent = b->parent;
        }
        
        
        if(is_left)
        {
            b->parent = o_parent;
            o_parent->left = b;
        }
        
        else{
            b->parent = o_parent;
            o_parent->right = b;
        }
        
        reorder();
    }
    
    
    bool  is_parent(node*a,node*b)//check whether b is a's paent or not
    {
        node* now = a->parent;
        while(now!= root)
        {
            if(b == now)return true;
            now = now->parent;
        }
        return false;
    }
    
    DHT(){
        root = new node(100);//initial order of the node is set to 100
        NYT = root;
        size = 1;
        for(int i = 0;i < MAX_NODE;i++)
        {
            chk_box[i]=NULL;
            in_the_box[i] = false;
        }
        chk_box[0] = root;
        size = 1;
    }
    
    void insert(node* n,char c){//insert two node with charactor
        node* r_point,*l_point;
        
        
        r_point = new node(100 - size,c);
        chk_box[size] = r_point;
        in_the_box[c] = true;
        size++;
        //update(n);
        
        
       // l_point = new node(100 - size,c);
        l_point = new node(100 - size);
        chk_box[size] = l_point;
        size++;
        
        n->right = r_point;
        n->left = l_point;
        r_point->parent =  n;
        l_point->parent = n;
        
        NYT =l_point;
        
        update(r_point);
        
    }
    
   
    
    void update(node* n){//increase weight of node n  and adjust all node in whole tree
        node * now=n;
        while(now!=root){
            int w= now->wight;
            for(int i=1;i<size;i++)
            {
                if(chk_box[i] == now || chk_box[i]->order <= now->order)break;
                
                if(chk_box[i]->wight <= w && !is_parent(now,chk_box[i]))
                {
                    swap(now,chk_box[i]);//change the node
                }
            }
        
            now->increase();
            now = now->parent;
        }
        
    }
};





int main() 
{
    char c;
    char input[100],output[100];
    char buf[MAX];
    FILE* in_file, *out_file;
    cin >> c >> input >> output;
    DHT *dht = new DHT();
    in_file = fopen(input,"r");
    out_file = fopen(output,"w");
    fscanf(in_file, "%s" ,buf);
    int len = strlen(buf);
    if(c == 'E')
    {
        
        for(int i=0;i < len;i++)// read & encoding
        {
            char in_char = buf[i];//input character
            if(dht->in_the_box[in_char])
            {//in the box
                for(int j=0;j<dht->size;j++)
                {
                    if(dht->chk_box[j]->is_char && dht->chk_box[j]->c == in_char)
                    {
                        dht->output(dht->chk_box[j],out_file);
                        dht->update(dht->chk_box[j]);
                        break;
                    }
                }
            }
            else
            {//not in the tree
                dht->output(dht->NYT,out_file);
                fprintf(out_file,"%c",in_char);
                dht->insert(dht->NYT,in_char);
            }
        }
    }
    else if(c == 'D')
    {
        for(int i=0;i < len;i++)
        {
            char in_char = buf[i];//input character
            bool check=false;
            if((in_char-'a'>=0&&in_char-'a'<26)||(in_char-'A'>=0 && in_char-'A'<26))check=true;  
            if(check)//letter
            {
                fprintf(out_file,"%c",in_char);
                if(dht->in_the_box[in_char])
                {//in the box
                    for(int j=0;j<dht->size;j++)
                    {
                        if(dht->chk_box[j]->is_char && dht->chk_box[j]->c == in_char)
                        {
                           // dht->output(dht->chk_box[j],out_file);
                            dht->update(dht->chk_box[j]);
                            break;
                        }
                    }
                }
                else
                {//not in the tree
                    dht->insert(dht->NYT,in_char);
                }
            }
            else//number
            {
                node* n_node=dht->root;
                if(in_char == '1') n_node = n_node->right;
                else n_node = n_node->left;
                while(n_node->left != NULL || n_node->right != NULL)
                {
                    in_char = buf[++i];
                    if(in_char == '1')n_node = n_node->right;
                    else n_node = n_node->left;
                }
                if(n_node != dht->NYT)
                {
                    fprintf(out_file,"%c",n_node->c);
                    for(int j=0;j < dht->size;j++)
                    {
                        if(dht->chk_box[j]->is_char && dht->chk_box[j]->c==n_node->c)
                        {
                            dht->update(dht->chk_box[j]);
                            break;
                        }
                    }
                }
            }
        }
        
    }
  //  in_file.close();
    
   // system("pasuse");
}
