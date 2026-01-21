const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question('Input: ', (ans) => {
    console.log('Hi! ' + ans + '.');
    rl.close();
});