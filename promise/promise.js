const promise = require("./build/Release/promise");
(async ()=>{
	let b = Buffer.from([0, 1, 2]);
	while(true){
		b=await promise.incrementAll(b);//500msかかる
		console.log(b, "500msおきにincrementします");
	}
})();

setInterval(function(){
	console.log("非同期の証拠！");
},100);