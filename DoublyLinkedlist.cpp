//#include <iostream>
//#include <cassert>
//using namespace std;
//
//struct d_NODE {
//    int key;
//    d_NODE* pNext;
//    d_NODE* pPrev;
//
//   
//    d_NODE(int val) : key(val), pNext(nullptr), pPrev(nullptr) {}
//};
//
//struct d_List {
//    d_NODE* pHead;
//    d_NODE* pTail;
//
//    
//    d_List() : pHead(nullptr), pTail(nullptr) {}
//
//   
//    ~d_List() {
//        while (pHead) {
//            d_NODE* temp = pHead;
//            pHead = pHead->pNext;
//            delete temp;
//        }
//    }
//};
//
//
//d_NODE* createNode(int data) {
//    return new d_NODE(data);
//}
//
//
//d_List* createList(d_NODE* p_node) {
//    d_List* newList = new d_List();
//    newList->pHead = p_node;
//    newList->pTail = p_node;
//    return newList;
//}
//
//
//bool addHead(d_List*& L, int data) {
//    if (!L) return false;
//
//    d_NODE* newNode = createNode(data);
//    if (!L->pHead) {
//        L->pHead = L->pTail = newNode;
//    }
//    else {
//        newNode->pNext = L->pHead;
//        L->pHead->pPrev = newNode;
//        L->pHead = newNode;
//    }
//    return true;
//}
//
//
//bool addTail(d_List*& L, int data) {
//    if (!L) return false;
//
//    d_NODE* newNode = createNode(data);
//    if (!L->pTail) {
//        L->pHead = L->pTail = newNode;
//    }
//    else {
//        newNode->pPrev = L->pTail;
//        L->pTail->pNext = newNode;
//        L->pTail = newNode;
//    }
//    return true;
//}
//
//
//bool removeHead(d_List*& L) {
//    if (!L || !L->pHead) return false;
//
//    d_NODE* temp = L->pHead;
//    if (L->pHead == L->pTail) {
//        L->pHead = L->pTail = nullptr;
//    }
//    else {
//        L->pHead = L->pHead->pNext;
//        L->pHead->pPrev = nullptr;
//    }
//    delete temp;
//    return true;
//}
//
//
//void removeTail(d_List*& L) {
//    if (!L || !L->pTail) return;
//
//    d_NODE* temp = L->pTail;
//    if (L->pHead == L->pTail) {
//        L->pHead = L->pTail = nullptr;
//    }
//    else {
//        L->pTail = L->pTail->pPrev;
//        L->pTail->pNext = nullptr;
//    }
//    delete temp;
//}
//
//
//void removeAll(d_List*& L) {
//    if (!L) return;
//
//    while (L->pHead) {
//        removeHead(L);
//    }
//}
//
//
//void removeBefore(d_List*& L, int val) {
//    if (!L || !L->pHead) return;
//
//    d_NODE* current = L->pHead;
//    while (current && current->key != val) {
//        current = current->pNext;
//    }
//
//    if (!current || !current->pPrev) return;
//
//    d_NODE* toRemove = current->pPrev;
//    if (toRemove == L->pHead) {
//        L->pHead = current;
//        current->pPrev = nullptr;
//    }
//    else {
//        toRemove->pPrev->pNext = current;
//        current->pPrev = toRemove->pPrev;
//    }
//    delete toRemove;
//}
//
//
//void removeAfter(d_List*& L, int val) {
//    if (!L || !L->pHead) return;
//
//    d_NODE* current = L->pHead;
//    while (current && current->key != val) {
//        current = current->pNext;
//    }
//
//    if (!current || !current->pNext) return;
//
//    d_NODE* toRemove = current->pNext;
//    if (toRemove == L->pTail) {
//        L->pTail = current;
//        current->pNext = nullptr;
//    }
//    else {
//        current->pNext = toRemove->pNext;
//        toRemove->pNext->pPrev = current;
//    }
//    delete toRemove;
//}
//
//bool addPos(d_List*& L, int data, int pos) {
//    if (!L || pos < 0) return false;
//
//    if (pos == 0) return addHead(L, data);
//
//    d_NODE* current = L->pHead;
//    int count = 0;
//    while (current && count < pos - 1) {
//        current = current->pNext;
//        count++;
//    }
//
//    if (!current) return false;
//
//    d_NODE* newNode = createNode(data);
//    newNode->pNext = current->pNext;
//    newNode->pPrev = current;
//
//    if (current->pNext) {
//        current->pNext->pPrev = newNode;
//    }
//    else {
//        L->pTail = newNode;
//    }
//    current->pNext = newNode;
//    return true;
//}
//
//
//void removePos(d_List*& L, int pos) {
//    if (!L || !L->pHead || pos < 0) return;
//
//    if (pos == 0) {
//        removeHead(L);
//        return;
//    }
//
//    d_NODE* current = L->pHead;
//    int count = 0;
//    while (current && count < pos) {
//        current = current->pNext;
//        count++;
//    }
//
//    if (!current) return;
//
//    if (current == L->pTail) {
//        removeTail(L);
//        return;
//    }
//
//    current->pPrev->pNext = current->pNext;
//    current->pNext->pPrev = current->pPrev;
//    delete current;
//}
//
//
//bool addBefore(d_List*& L, int data, int val) {
//    if (!L || !L->pHead) return false;
//
//    if (L->pHead->key == val) {
//        return addHead(L, data);
//    }
//
//    d_NODE* current = L->pHead;
//    while (current && current->key != val) {
//        current = current->pNext;
//    }
//
//    if (!current) return false;
//
//    d_NODE* newNode = createNode(data);
//    newNode->pNext = current;
//    newNode->pPrev = current->pPrev;
//    current->pPrev->pNext = newNode;
//    current->pPrev = newNode;
//    return true;
//}
//
//
//bool addAfter(d_List*& L, int data, int val) {
//    if (!L || !L->pHead) return false;
//
//    d_NODE* current = L->pHead;
//    while (current && current->key != val) {
//        current = current->pNext;
//    }
//
//    if (!current) return false;
//
//    d_NODE* newNode = createNode(data);
//    newNode->pNext = current->pNext;
//    newNode->pPrev = current;
//
//    if (current->pNext) {
//        current->pNext->pPrev = newNode;
//    }
//    else {
//        L->pTail = newNode;
//    }
//    current->pNext = newNode;
//    return true;
//}
//
//
//void printList(d_List* L) {
//    if (!L) return;
//
//    d_NODE* current = L->pHead;
//    while (current) {
//        cout << current->key << " ";
//        current = current->pNext;
//    }
//    cout << endl;
//}
//
//
//int countElements(d_List* L) {
//    if (!L) return 0;
//
//    int count = 0;
//    d_NODE* current = L->pHead;
//    while (current) {
//        count++;
//        current = current->pNext;
//    }
//    return count;
//}
//
//
//d_List* reverseList(d_List* L) {
//    if (!L || !L->pHead) return nullptr;
//
//    d_List* newList = new d_List();
//    d_NODE* current = L->pHead;
//    while (current) {
//        addHead(newList, current->key);
//        current = current->pNext;
//    }
//    return newList;
//}
//
//
//void removeDuplicate(d_List*& L) {
//    if (!L || !L->pHead) return;
//
//    d_NODE* current = L->pHead;
//    while (current) {
//        d_NODE* runner = current->pNext;
//        while (runner) {
//            if (runner->key == current->key) {
//                d_NODE* temp = runner;
//                if (runner->pPrev) runner->pPrev->pNext = runner->pNext;
//                if (runner->pNext) runner->pNext->pPrev = runner->pPrev;
//                if (runner == L->pTail) L->pTail = runner->pPrev;
//                runner = runner->pNext;
//                delete temp;
//            }
//            else {
//                runner = runner->pNext;
//            }
//        }
//        current = current->pNext;
//    }
//}
//bool removeElement(d_List*& L, int key) {
//    if (!L || !L->pHead) return false;
//
//    bool found = false;
//    d_NODE* current = L->pHead;
//    while (current) {
//        if (current->key == key) {
//            found = true;
//            d_NODE* temp = current;
//            if (current == L->pHead) {
//                L->pHead = current->pNext;
//                if (L->pHead) L->pHead->pPrev = nullptr;
//            }
//            else if (current == L->pTail) {
//                L->pTail = current->pPrev;
//                if (L->pTail) L->pTail->pNext = nullptr;
//            }
//            else {
//                current->pPrev->pNext = current->pNext;
//                current->pNext->pPrev = current->pPrev;
//            }
//            current = current->pNext;
//            delete temp;
//        }
//        else {
//            current = current->pNext;
//        }
//    }
//    return found;
//}
//
//
//d_List* createListFromArray(int arr[], int n) {
//    d_List* newList = new d_List();
//    for (int i = 0; i < n; ++i) {
//        addTail(newList, arr[i]);
//    }
//    return newList;
//}
//
//
//bool areListsEqual(d_List* list1, d_List* list2) {
//    d_NODE* current1 = list1 ? list1->pHead : nullptr;
//    d_NODE* current2 = list2 ? list2->pHead : nullptr;
//
//    while (current1 && current2) {
//        if (current1->key != current2->key) return false;
//        current1 = current1->pNext;
//        current2 = current2->pNext;
//    }
//    return (current1 == nullptr && current2 == nullptr);
//}
//
//
//void freeList(d_List* L) {
//    if (L) {
//        delete L; 
//    }
//}
//
//int main() {
//    cout << "--- Begin running test cases ---" << endl;
//
//    // Test case 1: createNode
//    cout << "Test 1/18 - createNode: ";
//    d_NODE* node1 = createNode(10);
//    assert(node1 != nullptr && node1->key == 10 && node1->pNext == nullptr && node1->pPrev == nullptr);
//    cout << "Passed" << endl;
//    delete node1;
//
//    // Test case 2: createList
//    cout << "Test 2/18 - createList: ";
//    d_NODE* head2 = createNode(20);
//    d_List* list2 = createList(head2);
//    assert(list2 != nullptr && list2->pHead == head2 && list2->pTail == head2);
//    cout << "Passed" << endl;
//    freeList(list2);
//
//    // Test case 3: addHead
//    cout << "Test 3/18 - addHead: ";
//    d_List* list3 = new d_List();
//    assert(addHead(list3, 30));
//    assert(list3->pHead != nullptr && list3->pHead->key == 30 && list3->pTail->key == 30);
//    assert(addHead(list3, 40));
//    assert(list3->pHead->key == 40 && list3->pHead->pNext->key == 30 && list3->pTail->key == 30);
//    assert(list3->pHead->pNext->pPrev == list3->pHead);
//    cout << "Passed" << endl;
//    freeList(list3);
//
//    // Test case 4: addTail
//    cout << "Test 4/18 - addTail: ";
//    d_List* list4 = new d_List();
//    assert(addTail(list4, 50));
//    assert(list4->pHead != nullptr && list4->pHead->key == 50 && list4->pTail->key == 50);
//    assert(addTail(list4, 60));
//    assert(list4->pHead->key == 50 && list4->pTail->key == 60 && list4->pHead->pNext->key == 60);
//    assert(list4->pTail->pPrev == list4->pHead);
//    cout << "Passed" << endl;
//    freeList(list4);
//
//    // Test case 5: removeHead
//    cout << "Test 5/18 - removeHead: ";
//    int arr1[3] = { 70, 80, 90 };
//    d_List* list5 = createListFromArray(arr1, 3);
//    assert(removeHead(list5) && list5->pHead->key == 80);
//    assert(list5->pHead->pPrev == nullptr);
//    assert(removeHead(list5) && list5->pHead->key == 90);
//    assert(removeHead(list5) && list5->pHead == nullptr && list5->pTail == nullptr);
//    assert(!removeHead(list5));
//    cout << "Passed" << endl;
//    freeList(list5);
//
//    // Test case 6: removeTail
//    cout << "Test 6/18 - removeTail: ";
//    int arr2[3] = { 100, 110, 120 };
//    d_List* list6 = createListFromArray(arr2, 3);
//    removeTail(list6);
//    assert(list6->pTail->key == 110 && list6->pTail->pNext == nullptr);
//    removeTail(list6);
//    assert(list6->pTail->key == 100 && list6->pTail->pNext == nullptr && list6->pHead == list6->pTail);
//    removeTail(list6);
//    assert(list6->pHead == nullptr && list6->pTail == nullptr);
//    d_List* emptyList6 = new d_List();
//    removeTail(emptyList6);
//    cout << "Passed" << endl;
//    freeList(emptyList6);
//    freeList(list6);
//
//    // Test case 7: removeAll
//    cout << "Test 7/18 - removeAll: ";
//    int arr3[3] = { 130, 140, 150 };
//    d_List* list7 = createListFromArray(arr3, 3);
//    removeAll(list7);
//    assert(list7->pHead == nullptr && list7->pTail == nullptr);
//    d_List* emptyList7 = new d_List();
//    removeAll(emptyList7);
//    assert(emptyList7->pHead == nullptr && emptyList7->pTail == nullptr);
//    cout << "Passed" << endl;
//    freeList(emptyList7);
//    freeList(list7);
//
//    // Test case 8: removeBefore
//    cout << "Test 8/18 - removeBefore: ";
//    int arr4[5] = { 160, 170, 180, 190, 200 };
//    d_List* list8 = createListFromArray(arr4, 5);
//    removeBefore(list8, 180);
//    assert(list8->pHead->key == 160 && list8->pHead->pNext->key == 180);
//    removeBefore(list8, 200);
//    assert(list8->pTail->key == 200 && list8->pTail->pPrev->key == 180);
//    cout << "Passed" << endl;
//    freeList(list8);
//
//    // Test case 9: removeAfter
//    cout << "Test 9/18 - removeAfter: ";
//    int arr5[4] = { 210, 220, 230, 240 };
//    d_List* list9 = createListFromArray(arr5, 4);
//    removeAfter(list9, 220);
//    assert(list9->pHead->pNext->key == 220 && list9->pHead->pNext->pNext->key == 240);
//    removeAfter(list9, 230);
//    assert(list9->pTail->key == 240);
//    cout << "Passed" << endl;
//    freeList(list9);
//
//    // Test case 10: addPos
//    cout << "Test 10/18 - addPos: ";
//    d_List* list10 = new d_List();
//    assert(addPos(list10, 250, 0));
//    assert(addPos(list10, 260, 1));
//    assert(addPos(list10, 270, 1));
//    assert(list10->pHead->key == 250 && list10->pHead->pNext->key == 270 && list10->pTail->key == 260);
//    assert(!addPos(list10, 280, 5));
//    cout << "Passed" << endl;
//    freeList(list10);
//
//    // Test case 11: removePos
//    cout << "Test 11/18 - removePos: ";
//    int arr6[5] = { 290, 300, 310, 320, 330 };
//    d_List* list11 = createListFromArray(arr6, 5);
//    removePos(list11, 2);
//    assert(list11->pHead->pNext->pNext->key == 320);
//    removePos(list11, 0);
//    assert(list11->pHead->key == 300);
//    cout << "Passed" << endl;
//    freeList(list11);
//
//    // Test case 12: addBefore
//    cout << "Test 12/18 - addBefore: ";
//    int arr7[3] = { 340, 350, 360 };
//    d_List* list12 = createListFromArray(arr7, 3);
//    assert(addBefore(list12, 345, 350));
//    assert(list12->pHead->pNext->key == 345);
//    assert(addBefore(list12, 335, 340));
//    assert(list12->pHead->key == 335);
//    cout << "Passed" << endl;
//    freeList(list12);
//
//    // Test case 13: addAfter
//    cout << "Test 13/18 - addAfter: ";
//    int arr8[3] = { 370, 380, 390 };
//    d_List* list13 = createListFromArray(arr8, 3);
//    assert(addAfter(list13, 385, 380));
//    assert(list13->pHead->pNext->pNext->key == 385);
//    assert(addAfter(list13, 395, 390));
//    assert(list13->pTail->key == 395);
//    cout << "Passed" << endl;
//    freeList(list13);
//
//    // Test case 14: printList
//    cout << "Test 14/18 - printList: ";
//    int arr9[3] = { 400, 410, 420 };
//    d_List* list14 = createListFromArray(arr9, 3);
//    cout << "Expected: 400 410 420 | Actual: ";
//    printList(list14);
//    cout << "Passed" << endl;
//    freeList(list14);
//
//    // Test case 15: countElements
//    cout << "Test 15/18 - countElements: ";
//    int arr10[5] = { 430, 440, 450, 460, 470 };
//    d_List* list15 = createListFromArray(arr10, 5);
//    assert(countElements(list15) == 5);
//    d_List* emptyList15 = new d_List();
//    assert(countElements(emptyList15) == 0);
//    cout << "Passed" << endl;
//    freeList(list15);
//    freeList(emptyList15);
//
//    // Test case 16: reverseList
//    cout << "Test 16/18 - reverseList: ";
//    int arr11[4] = { 480, 490, 500, 510 };
//    d_List* list16 = createListFromArray(arr11, 4);
//    d_List* reversedList = reverseList(list16);
//    assert(reversedList->pHead->key == 510 && reversedList->pTail->key == 480);
//    cout << "Passed" << endl;
//    freeList(list16);
//    freeList(reversedList);
//
//    // Test case 17: removeDuplicate
//    cout << "Test 17/18 - removeDuplicate: ";
//    int arr12[6] = { 520, 530, 530, 540, 540, 540 };
//    d_List* list17 = createListFromArray(arr12, 6);
//    removeDuplicate(list17);
//    assert(countElements(list17) == 3);
//    cout << "Passed" << endl;
//    freeList(list17);
//
//    // Test case 18: removeElement
//    cout << "Test 18/18 - removeElement: ";
//    int arr13[5] = { 550, 560, 570, 560, 580 };
//    d_List* list18 = createListFromArray(arr13, 5);
//    assert(removeElement(list18, 560));
//    assert(countElements(list18) == 3);
//    assert(!removeElement(list18, 999));
//    cout << "Passed" << endl;
//    freeList(list18);
//
//    cout << "--- The end ---" << endl;
//    return 0;
//}



#include <iostream>
#include <cassert>
using namespace std;

struct d_NODE {
    int key;
    d_NODE* pNext;
    d_NODE* pPrev;
};

struct d_List {
    d_NODE* pHead;
    d_NODE* pTail;
};

d_NODE* createNode(int data) {
    d_NODE* newNode = new d_NODE;
    newNode->key = data;
    newNode->pNext = nullptr;
    newNode->pPrev = nullptr;
    return newNode;
}

d_List* createList(d_NODE* p_node) {
    d_List* newList = new d_List;
    newList->pHead = p_node;
    newList->pTail = p_node;
    return newList;
}

bool addHead(d_List*& L, int data) {
    if (!L) return false;

    d_NODE* newNode = createNode(data);
    if (!L->pHead) {
        L->pHead = L->pTail = newNode;
    }
    else {
        newNode->pNext = L->pHead;
        L->pHead->pPrev = newNode;
        L->pHead = newNode;
    }
    return true;
}

bool addTail(d_List*& L, int data) {
    if (!L) return false;

    d_NODE* newNode = createNode(data);
    if (!L->pTail) {
        L->pHead = L->pTail = newNode;
    }
    else {
        newNode->pPrev = L->pTail;
        L->pTail->pNext = newNode;
        L->pTail = newNode;
    }
    return true;
}

bool removeHead(d_List*& L) {
    if (!L || !L->pHead) return false;

    d_NODE* temp = L->pHead;
    if (L->pHead == L->pTail) {
        L->pHead = L->pTail = nullptr;
    }
    else {
        L->pHead = L->pHead->pNext;
        L->pHead->pPrev = nullptr;
    }
    delete temp;
    return true;
}

void removeTail(d_List*& L) {
    if (!L || !L->pTail) return;

    d_NODE* temp = L->pTail;
    if (L->pHead == L->pTail) {
        L->pHead = L->pTail = nullptr;
    }
    else {
        L->pTail = L->pTail->pPrev;
        L->pTail->pNext = nullptr;
    }
    delete temp;
}

void removeAll(d_List*& L) {
    if (!L) return;

    while (L->pHead) {
        removeHead(L);
    }
}

void removeBefore(d_List*& L, int val) {
    if (!L || !L->pHead) return;

    d_NODE* current = L->pHead;
    while (current && current->key != val) {
        current = current->pNext;
    }

    if (!current || !current->pPrev) return;

    d_NODE* toRemove = current->pPrev;
    if (toRemove == L->pHead) {
        L->pHead = current;
        current->pPrev = nullptr;
    }
    else {
        toRemove->pPrev->pNext = current;
        current->pPrev = toRemove->pPrev;
    }
    delete toRemove;
}

void removeAfter(d_List*& L, int val) {
    if (!L || !L->pHead) return;

    d_NODE* current = L->pHead;
    while (current && current->key != val) {
        current = current->pNext;
    }

    if (!current || !current->pNext) return;

    d_NODE* toRemove = current->pNext;
    if (toRemove == L->pTail) {
        L->pTail = current;
        current->pNext = nullptr;
    }
    else {
        current->pNext = toRemove->pNext;
        toRemove->pNext->pPrev = current;
    }
    delete toRemove;
}

bool addPos(d_List*& L, int data, int pos) {
    if (!L || pos < 0) return false;

    if (pos == 0) return addHead(L, data);

    d_NODE* current = L->pHead;
    int count = 0;
    while (current && count < pos - 1) {
        current = current->pNext;
        count++;
    }

    if (!current) return false;

    d_NODE* newNode = createNode(data);
    newNode->pNext = current->pNext;
    newNode->pPrev = current;

    if (current->pNext) {
        current->pNext->pPrev = newNode;
    }
    else {
        L->pTail = newNode;
    }
    current->pNext = newNode;
    return true;
}

void removePos(d_List*& L, int pos) {
    if (!L || !L->pHead || pos < 0) return;

    if (pos == 0) {
        removeHead(L);
        return;
    }

    d_NODE* current = L->pHead;
    int count = 0;
    while (current && count < pos) {
        current = current->pNext;
        count++;
    }

    if (!current) return;

    if (current == L->pTail) {
        removeTail(L);
        return;
    }

    current->pPrev->pNext = current->pNext;
    current->pNext->pPrev = current->pPrev;
    delete current;
}

bool addBefore(d_List*& L, int data, int val) {
    if (!L || !L->pHead) return false;

    if (L->pHead->key == val) {
        return addHead(L, data);
    }

    d_NODE* current = L->pHead;
    while (current && current->key != val) {
        current = current->pNext;
    }

    if (!current) return false;

    d_NODE* newNode = createNode(data);
    newNode->pNext = current;
    newNode->pPrev = current->pPrev;
    current->pPrev->pNext = newNode;
    current->pPrev = newNode;
    return true;
}

bool addAfter(d_List*& L, int data, int val) {
    if (!L || !L->pHead) return false;

    d_NODE* current = L->pHead;
    while (current && current->key != val) {
        current = current->pNext;
    }

    if (!current) return false;

    d_NODE* newNode = createNode(data);
    newNode->pNext = current->pNext;
    newNode->pPrev = current;

    if (current->pNext) {
        current->pNext->pPrev = newNode;
    }
    else {
        L->pTail = newNode;
    }
    current->pNext = newNode;
    return true;
}

void printList(d_List* L) {
    if (!L) return;

    d_NODE* current = L->pHead;
    while (current) {
        cout << current->key << " ";
        current = current->pNext;
    }
    cout << endl;
}

int countElements(d_List* L) {
    if (!L) return 0;

    int count = 0;
    d_NODE* current = L->pHead;
    while (current) {
        count++;
        current = current->pNext;
    }
    return count;
}

d_List* reverseList(d_List* L) {
    if (!L || !L->pHead) return nullptr;

    d_List* newList = new d_List;
    newList->pHead = newList->pTail = nullptr;
    d_NODE* current = L->pHead;
    while (current) {
        addHead(newList, current->key);
        current = current->pNext;
    }
    return newList;
}

void removeDuplicate(d_List*& L) {
    if (!L || !L->pHead) return;

    d_NODE* current = L->pHead;
    while (current) {
        d_NODE* runner = current->pNext;
        while (runner) {
            if (runner->key == current->key) {
                d_NODE* temp = runner;
                if (runner->pPrev) runner->pPrev->pNext = runner->pNext;
                if (runner->pNext) runner->pNext->pPrev = runner->pPrev;
                if (runner == L->pTail) L->pTail = runner->pPrev;
                runner = runner->pNext;
                delete temp;
            }
            else {
                runner = runner->pNext;
            }
        }
        current = current->pNext;
    }
}

bool removeElement(d_List*& L, int key) {
    if (!L || !L->pHead) return false;

    bool found = false;
    d_NODE* current = L->pHead;
    while (current) {
        if (current->key == key) {
            found = true;
            d_NODE* temp = current;
            if (current == L->pHead) {
                L->pHead = current->pNext;
                if (L->pHead) L->pHead->pPrev = nullptr;
            }
            else if (current == L->pTail) {
                L->pTail = current->pPrev;
                if (L->pTail) L->pTail->pNext = nullptr;
            }
            else {
                current->pPrev->pNext = current->pNext;
                current->pNext->pPrev = current->pPrev;
            }
            current = current->pNext;
            delete temp;
        }
        else {
            current = current->pNext;
        }
    }
    return found;
}

d_List* createListFromArray(int arr[], int n) {
    d_List* newList = new d_List;
    newList->pHead = newList->pTail = nullptr;
    for (int i = 0; i < n; ++i) {
        addTail(newList, arr[i]);
    }
    return newList;
}

bool areListsEqual(d_List* list1, d_List* list2) {
    d_NODE* current1 = list1 ? list1->pHead : nullptr;
    d_NODE* current2 = list2 ? list2->pHead : nullptr;

    while (current1 && current2) {
        if (current1->key != current2->key) return false;
        current1 = current1->pNext;
        current2 = current2->pNext;
    }
    return (current1 == nullptr && current2 == nullptr);
}

void freeList(d_List* L) {
    if (L) {
        removeAll(L);
        delete L;
    }
}

int main() {
    cout << "--- Begin running test cases ---" << endl;

    // Test case 1: createNode
    cout << "Test 1/18 - createNode: ";
    d_NODE* node1 = createNode(10);
    assert(node1 != nullptr && node1->key == 10 && node1->pNext == nullptr && node1->pPrev == nullptr);
    cout << "Passed" << endl;
    delete node1;

    // Test case 2: createList
    cout << "Test 2/18 - createList: ";
    d_NODE* head2 = createNode(20);
    d_List* list2 = createList(head2);
    assert(list2 != nullptr && list2->pHead == head2 && list2->pTail == head2);
    cout << "Passed" << endl;
    freeList(list2);

    // Test case 3: addHead
    cout << "Test 3/18 - addHead: ";
    d_List* list3 = new d_List;
    list3->pHead = list3->pTail = nullptr;
    assert(addHead(list3, 30));
    assert(list3->pHead != nullptr && list3->pHead->key == 30 && list3->pTail->key == 30);
    assert(addHead(list3, 40));
    assert(list3->pHead->key == 40 && list3->pHead->pNext->key == 30 && list3->pTail->key == 30);
    assert(list3->pHead->pNext->pPrev == list3->pHead);
    cout << "Passed" << endl;
    freeList(list3);

    // Test case 4: addTail
    cout << "Test 4/18 - addTail: ";
    d_List* list4 = new d_List;
    list4->pHead = list4->pTail = nullptr;
    assert(addTail(list4, 50));
    assert(list4->pHead != nullptr && list4->pHead->key == 50 && list4->pTail->key == 50);
    assert(addTail(list4, 60));
    assert(list4->pHead->key == 50 && list4->pTail->key == 60 && list4->pHead->pNext->key == 60);
    assert(list4->pTail->pPrev == list4->pHead);
    cout << "Passed" << endl;
    freeList(list4);

    // Test case 5: removeHead
    cout << "Test 5/18 - removeHead: ";
    int arr1[3] = { 70, 80, 90 };
    d_List* list5 = createListFromArray(arr1, 3);
    assert(removeHead(list5) && list5->pHead->key == 80);
    assert(list5->pHead->pPrev == nullptr);
    assert(removeHead(list5) && list5->pHead->key == 90);
    assert(removeHead(list5) && list5->pHead == nullptr && list5->pTail == nullptr);
    assert(!removeHead(list5));
    cout << "Passed" << endl;
    freeList(list5);

    // Test case 6: removeTail
    cout << "Test 6/18 - removeTail: ";
    int arr2[3] = { 100, 110, 120 };
    d_List* list6 = createListFromArray(arr2, 3);
    removeTail(list6);
    assert(list6->pTail->key == 110 && list6->pTail->pNext == nullptr);
    removeTail(list6);
    assert(list6->pTail->key == 100 && list6->pTail->pNext == nullptr && list6->pHead == list6->pTail);
    removeTail(list6);
    assert(list6->pHead == nullptr && list6->pTail == nullptr);
    d_List* emptyList6 = new d_List;
    emptyList6->pHead = emptyList6->pTail = nullptr;
    removeTail(emptyList6);
    cout << "Passed" << endl;
    freeList(emptyList6);
    freeList(list6);

    // Test case 7: removeAll
    cout << "Test 7/18 - removeAll: ";
    int arr3[3] = { 130, 140, 150 };
    d_List* list7 = createListFromArray(arr3, 3);
    removeAll(list7);
    assert(list7->pHead == nullptr && list7->pTail == nullptr);
    d_List* emptyList7 = new d_List;
    emptyList7->pHead = emptyList7->pTail = nullptr;
    removeAll(emptyList7);
    assert(emptyList7->pHead == nullptr && emptyList7->pTail == nullptr);
    cout << "Passed" << endl;
    freeList(emptyList7);
    freeList(list7);

    // Test case 8: removeBefore
    cout << "Test 8/18 - removeBefore: ";
    int arr4[5] = { 160, 170, 180, 190, 200 };
    d_List* list8 = createListFromArray(arr4, 5);
    removeBefore(list8, 180);
    assert(list8->pHead->key == 160 && list8->pHead->pNext->key == 180);
    removeBefore(list8, 200);
    assert(list8->pTail->key == 200 && list8->pTail->pPrev->key == 180);
    cout << "Passed" << endl;
    freeList(list8);

    // Test case 9: removeAfter
    cout << "Test 9/18 - removeAfter: ";
    int arr5[4] = { 210, 220, 230, 240 };
    d_List* list9 = createListFromArray(arr5, 4);
    removeAfter(list9, 220);
    assert(list9->pHead->pNext->key == 220 && list9->pHead->pNext->pNext->key == 240);
    removeAfter(list9, 230);
    assert(list9->pTail->key == 240);
    cout << "Passed" << endl;
    freeList(list9);

    // Test case 10: addPos
    cout << "Test 10/18 - addPos: ";
    d_List* list10 = new d_List;
    list10->pHead = list10->pTail = nullptr;
    assert(addPos(list10, 250, 0));
    assert(addPos(list10, 260, 1));
    assert(addPos(list10, 270, 1));
    assert(list10->pHead->key == 250 && list10->pHead->pNext->key == 270 && list10->pTail->key == 260);
    assert(!addPos(list10, 280, 5));
    cout << "Passed" << endl;
    freeList(list10);

    // Test case 11: removePos
    cout << "Test 11/18 - removePos: ";
    int arr6[5] = { 290, 300, 310, 320, 330 };
    d_List* list11 = createListFromArray(arr6, 5);
    removePos(list11, 2);
    assert(list11->pHead->pNext->pNext->key == 320);
    removePos(list11, 0);
    assert(list11->pHead->key == 300);
    cout << "Passed" << endl;
    freeList(list11);

    // Test case 12: addBefore
    cout << "Test 12/18 - addBefore: ";
    int arr7[3] = { 340, 350, 360 };
    d_List* list12 = createListFromArray(arr7, 3);
    assert(addBefore(list12, 345, 350));
    assert(list12->pHead->pNext->key == 345);
    assert(addBefore(list12, 335, 340));
    assert(list12->pHead->key == 335);
    cout << "Passed" << endl;
    freeList(list12);

    // Test case 13: addAfter
    cout << "Test 13/18 - addAfter: ";
    int arr8[3] = { 370, 380, 390 };
    d_List* list13 = createListFromArray(arr8, 3);
    assert(addAfter(list13, 385, 380));
    assert(list13->pHead->pNext->pNext->key == 385);
    assert(addAfter(list13, 395, 390));
    assert(list13->pTail->key == 395);
    cout << "Passed" << endl;
    freeList(list13);

    // Test case 14: printList
    cout << "Test 14/18 - printList: ";
    int arr9[3] = { 400, 410, 420 };
    d_List* list14 = createListFromArray(arr9, 3);
    cout << "Expected: 400 410 420 | Actual: ";
    printList(list14);
    cout << "Passed" << endl;
    freeList(list14);

    // Test case 15: countElements
    cout << "Test 15/18 - countElements: ";
    int arr10[5] = { 430, 440, 450, 460, 470 };
    d_List* list15 = createListFromArray(arr10, 5);
    assert(countElements(list15) == 5);
    d_List* emptyList15 = new d_List;
    emptyList15->pHead = emptyList15->pTail = nullptr;
    assert(countElements(emptyList15) == 0);
    cout << "Passed" << endl;
    freeList(list15);
    freeList(emptyList15);

    // Test case 16: reverseList
    cout << "Test 16/18 - reverseList: ";
    int arr11[4] = { 480, 490, 500, 510 };
    d_List* list16 = createListFromArray(arr11, 4);
    d_List* reversedList = reverseList(list16);
    assert(reversedList->pHead->key == 510 && reversedList->pTail->key == 480);
    cout << "Passed" << endl;
    freeList(list16);
    freeList(reversedList);

    // Test case 17: removeDuplicate
    cout << "Test 17/18 - removeDuplicate: ";
    int arr12[6] = { 520, 530, 530, 540, 540, 540 };
    d_List* list17 = createListFromArray(arr12, 6);
    removeDuplicate(list17);
    assert(countElements(list17) == 3);
    cout << "Passed" << endl;
    freeList(list17);

    // Test case 18: removeElement
    cout << "Test 18/18 - removeElement: ";
    int arr13[5] = { 550, 560, 570, 560, 580 };
    d_List* list18 = createListFromArray(arr13, 5);
    assert(removeElement(list18, 560));
    assert(countElements(list18) == 3);
    assert(!removeElement(list18, 999));
    cout << "Passed" << endl;
    freeList(list18);

    cout << "--- The end " << endl;
    return 0;
}