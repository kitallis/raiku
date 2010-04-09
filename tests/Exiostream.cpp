#include <ruby.h>
#include <string.h>
#include <vector>
#include <iostream>

typedef VALUE (ruby_method)(...);

extern "C" VALUE t_init(VALUE self)
{
   VALUE arr;
   arr = rb_ary_new();
   rb_iv_set(self, "@arr", arr);
   return self;
}

// push VALUE inside a ruby array as an argument from a method
extern "C" VALUE t_add(VALUE self, VALUE obj)
{  
   VALUE arr;
   arr = rb_iv_get(self, "@arr");
   rb_ary_push(arr, obj);
   return arr;
}

extern "C" VALUE t_foo(VALUE self)
{
   // iostream example stolen from an old draft
   using namespace std;
   
   vector<int> ii;
   for(int i=0; i<10; i++) 
   	 ii.push_back(i); 
   int k = 0;
   vector<int>::iterator i2;
   cout<<"Executing foo on <"<<self<<">"<<endl;
   for(i2=ii.begin(); i2!=ii.end(); i2++) {
     cout<<"ii["<<k++<<"] = "<<*i2<<endl; 
   }
   return self;
}

VALUE cTest;

extern "C" void Init_Test() 
{
   cTest = rb_define_class("Exiostream", rb_cObject);
   rb_define_method(cTest, "initialize", (ruby_method*) &t_init, /*n_args*/0);
   rb_define_method(cTest, "add", (ruby_method*) &t_add, 1);
   rb_define_method(cTest, "foo", (ruby_method*) &t_foo, 0);
}
