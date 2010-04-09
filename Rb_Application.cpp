#include <ruby.h>
#include <Window.h>
#include <Application.h>
#include "HelloWorldCtor.h"

HelloWorldWindowApplication::HelloWorldWindowApplication() : BApplication("application/x-vnd.HelloWorldCtor")
{		
	BWindow* hw = new BWindow(BRect(10,10,210,110), "I GOT SPAWNED THROUGH RUBY!", B_TITLED_WINDOW, NULL);    			
    hw->Show();
}

typedef VALUE (ruby_method)(...);

extern "C" VALUE t_init(VALUE self)
{
   VALUE arr;
   arr = rb_ary_new();
   rb_iv_set(self, "@arr", arr);
   return self;
}

extern "C" VALUE t_run(VALUE self)
{
	HelloWorldWindowApplication myApp;
	myApp.Run();
	return self;
}

/*
extern "C" VALUE t_ctor(VALUE self)
{  
	HelloWorldWindowApplication::HelloWorldWindowApplication() : BApplication("application/x-vnd.hw")
   	{		
      BWindow* myHW = new BWindow(BRect(10,10,210,110), "I GOT SPAWNED THROUGH RUBY!", B_TITLED_WINDOW, NULL);    			
      myHW->Show();
    }
    return self;
}
*/

extern "C" VALUE t_rect(VALUE self) 
{
   VALUE cmd = rb_str_new2("puts 'heya'");
   rb_yield(Qnil);
   rb_funcall(self, rb_intern("instance_eval"), 1, cmd);
   return Qnil;
}

VALUE cTest;

extern "C" void Init_Rb_Application() 
{
   cTest = rb_define_class("Rb_Application", rb_cObject);
   rb_define_method(cTest, "initialize", (ruby_method*) &t_init, /*n_args*/0);
   rb_define_method(cTest, "run", (ruby_method*) &t_run, 0);
   rb_define_method(cTest, "rect", (ruby_method*) &t_rect, 0);
}
