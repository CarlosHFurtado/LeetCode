/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct lista
{
    int val;
    int cont;
    struct lista *next;
} CTRL;

CTRL *insere(CTRL *l, int k)
{
    CTRL *new = malloc(sizeof(CTRL));
    new->cont = 1;
    new->next = l;
    new->val = k;
    return new;
}

int cont(struct TreeNode *root)
{
    if (!root)
        return 0;
    return root->val + cont(root->left) + cont(root->right);
}

void solve(struct TreeNode *root, CTRL *hash[101])
{
    if (!root)
        return;
    int atual = cont(root);
    CTRL *p;
    p = hash[abs(atual) % 101];
    while (p)
    {
        if (p->val == atual)
        {
            p->cont++;
            break;
        }
        p = p->next;
    }
    if (!p)
        hash[abs(atual) % 101] = insere(hash[abs(atual) % 101], atual);
    solve(root->left, hash);
    solve(root->right, hash);
}

int *findFrequentTreeSum(struct TreeNode *root, int *returnSize)
{
    CTRL *hash[101];
    for (int i = 0; i < 101; i++)
        hash[i] = NULL;
    solve(root, hash);
    int max = 0;
    int cont = 0;
    CTRL *res = NULL;
    for (int i = 0; i < 101; i++)
    {
        CTRL *p = hash[i];
        while (p)
        {
            if (p->cont == max)
            {
                res = insere(res, p->val);
                cont++;
            }
            if (p->cont > max)
            {
                max = p->cont;
                res = NULL;
                res = insere(res, p->val);
                cont = 1;
            }
            p = p->next;
        }
    }
    *returnSize = cont;
    int *res1 = malloc(sizeof(int) * cont);
    for (int i = 0; i < cont; i++)
    {
        res1[i] = res->val;
        res = res->next;
    }
    return res1;
}
