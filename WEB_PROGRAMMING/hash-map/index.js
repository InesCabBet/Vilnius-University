import {HashMap} from "./hashMap.js"; 

const test = new HashMap();

test.set('apple', 'red');
test.set('banana', 'yellow');
test.set('carrot', 'orange');
test.set('dog', 'brown');
test.set('elephant', 'gray');
test.set('frog', 'green');
test.set('grape', 'purple');
test.set('hat', 'black');
test.set('ice cream', 'white');
test.set('jacket', 'blue');
test.set('kite', 'pink');
test.set('lion', 'golden');

console.log(`Current Capacity: ${test.capacity}`);
console.log(`Current Length ${test.length()}`);

test.set('moon', 'silver');

console.log(`Current Capacity: ${test.capacity}`);
console.log(`Current Length ${test.length()}`);

console.log(`Get Value: ${test.get("apple")}`);
console.log(`Get Value: ${test.get("none")}`);
console.log(`Has Value: ${test.has("carrot")}`);
console.log(`Has Value ${test.has("none")}`);
console.log(`Remove Value ${test.remove("carrot")}`);
console.log(`Remove Value ${test.remove("none")}`);
console.log(`Current Length: ${test.length()}`);
console.log("All Keys: ", test.keys());
console.log("All Values: ", test.values());
console.log("All Entries: ", test.entries());
console.log(`Clear: ${test.clear()}`);
console.log("All Keys: ", test.keys());
console.log("All Values: ", test.values());
console.log("All Entries: ", test.entries());