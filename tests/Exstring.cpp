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

// ruby block yielding test
extern "C" VALUE t_blocks(VALUE self) 
{
   VALUE cmd = rb_str_new2("puts "DONE");
   rb_yield(Qnil);
   rb_funcall(self, rb_intern("instance_eval"), 1, cmd);
   cout << self;
   return Qnil;
}

// a string.h implemented from a document found on haiku-os.org
extern "C" VALUE t_strings(VALUE self, VALUE a)
{
   char string[30];
   memset(string,0,30);
   for(char i=0; i<26; i++) 
	 string[i] = 65 + i;
   printf("String contains: %s\n", string);
   sprintf(string,"%f",3.1415927);
   printf("String changed, now it has  %s\n: ", string);
   cout << "a is" << a;
   return self;
}

VALUE cTest;

extern "C" void Init_Test() 
{
   cTest = rb_define_class("Exstring", rb_cObject);
   rb_define_method(cTest, "initialize", (ruby_method*) &t_init, /*n_args*/0);
   rb_define_method(cTest, "strings", (ruby_method*) &t_strings, 1);
   rb_define_method(cTest, "blocks", (ruby_method*) &t_blocks, 0);
}
