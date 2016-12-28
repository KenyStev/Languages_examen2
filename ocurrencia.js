var HashMap = require('hashmap');

function ocur(arr){
	has = new HashMap()
	for (var i = arr.length - 1; i >= 0; i--) {
		has.set(arr[i],0)
	};
	for (var i = arr.length - 1; i >= 0; i--) {
		v = has.get(arr[i]) + 1
		has.set(arr[i],v)
	};
	let m = []
	has.forEach(function(value,key){
		m.push({"Nombre:":key,"Ocurrencia":value})
	})
	return m
}

r = [5,6,9,7,5,1,4,7,3,5]
console.log(ocur(r))