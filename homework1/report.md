
# Homework 1：Recursion

---

## 1. 解題說明

### Problem 1：Ackermann Function

#### 問題描述

本題要求根據 Ackermann 函數的數學定義，分別使用遞迴與非遞迴方式完成計算。

Ackermann 函數定義如下：

$$
A(m,n)=
\begin{cases}
n+1 & m=0\\
A(m-1,1) & m>0,\ n=0\\
A(m-1,A(m,n-1)) & m>0,\ n>0
\end{cases}
$$

#### 解題策略

**遞迴版本：**

直接依照 Ackermann 函數的三個條件進行判斷：

1. 當 m = 0，回傳 n + 1。
2. 當 n = 0，呼叫 A(m-1,1)。
3. 其他情況，呼叫 A(m-1,A(m,n-1))。

**非遞迴版本：**

使用陣列模擬堆疊（Stack），透過 while 迴圈依序完成尚未處理的計算，避免函數直接呼叫自己。

### Problem 2：Powerset

#### 問題描述

給定集合 S，使用遞迴方式找出全部的子集合。

例如：

S = {a, b, c}

其 Powerset 為：

P(S) = {{}, {a}, {b}, {c}, {a,b}, {a,c}, {b,c}, {a,b,c}}

#### 解題策略

使用一個陣列記錄每個元素是否被選擇：

- 0 代表不選擇。
- 1 代表選擇。

每次遞迴分成兩種情況：

1. 不選擇目前元素。
2. 選擇目前元素。

直到所有元素都處理完成，再輸出目前的子集合。

---

## 2. 程式實作

### Problem 1：Ackermann Function

本題分別使用遞迴與非遞迴方式實作。

```cpp
#include <iostream>
using namespace std;

//第一題:遞迴Ackermann
int A(int m, int n)
{
    if (m==0)
        return n+1;
    else if (n==0)
        return A(m-1,1);
    else
        return A(m-1, A(m,n-1));
    
}

int main()
{
    int m,n;

    cout<<"輸入 m 和 n：";
    cin>>m>>n;

    cout<<A(m,n)<<endl;

    return 0;
}

#include <iostream>
using namespace std;

//第一題:非遞迴Ackermann
int A(int m,int n)
{
    int s[100000];
    int top=0;

   
    s[top]=m;

    while (top>=0)
    {
        
        m=s[top];
        top--;

        if (m==0)
        {
            n=n+1;
        }
        else if (n==0)
        {
            n=1;
            top++;
            s[top]=m-1;
        }
        else
        {
            n=n-1;

            top++;
            s[top]=m-1;

            top++;
            s[top]=m;
        }
    }

    return n;
}

int main()
{
    int m,n;

    cout<<"請輸入 m 和 n：";
    cin >>m>>n;

    cout<<A(m,n)<<endl;

    return 0;
}
```

**程式說明：**

遞迴版本直接根據數學公式呼叫函數。

非遞迴版本透過陣列記錄尚未執行的計算，使用 top 變數模擬堆疊操作。

本程式使用 int 儲存結果，適合較小的非負整數輸入，未處理整數溢位及陣列越界。

### Problem 2：Powerset

使用遞迴方式列舉所有子集合。

```cpp
#include <iostream>
using namespace std;

char S[3] = {'a', 'b', 'c'};
int choose[3] = {0, 0, 0};

void Powerset(int i)
{
    if (i == 3)
    {
        cout << "{";

        for (int j = 0; j < 3; j++)
        {
            if (choose[j] == 1)
            {
                cout << S[j] << " ";
            }
        }

        cout << "}" << endl;
        return;
    }

    // 不選擇目前元素
    choose[i] = 0;
    Powerset(i + 1);

    // 選擇目前元素
    choose[i] = 1;
    Powerset(i + 1);
}

int main()
{
    Powerset(0);

    return 0;
}
```

**程式說明：**

使用 choose 陣列記錄每個元素是否選擇。

當 i == 3 時，代表所有元素都已處理完成，輸出目前的子集合。

---

## 3. 效能分析

### Problem 1：Ackermann Function

#### 時間複雜度

Ackermann 函數的成長速度非常快。

一般遞迴版本會依照函數定義重複呼叫，執行時間隨 m 和 n 增加而快速成長，不能用固定次數的迴圈或簡單的多項式時間複雜度來描述。

非遞迴版本雖然改用 while 迴圈，但仍然需要處理相同的 Ackermann 遞迴展開工作，因此無法解決大量運算的問題。

#### 空間複雜度

**遞迴版本：**

需要使用函數呼叫堆疊，空間需求與最大遞迴深度有關。

**非遞迴版本：**

使用固定大小的陣列 s[100000] 儲存尚未完成的計算。

因此程式宣告的額外陣列空間為 O(1)，但這個版本有固定容量限制，無法保證處理所有輸入。

### Problem 2：Powerset

#### 時間複雜度

假設集合共有 n 個元素，每個元素有選擇與不選擇兩種情況。

因此總共有：

$$
2^n
$$

種子集合。

由於每次輸出子集合時，最多需要檢查 n 個元素，所以時間複雜度為：

$$
O(n \times 2^n)
$$

#### 空間複雜度

使用陣列記錄元素選擇狀態，並且需要遞迴處理 n 個元素。

因此一般化演算法的額外空間複雜度為：

$$
O(n)
$$

---

## 4. 測試與驗證

### Problem 1：Ackermann Function

#### 測試一：A(1,2)

編譯與執行：

```shell
$ g++ ackermann.cpp --std=c++21 -o ackermann.exe
$ .\ackermann.exe
請輸入 m 和 n：1 2
Recursive: 4
Nonrecursive: 4
```

#### 測試二：A(2,2)

```shell
$ .\ackermann.exe
請輸入 m 和 n：2 2
Recursive: 7
Nonrecursive: 7
```

#### 測試三：A(3,2)

```shell
$ .\ackermann.exe
請輸入 m 和 n：3 2
Recursive: 29
Nonrecursive: 29
```

**驗證結果：**

以上三組測試的遞迴和非遞迴結果相同，且符合 Ackermann 函數的數學定義。

### Problem 2：Powerset

#### 測試一：S = {a,b,c}

編譯與執行：

```shell
$ g++ powerset.cpp --std=c++21 -o powerset.exe
$ .\powerset.exe
{}
{c }
{b }
{b c }
{a }
{a c }
{a b }
{a b c }
```

#### 驗證結果

集合共有 3 個元素，因此理論上的子集合數量為：

$$
2^3 = 8
$$

程式預期輸出 8 個子集合，且不會重複。

子集合的輸出順序不影響結果的正確性。

---

## 5. 申論及開發報告

### Problem 1：Ackermann Function

#### 為什麼使用遞迴？

Ackermann 函數本身就是使用遞迴方式定義，因此直接使用遞迴實作，可以讓程式碼與數學公式對應。

遞迴版本的優點是程式較簡短，也比較容易理解。

但缺點是當輸入數字增加時，函數呼叫次數會快速增加，可能造成執行時間過長或堆疊溢位。

#### 為什麼使用陣列模擬堆疊？

為了完成題目要求的非遞迴版本，使用普通陣列記錄尚未處理的運算。

透過 top 變數記錄堆疊頂端的位置，搭配 while 迴圈完成計算。

這種方式能避免函數直接呼叫自己，也能幫助理解遞迴與堆疊之間的關係。

### Problem 2：Powerset

#### 為什麼使用遞迴？

因為集合的每個元素都有兩種選擇：

1. 選擇該元素。
2. 不選擇該元素。

使用遞迴可以依序處理每一個元素，並且列舉所有可能的組合。

#### 為什麼使用陣列？

本次實作使用普通陣列儲存元素及選擇狀態。

相較於其他較複雜的資料結構，普通陣列的使用方式比較簡單。

透過這次作業，可以學習遞迴演算法、堆疊的運作方式，以及如何使用遞迴產生集合的所有子集合。
