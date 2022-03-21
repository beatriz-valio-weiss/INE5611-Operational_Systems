export default class LRU {
    constructor(acessos, quadros) {
        this.lista = [];
        this.tamanhoMaximo = quadros;
        this.qtdPageFault = 0;
        this.acessos = acessos;
    }

    atualizarUltimo() {
        this.ultimoAcessado = this.lista[0];
    }
    
    acessarPaginas() {
        this.acessos.forEach(e => {
            this.procurarPagina(e);
        });
        return this.qtdPageFault;
    }

    adicionar(pag) {
        if (this.tamanhoLRU() < this.tamanhoMaximo) {
            this.lista.unshift(pag);
        }
    }

    remover(ultimoAcessado) {
        if (!this.filaVazia()) {
            this.lista.pop();
        }
    }

    tamanhoLRU() {
        return this.lista.length;
    }

    filaVazia() {
        return this.lista.length === 0;
    }

    procurarPagina(pag) {
        if (!this.lista.some(e => e === pag)) {
            this.qtdPageFault++;
            if (this.tamanhoLRU() < this.tamanhoMaximo) {
                this.adicionar(pag);
            } else {
                this.remover(this.ultimoAcessado);
                this.adicionar(pag);
            }
        } else {
            let i = this.lista.indexOf(pag);

            while(i > 0) {
                let temp = this.lista[--i];
                this.lista[i] = this.lista[i+1];
                this.lista[i+1] = temp;
            }
        }
    }
}