#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <cstring>
#include <math.h>
using namespace std;
struct Node{
    int rows;
    int colums;
    int value;
    Node *next = NULL;
};

Node* add(Node* &head, int column, int row, int valueInput)
{
    if (head == nullptr) {
        Node* newNode = new Node;
        newNode->value = valueInput;
        newNode->colums = column;
        newNode->rows=row;
        newNode->next = head;

        return newNode;
    }

    else {
        Node* current = head;
        Node* newNode = new Node;
        newNode->value = valueInput;
        newNode->colums = column;
        newNode->rows=row;
        newNode->next = current->next;
        current->next = newNode;

        return head;
    }
};

Node* addMinor(Node* head, int column, int row, int valueInput)
{
    Node* current = head;
    while(current != NULL){

        if(current->next == NULL){

            Node* newNode = new Node;
            newNode->value = valueInput;
            newNode->colums = column;
            newNode->rows=row;
            newNode->next = NULL;
            current->next = newNode;
            break;
        }
        current = current->next;
    }
    return head;
};
Node* readMatrix(){
    string line;
    string token;
    int rowNum=0;
    int colNum=0;
    int currSize = 0;
    int test;
    Node *temp= nullptr;


    while(getline(cin, line))
    {
        stringstream ss(line);
        currSize = 0;
        colNum = 0;

        while(getline(ss, token, ' '))
        {
            test =stoi(token);
            if(test != 0){
                temp = add(temp, colNum, rowNum, test);
                currSize++;
                colNum++;
            }else{
                currSize++;
                colNum++;
            }
        }
        if(colNum - 1 == rowNum){
            break;
        }else {
            rowNum++;
        }
    }
    if(colNum - 1 != rowNum){
        cout << ("Error! Non-square matrix!");
        return 0;
    }
    if(temp == NULL){
        return 0;

    }
    return temp;
};


int columns(Node *matrix){
    int C = 0;
    while(matrix->next != NULL){
        if(matrix->next->colums >= matrix->colums && C < matrix->next->colums){
            C = matrix->next->colums;
            matrix = matrix->next;
        }else if(matrix->colums >= matrix->next->colums && C < matrix->colums){
            C = matrix->colums;
            matrix = matrix->next;
        }else{
            matrix = matrix->next;
        }}
    return C;
};

int rows(Node *matrix){
    int R = 0;
    while(matrix->next != NULL){
        if(matrix->next->rows >= matrix->colums && R < matrix->next->rows){
            R = matrix->next->rows;
            matrix = matrix->next;
        }else if(matrix->rows >= matrix->next->rows && R < matrix->rows){
            R = matrix->rows;
            matrix = matrix->next;
        }else{
            matrix = matrix->next;
        }}
    return R;
};
int size(Node *head){
    int R;
    int C;
    R = rows(head) + 1;
    C = columns(head) + 1;
    return R*C;
};

int printNodes(Node *matrix){
    while(matrix != NULL){
        cout << matrix->value << " ";
        matrix = matrix->next;
    }
};
bool isSquare(Node *matrix){
    int R;
    int C;
    R = rows(matrix);
    C = columns(matrix);
    if(R != C){
        return false;
    }else{
        return true;
    }

};

int getValue(Node *matrix, int row, int column){
    while(matrix != NULL) {
        if (matrix->rows == row && matrix->colums == column) {
            return matrix->value;
        } else {
            matrix = matrix->next;
        }
    }
    if(matrix == NULL){
        return 0;
    }
};

Node *minor(Node *head, int row, int col, int count){
    Node *node = nullptr;
    Node *temp = head;
    int scale = 1;
    while (temp != nullptr){
        if(temp->rows == 0 && temp->colums == col){
            scale = temp->value;
        }
        if(temp->rows != 0 && temp->colums != col){
            int a  = temp->rows-1;
            int b = temp->colums;
            if(temp->colums > col){
                b--;
            }
            add(node, b, a,temp->value);
        }
        temp = temp->next;
    }
    return node;
}

int determinant(Node *matrix, int d){
    int sum = 0;
    if(d == 1){
        return matrix->value;
    }
    for(int i = 0; i < d - 1; i++){
        sum+= pow(-1,i)* getValue(matrix,0, i) * determinant(minor(matrix, matrix->rows, matrix->colums, d),d-1);
    }
    return sum;
};


int main() {
    Node *matrix;
    matrix = readMatrix();
    int d = rows(matrix);

    if(matrix == NULL){
        cout << "0";
        return 0;
    }
    if(isSquare(matrix)==false){
        cout << "Error! Non-square matrix!";
        return 0;
    }

    cout << determinant(matrix, d);



}