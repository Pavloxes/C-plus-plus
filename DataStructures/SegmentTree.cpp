#include <iostream>
#include <vector>

using namespace std;

typedef int my_type;

my_type my_max(my_type a, my_type b)
{
    return max(a, b);
}

my_type my_sum(my_type a, my_type b)
{
    return a + b;
}

template <typename Type>
class segment_tree
{
private:
    Type e0;
    int MAXN;
    vector<Type> ar, push;
    Type(*f)(Type a, Type b);

    void push_me(int v, int from, int to)
    {
        ar[v] += push[v];// если ДО на сумму, заменить на: ar[v] += push[v] * (to - from);
        if (from + 1 != to)
        {
            push[v * 2] += push[v];
            push[v * 2 + 1] += push[v];
        }
        push[v] = 0;
    }

    void update(int v, int l, int r, int i, my_type val)
    {
        if (l + 1 == r)
        {
            ar[v] = val;
        }
        else
        {
            if (i < (l + r) / 2)
                update(v * 2, l, (l + r) / 2, i, val);
            else
                update(v * 2 + 1, (l + r) / 2, r, i, val);
            ar[v] = f(ar[v * 2], ar[v * 2 + 1]);
        }
    }

    my_type get(int v, int l, int r, int seg_l, int seg_r)
    {
        if (seg_r <= l || r <= seg_l)
        {
            return e0;
        }
        push_me(v, l, r);
        if (seg_l <= l && r <= seg_r)
        {
            return ar[v];
        }
        push_me(v * 2, l, (l + r) / 2);
        push_me(v * 2 + 1, (l + r) / 2, r);
        return f(get(v * 2, l, (l + r) / 2, seg_l, seg_r),
            get(v * 2 + 1, (l + r) / 2, r, seg_l, seg_r));
    }

    void add(int v, int l, int r, int seg_l, int seg_r, int x)
    {
        if (seg_r <= l || r <= seg_l)
        {
            return;
        }
        push_me(v, l, r);
        if (seg_l <= l && r <= seg_r)
        {
            push[v] = x;
            return;
        }
        add(v * 2, l, (l + r) / 2, seg_l, seg_r, x);
        add(v * 2 + 1, (l + r) / 2, r, seg_l, seg_r, x);
        push_me(v * 2, l, (l + r) / 2);
        push_me(v * 2 + 1, (l + r) / 2, r);
        ar[v] = f(ar[v * 2], ar[v * 2 + 1]);
    }

public:
    //инициализация дерева
    segment_tree(int n, Type(*func)(Type a, Type b), Type e)
    {
        e0 = e;
        f = func;
        for (MAXN = 1; MAXN < n; MAXN *= 2);
        ar.assign(MAXN * 2, e0);
        push.assign(MAXN * 2, 0);
    }

    //используется для инициализации массива
    void change(int ind, my_type val)
    {
        ar[ind + MAXN] = val;
    }

    //добавляет значение val на отрезке (так как ДО на полуинтервалах [..) => для запроса пишем add(from - 1, to, ind))
    void add(int from, int to, my_type val)
    {
        add(1, 0, MAXN, from, to, val);
    }

    //добавляет значение val для элемента с индексом ind в 1 индесации
    void add(int ind, my_type val)
    {
        add(1, 0, MAXN, ind - 1, ind, val);
    }

    //меняет значение элемента с индексом ind на val в 1 индесации
    void update(int ind, my_type val)
    {
        update(1, 0, MAXN, ind, val);
    }

    //возвращает значение на отрезке от l до r (так как ДО на полуинтервалах [..) => для запроса пишем get(l - 1, r))
    my_type get(int l, int r)
    {
        return get(1, 0, MAXN, l, r);
    }

    //возвращает значение элемента с индексом ind в 1 индесации
    my_type get(int ind)
    {
        return get(1, 0, MAXN, ind - 1, ind);
    }

    //строит дерево по массиву
    void build()
    {
        for (int i = MAXN - 1; i > 0; --i)
        {
            ar[i] = f(ar[2 * i], ar[2 * i + 1]);
        }
    }

    //выводит нижний слой дерева
    void print()
    {
        for (int i = 1; i <= MAXN; ++i)
        {
            cout << get(i) << ' ';
        }
        cout << '\n';
    }

};

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n = 10, from, to, val;

    segment_tree<my_type> my_max_segment_tree(n, my_max, -1);
    for (int i = 0; i < n; ++i)
    {
        my_max_segment_tree.change(i, i + 1);
    }
    my_max_segment_tree.build();

    from = 5, to = 8, val = 52;

    cout << "MaxTree: \n";
    my_max_segment_tree.print();
    cout << "add(" << from << ", " << to << ", " << val << ")\n";
    my_max_segment_tree.add(from - 1, to, val);
    my_max_segment_tree.print();

//-----------------------------------------------------

    segment_tree<my_type> my_sum_segment_tree(n, my_sum, 0);
    for (int i = 0; i < n; ++i)
    {
        my_sum_segment_tree.change(i, i + 12);
    }
    my_sum_segment_tree.build();

    from = 2, to = 5, val = 13;

    cout << "\nSumTree: \n";
    my_sum_segment_tree.print();
    cout << "add(" << from << ", " << to << ", " << val << ")\n";
    my_sum_segment_tree.add(from - 1, to, val);
    my_sum_segment_tree.print();

    return 0;
}
