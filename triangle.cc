// addon.cc
#include <node.h>

namespace demo {

using v8::Exception;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Array;
using v8::String;
using v8::Value;

// This is the implementation of the "add" method
// Input arguments are passed using the
// const FunctionCallbackInfo& args struct

void Triangulate(const FunctionCallbackInfo<Value>& args) {

  Isolate* isolate = args.GetIsolate();

  // Check the number of arguments passed.

 if (args.Length() < 3) {
    // Throw an Error that is passed back to JavaScript

    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));

    return;
  }
  // Check the argument types

  if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
     return;
  }
  // Perform the operation

  Local<Object> obj = Object::New(isolate);

  int height = args[0]->NumberValue();
  int width = args[1]->NumberValue();
  int deep = args[2]->NumberValue();

  int matrix[8][3] = {
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},
    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
                     };

  int pattern[36] = {1,0,4,4,5,1, 2,3,7,7,6,2, 1,3,2,2,0,1, 4,6,7,7,5,4, 2,6,4,4,0,2, 1,5,7,7,3,1};

  double vertices[8][3];
//  int vertices[8][3];

//  Local<Array> vert = Array::New(isolate);
  for(int i = 0; i<8; i++){
    Local<Array> buf = Array::New(isolate);
    vertices[i][0] = matrix[i][0] * width - width/2;
//    buf->Set(Number::New(isolate,0), Number::New(isolate,vertices[i][0]));
    vertices[i][1] = matrix[i][1] * height - height/2;
//    buf->Set(Number::New(isolate,1), Number::New(isolate,vertices[i][1]));
    vertices[i][2] = matrix[i][2] * deep - deep/2;
//    buf->Set(Number::New(isolate,2), Number::New(isolate,vertices[i][2]));

//    vert->Set(Number::New(isolate, i), buf);
  }

//  obj->Set(String::NewFromUTF8(isolate, "vertices"),  )

  int triangles[12][3];

  // Создадим 12 треугольников
  // Создадим массив для треугольников
  Local<Array> triMass = Array::New(isolate);
  int counter = 0;
  for (int triCount = 0; triCount < 12; triCount++){
    // Для каждого треугольника зададим три вершины
    Local<Array> vertMass = Array::New(isolate);
    for (int vertCount = 0; vertCount < 3; vertCount++){
      // Для каждой вершины зададим три координаты
      Local<Array> coordMass = Array::New(isolate);
      for (int coordCount = 0; coordCount < 3; coordCount++){
//        double res =
        coordMass->Set(Number::New(isolate, coordCount), Number::New(isolate, vertices[pattern[counter]][coordCount]));
      }
      counter++;
      vertMass->Set(Number::New(isolate, vertCount), coordMass);
    }
    triMass->Set(Number::New(isolate, triCount), vertMass);
  }


//  double value = args[0]->NumberValue() + args[1]->NumberValue() + args[2]->NumberValue();

//  Local<Number> num = Number::New(isolate, value);
  // Set the return value (using the passed in
  // FunctionCallbackInfo<Value>&)

//  Local<Function> cb = Local<Function>::Cast(args[3]);

//  const unsigned argc = 1;

//  Local<Value> argv[argc] = {String::NewFromUtf8(isolate, res)};

//  cb->Call(Null(isolate), argc, argv);




  args.GetReturnValue().Set(triMass);
//  args.GetReturnValue().Set(vert);
}

void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "triangulate", Triangulate);
}

NODE_MODULE(addon, Init)

}  // namespace demo
