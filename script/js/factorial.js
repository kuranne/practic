const readline = require('node:readline');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
})

function factorial(n) {
    if (n > 0) {
        return n * factorial(n - 1);
    }
    return 1;
}

rl.question('n: ', (n) => {
    console.log(factorial(n));
    rl.close();
});