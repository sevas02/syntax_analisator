#include "hash_table.h"
#include <string>
#include <iostream>
#include <list>
#include <fstream>

hash_table::hash_table() {
    capacity = 1000;
    size = 0;
    arr = new node_table * [capacity];
    for (int i = 0; i < capacity; i++)
        arr[i] = NULL;
    deleted = new node_table(-1, -1);
}

//���-�������
int hash_table::hash_function(info info) {
    unsigned int hash = 0;
    for (int i = 0; i < info.lexem.size(); i++)
        hash = 31 * hash + info.lexem[i];
    return hash % capacity;
}

//������� ������ � ������ � ���������
void hash_table::insert_node(int key, info info) {
    node_table* temp = new node_table(key, info);
    int hash_idx = hash_function(info);

    //����� ���������� �����
    while (arr[hash_idx] != NULL &&
        arr[hash_idx]->key != key &&
        arr[hash_idx]->key != -1) {
        hash_idx++;
        hash_idx %= capacity;
    }

    if (arr[hash_idx] == NULL ||
        arr[hash_idx]->key == -1)
        size++;

    arr[hash_idx] = temp;
}

//�������� ������
info hash_table::delete_node(int key) {
    int hash_idx = hash_function(key);
    //����� ���� �� �����
    while (arr[key] != NULL) {
        if (arr[key]->key == key) {
            node_table* temp = arr[key];
            //�������� ������
            arr[key] = deleted;
            size--;
            return temp->value;
        }
        key++;
        key %= capacity;
    }
    return 0;
}

//����� �������� �� �����
info hash_table::find(int key) {
    int counter = 0;
    //����� ���� �� �����
    while (arr[key] != NULL) {
        if (counter++ > capacity)
            return 0;
        if (arr[key]->key == key)
            return arr[key]->value;
        key++;
        key %= capacity;
    }
    return 0;
}

//������ ������� � ����
void hash_table::print(std::ofstream &fout) {
    for (int i = 0; i < capacity; i++) {
        if (arr[i] != NULL && arr[i]->key != -1)
            fout <<  arr[i]->value << 
            "   key = " << "[" << i << "]" << "\n";
    }
}

//�������
void hash_table::insert(info info) {
    insert_node(hash_function(info), info);
}

info hash_table::erase(info info) {
    return delete_node(hash_function(info));
}

info hash_table::find(info info) {
    return find(hash_function(info));
}