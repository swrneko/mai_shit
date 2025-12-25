#include <iostream>
#include <iomanip>  // Нужно для красивого вывода таблицы (setw)
#include <cstdlib>  // Для генератора чисел (rand) и работы с памятью
#include <ctime>    // Чтобы рандом был разным при каждом запуске

using namespace std;

// =========================================================
// СТРУКТУРЫ ДАННЫХ
// =========================================================

// Узел обычного Бинарного Дерева Поиска (BST)
struct Node {
    int key;      // Само число
    Node* left;   // Указатель на левого потомка (меньше)
    Node* right;  // Указатель на правого потомка (больше)

    // Конструктор для удобного создания узла
    Node(int k) : key(k), left(NULL), right(NULL) {}
};

// Узел Рандомизированного дерева (Treap - Декартово дерево)
struct TreapNode {
    int key;      // Ключ для поиска (как в обычном дереве)
    int priority; // Случайный приоритет (как в куче)
    TreapNode* left;
    TreapNode* right;

    TreapNode(int k) : key(k), left(NULL), right(NULL) {
        priority = rand(); // Приоритет генерируется случайно при создании!
    }
};

// =========================================================
// ВСПОМОГАТЕЛЬНЫЕ ИНСТРУМЕНТЫ
// =========================================================

// Проверяем, есть ли число в массиве (чтобы не было повторов)
bool isUnique(int* arr, int n, int val) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == val) return false;
    }
    return true;
}

// Сортировка пузырьком (написали сами, т.к. std::sort использовать нельзя)
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

// Заполняем массив случайными УНИКАЛЬНЫМИ числами
void generateUniqueArray(int* arr, int n, int minVal, int maxVal) {
    int count = 0;
    while (count < n) {
        int val = minVal + rand() % (maxVal - minVal + 1);
        // Если такого числа еще нет - добавляем
        if (isUnique(arr, count, val)) {
            arr[count] = val;
            count++;
        }
    }
}

// =========================================================
// ОСНОВНЫЕ ФУНКЦИИ BST (Обычное дерево)
// =========================================================

// Рекурсивная вставка элемента
void insert(Node*& root, int key) {
    if (root == NULL) {
        root = new Node(key); // Если дошли до пустого места - вставляем сюда
        return;
    }
    if (key < root->key)
        insert(root->left, key); // Меньше - идем влево
    else if (key > root->key)
        insert(root->right, key); // Больше - идем вправо
}

// Поиск элемента (стандартный алгоритм)
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

// Поиск минимального узла (нужен для удаления)
// Идем всегда влево до упора
Node* findMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

// Удаление узла (самая сложная часть в BST)
void deleteNode(Node*& root, int key) {
    if (root == NULL) return;

    // Сначала ищем узел
    if (key < root->key) {
        deleteNode(root->left, key);
    } else if (key > root->key) {
        deleteNode(root->right, key);
    } else {
        // Узел найден! Рассматриваем 3 случая:
        
        // Случай 1 и 2: Нет детей или только один ребенок
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            root = temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            root = temp;
        } else {
            // Случай 3: Есть оба ребенка
            // Ищем преемника (самый маленький в ПРАВОМ поддереве)
            Node* temp = findMin(root->right);
            root->key = temp->key; // Копируем данные преемника сюда
            deleteNode(root->right, temp->key); // Удаляем старый узел преемника
        }
    }
}

// Считаем высоту дерева (максимальная глубина)
int getHeight(Node* root) {
    if (root == NULL) return 0;
    int hL = getHeight(root->left);
    int hR = getHeight(root->right);
    return 1 + (hL > hR ? hL : hR); // +1 за текущий уровень
}

// Считаем общее количество узлов
int getCount(Node* root) {
    if (root == NULL) return 0;
    return 1 + getCount(root->left) + getCount(root->right);
}

// Вывод дерева "лесенкой" (иерархический вид)
// Корень сверху, дети снизу с отступами
void printTree(Node* root, int level = 0, const char* type = "ROOT") {
    if (root == NULL) return;

    // Делаем отступ пропорционально уровню вложенности
    for (int i = 0; i < level; i++) cout << "    ";

    // Печатаем сам узел
    if (level == 0)
        cout << "[" << type << "] " << root->key << endl;
    else
        cout << "|__" << type << ": " << root->key << endl;

    // Рекурсивно выводим левое и правое поддерево
    printTree(root->left, level + 1, "L");
    printTree(root->right, level + 1, "R");
}

// Симметричный обход (In-order) - выводит отсортированный список
void printSorted(Node* root) {
    if (root == NULL) return;
    printSorted(root->left);
    cout << root->key << " ";
    printSorted(root->right);
}

// Удаление всего дерева (очистка памяти через Post-order)
void deleteTree(Node*& root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root; // Удаляем узел только после удаления его детей
    root = NULL;
}

// ЗАДАНИЕ ВАРИАНТА 4: Сумма четных чисел в ЛИСТЬЯХ
void sumEvenLeaves(Node* root, int& sum) {
    if (root == NULL) return;
    
    // Проверка: является ли узел листом (нет детей)
    if (root->left == NULL && root->right == NULL) {
        // Проверка на четность
        if (root->key % 2 == 0) sum += root->key;
    }
    
    // Идем дальше искать листья
    sumEvenLeaves(root->left, sum);
    sumEvenLeaves(root->right, sum);
}

// =========================================================
// ФУНКЦИИ TREAP (Декартово дерево)
// =========================================================

// Разрезание дерева на два: l (ключи <= key) и r (ключи > key)
void split(TreapNode* t, int key, TreapNode*& l, TreapNode*& r) {
    if (!t)
        l = r = NULL;
    else if (key < t->key)
        // Если ключ меньше текущего, режем левое поддерево
        split(t->left, key, l, t->left), r = t;
    else
        // Иначе режем правое
        split(t->right, key, t->right, r), l = t;
}

// Слияние двух деревьев в одно (по приоритетам)
void merge(TreapNode*& t, TreapNode* l, TreapNode* r) {
    if (!l || !r)
        t = l ? l : r; // Если одно пустое, берем другое
    else if (l->priority > r->priority)
        // Если приоритет левого выше, оно становится корнем
        merge(l->right, l->right, r), t = l;
    else
        merge(r->left, l, r->left), t = r;
}

// Вставка в Treap
void insertTreap(TreapNode*& t, TreapNode* it) {
    if (!t)
        t = it;
    else if (it->priority > t->priority)
        // Если приоритет нового выше текущего -> он должен стать корнем
        // Разрезаем текущее дерево и ставим новый узел между кусками
        split(t, it->key, it->left, it->right), t = it;
    else
        // Иначе спускаемся ниже по правилам BST
        insertTreap(it->key < t->key ? t->left : t->right, it);
}

// Высота Treap (аналогично обычному)
int getTreapHeight(TreapNode* t) {
    if (!t) return 0;
    int hL = getTreapHeight(t->left);
    int hR = getTreapHeight(t->right);
    return 1 + (hL > hR ? hL : hR);
}

// Очистка памяти для Treap
void deleteTreap(TreapNode*& t) {
    if (!t) return;
    deleteTreap(t->left);
    deleteTreap(t->right);
    delete t;
    t = NULL;
}

// =========================================================
// MAIN (Основная программа)
// =========================================================

int main() {
    setlocale(LC_ALL, "Russian"); // Русский язык в консоли
    srand(time(0)); // Инициализация рандома временем

    // --- ЭТАП 1: Демонстрация работы на малых данных ---
    cout << "=== ЭТАП 1: Проверка BST ===" << endl;
    
    int n1 = 20;
    int* arr1 = new int[n1]; // Динамический массив
    generateUniqueArray(arr1, n1, 0, 100); // 20 чисел от 0 до 100

    Node* root = NULL;
    cout << "Ключи: ";
    for (int i = 0; i < n1; i++) {
        cout << arr1[i] << " ";
        insert(root, arr1[i]); // Строим дерево
    }
    cout << endl << endl;

    cout << "Структура дерева:" << endl;
    printTree(root);
    cout << "---------------------------------" << endl;

    cout << "Высота: " << getHeight(root) << endl;
    cout << "Узлов: " << getCount(root) << endl;

    cout << "Сортировка (симметричный обход): ";
    printSorted(root);
    cout << endl;

    // Выполнение задания варианта
    int sum = 0;
    sumEvenLeaves(root, sum);
    cout << "Сумма четных листьев: " << sum << endl;

    // Тест удаления (удаляем первый элемент массива, он часто корень)
    int keyDel = arr1[0];
    cout << "\nУдаляем узел " << keyDel << "..." << endl;
    deleteNode(root, keyDel);
    
    cout << "Структура после удаления:" << endl;
    printTree(root);
    
    deleteTree(root); // Чистим память дерева
    delete[] arr1;    // Чистим память массива
    cout << endl;

    // --- ЭТАП 2: Сравнение эффективности ---
    cout << "=== ЭТАП 2: Сравнение высот ===" << endl;
    // Заголовок таблицы
    cout << left << setw(8) << "N" 
         << " | " << setw(15) << "Rand BST" 
         << " | " << setw(15) << "Rand Treap" 
         << " | " << setw(15) << "Sort BST" 
         << " | " << setw(15) << "Sort Treap" << endl;
    cout << string(80, '-') << endl;

    // Цикл от 25 до 300 с шагом 25
    for (int n = 25; n <= 300; n += 25) {
        int* randKeys = new int[n];
        int* sortedKeys = new int[n];

        // Генерируем случайные данные
        generateUniqueArray(randKeys, n, 0, 10000);
        
        // Создаем отсортированную копию
        for(int i=0; i<n; i++) sortedKeys[i] = randKeys[i];
        bubbleSort(sortedKeys, n);

        // 1. Строим деревья на СЛУЧАЙНЫХ данных
        Node* bstRand = NULL;
        TreapNode* treapRand = NULL;
        for (int i = 0; i < n; i++) {
            insert(bstRand, randKeys[i]);
            insertTreap(treapRand, new TreapNode(randKeys[i]));
        }
        // Замеряем высоту
        int h_bst_r = getHeight(bstRand);
        int h_treap_r = getTreapHeight(treapRand);
        
        deleteTree(bstRand);
        deleteTreap(treapRand);

        // 2. Строим деревья на ОТСОРТИРОВАННЫХ данных (Худший случай для BST)
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

        // Выводим результаты в таблицу
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
