# tesseract_bindings

Tesseract OCR bindings to NodeJS

## Dependencies
```
sudo apt-get install -y tesseract-ocr tesseract-ocr-eng
```

## Installation
```
npm install --save tesseract_bindings
```

## Usage
```js
const {
	Tesseract,
	Image
} = require('tesseract_bindings');

const text = new Tesseract("eng").setImage(
	new Image(__dirname + "/image.png")
).getUTF8Text();
```