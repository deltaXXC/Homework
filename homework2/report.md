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

1. 時間複雜度：程式的時間複雜度為 $O(\log n)$。
2. 空間複雜度：空間複雜度為 $O(100\times \log n + \pi)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $n = 0$      | 0        | 0        |
| 測試二   | $n = 1$      | 1        | 1        |
| 測試三   | $n = 3$      | 6        | 6        |
| 測試四   | $n = 5$      | 15       | 15       |
| 測試五   | $n = -1$     | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
P(x) = 3x^2 + 2x + 1
Q(x) = x + 4
Add = 3x^2 + 3x + 5
Mult = 3x^3 + 14x^2 + 9x + 4
Eval P(2) = 17

```

### 結論

1. 程式能正確計算 $n$ 到 $1$ 的連加總和。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
