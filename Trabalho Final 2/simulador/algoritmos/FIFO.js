export default class FIFO {
    constructor(acessos, quadros) {
        this.lista = [];
        this.tamanhoMaximo = quadros;
        this.qtdPageFault = 0;
        this.acessos = acessos;
    }
    
    acessarPaginas() {
        this.acessos.forEach(e => {
            this.procurarPagina(e);
        });
        return this.qtdPageFault;
    }

    adicionar(pag) {
        this.lista.push(pag);
    }

    remover() {
        return this.lista.shift();
    }

    procurarPagina(pag) {
        if (!this.lista.some(e => e === pag)) {
            this.qtdPageFault++;
            if (this.lista.length < this.tamanhoMaximo) {
                this.adicionar(pag);
            } else {
                this.remover();
                this.adicionar(pag);
            }
        }
    }
}