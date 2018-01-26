#ifndef LEPTONICA_PIX_H_
#define LEPTONICA_PIX_H_

#include <node_api.h>
#include <leptonica/allheaders.h>

class LeptonicaPix {
public:
	static napi_value New(napi_env env, napi_callback_info info);
	static void Init(napi_env env, napi_value exports);
	static napi_ref constructor;
	void End();
	Pix* image;

private:
	LeptonicaPix(const char* file_path);
	~LeptonicaPix();
	static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);

	napi_ref wrapper;
};

#endif