
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
