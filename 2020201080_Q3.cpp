#include<bits/stdc++.h>
using namespace std;

template <class T1, class T2>

class orderedMap{

    class TreeNode 
    {   
        public:
        T1 data; T2 value; int height;
        struct TreeNode *left, *right; 
    };

    TreeNode *root = NULL; int count = 0;

    public: 

        /****************************** CREATE NEW NODE **********************************************/

        TreeNode* createTreeNode(T1 key, T2 val) 
        { 
            TreeNode* newNode =  new TreeNode; 
            newNode->data = key; newNode->value = val;
            newNode->left = newNode->right = NULL; 
            newNode->height = 0;
            count++;
            return newNode; 
        }

        /****************************** FUNCTION TO CALCULATE HEIGHT OF NODE **************************/

        int height(TreeNode *node){
            if(!node) return -1;
            return node->height;
        }

        /****************************** ROTATE RIGHT FUNCTION  ****************************************/

        TreeNode* rotateRight(TreeNode* root){
            //cout<<endl<<"=======INSIDE ROTATE RIGHT======="<<endl;
            TreeNode *pivot = root->left;
            root->left = pivot->right; pivot->right = root;
            root->height = max( height(root->left), height(root->right) ) + 1;
            pivot->height = max( height(pivot->left), height(pivot->right) ) + 1;
            return pivot;
        }

        /****************************** ROTATE LEFT FUNCTION ******************************************/

        TreeNode* rotateLeft(TreeNode* root){
            //cout<<endl<<"=======INSIDE ROTATE LEFT======="<<endl;
            TreeNode *pivot = root->right;
            root->right = pivot->left; pivot->left = root;
            root->height = max( height(root->left), height(root->right) ) + 1;
            pivot->height = max( height(pivot->left), height(pivot->right) ) + 1;
            return pivot;
        }

        /****************************** INSERTION OF NODE IN AVL **************************************/

        TreeNode* insertKey(TreeNode* node, T1 key, T2 val) 
        { 
            if (!node) return createTreeNode(key, val); 

            if(key == node->data){
                node->value = val; return node;
            }

            if (key < node->data) node->left  = insertKey(node->left, key, val); 
            else if (key > node->data) node->right = insertKey(node->right, key, val);    

            int heightDifference = height(node->left) - height(node->right);

            if (heightDifference < -1){
                if(height(node->right->right) >= height(node->right->left)){
                    return rotateLeft(node);
                }
                else{
                    node->right = rotateRight(node->right); return rotateLeft(node);
                }
            }

            else if(heightDifference > 1){
                if(height(node->left->left) >= height(node->left->right)){
                    return rotateRight(node);
                }
                else{
                    node->left = rotateLeft(node->left); return rotateRight(node);
                }
            }

            node->height = max(height(node->left), height(node->right)) + 1;
            return node; 
        } 

        void insert(T1 key, T2 val){
            root = insertKey(root, key, val);
        }

        /****************************** LEVEL ORDER TRAVERSAL ****************************************/

        void levelorder_helper(TreeNode* root){
            queue<TreeNode*> q;
            q.push(root);

            if(!root){
                cout<<"MAP IS EMPTY"; return;
            }  

            while(!q.empty()){

                TreeNode* node = q.front();
                q.pop();

                cout<<node->data<<"->"<<node->value<<"  ";

                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }

        void levelOrder(){
            levelorder_helper(root);
        }

        /****************************** RETURN MIN VALUE OF AVL **************************************/

        TreeNode* minValue( TreeNode* root){
            if(!root) return root; 
            if(!root->left) return root;
            return minValue(root->left);
        }

        /****************************** DELETE NODE FROM AVL *****************************************/

        TreeNode* deleteNode(TreeNode* node, T1 key){
            if(!node) return NULL;

            if(key < node->data) node->left = deleteNode(node->left, key);

            else if(key > node->data) node->right = deleteNode(node->right, key);
            
            else{
                if(!node->left && !node->right){
                    return NULL;
                } 

                if(!node->left){
                    TreeNode* temp = node->right;
                    delete(node);
                    return temp;
                }

                if(!node->right){
                    TreeNode* temp = node->left;
                    delete(node);
                    return temp;
                }

                else{
                    TreeNode* temp = minValue(node->right); node->data = temp->data;
                    node->right = deleteNode(node->right, node->data);
                }
            }

            int heightDifference = height(node->left) - height(node->right);

            if (heightDifference < -1){
                if(height(node->right->right) >= height(node->right->left)){
                    return rotateLeft(node);
                }
                else{
                    node->right = rotateRight(node->right); return rotateLeft(node);
                }
            }

            else if(heightDifference > 1){
                if(height(node->left->left) >= height(node->left->right)){
                    return rotateRight(node);
                }
                else{
                    node->left = rotateLeft(node->left); return rotateRight(node);
                }
            }

            node->height = max(height(node->left), height(node->right)) + 1;
            return node;
        }

        void erase(T1 key){root = deleteNode(root, key); count--;}

        /****************************** SEARCH GIVEN DATA IN AVL *************************************/

        TreeNode* search(TreeNode* root, T1 key){
            if(!root) return NULL;

            if(root->data == key) return root;

            if(root->data > key) return search(root->left, key);

            return search(root->right, key);
        }

        bool find(T1 key){
            TreeNode* node = search(root, key);
            if(!node) return false;
            return true;
        }

        /************************************** SIZE OF AVL *****************************************/

        int size(){return count;}

        /********************************* DELETE ALL NODES OF AVL **********************************/

        TreeNode* clear_helper(TreeNode* root){
            if(!root) return NULL;

            root->left = clear_helper(root->left);

            root->right = clear_helper(root->right);

            if(!root->left && !root->right){
                count--; delete(root);
            }
            return NULL;
        }

        void clear(){root = clear_helper(root);}

        /********************************* [] OPERATOR OVERLOADING **********************************/

        T1* operator[](T1 key){
            TreeNode* node = search(root, key);
            if(!node){
                insert(key, 0);
                TreeNode* searchedNode = search(root, key); return &(searchedNode->value);
            }
            else return &(node->value);
        } 

};

int main() 
{ 
    orderedMap<int, int> mp;

    /*t.insertKey(1.3);
    t.insertKey(2.4);
    t.insertKey(3.5);
    t.insertKey(4.6);
    t.insertKey(5.7);
    t.insertKey(6.8);
    t.insertKey(7.9);

    cout<<"\nLevelOrder after Insertion : "; t.levelOrder();
    cout<<endl;

    t.deleteKey(5.7);
    t.deleteKey(6.8);
    t.deleteKey(2.4);*/
  
    mp.insert(50,2); 
    mp.insert(40, 1); 
    mp.insert(60, 34); 
    mp.insert(40, 132); 
    mp.insert(30, 132); 
    mp.insert(45, 16); 
    mp.insert(55, 3); 
    mp.insert(70, 14); 

    cout<<"\nLevelOrder after Insertion : "; mp.levelOrder();
    cout<<endl;

    mp.erase(40);
   /* tree.deleteKey(55);
    tree.deleteKey(60);
    tree.deleteKey(70);*/

    cout<<"\nLevelOrder after Deletion : "; mp.levelOrder();

    bool isfound = mp.find(40);
    if(isfound) cout<<endl<<endl<<"Node Found !";
    else cout<<endl<<endl<<"Node NOT Found !";

    cout<<endl<<endl<<"Size of Map : "<<mp.size();

    cout<<endl<<endl<<"mp[50] = "<<*mp[50];

    mp.clear();
    cout<<"\n\nLevelOrder after clear : "; mp.levelOrder();
    cout<<endl<<endl<<"Size of Map after clear : "<<mp.size();

    cout<<endl<<endl<<"mp[50] = "<<*mp[50];

    *mp[50] += 2;

    cout<<endl<<endl<<"after inserting 2 -> mp[50] = "<<*mp[50];

    cout<<endl<<endl;
    return 0; 
} 