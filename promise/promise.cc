#include <node_api.h>
#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
using namespace std;

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

//きゃりあー
struct ia_carrier{
	char* inp;
	size_t len;
	char* out;
	napi_ref ref_args0;
	napi_ref ref_promise;
	napi_deferred deferred;
	napi_value promise;
};

void NodeAsyncDoIncrementAll(napi_env env, void* data) {
	ia_carrier* carrier=static_cast<ia_carrier*>(data);
	
	//一時出力バッファ確保
	carrier->out=(char *)malloc(carrier->len);
	
	//おもい処理
	Sleep(500);
	
	//increment
	for(size_t i=0; i < carrier->len; i++){
		carrier->out[i] = carrier->inp[i] + 1;
	}
}
void NodeAsyncEndIncrementAll(napi_env env, napi_status status, void* data) {
	napi_value result;
	ia_carrier* carrier=static_cast<ia_carrier*>(data);
	
	//戻り値を作る
	status = napi_create_buffer_copy(env, carrier->len, (void*)carrier->out, (void**)NULL, &result);
	assert(status == napi_ok);
	
	//Promiseをresolve
 	status = napi_resolve_deferred(env, carrier->deferred, result);
 	assert(status == napi_ok);
 	
 	//Promiseのrefを解除
 	status = napi_delete_reference(env, carrier->ref_args0);
 	assert(status == napi_ok);
 	status = napi_delete_reference(env, carrier->ref_promise);
 	assert(status == napi_ok);
	
	//一時出力バッファの開放
	free(carrier->out);
	free(carrier);
}

napi_value NodeIncrementAll(napi_env env, napi_callback_info info) {
	napi_status status;
	
	size_t argc = 1;
	napi_value args[1];
	status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
	assert(status == napi_ok);
	if (argc < 1) {
		napi_throw_type_error(env, nullptr, "Wrong number of arguments");
		return nullptr;
	}
	ia_carrier* carrier=(ia_carrier*)malloc(sizeof(ia_carrier));
	
	//arguments[0]のBufferの中身のポインタと長さを取得
	status = napi_get_buffer_info(env, args[0], (void**)&carrier->inp, (size_t*)&carrier->len);
	assert(status == napi_ok);
	
	//CreatePromise
	status = napi_create_promise(env, &carrier->deferred, &carrier->promise);
	assert(status == napi_ok);
	
	//CreateReferences
	status = napi_create_reference(env, args[0], 1, &carrier->ref_args0);
	assert(status == napi_ok);
	status = napi_create_reference(env, carrier->promise, 1, &carrier->ref_promise);
	assert(status == napi_ok);
	
	//CreateAsyncWork
	napi_async_work aw;
	napi_value aw_name;
	status = napi_create_string_latin1(env, "NodeAsyncIncrementAll", NAPI_AUTO_LENGTH, &aw_name);
	assert(status == napi_ok);
	status = napi_create_async_work(
		env,
		nullptr,
		aw_name,
		NodeAsyncDoIncrementAll,
		NodeAsyncEndIncrementAll,
		carrier,
		&aw
	);
	assert(status == napi_ok);
	
	//QueueAsyncWork
	status = napi_queue_async_work(env, aw);
	assert(status == napi_ok);
	
	return carrier->promise;
}

#define DECLARE_NAPI_METHOD(name, func) \
  { name, 0, func, 0, 0, 0, (napi_property_attributes)(napi_default | napi_enumerable), 0 }

napi_value ModuleExports(napi_env env, napi_value exports) {
	napi_status status;
	
	napi_property_descriptor desc[] = {
		DECLARE_NAPI_METHOD("incrementAll", NodeIncrementAll),
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
