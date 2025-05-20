#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
NODE* Search(NODE* pRoot, int x) {
	if (pRoot == NULL)return NULL;
	if (pRoot->key == x)return pRoot;
	NODE* left = Search(pRoot->p_left, x);
	if (left != NULL)return left;
	return Search(pRoot->p_right, x);
}
void Insert(NODE*& pRoot, int x) {
	if (pRoot == NULL) {
		pRoot = new NODE;
		pRoot->key = x;
		pRoot->p_left = NULL;
		pRoot->p_right = NULL;
	}
	else {
		if (x < pRoot->key) {
			Insert(pRoot->p_left, x);
		}
		else if (x > pRoot->key) {
			Insert(pRoot->p_right, x);
		}
	}
}
void Remove(NODE*& pRoot, int x) {
	if (pRoot == NULL) return;
	if (x < pRoot->key) {
		Remove(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Remove(pRoot->p_right, x);
	}
	else {
		if (pRoot->p_right == NULL && pRoot->p_left==NULL) {
			delete pRoot;
			pRoot = NULL;
		}
		else if (pRoot->p_right == NULL) {
			NODE* cur = pRoot;
			pRoot = pRoot->p_left;
			delete cur;
		}
		else if (pRoot->p_left == NULL) {
			NODE* cur = pRoot;
			pRoot = pRoot->p_right;
			delete cur;
		}
		else {
			NODE* temp = pRoot->p_right;
			while (temp->p_left!= NULL) {
				temp = temp->p_left;//đã thấy trái nhất bên phải
			}
			pRoot->key = temp->key;
			Remove(pRoot->p_right, temp->key);
		}

	}
}
NODE* createTree(int a[], int n) {
	NODE* tree = NULL;
	for (int i = 0; i < n; i++) {
		Insert(tree, a[i]);
	}
	return tree;
}

void removeTree(NODE*& pRoot) {
	if (pRoot == NULL)return;
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
}
int Height(NODE* pRoot) {
	if (pRoot == NULL)return -1;
	int left = Height(pRoot->p_left);
	int right = Height(pRoot->p_right);
	return 1 + max(left, right);
}
int countLess(NODE* pRoot, int x) {
	if (pRoot == NULL)return 0;
	if (pRoot->key < x) {
		return 1 + countLess(pRoot->p_left,x) + countLess(pRoot->p_right,x);

	}
	else {
		return countLess(pRoot->p_left,x);
	}
}

int countGreater(NODE* pRoot, int x) {
	if (pRoot == NULL)return 0;
	if (pRoot->key > x) {
		return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
	}
	else {
		return countGreater(pRoot->p_right, x);
	}
}
bool _isBST(NODE* pRoot, int minval, int maxval) {
	if (pRoot == NULL)return true;
	if (pRoot->key <= minval || pRoot->key >= maxval) return false;
	return _isBST(pRoot->p_left, minval, pRoot->key)&&
	_isBST(pRoot->p_right, pRoot->key, maxval);
			
}
bool isBST(NODE* pRoot) {
	return _isBST(pRoot, -2147483648, 2147483647);
}
bool isFull(NODE* pRoot) {
	if (pRoot == NULL)return true;
	if (pRoot->p_left == NULL && pRoot->p_right != NULL || pRoot->p_left != NULL && pRoot->p_right == NULL) return false;
	return isFull(pRoot->p_left) && isFull(pRoot->p_right);
}
bool isFullBST(NODE* pRoot) {
	
	return _isBST(pRoot, -2147483648, 2147483647)&& isFull(pRoot);
}
int main() {
	// Test 1: Insert + Height
	cout << "==== Test Insert + Height ====" << endl;
	int a[] = { 10, 5, 1, 7, 15, 12, 20 };
	NODE* tree = createTree(a, 7);
	cout << "Height: " << Height(tree) << " (expect 2)" << endl;

	// Test 2: Search
	cout << "\n==== Test Search ====" << endl;
	cout << "Search 7: " << (Search(tree, 7) != NULL) << " (expect 1)" << endl;
	cout << "Search 100: " << (Search(tree, 100) != NULL) << " (expect 0)" << endl;

	// Test 3: Remove các loại node (lá, 1 con, 2 con)
	cout << "\n==== Test Remove ====" << endl;
	Remove(tree, 1);  // node lá
	Remove(tree, 15); // node có 1 con (chỉ còn 20)
	Remove(tree, 10); // node có 2 con
	cout << "Height after removals: " << Height(tree) << " (expect 2)" << endl;
	cout << "Search 1: " << (Search(tree, 1) != NULL) << " (expect 0)" << endl;

	// Test 4: countLess + countGreater
	cout << "\n==== Test countLess / countGreater ====" << endl;
	NODE* t2 = createTree(a, 7);
	cout << "countLess(12): " << countLess(t2, 12) << " (expect 4)" << endl;   // 1,5,7,10
	cout << "countGreater(7): " << countGreater(t2, 7) << " (expect 4)" << endl; // 10,12,15,20

	// Test 5: isBST
	cout << "\n==== Test isBST ====" << endl;
	cout << "isBST (correct): " << isBST(t2) << " (expect 1)" << endl;
	NODE* wrong = new NODE{ 10, new NODE{20, NULL, NULL}, NULL };
	cout << "isBST (wrong): " << isBST(wrong) << " (expect 0)" << endl;

	// Test 6: isFull
	cout << "\n==== Test isFull ====" << endl;
	NODE* full = createTree(a, 7);
	cout << "isFull: " << isFull(full) << " (expect 1)" << endl;
	full->p_left->p_left = NULL;
	cout << "isFull (after breaking): " << isFull(full) << " (expect 0)" << endl;

	// Test 7: isFullBST
	cout << "\n==== Test isFullBST ====" << endl;
	NODE* t3 = createTree(a, 7);
	cout << "isFullBST (correct): " << isFullBST(t3) << " (expect 1)" << endl;
	t3->p_left->p_right = NULL;
	cout << "isFullBST (after breaking): " << isFullBST(t3) << " (expect 0)" << endl;

	// Giải phóng bộ nhớ
	removeTree(tree);
	removeTree(t2);
	removeTree(t3);
	removeTree(wrong);
	removeTree(full);

	return 0;
}