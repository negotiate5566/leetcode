/*
 * input digit contains only '0' ~ '9'
 * so linked list is not necessary.
 * it would be faster if using an array to count B.
 * ex: https://discuss.leetcode.com/topic/28776/don-t-know-how-to-fix-the-runtime-error-my-code-is-in-c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG(...) (void *)0//printf(__VA_ARGS__)

struct digit_count_node
{
    int val;
    int count;
    struct digit_count_node *next;
};

void add_digit_to_list(struct digit_count_node *list, int digit)
{
    struct digit_count_node *p;
    //first node
    if (list->val == -1)
    {
        list->val = digit;
        list->count++;
        return;
    }

    p = list;

    while(p != NULL)
    {
        if (p->val == digit)
        {
            p->count++;
            return;
        }
        p = p->next;
    }

    // create a new node
    if (p == NULL)
    {
        p = list;
        while(p->next != NULL)
            p = p->next;
        p->next = malloc(sizeof(struct digit_count_node));
        p = p->next;
        p->val = digit;
        p->count = 1;
        p->next = NULL;
    }

    return;
}

void print_element(struct digit_count_node *list)
{
    struct digit_count_node *p;
    p = list;
    printf("list element -------\n");
    while(p != NULL)
    {
        printf("val: %c, count: %d\n", p->val, p->count);
        p = p->next;
    }
}

int calculate_B(struct digit_count_node *list_secret, struct digit_count_node *list_guess)
{
    struct digit_count_node *p = list_guess, *p_secret = list_secret;
    int count_B = 0;

    while(p != NULL)
    {
        while(p_secret != NULL)
        {
            if (p->val == p_secret->val)
            {
                count_B += p->count <= p_secret->count ? p->count : p_secret->count;
                break;
            }
            p_secret = p_secret->next;
        }
        p = p->next;
        p_secret = list_secret;
    }
    return count_B;
}

void init_list(struct digit_count_node *list)
{
    list->val = -1;
    list->count = 0;
    list->next = NULL;
}

void free_list(struct digit_count_node *list)
{
    struct digit_count_node *p = list;

    while(p != NULL)
    {
        list = list->next;
        free(p);
        p = list;
    }
}

char* getHint(char* secret, char* guess) {
    struct digit_count_node *list_guess = malloc(sizeof(struct digit_count_node));
    struct digit_count_node *list_secret = malloc(sizeof(struct digit_count_node));
    int i, count_A=0, count_B=0, ans_size;
    char *ans;

    LOG("input [%s] [%s]\n", secret, guess);

    init_list(list_secret);
    init_list(list_guess);

    for (i = 0; i < strlen(secret); i++)
    {
        if (secret[i] == guess[i])
        {
            LOG("digit[%d]: A++\n", i);
            count_A++;
        }
        else
        {
            LOG("digit[%d]: diff!\n", i);
            add_digit_to_list(list_secret, secret[i]);
            add_digit_to_list(list_guess, guess[i]);
        }
    }

    //print_element(list_secret);
    //print_element(list_guess);

    count_B = calculate_B(list_secret, list_guess);

    LOG("A: %d, B: %d\n", count_A, count_B);

    ans_size = snprintf(NULL, 0, "%dA%dB", count_A, count_B);
    ans = malloc(sizeof(ans_size + 1));
    snprintf(ans, ans_size + 1, "%dA%dB", count_A, count_B);

    free_list(list_secret);
    free_list(list_guess);

    return ans;
}

int main(void)
{
    char *ans;
    ans = getHint("1807", "7810");

    printf("ANSWER 1 (1807, 7810): [%s]\n", ans);
    free(ans);

    ans = getHint("9988", "9800");
    printf("ANSWER 2 (9988, 9800): [%s]\n", ans);
    free(ans);

    return 0;
}
