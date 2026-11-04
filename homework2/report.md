# 41143268

作業二

## 解題說明

本題要求實現一個多項式加法，乘法以及帶入x所出來的一個結果。

### 解題策略

1. 使用動態陣列儲存多項式的係數與指數。

```cpp
class Term {
    friend class polynomial;
private:
    float coef;
    int Exp;
};

Term* TermArray;
int capacity;
int terms;
```

2. 陣列空間不足時，自動擴充容量。

```cpp
if (terms == capacity) {
    capacity *= 2;
    Term* temp = new Term[capacity];
    copy(TermArray, TermArray + terms, temp);
    delete[] TermArray;
    TermArray = temp;
}
```

3. 比較指數，相同指數的係數相加。

```cpp
if (TermArray[firstindex].Exp ==
    secondpolymial.TermArray[secondindex].Exp) {

    float sumCoef = TermArray[firstindex].coef +
                    secondpolymial.TermArray[secondindex].coef;

    resultpolynomial.newTerm(sumCoef, TermArray[firstindex].Exp);

    firstindex++;
    secondindex++;
}
```

4. 使用雙層迴圈進行多項式乘法。

```cpp
for (int i = 0; i < terms; i++) {
    for (int j = 0; j < secondpolymial.terms; j++) {

        float newCoef = TermArray[i].coef *
                        secondpolymial.TermArray[j].coef;

        int newExp = TermArray[i].Exp +
                     secondpolymial.TermArray[j].Exp;

        resultpolynomial.newTerm(newCoef, newExp);
    }
}
```

5. 將乘積中相同指數的項目合併，並將x次方多的排左邊。

```cpp
sort(resultpolynomial.TermArray,
     resultpolynomial.TermArray + resultpolynomial.terms,
     [](const Term& a, const Term& b) {
         return a.Exp > b.Exp;
     });

polynomial merged;

for (int i = 0; i < resultpolynomial.terms; ) {
    int exp = resultpolynomial.TermArray[i].Exp;
    float sum = 0;

    while (i < resultpolynomial.terms &&
           resultpolynomial.TermArray[i].Exp == exp) {
        sum += resultpolynomial.TermArray[i].coef;
        i++;
    }

    merged.newTerm(sum, exp);
}
```

6. 代入指定數值，計算代入x的多項式結果。

```cpp
float polynomial::Eval(float f) const {
    float result = 0;

    for (int i = 0; i < terms; i++) {
        result += TermArray[i].coef *
                  pow(f, TermArray[i].Exp);
    }

    return result;
}
```
## 程式實作

以下為主要程式碼：

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

class Term{
    friend class polynomial;
private:
    float coef;
    int Exp;
};

class polynomial{
private:
    Term* TermArray;
    int capacity;
    int terms;
public:
    polynomial():capacity(2),terms(0){
    TermArray = new Term[capacity];
    };

    polynomial(const polynomial& other) {
        capacity = other.capacity;
        terms = other.terms;
        TermArray = new Term[capacity];

        for (int i = 0; i < terms; i++)
            TermArray[i] = other.TermArray[i];
    }
    polynomial& operator=(const polynomial& other) {
        if (this == &other)
            return *this;
        Term* temp = new Term[other.capacity];

        for (int i = 0; i < other.terms; i++)
            temp[i] = other.TermArray[i];

        delete[] TermArray;

        TermArray = temp;
        capacity = other.capacity;
        terms = other.terms;

        return *this;
    }
    ~polynomial() {
        delete[] TermArray;
    }

    void newTerm(const float theCoef, const int theExp);

    polynomial Add(const polynomial& secondpolymial) ;
    polynomial Mult(const polynomial& secondpolymial) ;
    float Eval(float f) const;
    void print() const;
};

void polynomial::newTerm(const float theCoef,const int theExp){
    if (theCoef == 0)
        return;
    if (terms==capacity){
        capacity*=2;
        Term *temp = new Term[capacity];
        copy(TermArray,TermArray+terms,temp);
        delete []TermArray;
        TermArray = temp;
    }
    TermArray[terms].coef=theCoef;
    TermArray[terms].Exp =theExp;

    terms++;
}

polynomial polynomial::Add(const polynomial& secondpolymial) {
    polynomial resultpolynomial;
    int firstindex =0;
    int secondindex=0;
    while((firstindex<terms)&&(secondindex<secondpolymial.terms)){
        if((TermArray[firstindex].Exp ==secondpolymial.TermArray[secondindex].Exp)){
            float sumCoef = TermArray[firstindex].coef+secondpolymial.TermArray[secondindex].coef;
            if(sumCoef !=0){
                resultpolynomial.newTerm(sumCoef,TermArray[firstindex].Exp);
            }
            firstindex++;
            secondindex++;
        }
        else if(TermArray[firstindex].Exp<secondpolymial.TermArray[secondindex].Exp){
            resultpolynomial.newTerm(secondpolymial.TermArray[secondindex].coef,secondpolymial.TermArray[secondindex].Exp);
            secondindex++;
        }
        else{
            resultpolynomial.newTerm(TermArray[firstindex].coef,TermArray[firstindex].Exp);
            firstindex++;
        }  
    }
    while(firstindex<terms){
            resultpolynomial.newTerm(TermArray[firstindex].coef,TermArray[firstindex].Exp);
            firstindex++;
    }
    while (secondindex<secondpolymial.terms){
            resultpolynomial.newTerm(secondpolymial.TermArray[secondindex].coef,secondpolymial.TermArray[secondindex].Exp);
            secondindex++;
    }
    return resultpolynomial;
}

polynomial polynomial::Mult(const polynomial& secondpolymial) {
    polynomial resultpolynomial;
    for(int i=0;i<terms;i++){
        for (int j = 0; j < secondpolymial.terms; j++) {
            float newCoef =TermArray[i].coef *secondpolymial.TermArray[j].coef;
            int newExp =TermArray[i].Exp +secondpolymial.TermArray[j].Exp;

            resultpolynomial.newTerm(newCoef, newExp);
        }
    }
    sort(resultpolynomial.TermArray,resultpolynomial.TermArray + resultpolynomial.terms,[](const Term& a, const Term& b) {return a.Exp > b.Exp;});
    polynomial merged;

    for (int i = 0; i < resultpolynomial.terms; ) {
        int exp = resultpolynomial.TermArray[i].Exp;
        float sum = 0;

        while (i < resultpolynomial.terms &&
               resultpolynomial.TermArray[i].Exp == exp) {

            sum += resultpolynomial.TermArray[i].coef;
            i++;
        }
        merged.newTerm(sum, exp);
    }

    return merged;
}

float polynomial::Eval(float f) const {
    float result = 0;

    for (int i = 0; i < terms; i++) {
        result += TermArray[i].coef *pow(f, TermArray[i].Exp);
    }
    return result;
}
void polynomial::print() const {
    if (terms == 0) {
        cout << "0" << endl;
        return;
    }

    for (int i = 0; i < terms; i++) {
        float c = TermArray[i].coef;
        int e = TermArray[i].Exp;

        if (i > 0)
            cout << (c >= 0 ? " + " : " - ");
        else if (c < 0)
            cout << "-";

        float absCoef = abs(c);

        if (e == 0 || absCoef != 1)
            cout << absCoef;

        if (e > 0)
            cout << "x";

        if (e > 1)
            cout << "^" << e;
    }

    cout << endl;
}

int main() {
    polynomial P;
    polynomial Q;


    P.newTerm(3, 2);
    P.newTerm(2, 1);
    P.newTerm(1, 0);

    Q.newTerm(1, 1);
    Q.newTerm(4, 0);

    cout << "P(x) = ";
    P.print();

    cout << "Q(x) = ";
    Q.print();

    polynomial R = P.Add(Q);
    cout << "Add = ";
    R.print();

    polynomial M = P.Mult(Q);
    cout << "Mult = ";
    M.print();

    cout << "Eval P(2) = " << P.Eval(2) << endl;

    return 0;
}
```

## 效能分析

1. 動態陣列新增項目 newTerm()
時間複雜度：O(1)，擴充陣列時為 O(n)。
說明：一般新增只需常數時間，容量不足時需複製原本資料。
空間複雜度：O(n)。
說明：使用動態陣列儲存 n 個項目，擴充時需建立新陣列並複製資料。


3. 多項式加法 Add()
時間複雜度：O(n + m)。
說明：使用兩個索引比較指數，各項最多處理一次。
空間複雜度：O(n + m)。
說明：建立新陣列儲存相加結果，最多需要 n + m 個項目的空間。


5. 多項式乘法 Mult()
時間複雜度：O(n × m × log(n × m))。
說明：因為雙層迴圈產生乘積，雙迴圈為O(n^2)，log(n × m)為再排序並合併相同指數所產生的時間複雜度。
空間複雜度：O(n × m)。
說明：雙層迴圈最多產生 n × m 個乘積項目，需額外陣列儲存及合併結果。

7. 多項式求值 Eval()
時間複雜度：O(n)。
說明：逐項計算係數與次方的乘積，累加得到結果。
空間複雜度：O(1)。
說明：只使用固定數量的變數儲存計算結果，不需額外陣列。

9. 輸出多項式 print()
時間複雜度：O(n)。
說明：逐項讀取並輸出係數和指數，不需要額外陣列。
空間複雜度：O(1)。
說明：逐項讀取並輸出資料，只使用固定數量的變數。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 | 預期輸出 | 實際輸出 |
|----------|----------|----------|----------|
| 測試一 | P=3x²+2x+1，Q=x+4，x=2 | Add=3x^2+3x+5<br>Mult=3x^3+14x^2+9x+4<br>Eval=17 | Add=3x²+3x+5<br>Mult=3x³+14x²+9x+4<br>Eval=17 |
| 測試二 | P=2x+3，Q=x+1，x=1 | Add=3x+4<br>Mult=2x^2+5x+3<br>Eval=5 | Add=3x + 4<br>Mult=2x^2 + 5x + 3<br>Eval=5 |
| 測試三 | P=x²+2x+1，Q=x+2，x=3 | Add=x^2+3x+3<br>Mult=x^3+4x^2+5x+2<br>Eval=16 | Add=x^2 + 3x + 3<br>Mult=x^3 + 4x^2 + 5x + 2<br>Eval=16 |

### 編譯與執行指令

```shell
D:\code\C++> cmd /C "set "DEBUGINFOD_URLS=" && c:\Users\awer1\.vscode\extensions\ms-vscode.cpptools-1.35.6-win32-x64\debugAdapters\bin\WindowsDebugLauncher.exe --stdin=Microsoft-MIEngine-In-0fu5b5nn.5sl --stdout=Microsoft-MIEngine-Out-d50ajhps.yaw --stderr=Microsoft-MIEngine-Error-5sd1wloe.pbt --pid=Microsoft-MIEngine-Pid-ickz4ygb.h3b --dbgExe=C:\mingw64\bin\gdb.exe --interpreter=mi "
P(x) = 3x^2 + 2x + 1
Q(x) = x + 4
Add = 3x^2 + 3x + 5
Mult = 3x^3 + 14x^2 + 9x + 4
Eval P(2) = 17

```

### 結論

本次作業使用 C++ 的 Class 與動態陣列實作多項式運算，完成 Add、Mult、Eval 三種功能。透過這次實作，更加了解物件導向、動態記憶體管理及多項式的運算方式。

一開始不熟悉 `new`、`delete[]` 和 `copy()` 的使用方式，也曾忘記在新增項目後使用 `terms++`，導致程式一直輸出 0。
另外，`if (theCoef == 0)` 忘記加上 `return`，造成陣列容量無法正常擴充，導致記憶體越界及程式異常。
經過修改後，了解動態陣列需要在容量不足時擴充，並正確更新項目數量。

在 Add() 中，也曾經比較錯誤的陣列位置、忘記增加 `firstindex`，以及將處理剩餘項目的 `while` 迴圈放錯位置。
修正後，了解需要透過兩個索引比較指數，相同指數則係數相加，不同指數則先處理指數較大的項目，最後再加入剩餘項目。

透過這次作業，除了學會多項式的加法、乘法及求值，也讓我知道我對 Class、指標與動態陣列的使用方式還不熟。
這次遇到的主要問題包含陣列越界、索引控制錯誤、迴圈位置錯誤及函式宣告不一致。透過逐步檢查與修正，了解到程式即使只有少寫一行，也可能影響整體執行結果。
未來撰寫程式時，會更加注意記憶體管理、迴圈條件與類別成員的使用方式。

## 申論及開發報告

### 選擇遞迴的原因

## 申論及開發報告

### 一、選擇 Term 類別的原因

在本程式中，使用 `Term` 類別儲存多項式的單一項目，每個項目包含係數（coef）與指數（Exp）。

例如：

$$
3x^2+2x+1
$$

可以拆成三個 Term：

- (3, 2)：代表 3x²
- (2, 1)：代表 2x
- (1, 0)：代表常數 1

```cpp
class Term {
    friend class polynomial;
private:
    float coef;
    int Exp;
};
```

使用 `private` 保護資料，並透過 `friend class polynomial` 讓 polynomial 類別能夠存取係數與指數。

這樣能將每一項的資料集中管理，方便後續進行多項式運算。

### 二、選擇 polynomial 類別的原因

`polynomial` 類別負責管理整個多項式，使用動態陣列儲存多個 Term。

```cpp
class polynomial {
private:
    Term* TermArray;
    int capacity;
    int terms;
};
```

其中：

- `TermArray`：儲存多項式的所有項目。
- `capacity`：陣列目前可容納的項目數量。
- `terms`：多項式實際儲存的項目數量。

使用動態陣列的原因是多項式的項數不固定，當陣列容量不足時，可以自動擴充空間。

這種設計可以依照實際需求配置記憶體，不需要事先設定固定的項數上限。

### 三、Add() 多項式加法的設計概念

多項式相加時，只有指數相同的項目才能合併。

例如：

$$
(3x^2+2x+1)+(x+4)
$$

$$
=3x^2+3x+5
$$

程式使用兩個索引，分別讀取兩個多項式的項目。

```cpp
if (TermArray[firstindex].Exp ==
    secondpolymial.TermArray[secondindex].Exp) {

    float sumCoef = TermArray[firstindex].coef +
                    secondpolymial.TermArray[secondindex].coef;

    resultpolynomial.newTerm(
        sumCoef, TermArray[firstindex].Exp
    );

    firstindex++;
    secondindex++;
}
```

當指數相同時，將係數相加；指數不同時，先加入指數較大的項目。

這種方法適合已經按照指數由大到小排列的多項式，可以依序完成加法，不需要重新排序。

### 四、Mult() 多項式乘法的設計概念

多項式乘法需要將第一個多項式的每一項，分別乘上第二個多項式的所有項目。

乘法規則為：

$$
(ax^m)(bx^n)=abx^{m+n}
$$

例如：

$$
(3x^2)(2x)=6x^3
$$

程式使用雙層迴圈進行乘法：

```cpp
for (int i = 0; i < terms; i++) {
    for (int j = 0; j < secondpolymial.terms; j++) {

        float newCoef = TermArray[i].coef *
                        secondpolymial.TermArray[j].coef;

        int newExp = TermArray[i].Exp +
                     secondpolymial.TermArray[j].Exp;

        resultpolynomial.newTerm(newCoef, newExp);
    }
}
```

完成乘法後，可能產生指數相同的項目，因此再利用 `sort()` 排序，並將相同指數的係數合併。
使用雙層迴圈可以確保每一組項目都完成相乘，適合實作基本的多項式乘法。
### 五、Eval() 多項式求值的設計概念

`Eval()` 的功能是將指定的數值代入多項式，計算最後的結果。

例如：

$$
P(x)=3x^2+2x+1
$$

當 x = 2 時：

$$
P(2)=3(2)^2+2(2)+1=17
$$

程式利用 `pow()` 計算次方，再將每一項的結果加總。

```cpp
float polynomial::Eval(float f) const {
    float result = 0;

    for (int i = 0; i < terms; i++) {
        result += TermArray[i].coef *
                  pow(f, TermArray[i].Exp);
    }

    return result;
}
```

使用迴圈逐項計算，可以支援不同項數與指數的多項式，不需要針對每一種多項式另外撰寫公式。
本程式利用 `Term` 儲存單一項目的係數與指數，再透過 `polynomial` 類別及動態陣列管理整個多項式。
`Add()` 使用索引比較指數，`Mult()` 使用雙層迴圈完成乘法與同類項合併，`Eval()` 則透過迴圈與 `pow()` 計算多項式的數值。
這種設計將資料儲存與運算功能整合在類別中，使程式結構清楚，也方便未來增加多項式減法、微分等其他功能。
