
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//�˻�(�ݺ�) s
//��� �߰�(���) i
//��� ����(���) d
//���� ��ȸ t (���)
//��� �߰�(�ݺ�) I
//��� ����(�ݺ�) D
//���� C

//count ��������� ���߷��� �̻��ϰ� �����Ͽ�, ���� �����մϴ�. (10.05)
typedef int element;

typedef struct TreeNode {
    element key;
    struct TreeNode* left, * right;
} TreeNode;

TreeNode n1 = { 25,NULL,NULL };
TreeNode n2 = { 16,NULL,&n1 };
TreeNode n3 = { 42,NULL,NULL };
TreeNode n4 = { 46,&n3,NULL };
TreeNode n5 = { 55,NULL,NULL };
TreeNode n6 = { 53,&n4,&n5 };
TreeNode n7 = { 41,&n2,&n6 };
TreeNode n8 = { 62,NULL,NULL };
TreeNode n9 = { 64,NULL,NULL };
TreeNode n10 = { 63,&n8,&n9 };
TreeNode n11 = { 70,NULL,NULL };
TreeNode n12 = { 65,&n10,&n11 };
TreeNode n13 = { 74,&n12,NULL };
TreeNode n14 = { 60,&n7,&n13 };
TreeNode* root = &n14;

int count = 0;

TreeNode* search(TreeNode* root, int key) {  //�ݺ� �˻�
    count = 0;
    while (root != NULL) {
        count++;
        if (key == root->key) return root;
        else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

TreeNode* newNode(int key) {
    struct TreeNode* temp = (TreeNode*)malloc(sizeof(struct TreeNode));
    if (temp == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(1);
    }
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

TreeNode* insert(TreeNode* root, int key) { //(���) �߰�
    count++;
    if (root == NULL) {
        
        return newNode(key);
    }
    

    if (key < root->key) {
        
        root->left = insert(root->left, key);
    }
    else if (key > root->key) {
        
        root->right = insert(root->right, key);
    }
    else {
        printf("�̹� �����ϴ� ��� �Դϴ�.\n");
    }

    return root;
}

TreeNode* minValueNode(TreeNode* node) { //����� �ּҰ�
    TreeNode* current = node;

    while (current->left != NULL) {
        current = current->left;
        count++;
    }
    
    return current;
}

TreeNode* delete(TreeNode* root, int key) { //(���) ����

    if (root == NULL)
        return root;
    count++;
    if (key < root->key) {
        
        root->left = delete(root->left, key);
    }
    else if (key > root->key) {
        
        root->right = delete(root->right, key);
    }

    else {
        
        if (root->left == NULL) {
            
            TreeNode* temp = root->right;
            return temp;
        }
        else if (root->right == NULL) {
            
            TreeNode* temp = root->left;
            return temp;
        }
        TreeNode* temp = minValueNode(root->right);
        root->key = temp->key;
        
        root->right = delete(root->right, temp->key);
    }
    
    return root;
}

int incount = 0;

void inorder(TreeNode* root) { //������ȸ

    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
        incount++;

    }

}

TreeNode* insert2(TreeNode* root, int key) { //���� �ݺ�
    TreeNode* newnode = newNode(key);
    if (root == NULL) return newnode;
    TreeNode* parent = NULL;
    TreeNode* current = root;

    while (current != NULL) {
        count++;
        parent = current;
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else {
            free(newnode); 
            return root;
        }
    }
    if (key < parent->key)
        parent->left = newnode;
    else
        parent->right = newnode;

    return root;
}

TreeNode* delete2(TreeNode* root, int key) { //���� (�ݺ�)
    if (root == NULL) return root;
    TreeNode* parent = NULL;
    TreeNode* current = root;

    while (current != NULL && current->key != key) {
        count++;
        parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    if (current == NULL) {
        printf("���� �߻�\n");
        return root;
    }

    if (current->left == NULL) {
        
        TreeNode* temp = current->right;
        if (parent == NULL)
            free(current);
        else if (current == parent->left)
            parent->left = temp;
        else
            parent->right = temp;
        return root;
    }
    else if (current->right == NULL) {
        
        TreeNode* temp = current->left;
        if (parent == NULL)
            free(current);
        else if (current == parent->left)
            parent->left = temp;
        else
            parent->right = temp;
        return root;
    }
    else {
        
        TreeNode* successor = minValueNode(current->right);
        current->key = successor->key;
        current->right = delete2(current->right, successor->key);
        return root;
    }
}

int main() {

    TreeNode* tmp = NULL;

    printf("----------------------------------\n");
    printf("|  s        :    �˻�             |\n");
    printf("|  i        :    ��� �߰�        |\n");
    printf("|  d        :    ��� ����        |\n");
    printf("|  t        :    ���� ��ȸ        |\n");
    printf("|  I        :    ��� �߰�(�ݺ�)  |\n");
    printf("|  D        :    ��� ����(�ݺ�)  |\n");
    printf("|  c        :    ����             |\n");
    printf("----------------------------------\n");
    printf("\n\n");

    while (1) {

        int key;
        printf("�޴� �Է�: ");
        char input;
        scanf_s(" %c", &input, sizeof(input));

        if (input == 's') {
            printf("�˻��� �� �Է� : ");
            scanf_s("%d", &key);
            if (search(root, key) != NULL)
                printf("�˻� ���� : %d\n", key);
            else
                printf("�˻� ����\n");

            inorder(root);
            printf("\n�湮�� ����� �� : %d\n", count);
            count = 0;
        }
        else if (input == 'i') {
            printf("������ �� �Է� : ");
            scanf_s("%d", &key);
            root = insert(root, key);
            inorder(root);
            printf("\n�湮�� ����� �� : %d\n", count);
            count = 0;
        }
        else if (input == 'd') {
            printf("������ �� �Է� : ");
            scanf_s("%d", &key);
            root = delete(root, key);
            inorder(root);
            printf("\n�湮�� ����� �� : %d\n", count);
            count = 0;
        }
        else if (input == 't') {
            inorder(root);
            printf("\n�湮�� ����� �� : %d\n", incount);
            incount = 0;
        }
        else if (input == 'I') {
            printf("������ �� �Է� : ");
            scanf_s("%d", &key);
            root = insert2(root, key);
            inorder(root);
            printf("\n�湮�� ����� �� : %d\n", count);
            count = 0;
        }
        else if (input == 'D') {
            printf("������ �� �Է� : ");
            scanf_s("%d", &key);
            root = delete2(root, key);
            inorder(root);
            printf("\n�湮�� ����� �� : %d\n", count);
            count = 0;
        }
        else if (input == 'c') {
            printf("���α׷��� �����մϴ�.");
            exit(1);
        }
        printf("\n\n");
    }

    return 0;
}