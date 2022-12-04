#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "data.h"
#include <iostream>
#include <string>
#include <list>
#include <fstream>

class node_table {
public:
    info value;
    int key;
    node_table(int key, info value) {
        this->value = value;
        this->key = key;
    }
};

class hash_table {
private:
    //дл€ хранени€ хэш-элементов
    node_table** arr;

    //сколько выделено места
    int capacity;

    //текущий размер
    int size;

    //удаленный узел
    node_table* deleted;

    //вставка €чейки с ключем и значением
    void insert_node(int key, info info);

    //удаление €чейки
    info delete_node(int key);

    //поиск значени€ по ключу
    info find(int key);
public:
    //вставка €чейки по значению
    void insert(info info);

    //удаление по значению
    info erase(info info);

    //поиск по значению
    info find(info info);

    //конструктор по умолчанию
    hash_table();

    //хэш-функци€
    int hash_function(info info);

    int get_size() { return size; }

    bool is_empty() { return size == 0; }

    //запись таблицы в файл
    void print(std::ofstream &fout);
};


#endif