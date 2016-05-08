#include "iif.h"
#include <iostream>
using namespace iif;

int loopFunction(int _reverved_input_[]) {
int i = _reverved_input_[0];
int k = _reverved_input_[1];

iif_assume( 0<=k && k <= 10 && i == 0);
while( i < 1024 * k)
{
recordi(i, k);
i += k;
}
recordi(i, k);
iif_assert(i == 1024 * k);
return 0;
}

int main(int argc, char** argv)
 {
iifContext context("../tmp/count_by_k_true-unreach-call.var", loopFunction, "loopFunction", "../tmp/count_by_k_true-unreach-call.ds");
context.addLearner("linear");
context.addLearner("poly");
context.addLearner("conjunctive");
return context.learn("../tmp/count_by_k_true-unreach-call.cnt", "../tmp/count_by_k_true-unreach-call");
}
