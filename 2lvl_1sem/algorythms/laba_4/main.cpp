#include <iostream>
#include <iomanip>  // Для таблицы (setw)
#include <cstdlib>  // rand, srand
#include <ctime>    // time

using namespace std;

// =========================================================
// СТРУКТУРЫ ДАННЫХ
// =========================================================

// Узел обычного Бинарного Дерева Поиска (BST)
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(NULL), right(NULL) {}
};

// Узел Рандомизированного дерева (Treap)
struct TreapNode {
    int key;
    int priority;
    TreapNode* left;
    TreapNode* right;

    TreapNode(int k) : key(k), left(NULL), right(NULL) {
        priority = rand();
    }
};

// =========================================================
// ВСПОМОГАТЕЛЬНЫЕ ИНСТРУМЕНТЫ (Без STL)
// =========================================================

// Проверка на уникальность
bool isUnique(int* arr, int n, int val) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == val) return false;
    }
    return true;
}

// Сортировка пузырьком
void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Генерация уникального массива
void generateUniqueArray(int* arr, int n, int minVal, int maxVal) {
    int count = 0;
    while (count < n) {
        int val = minVal + rand() % (maxVal - minVal + 1);
        if (isUnique(arr, count, val)) {
            arr[count] = val;
            count++;
        }
    }
}

// =========================================================
// ОСНОВНЫЕ ФУНКЦИИ BST
// =========================================================

// Вставка
void insert(Node*& root, int key) {
    if (root == NULL) {
        root = new Node(key);
        return;
    }
    if (key < root->key)
        insert(root->left, key);
    else if (key > root->key)
        insert(root->right, key);
}

// Поиск
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

// Поиск минимума
Node* findMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

// Удаление узла
void deleteNode(Node*& root, int key) {
    if (root == NULL) return;

    if (key < root->key) {
        deleteNode(root->left, key);
    } else if (key > root->key) {
        deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            root = temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            root = temp;
        } else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            deleteNode(root->right, temp->key);
        }
    }
}

// Высота
int getHeight(Node* root) {
    if (root == NULL) return 0;
    int hL = getHeight(root->left);
    int hR = getHeight(root->right);
    return 1 + (hL > hR ? hL : hR);
}

// Количество узлов
int getCount(Node* root) {
    if (root == NULL) return 0;
    return 1 + getCount(root->left) + getCount(root->right);
}

// --- НОВЫЙ ВЫВОД (ВЕРТИКАЛЬНЫЙ) ---
// Корень сверху, дети снизу с отступами
void printTree(Node* root, int level = 0, const char* type = "ROOT") {
    if (root == NULL) return;

    // Делаем отступ
    for (int i = 0; i < level; i++) cout << "    ";

    // Печатаем узел
    if (level == 0)
        cout << "[" << type << "] " << root->key << endl;
    else
        cout << "|__" << type << ": " << root->key << endl;

    // Рекурсивно выводим детей (сначала левого, потом правого)
    printTree(root->left, level + 1, "L");
    printTree(root->right, level + 1, "R");
}

// Сортированный вывод
void printSorted(Node* root) {
    if (root == NULL) return;
    printSorted(root->left);
    cout << root->key << " ";
    printSorted(root->right);
}

// Очистка памяти
void deleteTree(Node*& root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = NULL;
}

// ВАРИАНТ 4: Сумма четных в листьях
void sumEvenLeaves(Node* root, int& sum) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        if (root->key % 2 == 0) sum += root->key;
    }
    sumEvenLeaves(root->left, sum);
    sumEvenLeaves(root->right, sum);
}

// =========================================================
// ФУНКЦИИ TREAP
// =========================================================

void split(TreapNode* t, int key, TreapNode*& l, TreapNode*& r) {
    if (!t) l = r = NULL;
    else if (key < t->key) split(t->left, key, l, t->left), r = t;
    else split(t->right, key, t->right, r), l = t;
}

void merge(TreapNode*& t, TreapNode* l, TreapNode* r) {
    if (!l || !r) t = l ? l : r;
    else if (l->priority > r->priority) merge(l->right, l->right, r), t = l;
    else merge(r->left, l, r->left), t = r;
}

void insertTreap(TreapNode*& t, TreapNode* it) {
    if (!t) t = it;
    else if (it->priority > t->priority) split(t, it->key, it->left, it->right), t = it;
    else insertTreap(it->key < t->key ? t->left : t->right, it);
}

int getTreapHeight(TreapNode* t) {
    if (!t) return 0;
    int hL = getTreapHeight(t->left);
    int hR = getTreapHeight(t->right);
    return 1 + (hL > hR ? hL : hR);
}

void deleteTreap(TreapNode*& t) {
    if (!t) return;
    deleteTreap(t->left);
    deleteTreap(t->right);
    delete t;
    t = NULL;
}

// =========================================================
// MAIN
// =========================================================

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    // --- ЭТАП 1 ---
    cout << "=== ЭТАП 1: Проверка BST ===" << endl;
    
    int n1 = 20;
    int* arr1 = new int[n1];
    generateUniqueArray(arr1, n1, 0, 100);

    Node* root = NULL;
    cout << "Ключи: ";
    for (int i = 0; i < n1; i++) {
        cout << arr1[i] << " ";
        insert(root, arr1[i]);
    }
    cout << endl << endl;

    cout << "Структура дерева:" << endl;
    printTree(root);
    cout << "---------------------------------" << endl;

    cout << "Высота: " << getHeight(root) << endl;
    cout << "Узлов: " << getCount(root) << endl;

    cout << "Сортировка: ";
    printSorted(root);
    cout << endl;

    int sum = 0;
    sumEvenLeaves(root, sum);
    cout << "[Вар. 4] Сумма четных листьев: " << sum << endl;

    int keyDel = arr1[0];
    cout << "\nУдаляем узел " << keyDel << "..." << endl;
    deleteNode(root, keyDel);
    
    cout << "Структура после удаления:" << endl;
    printTree(root);
    
    deleteTree(root);
    delete[] arr1;
    cout << endl;

    // --- ЭТАП 2 ---
    cout << "=== ЭТАП 2: Сравнение высот ===" << endl;
    cout << left << setw(8) << "N" 
         << " | " << setw(15) << "Rand BST" 
         << " | " << setw(15) << "Rand Treap" 
         << " | " << setw(15) << "Sort BST" 
         << " | " << setw(15) << "Sort Treap" << endl;
    cout << string(80, '-') << endl;

    for (int n = 25; n <= 300; n += 25) {
        int* randKeys = new int[n];
        int* sortedKeys = new int[n];

        generateUniqueArray(randKeys, n, 0, 10000);
        for(int i=0; i<n; i++) sortedKeys[i] = randKeys[i];
        bubbleSort(sortedKeys, n);

        Node* bstRand = NULL;
        TreapNode* treapRand = NULL;
        for (int i = 0; i < n; i++) {
            insert(bstRand, randKeys[i]);
            insertTreap(treapRand, new TreapNode(randKeys[i]));
        }
        int h_bst_r = getHeight(bstRand);
        int h_treap_r = getTreapHeight(treapRand);
        deleteTree(bstRand);
        deleteTreap(treapRand);

        Node* bstSort = NULL;
        TreapNode* treapSort = NULL;
        for (int i = 0; i < n; i++) {
            insert(bstSort, sortedKeys[i]);
            insertTreap(treapSort, new TreapNode(sortedKeys[i]));
        }
        int h_bst_s = getHeight(bstSort);
        int h_treap_s = getTreapHeight(treapSort);
        deleteTree(bstSort);
        deleteTreap(treapSort);

        cout << left << setw(8) << n 
             << " | " << setw(15) << h_bst_r 
             << " | " << setw(15) << h_treap_r 
             << " | " << setw(15) << h_bst_s 
             << " | " << setw(15) << h_treap_s << endl;

        delete[] randKeys;
        delete[] sortedKeys;
    }

    return 0;
}
