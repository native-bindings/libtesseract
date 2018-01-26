const tesseract = require('../build/Release/tesseract');
const assert = require('assert');

assert.deepEqual(new tesseract.Tesseract("por").setImage(
	new tesseract.Image(__dirname + '/screenshot.png')
).getUTF8Text().trim(), `diretrizes B
Significado de Diretrizes

substantivo feminino plural

Linhas a partir das quais um plano é traçado.

[Figurado] Esboços, planos delineados: o prefeito traçou novas diretrizes para o
município.

Metas ou propósitos que direcionam um trabalho; objetivos.

Conjunto de normas e critérios que determinam e direcionam o
desenvolvimento ou a criação de alguma coisa; procedimentos.

Etimologia (origem da palavra diretrizes). Plural de diretriz.

Definicão de Diretrizes`);