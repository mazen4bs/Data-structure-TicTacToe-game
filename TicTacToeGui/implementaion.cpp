#include "header.h"
#include "pch.h"
#include <iostream>

using namespace std;

linked_list::linked_list() : first(0), mysize(3) {}

linked_list::big_node::small_node::small_node() : next(0) {}

linked_list::big_node::big_node() : b_next(0) {}
linked_list::big_node::big_node(small_node* dataValue) : b_data(dataValue), b_next(0), S_first(dataValue) {
    small_node* s2 = new small_node();
    S_first->next = s2;
    small_node* s3 = new small_node();
    s2->next = s3;
}

linked_list::~linked_list() {
    big_node* prev = first, * ptr;
    while (prev != 0) {
        big_node::small_node* sprev = prev->S_first, * sptr;
        while (sprev != 0) {
            sptr = sprev->next;
            delete sprev;
            sprev = sptr;
        }
        ptr = prev->b_next;
        delete prev;
        prev = ptr;
    }
}

bool linked_list::insert(int row, int col, char value) {
    if (row < 0 || col < 0 || row>3 || col>3) {
        return false;
    }
    big_node* ptr = first;
    for (int i = 1; i < row; i++) {
        ptr = ptr->b_next;
    }

    big_node::small_node* sptr = ptr->b_data;
    for (int j = 1; j < col; j++)
        sptr = sptr->next;

    if (sptr->data != 'X' && sptr->data != 'O') {
        sptr->data = value;
        return true;
    }
    else
        return false;
}

void linked_list::drawBoard() {
    big_node::small_node* s1 = new big_node::small_node();
    big_node* b1 = new big_node(s1);
    first = b1;
    big_node::small_node* s2 = new big_node::small_node();
    big_node* b2 = new big_node(s2);
    b1->b_next = b2;
    big_node::small_node* s3 = new big_node::small_node();
    big_node* b3 = new big_node(s3);
    b2->b_next = b3;
    reset();
}

void linked_list::reset() {
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            insert(i, j, '-');

        }
    }
}

char linked_list::getCellValue(int row, int col) {
    big_node* ptr = first;
    for (int i = 1; i < row; i++) {
        ptr = ptr->b_next;
    }

    big_node::small_node* sptr = ptr->b_data;
    for (int j = 1; j < col; j++) {
        sptr = sptr->next;
    }
    return (sptr->data);
}

bool linked_list::isBoardFull() {
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (getCellValue(i, j) == '-') {
                return false;
            }
        }
    }
    return true;
}

void linked_list::print() {
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << getCellValue(i, j);
            if (j != 3)cout << "|";
        }
        cout << endl;
    }
    cout << endl;
}

bool linked_list::checkWin() {

    if (getCellValue(row, 1) == getCellValue(row, 2) && getCellValue(row, 2) == getCellValue(row, 3)) {
        if (getCellValue(row, 1) == 'X' || getCellValue(row, 1) == 'O') {
            cout << "Player " << (getCellValue(row, 1) == 'X' ? "1" : "2") << " wins!" << endl;
            return true;
        }
    }

    if (getCellValue(1, col) == getCellValue(2, col) && getCellValue(2, col) == getCellValue(3, col)) {
        if (getCellValue(1, col) == 'X' || getCellValue(1, col) == 'O') {
            cout << "Player " << (getCellValue(1, col) == 'X' ? "1" : "2") << " wins!" << endl;
            return true;
        }
    }

    if ((getCellValue(1, 1) == getCellValue(2, 2) && getCellValue(2, 2) == getCellValue(3, 3)) ||
        (getCellValue(1, 3) == getCellValue(2, 2) && getCellValue(2, 2) == getCellValue(3, 1))) {
        if (getCellValue(2, 2) != '-') {
            cout << "Player " << (getCellValue(2, 2) == 'X' ? "1" : "2") << " wins!" << endl;
            return true;
        }
    }

    if (isBoardFull()) {
        cout << "It's a draw!" << endl;
        return false;
    }

    return false;
}

void linked_list::play() {
    drawBoard();
    print();
    static int P1score = 0, P2score = 0;
    cout << "Player 1: " << P1score << " \tPlayer 2: " << P2score << endl << endl;
    char replay, value = 'X';
    int turn = 1;
    while (!isBoardFull()) {
        cout << (value == 'X' ? "Player 1 " : "Player 2 ") << "please enter the row and column you want\n";
        cout << "row: ";
        cin >> row;
        while (row > 3 || row < 1) {
            cout << "Invalid row\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "row: ";
            cin >> row;
        }
        cout << "column: ";
        cin >> col;
        while (col > 3 || col < 1) {
            cout << "Invalid column\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "column: ";
            cin >> col;
        }
        if (!insert(row, col, value)) {
            cerr << "Invalid position\n";
            turn--;
        }
        turn % 2 == 0 ? value = 'X' : value = 'O';
        print();
        turn++;
        if (checkWin()) {
            value != 'X' ? P1score++ : P2score++;
            break;
        }
    }
    cout << "Do you want to play again Y/N" << endl;
    cin >> replay;
    switch (replay) {
    case 'Y':
    case 'y':
        play();
        break;
    case 'N':
    case 'n':
        cout << "Player 1: " << P1score << " \tPlayer 2: " << P2score << endl << endl;
        P1score = 0;
        P2score = 0;
        return;
        break;
    default:
        cout << "Player 1: " << P1score << " \tPlayer 2: " << P2score << endl << endl;
        exit(1);
        break;
    }
}