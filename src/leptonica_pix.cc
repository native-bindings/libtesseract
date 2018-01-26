#include <node_api.h>
#include <leptonica/allheaders.h>
#include "common.h"
#include "leptonica_pix.h"

LeptonicaPix::LeptonicaPix(const char* file_path) {
	image = pixRead(file_path);
}

LeptonicaPix::~LeptonicaPix() {
	pixDestroy(&image);
}

void LeptonicaPix::Destructor(napi_env env, void* nativeObject, void* finalize_hint) {
	LeptonicaPix *image = static_cast<LeptonicaPix*>(nativeObject);
	pixDestroy(&image->image);
}

napi_value LeptonicaPix::New(napi_env env, napi_callback_info info) {
	size_t argc = 1;
	napi_value argv[argc];
	napi_value self;

	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &self, nullptr));

	size_t file_path_length = 0;
	NAPI_CALL(env, napi_get_value_string_utf8(env, argv[0], nullptr, 0, &file_path_length));

	char file_path[file_path_length];
	NAPI_CALL(env, napi_get_value_string_utf8(env, argv[0], file_path, file_path_length + 1, &file_path_length));

	LeptonicaPix* image = new LeptonicaPix(file_path);
	NAPI_CALL(env, napi_wrap(env, self, image, LeptonicaPix::Destructor, nullptr, &image->wrapper));

	return self;
}

napi_ref LeptonicaPix::constructor;

void LeptonicaPix::Init(napi_env env, napi_value exports) {
	napi_property_descriptor properties[] = {};

	napi_value cons;
	NAPI_CALL_RETURN_VOID(env, napi_define_class(env, "Image", -1, New, nullptr, 0, properties, &cons));

	napi_ref constructor;
	NAPI_CALL_RETURN_VOID(env, napi_create_reference(env, cons, 1, &constructor));

	NAPI_CALL_RETURN_VOID(env, napi_set_named_property(env, exports, "Image", cons));
}