#include "../svm_struct_api.h"
#include <opencv2/core.hpp>

#include <iostream>
using std::cout;
using std::endl;

void printS(SAMPLE s)
{
    cout<<"SAMPLE"<<endl;
    cout<<"s.n="<<s.n<<endl;
    for (int i=0; i<s.n;i++){
      cout<<i<<endl;
      cout<<s.examples[i].x.unary<<endl;
      cout<<s.examples[i].x.edges <<endl;
      cout<<s.examples[i].x.pairwise<<endl;
      cout<<s.examples[i].y.label<<endl;
      cout<<endl;
    }
}

int main(int argc, char* argv[])
{
  const int n_examples = 5;
  // write
  {
    SAMPLE s;
    s.n = n_examples;
    EXAMPLE *examples = new EXAMPLE[n_examples];
    for (int i=0; i<n_examples;i++){
      examples[i].x.unary.create(2,5,CV_32F);
      examples[i].x.edges.create(3,2,CV_32S);
      examples[i].x.pairwise.create(4,3, CV_32F);
      examples[i].y.label.create(2,1,CV_32S);
    }
    s.examples = examples;
    write_struct_examples("s", s);

#if 1
    printS(s);
#endif
  }
  cout<<"read SAMPLE from file"<<endl;
  // read
  {
    SAMPLE s = read_struct_examples("s", NULL);
    printS(s);
  }

  return 0;
}
