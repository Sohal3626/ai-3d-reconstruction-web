Module.onRuntimeInitialized = function() {
    console.log("모듈 로드 완료");
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');

    Module._init_canvas(800, 600);
    console.log("캔버스 초기화 완료");

    const path = "/test_data/testModel.obj";
    const pathPtr = Module.allocateUTF8(path);
    Module._load_obj(pathPtr);
    Module._set_rotation(0, 0, 0);
    Module._set_model_translation(0, 0.0, -2);
    Module._set_view_translation(0, -0.2, 0);
    const ptr = Module._render(1)

    const pixels = new Uint8ClampedArray(Module.HEAPU8.buffer, ptr, 800 * 600 * 4);
    ctx.putImageData(new ImageData(pixels, 800, 600), 0, 0);
}
