#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
    element key;
    struct TreeNode* left, * right;
} TreeNode;

TreeNode* search(TreeNode* node, int key) {  //�˻�(�ݺ�)
    while (node != NULL) {
        if (key == node->key) return node;
        else if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return NULL;
}

TreeNode* new_node(int item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode* iterative_insert_node(TreeNode* root, int key) {
    TreeNode* new_no = new_node(key);
    if (root == NULL) return new_node;

    TreeNode* parent = NULL;
    TreeNode* current = root;

    while (current != NULL) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else {
            free(new_node);
            return root;
        }
    }

    if (key < parent->key)
        parent->left = new_node;
    else
        parent->right = new_node;

    return root;
}

TreeNode* min_value_node(TreeNode* node) {
    TreeNode* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

TreeNode* iterative_delete_node(TreeNode* root, int key) {
    if (root == NULL) return root;

    TreeNode* parent = NULL;
    TreeNode* current = root;

    while (current != NULL && current->key != key) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL) {
        
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
        free(current);
    }
    else if (current->right == NULL) {
        TreeNode* temp = current->left;
        if (parent == NULL)
            free(current);
        else if (current == parent->left)
            parent->left = temp;
        else
            parent->right = temp;
        free(current);
    }
    else {
        TreeNode* successor = min_value_node(current->right);
        current->key = successor->key;
        current->right = iterative_delete_node(current->right, successor->key);
    }
    return root;
}

void inorder(TreeNode* root) { //������ȸ
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}


int main(void) {
    TreeNode* root = NULL;
    TreeNode* tmp = NULL;

    printf("s     :   �˻�\n");
    printf("i     :   ��� �߰�\n");
    printf("d     :   ��� ����\n");
    printf("t     :   ���� ��ȸ\n");
    printf("I     :   ��� �߰�(�ݺ�)\n");
    printf("D     :   ��� ����(�ݺ�)\n");
    printf("c     :   ����\n");

    char i;
    while (1) {
        printf("�޴��Է� : ");
        scanf_s("%c", &i);
        if (i == 's') {
            int snum;
            printf("�˻��� �� �Է� : ");
            scanf_s("%d", snum);
            tmp = search(root, snum);
            if (tmp != NULL)
                printf("�˻�����\n", snum);
            else
                printf("�˻� ����\n");
        }
        if (i == 'i') {

        }
    }
}