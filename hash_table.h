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
    //��� �������� ���-���������
    node_table** arr;

    //������� �������� �����
    int capacity;

    //������� ������
    int size;

    //��������� ����
    node_table* deleted;

    //������� ������ � ������ � ���������
    void insert_node(int key, info info);

    //�������� ������
    info delete_node(int key);

    //����� �������� �� �����
    info find(int key);
public:
    //������� ������ �� ��������
    void insert(info info);

    //�������� �� ��������
    info erase(info info);

    //����� �� ��������
    info find(info info);

    //����������� �� ���������
    hash_table();

    //���-�������
    int hash_function(info info);

    int get_size() { return size; }

    bool is_empty() { return size == 0; }

    //������ ������� � ����
    void print(std::ofstream &fout);
};


#endif