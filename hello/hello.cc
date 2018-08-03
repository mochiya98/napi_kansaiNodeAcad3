#include <node_api.h>
#include <assert.h>

// napi_valueは"jsの変数"だと思えばだいたいOK

/*
	ここから下でやっていること
	function NodeHelloWorld(){
		let hw = "Hello? Hello!!";
		return hw;
	}
*/

napi_value NodeHelloWorld(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value hw;
  status = napi_create_string_utf8(env, "Hello? Hello!!", NAPI_AUTO_LENGTH, &hw);
  assert(status == napi_ok);
  //NAPI_AUTO_LENGTHを固定値に変えると\0を含む文字列が作れます。。
  return hw;
}

/*
	ここから下でやっていること
	let definePort = 8080
	exports {
		helloWorld: NodeHelloWorld,
		definePort,
	}
*/

#define DECLARE_NAPI_METHOD(name, func) \
  { name, 0, func, 0, 0, 0, (napi_property_attributes)(napi_default | napi_enumerable), 0 }
#define DECLARE_NAPI_VALUE(name, val) \
  { name, 0, 0, 0, 0, val, (napi_property_attributes)(napi_default | napi_enumerable), 0 }

napi_value ModuleExports(napi_env env, napi_value exports) {
	napi_status status;
	
	napi_value definePort;
	status = napi_create_int32(env, 8080, &definePort);
	if (status != napi_ok) return nullptr;
	
	napi_property_descriptor desc[] = {
		DECLARE_NAPI_METHOD("helloWorld", NodeHelloWorld),
		DECLARE_NAPI_VALUE("definePort", definePort)
		//文字列や数値もexportできます。。
	};
	status = napi_define_properties(
		env,
		exports,
		sizeof(desc)/sizeof(napi_property_descriptor),
		(napi_property_descriptor*)&desc
	);
	if (status != napi_ok) return nullptr;
	return exports;
}
NAPI_MODULE(NODE_GYP_MODULE_NAME, ModuleExports)
