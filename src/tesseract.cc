#include <tesseract/baseapi.h>
#include <node_api.h>
#include "tesseract.h"
#include "common.h"

Tesseract::Tesseract(char* language_name = "por") {
	api = new tesseract::TessBaseAPI();

	if(api->Init(NULL, language_name))
		return;
}

void Tesseract::End() {
	api->End();
	image->End();
}

Tesseract::~Tesseract() {
}

void Tesseract::Destructor(napi_env env, void* nativeObject, void* finalize_hint) {
	Tesseract *tess = static_cast<Tesseract*>(nativeObject);
	tess->End();
	delete tess;
}

napi_value Tesseract::New(napi_env env, napi_callback_info info) {
	size_t argc = 1;
	napi_value argv[1];
	napi_value self;
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &self, nullptr));

	size_t language_name_length = 0;
	NAPI_CALL(env, napi_get_value_string_utf8(env, argv[0], nullptr, 0, &language_name_length));

	char language_name[language_name_length];
	NAPI_CALL(env, napi_get_value_string_utf8(env, argv[0], language_name, language_name_length + 1, &language_name_length));

	Tesseract* tess = new Tesseract(language_name);

	NAPI_CALL(env, napi_wrap(env, self, tess, Tesseract::Destructor, nullptr, &tess->wrapper));

	return self;
}

char* Tesseract::GetUTF8Text() {
	return api->GetUTF8Text();
}

napi_value Tesseract::GetUTF8Text(napi_env env, napi_callback_info info) {
	napi_value self;
	NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &self, nullptr));

	Tesseract *tess;
	NAPI_CALL(env, napi_unwrap(env, self, reinterpret_cast<void**>(&tess)));

	char* outText = tess->GetUTF8Text();

	napi_value result;
	NAPI_CALL(env, napi_create_string_utf8(env, outText, NAPI_AUTO_LENGTH, &result));

	tess->api->End();

	return result;
}

void Tesseract::SetImage(LeptonicaPix *image) {
	// image = pixRead(file_path);
	api->SetImage(image->image);
}

napi_value Tesseract::SetImage(napi_env env, napi_callback_info info) {
	size_t argc = 1;
	napi_value argv[argc];
	napi_value self;

	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &self, nullptr));

	Tesseract *tess;
	NAPI_CALL(env, napi_unwrap(env, self, reinterpret_cast<void**>(&tess)));

	LeptonicaPix *image;
	NAPI_CALL(env, napi_unwrap(env, argv[0], reinterpret_cast<void**>(&image)));

	tess->SetImage(image);

	return self;
}

napi_ref Tesseract::constructor;

void Tesseract::Init(napi_env env, napi_value exports) {
	napi_property_descriptor properties[] = {
		DECLARE_NAPI_PROPERTY("setImage", SetImage),
		DECLARE_NAPI_PROPERTY("getUTF8Text", GetUTF8Text)
	};

	napi_value cons;
	NAPI_CALL_RETURN_VOID(env, napi_define_class(env, "Tesseract", -1, New, nullptr, 2, properties, &cons));

	NAPI_CALL_RETURN_VOID(env, napi_create_reference(env, cons, 1, &constructor));

	NAPI_CALL_RETURN_VOID(env, napi_set_named_property(env, exports, "Tesseract", cons));
}

napi_value Init(napi_env env, napi_value exports) {
	Tesseract::Init(env, exports);
	LeptonicaPix::Init(env, exports);

	return exports;
}

NAPI_MODULE(tesseract, Init);