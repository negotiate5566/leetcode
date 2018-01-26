/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
 * return height, get value in param
 */
int heightAndLeftMost(struct TreeNode *node, int *value)
{
    int height = 0, value_left = 0, value_right = 0, height_left = 0, height_right = 0;

    if (node->left == NULL && node->right == NULL)
    {
        *value = node->val;
        height = 1;
    }
    else
    {
        if (node->left != NULL)
            height_left = heightAndLeftMost(node->left, &value_left);
        
        if (node->right != NULL)
            height_right = heightAndLeftMost(node->right, &value_right);

        // use if to reduce the comparison times from 2 to 1 may improve efficiency?
        height = (height_left >= height_right ? height_left : height_right) + 1;
        *value = height_left >= height_right ? value_left : value_right;
    }

    return height;
}

int findBottomLeftValue(struct TreeNode* root) {
    int left_most_value;
    heightAndLeftMost(root, &left_most_value);
    return left_most_value;
}

void free_tree(struct TreeNode *node)
{
    if (node->left == NULL && node->right == NULL)
    {
        free(node);
        return;
    }

    if (node->left != NULL)
        free_tree(node->left);

    if (node->right != NULL)
        free_tree(node->right);

    free(node);
}

int main(void)
{
    int answer;
    //example 1
    struct TreeNode *ex1 = malloc(sizeof(struct TreeNode));
    ex1->val = 2;
    
    ex1->left = malloc(sizeof(struct TreeNode));
    ex1->left->val = 1;
    ex1->left->left = NULL;
    ex1->left->right = NULL;

    ex1->right = malloc(sizeof(struct TreeNode));
    ex1->right->val = 3;
    ex1->right->left = NULL;
    ex1->right->right = NULL;

    answer = findBottomLeftValue(ex1);
    printf("example 1: %d\n", answer);
    free_tree(ex1);

    //example 2
    struct TreeNode *ex2 = malloc(sizeof(struct TreeNode));
    ex2->val = 1; // root 1
    
    ex2->left = malloc(sizeof(struct TreeNode)); // root left 2
    ex2->left->val = 2;
    ex2->left->right = NULL;
    ex2->left->left = malloc(sizeof(struct TreeNode)); // 2 left 4
    ex2->left->left->val = 4;
    ex2->left->left->left = NULL;
    ex2->left->left->right = NULL;
    
    ex2->right = malloc(sizeof(struct TreeNode)); // root right 3
    ex2->right->val = 3;

    ex2->right->left = malloc(sizeof(struct TreeNode)); // 3 left 5
    ex2->right->left->val = 5;

    ex2->right->left->left = malloc(sizeof(struct TreeNode)); // 5 left 7
    ex2->right->left->left->val = 7;
    ex2->right->left->left->left = NULL;
    ex2->right->left->left->right = NULL;

    ex2->right->right = malloc(sizeof(struct TreeNode)); // 3 right 6
    ex2->right->right->val = 6;
    ex2->right->right->left = NULL;
    ex2->right->right->right = NULL;
    

    answer = findBottomLeftValue(ex2);
    printf("example 2: %d\n", answer);
    free_tree(ex2);
    
    return 0;
}
