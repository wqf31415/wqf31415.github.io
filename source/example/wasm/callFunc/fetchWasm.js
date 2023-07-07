function fetchAndInstantiate(url, importObj) {
  return fetch(url) // 获取 .wasm
    .then(resp => resp.arrayBuffer()) // 将响应转换成 ArrayBuffer
    .then(arrBuf => WebAssembly.instantiate(arrBuf, importObj))
    .then(res => {
		console.log('res:',res)
		return res.instance;
	); // 使用 WebAssembly.instantiate() 将 ArrayBuffer 编译和实例化
}
