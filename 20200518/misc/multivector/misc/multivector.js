var GA = function () {
    function e(n) {
	var result = [];
	result[1 << n] = 1;
	return result;
    }
    function cdot(a, b) { return mul([0.5], add(mul(a, b), mul(b, a))) }
    function neg(x) { return mul([-1], x) }
    function bitCount(i) {
	// Note that unsigned shifting (>>>) is not required.
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	i = (i + (i >> 4)) & 0x0F0F0F0F;
	i = i + (i >> 8);
	i = i + (i >> 16);
	return i & 0x0000003F;
    }
    function reorderingSign(a, b) {
	a >>= 1;
	var sum = 0;
	while (a != 0) {
	    sum += bitCount(a & b);
	    a >>= 1;
	}
	return (sum & 1) == 0 ? 1 : -1;
    }
    function add(a, b) {
	var result = a.slice(0);
	for (var i in b) {
	    if (result[i]) {
		result[i] += b[i];
	    } else {
		result[i] = b[i];
	    }
	}
	return result;
    }
    function mul(a, b)
    {
	var result = [];
	for (var i in a) {
	    if (a[i]) {
		for (var j in b) {
		    if (b[j]) {
			var s = reorderingSign(i, j) * a[i] * b[j];
			// if (i == 1 && j == 1) { s *= -1 }  // e0*e0 == -1
			var k = i ^ j;
			if (result[k]) {
			    result[k] += s;
			} else {
			    result[k] = s;
			}
		    }
		}
	    }
	}
	return result;
    }
    return {
	e   : e,
	cdot : cdot,
	neg : neg,
	add : add,
	mul : mul
    };
}();

// And then, from the console:

var e = GA.e, cdot = GA.cdot;
 
for (var i = 0; i < 5; i++) {
    for (var j = 0; j < 5; j++) {
        if (i < j) {
            if (cdot(e(i), e(j))[0]) { console.log("unexpected non-nul scalar product"); }
        } else if (i === j) {
            if (!cdot(e(i), e(j))[0]) { console.log("unexpected nul scalar product"); }
        }
    }
}
 
function randomVector() {
    var result = [];
    for (var i = 0; i < 5; i++) { result = GA.add( result, GA.mul([Math.random()], e(i))); }
    return result;
}
function randomMultiVector() {
    var result = [];
    for (var i = 0; i < 32; i++) { result[i] = Math.random(); }
    return result;
}



// var a = randomMultiVector(), b = randomMultiVector(), c = randomMultiVector();
// var x = randomVector();


a = [0,1,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 ];
b = [0,1,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 ];
c = [0,1,0,1,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 ];
x = [0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 ];
 
// (ab)c == a(bc)
console.log(GA.mul(GA.mul(a, b), c));
console.log(GA.mul(a, GA.mul(b, c)));
 
// a(b + c) == ab + ac
console.log(GA.mul(a, GA.add(b, c)));
console.log(GA.add(GA.mul(a,b), GA.mul(a, c)));
 
// (a + b)c == ac + bc
console.log(GA.mul(GA.add(a, b), c));
console.log(GA.add(GA.mul(a,c), GA.mul(b, c)));
 
// x² is real
console.log(GA.mul(x, x));


console.log(GA.mul(GA.mul(a, b), c));
console.log(GA.mul(a, GA.mul(b, c)));
