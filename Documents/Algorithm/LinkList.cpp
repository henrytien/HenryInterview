
#include <iostream>
#include<vector>
using namespace std;
struct Node {
    char val;
    Node* next;
};

Node *creat_list_by_head(vector<char> &str){
    Node *head = new Node;
    for(int i = 0; i < str.size(); i++){
        Node *s = new Node;
        s->val = str[i];
        s->next = head->next;
        head->next = s;
    }
    return head;
}

Node *creat_list_by_tail(vector<char> &str){
    Node *tail,*head = new Node;
    tail = head;
    for(int i = 0; i < str.size(); i++){
        Node *s = new Node;
        s->val = str[i];
        tail->next = s;
        tail = s;
    }
    return head;
}

void print(Node *n){
    while(n){
        cout << n->val << endl;
        n = n->next;
    }
}

int main()
{
    vector<char> s = {'a','b','c'};
    print(creat_list_by_head(s));
    print(creat_list_by_tail(s));
    return 0;
}
