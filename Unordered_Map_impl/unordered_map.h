#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <list>


template <class Key, class Value> class UnorderedMap {

private:
  using ValueType = std::pair<Key, Value>;
  std::vector<std::list<ValueType>> data;
  size_t map_size;

  size_t hash_f(const Key& key) const
  {
    return std::hash<Key>{}(key) % data.size();
  }

  void check_colisium()
  {
    if(map_size >= 4 * data.size())
    {
      rehashing();
    }
  }


  void rehashing()
  {
    int old_size = data.size();
    
    // data.resize(old_size * 2);
    
    // for(int i = 0; i < old_size; ++i)
    // {
    //   for(auto it = data[i].begin(); it != data[i].end(); )
    //   {
    //     int index = hash_f((*it).first);
        
    //     if(index >= old_size)
    //     {
    //       data[old_size + i].push_back(*it);
    //       it = data[i].erase(it);
    //     }
    //     else
    //     {
    //       ++it;
    //     }
        
    //   }
      
    // }

    
    std::vector<std::list<ValueType>> new_data(old_size * 2);

    size_t new_index{};
    
    for(int i = 0; i < old_size; ++i)
    {
      for(auto it = data[i].begin(); it != data[i].end(); ++it)
      {
        auto key = (*it).first;
        new_index = std::hash<Key>{}(key) % new_data.size();

        new_data[new_index].push_back(*it); // *it --> std::pair<K,V> 
        //new_data[index] is list --> .push_back(*it),adding in list
      }
      
    }

    data = std::move(new_data);

    // for(auto it = data.begin(); it != data.end(); ++it)
    // {
    //     std::cout << (*it).first << std::endl;
    // }

    
  }

  
public:
  class Iterator;
  class ConstIterator;
  // Создает пустой словарь
  UnorderedMap(size_t vec_size = 7): data(vec_size) , map_size(0) {}

  // Создает новый UnorderedMap, являющийся глубокой копией other [O(n)]
  // UnorderedMap<std::string, int>  map;
  // map["something"] = 69;
  // map["anything"] = 199;
  // UnorderedMap<std::string, int> copied{map};
  // copied["something"] == map["something"] == 69
  UnorderedMap(const UnorderedMap &other) = default;

  // Конструктор перемещения
  UnorderedMap(UnorderedMap &&other)
  {
    std::swap(data, other.data);
    std::swap(map_size, other.map_size); 
    other.data.clear();
    other.map_size = 0;
  }

  // Перезаписывает текущий словарь словарем other
  UnorderedMap &operator=(const UnorderedMap &other) = default;

  // Присваивание перемещением
  UnorderedMap &operator=(UnorderedMap &&other)
  {
    UnorderedMap new_map{std::move(other)};
    std::swap(data, new_map.data);
    std::swap(map_size, new_map.map_size);

    return *this;
  }

  ~UnorderedMap() = default;

  // Возвращает итератор на первый элемент
  Iterator begin()
  {
    auto start = data.begin();
    while((*start).empty())
    {
      ++start;
    }
    return Iterator((*start).begin(), start, data);
  }

  // Возвращает константный итератор на первый элемент
  ConstIterator begin() const
  {
    UnorderedMap* no_const = const_cast<UnorderedMap*>(this);
    return ConstIterator(no_const->begin());
  }

  // Возвращает итератор обозначающий конец контейнера (за последним элементом)
  Iterator end()
  {
    auto start = data.begin();
    start += data.size() - 1;
    return Iterator((*start).end(), start, data);
  }

  // Возвращает константный итератор, обозначающий конец контейнера
  ConstIterator end() const
  {
    UnorderedMap* no_const = const_cast<UnorderedMap*>(this);
    return ConstIterator(no_const->end());
  }

  // Возвращает размер UnorderedMap (сколько элементов добавлено)
  std::size_t size() const
  {
    return map_size;
  }

  // Проверяет является ли UnorderedMap пустым
  bool empty() const
  {
    return map_size == 0;
  }

  // Возвращает элемент по ключу. Если отсутсвует, выбрасывает исключение
  const Value &operator[](const Key& key) const
  {
    // for(const auto& list: data[hash_f(key)])
    // {
    //   if(list.first  == key)
    //   {
    //     return list.second;
    //   }
    // }
    auto found_key = find(key);

    if(found_key != end())
    {
      return (*found_key).second;
    }

    throw std::out_of_range("You haven't that key in your map\n");
  }

  // Возвращает ссылку на элемент по Key (позволяет менять элемент). Если
  // элемент с таким ключом отсутствует, создает его и инициализирует дефолтным
  // значением map["something"] = 75;
  Value &operator[](const Key& key)
  {
    // size_t index = hash_f(key);
    // for(auto& list: data[index])
    // {
    //   if(list.first  == key)
    //   {
    //     return list.second;
    //   }
    // }
    
    auto found_key = find(key);

    if(found_key != end())
    {
      return (*found_key).second;
    }
    
    size_t index = hash_f(key);
    data[index].push_back({key, Value{}});
    map_size++;
    check_colisium();
    return data[index].back().second;
  }

  // Проверяет есть ли в контейнере элемент с таким Key
  bool contains(const Key &key) const
  {
    return find(key) != end();
  }

  // Возвращяет Итератор на элемент который ищем, если нет такого элемента
  // возвращает итератор на последный элемент
  Iterator find(const Key &key)
  {
    size_t i = hash_f(key);
    for(auto it = data[i].begin(); it != data[i].end(); ++it){
      if(it->first == key)
        return Iterator{it, data.begin() + i, data};
    }
    return end();
  };

   ConstIterator find(const Key &key) const
  {
    UnorderedMap* no_const = const_cast<UnorderedMap*>(this);
    return ConstIterator(no_const->find(key));
  };

  // Добавляет новый элемент с ключем и значением, если нет уже существуюшего
  // элемента с таким же ключом Map<int, std::string> c =
  //   {
  //       {1, "one" }, {2, "two" }, {3, "three"},
  //       {4, "four"}, {5, "five"}, {6, "six"  }
  //   };
  // c.(5,"something");
  // возвращает false, потому что элмемент с key = 5 уже существует․
  bool insert(const Key& key, const Value& value)
  {
    auto found_key = find(key);
    if(found_key != end())
    {
      return false;
    }

    size_t index = hash_f(key);
    data[index].push_back({key,value});
    map_size++;
    check_colisium();
    return true;
  }

  // Удаляет элемент по ключу и возвращает результат операции
  // UnorderedMap<int, std::string> c =
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
  bool erase(const Key &key)
  {
    auto found = find(key);
    if(found == end())
    {
      return false;
    }

    size_t index = hash_f(key);
    for(auto it = data[index].begin(); it != data[index].end(); ++it)
    {
      if((*it).first == key)
      {
        data[index].erase(it);
        map_size--;
        return true;
      }
      
    }

    return false;
  }


  class Iterator {
  private:
    // Заполнить
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Key;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;


    using ListIterator = typename std::list<ValueType>::iterator; 
    using VectorIterator = typename std::vector<std::list<ValueType>>::iterator;
    using Data = std::vector<std::list<ValueType>>;
    
    ListIterator list_it;
    VectorIterator vec_it;
    Data& data;
    
  public:
    Iterator(ListIterator list_iter, VectorIterator vec_iter, Data& table): list_it(list_iter),
  vec_it(vec_iter), data(table) {}

    Iterator &operator++()
    {
      // when we are located in circles of one of the lists
      if(++list_it != (*vec_it).end())
      {
        return *this;
      }

      // when we are located at the end() of the list
      // and we want to get to the next begin() of the
      // not empty list, if that list is in range of data
      if(++vec_it != data.end()) 
      {
        while(++vec_it != data.end() && (*vec_it).empty())
        {
          vec_it++;
          list_it = (*vec_it).begin();
          return *this;
        }
      }

      // when we can't do increment the iterator
      // we return the end() of the data
      list_it = (*vec_it).end();
      return *this;
    }

    // NE NUJNO SDELAT !
    // Iterator &operator--()
    // {
      
    // }

    bool operator!=(const Iterator &other)
    {
      return list_it != other.list_it;
    }

    bool operator==(const Iterator &other)
    {
      return list_it == other.list_it;
    }

    // Разыменовывает указатель: std::cout << it->second;
    std::pair<Key, Value>* operator->()
    {
      return &(*list_it);
    }

    // Возвращает значение итератора: *it = {"travel", 42};
    std::pair<Key, Value>& operator*()
    {
      return (*list_it);
    }

  };



  class ConstIterator {
    // Заполнить
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Key;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;
  private:
    Iterator it;
  
  public:

    ConstIterator(Iterator iterat):it(iterat) {}

    ConstIterator &operator++()
    {
      ++it;
      return *this;
    }

    ConstIterator &operator--()
    {
      --it;
      return *this;
    }

    bool operator!=(const ConstIterator &other)
    {
      return it != other.it;
    }

    bool operator==(const ConstIterator &other)
    {
      return it == other.it;
    }

    // единственное отличие от Iterator, что возвращает константную ссылку
    const std::pair<Key, Value>& operator*()
    {
      return *it;
    }

  };
};
