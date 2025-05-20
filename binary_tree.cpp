#include<iostream>
#include<vector>
#include<queue>
#include <cassert>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
NODE* createNode(int data) {
	NODE* p = new NODE;
	p->key = data;
	p->p_left = NULL;
	p->p_right = NULL;
	return p;
}
vector<int> NLR(NODE* pRoot) {
	vector<int>NLR_new;
	if (!pRoot)return NLR_new;
	NLR_new.push_back(pRoot->key);
	vector<int>left = NLR(pRoot->p_left);
	for (int i = 0; i < left.size(); i++) {
		NLR_new.push_back(left[i]);
	}
	vector<int>right = NLR(pRoot->p_right);
	for (int i = 0; i < right.size(); i++) {
		NLR_new.push_back(right[i]);
	}
	//NLR_new.insert(NLR_new.end(), left.begin(), left.end());
    //NLR_new.insert(NLR_new.end(), right.begin(), right.end());
	return NLR_new;
}
vector<int> LNR(NODE* pRoot) {
	vector<int>LNR_new;
	if (!pRoot)return LNR_new;

	vector<int>left = LNR(pRoot->p_left);
	for (int i = 0; i < left.size(); i++) {
		LNR_new.push_back(left[i]);
	}
	LNR_new.push_back(pRoot->key);
	vector<int>right = LNR(pRoot->p_right);
	for (int i = 0; i < right.size(); i++) {
		LNR_new.push_back(right[i]);
	}
	

	return LNR_new;

}
vector<int> LRN(NODE* pRoot) {
	vector<int>LRN_new;
	if (!pRoot)return LRN_new;

	vector<int>left = LRN(pRoot->p_left);
	for (int i = 0; i < left.size(); i++) {
		LRN_new.push_back(left[i]);
	}
	
	vector<int>right = LRN(pRoot->p_right);
	for (int i = 0; i < right.size(); i++) {
		LRN_new.push_back(right[i]);
	}
	LRN_new.push_back(pRoot->key);

	return LRN_new;
}
//vector<vector<int>> LevelOrder(NODE* pRoot)
//{
//	vector<vector<int>>BFS;
//	if (!pRoot)return BFS;
//	queue<NODE*> q;
//	q.push(pRoot);
//	while (!q.empty()) {
//		vector<int>node_eachlevel;
//		int sizequeue = q.size();
//
//		for (int i=0; i < sizequeue; i++) {
//			NODE* cur = q.front();
//			q.pop();
//			node_eachlevel.push_back(cur->key);
//			if (cur->p_left != NULL) {
//				q.push(cur->p_left);
//			}
//			if (cur->p_right != NULL) {
//				q.push(cur->p_right);
//			}
//
//		}
//		BFS.push_back(node_eachlevel);
//
//
//
//
//	}
//	return BFS;
//}

vector<vector<int>> LevelOrder(NODE* pRoot) {
	
	vector<vector<int>>BFS;
	if (pRoot == NULL)return BFS;
	queue<NODE*>q;
	q.push(pRoot);
	while (!q.empty()) {
		int size_q = q.size();
		vector<int>level;
		for (int i = 0; i < size_q; i++) {
			NODE* p = q.front();
			q.pop();
			level.push_back(p->key);
			if (p->p_left != NULL) {
				q.push(p->p_left);
			}
			if (p->p_right) {
				q.push(p->p_right);
			}
		}
		BFS.push_back(level);
	}
	return BFS;
}



//int countNode(NODE* pRoot) {
//	if (!pRoot)return -1;
//	vector<int>N_tree = NLR(pRoot);
//	return N_tree.size();
//}
int countNode(NODE* pRoot) {
	if (!pRoot)return 0;
	int left = countNode(pRoot->p_left);
	int right = countNode(pRoot->p_right);
	return 1 + left + right;
}
int sumNode(NODE* pRoot) {
	if (!pRoot)return 0;
	int left = sumNode(pRoot->p_left);
	int right = sumNode(pRoot->p_right);
	return pRoot->key + left + right;
}

//int heightNode(NODE* pRoot, int value) {
//	if (pRoot == NULL)return -1;
//	int height = -1;
//	queue<NODE*>q;
//	q.push(pRoot);
//	int h_x = -2;
//	while (!q.empty()) {
//		height++;
//		int s = q.size();
//		for (int i = 0; i < s; i++) {
//			NODE* cur = q.front();
//			q.pop();
//			if (cur->key == value)h_x = height;
//			if(cur->p_left!=NULL){
//				q.push(cur->p_left);
//			}
//			if (cur->p_right != NULL) {
//				q.push(cur->p_right);
//			}
//		}
//	}
//	if (h_x == -2)return -1;
//	return height - h_x;
//
//}
int height(NODE* pRoot) {
	if (pRoot == NULL) return -1;
	int left = height(pRoot->p_left);
	int right = height(pRoot->p_right);
	return 1 + max(left, right);
}
NODE* find(NODE* pRoot, int value) {
	
	if (pRoot == NULL)return NULL;
	if (pRoot->key == value)return pRoot;
	NODE* left = find(pRoot->p_left,value);
	if (left != NULL)return left;
	return find(pRoot->p_right, value);
}
int heightNode(NODE* pRoot, int value) {
	NODE* x = find(pRoot, value);
	if (x == NULL)return -1;
	int h = height(x);
	return h;
}
int _level(NODE* pRoot, NODE* p, int level) {
	if (pRoot == NULL)return -1;
	if (pRoot == p)return level;
	int left = _level(pRoot->p_left, p, level + 1);
	if (left != -1)return left;
	int right = _level(pRoot->p_right, p, level + 1);
	return right;
}
int Level(NODE* pRoot, NODE* p) {
	if (pRoot == NULL || p == NULL)return -1;
	return _level(pRoot, p, 0);

}
int countLeaf(NODE* pRoot) {
	if (pRoot == NULL)return 0;
	if (pRoot->p_left == NULL && pRoot->p_right == NULL)return 1;
	int left = countLeaf(pRoot->p_left);
	int right = countLeaf(pRoot->p_right);
	return left + right;
}
void printVector(string title, vector<int> v) {
	cout << title << ": ";
	for (int x : v) cout << x << " ";
	cout << endl;
}

void printLevelOrder(string title, vector<vector<int>> levels) {
	cout << title << ":\n";
	for (auto& level : levels) {
		for (int x : level) cout << x << " ";
		cout << endl;
	}
}
// Hàm xóa cây
void deleteTree(NODE* root) {
	if (root == NULL) return;
	deleteTree(root->p_left);
	deleteTree(root->p_right);
	delete root;
}
int main() {
	// Test cây đầy đủ
	NODE* root = createNode(10);
	root->p_left = createNode(5);
	root->p_right = createNode(20);
	root->p_left->p_left = createNode(3);
	root->p_left->p_right = createNode(7);
	root->p_right->p_left = createNode(15);
	root->p_right->p_right = createNode(30);

	printVector("NLR", NLR(root));
	printVector("LNR", LNR(root));
	printVector("LRN", LRN(root));
	printLevelOrder("LevelOrder", LevelOrder(root));

	cout << "Total nodes: " << countNode(root) << " (expect 7)\n";
	cout << "Sum of nodes: " << sumNode(root) << " (expect 90)\n";
	cout << "Tree height: " << height(root) << " (expect 2)\n";
	cout << "Height of node 5: " << heightNode(root, 5) << " (expect 1)\n";
	cout << "Height of node 3: " << heightNode(root, 3) << " (expect 0)\n";
	cout << "Height of node 100 (not exist): " << heightNode(root, 100) << " (expect -1)\n";
	cout << "Level of node 15: " << Level(root, root->p_right->p_left) << " (expect 2)\n";
	cout << "Leaf count: " << countLeaf(root) << " (expect 4)\n";

	deleteTree(root);

	// Test 1 nút
	NODE* single = createNode(42);
	cout << "\n--- Single node test ---\n";
	cout << "Total nodes: " << countNode(single) << " (expect 1)\n";
	cout << "Sum: " << sumNode(single) << " (expect 42)\n";
	cout << "Height: " << height(single) << " (expect 0)\n";
	cout << "Leaf count: " << countLeaf(single) << " (expect 1)\n";
	deleteTree(single);

	// Test cây rỗng
	NODE* empty = NULL;
	cout << "\n--- Empty tree test ---\n";
	assert(NLR(empty).empty());
	assert(LNR(empty).empty());
	assert(LRN(empty).empty());
	assert(LevelOrder(empty).empty());
	cout << "All traversals empty - OK\n";
	cout << "Total nodes: " << countNode(empty) << " (expect 0)\n";
	cout << "Sum: " << sumNode(empty) << " (expect 0)\n";
	cout << "Height: " << height(empty) << " (expect -1)\n";
	cout << "HeightNode(5): " << heightNode(empty, 5) << " (expect -1)\n";
	cout << "Level: " << Level(empty, NULL) << " (expect -1)\n";
	cout << "Leaf count: " << countLeaf(empty) << " (expect 0)\n";

	return 0;
}