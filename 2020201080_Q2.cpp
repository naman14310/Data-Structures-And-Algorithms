#include<bits/stdc++.h>
#define SIZE 100000
#define prime 19
using namespace std;

template <class T1, class T2>

class unorderedMap{

    struct node{
        T1 key; T2 val;
        node *next;
    };

    node *arr[SIZE]; int factor;

    public:

    long long int hashKey(T1 KEY){
        ostringstream ss; ss << KEY; string key = ss.str();
        factor = 1; long long int sum = 0;
        for(int i=0; i<key.length(); i++){
            sum += (key[i] * factor);
            sum = sum % SIZE;
            factor *= prime;
        }
        //cout<<"sum : "<<sum<<endl;
        return sum;
    }

    int hash(T1 key){
        long long int hashkey = hashKey(key);
        //cout<<"hashkey : "<<hashkey<<endl;
        return (hashkey % SIZE);
    }

    node* createNode(T1 key, T2 val){
        node* newNode = new node;
        newNode->key = key; newNode->val = val; newNode->next = NULL; 
        return newNode;
    }

    void insert(T1 key, T2 val){
        int index = hash(key);
        //cout<<"index : "<<index<<endl;
        node* head = arr[index];

        if(!head){
            node *newNode = createNode(key, val);
            arr[index] = newNode;
            return;
        }

        else if(!head->next){
            if(head->key == key)return;
            else{
                node *newNode = createNode(key, val);
                head->next = newNode;return;
            }
        }

        else{
            node* itr = head;
            while(itr->next){            
                if(itr->key == key)return;
                else itr = itr->next;
            }
            node *newNode = createNode(key, val);
            itr->next = newNode;return;
        }
    }

    void erase(T1 key){
        int index = hash(key);

        node* head = arr[index];

        if(!head) return;
    
        else if(!head->next){
            if(head->key == key){
                delete(head);
                arr[index] = NULL;return;
            } else return;
        }

        else{
            node* prev = head;
            node* itr = prev->next;
            if(prev->key == key){
                arr[index] = itr;
                delete(prev);return;
            }
            while(itr){
                if(itr->key == key){
                    prev->next = itr->next;
                    delete(itr);return;
                }
            }
        }
    }

    pair<bool,T2> find_helper(T1 key){
        int index = hash(key);

        node* itr = arr[index];
        while(itr){
            if(itr->key == key){
                return {true,itr->val};
            }
        }
        return {false,0};
    }

    bool find(T1 key){
        pair<bool, T2> p = find_helper(key);
        return p.first;
    }

    T1 operator[](T1 key){

        pair<bool, T2> found = find_helper(key);
        if(!found.first){
            insert(key, 0);return 0;
        }
        else return found.second;
                  
    } 

};

int main(){

    unorderedMap<float, float> ump;

    ump.insert(34.123, 32424424.12);
    cout<<endl<<ump[34.123]<<endl<<endl;
    ump.erase(34.123);
    cout<<endl<<ump[34.123]<<endl<<endl;
    return 0;
}