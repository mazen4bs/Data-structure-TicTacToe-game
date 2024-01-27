#pragma once

class linked_list {
private:
    class big_node {
    public:
        class small_node {
        public:
            char data;
            small_node* next;
            small_node();
        };

        small_node* b_data;
        small_node* S_first;
        big_node* b_next;

        big_node();

        big_node(small_node* dataValue);
    };

    int mysize;
    big_node* first;

public:
    linked_list();
    ~linked_list();
    int row, col;
    bool insert(int row, int col, char value);
    void drawBoard();
    void reset();
    char getCellValue(int row, int col);
    bool isBoardFull();
    void print();
    bool checkWin();
    void play();
};