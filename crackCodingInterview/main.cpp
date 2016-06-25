//
//  main.cpp
//  crackCodingInterview
//
//  Created by jdlander on 16/6/25.
//  Copyright © 2016年 jdlander. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unordered_map>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <list>
#include <unordered_map>
#include <deque>
#include <algorithm>
using namespace std;

struct linkNode{
    int val;
    linkNode* next;
    linkNode(int v,linkNode* n = NULL):val(v),next(n){}
};
struct linkList {
    linkList* next;
    int val;
    linkList(int v = 0,linkList* n = NULL):val(v),next(n){}
};
struct treeNode{
    int val;
    treeNode* left;
    treeNode* right;
    treeNode* parent;
    treeNode(int v,treeNode* l = NULL,treeNode* r = NULL):val(v),left(l),right(r){}
};






//cc150 1.1判断字符串中是否所有字符都不一样

bool isUniqueChars(string str){
    bool *char_set = new bool[256]();
    for(int i = 0; i < 256; ++i){
        char_set[i] = false;
    }
    int len = str.length();
    for(int i = 0; i < len; ++i){
        if(char_set[static_cast<int>(str[i])] != false)
            return false;
        else
            char_set[static_cast<int>(str[i])] = true;
    }
    return true;
}

//cc150 1.2反转字符串
void reverse(char* str){
    char* last = str;
    if(!str)
        return;
    
    while(*last){
        last++;
    }
    --last;
    while(str < last){
        char temp = *str;
        *str = *last;
        *last = temp;
        
        ++str;
        --last;
    }
    return;
}
//cc150 1.3判断两个字符串是否是变位词

bool permutation(string str_1,string str_2){
    if(str_1.length() != str_2.length())
        return false;
    int* times = new int[256]();
    int str_len = str_1.length();
    int i = 0;
    for(const char* temp = str_1.c_str();i < str_len;++i){
        char c = *(temp + i);
        times[static_cast<int>(c)]++;
    }
    i = 0;
    for(const char* temp = str_2.c_str();i < str_len;++i){
        char c = *(temp + i);
        times[static_cast<int>(c)]--;
    }
    for(int i = 0; i < 256; ++i){
        if(times[i] != 0){
            return false;
        }
    }
    return true;
}


//cc150 1.4 用%20替换空格
void replaceSpace(char* str){
    int spaceCount = 0;
    int len = strlen(str);
    for(int i = 0; i < len; ++i){
        if(*(str + i) == ' ')
            spaceCount++;
    }
    
    for(int i = len;i >= 0; --i){
        if(*(str + i) != ' '){
            *(str + i + 2 * spaceCount) = *(str + i);
        }
        else{
            *(str + i + 2 * spaceCount - 2) = '%';
            *(str + i + 2 * spaceCount - 1) = '2';
            *(str + i + 2 * spaceCount) = '0';
            spaceCount--;
        }
    }
}

//cc150 1.5 压缩字符串

string compressBad(string str){
    int len = str.length();
    char* result = new char[len]();
    const char* cStr = str.c_str();
    char last = *cStr;
    int count = 1;
    int resultCount = 0;
    for(int i = 1; i < len && resultCount < len; ++i){
        if(*(cStr + i) == last){
            count++;
        }
        else{
            result[resultCount] = last;
            result[resultCount + 1] = '0' + count;
            resultCount += 2;
            last = *(cStr + i);
            count = 1;
        }
    }
    if(resultCount == len){
        return str;
    }
    string re(result);
    //   delete[] result;
    return re;
}



//cc150 1.7 将0元素的行和列都清零

void setZeros(int** matrix,int row,int column){
    bool *rowsHasZero = new bool[row]();
    bool *columnHasZero = new bool[column]();
    memset(rowsHasZero,0,row);
    memset(columnHasZero,0,column);
    
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < column; ++j){
            if(matrix[i][j] == 0){
                rowsHasZero[i] = true;
                columnHasZero[j] = true;
            }
        }
    }
    for(int i = 0; i < row; ++i){
        if(rowsHasZero[i]){
            for(int j = 0; j < column; ++j){
                matrix[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < column; ++i){
        if(columnHasZero[i]){
            for(int j = 0; j < row; ++j){
                matrix[j][i] = 0;
            }
        }
    }
    
    delete [] rowsHasZero;
    delete [] columnHasZero;
}

bool isSubstring(string s1, string s2){return true;} //判断s2是否是s1的子串，可以用KMP算法或者后缀树进行判断

//cc150 1.8 用isSubstring判断S2是否是s1旋转后的字符串
bool isRotation(string s1,string s2){
    int len_1 = s1.length();
    int len_2 = s2.length();
    if(len_1 == len_2 && len_1 > 0){
        s1 = s1.append(s1);
        return isSubstring(s1,s2);
    }
    return false;
}


//cc150 2.1 移除链表中的重复节点
void removeDuplicatedNode(linkNode* head){    //时间复杂度O(n)空间复杂度O(n)
    unordered_map<int,bool> hashMap;
    if(head == NULL) return;
    hashMap[head->val] = true;
    while(head->next != NULL){
        linkNode* nextNode = head->next;
        if(hashMap.find(nextNode->val) == hashMap.end()){
            // head = head->next;
            hashMap[nextNode->val] = true;
        }
        else{
            head->next = nextNode->next;
            delete nextNode;
        }
    }
}

void removeDuplicatedNode_2(linkNode* head){    //时间复杂度O(n2)空间复杂度O(1)
    if(head == NULL){
        
    }
    linkNode* current = head;
    linkNode* runner;
    while(current != NULL){
        runner = current;
        while(runner->next != NULL){
            if(runner->next->val == current->val){
                runner->next = runner->next->next;
            }
            else{
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

//cc150 2.2 找出单链表中倒数第K个节点

linkNode* nthToLast(linkNode* head,int n){
    if(n <= 0)
        return NULL;
    int i = 0;
    linkNode *walk = head;
    for(; walk != NULL && i < n; ++i){
        walk = walk->next;
    }
    if(i < n)
        return NULL;
    while(walk->next != NULL){
        walk = walk->next;
        head = head->next;
    }
    return head;
}



//cc150 2.3删除单向链表中的某个节点，假设只能访问该节点

void deleteNode(linkNode* node){
    if(node == NULL || node->next == NULL){
        return;
    }
    linkNode* nodeToDelete = node->next;
    node->val = nodeToDelete->val;
    node->next = nodeToDelete->next;
    delete nodeToDelete;
}

//cc150 2.4 以给定值x为基准，将链表中小于x的放在前面，大于x的放在后面

linkNode* partitionLinkList(linkNode* head,int keyVal){
    linkNode* beforeBegin = NULL;
    linkNode* beforeEnd = NULL;
    linkNode* afterBegin = NULL;
    linkNode* afterEnd = NULL;
    linkNode* walk = head;
    
    while(walk != NULL){
        linkNode* nextNode = walk->next;
        walk->next = NULL;
        if(walk->val <= keyVal){
            if(beforeBegin == NULL){
                beforeBegin = walk;
                beforeEnd = beforeBegin;
            }
            else{
                beforeEnd->next = walk;
                beforeEnd = walk;
            }
        }
        else{
            if(afterBegin = NULL){
                afterBegin = walk;
                afterEnd = afterBegin;
            }
            else{
                afterEnd->next = walk;
                afterEnd = walk;
            }
        }
        walk = nextNode;
    }
    
    if(beforeBegin == NULL)  //如果全部都大于keyVal
        return afterBegin;
    
    beforeEnd->next = afterBegin;
    return beforeBegin;
}




//cc150 2.5 给定两个用链表标示的整数，求两个整数只和，分别考虑正向存放和反向存放的情况

linkNode* addListCore(linkNode* head_1,linkNode* head_2,int overNum){
    linkNode* result = new linkNode(0);
    if(head_1 == NULL){
        
    }
    
    int sum = head_1->val + head_2->val + overNum;
    result->val = sum % 10;
    result->next = addListCore(head_1->next,head_2->next,sum / 10);
    return result;
}

linkNode* addLists(linkNode* head_1,linkNode* head_2){
    return  NULL;
}

//递归及动态规划

//9.1 爬楼梯


int countWaysDP(int n){
    if(n < 0)
        return -1;
    if(n <= 3)
        return n;
    int left = 1;
    int middle = 2;
    int right = 3;
    
    int count = 3;
    while(count < n){
        int nextVal = left + middle + right;
        left = middle;
        middle = right;
        right = nextVal;
        count++;
    }
    return right;
}


//9.3 魔术索引

int magicFast(int a[],int begin, int end){
    if(begin > end)
        return -1;
    int middle = begin + ((end - begin) >> 1);
    if(a[middle] == middle)
        return middle;
    else if(a[middle] > middle)
        return magicFast(a,middle + 1,end);
    else
        return magicFast(a,begin,middle - 1);
}


int magicFastHasDupVal(int a[],int begin,int end){
    if(begin > end)
        return -1;
    int middle = begin + ((end - begin) >> 1);
    
    if(middle == a[middle])
        return middle;
    else if(middle > a[middle]){
        int temp = magicFastHasDupVal(a,begin,a[middle]);
        if(temp != -1)
            return temp;
        else
            return magicFastHasDupVal(a,middle + 1,end);
    }
    else{
        int temp = magicFastHasDupVal(a,a[middle],end);
        if(temp != -1)
            return temp;
        else
            return magicFastHasDupVal(a,begin,middle - 1);
    }
}

#pragma mark - 2.6有环链表的入口

linkList* findBeginning(linkList* head){
    if(head == NULL || head->next == NULL)
        return NULL;
    linkList* slowWalk = head->next;
    linkList* fastWalk = head->next->next;
    int k = 1;
    while (fastWalk != NULL && fastWalk->next != NULL && fastWalk != slowWalk) {
        fastWalk = fastWalk->next->next;
        slowWalk = slowWalk->next;
        k++;
    }
    if(fastWalk == NULL)
        return NULL;
    slowWalk = head;
    while (slowWalk != fastWalk) {
        slowWalk = slowWalk->next;
        fastWalk = fastWalk->next;
    }
    return slowWalk;
}



#pragma mark - 2.7链表回文

bool isPalindrome(linkList* head){
    stack<linkList*> sk;
    if(head == NULL)
        return false;
    linkList* fastWalk = head;
    linkList* slowWalk = head;
    while (fastWalk != NULL && fastWalk->next != NULL) {
        sk.push(slowWalk);
        fastWalk = fastWalk->next->next;
        slowWalk = slowWalk->next;
    }
    if (fastWalk != NULL) {
        slowWalk = slowWalk->next;
    }
    while (!sk.empty() && slowWalk != NULL) {
        linkList* temp = sk.top();
        sk.pop();
        if (temp->val != slowWalk->val) {
            return false;
        }
        slowWalk = slowWalk->next;
    }
    return true;
    
}

#pragma mark - 第三章：栈与队列


#pragma mark - 3.1 用一个数组实现三个栈

#pragma mark - 3.2 设计一个支持 min 操作的栈

//solution_1 在元素的数据结构中加入 min 成员，随时记录每一个栈元素的当前最小值，当入栈时就比较入栈的值和当前最小值的关系，出栈时直接 pop 出栈
//solution_2 使用另外一个栈来存储 min 元素的值和个数，可以节省空间

#pragma mark - 3.3 设计一个多栈数据结构，当每个单栈内的元素数量过大时会新建另一个栈进行存储，但是其余操作与栈无异。进阶：实现一个 popAt(int Index)方法，根据指定的子栈，进行 pop 操作

#pragma mark - 3.4 汉罗塔问题

int theOtherTowerNum(int tower1,int tower2){   //返回另外一个缓冲tower
    if (tower1 != 1 && tower2 != 1) {
        return 1;
    }
    else if(tower1 != 2 && tower2 != 2){
        return 2;
    }
    else{
        return 3;
    }
}

void hanoi(int fromTowerNum,int toTowerNum,int diskNum){
    if (diskNum <= 0) {
        return;
    }
    if (diskNum == 1) {
        cout<<"move disc from "<<fromTowerNum<<" to "<<toTowerNum<<endl;
        
    }
    else{
        hanoi(fromTowerNum, theOtherTowerNum(toTowerNum, fromTowerNum), diskNum - 1);
        cout<<"move disc from "<<fromTowerNum<<" to "<<toTowerNum<<endl;
        hanoi(theOtherTowerNum(fromTowerNum, toTowerNum), toTowerNum, diskNum - 1);
    }
    
}

#pragma mark - 3.5 两个栈实现一个队列

template <typename T>
class queueWithTwoStack {
    stack<T> sk_1;
    stack<T> sk_2;
    
public:
    void push(T&);
    void pop();
    T top();
    bool isEmpty();
};

template <typename T>
void queueWithTwoStack<T>::push(T &temp){
    sk_1.push(temp);
}

template <typename T>
void queueWithTwoStack<T>::pop() {
    if(!sk_2.empty()){
        sk_2.pop();
    }
    else{
        while (!sk_1.empty()) {
            T temp = sk_1.top();
            sk_1.pop();
            sk_2.push(temp);
        }
        sk_2.pop();
    }
}

#pragma mark - 3.6 按照升序对栈进行排序,只能用一个栈辅助


void stackSort(stack<int>& originalStack,stack<int>& sortedStack){
    while (!originalStack.empty()) {
        int temp = originalStack.top();
        originalStack.pop();
        while (sortedStack.top() > temp && !sortedStack.empty()) {
            int temp_1 = sortedStack.top();
            sortedStack.pop();
            originalStack.push(temp_1);
        }
        sortedStack.push(temp);
    }
}


#pragma mark - 3.7 实现一个数据结构，支持 enqueue，dequeueAny，dequeueDog，dequeueCat


#pragma mark - 第四章：图与二叉树


#pragma mark - 4.1 判断是否是平衡二叉树

int isBalanceTreeCore(treeNode* root){
    if (root == NULL) {
        return 0;
    }
    int leftHeight = isBalanceTreeCore(root->left);
    if (leftHeight == -1) {
        return -1;
    }
    int rightHeight = isBalanceTreeCore(root->right);
    if (rightHeight == -1) {
        return -1;
    }
    
    if (abs(leftHeight - rightHeight) > 1) {
        return false;
    }
    else{
        return ((leftHeight > rightHeight ? leftHeight : rightHeight) + 1);
    }
}



bool isBalanceTree(treeNode* root){
    if (isBalanceTreeCore(root) == -1) {
        return false;
    } else {
        return true;
    }
}

#pragma mark - 4.3 给定有序整数数组，生成高度最低的二叉树

treeNode* createMinimalBSTCore(int arr[],int beginIndex,int endIndex){
    if (endIndex >= beginIndex) {
        return NULL;
    }
    
    
    int middle = beginIndex + ((endIndex - beginIndex) >> 1);
    int middleNum = arr[middle];
    treeNode* node = new treeNode(middleNum);
    node->left = createMinimalBSTCore(arr, beginIndex, middle - 1);
    node->right = createMinimalBSTCore(arr, middle + 1, endIndex);
    return node;
}


treeNode* createMinimalBST(int arr[],int size){
    return createMinimalBSTCore(arr, 0, size - 1);
}
#pragma mark - 4.4 给定一个二叉树生成K 层个链表


void createLevelLinklistCore(vector<linkList*> vec,treeNode* curRoot,int level){
    if (curRoot == NULL) {
        return ;
    }
    linkList* temp = NULL;
    if (vec.size() == level) {
        temp = new linkList(curRoot->val);
        vec.push_back(temp);
    }
    else{
        temp = vec.at(level);
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new linkList(curRoot->val);
    }
    createLevelLinklistCore(vec, curRoot->left, level + 1);
    createLevelLinklistCore(vec, curRoot->right, level + 1);
}

vector<linkList*> createLevelLinklist(treeNode* root){
    vector<linkList*> result;
    createLevelLinklistCore(result, root, 0);
    return result;
}

#pragma mark - 4.5 检查二叉树是否是排序二叉树

//并不是当前节点大于左节点小于右节点的同时左右节点都是排序二叉树整个二叉树就是排序二叉树


//bool isBST(treeNode* root){
//    if (root == NULL) {
//        return false;
//    }
//    else if(root->left == NULL && root->right == NULL){
//        return true;
//    }
//    else if (root->left != NULL && root->right != NULL){
//        if (root->val < root->left->val || root->val >= root->right->val) {
//            return false;
//        } else {
//            return isBST(root->left) && isBST(root->right);
//        }
//    }
//    else if(root->left == NULL){
//        if (root->val >= root->right->val) {
//            return false;
//        }
//        else{
//            return isBST(root->right);
//        }
//    }
//    else if(root->right == NULL){
//        if(root->val < root->left->val){
//            return false;
//        }
//        else{
//            return isBST(root->left);
//        }
//    }
//    return false;
//}

bool isBSTCore(treeNode* node,int min,int max){
    if (node == NULL) {
        return true;
    }
    if (node->val < min || node->val >= max) {
        return false;
    }
    return isBSTCore(node->left, min, node->val) && isBSTCore(node->right, node->val, max);
}


bool isBST(treeNode* root){
    if (root == NULL) {
        return false;
    }
    return isBSTCore(root,INT32_MIN,INT32_MAX);
}


#pragma mark - 4.6排序二叉树的后继节点

treeNode* successorNode(treeNode* node){
    
    if (node == NULL) {
        return NULL;
    }
    if (node->right != NULL) {
        node = node->right;
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }
    while (node->parent != NULL) {
        if(node == node->parent->left){
            break;
        }
        node = node->parent;
    }
    return node->parent;
}


#pragma mark - 4.7二叉树最低公共祖先

//如果有指向父节点的指针，则问题转化为Y 型链表求交叉节点
//如果没有指向父节点的指针，由上往下，如果两个节点都是当前节点的左子树则遍历左节点，都是当前节点的右子树则便利右节点，否则为最低公共祖先
//该方法在平衡二叉树上运行的渐进复杂度为 O(n)

bool cover(treeNode* root,treeNode* node){
    if (root == NULL) {
        return false;
    }
    if (root == node) {
        return true;
    }
    else{
        return cover(root->left, node) || cover(root->right, node);
    }
}

treeNode* lowestAncestorTreeNode(treeNode* root,treeNode* node_1,treeNode* node_2){
    while (root != NULL) {
        if (cover(root->left, node_1) && cover(root->left, node_2)) {
            root = root->left;
        }
        else if(cover(root->right, node_1) && cover(root->right, node_2)){
            root = root->right;
        }
        else if (!cover(root->right, node_1) && !cover(root->left, node_1)){
            return NULL;
        }
        else if (!cover(root->left, node_2) && !cover(root->right, node_2)){
            return NULL;
        }
        else{
            return root;
        }
    }
    return NULL;
}

#pragma mark - 4.8匹配两个二叉树，T1 T2，T2是否是 T1的子树

//Solution1 找出两个树的中序和前序便利序列，T2的中序前序序列是否是 T1的子序列。如果是，则是子树(判断子串可以用后缀树)  此种方法的空间复杂度较高，O(n)

//Solution2 便利 T1，若遇到节点等于 T2的根节点则遍历看是否是相同的两颗树 此种方式的最坏时间复杂度较高，空间复杂度很低

bool isSameTree(treeNode* node_1,treeNode* node_2){
    if (node_1 == NULL && node_2 == NULL) {
        return true;
    }
    if((node_1 == NULL ^ node_2 == NULL) || (node_1->val != node_2->val))
        return false;
    return isSameTree(node_1->left,node_2->left) && isSameTree(node_1->right, node_2->right);
}



bool isSubtree(treeNode* tree_1,treeNode* tree_2){
    if (tree_2 == NULL) {
        return true;
    }
    if (tree_1 == NULL) {
        return false;
    }
    stack<treeNode*> sk;
    int rootKey = tree_2->val;
    treeNode* walk = tree_1;
    
    while (!sk.empty() || walk != NULL) {
        while (walk != NULL){
            if (walk->val == rootKey && isSubtree(walk, tree_2)) {
                return true;
            }
            sk.push(walk);
            walk = walk->left;
        }
        walk = sk.top();
        sk.pop();
        walk = walk->right;
    }
    return false;
}


#pragma mark - 4.9二叉树中路径和为指定值问题


void printPath(int path[],int begin,int end){
    for (int i = begin; i < end; ++i) {
        cout<<path[i]<<"->";
    }
    cout<<path[end]<<endl;
}
void findSumCore(treeNode* node,int sum,int path[],int level){
    if (node == NULL) {
        return;
    }
    path[level] = node->val;
    int sumVal = 0;
    for (int i = level; i >= 0; --i) {
        sumVal += path[i];
        if (sumVal == sum) {
            printPath(path,i,level);
        }
    }
    findSumCore(node->left, sum, path, level + 1);
    findSumCore(node->right, sum, path, level + 1);
}

int treeHeight(treeNode* root){
    if (root == NULL) {
        return 0;
    }
    else{
        return max(treeHeight(root->left),treeHeight(root->right)) + 1;
    }
}

void findSum(treeNode* root,int sum){
    int height = treeHeight(root);
    int *path = new int[height];
    findSumCore(root, sum, path, 0);
    delete [] path;
}

#pragma mark - 第五章：位操作

#pragma mark - 5.1

int updateBit(int n,int m,int j,int i){
    int mask = 0xFFFFFFFF;
    mask <<= j+1;
    int mask_1 = (1 << i)- 1;
    mask = mask | mask_1;
    m = mask & m;
    n <<= i;
    return m | n;
}

#pragma mark - 5.2 将浮点型转化为二进制形式

string printBinary(double num){
    if (num <= 0 || num >= 1) {
        return string("ERROR");
    }
    char* result = new char[32];
    result[0] = '0';
    result[1] = '.';
    int count = 2;
    while (count < 32 && num > 0) {
        num *= 2;
        if (num / 1) {
            result[count++] = '1';
            num -= 1.0;
        }
    }
    if (num != 0) {
        return string("ERROR");
    }
    else{
        string r(result);
        delete [] result;
        return r;
    }
}

#pragma mark - 5.3 二进制中1个数相同的最小不小于的数/最大不大于的数

int getNext(int n){
    int index = 1;
    while (!(n & (0x1 << index))) {
        index++;
    }
    int index_1 = index + 1;
    for (; index_1 < 32; ++index_1) {
        if (!(n & (0x1 << index_1))) {
            break;
        }
    }
    if (index_1 == 31) {
        return -1;
    }
    n = n | (0x1 << index_1);
    index_1--;
    n = n & ~(0x1 << index_1);
    return n;
}

bool isPatten(int n,int index){
    if ( !(n & (0x1 << index)) && (n & (0x1 << (index + 1)))) {
        return true;
    }
    return false;
}
bool isOne(int n,int index){
    return n & (0x1 << index);
}
bool isZero(int n,int index){
    return !(n & (0x1 << index));
}
int setOne(int n,int index){
    return n | (0x1 << index);
}
int getPre(int n){
    int lastOneCount = 0;
    for (; isOne(n, lastOneCount); lastOneCount++);
    
    int index = 0;
    for (; index < 31; ++index) {
        if (isPatten(n, index)) {
            n = n | (0x1 << index);
            n = n & ~(0x1 << (index + 1));
            n = n & (0xFFFFFFFF << index);
            for (int i = 1;i <= lastOneCount; i++) {
                n = setOne(n, index - 1);
            }
            return n;
        }
        
    }
    return -1;
}

//9.6 打印N对括号的所有组合
void addParrentnessCore(vector<string>& list,int leftParNum,int rightParNum,int count,char* tempStr);
vector<string> addParrentness(int n){
    char* temp= new char[n * 2 + 1];
    vector<string> result;
    addParrentnessCore(result,n,n,0,temp);
    delete [] temp;
    return result;
}

void addParrentnessCore(vector<string>& list,int leftParNum,int rightParNum,int count,char* tempStr){
    if(leftParNum < 0 || leftParNum > rightParNum)
        return;
    
    if(leftParNum == 0 && rightParNum == 0)
    {
        tempStr[count] = '\0';
        string str(tempStr);
        list.push_back(str);
        return;
    }
    if(leftParNum > 0){
        tempStr[count] = '(';
        addParrentnessCore(list,leftParNum - 1,rightParNum,count + 1,tempStr);
    }
    if(rightParNum > leftParNum){
        tempStr[count] = ')';
        addParrentnessCore(list,leftParNum, rightParNum - 1,count + 1,tempStr);
    }
}

//11.5 查找给定字符串的位置

int searchR(vector<string>& strs,string str,int first,int last){
    int middle = first + ((last - first) >> 1);
    if(strs[middle].empty()){
        int left = middle - 1;
        int right = middle + 1;
        while(true){
            if(left < first && last > right)
                return -1;
            else if(left >= first && !strs[left].empty()){
                middle = left;
                break;
            }
            else if(last >= right && !strs[right].empty()){
                middle = right;
                break;
            }
            right++;
            left--;
        }
        if(str == strs[middle])
            return middle;
        else if(str.compare(strs[middle]) < 0)
            return searchR(strs,str,first,middle - 1);
        else
            return searchR(strs,str,middle + 1,last);
        
    }
    return 0;
}
int searchString(vector<string>& strs,string str){
    if(strs.size() <= 0 || str.compare(string("")) == 0)
        return -1;
    return searchR(strs,str,0,strs.size() - 1);
}



#pragma mark - 11.1


void merge(int a[],int b[],int lastA,int lastB){
    while (lastA > 0 && lastB > 0) {
        if (a[lastA - 1] >= b[lastB - 1]) {
            a[lastA + lastB - 1] = a[lastA -  1];
            lastA--;
        }else{
            a[lastA + lastB - 1] = b[lastB - 1];
            lastB--;
        }
    }
    if (lastB > 0) {
        while (lastB > 0) {
            a[lastB - 1] = b[lastB - 1];
            lastB--;
        }
    }
}



#pragma mark - 11.2

string strSort(string str){
    sort(str.begin(), str.end());
    return str;
}

void wordsSort(vector<string>& strArray){
    unordered_map<string, list<string>> hash_map;
    for (int i = 0; i < strArray.size(); ++i) {
        string temp = strSort(strArray.at(i));
        if (hash_map.count(temp) == 0) {
            list<string> tempList;
            tempList.push_back(strArray.at(i));
            hash_map[temp] = tempList;
        }else{
            hash_map[temp].push_back(strArray.at(i));
        }
    }
    strArray.clear();
    for (unordered_map<string, list<string>>::iterator ite = hash_map.begin(); ite != hash_map.end(); ++ite) {
        strArray.insert(strArray.end(), (*ite).second.begin(),(*ite).second.end());
    }
}


#pragma mark - 11.3

int rotateArrayBinarySearch(int num[],int n,int key){
    int begin = 0, end = n - 1;
    while (begin < end) {
        int middle = begin + ((end - begin)>>1);
        if(num[middle] == key)
            return middle;
        else if((num[middle] < key && key < num[end]) || (num[middle] > key && key < num[begin])){
            begin = middle + 1;
        }
        else if ((num[middle] < key && key > num[end]) || (num[middle] > key && key > num[begin])){
            end = middle - 1;
        }
    }
    return false;
}


//11.7 马戏团叠罗汉的高度

struct actor{
    int height;
    int weight;
};
bool comp(const actor a,const actor b){
    return a.height < b.height;
}
int longgestIncreaseSquence(vector<actor>& actors){
    size_t length = actors.size();
    if(length <= 0)
        return -1;
    int* dp = (int*)malloc(sizeof(int) * length);
    dp[0] = 1;
    for(int i = 1; i < length; ++i){
        int longest = 1;
        for(int j = 0; j < i; ++j){
            if(actors[j].weight < actors[i].weight && dp[j] + 1 >= longest)
            {
                longest = dp[j] + 1;
            }
        }
        dp[i] = longest;
    }
    int result = dp[length - 1];
    free(dp);
    return result;
}
int getHeight(vector<actor>& actors){
    sort(actors.begin(),actors.end(),comp);
    int result = longgestIncreaseSquence(actors);
    return result;
}

//11.8 GetRankOfNum(int x)
class Set{
    struct Node{
        Node* left;
        Node* right;
        int val;
        int ranks;
        Node(int v = 0, Node* l = NULL,Node* r = NULL,int ra = 0):left(l),right(r),val(v),ranks(ra){}
    };
public:
    int getRankOfNum(int x){
        int result = 0;
        Node* walk = root;
        while(walk != NULL){
            if(walk->val == x){
                result = walk->ranks + result;
                break;
            }else if(walk->val < x){
                if(walk->left == NULL)
                    return -1;
                walk = walk->left;
            }else{
                if(walk->right == NULL)
                    return -1;
                result += (walk->ranks + 1);
            }
        }
        return result;
    }
    void insetNum(int x){
        Node* walk = root;
        if(walk == NULL){
            walk = new Node(x);
            return;
        }
        while(walk != NULL){
            if(x <= walk->val){
                ++(walk->ranks);
                if(walk->left == NULL){
                    walk->left = new Node(x);
                    break;
                }
                walk = walk->left;
            }
            else{
                if(walk->right == NULL){
                    walk->right = new Node(x);
                    break;
                }
                walk = walk->right;
            }
        }
    }
private:
    Node* root;
};


//13.8 实现智能指针
template<class T> class SmartPointer{
public:
    SmartPointer(T* ptr){
        ref = ptr;
        ref_count = (unsigned*)malloc(sizeof(unsigned));
        *ref_count = 1;
    }
    SmartPointer(SmartPointer<T> &sptr){
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++(*ref_count);
    }
    SmartPointer<T> &operator= (SmartPointer<T> &sptr){
        if(this == &sptr)
            return *this;
        if(*ref_count > 0)
            remove();
        ref = sptr.ref;
        ref_count = sptr.ref_count;
        ++(*ref_count);
        return *this;
    }
    ~SmartPointer(){
        remove();
    }
    T getVal(){
        return *ref;
    }
private:
    T* ref;
    unsigned* ref_count;
    void remove(){
        --(*ref_count);
        if(*ref_count == 0){
            delete ref;
            free(ref_count);
            ref == NULL;
            ref_count == NULL;
        }
    }
};


//13.9 设计一个malloc返回的地址为一个数(2的n次方)的整数倍


void* aligned_malloc(size_t requiredBytes,size_t alignment){
    void* p1;
    void** p2;
    size_t offset = alignment - 1 + sizeof(void*);
    p1 = (void*) malloc(requiredBytes + offset);
    if(p1 == NULL)
        return NULL;
    p2 = (void**)(((size_t)p1 + offset) & ~(alignment - 1));
    p2[-1] = p1;
    return p2;
}

void aligned_free(void* ptr){
    void** p2 = (void**)ptr;
    free(p2[-1]);
}


//13.10 分配一个二维数组


int** my2DAlloc(int rows,int columns){
    int** matrix = (int**) malloc(rows * sizeof(int*));
    if(matrix == NULL)
        return NULL;
    for(int i = 0; i < rows; ++i)
        matrix[i] = (int*)malloc(columns * sizeof(int));
    return matrix;
}

void my2DDealloc(int** pptr,int rows){
    for(int i = 0; i < rows; ++rows)
        free(pptr[i]);
    free(pptr);
}


int** my2DAlloc_2(int rows,int columns){
    int** matrix = (int**) malloc(sizeof(int*) * rows + sizeof(int) * rows * columns);
    if(matrix == NULL)
        return NULL;
    size_t headerLen = sizeof(int*) * rows;
    for(int i = 0; i < rows; ++i)
        matrix[i] = (int*)matrix + headerLen + i * columns;
    return matrix;
}


//17.1 不用临时变量交换两个数

void swapWithNoTemp(int& a,int &b){
    a = a - b;
    b = b + a;
    a = b  - a;
}

void swapWithNoTemp_2(int& a,int& b){
    a = a ^ b;
    b = a ^ b;
    b = a ^ b;
}
int main()
{
    cout<<sizeof(void*)<<endl;
    return 0;
}
