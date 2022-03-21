import SCR from "./algoritmos/SCR.js";
import FIFO from "./algoritmos/FIFO.js";
import LRU from "./algoritmos/LRU.js";
import NRU from "./algoritmos/NRU.js";

import * as fs from 'fs';

const args =  process.argv.slice(2);
var acessos = JSON.parse(fs.readFileSync("./acessos/" + args[0]));

const fifo = new FIFO(acessos, args[1]);
const scr = new SCR(acessos, args[1]);
const nru = new NRU(acessos, args[1]);
const lru = new LRU(acessos, args[1]);

console.log("FIFO: " + fifo.acessarPaginas());
console.log("SCR:  " + scr.acessarPaginas());
console.log("NRU:  " + nru.acessarPaginas());
console.log("LRU:  " + lru.acessarPaginas());
