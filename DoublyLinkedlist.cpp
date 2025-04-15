


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
void removePos(d_List*& L, int data, int pos) {
    if (!L || !L->pHead || pos < 0) return;

    d_NODE* current = L->pHead;
    int count = 0;

    // Find the node at the specified position
    while (current && count < pos) {
        current = current->pNext;
        count++;
    }

    // If node found at position and data matches
    if (current && current->key == data) {
        if (current == L->pHead) {
            removeHead(L);
        }
        else if (current == L->pTail) {
            removeTail(L);
        }
        else {
            current->pPrev->pNext = current->pNext;
            current->pNext->pPrev = current->pPrev;
            delete current;
        }
    }
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

//d_List* reverseList(d_List* L) {
//    if (!L || !L->pHead) return nullptr;
//
//    d_List* newList = new d_List;
//    newList->pHead = newList->pTail = nullptr;
//    d_NODE* current = L->pHead;
//    while (current) {
//        addHead(newList, current->key);
//        current = current->pNext;
//    }
//    return newList;
//}
//d_List* reverseList(d_List* L) {
//    if (!L || !L->pHead) return nullptr;
//
//    d_List* reversedList = new d_List();
//    reversedList->pHead = nullptr;
//    reversedList->pTail = nullptr;
//
//    d_NODE* current = L->pHead;
//    while (current != nullptr) {
//        addHead(reversedList, current->key);
//        current = current->pNext;
//    }
//
//    return reversedList;
//}
d_List* reverseList(d_List* L) {
    // Kiểm tra null và list rỗng
    if (!L || !L->pHead) {
        d_List* emptyList = new d_List();
        emptyList->pHead = emptyList->pTail = nullptr;
        return emptyList;
    }

    d_List* reversedList = new d_List();
    reversedList->pHead = reversedList->pTail = nullptr;

    d_NODE* current = L->pHead;
    while (current != nullptr) {
        d_NODE* newNode = new d_NODE();
        newNode->key = current->key;
        newNode->pNext = reversedList->pHead;
        newNode->pPrev = nullptr;

        if (reversedList->pHead != nullptr) {
            reversedList->pHead->pPrev = newNode;
        }
        else {
            reversedList->pTail = newNode;
        }

        reversedList->pHead = newNode;
        current = current->pNext;
    }

    return reversedList;
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
    std::cout << "--- Begin running test cases ---" << std::endl;

    // Test case 1: createNode /////////////////////////////////////////////////
    std::cout << "Test createDNode: ";
    d_NODE* node1 = createNode(10);
    assert(node1 != nullptr && node1->key == 10 && node1->pNext == nullptr && node1->pPrev == nullptr);
    std::cout << "Passed" << std::endl;
    delete node1;

    // Test case 2: createList //////////////////////////////////////////////////
    std::cout << "Test createDList: ";
    d_NODE* head2 = createNode(20);
    d_List* list2 = createList(head2);
    assert(list2 != nullptr && list2->pHead == head2 && list2->pTail == head2);
    std::cout << "Passed" << std::endl;
    freeList(list2);

    // Test case 3: addHead //////////////////////////////////////////////////////
    std::cout << "Test addDHead: ";
    d_List* list3 = new d_List();
    assert(addHead(list3, 30));
    assert(list3->pHead != nullptr && list3->pHead->key == 30 && list3->pTail->key == 30);
    assert(addHead(list3, 40));
    assert(list3->pHead->key == 40 && list3->pHead->pNext->key == 30 && list3->pTail->key == 30);
    assert(list3->pHead->pNext->pPrev == list3->pHead); // Check prev pointer
    std::cout << "Passed" << std::endl;
    freeList(list3);

    // Test case 4: addTail /////////////////////////////////////////////////////////
    std::cout << "Test addDTail: ";
    d_List* list4 = new d_List();
    assert(addTail(list4, 50));
    assert(list4->pHead != nullptr && list4->pHead->key == 50 && list4->pTail->key == 50);
    assert(addTail(list4, 60));
    assert(list4->pHead->key == 50 && list4->pTail->key == 60 && list4->pHead->pNext->key == 60);
    assert(list4->pTail->pPrev == list4->pHead); // Check prev pointer
    std::cout << "Passed" << std::endl;
    freeList(list4);

    // Test case 5: removeHead //////////////////////////////////////////////////////////////////
    std::cout << "Test removeDHead: ";
    int arr1[3] = { 70, 80, 90 };
    d_List* list5 = createListFromArray(arr1, 3);
    assert(removeHead(list5) && list5->pHead->key == 80);
    assert(list5->pHead->pPrev == nullptr); // Check prev pointer after removal
    assert(removeHead(list5) && list5->pHead->key == 90);
    assert(removeHead(list5) && list5->pHead == nullptr && list5->pTail == nullptr);
    assert(!removeHead(list5)); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(list5);

    // Test case 6: removeTail ///////////////////////////////////////////////////////////////////
    std::cout << "Test removeDTail: ";
    int arr2[3] = { 100, 110, 120 };
    d_List* list6 = createListFromArray(arr2, 3);
    removeTail(list6);
    assert(list6->pTail->key == 110 && list6->pTail->pNext == nullptr);
    removeTail(list6);
    assert(list6->pTail->key == 100 && list6->pTail->pNext == nullptr && list6->pHead == list6->pTail);
    removeTail(list6);
    assert(list6->pHead == nullptr && list6->pTail == nullptr);
    d_List* emptyList6 = new d_List();
    removeTail(emptyList6); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(emptyList6);
    freeList(list6);

    // Test case 7: removeAll /////////////////////////////////////////////////////////////////////
    std::cout << "Test removeAllD: ";
    int arr3[3] = { 130, 140, 150 };
    d_List* list7 = createListFromArray(arr3, 3);
    removeAll(list7);
    assert(list7->pHead == nullptr && list7->pTail == nullptr);
    d_List* emptyList7 = new d_List();
    removeAll(emptyList7); // Remove from empty list
    assert(emptyList7->pHead == nullptr && emptyList7->pTail == nullptr);
    std::cout << "Passed" << std::endl;
    freeList(emptyList7);
    freeList(list7);

    // Test case 8: removeBefore //////////////////////////////////////////////////////////////////////
    std::cout << "Test removeDBefore: ";
    int arr4[5] = { 160, 170, 180, 190, 200 };
    d_List* list8 = createListFromArray(arr4, 5);

    // testcase 1
    removeBefore(list8, 180);
    int expectedArr8[4] = { 160, 180, 190, 200 };
    d_List* expectedList8 = createListFromArray(expectedArr8, 4);
    assert(areListsEqual(list8, expectedList8));
    assert(list8->pHead->pNext->pPrev == list8->pHead); // Check prev pointer

    // testcase 2
    removeBefore(list8, 200);
    int expectedArr8_2[3] = { 160, 180, 200 };
    d_List* expectedList8_2 = createListFromArray(expectedArr8_2, 3);
    assert(areListsEqual(list8, expectedList8_2));
    assert(list8->pTail->pPrev == list8->pHead->pNext); // Check prev pointer

    // testcase 3
    removeBefore(list8, 170); // Don't have any element before
    int expectedArr8_2_2[3] = { 160, 180, 200 };
    d_List* expectedList8_2_2 = createListFromArray(expectedArr8_2_2, 3);
    assert(areListsEqual(list8, expectedList8_2_2));

    // free memory
    freeList(expectedList8);
    freeList(expectedList8_2);
    freeList(expectedList8_2_2);
    freeList(list8);
    std::cout << "Passed" << std::endl;

    // Test case 9: remove after ////////////////////////////////////////////////////////////
    std::cout << "Test removeDAfter: ";
    int arr5[4] = { 220, 230, 240, 250 };
    d_List* list9 = createListFromArray(arr5, 4);
    // testcase 1
    removeAfter(list9, 220);
    int expectedArr9[3] = { 220, 240, 250 };
    d_List* expectedList9 = createListFromArray(expectedArr9, 3);
    assert(areListsEqual(list9, expectedList9));
    assert(list9->pHead->pNext->pPrev == list9->pHead); // Check prev pointer

    // testcase 2
    removeAfter(list9, 250); // Don't have any element after
    int expectedArr9_2[3] = { 220, 240, 250 };
    d_List* expectedList9_2 = createListFromArray(expectedArr9_2, 3);
    assert(areListsEqual(list9, expectedList9_2));

    // testcase 3
    removeAfter(list9, 240);
    int expectedArr9_3[2] = { 220, 240 };
    d_List* expectedList9_3 = createListFromArray(expectedArr9_3, 2);
    assert(areListsEqual(list9, expectedList9_3));
    assert(list9->pTail->pPrev == list9->pHead); // Check prev pointer

    // testcase 4
    int arr9_single[1] = { 260 };
    d_List* list9_single = createListFromArray(arr9_single, 1);
    removeAfter(list9_single, 260);
    int expectedArr9_single[1] = { 260 };
    d_List* expectedList9_single = createListFromArray(expectedArr9_single, 1);
    assert(areListsEqual(list9_single, expectedList9_single));

    // testcase 5
    d_List* emptyList9 = new d_List();
    removeAfter(emptyList9, 270);
    assert(areListsEqual(emptyList9, new d_List()));

    // free memory
    freeList(expectedList9);
    freeList(expectedList9_2);
    freeList(expectedList9_3);
    freeList(expectedList9_single);
    freeList(list9);
    freeList(list9_single);
    freeList(emptyList9);
    std::cout << "Passed" << std::endl;

    // Test case 10: addPos /////////////////////////////////////////////////////////
    std::cout << "Test addDPos: ";
    d_List* list10 = new d_List();
    assert(addPos(list10, 280, 0));
    assert(list10->pHead != nullptr && list10->pHead->key == 280 && list10->pTail->key == 280);
    assert(addPos(list10, 290, 1));
    assert(list10->pHead->key == 280 && list10->pTail->key == 290 && list10->pHead->pNext->key == 290);
    assert(list10->pTail->pPrev == list10->pHead); // Check prev pointer
    assert(addPos(list10, 300, 1));
    assert(list10->pHead->key == 280 && list10->pTail->key == 290 && list10->pHead->pNext->key == 300);
    assert(list10->pHead->pNext->pNext->key == 290);
    assert(list10->pTail->pPrev == list10->pHead->pNext); // Check prev pointer
    assert(addPos(list10, 310, 3));
    assert(list10->pHead->key == 280 && list10->pTail->key == 310 && list10->pHead->pNext->key == 300);
    assert(list10->pHead->pNext->pNext->key == 290 && list10->pHead->pNext->pNext->pNext->key == 310);
    assert(list10->pTail->pPrev == list10->pHead->pNext->pNext); // Check prev pointer
    assert(!addPos(list10, 320, 5));  // Positions out of range
    assert(!addPos(list10, 330, -1)); // Negative position
    // free memory
    freeList(list10);
    std::cout << "Passed" << std::endl;

    // Test case 11: RemovePos /////////////////////////////////////////////////////////
    std::cout << "Test RemoveDPos: ";
    int arr11[5] = { 340, 350, 360, 370, 380 };
    d_List* list11 = createListFromArray(arr11, 5);
    assert(list11->pHead->key == 340 && list11->pTail->key == 380);
    // testcase 1
    removePos(list11, 340, 0);
    assert(list11->pHead->key == 350 && list11->pTail->key == 380);
    assert(list11->pHead->pPrev == nullptr); // Check prev pointer
    assert(list11->pHead->pNext->key == 360 && list11->pHead->pNext->pNext->key == 370 && list11->pHead->pNext->pNext->pNext->key == 380);
    assert(list11->pHead->pNext->pNext->pNext->pNext == nullptr);
    assert(list11->pHead->pNext->pPrev == list11->pHead); // Check prev pointer

    // testcase 2
    removePos(list11, 370, 2);
    assert(list11->pHead->key == 350 && list11->pTail->key == 380);
    assert(list11->pHead->pNext->key == 360 && list11->pHead->pNext->pNext->key == 380);
    assert(list11->pHead->pNext->pNext->pNext == nullptr);
    assert(list11->pTail->pPrev == list11->pHead->pNext); // Check prev pointer

    // testcase 3
    removePos(list11, 350, 5); // Positions out of range
    assert(list11->pHead->key == 350 && list11->pTail->key == 380);
    assert(list11->pHead->pNext->key == 360 && list11->pHead->pNext->pNext->key == 380);
    assert(list11->pHead->pNext->pNext->pNext == nullptr);

    // free memory
    freeList(list11);
    std::cout << "Passed" << std::endl;

    // Test case 12: addBefore /////////////////////////////////////////////////////////
    std::cout << "Test addDBefore: ";
    int arr12[4] = { 390, 400, 410, 420 };
    d_List* list12 = createListFromArray(arr12, 4);
    assert(list12->pHead->key == 390 && list12->pTail->key == 420);
    // testcase 1
    addBefore(list12, 380, 400);
    int arr12_1[5] = { 390, 380, 400, 410, 420 };
    d_List* expectedList12_1 = createListFromArray(arr12_1, 5);
    assert(areListsEqual(list12, expectedList12_1));
    assert(list12->pHead->pNext->pPrev == list12->pHead); // Check prev pointer
    assert(list12->pHead->pNext->pNext->pPrev == list12->pHead->pNext); // Check prev pointer

    // testcase 2
    addBefore(list12, 370, 390);
    int arr12_2[6] = { 370, 390, 380, 400, 410, 420 };
    d_List* expectedList12_2 = createListFromArray(arr12_2, 6);
    assert(areListsEqual(list12, expectedList12_2));
    assert(list12->pHead->pNext->pPrev == list12->pHead); // Check prev pointer

    // testcase 3
    addBefore(list12, 360, 350); // Don't have any element before
    int arr12_3[6] = { 370, 390, 380, 400, 410, 420 };
    d_List* expectedList12_3 = createListFromArray(arr12_3, 6);
    assert(areListsEqual(list12, expectedList12_3));

    // free memory
    freeList(list12);
    freeList(expectedList12_1);
    freeList(expectedList12_2);
    freeList(expectedList12_3);
    std::cout << "Passed" << std::endl;

    // Test case 13: addAfter /////////////////////////////////////////////////////////
    std::cout << "Test addDAfter: ";
    int arr13[4] = { 430, 440, 450, 460 };
    d_List* list13 = createListFromArray(arr13, 4);
    assert(list13->pHead->key == 430 && list13->pTail->key == 460);
    // testcase 1
    addAfter(list13, 470, 440);
    int arr13_1[5] = { 430, 440, 470, 450, 460 };
    d_List* expectedList13_1 = createListFromArray(arr13_1, 5);
    assert(areListsEqual(list13, expectedList13_1));
    assert(list13->pHead->pNext->pNext->pPrev == list13->pHead->pNext); // Check prev pointer

    // testcase 2
    addAfter(list13, 480, 460);
    int arr13_2[6] = { 430, 440, 470, 450, 460, 480 };
    d_List* expectedList13_2 = createListFromArray(arr13_2, 6);
    assert(areListsEqual(list13, expectedList13_2));
    assert(list13->pTail->pPrev == list13->pTail->pPrev); // Check prev pointer

    // testcase 3
    addAfter(list13, 490, 200); // Don't have any element after
    int arr13_3[6] = { 430, 440, 470, 450, 460, 480 };
    d_List* expectedList13_3 = createListFromArray(arr13_3, 6);
    assert(areListsEqual(list13, expectedList13_3));

    // free memory
    freeList(expectedList13_1);
    freeList(expectedList13_2);
    freeList(expectedList13_3);
    freeList(list13);
    std::cout << "Passed" << std::endl;

    // Test case 14: printList /////////////////////////////////////////////////////////
    std::cout << "Test printDList: "; // Don't need to assert anything
    std::cout << "Passed" << std::endl;

    // Test case 15: countElements /////////////////////////////////////////////////////////
    std::cout << "Test countDElements: ";
    // Test case 1
    int arr15[5] = { 500, 510, 520, 530, 540 };
    d_List* list15 = createListFromArray(arr15, 5);
    assert(countElements(list15) == 5);
    // Test case 2
    int arr15_2[3] = { 550, 560, 570 };
    d_List* list15_2 = createListFromArray(arr15_2, 3);
    assert(countElements(list15_2) == 3);
    // Test case 3
    int arr15_3[1] = { 580 };
    d_List* list15_3 = createListFromArray(arr15_3, 1);
    assert(countElements(list15_3) == 1);
    // Test case 4
    d_List* emptyList15 = new d_List();
    assert(countElements(emptyList15) == 0);
    // free memory
    freeList(list15);
    freeList(list15_2);
    freeList(list15_3);
    freeList(emptyList15);
    std::cout << "Passed" << std::endl;

    // Test case 16: reverseList /////////////////////////////////////////////////////////
    std::cout << "Test reverseDList: ";
    // Test case 1
    int arr16[5] = { 590, 600, 610, 620, 630 };
    d_List* list16 = createListFromArray(arr16, 5);
    d_List* reversedList16 = reverseList(list16);
    int expectedArr16[5] = { 630, 620, 610, 600, 590 };
    d_List* expectedList16 = createListFromArray(expectedArr16, 5);
    assert(areListsEqual(reversedList16, expectedList16));
    // Verify prev pointers
    d_NODE* current = reversedList16->pHead;
    while (current->pNext != nullptr) {
        assert(current->pNext->pPrev == current);
        current = current->pNext;
    }

    // Test case 2
    int arr16_2[3] = { 640, 650, 660 };
    d_List* list16_2 = createListFromArray(arr16_2, 3);
    d_List* reversedList16_2 = reverseList(list16_2);
    int expectedArr16_2[3] = { 660, 650, 640 };
    d_List* expectedList16_2 = createListFromArray(expectedArr16_2, 3);
    assert(areListsEqual(reversedList16_2, expectedList16_2));
    // Verify prev pointers
    current = reversedList16_2->pHead;
    while (current->pNext != nullptr) {
        assert(current->pNext->pPrev == current);
        current = current->pNext;
    }

    // Test case 3
    int arr16_3[1] = { 670 };
    d_List* list16_3 = createListFromArray(arr16_3, 1);
    d_List* reversedList16_3 = reverseList(list16_3);
    int expectedArr16_3[1] = { 670 };
    d_List* expectedList16_3 = createListFromArray(expectedArr16_3, 1);
    assert(areListsEqual(reversedList16_3, expectedList16_3));

    // Test case 4
    d_List* emptyList16 = new d_List();
    d_List* reversedList16_4 = reverseList(emptyList16);
    assert(reversedList16_4->pHead == nullptr && reversedList16_4->pTail == nullptr);

    // free memory
    freeList(expectedList16);
    freeList(expectedList16_2);
    freeList(expectedList16_3);
    freeList(reversedList16);
    freeList(reversedList16_2);
    freeList(reversedList16_3);
    freeList(reversedList16_4);
    freeList(list16);
    freeList(list16_2);
    freeList(list16_3);
    freeList(emptyList16);
    std::cout << "Passed" << std::endl;

    // Test case 17: removeDuplicate /////////////////////////////////////////////////////////
    std::cout << "Test removeDDuplicate: ";
    // Test case 1
    int arr17[6] = { 680, 690, 690, 700, 710, 710 };
    d_List* list17 = createListFromArray(arr17, 6);
    removeDuplicate(list17);
    int expectedArr17[4] = { 680, 690, 700, 710 };
    d_List* expectedList17 = createListFromArray(expectedArr17, 4);
    assert(areListsEqual(list17, expectedList17));
    // Verify prev pointers
    current = list17->pHead;
    while (current->pNext != nullptr) {
        assert(current->pNext->pPrev == current);
        current = current->pNext;
    }

    // Test case 2
    int arr17_2[5] = { 720, 730, 740, 740, 740 };
    d_List* list17_2 = createListFromArray(arr17_2, 5);
    removeDuplicate(list17_2);
    int expectedArr17_2[3] = { 720, 730, 740 };
    d_List* expectedList17_2 = createListFromArray(expectedArr17_2, 3);
    assert(areListsEqual(list17_2, expectedList17_2));

    // Test case 3
    int arr17_3[4] = { 750, 760, 760, 770 };
    d_List* list17_3 = createListFromArray(arr17_3, 4);
    removeDuplicate(list17_3);
    int expectedArr17_3[3] = { 750, 760, 770 };
    d_List* expectedList17_3 = createListFromArray(expectedArr17_3, 3);
    assert(areListsEqual(list17_3, expectedList17_3));

    // Test case 4
    int arr17_4[2] = { 780, 780 };
    d_List* list17_4 = createListFromArray(arr17_4, 2);
    removeDuplicate(list17_4);
    int expectedArr17_4[1] = { 780 };
    d_List* expectedList17_4 = createListFromArray(expectedArr17_4, 1);
    assert(areListsEqual(list17_4, expectedList17_4));

    // Test case 5
    int arr17_5[1] = { 790 };
    d_List* list17_5 = createListFromArray(arr17_5, 1);
    removeDuplicate(list17_5);
    int expectedArr17_5[1] = { 790 };
    d_List* expectedList17_5 = createListFromArray(expectedArr17_5, 1);
    assert(areListsEqual(list17_5, expectedList17_5));

    // Test case 6
    d_List* emptyList17 = new d_List();
    removeDuplicate(emptyList17);
    assert(emptyList17->pHead == nullptr && emptyList17->pTail == nullptr);

    // free memory
    freeList(expectedList17);
    freeList(expectedList17_2);
    freeList(expectedList17_3);
    freeList(expectedList17_4);
    freeList(expectedList17_5);
    freeList(list17);
    freeList(list17_2);
    freeList(list17_3);
    freeList(list17_4);
    freeList(list17_5);
    freeList(emptyList17);
    std::cout << "Passed" << std::endl;

    // Test case 18: removeElement /////////////////////////////////////////////////////////
    std::cout << "Test removeDElement: ";
    // Test case 1
    int arr18[5] = { 800, 810, 820, 830, 840 };
    d_List* list18 = createListFromArray(arr18, 5);
    assert(removeElement(list18, 820));
    int expectedArr18[4] = { 800, 810, 830, 840 };
    d_List* expectedList18 = createListFromArray(expectedArr18, 4);
    assert(areListsEqual(list18, expectedList18));
    assert(list18->pHead->pNext->pNext->pPrev == list18->pHead->pNext); // Check prev pointer

    // Test case 2
    int arr18_2[3] = { 850, 860, 870 };
    d_List* list18_2 = createListFromArray(arr18_2, 3);
    assert(removeElement(list18_2, 850));
    int expectedArr18_2[2] = { 860, 870 };
    d_List* expectedList18_2 = createListFromArray(expectedArr18_2, 2);
    assert(areListsEqual(list18_2, expectedList18_2));
    assert(list18_2->pHead->pPrev == nullptr); // Check prev pointer

    // Test case 3
    int arr18_3[4] = { 880, 890, 900, 910 };
    d_List* list18_3 = createListFromArray(arr18_3, 4);
    assert(removeElement(list18_3, 910));
    int expectedArr18_3[3] = { 880, 890, 900 };
    d_List* expectedList18_3 = createListFromArray(expectedArr18_3, 3);
    assert(areListsEqual(list18_3, expectedList18_3));
    assert(list18_3->pTail->pNext == nullptr); // Check next pointer

    // Test case 4
    int arr18_4[2] = { 920, 930 };
    d_List* list18_4 = createListFromArray(arr18_4, 2);
    assert(removeElement(list18_4, 920));
    int expectedArr18_4[1] = { 930 };
    d_List* expectedList18_4 = createListFromArray(expectedArr18_4, 1);
    assert(areListsEqual(list18_4, expectedList18_4));

    // Test case 5
    int arr18_5[1] = { 940 };
    d_List* list18_5 = createListFromArray(arr18_5, 1);
    assert(removeElement(list18_5, 940));

    // Test case 6
    d_List* emptyList18 = new d_List();
    assert(!removeElement(emptyList18, 950)); // Remove from empty list
    assert(emptyList18->pHead == nullptr && emptyList18->pTail == nullptr);

    // free memory
    freeList(expectedList18);
    freeList(expectedList18_2);
    freeList(expectedList18_3);
    freeList(expectedList18_4);
    freeList(list18);
    freeList(list18_2);
    freeList(list18_3);
    freeList(list18_4);
    freeList(list18_5);
    freeList(emptyList18);
    std::cout << "Passed" << std::endl;

    std::cout << "--- End running test cases ---" << std::endl;

    return 0;
}
