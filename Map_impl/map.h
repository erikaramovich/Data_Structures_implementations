#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>

template <class Key, class Value> class Map {
private:
  struct Node {
    Node *left;
    Node *right;
    Node *parent;
    std::pair<Key, Value> data;

    Node(Node *left = nullptr, Node *right = nullptr, Node *parent = nullptr)
        : left(left), right(right), parent(parent) {}
  };

  Node *root = nullptr;
  std::size_t map_size = 0;

  void private_clear(Node *node) {
    if (node == nullptr) {
      return;
    }

    private_clear(node->left);
    private_clear(node->right);
    delete node;
  }

  void copy(Node *from_node, Node *to_node) {
    Node *tmp = from_node;

    to_node->data = from_node->data;

    if (from_node->left) {
      to_node->left = new Node(nullptr, nullptr, to_node);
      copy(from_node->left, to_node->left);
    }
    if (from_node->right) {
      to_node->right = new Node(nullptr, nullptr, to_node);
      copy(from_node->right, to_node->right);
    }
  }

  Node* find(const Key &key) {
    Node *cur = root;

    while (cur) {

      if (key > cur->data.first) {
        cur = cur->right;
      }

      else if (key < cur->data.first) {
        cur = cur->left;
      }

      else {
        return cur;
      }
    }

    return nullptr;
  }

  // for const objects
  Node* find(const Key &key)const {
    Node *cur = root;

    while (cur) {

      if (key > cur->data.first) {
        cur = cur->right;
      }

      else if (key < cur->data.first) {
        cur = cur->left;
      }

      else {
        return cur;
      }
    }

    return nullptr;
  }


  Node* FindPossibleParent(const Key &key, Node* node){
    if(node == nullptr){
      return nullptr;
    }

    if(key < node->data.first && node->left == nullptr){
      return node;
    }

    if(key > node->data.first && node->right == nullptr){
      return node;
    }

    if(key < node->data.first && node->left){
      return FindPossibleParent(key, node->left);
    }

    if(key > node->data.first && node->right){
      return FindPossibleParent(key, node->right);
    }

    return nullptr;
  }

public:
  class Iterator;
  class ConstIterator;

  // Создает пустой словарь
  Map() : root(nullptr), map_size(0) {}

  // Создает новый словарь, являющийся глубокой копией other [O(n)]
  //  Map<std::string, int> map;
  //  map["something"] = 69;
  //  map["anything"] = 199;
  //  Map<std::string, int> copied{map};
  //  copied["something"] == map["something"] == 69
  Map(const Map &other) {
    if (other.root != nullptr) {
      root = new Node{};
      copy(other.root, root);
      map_size = other.map_size;
    } else {
      root = other.root;
    }
  }

  // Move конструктор
  Map(Map &&other) {
    std::swap(other.root, root);
    std::swap(other.map_size, map_size);
  }

  // Перезаписывает текущий словарь словарем other
  Map &operator=(const Map &other) {
    Map curent{other};
    std::swap(curent.root, root);
    std::swap(curent.map_size, map_size);

    return *this;
  }

  // Присвоивание перемещением
  Map &operator=(Map &&other) {
    Map curent{std::move(other)};
    std::swap(curent.root, root);
    std::swap(curent.map_size, map_size);

    return *this;
  }

  // Очищает память словаря
  ~Map() { clear(); }

  // Возвращает итератор на первый элемент
  Iterator begin() {
    if (root != nullptr) {
      Node *cur = root;
      while (cur->left)
        ;
      { cur = cur->left; }
      return Iterator(cur);
    }

    return Iterator(nullptr);
  }

  // Возвращает const итератор на первый элемент
  ConstIterator begin() const {
    if (root != nullptr) {
      Node *cur = root;
      while (cur->left)
        ;
      { cur = cur->left; }
      return ConstIterator(cur);
    }

    return ConstIterator(nullptr);
  }

  // Возвращает итератор обозначающий конец контейнера
  Iterator end() { return Iterator(nullptr); }

  // Возвращает const итератор обозначающий конец контейнера
  ConstIterator end() const { return ConstIterator(nullptr); }

  // Возвращает размер словаря (сколько есть узлов)
  std::size_t size() const { return map_size; }

  // Проверяет есть ли элемент с таким ключом в контейнере
  bool contains(const Key &key) const { return find(key) != nullptr; }

  // Возвращает элемент по ключу. Если в словаре нет элемента с таким ключом, то
  // бросает исключение std::out_of_range
  const Value &operator[](const Key &key) const {
    Node *our_key = find(key);
    if (our_key) {
      return our_key->data.second;
    }

    throw std::out_of_range("The key doesn't exist!\n");
  }

  // Возвращает ссылку на элемент по ключу (позволяет менять элемент). Если в
  // словаре нет элемента с таким ключем, то создает его и устанавливает
  // дефолтное значение, после чего возвращает на него ссылку. map["something"]
  // = 75;
  Value &operator[](const Key &key)
  {
    if(root == nullptr)
    {
      Node* tmp = new Node{};
      tmp->data.first = key;
      tmp->data.second = Value{};
      root = tmp;
      map_size++;
      return root->data.second;
    }

    Node* tmp = find(key);
    if(tmp)
    {
      return tmp->data.second;
    }

    Node* pos_parent = FindPossibleParent(key, root);
    if(pos_parent)
    {
      Node* node = new Node{nullptr, nullptr, pos_parent};
      node->data.first = key;
      node->data.second = Value{};
      map_size++;

      if(key > pos_parent->data.first)
      {
        pos_parent->right = node;
      }
      else //key < pos_parent->data.first
      {
        pos_parent->left = node;
      }

      return node->data.second;
      
    }

    
  }





  // Удаляет элемент по ключу и возвращает значение удаленного элемента
  // Map<int, std::string> c =
  //   {
  //       {1, "one" }, {2, "two" }, {3, "three"},
  //       {4, "four"}, {5, "five"}, {6, "six"  }
  //   };
  // c.erase(4) == true
  // c =
  //   {
  //       {1, "one" }, {2, "two" }, {3, "three"},
  //             {5, "five"}, {6,"six"  }
  //   }; результат после erase

  bool erase(const Key &key) {
    Node *tmp = find(key);

    if (!tmp) {
      return false;
    }

    // case 1
    if (tmp->parent && !tmp->right && !tmp->left) {
      if (tmp->data.first < tmp->parent->data.first) {
        tmp->parent->left = nullptr;
      } else {
        tmp->parent->right = nullptr;
      }
    } else {
      root = nullptr;
    }

    // case 2.right
    if (tmp->right && !tmp->left) {
      if (tmp->parent)
      {
        if (tmp->data.first < tmp->parent->data.first) {
          tmp->parent->left = tmp->right;
        } else {
          tmp->parent->right = tmp->right;
        }
        
      }
      else {
        root = tmp->right;
      }

      tmp->right->parent = tmp->parent;
    }

    //case 2.left
    // write the same for the left side
    if(tmp->left && !tmp->right)
    {
      if(tmp->parent)
      {
        if (tmp->data.first < tmp->parent->data.first) {
          tmp->parent->left = tmp->left;
        } else {
          tmp->parent->right = tmp->left;
        }
      }
      else {
        root = tmp->left;
      }

      tmp->left->parent = tmp->parent;
    }

    
    // case 3 when exists 2
    if(tmp->left && tmp->right)
    {
      // Finding successor
      Node* successor = tmp;
      successor = successor->right;
      while(successor->left)
      {
        successor = successor->left;
      }
      //successor was found !

      std::swap(tmp->data, successor->data);

      if(successor->right)
      {
        successor->parent->left = successor->right;
        successor->right->parent = successor->parent;
      }

    }
     
    map_size--;
    delete tmp;
    return true;
  }

  // Меняет текуший контейнер с контейнером other
  void swap(Map &other) {
    std::swap(other.root, root);
    std::swap(other.map_size, map_size);
  }

  // Возвращает итератор на первый элемент который не меньше чем переданный
  // ключ. [O(h)]
  Iterator lower_bound(const Key &key)
  {
    Node* tmp = find(key);
    if(tmp)
    {
      Iterator it(tmp);
      return it;
    }
    else
    {
      Node* pos_parent = FindPossibleParent(key, root);
      if(pos_parent->data.first > key)
      {
        Iterator it(pos_parent);
        return it;
      }
      else if(pos_parent->data.first < key && pos_parent->right)
      {
        Iterator it(pos_parent);
        ++it;
        return it;
      }
    }
    
  }

  // Очищает контейнер [O(n)]
  // Map<int, std::string> c =
  //   {
  //       {1, "one" }, {2, "two" }, {3, "three"},
  //       {4, "four"}, {5, "five"}, {6, "six"  }
  //   };
  // c.clear;
  // c.size() == 0 //true;
  void clear() {
    private_clear(root);
    root = nullptr;
    map_size = 0;
  }

  class Iterator {
  private:
    Node *node;

  public:
    // Заполнить:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Key;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    Iterator(Node *arg = nullptr) : node(arg) {}

    // Инкремент. Движение к следующему элементу.
    Iterator &operator++() {
      if (node->right == nullptr) {
        while (node->parent && node->parent->data.first > node->data.first) {
          node = node->parent;
        }
        node = node->parent;
      } else {
        node = node->right;
        while (node->left) {
          node = node->left;
        }
      }

      return *this;
    }

    // Декремент. Движение к предыдущему элементу.
    Iterator &operator--() {
      if (node->left == nullptr) {
        while (node->parent && node->parent->data.first < node->data.first) {
          node = node->parent;
        }
        node = node->parent;
      } else {
        node = node->left;
        while (node->right) {
          node = node->right;
        }
      }

      return *this;
    }

    // Проверка на неравенство двух итераторов.
    bool operator!=(const Iterator &other) { return node != other.node; }

    bool operator==(const Iterator &other) { return node == other.node; }

    // Разыменовывает указатель: std::cout << it->second;
    std::pair<Key, Value> *operator->() {
      return &node->data;
    }

    // Возвращает значение итератора: *it = {"travel", 42};
    std::pair<Key, Value> &operator*() { 
      return node->data; 
    }

  };

  class ConstIterator {
    Iterator it;

  public:
    // Заполнить
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Key;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    ConstIterator(Node *node) : it(node) {}

    ConstIterator &operator++() { ++it; }

    ConstIterator &operator--() { --it; }

    bool operator!=(const ConstIterator &other) { return it != other.it; }

    bool operator==(const ConstIterator &other) { return it == other.it; }

    // единственное отличие от Iterator, что возвращает константную ссылку
    const std::pair<Key, Value> &operator*() { return *it; }

    const std::pair<Key, Value> *operator->() { return &(*it); }
  };
};
