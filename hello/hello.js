const hello = require("./build/Release/hello");
console.log(" hello             :", hello);
console.log(` hello.helloWorld  : ${hello.helloWorld}`);
console.log(` hello.helloWorld(): ${hello.helloWorld()}`);
