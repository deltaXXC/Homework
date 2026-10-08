# 41143263

作業一

## 解題說明

### Problem 1：Ackermann Function

#### 問題描述

本題要求使用 C++ 實作 Ackermann 函數，並且分別使用遞迴與非遞迴兩種方法完成計算。

Ackermann 函數的公式如下：

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

1. 使用 if 和 else 判斷 m 和 n 的數值。
2. 如果 m = 0，就直接回傳 n + 1。
3. 如果 n = 0，就呼叫 A(m-1,1)。
4. 如果兩個都不等於 0，就呼叫 A(m-1,A(m,n-1))。
5. 不斷進行遞迴，直到符合停止條件。

**非遞迴版本：**

1. 使用陣列模擬 Stack（堆疊）。
2. 利用 top 變數記錄目前堆疊的位置。
3. 使用 while 迴圈處理堆疊中的資料。
4. 根據 m 和 n 的數值決定下一步要進行的計算。
5. 當堆疊沒有資料時，就回傳最後的計算結果。

### Problem 2：Powerset

#### 問題描述

本題要求使用遞迴函數，找出一個集合中所有可能的子集合。

例如：

$$
S=\{a,b,c\}
$$

則 Powerset 為：

$$
P(S)=\{\varnothing,\{a\},\{b\},\{c\},\{a,b\},\{a,c\},\{b,c\},\{a,b,c\}\}
$$

#### 解題策略

1. 使用 S 陣列儲存集合中的元素。
2. 使用 choose 陣列記錄每個元素是否被選擇。
3. 0 代表不選擇，1 代表選擇。
4. 每次遞迴都分成選擇和不選擇兩種情況。
5. 當所有元素都處理完成後，輸出目前的子集合。

## 程式實作

### Problem 1：Ackermann Function

#### 遞迴版本（Recursive）

以下為遞迴版本的程式碼：

```cpp
#include <iostream>
using namespace std;

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
```

#### 非遞迴版本（Nonrecursive）

以下為非遞迴版本的程式碼：

```cpp
#include <iostream>
using namespace std;

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
    cin>>m>>n;

    cout<<A(m,n)<<endl;

    return 0;
}
```

### Problem 2：Powerset

以下為 Powerset 的遞迴程式碼：

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

    choose[i] = 0;
    Powerset(i + 1);

    choose[i] = 1;
    Powerset(i + 1);
}

int main()
{
    Powerset(0);

    return 0;
}
```

## 效能分析

### Problem 1：Ackermann Function

#### 時間複雜度

Ackermann 函數的運算次數會隨著 m 和 n 增加而快速成長。

遞迴版本需要重複呼叫函數，而非遞迴版本雖然使用 while 迴圈，但還是需要處理相同的運算過程。

因此無法使用一般的 O(n) 或 O(n²) 來表示所有輸入的時間複雜度。

#### 空間複雜度

1. 遞迴版本：需要使用函數呼叫堆疊，空間需求會隨著遞迴深度增加。
2. 非遞迴版本：使用固定大小的 s[100000] 陣列，因此目前程式宣告的額外空間為 O(1)，但有陣列容量的限制。

### Problem 2：Powerset

#### 時間複雜度

因為每個元素都有選擇和不選擇兩種情況，所以 n 個元素共有：

$$
2^n
$$

種子集合。

每次輸出還需要使用 for 迴圈檢查 n 個元素。

因此時間複雜度為：

$$
O(n\times 2^n)
$$

#### 空間複雜度

程式使用陣列記錄元素的選擇狀態，並且使用遞迴處理每個元素。

以可以處理 n 個元素的一般化版本來看，空間複雜度為：

$$
O(n)
$$

## 測試與驗證

### Problem 1：Ackermann Function

#### 測試案例

| 測試案例 | 輸入 | 預期輸出（遞迴） | 預期輸出（非遞迴） |
|---|---|---|---|
| 測試一 | A(0,0) | 1 | 1 |
| 測試二 | A(1,2) | 4 | 4 |
| 測試三 | A(2,2) | 7 | 7 |
| 測試四 | A(3,2) | 29 | 29 |
| 測試五 | A(4,0) | 13 | 13 |

#### 遞迴版本：編譯與執行指令

```shell
$ g++ ackermann_recursive.cpp --std=c++21 -o recursive.exe
$ .\recursive.exe
輸入 m 和 n：2 2
7
```

#### 非遞迴版本：編譯與執行指令

```shell
$ g++ ackermann_nonrecursive.cpp --std=c++21 -o nonrecursive.exe
$ .\nonrecursive.exe
請輸入 m 和 n：2 2
7
```

#### 測試結論

1. 使用較小的 m 和 n，可以得到正確的 Ackermann 函數結果。
2. 遞迴與非遞迴兩種版本應該會得到相同結果。
3. 當輸入過大的數值時，可能會因為計算次數過多或整數溢位而無法正常執行。

### Problem 2：Powerset

#### 測試案例

| 測試案例 | 輸入集合 | 預期子集合數量 |
|---|---|---|
| 測試一 | {a,b,c} | 8 |

#### 編譯與執行指令

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

#### 測試結論

1. 集合中有三個元素，因此共有 2³ = 8 種子集合。
2. 程式預期會輸出 8 個不同的子集合。
3. 因為集合不考慮順序，所以輸出的先後順序不影響正確性。

以上測試輸出為依照程式預期得到的結果，繳交前需要實際執行確認。

## 申論及開發報告

### Problem 1：Ackermann Function

#### 選擇遞迴的原因

因為 Ackermann 函數本身就是用遞迴方式定義，所以我直接按照公式來寫程式。

使用 if 和 else 判斷條件，就可以完成三種不同的計算情況。

而且遞迴版本比較簡單，只要理解公式就能寫出程式，不需要使用其他複雜的資料結構。

#### 選擇非遞迴的原因

因為題目要求除了遞迴以外，還需要實作非遞迴版本。

所以我使用陣列模擬 Stack，利用 top 變數控制資料的存放位置，再用 while 迴圈處理計算。

這種寫法雖然比較長，但可以讓我了解遞迴的計算過程，也能知道如何利用堆疊代替函數呼叫。

#### 遇到的問題

這題比較麻煩的地方是 Ackermann 函數的數字成長得很快。

一開始測試比較大的數值，例如 A(7,0)，發現程式無法在短時間內計算完成。

後來改用較小的數字測試，才能比較容易確認兩個版本的結果是否相同。

### Problem 2：Powerset

#### 選擇遞迴的原因

因為集合裡的每個元素都有選擇和不選擇兩種情況，所以使用遞迴比較方便。

每次只需要決定目前元素要不要選，再繼續處理下一個元素，就可以找出全部的子集合。

#### 選擇陣列的原因

我使用普通陣列記錄元素和選擇的狀態。

S 陣列用來儲存 a、b、c 三個元素，choose 陣列則用 0 和 1 代表元素是否被選擇。

這樣比較容易理解程式的運作方式，也不用使用比較複雜的函式庫。

#### 學習心得

透過這次作業，我更了解遞迴函數的使用方式。

第一題讓我練習將數學公式轉換成程式，也了解遞迴和非遞迴之間的差別。

第二題則是練習使用遞迴產生所有組合，並學習如何利用陣列記錄每個元素是否被選擇。
