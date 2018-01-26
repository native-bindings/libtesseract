#ifndef TESSERACT_H_
#define TESSERACT_H_

#include <node_api.h>
#include "leptonica_pix.h"

class Tesseract {
public:
	static napi_ref constructor;
	static void Init(napi_env env, napi_value exports);
	void End();
	char* GetUTF8Text();

private:
	Tesseract(char* language_name);
	~Tesseract();

	static napi_value New(napi_env env, napi_callback_info info);
	static napi_value SetImage(napi_env env, napi_callback_info info);
	static napi_value GetUTF8Text(napi_env env, napi_callback_info info);
	static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);

	void SetImage(LeptonicaPix* image);

	tesseract::TessBaseAPI* api;
	napi_env env;
	napi_ref wrapper;
	LeptonicaPix* image;
};

#endif