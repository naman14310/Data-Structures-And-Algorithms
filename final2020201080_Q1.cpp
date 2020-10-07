#include<bits/stdc++.h>
using namespace std;

template <class T>

class avl{

        /****************************** STRUCTURE OF AVL TREENODE *************************************/

    struct TreeNode 
    { 
        T data; 
        int height;
        int count;
        int lc; int rc;
        struct TreeNode *left, *right; 
    };

    struct TreeNode *root = NULL; TreeNode *rql = NULL, *rqr = NULL; int rans = 0;
    T nextgreater = {}; T nextsmaller = {};  

    public:

        /****************************** RETURN MIN VALUE OF AVL **************************************/

        TreeNode* minValue( TreeNode* root){
            if(!root) return root; 
            if(!root->left) return root;
            return minValue(root->left);
        }

        /****************************** RETURN MAX VALUE OF AVL **************************************/

        TreeNode* maxValue( TreeNode* root){
            if(!root) return root; 
            if(!root->right) return root;
            return maxValue(root->right);
        }

        /************************************* INIT **************************************************/

        void init(){
            rql = NULL; rqr = NULL; rans = 0;
            nextgreater = {};
            nextsmaller = {};
        } 

        /****************************** CREATE NEW NODE **********************************************/

        TreeNode* createTreeNode(T key) 
        { 
            TreeNode* newNode =  new TreeNode; 
            newNode->data = key; 
            newNode->left = newNode->right = NULL; 
            newNode->height = 0; newNode->lc = 0; newNode->rc = 0;
            newNode->count = 1;
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
            root->left = pivot->right; root->lc = pivot->rc;
            pivot->right = root; pivot->rc = root->lc + root->rc + root->count;
            root->height = max( height(root->left), height(root->right) ) + 1;
            pivot->height = max( height(pivot->left), height(pivot->right) ) + 1;
            return pivot;
        }

        /****************************** ROTATE LEFT FUNCTION ******************************************/

        TreeNode* rotateLeft(TreeNode* root){
            //cout<<endl<<"=======INSIDE ROTATE LEFT======="<<endl;
            TreeNode *pivot = root->right; 
            root->right = pivot->left; root->rc = pivot->lc;
            pivot->left = root; pivot->lc = root->lc + root->rc + root->count;
            root->height = max( height(root->left), height(root->right) ) + 1;
            pivot->height = max( height(pivot->left), height(pivot->right) ) + 1;
            return pivot;
        }

        /****************************** INSERTION OF NODE IN AVL **************************************/

        TreeNode* insert(TreeNode* node, T key) 
        { 
            if (node == NULL) return createTreeNode(key); 
            
            if(key == node->data){
                node->count = node->count + 1;
                return node;
            }

            if (key < node->data) 
                {node->lc++; node->left  = insert(node->left, key);}
            else if (key > node->data) 
                {node->rc++; node->right = insert(node->right, key);}    

            int heightDifference = height(node->left) - height(node->right);

            if (heightDifference < -1){
                if(height(node->right->right) >= height(node->right->left)){
                    return rotateLeft(node);
                }
                else{
                    node->right = rotateRight(node->right);
                    return rotateLeft(node);
                }
            }

            else if(heightDifference > 1){
                if(height(node->left->left) >= height(node->left->right)){
                    return rotateRight(node);
                }
                else{
                    node->left = rotateLeft(node->left);
                    return rotateRight(node);
                }
            }

            node->height = max(height(node->left), height(node->right)) + 1;
            return node; 
        } 

        void insertKey(T key){
            root = insert(root, key);
        }

        /****************************** LEVEL ORDER TRAVERSAL ****************************************/

        void levelorder_helper(TreeNode* root){
            queue<TreeNode*> q;
            q.push(root); 

            while(!q.empty()){

                TreeNode* node = q.front();
                q.pop();

                cout<<node->data<<"|"<<node->count<<"|"<<node->lc<<"|"<<node->rc<<"  ";

                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }

        void levelOrder(){
            levelorder_helper(root);
        }

        /****************************** PRE ORDER TRAVERSAL ****************************************/

        void preorder_helper(TreeNode* root){
            if(root){
            cout<<root->data<<"|"<<root->count<<"|"<<root->lc<<"|"<<root->rc<<"  ";
            preorder_helper(root->left);
            preorder_helper(root->right);
            }
        }

        void preorder(){
            preorder_helper(root);
        }

        /****************************** SEARCH GIVEN DATA IN AVL *************************************/

        TreeNode* search(TreeNode* root, T key){
            if(!root) return NULL;

            if(root->data == key) return root;

            if(root->data > key) return search(root->left, key);

            return search(root->right, key);
        }

        bool searchKey(T key){
            TreeNode* node = search(root, key);
            if(!node) return false;
            return true;
        }

        /****************************** DELETE NODE FROM AVL *****************************************/

        TreeNode* recurrDelete(TreeNode* node, T key){
            if(!node) return NULL;

            if(key < node->data){
                node->lc--;
                node->left = recurrDelete(node->left, key);
            }

            else if(key > node->data){
                node->rc--;
                node->right = recurrDelete(node->right, key);
            }

            else{

                /*if(node->count > 1){
                    node->count = node->count - 1 ;
                    return node;
                }*/

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
                    TreeNode* temp = minValue(node->right);
                    node->data = temp->data;
                    node->count = temp->count;
                    node->right = recurrDelete(node->right, node->data);
                }
            }

            int heightDifference = height(node->left) - height(node->right);

            if (heightDifference < -1){
                if(height(node->right->right) >= height(node->right->left)){
                    return rotateLeft(node);
                }
                else{
                    node->right = rotateRight(node->right);
                    return rotateLeft(node);
                }
            }

            else if(heightDifference > 1){
                if(height(node->left->left) >= height(node->left->right)){
                    return rotateRight(node);
                }
                else{
                    node->left = rotateLeft(node->left);
                    return rotateRight(node);
                }
            }

            node->height = max(height(node->left), height(node->right)) + 1;
            
            return node;
        }

        TreeNode* deleteNode(TreeNode* node, T key){
            if(!node) return NULL;

            if(key < node->data){
                node->lc--;
                node->left = deleteNode(node->left, key);
            }

            else if(key > node->data){
                node->rc--;
                node->right = deleteNode(node->right, key);
            }

            else{

                if(node->count > 1){
                    node->count = node->count - 1 ;
                    return node;
                }

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
                    TreeNode* temp = minValue(node->right);
                    node->data = temp->data;
                    node->count = temp->count;
                    node->rc -= temp->count ;  
                    node->right = recurrDelete(node->right, node->data);
                }
            }

            int heightDifference = height(node->left) - height(node->right);

            if (heightDifference < -1){
                if(height(node->right->right) >= height(node->right->left)){
                    return rotateLeft(node);
                }
                else{
                    node->right = rotateRight(node->right);
                    return rotateLeft(node);
                }
            }

            else if(heightDifference > 1){
                if(height(node->left->left) >= height(node->left->right)){
                    return rotateRight(node);
                }
                else{
                    node->left = rotateLeft(node->left);
                    return rotateRight(node);
                }
            }

            node->height = max(height(node->left), height(node->right)) + 1;
            
            return node;
        }

        void deleteKey(T key){
            TreeNode* nodeToBeDelete = search(root, key);
            if(!nodeToBeDelete){
                cout<<endl<<endl<<"Key "<<key<<" doesn't exist"<<endl<<endl;
                return;
            }
            else root = deleteNode(root, key);
        }

        /****************************** COUNT OCCURRANCES OF ELEMENT ********************************/

        int countOccurrance_helper(TreeNode* root, T key){
            if(!root) return 0;
        // cout<<endl<<"count out : "<<count<<endl;
            if(root->data == key){
                return root->count;
            //    cout<<endl<<"count in : "<<count<<endl;
            }

            if(root->data >= key) return countOccurrance_helper(root->left, key);

            return countOccurrance_helper(root->right, key);
        }

        int countOccurrance(T key){
            return countOccurrance_helper(root, key);
        }



        /****************************** NEXT GREATER IN AVL *****************************************/
    
        void nextGreater(TreeNode* root, T key){
            if(!root) return;

            if(key < root->data){
                nextgreater = root->data;
                rqr = root;
                nextGreater(root->left, key);
            }
            else nextGreater(root->right, key);
        }

        /****************************** NEXT SMALLER IN AVL *****************************************/

        void nextSmaller(TreeNode* root, T key){
            if(!root) return;

            if(key >= root->data){
                nextsmaller = root->data;
                rql = root;
                //cout<<"nextS : "<<nextsmaller<<endl;
                nextSmaller(root->right, key);
            }
            else nextSmaller(root->left, key);
        }

        /****************************** LOWER BOUND OF GIVEN DATA IN AVL *****************************/

        T lowerBound(TreeNode* root, T key){
            TreeNode *node = search(root, key);
            if(node){rqr=node; return key;}

            nextGreater(root, key);
            return nextgreater;
        }

        T lowerbound(T key){
            init();
            return lowerBound(root, key);
        }

        /****************************** UPPER BOUND OF GIVEN DATA IN AVL *****************************/

        T upperBound(TreeNode* root, T key){
            nextGreater(root, key);
            return nextgreater;
        }

        T upperbound(T key){
            init();
            return upperBound(root, key);
        }

        /**************************** CLOSEST ELEMENT OF GIVEN DATA IN AVL ***************************/

        T closest(T key){
            init();
            if(key<=minValue(root)->data) return minValue(root)->data;
            else if (key >= maxValue(root)->data){return maxValue(root)->data;}

            T n1 = lowerbound(key);
            nextSmaller(root, key);
            T n2 = nextsmaller;

            //cout << " n1 : "<<n1;
            //cout<<" n2 : "<<n2;
            if(key-n2 > n1-key)
            return n1;
            else return n2;
        }

        /************************* Kth LARGEST ELEMENT IN LOG-N TIME IN AVL *************************/

        T klargest_helper(TreeNode* root, int k){
            if(root->rc >= k){
                return klargest_helper(root->right, k);
            }
            else if(root->rc + root->count >= k){
                return root->data;
            }

            return klargest_helper(root->left, k - root->rc - root->count);            
        }

        T klargest(int k){
            return klargest_helper(root, k);
        }

        /***************************** LONGEST COMMON ANCESTOR IN AVL *******************************/

        TreeNode* lca_helper(TreeNode* root, T min, T max){

            if(!root) return NULL;;
            
            if(root->data>=min && root->data<=max)
                return root;

            else if(root->data<min){
                return lca_helper(root->right, min, max);
            }

            else if(root->data>max){
                return lca_helper(root->left, min, max);
            }

            return NULL;

        }

        void traverseLeft(TreeNode* root, T a){
            
            if(!root) return;

            if(root->data > a){
                rans += root->count + root->rc;
                traverseLeft(root->left, a);
            } 

            else return;
        }

         void traverseRight(TreeNode* root, T b){
            
            if(!root) return;

            if(root->data < b){
                rans += root->count + root->lc;
                traverseRight(root->right, b);
            } 

            else return;
        }

        int rangeQuery(T data1, T data2){
            init();
            lowerbound(data1);
            nextSmaller(root, data2);
            TreeNode* a = rqr;
            TreeNode* b = rql;  

            TreeNode* lca = lca_helper(root, a->data, b->data);
             //cout<<"lca : "<<lca->data<<endl<<endl;
            if(lca==a){
                //cout<<"hello";
                rans += lca->count + b->count + b->lc; 
                traverseRight(lca->right, b->data);
                //cout<<rans;
                return rans;
            }

            else if(lca==b){
                rans += lca->count + a->count + a->rc;
                traverseLeft(lca->left, a->data);
                return rans;                 
            }
           
            rans += a->count + a->rc + b->count + b->lc + lca->count;
            //cout<<"\n\nrq ans : "<<rans<<endl<<endl;
            traverseLeft(lca->left, a->data);
            traverseRight(lca->right, b->data);
            //cout<<"\n\nrq ans : "<<rans<<endl<<endl;
            return rans;

        }


};

/****************************** MAIN FUNCTION ***********************************************/

int main() 
{ 
    /*avl<int> a;
    a.insertKey(30);
    a.insertKey(10);
    a.insertKey(25);
    a.insertKey(20);
    a.insertKey(40);
    a.insertKey(50);
    a.insertKey(25);
    a.insertKey(35);
    a.insertKey(50);
    a.insertKey(25);

    cout<<endl<<"preorder"<<endl;
    a.preorder();
    cout<<endl;
    cout<<a.searchKey(12);
    cout<<endl;
    cout<<a.searchKey(50)<<endl;
    cout<<"the occurance of 50 is : - "<<a.countOccurrance(50)<<endl;
    cout<<"the occurance of 30 is : - "<<a.countOccurrance(30)<<endl;
    cout<<"the occurance of 12 is : - "<<a.countOccurrance(12)<<endl;
    cout<<".........................."<<endl;
    cout<<"lower bound of 7 is = "<<a.lowerbound(7)<<endl;
    cout<<"lower bound of 40 is = "<<a.lowerbound(40)<<endl;
    cout<<"lower bound of 22 is = "<<a.lowerbound(22)<<endl;
    cout<<".........................."<<endl;
    cout<<"upper bound of 7 is = "<<a.upperbound(7)<<endl;
    cout<<"upper bound of 40 is = "<<a.upperbound(40)<<endl;
    cout<<"upper bound of 31 is = "<<a.upperbound(31)<<endl;
    cout<<".........................."<<endl;
    cout<<"closest value to 7 is = "<<a.closest(7)<<endl;
    cout<<"closest value to 22 is = "<<a.closest(22)<<endl;
    cout<<"closest value to 7 is = "<<a.closest(7)<<endl;
    cout<<"closest value to 60 is = "<<a.closest(60)<<endl;
    cout<<".........................."<<endl;
    cout<<"1 largest value is = "<<a.klargest(1)<<endl;
    cout<<"2 largest value is = "<<a.klargest(2)<<endl;
    cout<<"3 largest value is = "<<a.klargest(3)<<endl;
    cout<<"4 largest value is = "<<a.klargest(4)<<endl;
    cout<<"5 largest value is = "<<a.klargest(5)<<endl;
    cout<<"6 largest value is = "<<a.klargest(6)<<endl;
    cout<<"7 largest value is = "<<a.klargest(7)<<endl;
    cout<<"8 largest value is = "<<a.klargest(8)<<endl;
    cout<<"9 largest value is = "<<a.klargest(9)<<endl;
    cout<<"10 largest value is = "<<a.klargest(10)<<endl;
    a.deleteKey(25);
    a.deleteKey(10);
    a.deleteKey(40);

    cout<<endl<<"preorder"<<endl;
    a.preorder();
    cout<<endl;
    cout<<a.searchKey(12);
    cout<<endl;
    cout<<a.searchKey(50)<<endl;
    cout<<"the occurance of 50 is : - "<<a.countOccurrance(50)<<endl;
    cout<<"the occurance of 30 is : - "<<a.countOccurrance(30)<<endl;
    cout<<"the occurance of 12 is : - "<<a.countOccurrance(12)<<endl;
    cout<<".........................."<<endl;
    cout<<"lower bound of 7 is = "<<a.lowerbound(7)<<endl;
    cout<<"lower bound of 40 is = "<<a.lowerbound(40)<<endl;
    cout<<"lower bound of 22 is = "<<a.lowerbound(22)<<endl;
    cout<<".........................."<<endl;
    cout<<"upper bound of 7 is = "<<a.upperbound(7)<<endl;
    cout<<"upper bound of 40 is = "<<a.upperbound(40)<<endl;
    cout<<"upper bound of 31 is = "<<a.upperbound(31)<<endl;
    cout<<".........................."<<endl;
    cout<<"closest value to 7 is = "<<a.closest(7)<<endl;
    cout<<"closest value to 22 is = "<<a.closest(22)<<endl;
    cout<<"closest value to 7 is = "<<a.closest(7)<<endl;
    cout<<"closest value to 60 is = "<<a.closest(60)<<endl;
    cout<<".........................."<<endl;
    cout<<"1 largest value is = "<<a.klargest(1)<<endl;
    cout<<"2 largest value is = "<<a.klargest(2)<<endl;
    cout<<"3 largest value is = "<<a.klargest(3)<<endl;
    cout<<"4 largest value is = "<<a.klargest(4)<<endl;
    cout<<"5 largest value is = "<<a.klargest(5)<<endl;
    cout<<"6 largest value is = "<<a.klargest(6)<<endl;
    cout<<"7 largest value is = "<<a.klargest(7)<<endl;
    cout<<".........................................."<<endl;*/

    avl<float> t;

    t.insertKey(1.3);
    t.insertKey(2.4);
     t.insertKey(2.4);
      t.insertKey(2.4); t.insertKey(2.4);
    t.insertKey(3.5);
    t.insertKey(4.6);
    t.insertKey(5.7);
    t.insertKey(6.8);
    t.insertKey(7.9);

    cout<<"\nLevelOrder after Insertion : "; t.levelOrder();
    cout<<endl;

    /*t.deleteKey(5.7);
    t.deleteKey(6.8);
    t.deleteKey(7.9);

   // cout<<endl<<"root : "<<root->data<<endl;

    cout<<"\nLevelOrder after Deletion : "; t.levelOrder();
    cout<<endl;*/

   /* tree.deleteKey(55);
    tree.deleteKey(60);
    tree.deleteKey(70);

    cout<<"\nLevelOrder after Deletion : "; tree.levelOrder();*/

    bool found = t.searchKey(1.3);
    if(found) cout<<endl<<endl<<"Node Found !";
    else cout<<endl<<endl<<"Node NOT Found !";

    int count = t.countOccurrance(1.3);
    cout<<endl<<endl<<"Count Occurances : "<<count;

    cout<<endl<<endl<<"Lower Bound : "<<t.lowerbound(5.7);
    cout<<endl<<endl<<"Upper Bound : "<<t.upperbound(5.7);

    cout<<endl<<endl<<"Closest Element : "<<t.closest(5.7);

    cout<<endl<<endl<<"3nd largest Element : "<<t.klargest(3);

    cout<<endl<<endl<<"No of elements that lies within the given range are : "<<t.rangeQuery(4.6 , 6);

    cout<<endl<<endl;
    return 0; 
} 