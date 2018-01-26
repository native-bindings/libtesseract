{
	"targets": [{
		"target_name": "tesseract",
		"sources": [
			"./src/tesseract.cc",
			"./src/leptonica_pix.cc"
		],
		"libraries": [
			"<!@(pkg-config --libs --cflags tesseract lept)"
		]
	}]
}